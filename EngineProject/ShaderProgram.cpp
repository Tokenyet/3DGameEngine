#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char *vertex_path, const char *fragment_path)
{
	this->vertexPath = vertex_path;
	this->fragPath = fragment_path;
	this->tcsPath = "";
	this->tesPath = "";
	this->geoPath = "";
	//this->program = LoadShader(vertex_path, fragment_path, nullptr, nullptr, nullptr);
}


ShaderProgram::ShaderProgram(const char *vertex_path, const char *fragment_path,
	const char *tcs_path = nullptr, const char *tes_path = nullptr, const char *geo_path = nullptr) 
{
	this->vertexPath = vertex_path;
	this->fragPath = fragment_path;
	if (tcs_path == nullptr)
		this->tcsPath = "";
	else
		this->tcsPath = tcs_path;
	if (tes_path == nullptr)
		this->tesPath = "";
	else
		this->tesPath = tes_path;
	if (geo_path == nullptr)
		this->geoPath = "";
	else
		this->geoPath = geo_path;
	//this->program = LoadShader(vertex_path, fragment_path, tcs_path, tes_path, geo_path);
}

void ShaderProgram::Init()
{
	//http://gamedev.stackexchange.com/questions/58095/does-glbindattriblocation-silently-ignore-names-not-found-in-a-shader
	this->program = LoadShader(this->vertexPath.c_str(), this->fragPath.c_str(),
		this->tcsPath == "" ? nullptr: this->tcsPath.c_str(),
		this->tesPath == "" ? nullptr: this->tesPath.c_str(),
		this->geoPath == "" ? nullptr: this->geoPath.c_str());
	ListAllAttributes(); //debug using 
	ListAllUniforms();
}


std::string ShaderProgram::ReadFile(const char *filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open()) {
		//std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		std::string output = std::string("Could not read file ") + filePath + ". File does not exist.";
		Debug::Log(output.c_str());
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


GLuint ShaderProgram::LoadShader(const char *vertex_path, const char *fragment_path,
	const char *tcs_path = nullptr, const char *tes_path = nullptr, const char *geo_path = nullptr) 
{
	// 準備頂點著色器  // 創造頂點著色器
	GLuint vertShader = CreateBasicShader(0, vertex_path);
	// 準備像素著色器  // 創造像素著色器
	GLuint fragShader = CreateBasicShader(1, fragment_path);
	GLuint tcsShader = -1, tesShader = -1, geoShader = -1;
	if(tcs_path != nullptr)
		tcsShader = CreateBasicShader(2, tcs_path);
	if (tes_path != nullptr)
		tesShader = CreateBasicShader(3, tes_path);
	if (geo_path != nullptr)
		geoShader = CreateBasicShader(4, geo_path);

	/*********************建立程式綁定著色器**********************/
	//std::cout << "Linking program" << std::endl;
	Debug::Log("Linking program");
	// 建立著色器程式 // 創造著色器程式
	//GLuint program = glCreateProgram();
	this->program = glCreateProgram();
	// 將需要的著色器載入到著色器程式中
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	tcsShader == -1 ? tcsShader = -1: glAttachShader(program, tcsShader);
	tesShader == -1 ? tesShader = -1 : glAttachShader(program, tesShader);
	geoShader == -1 ? geoShader = -1 : glAttachShader(program, geoShader);
	// Bind Attributes
	BindAttributes();
	// 載入完後連結到著色器
	glLinkProgram(program);
	GLuint tester1 = glGetAttribLocation(program, "boneID");
	GLuint tester2 = glGetAttribLocation(program, "boneWeight");
	// 確認著色器程式是否成功連結
	DebugProgram(program);

	// 刪除不用的著色器
	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return program;
}

// 0 vertex 1 fragment 2 tcs 3 tes 4 gs
GLuint ShaderProgram::CreateBasicShader(int shaderCmd, const char * path)
{
	// 準備著色器  // 創造著色器
	GLuint shader;
	if (shaderCmd == 0)
		shader = glCreateShader(GL_VERTEX_SHADER);
	else if (shaderCmd == 1)
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	else if (shaderCmd == 2)
		shader = glCreateShader(GL_TESS_CONTROL_SHADER);
	else if (shaderCmd == 3)
		shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
	else if(shaderCmd == 4)
		shader = glCreateShader(GL_GEOMETRY_SHADER);
	// Read shaders
	std::string shaderStr = ReadFile(path);
	const char *shaderSrc = shaderStr.c_str();
	return CompileShader(shaderCmd, shader, shaderSrc);
}

GLuint ShaderProgram::CompileShader(int shaderCmd, GLuint shader, const char* shaderSrc)
{
	if (shaderCmd == 0)
		Debug::Log("Compiling vertex shader.");
		//std::cout << "Compiling vertex shader." << std::endl;
	else if (shaderCmd == 1)
		Debug::Log("Compiling fragment shader.");
		//std::cout << "Compiling fragment shader." << std::endl;
	else if (shaderCmd == 2)
		Debug::Log("Compiling tcs shader.");
		//std::cout << "Compiling tcs shader." << std::endl;
	else if (shaderCmd == 3)
		Debug::Log("Compiling tes shader.");
		//std::cout << "Compiling tes shader." << std::endl;
	else if (shaderCmd == 4)
		Debug::Log("Compiling geometry shader.");
		//std::cout << "Compiling geometry shader." << std::endl;
	// 將著色器的原始碼(們)綁定到著色器中
	glShaderSource(shader, 1, &shaderSrc, NULL);
	// 編譯著色器
	glCompileShader(shader);

	// Check vertex shader
	//確認著色器是否綁定成功
	DebugShader(shader);
	return shader;
}

void ShaderProgram::DebugShader(GLuint shader)
{
	GLint result = GL_FALSE;
	int logLength;
	// Check vertex shader
	//確認著色器是否綁定成功
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
	std::vector<GLchar> shaderError((logLength > 1) ? logLength : 1);
	glGetShaderInfoLog(shader, logLength, NULL, &shaderError[0]);
	//std::cout << &shaderError[0] << std::endl;
	Debug::Log(&shaderError[0]);
}

void ShaderProgram::DebugProgram(GLuint program)
{
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		Debug::Log(&infoLog[0]);

		//The program is useless now. So delete it.
		glDeleteProgram(program);

		//Provide the infolog in whatever manner you deem best.
		//Exit with failure.
		return;
	}
}

void ShaderProgram::ListAllUniforms()
{
	GLint i;
	GLint count;

	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)

	const GLsizei bufSize = 16; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length; // name length
	glGetProgramiv(this->GetProgram(), GL_ACTIVE_UNIFORMS, &count);
	std::string s = "Active Uniforms: " + std::to_string(count);
	Debug::Log(s);

	for (i = 0; i < count; i++)
	{
		glGetActiveUniform(this->GetProgram(), (GLuint)i, bufSize, &length, &size, &type, name);
		std::string st = "Uniform #" + std::to_string(i) + " Type :" + std::to_string(type) + "Name : " + name;
		Debug::Log(st);
	}
}

void ShaderProgram::ListAllAttributes()
{
	GLint i;
	GLint count;

	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)

	const GLsizei bufSize = 16; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length; // name length
	glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &count);
	std::string s = "Active Attributes: " + std::to_string(count);
	Debug::Log(s);

	for (i = 0; i < count; i++)
	{
		glGetActiveAttrib(program, (GLuint)i, bufSize, &length, &size, &type, name);
		std::string st = "Attribute #" + std::to_string(i) + " Type :" + std::to_string(type) + "Name : " + name;
		Debug::Log(st);
	}
}

void ShaderProgram::BindAttribute(int attributeLoc, const char* attributeName)
{
	glBindAttribLocation(this->GetProgram(), attributeLoc, attributeName);
}