//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#pragma once
#include <lib/glm/glm/glm.hpp>
#include <lib/glm/glm/ext.hpp>
#include <algorithm>
#include <iostream>
#include "Ray.h"
#include "Scene.h"

class Camera
{
public:
	Camera(glm::vec3 eye, glm::vec3 center);
	~Camera();

	glm::mat4 getCTransform() { return c2w; } 

	glm::vec3 calculateL(Scene *scene, Ray *ray);
	glm::vec3 castShadowRays(Scene *scene, Ray *ray);

private:
	glm::mat4 c2w;

	int objIndex, lightIndex, maxIterations;
	bool hitLight;
};

