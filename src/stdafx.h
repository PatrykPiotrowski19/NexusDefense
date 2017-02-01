// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define PI 3.14159265



#include "targetver.h"
#include<vector>
#include <cassert>
#include <math.h>
#include<time.h>
#include<conio.h>
#include <vector>
#include<process.h>
#include <cstdio>
#include<list>
#include<string>
#include<fstream>
#include<iostream>
#include <string>
#include <sstream>
#include <vector>
#include<stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include <algorithm>
#include<al.h>
#include<alc.h>
#include<GL/glew.h>

#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib,"glew32.lib")

using namespace std;


#include "LoadShader.h"
#include "SoundManage.h"
#include "config.h"
#include "bmp.h"
#include "pcx.h"
#include "tga.h"

#include <GL/freeglut.h>
#include <GL/glext.h>

#include "Nexus.h"
#include "MD2_loader.h"
#include "MD2_texture.h"
#include "Fonts_management.h"
#include "Vec3.h"
#include "Bitmap.h"
#include "Texture.h"
#include "Obj_loader.h"
#include "Enemy_models.h"
#include "CollisionDetection.h"
#include "Collision.h"
#include "CollisionEllipsoid.h"
#include "CollisionPlane.h"
#include "CollisionPolygon.h"
#include "Board.h"
#include "Turrets.h"
#include "Player.h"
#include "Enemy.h"
#include "SceneObject.h"
#include "Skydome.h"
#include "Terrain.h"
#include "Wall.h"
#include "HUD.h"
#include "Coursor.h"
#include "Scene.h"
#include "Bullets.h"

#include "GKiW_Lab6.h"

#pragma region Zmienne globalne

	extern config_display _config_display;
	extern SoundManage *_SoundManage;
	extern Shading shaders;

	extern float gamespeed;
	extern float T;
	extern int mouseX;
	extern int mouseY;

	extern bool captureMouse;
	extern bool free3DMovement;
	extern bool left_mouse_button;

	extern float mouseSensitivity;

	extern CScene * Scene;
	extern bool pause;
	extern bool keystate[255];
	extern long int time_game;
	extern int frames;
	extern int updatetime;
	extern int updatetime_const;
	extern float gamespeed;

#pragma endregion
