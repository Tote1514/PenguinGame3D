#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Area.h"
#include "Pinguim.h"
#include "Cor.h"
#include "Filhote.h"
#include "Peixe.h"
#include "Gelo.h"

void init();
void reshape(int w, int h);
void specialKeyboard(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);
void doFrame(int value);
void timerJogo(int value);

float alturaDoChao{ -0.8 };

GLfloat rotX, rotY;
int INITIAL_WIDTH = 800;
int INITIAL_HEIGHT = 600;
int window_top, window_side, window_front, window_free;
std::vector<int> window_ids;

Pinguim pinguim(1, 0.0f, 0.0f);
Filhote filhote(0.0f, 0.0f, 0.0f);

std::vector<Peixe> cardume = {
		Peixe(12.0f, alturaDoChao, -2.0f, 90),
		Peixe(15.0f, alturaDoChao, 13.0f, 180),
		Peixe(8.0f, alturaDoChao, -15.0f, 90),
		Peixe(-10.0f, alturaDoChao, 10.0f, 180),
		Peixe(-9.0f, alturaDoChao, -4.f, 90),
};

std::vector<Gelo> gelos =
{
	Gelo(-10.0f, alturaDoChao, -15.0f),
	Gelo(-10.0f, alturaDoChao, 16.0f),
	Gelo(13.0f, alturaDoChao, -7.0f),
	Gelo(15.0f, alturaDoChao, 10.0f)
};

void gerarPosicoesAleatoriasPeixes()
{
    for (auto &peixe : cardume)
    {
        float novoX = -20.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (40.0f)));
        float novoZ = -20.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (40.0f)));
        peixe.setNewPosition(novoX, novoZ);
    }
}

void gerarPosicoesAleatoriasGelos()
{
	for (auto &gelo : gelos)
	{
		float novoX = -15.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (30.0f)));
		float novoZ = -15.0f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (30.0f)));
		gelo.setNewPosition(novoX, novoZ);
	}
}

void timerGelos(int value)
{
	gerarPosicoesAleatoriasGelos();
	
	glutTimerFunc(5000, timerGelos, 0);
}

void timerPeixes(int value)
{
    gerarPosicoesAleatoriasPeixes();
    
    glutTimerFunc(10000, timerPeixes, 0);
}

void drawScene()
{
	// Plataforma de gelo

	float zoom{ 40.f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, new float[4] {0.8f, 0.95f, 1.0f, 1.0f});
	glMaterialfv(GL_FRONT, GL_SPECULAR, new float[4] {1.0f, 1.0f, 1.0f, 1.0f});
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0f);

	glPushMatrix();
		glTranslatef(0 , alturaDoChao, 0);
		glScalef(zoom , 0.05f, zoom);
		glutSolidCube(1.0f);
	glPopMatrix();

	pinguim.desenha();
	filhote.desenha();

	for (auto &peixe : cardume)
		peixe.desenha();

	for (auto& gelo : gelos)
		gelo.desenha();


	glutSwapBuffers();
}

void display_top()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(pinguim.getX(), pinguim.getY() + 20.0f, pinguim.getZ(),
						pinguim.getX(), pinguim.getY(), pinguim.getZ(),
						0, 0, -1);
	drawScene();
}

void display_side()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(pinguim.getX(), pinguim.getY() + 5.0f, pinguim.getZ() + 20.0f,
						pinguim.getX(), pinguim.getY(), pinguim.getZ(),
						0, 1, 0);
	drawScene();
}

void display_front()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(pinguim.getX() + 20.0f, pinguim.getY() + 5.0f, pinguim.getZ(), pinguim.getX(), pinguim.getY(), pinguim.getZ(),
						0, 1, 0);
	drawScene();
}

void display_free()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(pinguim.getX() + 10.0f, pinguim.getY() + 10.0f, pinguim.getZ() + 10.0f,
						pinguim.getX(), pinguim.getY(), pinguim.getZ(),
						0, 1, 0);
	drawScene();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, GLfloat(w) / GLfloat(h), 0.1, 100.0);
}

void specialKeyboard(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		pinguim.orientarPara(1.0f, 0.0f);
		pinguim.mover(0.2f, 0);
		break;
	case GLUT_KEY_RIGHT:
		pinguim.orientarPara(-1.0f, 0.0f);
		pinguim.mover(-0.2f, 0);
		break;
	case GLUT_KEY_UP:
		pinguim.orientarPara(0.0f, 1.0f);
		pinguim.mover(0, -0.2f);
		break;
	case GLUT_KEY_DOWN:
		pinguim.orientarPara(0.0f, -1.0f);
		pinguim.mover(0, 0.2f);
		break;
	}
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (tolower(key))
	{
	case 'w':
		pinguim.orientarPara(0.0f, 1.0f);
		pinguim.mover(0, -0.2f);
		break;
	case 's':
		pinguim.orientarPara(0.0f, -1.0f);
		pinguim.mover(0, 0.2f);
		break;
	case 'a':
		pinguim.orientarPara(-1.0f, 0.0f);
		pinguim.mover(-0.2f, 0);
		break;
	case 'd':
		pinguim.orientarPara(1.0f, 0.0f);
		pinguim.mover(0.2f, 0);
		break;
	}
	glutPostRedisplay();
}

void doFrame(int value)
{
	for (auto &peixe : cardume)
	{
		if (!pinguim.temPeixePegado())
			pinguim.verificarSePegouPeixe(peixe);
	}

	for (auto& gelo : gelos)
	{
		auto areaGelo = gelo.getArea();

		if (areaGelo.colideCom(pinguim.getArea()))
		{
			std::cout << "Pinguim escorregou no gelo!" << std::endl;
			std::cout << "Jogo acabou!" << std::endl;
			std::cout << "Voce perdeu!" << std::endl;

			exit(0);
		}

	}

	if (pinguim.temPeixePegado())
		pinguim.verificarSeAlimentouFilhote(filhote);


	for (int id : window_ids)
	{
		glutSetWindow(id);
		glutPostRedisplay();
	}
	glutTimerFunc(1000 / 60, doFrame, 0);
}

void timerJogo(int value)
{
}

void init()
{
	glClearColor(0.529f, 0.808f, 0.922f, 1.0f);
	GLfloat black[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat yellow[] = {1.0, 1.0, 0.0, 1.0};
	GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat cyan[] = {0.0, 1.0, 1.0, 1.0};
	GLfloat direction[] = {0.0, -10.0, 0.0, 1.0};
	GLfloat direction1[] = {0.0, 10.0, 0.0, 1.0};

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

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	const int spacing = 10;
	const int winW = 600;
	const int winH = 450;
	const int baseX = 50;
	const int baseY = 50;

	// Free camera (canto superior esquerdo)
	glutInitWindowSize(winW, winH);
	glutInitWindowPosition(baseX + 0 * (winW + spacing), baseY + 0 * (winH + spacing));
	window_free = glutCreateWindow("Free Camera");
	init();
	glutDisplayFunc(display_free);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	window_ids.push_back(window_free);

	// Top view (canto superior direito)
	glutInitWindowSize(winW, winH);
	glutInitWindowPosition(baseX + 1 * (winW + spacing), baseY + 0 * (winH + spacing));
	window_top = glutCreateWindow("Top Camera");
	init();
	glutDisplayFunc(display_top);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	window_ids.push_back(window_top);

	// Side view (canto inferior esquerdo)
	glutInitWindowSize(winW, winH);
	glutInitWindowPosition(baseX + 0 * (winW + spacing), baseY + 1 * (winH + spacing));
	window_side = glutCreateWindow("Side Camera");
	init();
	glutDisplayFunc(display_side);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	window_ids.push_back(window_side);

	// Front view (canto inferior direito)
	glutInitWindowSize(winW, winH);
	glutInitWindowPosition(baseX + 1 * (winW + spacing), baseY + 1 * (winH + spacing));
	window_front = glutCreateWindow("Front Camera");
	init();
	glutDisplayFunc(display_front);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	window_ids.push_back(window_front);

	glutTimerFunc(100, doFrame, 0);
	srand(static_cast<unsigned int>(time(nullptr)));
	glutTimerFunc(10000, timerPeixes, 0);
	glutTimerFunc(5000, timerGelos, 0);
	glutMainLoop();
	return 0;
}
