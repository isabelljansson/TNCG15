//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#define GLFW_INCLUDE_GLU
#define INF 9999999999
#define _USE_MATH_DEFINES


#include <iostream>
#include <lib/glm/glm/glm.hpp>
#include <math.h>
#include <fstream>
#include <random>
#include <algorithm>

#include "Sphere.h"
#include "Scene.h"
#include "SceneObject.h"
#include "Image.h"
#include "Ray.h"
#include "CornellBox.h"
#include "Light.h"
#include "Camera.h"
#include "Box.h"


using namespace std;


int main()
{

	//Initialize image buffer
	int imageWidth = 512, imageHeight = 512;

	//Initialize scene
	Scene *scene = new Scene();
	Image *image = new Image(imageWidth, imageHeight);

	glm::mat4 sc = glm::mat4(0.0f);
	sc[0][0] = 0.45;
	sc[1][1] = 0.45;
	sc[2][2] = 0.45;
	sc[3][3] = 1.0;

	//Create a cornell box
	SceneObject *cornellBox = new CornellBox(0.9f, 0.8f / M_PI, glm::translate<float>(0.0, 0.0, 0.0)*sc);// *
		//glm::scale<float>(0.45, 0.45, 0.45));
	scene->addObject(cornellBox);

	//Create some objects
	SceneObject *sphere = new Sphere(glm::translate<float>(-0.2, -0.2, 0.0), 0.2f, 
		0.2f, 0.4f/M_PI, glm::vec3(255, 105,180)/255.f);
	scene->addObject(sphere);

	SceneObject *sphere2nd = new Sphere(glm::translate<float>(0.2, -0.2, 0.0), 0.2f,
		0.8f, 0.6f / M_PI, glm::vec3(173, 255, 47) / 255.f);
	scene->addObject(sphere2nd);

	sc[0][0] = 0.15;
	sc[1][1] = 0.15;
	sc[2][2] = 0.15;
	sc[3][3] = 1.0;
	
	//Create a box
	SceneObject *box = new Box(0.9f, 0.8f / M_PI, glm::translate<float>(0.2, -0.2, 0.0) *
	glm::rotate<float>(40, glm::vec3(0, 1, 0)) * sc);
		//glm::scale<float>(0.15, 0.15, 0.15));
	//scene->addObject(box);

	sc[0][0] = 0.2;
	sc[1][1] = 1.0;
	sc[2][2] = 0.2;
	sc[3][3] = 1.0;

	//Create light sources
	scene->addLight(new Light(glm::translate<float>(0.0, 0.45, 0.0)*sc));// *
		//glm::scale<float>(0.2, 1.0, 0.2) //do not scale i y
		//));


	//Set up camera
	glm::vec3 cameraPos(0.0f, 0.0f, 1.0f);
	Camera *cam = new Camera(cameraPos, glm::vec3(0.0f, 0.0f, -1.0f));

	//Monte Carlo ray tracing

	float xRatio = imageWidth / imageHeight;
	float yRatio = 1.0f;

	float xPos = -xRatio;
	float yPos = -yRatio;

	float xStep = (2*xRatio) / imageWidth;
	float yStep = (2*yRatio) / imageHeight; 

	float lmax = 0, maximum = 0;
	int xx, yy;

	glm::vec3 l = glm::vec3(0.0, 0.0, 0.0); //light vector, 0 = no light, black color
	int rpp = 3; //number of rays per pixel
	float dx, dy;

	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(-0.5, 0.5); //[-0.5, 0.5)
	
	//MONTE CARLO RAY TRACING
	for(int y = 0; y < imageHeight; y++)
	{
		yPos += yStep;
		xPos = -xRatio;  

		for(int x = 0; x < imageWidth; x++)
		{
			xPos += xStep;

			//Save pixel as black in case of no intersection
			image->saveToBuffer(x,y, glm::vec3(0, 0, 0));

			//Add a random outgoing postition for xPos and yPos 
			//so that several rays can be randomly sent from each x and y pos. in the image plane
			for (int p = 0; p < rpp; p++)
			{
				dx = distribution(generator) * xStep;
				dy = distribution(generator) * yStep;
				
				//calculate a ray's position and direction and transform it to world coordinates
				glm::vec3 rDirection = glm::normalize(glm::mat3(cam->getCTransform()) * (glm::vec3(xPos + dx, yPos + dy, -1.0f)));
				glm::vec3 rPos = glm::vec3(cam->getCTransform() * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
			
				//create a ray with the position and direction calculated above
				//the first ray has importance = (1,1,1)
				Ray *ray = new Ray(rPos, rDirection, nullptr);
				ray->importance = glm::vec3(1.0f,1.0f,1.0f);
			
				//perform ray tracing and add the result to l-vector 
				l += cam->calculateL(scene, ray);

				delete ray;
			}
			//Save in buffer
			l /= (float)rpp;
			image->saveToBuffer(x,y, l);

			maximum = max(max(l.x, l.y), l.z);
			if (lmax < maximum)
			{
				lmax = maximum;
				xx = x;
				yy = y;
			}

			l = glm::vec3(0.0, 0.0, 0.0);		
		}
	}

	//scale light such that max intensity -> 1.0 and save the result to an image
	image->scaleImage(lmax);
	image->saveImage();
	

	return 0;
}