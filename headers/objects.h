#ifndef OBJECTS_H_INCLUDED
#define OBJECTS_H_INCLUDED

void renderCubes();
//void renderFrustumPyramid(float topRadius, float bottomRadius, float height);
void initFrustumPyramid(int vertexNumber, float vertices[], unsigned int indices[]);
void renderFrustumPyramids(int vertexNumber, int pyromidsNum, float pyromidsPos[][3], float opacityArr[], float vertices[], unsigned int indices[]);

#endif OBJECTS_H_INCLUDED