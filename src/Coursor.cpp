#include "stdafx.h"
#include "Coursor.h"

Coursor::Coursor(CPlayer *_CPlayer)
{
	turret_id = -1;
	Obj.LoadModel("Data/Models/Coursor/Coursor.md2");
	Obj.LoadSkin("Data/Models/Coursor/Coursor_Texture.bmp");

	Obj.SetAnim(50);
	Obj.ScaleModel(1);




	this->_CPlayer = _CPlayer;
	position.x = 5;
	position.y = 0;
	position.z = 2;
}

void Coursor::Get_Turrets_Pointer(Turrets * _Turrets)
{
	this->_Turrets = _Turrets;
}

void Coursor::GetMapLimits(map * _map)
{


	range_x = (_map->y_size + 3)*-1;
	range_z = _map->x_size + 3;

}

void Coursor::Update()
{

	position.z += _CPlayer->velRY * 0.3;
	position.x += _CPlayer->velRX * 0.3;

	if (position.z > range_z)
		position.z = range_z;
	if (position.z < -3)
		position.z = -3;
	if (position.x < range_x)
		position.x = range_x;
	if (position.x > 3)
		position.x = 3;
		

}

void Coursor::Render()
{
	if (turret_id == -1) {
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glPushMatrix();
		glColor3f(1, 1, 1);
		glTranslatef(position.x, position.y, position.z);
		glRotatef(-30, 0, 0, 1);
		Obj.DrawModel(glutGet(GLUT_ELAPSED_TIME)*0.02);
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
	}

}

void Coursor::SetCurrentSelection(int turret_id)
{
	this->turret_id = turret_id;
}

int Coursor::ReturnCurrentSelection()
{
	return turret_id;
}


vec3 Coursor::ReturnPos()
{
	return position;
}
