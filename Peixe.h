#pragma once
class Peixe
{
public: 
	Peixe(float x, float y, float z, float angulo);

	~Peixe() = default;

	void desenha() const;

	void mover(float delta, float boundary);

private:

	float x, y, z;
	float anguloY;

	void desenhaCorpo() const;
	void desenhaCauda() const;

};

