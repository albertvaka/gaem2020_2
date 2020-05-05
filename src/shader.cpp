#include "shader.h"

#include "debug.h"

#include <SDL_gpu.h>

void Shader::loadAndAttach(GPU_ShaderEnum type, const char* path) {
	int id = GPU_LoadShader(type, path);
	GPU_AttachShader(program, id);
}

void Shader::Load(const char* vertex_path, const char* geometry_path, const char* fragment_path) {
	program = GPU_CreateShaderProgram();
	loadAndAttach(GPU_ShaderEnum::GPU_VERTEX_SHADER, vertex_path);
	loadAndAttach(GPU_ShaderEnum::GPU_GEOMETRY_SHADER, geometry_path);
	loadAndAttach(GPU_ShaderEnum::GPU_FRAGMENT_SHADER, fragment_path);
	GPU_LinkShaderProgram(program);
	block = GPU_LoadShaderBlock(program, "gpu_Vertex", "gpu_TexCoord", "gpu_Color", "gpu_ModelViewProjectionMatrix");
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
