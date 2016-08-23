#include <iostream>
#include "mesh.h"

Mesh::Mesh(){

    //glGenBuffers(1, &vboID);

}

Mesh::Mesh(GLfloat vertPositions[], int numElements){

    //glGenBuffers(1, &vboID);
    //setVerts(vertPositions, numElements);

}

Mesh::~Mesh(){}

void Mesh::setVerts(GLfloat vertPositions[], int numElements){

    glGenBuffers(1, &vboID);
    
    //std::cout << "GLFLOAT SIZE "<<sizeof(GLfloat) << std::endl;
    //std::cout << "POSITIONS SIZE "<<size << std::endl; 
    
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

   // glBufferData(GL_ARRAY_BUFFER, 2*((float) izeof(vertPositions)/5.0f)*sizeof(vertPositions)*sizeof(GLfloat), vertPositions, GL_STATIC_DRAW);

   glBufferData(GL_ARRAY_BUFFER, numElements*sizeof(GLfloat), vertPositions, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    vertAmount = numElements /5;
    std::cout << vertAmount << " <- VAMT" << std::endl;
}

void Mesh::draw(){

  //glBegin(GL_TRIANGLES);
//
   // std::cout << vboID << std::endl;
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 5*4, 0);
  glVertexAttribPointer(1,2, GL_FLOAT, GL_FALSE, 5*4, (const GLvoid*)12);

  glEnableClientState(GL_VERTEX_ARRAY);

  glDrawArrays(GL_TRIANGLES, 0, vertAmount);

  glDisableClientState(GL_VERTEX_ARRAY);

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);

  //std::cout << " DRAWING VBO: " << vboID;

  //glEnd();
  //glFlush();
  //glEnd();
}
