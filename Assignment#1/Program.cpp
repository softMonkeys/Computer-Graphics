/*
 * Program.cpp
 *
 *  Created on: Sep 10, 2018
 *      Author: John Hall
 *      Modified by BenKun Chen
 */

#include "Program.h"

#include <iostream>
#include <string>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "RenderingEngine.h"
#include "Scene.h"


#define GLFW_KEY_SPACE 32


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
	window = glfwCreateWindow(width, height, "CPSC 453 OpenGL Assignment#1", 0, 0);
	if (!window) {
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}

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
	//Key codes are often prefixed with GLFW_KEY_ and can be found on the GLFW website
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		std::cout << "GLFW: ESCAPE PRESSED" << std::endl;
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	Program* program = (Program*)glfwGetWindowUserPointer(window);

	// Part I: Squares & Diamonds
	if(key == GLFW_KEY_1 && action == GLFW_PRESS){
		program->getScene()->iteration = 1;
		program->getScene()->changeToSquareScene(program->getScene()->iteration);
	}

	// Part II: Parametric Spiral
	if(key == GLFW_KEY_2 && action == GLFW_PRESS){
		program->getScene()->iteration = 1;
		program->getScene()->changeToSpiralScene(program->getScene()->iteration);
	}

	// Part III: Sierpinski Triangle or 2D Merger Sponge
	if(key == GLFW_KEY_3 && action == GLFW_PRESS){
		program->getScene()->iteration = 1;
		program->getScene()->changeToSierpinskiTriangleScene(0.0, 0.639230485, -0.6, -0.4, 0.6, -0.4, program->getScene()->iteration, 1);
	}

	// Part IV: Sierpinski Triangle Reloaded
	if(key == GLFW_KEY_4 && action == GLFW_PRESS){
		program->getScene()->iteration = 200;
		program->getScene()->changeToSierpinskiTriangleReloadedScene(program->getScene()->iteration);
	}


	// Iteration Up
	if(key == GLFW_KEY_UP && action == GLFW_PRESS){
			program->getScene()->iterationUp();
	}

	// Iteration Down
	if(key == GLFW_KEY_DOWN && action == GLFW_PRESS){
			program->getScene()->iterationDown();
	}

}
