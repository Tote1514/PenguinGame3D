#include "Buraco.h"
#include <cstdlib>
#include <cmath>

Buraco::Buraco() {
    const float ICE_SHEET_SIZE = 40.0f;
    const float HOLE_RADIUS = 1.5f;
    radius = HOLE_RADIUS;
    
    // Garante que o buraco não spawne muito perto do centro (onde está o filhote)
    do {
        x = (rand() % (int)(ICE_SHEET_SIZE - 4)) - (ICE_SHEET_SIZE / 2.0f - 2);
        z = (rand() % (int)(ICE_SHEET_SIZE - 4)) - (ICE_SHEET_SIZE / 2.0f - 2);
    } while (sqrt(x*x + z*z) < 5.0f);
}

void Buraco::desenha() const {
    glDisable(GL_LIGHTING);
    glColor3f(0.0f, 0.1f, 0.2f);
    glPushMatrix();
    glTranslatef(x, 0.01f, z);
    glRotatef(90, 1, 0, 0);
    gluDisk(gluNewQuadric(), 0, radius, 32, 1);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

void Buraco::desenhaPlataforma(float size) {
    glDepthMask(GL_FALSE);
    glColor4f(0.9f, 0.95f, 1.0f, 0.9f);
    glPushMatrix();
    glTranslatef(0.0f, -0.1f, 0.0f);
    glScalef(size, 0.2f, size);
    glutSolidCube(1.0);
    glPopMatrix();
    glDepthMask(GL_TRUE);
}
