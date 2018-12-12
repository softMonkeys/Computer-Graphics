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
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "RenderingEngine.h"
#include "Scene.h"
#include "Carmera.h"

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
	scene = new Scene(renderingEngine, window);

	Program* p = (Program*)glfwGetWindowUserPointer(window);
	Scene* s = p->getScene();
	s->sun();
	s->earth();
	s->moon();
	s->mars();
	s->mercury();
	s->venus();
	s->jupitor();
	s->milky();


	//Main render loop
	while (!glfwWindowShouldClose(window)) {
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
	int width = 1024;
	int height = 1024;
	window = glfwCreateWindow(width, height, "CPSC 453 OpenGL Boilerplate", 0, 0);
	if (!window) {
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}
	glfwSetWindowUserPointer(window, this);
	//Set the custom function that tracks key presses
	glfwSetKeyCallback(window, KeyCallback);

	//Set the custom function that tracks scroll input
	glfwSetScrollCallback(window, scroll_callback);

	//Set the custom function that tracks mouse input
	glfwSetCursorPosCallback(window, cursor_position_callback);

	//Set the custom function that tracks mouse button input
	glfwSetMouseButtonCallback(window, mouse_button_callback);

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
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	Program* p = (Program*)glfwGetWindowUserPointer(window);
	Scene* s = p->getScene();
	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
		s->cmr.phi_up();
		printf("phi: %f\n", s->cmr.phi);
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		s->cmr.phi_down();
		printf("phi: %f\n", s->cmr.phi);
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		float temp = p->renderingEngine->getSpeed();
		p->renderingEngine->setSpeed(temp + 5.f);
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		float temp = p->renderingEngine->getSpeed();
		if(temp - 5.f > 0.f){
			p->renderingEngine->setSpeed(temp - 5.f);
		}
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		if(p->flag == 0){
			p->store = p->renderingEngine->getSpeed();
			p->renderingEngine->setSpeed(0.f);
			p->flag = 1;
		}else{
			p->renderingEngine->setSpeed(p->store);
			p->flag = 0;
		}

	}
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	Program* p = (Program*)glfwGetWindowUserPointer(window);
	Scene* s = p->getScene();
	if (p->getMouseClicked()) {
		if (xpos - p->lastx > 0.0f) {
			s->cmr.phi_up();
		}else if(xpos - p->lastx < 0.0f){
			s->cmr.phi_down();
		}

		if (ypos - p->lasty > 0.0f) {
			s->cmr.theta_up();
		}else if (ypos - p->lasty < 0.0f){
			s->cmr.theta_down();
		}
		p->lastx = xpos;
		p->lasty = ypos;
	}
}

//Detect if the mouse id clicked or not
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	Program* p = (Program*)glfwGetWindowUserPointer(window);
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		p->setMouseClicked(1);
		// float x, y;
		// glfwGetCursorPos(&x, &y);
	}
	else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		p->setMouseClicked(0);
	}
}

//Detect the scroll
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	Program* p = (Program*)glfwGetWindowUserPointer(window);
	Scene* s = p->getScene();
	if (yoffset == 1.0f) {
		s->cmr.r_up();	// zoom in
	}
	else if (yoffset == -1.0f) {
		s->cmr.r_down();
	}
}
