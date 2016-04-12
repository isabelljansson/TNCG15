//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#include "SceneObject.h"

SceneObject::SceneObject(const glm::mat4 &object2World, float _p, float brdf)
{
	o2w = object2World;
	w2o = glm::inverse(o2w);
	p = _p;
	fr = brdf;
}


SceneObject::~SceneObject()
{

}

glm::vec3 SceneObject::intersection(Ray *ray)
{
	return glm::vec3(INF, INF, INF);
}

float SceneObject::getFr()
{
	return fr;
}

float SceneObject::getProb()
{
	return p;
}