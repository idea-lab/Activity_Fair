#ifndef MESH_H
#define MESH_H


#include <GL/glew.h>



class Mesh {

public:

    Mesh();
    Mesh(float vertPositions[], int numElements);
    ~Mesh();
    void setVerts(float vertPositions[], int numElements);
    void draw();

private:

    GLuint vboID;
    int vertAmount;
};

#endif
