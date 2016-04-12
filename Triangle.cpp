//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#include "Triangle.h"
#define EPSILON 0.000001
#include <iostream>



Triangle::Triangle(glm::vec3 vert1, glm::vec3 vert2, glm::vec3 vert3, glm::vec3 colorRGB)
{
	v1 = vert1;
	v2 = vert2;
	v3 = vert3;

	//Calculate edges of triangle
	e1 = (v2 - v1);
	//e2 = v3 - v2;
	e3 = (v3 - v1);

	normal = glm::normalize(glm::cross(e1, e3));
	color = colorRGB;

}


Triangle::~Triangle()
{
}

bool Triangle::intersection(glm::vec3 startPos, glm::vec3 direction, float &t)
{
	glm::vec3 pvec = glm::cross(direction, e3);
	float det = glm::dot(e1, pvec);
	
	//The triangle and the ray are parallel or the triangle is back-facing
	if(det > -EPSILON && det < EPSILON)
		return false;

	
	float invDet = 1.0f/det;
	glm::vec3 tvec = startPos - v1;

	float u = glm::dot(tvec, pvec) * invDet;

	//Does not intersect triangle
	if( u < 0.0f || u > 1.0f ) 
		return false;
	
	glm::vec3 qvec = glm::cross(tvec, e1);
	float v = glm::dot(direction, qvec) * invDet;

	//No intersection
	if(v < 0.0f || u + v > 1.0f )
		return false;
	
	t = glm::dot(e3, qvec) * invDet;

	//Ray intersection
	if(t > EPSILON)
		return true;

	return false;
}