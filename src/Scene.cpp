#include "StdAfx.h"

// Konstruktor.
CScene::CScene(void)
{
	mouse_velocity = 0;
	speedup_keys[0] = false;
	speedup_keys[1] = false;
	status = 0;
	arrow_dir = 0;
	move_wheel = false;
	timestamp = 0;
	spawned_bullet = false;


	SetConfig();


	pause = false;
	pause_pressed = false;
	pause_interval = 0;
	DrawCollisions = false;
	DrawNormals = false;
	MarkCollision = false;
#pragma region inicjacja funkcji
	_Nexus = new Nexus(1000);
	_enemy_models = new enemy_models;
	
	fonts_man.load_fonts();
	bullets = new manage_bullets;
	_HUD = new HUD(&fonts_man, &Player, _Nexus);
	_Coursor = new Coursor(&Player);
	_board = new board(_Coursor, _config);
	_Coursor->GetMapLimits(_board->mapk);
	_manage_enemy = new manage_enemy(_board, _enemy_models, _Nexus, &Player);
	_Turrets = new Turrets(_board->mapk, &Player);
	_Turrets->Get_Enemy_Pointer(_manage_enemy->enemies, _manage_enemy->max_enemies);
	
	_board->fetch_turret_pointer(_Turrets);
	_Coursor->Get_Turrets_Pointer(_Turrets);
	_HUD->Get_EnemyModels_Pointer(_enemy_models);
	_board->fetch_fonts_pointer(&fonts_man);
	_board->fetch_nexus_pointer(_Nexus);
	_board->fetch_HUD_Pointer(_HUD);
	_Turrets->Get_HUD_Pointer(_HUD);
	_HUD->Get_Turrets_Pointer(_Turrets);
	_manage_enemy->fetch_HUD_Pointer(_HUD);
	_HUD->Get_TimeStamp(&timestamp);
	_manage_enemy->fetch_Fonts_Pointer(&fonts_man);
	_HUD->Get_Actual_Map_Pointer(_board->mapk);
	_Turrets->Get_Player_Pointer(&Player);
	_Turrets->Get_Bullet_Pointer(bullets);
#pragma endregion
	time_game = 0;

}

// Destruktor - sprz¹tamy po sobie.
CScene::~CScene(void)
{
	if (Skydome != NULL) {
		delete Skydome;
	}
	if (Terrain != NULL) {
		delete Terrain;
	}
}

// Inicjalizacja sceny.
void CScene::Initialize(void) {
	
	#pragma region Ustawienia
		
		// Ustawienie wszelkiego rodzaju rzeczy, które s¹ charakterystyczne dla tej konkretnej sceny.
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		glEnable(GL_FOG);
		float gl_fogcolor[] = { 0.875f, 0.957f, 1.0f, 0.4f };
		glFogi(GL_FOG_MODE, GL_LINEAR);
		glFogfv(GL_FOG_COLOR, gl_fogcolor);
		glFogf(GL_FOG_START, 25.0f);
		glFogf(GL_FOG_END, 88.0f);
		float gl_amb[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gl_amb);

	
		Player.money = _board->mapk->conf->start_money;
		Player.pos.x = _board->mapk->conf->cam_pos.x;
		Player.pos.y = _board->mapk->conf->cam_pos.y;
		Player.pos.z = _board->mapk->conf->cam_pos.z;

		Player.dir.x = _board->mapk->conf->cam_dir.x;
		Player.dir.y = _board->mapk->conf->cam_dir.y;
		Player.dir.z = _board->mapk->conf->cam_dir.z;


		Player.pos_def = Player.pos.x;
		Player.dir_def = Player.dir_def;


		Player.speed = 7.8f;
		bullets->LoadModels();
		bullets->get_pointer_manage_enemy(_manage_enemy);
		_Turrets->Get_Coursor_Pointer(_Coursor);
		if(_config_display.FullScreen)
		glutFullScreen();

	#pragma endregion

	#pragma region Zawartosc sceny
	
		// Scena zawieraæ bêdzie skydome...
		Skydome = new CSkydome();
		Skydome->Initialize();

		// ...oraz teren.
		Terrain = new CTerrain();
		Terrain->Initialize();
		// Dodanie wszystkich obiektów sceny do wektora, po którym póŸniej bêdziemy iterowaæ chc¹c je rysowaæ.
		// Dlatego w³aœnie wygodnie jest, gdy wszystkie obiekty sceny dziedzicz¹ po jednej, wspólnej klasie bazowej (CSceneObject).

		Objects = new vector<CSceneObject *>();

		// Definicje po³o¿enia naszych œcian. Ka¿da kolejna czwórka wektorów to jeden quad.
		vec3 walls[][4] = {
			{ vec3( 1.0f,  0.0f, -3.0f), vec3( 1.0f,  1.0f, -3.0f), vec3( 0.0f,  1.0f, -3.0f), vec3( 0.0f,  0.0f, -3.0f) },
			{ vec3( 0.0f,  0.0f, -3.0f), vec3( 0.0f,  1.0f, -3.0f), vec3(-1.0f,  1.0f, -3.0f), vec3(-1.0f,  0.0f, -3.0f) },
			{ vec3(-1.0f,  0.0f, -3.0f), vec3(-1.0f,  1.0f, -3.0f), vec3(-1.0f,  1.0f, -1.0f), vec3(-1.0f,  0.0f, -1.0f) },
			{ vec3(-1.0f,  0.0f, -1.0f), vec3(-1.0f,  1.0f, -1.0f), vec3(-3.0f,  1.0f, -1.0f), vec3(-3.0f,  0.0f, -1.0f) },
			{ vec3(-3.0f,  0.0f, -1.0f), vec3(-3.0f,  1.0f, -1.0f), vec3(-1.0f,  1.0f,  1.0f), vec3(-1.0f,  0.0f,  1.0f) },
			{ vec3(-1.0f,  0.0f,  1.0f), vec3(-1.0f,  1.0f,  1.0f), vec3(-3.0f,  1.0f,  1.0f), vec3(-3.0f,  0.0f,  1.0f) },
			{ vec3(-3.0f,  0.0f,  2.0f), vec3(-3.0f,  1.0f,  2.0f), vec3(-1.0f,  1.0f,  2.0f), vec3(-1.0f,  0.0f,  2.0f) },
			{ vec3(-3.0f,  0.0f, -2.0f), vec3(-3.0f,  1.0f, -2.0f), vec3(-6.0f,  1.0f, -2.0f), vec3(-6.0f,  0.0f, -2.0f) },
			{ vec3(-3.0f,  0.0f,  1.0f), vec3(-3.0f,  1.0f,  1.0f), vec3(-3.0f,  1.0f, -2.0f), vec3(-3.0f,  0.0f, -2.0f) },
			{ vec3(-6.0f,  0.0f, -2.0f), vec3(-6.0f,  1.0f, -2.0f), vec3(-6.0f,  1.0f,  5.0f), vec3(-6.0f,  0.0f,  5.0f) },
			{ vec3(-6.0f,  0.0f,  5.0f), vec3(-6.0f,  1.0f,  5.0f), vec3(-4.0f,  1.0f,  4.0f), vec3(-4.0f,  0.0f,  4.0f) },
			{ vec3(-4.0f,  0.0f,  4.0f), vec3(-4.0f,  1.0f,  4.0f), vec3(-3.0f,  1.0f,  2.0f), vec3(-3.0f,  0.0f,  2.0f) },
			{ vec3(-5.5f,  0.0f,  0.0f), vec3(-5.0f,  0.3f,  1.0f), vec3(-4.0f,  0.3f,  1.0f), vec3(-4.0f,  0.0f,  0.0f) },
			{ vec3(-5.5f,  0.0f,  3.0f), vec3(-4.0f,  0.0f,  3.0f), vec3(-4.0f,  0.3f,  2.0f), vec3(-5.0f,  0.3f,  2.0f) },
			{ vec3(-5.0f,  0.3f,  1.0f), vec3(-5.0f,  0.3f,  2.0f), vec3(-4.0f,  0.3f,  2.0f), vec3(-4.0f,  0.3f,  1.0f) },
			{ vec3(-1.0f,  0.0f,  2.0f), vec3(-1.0f,  1.0f,  2.0f), vec3( 1.0f,  1.0f,  3.0f), vec3( 1.0f,  0.0f,  3.0f) },
			{ vec3( 1.0f,  0.0f,  3.0f), vec3( 1.0f,  1.0f,  3.0f), vec3( 4.0f,  1.0f,  0.0f), vec3( 4.0f,  0.0f,  0.0f) },
			{ vec3( 4.0f,  0.0f,  0.0f), vec3( 4.0f,  1.0f,  0.0f), vec3( 1.0f,  1.0f, -1.0f), vec3( 1.0f,  0.0f, -1.0f) },
			{ vec3( 1.0f,  0.0f, -1.0f), vec3( 1.0f,  1.0f, -1.0f), vec3( 1.0f,  1.0f, -3.0f), vec3( 1.0f,  0.0f, -3.0f) },
			{ vec3(-4.0f,  0.0f,  0.0f), vec3(-4.0f,  0.3f,  1.0f), vec3(-4.0f,  0.3f,  2.0f), vec3(-4.0f,  0.0f,  3.0f) },
			{ vec3(-5.5f,  0.0f,  0.0f), vec3(-5.5f,  0.0f,  3.0f), vec3(-5.0f,  0.3f,  2.0f), vec3(-5.0f,  0.3f,  1.0f) }
		};

		// Tyle mamy œcian.
		int N = 21;

		// Zamieniamy powy¿sz¹ tablicê na obiekty typu CWall, które dodamy do listy obiektów na scenie.
		for (int i = 0; i < N; ++i) {
			CWall *w = new CWall(walls[i][0], walls[i][1], walls[i][2], walls[i][3]);
			sprintf(w->Name, "Wall %d", i); // Nadanie nazwy, aby np. mo¿na by³o póŸniej ³atwo dowiedzieæ siê z czym mamy kolizjê.
			w->Initialize();
			Objects->push_back(w); // Dodanie do wektora rysowanych/przetwarzanych obiektów.
		}

	#pragma endregion
	
}

// Aktualizacja œwiata gry.
void CScene::Update(void) {
	
	if (_manage_enemy->victory)
	{
		status = 2;
		return;
	}

	if (Player.pos.x > -1)
		Player.pos.x = -1;

	if (Player.pos.x < -26)
		Player.pos.x = -26;

	if (Player.pos.z < -8)
		Player.pos.z = -8;

	if (Player.pos.z > 20)
		Player.pos.z = 20;



	if (status) {
#pragma region RESTART GRY
		if (keystate['R'] || keystate['r']) {
			_manage_enemy->Restart();
			_Nexus->reset();
			Player.reset_money();
			Player.add_money(_board->mapk->conf->start_money);
			_Turrets->reset();
			status = 0;

		}

		return;
	}

#pragma endregion

	if (!_board->mapk->wave_start) {
		if (keystate[32]) {
			_board->mapk->wave_start = true;
			if (_board->mapk->actual_wave == 1)
				_SoundManage->_Announcer_Prepare();
			else
				_SoundManage->_Announcer_New_Round();
		}

	}

	if (_Nexus->return_health() <= 0) {
		status = 1;
		return;
	}

	SpeedUpGame();


	if (pause_interval > 0)
		pause_interval -= 17;

	if (keystate[27] && pause_interval <= 0)
	{
		if (!pause_pressed) {
			pause_pressed = true;
			pause = !pause;
			pause_interval = 100;
		}
	}
	if (!keystate[27])
		pause_pressed = false;


	if (pause) {


		
		return;
	}


	#pragma region Ruch kamery

		bullets->Update();
		Terrain->Update();
		Skydome->Update();
		_Turrets->Update();


	_manage_enemy->Update();


	time_game += 17;
}

void CScene::CameraUpdate(void)
{

	if (pause) return;


	Player.velRY = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX);
	Player.velRX = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY);
	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	_Coursor->Update();


	if (move_wheel)
	{
		WheelMove();
	}

	_board->Update();
	Zoom_Fade_Camera();

	float T = acos(Player.dir.y);
	float G = atan2(Player.dir.z, Player.dir.x);
	T -= Player.velRX * .03f;
	G += Player.velRY * .03f;

	vec3 per;
	per.x = -Player.dir.z;
	per.y = 0;
	per.z = Player.dir.x;

	vec3 nextPlayerPos = Player.pos;

	nextPlayerPos.x += Player.dir.x * Player.velM * .1f;
	nextPlayerPos.y += Player.dir.y * Player.velM * .1f;

}

// Narysowanie sceny.
void CScene::Render(void) {

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_TEXTURE_2D);

	float l0_amb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float l0_dif[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l0_spe[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l0_pos[] = { 0, 1, 0, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0_spe);
	glLightfv(GL_LIGHT0, GL_POSITION, l0_pos);



	float l0_amb1[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	float l0_dif1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l0_spe1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float l0_pos1[] = { 0, 2, 0, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, l0_amb1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, l0_dif1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, l0_spe1);
	glLightfv(GL_LIGHT1, GL_POSITION, l0_pos1);

#pragma endregion

	shaders.Enable_Shader();
	


#pragma region Swiatlo

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

#pragma endregion




	timestamp = glutGet(GLUT_ELAPSED_TIME);
	#pragma region Kamera

		gluLookAt(
			Player.pos.x + Player.cam.x, Player.pos.y + Player.cam.y, Player.pos.z + Player.cam.z,
			Player.pos.x + Player.cam.x + Player.dir.x, Player.pos.y + Player.cam.y + Player.dir.y, Player.pos.z + Player.cam.z + Player.dir.z,
			0.0f, 1.0f, 0.0f
		);

	#pragma endregion


		_board->Render();
		shaders.Disable_Shader();
		_manage_enemy->Render(Player.pos);
		shaders.Enable_Shader();

		vec3 posit;
		posit.x = -4;
		posit.y = 0.5;
		posit.z = 0;

		


	#pragma region Skydome

		glDisable(GL_FOG); // Nie chcemy, by nasz zawsze odleg³y skydome by³ za mg³¹, bo nie by³oby go widaæ.

		Skydome->Position = Player.pos;
		Skydome->Render();
		
		glEnable(GL_FOG);

	#pragma endregion

	#pragma region Teren
		Terrain->Render();
		shaders.Disable_Shader();
		_Turrets->Render();
		_Coursor->Render();
		bullets->Render();
		shaders.Enable_Shader();
		shaders.Disable_Shader();
		if (status) {
			_HUD->Render_End_Game(status);
			return;
		}

		else {
			if (pause) {
				_HUD->Render_Pause();
			}
			else
			{
				_HUD->Render();
			}
		}
		shaders.Enable_Shader();
	#pragma endregion

}

void CScene::WheelZoom()
{
	if (Player.pos.y - 0.8 > 5)
		Player.pos.y -= 0.8;

}

void CScene::WheelBack()
{
	if (Player.pos.y + 0.8 < 22)
		Player.pos.y += 0.8;
	else
		Player.pos.y = 22;
}

void CScene::WheelMove()
{
	Player.pos.z += Player.velRY * 0.3;
	Player.pos.x += Player.velRX * 0.3;


}

void CScene::ArrowsControl(int key)
{

	switch (key) {
	case 0: Player.pos.x += 0.15; break;
	case 1: Player.pos.x -= 0.15; break;
	case 2: Player.pos.z -= 0.15; break;
	case 3: Player.pos.z += 0.15; break;

	}



	

}

void CScene::SpeedUpGame(void)
{

	if (keystate['+']) {

		if (!speedup_keys[0]) {
			speedup_keys[0] = true;
			gamespeed += 1.0;
		}
	}
	else
		speedup_keys[0] = false;



	if (keystate['-'] ) {

		if (!speedup_keys[1]) {
			speedup_keys[1] = true;
			gamespeed -= 1.0;
		}
	}
	else
		speedup_keys[1] = false;


	if (gamespeed > 6)
		gamespeed = 6;

	if (gamespeed < 1)
		gamespeed = 1;



}

void CScene::SetConfig(void)
{

	_config = new config;
	_config->min_money = 18;
	_config->max_money = 50;
	_config->max_enemies = 100;
	_config->cam_pos.x = -12.3467;
	_config->cam_pos.y = 12;
	_config->cam_pos.z = 5.42845;

	_config->cam_dir.x = 0.4299;
	_config->cam_dir.y = -0.892839;
	_config->cam_dir.z = 0;

	_config->max_health = 10000;
	_config->enemy_base_health = 50;
	_config->enemy_gain_health = 40;

	_config->start_interval = 1000;
	_config->interval_loose = 150;
	_config->min_interval = 450;
	_config->start_money = 500;


	_config->base_speed = 15;
	_config->increase_speed_per_wave = 1.3;
	_config->max_speed = 50;


}

void CScene::SetMouseVelocity(float value)
{
	mouse_velocity += value;

}

void CScene::Zoom_Fade_Camera()
{
	float max_velocity = mouse_velocity;

	if (mouse_velocity > 0.5)
	{
		max_velocity = 0.5;
		mouse_velocity = 0.5;
	}
		
	if (mouse_velocity < -0.5)
	{
		max_velocity = -0.5;
		mouse_velocity = -0.5;
	}
		


	Player.pos.y += max_velocity;

	if (mouse_velocity >= 0.07)
		mouse_velocity -= 0.035;

	if (mouse_velocity <= -0.07)
		mouse_velocity += 0.035;

	if (mouse_velocity < 0.07 && mouse_velocity > -0.07)
		mouse_velocity = 0;
	




	if (Player.pos.y < 6)
		Player.pos.y = 6;


	if (Player.pos.y > 28)
		Player.pos.y = 28;

	//cout << mouse_velocity << endl;

}


