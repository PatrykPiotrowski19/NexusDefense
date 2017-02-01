#include "stdafx.h"
#include "Turrets.h"

struct enemy;


Turrets::Turrets(map *_map, CPlayer *_CPlayer)
{
	current_placed = false;
	buff_mult = 1;
	this->_CPlayer = _CPlayer;
	this->_map = _map;
	x_size = _map->y_size;
	y_size = _map->x_size;
	ring = LoadObj("Models/ring.obj");
	buy_multiplier = 0.1;

	pressed_q = false;
	pressed_w = false;
	pressed_e = false;


	_Zone = (Zone **) new Zone *[x_size]; //alokacja pamieci
	
	for (int i = 0; i < x_size; ++i)
	{
		_Zone[i] = new Zone[y_size]; //alokacja pamieci
	}

	cout << x_size << "\t" << y_size << endl;

	for (int i = 0; i < x_size; ++i) {
	
		for (int j = 0; j < y_size; ++j) {

			_Zone[i][j].atk_speed = 0;
			_Zone[i][j].atk_speed_lvl = 1;
			_Zone[i][j].damage = 0;
			_Zone[i][j].damage_lvl = 1;
			_Zone[i][j].placed = false;
			_Zone[i][j].range = 0;
			_Zone[i][j].range_lvl = 1;
			_Zone[i][j].turret_id = 0;
			_Zone[i][j].Turret_ATTACK = NULL;
			_Zone[i][j].Turret_IDLE = NULL;
			_Zone[i][j].Current_Animation = NULL;
			_Zone[i][j].target = NULL;
			_Zone[i][j].rotation = 0;
			_Zone[i][j].bonus_damage = 0;
			_Zone[i][j].target_shoots = 0;
		}


	}


	for (int i = 0; i < x_size; ++i) {
		for (int j = 0; j < y_size; j++) {

			cout << _Zone[i][j].placed << "\t";

		}
		cout << endl;
	}





	#pragma region ShacoTurret

	if(_config_display.Turrets_Quality == 1)
		_Turrets[0].Turret_IDLE.LoadModel("Data/Turrets/Shaco_Doll/ShacoDoll_L_Idle.md2");
	if(_config_display.Turrets_Quality == 2)
		_Turrets[0].Turret_IDLE.LoadModel("Data/Turrets/Shaco_Doll/ShacoDoll_M_Idle.md2");
	if (_config_display.Turrets_Quality == 3)
		_Turrets[0].Turret_IDLE.LoadModel("Data/Turrets/Shaco_Doll/ShacoDoll_H_Idle.md2");


	_Turrets[0].Turret_IDLE.LoadSkin("Data/Turrets/Shaco_Doll/ShacoDoll_Texture.bmp");

	_Turrets[0].Turret_ATTACK = _Turrets[0].Turret_IDLE;

	if (_config_display.Turrets_Quality == 1)
		_Turrets[0].Turret_ATTACK.LoadModel("Data/Turrets/Shaco_Doll/ShacoDoll_L_Attack.md2");
	if (_config_display.Turrets_Quality == 2)
		_Turrets[0].Turret_ATTACK.LoadModel("Data/Turrets/Shaco_Doll/ShacoDoll_M_Attack.md2");
	if (_config_display.Turrets_Quality == 3)
		_Turrets[0].Turret_ATTACK.LoadModel("Data/Turrets/Shaco_Doll/ShacoDoll_H_Attack.md2");


	_Turrets[0].Turret_ATTACK.ScaleModel(5.0);
	_Turrets[0].attack_length = 30;
	_Turrets[0].Turret_ATTACK.SetAnim(_Turrets[0].attack_length);

	_Turrets[0].Turret_IDLE.ScaleModel(5.0);
	_Turrets[0].idle_length = 30;
	_Turrets[0].Turret_IDLE.SetAnim(_Turrets[0].idle_length);


	_Turrets[0].base_damage = 55;
	_Turrets[0].base_attackspeed = 1.0;
	_Turrets[0].base_range = 1.2;
	
	_Turrets[0].max_dmg_lvl = 5;
	_Turrets[0].max_atk_speed_lvl = 5;
	_Turrets[0].max_range_lvl = 5;

	_Turrets[0].dmg_multiplier = 1.21 * buff_mult;
	_Turrets[0].atk_speed_multiplier = 1.135 * buff_mult;
	_Turrets[0].range_multiplier = 1.11 * buff_mult;

	_Turrets[0].cost = 180;

	#pragma endregion

	#pragma region HeimerTurret1

	if (_config_display.Turrets_Quality == 1)
		_Turrets[1].Turret_IDLE.LoadModel("Data/Turrets/Heimer_Turret1/HeimerTurret1_L_Idle.md2");
	if (_config_display.Turrets_Quality == 2)
		_Turrets[1].Turret_IDLE.LoadModel("Data/Turrets/Heimer_Turret1/HeimerTurret1_M_Idle.md2");
	if (_config_display.Turrets_Quality == 3)
		_Turrets[1].Turret_IDLE.LoadModel("Data/Turrets/Heimer_Turret1/HeimerTurret1_H_Idle.md2");


	_Turrets[1].Turret_IDLE.LoadSkin("Data/Turrets/Heimer_Turret1/HeimerTurret1_Texture.bmp");
	_Turrets[1].idle_length = 78;
	_Turrets[1].Turret_IDLE.SetAnim(_Turrets[1].idle_length);
	_Turrets[1].Turret_IDLE.ScaleModel(1.5);

	_Turrets[1].Turret_ATTACK = _Turrets[1].Turret_IDLE;
	if (_config_display.Turrets_Quality == 1)
		_Turrets[1].Turret_ATTACK.LoadModel("Data/Turrets/Heimer_Turret1/HeimerTurret1_L_Attack.md2");
	if (_config_display.Turrets_Quality == 2)
		_Turrets[1].Turret_ATTACK.LoadModel("Data/Turrets/Heimer_Turret1/HeimerTurret1_M_Attack.md2");
	if (_config_display.Turrets_Quality == 3)
		_Turrets[1].Turret_ATTACK.LoadModel("Data/Turrets/Heimer_Turret1/HeimerTurret1_H_Attack.md2");


	_Turrets[1].attack_length = 35;
	_Turrets[1].Turret_ATTACK.SetAnim(_Turrets[1].attack_length);
	_Turrets[1].Turret_ATTACK.ScaleModel(1.5);


	_Turrets[1].base_damage = 85;
	_Turrets[1].base_attackspeed = 1.05;
	_Turrets[1].base_range = 1.3;

	_Turrets[1].max_dmg_lvl = 5;
	_Turrets[1].max_atk_speed_lvl = 5;
	_Turrets[1].max_range_lvl = 5;

	_Turrets[1].dmg_multiplier = 1.17 * buff_mult;
	_Turrets[1].atk_speed_multiplier = 1.12 * buff_mult;
	_Turrets[1].range_multiplier = 1.12 * buff_mult;

	_Turrets[1].cost = 400;

	#pragma endregion

	#pragma region HeimerTurret2

	if (_config_display.Turrets_Quality == 1)
		_Turrets[2].Turret_IDLE.LoadModel("Data/Turrets/Heimer_Turret2/HeimerTurret2_L_Idle.md2");
	if (_config_display.Turrets_Quality == 2)
		_Turrets[2].Turret_IDLE.LoadModel("Data/Turrets/Heimer_Turret2/HeimerTurret2_M_Idle.md2");
	if (_config_display.Turrets_Quality == 3)
		_Turrets[2].Turret_IDLE.LoadModel("Data/Turrets/Heimer_Turret2/HeimerTurret2_H_Idle.md2");


	_Turrets[2].Turret_IDLE.LoadSkin("Data/Turrets/Heimer_Turret2/HeimerTurret2_Texture.bmp");
	_Turrets[2].idle_length = 26;
	_Turrets[2].Turret_IDLE.SetAnim(_Turrets[2].idle_length);
	_Turrets[2].Turret_IDLE.ScaleModel(1);

	_Turrets[2].Turret_ATTACK = _Turrets[2].Turret_IDLE;

	if (_config_display.Turrets_Quality == 1)
		_Turrets[2].Turret_ATTACK.LoadModel("Data/Turrets/Heimer_Turret2/HeimerTurret2_L_Attack.md2");
	if (_config_display.Turrets_Quality == 2)
		_Turrets[2].Turret_ATTACK.LoadModel("Data/Turrets/Heimer_Turret2/HeimerTurret2_M_Attack.md2");
	if (_config_display.Turrets_Quality == 3)
		_Turrets[2].Turret_ATTACK.LoadModel("Data/Turrets/Heimer_Turret2/HeimerTurret2_H_Attack.md2");

	_Turrets[2].attack_length = 36;
	_Turrets[2].Turret_ATTACK.SetAnim(_Turrets[2].attack_length);
	_Turrets[2].Turret_ATTACK.ScaleModel(1);


	_Turrets[2].base_damage = 125;
	_Turrets[2].base_attackspeed = 1.1;
	_Turrets[2].base_range = 1.35;

	_Turrets[2].max_dmg_lvl = 5;
	_Turrets[2].max_atk_speed_lvl = 5;
	_Turrets[2].max_range_lvl = 5;

	_Turrets[2].dmg_multiplier = 1.13 * buff_mult;
	_Turrets[2].atk_speed_multiplier = 1.12 * buff_mult;
	_Turrets[2].range_multiplier = 1.13 * buff_mult;

	_Turrets[2].cost = 650;



	#pragma endregion	

	#pragma region Turret3

	if (_config_display.Turrets_Quality == 1)
		_Turrets[3].Turret_IDLE.LoadModel("Data/Turrets/Zyra_Plant/ZyraPlant_L_Idle.md2");
	if (_config_display.Turrets_Quality == 2)
		_Turrets[3].Turret_IDLE.LoadModel("Data/Turrets/Zyra_Plant/ZyraPlant_M_Idle.md2");
	if (_config_display.Turrets_Quality == 3)
		_Turrets[3].Turret_IDLE.LoadModel("Data/Turrets/Zyra_Plant/ZyraPlant_H_Idle.md2");


	_Turrets[3].Turret_IDLE.LoadSkin("Data/Turrets/Zyra_Plant/ZyraPlant_Texture.bmp");
	_Turrets[3].idle_length = 40;
	_Turrets[3].Turret_IDLE.SetAnim(_Turrets[3].idle_length);
	_Turrets[3].Turret_IDLE.ScaleModel(1.4);

	_Turrets[3].Turret_ATTACK = _Turrets[3].Turret_IDLE;
	if (_config_display.Turrets_Quality == 1)
		_Turrets[3].Turret_ATTACK.LoadModel("Data/Turrets/Zyra_Plant/ZyraPlant_L_Attack.md2");
	if (_config_display.Turrets_Quality == 2)
		_Turrets[3].Turret_ATTACK.LoadModel("Data/Turrets/Zyra_Plant/ZyraPlant_M_Attack.md2");
	if (_config_display.Turrets_Quality == 3)
		_Turrets[3].Turret_ATTACK.LoadModel("Data/Turrets/Zyra_Plant/ZyraPlant_H_Attack.md2");
	_Turrets[3].attack_length = 25;
	_Turrets[3].Turret_ATTACK.SetAnim(_Turrets[3].attack_length);
	_Turrets[3].Turret_ATTACK.ScaleModel(1.4);


	_Turrets[3].base_damage = 155;
	_Turrets[3].base_attackspeed = 1.05;
	_Turrets[3].base_range = 1.45;

	_Turrets[3].max_dmg_lvl = 5;
	_Turrets[3].max_atk_speed_lvl = 5;
	_Turrets[3].max_range_lvl = 5;

	_Turrets[3].dmg_multiplier = 1.14 * buff_mult;
	_Turrets[3].atk_speed_multiplier = 1.1 * buff_mult;
	_Turrets[3].range_multiplier = 1.11 * buff_mult;

	_Turrets[3].cost = 850;

	#pragma endregion

	#pragma region Turret4

	if (_config_display.Turrets_Quality == 1)
		_Turrets[4].Turret_IDLE.LoadModel("Data/Turrets/AzirSoldier/AzirSoldier_L_Idle.md2");
	if (_config_display.Turrets_Quality == 2)
		_Turrets[4].Turret_IDLE.LoadModel("Data/Turrets/AzirSoldier/AzirSoldier_M_Idle.md2");
	if (_config_display.Turrets_Quality == 3)
		_Turrets[4].Turret_IDLE.LoadModel("Data/Turrets/AzirSoldier/AzirSoldier_H_Idle.md2");

	_Turrets[4].Turret_IDLE.LoadSkin("Data/Turrets/AzirSoldier/AzirSoldier_Texture.bmp");

	_Turrets[4].idle_length = 40;
	_Turrets[4].Turret_IDLE.ScaleModel(0.9);
	_Turrets[4].Turret_IDLE.SetAnim(_Turrets[4].idle_length);

	_Turrets[4].Turret_ATTACK = _Turrets[4].Turret_IDLE;

	if (_config_display.Turrets_Quality == 1)
		_Turrets[4].Turret_ATTACK.LoadModel("Data/Turrets/AzirSoldier/AzirSoldier_L_Attack.md2");
	if (_config_display.Turrets_Quality == 2)
		_Turrets[4].Turret_ATTACK.LoadModel("Data/Turrets/AzirSoldier/AzirSoldier_M_Attack.md2");
	if (_config_display.Turrets_Quality == 3)
		_Turrets[4].Turret_ATTACK.LoadModel("Data/Turrets/AzirSoldier/AzirSoldier_H_Attack.md2");

	_Turrets[4].attack_length = 48;
	_Turrets[4].Turret_ATTACK.ScaleModel(0.9);
	_Turrets[4].Turret_ATTACK.SetAnim(_Turrets[4].attack_length);

	_Turrets[4].base_damage = 165;
	_Turrets[4].base_attackspeed = 1.2;
	_Turrets[4].base_range = 1.75;

	_Turrets[4].max_dmg_lvl = 5;
	_Turrets[4].max_atk_speed_lvl = 5;
	_Turrets[4].max_range_lvl = 0;

	_Turrets[4].dmg_multiplier = 1.15 * buff_mult;
	_Turrets[4].atk_speed_multiplier = 1.14 * buff_mult;
	_Turrets[4].range_multiplier = 1.24 * buff_mult;

	_Turrets[4].cost = 1100;

	#pragma endregion

	#pragma region Turret5

	if (_config_display.Turrets_Quality == 1)
		_Turrets[5].Turret_IDLE.LoadModel("Data/Turrets/Urf/Urf_L_Idle.md2");
	if (_config_display.Turrets_Quality == 2)
		_Turrets[5].Turret_IDLE.LoadModel("Data/Turrets/Urf/Urf_M_Idle.md2");
	if (_config_display.Turrets_Quality == 3)
		_Turrets[5].Turret_IDLE.LoadModel("Data/Turrets/Urf/Urf_H_Idle.md2");

	_Turrets[5].Turret_IDLE.LoadSkin("Data/Turrets/Urf/Urf_Texture.bmp");

	_Turrets[5].idle_length = 30;
	_Turrets[5].Turret_IDLE.ScaleModel(1.2);
	_Turrets[5].Turret_IDLE.SetAnim(_Turrets[5].idle_length);

	_Turrets[5].Turret_ATTACK = _Turrets[5].Turret_IDLE;

	if (_config_display.Turrets_Quality == 1)
		_Turrets[5].Turret_ATTACK.LoadModel("Data/Turrets/Urf/Urf_L_Attack.md2");
	if (_config_display.Turrets_Quality == 2)
		_Turrets[5].Turret_ATTACK.LoadModel("Data/Turrets/Urf/Urf_M_Attack.md2");
	if (_config_display.Turrets_Quality == 3)
		_Turrets[5].Turret_ATTACK.LoadModel("Data/Turrets/Urf/Urf_H_Attack.md2");

	_Turrets[5].attack_length = 80;
	_Turrets[5].Turret_ATTACK.ScaleModel(1.2);
	_Turrets[5].Turret_ATTACK.SetAnim(_Turrets[5].attack_length);


	_Turrets[5].base_damage = 200;
	_Turrets[5].base_attackspeed = 1.11;
	_Turrets[5].base_range = 1.85;

	_Turrets[5].max_dmg_lvl = 5;
	_Turrets[5].max_atk_speed_lvl = 5;
	_Turrets[5].max_range_lvl = 5;

	_Turrets[5].dmg_multiplier = 1.1 * buff_mult;
	_Turrets[5].atk_speed_multiplier = 1.09 * buff_mult;
	_Turrets[5].range_multiplier = 1.11 * buff_mult;

	_Turrets[5].cost = 1550;


	#pragma endregion

	#pragma region Turret6
	_Turrets[6].Turret_IDLE.LoadModel("Data/Turrets/AzirTurret/AzirTurret_Idle.md2");
	_Turrets[6].Turret_IDLE.LoadSkin("Data/Turrets/AzirTurret/AzirTurret_Texture.bmp");

	_Turrets[6].idle_length = 43;
	_Turrets[6].Turret_IDLE.ScaleModel(1.3);
	_Turrets[6].Turret_IDLE.SetAnim(_Turrets[6].idle_length);

	_Turrets[6].Turret_ATTACK = _Turrets[6].Turret_IDLE;
	_Turrets[6].Turret_ATTACK.LoadModel("Data/Turrets/AzirTurret/AzirTurret_Attack.md2");

	_Turrets[6].attack_length = 55;
	_Turrets[6].Turret_ATTACK.ScaleModel(1.3);
	_Turrets[6].Turret_ATTACK.SetAnim(_Turrets[6].attack_length);

	_Turrets[6].base_damage = 290;
	_Turrets[6].base_attackspeed = 1.0;
	_Turrets[6].base_range = 2.0;

	_Turrets[6].max_dmg_lvl = 5;
	_Turrets[6].max_atk_speed_lvl = 5;
	_Turrets[6].max_range_lvl = 5;

	_Turrets[6].dmg_multiplier = 1.08 * buff_mult;
	_Turrets[6].atk_speed_multiplier = 1.08 * buff_mult;
	_Turrets[6].range_multiplier = 1.16 * buff_mult;

	_Turrets[6].cost = 2150;


	#pragma endregion

}

void Turrets::Get_Enemy_Pointer(enemy ** _enemy, int enemy_count)
{
	this->_enemy = _enemy;
	this->enemy_count = enemy_count;
}

void Turrets::Get_Player_Pointer(CPlayer * _Player)
{
	this->_CPlayer = _Player;
}

void Turrets::Get_HUD_Pointer(HUD * _HUD)
{
	this->_HUD = _HUD;
	_HUD->_BuyBuff.sell_value = 0;
}

void Turrets::Get_Bullet_Pointer(manage_bullets * bullets)
{
	this->bullets = bullets;

}

void Turrets::Get_Coursor_Pointer(Coursor * _Coursor)
{
	this->_Coursor = _Coursor;
}

void Turrets::Render()
{

	#pragma region Pozycja wiezyczki (podglad)
	int turr_id = _Coursor->ReturnCurrentSelection();

	if (turr_id != -1) {

		if (_CPlayer->money >= _Turrets[turr_id-1].cost)
			shaders.Enable_Turrets(1);
		else
			shaders.Enable_Turrets(0);


		vec3 coursor_pos = _Coursor->ReturnPos();
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glTranslatef(coursor_pos.x, 1.6 + sin(glutGet(GLUT_ELAPSED_TIME)*0.004) * 0.2, coursor_pos.z);
		glRotatef(glutGet(GLUT_ELAPSED_TIME)*0.05, 0, 1, 0);
		glScalef(0.6, 0.6, 0.6);
		glColor4f(1, 0, 0, 1);
		_Turrets[turr_id-1].Turret_IDLE.DrawModel(1);
		_HUD->_TurretInfo.atk_speed = _Turrets[turr_id - 1].base_attackspeed;
		_HUD->_TurretInfo.damage = _Turrets[turr_id - 1].base_damage;
		_HUD->_TurretInfo.range = _Turrets[turr_id - 1].base_range;
		_HUD->_TurretInfo.turret_id = turr_id - 1;
		_HUD->_TurretInfo.display_turret_info = true;
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		shaders.Disable_Shader();
	}

	#pragma endregion


	for (int i = 0; i < x_size; ++i) {
		for (int j = 0; j < y_size; ++j) {
			if (_Zone[i][j].placed && _Zone[i][j].Turret_ATTACK != NULL && _Zone[i][j].Turret_IDLE != NULL) {

				if (_Zone[i][j].target != NULL && _Zone[i][j].target->enabled && _Zone[i][j].turret_id == 6) {
					glPushMatrix();
					glColor4f(1, 0, 0, 0.8);
					glBegin(GL_LINES);
					glVertex3f(-(float)i, 1.7, (float)j);
					glVertex3f(_Zone[i][j].target->pos.x, _Zone[i][j].target->pos.y + 0.25, _Zone[i][j].target->pos.z);
					glEnd();

					glPopMatrix();
				}



				glPushMatrix();
				glEnable(GL_TEXTURE_2D);
				glTranslatef(-i, 1.15, j);
				glScalef(0.6, 0.6, 0.6);

				

				glRotatef(_Zone[i][j].rotation, 0, 1, 0);
				glColor3f(0.5, 1, 1);

				//glRotatef(glutGet(GLUT_ELAPSED_TIME) * 0.01, 0, 1, 0);
				if(_Zone[i][j].target)
					_Zone[i][j].Current_Animation->DrawModel(glutGet(GLUT_ELAPSED_TIME)*0.001 * 25 * _Zone[i][j].animation_speed * _Zone[i][j].atk_speed * !pause);
				else
					_Zone[i][j].Current_Animation->DrawModel(glutGet(GLUT_ELAPSED_TIME)*0.001 * 25 * _Zone[i][j].animation_speed * !pause);
				glDisable(GL_TEXTURE_2D);
				glPopMatrix();

			}
		}
	}

}

void Turrets::Update()
{

	if (keystate['1'])
		_Coursor->SetCurrentSelection(1);
	if (keystate['2'])
		_Coursor->SetCurrentSelection(2);
	if (keystate['3'])
		_Coursor->SetCurrentSelection(3);
	if (keystate['4'])
		_Coursor->SetCurrentSelection(4);
	if (keystate['5'])
		_Coursor->SetCurrentSelection(5);
	if (keystate['6'])
		_Coursor->SetCurrentSelection(6);
	if (keystate['7'])
		_Coursor->SetCurrentSelection(7);
	if (keystate['c'])
		_Coursor->SetCurrentSelection(-1);

	_HUD->GetCurrentSelection(_Coursor->ReturnCurrentSelection());


	for (int i = 0; i < x_size; i++) {

		for (int j = 0; j < y_size; j++) {

			vec3 turret_pos;
			turret_pos.x = -i;
			turret_pos.y = 0;
			turret_pos.z = j;

			if (_Zone[i][j].placed == true) {


				if (_Zone[i][j].target != NULL && _Zone[i][j].target->enabled)
				{
					//obrot wiezyczki
					vec3 pos;
					pos.x = -i;
					pos.y = 0;
					pos.z = j;
					float tmp_rotation = Rotate_To_Target(pos, _Zone[i][j].target->pos);
					float rotation_value = tmp_rotation + 360;

					if (abs(_Zone[i][j].rotation - rotation_value) > abs(_Zone[i][j].rotation - tmp_rotation)) {
						rotation_value = tmp_rotation;
					}


					float odl = abs(_Zone[i][j].rotation - rotation_value);
					if (abs(_Zone[i][j].rotation - rotation_value) < 7) {
						_Zone[i][j].rotation = rotation_value;

					}
					else {

						if (_Zone[i][j].rotation > rotation_value)
						{
							_Zone[i][j].rotation -= 12;

						}
						else
							_Zone[i][j].rotation += 12;

					}

				}




				//Jezeli nie ma zadnego celu
				if(_Zone[i][j].target == NULL){

					if (_Zone[i][j].turret_id == 6)
						_Zone[i][j].bonus_damage = 0;


					_Zone[i][j].target_shoots = 0;
					int dist;
					tmp_info info;
					info.target = NULL;
					info.distance = -1;
		
					for (int k = 0; k < enemy_count; k++) {
							if (_enemy[k]->enabled) {
								dist = return_distance(turret_pos, _enemy[k]->pos);
								//Jezeli cel jest w zasiegu wiezyczki
								if (_Zone[i][j].range >= dist) {

									if (info.distance == -1 || info.distance > dist) {
										info.distance = dist;
										info.target = _enemy[k];
									}
								}
							}
							//Jezeli znaleziono
							if (info.distance != -1) {

								_Zone[i][j].target = info.target;
								_Zone[i][j].Current_Animation = _Zone[i][j].Turret_ATTACK;
							}

						}
					}
				//Sprawdzam cele czy nadal sa w zasiegu
				else
				{
					
					int dist = return_distance(turret_pos, _Zone[i][j].target->pos);
					_Zone[i][j].interval += 17;

					if (_Zone[i][j].interval >= 1000 / _Zone[i][j].atk_speed) {

						vec3 tmp_pos = {(float)-i, 1.5,(float) j};
						_Zone[i][j].shoots++;
						_Zone[i][j].target_shoots++;


						//Dla wiezyczki aziry
						if (_Zone[i][j].turret_id == 6 && _Zone[i][j].target_shoots <= 6) {

							_Zone[i][j].bonus_damage = _Zone[i][j].damage * 0.2 * _Zone[i][j].target_shoots;

						}


						_Zone[i][j].interval = 0;
						//_Zone[i][j].target->health -= _Zone[i][j].damage;

						//dla wiezyczki heimera
						if (_Zone[i][j].turret_id == 1) {

							if(_Zone[i][j].shoots % 3 == 0 && _Zone[i][j].shoots > 0)
								bullets->add_bullet(tmp_pos, _Zone[i][j].damage*2+_Zone[i][j].bonus_damage, 30, _Zone[i][j].turret_id, _Zone[i][j].target);
							else
								bullets->add_bullet(tmp_pos, _Zone[i][j].damage + _Zone[i][j].bonus_damage, 30, _Zone[i][j].turret_id, _Zone[i][j].target);
						}

						//dla normalnych wiezyczek
						else
								bullets->add_bullet(tmp_pos,_Zone[i][j].damage + _Zone[i][j].bonus_damage,30,_Zone[i][j].turret_id, _Zone[i][j].target);


						
						//_Zone[i][j].Turret_ATTACK->SetAnim(_Turrets[_Zone[i][j].turret_id].attack_length);
						//_Zone[i][j].Turret_IDLE->SetAnim(_Turrets[_Zone[i][j].turret_id].idle_length);
					}

					
					//Jezeli jest poza zasiegiem
					if (dist > _Zone[i][j].range)
					{
						_Zone[i][j].target = NULL;
						_Zone[i][j].Current_Animation = _Zone[i][j].Turret_IDLE;
						//_Zone[i][j].interval = 0;
						_Zone[i][j].Turret_IDLE->SetAnim(_Turrets[_Zone[i][j].turret_id].idle_length);
						_Zone[i][j].Turret_ATTACK->SetAnim(_Turrets[_Zone[i][j].turret_id].attack_length);
					}
					}

				}
			}
		}


	}





void Turrets::PlaceTurret(int id, int x, int y)
{

	if (!_Zone[x][y].placed) {

		_Zone[x][y].turret_id = id;
		_Zone[x][y].atk_speed = _Turrets[id].base_attackspeed;
		_Zone[x][y].damage = _Turrets[id].base_damage;
		_Zone[x][y].range = _Turrets[id].base_range;

		_Zone[x][y].atk_speed_lvl = 0;
		_Zone[x][y].damage_lvl = 0;
		_Zone[x][y].range_lvl = 0;

		_Zone[x][y].placed = true;
		_Zone[x][y].shoots = 0;

	 _Zone[x][y].Turret_IDLE = new CMD2Model(&_Turrets[id].Turret_IDLE);
	 _Zone[x][y].Turret_ATTACK = new CMD2Model(&_Turrets[id].Turret_ATTACK);
	 _Zone[x][y].Current_Animation = _Zone[x][y].Turret_IDLE;
	 _Zone[x][y].interval = 0;
	 _Zone[x][y].target = NULL;
	 _Zone[x][y].rotation = 270;

	 switch (id) {
	 case 0: _Zone[x][y].animation_speed = 1.4; break;
	 case 1: _Zone[x][y].animation_speed = 0.9; break;
	 case 2: _Zone[x][y].animation_speed = 1.0; break;
	 case 3: _Zone[x][y].animation_speed = 0.9; break;
	 case 4: _Zone[x][y].animation_speed = 1.2; break;
	 case 5: _Zone[x][y].animation_speed = 1.2; break;
	 case 6: _Zone[x][y].animation_speed = 1.6; break;

	 }
	 
	 _Zone[x][x].animation_base_speed = _Zone[x][y].animation_speed;

	}

}

void Turrets::ManageTurret(int pos_x, int pos_z)
{
	_HUD->_BuyBuff.display = false;
	_HUD->_BuyBuff.sell_value = false;
	//cout <<"PLACED = "<< _Zone[-pos_x][pos_z].placed<<endl;

	if (_Zone[-pos_x][pos_z].placed) {

		_HUD->_TurretInfo.display_turret_info = true;
		_HUD->_TurretInfo.x = -pos_x;
		_HUD->_TurretInfo.y = pos_z;
		_HUD->_TurretInfo.atk_speed = _Zone[-pos_x][pos_z].atk_speed;
		_HUD->_TurretInfo.damage = _Zone[-pos_x][pos_z].damage + _Zone[-pos_x][pos_z].bonus_damage;
		_HUD->_TurretInfo.range = _Zone[-pos_x][pos_z].range;
		_HUD->_TurretInfo.turret_id = _Zone[-pos_x][pos_z].turret_id;

		float scale = _Zone[-pos_x][pos_z].range * 4;
		glPushMatrix();
		shaders.Disable_Shader();
		glDisable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
		glTranslatef(0, 1, 0);
		glPushMatrix();
			glColor4f(0.6, 0, 0, 0.4);
			glScalef(scale*0.6, 1, scale*0.6);
			glTranslatef(0, -1.2, 0);
			glCallList(ring);
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		shaders.Enable_Shader();
		glPopMatrix();




		//cout << "Aktualizacja wiezyczki\n";

		Upgrade_Attack(&_Zone[-pos_x][pos_z]);
		Upgrade_Atk_Speed(&_Zone[-pos_x][pos_z]);
		Upgrade_Range(&_Zone[-pos_x][pos_z]);
		Upgrade_HUD(&_Zone[-pos_x][pos_z]);


		if (keystate['r'] || keystate['R']) {

			RemoveTurret(-pos_x, pos_z);
			_CPlayer->add_money(_HUD->_BuyBuff.sell_value);
			
		}


	}
	else
	{

		int turret_id = _Coursor->ReturnCurrentSelection();

		if (left_mouse_button && turret_id != -1 && !current_placed) {

			current_placed = true;

			//cout << "Zakup wiezyczki\n";
			
			if (turret_id == 1) {

				if (_CPlayer->money >= _Turrets[0].cost) {
					_CPlayer->remove_money(_Turrets[0].cost);
					_CPlayer->add_money_turrets(_Turrets[0].cost);
					PlaceTurret(0, -pos_x, pos_z);
					_SoundManage->_PlaceTurret_Shaco();
					_Coursor->SetCurrentSelection(-1);
				}

			}
			if (turret_id == 2) {

				if (_CPlayer->money >= _Turrets[1].cost) {
					_CPlayer->remove_money(_Turrets[1].cost);
					_CPlayer->add_money_turrets(_Turrets[1].cost);
					PlaceTurret(1, -pos_x, pos_z);
					_SoundManage->_PlaceTurret_Heimer();
					_Coursor->SetCurrentSelection(-1);
				}
			}
			if (turret_id == 3) {

				if (_CPlayer->money >= _Turrets[2].cost) {
					_CPlayer->remove_money(_Turrets[2].cost);
					_CPlayer->add_money_turrets(_Turrets[2].cost);
					PlaceTurret(2, -pos_x, pos_z);
					_SoundManage->_PlaceTurret_Heimer();
					_Coursor->SetCurrentSelection(-1);
				}
			}
			if (turret_id == 4) {

				if (_CPlayer->money >= _Turrets[3].cost) {
					_CPlayer->remove_money(_Turrets[3].cost);
					_CPlayer->add_money_turrets(_Turrets[3].cost);
					PlaceTurret(3, -pos_x, pos_z);
					_SoundManage->_PlaceTurret_Zyra();
					_Coursor->SetCurrentSelection(-1);
				}
			}
			if (turret_id == 5) {

				if (_CPlayer->money >= _Turrets[4].cost) {
					_CPlayer->remove_money(_Turrets[4].cost);
					_CPlayer->add_money_turrets(_Turrets[4].cost);
					PlaceTurret(4, -pos_x, pos_z);
					_SoundManage->_PlaceTurret_Azir();
					_Coursor->SetCurrentSelection(-1);
				}
			}
			if (turret_id == 6) {

				if (_CPlayer->money >= _Turrets[5].cost) {
					_CPlayer->remove_money(_Turrets[5].cost);
					_CPlayer->add_money_turrets(_Turrets[5].cost);
					PlaceTurret(5, -pos_x, pos_z);
					_Coursor->SetCurrentSelection(-1);
				}
			}

			if (turret_id == 7) {

				if (_CPlayer->money >= _Turrets[6].cost) {
					_CPlayer->remove_money(_Turrets[6].cost);
					_CPlayer->add_money_turrets(_Turrets[6].cost);
					PlaceTurret(6, -pos_x, pos_z);
					_SoundManage->_PlaceTurret_Azir();
					_Coursor->SetCurrentSelection(-1);
				}
			}
			
		}

		if (!left_mouse_button)
			current_placed = false;

	}
}

int Turrets::Rotate_To_Target(vec3 turret, vec3 enemy)
{
	float odl_x = enemy.x - turret.x;
	float odl_z = enemy.z - turret.z;
	float przekatna = sqrt(abs(odl_x)*abs(odl_x) + abs(odl_z)*abs(odl_z));


	float kat = atan2(odl_x, odl_z) * 180 / PI;
	
	return kat;

}

void Turrets::RemoveTurret(int i, int j)
{

	_Zone[i][j].atk_speed = 0;
	_Zone[i][j].atk_speed_lvl = 1;
	_Zone[i][j].damage = 0;
	_Zone[i][j].damage_lvl = 1;
	_Zone[i][j].placed = false;
	_Zone[i][j].range = 0;
	_Zone[i][j].range_lvl = 1;
	_Zone[i][j].turret_id = 0;
	_Zone[i][j].rotation = 0;

	try
	{
		delete _Zone[i][j].Turret_ATTACK;

	}
	catch (exception& e)
	{
		cout << "Error: Cannot delete Turret\n";
	}

	try {
		delete _Zone[i][j].Turret_IDLE;
	}
	catch (exception& e)
	{
		cout << "Error: Cannot delete Turret 2\n";
	}

	_Zone[i][j].Turret_ATTACK = NULL;
	_Zone[i][j].Turret_IDLE = NULL;
	_Zone[i][j].Current_Animation = NULL;

	_Zone[i][j].target = NULL;

}

float Turrets::return_distance(vec3 turret, vec3 enemy)
{
	//Uzywa tylko koordynatow x,z

	return sqrt((turret.x - enemy.x)*(turret.x - enemy.x) + (turret.z - enemy.z)*(turret.z - enemy.z));
}

void Turrets::Upgrade_Atk_Speed(Zone * _Zone)
{

	if (keystate['w'] || keystate['W']) {
		if (!pressed_w) {

			pressed_w = true;
			
			if (_Zone->atk_speed_lvl + 1 <= _Turrets[_Zone->turret_id].max_atk_speed_lvl) {

				int cost = (_Zone->atk_speed_lvl + 1) * buy_multiplier * _Turrets[_Zone->turret_id].cost;

				if (cost <= _CPlayer->money) {
					_CPlayer->remove_money(cost);
					_CPlayer->add_money_upgrades(cost);
					_Zone->atk_speed = _Turrets[_Zone->turret_id].base_attackspeed * pow(_Turrets[_Zone->turret_id].atk_speed_multiplier, _Zone->atk_speed_lvl+1);
					_Zone->atk_speed_lvl += 1;

				}
				else
				{

				//	cout << "Brakuje pieniedzy, koszt " << cost << "\n";

				}


			}
			else
			{
			//	cout << "Nie mozna ulepszac\n";

			}




		}
	}
	else
		pressed_w = false;


}

void Turrets::Upgrade_Attack(Zone * _Zone)
{
	if (keystate['q'] || keystate['Q']) {
		if (!pressed_q) {

			pressed_q = true;
			
			if (_Zone->damage_lvl + 1 <= _Turrets[_Zone->turret_id].max_dmg_lvl) {

				int cost = (_Zone->damage_lvl + 1) * buy_multiplier * _Turrets[_Zone->turret_id].cost;
				
				if (cost <= _CPlayer->money) {
					_CPlayer->remove_money(cost);
					_CPlayer->add_money_upgrades(cost);
					_Zone->damage = _Turrets[_Zone->turret_id].base_damage * pow(_Turrets[_Zone->turret_id].dmg_multiplier, _Zone->damage_lvl+1);
					_Zone->damage_lvl += 1;

				}
				else
				{

				//	cout << "Brakuje pieniedzy, koszt " << cost << "\n";

				}


			}
			else
			{
			//	cout << "Nie mozna ulepszac\n";

			}


		}
	}
	else
		pressed_q = false;

}

void Turrets::Upgrade_Range(Zone * _Zone)
{

	if (keystate['e'] || keystate['E']) {
		if (!pressed_e) {
			//cout << "UPGRADE E\n";
			pressed_e = true;

			if (_Zone->range_lvl + 1 <= _Turrets[_Zone->turret_id].max_range_lvl) {

				int cost = (_Zone->range_lvl + 1) * buy_multiplier * _Turrets[_Zone->turret_id].cost;

				if (cost <= _CPlayer->money) {
					_CPlayer->remove_money(cost);
					_CPlayer->add_money_upgrades(cost);
					_Zone->range = _Turrets[_Zone->turret_id].base_range * pow(_Turrets[_Zone->turret_id].range_multiplier, _Zone->range_lvl+1);
					_Zone->range_lvl += 1;

				}
				else
				{

				//	cout << "Brakuje pieniedzy, koszt " << cost << "\n";

				}


			}
			else
			{
			//	cout << "Nie mozna ulepszac\n";

			}





		}
	}
	else
		pressed_e = false;

}

void Turrets::Upgrade_HUD(Zone * _Zone)
{
	_HUD->_BuyBuff.sell_value = _Turrets[_Zone->turret_id].cost * 0.36 + ((_Zone->atk_speed_lvl + _Zone->damage_lvl + _Zone->range_lvl) * _Turrets[_Zone->turret_id].cost * 0.15);


	if (_Zone->atk_speed_lvl + 1 <= _Turrets[_Zone->turret_id].max_atk_speed_lvl) {

		_HUD->_BuyBuff.atkspeed_buff = true;
		_HUD->_BuyBuff.atkspeed_cost = (_Zone->atk_speed_lvl + 1) * buy_multiplier * _Turrets[_Zone->turret_id].cost;
		_HUD->_BuyBuff.atkspeed_value = _Turrets[_Zone->turret_id].base_attackspeed * _Turrets[_Zone->turret_id].atk_speed_multiplier;

		
		_HUD->_BuyBuff.display = true;
	}
	else
	{
		_HUD->_BuyBuff.atkspeed_buff = false;
		_HUD->_BuyBuff.atkspeed_cost = 0;
	}

	if (_Zone->damage_lvl + 1 <= _Turrets[_Zone->turret_id].max_dmg_lvl) {

		_HUD->_BuyBuff.attack_buff = true;
		_HUD->_BuyBuff.attack_cost = (_Zone->damage_lvl + 1) * buy_multiplier * _Turrets[_Zone->turret_id].cost;
		_HUD->_BuyBuff.attack_value = _Turrets[_Zone->turret_id].base_damage * _Turrets[_Zone->turret_id].dmg_multiplier;
		_HUD->_BuyBuff.display = true;
	}
	else
	{
		_HUD->_BuyBuff.attack_buff = false;
		_HUD->_BuyBuff.attack_cost = 0;
	}

	
	if (_Zone->range_lvl + 1 <= _Turrets[_Zone->turret_id].max_range_lvl) {

		_HUD->_BuyBuff.range_buff = true;
		_HUD->_BuyBuff.range_cost = (_Zone->range_lvl + 1) * buy_multiplier * _Turrets[_Zone->turret_id].cost;
		_HUD->_BuyBuff.range_value = _Turrets[_Zone->turret_id].base_range * _Turrets[_Zone->turret_id].range_multiplier;
		_HUD->_BuyBuff.display = true;
	}
	else
	{
		_HUD->_BuyBuff.range_buff = false;
		_HUD->_BuyBuff.range_cost = 0;
	}


	

}

void Turrets::reset()
{


	for (int i = 0; i < x_size; ++i) {

		for (int j = 0; j < y_size; ++j) {

			_Zone[i][j].atk_speed = 0;
			_Zone[i][j].atk_speed_lvl = 1;
			_Zone[i][j].damage = 0;
			_Zone[i][j].damage_lvl = 1;
			_Zone[i][j].placed = false;
			_Zone[i][j].range = 0;
			_Zone[i][j].range_lvl = 1;
			_Zone[i][j].turret_id = 0;
			_Zone[i][j].Turret_ATTACK = NULL;
			_Zone[i][j].Turret_IDLE = NULL;
			_Zone[i][j].Current_Animation = NULL;
			_Zone[i][j].target = NULL;
			_Zone[i][j].rotation = 0;
		}


	}


}
