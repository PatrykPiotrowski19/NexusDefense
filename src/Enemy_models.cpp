#include "stdafx.h"
#include "Enemy_models.h"

enemy_models::enemy_models()
{
	if(_config_display.Enemies_Quality == 1)
		Alistar.LoadModel("Data/Models/Alistar/Alistar_L.md2");
	if (_config_display.Enemies_Quality == 2)
		Alistar.LoadModel("Data/Models/Alistar/Alistar_M.md2");
	if (_config_display.Enemies_Quality == 3)
		Alistar.LoadModel("Data/Models/Alistar/Alistar_H.md2");


	Alistar.LoadSkin("Data/Models/Alistar/Alistar_Texture.bmp");


	if (_config_display.Enemies_Quality == 1)
		Evelynn.LoadModel("Data/Models/Evelynn/Evelynn_L.md2");
	if (_config_display.Enemies_Quality == 2)
		Evelynn.LoadModel("Data/Models/Evelynn/Evelynn_M.md2");
	if (_config_display.Enemies_Quality == 3)
		Evelynn.LoadModel("Data/Models/Evelynn/Evelynn_H.md2");

	Evelynn.LoadSkin("Data/Models/Evelynn/Evelynn_Texture.bmp");





	if (_config_display.Enemies_Quality == 1)
		Gromp.LoadModel("Data/Models/Gromp/Gromp_L.md2");
	if (_config_display.Enemies_Quality == 2)
		Gromp.LoadModel("Data/Models/Gromp/Gromp_M.md2");
	if (_config_display.Enemies_Quality == 3)
		Gromp.LoadModel("Data/Models/Gromp/Gromp_H.md2");


	Gromp.LoadSkin("Data/Models/Gromp/Gromp_Texture.bmp");


	if (_config_display.Enemies_Quality == 1)
		Minion_Melee.LoadModel("Data/Models/MinionMelee/MinionMelee_L.md2");
	if (_config_display.Enemies_Quality == 2)
		Minion_Melee.LoadModel("Data/Models/MinionMelee/MinionMelee_M.md2");
	if (_config_display.Enemies_Quality == 3)
		Minion_Melee.LoadModel("Data/Models/MinionMelee/MinionMelee_H.md2");


	Minion_Melee.LoadSkin("Data/Models/MinionMelee/MinionMelee_Texture.bmp");

	if (_config_display.Enemies_Quality == 1)
		Minion_Mage.LoadModel("Data/Models/MinionMage/MinionMage_L.md2");
	if (_config_display.Enemies_Quality == 2)
		Minion_Mage.LoadModel("Data/Models/MinionMage/MinionMage_M.md2");
	if (_config_display.Enemies_Quality == 3)
		Minion_Mage.LoadModel("Data/Models/MinionMage/MinionMage_H.md2");


	Minion_Mage.LoadSkin("Data/Models/MinionMage/MinionMage_Texture.bmp");


	if (_config_display.Enemies_Quality == 1)
		Krug.LoadModel("Data/Models/Krug/Krug_L.md2");
	if (_config_display.Enemies_Quality == 2)
		Krug.LoadModel("Data/Models/Krug/Krug_M.md2");
	if (_config_display.Enemies_Quality == 3)
		Krug.LoadModel("Data/Models/Krug/Krug_H.md2");


	Krug.LoadSkin("Data/Models/Krug/Krug_Texture.bmp");

	if (_config_display.Enemies_Quality == 1)
		Raptor_Mini.LoadModel("Data/Models/RaptorMini/RaptorMini_L.md2");
	if (_config_display.Enemies_Quality == 2)
		Raptor_Mini.LoadModel("Data/Models/RaptorMini/RaptorMini_M.md2");
	if (_config_display.Enemies_Quality == 3)
		Raptor_Mini.LoadModel("Data/Models/RaptorMini/RaptorMini_H.md2");


	Raptor_Mini.LoadSkin("Data/Models/RaptorMini/RaptorMini_Texture.bmp");


	if (_config_display.Enemies_Quality == 1)
		RiderChaos.LoadModel("Data/Models/RiderChaos/RiderChaos_L.md2");
	if (_config_display.Enemies_Quality == 2)
		RiderChaos.LoadModel("Data/Models/RiderChaos/RiderChaos_M.md2");
	if (_config_display.Enemies_Quality == 3)
		RiderChaos.LoadModel("Data/Models/RiderChaos/RiderChaos_H.md2");


	RiderChaos.LoadSkin("Data/Models/RiderChaos/RiderChaos_Texture.bmp");


	if (_config_display.Enemies_Quality == 1)
		RiderOrder.LoadModel("Data/Models/RiderOrder/RiderOrder_L.md2");
	if (_config_display.Enemies_Quality == 2)
		RiderOrder.LoadModel("Data/Models/RiderOrder/RiderOrder_M.md2");
	if (_config_display.Enemies_Quality == 3)
		RiderOrder.LoadModel("Data/Models/RiderOrder/RiderOrder_H.md2");


	RiderOrder.LoadSkin("Data/Models/RiderOrder/RiderOrder_Texture.bmp");

	if (_config_display.Enemies_Quality == 1)
		Hecarim.LoadModel("Data/Models/Hecarim/Hecarim_L.md2");
	if (_config_display.Enemies_Quality == 2)
		Hecarim.LoadModel("Data/Models/Hecarim/Hecarim_M.md2");
	if (_config_display.Enemies_Quality == 3)
		Hecarim.LoadModel("Data/Models/Hecarim/Hecarim_H.md2");


	Hecarim.LoadSkin("Data/Models/Hecarim/Hecarim_Texture.bmp");


	if (_config_display.Enemies_Quality == 1)
		Galio.LoadModel("Data/Models/Galio/Galio_L.md2");
	if (_config_display.Enemies_Quality == 2)
		Galio.LoadModel("Data/Models/Galio/Galio_M.md2");
	if (_config_display.Enemies_Quality == 3)
		Galio.LoadModel("Data/Models/Galio/Galio_H.md2");


	Galio.LoadSkin("Data/Models/Galio/Galio_Texture.bmp");


	Rammus.LoadModel("Data/Models/Rammus/Rammus.md2");
	Rammus.LoadSkin("Data/Models/Rammus/Rammus_Texture.bmp");


	if (_config_display.Enemies_Quality == 1)
		Udyr.LoadModel("Data/Models/Udyr/Udyr_L.md2");
	if (_config_display.Enemies_Quality == 2)
		Udyr.LoadModel("Data/Models/Udyr/Udyr_M.md2");
	if (_config_display.Enemies_Quality == 3)
		Udyr.LoadModel("Data/Models/Udyr/Udyr_H.md2");

	Udyr.LoadSkin("Data/Models/Udyr/Udyr_Texture.bmp");

	Herald.LoadModel("Data/Models/Herald/Herald.md2");
	Herald.LoadSkin("Data/Models/Herald/Herald_Texture.bmp");

	if (_config_display.Enemies_Quality == 1)
		Raptor.LoadModel("Data/Models/Raptor/Raptor_L.md2");
	if (_config_display.Enemies_Quality == 2)
		Raptor.LoadModel("Data/Models/Raptor/Raptor_M.md2");
	if (_config_display.Enemies_Quality == 3)
		Raptor.LoadModel("Data/Models/Raptor/Raptor_M.md2");


	Raptor.LoadSkin("Data/Models/Raptor/Raptor_Texture.bmp");

	Alistar.ScaleModel(1.1);
	Alistar.SetAnim(32);

	Evelynn.ScaleModel(1.1);
	Evelynn.SetAnim(22);

	Minion_Melee.ScaleModel(0.55);
	Minion_Melee.SetAnim(23);

	Minion_Mage.ScaleModel(0.55);
	Minion_Mage.SetAnim(23);

	Gromp.ScaleModel(0.45);
	Gromp.SetAnim(32);

	Krug.ScaleModel(0.55);
	Krug.SetAnim(15);

	Raptor_Mini.ScaleModel(0.7);
	Raptor_Mini.SetAnim(53);

	RiderChaos.ScaleModel(1.6);
	RiderChaos.SetAnim(57);

	RiderOrder.ScaleModel(1.6);
	RiderOrder.SetAnim(25);

	Hecarim.ScaleModel(0.8);
	Hecarim.SetAnim(25);

	Galio.ScaleModel(0.7);
	Galio.SetAnim(59);

	Rammus.ScaleModel(1.0);
	Rammus.SetAnim(14);

	Udyr.ScaleModel(0.65);
	Udyr.SetAnim(16);

	Herald.ScaleModel(0.55);
	Herald.SetAnim(40);
	
	Raptor.ScaleModel(1.05);
	Raptor.SetAnim(29);


}
