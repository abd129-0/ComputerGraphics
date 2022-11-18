#include "game.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <vector>

static void printMat(const glm::mat4 mat)
{
	std::cout<<" matrix:"<<std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout<< mat[j][i]<<" ";
		std::cout<<std::endl;
	}
}

Game::Game() : Scene()
{
}

Game::Game(float angle ,float relationWH, float near1, float far1) : Scene(angle,relationWH,near1,far1)
{ 	
}

std::vector<std::vector<unsigned char>> pixelsAverage(unsigned char* data) {
	std::vector<std::vector<unsigned char>> average;
	int counter = 0;
	for (int i = 0; i < 256; i++) {
		std::vector<unsigned char> vec;
		for (int j = 0; j < 256; j++) {
			vec.push_back((data[counter] + data[counter + 1] + data[counter + 2]) / 3);
			counter = counter + 4;
		}
		average.push_back(vec);
	}
	return average;
}


std::vector<std::vector<unsigned char>> floydAlgorithm(std::vector<std::vector<unsigned char>> data, unsigned char* original) {
	std::vector<std::vector<unsigned char>> floydData = pixelsAverage(original);
	for (int x = 1; x < 255; x++) {
		for (int y = 1; y < 255; y++) {
			char oldpixel = data[x][y];
			char newpixel = oldpixel/255;
			floydData[x][y] = newpixel;
			char quant_error = oldpixel - newpixel;
			floydData[x + 1][y] = floydData[x + 1][y] + quant_error * 7 / 16;
			floydData[x - 1][y + 1] = floydData[x - 1][y + 1] + quant_error * 1 / 16;
			floydData[x][y + 1] = floydData[x][y + 1] + quant_error * 5 / 16;
			floydData[x + 1][y + 1] = floydData[x + 1][y + 1] + quant_error * 3 / 16;
		}
	}
	return floydData;
}

unsigned char* averageToNormal(std::vector<std::vector<unsigned char>> average, unsigned char* data) {
	unsigned char* normal = (unsigned char*)malloc(512 * 512);
	int counter = 0;
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			normal[counter] = average[i][j];
			normal[counter+1] = average[i][j];
			normal[counter+2] = average[i][j];
			normal[counter + 3] = data[counter+3];
			counter = counter + 4;
		}
	}
	return normal;
}

void Game::Init()
{		
	int width, height, numComponents;
	unsigned char* data = stbi_load("../lena256.jpg", &width, &height, &numComponents, 4);


	AddShader("../res/shaders/pickingShader");	
	AddShader("../res/shaders/basicShader");

	AddTexture(256, 256, averageToNormal(pixelsAverage(data), data)); //index = 0; grayscale
	AddTexture(256, 256, data); //index = 1; halftone
	AddTexture(256, 256, averageToNormal(floydAlgorithm(pixelsAverage(data), data), data)); //index = 2; floyd
	AddTexture(256, 256, data); //index = 3; edges

	AddShape(Plane,-1,TRIANGLES);
	
	pickedShape = 0;
	
	SetShapeTex(0,0);
	MoveCamera(0,zTranslate,10);
	pickedShape = -1;
	
	//ReadPixel(); //uncomment when you are reading from the z-buffer
}

void Game::Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx)
{
	Shader *s = shaders[shaderIndx];
	int r = ((pickedShape+1) & 0x000000FF) >>  0;
	int g = ((pickedShape+1) & 0x0000FF00) >>  8;
	int b = ((pickedShape+1) & 0x00FF0000) >> 16;
	s->Bind();
	s->SetUniformMat4f("MVP", MVP);
	s->SetUniformMat4f("Normal",Model);
	s->SetUniform4f("lightDirection", 0.0f , 0.0f, -1.0f, 0.0f);
	if(shaderIndx == 0)
		s->SetUniform4f("lightColor",r/255.0f, g/255.0f, b/255.0f,1.0f);
	else 
		s->SetUniform4f("lightColor",0.7f,0.8f,0.1f,1.0f);
	s->Unbind();
}

void Game::WhenRotate()
{
}

void Game::WhenTranslate()
{
}

void Game::Motion()
{
	if(isActive)
	{
	}
}

Game::~Game(void)
{
}
