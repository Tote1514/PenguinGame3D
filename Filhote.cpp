#include "Filhote.h"

#include <GL/glut.h>

Filhote::Filhote(float x, float y, float z)
	:Pinguim(x, y, z)
{
	filhote = true;
}

void Filhote::desenhar() const
{
	glPushMatrix();
		Pinguim::desenha();
	glPopMatrix();
}
