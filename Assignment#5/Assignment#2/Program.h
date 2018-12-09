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
class GLFWwindow;
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

	Scene* getScene(){
		return scene;
	}

	void setpressOrRelease(int value){
		pressOrRelease = value;
	}

	int getpressOrRelease(){
		return pressOrRelease;
	}

	void setchecker(int value){
		checker = value;
	}

	int getchecker(){
		return checker;
	}

	void setzoom(float value){
		zoom = value;
	}

	float getzoom(){
		return zoom;
	}

	void setx(float value){
		x = value;
	}

	float getx(){
		return x;
	}

	void sety(float value){
		y = value;
	}

	float gety(){
		return y;
	}

	void setdegree(float value){
		degree = value;
	}

	float getdegree(){
		return degree;
	}
	RenderingEngine* renderingEngine;

private:
	int pressOrRelease;	// 1 - pressed    0 - released
	int checker = 1;	// checks if it is the first time open
						// 1 - first time	0 - runned
	float zoom = 1.0f;		// increment whenever scroll up
						// decrement whenever scroll down
	float x = 0.0f;
	float y = 0.0f;

	float degree = 0.0f;	// degree for rotation

	GLFWwindow* window;

	Scene* scene;

};

//Functions passed to GLFW to handle errors and keyboard input
//Note, GLFW requires them to not be member functions of a class
void ErrorCallback(int error, const char* description);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

#endif /* PROGRAM_H_ */
