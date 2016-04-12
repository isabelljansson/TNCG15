//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#pragma once
#include <lib/glm/glm/glm.hpp>
#include <lib/glm/glm/ext.hpp>
#include "SceneObject.h"
#include "Ray.h"


class Sphere : public SceneObject
{
public:
	Sphere(const glm::mat4 &object2World, float rad, float _p, float brdf, glm::vec3 _color);

	~Sphere();

	glm::vec3 intersection(Ray *ray);
	glm::vec3 Sphere::getNormal(glm::vec3 pos);

private: 
	float radius;
	glm::vec3 color;
};

