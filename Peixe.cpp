#include "Peixe.h"
#include <GL/glut.h>
#include <cstdlib>

Peixe::Peixe() {
    const float ICE_SHEET_SIZE = 40.0f;
    x = (rand() % (int)(ICE_SHEET_SIZE - 4)) - (ICE_SHEET_SIZE / 2.0f - 2);
    y = 0.25f;
    z = (rand() % (int)(ICE_SHEET_SIZE - 4)) - (ICE_SHEET_SIZE / 2.0f - 2);
}

void Peixe::desenha() const {
    glPushMatrix();
    glTranslatef(x, y, z);
    desenhaModelo();
    glPopMatrix();
}

void Peixe::desenhaModelo() {
    glPushMatrix();
    glColor3f(0.3f, 0.5f, 0.9f);
    glPushMatrix();
    glScalef(2.0f, 0.7f, 1.0f);
    glutSolidSphere(0.5, 15, 15);
    glPopMatrix();
    
    glColor3f(0.2f, 0.4f, 0.8f);
    glPushMatrix();
    glTranslatef(-1.0f, 0.0f, 0.0f);
    glRotatef(90, 0, 1, 0);
    glScalef(1.0f, 2.0f, 1.0f);
    glutSolidCone(0.3, 0.5, 10, 2);
    glPopMatrix();
    glPopMatrix();
}
