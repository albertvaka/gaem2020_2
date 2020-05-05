#pragma once

#include <map>
#include <string>

#include "vector.h"
#include "debug.h"
#include "SDL_gpu.h"

struct Shader;

struct ShaderBuilder {
	ShaderBuilder(Shader*);
	ShaderBuilder(ShaderBuilder&& o) noexcept : shader(o.shader) { }
	~ShaderBuilder();
	ShaderBuilder& withVertex(const char* path);
	ShaderBuilder& withGeometry(const char* path);
	ShaderBuilder& withFragment(const char* path);
private:
	void loadAndAttach(GPU_ShaderEnum type, const char* path);
	Shader* shader;
};

struct Shader {
	ShaderBuilder Build() { return ShaderBuilder(this); }

	Shader& SetUniform(int location, int v) {
		assertActive();
		GPU_SetUniformi(location, v);
		return *this;
	}

	Shader& SetUniform(int location, float v) {
		assertActive();
		GPU_SetUniformf(location, v);
		return *this;
	}

	Shader& SetUniform(int location, float x, float y) {
		assertActive();
		float v[] = { x,y };
		GPU_SetUniformfv(location, 2, 1, v);
		return *this;
	}

	Shader& SetUniform(int location, float r, float g, float b, float a) {
		assertActive();
		float v[] = { r,g,b,a };
		GPU_SetUniformfv(location, 4, 1, v);
		return *this;
	}

	Shader& SetUniform(int location, vec v) { return SetUniform(location, v.x, v.y); }

	Shader& SetUniform(const char* name, int v) { return SetUniform(GetUniformLocation(name), v); }
	Shader& SetUniform(const char* name, float v) { return SetUniform(GetUniformLocation(name), v); }
	Shader& SetUniform(const char* name, float x, float y) { return SetUniform(GetUniformLocation(name), x, y); }
	Shader& SetUniform(const char* name, vec v) { return SetUniform(GetUniformLocation(name), v); }
	Shader& SetUniform(const char* name, float r, float g, float b, float a) { return SetUniform(GetUniformLocation(name), r, g, b, a); }

	void Activate() { 
		if (GPU_GetCurrentShaderProgram() != program) {
			GPU_ActivateShaderProgram(program, &block);
		}
	}
	void Deactivate() { GPU_DeactivateShaderProgram(); }

	int GetUniformLocation(const char* name);

    int program;
	GPU_ShaderBlock block;

private:
	std::map<std::string, int> uniforms;

	void assertActive() {
		if (GPU_GetCurrentShaderProgram() != program) {
			Debug::out << "Can't set uniform on inactive shader";
		}
	}
};
