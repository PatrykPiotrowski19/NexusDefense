#pragma once
#include "stdafx.h"

class enemy_models {
public:
	
	#pragma region TIER_1
	
	CMD2Model Minion_Melee;
	CMD2Model Minion_Mage;
	CMD2Model Krug;
	CMD2Model Raptor_Mini;

#pragma endregion

	#pragma region TIER_2
	CMD2Model Gromp;
	CMD2Model RiderChaos;
	CMD2Model RiderOrder;
	CMD2Model Raptor;

#pragma endregion

	#pragma region TIER_3
	CMD2Model Alistar;
	CMD2Model Hecarim;
	CMD2Model Galio;
	CMD2Model Rammus;
	CMD2Model Udyr;

#pragma endregion

	#pragma region TIER_4

	CMD2Model Herald;

#pragma endregion

#pragma region TIER_5 SPECJALNE POSTACIE

	CMD2Model Evelynn;

#pragma endregion
	enemy_models();


};