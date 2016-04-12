//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#include "CornellBox.h"
#define INF 9999999999


CornellBox::CornellBox(float _p, float brdf, glm::mat4 _o2w) 
	: SceneObject( _o2w, _p, brdf)
{
	createCBox();
}


CornellBox::~CornellBox()
{
	for (it = cornellBox.begin(); it != cornellBox.end(); ++it)
	{
	   delete (*it);
	} 
	cornellBox.clear();
}

void CornellBox::createCBox()
{

	v0 = glm::vec3(-1.0, -1.0,  1.0);
	v1 = glm::vec3( 1.0, -1.0,  1.0);
	v2 = glm::vec3(-1.0,  1.0,  1.0);
	v3 = glm::vec3( 1.0,  1.0,  1.0);
	v4 = glm::vec3(-1.0, -1.0, -1.0);
	v5 = glm::vec3 (1.0, -1.0, -1.0);
	v6 = glm::vec3(-1.0,  1.0, -1.0);
	v7 = glm::vec3( 1.0,  1.0, -1.0);
	
	cornellBox.push_back(new Triangle(v0, v6, v2, glm::vec3 (1, 0, 0))); //Left wall
	cornellBox.push_back(new Triangle(v0, v4, v6, glm::vec3 (1, 0, 0))); //Left wall
	
	cornellBox.push_back(new Triangle(v4, v7, v6, glm::vec3 (1, 1, 1))); //Back wall
	cornellBox.push_back(new Triangle(v4, v5, v7, glm::vec3 (1, 1, 1))); //Back wall
	
	cornellBox.push_back(new Triangle(v1, v3, v7, glm::vec3 (0, 0, 1))); //Right wall
	cornellBox.push_back(new Triangle(v1, v7, v5, glm::vec3 (0, 0, 1))); //Right wall

	cornellBox.push_back(new Triangle(v2, v6, v7, glm::vec3 (1, 1, 1))); //Ceiling
	cornellBox.push_back(new Triangle(v2, v7, v3, glm::vec3 (1, 1, 1))); //Ceiling
	
	cornellBox.push_back(new Triangle(v0, v5, v4, glm::vec3 (1, 1, 1))); //Floor
	cornellBox.push_back(new Triangle(v0, v1, v5, glm::vec3 (1, 1, 1))); //Floor
}


glm::vec3 CornellBox::intersection(Ray *ray)
{
	float t = INF;
	float length = INF;
	glm::vec3 hitPos;

	//Transform ray to cornellBox coordinates
	glm::vec3 direction = glm::normalize(glm::vec3(w2o*glm::vec4(ray->direction, 1.0)));
	glm::vec3 startPos = glm::vec3 ( w2o*glm::vec4(ray->startPos, 1.0));

	//Test intersection with every triangle
	for (it = cornellBox.begin(); it != cornellBox.end(); it++)
		if((*it)->intersection(startPos, direction, t))
			if(t < length)
			{
				length = t;
				ray->hitNormal = glm::normalize(glm::vec3(o2w*glm::vec4((*it)->normal, 1.0f)));
				ray->objColor = (*it)->color;
				ray->e1 = glm::normalize(glm::vec3(o2w*glm::vec4((*it)->e1, 1.0f)));
			}
	if (length != INF)
		hitPos = glm::vec3(o2w*glm::vec4(startPos + length*direction, 1));
	else
		hitPos = glm::vec3(INF, INF, INF);

	return hitPos;
}

