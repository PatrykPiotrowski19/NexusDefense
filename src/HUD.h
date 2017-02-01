#pragma once
#include "Vec3.h"

class HUD {

	Fonts_management *fonts_management;
	CPlayer *_CPlayer;
	vec3 position;
	Nexus *_Nexus;
	Turrets *_Turrets;
	enemy_models *_enemy_models;
	int width, height;
	map *_map;

	CTexture *Turret_Texture[7];
	CTexture *Turret_Texture_D[7];

	CTexture *Enemy_Icon[15];

	CTexture *TurretInfo;
	GLuint TurretInfoSquare;
	float fps;

	struct InfoGame {

		float visible_info;
		float other_visible;

	};

	InfoGame _InfoGame;
	int turret_id;
public:

	struct TurretInfo{
		int turret_id;
		int x, y;
		float atk_speed;
		float damage;
		float range;
		bool display_turret_info;
	};

	struct BuyBuff {

		bool display;

		bool attack_buff;
		int attack_cost;
		int attack_level;
		float attack_value;
		
		bool atkspeed_buff;
		int atkspeed_cost;
		int atkspeed_level;
		float atkspeed_value;

		bool range_buff;
		int range_cost;
		int range_level;
		float range_value;

		int sell_value;


	};
	int *timestamp;
	float last_time;
	int enemies_slained;
	int framerate;

	struct TurretInfo _TurretInfo;
	struct BuyBuff _BuyBuff;
	CTexture *Enemy_Effects[2];



	HUD(Fonts_management *fonts_management, CPlayer *_CPlayer, Nexus *_Nexus);
	void Get_EnemyModels_Pointer(enemy_models *_enemy_models);
	void Get_TimeStamp(int *timestamp);
	void GetCurrentSelection(int turret_id);
	void Get_Actual_Map_Pointer(map *_map);
	void Get_Turrets_Pointer(Turrets *_Turrets);
	void Render_header();
	void Render_footer();
	void Render_End_Game(int);


	void End_Info(int);
	
	void Render();
	void Render_Turret_Info();
	void Render_Turret_Place_Info();
	void Render_Turrets();
	void DisplayBuffInfo();
	void Show_FPS();
	void Show_Speed();
	void Author();
	void Enemies_slained();
	void Watermark();
	void Render_Pause();
	void Draw_Money_Info();
	void WaveInfo();
	void NewGame();


	void Pause_Info();


};