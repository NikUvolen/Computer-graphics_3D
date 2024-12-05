#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

typedef struct {
    float x, y
} Observer;

Observer* initObserver();
void cameraMove(Observer *observer);

#endif CAMERA_H_INCLUDED
