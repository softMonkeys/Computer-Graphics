/*
* Scene.cpp
*
* Created on: Nov 11, 2018
*     Author: Heavenel Cerna
*/

#include "Scene.h"
#include "RayTracer.h"
#include "Object.h"
#include "Light.h"

Scene::Scene(RayTracer* raytracer) : raytracer(raytracer) {
	changeToSceneOne();
}


void Scene::changeToSceneOne() {
	objects.clear();
	lights.clear();

	camera = new Camera(55);
	Light light(glm::vec3(0.0f, 2.5f, -7.75f), glm::vec3(1.0f, 1.0f, 1.0f));

	//Sphere
	objects.push_back(std::unique_ptr<Object>(new Sphere(glm::vec3(0.9f, -1.925f, -6.69f), 0.825f, glm::vec3(1,0,0), glm::vec3(1,0,0), glm::vec3(1.0f, 1.0f, 1.0f), 40)));

	//Pyramid
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(0.11f, -2.75f, -7.98f), glm::vec3(-0.93f, 0.55f, -8.51f), glm::vec3(-1.46f, -2.75f, -7.47f), glm::vec3(0.317, 0.627, 0.941), glm::vec3(0.317, 0.627, 0.941), glm::vec3(0.0f, 0.0f, 0.1f), 16)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-0.4f, -2.75f, -9.55f), glm::vec3(-0.93f, 0.55f, -8.51f), glm::vec3(0.11f, -2.75f, -7.98f), glm::vec3(0.317, 0.627, 0.941), glm::vec3(0.317, 0.627, 0.941), glm::vec3(0.0f, 0.0f, 0.0f), 16)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-1.46f, -2.75f, -7.47f), glm::vec3(-0.93f, 0.55f, -8.51f), glm::vec3(-1.97f, -2.75f, -9.04f), glm::vec3(0.317, 0.627, 0.941), glm::vec3(0.317, 0.627, 0.941), glm::vec3(0.0f, .0f, .0f), 16)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-1.97f, -2.75f, -9.04f), glm::vec3(-0.93f, 0.55f, -8.51f), glm::vec3(-0.4f, -2.75f, -9.55f), glm::vec3(0.317, 0.627, 0.941), glm::vec3(0.317, 0.627, 0.941), glm::vec3(0.0f, 0.0f, 0.0f), 16)));

	//Back wall
	objects.push_back(std::unique_ptr<Object>(new Plane(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -10.5f), glm::vec3(0.231, 0.305, 0.305), glm::vec3(0.611, 0.588, 0.588), glm::vec3(0.611, 0.588, 0.588), 1)));

	//Green wall on right
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(2.75,2.75,-5), glm::vec3(2.75,2.75,-10.5), glm::vec3(2.75,-2.75,-10.5f), glm::vec3(0.066, 0.572, 0.176), glm::vec3(0.066, 0.572, 0.176), glm::vec3(0.066, 0.572, 0.176), 2)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(2.75,-2.75,-5), glm::vec3(2.75,2.75,-5), glm::vec3(2.75,-2.75,-10.5), glm::vec3(0.066, 0.572, 0.176), glm::vec3(0.066, 0.572, 0.176), glm::vec3(0.066, 0.572, 0.176), 2)));

	//Red wall on left
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-2.75,-2.75,-5), glm::vec3(-2.75,-2.75,-10.5), glm::vec3(-2.75,2.75,-10.5), glm::vec3(0.819, 0.203, 0.101), glm::vec3(0.819, 0.203, 0.101), glm::vec3(0.819, 0.203, 0.101), 2)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-2.75,2.75,-5), glm::vec3(-2.75,-2.75,-5), glm::vec3(-2.75,2.75,-10.5), glm::vec3(0.819, 0.203, 0.101), glm::vec3(0.819, 0.203, 0.101), glm::vec3(0.819, 0.203, 0.101), 2)));

	//Floor
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(2.75, -2.75, -5), glm::vec3(2.75, -2.75, -10.5), glm::vec3(-2.75, -2.75, -10.5), glm::vec3(0.611, 0.588, 0.588), glm::vec3(0.611, 0.588, 0.588), glm::vec3(0.611, 0.588, 0.588), 20)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-2.75, -2.75, -5), glm::vec3(2.75, -2.75, -5), glm::vec3(-2.75, -2.75, -10.5), glm::vec3(0.611, 0.588, 0.588), glm::vec3(0.611, 0.588, 0.588), glm::vec3(0.611, 0.588, 0.588), 20)));

	//Ceiling
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(2.75,2.75,-10.5), glm::vec3(2.75,2.75,-5), glm::vec3(-2.75,2.75,-5), glm::vec3(0.611, 0.588, 0.588), glm::vec3(0.611, 0.588, 0.588), glm::vec3(1,1,1), 20)));
	objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(-2.75,2.75,-10.5), glm::vec3(2.75,2.75,-10.5), glm::vec3(-2.75,2.75,-5), glm::vec3(0.611, 0.588, 0.588), glm::vec3(0.611, 0.588, 0.588), glm::vec3(1,1,1), 20)));

	lights.push_back(light);
}

void Scene::changeToSceneTwo() {
	objects.clear();
	lights.clear();

	camera = new Camera(90);
	Light light(glm::vec3(4.0f, 6.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	//Floor
	objects.push_back(std::unique_ptr<Object>(new Plane(glm::vec3(0, 1, 0), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.231, 0.305, 0.305), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 16)));

	//Back wall
	objects.push_back(std::unique_ptr<Object>(new Plane(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -12.0f), glm::vec3(0.372, 0.482, 0.486), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 16)));

	//Large yellow sphere
	objects.push_back(std::unique_ptr<Object>(new Sphere(glm::vec3(1, -0.5, -3.5), 0.5, glm::vec3(0.913, 0.862, 0.247), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 16)));

	//Reflective grey sphere
	objects.push_back(std::unique_ptr<Object>(new Sphere(glm::vec3(0, 1, -5), 0.4, glm::vec3(0.349, 0.509, 0.486), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 16)));

	//Metallic purple sphere
	objects.push_back(std::unique_ptr<Object>(new Sphere(glm::vec3(-0.8, -0.75, -4), 0.25f, glm::vec3(0.690, 0.239, 0.819), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 16)));

	//Green cone
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  0 -1 -5.8
//	  0 0.6 -5
//	  0.4 -1 -5.693
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  0.4 -1 -5.693
//	  0 0.6 -5
//	  0.6928 -1 -5.4
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  0.6928 -1 -5.4
//	  0 0.6 -5
//	  0.8 -1 -5
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  0.8 -1 -5
//	  0 0.6 -5
//	  0.6928 -1 -4.6
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  0.6928 -1 -4.6
//	  0 0.6 -5
//	  0.4 -1 -4.307
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  0.4 -1 -4.307
//	  0 0.6 -5
//	  0 -1 -4.2
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  0 -1 -4.2
//	  0 0.6 -5
//	  -0.4 -1 -4.307
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -0.4 -1 -4.307
//	  0 0.6 -5
//	  -0.6928 -1 -4.6
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -0.6928 -1 -4.6
//	  0 0.6 -5
//	  -0.8 -1 -5
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -0.8 -1 -5
//	  0 0.6 -5
//	  -0.6928 -1 -5.4
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -0.6928 -1 -5.4
//	  0 0.6 -5
//	  -0.4 -1 -5.693
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -0.4 -1 -5.693
//	  0 0.6 -5
//	  0 -1 -5.8
//	))));
//
//	//Shiny red icosahedron
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -2 -1 -7
//	  -1.276 -0.4472 -6.474
//	  -2.276 -0.4472 -6.149
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -1.276 -0.4472 -6.474
//	  -2 -1 -7
//	  -1.276 -0.4472 -7.526
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -2 -1 -7
//	  -2.276 -0.4472 -6.149
//	  -2.894 -0.4472 -7
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -2 -1 -7
//	  -2.894 -0.4472 -7
//	  -2.276 -0.4472 -7.851
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -2 -1 -7
//	  -2.276 -0.4472 -7.851
//	  -1.276 -0.4472 -7.526
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -1.276 -0.4472 -6.474
//	  -1.276 -0.4472 -7.526
//	  -1.106 0.4472 -7
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -2.276 -0.4472 -6.149
//	  -1.276 -0.4472 -6.474
//	  -1.724 0.4472 -6.149
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -2.894 -0.4472 -7
//	  -2.276 -0.4472 -6.149
//	  -2.724 0.4472 -6.474
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -2.276 -0.4472 -7.851
//	  -2.894 -0.4472 -7
//	  -2.724 0.4472 -7.526
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -1.276 -0.4472 -7.526
//	  -2.276 -0.4472 -7.851
//	  -1.724 0.4472 -7.851
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -1.276 -0.4472 -6.474
//	  -1.106 0.4472 -7
//	  -1.724 0.4472 -6.149
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -2.276 -0.4472 -6.149
//	  -1.724 0.4472 -6.149
//	  -2.724 0.4472 -6.474
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -2.894 -0.4472 -7
//	  -2.724 0.4472 -6.474
//	  -2.724 0.4472 -7.526
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -2.276 -0.4472 -7.851
//	  -2.724 0.4472 -7.526
//	  -1.724 0.4472 -7.851
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -1.276 -0.4472 -7.526
//	  -1.724 0.4472 -7.851
//	  -1.106 0.4472 -7
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -1.724 0.4472 -6.149
//	  -1.106 0.4472 -7
//	  -2 1 -7
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -2.724 0.4472 -6.474
//	  -1.724 0.4472 -6.149
//	  -2 1 -7
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -2.724 0.4472 -7.526
//	  -2.724 0.4472 -6.474
//	  -2 1 -7
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -1.724 0.4472 -7.851
//	  -2.724 0.4472 -7.526
//	  -2 1 -7
//	))));
//objects.push_back(std::unique_ptr<Object>(new Triangle(glm::vec3(
//	  -1.106 0.4472 -7
//	  -1.724 0.4472 -7.851
//	  -2 1 -7
//	))));
	lights.push_back(light);
}


Scene::~Scene() {

}

void Scene::renderScene() {
	raytracer->renderScene(objects, lights, camera);
}










