#ifndef SHADER_H
#define SHADER_H


#include <GL/glew.h>



class Shader {

public:

    Shader();

    Shader(char* path);

    Shader(char* vPath, char* fPath);

    ~Shader();

    void load();

    void load(char* path);

    void setPath(char* path);

    void setPath(char* vPath, char* fPath);

    char* getPath();

    void bind();

    void unbind();

    GLuint getID();

private:


    //char* vSrc;
    //char* fSrc;
    char* path;

    //GLuint vID;
    //GLuint fID;

    GLuint pID;

    bool loadShaderFiles();
    void printShaderLog(GLuint shader);
    void printProgramLog(GLuint program);
};

#endif
