
#include "scene.h"
#include "MyCube.h"
#include "display.h"

class Game : public Scene
{
public:
	
	Game();
	Game(float angle,float relationWH,float near, float far);
	void Init(Display* display);
	void Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx);
	void ControlPointUpdate();
	void WhenRotate();
	void WhenTranslate();
	void Motion();
	~Game(void);

    MyCube myCube;
    void RotateRightWall();

    void RotateLeftWall();

    void RotateUpperWall();

    void RotateDownWall();

    void RotateFrontWall();

    void RotateBackWall();

    void changeClockwise();

    void Randomizer();

    void DivideAngle();

    void MultiplyAngle();

    Display *display;
};

