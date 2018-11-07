/*
 * Scene.cpp
 *
 *  Created on: Sep 10, 2018
 *  Author: John Hall
 *  Modified by: BenKun Chen
 */

#include "Scene.h"

#include <iostream>
#include <math.h>
#include <list>
#include "RenderingEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {
	changeToSquareScene(iteration);
}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}

// Part I: Squares & Diamonds
void Scene::changeToSquareScene(int iteration){
	sceneType = "SQUARE_SCENE";

	objects.clear();

	float side = 1.2;	// side length of the outtermost square

	for(int i = 0; i < iteration; i++){
		// Create a single square, by initializing 4 vertices
		Geometry square;
		square.verts.push_back(glm::vec3(-side/2, side/2, 1.0f));
		square.verts.push_back(glm::vec3(side/2, side/2, 1.0f));
		square.verts.push_back(glm::vec3(side/2, -side/2, 1.0f));
		square.verts.push_back(glm::vec3(-side/2, -side/2, 1.0f));

		//Colors are stored per vertex in the order of the vertices
		square.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		square.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		square.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));
		square.colors.push_back(glm::vec3(1.0f, 1.0f, 1.0f));

		square.drawMode = GL_LINE_LOOP;

		//Construct vao and vbos for the square
		RenderingEngine::assignBuffers(square);

		//Send the square data to the GPU
		//Must be done every time the square is modified in any way, ex. verts, colors, normals, uvs, etc.
		RenderingEngine::setBufferData(square);

		//Add the square to the scene objects
		objects.push_back(square);



		// Create a single diamond, by initializing 4 vertices
		Geometry diamond;
		diamond.verts.push_back(glm::vec3(-side/2, 0.0f, 1.0f));
		diamond.verts.push_back(glm::vec3(0.0f, side/2, 1.0f));
		diamond.verts.push_back(glm::vec3(side/2, 0.0f, 1.0f));
		diamond.verts.push_back(glm::vec3(0.0, -side/2, 1.0f));

		diamond.colors.push_back(glm::vec3(0.474f, 0.776f, 0.964f));
		diamond.colors.push_back(glm::vec3(0.474f, 0.776f, 0.964f));
		diamond.colors.push_back(glm::vec3(0.474f, 0.776f, 0.964f));
		diamond.colors.push_back(glm::vec3(0.474f, 0.776f, 0.964f));

		diamond.drawMode = GL_LINE_LOOP;

		//Construct vao and vbos for the diamond
		RenderingEngine::assignBuffers(diamond);

		//Send the triangle data to the GPU
		//Must be done every time the diamond is modified in any way, ex. verts, colors, normals, uvs, etc.
		RenderingEngine::setBufferData(diamond);

		//Add the diamond to the scene objects
		objects.push_back(diamond);

		// The side length of the square in the next level is 1/2 of side length of the current square
		side = side / 2;
	}


}

// Part II: Parametric Spiral
void Scene::changeToSpiralScene(int iteration){
	sceneType = "SPIRAL_SCENE";

	objects.clear();

	Geometry spiral;
	int numSegments = 100;
	float du = 2 * M_PI / numSegments;		// calculate the number of angles
	float color = 0.0;		// color variable for smooth transitions to a different color at the edge
	float increment = 1.0f / (((iteration + 1) * 2 * M_PI) / du);
	for(float u = 0; u < (iteration + 1) * 2 * M_PI; u = u + du){
		spiral.verts.push_back(glm::vec3(0.02 * u * cos(-u), 0.02 * u * sin(-u), 1.0));
		spiral.colors.push_back(glm::vec3(0.0f, 0.0f, color));
		color = color + increment;		// smooth transitions to a different color at the edge
	}

	spiral.drawMode = GL_LINE_STRIP;

	//Construct vao and vbos for the spiral
	RenderingEngine::assignBuffers(spiral);

	//Send the triangle data to the GPU
	//Must be done every time the spiral is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(spiral);

	//Add the spiral to the scene objects
	objects.push_back(spiral);
}

// Part III: Sierpinski Triangle or 2D Merger Sponge
void Scene::changeToSierpinskiTriangleScene(float x_0, float y_0, float x_1, float y_1, float x_2, float y_2, int iteration, int flag){
	sceneType = "SIERPINSKI_SCENE";

	// set the flag to only clear the object in the beginning
	if(flag == 1){
		objects.clear();
		flag = 0;
	}

	//Create a single triangle
	//Additional triangles can be created by pushing groups of three more vertices into the verts vector
	Geometry equalTriangle;


	// temp variables to keep track of the vertice from the previous iteration
	float temp_x = x_1;
	float temp_y = y_2;
	float side = (x_2 - x_1);
	float height = sin(1.047197551) * side;
	float heightSmall = height / 2.0f;

	equalTriangle.verts.push_back(glm::vec3(x_1, y_1, 1.0f));
	equalTriangle.verts.push_back(glm::vec3(x_2, y_2, 1.0f));
	equalTriangle.verts.push_back(glm::vec3(x_0, y_0, 1.0f));

	//Colors are stored per vertex in the order of the vertices
	equalTriangle.colors.push_back(glm::vec3(0.2f, 0.19f, 0.19f));
	equalTriangle.colors.push_back(glm::vec3(0.2f, 0.19f, 0.19f));
	equalTriangle.colors.push_back(glm::vec3(0.2f, 0.19f, 0.19f));

	// CALCULATE VERTICES FOR ALL THREE TRIANGLES
	equalTriangle.verts.push_back(glm::vec3(temp_x + (side / 4.0f), temp_y + heightSmall, 1.0f));
	equalTriangle.verts.push_back(glm::vec3(x_2 - (side / 4.0f), y_2 + heightSmall, 1.0f));
	equalTriangle.verts.push_back(glm::vec3(x_0, y_0, 1.0f));

	equalTriangle.verts.push_back(glm::vec3(temp_x, temp_y, 1.0f));
	equalTriangle.verts.push_back(glm::vec3(x_2 - (side / 2.0f), y_2, 1.0f));
	equalTriangle.verts.push_back(glm::vec3(x_0 - (side / 4.0f), y_0 - heightSmall, 1.0f));

	equalTriangle.verts.push_back(glm::vec3(temp_x + (side / 2.0f), temp_y, 1.0f));
	equalTriangle.verts.push_back(glm::vec3(x_2, y_2, 1.0f));
	equalTriangle.verts.push_back(glm::vec3(x_0 + (side / 4.0f), y_0 - heightSmall, 1.0f));

	//Colors are stored per vertex in the order of the vertices
	equalTriangle.colors.push_back(glm::vec3(0.07f, 0.0f, 0.5f));
	equalTriangle.colors.push_back(glm::vec3(0.07f, 0.0f, 0.5f));
	equalTriangle.colors.push_back(glm::vec3(0.07f, 0.0f, 0.5f));

	//Colors are stored per vertex in the order of the vertices
	equalTriangle.colors.push_back(glm::vec3(0.49f, 0.0f, 0.01f));
	equalTriangle.colors.push_back(glm::vec3(0.49f, 0.0f, 0.01f));
	equalTriangle.colors.push_back(glm::vec3(0.49f, 0.0f, 0.01f));

	//Colors are stored per vertex in the order of the vertices
	equalTriangle.colors.push_back(glm::vec3(0.0f, 0.33f, 0.08f));
	equalTriangle.colors.push_back(glm::vec3(0.0f, 0.33f, 0.08f));
	equalTriangle.colors.push_back(glm::vec3(0.0f, 0.33f, 0.08f));


	equalTriangle.drawMode = GL_TRIANGLES;

	//Construct vao and vbos for the spiral
	RenderingEngine::assignBuffers(equalTriangle);

	//Send the triangle data to the GPU
	//Must be done every time the spiral is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(equalTriangle);

	//Add the spiral to the scene objects
	objects.push_back(equalTriangle);


	// Recursion
	if(iteration - 1 != 0){
		iteration = iteration - 1;
		changeToSierpinskiTriangleScene(x_0, y_0, temp_x + (side / 4.0f), temp_y + heightSmall, x_2 - (side / 4.0f), y_2 + heightSmall, iteration, 0);
		changeToSierpinskiTriangleScene(x_0 - (side / 4.0f), y_0 - heightSmall, temp_x, temp_y, x_2 - (side / 2.0f), y_2, iteration, 0);
		changeToSierpinskiTriangleScene(x_0 + (side / 4.0f), y_0 - heightSmall, temp_x + (side / 2.0f), temp_y, x_2, y_2, iteration, 0);
	}


}


// Part IV: Sierpinski Triangle Reloaded
void Scene::changeToSierpinskiTriangleReloadedScene(int iteration){
	sceneType = "SIERPINSKI_RELOAD_SCENE";

	objects.clear();

	//Create a single triangle
	//Additional triangles can be created by pushing groups of three more vertices into the verts vector
	Geometry sierpiinskiTriangleReloaded;

	// create variables for the initial three vertices
	float x_0 = 0.0;
	float y_0 = 0.6;
	float x_1 = -0.6;
	float y_1 = -0.4;
	float x_2 = 0.6;
	float y_2 = -0.4;
	// temp variables to keep track of the vertice from the previous iteration
	float temp_x = x_0;
	float temp_y = y_0;
	sierpiinskiTriangleReloaded.verts.push_back(glm::vec3(x_0, y_0, 1.0f));
	sierpiinskiTriangleReloaded.verts.push_back(glm::vec3(x_1, y_1, 1.0f));
	sierpiinskiTriangleReloaded.verts.push_back(glm::vec3(x_2, y_2, 1.0f));

	//Colors are stored per vertex in the order of the vertices
	sierpiinskiTriangleReloaded.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	sierpiinskiTriangleReloaded.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	sierpiinskiTriangleReloaded.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

	for(int i = 0; i < iteration; i++){
		int random = std::rand() % (3);		// generates a random number among 3 numbers: 0, 1, 2
		if(random == 0){		// if the top vertice is choosen, calcualte the vertice in between the vertice and the previous vertice
			temp_x = (temp_x + x_1) / 2;
			temp_y = (temp_y + y_1) / 2;
			sierpiinskiTriangleReloaded.verts.push_back(glm::vec3(temp_x, temp_y, 1.0f));
			sierpiinskiTriangleReloaded.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
		}else if(random == 1){		// if the bottom left vertice is choosen, calcualte the vertice in between the vertice and the previous vertice
			temp_x = (temp_x + x_2) / 2;
			temp_y = (temp_y + y_2) / 2;
			sierpiinskiTriangleReloaded.verts.push_back(glm::vec3(temp_x, temp_y, 1.0f));
			sierpiinskiTriangleReloaded.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

		}else if(random == 2){		// if the bottom right is choosen, calcualte the vertice in between the vertice and the previous vertice
			temp_x = (temp_x + x_0) / 2;
			temp_y = (temp_y + y_0) / 2;
			sierpiinskiTriangleReloaded.verts.push_back(glm::vec3(temp_x, temp_y, 1.0f));
			sierpiinskiTriangleReloaded.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		}
	}


	sierpiinskiTriangleReloaded.drawMode = GL_POINTS;

	//Construct vao and vbos for the spiral
	RenderingEngine::assignBuffers(sierpiinskiTriangleReloaded);

	//Send the triangle data to the GPU
	//Must be done every time the spiral is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(sierpiinskiTriangleReloaded);

	//Add the spiral to the scene objects
	objects.push_back(sierpiinskiTriangleReloaded);
}

void Scene::iterationUp(){
	if(sceneType == "SQUARE_SCENE"){
		iteration = iteration + 1;
		changeToSquareScene(iteration);
		std::cout << "up for square" << std::endl;
	} else if(sceneType == "SPIRAL_SCENE"){
		iteration = iteration + 1;
		changeToSpiralScene(iteration);
		std::cout << "up for spiral" << std::endl;
	} else if (sceneType == "SIERPINSKI_SCENE"){
		iteration = iteration + 1;
		changeToSierpinskiTriangleScene(0.0, 0.639230485, -0.6, -0.4, 0.6, -0.4, iteration, 1);
		std::cout << "up for sierpinski triangle" << std::endl;
	} else if(sceneType == "SIERPINSKI_RELOAD_SCENE"){
		iteration = iteration + 200;
		changeToSierpinskiTriangleReloadedScene(iteration);
		std::cout << "up for sierpinski reloaded triangle" << std::endl;
	}
}

void Scene::iterationDown(){
	if(sceneType == "SQUARE_SCENE"){
		if(iteration - 1 != 0){
			iteration = iteration - 1;
		}
		changeToSquareScene(iteration);
		std::cout << "down for square" << std::endl;
	} else if(sceneType == "SPIRAL_SCENE"){
		if(iteration - 1 != 0){
			iteration = iteration - 1;
		}
		changeToSpiralScene(iteration);
		std::cout << "down for spiral" << std::endl;
	} else if(sceneType == "SIERPINSKI_SCENE"){
		if(iteration - 1 != 0){
			iteration = iteration - 1;
		}
		changeToSierpinskiTriangleScene(0.0, 0.639230485, -0.6, -0.4, 0.6, -0.4, iteration, 1);
		std::cout << "down for sierpinski triangle" << std::endl;
	}else if(sceneType == "SIERPINSKI_RELOAD_SCENE"){
		if(iteration - 200 != 0){
			iteration = iteration - 200;
		}
		changeToSierpinskiTriangleReloadedScene(iteration);
		std::cout << "down for sierpinski reloaded triangle" << std::endl;
	}
}

