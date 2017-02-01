#include "stdafx.h"
#include "Board.h"
#include "Coursor.h"
#include "Turrets.h"



board::board(Coursor *_Coursor, config *_config)
{
	_zoom_board.pos[0] = 0;
	_zoom_board.pos[1] = 0;
	_zoom_board.scale = 0;


	this->_config = _config;
	this->_Coursor = _Coursor;
	_stone_texture = new CTexture("Resources\\Stone.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	_nexus = new CTexture("Resources\\Nexus.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	brick = LoadObj("Models/brick.obj");
	nexus_obj = LoadObj("Models/nexus.obj");
	_brick = new CTexture("Resources\\Brick.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	//cout << "BRICK ID " << brick << endl;
	load_maps();
	int select;
	//cout << "LOADED " << map_count << " MAPS: \n";
	/*for (int i = 0; i < map_count; i++) {

		cout << "ID " << i + 1 << "\tNAME: " << maps[i]->name << endl;
	}
	cout << "SELECT MAP (WRITE ID)\n";
	cin >> select;
	cout << "PRESS ALT-TAB TO HIDE CONSOLE\n";
	*/
	
	if (_config_display.map_id < 0 || _config_display.map_id >= map_count)
		mapk = maps[0];
	else
		mapk = maps[_config_display.map_id];

}

void board::fetch_turret_pointer(Turrets * _Turrets)
{
	this->_Turrets = _Turrets;
}

void board::assign_config(config * _conf)
{
	_conf->cam_dir.x = _config->cam_dir.x;
	_conf->cam_dir.y = _config->cam_dir.y;
	_conf->cam_dir.z = _config->cam_dir.z;

	_conf->cam_pos.x = _config->cam_pos.x;
	_conf->cam_pos.y = _config->cam_pos.y;
	_conf->cam_pos.z = _config->cam_pos.z;

	_conf->max_enemies = _config->max_enemies;
	_conf->max_health = _config->max_health;
	_conf->max_money = _config->max_money;
	_conf->max_speed = _config->max_speed;

	_conf->start_interval = _config->start_interval;
	_conf->interval_loose = _config->interval_loose;
	_conf->min_interval = _config->min_interval;

	_conf->base_speed = _config->base_speed;
	_conf->increase_speed_per_wave = _config->increase_speed_per_wave;

	_conf->enemy_base_health = _config->enemy_base_health;
	_conf->start_money = _config->start_money;
	_conf->enemy_gain_health = _config->enemy_gain_health;
	_conf->min_money = _config->min_money;

}

void board::fetch_HUD_Pointer(HUD * _HUD)
{
	this->_HUD = _HUD;
}

void board::fetch_nexus_pointer(Nexus * _Nexus)
{
	this->_Nexus = _Nexus;
}

void board::fetch_fonts_pointer(Fonts_management *_Fonts_management)
{
	this->_Fonts_management = _Fonts_management;

}

void board::load_maps()
{

	char info[50];
	char info2[50];
	int tmp;
	FILE *fp = fopen("Data/Levels/Levels.dat", "r");

	if (!fp) {
		cout << "Error: Cannot load file Levels.dat\n";
		exit(-1);
	}
		//cout << "Succesfully opened map\n";

	//Czytanie naglowka pliku - informacje o ilosci map
		fscanf(fp,"%s = %d",&info,&map_count);
		//cout << info << " = " << map_count << endl;

	//Alokacja pamieci na mapy
		maps =(map **) new map;

		for (int i = 0; i < map_count;i++) {
			maps[i] = new map;
		}

		while (fscanf(fp, "%d.%s = %s", &tmp, &info, &info2) !=-1) {
			//cout << tmp << "\t" << info << "\t" << info2 << endl;

			if (strcmp(info,"Name") == 0) {
				maps[tmp]->name = info2;
			//	cout << maps[tmp]->name << endl;
			}
			if (strcmp(info, "Dir") == 0) {

				load_maps_spec(info2, maps[tmp]);

			}

			if (strcmp(info, "Wave") == 0) {

				load_wave_info(info2, maps[tmp]);

			}



		}

		fclose(fp);
}


void board::load_maps_spec(char dir[100], map * tmp)
{
	char tmp_str[100];
	float value;
	int value_dec;
	//cout << "Name\t" << dir << endl;
	FILE *fp = fopen(dir, "r");

	tmp->conf = new config;
	assign_config(tmp->conf);


	if (!fp) {
		cout << "Error: Cannot load file "<<dir<<"\n";
		exit(-1);
	}

	tmp->entraces = 1;

	//cout << "Succesfully opened file "<<dir<<"\n";
	while (fscanf(fp, "%s = %f", &tmp_str, &value) != -1) {

		if (strcmp(tmp_str, "Level.dim_x") == 0)
			tmp->x_size = value;

		if (strcmp(tmp_str, "Level.entraces") == 0)
			tmp->entraces = value;

		if (strcmp(tmp_str, "Level.dim_y") == 0)
			tmp->y_size = value;

		if (strcmp(tmp_str, "Level.max_enemies") == 0)
			tmp->conf->max_enemies = value;

		if (strcmp(tmp_str, "Level.max_money") == 0)
			tmp->conf->max_money = value;

		if (strcmp(tmp_str, "Level.max_health") == 0)
			tmp->conf->max_health = value;

		if (strcmp(tmp_str, "Level.max_speed") == 0)
			tmp->conf->max_speed = value;

		if (strcmp(tmp_str, "Level.min_interval") == 0)
			tmp->conf->min_interval = value;

		if (strcmp(tmp_str, "Level.pos_x") == 0)
			tmp->conf->cam_pos.x = value;

		if (strcmp(tmp_str, "Level.pos_y") == 0)
			tmp->conf->cam_pos.y = value;

		if (strcmp(tmp_str, "Level.pos_z") == 0)
			tmp->conf->cam_pos.z = value;

		if (strcmp(tmp_str, "Level.dir_x") == 0)
			tmp->conf->cam_dir.x = value;

		if (strcmp(tmp_str, "Level.dir_y") == 0)
			tmp->conf->cam_dir.y = value;

		if (strcmp(tmp_str, "Level.dir_z") == 0)
			tmp->conf->cam_dir.z = value;

		if (strcmp(tmp_str, "Level.start_money") == 0)
			tmp->conf->start_money = value;

		if (strcmp(tmp_str, "Level.base_speed") == 0)
			tmp->conf->base_speed = value;

		if (strcmp(tmp_str, "Level.increase_base_speed_per_wave") == 0)
			tmp->conf->increase_speed_per_wave = value;

		if (strcmp(tmp_str, "Level.start_interval") == 0)
			tmp->conf->start_interval = value;

		if (strcmp(tmp_str, "Level.interval_loose_per_wave ") == 0)
			tmp->conf->interval_loose = value;

		if (strcmp(tmp_str, "Level.base_health") == 0)
			tmp->conf->enemy_base_health = value;

		if (strcmp(tmp_str, "Level.gain_health") == 0)
			tmp->conf->enemy_gain_health = value;

		if (strcmp(tmp_str, "Level.min_money") == 0)
			tmp->conf->min_money = value;




		if (strcmp(tmp_str, "Level.map") == 0 )
			break;
	}
	//cout << "x_size =" << tmp->x_size << " y_size =" << tmp->y_size << endl;



	#pragma region alokacja pamieci na mape

	tmp->map_v =(int **) new int *[tmp->y_size];

	for (int i = 0; i < tmp->y_size; i++) {
		tmp->map_v[i] = new int[tmp->x_size];
	}



	#pragma endregion
	int i = 0, j = 0;
			while (fscanf(fp, "%d", &value_dec) != -1) {
			
				tmp->map_v[i][j++] = value_dec;
				if (j >= tmp->x_size)
				{
					j = 0;
					i++;
				}
			}

		//	cout << "MAP " << dir << " loaded succesfully \n\n";
/*			for (int i = 0; i < tmp->y_size; i++) {
				for (int j = 0; j < tmp->x_size; j++) {
					cout << tmp->map_v[i][j] << "\t";

				}
				cout << "\n";
			}
		*/	


	fclose(fp);

}

void board::load_wave_info(char wavedir[100], map * tmp)
{
	char tmp_str[100];
	char info[100];
	char info2[100];
	int value;
	int i;
	tmp->actual_wave = 1;
	tmp->wave_start = 0;
	tmp->bonus = 0;


	//cout << "Loading wave info" << wavedir << endl;
	FILE *fp = fopen(wavedir, "r");


	if (!fp) {
		cout << "Error: Cannot load wavefile " << wavedir << "\n";
		exit(-1);
	}

	tmp->wave_count = 0;
	tmp->enemy_count = 0;

	while (fscanf(fp, "%s = %d", &tmp_str, &value) != -1) {


		if (strcmp(tmp_str, "Wave.waves") == 0)
			tmp->wave_count = value;
	
		if (strcmp(tmp_str, "Wave.enemies") == 0)
			tmp->enemy_count = value;

		if(tmp->wave_count != 0 && tmp->enemy_count != 0)
			break;
	}

	tmp->enemies = new int[tmp->enemy_count];
	tmp->slained_enemies = new int[tmp->enemy_count];

	for (int k = 0; k < tmp->enemy_count; k++) {

		fscanf(fp, "%d.%s = %s", &i, &info, &info2);
		tmp->enemies[k] = return_enemy_type(info2);

		if (tmp->enemies[k] == -1)
		{
			cout << "Error: Enemy name unavalible - "<<info2<<"\n";
			exit(-1);
		}

	}

	tmp->actual_enemies = new int[tmp->enemy_count];
	tmp->base_enemies = new int[tmp->enemy_count];

	fscanf(fp, "%s", &tmp_str);
	if (strcmp(tmp_str, "Wave.info") == 0)
	{
		
		#pragma region alokacja pamieci

		tmp->enemies_waves = (int **) new int *[tmp->wave_count];

		for (int i = 0; i < tmp->wave_count; i++) {
			tmp->enemies_waves[i] = new int[tmp->enemy_count];
		}
		#pragma endregion

		int i = 0;
		int j = 0;

		while (fscanf(fp, "%d", &value) != -1) {

			tmp->enemies_waves[i][j++] = value;

			if (j == tmp->enemy_count) {
				i++;
				j = 0;
			}

		}


	}

	for (int i = 0; i < tmp->enemy_count; i++) {
		tmp->actual_enemies[i] = tmp->enemies_waves[0][i];
		tmp->slained_enemies[i] = 0;
		tmp->base_enemies[i] = tmp->enemies_waves[0][i];
	}

	/*for (int i = 0; i < tmp->wave_count; i++) {
		for (int j = 0; j < tmp->enemy_count; j++) {
			cout << tmp->enemies_waves[i][j] << "\t";
		}
		cout << endl;
	}
	*/


	fclose(fp);
}

int board::return_enemy_type(char type[100])
{

				/*	case 0: enemies[i]->model = new CMD2Model(&_enemy_models->Minion_Mage);  enemies[i]->anim_speed = 0.8; break;
					case 1: enemies[i]->model = new CMD2Model(&_enemy_models->Minion_Melee);  enemies[i]->anim_speed = 0.8; break;
					case 2: enemies[i]->model = new CMD2Model(&_enemy_models->Krug); enemies[i]->anim_speed = 0.6; break;
					case 3: enemies[i]->model = new CMD2Model(&_enemy_models->Raptor_Mini); enemies[i]->anim_speed = 1; break;
					case 4:	enemies[i]->model = new CMD2Model(&_enemy_models->Gromp); enemies[i]->anim_speed = 0.7; break;
					case 5: enemies[i]->model = new CMD2Model(&_enemy_models->RiderChaos);  enemies[i]->anim_speed = 1; break;
					case 6: enemies[i]->model = new CMD2Model(&_enemy_models->RiderOrder); enemies[i]->anim_speed = 0.7; break;
					case 7: enemies[i]->model = new CMD2Model(&_enemy_models->Raptor); enemies[i]->anim_speed = 0.7; break;
					case 8: enemies[i]->model = new CMD2Model(&_enemy_models->Alistar); enemies[i]->anim_speed = 1; break;
					case 9: enemies[i]->model = new CMD2Model(&_enemy_models->Hecarim); enemies[i]->anim_speed = 0.45; break;
					case 10: enemies[i]->model = new CMD2Model(&_enemy_models->Galio); enemies[i]->anim_speed = 1; break;
					case 11: enemies[i]->model = new CMD2Model(&_enemy_models->Rammus); enemies[i]->anim_speed = 0.6; break;
					case 12: enemies[i]->model = new CMD2Model(&_enemy_models->Udyr); enemies[i]->anim_speed = 0.7; break;
					case 13: enemies[i]->model = new CMD2Model(&_enemy_models->Herald); enemies[i]->anim_speed = 1.8; break;
				*/





	if (strcmp(type, "Minion_Mage") == 0)
		return 0;

	if (strcmp(type, "Minion_Melee") == 0)
		return 1;

	if (strcmp(type, "Krug") == 0)
		return 2;

	if (strcmp(type, "Raptor_Mini") == 0)
		return 3;

	if (strcmp(type, "Gromp") == 0)
		return 4;

	if (strcmp(type, "RiderChaos") == 0)
		return 5;

	if (strcmp(type, "RiderOrder") == 0)
		return 6;

	if (strcmp(type, "Raptor") == 0)
		return 7;

	if (strcmp(type, "Alistar") == 0)
		return 8;

	if (strcmp(type, "Hecarim") == 0)
		return 9;

	if (strcmp(type, "Galio") == 0)
		return 10;

	if (strcmp(type, "Rammus") == 0)
		return 11;

	if (strcmp(type, "Udyr") == 0)
		return 12;

	if (strcmp(type, "Herald") == 0)
		return 13;

	if (strcmp(type, "Evelynn") == 0)
		return 14;




	return -1;
}

void board::Render()
{
	glEnable(GL_LIGHTING);
	Coursor_Pos = _Coursor->ReturnPos();

	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	_HUD->_TurretInfo.display_turret_info = false;
	_HUD->_BuyBuff.display = false;

	if (_zoom_board.pos[0] != (int)(Coursor_Pos.x - 0.5) || _zoom_board.pos[1] != (int)(Coursor_Pos.z + 0.5)) {

		_zoom_board.pos[0] = (int)(Coursor_Pos.x - 0.5);
		_zoom_board.pos[1] = (int)(Coursor_Pos.z + 0.5);
		_zoom_board.scale = 0;
	}


	for (int i = 0; i < mapk->y_size; i++) {

		for (int j = 0; j < mapk->x_size; j++) {

			if ((int)(Coursor_Pos.x - 0.5) == -i && (int)(Coursor_Pos.z + 0.5) == j)
			{
				_HUD->_BuyBuff.display = false;
				_HUD->_BuyBuff.sell_value = false;
			}

			if (mapk->map_v[i][j] == 0) {
				
				glPushMatrix();

				glTranslatef(-i, 0.01, j);
				glScalef(0.5, 0.03, 0.5);
				glBindTexture(GL_TEXTURE_2D, _brick->GetId());
				glCallList(brick);

				glPopMatrix();
				
				
				
				glPushMatrix();

	

				glTranslatef(-i, 0.25, j);
				glScalef(0.45, 0.8, 0.45);






				if ((int)(Coursor_Pos.x - 0.5) == -i && (int)(Coursor_Pos.z + 0.5) == j) {



					if (_Turrets->_Zone[i][j].placed == false) {

						//_zoom_board.scale += 0.00001;
						//if (_zoom_board.scale > 0.4);
						//_zoom_board.scale = 0.4;



						glScalef(1.0 + _zoom_board.scale, 1.0 + _zoom_board.scale, 1.0 + _zoom_board.scale);
						_HUD->_TurretInfo.display_turret_info = false;
					}
					
					
					
					//cout <<(int) (Coursor_Pos.x - 0.5) << "\t" <<(int) (Coursor_Pos.z + 0.5) <<"\t"<<mapk->map_v[(int)(-1*(Coursor_Pos.x - 0.5))][(int)(Coursor_Pos.z + 0.5)]<< endl;
					_Turrets->ManageTurret((int)(Coursor_Pos.x - 0.5), (int)(Coursor_Pos.z + 0.5));

				}
				//_HUD->display_turret_info = false;
				glTranslatef(0, 0.35, 0);
				glBindTexture(GL_TEXTURE_2D, _stone_texture->GetId());
				glCallList(brick);






				glPopMatrix();

			}
			else if(mapk->map_v[i][j] != -1)
			{


				if (mapk->map_v[i][j] == 1) {

					glPushMatrix();
					glTranslatef(-i - 0.5, 2 + sin(glutGet(GLUT_ELAPSED_TIME) * 0.003) * 0.3, j );
					//glRotatef(180, 0, 0, 1);
					glRotatef(-90, 0, 1, 0);
					glRotatef(30, 1, 0, 0);
					glDisable(GL_TEXTURE_2D);
					glColor3f(0.8, 0.7, 0.3);
					glDisable(GL_LIGHTING);
					shaders.Disable_Shader();
					_Fonts_management->drawtext("SPAWN", 0, 1, 0.3);
					shaders.Enable_Shader();
					glEnable(GL_TEXTURE_2D);
					glEnable(GL_LIGHTING);
					glPopMatrix();

				}



				glPushMatrix();
					
					glTranslatef(-i, 0.02, j);
					glScalef(0.5, 0.03, 0.5);
					glBindTexture(GL_TEXTURE_2D, _brick->GetId());
					glCallList(brick);

				glPopMatrix();
			}
			
			#pragma region NEXUS
			float speed = 1;

			if (mapk->map_v[i][j] == 1000) {
				shaders.Disable_Shader();
				glPushAttrib(GL_CURRENT_BIT);
				char health[6];
				vec3 pos;
				pos.x = 0;
				pos.y = 0;
				pos.z = 0;
				glPushMatrix();
				speed = ((_Nexus->return_max_health() - _Nexus->return_health()) + 1) * 0.006;

				if (speed < 1)
					speed = 1;

				if (speed > 5)
					speed = 5;
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glTranslatef(-i, 3.0 + sin(glutGet(GLUT_ELAPSED_TIME) * 0.001  * speed) * 0.3, j);
				//glRotatef(180, 0, 0, 1);
				glRotatef(-90, 0, 1, 0);
				glRotatef(30, 1, 0, 0);
				glDisable(GL_TEXTURE_2D);

				glColor4f((float) (_Nexus->return_max_health() - _Nexus->return_health())/_Nexus->return_max_health() + 0.3 , (float)_Nexus->return_health()/_Nexus->return_max_health(), 0.2,0.75);
				glDisable(GL_LIGHTING);
				sprintf(health, "%d", _Nexus->return_health());
				if(_Nexus->return_health() >= 0)
					_Fonts_management->drawtext(health, pos, 1, 1);
				else
					_Fonts_management->drawtext("0", pos, 1, 1);
				
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_LIGHTING);
				glPopMatrix();



				glPushMatrix();
				glTranslatef(-i, 0.25, j);
				glScalef(0.8, 0.8, 0.8);
				glBindTexture(GL_TEXTURE_2D, _nexus->GetId());
				glCallList(nexus_obj);
				glPopMatrix();
				glPopAttrib();
				shaders.Enable_Shader();
			}

		}

			#pragma endregion

	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
}

void board::Update()
{

	#pragma region Efekt powiekszania miejsca na turetki

	if (_zoom_board.scale < 0.3) {
		_zoom_board.scale += 0.026;
	}

#pragma endregion


}
