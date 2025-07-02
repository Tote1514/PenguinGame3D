#pragma once

#include "Pinguim.h"

class Area;

class Filhote : public Pinguim
{
public:
	Filhote(float x, float y, float z);

	void desenhar() const;

	Area getArea(); 
};

