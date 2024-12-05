#include <windows.h>
#include <gl/GL.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "../headers/camera.h"

float xAlpha = 20;
float zAlpha = 0; 

struct Observer {
    float x, y;
} observer;

void _moveDirectional(short vertical, short horizontal) {
    if (vertical == 1) xAlpha = ++xAlpha > 180 ? 180 : xAlpha;
    if (vertical == -1) xAlpha = --xAlpha < 0 ? 0 : xAlpha;

    if (horizontal == 1) ++zAlpha;
    if (horizontal == -1) --zAlpha;
}

void _moving(Observer* observer, short vertical, short horizontal) {
    float angle = -zAlpha / 180 * M_PI;
    float speed = 0;

    if (vertical == 1) speed = 0.1;
    if (vertical == -1) speed = -0.1;

    if (horizontal == 1) { speed = 0.1; angle -= M_PI*.5; }
    if (horizontal == -1) { speed = 0.1; angle += M_PI*.5; }

    if (speed != 0) {
        observer->x += sin(angle) * speed;
        observer->y += cos(angle) * speed;
    }
}

Observer* initObserver() {
    Observer* observer = malloc(sizeof(Observer));

    observer->x = 0;
    observer->y = 0;
}

void cameraMove(Observer *observer) {
    _moveDirectional(
        GetKeyState(VK_UP) < 0 ? 1 : GetKeyState(VK_DOWN) < 0 ? -1 : 0,
        GetKeyState(VK_LEFT) < 0 ? 1 : GetKeyState(VK_RIGHT) < 0 ? -1 : 0
    );
    _moving(observer, 
        GetKeyState('W') < 0 ? 1 : GetKeyState('S') < 0 ? -1 : 0,
        GetKeyState('A') < 0 ? 1 : GetKeyState('D') < 0 ? -1 : 0
    );

    glRotatef(-xAlpha, 1, 0, 0);
    glRotatef(-zAlpha, 0, 0, 1);
    glTranslatef(-observer->x, -observer->y, -3);
}