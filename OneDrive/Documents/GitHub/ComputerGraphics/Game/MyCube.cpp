
#include "MyCube.h"
#include "glm/gtc/matrix_transform.inl"
#include <random>
#include <unistd.h>

MyCube::MyCube()
{
    this->clockwise = 1.0f;
    this->angle = -90.0f;
}

void MyCube::addCube(Shape *&pShape)
{
    cubes.push_back(dynamic_cast<UnitCube*>(pShape));
}

void MyCube::FlipClockwise() {
    this->clockwise = -1.0f*clockwise;
}

void MyCube::Randomizer() {
    for(int i=0; i<100; i++)
    {
        // Create a random number generator
        std::random_device rd;  // Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
        std::uniform_int_distribution<> dis(1, 6);

        // Choose a random number between 1 and 6
        int option = dis(gen);

        //Choose random rotation
        switch (option)
        {
            case 1:
                RotateRightWall(-90.0f);
                break;
            case 2:
                RotateLeftWall(-90.0f);
                break;
            case 3:
                RotateUpperWall(-90.0f);
                break;
            case 4:
                RotateDownWall(-90.0f);
                break;
            case 5:
                RotateFrontWall(-90.0f);
                break;
            case 6:
                RotateBackWall(-90.0f);
                break;
        }
    }


}

void MyCube::DivideAngle() {
    this->angle = -1.0f*std::fmax(-1.0f*this->angle/2.0f, 1.0f);
}

void MyCube::MultiplyAngle() {
    this->angle = -1.0f*std::fmin(-1.0f*this->angle*2.0f, 180.0f);
}

void MyCube::updateUnitCube(int index, glm::vec3 pos) {
    cubes[index]->updateCube(pos);
}



//==========================================Wall Rotations==================================================

void MyCube::RotateRightWall(float angle) {
    for(UnitCube* cube : cubes)
    {
        if (cube->x <= 1.008 && cube->x >= 0.992)  // 1 is the x-coordinate of the right wall
        {
                glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f,0.0f,0.0f));
                glm::vec3 newPos = glm::vec3(rotationMatrix * glm::vec4(cube->x, cube->y, cube->z, 1.0f));
                glm::vec3 originalCubePos = glm::vec3(cube->x, cube->y, cube->z);
                newPos.x = 1.0f;
                glm::vec3 translationVector = newPos-originalCubePos;
                cube->MyTranslate(translationVector,0);
                cube->MyRotate(angle, glm::vec3(1.0f,0.0f,0.0f), 0);
                cube->updateCube(newPos);
        }
    }
}

void MyCube::RotateLeftWall(float angle) {
    for(UnitCube* cube : cubes)
    {
        if (cube->x >= -1.008 && cube->x <= -0.992)  // 1 is the x-coordinate of the right wall
        {
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f,0.0f,0.0f));
            glm::vec3 newPos = glm::vec3(rotationMatrix * glm::vec4(cube->x, cube->y, cube->z, 1.0f));
            glm::vec3 originalCubePos = glm::vec3(cube->x, cube->y, cube->z);
            newPos.x = -1.0f;
            glm::vec3 translationVector = newPos-originalCubePos;
            cube->MyTranslate(translationVector,0);
            cube->MyRotate(angle, glm::vec3(1.0f,0.0f,0.0f), 0);
            cube->updateCube(newPos);
        }
    }
}

void MyCube::RotateUpperWall(float angle) {
    for(UnitCube* cube : cubes)
    {
        if (cube->y <= 1.008 && cube->y >= 0.992)  // 1 is the x-coordinate of the right wall
        {
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f,1.0f,0.0f));
            glm::vec3 newPos = glm::vec3(rotationMatrix * glm::vec4(cube->x, cube->y, cube->z, 1.0f));
            glm::vec3 originalCubePos = glm::vec3(cube->x, cube->y, cube->z);
            newPos.y = 1.0f;
            glm::vec3 translationVector = newPos-originalCubePos;
            cube->MyTranslate(translationVector,0);
            cube->MyRotate(angle, glm::vec3(0.0f,1.0f,0.0f), 0);
            cube->updateCube(newPos);
        }
    }
}

void MyCube::RotateDownWall(float angle) {
    for(UnitCube* cube : cubes)
    {
        if (cube->y >= -1.008 && cube->y <= -0.992)  // 1 is the x-coordinate of the right wall
        {
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f,1.0f,0.0f));
            glm::vec3 newPos = glm::vec3(rotationMatrix * glm::vec4(cube->x, cube->y, cube->z, 1.0f));
            glm::vec3 originalCubePos = glm::vec3(cube->x, cube->y, cube->z);
            newPos.y = -1.0f;
            glm::vec3 translationVector = newPos-originalCubePos;
            cube->MyTranslate(translationVector,0);
            cube->MyRotate(angle, glm::vec3(0.0f,1.0f,0.0f), 0);
            cube->updateCube(newPos);
        }
    }
}

void MyCube::RotateFrontWall(float angle) {
    for(UnitCube* cube : cubes)
    {
        if (cube->z <= 1.008 && cube->z >= 0.992)  // 1 is the x-coordinate of the right wall
        {
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f,0.0f,1.0f));
            glm::vec3 newPos = glm::vec3(rotationMatrix * glm::vec4(cube->x, cube->y, cube->z, 1.0f));
            glm::vec3 originalCubePos = glm::vec3(cube->x, cube->y, cube->z);
            newPos.z = 1.0f;
            glm::vec3 translationVector = newPos-originalCubePos;
            cube->MyTranslate(translationVector,0);
            cube->MyRotate(angle, glm::vec3(0.0f,0.0f,1.0f), 0);
            cube->updateCube(newPos);
        }
    }
}

void MyCube::RotateBackWall(float angle) {
    for(UnitCube* cube : cubes)
    {
        if (cube->z >= -1.008 && cube->z <= -0.992)  // 1 is the x-coordinate of the right wall
        {
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f,0.0f,1.0f));
            glm::vec3 newPos = glm::vec3(rotationMatrix * glm::vec4(cube->x, cube->y, cube->z, 1.0f));
            glm::vec3 originalCubePos = glm::vec3(cube->x, cube->y, cube->z);
            newPos.z = -1.0f;
            glm::vec3 translationVector = newPos-originalCubePos;
            cube->MyTranslate(translationVector,0);
            cube->MyRotate(angle, glm::vec3(0.0f,0.0f,1.0f), 0);
            cube->updateCube(newPos);
        }
    }
}



