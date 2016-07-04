#include "shader_program.h"
#include "shader.h"

#include <vector>
#include <string>
#include <iostream>

ShaderProgram::ShaderProgram() {
    program_id = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    for (ShaderCollection::iterator it = shaders.begin(); it != shaders.end(); it++) {
        glDetachShader(program_id, *it);
    }
    if (glIsProgram(program_id == GL_TRUE))
        glDeleteProgram(program_id);
}

void ShaderProgram::attachShader(GLuint shader) {
    glAttachShader(program_id, shader);
    shaders.insert(shader);
}

void ShaderProgram::attachShader(Shader *shader) {
    attachShader(shader->getId());
}

void ShaderProgram::detachShader(GLuint shader) {
    ShaderCollection::iterator it = shaders.find(shader);
    if (it != shaders.end()) {
        glDetachShader(program_id, shader);
        shaders.erase(it);
    }
}

bool ShaderProgram::link() {
    glLinkProgram(program_id);

    if (!isLinked()) {        
        std::cerr << "Shader program linking error:\n" << getLog() << std::endl;
        return false;
    }
    return true;
}

bool ShaderProgram::isLinked() {
    GLint is_linked = 0;
    glGetProgramiv(program_id, GL_LINK_STATUS, &is_linked);
    return (is_linked == GL_TRUE);
}

void ShaderProgram::use() {
    glUseProgram(program_id);
}

void ShaderProgram::unUse() {
    glUseProgram(0);
}

std::string ShaderProgram::getLog() {
    GLint max_length = 0;
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &max_length);
    GLint log_length = 0;
    std::vector<GLchar> info_log(max_length);
    glGetProgramInfoLog(program_id, max_length, &log_length, &info_log[0]);
    return std::string(&info_log[0], log_length);
}

void ShaderProgram::bindAttribLocation(const std::string &attrib, GLuint index) {
    glBindAttribLocation(program_id, index, attrib.c_str());
}

GLint ShaderProgram::getAttribLocation(const std::string &attrib) {
    return glGetAttribLocation(program_id, attrib.c_str());
}

GLint ShaderProgram::getUniformLocation(const std::string &uniform) {
    return glGetUniformLocation(program_id, uniform.c_str());
}


