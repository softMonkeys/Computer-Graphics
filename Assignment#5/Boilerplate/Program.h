/*
* Program.h
*	Base class of a rendering program. Has a scene to render, a rendering engine and a window to render to.
*  Created on: Sep 10, 2018
*  Author: John Hall
*/

#ifndef PROGRAM_H_
#define PROGRAM_H_
//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
struct GLFWwindow;
class RenderingEngine;
class Scene;

class Program {
public:
	Program();
	virtual ~Program();

	//Creates the rendering engine and the scene and does the main draw loop
	void start();

	//Initializes GLFW and creates the window
	void setupWindow();

	//Prints system specs to the console
	void QueryGLVersion();

	Scene* getScene() { return scene; }

	// mouse movement
	void setMouseClicked(int i) {
		mouseClicked = i;
	};

	int getMouseClicked() {
		return mouseClicked;
	};

	float lastx = 0.0f;
	float lasty = 0.0f;

	RenderingEngine* renderingEngine;

	float store;
	int flag = 0;
private:
	GLFWwindow * window;

	Scene* scene;
	int mouseClicked = 0; // 0 - false, 1 - true
};

//Functions passed to GLFW to handle errors and keyboard input
//Note, GLFW requires them to not be member functions of a class
void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

#endif /* PROGRAM_H_ */
