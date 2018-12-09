/*
 * Scene.cpp
 *
 *  Created on: Sep 10, 2018
 *  Author: John Hall
 */

#include "Scene.h"

#include <iostream>

#include "RenderingEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.h"

Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {

	imageTransformation(0.0f, 0.0f, "image1-mandrill.png", 1, 0);		// default screen
	background();

}

void Scene::background(){
		MyTexture texture1;
		InitializeTexture(&texture1, "background3-wood.jpg", GL_TEXTURE_RECTANGLE);

		//Load texture uniform
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//Shaders need to be active to load uniforms
		glUseProgram(renderer->shaderProgram);
		//Set which texture unit the texture is bound to
		glActiveTexture(GL_TEXTURE0);
		//Bind the texture to GL_TEXTURE0
		glBindTexture(GL_TEXTURE_RECTANGLE, texture1.textureID);
		//Get identifier for uniform
		GLuint uniformLocation1 = glGetUniformLocation(renderer->shaderProgram, "imageTexture");
		//Load texture unit number into uniform
		glUniform1i(uniformLocation1, 0);


		if(renderer->CheckGLErrors()) {
			std::cout << "Texture creation failed" << std::endl;
		}

			// three vertex positions and assocated colours of a triangle
		rectangle.verts.push_back(glm::vec3( -1.0f, -1.0f, 1.0f));
		rectangle.verts.push_back(glm::vec3( 1.0f,  -1.0f, 1.0f));
		rectangle.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		rectangle.verts.push_back(glm::vec3( -1.0f, -1.0f, 1.0f));
		rectangle.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
		rectangle.verts.push_back(glm::vec3( -1.0f, 1.0f, 1.0f));



		rectangle.drawMode = GL_TRIANGLES;

		rectangle.uvs.push_back(glm::vec2( 0.0f, 0.0f));
		rectangle.uvs.push_back(glm::vec2( float(texture1.width), 0.f));
		rectangle.uvs.push_back(glm::vec2( float(texture1.width), float(texture1.height)));
		rectangle.uvs.push_back(glm::vec2( 0.0f, 0.0f));
		rectangle.uvs.push_back(glm::vec2( float(texture1.width), float(texture1.height)));
		rectangle.uvs.push_back(glm::vec2(0.0f, float(texture1.height)));

		//Construct vao and vbos for the triangle
		RenderingEngine::assignBuffers(rectangle);

		//Send the triangle data to the GPU
		//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
		RenderingEngine::setBufferData(rectangle);

		//Add the triangle to the scene objects
		objects.push_back(rectangle);
}

void Scene::imageTransformation(double x, double y, string picture, float zoom, float degree){
	objects.clear();
	rectangle.verts.clear();
	rectangle.uvs.clear();

	MyTexture texture;
	const char* pictures = picture.c_str();
	InitializeTexture(&texture, pictures, GL_TEXTURE_RECTANGLE);

	//Load texture uniform
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Shaders need to be active to load uniforms
	glUseProgram(renderer->shaderProgram);
	//Set which texture unit the texture is bound to
	glActiveTexture(GL_TEXTURE0);
	//Bind the texture to GL_TEXTURE0
	glBindTexture(GL_TEXTURE_RECTANGLE, texture.textureID);
	//Get identifier for uniform
	GLuint uniformLocation = glGetUniformLocation(renderer->shaderProgram, "imageTexture");
	//Load texture unit number into uniform
	glUniform1i(uniformLocation, 0);

	if(renderer->CheckGLErrors()) {
		std::cout << "Texture creation failed" << std::endl;
	}


	if(float(texture.width) == float(texture.height)){		// if the image is a square, set ratio as 1.8 * 1.8
		std::cout << "equal" << std::endl;
		// three vertex positions and assocated colours of a triangle
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x - 0.9f) - sin(degree) * (y - 0.9f)) * zoom, (sin(degree) * (x - 0.9f) + cos(degree) * (y - 0.9f)) * zoom, 1.0f));
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x + 0.9f) - sin(degree) * (y - 0.9f)) * zoom, (sin(degree) * (x + 0.9f) + cos(degree) * (y - 0.9f)) * zoom, 1.0f));
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x + 0.9f) - sin(degree) * (y + 0.9f)) * zoom, (sin(degree) * (x + 0.9f) + cos(degree) * (y + 0.9f)) * zoom, 1.0f));
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x - 0.9f) - sin(degree) * (y - 0.9f)) * zoom, (sin(degree) * (x - 0.9f) + cos(degree) * (y - 0.9f)) * zoom, 1.0f));
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x + 0.9f) - sin(degree) * (y + 0.9f)) * zoom, (sin(degree) * (x + 0.9f) + cos(degree) * (y + 0.9f)) * zoom, 1.0f));
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x - 0.9f) - sin(degree) * (y + 0.9f)) * zoom, (sin(degree) * (x - 0.9f) + cos(degree) * (y + 0.9f)) * zoom, 1.0f));
	}else if(float(texture.width) < float(texture.height)){		// if the image's height is larger than width, set the ratio as x * 1.8
		std::cout << "height" << std::endl;
		// three vertex positions and assocated colours of a triangle
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x -((float(texture.width) / float(texture.height)) * 1.8f) / 2) - sin(degree) * (y - 0.9f)) * zoom, (sin(degree) * (x -((float(texture.width) / float(texture.height)) * 1.8f) / 2) + cos(degree) * (y - 0.9f)) * zoom, 1.0f));
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x + ((float(texture.width) / float(texture.height)) * 1.8f) / 2) - sin(degree) * (y - 0.9f)) * zoom, (sin(degree) * (x + ((float(texture.width) / float(texture.height)) * 1.8f) / 2) + cos(degree) * (y - 0.9f)) * zoom, 1.0f));
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x + ((float(texture.width) / float(texture.height)) * 1.8f) / 2) - sin(degree) * (y + 0.9f)) * zoom, (sin(degree) * (x + ((float(texture.width) / float(texture.height)) * 1.8f) / 2) + cos(degree) * (y + 0.9f)) * zoom, 1.0f));
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x -((float(texture.width) / float(texture.height)) * 1.8f) / 2) - sin(degree) * (y - 0.9f)) * zoom, (sin(degree) * (x -((float(texture.width) / float(texture.height)) * 1.8f) / 2) + cos(degree) * (y - 0.9f)) * zoom, 1.0f));
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x + ((float(texture.width) / float(texture.height)) * 1.8f) / 2) - sin(degree) * (y + 0.9f)) * zoom, (sin(degree) * (x + ((float(texture.width) / float(texture.height)) * 1.8f) / 2) + cos(degree) * (y + 0.9f)) * zoom, 1.0f));
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x -((float(texture.width) / float(texture.height)) * 1.8f) / 2) - sin(degree) * (y + 0.9f)) * zoom, (sin(degree) * (x -((float(texture.width) / float(texture.height)) * 1.8f) / 2) + cos(degree) * (y + 0.9f)) * zoom, 1.0f));
	}else if(float(texture.width) > float(texture.height)){		// if the image's height is smaller than width, set the ratio as 1.8 * y
		std::cout << "width" << std::endl;
		// three vertex positions and assocated colours of a triangle
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x - 0.9f) - sin(degree) * (y - ((float(texture.height) / float(texture.width)) * 1.8f) / 2)) * zoom, (sin(degree) * (x - 0.9f) + cos(degree) * (y - ((float(texture.height) / float(texture.width)) * 1.8f) / 2)) * zoom, 1.0f));
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x + 0.9f) - sin(degree) * (y - ((float(texture.height) / float(texture.width)) * 1.8f) / 2)) * zoom, (sin(degree) * (x + 0.9f) + cos(degree) * (y - ((float(texture.height) / float(texture.width)) * 1.8f) / 2))  * zoom, 1.0f));
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x + 0.9f) - sin(degree) * (y + ((float(texture.height) / float(texture.width)) * 1.8f) / 2)) * zoom, (sin(degree) * (x + 0.9f) + cos(degree) * (y + ((float(texture.height) / float(texture.width)) * 1.8f) / 2)) * zoom, 1.0f));
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x - 0.9f) - sin(degree) * (y - ((float(texture.height) / float(texture.width)) * 1.8f) / 2)) * zoom, (sin(degree) * (x - 0.9f) + cos(degree) * (y - ((float(texture.height) / float(texture.width)) * 1.8f) / 2)) * zoom, 1.0f));
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x + 0.9f) - sin(degree) * (y + ((float(texture.height) / float(texture.width)) * 1.8f) / 2)) * zoom, (sin(degree) * (x + 0.9f) + cos(degree) * (y + ((float(texture.height) / float(texture.width)) * 1.8f) / 2)) * zoom, 1.0f));
		rectangle.verts.push_back(glm::vec3( (cos(degree) * (x - 0.9f) - sin(degree) * (y + ((float(texture.height) / float(texture.width)) * 1.8f) / 2)) * zoom, (sin(degree) * (x - 0.9f) + cos(degree) * (y + ((float(texture.height) / float(texture.width)) * 1.8f) / 2)) * zoom, 1.0f));
	}

	rectangle.drawMode = GL_TRIANGLES;

	rectangle.uvs.push_back(glm::vec2( 0.0f, 0.0f));
	rectangle.uvs.push_back(glm::vec2( float(texture.width), 0.f));
	rectangle.uvs.push_back(glm::vec2( float(texture.width), float(texture.height)));
	rectangle.uvs.push_back(glm::vec2( 0.0f, 0.0f));
	rectangle.uvs.push_back(glm::vec2( float(texture.width), float(texture.height)));
	rectangle.uvs.push_back(glm::vec2(0.0f, float(texture.height)));

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(rectangle);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(rectangle);

	//Add the triangle to the scene objects
	objects.push_back(rectangle);
}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}

