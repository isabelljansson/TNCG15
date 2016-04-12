//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#pragma once
#include <fstream>
#include <lib/glm/glm/glm.hpp>

class Image
{
public:
	Image(int imageWidth, int imageHeigth);
	~Image();

	void saveToBuffer(int x, int y, glm::vec3 color);
	void Image::scaleImage(float lmax);
	void saveImage();

private:
	int height;
	int width;
	int i, j, r, g, b;

	FILE *f;
	unsigned char *img;
	int filesize;
};

