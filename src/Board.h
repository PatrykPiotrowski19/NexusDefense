#pragma once
#include <string.h>
#include "Coursor.h"
#include "Turrets.h"

class HUD;
struct config;





struct map {
	string name;
	int x_size;
	int y_size;
	int **map_v;
	struct config *conf;

	int wave_count;
	int enemy_count;
	int *enemies;
	int **enemies_waves;
	int actual_wave;
	int *actual_enemies;
	int *base_enemies;
	int *slained_enemies;
	bool wave_start;
	float opacity;
	float bonus;
	int entraces;
};


class board {

	struct zoom_board {
		
		float scale;
		int pos[2];

	};

	zoom_board _zoom_board;


public:
	CTexture * _stone_texture;
	CTexture * _nexus;
	CTexture * _brick;
	map **maps;
	Turrets *_Turrets;
	int map_count;
	map *mapk;
	GLuint brick;
	GLuint nexus_obj;
	Coursor *_Coursor;
	vec3 Coursor_Pos;
	Fonts_management *_Fonts_management;
	Nexus *_Nexus;
	config *_config;
	HUD *_HUD;

	board(Coursor *_Coursor, config *_config);

	void fetch_turret_pointer(Turrets *_Turrets);
	void assign_config(config *_conf);
	void fetch_HUD_Pointer(HUD *_HUD);
	void fetch_nexus_pointer(Nexus *_Nexus);
	void fetch_fonts_pointer(Fonts_management *_Fonts_management);

	void load_maps();
	void load_maps_spec(char[100], map *tmp);
	void load_wave_info(char[100], map *tmp);
	int return_enemy_type(char[100]);


	void Render();
	void Update();
};