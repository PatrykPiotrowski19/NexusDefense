#pragma once

#include "Board.h"

class manage_bullets;
class Coursor;
struct map;
struct enemy;
class HUD;
class Turrets {



	struct Zone {

		CMD2Model *Turret_IDLE;
		CMD2Model *Turret_ATTACK;
		CMD2Model *Current_Animation;
		

		enemy *target;
		bool placed;
		int turret_id;
		int target_shoots;

		float damage;
		float bonus_damage;
		float damage_lvl;
		
		float atk_speed;
		float atk_speed_lvl;

		float range;
		float range_lvl;

		float interval;

		int rotation;
		int shoots;

		float animation_speed;
		float animation_base_speed;

	};


	CPlayer *_CPlayer;
	int x_size;
	int y_size;


	map *_map;
	GLuint ring;


	enemy **_enemy;
	int enemy_count;
	Coursor *_Coursor;

	struct tmp_info {
		enemy *target;
		float distance;
	};

	public:

		struct Turret_Model {

			CMD2Model Turret_IDLE;
			CMD2Model Turret_ATTACK;
			int idle_length;
			int attack_length;

			//Elementy startowe
			float base_damage;
			float base_attackspeed;
			float base_range;

			//Maksymalne poziomy
			int max_dmg_lvl;
			int max_atk_speed_lvl;
			int max_range_lvl;

			//Mnoznik co poziom
			float dmg_multiplier;
			float atk_speed_multiplier;
			float range_multiplier;
			int cost;


		};
		float buff_mult;
		bool pressed_q;
		bool pressed_w;
		bool pressed_e;
		bool current_placed;



		Zone **_Zone;
		manage_bullets *bullets;
		HUD *_HUD;
		Turret_Model _Turrets[7];
		float buy_multiplier;
		CPlayer *_Player;
	Turrets(map *_map, CPlayer *_CPlayer);


	void Get_Enemy_Pointer(enemy **_enemy, int enemy_count);
	void Get_Player_Pointer(CPlayer *_Player);
	void Get_HUD_Pointer(HUD *_HUD);
	void Get_Bullet_Pointer(manage_bullets *bullets);
	void Get_Coursor_Pointer(Coursor *_Coursor);


	void Render();
	void Update();

	void PlaceTurret(int id, int x, int y);
	void ManageTurret(int pos_x, int pos_z);
	int Rotate_To_Target(vec3 turret, vec3 enemy);
	void RemoveTurret(int x, int y);
	float return_distance(vec3 turret, vec3 enemy);


	void Upgrade_Atk_Speed(Zone *_Zone);
	void Upgrade_Attack(Zone *_Zone);
	void Upgrade_Range(Zone *_Zone);
	void Upgrade_HUD(Zone *_Zone);


	void reset();


};