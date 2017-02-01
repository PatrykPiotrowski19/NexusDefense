#include"MD2_loader.h"
#include"MD2_texture.h"
#include"stdafx.h"


// precalculated normal vectors
vec3_t	CMD2Model::anorms[NUMVERTEXNORMALS] = {
#include	"anorms.h"
};

// precalculated dot product results
float	CMD2Model::anorms_dots[SHADEDOT_QUANT][256] = {
#include	"anormtab.h"
};


static float	*shadedots = CMD2Model::anorms_dots[0];
static vec3_t	lcolor;


/////////////////////////////////////////////////

vec3_t			g_lightcolor = { 1.0, 1.0, 1.0 };
int				g_ambientlight = 32;
float			g_shadelight = 128;
float			g_angle = 0.0;

/////////////////////////////////////////////////



// ----------------------------------------------
// constructor - reset all data.
// ----------------------------------------------

CMD2Model::CMD2Model(void)
{
	is_reference = 0;
	m_vertices = 0;
	m_glcmds = 0;
	m_lightnormals = 0;

	num_frames = 0;
	num_xyz = 0;
	num_glcmds = 0;

	m_texid = 0;
	m_scale = 1.0;

	SetAnim(0);
}



// ----------------------------------------------
// destructeur - free allocated memory.
// ----------------------------------------------

CMD2Model::~CMD2Model(void)
{
	if (is_reference == 0) {

		delete[] m_vertices;
		delete[] m_glcmds;
		delete[] m_lightnormals;

	}

}

//Konstruktor kopiujacy - bo tak xD

CMD2Model::CMD2Model(CMD2Model * _CM2Model)
{
	this->is_reference = 1;
	this->m_anim = _CM2Model->m_anim;
	this->m_glcmds = _CM2Model->m_glcmds;
	this->m_lightnormals = _CM2Model->m_lightnormals;
	this->m_scale = _CM2Model->m_scale;
	this->m_texid = _CM2Model->m_texid;
	this->m_vertices = _CM2Model->m_vertices;
	this->num_frames = _CM2Model->num_frames;
	this->num_glcmds = _CM2Model->num_glcmds;
	this->num_xyz = _CM2Model->num_xyz;

}



// ----------------------------------------------
// LoadModel() - load model from file.
// ----------------------------------------------

bool CMD2Model::LoadModel(const char *filename)
{
	std::ifstream	file;			// file stream
	md2_t			header;			// md2 header
	char			*buffer;		// buffer storing frame data
	frame_t			*frame;			// temporary variable
	vec3_t			*ptrverts;		// pointer on m_vertices
	GLint			*ptrnormals;	// pointer on m_lightnormals


									// try to open filename
	file.open(filename, std::ios::in | std::ios::binary);

	if (file.fail())
		return false;

	// read header file
	file.read((char *)&header, sizeof(md2_t));


	/////////////////////////////////////////////
	//		verify that this is a MD2 file

	// check for the ident and the version number

	if ((header.ident != MD2_IDENT) && (header.version != MD2_VERSION))
	{
		// this is not a MD2 model
		file.close();
		return false;
	}

	/////////////////////////////////////////////


	// initialize member variables
	num_frames = header.num_frames;
	num_xyz = header.num_xyz;
	num_glcmds = header.num_glcmds;


	// allocate memory
	m_vertices = new vec3_t[num_xyz * num_frames];
	m_glcmds = new GLint[num_glcmds];
	m_lightnormals = new GLint[num_xyz * num_frames];
	buffer = new char[num_frames * header.framesize];


	/////////////////////////////////////////////
	//			reading file data

	// read frame data...
	file.seekg(header.ofs_frames, std::ios::beg);
	file.read((char *)buffer, num_frames * header.framesize);

	// read opengl commands...
	file.seekg(header.ofs_glcmds, std::ios::beg);
	file.read((char *)m_glcmds, num_glcmds * sizeof(int));

	/////////////////////////////////////////////


	// vertex array initialization
	for (int j = 0; j < num_frames; j++)
	{
		// ajust pointers
		frame = (frame_t *)&buffer[header.framesize * j];
		ptrverts = &m_vertices[num_xyz * j];
		ptrnormals = &m_lightnormals[num_xyz * j];

		for (int i = 0; i < num_xyz; i++)
		{
			ptrverts[i][0] = (frame->verts[i].v[0] * frame->scale[0]) + frame->translate[0];
			ptrverts[i][1] = (frame->verts[i].v[1] * frame->scale[1]) + frame->translate[1];
			ptrverts[i][2] = (frame->verts[i].v[2] * frame->scale[2]) + frame->translate[2];

			ptrnormals[i] = frame->verts[i].lightnormalindex;
		}
	}


	// free buffer's memory
	delete[] buffer;

	// close the file and return
	file.close();
	return true;
}



// ----------------------------------------------
// LoadSkin() - load model texture.
// ----------------------------------------------

bool CMD2Model::LoadSkin(const char *filename)
{
	m_texid = LoadTexture(filename);

	return (m_texid != LoadTexture("default"));
}



// ----------------------------------------------
// DrawModel() - draw the model.
// ----------------------------------------------

void CMD2Model::DrawModel(float time)
{
	// animate. calculate current frame and next frame
	if (time > 0.0)
		Animate(time);

	glPushMatrix();
	// rotate the model
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glRotatef(-90.0, 0.0, 0.0, 1.0);

	// render it on the screen
	RenderFrame();
	glPopMatrix();
}



// ----------------------------------------------
// Animate() - calculate the current frame, next
// frame and interpolation percent.
// ----------------------------------------------

void CMD2Model::Animate(float time)
{
	m_anim.curr_time = time;

	// calculate current and next frames
	if (m_anim.curr_time - m_anim.old_time > (1.0 / m_anim.fps))
	{
		m_anim.curr_frame = m_anim.next_frame;
		m_anim.next_frame++;

		if (m_anim.next_frame > m_anim.endframe)
			m_anim.next_frame = m_anim.startframe;

		m_anim.old_time = m_anim.curr_time;
	}

	// prevent having a current/next frame greater
	// than the total number of frames...
	if (m_anim.curr_frame > (num_frames - 1))
		m_anim.curr_frame = 0;

	if (m_anim.next_frame > (num_frames - 1))
		m_anim.next_frame = 0;

	m_anim.interpol = m_anim.fps * (m_anim.curr_time - m_anim.old_time);
}



// ----------------------------------------------
// ProcessLighting() - process all lighting calculus.
// ----------------------------------------------

void CMD2Model::ProcessLighting(void)
{
	float lightvar = (float)((g_shadelight + g_ambientlight) / 256.0);

	lcolor[0] = g_lightcolor[0] * lightvar;
	lcolor[1] = g_lightcolor[1] * lightvar;
	lcolor[2] = g_lightcolor[2] * lightvar;

	shadedots = anorms_dots[((int)(g_angle * (SHADEDOT_QUANT / 360.0))) & (SHADEDOT_QUANT - 1)];
}



// ----------------------------------------------
// Interpolate() - interpolate and scale vertices
// from the current and the next frame.
// ----------------------------------------------

void CMD2Model::Interpolate(vec3_t *vertlist)
{
	vec3_t	*curr_v;	// pointeur to current frame vertices
	vec3_t	*next_v;	// pointeur to next frame vertices

						// create current frame and next frame's vertex list
						// from the whole vertex list
	curr_v = &m_vertices[num_xyz * m_anim.curr_frame];
	next_v = &m_vertices[num_xyz * m_anim.next_frame];

	// interpolate and scale vertices to avoid ugly animation
	for (int i = 0; i < num_xyz; i++)
	{
		vertlist[i][0] = (curr_v[i][0] + m_anim.interpol * (next_v[i][0] - curr_v[i][0])) * m_scale;
		vertlist[i][1] = (curr_v[i][1] + m_anim.interpol * (next_v[i][1] - curr_v[i][1])) * m_scale;
		vertlist[i][2] = (curr_v[i][2] + m_anim.interpol * (next_v[i][2] - curr_v[i][2])) * m_scale;
	}
}



// ----------------------------------------------
// RenderFrame() - draw the current model frame
// using OpenGL commands.
// ----------------------------------------------

void CMD2Model::RenderFrame(void)
{
	static vec3_t	vertlist[MAX_MD2_VERTS];	// interpolated vertices
	int				*ptricmds = m_glcmds;		// pointer on gl commands


												// reverse the orientation of front-facing
												// polygons because gl command list's triangles
												// have clockwise winding
	glPushAttrib(GL_POLYGON_BIT);
	glFrontFace(GL_CW);

	// enable backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);


	// process lighting
	ProcessLighting();

	// interpolate
	Interpolate(vertlist);

	// bind model's texture
	glBindTexture(GL_TEXTURE_2D, m_texid);
	// draw each triangle!
	while (int i = *(ptricmds++))
	{
		if (i < 0)
		{
			glBegin(GL_TRIANGLE_FAN);
			i = -i;
		}
		else
		{
			glBegin(GL_TRIANGLE_STRIP);
		}


		for ( /* nothing */; i > 0; i--, ptricmds += 3)
		{
			// ptricmds[0] : texture coordinate s
			// ptricmds[1] : texture coordinate t
			// ptricmds[2] : vertex index to render

			float l = shadedots[m_lightnormals[ptricmds[2]]];

			// set the lighting color
			glColor3f(l * lcolor[0], l * lcolor[1], l * lcolor[2]);

			// parse texture coordinates
			glTexCoord2f(((float *)ptricmds)[0], ((float *)ptricmds)[1]);

			// parse triangle's normal (for the lighting)
			// >>> only needed if using OpenGL lighting
			glNormal3fv(anorms[m_lightnormals[ptricmds[2]]]);

			// draw the vertex
			glVertex3fv(vertlist[ptricmds[2]]);
		}

		glEnd();
	}
	glDisable(GL_CULL_FACE);
	glPopAttrib();
}



// ----------------------------------------------
// RenderFrame() - draw one frame of the model
// using gl commands.
// ----------------------------------------------

void CMD2Model::DrawFrame(int frame)
{
	// set new animation parameters...
	m_anim.startframe = frame;
	m_anim.endframe = frame;
	m_anim.next_frame = frame;
	m_anim.fps = 1;
	m_anim.type = -1;

	// draw the model
	DrawModel(1.0);
}



// ----------------------------------------------
// initialize the 21 MD2 model animations.
// ----------------------------------------------

anim_t CMD2Model::animlist[130] =
{
	// first, last, fps

	{ 1,  0,  1 },	// ALISTAR
	{ 1,  1, 1 },	// MINION CANNON
	{ 1,  2, 1 },	// FAST RUN
	{ 1,  3,  1 },	// 
	{ 1,  4,  1 },	// 
	{ 1,  5,  1 },	// 
	{ 1,  6,  1 },	// 
	{ 1,  7,  1 },	// 
	{ 1,  8,  1 },	// 
	{ 1,  9,  1 },	// 
	{ 1,  0,  1 },	// ALISTAR
	{ 1,  11, 1 },	// MINION CANNON
	{ 1,  12, 1 },	// FAST RUN
	{ 1,  13,  1 },	// 
	{ 1,  14,  1 },	// 
	{ 1,  15,  1 },	// 
	{ 1,  16,  1 },	// 
	{ 1,  17,  1 },	// 
	{ 1,  18,  1 },	// 
	{ 1,  19,  1 },	// 
	{ 1,  20,  1 },	// ALISTAR
	{ 1,  21, 1 },	// MINION CANNON
	{ 1,  22, 1 },	// FAST RUN
	{ 1,  23,  1 },	// 
	{ 1,  24,  1 },	// 
	{ 1,  25,  1 },	// 
	{ 1,  26,  1 },	// 
	{ 1,  27,  1 },	// 
	{ 1,  28,  1 },	// 
	{ 1,  29,  1 },	// 
	{ 1,  30,  1 },	// ALISTAR
	{ 1,  31, 1 },	// MINION CANNON
	{ 1,  32, 1 },	// FAST RUN
	{ 1,  33,  1 },	// 
	{ 1,  34,  1 },	// 
	{ 1,  35,  1 },	// 
	{ 1,  36,  1 },	// 
	{ 1,  37,  1 },	// 
	{ 1,  38,  1 },	// 
	{ 1,  39,  1 },	// 
	{ 1,  40,  1 },	// ALISTAR
	{ 1,  41, 1 },	// MINION CANNON
	{ 1,  42, 1 },	// FAST RUN
	{ 1,  43,  1 },	// 
	{ 1,  44,  1 },	// 
	{ 1,  45,  1 },	// 
	{ 1,  46,  1 },	// 
	{ 1,  47,  1 },	// 
	{ 1,  48,  1 },	// 
	{ 1,  49,  1 },	// 
	{ 1,  50,  1 },	// ALISTAR
	{ 1,  51, 1 },	// MINION CANNON
	{ 1,  52, 1 },	// FAST RUN
	{ 1,  53,  1 },	// 
	{ 1,  54,  1 },	// 
	{ 1,  55,  1 },	// 
	{ 1,  56,  1 },	// 
	{ 1,  57,  1 },	// 
	{ 1,  58,  1 },	// 
	{ 1,  59,  1 },	// 
	{ 1,  60,  1 },	// ALISTAR
	{ 1,  61, 1 },	// MINION CANNON
	{ 1,  62, 1 },	// FAST RUN
	{ 1,  63,  1 },	// 
	{ 1,  64,  1 },	// 
	{ 1,  65,  1 },	// 
	{ 1,  66,  1 },	// 
	{ 1,  67,  1 },	// 
	{ 1,  68,  1 },	// 
	{ 1,  69,  1 },	// 
	{ 1,  70,  1 },	// ALISTAR
	{ 1,  71, 1 },	// MINION CANNON
	{ 1,  72, 1 },	// FAST RUN
	{ 1,  73,  1 },	// 
	{ 1,  74,  1 },	// 
	{ 1,  75,  1 },	// 
	{ 1,  76,  1 },	// 
	{ 1,  77,  1 },	// 
	{ 1,  78,  1 },	// 
	{ 1,  79,  1 },	// 
	{ 1,  80,  1 },	// ALISTAR
	{ 1,  81, 1 },	// MINION CANNON
	{ 1,  82, 1 },	// FAST RUN
	{ 1,  83,  1 },	// 
	{ 1,  84,  1 },	// 
	{ 1,  85,  1 },	// 
	{ 1,  86,  1 },	// 
	{ 1,  87,  1 },	// 
	{ 1,  88,  1 },	// 
	{ 1,  89,  1 },	// 
	{ 1,  90,  1 },	// ALISTAR
	{ 1,  91, 1 },	// MINION CANNON
	{ 1,  92, 1 },	// FAST RUN
	{ 1,  93,  1 },	// 
	{ 1,  94,  1 },	// 
	{ 1,  95,  1 },	// 
	{ 1,  96,  1 },	// 
	{ 1,  97,  1 },	// 
	{ 1,  98,  1 },	// 
	{ 1,  99,  1 },	// 
	{ 1,  100,  1 },	// ALISTAR
	{ 1,  101, 1 },	// MINION CANNON
	{ 1,  102, 1 },	// FAST RUN
	{ 1,  103,  1 },	// 
	{ 1,  104,  1 },	// 
	{ 1,  105,  1 },	// 
	{ 1,  106,  1 },	// 
	{ 1,  107,  1 },	// 
	{ 1,  108,  1 },	// 
	{ 1,  109,  1 },	// 
	{ 1,  110,  1 },	// ALISTAR
	{ 1,  111, 1 },	// MINION CANNON
	{ 1,  112, 1 },	// FAST RUN
	{ 1,  113,  1 },	// 
	{ 1,  114,  1 },	// 
	{ 1,  115,  1 },	// 
	{ 1,  116,  1 },	// 
	{ 1,  117,  1 },	// 
	{ 1,  118,  1 },	// 
	{ 1,  119,  1 },	// 
	{ 1,  120,  1 },	// ALISTAR
	{ 1,  121, 1 },	// MINION CANNON
	{ 1,  122, 1 },	// FAST RUN
	{ 1,  123,  1 },	// 
	{ 1,  124,  1 },	// 
	{ 1,  125,  1 },	// 
	{ 1,  126,  1 },	// 
	{ 1,  127,  1 },	// 
	{ 1,  128,  1 },	// 
	{ 1,  129,  1 },	// 

};



// ----------------------------------------------
// SetAnim() - initialize m_anim from the specified
// animation.
// ----------------------------------------------

void CMD2Model::SetAnim(int type)
{
	if ((type < 0) || (type > MAX_ANIMATIONS))
		type = 0;

	m_anim.startframe = animlist[type].first_frame;
	m_anim.endframe = animlist[type].last_frame;
	m_anim.next_frame = animlist[type].first_frame + 1;
	m_anim.fps = animlist[type].fps;
	m_anim.type = type;
}
