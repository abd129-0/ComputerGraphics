#include "game.h"
#include "MyCube.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

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

void Game::Init(Display* display)
{
    this->display = display;
    //Shaders
	AddShader("../res/shaders/pickingShader");	
	AddShader("../res/shaders/basicShader");

	//Textures
	AddTexture("../res/textures/plane.png",false);
	AddTexture("../res/textures/grass.bmp",false);
	AddTexture("../res/textures/bricks.jpg",false);

    //MyCube Construction and Init
    int indx =0 ;
    for(int i=-1; i<=1; i++)
    {
        for(int j=-1; j<=1; j++)
        {
            for(int k=-1; k<=1; k++)
            {
	            AddShape(Cube,-1,TRIANGLES); //Add Cube to scene
//                if(indx==26)
//                {
//                    SetShapeTex(indx, 1);
//                }
//                else if(indx==0)
//                {
//                    SetShapeTex(indx, 2);
//                }
//                else
//                {
                   SetShapeTex(indx, 0);
//                }

                shapes[indx]->MyScale(glm::vec3(0.5,0.5,0.5)); // Scale by 0.5
                shapes[indx]->MyTranslate(glm::vec3(i,j,k),0); //Move to initial position
                myCube.addCube(shapes[indx]);
                myCube.updateUnitCube(indx, glm::vec3(i,j,k)); //Set Position
                indx++;
            }
        }
    }

	pickedShape = 0;

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

void Game::RotateRightWall() {
    float fullAngleToRotate = myCube.angle*myCube.clockwise;
    float partialAngleToRotate = fullAngleToRotate/144.0f;
    float currentRotationAngle = 0.0f;
    while(std::abs(currentRotationAngle)<std::abs(fullAngleToRotate))
    {
        myCube.RotateRightWall(partialAngleToRotate);
        currentRotationAngle = currentRotationAngle + partialAngleToRotate;
        Draw(1,0,this->BACK,true,false);
        display->SwapBuffers();
        display->PollEvents();
    }
}

void Game::RotateLeftWall() {
    float fullAngleToRotate = myCube.angle*myCube.clockwise;
    float partialAngleToRotate = fullAngleToRotate/144.0f;
    float currentRotationAngle = 0.0f;
    while(std::abs(currentRotationAngle)<std::abs(fullAngleToRotate))
    {
        myCube.RotateLeftWall(partialAngleToRotate);
        currentRotationAngle = currentRotationAngle + partialAngleToRotate;
        Draw(1,0,this->BACK,true,false);
        display->SwapBuffers();
        display->PollEvents();
    }
}

void Game::RotateUpperWall() {
    float fullAngleToRotate = myCube.angle*myCube.clockwise;
    float partialAngleToRotate = fullAngleToRotate/144.0f;
    float currentRotationAngle = 0.0f;
    while(std::abs(currentRotationAngle)<std::abs(fullAngleToRotate))
    {
        myCube.RotateUpperWall(partialAngleToRotate);
        currentRotationAngle = currentRotationAngle + partialAngleToRotate;
        Draw(1,0,this->BACK,true,false);
        display->SwapBuffers();
        display->PollEvents();
    }
}

void Game::RotateDownWall() {
    float fullAngleToRotate = myCube.angle*myCube.clockwise;
    float partialAngleToRotate = fullAngleToRotate/144.0f;
    float currentRotationAngle = 0.0f;
    while(std::abs(currentRotationAngle)<std::abs(fullAngleToRotate))
    {
        myCube.RotateDownWall(partialAngleToRotate);
        currentRotationAngle = currentRotationAngle + partialAngleToRotate;
        Draw(1,0,this->BACK,true,false);
        display->SwapBuffers();
        display->PollEvents();
    }
}

void Game::RotateFrontWall() {
    float fullAngleToRotate = myCube.angle*myCube.clockwise;
    float partialAngleToRotate = fullAngleToRotate/144.0f;
    float currentRotationAngle = 0.0f;
    while(std::abs(currentRotationAngle)<std::abs(fullAngleToRotate))
    {
        myCube.RotateFrontWall(partialAngleToRotate);
        currentRotationAngle = currentRotationAngle + partialAngleToRotate;
        Draw(1,0,this->BACK,true,false);
        display->SwapBuffers();
        display->PollEvents();
    }
}

void Game::RotateBackWall() {
    float fullAngleToRotate = myCube.angle*myCube.clockwise;
    float partialAngleToRotate = fullAngleToRotate/144.0f;
    float currentRotationAngle = 0.0f;
    while(std::abs(currentRotationAngle)<std::abs(fullAngleToRotate))
    {
        myCube.RotateBackWall(partialAngleToRotate);
        currentRotationAngle = currentRotationAngle + partialAngleToRotate;
        Draw(1,0,this->BACK,true,false);
        display->SwapBuffers();
        display->PollEvents();
    }
}

void Game::changeClockwise() {
    myCube.FlipClockwise();
}

void Game::Randomizer() {
    myCube.Randomizer();
}

void Game::DivideAngle() {
    myCube.DivideAngle();
}

void Game::MultiplyAngle() {
    myCube.MultiplyAngle();
}

