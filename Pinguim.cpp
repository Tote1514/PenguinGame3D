#include "Pinguim.h"

#include <GL/glut.h>
#include <math.h>

#include "Area.h"
#include "Cor.h"
#include "Peixe.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846 
#endif

Pinguim::Pinguim(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

void Pinguim::desenha() const
{
	glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(anguloY, 0.0f, 1.0f, 0.0f);
		glRotatef(anguloX, 1, 0, 0);
		if (filhote)
			glScalef(0.5f, 0.5f, 0.5f);

		desenhaCorpo();
		desenhaOlhos();
		desenhaBico();
		desenhaPatas();
		desenhaAsas();
		desenhaCabeca();
	glPopMatrix();
}

void Pinguim::desenhaCorpo() const
{
	auto corPreta = Cor::preto();

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corPreta[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corPreta[1]);
	glMaterialfv(GL_FRONT, GL_SHININESS, corPreta[2]);

	glPushMatrix();
		glScalef(0.6f, 0.7f, 0.6f);
		glutSolidSphere(1.0f, 20, 20);
	glPopMatrix();

	auto corBranca = Cor::branco();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corBranca[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corBranca[1]);
	glMaterialfv(GL_FRONT, GL_SHININESS, corBranca[2]);

	glPushMatrix();
		glTranslatef(0.0f, 0.f, 0.5f);
		glScalef(0.3f, 0.4f, 0.1f);
		glutSolidSphere(1.0f, 20, 20);
	glPopMatrix();
}

void Pinguim::desenhaOlhos() const
{
	auto corBranca = Cor::branco();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corBranca[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corBranca[1]);
	glMaterialfv(GL_FRONT, GL_SHININESS, corBranca[2]);

	glPushMatrix();
		glTranslatef(-0.2f, 1.2f, 0.2f);
		glutSolidSphere(0.1f, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.2f, 1.2f, 0.2f);
		glutSolidSphere(0.1f, 20, 20);
	glPopMatrix();
}

void Pinguim::desenhaBico() const
{
	auto corLaranja = Cor::laranjaOpaco();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corLaranja[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corLaranja[1]);
	glMaterialfv(GL_FRONT, GL_SHININESS, corLaranja[2]);

	glPushMatrix();
		glTranslatef(0.0f, 1.0f, 0.3f);
		glScalef(0.7f, 0.7f, 1.f);
		glutSolidCone(0.2f, 0.4f, 20, 20);
	glPopMatrix();

	if (!temPeixe) 
		return;

	Peixe peixeNoBico(0.0f, 1.0f, 0.8f, 180);
	peixeNoBico.desenha();

}

void Pinguim::desenhaPatas() const
{
	auto corLaranja = Cor::laranja();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corLaranja[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corLaranja[1]);
	glMaterialfv(GL_FRONT, GL_SHININESS, corLaranja[2]);

	glPushMatrix();
		glTranslatef(-0.3f, -0.7f, 0.0f);
		glScalef(0.5f, 0.2f, 0.5f);
		glutSolidSphere(0.5f, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.3f, -0.7f, 0.0f);
		glScalef(0.5f, 0.2f, 0.5f);
		glutSolidSphere(0.5f, 20, 20);
	glPopMatrix();
}

void Pinguim::desenhaAsas() const
{
	auto corPreta = Cor::preto();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corPreta[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corPreta[1]);
	glMaterialfv(GL_FRONT, GL_SHININESS, corPreta[2]);
	glPushMatrix();
		glTranslatef(-0.6f, 0.0f, 0.0f);
		glScalef(0.2f, 0.5f, 0.2f);
		glutSolidSphere(1.0f, 20, 20);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0.6f, 0.0f, 0.0f);
		glScalef(0.2f, 0.5f, 0.2f);
		glutSolidSphere(1.0f, 20, 20);
	glPopMatrix();
}

void Pinguim::desenhaCabeca() const
{
	auto corPreto = Cor::preto();
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, corPreto[0]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corPreto[1]);
	glMaterialfv(GL_FRONT, GL_SHININESS, corPreto[2]);

	glPushMatrix();
		glTranslatef(0.0f, 1.f, 0.0f);
		glutSolidSphere(0.4f, 20, 20);
	glPopMatrix();
}

void Pinguim::andarFrente(float distancia)
{
	x += distancia * sin(anguloY * 3.14159f / 180.0f);
	z -= distancia * cos(anguloY * 3.14159f / 180.0f);
}

void Pinguim::andarLateral(float distancia)
{
	// 90 graus para a esquerda: usa cos para x e sin para z
	x += distancia * cos(anguloY * 3.14159f / 180.0f);
	z += distancia * sin(anguloY * 3.14159f / 180.0f);
}

void Pinguim::orientarPara(float dx, float dz)
{
	anguloY = atan2(dx, -dz) * 180.0f / 3.14159f;
}

void Pinguim::mover(float dx, float dz, float boundary)
{
	x += dx;
	z += dz;


	if (x > boundary)
	{
		y = -0.8;
		anguloX = 90;
	}
	else if (x <= boundary)
	{
		y = 0.0;
		anguloX = 0;
	}
}

#include <iostream>

void Pinguim::verificarSePegouPeixe(Peixe& peixe)
{
	// Ajusta a posição da cabeça com base no ângulo
	float deslocamento = 0.5f; // distância da cabeça em relação ao centro do corpo

	float rad = anguloY * M_PI / 180.0f; // converte para radiano


	float posicaoXCabeca = x + deslocamento * sin(rad);
	float posicaoZCabeca = z - deslocamento * cos(rad); // negativo porque o eixo Z cresce pra "trás"
	float posicaoYCabeca = y + 1.0f; // assumindo que a cabeça fica acima do corpo

	// Debug
	std::cout << "anguloY: " << anguloY << std::endl;
	std::cout << "posicaoXCabeca: " << posicaoXCabeca << ", posicaoZCabeca: " << posicaoZCabeca << std::endl;

	// Dimensões da cabeça
	float larguraCabeca = 0.4f;
	float profundidadeCabeca = 0.4f;
	float alturaCabeca = 0.4f;

	// Corrigindo a ordem: altura, largura, profundidade, centroX, centroY, centroZ
	Area areaCabeca(
		alturaCabeca, larguraCabeca, profundidadeCabeca,
		posicaoXCabeca, posicaoYCabeca, posicaoZCabeca
	);

	if (areaCabeca.colideCom(peixe.getArea()))
	{
		temPeixe = true;
		std::cout << "Pinguim pegou o peixe!" << std::endl;
	}
}


bool Pinguim::temPeixePegado() const
{
	return temPeixe;
}
