//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#include "Camera.h"

std::default_random_engine generator;
std::uniform_real_distribution<float> distribution(0.0, 1.0); //[0, 1)
std::uniform_real_distribution<float> distribution2(-1.0, 1.0); //[-1, 1)


Camera::Camera(glm::vec3 eye, glm::vec3 center)
{
	c2w = glm::inverse(glm::lookAt(eye, center, glm::vec3(0.0, 1.0, 0.0)));

	objIndex = -1;
	lightIndex = -1;
	maxIterations = 0;
}


Camera::~Camera(void)
{
}

glm::vec3 Camera::calculateL(Scene *scene, Ray *ray)
{
	float length = INF; 
	glm::vec3 t;
	

	float u1, u2; //Random numbers
	float phi, theta; //Angles for new ray
	
	
	glm::vec3 temphit;

	//calculate if continue
	for(int i = 0; i < scene->lights->size(); i++)
	{
		hitLight = scene->lights->at(i)->intersection(ray);
		
		lightIndex = i;
	}

	if(!hitLight)
	{
		//Calculate intersection with nearest object in scene
		for(int i = 0; i < scene->objects->size(); i++)
		{
			
			t = scene->objects->at(i)->intersection(ray);
			if(glm::length(t - ray->startPos) < length && t.x < INF)
			{
				length = glm::length(t - ray->startPos);
				temphit = t;
				objIndex = i;
			}
		}

		//Ray hits a surface, continue
		if(length != INF)
		{
			//Save rays hit position and ray length
				ray->rayLength = length;
				
				ray->hitPos = temphit;
				if (objIndex == 1 && ray->hitPos.z == 0.15)
					std::cout << ray->hitPos.x << " " << ray->hitPos.y << " " << ray->hitPos.z << " " << std::endl;

				//Russian roulette, will it continue?
				u1 = distribution(generator);
				phi = 2 * M_PI*u1/scene->objects->at(objIndex)->getProb();
				
				//Terminate ray, don't continue
				if(phi < 2*M_PI)
				{
					u2 = distribution(generator);
					theta = acos(sqrt(u2));
					
					//calculate the new ray direction
					glm::vec3 newdir = glm::normalize(glm::rotate(ray->e1, phi, ray->hitNormal));
					newdir = glm::normalize(glm::rotate(ray->hitNormal, theta, newdir));
					
					//set importance for the child
					ray->refChild = new Ray(ray->hitPos, newdir, ray);
					ray->refChild->importance = (scene->objects->at(objIndex)->getFr()*ray->objColor*(float)M_PI*ray->importance) /
						scene->objects->at(objIndex)->getProb();
				}	
			
					
				
		}
	}

	//if continue, recursive cal for refChild
	if(ray->refChild && maxIterations < 2)
	{
		maxIterations++;
		return (calculateL(scene, ray->refChild) * ray->refChild->importance / ray->importance) + castShadowRays(scene, ray); 
	}
	else //Last ray in path
	{
		maxIterations = 0;
		return castShadowRays(scene, ray);
	}
}

glm::vec3 Camera::castShadowRays(Scene *scene, Ray *ray)
{
	

	glm::vec3 ld = glm::vec3(0.0), randPos;
	float length = INF;
	glm::vec3 t;
	int shadowLight = 3; //number of shadow rays

	//Hit a light source
	if(hitLight)
	{
		for(int i = 0; i < scene->lights->size(); i++)
		{
			//Only add le from one light source atm
			ld += scene->lights->at(i)->color*scene->lights->at(i)->le; 
		}
		hitLight = false;
	}
	else if(ray->hitPos.x < INF) //Terminated on an object, calc shadow rays
	{		
		for(int i = 0; i < scene->lights->size(); i++)
		{
			for(int j = 0; j<shadowLight; j++)
			{
				length = INF;

				//generate a random position at the area light source
				randPos.x = distribution2(generator);
				randPos.y = 0.0;
				randPos.z = distribution2(generator);
				scene->lights->at(i)->randomPos(randPos);

				//Intersection to check if there is an object between our hit object and
				//the light source
				for(int k = 0; k < scene->objects->size(); k++)
				{
					Ray *newRay = new Ray(ray->hitPos, glm::normalize(randPos - ray->hitPos), nullptr);
					t = scene->objects->at(k)->intersection(newRay);
					if(glm::length(t - ray->startPos)  < length && t.x < INF)
					{
						if(objIndex != k)
							glm::length(t - ray->startPos);	
					}
				}
				
				if(length >= glm::length(randPos - ray->hitPos))
					ld += scene->objects->at(objIndex)->getFr()*ray->objColor*scene->lights->at(i)->le*(glm::dot(scene->lights->at(i)->getNormal(),(-1.f)*(randPos - ray->hitPos)*glm::dot(ray->hitNormal, (randPos - ray->hitPos))) / std::max(glm::length(randPos - ray->hitPos)*glm::length(randPos - ray->hitPos), 1.f));
			}
		}
	}

	return (ld/(float)shadowLight);
}