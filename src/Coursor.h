#pragma once
#include "stdafx.h"
#include "Turrets.h"

struct config;

class Coursor {

	CPlayer *_CPlayer;
	Turrets *_Turrets;
	vec3 position;
	CMD2Model Obj;
	int range_x;
	int range_z;
	int turret_id;

public:
	Coursor(CPlayer *_CPlayer);
	void Get_Turrets_Pointer(Turrets *_Turrets);
	void GetMapLimits(map *_map);
	void Update();
	void Render();
	void SetCurrentSelection(int turret_id);
	int ReturnCurrentSelection();
	vec3 ReturnPos();


};