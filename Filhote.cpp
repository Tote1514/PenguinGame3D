#include "Filhote.h"
#include <GL/glut.h>

Filhote::Filhote(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}

void Filhote::desenha() const {
    glPushMatrix();
    glTranslatef(x, y, z);
    // CORREÇÃO: Chama o método estático da classe Pinguim para desenhar o modelo do filhote.
    // O filhote não tem animação de asas/patas, então os ângulos são 0.
    Pinguim::desenhaModelo(true, false, 0.0f, 0.0f);
    glPopMatrix();
}
