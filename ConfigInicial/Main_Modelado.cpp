//Osorio Angeles Rodrigo Jafet --Practica 04--
//318008893
#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);

const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Osorio Angeles Rodrigo Jafet 318008893  ---Modelado geometrico---", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificaci�n de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers

	// use with Perspective Projection
	//componentes del cubo en x, y, z -> el color de la cara en RGB R,G,B
	//Para la creaci�n de un cubo, son necesarios 6 v�rtices, por lo que se tienen 2 tri�ngulos por cada cara. 
	float vertices[] = {

		//Color azul claro [0]
		-0.5f, -0.5f, 0.5f, 0.4f, 0.7608f,0.9137f,//Front
		0.5f, -0.5f, 0.5f,  0.4f, 0.7608f,0.9137f,
		0.5f,  0.5f, 0.5f,  0.4f, 0.7608f,0.9137f,
		0.5f,  0.5f, 0.5f,  0.4f, 0.7608f,0.9137f,
		-0.5f,  0.5f, 0.5f, 0.4f, 0.7608f,0.9137f,
		-0.5f, -0.5f, 0.5f, 0.4f, 0.7608f,0.9137f,
		//cara de atr�s black
		-0.5f, -0.5f,-0.5f, 0.4f, 0.7608f,0.9137f,
		 0.5f, -0.5f,-0.5f, 0.4f, 0.7608f,0.9137f,
		 0.5f,  0.5f,-0.5f, 0.4f, 0.7608f,0.9137f,
		 0.5f,  0.5f,-0.5f, 0.4f, 0.7608f,0.9137f,
		-0.5f,  0.5f,-0.5f, 0.4f, 0.7608f,0.9137f,
		-0.5f, -0.5f,-0.5f, 0.4f, 0.7608f,0.9137f,
		// Cara derecha
		 0.5f, -0.5f,  0.5f,  0.4f, 0.7608f,0.9137f,
		 0.5f, -0.5f, -0.5f,  0.4f, 0.7608f,0.9137f,
		 0.5f,  0.5f, -0.5f,  0.4f, 0.7608f,0.9137f,
		 0.5f,  0.5f, -0.5f,  0.4f, 0.7608f,0.9137f,
		 0.5f,  0.5f,  0.5f,  0.4f, 0.7608f,0.9137f,
		 0.5f,  -0.5f, 0.5f,  0.4f, 0.7608f,0.9137f,
		 // Cara izquierda
		-0.5f,  0.5f,  0.5f,  0.4f, 0.7608f,0.9137f,
		-0.5f,  0.5f, -0.5f,  0.4f, 0.7608f,0.9137f,
		-0.5f, -0.5f, -0.5f,  0.4f, 0.7608f,0.9137f,
		-0.5f, -0.5f, -0.5f,  0.4f, 0.7608f,0.9137f,
		-0.5f, -0.5f,  0.5f,  0.4f, 0.7608f,0.9137f,
		-0.5f,  0.5f,  0.5f,  0.4f, 0.7608f,0.9137f,

		-0.5f, -0.5f, -0.5f, 0.4f, 0.7608f,0.9137f,
		0.5f, -0.5f, -0.5f,  0.4f, 0.7608f,0.9137f,
		0.5f, -0.5f,  0.5f,  0.4f, 0.7608f,0.9137f,
		0.5f, -0.5f,  0.5f,  0.4f, 0.7608f,0.9137f,
		-0.5f, -0.5f,  0.5f, 0.4f, 0.7608f,0.9137f,
		-0.5f, -0.5f, -0.5f, 0.4f, 0.7608f,0.9137f,

		-0.5f,  0.5f, -0.5f, 0.4f, 0.7608f,0.9137f,
		0.5f,  0.5f, -0.5f,  0.4f, 0.7608f,0.9137f,
		0.5f,  0.5f,  0.5f,  0.4f, 0.7608f,0.9137f,
		0.5f,  0.5f,  0.5f,  0.4f, 0.7608f,0.9137f,
		-0.5f,  0.5f,  0.5f, 0.4f, 0.7608f,0.9137f,
		-0.5f,  0.5f, -0.5f, 0.4f, 0.7608f,0.9137f,

		//Color blanco cremoso [36]
		-0.5f, -0.5f, 0.5f, 0.8706f, 0.8431f,0.7725f,//Front
		0.5f, -0.5f, 0.5f,  0.8706f, 0.8431f,0.7725f,
		0.5f,  0.5f, 0.5f,  0.8706f, 0.8431f,0.7725f,
		-0.5f,  0.5f, 0.5f, 0.8706f, 0.8431f,0.7725f,
		0.5f,  0.5f, 0.5f,  0.8706f, 0.8431f,0.7725f,
		-0.5f, -0.5f, 0.5f, 0.8706f, 0.8431f,0.7725f,

		-0.5f, -0.5f,-0.5f, 0.8706f, 0.8431f,0.7725f,//Back
		 0.5f, -0.5f,-0.5f, 0.8706f, 0.8431f,0.7725f,
		 0.5f,  0.5f,-0.5f, 0.8706f, 0.8431f,0.7725f,
		 0.5f,  0.5f,-0.5f, 0.8706f, 0.8431f,0.7725f,
		-0.5f,  0.5f,-0.5f, 0.8706f, 0.8431f,0.7725f,
		-0.5f, -0.5f,-0.5f, 0.8706f, 0.8431f, 0.7725f,

		 0.5f, -0.5f,  0.5f, 0.8706f, 0.8431f, 0.7725f,
		 0.5f, -0.5f, -0.5f, 0.8706f, 0.8431f, 0.7725f,
		 0.5f,  0.5f, -0.5f, 0.8706f, 0.8431f, 0.7725f,
		 0.5f,  0.5f, -0.5f, 0.8706f, 0.8431f, 0.7725f,
		 0.5f,  0.5f,  0.5f, 0.8706f, 0.8431f, 0.7725f,
		 0.5f,  -0.5f, 0.5f, 0.8706f, 0.8431f, 0.7725f,

		-0.5f,  0.5f,  0.5f, 0.8706f, 0.8431f, 0.7725f,
		-0.5f,  0.5f, -0.5f, 0.8706f, 0.8431f, 0.7725f,
		-0.5f, -0.5f, -0.5f, 0.8706f, 0.8431f, 0.7725f,
		-0.5f, -0.5f, -0.5f, 0.8706f, 0.8431f, 0.7725f,
		-0.5f, -0.5f,  0.5f, 0.8706f, 0.8431f, 0.7725f,
		-0.5f,  0.5f,  0.5f, 0.8706f, 0.8431f, 0.7725f,

		-0.5f, -0.5f, -0.5f, 0.8706f, 0.8431f, 0.7725f,
		0.5f, -0.5f, -0.5f,  0.8706f, 0.8431f, 0.7725f,
		0.5f, -0.5f,  0.5f,  0.8706f, 0.8431f, 0.7725f,
		0.5f, -0.5f,  0.5f,  0.8706f, 0.8431f, 0.7725f,
		-0.5f, -0.5f,  0.5f, 0.8706f, 0.8431f, 0.7725f,
		-0.5f, -0.5f, -0.5f, 0.8706f, 0.8431f, 0.7725f,

		-0.5f,  0.5f, -0.5f, 0.8706f, 0.8431f, 0.7725f,
		0.5f,  0.5f, -0.5f,  0.8706f, 0.8431f, 0.7725f,
		0.5f,  0.5f,  0.5f,  0.8706f, 0.8431f, 0.7725f,
		0.5f,  0.5f,  0.5f,  0.8706f, 0.8431f, 0.7725f,
		-0.5f,  0.5f,  0.5f, 0.8706f, 0.8431f, 0.7725f,
		-0.5f,  0.5f, -0.5f, 0.8706f, 0.8431f, 0.7725f,
		
		//Color naranja [72]  0.2706f
		-0.5f, -0.5f, 0.5f, 1.0f, 0.2706f, 0.0f,//Front
		0.5f, -0.5f, 0.5f,  1.0f, 0.2706f, 0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.2706f, 0.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 0.2706f, 0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.2706f, 0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.2706f, 0.0f,

		-0.5f, -0.5f,-0.5f, 1.0f, 0.2706f, 0.0f,//Back
		 0.5f, -0.5f,-0.5f, 1.0f, 0.2706f, 0.0f,
		 0.5f,  0.5f,-0.5f, 1.0f, 0.2706f, 0.0f,
		 0.5f,  0.5f,-0.5f, 1.0f, 0.2706f, 0.0f,
		-0.5f,  0.5f,-0.5f, 1.0f, 0.2706f, 0.0f,
		-0.5f, -0.5f,-0.5f, 1.0f, 0.2706f, 0.0f,

		 0.5f, -0.5f,  0.5f, 1.0f, 0.2706f, 0.0f,
		 0.5f, -0.5f, -0.5f, 1.0f, 0.2706f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.2706f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f, 0.2706f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f, 0.2706f, 0.0f,
		 0.5f,  -0.5f, 0.5f, 1.0f, 0.2706f, 0.0f,

		-0.5f,  0.5f,  0.5f, 1.0f, 0.2706f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2706f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.2706f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.2706f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.2706f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.2706f, 0.0f,

		-0.5f, -0.5f, -0.5f, 1.0f, 0.2706f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.2706f, 0.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 0.2706f, 0.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 0.2706f, 0.0f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.2706f, 0.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.2706f, 0.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 0.2706f, 0.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 0.2706f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 0.2706f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 0.2706f, 0.0f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.2706f, 0.0f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2706f, 0.0f,

		//Negro [108]
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,//Front
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,-0.5f, 0.0f, 0.0f, 0.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,-0.5f, 0.0f, 0.0f, 0.0f,

		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f,

		//Color azul fuerte [144]
		-0.5f, -0.5f, 0.5f, 0.0f, 0.191f,0.255f,//Front
		0.5f, -0.5f, 0.5f,  0.0f, 0.191f,0.255f,
		0.5f,  0.5f, 0.5f,  0.0f, 0.191f,0.255f,
		0.5f,  0.5f, 0.5f,  0.0f, 0.191f,0.255f,
		-0.5f,  0.5f, 0.5f, 0.0f, 0.191f,0.255f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.191f,0.255f,
		//cara de atr�s blac0.0f, 0.191f,0.255f,
		-0.5f, -0.5f,-0.5f, 0.0f, 0.191f,0.255f,
		 0.5f, -0.5f,-0.5f, 0.0f, 0.191f,0.255f,
		 0.5f,  0.5f,-0.5f, 0.0f, 0.191f,0.255f,
		 0.5f,  0.5f,-0.5f, 0.0f, 0.191f, 0.255f,
		-0.5f,  0.5f,-0.5f, 0.0f, 0.191f, 0.255f,
		-0.5f, -0.5f,-0.5f, 0.0f, 0.191f,0.255f,
		// Cara derecha
		 0.5f, -0.5f,  0.5f,  0.0f, 0.191f,0.255f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.191f,0.255f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.191f,0.255f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.191f,0.255f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.191f,0.255f,
		 0.5f,  -0.5f, 0.5f,  0.0f, 0.191f,0.255f,
		 // Cara izquierda
		-0.5f,  0.5f,  0.5f,  0.0f, 0.191f,0.255f,
		-0.5f,  0.5f, -0.5f,  0.0f, 0.191f,0.255f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.191f,0.255f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.191f,0.255f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.191f,0.255f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.191f,0.255f,

		-0.5f, -0.5f, -0.5f, 0.0f, 0.191f,0.255f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.191f,0.255f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.191f,0.255f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.191f,0.255f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.191f,0.255f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.191f,0.255f,

		-0.5f,  0.5f, -0.5f, 0.0f, 0.191f,0.255f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.191f,0.255f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.191f,0.255f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.191f,0.255f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.191f,0.255f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.191f,0.255f,

		//rosa clarito [180]
		-0.5f, -0.5f, 0.5f, 1.0f, 0.7137f, 0.7569f,//Front
		0.5f, -0.5f, 0.5f,  1.0f, 0.7137f, 0.7569f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.7137f, 0.7569f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.7137f, 0.7569f,
		-0.5f,  0.5f, 0.5f, 1.0f, 0.7137f, 0.7569f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.7137f, 0.7569f,
		
	    -0.5f, -0.5f,-0.5f, 1.0f, 0.7137f, 0.7569f,//Back
		 0.5f, -0.5f,-0.5f, 1.0f, 0.7137f, 0.7569f,
		 0.5f,  0.5f,-0.5f, 1.0f, 0.7137f, 0.7569f,
		 0.5f,  0.5f,-0.5f, 1.0f, 0.7137f, 0.7569f,
	    -0.5f,  0.5f,-0.5f, 1.0f, 0.7137f, 0.7569f,
	    -0.5f, -0.5f,-0.5f, 1.0f, 0.7137f, 0.7569f,
		
		 0.5f, -0.5f,  0.5f,  1.0f, 0.7137f, 0.7569f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.7137f, 0.7569f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.7137f, 0.7569f,
		 0.5f,  0.5f, -0.5f,  1.0f, 0.7137f, 0.7569f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.7137f, 0.7569f,
		 0.5f,  -0.5f, 0.5f, 1.0f, 0.7137f, 0.7569f,
      
		-0.5f,  0.5f,  0.5f,  1.0f, 0.7137f, 0.7569f,
		-0.5f,  0.5f, -0.5f,  1.0f, 0.7137f, 0.7569f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.7137f, 0.7569f,
		-0.5f, -0.5f, -0.5f,  1.0f, 0.7137f, 0.7569f,
		-0.5f, -0.5f,  0.5f,  1.0f, 0.7137f, 0.7569f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.7137f, 0.7569f,
		
		-0.5f, -0.5f, -0.5f, 1.0f, 0.7137f, 0.7569f,
		0.5f, -0.5f, -0.5f,  1.0f, 0.7137f, 0.7569f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.7137f, 0.7569f,
		0.5f, -0.5f,  0.5f,  1.0f, 0.7137f, 0.7569f,
		-0.5f, -0.5f,  0.5f, 1.0f, 0.7137f, 0.7569f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.7137f, 0.7569f,
		
		-0.5f,  0.5f, -0.5f, 1.0f, 0.7137f, 0.7569f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.7137f, 0.7569f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.7137f, 0.7569f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.7137f, 0.7569f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.7137f, 0.7569f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.7137f, 0.7569f,
	};


	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	
		//Se manda el valor de las variables de tipo float
		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));


		glBindVertexArray(VAO);
	

		//creaci�n de Squirtle 
		//cuerpo central 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.5f, 0.3f, 0.4f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, -2.4f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.5f, 0.8f, 0.2f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 1.73f, -3.25f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.1f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 10.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.1f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 11.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		//cabeza
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(1.3f, 1.3f, 1.3f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 1.25f, 0.5f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//Chapatas
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-6.05f, 8.05f, 5.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 180, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0.2f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(6.05f, 8.05f, 5.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 180, 36);


		//ojos
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-1.68f, 6.2f, 3.85f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(1.68f, 6.2f, 3.85f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 108, 36);

		//sombrero
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.7f, 0.3f, 0.7f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 8.0f, 0.9f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//boca
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.2f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 3.5f, 6.5f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 36);

		//Nariz
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.2f, 0.15f, 0.2f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 11.0f, 6.5f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 144, 36);

		//caparazon naranja 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.5f, 2.7f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.5f, 2.9f, 0.4f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.5f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.5f, 2.9f, 0.4f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, -0.1f, -4.5f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.5f, 2.9f, 0.4f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, -5.5f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.5f, 1.7f, 0.4f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, -0.5f, -6.5f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 72, 36);

		//parte blanca de caparazon 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.5f, 2.7f, 0.2f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.2f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.5f, 0.2f, 0.6f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, -7.3f, -1.5f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.5f, 0.6f, 0.4f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, -2.8f, -3.5f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.5f, 0.28f, 0.4f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, -6.74f, -4.5f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.5f, 0.3f, 0.6f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, -7.2f, -3.5f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 36, 36);

		//Brazo derecho 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.7f, 1.0f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-1.7f, 0.5f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.7f, 1.0f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-1.7f, 0.0f, 1.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.7f, 1.0f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-1.7f, 0.5f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-2.5f, -0.5f, 2.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//brazo izquierdo

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.7f, 1.0f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(1.7f, 0.5f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.7f, 1.0f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(1.7f, 0.0f, 1.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.7f, 1.0f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(1.7f, 0.5f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(2.5f, -0.5f, 2.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		//pierna derecha 
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 1.5f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-2.5f, -1.0f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-2.5f, -2.0f, -1.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.247f, 0.7f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(-2.5f, -9.625f, 0.141f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//pierna izquierda
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 1.5f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(2.5f, -1.0f, 0.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(2.5f, -2.0f, -1.0f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(0.5f, 0.247f, 0.7f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(2.5f, -9.625f, 0.141f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		//cola
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, -1.2f, -6.1f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, -0.9f, -7.1f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, -0.9f, -8.1f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, -0.9f, -9.1f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f, 0.5f, 0.5f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, -10.1f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2.0f, 0.2f, 0.75f)); //ancho, grosor y profundidad
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, -5.4f));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);



		//Parte final del envio de matrices
		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 /*
 * funci�n void es para manejar la entrada del teclado
 *	if, si esta presionada la tecla esc, se va a cerrar la ventana o termina ejecuci�n
 *	if si se oprime D se suma a la variable movX un valor cte de 0.08
 */

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX += 0.002f;
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX -= 0.002f;
	 if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) //UP
		 movY += 0.002f;
	 if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) //DOWN
		 movY -= 0.002f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ -= 0.002f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ += 0.002f;
	 if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		 rot += 0.015f;
	 if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		 rot -= 0.015f;
 }


