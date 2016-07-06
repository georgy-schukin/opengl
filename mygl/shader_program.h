#pragma once

#include "mygl.h"

#include <set>
#include <string>

namespace mygl {

class Shader;

class ShaderProgram {
public:
    ShaderProgram();
    ~ShaderProgram();

    GLuint getId() const {
        return program_id;
    }

    void attachShader(GLuint shader);    
    void attachShader(Shader *shader);
    void detachShader(GLuint shader);

    bool link();
    bool isLinked();

    void use();
    void unUse();

    void bindAttribLocation(const std::string &attrib, GLuint index);
    GLint getAttribLocation(const std::string &attrib);
    GLint getUniformLocation(const std::string &uniform);

protected:
    std::string getLog();

private:
    typedef std::set<GLuint> ShaderCollection;

    GLuint program_id;
    ShaderCollection shaders;
};

}
