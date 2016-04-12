//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#include "Scene.h"

Scene::Scene()
{
	objects = new std::vector<SceneObject*>();
	lights = new std::vector<Light*>();
}

void Scene::addObject(SceneObject *obj)
{
	objects->push_back(obj);
}

void Scene::addLight(Light *_light)
{
	lights->push_back(_light);
}


Scene::~Scene()
{
}
