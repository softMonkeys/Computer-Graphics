/*
 * Program.cpp
 *
 *  Created on: Sep 10, 2018
 *      Author: John Hall
 */

#include "Program.h"

#include <iostream>
#include <string>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "RenderingEngine.h"
#include "Scene.h"
#include <math.h>

Program::Program() {
	setupWindow();
}

Program::~Program() {
	//Must be cleaned up in the destructor because these are allocated to the heap
	delete renderingEngine;
	delete scene;
}

void Program::start() {
	renderingEngine = new RenderingEngine();
	scene = new Scene(renderingEngine);

	//Main render loop
	while(!glfwWindowShouldClose(window)) {
		scene->displayScene();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

}

void Program::setupWindow() {
	//Initialize the GLFW windowing system
	if (!glfwInit()) {
		std::cout << "ERROR: GLFW failed to initialize, TERMINATING" << std::endl;
		return;
	}

	//Set the custom error callback function
	//Errors will be printed to the console
	glfwSetErrorCallback(ErrorCallback);

	//Attempt to create a window with an OpenGL 4.1 core profile context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int width = 512;
	int height = 512;
	window = glfwCreateWindow(width, height, "CPSC 453 Assignment #2", 0, 0);
	if (!window) {
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}

	glfwSetMouseButtonCallback(window, mouse_button_callback);

	glfwSetCursorPosCallback(window, cursor_position_callback);

	glfwSetScrollCallback(window, scroll_callback);

	// So that we can access this object on key callbacks ..
	glfwSetWindowUserPointer(window, this);

	//Set the custom function that tracks key presses
	glfwSetKeyCallback(window, KeyCallback);

	//Bring the new window to the foreground (not strictly necessary but convenient)
	glfwMakeContextCurrent(window);

	//Intialize GLAD (finds appropriate OpenGL configuration for your system)
	if (!gladLoadGL()) {
		std::cout << "GLAD init failed" << std::endl;
		return;
	}

	//Query and print out information about our OpenGL environment
	QueryGLVersion();
}



void Program::QueryGLVersion() {
	// query opengl version and renderer information
	std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
	std::string glslver = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

	std::cout << "OpenGL [ " << version << " ] "
		<< "with GLSL [ " << glslver << " ] "
		<< "on renderer [ " << renderer << " ]" << std::endl;
}

void ErrorCallback(int error, const char* description) {
	std::cout << "GLFW ERROR " << error << ":" << std::endl;
	std::cout << description << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Program* program = (Program*)glfwGetWindowUserPointer(window);
	//Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		std::cout << "GLFW: ESCAPE PRESSED" << std::endl;
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if(key == GLFW_KEY_1 && action == GLFW_PRESS){
		program -> getScene() -> setPicture("image1-mandrill.png");
		program -> setzoom(1);
		program -> setx(0);
		program -> sety(0);
		program -> setdegree(0.0f);
		program -> getScene() -> imageTransformation(program -> getx(), program -> gety(), program -> getScene() -> getPicture(), program -> getzoom(), program -> getdegree());
		program -> setchecker(0);
		std::cout << "GLFW: KEY_1 PRESSED" << std::endl;
	}

	if(key == GLFW_KEY_2 && action == GLFW_PRESS){
		program -> getScene() -> setPicture("image2-uclogo.png");
		program -> setzoom(1);
		program -> setx(0);
		program -> sety(0);
		program -> setdegree(0.0f);
		program -> getScene() -> imageTransformation(program -> getx(), program -> gety(), program -> getScene() -> getPicture(), program -> getzoom(), program -> getdegree());
		program -> setchecker(0);
		std::cout << "GLFW: KEY_2 PRESSED" << std::endl;
	}

	if(key == GLFW_KEY_3 && action == GLFW_PRESS){
		program -> getScene() -> setPicture("image3-aerial.jpg");
		program -> setzoom(1);
		program -> setx(0);
		program -> sety(0);
		program -> setdegree(0.0f);
		program -> getScene() -> imageTransformation(program -> getx(), program -> gety(), program -> getScene() -> getPicture(), program -> getzoom(), program -> getdegree());
		program -> setchecker(0);
		std::cout << "GLFW: KEY_3 PRESSED" << std::endl;
	}

	if(key == GLFW_KEY_4 && action == GLFW_PRESS){
		program -> getScene() -> setPicture("image4-thirsk.jpg");
		program -> setzoom(1);
		program -> setx(0);
		program -> sety(0);
		program -> setdegree(0.0f);
		program -> getScene() -> imageTransformation(program -> getx(), program -> gety(), program -> getScene() -> getPicture(), program -> getzoom(), program -> getdegree());
		program -> setchecker(0);
		std::cout << "GLFW: KEY_4 PRESSED" << std::endl;
	}

	if(key == GLFW_KEY_5 && action == GLFW_PRESS){
		program -> getScene() -> setPicture("image5-pattern.png");
		program -> setzoom(1);
		program -> setx(0);
		program -> sety(0);
		program -> setdegree(0.0f);
		program -> getScene() -> imageTransformation(program -> getx(), program -> gety(), program -> getScene() -> getPicture(), program -> getzoom(), program -> getdegree());
		program -> setchecker(0);
		std::cout << "GLFW: KEY_5 PRESSED" << std::endl;
	}

	if(key == GLFW_KEY_6 && action == GLFW_PRESS){
		program -> getScene() -> setPicture("image6-bubble.png");
		program -> setzoom(1);
		program -> setx(0);
		program -> sety(0);
		program -> setdegree(0.0f);
		program -> getScene() -> imageTransformation(program -> getx(), program -> gety(), program -> getScene() -> getPicture(), program -> getzoom(), program -> getdegree());
		program -> setchecker(0);
		std::cout << "GLFW: KEY_6 PRESSED" << std::endl;
	}

	if(key == GLFW_KEY_7 && action == GLFW_PRESS){
		program -> getScene() -> setPicture("Globe.png");
		program -> setzoom(1);
		program -> setx(0);
		program -> sety(0);
		program -> setdegree(0.0f);
		program -> getScene() -> imageTransformation(program -> getx(), program -> gety(), program -> getScene() -> getPicture(), program -> getzoom(), program -> getdegree());
		program -> setchecker(0);
		std::cout << "GLFW: KEY_7 PRESSED" << std::endl;
	}

	// Rotate counter-clockwise
	if(key == GLFW_KEY_LEFT && action == GLFW_PRESS){
		if(program -> getchecker() == 1){
			program -> getScene() -> setPicture("image1-mandrill.png");
			program -> setchecker(0);
		}
		program -> setdegree(program -> getdegree() + (M_PI / 9.0f));
/*
		double xpos = program -> getx();
		double ypos = program -> gety();
		double degree = program -> getdegree();
		program -> setx(xpos = cos(degree) * ((xpos - 256.0f) / 256.0f) - sin(degree) * ((ypos - 256.0f) / -256.0f));
		program -> sety(ypos = sin(degree) * ((xpos - 256.0f) / 256.0f) + cos(degree) * ((ypos - 256.0f) / -256.0f));
*/
		program -> getScene() -> imageTransformation(program -> getx(), program -> gety(), program -> getScene() -> getPicture(), program -> getzoom(), program -> getdegree());
	}

	// Rotate clockwise
	if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
		if(program -> getchecker() == 1){
			program -> getScene() -> setPicture("image1-mandrill.png");
			program -> setchecker(0);
		}
		program -> setdegree(program -> getdegree() - (M_PI / 9.0f));
		program -> getScene() -> imageTransformation(program -> getx(), program -> gety(), program -> getScene() -> getPicture(), program -> getzoom(), program -> getdegree());
	}

	glUseProgram(program->renderingEngine->shaderProgram);

	if(key == GLFW_KEY_A && action == GLFW_PRESS){
		std::cout << "GLFW: KEY_A PRESSED" << std::endl;
		GLuint Location1 = glGetUniformLocation(program->renderingEngine->shaderProgram, "effects");
		//Load texture unit number into uniform
		glUniform1i(Location1, 1);
	}

	if(key == GLFW_KEY_S && action == GLFW_PRESS){
		std::cout << "GLFW: KEY_S PRESSED" << std::endl;
		GLuint Location2 = glGetUniformLocation(program->renderingEngine->shaderProgram, "effects");
		//Load texture unit number into uniform
		glUniform1i(Location2, 2);
	}

	if(key == GLFW_KEY_D && action == GLFW_PRESS){
		std::cout << "GLFW: KEY_D PRESSED" << std::endl;
		GLuint Location3 = glGetUniformLocation(program->renderingEngine->shaderProgram, "effects");
		//Load texture unit number into uniform
		glUniform1i(Location3, 3);
	}

	if(key == GLFW_KEY_F && action == GLFW_PRESS){
		std::cout << "GLFW: KEY_F PRESSED" << std::endl;
		GLuint Location4 = glGetUniformLocation(program->renderingEngine->shaderProgram, "effects");
		//Load texture unit number into uniform
		glUniform1i(Location4, 4);
	}

	if(key == GLFW_KEY_G && action == GLFW_PRESS){
		std::cout << "GLFW: KEY_G PRESSED" << std::endl;
		GLuint Location5 = glGetUniformLocation(program->renderingEngine->shaderProgram, "effects");
		//Load texture unit number into uniform
		glUniform1i(Location5, 0);
	}

	if(key == GLFW_KEY_Z && action == GLFW_PRESS){
		std::cout << "GLFW: KEY_Z PRESSED" << std::endl;
		GLuint Location6 = glGetUniformLocation(program->renderingEngine->shaderProgram, "effects");
		//Load texture unit number into uniform
		glUniform1i(Location6, 5);
	}

	if(key == GLFW_KEY_X && action == GLFW_PRESS){
		std::cout << "GLFW: KEY_X PRESSED" << std::endl;
		GLuint Location7 = glGetUniformLocation(program->renderingEngine->shaderProgram, "effects");
		//Load texture unit number into uniform
		glUniform1i(Location7, 6);
	}

	if(key == GLFW_KEY_C && action == GLFW_PRESS){
		std::cout << "GLFW: KEY_C PRESSED" << std::endl;
		GLuint Location8 = glGetUniformLocation(program->renderingEngine->shaderProgram, "effects");
		//Load texture unit number into uniform
		glUniform1i(Location8, 7);
	}

	if(key == GLFW_KEY_V && action == GLFW_PRESS){
		std::cout << "GLFW: KEY_V PRESSED" << std::endl;
		GLuint Location9 = glGetUniformLocation(program->renderingEngine->shaderProgram, "effects");
		//Load texture unit number into uniform
		glUniform1i(Location9, 8);
	}

	if(key == GLFW_KEY_B && action == GLFW_PRESS){
		std::cout << "GLFW: KEY_B PRESSED" << std::endl;
		GLuint Location10 = glGetUniformLocation(program->renderingEngine->shaderProgram, "effects");
		//Load texture unit number into uniform
		glUniform1i(Location10, 9);
	}

	if(key == GLFW_KEY_N && action == GLFW_PRESS){
		std::cout << "GLFW: KEY_N PRESSED" << std::endl;
		GLuint Location11 = glGetUniformLocation(program->renderingEngine->shaderProgram, "effects");
		//Load texture unit number into uniform
		glUniform1i(Location11, 10);
	}



}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
	Program* program = (Program*)glfwGetWindowUserPointer(window);
	if(program -> getpressOrRelease() == 1){
		// normalization
		program -> setx(xpos = (xpos - 256.0f) / 256.0f);
		program -> sety(ypos = (ypos - 256.0f) / -256.0f);
		// if it is the first time that the program is been run, we set the mandrill as the first picture to display
		if(program -> getchecker() == 1){
			program -> getScene() -> setPicture("image1-mandrill.png");
			program -> setchecker(0);
		}
		program -> getScene() -> imageTransformation(program -> getx(), program -> gety(), program -> getScene() -> getPicture(), program -> getzoom(), program -> getdegree());
		// std::cout << "x " << xpos << " y: " << ypos << std::endl;
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	Program* program = (Program*)glfwGetWindowUserPointer(window);
	if(action == GLFW_PRESS){
		program -> setpressOrRelease(1);
		std::cout << "mouse pressed" << std::endl;
	}else if(action == GLFW_RELEASE){
		program -> setpressOrRelease(0);
		std::cout << "mouse release" << std::endl;
	}

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	Program* program = (Program*)glfwGetWindowUserPointer(window);
	if(yoffset == 1){
		program -> setzoom(program -> getzoom() + 0.1f);
	}else if(yoffset == -1){
		if(program -> getzoom() - 0.1f > 0.1f){
			program -> setzoom(program -> getzoom() - 0.1f);
		}
	}
	if(program -> getchecker() == 1){
		program -> getScene() -> setPicture("image1-mandrill.png");
		program -> setchecker(0);
	}
	program -> getScene() -> imageTransformation(program -> getx(), program -> gety(), program -> getScene() -> getPicture(), program -> getzoom(), program -> getdegree());
	std::cout << program -> getzoom() << std::endl;

}
