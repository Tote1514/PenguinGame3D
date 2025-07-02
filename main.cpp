#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

#include "Pinguim.h"
#include "Filhote.h"
#include "Peixe.h"
#include "Buraco.h"

// --- Constantes Globais ---
const int FPS = 60;
const int DELAY = 1000 / FPS;
const float ICE_SHEET_SIZE = 40.0f;

// --- Variáveis Globais de Jogo ---
Pinguim pinguim;
Filhote filhote(0.0f, 0.5f, 0.0f);
std::vector<Peixe> peixes;
std::vector<Buraco> buracos;

int chickLifeTimer;
int sessionTimer;
int framesSinceLastSecond = 0;
int holeSpawnTimer = 0;
bool isGameOver = false;
bool playerWon = false;
std::string gameOverReason = "";

int window_top, window_chase, window_side, window_free;
std::vector<int> window_ids;

// --- Protótipos ---
void initializeGame();
void drawScene();
void drawUI();
void reshape_perspective(int w, int h);
void reshape_ortho(int w, int h);


// --- Funções Auxiliares ---
std::string formatTime(int totalSeconds) {
    if (totalSeconds < 0) totalSeconds = 0;
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;
    return oss.str();
}

void checkCollisions() {
    if (pinguim.temPeixe()) {
        if (pinguim.colideCom(filhote)) {
            pinguim.darPeixe();
            chickLifeTimer += 60;
            peixes.push_back(Peixe());
        }
    } else {
        for (auto it = peixes.begin(); it != peixes.end(); ++it) {
            if (pinguim.colideCom(*it)) {
                pinguim.pegarPeixe();
                it = peixes.erase(it);
                break;
            }
        }
    }
    for (const auto& hole : buracos) {
        if (pinguim.caiuNoBuraco(hole)) {
            isGameOver = true;
            gameOverReason = "Voce caiu em um buraco!";
        }
    }
}

void updateGameLogic() {
    framesSinceLastSecond++;
    if (framesSinceLastSecond >= FPS) {
        if (chickLifeTimer > 0) chickLifeTimer--;
        else {
            isGameOver = true;
            gameOverReason = "O filhote nao sobreviveu!";
        }
        if (sessionTimer > 0) sessionTimer--;
        else if (!isGameOver) {
            playerWon = true;
        }
        framesSinceLastSecond = 0;

        holeSpawnTimer++;
        if (holeSpawnTimer >= 15 && buracos.size() < 10) {
            buracos.push_back(Buraco());
            holeSpawnTimer = 0;
        }
    }
    pinguim.update();
    checkCollisions();
}

// --- Funções de Desenho ---
void drawScene() {
    Buraco::desenhaPlataforma(ICE_SHEET_SIZE);
    filhote.desenha();
    for (const auto& fish : peixes) {
        fish.desenha();
    }
    for (const auto& hole : buracos) {
        hole.desenha();
    }
    pinguim.desenha();
}

void drawUI() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_LIGHTING);

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    if (playerWon || isGameOver) {
        std::string endMsg = playerWon ? "VOCE GANHOU!" : "GAME OVER";
        if (playerWon) glColor3f(0.1f, 0.8f, 0.1f);
        else glColor3f(0.8f, 0.1f, 0.1f);
        glRasterPos2i(w / 2 - 100, h / 2 + 20);
        for (char c : endMsg) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c);

        if (isGameOver && !gameOverReason.empty()) {
             glColor3f(0.8f, 0.1f, 0.1f);
             glRasterPos2i(w / 2 - 120, h / 2);
             for (char c : gameOverReason) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
        }

        glColor3f(0.0f, 0.0f, 0.0f);
        std::string restartMsg = "Pressione 'R' para reiniciar";
        glRasterPos2i(w / 2 - 100, h / 2 - 30);
        for (char c : restartMsg) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    } else {
        glColor3f(0.0f, 0.0f, 0.0f);
        std::string lifeStr = "Vida do Filhote: " + formatTime(chickLifeTimer);
        glRasterPos2i(10, h - 20);
        for (char c : lifeStr) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

        std::string sessionStr = "Vitoria em: " + formatTime(sessionTimer);
        glRasterPos2i(10, h - 40);
        for (char c : sessionStr) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
    
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

// --- Funções do GLUT ---
void init(void) {
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLfloat light_ambient[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {10.0, 20.0, 10.0, 0.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void timer(int /*value*/) {
    if (!isGameOver && !playerWon) {
        updateGameLogic();
    }
    for (int id : window_ids) {
        glutSetWindow(id);
        glutPostRedisplay();
    }
    glutTimerFunc(DELAY, timer, 0);
}

void reshape_perspective(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void reshape_ortho(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = (float)w / h;
    float ortho_size = 25.0f; // Zoom da câmera de topo
    glOrtho(-ortho_size * aspect, ortho_size * aspect, -ortho_size, ortho_size, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}


void display_top() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); // CORREÇÃO
    glLoadIdentity();          // CORREÇÃO: Reseta a matriz da câmera
    gluLookAt(pinguim.getX(), 50.0, pinguim.getZ(), pinguim.getX(), 0, pinguim.getZ(), 0, 0, -1);
    drawScene();
    drawUI();
    glutSwapBuffers();
}

void display_chase() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); // CORREÇÃO
    glLoadIdentity();          // CORREÇÃO: Reseta a matriz da câmera
    pinguim.configuraCamera();
    drawScene();
    drawUI();
    glutSwapBuffers();
}

void display_side() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); // CORREÇÃO
    glLoadIdentity();          // CORREÇÃO: Reseta a matriz da câmera
    gluLookAt(pinguim.getX() + 25.0, pinguim.getY() + 5, pinguim.getZ(), pinguim.getX(), pinguim.getY(), pinguim.getZ(), 0, 1, 0);
    drawScene();
    drawUI();
    glutSwapBuffers();
}

void display_free() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW); // CORREÇÃO
    glLoadIdentity();          // CORREÇÃO: Reseta a matriz da câmera
    gluLookAt(3.0, 20.0, 20.0, 0.0, 0.0, 0.0, 0, 1, 0);
    drawScene();
    drawUI();
    glutSwapBuffers();
}

void keyboard(unsigned char key, int /*x*/, int /*y*/) {
    if (isGameOver || playerWon) {
        if (key == 'r' || key == 'R') {
            initializeGame();
        }
    }
    if (key == 27) exit(0);
}

void specialKeyboard(int key, int /*x*/, int /*y*/) {
    if (isGameOver || playerWon) return;
    pinguim.setMovendo(true);
    pinguim.handleInput(key, ICE_SHEET_SIZE);
}

void initializeGame() {
    peixes.clear();
    buracos.clear();
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < 5; ++i) {
        peixes.push_back(Peixe());
    }
    for (int i = 0; i < 3; ++i) {
        buracos.push_back(Buraco());
    }

    pinguim.reset();
    isGameOver = false;
    playerWon = false;
    gameOverReason = "";
    chickLifeTimer = 60;
    sessionTimer = 300;
    framesSinceLastSecond = 0;
    holeSpawnTimer = 0;
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    // Inicializa o jogo ANTES de criar as janelas
    init();
    initializeGame();

    // Janela 1: Câmera de perseguição ("de frente" para o pinguim)
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(50, 50);
    window_chase = glutCreateWindow("Penguin Adventure - Eixo Z (Perseguicao)");
    init(); // Chama init para cada contexto de janela
    glutDisplayFunc(display_chase);
    glutReshapeFunc(reshape_perspective);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    window_ids.push_back(window_chase);

    // Janela 2: Câmera de topo
    glutInitWindowPosition(700, 50);
    window_top = glutCreateWindow("Penguin Adventure - Eixo Y (Topo)");
    init();
    glutDisplayFunc(display_top);
    glutReshapeFunc(reshape_ortho); // CORREÇÃO: Usa reshape ortográfico
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    window_ids.push_back(window_top);

    // Janela 3: Câmera lateral
    glutInitWindowPosition(50, 700);
    window_side = glutCreateWindow("Penguin Adventure - Eixo X (Lateral)");
    init();
    glutDisplayFunc(display_side);
    glutReshapeFunc(reshape_perspective);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    window_ids.push_back(window_side);

    // Janela 4: Câmera livre
    glutInitWindowPosition(700, 700);
    window_free = glutCreateWindow("Penguin Adventure - Posicao Livre");
    init();
    glutDisplayFunc(display_free);
    glutReshapeFunc(reshape_perspective);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeyboard);
    window_ids.push_back(window_free);
    
    glutTimerFunc(DELAY, timer, 0);
    glutMainLoop();
    return 0;
}
