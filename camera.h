#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
#include <mat4.h>
void sendMatricesToOpenGL(const unsigned int shaderProgramId);

void setModelMatrix(mat4 modelMatrix);
void setViewMatrix(mat4 viewMatrix);
void setProjectionMatrix(mat4 projectionMatrix);


#endif // 3D_H_INCLUDED
