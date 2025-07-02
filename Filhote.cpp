#include "Filhote.h"

#include "Area.h"

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

Area Filhote::getArea()
{
	return Area(1.0f, 1.0f, 1.0f, x, y, z);
}
