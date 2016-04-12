//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#pragma once
#define INF 9999999999
#define _USE_MATH_DEFINES

#include <lib/glm/glm/glm.hpp>
#include <lib/glm/glm/ext.hpp>


class Ray
{
public:
	Ray();
	Ray(const glm::vec3 start, const glm::vec3 _direction, Ray *p);
	~Ray();

	glm::vec3 startPos;
	glm::vec3 direction;

	glm::vec3 hitPos, hitNormal, lightNormal, e1;
	float rayLength;
	glm::vec3 importance;
	glm::vec3 objColor;

	Ray *parent;
	Ray *refChild;
	Ray *transChild;
};

