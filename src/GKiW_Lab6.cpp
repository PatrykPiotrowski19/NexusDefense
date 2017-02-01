#include "stdafx.h"

#pragma region Zmienne globalne
	int mouseX = 0;
	int mouseY = 0;
	int frames = 0;
	float gamespeed = 1;
	int updatetime = 0;
	int updatetime_const = 0;
	int time_tmp;
	int test_var = 0;
	bool pressed_mouse_button;
	bool left_mouse_button = false;
	float T;

	bool captureMouse = true;
	bool free3DMovement = false;

	float mouseSensitivity = .15f;
	float mouse_velocity = 0;
	bool update = false;

	CScene * Scene;
	GLuint program;
	bool keystate[255];
	bool pause;
	config_display _config_display;
	SoundManage *_SoundManage;
	ALCcontext *context;
	ALCdevice *device;
	Shading shaders;


	HANDLE hThread;

#pragma endregion
	void mouseWheel(int, int, int, int);
	void SpecialInput(int key, int x, int y);
	void LoadConfig(char * argv[]);
	void __cdecl ThreadProc(void * Args);



int main(int argc, char* argv[])
{

	if (argc <= 1)
	{
		printf("Unable to start game. Use launcher to run.\n");
		return -1;
	}


	device = alcOpenDevice(nullptr);
	if (device == NULL)
	{
		cerr << "Error finding default Audio Output Device" << endl;
	}

	context = alcCreateContext(device, NULL);

	alcMakeContextCurrent(context);
	alGetError();

	updatetime = 0;
	pressed_mouse_button = false;
	srand(time(NULL));
	glutInit(&argc, argv);
	pause = false;
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1024, 768);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	


	_SoundManage = new SoundManage;
	LoadConfig(argv);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//glutGameModeString("1920x1080@60");
	//glutEnterGameMode();
	//glutCreateWindow("GKiW: Lab 6");
	glutCreateWindow("Nexus Defense");
	
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}


	shaders.LoadShaders();


	time_tmp = 0;
	//glutCreateWindow("Zombie Apocalypse");
	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);
	glutTimerFunc(17, OnTimer, 0);
	glutMouseWheelFunc(mouseWheel);
	glutMouseFunc(mouseWheel);
	glutSpecialFunc(SpecialInput);
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);
	
	mouseX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	mouseY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	//glutWarpPointer(mouseX, mouseY);
	glutSetCursor(GLUT_CURSOR_NONE);



	// Inicjalizacja sceny.
	Scene = new CScene();
	Scene->Initialize();
	hThread = (HANDLE)_beginthread(ThreadProc, 0, NULL);
	glutMainLoop();


	return 0;
}

#pragma region Obsluga wejscia

	void OnKeyPress(unsigned char key, int x, int y) {
		if (!keystate[key]) {
			if (key >= 'A' && key <= 'Z')
			{
				keystate[key] = false;

				key += 32;

			}
			keystate[key] = true;

			OnKeyDown(key, x, y);
		}
	}

	void OnKeyDown(unsigned char key, int x, int y) {
		if (key == 'X' || key == 'x') {
			glutLeaveMainLoop();
		}

		if (key == 'm' || key == 'M') {
			if (captureMouse) {
				captureMouse = false;
				glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
			}
			else {
				captureMouse = true;
				glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
				glutSetCursor(GLUT_CURSOR_NONE);
			}
		}
		if (key == 'l' || key == 'L') {
			free3DMovement = !free3DMovement;
		}
		if (key == 'k' || key == 'K') {
			// Rysowanie kolizji.
			Scene->DrawCollisions = !Scene->DrawCollisions;
		}
		if (key == 'n' || key == 'N') {
			// Rysowanie wektorów normalnych.
			Scene->DrawNormals = !Scene->DrawNormals;
		}
	}

	void OnKeyUp(unsigned char key, int x, int y) {
	
		if (key >= 'A' && key <= 'Z')
		{
			key += 32;
		}
			
		keystate[key] = false;
	}

	void mouseWheel(int button, int dir, int x, int y)
	{
		bool keys[3] = { 0,0,0 };

		// only start motion if the left button is pressed
		if ((button == GLUT_LEFT_BUTTON) && (dir == GLUT_DOWN)) {
				left_mouse_button = true;
			// when the button is released
				keys[0] = 1;
		}

		if ((button == GLUT_RIGHT_BUTTON) && (dir == GLUT_DOWN)){
			keys[1] = 1;
			
		}


			if (dir == 0 && !keys[0]) {
				Scene->move_wheel = true;
				pressed_mouse_button = true;
			}
			else
			{
				if (pressed_mouse_button) {
					pressed_mouse_button = 0;
					Scene->SetMouseVelocity(0.3);
				}


				Scene->move_wheel = false;
				if (dir > 0)
				{
					if (!left_mouse_button) {

						//Scene->WheelZoom();
						Scene->SetMouseVelocity(-0.3);

					}
					else
						left_mouse_button = false;

				}
				else
				{
					if (!keys[0]) {
						//Scene->WheelBack();
						Scene->SetMouseVelocity(0.3);
					}
				}

				return;
			}
		
	}

	void OnMouseMove(int x, int y) {
		mouseX = x;
		mouseY = y;
	}

	void SpecialInput(int key, int x, int y)
	{
		switch (key)
		{
		case GLUT_KEY_UP:
			Scene->ArrowsControl(0);
			break;
		case GLUT_KEY_DOWN:
			Scene->ArrowsControl(1);
			break;
		case GLUT_KEY_LEFT:
			Scene->ArrowsControl(2);
			break;
		case GLUT_KEY_RIGHT:
			Scene->ArrowsControl(3);
			break;

		}

		glutPostRedisplay();
	}


#pragma endregion


	void __cdecl ThreadProc(void * Args)
	{

	
	}


void OnTimer(int id) {



	int tmp = glutGet(GLUT_ELAPSED_TIME);

	glutTimerFunc(17, OnTimer, 0);
	//Scene->Update();


	++updatetime;
	if (time_tmp + 1000 < glutGet(GLUT_ELAPSED_TIME))
	{
		updatetime_const = updatetime;
		updatetime = 0;
		time_tmp = glutGet(GLUT_ELAPSED_TIME);
	}

}

void OnRender() {
	
	if (glutGet(GLUT_ELAPSED_TIME) >= test_var + 17) {

		Scene->CameraUpdate();


		for (int i = 0; i < gamespeed;i++)
		Scene->Update();
		test_var = glutGet(GLUT_ELAPSED_TIME);
	}


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	Scene->Render();

	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();
	++frames;
	T = glutGet(GLUT_ELAPSED_TIME);
}

void OnReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(48, 1.8, .01f, 300.0f);
}

void LoadConfig(char * argv[]) {

	FILE *fp = fopen("Data/config.cfg","r");

	if (!fp) {
		printf("Cannot load file config.cfg.");
		exit(-1);
	}

	char tmp_str[100];
	int value;

	#pragma region domyslne ustawienia gry
	
	_config_display.draw_fps = true;

	_config_display.Enemies_Quality = 1;
	_config_display.Turrets_Quality = 1;
	_config_display.Shadow_Quality = 0;
	
	_config_display.Sound_Enabled = true;
	_config_display.Music_Enabled = true;
	_config_display.Music_Volume = 20;
	_config_display.Sound_Volume = 20;
	_config_display.FullScreen = 1;
	
	char buff[10];

	
	_config_display.map_id = atoi(argv[1]);

	value = atoi(argv[2]);


	if(value == 0)
		_config_display.difficulty = 1.0;
	if(value == 1)
		_config_display.difficulty = 1.25;
	if(value == 2)
		_config_display.difficulty = 2.0;
	if (value == 3)
		_config_display.difficulty = 4.4;

	#pragma endregion



	while (fscanf(fp, "%s = %d", &tmp_str, &value) != -1) {

		if (strcmp(tmp_str, "Config.DrawFPS") == 0)
			_config_display.draw_fps = value;

		if (strcmp(tmp_str, "Config.TurretsQuality") == 0 && value <=3 && value >= 1)
			_config_display.Turrets_Quality = value;

		if (strcmp(tmp_str, "Config.EnemiesQuality") == 0 && value <= 3 && value >= 1)
			_config_display.Enemies_Quality = value;

		if (strcmp(tmp_str, "Config.ShadowQuality") == 0)
			_config_display.Shadow_Quality = value;

		if (strcmp(tmp_str, "Config.Sound") == 0)
			_config_display.Sound_Enabled = value;

		if (strcmp(tmp_str, "Config.SoundVolume") == 0)
			_config_display.Sound_Volume = value;

		if (strcmp(tmp_str, "Config.Music") == 0)
			_config_display.Music_Enabled = value;

		if (strcmp(tmp_str, "Config.MusicVolume") == 0)
			_config_display.Music_Volume = value;

		if (strcmp(tmp_str, "Config.FullScreen") == 0)
			_config_display.FullScreen = value;

	}



	printf("Config loaded\n");

}