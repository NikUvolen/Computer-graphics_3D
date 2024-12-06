#include <gl/gl.h>

#include "../headers/objects.h"

#define _USE_MATH_DEFINES
#include <math.h>

void _initCube(){
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0,
        1, 5, 6,
        6, 2, 1,
        7, 6, 5,
        5, 4, 7,
        4, 0, 3,
        3, 7, 4,
        4, 5, 1,
        1, 0, 4,
        3, 2, 6,
        6, 7, 3
    };

    GLfloat normals[] = {
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
         0.0f,  0.0f,  1.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
        -1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f, -1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
         0.0f,  1.0f,  0.0f
    };

    glColor3f(1, 0.65, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glEnableClientState(GL_NORMAL_ARRAY);
            glNormalPointer(GL_FLOAT, 0, normals);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, indices);
        glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
}

void renderCubes() {
    #define numberOfCubes 3
    float cubesPos[numberOfCubes][3] = {
        {0, -6, .5},
        {0, 0, .5},
        {-1, -1, .5},
    };
    float scale[numberOfCubes] = {1, 2, 3};

    for (int i = 0; i < numberOfCubes; i++) {
        glPushMatrix();
            glScalef(scale[i], scale[i], scale[i]);
            glTranslatef(cubesPos[i][0], cubesPos[i][1], cubesPos[i][2]);
            _initCube();
        glPopMatrix();
    }
}

void initFrustumPyramid(int vertexNumber, float vertices[], unsigned int indices[]) {
    float topRadius = 0.5f, bottomRadius = 1.0f;
    float angle = 2 * M_PI / vertexNumber;

    // Создание вершин для нижнего основания
    for (int vert = 0; vert < vertexNumber; vert++) {
        vertices[vert * 3] = cos(angle * vert) * bottomRadius;
        vertices[vert * 3 + 1] = sin(angle * vert) * bottomRadius;
        vertices[vert * 3 + 2] = 0; // Z = 0 для нижнего основания
    }

    // Создание вершин для верхнего основания
    for (int vert = vertexNumber; vert < vertexNumber * 2; vert++) {
        vertices[vert * 3] = cos(angle * vert) * topRadius;
        vertices[vert * 3 + 1] = sin(angle * vert) * topRadius;
        vertices[vert * 3 + 2] = 1; // Z = 1 для верхнего основания
    }

    // Центры оснований
    for (int i = 0; i < 5; i++)
        vertices[vertexNumber * 2 * 3 + i] = 0; 
    vertices[vertexNumber * 2 * 3 + 5] = 1; // Верхний центр

    // Создание индексов для боковых граней
    for (int side = 0; side < vertexNumber; side++) {
        indices[6 * side] = side;                           // Нижнее основание
        indices[6 * side + 1] = side + 1;                   // Нижнее основание
        indices[6 * side + 2] = vertexNumber + side;        // Верхнее основание

        indices[6 * side + 3] = side + 1;                   // Нижнее основание
        indices[6 * side + 4] = vertexNumber + side;        // Верхнее основание
        indices[6 * side + 5] = vertexNumber + side + 1;    // Верхнее основание

        if (side + 1 == vertexNumber) {
            indices[6 * side + 1] = 0;
            indices[6 * side + 5] = 0;
        }

        // Индексы для торцов
        indices[6 * side + vertexNumber * 6] = side;
        indices[6 * side + 1 + vertexNumber * 6] = side + 1;
        indices[6 * side + 2 + vertexNumber * 6] = vertexNumber * 2; // Центр нижнего

        indices[6 * side + 3 + vertexNumber * 6] = side + vertexNumber;
        indices[6 * side + 4 + vertexNumber * 6] = side + vertexNumber + 1;
        indices[6 * side + 5 + vertexNumber * 6] = vertexNumber * 2 + 1; // Центр верхнего

        if (side + 1 == vertexNumber) {
            indices[6 * side + 1 + vertexNumber * 6] = 0;
            indices[6 * side + 4 + vertexNumber * 6] = vertexNumber;
        }
    }
}

void renderFrustumPyramids(int vertexNumber, int pyromidsNum, float pyromidsPos[][3], float opacityArr[], float vertices[], unsigned int indices[]) {
    for (int i = 0; i < pyromidsNum; i++) {
        glPushMatrix();
            glScalef(2, 2, 2);
            glTranslatef(pyromidsPos[i][0], pyromidsPos[i][1], pyromidsPos[i][2]);
            glColor4f(1.0f, 0.65f, 0.0f, opacityArr[i]);

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_NORMAL_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, vertices);
            glNormalPointer(GL_FLOAT, 0, vertices);
            glDrawElements(GL_TRIANGLES, vertexNumber * 3 * sizeof(unsigned int), GL_UNSIGNED_INT, indices);
            glDisableClientState(GL_NORMAL_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);
        glPopMatrix();
    }
}
