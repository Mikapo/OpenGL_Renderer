#include "World.h"

#include <glm/ext/matrix_clip_space.hpp>

#include "Rendering/Shader_compiler.h"
#include "Rendering/Shader.h"
#include "Utility/Uniform_names.h"


void World::init()
{
    m_shadow_map.init(1500, 1500);
}

void World::update(float deltatime)
{
    m_camera->update(deltatime);
}

void World::render() const
{
    update_matrices();
    update_lighting();
    render_shadow_map();

    for (auto object : m_mesh_objects)
        object->render();
}

void World::render_shadow_map() const
{
    int shadow_width, shadow_height;
    m_shadow_map.get_shadow_resolution(shadow_width, shadow_height);

    m_shadow_map.bind_frame_buffer();
    glViewport(0, 0, shadow_width, shadow_height);
    glCullFace(GL_FRONT);
    glClear(GL_DEPTH_BUFFER_BIT);

    for (auto object : m_mesh_objects)
        object->render_to_shadow_map(&m_shadow_map);

    glCullFace(GL_BACK);
    m_shadow_map.unbind_frame_buffer();
    glViewport(0, 0, 1000, 1000);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shadow_map.bind_texture(Texture_slot::shadow_map);
}

void World::update_lighting() const
{
    auto light = m_lights[0];

    if (light)
    {
        auto shaders = Shader_compiler::get_current_shaders();
        for (auto shader_pair : shaders)
        {
            auto shader = shader_pair.second.lock();
            shader->set_uniform4f(LIGHT_COLOR_UNIFORM_NAME, light->get_color().r, light->get_color().g, light->get_color().b, light->get_color().a);

            glm::vec3 location = light->get_location();
            shader->set_uniform3f(LIGHT_LOCATION_UNIFORM_NAME, location.x, location.y, location.z);

            location = m_camera->get_location();
            shader->set_uniform3f(EYE_LOCATION_UNIFORM_NAME, location.x, location.y, location.z);

            float near_plane = 1.0f, far_plane = 1000.0f;
            glm::mat4 light_view = glm::lookAt(light->get_location(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 light_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
            glm::mat4 light_space_matrix = light_projection * light_view;
            shader->set_uniform_mat4f(LIGHT_SPACE_MATRIX_UNIFORM_NAME, light_space_matrix);

            shader->set_uniform1i(AMBIENT_ENABLED_UNIFORM_NAME, m_shader_settings.ambient);
            shader->set_uniform1i(DIFFUSE_ENABLED_UNIFORM_NAME, m_shader_settings.diffuse);
            shader->set_uniform1i(SPECULAR_ENABLED_UNIFORM_NAME, m_shader_settings.specular);
            shader->set_uniform1i(SHADOW_ENABLED_UNIFORM_NAME, m_shader_settings.shadow);
            shader->set_uniform1i(TEXTURE_ENABLED_UNIFORM_NAME, m_shader_settings.texture);

            if (m_shader_settings.anti_alias)
                glEnable(GL_MULTISAMPLE);
            else
                glDisable(GL_MULTISAMPLE);
        }
    }
}

void World::update_matrices() const
{
    auto shaders = Shader_compiler::get_current_shaders();
    for (auto shader_pair : shaders)
    {
        auto shader = shader_pair.second.lock();
        glm::mat4 view = get_camera_view_matrix();
        glm::mat4 projection = get_camera_projection_matrix();

        shader->set_uniform_mat4f(VIEW_UNIFORM_NAME, view);
        shader->set_uniform_mat4f(PROJECTION_UNIFORM_NAME, projection);
    }
}

glm::mat4 World::get_camera_view_matrix() const
{
    if (m_camera)
        return m_camera->get_view_matrix();
    else
        return glm::mat4(1);
}

glm::mat4 World::get_camera_projection_matrix() const
{
    if (m_camera)
        return m_camera->get_projection_matrix();
    else
        return glm::mat4(1);
}

std::shared_ptr<Camera> World::spawn_camera(Transform transform)
{
    this->m_camera.reset(new Camera(this, transform));
    return this->m_camera;
}

std::shared_ptr<Mesh_object> World::spawn_mesh_object(Transform transform)
{
    m_mesh_objects.emplace_back(new Mesh_object(this));
    m_mesh_objects.back()->set_transform(transform);
    return m_mesh_objects.back();
}

std::shared_ptr<Light> World::spawn_light(Transform transform)
{
    m_lights.emplace_back(new Light(this));
    m_lights.back()->set_transform(transform);
    return m_lights.back();
}
