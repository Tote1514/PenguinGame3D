#pragma once

class Peixe;

class Pinguim
{
public:
	Pinguim(float x, float y, float z);
	void desenha() const;
	void andarFrente(float distancia);
	void andarLateral(float distancia);

	void orientarPara(float dx, float dz);
	void mover(float dx, float dz, float boundary = 0.5);

	void verificarSePegouPeixe(Peixe& peixe);
	bool temPeixePegado() const;

private:
	void desenhaCorpo() const;
	void desenhaOlhos() const;
	void desenhaBico() const;
	void desenhaPatas() const;
	void desenhaAsas() const;
	void desenhaCabeca() const;

protected:
	float x, y, z;
	float anguloY{ 90.f };
	float anguloX{ 0.f };
	bool filhote{ false };

	bool temPeixe{ false };
};

