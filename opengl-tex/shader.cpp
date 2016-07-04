#include "shader.h"

#include <fstream>
#include <iostream>
#include <streambuf>
#include <vector>
#include <stdexcept>

Shader::Shader(GLenum type) : shader_type(type) {
    shader_id = glCreateShader(shader_type);
}

Shader::Shader(GLenum type, const std::string &file) : shader_type(type) {
    shader_id = glCreateShader(shader_type);
    loadFromFile(file);
}

Shader::~Shader() {
    if (glIsShader(shader_id) == GL_TRUE)
        glDeleteShader(shader_id);
}

bool Shader::loadFromFile(const std::string &filename) {
    std::string shader_str;
    try {
        getFileContents(filename, shader_str);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return false;
    }

    const GLchar *source = shader_str.c_str();
    const GLint source_length = shader_str.length();

    glShaderSource(shader_id, 1, &source, &source_length);
    glCompileShader(shader_id);

    if (!isCompiled()) {        
        std::cerr << "Shader " << filename << " compilation error:\n" << getLog() << std::endl;
        return false;
    }
    return true;
}

bool Shader::isCompiled() {
    GLint is_compiled = 0;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &is_compiled);
    return (is_compiled == GL_TRUE);
}

void Shader::getFileContents(const std::string &filename, std::string &data) {
    std::ifstream f_in(filename.c_str());

    if (!f_in.is_open()) {
        throw std::runtime_error("Shader error: failed to open " + filename);
    }

    data.assign((std::istreambuf_iterator<char>(f_in)),
                std::istreambuf_iterator<char>());

    f_in.close();    
}

std::string Shader::getLog() {
    GLint max_length = 0;
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &max_length);
    GLint log_length;
    std::vector<GLchar> info_log(max_length);
    glGetShaderInfoLog(shader_id, max_length, &log_length, &info_log[0]);
    return std::string(&info_log[0], log_length);
}
