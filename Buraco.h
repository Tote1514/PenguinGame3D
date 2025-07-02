#pragma once
#include <GL/glut.h>

class Buraco {
private:
    float x, z;
    float radius;

public:
    Buraco();
    
    // Getters
    float getX() const { return x; }
    float getZ() const { return z; }
    float getRadius() const { return radius; }
    
    // Desenho
    void desenha() const;
    static void desenhaPlataforma(float size);
};
