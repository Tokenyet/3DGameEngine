#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>
#include <iostream>
#include <fstream>
#include "Core.h"

class ShaderProgram
{
public:
	ShaderProgram(const char *vertex_path, const char *fragment_path);
	ShaderProgram(const char *vertex_path, const char *fragment_path, const char *tcs_path, const char *tes_path, const char *geo_pathr);
	void Init();
	void StartProgram() { glUseProgram(program); }
	void StopProgram() { glUseProgram(0); }
	void DeleteProgram() { glDeleteProgram(program); }
	GLuint GetProgram() { return program; }
protected:
	// Dont use this in constructor, because pure virtual function problem,
	// Must use this before vertex shader bounded to the specified program.
	virtual void BindAttributes() = 0;
	void BindAttribute(int attributeLoc, const char* attributeName);
private:
	std::string vertexPath, fragPath, tcsPath, tesPath, geoPath;
	std::string ReadFile(const char *filePath);
	GLuint LoadShader(const char *vertex_path, const char *fragment_path, const char *tcs_path, const char *tes_path, const char *geo_pathr);
	GLuint CreateBasicShader(int shaderCmd, const char * path);
	GLuint CompileShader(int shaderCmd, GLuint shader, const char* Source);
	void DebugShader(GLuint shader);
	void DebugProgram(GLuint program);
	void ListAllUniforms();
	void ListAllAttributes();
	GLuint program;
};

#endif