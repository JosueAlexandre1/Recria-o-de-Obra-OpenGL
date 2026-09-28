#include "GL/glut.h" // Em alguns ambientes pode ser <GL/freeglut.h>
#include <stdlib.h>

// Variáveis de estado da interatividade
int modoNoite = 0; // 0 = Dia (Magritte), 1 = Noite
float zoom = 1.0f; // Nível de zoom
float camX = 0.0f; // Deslocamento horizontal da câmera
float camY = 0.0f; // Deslocamento vertical da câmera

// Função de inicialização de parâmetros do OpenGL
void init(void)
{
    // Define a cor de fundo (RGBA) — Azul pastel para o céu
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'n': // Alterna entre modo dia e noite
        modoNoite = !modoNoite;
        glutPostRedisplay();
        break;
    case '+': // Aumenta o zoom
        zoom *= 1.1f;
        glutPostRedisplay();
        break;
    case '-': // Diminui o zoom
        zoom /= 1.1f;
        glutPostRedisplay();
        break;
    case 'w': // Move a câmera para cima
        camY += 0.1f / zoom;
        glutPostRedisplay();
        break;
    case 's': // Move a câmera para baixo
        camY -= 0.1f / zoom;
        glutPostRedisplay();
        break;
    case 'a': // Move a câmera para a esquerda
        camX -= 0.1f / zoom;
        glutPostRedisplay();
        break;
    case 'd': // Move a câmera para a direita
        camX += 0.1f / zoom;
        glutPostRedisplay();
        break;
    case 27: // Tecla ESC para sair
        exit(0);
        break;
    default:
        break;
    }
    glutPostRedisplay(); // Solicita redesenho da cena após qualquer alteração
}

void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP: // Move a câmera para cima
        camY += 0.1f / zoom;
        break;
    case GLUT_KEY_DOWN: // Move a câmera para baixo
        camY -= 0.1f / zoom;
        break;
    case GLUT_KEY_LEFT: // Move a câmera para a esquerda
        camX -= 0.1f / zoom;
        break;
    case GLUT_KEY_RIGHT: // Move a câmera para a direita
        camX += 0.1f / zoom;
        break;
    default:
        break;
    }
    glutPostRedisplay(); // Solicita redesenho da cena após qualquer alteração
}

void drawScene()
{
    // Desenhar o cenário (céu, nuvens, etc.)
    // Céu
    glBegin(GL_QUADS);

    if (!modoNoite)
    {
        glColor3f(0.50f, 0.57f, 0.53f); // cinza-esverdeado pálido
        glVertex2f(-2.0f, -0.15f);
        glVertex2f(2.0f, -0.15f);

        // linha do horizonte
        glColor3f(0.23f, 0.28f, 0.26f); // nuvens escuras cinza-pardo/esverdeado
        glVertex2f(2.0f, 1.0f);
        glVertex2f(-2.0f, 1.0f);
    }
    else
    {
        glColor3f(0.12f, 0.15f, 0.22f);
        glVertex2f(-2.0f, -0.15f);
        glVertex2f(2.0f, -0.15f);

        // linha do horizonte
        glColor3f(0.02f, 0.03f, 0.08f);
        glVertex2f(2.0f, 1.00f);
        glVertex2f(-2.0f, 1.00f);
    }

    glEnd();

    // Mar
    glBegin(GL_QUADS);

    if (!modoNoite)
    {
        // Dia
        glColor3f(0.18f, 0.28f, 0.36f); //
        glVertex2f(-2.0f, -0.62f);
        glVertex2f(2.0f, -0.62f);

        glColor3f(0.30f, 0.42f, 0.50f); //
        glVertex2f(2.0f, -0.15f);
        glVertex2f(-2.0f, -0.15f);
    }
    else
    {
        // Noite
        glColor3f(0.05f, 0.08f, 0.14f);
        glVertex2f(-2.0f, -0.57f);
        glVertex2f(2.0f, -0.57f);

        glColor3f(0.10f, 0.15f, 0.22f);
        glVertex2f(2.0f, -0.15f);
        glVertex2f(-2.0f, -0.15f);
    }
    glEnd();

    // linha de contorno do horizonte
    glLineWidth(1.5f);
    glColor3f(0.20f, 0.30f, 0.38f); //
    glBegin(GL_LINES);
    glVertex2f(-2.0f, -0.15f);
    glVertex2f(2.0f, -0.15f);
    glEnd();

    // Muro de Pedra

    // Corpo principal do muro
    if (!modoNoite)
        glColor3f(0.42f, 0.42f, 0.44f);
    else
        glColor3f(0.18f, 0.18f, 0.20f);
    glBegin(GL_QUADS);
    glVertex2f(-2.0f, -1.0f);
    glVertex2f(2.0f, -1.0f);
    glVertex2f(2.0f, -0.62f);
    glVertex2f(-2.0f, -0.62f);
    glEnd();

    // Borda superior do muro
    if (!modoNoite)
        glColor3f(0.55f, 0.55f, 0.58f);
    else
        glColor3f(0.25f, 0.25f, 0.28f); //
    glBegin(GL_QUADS);
    glVertex2f(-2.0f, -0.62f);
    glVertex2f(2.0f, -0.62f);
    glVertex2f(2.0f, -0.57f);
    glVertex2f(-2.0f, -0.57f);
    glEnd();

    // Juntas dos blocos de pedra
    if (!modoNoite)
        glColor3f(0.30f, 0.30f, 0.30f);
    else
        glColor3f(0.10f, 0.10f, 0.12f);
    glBegin(GL_LINES);
    glVertex2f(-2.0f, -0.81f);
    glVertex2f(2.0f, -0.81f);

    float larguraBloco = 0.5f; // Largura de cada tijolo

    // Linhas verticais da fileira superior (de -2.0 a 2.0)
    for (float x = -2.0f; x <= 2.0f; x += larguraBloco)
    {
        glVertex2f(x, -0.62f);
        glVertex2f(x, -0.81f);
    }

    // Linhas verticais da fileira inferior (intercaladas com offset de metade do bloco)
    for (float x = -2.0f + (larguraBloco / 2.0f); x <= 2.0f; x += larguraBloco)
    {
        glVertex2f(x, -0.81f);
        glVertex2f(x, -1.00f);
    }
    glEnd();
}

// Função responsável por redesenhar a cena (Display Callback)
void display(void)
{
    // Limpa o buffer de cor
    glClear(GL_COLOR_BUFFER_BIT);

    // Carrega a matriz de modelo para transformações
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Aplica transformações de zoom e deslocamento da câmera
    glScalef(zoom, zoom, 1.0f);     // Aplica o zoom
    glTranslatef(camX, camY, 0.0f); // Aplica o deslocamento da câmera

    // =========================================================
    // TODO: Inserir chamadas de desenho (cenário, homem, maçã)
    // =========================================================

    // Renderiza a cena
    drawScene();
    // drewCorpo();
    // drewChapeuECabeca();
    // drewMaca();

    // Troca os buffers
    glutSwapBuffers();
}

// Função chamada ao redimensionar a janela (Reshape Callback)
void reshape(int width, int height)
{
    if (height == 0)
        height = 1;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)width / (float)height;
    if (width >= height)
    {
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    }
    else
    {
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("CG I - Releitura: O Filho do Homem (Rene Magritte)");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutKeyboardFunc(keyboard);   // Registra teclas normais (W, A, S, D, +, -, N)
    glutSpecialFunc(specialKeys); // Registra as setas do teclado

    glutMainLoop();

    return 0;
}