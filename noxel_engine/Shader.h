#pragma once
#include <iostream>

enum SHADER_TYPE {
	VERTEX_SHADER,
	FRAGMENT_SHADER,
};

class Shader {

public:
	Shader(const std::string &vertex_file_path, const std::string &fragment_file_path);
	void bind() const;
	void unbind() const;
	void compile(unsigned int shader_obj_id, enum SHADER_TYPE shader_type);
	void link(unsigned int shader_program_id);
	unsigned int get_renderer_id() { return renderer_id; };
	~Shader();
private:
	unsigned int renderer_id;
};

