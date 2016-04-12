//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#pragma once
#include <lib/glm/glm/glm.hpp>
#include <lib/glm/glm/ext.hpp>
#include <vector>
#include "SceneObject.h"
#include "Light.h"


class Scene
{
public:
	Scene();
	~Scene();

	void addObject(SceneObject *obj);
	void addLight(Light *_light);

	std::vector<SceneObject*> *objects;
	//vector with light sources
	std::vector<Light*> *lights;

};

