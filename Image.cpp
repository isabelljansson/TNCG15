//Ronja Grosz rongr946
//Isabell Jansson isaja187
//Advanced global illumination and rendering
//TNCG15

#include "Image.h"
#include <iostream>


Image::Image(int imageWidth, int imageHeigth)
{
	width = imageWidth; height = imageHeigth;
	img = nullptr;
	filesize = 54 + 3*width*height;  //w is the image width, h is image height, both ints
	if( img )
		free( img );

	img = (unsigned char *)malloc(3*width*height);
	memset(img,0,sizeof(img));
}


Image::~Image()
{
}

void Image::saveToBuffer(int x, int y, glm::vec3 color)
{
	j = x, i=(height-1) - y;

	r = sqrt(color.x) * 255;
	g = sqrt(color.y) * 255;
	b = sqrt(color.z) * 255;

	img[(j+i*width)*3+2] = (unsigned char)(r);
	img[(j+i*width)*3+1] = (unsigned char)(g);
	img[(j+i*width)*3+0] = (unsigned char)(b);
}
void Image::scaleImage(float lmax)
{
	//Scale img to [0,1]*255
	for(int i = 0; i < 3*width*height; i++)
	{
		img[i] = (img[i] / (sqrt(lmax) * 255) *255);

		if (img[i] > 255) 
			img[i]=255;
	}
}

void Image::saveImage()
{
	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
	unsigned char bmppad[3] = {0,0,0};

	bmpfileheader[ 2] = (unsigned char)(filesize    );
	bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(       width    );
	bmpinfoheader[ 5] = (unsigned char)(       width>> 8);
	bmpinfoheader[ 6] = (unsigned char)(       width>>16);
	bmpinfoheader[ 7] = (unsigned char)(       width>>24);
	bmpinfoheader[ 8] = (unsigned char)(       height    );
	bmpinfoheader[ 9] = (unsigned char)(       height>> 8);
	bmpinfoheader[10] = (unsigned char)(       height>>16);
	bmpinfoheader[11] = (unsigned char)(       height>>24);

	f = fopen("img.bmp","wb");
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);

	for(int i=0; i<height; i++)
	{
		fwrite(img+(width*(height-i-1)*3),3,width,f);
		fwrite(bmppad,1,(4-(width*3)%4)%4,f);
	}
	fclose(f);
}
