//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#include "Box.h"


Box::Box(float _p, float brdf, glm::mat4 _o2w) 
	: SceneObject( _o2w, _p, brdf)
{
	createBox();
}


Box::~Box()
{
	for (it = box.begin(); it != box.end(); ++it)
	{
	   delete (*it);
	} 
	box.clear();
}

void Box::createBox()
{
	glm::vec3 cLeft = glm::vec3 (0, 153, 76)/255.f;
	glm::vec3 cBack = glm::vec3(0, 153, 76) / 255.f;
	glm::vec3 cRight = glm::vec3(0, 153, 76) / 255.f;
	glm::vec3 cFront = glm::vec3(0, 153, 76) / 255.f;
	glm::vec3 cCeiling = glm::vec3(0, 153, 76) / 255.f;
	glm::vec3 cFloor = glm::vec3(0, 153, 76) / 255.f;

	v0 = glm::vec3(-1.0, -1.0,  1.0);
	v1 = glm::vec3( 1.0, -1.0,  1.0);
	v2 = glm::vec3(-1.0,  1.0,  1.0);
	v3 = glm::vec3( 1.0,  1.0,  1.0);
	v4 = glm::vec3(-1.0, -1.0, -1.0);
	v5 = glm::vec3 (1.0, -1.0, -1.0);
	v6 = glm::vec3(-1.0,  1.0, -1.0);
	v7 = glm::vec3( 1.0,  1.0, -1.0);
	
	box.push_back(new Triangle(v2, v6, v0, cLeft)); //Left wall
	box.push_back(new Triangle(v6, v4, v0, cLeft)); //Left wall
	
	box.push_back(new Triangle(v6, v7, v4, cBack)); //Back wall
	box.push_back(new Triangle(v7, v5, v4, cBack)); //Back wall
	
	box.push_back(new Triangle(v7, v3, v1, cRight)); //Right wall
	box.push_back(new Triangle(v5, v7, v1, cRight)); //Right wall

	box.push_back(new Triangle(v0, v3, v2, cFront)); //Front wall
	box.push_back(new Triangle(v0, v1, v3, cFront)); //Front wall

	box.push_back(new Triangle(v7, v6, v2, cCeiling)); //Ceiling
	box.push_back(new Triangle(v3, v7, v2, cCeiling)); //Ceiling
	
	box.push_back(new Triangle(v4, v5, v0, cFloor)); //Floor
	box.push_back(new Triangle(v5, v1, v0, cFloor)); //Floor
}


glm::vec3 Box::intersection(Ray *ray)
{
	float t = INF;
	float length = INF;
	glm::vec3 hitPos;

	//Transform ray to cornellBox coordinates
	glm::vec3 direction = glm::normalize(glm::vec3(w2o*glm::vec4(ray->direction, 1.0)));
	glm::vec3 startPos = glm::vec3 ( w2o*glm::vec4(ray->startPos, 1.0));

	//Test intersection with every triangle
	for (it = box.begin(); it != box.end(); it++)
		if((*it)->intersection(startPos, direction, t))
			if(t < length)
			{
				length = t;
				ray->hitNormal = glm::normalize(glm::vec3(o2w*glm::vec4((*it)->normal, 1.0f)));
				ray->objColor = (*it)->color;
				ray->e1 = glm::normalize(glm::vec3(o2w*glm::vec4((*it)->e1, 1.0f)));
			}

	//calculate hitPos for the ray
	if (length != INF)
		hitPos = glm::vec3(o2w*glm::vec4(startPos + length*direction, 1));
	else
		hitPos = glm::vec3(INF, INF, INF);

	return hitPos;
}
