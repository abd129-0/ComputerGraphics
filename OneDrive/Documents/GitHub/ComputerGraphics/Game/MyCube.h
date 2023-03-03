
#ifndef GAME_MYCUBE_H
#define GAME_MYCUBE_H

#include <vector>
#include "UnitCube.h"
#include "shape.h"


class MyCube {
    public:
        std::vector<UnitCube*> cubes;
        MyCube();
        float clockwise;
        float angle;

    void addCube(Shape *&pShape);

    void RotateRightWall(float angle);

    void updateUnitCube(int i, glm::vec3 pos);

    void RotateLeftWall(float angle);

    void RotateUpperWall(float angle);

    void RotateDownWall(float angle);

    void RotateFrontWall(float angle);

    void RotateBackWall(float angle);

    void FlipClockwise();

    void Randomizer();

    void DivideAngle();

    void MultiplyAngle();
};


#endif //GAME_MYCUBE_H
