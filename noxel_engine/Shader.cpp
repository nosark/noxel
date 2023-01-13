#include "Shader.h"
#include "FileOps.h"
#include "Renderer.h"

Shader::Shader(const std::string& vertex_shader_file, const std::string& fragment_shader_file) {
	std::string vertex_shader_src, fragment_shader_src;
	const char* vert_shader_source, * frag_shader_source;

	FileOps::load_shader(vertex_shader_file, vertex_shader_src);
	FileOps::load_shader(fragment_shader_file, fragment_shader_src);

	vert_shader_source = vertex_shader_src.c_str();
	frag_shader_source = fragment_shader_src.c_str();

	// create shader object w/ ids
	unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

	//set the source code of shader objs
	glShaderSource(vertex_shader, 1, &vert_shader_source, nullptr);
	glShaderSource(fragment_shader, 1, &frag_shader_source, nullptr);

	compile(vertex_shader, VERTEX_SHADER);
	compile(fragment_shader, FRAGMENT_SHADER);

	renderer_id = glCreateProgram();
	glAttachShader(renderer_id, vertex_shader);
	glAttachShader(renderer_id, fragment_shader);

	link(renderer_id);

	//delete shaders
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

void Shader::compile(unsigned int shader_obj_id, enum SHADER_TYPE shader_type) {
	//TODO: add shader type enum
	std::string shader_str_type = (shader_type == VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
	glCompileShader(shader_obj_id);
	int  success;
	char infoLog[512];
	glGetShaderiv(shader_obj_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader_obj_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shader_str_type<< "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

void Shader::link(unsigned int shader_program_id) {
	glLinkProgram(shader_program_id);
	int  success;
	char infoLog[512];
	//check shader program link success
	glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKAGE\n" << infoLog << std::endl;
	}
}

void Shader::bind() const {
	glUseProgram(renderer_id);
}

void Shader::unbind() const {
	glUseProgram(0);
}

Shader::~Shader() {
	glDeleteProgram(renderer_id);
}