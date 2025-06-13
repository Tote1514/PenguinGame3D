#include <GL/glut.h>
#include <iostream>

#include "Pinguim.h"
#include "Cor.h"

void desenha();
void init();
void reshape(int w, int h);
void posicaoObservador(void);
void teclasEspecias(int tecla, int x, int y);
void teclas(unsigned char key, int x, int y);

GLfloat angle, fAspect, rotX, rotY;
GLdouble obsX, obsY, obsZ;


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Pinguim 3D Game");
	init();
	
	glutDisplayFunc(desenha);
	glutReshapeFunc(reshape);
	glutSpecialFunc(teclasEspecias);
	glutKeyboardFunc(teclas);
	
	glutMainLoop();
	
	return 0;
}

void init()
{
	glClearColor(0.529f, 0.808f, 0.922f, 1.0f); // background color
	GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat yellow[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat cyan[] = { 0.0, 1.0, 1.0, 1.0 };
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat direction[] = { 0.0, -10.0, 0.0, 1.0 };
	GLfloat direction1[] = { 0.0, 10.0, 0.0, 1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cyan);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 30);

	glLightfv(GL_LIGHT0, GL_AMBIENT, black);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, yellow);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glLightfv(GL_LIGHT0, GL_POSITION, direction);

	glLightfv(GL_LIGHT1, GL_AMBIENT, black);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);
	glLightfv(GL_LIGHT1, GL_POSITION, direction1);

	glEnable(GL_LIGHTING);                // so the renderer considers light
	glEnable(GL_LIGHT0);                  // turn LIGHT0 on
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);

	rotX = 30;
	rotY = 0;
	obsZ = 5;

	glDisable(GL_COLOR_MATERIAL);
}

Pinguim pinguim(0.0f, 0.0f, 0.0f);

void desenha()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	// Plano de gelo
	glPushMatrix();
	glTranslatef(-12, -0.8, 0); // um pouco abaixo do pinguim
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, new float[4] {0.8f, 0.95f, 1.0f, 1.0f}); // azul gelo claro
	glMaterialfv(GL_FRONT, GL_SPECULAR, new float[4] {1.0f, 1.0f, 1.0f, 1.0f});
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);
	glScalef(25.0f, 0.05f, 20.0f); // bem largo e bem fino
	glutSolidCube(1.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(13, -0.8, 0);
	auto corLaranja = Cor::azul();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corLaranja[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corLaranja[1]);
	glMaterialfv(GL_FRONT, GL_SHININESS, corLaranja[2]);
	glScalef(25.0f, 0.05f, 20.0f);
	glutSolidCube(1.0f);
	glPopMatrix();


	pinguim.desenha();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	posicaoObservador();
}

void posicaoObservador(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -20);
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
}

void teclasEspecias(int tecla, int x, int y)
{
	switch (tecla)
	{
	case GLUT_KEY_LEFT:	rotY--;
		break;
	case GLUT_KEY_RIGHT:rotY++;
		break;
	case GLUT_KEY_UP:	rotX++;
		break;
	case GLUT_KEY_DOWN:	rotX--;
		break;
	}
	posicaoObservador();
	glutPostRedisplay();
}

void teclas(unsigned char key, int x, int y)
{
	switch (tolower(key))
	{
	case 'w': // frente
		pinguim.orientarPara(0.0f, -1.0f);
		pinguim.mover(0, 0.2f);
		break;

	case 's': // trás
		pinguim.orientarPara(0.0f, 1.0f);
		pinguim.mover(0, -0.2f);
		break;

	case 'a': // esquerda
		pinguim.orientarPara(-1.0f, 0.0f);
		pinguim.mover(-0.2f, 0);
		break;

	case 'd': // direita
		pinguim.orientarPara(1.0f, 0.0f);
		pinguim.mover(0.2f, 0);
		break;
	}

	posicaoObservador();
	glutPostRedisplay();
}
