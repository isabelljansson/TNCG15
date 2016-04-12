//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#pragma once
#include <lib/glm/glm/glm.hpp>
#include <lib/glm/glm/ext.hpp>
#include <vector>
#include <iostream>

#include "SceneObject.h"
#include "Triangle.h"
#include "Ray.h"


class CornellBox : public SceneObject
{
public:
	CornellBox(float _p, float brdf, glm::mat4 _o2w);
	~CornellBox();

	std::vector<Triangle*> cornellBox;

	glm::vec3 intersection(Ray *ray);
	


private:
	void createCBox();

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

