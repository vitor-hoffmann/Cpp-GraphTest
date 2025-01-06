#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "renderer.h"
#include "shaders.h"
#include "inputs.h"
#include "window.h"
#include "shaders.h" // Módulo para gerenciar shaders

// Variáveis globais para a câmera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 400.0f, lastY = 300.0f;
bool firstMouse = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main() {
    // Inicializar janela usando o módulo `window.h`
    GLFWwindow* window = initializeWindow(800, 600, "Graphics test");
    if (!window) {
        return -1; // Falha ao criar a janela
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Inicializar GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Falha ao inicializar GLAD!" << std::endl;
        terminateGLFW(window);
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    // Criar e usar o programa de shaders com o módulo `shader.h`
    unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);

    // Configurar buffers para renderização
    unsigned int VAO, VBO, EBO;
    setupBuffers(VAO, VBO, EBO);

    // Configurar projeção
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    // Controle de tempo
    float deltaTime, lastFrame = 0.0f;

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        // Calcular deltaTime
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Processar entrada
        processInput(window, deltaTime);

        // Limpar buffers de cor e profundidade
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Usar o programa de shader
        glUseProgram(shaderProgram);

        // Configurar matrizes de transformação
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Renderizar o cubo
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // Trocar buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Limpar recursos
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    terminateGLFW(window); // Encerrar GLFW usando o módulo
    return 0;
}
