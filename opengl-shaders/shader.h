#pragma once

#include "mygl.h"
#include <string>

class Shader {
public:    
    Shader(GLenum type);
    Shader(GLenum type, const std::string &file);
    ~Shader();

    GLenum getType () const {
        return shader_type;
    }

    GLuint getId() const {
        return shader_id;
    }

    bool loadFromFile(const std::string &filename);
    bool isCompiled();    

protected:
    void getFileContents(const std::string &filename, std::string &data);
    std::string getLog();

private:
    GLenum shader_type;
    GLuint shader_id;
};
