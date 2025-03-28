/*
Practica 08, Iluminación de objetos 3D            Rodrigo Jafet Osorio Angeles
Fecha de entrega: 28/03/2025                    318008893
*/

// Std. Includes
#include <iostream>
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Funciones prototipo
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Cámara
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

// Atributos de la luz
// La posición se deriva del ángulo "rot" (trayectoria semicircular)
glm::vec3 lightPos(0.0f, 0.0f, 0.0f); // No se usa directamente
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// Variables para la trayectoria semicircular de la luz en el plano XY
bool lightOn = true;            // Control de visualización de la lámpara (opcional)
float rot = 180.0f;             // Ángulo en grados (inicia en 180° => posición (-5,0,0))
const float maxAngle = 180.0f;  // Ángulo máximo
const float minAngle = 0.0f;    // Ángulo mínimo
const float radius = 5.0f;      // Radio para que la luz se mueva de (-5,0,0) a (5,0,0)

// Variable para alternar entre dos luces (cálida y fría)
bool useWarmLight = true;       // true: luz cálida (sun), false: luz fría (moon)

// Animación desactivada (la trayectoria se controla manualmente con O y L)
bool activanim = false;

int main()
{
    // Inicializar GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "28/03/2025    Rodrigo Osorio 318008893    --Materiales e Iluminacion--", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Configurar callbacks
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    // Compilar shaders
    // Se asume que el shader de iluminación (lighting.frag) ha sido modificado para incluir:
    //
    // struct Material {
    //    vec3 ambient;
    //    vec3 diffuse;
    //    vec3 specular;
    //    float shininess;
    //    vec3 emissive; // componente emisiva
    // };
    //
    // ... y en main() se enviará el valor correspondiente de material.emissive.
    Shader shader("Shader/modelLoading.vs", "Shader/modelLoading.frag"); // Para objetos de la escena
    Shader lampshader("Shader/lamp.vs", "Shader/lamp.frag");              // Si se desea un shader simple para otros fines
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");    // Para iluminación (incluye emissive)

    // Cargar modelos de la escena
    Model red_dog((char*)"Models/RedDog.obj");
    Model paloma((char*)"Models/Paloma.obj");
    Model boat((char*)"Models/Boat.obj");
    Model star((char*)"Models/Starfish.obj");
    Model tiller((char*)"Models/Tiller.obj");
    Model shark((char*)"Models/Shark.obj");

    // Cargar modelos para la lámpara (sun y moon)
    Model sun((char*)"Models/sun.obj");
    Model moon((char*)"Models/moon.obj");

    // Calcular la proyección
    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    // Bucle principal de renderizado
    while (!glfwWindowShouldClose(window))
    {
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        DoMovement();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Calcular la posición de la luz en el plano XY (trayectoria semicircular de -7 a 7 en X)
        float radian = glm::radians(rot);
        glm::vec3 newLightPos;
        newLightPos.x = radius * cos(radian);  // x = 5 * cos(rot)
        newLightPos.y = radius * sin(radian);    // y = 5 * sin(rot)
        newLightPos.z = 0.0f;

        // Enviar informacion de proyección y vista al shader de iluminación
        lightingShader.Use();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniform3f(glGetUniformLocation(lightingShader.Program, "viewPos"),
            camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        // Enviar propiedades de la luz
        if (useWarmLight)
        {
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.4f, 0.2f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 0.8f, 0.4f, 0.0f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 1.0f, 0.5f, 0.0f);
        }
        else
        {
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"), 0.1f, 0.1f, 0.2f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"), 0.2f, 0.2f, 0.8f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"), 0.4f, 0.5f, 1.0f);
        }
        glUniform3f(glGetUniformLocation(lightingShader.Program, "light.position"),
            newLightPos.x, newLightPos.y, newLightPos.z);

        // Enviar propiedades del material para los objetos de la escena
        // (sin autoiluminación)
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.8f, 0.8f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 0.8f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "material.emissive"), 0.0f, 0.0f, 0.0f);

        // Dibujar modelos de la escena

        // Red Dog
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(1.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        red_dog.Draw(lightingShader);

        // Paloma
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.8f));
        model = glm::scale(model, glm::vec3(1.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        paloma.Draw(lightingShader);

        // Boat
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.2f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        boat.Draw(lightingShader);

        // Starfish
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, -1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(2.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        star.Draw(lightingShader);

        // Tiller
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(0.5f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tiller.Draw(lightingShader);

        // Shark
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, -1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        shark.Draw(lightingShader);

        // Dibujar la lámpara (modelo de la fuente de luz) usando el mismo shader de iluminación
        // Configuramos la componente emisiva según el tipo de luz: para sun (cálida) o moon (fría)
        // Se reutilizan los mismos uniformes de proyección, vista y light
        lightingShader.Use();
        // En la lámpara, el material tendrá una fuerte componente emisiva
        if (useWarmLight)
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.emissive"), 0.8f, 0.5f, 0.0f);
        else
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.emissive"), 0.4f, 0.4f, 0.4f);
        // Para la lámpara, podemos mantener los demás parámetros de material (ambient, diffuse, specular) o ajustarlos si se desea
        // Se establece la transformación para colocar la lámpara en la posición de la luz calculada
        model = glm::mat4(1.0f);
        model = glm::translate(model, newLightPos);
        model = glm::scale(model, glm::vec3(0.8f));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

        // Dibujar el modelo correspondiente en la lámpara: sun para luz cálida, moon para luz fría
        if (useWarmLight)
            sun.Draw(lightingShader);
        else
            moon.Draw(lightingShader);

        glfwSwapBuffers(window);
    }

    // Liberar recursos creados en este código
    // Se liberan los buffers del cubo si se usaron (en este ejemplo se utiliza el modelo sun/moon, por lo que no es necesario)
    glfwTerminate();
    return 0;
}

void DoMovement()
{
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
        camera.ProcessKeyboard(RIGHT, deltaTime);

    // Control manual de la trayectoria con teclas O y L
    if (keys[GLFW_KEY_O])
    {
        rot -= 0.07f;
        if (rot < minAngle)
            rot = minAngle;
    }
    if (keys[GLFW_KEY_L])
    {
        rot += 0.07f;
        if (rot > maxAngle)
            rot = maxAngle;
    }
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = true;
        else if (action == GLFW_RELEASE)
            keys[key] = false;
    }

    // Alternar entre luz cálida y fría con la tecla P
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        useWarmLight = !useWarmLight;
    }
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Invertido
    lastX = xPos;
    lastY = yPos;
    camera.ProcessMouseMovement(xOffset, yOffset);
}
