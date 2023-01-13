#pragma once
#include <iostream>
class Shader {
public:
	Shader(const std::string &vertex_file_path, const std::string &fragment_file_path);
	void bind();
	void unbind();
	void compile();
	unsigned int get_renderer_id() { return renderer_id; };

private:
	unsigned int renderer_id;
};

