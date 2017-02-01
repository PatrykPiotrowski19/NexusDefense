#pragma once
#include "Vec3.h"
#include "Board.h"

struct enemy {

	int type;
	int reward;
	int move_dir;

	int path_x;
	int path_z;

	float speed;
	float anim_speed;
	int damage;
	int target_value;
	float health;
	float max_health;
	bool enabled;
	float lifetime;
	unsigned int token;
	vec3 pos;
	vec3 old_pos;
	vec3 dir;
	CMD2Model *model;
	CMD2Model *preview;

	bool bleeding;
	int bleeding_duration;
	float bleeding_damage;

	bool slowed;
	int slowing_duration;
	float slow_value;



};


struct enemy_base_info {
	int enemy_id;
	float health_mult;
	float mov_speed_mult;
	float reward_mult;
	float dmg_mult;
};

class manage_enemy{

	struct waves {

		int number;
		int max;
	};
	CTexture *Enemy_Effects[2];
	float difficulty;
	long int T;
	int tmp_x, tmp_z;
	int current_value;
	bool found;
	short dir_x, dir_z;
	int tmp_coord_x, tmp_coord_z;
	board *_board;

	enemy_models *_enemy_models;
	Nexus *_Nexus;
	Fonts_management *_Fonts_management;


#pragma region zmienne dotyczace poruszania sie

	int left_neighbor;
	int right_neighbor;
	int upper_neighbor;
	int bottom_neighbor;
	float mov_speed;
	float rotation_value;

#pragma endregion

	vec3 *start_coords;
	int entraces_count;
	int actual_entrace;
	GLuint brick;

	int interval;
	int Time;
	int losuj;

	HUD *_HUD;
	CPlayer *Player;

public:
	bool victory;
	bool ace_voice;
	bool restart;
	int n;
	enemy *enemies[1000];
	enemy_base_info _enemy_base_info[15];
	int enemy_type_count;
	int max_enemies;

	void Set_Enemies_Attributes();
	void Render_Enemy(enemy *_enemy);
	void fetch_HUD_Pointer(HUD *_HUD);
	void fetch_Fonts_Pointer(Fonts_management *_Fonts_management);
	manage_enemy(board *_board, enemy_models *_enemy_models, Nexus *_Nexus, CPlayer *Player);
	void Render(vec3 cam_pos);
	void deal_field_damage(float radius, float damage, vec3 pos, enemy *_enemy);
	void Move(enemy *enemies);
	void Clear_Enemy(enemy *enemies);
	void New_Wave();
	void Manage_Enemy();
	void Update();
	void Restart();
	float Rotate_Info_To_Camera(vec3 cam_pos, vec3 enemy_pos);

};