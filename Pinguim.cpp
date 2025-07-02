#include "Pinguim.h"
#include "Peixe.h"
#include "Filhote.h"
#include "Buraco.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

Pinguim::Pinguim() {
    reset();
}

void Pinguim::reset() {
    x = 0.0f; y = 0.75f; z = 5.0f;
    rotationY = 180.0f;
    hasFish = false;
    wingAngle = 0.0f; legAngle = 0.0f;
    movendo = false;
}

void Pinguim::handleInput(int key, float limit) {
    const float PINGUIN_MOVE_SPEED = 0.2f;
    const float PINGUIN_ROTATE_SPEED = 3.0f;

    switch (key) {
        case GLUT_KEY_UP:
            x += sin(rotationY * M_PI / 180.0) * PINGUIN_MOVE_SPEED;
            z += cos(rotationY * M_PI / 180.0) * PINGUIN_MOVE_SPEED;
            break;
        case GLUT_KEY_DOWN:
            x -= sin(rotationY * M_PI / 180.0) * PINGUIN_MOVE_SPEED;
            z -= cos(rotationY * M_PI / 180.0) * PINGUIN_MOVE_SPEED;
            break;
        case GLUT_KEY_LEFT:
            rotationY += PINGUIN_ROTATE_SPEED;
            break;
        case GLUT_KEY_RIGHT:
            rotationY -= PINGUIN_ROTATE_SPEED;
            break;
    }

    float boundary = limit / 2.0f - getRadius();
    if (x > boundary) x = boundary;
    if (x < -boundary) x = -boundary;
    if (z > boundary) z = boundary;
    if (z < -boundary) z = -boundary;
}

void Pinguim::update() {
    if (movendo) {
        wingAngle = 40.0f * sin(glutGet(GLUT_ELAPSED_TIME) * 0.01);
        legAngle = 35.0f * sin(glutGet(GLUT_ELAPSED_TIME) * 0.01);
    } else {
        wingAngle = 0;
        legAngle = 0;
    }
    movendo = false;
}

void Pinguim::desenha() const {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotationY, 0, 1, 0);
    // Chama o método de desenho estático, passando os parâmetros de animação
    desenhaModelo(false, hasFish, wingAngle, legAngle);
    glPopMatrix();
}

void Pinguim::configuraCamera() const {
    float camX = x - 8 * sin(rotationY * M_PI / 180.0);
    float camZ = z - 8 * cos(rotationY * M_PI / 180.0);
    gluLookAt(camX, y + 4, camZ, x, y, z, 0, 1, 0);
}

// Implementação das colisões
bool Pinguim::colideCom(const Peixe& peixe) const {
    float dist = sqrt(pow(x - peixe.getX(), 2) + pow(z - peixe.getZ(), 2));
    return dist < getRadius() + peixe.getRadius();
}

bool Pinguim::colideCom(const Filhote& filhote) const {
    float dist = sqrt(pow(x - filhote.getX(), 2) + pow(z - filhote.getZ(), 2));
    return dist < getRadius() + filhote.getRadius();
}

bool Pinguim::caiuNoBuraco(const Buraco& buraco) const {
    float dist = sqrt(pow(x - buraco.getX(), 2) + pow(z - buraco.getZ(), 2));
    return dist < buraco.getRadius();
}

// Modelo genérico do Pinguim/Filhote
void Pinguim::desenhaModelo(bool isChick, bool hasFishAttached, float wingAngle, float legAngle) {
    // Corpo
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
    glScalef(1.0f, 1.3f, 1.0f);
    glutSolidSphere(isChick ? 0.3 : 0.5, 20, 20);
    glPopMatrix();
    
    // Barriga
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.25f);
    glScalef(0.8f, 1.1f, 0.8f);
    glutSolidSphere(isChick ? 0.3 : 0.5, 20, 20);
    glPopMatrix();
    
    // Cabeça
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
    glTranslatef(0.0f, isChick ? 0.45f : 0.75f, 0.0f);
    glutSolidSphere(isChick ? 0.25 : 0.35, 20, 20);
    glPopMatrix();
    
    // Bico e Peixe
    glColor3f(1.0f, 0.6f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, isChick ? 0.5f : 0.75f, isChick ? 0.22f : 0.3f);
    glRotatef(90.0f, 1, 0, 0);
    glutSolidCone(isChick ? 0.08 : 0.1, isChick ? 0.3 : 0.5, 10, 10);
    if (hasFishAttached) {
        glPushMatrix();
        glTranslatef(0.0f, 0.4f, 0.0f);
        glRotatef(-90, 1, 0, 0);
        glScalef(0.3f, 0.3f, 0.3f);
        Peixe::desenhaModelo();
        glPopMatrix();
    }
    glPopMatrix();

    // Olhos
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(-0.1f, isChick ? 0.55f : 0.85f, isChick ? 0.2f : 0.3f);
    glutSolidSphere(isChick ? 0.05 : 0.07, 10, 10);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.1f, isChick ? 0.55f : 0.85f, isChick ? 0.2f : 0.3f);
    glutSolidSphere(isChick ? 0.05 : 0.07, 10, 10);
    glPopMatrix();

    // Patas
    glColor3f(1.0f, 0.6f, 0.0f);
    float legPosX = isChick ? 0.15f : 0.25f;
    float legPosY = isChick ? -0.2f : -0.6f;
    glPushMatrix();
    glTranslatef(-legPosX, legPosY, 0.1f);
    if (!isChick) glRotatef(legAngle, 1, 0, 0);
    glScalef(isChick?0.15f:0.2f, isChick?0.08f:0.1f, isChick?0.3f:0.5f);
    glutSolidCube(1.0);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(legPosX, legPosY, 0.1f);
    if (!isChick) glRotatef(-legAngle, 1, 0, 0);
    glScalef(isChick?0.15f:0.2f, isChick?0.08f:0.1f, isChick?0.3f:0.5f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Asas
    if (!isChick) {
        glColor3f(0.1f, 0.1f, 0.1f);
        glPushMatrix();
        glTranslatef(-0.5f, 0.0f, 0.0f);
        glRotatef(-20, 0, 0, 1);
        glRotatef(wingAngle, 1, 0, 0);
        glScalef(0.1f, 0.6f, 0.4f);
        glutSolidCube(1.0);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.5f, 0.0f, 0.0f);
        glRotatef(20, 0, 0, 1);
        glRotatef(-wingAngle, 1, 0, 0);
        glScalef(0.1f, 0.6f, 0.4f);
        glutSolidCube(1.0);
        glPopMatrix();
    }
}
