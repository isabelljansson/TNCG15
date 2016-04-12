//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#define INF 9999999999

#include "Light.h"
#include <iostream>

Light::Light(const glm::mat4 &_o2w)
{
	o2w = _o2w;
	w2o = glm::inverse(o2w);
	le = 1.0;
	color = glm::vec3(1,1,1);
	createLight();
	
}


Light::~Light()
{
	for (it = lightSource.begin(); it != lightSource.end(); ++it)
	{
	   delete (*it);
	} 
	lightSource.clear();
}

void Light::createLight()
{
	v1 = glm::vec3(-1.0, 0.0,  1.0); //2
	v2 = glm::vec3( 1.0, 0.0,  1.0); //3
	v3 = glm::vec3(-1.0, 0.0, -1.0); //6
	v4 = glm::vec3 (1.0, 0.0, -1.0); //7

	lightSource.push_back(new Triangle(v1, v3, v4, glm::vec3 (1, 1, 1))); //Ceiling
	lightSource.push_back(new Triangle(v1, v4, v2, glm::vec3 (1, 1, 1))); //Ceiling
}

void Light::randomPos(glm::vec3 &lightStart)
{
	

	lightStart = glm::vec3(o2w*glm::vec4(lightStart,1));
}

glm::vec3 Light::getNormal()
{
	return glm::normalize(glm::vec3(o2w*glm::vec4(glm::cross(v3-v1, v4-v1), 1.0)));

	
}

bool Light::intersection(Ray *ray)
{
	float t = INF;
	float length = INF;

	//Transform ray to light coordinates
	glm::vec3 direction = glm::normalize(glm::vec3 ( w2o * glm::vec4(ray->direction, 1.0)));
	glm::vec3 startPos = glm::vec3 ( w2o * glm::vec4(ray->startPos, 1.0));

	//Test intersection with every triangle
	for (it = lightSource.begin(); it != lightSource.end(); it++)
		if((*it)->intersection(startPos, direction, t))
			if(t < length)
				return true;

	return false;
}