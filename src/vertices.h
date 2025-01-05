#ifndef VERTICES_H
#define VERTICES_H

float cubo1[] = {
    // Posições            // Cores
    -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 1.0f,

    -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 1.0f
};

unsigned int indices[] = {
    0, 1, 2, 2, 3, 0, // Frente
    4, 5, 6, 6, 7, 4, // Trás
    0, 1, 5, 5, 4, 0, // Baixo
    3, 2, 6, 6, 7, 3, // Topo
    1, 2, 6, 6, 5, 1, // Direita
    0, 3, 7, 7, 4, 0  // Esquerda
};

#endif // VERTICES_H
