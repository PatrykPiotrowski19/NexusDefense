#include "stdafx.h"
#include "Enemy.h"

long int time_game;

void manage_enemy::Set_Enemies_Attributes()
{

	#pragma region TIER 1

	#pragma region Minion Mage
	
	_enemy_base_info[0].enemy_id = 0;
	_enemy_base_info[0].health_mult = 1;
	_enemy_base_info[0].mov_speed_mult = 1;
	_enemy_base_info[0].reward_mult = 1;
	_enemy_base_info[0].dmg_mult = 1;

	#pragma endregion

	#pragma region Minion Melee

	_enemy_base_info[1].enemy_id = 1;
	_enemy_base_info[1].health_mult = 1.1;
	_enemy_base_info[1].mov_speed_mult = 1.05;
	_enemy_base_info[1].reward_mult = 1.1;
	_enemy_base_info[1].dmg_mult = 1.3;

#pragma endregion

	#pragma region Krug Mini

	_enemy_base_info[2].enemy_id = 2;
	_enemy_base_info[2].health_mult = 1.2;
	_enemy_base_info[2].mov_speed_mult = 1.08;
	_enemy_base_info[2].reward_mult = 1.15;
	_enemy_base_info[2].dmg_mult = 1.5;

	#pragma endregion

	#pragma region Raptor Mini

	_enemy_base_info[3].enemy_id = 3;
	_enemy_base_info[3].health_mult = 1.3;
	_enemy_base_info[3].mov_speed_mult = 1.15;
	_enemy_base_info[3].reward_mult = 1.2;
	_enemy_base_info[3].dmg_mult = 1.3;

	#pragma endregion

#pragma endregion

	#pragma region TIER 2

	#pragma region Gromp

	_enemy_base_info[4].enemy_id = 4;
	_enemy_base_info[4].health_mult = 1.45;
	_enemy_base_info[4].mov_speed_mult = 1.15;
	_enemy_base_info[4].reward_mult = 1.3;
	_enemy_base_info[4].dmg_mult = 1.5;

	#pragma endregion

	#pragma region Rider Chaos

	_enemy_base_info[5].enemy_id = 5;
	_enemy_base_info[5].health_mult = 1.55;
	_enemy_base_info[5].mov_speed_mult = 1.15;
	_enemy_base_info[5].reward_mult = 1.4;
	_enemy_base_info[5].dmg_mult = 1.5;

	#pragma endregion

	#pragma region Rider Order

	_enemy_base_info[6].enemy_id = 6;
	_enemy_base_info[6].health_mult = 1.6;
	_enemy_base_info[6].mov_speed_mult = 1.18;
	_enemy_base_info[6].reward_mult = 1.55;
	_enemy_base_info[6].dmg_mult = 1.5;

	#pragma endregion

	#pragma region Raptor

	_enemy_base_info[7].enemy_id = 7;
	_enemy_base_info[7].health_mult = 1.75;
	_enemy_base_info[7].mov_speed_mult = 1.2;
	_enemy_base_info[7].reward_mult = 1.68;
	_enemy_base_info[7].dmg_mult = 1.5;

	#pragma endregion

	#pragma endregion

	#pragma region TIER 3

	#pragma region Alistar

	_enemy_base_info[8].enemy_id = 8;
	_enemy_base_info[8].health_mult = 3.5;
	_enemy_base_info[8].mov_speed_mult = 1.25;
	_enemy_base_info[8].reward_mult = 2;
	_enemy_base_info[8].dmg_mult = 2.8;

#pragma endregion

	#pragma region Hecarim

	_enemy_base_info[9].enemy_id = 9;
	_enemy_base_info[9].health_mult = 2.8;
	_enemy_base_info[9].mov_speed_mult = 1.8;
	_enemy_base_info[9].reward_mult = 1.85;
	_enemy_base_info[9].dmg_mult = 2.8;

#pragma endregion

	#pragma region Galio

	_enemy_base_info[10].enemy_id = 10;
	_enemy_base_info[10].health_mult = 2.8;
	_enemy_base_info[10].mov_speed_mult = 1.5;
	_enemy_base_info[10].reward_mult = 1.85;
	_enemy_base_info[10].dmg_mult = 2.6;

#pragma endregion

	#pragma region Rammus

	_enemy_base_info[11].enemy_id = 11;
	_enemy_base_info[11].health_mult = 3.2;
	_enemy_base_info[11].mov_speed_mult = 1.65;
	_enemy_base_info[11].reward_mult = 1.95;
	_enemy_base_info[11].dmg_mult = 2.6;

#pragma endregion

	#pragma region Udyr

	_enemy_base_info[12].enemy_id = 12;
	_enemy_base_info[12].health_mult = 2.75;
	_enemy_base_info[12].mov_speed_mult = 1.75;
	_enemy_base_info[12].reward_mult = 1.85;
	_enemy_base_info[12].dmg_mult = 2.6;

#pragma endregion


	#pragma endregion

	#pragma region TIER 4

	#pragma region Herald

	_enemy_base_info[13].enemy_id = 13;
	_enemy_base_info[13].health_mult = 10;
	_enemy_base_info[13].mov_speed_mult = 1.35;
	_enemy_base_info[13].reward_mult = 8.5;
	_enemy_base_info[13].dmg_mult = 5;

	#pragma endregion


#pragma endregion

	#pragma region TIER 5

	#pragma region Evelynn

	_enemy_base_info[14].enemy_id = 13;
	_enemy_base_info[14].health_mult = 2.2;
	_enemy_base_info[14].mov_speed_mult = 1.6;
	_enemy_base_info[14].reward_mult = 1.75;
	_enemy_base_info[14].dmg_mult = 2.4;

	#pragma endregion

#pragma endregion
}

void manage_enemy::Render_Enemy(enemy *_enemy)
{
	char health_info[10];
	glEnable(GL_CULL_FACE);
	if (_enemy->enabled == true) {
		glPushMatrix();

#pragma region rysowanie paska zycia
		
		//rotation_value = Rotate_Info_To_Camera(cam_pos, enemies[i]->pos);
		glTranslatef(_enemy->pos.x, _enemy->pos.y, _enemy->pos.z);
		
		glPushMatrix();

		glDisable(GL_TEXTURE_2D);
		glTranslatef(0, 1.5, 0);
		glColor4f(0, 0, 0, 1.0);
		glPushMatrix();
		glScalef(0.05, 0.05, 0.25);
		glCallList(brick);
		glPopMatrix();


		float offset = 0;

		offset = 0.23 - (_enemy->health / _enemy->max_health)*0.23;

		glColor4f(0.2 + (_enemy->max_health - _enemy->health) / _enemy->max_health, _enemy->health / _enemy->max_health, 0, 0.7);
			glPushMatrix();
			glTranslatef(-0.015, 0.04, -offset);
		glScalef(0.03, 0.03, (_enemy->health/_enemy->max_health)*0.23);
		glCallList(brick);
		glPopMatrix();
		

		glPushMatrix();
		
		glRotatef(270, 0, 1, 0);
		glPushAttrib(GL_CURRENT_BIT);
		glColor4f(1, 1, 1,0.75);
		//glTranslatef(0.2, 1.5, 0.0);
		glTranslatef(0.00, 0, -0.15);

		sprintf(health_info, "%d",(int) _enemy->health);
		_Fonts_management->drawtext(health_info, 0, 1, 0.27);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPushAttrib(GL_CURRENT_BIT);
		//Rysowanie efektow na przeciwnikach
		
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glTranslatef(-0.17, 0, 0.38);
		glColor4f(1, 1, 1, 0.8);
		if (_enemy->slowed) {
			glBindTexture(GL_TEXTURE_2D, Enemy_Effects[0]->GetId());
			_Fonts_management->drawtext("CIRCLE", 0, 1, 0.3);
		}
		glTranslatef(0.22, 0, 0);
		if (_enemy->bleeding) {
			glBindTexture(GL_TEXTURE_2D, Enemy_Effects[1]->GetId());
			_Fonts_management->drawtext("CIRCLE", 0, 1, 0.3);
		}
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		
		glPopAttrib();
		
		glPopAttrib();
		glPopMatrix();

		
		
#pragma endregion

		glPopMatrix();

		glEnable(GL_TEXTURE_2D);

		if (_enemy->dir.x == 1)
			glRotatef(90, 0, 1, 0);
		if (_enemy->dir.x == -1)
			glRotatef(270, 0, 1, 0);
		if (_enemy->dir.z == -1)
			glRotatef(180, 0, 1, 0);

		//_enemy_models->Alistar.DrawModel(glutGet(GLUT_ELAPSED_TIME)*0.02);
		glScalef(0.8, 0.8, 0.8);
		glTranslatef(0, 0.05, 0);
		glColor4f(0.0, 1, 1,1);

		if (_enemy->slowed)
			shaders.Enable_SlowEffect();
		_enemy->model->DrawModel(_enemy->lifetime);

		if (_enemy->slowed)
			shaders.Disable_Shader();

		//_enemy_models->Alistar.DrawModel(glutGet(GLUT_ELAPSED_TIME)*0.001 * 7);
		glPopMatrix();
	}




}

void manage_enemy::fetch_HUD_Pointer(HUD * _HUD)
{
	this->_HUD = _HUD;
}

void manage_enemy::fetch_Fonts_Pointer(Fonts_management * _Fonts_management)
{

	this->_Fonts_management = _Fonts_management;

}

manage_enemy::manage_enemy(board * _board, enemy_models *_enemy_models, Nexus *_Nexus, CPlayer *Player)
{
	victory = false;
	ace_voice = false;
	losuj = 0;
	this->Player = Player;
	Time = 0;
	enemy_type_count = 5;
	restart = false;

	difficulty = 1;

	n = 0;
	interval = _board->mapk->conf->start_interval;
	T = 0;
	brick = LoadObj("Models/brick.obj");
	mov_speed = 0.001;
	this->_Nexus = _Nexus;
	this->_board = _board;
	this->_enemy_models = _enemy_models;
	max_enemies = _board->mapk->conf->max_enemies;
	for (int i = 0; i < max_enemies; i++)
		enemies[i] = new enemy;
	Set_Enemies_Attributes();

	for (int j = max_enemies; j < 1000; j++)
		enemies[j] = NULL;

	entraces_count = _board->mapk->entraces;
	start_coords = new vec3[entraces_count];
	actual_entrace = 0;
	int ent = 0;
	

	Enemy_Effects[0] = new CTexture("Data\\HUD\\Icons\\slow.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Enemy_Effects[1] = new CTexture("Data\\HUD\\Icons\\bleeding.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);


	//Ustalanie poczatku wejscia

	for (int i = 0; i < _board->mapk->y_size; i++) {

		for (int j = 0; j < _board->mapk->x_size; j++) {

			if (_board->mapk->map_v[i][j] == 1) {

				start_coords[ent].x = -i;
				start_coords[ent].z = j;
				start_coords[ent++].y = 0;
			}
		}


	}


	for (int s = 0; s < max_enemies; s++) {

		enemies[s]->enabled = false;
	}


}

void manage_enemy::Render(vec3 cam_pos)
{
	GLuint test;

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	for (int i = 0; i < max_enemies; i++)
	{

		Render_Enemy(enemies[i]);
		
	}

	glDisable(GL_TEXTURE_2D);

}

void manage_enemy::deal_field_damage(float radius, float damage, vec3 pos, enemy *_enemy)
{
	for (int i = 0; i < max_enemies; i++) {

		if (abs(enemies[i]->pos.x - pos.x) <= radius && abs(enemies[i]->pos.z - pos.z) <= radius && enemies[i] != _enemy) {


			float odl = sqrt(abs(enemies[i]->pos.x - pos.x) * abs(enemies[i]->pos.x - pos.x) + abs(enemies[i]->pos.z - pos.z) * abs(enemies[i]->pos.z - pos.z));

			if (odl < 1) odl = 1;
			enemies[i]->health -= damage / odl;

		}
	}


}

void manage_enemy::Move(enemy *enemies)
{
	if (enemies->enabled == false)
		return;
	#pragma region pobieranie wartosci dla przeciwnika
	found = false;


	//_enemy->speed * 2 * _enemy->anim_speed * !pause
	
	float max_speed = 100;

	if (enemies->slowed)
		max_speed = 100-enemies->slow_value;


	enemies->lifetime += enemies->speed * 2 * enemies->anim_speed * !pause * 0.025 * (max_speed/100);


	if (enemies->dir.x == 0 && enemies->dir.z == -1)
		tmp_z = round(enemies->pos.z + 0.48);
	else
		tmp_z = round(enemies->pos.z - 0.48);

	if(enemies->dir.x == -1 && enemies->dir.z == 0)
		tmp_x = round(enemies->pos.x + 0.48);
	else
		tmp_x = round(enemies->pos.x - 0.48);


	
	if (enemies->dir.x == -1 || enemies->dir.x == 1 && enemies->dir.z == 0) {

		enemies->pos.z= round(enemies->pos.z);
	}

	if (enemies->dir.z == -1 || enemies->dir.z == 1 && enemies->dir.x == 0) {

		enemies->pos.x = round(enemies->pos.x);
	}
	

	tmp_coord_x = -tmp_x;
	tmp_coord_z = tmp_z;

	float actual_speed;
	
	#pragma region nowa wartosc spowolnienia

	if (enemies->slowed)
		actual_speed = enemies->speed * ((100 - enemies->slow_value) / 100);
	else
		actual_speed = enemies->speed;

	#pragma endregion

	#pragma region efekt krwawienia

	if (enemies->bleeding) {

		if (enemies->bleeding_duration <= 0)
			enemies->bleeding = false;

		enemies->bleeding_duration -= 17;

		if (enemies->slowed)
			enemies->health -= enemies->bleeding_damage * 2;
		else
			enemies->health -= enemies->bleeding_damage;
	}

#pragma endregion

	#pragma region efekt spowolnienia

	if (enemies->slowed) {

		enemies->slowing_duration -= 17;


		if (enemies->slowing_duration <= 0)
		{
			enemies->slow_value = NULL;
			enemies->slowed = false;
		}


	}

#pragma endregion


#pragma region Poruszanie sie przeciwnika

	if (enemies->health < 1)
	{
		Clear_Enemy(enemies);
		Player->add_money(enemies->reward);
	}

	current_value = _board->mapk->map_v[tmp_coord_x][tmp_coord_z];

#pragma region modul_sterowania przeciwnikiem

	//Jezeli jest w nexusie
	if (_board->mapk->map_v[tmp_coord_x][tmp_coord_z] == 1000) {
		enemies->enabled = false;
		enemies->pos.x = 10;
		enemies->pos.z = 10;
		_Nexus->Remove_health(enemies->damage * 0.4);
		Clear_Enemy(enemies);
		return;
	}
	//sprawdza czy jest w obecnym polu
	if (enemies->target_value == _board->mapk->map_v[tmp_coord_x][tmp_coord_z]) {

		int paths[4][5];
		int found_paths = 0;

		//sprawdza kandydata na gorze (nad nim)
		if (tmp_coord_x - 1 >= 0)
			if (_board->mapk->map_v[tmp_coord_x - 1][tmp_coord_z] > enemies->target_value) {

				paths[found_paths][0] = 1;
				paths[found_paths][1] = 0;

				paths[found_paths][2] = 1;
				paths[found_paths][3] = 0;
				paths[found_paths++][4] = _board->mapk->map_v[tmp_coord_x - 1][tmp_coord_z];
			}

		//sprawdza kandydata na dole (pod nim)
		if(tmp_coord_x + 1 < _board->mapk->y_size)
			if (_board->mapk->map_v[tmp_coord_x + 1][tmp_coord_z] > enemies->target_value) {

				paths[found_paths][0] = -1;
				paths[found_paths][1] = 0;

				paths[found_paths][2] = -1;
				paths[found_paths][3] = 0;
				paths[found_paths++][4] = _board->mapk->map_v[tmp_coord_x + 1][tmp_coord_z];
			}

		//sprawdza kandydata na lewo
		if(tmp_coord_z - 1 >= 0)
			if (_board->mapk->map_v[tmp_coord_x][tmp_coord_z-1] > enemies->target_value) {

				paths[found_paths][0] = 0;
				paths[found_paths][1] = -1;

				paths[found_paths][2] = 0;
				paths[found_paths][3] = -1;
				paths[found_paths++][4] = _board->mapk->map_v[tmp_coord_x][tmp_coord_z-1];

			}

		//sprawdza kandydata na prawo
		if(tmp_coord_z + 1 < _board->mapk->x_size)
			if (_board->mapk->map_v[tmp_coord_x][tmp_coord_z + 1] > enemies->target_value) {

				paths[found_paths][0] = 0;
				paths[found_paths][1] = 1;

				paths[found_paths][2] = 0;
				paths[found_paths][3] = 1;
				paths[found_paths++][4] = _board->mapk->map_v[tmp_coord_x][tmp_coord_z + 1];

			}

		//losuje droge sposrod kandydatow na droge

		if (found_paths == 0) {

		}
		else

		if (found_paths == 1) {

			enemies->target_value = paths[0][4];
			
			enemies->path_x = paths[0][0];
			enemies->path_z = paths[0][1];
			
			enemies->dir.x = paths[0][2];
			enemies->dir.z = paths[0][3];

		}
		else
		{
			int random_value = rand() % found_paths;

			enemies->target_value = paths[random_value][4];
			
			enemies->path_x = paths[random_value][0];
			enemies->path_z = paths[random_value][1];

			enemies->dir.x = paths[random_value][2];
			enemies->dir.z = paths[random_value][3];

		}
	}
	//ma wyznaczona sciezke do ktorej ma sie udac
	else
	{
		enemies->pos.x += actual_speed * enemies->path_x * mov_speed;
		enemies->pos.z += actual_speed * enemies->path_z * mov_speed;

	}
	

#pragma endregion


}

void manage_enemy::Clear_Enemy(enemy * enemies)
{
	_board->mapk->slained_enemies[enemies->type]++;
	enemies->enabled = false;
	enemies->pos.x = 10;
	enemies->pos.z = 10;

	enemies->token = NULL;
	enemies->dir = NULL;
	enemies->bleeding = NULL;
	enemies->bleeding_damage = NULL;
	enemies->bleeding_duration = NULL;
	enemies->damage = NULL;
	enemies->health = NULL;
	enemies->lifetime = NULL;
	enemies->max_health = NULL;
	enemies->slowed = NULL;
	enemies->slowing_duration = NULL;
	enemies->slow_value = NULL;

	n++;
	_HUD->enemies_slained = n;

	//interval -= 3;
	//if (interval < _board->mapk->conf->min_interval)
	//	interval = _board->mapk->conf->min_interval;


	try
	{
		//delete enemies->model;
	}
	catch (exception& e)
	{
		cout << "BUG\n";
	}


}

void manage_enemy::New_Wave()
{
	if (!victory) {
		_board->mapk->wave_start = false;

		_board->mapk->actual_wave++;
		_board->mapk->bonus = 0;

		if (_board->mapk->actual_wave > _board->mapk->wave_count)
		{
			_board->mapk->actual_wave--;
			victory = true;
			return;
		}

		for (int i = 0; i < _board->mapk->enemy_count; i++) {

			_board->mapk->slained_enemies[i] = 0;
			_board->mapk->actual_enemies[i] = _board->mapk->enemies_waves[_board->mapk->actual_wave - 1][i];
			_board->mapk->bonus += _board->mapk->base_enemies[i] * 7;
			_board->mapk->base_enemies[i] = _board->mapk->enemies_waves[_board->mapk->actual_wave - 1][i];

		}

		if (restart)
		{
			_board->mapk->bonus = 0;
			restart = false;
		}
		
		actual_entrace = 0;
			Player->add_money((int)_board->mapk->bonus);



		interval -= _board->mapk->conf->interval_loose * _config_display.difficulty;

		if (interval < _board->mapk->conf->min_interval)
			interval = _board->mapk->conf->min_interval;

		ace_voice = false;

	}

}

void manage_enemy::Manage_Enemy()
{


	int iterations;

	if (_board->mapk->wave_start) {

		//Czy nie ma juz przeciwnikow
		if (T > interval) {


			int count = 0;

			for (int i = 0; i < _board->mapk->enemy_count; i++)
				count += _board->mapk->base_enemies[i] - _board->mapk->slained_enemies[i];

			if (count == 0) {
				if (!ace_voice) {
					_SoundManage->_Announcer_Ace();
					ace_voice = true;
				}
				New_Wave();
				return;
			}
				


			int avalible = 0;

			for (int i = 0; i < _board->mapk->enemy_count; i++)
				avalible += _board->mapk->actual_enemies[i];

			if (avalible == 0)
				return;



			for (int i = 0; i < max_enemies; i++) {
				if (!enemies[i]->enabled) {
					enemies[i]->move_dir = 0;
					enemies[i]->damage = 30 + (_board->mapk->actual_wave - 1) * 5;
					enemies[i]->health = _board->mapk->conf->enemy_base_health + (_board->mapk->actual_wave-1) * _board->mapk->conf->enemy_gain_health * _config_display.difficulty;

					if (enemies[i]->health > _board->mapk->conf->max_health)
						enemies[i]->health = _board->mapk->conf->max_health;

					enemies[i]->pos.x = start_coords[actual_entrace].x;
					enemies[i]->pos.z = start_coords[actual_entrace].z;
					enemies[i]->pos.y = start_coords[actual_entrace++].y;
					enemies[i]->speed = _board->mapk->conf->base_speed + (_board->mapk->actual_wave - 1) * _board->mapk->conf->increase_speed_per_wave * _config_display.difficulty;

					if (actual_entrace == entraces_count)
						actual_entrace = 0;

					if (enemies[i]->speed > _board->mapk->conf->max_speed)
						enemies[i]->speed = _board->mapk->conf->max_speed;

					enemies[i]->enabled = true;
					enemies[i]->reward = _board->mapk->conf->min_money + (_board->mapk->actual_wave - 1) * 1.3;

					if (enemies[i]->reward > _board->mapk->conf->max_money) {
						enemies[i]->reward = _board->mapk->conf->max_money;
					}

					enemies[i]->lifetime = 1;

					
					do {
						losuj = rand()%_board->mapk->enemy_count;
						//cout << losuj << endl;
					} while (_board->mapk->actual_enemies[losuj] <= 0);
					_board->mapk->actual_enemies[losuj]--;

					int id = _board->mapk->enemies[losuj];


					//enemies[i]->speed = 160;

					switch (id) {
					case 0: enemies[i]->model = new CMD2Model(&_enemy_models->Minion_Mage);  enemies[i]->anim_speed = 0.8; break;
					case 1: enemies[i]->model = new CMD2Model(&_enemy_models->Minion_Melee);  enemies[i]->anim_speed = 0.8; break;
					case 2: enemies[i]->model = new CMD2Model(&_enemy_models->Krug); enemies[i]->anim_speed = 0.6; break;
					case 3: enemies[i]->model = new CMD2Model(&_enemy_models->Raptor_Mini); enemies[i]->anim_speed = 1; break;
					case 4:	enemies[i]->model = new CMD2Model(&_enemy_models->Gromp); enemies[i]->anim_speed = 0.7; break;
					case 5: enemies[i]->model = new CMD2Model(&_enemy_models->RiderChaos);  enemies[i]->anim_speed = 1; break;
					case 6: enemies[i]->model = new CMD2Model(&_enemy_models->RiderOrder); enemies[i]->anim_speed = 0.7; break;
					case 7: enemies[i]->model = new CMD2Model(&_enemy_models->Raptor); enemies[i]->anim_speed = 0.7; break;
					case 8: enemies[i]->model = new CMD2Model(&_enemy_models->Alistar); enemies[i]->anim_speed = 1; break;
					case 9: enemies[i]->model = new CMD2Model(&_enemy_models->Hecarim); enemies[i]->anim_speed = 0.45; break;
					case 10: enemies[i]->model = new CMD2Model(&_enemy_models->Galio); enemies[i]->anim_speed = 0.7; break;
					case 11: enemies[i]->model = new CMD2Model(&_enemy_models->Rammus); enemies[i]->anim_speed = 0.6; break;
					case 12: enemies[i]->model = new CMD2Model(&_enemy_models->Udyr); enemies[i]->anim_speed = 0.4; break;
					case 13: enemies[i]->model = new CMD2Model(&_enemy_models->Herald); enemies[i]->anim_speed = 1.8; break;
					case 14: enemies[i]->model = new CMD2Model(&_enemy_models->Evelynn); enemies[i]->anim_speed = 0.7; break;

					}
					

					enemies[i]->target_value = 1;
					enemies[i]->speed *= _enemy_base_info[id].mov_speed_mult * difficulty;
					enemies[i]->health *= _enemy_base_info[id].health_mult * difficulty;
					enemies[i]->reward *= _enemy_base_info[id].reward_mult;
					enemies[i]->damage *= _enemy_base_info[id].dmg_mult * difficulty;
					enemies[i]->max_health = enemies[i]->health;

					enemies[i]->token = rand() % 1000000;



					//Efekty nalozone na postac
					enemies[i]->bleeding = false;
					enemies[i]->bleeding_duration = NULL;
					enemies[i]->bleeding_damage = NULL;

					enemies[i]->slowed = false;
					enemies[i]->slowing_duration = NULL;
					enemies[i]->slow_value = NULL;

					enemies[i]->dir.x = 0;
					enemies[i]->dir.z = 0;

					//enemies[i]->model = new CMD2Model(&_enemy_models->Raptor);

					enemies[i]->type = losuj;

					T = 0;

					if (actual_entrace != 0)
						T = interval;


					break;
				}
			}
		}
	}
}

void manage_enemy::Update()
{

	#pragma region aktualizacja poruszania dla przeciwników
	Manage_Enemy();
	for (int i = 0; i < max_enemies; i++)
	{

		Move(enemies[i]);
		//enemies[i]->health -= 0.04;
	}
		

#pragma endregion
	T+=17;
}

void manage_enemy::Restart()
{



	for (int i = 0; i < 1000; i++) {
		if (enemies[i] == NULL)
			break;
		enemies[i]->enabled = false;
		enemies[i]->pos.x = 10;
		enemies[i]->pos.z = 10;

	}
	interval = _board->mapk->conf->start_interval;
	_board->mapk->actual_wave = 0;
	_board->mapk->bonus = 0;
	restart = true;
	New_Wave();
	_HUD->NewGame();

}

float manage_enemy::Rotate_Info_To_Camera(vec3 cam_pos, vec3 enemy_pos)
{

	float odl_x = cam_pos.x - enemy_pos.x;
	float odl_z = cam_pos.z - enemy_pos.z;
	float przekatna = sqrt(abs(odl_x)*abs(odl_x) + abs(odl_z)*abs(odl_z));

	float kat = atan2(odl_x, odl_z) * 180 / PI + 180;
	return kat;
}

