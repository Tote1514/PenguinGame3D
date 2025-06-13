#pragma once
class Pinguim
{
public:
	Pinguim(float x, float y, float z);
	void desenha() const;
	void andarFrente(float distancia);
	void andarLateral(float distancia);

	void orientarPara(float dx, float dz);
	void mover(float dx, float dz);

private:
	void desenhaCorpo() const;
	void desenhaOlhos() const;
	void desenhaBico() const;
	void desenhaPatas() const;
	void desenhaAsas() const;
	void desenhaCabeca() const;
	
	float x, y, z;
	float anguloY{ 0.f };
};

