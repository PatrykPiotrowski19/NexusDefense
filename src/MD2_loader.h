#pragma once

//
//	md2.h - header file
//
//	David Henry - tfc_duke@hotmail.com
//


#ifndef		__MD2_H
#define		__MD2_H



// number of precalculated normals
#define NUMVERTEXNORMALS		162

// precalculated normal vectors
#define SHADEDOT_QUANT			16

// magic number "IDP2" or 844121161
#define MD2_IDENT				(('2'<<24) + ('P'<<16) + ('D'<<8) + 'I')

// model version
#define	MD2_VERSION				8

// maximum number of vertices for a MD2 model
#define MAX_MD2_VERTS			2048



typedef float vec3_t[3];



// md2 header
typedef struct
{
	int		ident;				// magic number. must be equal to "IPD2"
	int		version;			// md2 version. must be equal to 8

	int		skinwidth;			// width of the texture
	int		skinheight;			// height of the texture
	int		framesize;			// size of one frame in bytes

	int		num_skins;			// number of textures
	int		num_xyz;			// number of vertices
	int		num_st;				// number of texture coordinates
	int		num_tris;			// number of triangles
	int		num_glcmds;			// number of opengl commands
	int		num_frames;			// total number of frames

	int		ofs_skins;			// offset to skin names (64 bytes each)
	int		ofs_st;				// offset to s-t texture coordinates
	int		ofs_tris;			// offset to triangles
	int		ofs_frames;			// offset to frame data
	int		ofs_glcmds;			// offset to opengl commands
	int		ofs_end;			// offset to the end of file

} md2_t;



// vertex
typedef struct
{
	unsigned char	v[3];				// compressed vertex' (x, y, z) coordinates
	unsigned char	lightnormalindex;	// index to a normal vector for the lighting

} vertex_t;



// frame
typedef struct
{
	float		scale[3];		// scale values
	float		translate[3];	// translation vector
	char		name[16];		// frame name
	vertex_t	verts[1];		// first vertex of this frame

} frame_t;



// animation
typedef struct
{
	int		first_frame;			// first frame of the animation
	int		last_frame;				// number of frames
	int		fps;					// number of frames per second

} anim_t;



// status animation
typedef struct
{
	int		startframe;				// first frame
	int		endframe;				// last frame
	int		fps;					// frame per second for this animation

	float	curr_time;				// current time
	float	old_time;				// old time
	float	interpol;				// percent of interpolation

	GLint		type;					// animation type

	int		curr_frame;				// current frame
	int		next_frame;				// next frame

} animState_t;



// animation list
typedef enum {
	//ANIMACJE POSTACI
	s1,
	s2,
	s3,
	s4,
	s5,
	s6,
	s7,
	s8,
	s9,
	s10,
	s11,
	s12,
	s13,
	s14,
	s15,
	s16,
	s17,
	s18,
	s19,
	s20,
	s21,
	s22,
	s23,
	s24,
	s25,
	s26,
	s27,
	s28,
	s29,
	s30,
	s31,
	s32,
	s33,
	s34,
	s35,
	s36,
	s37,
	s38,
	s39,
	s40,
	s41,
	s42,
	s43,
	s44,
	s45,
	s46,
	s47,
	s48,
	s49,
	s50,
	s51,
	s52,
	s53,
	s54,
	s55,
	s56,
	s57,
	s58,
	s59,
	s60,
	s61,
	s62,
	s63,
	s64,
	s65,
	s66,
	s67,
	s68,
	s69,
	s70,
	s71,
	s72,
	s73,
	s74,
	s75,
	s76,
	s77,
	s78,
	s79,
	s80,
	s81,
	s82,
	s83,
	s84,
	s85,
	s86,
	s87,
	s88,
	s89,
	s90,
	s91,
	s92,
	s93,
	s94,
	s95,
	s96,
	s97,
	s98,
	s99,
	s100,
		s101,
		s102,
		s103,
		s104,
		s105,
		s106,
		s107,
		s108,
		s109,
		s110,
		s111,
		s112,
		s113,
		s114,
		s115,
		s116,
		s117,
		s118,
		s119,
		s120,
		s121,
		s122,
		s123,
		s124,
		s125,
		s126,
		s127,
		s128,
		s129,
		s130,



	MAX_ANIMATIONS

} animType_t;



// ==============================================
// CMD2Model - MD2 model class object.
// ==============================================

class CMD2Model
{
public:
	// constructor/destructor
	CMD2Model(void);
	~CMD2Model(void);
	CMD2Model(CMD2Model *_CM2Model);


	// functions
	bool	LoadModel(const char *filename);
	bool	LoadSkin(const char *filename);

	void	DrawModel(float time);
	void	DrawFrame(int frame);

	void	SetAnim(int type);
	void	ScaleModel(float s) { m_scale = s; }


	void	Animate(float time);
	void	ProcessLighting(void);
	void	Interpolate(vec3_t *vertlist);
	void	RenderFrame(void);


	// member variables
	static vec3_t	anorms[NUMVERTEXNORMALS];
	static float	anorms_dots[SHADEDOT_QUANT][256];

	static anim_t	animlist[130];		// animation list

	int				is_reference;
	int				num_frames;			// number of frames
	int				num_xyz;			// number of vertices
	int				num_glcmds;			// number of opengl commands

	vec3_t			*m_vertices;		// vertex array
	int				*m_glcmds;			// opengl command array
	int				*m_lightnormals;	// normal index array

	GLuint			m_texid;			// texture id
	animState_t		m_anim;				// animation
	float			m_scale;			// scale value

};


#endif	// __MD2_H
