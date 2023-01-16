#include "Shader.h"
#include "FileOps.h"
#include "Renderer.h"

/// <summary>
/// Creates a Shader Program w/ an ID.
/// </summary>
/// <param name="vertex_shader_file">: vertex shader file we are using to create the program</param>
/// <param name="fragment_shader_file">: fragment shader file we are using to create the program</param>
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

	m_renderer_id = glCreateProgram();
	glAttachShader(m_renderer_id, vertex_shader);
	glAttachShader(m_renderer_id, fragment_shader);

	link(m_renderer_id);

	//delete shaders
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
}

/// <summary>
/// Compiles a shader, and outputs any errors in the process
/// </summary>
/// <param name="shader_obj_id">: The shader object being compiled. </param>
/// <param name="shader_type">: The type of shader that is being compiled. </param>
void Shader::compile(unsigned int shader_obj_id, enum SHADER_TYPE shader_type) {
	std::string shader_str_type = (shader_type == VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
	glCompileShader(shader_obj_id);
	int  success;
	char infoLog[512];
	glGetShaderiv(shader_obj_id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader_obj_id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << shader_str_type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

/// <summary>
/// Links a shader program to the program object and creates a handle for the shader object.
/// </summary>
/// <param name="shader_program_id">: handle to use this specific shader program</param>
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

/// <summary>
/// Binds shader program object to "program" as part of the current rendering state.
/// We track this object with a renderer_id
/// </summary>
void Shader::bind() const {
	glUseProgram(m_renderer_id);
}

/// <summary>
/// Unbinds shader program from the program object in the current rendering state.
/// </summary>
void Shader::unbind() const {
	glUseProgram(0);
}

/// <summary>
/// Deletes our shader program object and frees memory previously consumed by it.
/// renders the renderer_id handle obselete.
/// </summary>
Shader::~Shader() {
	glDeleteProgram(m_renderer_id);
}