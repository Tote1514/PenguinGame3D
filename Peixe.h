#pragma once

class Peixe {
private:
    float x, y, z;

public:
    Peixe();
    
    // Getters
    float getX() const { return x; }
    float getZ() const { return z; }
    float getRadius() const { return 0.8f; }

    // Desenho
    void desenha() const;
    static void desenhaModelo();
};
