#include "shader.h"

#include "debug.h"

#include <SDL_gpu.h>

void ShaderBuilder::loadAndAttach(GPU_ShaderEnum type, const char* path) {
	int id = GPU_LoadShader(type, path);
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
