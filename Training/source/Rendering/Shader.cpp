#include "Shader.h"
#include "Renderer.h"

#include <fstream>
#include <iostream>
#include <sstream>

Shader::Shader(const std::string& frag_path, const std::string& fert_path)
    : m_frag_path(frag_path), m_fert_path(fert_path), m_shader_id(0)
{
    std::string frag_source = parse_shader(frag_path);
    std::string fert_source = parse_shader(fert_path);

    m_shader_id = create_shader(fert_source, frag_source);
    glUseProgram(m_shader_id);
}

Shader::~Shader() { glDeleteProgram(m_shader_id); }

void Shader::bind() const { glUseProgram(m_shader_id); }

void Shader::unbind() const { glUseProgram(0); }

void Shader::set_uniform4f(const std::string& name, float v1, float v2, float v3, float v4) const
{
    int location = get_uniform_location(name);
    glUniform4f(location, v1, v2, v3, v4);
}

void Shader::set_uniform2f(const std::string& name, float v1, float v2) const 
{
    int location = get_uniform_location(name);
    glUniform2f(location, v1, v2);
}

void Shader::set_uniform1i(const std::string& name, int v1) const
{
    int location = get_uniform_location(name);
    glUniform1i(location, v1);
}

void Shader::set_uniform_mat4f(const std::string& name, const glm::mat4& matrix) const
{
    int location = get_uniform_location(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

int Shader::get_uniform_location(const std::string& name) const
{
    /* if (m_uniform_location_cache.find(name) != m_uniform_location_cache.end())
        return m_uniform_location_cache[name];*/

    int location = glGetUniformLocation(m_shader_id, name.c_str());
    if (location == -1)
    {
        std::cout << " warning: uniform " << name << " does not exist ";
        return -1;
    }
    else
    {
        // m_uniform_location_cache[name] = location;
        return location;
    }
}

unsigned int Shader::compile_shader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* message = static_cast<char*>(alloca(sizeof(char) * lenght));
        glGetShaderInfoLog(id, lenght, &lenght, message);
        std::cout << "failed to compile shader!" << std::endl;
        std::cout << message;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int Shader::create_shader(const std::string& vertex_shader, const std::string& fragment_shader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
    unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

std::string Shader::parse_shader(const std::string& filepath)
{

    std::ifstream stream(filepath);
    std::stringstream ss[1];
    std::string line;

    while (getline(stream, line))
    {
        ss[0] << line << '\n';
    }
    return ss[0].str();
}