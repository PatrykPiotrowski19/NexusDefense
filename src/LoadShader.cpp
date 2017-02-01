#include "LoadShader.h"
#include "stdafx.h"



GLuint Shading::LoadShader(const char * vertex_path, const char * fragment_path)
{
	GLuint vertShader = NULL;
	GLuint fragShader = NULL;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Read shaders
	std::string vertShaderStr = readFile(vertex_path);
	std::string fragShaderStr = readFile(fragment_path);
	const char *vertShaderSrc = vertShaderStr.c_str();
	const char *fragShaderSrc = fragShaderStr.c_str();
	GLint result = GL_FALSE;
	int logLength;

	// Compile vertex shader
	//std::cout << "Compiling vertex shader." << std::endl;
	glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
	glCompileShader(vertShader);

	// Check vertex shader
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
	std::cout << &vertShaderError[0] << std::endl;

	// Compile fragment shader
	//std::cout << "Compiling fragment shader." << std::endl;
	glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
	glCompileShader(fragShader);

	// Check fragment shader
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
	std::cout << &fragShaderError[0] << std::endl;

	//std::cout << "Linking program" << std::endl;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<char> programError((logLength > 1) ? logLength : 1);
	glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
	std::cout << &programError[0] << std::endl;

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return program;
}

string Shading::readFile(const char *filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

Shading::Shading()
{


}

void Shading::Enable_Shader()
{


	glUseProgram(shaders);

	glUniform3f(glGetUniformLocation(shaders, "lightPos"), 0.0, -5.0, 29.0);      //light position (is the same as the player position)

	glUniform3f(glGetUniformLocation(shaders, "mambient"), 0.6, 0.6, 0.6);      //setting the material property
	glUniform3f(glGetUniformLocation(shaders, "mdiffuse"), 0.55, 0.55, 0.55);
	glUniform3f(glGetUniformLocation(shaders, "mspecular"), 0.7, 0.7, 0.7);

	glUniform3f(glGetUniformLocation(shaders, "lambient"), 0.9, 0.9, 0.9);      //setting light property
	glUniform3f(glGetUniformLocation(shaders, "ldiffuse"), 0.6, 0.6, 0.6);
	glUniform3f(glGetUniformLocation(shaders, "lspecular"), 0.8, 0.8, 0.8);

	glUniform1f(glGetUniformLocation(shaders, "shininess"), 0.01);    //shininess
}

void Shading::SetCustomColor(vec3 color)
{
	glUseProgram(turrets_shading);
	glUniform4f(glGetUniformLocation(turrets_shading, "val"), color.x, color.y, color.z, 1.0);

}

void Shading::Enable_Turrets(int value)
{
	glUseProgram(turrets_shading);
	if(value == 0)
		glUniform4f(glGetUniformLocation(turrets_shading, "val"), 0.9,0,0,0.8);
	if(value == 1)
		glUniform4f(glGetUniformLocation(turrets_shading, "val"), 0.0, 0.9, 0, 0.8);
}

void Shading::Enable_SlowEffect()
{

	glUseProgram(slow_effect);
	glUniform4f(glGetUniformLocation(slow_effect, "val"), 0.45 + sin(glutGet(GLUT_ELAPSED_TIME)*0.01)*0.1, 0.69, 0.94, 1);

}

void Shading::Disable_Shader()
{
	glUseProgram(0);
}

void Shading::LoadShaders()
{
	shaders = LoadShader("Data/Shaders/phong.vert", "Data/Shaders/phong.frag");
	turrets_shading = LoadShader("Data/Shaders/turrets/turrets.vert", "Data/Shaders/turrets/turrets.frag");
	slow_effect = LoadShader("Data/Shaders/effects/slow.vert", "Data/Shaders/effects/slow.frag");
}

