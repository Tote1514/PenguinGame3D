#pragma once
#include "Pinguim.h"

class Filhote {
private:
    float x, y, z;

public:
    Filhote(float _x, float _y, float _z);
    
    void desenha() const;
    
    // Getters para colisão
    float getX() const { return x; }
    float getZ() const { return z; }
    float getRadius() const { return 1.0f; }
};
