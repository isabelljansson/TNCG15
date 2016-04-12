//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#pragma once
#include <lib/glm/glm/glm.hpp>
#include <lib/glm/glm/ext.hpp>
#include <vector>
#include <random>


#include "Triangle.h"
#include "Ray.h"

class Light
{
public:
	Light(const glm::mat4 &_o2w);
	~Light();

	void createLight();
	void randomPos(glm::vec3 &lightStart);
	bool intersection(Ray *ray);
	glm::vec3 getNormal();
	float le;
	glm::vec3 color;

private:
	glm::mat4 o2w, w2o;
	glm::vec3 v1, v2, v3, v4;

	std::vector<Triangle*> lightSource;
	std::vector<Triangle*>::iterator it;

	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution; //[-1, 1)
};

