#pragma once

struct config_display {

	char resolution[70];
	unsigned short Turrets_Quality;
	unsigned short Enemies_Quality;
	unsigned short Shadow_Quality;
	bool draw_fps;

	bool Sound_Enabled;
	bool Music_Enabled;

	int Sound_Volume;
	int Music_Volume;
	bool FullScreen;

	int map_id;
	float difficulty;


};