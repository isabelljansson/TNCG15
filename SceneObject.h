//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#pragma once
#include <lib/glm/glm/glm.hpp>
#include <lib/glm/glm/ext.hpp>
#include "Ray.h"


class SceneObject
{
public:
	glm::mat4 w2o;
	glm::mat4 o2w;
	float p;
	float fr;
	

	SceneObject(const glm::mat4 &object2World, float _p, float brdf);
	virtual ~SceneObject();
	virtual glm::vec3 intersection(Ray *ray);
	virtual float getFr();
	virtual float getProb();
};

