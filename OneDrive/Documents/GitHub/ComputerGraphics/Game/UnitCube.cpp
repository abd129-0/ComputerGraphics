

#include "UnitCube.h"

UnitCube::UnitCube(int type, int mode) : Shape(type,mode) {

}
void UnitCube::updateCube(glm::vec3 pos) {
    this->x = pos.x;
    this->y = pos.y;
    this->z = pos.z;
}

