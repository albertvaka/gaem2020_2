#include "shader.h"

#include "debug.h"

#include <SDL_gpu.h>

void ShaderBuilder::loadAndAttach(GPU_ShaderEnum type, const char* path) {
	
	const char* header = "";
	GPU_Renderer* renderer = GPU_GetCurrentRenderer();
	if (renderer->shader_language == GPU_LANGUAGE_GLSL)
	{
		if (renderer->max_shader_version >= 330)
			header = "#version 330\n";
		else
			header = "#version 130\n";
	}
	else if (renderer->shader_language == GPU_LANGUAGE_GLSLES)
	{
		if (type == GPU_FRAGMENT_SHADER)
		{
			header = "#version 100\n\
                     #ifdef GL_FRAGMENT_PRECISION_HIGH\n\
                     precision highp float;\n\
                     #else\n\
                     precision mediump float;\n\
                     #endif\n\
                     precision mediump int;\n";
		}
		else
			header = "#version 100\nprecision highp float;\nprecision mediump int;\n";
	}

	std::ifstream content_is(path);
	std::string content((std::istreambuf_iterator<char>(content_is)), std::istreambuf_iterator<char>());

	content = std::string(header) + content;

	int id = GPU_CompileShader(type, content.c_str());
	GPU_AttachShader(shader->program, id);
}

ShaderBuilder::ShaderBuilder(Shader* shader) : shader(shader) {
	shader->program = GPU_CreateShaderProgram();
}
ShaderBuilder::~ShaderBuilder() {
	GPU_LinkShaderProgram(shader->program);
	shader->block = GPU_LoadShaderBlock(shader->program, "gpu_Vertex", "gpu_TexCoord", "gpu_Color", "gpu_ModelViewProjectionMatrix");
}

ShaderBuilder& ShaderBuilder::withVertex(const char* path) {
	loadAndAttach(GPU_ShaderEnum::GPU_VERTEX_SHADER, path);
	return *this;
}

ShaderBuilder& ShaderBuilder::withGeometry(const char* path) {
	loadAndAttach(GPU_ShaderEnum::GPU_GEOMETRY_SHADER, path);
	return *this;
}

ShaderBuilder& ShaderBuilder::withFragment(const char* path) {
	loadAndAttach(GPU_ShaderEnum::GPU_FRAGMENT_SHADER, path);
	return *this;
}


int Shader::GetUniformLocation(const char* name) {
	std::map<std::string, int>::const_iterator it = uniforms.find(name);
	if (it != uniforms.end()) {
		return it->second;
	}
	else {
		int location = GPU_GetUniformLocation(program, name);
		uniforms.insert(std::make_pair(name, location));
		if (location == -1) {
			Debug::out << "Uniform \"" << name << "\" not found in shader";
		}

		return location;
	}
}
