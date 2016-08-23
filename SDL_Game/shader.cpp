#include "shader.h"
//#include <GL/gl.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include <string>
#include <streambuf>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <fstream>

//#include <GL/glx.h>



Shader::Shader(){

    path = NULL;
    //vID = 0;
    //fID = 0;
    pID = 0;
}

Shader::Shader(char* path){

    setPath(path);
    load();

}

Shader::~Shader(){}

void Shader::load(){

    if(path != NULL){
        loadShaderFiles();
    }

    //else return NULL;

}

void Shader::load(char* path){
    setPath(path);
    loadShaderFiles();

}

void Shader::setPath(char* path){


    this->path = (char*)malloc(strlen(path) + 1);
    strcpy(this->path, path);

}

char* Shader::getPath(){

    return path;

}

bool Shader::loadShaderFiles(){

    GLuint vShaderID = 0;

    GLuint fShaderID = 0;

    std::string vSourceString;

    std::string fSourceString;

    //VERTEX

    char* vsPath = (char*) malloc(strlen(path)+strlen(".vert")+1);

    if(vsPath == NULL){
        std::cerr << "loadShaderFiles(): CANNOT ALLOCATE MEMORY FOR VERTEX SHADER PATH";
    }else{
        strcpy(vsPath,path);
        strcat(vsPath,".vert");
    }

    //FRAGMENT

    char* fsPath = (char*) malloc(strlen(path)+strlen(".frag")+1);

    if(fsPath == NULL){
        std::cerr << "loadShaderFiles(): CANNOT ALLOCATE MEMORY FOR FRAGMENT SHADER PATH";
    }else{
        strcpy(fsPath,path);
        strcat(fsPath,".frag");
    }

    std::ifstream vFile(vsPath);
    std::ifstream fFile(fsPath);

    if(!vFile){
        std::cout << "No Shader at: " << vsPath;
    } else{

        free(fsPath);

        vSourceString.assign(std::istreambuf_iterator<char>(vFile),std::istreambuf_iterator<char>());

        vShaderID = glCreateShader(GL_VERTEX_SHADER);

        const GLchar* vSource = vSourceString.c_str();

        glShaderSource(vShaderID, 1, (const GLchar**)&vSource, NULL);

        glCompileShader(vShaderID);

        GLint shaderCompiled = GL_FALSE;
        glGetShaderiv(vShaderID, GL_COMPILE_STATUS, &shaderCompiled);
        if (shaderCompiled != GL_TRUE) {

            std::cerr << "CANNOT COMPILE VERTEX SHADER: \n" << vShaderID << vSourceString;
            printShaderLog(vShaderID);
            glDeleteShader(vShaderID);
            vShaderID = 0;
            return false;

        }

    }

    if(!fFile){
        std::cout << "No Shader at: " << fsPath;
    } else{

        free(vsPath);

        fSourceString.assign(std::istreambuf_iterator<char>(fFile),std::istreambuf_iterator<char>());

        fShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        const GLchar* fSource = fSourceString.c_str();

        glShaderSource(fShaderID, 1, (const GLchar**)&fSource, NULL);

        glCompileShader(fShaderID);

        GLint shaderCompiled = GL_FALSE;
        glGetShaderiv(fShaderID, GL_COMPILE_STATUS, &shaderCompiled);
        if (shaderCompiled != GL_TRUE) {

            std::cerr << "CANNOT COMPILE FRAGMENT SHADER: \n" << fShaderID << fSourceString;
            printShaderLog(fShaderID);
            glDeleteShader(fShaderID);
            fShaderID = 0;
            return false;

        }

    }

    if(!vFile && !fFile){

        std::cerr << "NO SHADERS FOUND CALLED " << path;
        return false;
    }

    if(vShaderID == 0 && fShaderID == 0){

        glDeleteShader(vShaderID);
        glDeleteShader(fShaderID);
        return false;

    }

    pID = glCreateProgram();

    if(vShaderID == 0){

        glDeleteShader(vShaderID);

    }else{

     glAttachShader(pID, vShaderID);

    }

    if(fShaderID == 0){

        glDeleteShader(fShaderID);

    }else{

        glAttachShader(pID, fShaderID);

    }

    glLinkProgram(pID);

    GLint success = GL_TRUE;

    glGetProgramiv(pID, GL_LINK_STATUS, &success);

    if(success != GL_TRUE){

        std::cerr << "ERROR LINKING PROGRAM" << pID;
        printProgramLog(pID);
        glDeleteShader(vShaderID);
        glDeleteShader(fShaderID);
        glDeleteProgram(pID);
        pID = 0;
        return false;
    }

    glDeleteShader(vShaderID);
    glDeleteShader(fShaderID);

    std::cout << "Loaded shader at location: " << path << std::endl;

    return true;

}

void Shader::printShaderLog(GLuint shader){

    if(glIsShader(shader)){

        int infoLength = 0;
        int maxLength = infoLength;

        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        char* infoLog = new char[maxLength];

        glGetShaderInfoLog(shader, maxLength, &infoLength, infoLog);

        if(infoLength > 0){

            std::cerr << "\n" << infoLog;

        }

        free(infoLog);

    }else{

        std::cerr << "CANNOT PRINT LOG! " << shader << ": IS NOT A SHADER!!!";

    }

}

void Shader::printProgramLog(GLuint program){

    if(glIsProgram(program)){

        int infoLength = 0;
        int maxLength = infoLength;

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        char* infoLog = new char[maxLength];

        glGetProgramInfoLog(program, maxLength, &infoLength, infoLog);

        if(infoLength > 0){

            std::cerr << "\n" << infoLog;

        }

        free(infoLog);

    }else{

        std::cerr << "CANNOT PRINT LOG! " << program << ": IS NOT A PROGRAM!!!";

    }

}

void Shader::bind(){

  glUseProgram(pID);
  //std::cout << "BOUND SHADER: " << pID;
}

void Shader::unbind(){

  glUseProgram(0);

}

GLuint Shader::getID(){

  return pID;

}
