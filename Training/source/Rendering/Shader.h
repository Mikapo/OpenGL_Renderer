#pragma once

#include <array>
#include <glm/matrix.hpp>
#include <string>
#include <unordered_map>

#include "Renderer.h"

class Shader
{
public:

	Shader(const std::string& frag_path, const std::string& fert_path);
    ~Shader();

	void bind() const;
    void unbind() const;
    void set_uniform4f(const std::string& name, float v1, float v2, float v3, float v4);
    void set_uniform4fv(const std::string& name, size_t count, float* v);
    void set_uniform3f(const std::string& name, float v1, float v2, float v3);
    void set_uniform3fv(const std::string& name, size_t count, float* v);
    void set_uniform2f(const std::string& name, float v1, float v2);
    void set_uniform1f(const std::string& name, float v1);
    void set_uniform1i(const std::string& name, int v1);
    void set_uniform_mat4f(const std::string& name, const glm::mat4& matrix);

private:

    struct shader_source
    {
        std::string vertex_source;
        std::string fragment_source;
    };

    unsigned int create_shader(const std::string& vertex_shader, const std::string& fragment_shader);
    unsigned int compile_shader(unsigned int type, const std::string& source);
    std::string parse_shader(const std::string& filepath);
    int get_uniform_location(const std::string& name);

    std::string m_frag_path;
    std::string m_fert_path;
    unsigned int m_shader_id;
    std::unordered_map<std::string, int> m_uniform_location_cache;

};
