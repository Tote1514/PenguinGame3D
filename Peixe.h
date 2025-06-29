#pragma once

class Area;

class Peixe
{
public: 
	Peixe(float x, float y, float z, float angulo);

	~Peixe() = default;

	void desenha() const;

	void mover(float delta, float boundary);

	Area getArea() const;

	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }

private:

	float x, y, z;
	float anguloY;

	void desenhaCorpo() const;
	void desenhaCauda() const;

};

