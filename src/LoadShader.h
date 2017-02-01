#pragma once

#include "stdafx.h"
class vec3;

class Shading {

public:
	GLuint shaders;
	GLuint turrets_shading;
	GLuint FramebufferName;
	GLuint slow_effect;

	GLuint LoadShader(const char *vertex_path, const char *fragment_path);
	string readFile(const char *filePath);
	Shading();
	void Enable_Shader();
	void SetCustomColor(vec3);
	void Enable_Turrets(int value);

	void Enable_SlowEffect();
	void Disable_Shader();
	void LoadShaders();


};