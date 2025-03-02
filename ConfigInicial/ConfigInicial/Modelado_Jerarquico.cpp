//Previo Practica 05, modelado Jerarquico
//Osorio Angeles Rodrigo Jafet 318008893
//02-03-2025


#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);


const GLint WIDTH = 1200, HEIGHT = 800;

//variables para manipular vista
//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;

//Variables para manipular articulaciones
//Manipulacion de modelo, permite la articulación
//For model
float	hombro = 0.0f,
codo = 0.0f,
muneca = 0.0f,
dedo1 = 0.0f,
dedo2 = 0.0f;

int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Osorio Angeles Rodrigo ---Modelado jerarquico---", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

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
	// use with Orthographic Projection


	//para generar vértices, solo se utilizan 3 componentes (x,y,x)
	//el color se manda de otra forma, ya no en esta sección
	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 
		0.5f, -0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		-0.5f,  0.5f, 0.5f, 
		-0.5f, -0.5f, 0.5f, 
		
	    -0.5f, -0.5f,-0.5f, 
		 0.5f, -0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
	    -0.5f,  0.5f,-0.5f, 
	    -0.5f, -0.5f,-0.5f, 
		
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  -0.5f, 0.5f,
      
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f, 
		0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		
		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
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
	

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	glm::vec3 color= glm::vec3(0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		
		//manipular vista y modelo
		//modelTemp y Temp2, controlan la información de la posicion de los elementos
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp


		//se inicializa matriz de vista 
		//View set up 
		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = ourShader.uniformColor;

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	

		glBindVertexArray(VAO);
		
		//se aplica rotación dado por el valor de hombro, aplicado en z
		//se guarda lo de matriz model dentro de la matriz temporal, para generar matriz auxiliar
		//modelTemp, permite generar la movilidad del punto fijo que tiene el hombro
		//El pivote se traslada 1.5 en el eje x antes de comenzar a crear la caja, que si vale 3,
		// entonces al recorrer temp estamos colocando el pivote en el inicio de la caja y no en la mitad
		//Se aplica Scale a la matriz model, para colocar parametros del primer elemento a dibujar
		//La variable color, es un vec3 para generar un color diferente para cada caja creada, tiene RGB 
		//Se manda la información por medio de Uniform
		
		//Model Bicep
		model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f)); //hombro
		modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//A

		//Model Antebrazo
		//obtener la posición que va a tener el nuevo elemento
		//a la matriz temporal se le va a pasar el valor de la traslación
		model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0f, 0.0f));
		//Se realiza una rotación, con una variable para controlar la articulación CODO
		//CODO se tiene que definir en la sección de variales
		model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 1.0f, 0.0f));
		//generar matriz temporal, pasar matriz donde se quiere el elemento
		//Se tiene que considerar la posición del pivote, a partir de la escala del elemento
		modelTemp = model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		//creación del elemento con Scale
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		//Aplicando el color
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//B

		//Model Palma
		//obtener la posición que va a tener el nuevo elemento
		//matriz model antes de escala, checkpoint, para no tener desde el incio la matriz
		model = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.0f));
		//Se realiza una rotación, con una variable para controlar la articulación
		//Muneca se tiene que definir en la sección de variales
		model = glm::rotate(model, glm::radians(muneca), glm::vec3(0.0f, 1.0f, 0.0f));
		//generar matriz temporal, pasar matriz donde se quiere el elemento
		//Se tiene que considerar la posición del pivote, a partir de la escala del elemento
		//Se quiere regresar al valor de la palma, para generar los dedos
		modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//C

		//Model Dedo1 A
		model = glm::translate(modelTemp, glm::vec3(0.25f, 0.35f, 0.375f));
		model = glm::rotate(model, glm::radians(dedo1), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//D

		//Model Dedo2 B
		model = glm::translate(modelTemp, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 0.3f, 0.25f));
		color = glm::vec3(0.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//E




		glBindVertexArray(0);

		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 //controlar movimiento en la ventana 
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
	 //manipuación del hombro
	 if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) //rotate
		 hombro += 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) //
		 hombro -= 0.04f;
	 //manipulación del codo
	 if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) //rotate
		 codo += 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) //
		 codo -= 0.04f;
	 //manipulación de la muñeca
	 if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) //rotate
		 muneca += 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) //
		 muneca -= 0.04f;
	 //manipulación dedo1
	 if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) //rotate
		 dedo1 += 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) //
		 dedo1 -= 0.04f;
	 //manipulación dedo2
	 if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) //rotate
		 dedo2 += 0.04f;
	 if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) //
		 dedo2 -= 0.04f;
 }

