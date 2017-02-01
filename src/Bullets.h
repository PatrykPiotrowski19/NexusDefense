#pragma once
#include "stdafx.h"
class manage_bullets {


	struct bullet {
		vec3 position;
		float damage;
		float rotation;
		float speed;
		int bullet_type;
		enemy *target;
		int distance;
		int target_token;

		struct bullet *prev;
		struct bullet *next;

	};

	struct bullet *wsk;

	void remove_bullet(struct bullet *remove);
	void init_bullet();
	void move_bullet(struct bullet *current);
	void set_bleeding_effect(struct enemy *target, int duration, float damage);
	void set_slowing_effect(struct enemy *target, int duration, float slow);
	void deal_damage(struct bullet *_bullet);


	GLuint bullet_cylinder;
	manage_enemy *_manage_enemy;
	GLuint spoon;
	CTexture *spoon_texture;
	GLuint ball;
	CTexture *ball_texture;
	GLuint plant;
	CTexture *plant_texture;

public:

	manage_bullets();
	void get_pointer_manage_enemy(manage_enemy *_manage_enemy);
	void LoadModels();
	void add_bullet(vec3 position, float damage, float speed, int bullet_type, enemy *target);
	void Update();
	void Render();


};