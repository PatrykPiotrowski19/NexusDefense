#pragma once
#include <string>
#include "Vec3.h"

class Fonts_management{

private:

	GLuint uppercase[26];
	double uppercase_space_mult[26] = {
		0.88, //A
		0.88, //B
		0.88, //C
		0.88, //D
		0.82, //E
		0.76, //F
		0.88, //G
		0.88, //H
		0.4, //I
		0.45, //J
		0.88, //K
		0.62, //L
		1.28, //M
		0.88, //N
		0.88, //O
		0.88, //P
		0.88, //Q
		0.88, //R
		0.88, //S
		0.88, //T
		0.88, //U
		0.88, //V
		1.25, //W
		0.88, //X
		0.88, //Y
		0.88  //Z
		};

	GLuint lowercase[26];
	double lowercase_space_mult[26] = {
		0.88, //a
		0.88, //b
		0.88, //c
		0.88, //d
		0.82, //e
		0.76, //f
		0.88, //g
		0.88, //h 
		0.38, //i
		0.45, //j
		0.88, //k
		0.45, //l
		1.25, //m
		0.88, //n
		0.88, //o
		0.88, //p
		0.88, //q
		0.88, //r
		0.88, //s
		0.88, //t
		0.88, //u
		0.88, //v
		1.25, //w
		0.88, //x
		0.88, //y
		0.88  //z
		};


	GLuint numbers[10];
	double numbers_space_mult[10] = {
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88
	};

	GLuint special_symbols[40];
	double special_symbols_mult[40] = { 
		0.88,
		1.1,
		1.1,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		0.35,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		2.55,
		2.55,
		2.55,
		2.55,
		2.55,
		2.55,
		2.55,
		2.55,
		2.55,
		2.55,
		2.55,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
		0.88,
	};


	float T;
public:
	GLuint Turret_Circle;
	Fonts_management();
	void load_fonts();
	void Render_test();
	void drawtext(string text, vec3 start_pos, bool center, float scale);
	void drawtext_HUD(string text, vec3 start_pos, vec3 rotate, float scale);
};