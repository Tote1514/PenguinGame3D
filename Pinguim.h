#pragma once
#include <GL/glut.h>

class Peixe;
class Filhote;
class Buraco;

class Pinguim {
private:
    float x, y, z;
    float rotationY;
    bool hasFish;
    float wingAngle, legAngle;
    bool movendo;

public:
    Pinguim();
    void reset();

    // Getters
    float getX() const { return x; }
    float getY() const { return y; }
    float getZ() const { return z; }
    float getRadius() const { return 1.0f; }
    bool temPeixe() const { return hasFish; }

    // Setters e Ações
    void setMovendo(bool status) { movendo = status; }
    void pegarPeixe() { hasFish = true; }
    void darPeixe() { hasFish = false; }
    
    // Lógica
    void handleInput(int key, float limit);
    void update();
    void desenha() const;
    void configuraCamera() const;

    // Colisões
    bool colideCom(const Peixe& peixe) const;
    bool colideCom(const Filhote& filhote) const;
    bool caiuNoBuraco(const Buraco& buraco) const;

    // CORREÇÃO: Método de desenho do modelo agora é público e estático
    static void desenhaModelo(bool isChick, bool hasFishAttached, float wingAngle, float legAngle);
};
