#include "stdafx.h"
#include "HUD.h"

HUD::HUD(Fonts_management *fonts_management, CPlayer *_CPlayer, Nexus *_Nexus)
{
	turret_id = 0;
	last_time = 0;
	framerate = 0;
	_InfoGame.visible_info = 0;
	_InfoGame.other_visible = 0;
	this->_Nexus = _Nexus;
	this->fonts_management = fonts_management;
	this->_CPlayer = _CPlayer;
	T = 0;

	enemies_slained = 0;
	_BuyBuff.display = 0;
	_BuyBuff.atkspeed_buff = 0;
	_BuyBuff.atkspeed_cost = 0;
	_BuyBuff.attack_buff = 0;
	_BuyBuff.attack_cost = 0;
	_BuyBuff.range_buff = 0;
	_BuyBuff.range_cost = 0;


	_TurretInfo.turret_id = 0;
	_TurretInfo.atk_speed = 0;
	_TurretInfo.damage = 0;
	_TurretInfo.display_turret_info = false;
	_TurretInfo.range = 0;
	_TurretInfo.x = 0;
	_TurretInfo.y = 0;

	position.x = 0;
	position.y = 0;
	position.z = 0;

	TurretInfo = new CTexture("Data\\HUD\\HUD\\hud_img.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	TurretInfoSquare = LoadObj("Data/HUD/HUD/TurretInfo.obj");

	Turret_Texture[0] = new CTexture("Data\\HUD\\Turrets_Icons\\Shacodoll_Icon.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Turret_Texture[1] = new CTexture("Data\\HUD\\Turrets_Icons\\HeimerTurret1_Icon.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Turret_Texture[2] = new CTexture("Data\\HUD\\Turrets_Icons\\HeimerTurret2_Icon.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Turret_Texture[3] = new CTexture("Data\\HUD\\Turrets_Icons\\ZyraPlant_Icon.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Turret_Texture[4] = new CTexture("Data\\HUD\\Turrets_Icons\\IllaoiPlant_Icon.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Turret_Texture[5] = new CTexture("Data\\HUD\\Turrets_Icons\\Urf_Icon.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Turret_Texture[6] = new CTexture("Data\\HUD\\Turrets_Icons\\AzirTurret_Icon.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	Turret_Texture_D[0] = new CTexture("Data\\HUD\\Turrets_Icons\\Shacodoll_Icon_L.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Turret_Texture_D[1] = new CTexture("Data\\HUD\\Turrets_Icons\\HeimerTurret1_Icon_L.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Turret_Texture_D[2] = new CTexture("Data\\HUD\\Turrets_Icons\\HeimerTurret2_Icon_L.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Turret_Texture_D[3] = new CTexture("Data\\HUD\\Turrets_Icons\\ZyraPlant_Icon_L.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Turret_Texture_D[4] = new CTexture("Data\\HUD\\Turrets_Icons\\IllaoiPlant_Icon_L.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Turret_Texture_D[5] = new CTexture("Data\\HUD\\Turrets_Icons\\Urf_Icon_L.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Turret_Texture_D[6] = new CTexture("Data\\HUD\\Turrets_Icons\\AzirTurret_Icon_L.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);


	Enemy_Icon[0] = new CTexture("Data\\HUD\\EnemyIcons\\MinionMage.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Enemy_Icon[1] = new CTexture("Data\\HUD\\EnemyIcons\\MinionMelee.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Enemy_Icon[2] = new CTexture("Data\\HUD\\EnemyIcons\\KrugMini.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Enemy_Icon[3] = new CTexture("Data\\HUD\\EnemyIcons\\RaptorMini.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	Enemy_Icon[4] = new CTexture("Data\\HUD\\EnemyIcons\\Gromp.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Enemy_Icon[5] = new CTexture("Data\\HUD\\EnemyIcons\\RiderChaos.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Enemy_Icon[6] = new CTexture("Data\\HUD\\EnemyIcons\\RiderOrder.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Enemy_Icon[7] = new CTexture("Data\\HUD\\EnemyIcons\\Raptor.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	Enemy_Icon[8] = new CTexture("Data\\HUD\\EnemyIcons\\Alistar.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Enemy_Icon[9] = new CTexture("Data\\HUD\\EnemyIcons\\Hecarim.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Enemy_Icon[10] = new CTexture("Data\\HUD\\EnemyIcons\\Galio.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Enemy_Icon[11] = new CTexture("Data\\HUD\\EnemyIcons\\Rammus.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Enemy_Icon[12] = new CTexture("Data\\HUD\\EnemyIcons\\Udyr.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	Enemy_Icon[13] = new CTexture("Data\\HUD\\EnemyIcons\\Herald.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Enemy_Icon[14] = new CTexture("Data\\HUD\\EnemyIcons\\Evelynn.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

	Enemy_Effects[0] = new CTexture("Data\\HUD\\Icons\\slow.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
	Enemy_Effects[1] = new CTexture("Data\\HUD\\Icons\\bleeding.bmp", GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);


}

void HUD::Get_EnemyModels_Pointer(enemy_models * _enemy_models)
{
	this->_enemy_models = _enemy_models;
}

void HUD::Get_TimeStamp(int * timestamp)
{
	this->timestamp = timestamp;
}

void HUD::GetCurrentSelection(int turret_id)
{
	this->turret_id = turret_id;
}

void HUD::Get_Actual_Map_Pointer(map * _map)
{
	this->_map = _map;
}

void HUD::Get_Turrets_Pointer(Turrets * _Turrets)
{
	this->_Turrets = _Turrets;
}

void HUD::Render_header()
{
	//cout << "T: " << T << endl;
	if (last_time < T) {

		last_time = T + 1000;
		framerate = frames;
		frames = 0;
	}

	float color[3] = { 0.0f, 1.0f, 0.35f };
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, 1920, 0.0, 1080, -1.0, 1.0);
	gluPerspective(50.0f, 200/201, 1.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_TEXTURE_2D);
	width = 1920;
	height = 1080;

#pragma endregion	

	glRotatef(90, 1, 0, 0);

}

void HUD::Render_footer()
{

#pragma region PRZYWROCENIE POPRZEDNICH USTAWIEN
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRasterPos2d(10, 10);
	glScalef(0.1, 0.1, 0.1);
	glPopMatrix();

#pragma endregion

}

void HUD::Render_End_Game(int status)
{
	Render_header();

		End_Info(status);

	Author();
	Render_Turrets();
	Render_footer();
}

void HUD::End_Info(int status)
{

	vec3 color_bg;
	vec3 color_value;

	color_bg.x = 0.972;
	color_bg.y = 0.7109;
	color_bg.z = 0;
	color_value = 1;

	char buf[40];


	_InfoGame.visible_info += 0.0017;
	_InfoGame.other_visible += 0.0017;

	if (_InfoGame.visible_info > 0.9)
		_InfoGame.visible_info = 0.9;

	glPushMatrix();
	glTranslatef(960, 0.12, -920);
	if (status == 1) {
		glColor4f(1.0, 0.1, 0.1, _InfoGame.visible_info);
		fonts_management->drawtext("DEFEAT", 0, 1, 125);
	}
	if (status == 2) {
		glColor4f(0.1, 1.0, 0.1, _InfoGame.visible_info);
		fonts_management->drawtext("VICTORY", 0, 1, 125);
	}

	glTranslatef(0, 0, 90);
	glColor4f(color_value.x, color_value.y, color_value.x, _InfoGame.visible_info);
	fonts_management->drawtext("WAVES SURVIVED", 0, 1, 55);
	glTranslatef(0, 0, 45);
	glColor4f(color_bg.x, color_bg.y, color_bg.z, _InfoGame.visible_info);
	sprintf(buf, "%d/%d", _map->actual_wave, _map->wave_count);
	fonts_management->drawtext(buf, 0, 1, 40);
	glTranslatef(0, 0, 60);
	glColor4f(color_value.x, color_value.y, color_value.x, _InfoGame.visible_info);

	fonts_management->drawtext("SLAINED ENEMIES", 0, 1, 55);
	glTranslatef(0, 0, 45);
	sprintf(buf, "%d", enemies_slained);
	glColor4f(color_bg.x, color_bg.y, color_bg.z, _InfoGame.visible_info);
	fonts_management->drawtext(buf, 0, 1, 40);
	glTranslatef(0, 0, 60);
	glColor4f(color_value.x, color_value.y, color_value.x, _InfoGame.visible_info);

	fonts_management->drawtext("TOTAL GOLD EARNED", 0, 1, 55);
	glTranslatef(0, 0, 45);
	sprintf(buf, "%d$", _CPlayer->return_total_money());
	glColor4f(color_bg.x, color_bg.y, color_bg.z, _InfoGame.visible_info);
	fonts_management->drawtext(buf, 0, 1, 40);
	glTranslatef(0, 0, 60);
	glColor4f(color_value.x, color_value.y, color_value.x, _InfoGame.visible_info);
	fonts_management->drawtext("MONEY SPENT ON TURRETS", 0, 1, 55);
	glTranslatef(0, 0, 45);
	sprintf(buf, "%d$", _CPlayer->return_money_turrets());
	glColor4f(color_bg.x, color_bg.y, color_bg.z, _InfoGame.visible_info);
	fonts_management->drawtext(buf, 0, 1, 40);
	glTranslatef(0, 0, 60);
	glColor4f(color_value.x, color_value.y, color_value.x, _InfoGame.visible_info);
	fonts_management->drawtext("MONEY SPENT ON UPGRADES", 0, 1, 55);
	glTranslatef(0, 0, 45);
	sprintf(buf, "%d$", _CPlayer->return_money_upgrades());
	glColor4f(color_bg.x, color_bg.y, color_bg.z, _InfoGame.visible_info);
	fonts_management->drawtext(buf, 0, 1, 40);

	glTranslatef(0, 0, 170);
	glColor4f(1,1,1, _InfoGame.visible_info);
	fonts_management->drawtext("PRESS (X) TO QUIT GAME", 0, 1, 70);
	glTranslatef(0, 0, 90);
	glColor4f(1, 1, 1, _InfoGame.visible_info);
	fonts_management->drawtext("PRESS (R) TO RESTART GAME", 0, 1, 70);

	glPopMatrix();


}

void HUD::Render()
{
	
	Render_header();
	Show_FPS();
	Show_Speed();
	WaveInfo();
	Render_Turret_Info();
	//Render_Turret_Place_Info();
	Draw_Money_Info();
	Author();
	//Enemies_slained();
	DisplayBuffInfo();

	Render_Turrets();
	Watermark();



	Render_footer();
	
}

void HUD::Render_Turret_Info()
{
	char value[20];
	if (_TurretInfo.display_turret_info) {
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glTranslatef(0, 0, -35);
		glTranslatef(70, 0, -290);
		glScalef(87, 92, 92);
		glColor4f(1, 1, 1, 0.82);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, TurretInfo->GetId());
		glCallList(TurretInfoSquare);
		glPopMatrix();
		
		glPushMatrix();
		glTranslatef(0, 0, -35);
		glColor4f(0.7, 0.9, 0.5, 0.55);
		glDisable(GL_TEXTURE_2D);
		glTranslatef(295, 0, -252);
		sprintf(value, "%f", _TurretInfo.damage);
		value[5] = '\0';
		fonts_management->drawtext(value, 0, 0, 36);
		glTranslatef(0, 0, 48);
		sprintf(value, "%f", _TurretInfo.atk_speed);
		value[5] = '\0';
		fonts_management->drawtext(value, 0, 0, 36);
		glTranslatef(0, 0, 48);
		sprintf(value, "%f", _TurretInfo.range);
		value[5] = '\0';
		fonts_management->drawtext(value, 0, 0, 36);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0, 0, -35);
		glTranslatef(105, 0, -170);
		glColor4f(1, 1, 1, 0.6);
		glBindTexture(GL_TEXTURE_2D, Turret_Texture[_TurretInfo.turret_id]->GetId());
		fonts_management->drawtext("CIRCLE", 0, 0, 240);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(245, 0, -150);
		glColor4f(0.7, 0.9, 0.5, 0.9);
		glScalef(0.3, 0.3, 0.3);

		switch (_TurretInfo.turret_id) {

			case 0: fonts_management->drawtext("Slows the target by 15% for 1 second", 0, 1, 80); break;
			case 1: fonts_management->drawtext("Every 3rd shot deals double damage", 0, 1, 80); break;
			case 2: fonts_management->drawtext("Bullets deals up to 30% damage in area (range 1.6)", 0, 1, 80); break;
			case 3: fonts_management->drawtext("Her attacks slows the target by 35% for 1.5 seconds", 0, 1, 80); break;
			case 4: fonts_management->drawtext("Deals 100% damage to enemies near target (range 0.8)", 0, 1, 70); break;
			case 5: fonts_management->drawtext("His bullets deals damage over time", 0, 1, 80); 
				glTranslatef(0, 0, 60);
				fonts_management->drawtext("7 % of maximum health per 2 seconds", 0, 1, 80);
				glTranslatef(0, 0, 60);
				fonts_management->drawtext("This effect is doubled for slowed target", 0, 1, 80);
				break;
			case 6: fonts_management->drawtext("Every one shot deals 20% more damage to target ", 0, 1, 80);
				glTranslatef(0, 0, 60);
				fonts_management->drawtext("(stacks up to 6 times)", 0, 1, 80);
				break;
		}
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
	}
}

void HUD::Render_Turret_Place_Info()
{
	if (turret_id != -1) {
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, 0, -0.06);
		glBegin(GL_QUADS);
		glColor4f(0.0, 0, 0, 0.55f);
		glVertex2f(700, 315.0);
		glVertex2f(700, 180.0);
		glVertex2f(1220.0, 180.0);
		glVertex2f(1220.0, 315.0);

		glEnd();
		glPopMatrix();
	}

}

void HUD::Render_Turrets()
{
	int x_start = 510;
	bool placing = false;
	int x_size = 120;
	int x_interval = 120;
	int x_break = 10;
	char str[3];
	vec3 tmp;
	char money[10];
	glPushMatrix();
	glTranslatef(155, 0, 0);
	glScalef(0.85, 0.85, 0.85);
	for (int i = 0; i < 7; i++) {
		position.x = x_start + x_interval*i + x_break*i + 7;
		position.y = 0.05;
		position.z = -0.08 * height;
		itoa(i+1, str, 10);

		


		glPushAttrib(GL_CURRENT_BIT);
		glPushMatrix();
		glPushMatrix();
		glColor4f(1, 1, 1,0.65 - _InfoGame.other_visible * 0.8);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (_Turrets->_Turrets[i].cost <= _CPlayer->money)
			glBindTexture(GL_TEXTURE_2D, Turret_Texture[i]->GetId());
		else
			glBindTexture(GL_TEXTURE_2D, Turret_Texture_D[i]->GetId());
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		
		fonts_management->drawtext("CIRCLE", position, 0, 220);
		tmp = position;
		position.y = 0.4;
		position.x += 17;
		position.z -= 6;

		
		glPushAttrib(GL_CURRENT_BIT);
		glPushMatrix();
		glColor4f(1, 1, 1, 0.75 - _InfoGame.other_visible);

		if (i + 1 == turret_id)
		{
			placing = true;

			if(_CPlayer->money >= _Turrets->_Turrets[i].cost)
				glColor4f(sin(glutGet(GLUT_ELAPSED_TIME)*0.003) + 0.5, 1, sin(glutGet(GLUT_ELAPSED_TIME)*0.003) + 0.5, 1);
			else
				glColor4f(1, sin(glutGet(GLUT_ELAPSED_TIME)*0.003) + 0.5, sin(glutGet(GLUT_ELAPSED_TIME)*0.003) + 0.5, 1);
		}
			


		fonts_management->drawtext(str, position, 0, 120);

		position = tmp;
		position.x += 40;
		position.y = 0.4;
		position.z += 53;
		
		if(_Turrets->_Turrets[i].cost > _CPlayer->money)
			glColor4f(0.7,0,0,0.8 - _InfoGame.other_visible);
		else
			glColor4f(0,0.7,0,0.8 - _InfoGame.other_visible);



		sprintf(money, "%d", _Turrets->_Turrets[i].cost);

		fonts_management->drawtext(money, position, 1, 48);

		glDisable(GL_BLEND);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glPopMatrix();
		glPopAttrib();
		glPopMatrix();

		/*
		glBegin(GL_QUADS);
		glColor4f(0, 0, 0, 0.5f);
		glVertex2f(x_start + x_interval*i + x_break*i, 80.0);
		glVertex2f(x_start + x_interval*i + x_break*i, 200.0);
		glVertex2f(x_size + x_start + x_interval*i + x_break*i, 200.0);
		glVertex2f(x_size + x_start + x_interval*i + x_break*i, 80.0);

		glEnd();

		glBegin(GL_QUADS);
		glColor4f(0, 0, 0, 0.5f);
		glVertex2f(x_start + x_interval*i + x_break*i, 20.0);
		glVertex2f(x_start + x_interval*i + x_break*i, 70.0);
		glVertex2f(x_size + x_start + x_interval*i + x_break*i, 70.0);
		glVertex2f(x_size + x_start + x_interval*i + x_break*i, 20.0);

		glEnd();
		*/

		if (placing)
		{
			vec3 pos;
			pos.x = 960;
			pos.z = -200;
			glColor4f(0.9, 0.9, 0.9, 0.8);
			fonts_management->drawtext("Press C to cancel turret picking", pos, 1, 60);
		}

		glPopMatrix();
		glPopAttrib();
	}

	glPopMatrix();
}

void HUD::DisplayBuffInfo()
{

	float green[] = { 0,0.8,0 };
	float red[] = { 0.8,0,0 };
	if (_BuyBuff.display || _BuyBuff.sell_value) {
		char buff[60];
		glPushAttrib(GL_CURRENT_BIT);


		glPushMatrix();
		glTranslatef(250, 0.12, -480);
		glColor4f(1, 0.95, 0.66, 0.8);
		fonts_management->drawtext("UPGRADES", 0, 1, 48);

		glColor4f(1, 1, 1, 0.8);
		glTranslatef(-10, 0, 0);
		if (_BuyBuff.attack_buff) {
			glTranslatef(0, 0, 35);
			if (_CPlayer->money >= _BuyBuff.attack_cost)
				glColor4f(green[0], green[1], green[2], 0.8);
			else
				glColor4f(red[0], red[1], red[2], 0.8);

			sprintf(buff, "(Q)   Attack Damage  %d$", _BuyBuff.attack_cost,_BuyBuff.atkspeed_value);
			fonts_management->drawtext(buff, 0, 1, 25);
		}

		if (_BuyBuff.atkspeed_buff) {
			if (_CPlayer->money >= _BuyBuff.atkspeed_cost)
				glColor4f(green[0], green[1], green[2], 0.8);
			else
				glColor4f(red[0], red[1], red[2], 0.8);

			glTranslatef(0, 0, 35);
			sprintf(buff, "(W)   Attack Speed  %d$", _BuyBuff.atkspeed_cost);
			fonts_management->drawtext(buff, 0, 1, 25);
		}

		if (_BuyBuff.range_buff) {
			if (_CPlayer->money >= _BuyBuff.range_cost)
				glColor4f(green[0], green[1], green[2], 0.8);
			else
				glColor4f(red[0], red[1], red[2], 0.8);


			glTranslatef(0, 0, 35);
			sprintf(buff, "(E)   Range %d$", _BuyBuff.range_cost);
			fonts_management->drawtext(buff, 0, 1, 25);
		}
		glColor4f(0.7, 0.7, 0.7, 0.8);
		glTranslatef(0, 0, 35);
		sprintf(buff, "(R)   Sell for %d$", _BuyBuff.sell_value);
		fonts_management->drawtext(buff, 0, 1, 25);
		glPopMatrix();


		glPushMatrix();
		glScalef(1.1, 1, 1);
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, 0, -0.06);
		glBegin(GL_QUADS);
		glColor4f(0.0, 0, 0, 0.6f);
		glVertex2f(60, 295.0 + !_BuyBuff.range_buff * 45 + !_BuyBuff.attack_buff * 45 + !_BuyBuff.atkspeed_buff * 45);
		glVertex2f(60, 530.0);
		glVertex2f(380.0, 530.0);
		glVertex2f(380.0, 295.0 + !_BuyBuff.range_buff * 45 + !_BuyBuff.attack_buff * 45 + !_BuyBuff.atkspeed_buff * 45);

		glEnd();

		glPopMatrix();
		glPopAttrib();


	}

}

void HUD::Show_FPS()
{
	if (_config_display.draw_fps) {
		char value[30];
		glPushAttrib(GL_CURRENT_BIT);
		glPushMatrix();
		glColor4f(1, 1, 1, 0.9);
		position.x = width*0.94;
		position.z = -height*0.975;
		fonts_management->drawtext("FPS: ", position, 0, 30);
		position.x = width*0.97;
		sprintf(value, "%d", framerate);
		if (framerate > 45)
			glColor4f(0, 1, 0, 0.9);
		else
			if (framerate > 25)
				glColor4f(1, 0.8, 0, 0.9);
			else
				glColor4f(1, 0, 0, 0.9);

		fonts_management->drawtext(value, position, 0, 30);
		position.z = -height*0.945;
		position.x = width*0.93;
		sprintf(value, "Updates Per Second : %d", updatetime_const);
		glColor4f(0.5, 1, 1, 0.9);
		//fonts_management->drawtext(value,position, 1, 30);
		//sprintf(value, "UpdateTime (ms) : %d", updatetime);
		//position.z = -height*0.93;
		//position.x = width*0.9;
		//fonts_management->drawtext(value, position, 0, 27);
		glPopMatrix();
		glPopAttrib();

	}


}

void HUD::Show_Speed()
{

	char value[30];
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glColor4f(1, 1, 1, 0.9);
	vec3 position;
	position.x = width*0.86;
	position.z = -height*0.55;
	position.y = 0;
	sprintf(value, "GAMESPEED: x%f", gamespeed);
	value[15] = '\0';
	fonts_management->drawtext(value, position, 0, 42);
	position.x = width*0.915;
	glColor4f(0.5, 0.9, 0.1, 0.9);
	position.z = -height*0.52;
	fonts_management->drawtext("+ to speed-up" , position, 1, 25);
	position.z = -height*0.5;
	fonts_management->drawtext("- to slow-down", position, 1, 25);
	glPopMatrix();
	glPopAttrib();




}

void HUD::Author()
{

#pragma region Author
	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();
	glColor4f(1, 1, 1, 0.7);
	position.x = width*0.9;
	position.z = -height*0.06;
	fonts_management->drawtext("Public BETA  Version  0.30  Made by Cortez", position, 1, 26);
	position.z = -height * 0.01;
	glColor4f(1.5 + sin(glutGet(GLUT_ELAPSED_TIME)*0.001),1.5 + cos(glutGet(GLUT_ELAPSED_TIME)*0.001), 0, 1.0);
	fonts_management->drawtext("youtube.com/PirateeCortez", position, 1, 28);
	position.z = -height*0.035;
	glColor4f(1.5 + cos((glutGet(GLUT_ELAPSED_TIME)+2.4)*0.001), 1.5 + sin((glutGet(GLUT_ELAPSED_TIME) + 2.9)*0.001), 0, 1.0);
	fonts_management->drawtext("facebook.com/NexusDefenseGame", position, 1, 28);
	//fonts_management->drawtext("DieDope Edition", position, 1, 65);
	glPopMatrix();
	glPopAttrib();


	//cout << "GLUT SCREEN WIDTH" << GLUT_SCREEN_WIDTH << "\tGLUT SCREEN HEIGHT" << GLUT_SCREEN_HEIGHT << endl;
#pragma endregion


}

void HUD::Enemies_slained()
{
	char buf[25];
	glPushMatrix();
	sprintf(buf, "Enemies slained: %d", enemies_slained);
	glTranslatef(1500, -0.05, -70);
	fonts_management->drawtext(buf, 0, 0, 43);
	glPopMatrix();
	

}

void HUD::Watermark()
{


}

void HUD::Render_Pause()
{
	Render_header();

	Author();
	Pause_Info();

	Render_footer();

}

void HUD::Draw_Money_Info()
{
	char text[30];

	glPushMatrix();
	glColor3f((float)249/256,(float) 182/256,(float) 0/256);
	position.x = width*0.12;
	position.z = -height*0.05;
	sprintf(text, "Money: %d$", _CPlayer->money);
	fonts_management->drawtext(text, position, 1, 62);
	glPopMatrix();


	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();

	glScalef(1.1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 0, -0.06);
	glBegin(GL_QUADS);
	glColor4f(0, 0, 0, 0.45f);
	glVertex2f(60, 35.0);
	glVertex2f(60, 110.0);
	glVertex2f(380.0, 110.0);
	glVertex2f(380.0, 35.0);

	glEnd();

	glPopMatrix();
	glPopAttrib();



}

void HUD::WaveInfo()
{

	char buf[25];



	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();

	if (_map->wave_start == false) {

		char tmp[30];

		glPushMatrix();
		glTranslatef(960, 0.12, -740);
		glColor4f(1.0, 0.4, 0.3, 1.0 + sin(glutGet(GLUT_ELAPSED_TIME)*0.0025)*0.3);
		fonts_management->drawtext("Press SPACEBAR to start new wave", 0, 1, 80 + sin(glutGet(GLUT_ELAPSED_TIME)*0.0025) * 8);
		
		if (_map->bonus > 0) {
			glColor4f(1.0, 1.0, 0.0, 0.7);
			glTranslatef(0, 0, 95);
			sprintf(tmp, "Bonus Gold: %d$", (int)_map->bonus);
			fonts_management->drawtext(tmp, 0, 1, 55);


		}
		glPopMatrix();



	}


	glPushMatrix();

	glTranslatef(40, 0.12, -1040);
	glColor4f((float)249 / 256, (float)182 / 256, (float)0 / 256,0.9);
	if(_map->wave_start)
		sprintf(buf, "WAVE:  %d/%d",_map->actual_wave, _map->wave_count);
	else
		sprintf(buf, "NEXT WAVE:  %d/%d", _map->actual_wave, _map->wave_count);
	fonts_management->drawtext(buf, 0, 0, 38);
	glPopMatrix();
	int k = 0;
	glColor4f(1, 1, 1, 0.3);
	for (int i = 0; i < _map->enemy_count; i++) {
		
		if (_map->base_enemies[i] - _map->slained_enemies[i] > 0) {
			glPushMatrix();
			glTranslatef(45 + k++ * 55, 0.12, -980);
			glBindTexture(GL_TEXTURE_2D, Enemy_Icon[_map->enemies[i]]->GetId());
			fonts_management->drawtext("CIRCLE", 0, 0, 90);
			glTranslatef(16, 0, 30);
			glColor4f(1, 1, 1, 1);
			sprintf(buf, "%d", _map->base_enemies[i] - _map->slained_enemies[i]);
			fonts_management->drawtext(buf, 0, 1, 30);
			glPopMatrix();
		}
	}





	glScalef(1.1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 0, -0.06);
	/*
	glBegin(GL_QUADS);
	glColor4f(0, 0, 0, 0.35f);
	glVertex2f(60, 520.0);
	glVertex2f(60, 1050.0);
	glVertex2f(380.0, 1050.0);
	glVertex2f(380.0, 520.0);

	glEnd();
	*/

	glPopMatrix();
	glPopAttrib();

}

void HUD::NewGame()
{

	_InfoGame.visible_info = 0;
	_InfoGame.other_visible = 0;

}

void HUD::Pause_Info()
{


	glPushMatrix();
	glColor3f((float)233 / 256, (float)239 / 256, (float)163 / 256);
	position.x = width*0.5;
	position.z = -height*0.82;
	fonts_management->drawtext("Game Paused", position, 1, 62);
	glPushMatrix();
	position.z = -height*0.75;
	position.x = width*0.5;
	glColor3f(1, 1, 1);
	fonts_management->drawtext("(ESC) -> Resume", position, 1, 45);
	position.z = -height*0.69;
	fonts_management->drawtext("(X) -> Exit", position, 1, 45);
	glPopMatrix();
	position.x = width*0.13;
	glPopMatrix();


	glPushAttrib(GL_CURRENT_BIT);
	glPushMatrix();

	glScalef(1.1, 1, 1);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(0, 0, -0.06);
	glBegin(GL_QUADS);
	glColor4f(0.2,0.2, 0.2, 0.7);
	glVertex2f(690, 940.0);
	glVertex2f(690, 640.0);
	glVertex2f(1060.0, 640.0);
	glVertex2f(1060.0, 940.0);

	glEnd();

	glPopMatrix();
	glPopAttrib();


}
