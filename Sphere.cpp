//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#define EPSILON 0.000001
#define INF 9999999999
#include "Sphere.h"
#include "SceneObject.h"


#include <math.h> 
#include <iostream>


Sphere::Sphere(const glm::mat4 &object2World, float rad, float _p, float brdf, glm::vec3 _color) 
	: SceneObject(object2World, _p, brdf)
{
	radius = rad;
	color = _color;
}


Sphere::~Sphere()
{
}

glm::vec3 Sphere::intersection(Ray *ray) 
{
	//http://sci.tuomastonteri.fi/programming/sse/example3

	glm::vec3 rayDir;
	glm::vec3 rayStart, hitPos;
	float smin, a, b, c;

	rayDir = glm::normalize(glm::vec3(w2o*glm::vec4(ray->direction, 1.0)));
	rayStart = glm::vec3(w2o*glm::vec4(ray->startPos,1.0));

	//Transform ray to local coordinates for the sphere
	//The center of the sphere is (0,0,0) in local coordinates
	a = glm::dot(rayDir,rayDir); //||l||^2
	b = -glm::dot(rayDir,rayStart); //-(rayDir(rayStart-centerOfSphere)
	//(rayDir*(rayStart - cOS))^2 - a*(||rayStart -cOS||^2 + r^2)
	c = (pow(glm::dot(rayStart,rayDir),2) - a*(glm::dot(rayStart,rayStart)- radius*radius));

	//No intersecton
	if(c < 0.0)
		return  glm::vec3(INF, INF, INF);

	//One solution
	if(c > -EPSILON && c < EPSILON)
		return  glm::vec3(INF, INF, INF);

	smin = (b - sqrt(c))/a;

	if( smin < 0 )
		return  glm::vec3(INF, INF, INF);

	ray->hitNormal = glm::normalize(glm::vec3(o2w*glm::vec4(getNormal(rayStart + smin*rayDir), 1.0f)));
	ray->objColor = color;
	if (ray->hitNormal != glm::vec3(-1.0, 1.0, 0.0))
		ray->e1 = glm::vec3(ray->hitNormal.z, ray->hitNormal.z, -ray->hitNormal.x - ray->hitNormal.y);
	else
		ray->e1 = glm::vec3(-ray->hitNormal.y - ray->hitNormal.z, ray->hitNormal.x, ray->hitNormal.x);

	hitPos = glm::vec3(o2w*glm::vec4(rayStart + smin*rayDir, 1));

	return hitPos;
}

glm::vec3 Sphere::getNormal(glm::vec3 pos)
{
	return glm::normalize(pos - glm::vec3(0,0,0));
}