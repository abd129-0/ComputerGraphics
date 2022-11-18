#include "game.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <vector>

void export_file1(char* fileName, std::vector<std::vector<unsigned char>> data) {
	FILE* file = fopen(fileName, "w");
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[i].size(); j++) {
			if (i < 255 || j < 255) {
				if (data[i][j] == 0) {
					fprintf(file, "0,");
				}
				else {
					fprintf(file, "1,");
				}
			}
			else if (data[i][j] == 0) {
				fprintf(file, "0");
			}
			else {
				fprintf(file, "1");
			}
		}
	}
	fclose(file);
}
void export_file2(char* fileName, std::vector<std::vector<unsigned char>> data) {
	FILE* file = fopen(fileName, "w");
	for (int i = 0; i < data.size(); i++) {
		for (int j = 0; j < data[i].size(); j++) {
			fprintf(file, "%d,", data[i][j] / 16);
		}
	}
	fclose(file);
}

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

std::vector<std::vector<unsigned char>> pixelsAverage(unsigned char* data, int square) {
	std::vector<std::vector<unsigned char>> average;
	int counter = 0;
	for (int i = 0; i < square; i++) {
		std::vector<unsigned char> vec;
		for (int j = 0; j < square; j++) {
			unsigned char ch = (data[counter] + data[counter + 1] + data[counter + 2]) / 3;
			vec.push_back(ch);
			counter = counter + 4;
		}
		average.push_back(vec);
	}
	return average;
}

std::vector<std::vector<unsigned char>>  hysteresis(std::vector<std::vector<unsigned char>> data) {
	std::vector<std::vector<unsigned char>>  finalTouch;
	for (int i = 0; i < data.size(); i++) {
		std::vector<unsigned char> vec;
		for (int j = 0; j < data[i].size(); j++) {
			if (data[i][j] == 75) {
				if (i - 1 >= 0 & j - 1 >= 0 & i + 1 < data[i].size() & j + 1 < data[i].size()) {
					if ((data[(i - 1)][j - 1] == 255) || (data[(i - 1)][j] == 255) || (data[(i - 1)][j + 1] == 255) || (data[i][j - 1] == 255) ||
						(data[i][j + 1] == 255) || (data[(i + 1)][j - 1] == 255) || (data[(i + 1)][j] == 255) || (data[(i + 1)][j + 1] == 255)) {
						vec.push_back(255);
					} else {
						vec.push_back(0);
					}
				} else vec.push_back(255);
			} else {
				vec.push_back(data[i][j]);
			}
		}
		finalTouch.push_back(vec);
	}
	export_file1("../img4.txt", finalTouch);
	return finalTouch;
}

unsigned char getAngle(unsigned char byte) {
	unsigned char val = byte * (unsigned char)(180 / 3.14);
	if (val < 0) 
		return val + 180;
	return val;
}

std::vector<std::vector<unsigned char>>  non_max_suppression(std::vector<std::vector<unsigned char>>  data) {
	std::vector<std::vector<unsigned char>> nonmax;

	for (int i = 0; i < 256; i++) {
		std::vector<unsigned char> vec;
		for (int j = 0; j < 256; j++) {
			unsigned char val2 = 0;
			if (i - 1 >= 0 & j - 1 >= 0 & i + 1 < data[i].size() & j + 1 < data[i].size()) {
				unsigned char val = getAngle(data[i][j]);
				int q = 255;
				int r = 255;
				if ((0 <= val < 22.5) | (157.5 <= val <= 180))
				{
					q = data[i][j + 1]; r = data[i][j - 1];
				}
				else if (22.5 <= val < 67.5) {
					q = data[i + 1][j - 1]; r = data[i - 1][j + 1];
				}
				else if (67.5 <= val < 112.5) {
					q = data[i + 1][j]; r = data[i - 1][j];
				}
				else if (112.5 <= val < 157.5) {
					q = data[i - 1][j - 1]; r = data[i + 1][j + 1];
				}
				if ((data[i][j] >= q) & (data[i][j] >= r)) {
					val2 = data[i][j];
				}
				//threshold
				if (val2 >= 180)
					val2 = 255;
				else if (val2 <= 25)
					val2 = 0;
				else
					val2 = 75;
			}
			vec.push_back(val2);
		}
		nonmax.push_back(vec);
	}
	return hysteresis(nonmax);
}

std::vector<std::vector<unsigned char>> edgeAlgorithm(std::vector<std::vector<unsigned char>>  data) {
	std::vector<std::vector<unsigned char>> edge;
	int counter = 0;
	for (int i = 0; i < 256; i++) {
		std::vector<unsigned char> vec;
		unsigned char val = 0;
		for (int j = 0; j < 256; j++, counter++) {
			if (i - 1 >= 0 & j - 1 >= 0 & i + 1 < 256 & j + 1 < 256) {
				char gx = data[i - 1][j - 1] + 2 * data[i - 1][j] + data[i - 1][j + 1]
					- data[i + 1][j - 1] - 2 * data[i + 1][j] - data[i + 1][j + 1];
				char gy = -data[i + 1][j - 1] - 2 * data[i][j - 1] - data[i - 1][j - 1]
					+ data[i + 1][j + 1] + 2 * data[i][j + 1] + data[i - 1][j + 1];
				val = std::abs(gx) + std::abs(gy);
			}
			vec.push_back(val);
		}
		edge.push_back(vec);
	}
	return non_max_suppression(edge);
}

std::vector<std::vector<unsigned char>> halftoneAlgorithm(std::vector<std::vector<unsigned char>> averageData, unsigned char* original) {
	std::vector<std::vector<unsigned char>> halftone;
	for (int i = 0; i < 256; i++) {
		std::vector<unsigned char> line1;
		std::vector<unsigned char> line2;
		for (int j = 0; j < 256; j++) {
			int steps = averageData[i][j] / 51;
			switch (steps)
			{
			case 1: {
				line1.push_back(0);
				line1.push_back(0);
				line2.push_back(255);
				line2.push_back(0);
				break;
			}
			case 2: {
				line1.push_back(0);
				line1.push_back(255);
				line2.push_back(255);
				line2.push_back(0);
				break;
			}
			case 3: {
				line1.push_back(0);
				line1.push_back(255);
				line2.push_back(255);
				line2.push_back(255);
				break;
			}
			case 4: {
				line1.push_back(255);
				line1.push_back(255);
				line2.push_back(255);
				line2.push_back(255);
				break;
			}
			default:
				line1.push_back(0);
				line1.push_back(0);
				line2.push_back(0);
				line2.push_back(0);
				break;
			}
		}
		halftone.push_back(line1);
		halftone.push_back(line2);
	}
	export_file1("../img5.txt", halftone);
	return halftone;
}

std::vector<std::vector<unsigned char>> floydAlgorithm(std::vector<std::vector<unsigned char>> data, unsigned char* original) {
	std::vector<std::vector<unsigned char>> floydData = pixelsAverage(original, 256);
	for (int x = 1; x < 255; x++) {
		for (int y = 1; y < 255; y++) {
			char oldpixel = data[x][y];
			char newpixel = oldpixel/255;
			floydData[x][y] = newpixel;
			char quant_error = oldpixel - newpixel;
			floydData[x + 1][y] = data[x + 1][y] + quant_error * 7 / 16;
			floydData[x - 1][y + 1] = data[x - 1][y + 1] + quant_error * 1 / 16;
			floydData[x][y + 1] = data[x][y + 1] + quant_error * 5 / 16;
			floydData[x + 1][y + 1] = data[x + 1][y + 1] + quant_error * 3 / 16;
		}
	}
	export_file2("../img6.txt", floydData);
	return floydData;
}

unsigned char* averageToNormal(std::vector<std::vector<unsigned char>> average, unsigned char* data, int multiplier) {
	unsigned char* normal = (unsigned char*)malloc(512 * 512 * multiplier * multiplier);
	int counter = 0;
	int counter2 = 3;
	for (int i = 0; i < average.size(); i++) {
		for (int j = 0; j < average[i].size(); j++) {
			normal[counter] = average[i][j];
			normal[counter + 1] = average[i][j];
			normal[counter + 2] = average[i][j];
			normal[counter + 3] = data[counter2];
			counter = counter + 4;
			if (j % 2 == 1) counter2 = counter2 + 4;
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

	AddTexture(256, 256, averageToNormal(pixelsAverage(data, 256), data, 1)); //index = 0; grayscale
	AddTexture(512, 512, averageToNormal(halftoneAlgorithm(pixelsAverage(data, 256), data), data, 2)); //index = 1; halftone
	AddTexture(256, 256, averageToNormal(floydAlgorithm(pixelsAverage(data, 256), data), data, 1)); //index = 2; floyd
	AddTexture(256, 256, averageToNormal(edgeAlgorithm(pixelsAverage(data, 256)), data, 1)); //index = 3; edges

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