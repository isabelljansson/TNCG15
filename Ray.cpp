//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#include "Ray.h"

//Default constructor
Ray::Ray()
{
	parent = nullptr;
	refChild = nullptr;
	transChild = nullptr;
}

//Constructor

Ray::Ray(const glm::vec3 start, const glm::vec3 _direction, Ray *p)
{
	startPos = start;
	direction = _direction;

	parent = p;
	refChild = nullptr;
	transChild = nullptr;
	hitPos = glm::vec3(INF,INF,INF);
}

//Destructor
Ray::~Ray()
{
	delete refChild;
	delete transChild;
}