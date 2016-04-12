//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#pragma once

#include <lib/glm/glm/glm.hpp>
#include <lib/glm/glm/ext.hpp>
#include <vector>
#include <iostream>

#include "Ray.h"
#include "SceneObject.h"
#include "Triangle.h"


class Box : public SceneObject
{
public:
	Box(float _p, float brdf, glm::mat4 _o2w);
	~Box();

	std::vector<Triangle*> box;

	glm::vec3 Box::intersection(Ray *ray);

private:
	void createBox();

	glm::vec3 v0;
	glm::vec3 v1;
	glm::vec3 v2;
	glm::vec3 v3;
	glm::vec3 v4;
	glm::vec3 v5;
	glm::vec3 v6;
	glm::vec3 v7;

	std::vector<Triangle*>::iterator it;
};

//       v6------------v7
//      / .           / |
//     /  .          /  |
//    v2------------v3  |
//    |   .         |   |
//    |   .         |   |
//    |  v4 . . . . |. /v5
//    | .           | /
//    |.            |/
//    v0------------v1