//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#pragma once
#include <lib/glm/glm/glm.hpp>
#include <lib/glm/glm/gtc/constants.hpp>
#include <lib/glm/glm/ext.hpp>
#include <math.h>
#include <vector>

class Triangle
{
public:
	Triangle(glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3, glm::vec3 colorRGB);

	~Triangle();

	bool Triangle::intersection(glm::vec3 startPos, glm::vec3 direction, float &t);

	glm::vec3 v1, v2, v3; 
	glm::vec3 e1,e2,e3; //Edges for the traingle
	glm::vec3 normal;
	glm::vec3 color;
};

