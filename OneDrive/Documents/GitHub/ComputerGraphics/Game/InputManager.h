#pragma once   //maybe should be static class
#include "display.h"
#include "game.h"



    void mouse_callback(GLFWwindow* window,int button, int action, int mods)
	{	
		if(action == GLFW_PRESS )
		{
			Game *scn = (Game*)glfwGetWindowUserPointer(window);
			double x2,y2;
			glfwGetCursorPos(window,&x2,&y2);
			scn->Picking((int)x2,(int)y2);
		}
	}
	
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Game *scn = (Game*)glfwGetWindowUserPointer(window);
        scn->MoveCamera(0,2,(-4)*yoffset);
	}
	
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Game *scn = (Game*)glfwGetWindowUserPointer(window);

		if(action == GLFW_PRESS || action == GLFW_REPEAT)
		{
			switch (key)
			{
				case GLFW_KEY_ESCAPE:			
					glfwSetWindowShouldClose(window,GLFW_TRUE);
				break;

				case GLFW_KEY_UP:
                    scn->MyRotate(4, glm::vec3(1,0,0), 0);
					break;
				case GLFW_KEY_DOWN:
					//scn->shapeTransformation(scn->xGlobalRotate,-5.f);
					//cout<< "down: "<<endl;
                    scn->MyRotate(-4, glm::vec3(1,0,0), 0);
					break;
                case GLFW_KEY_LEFT:
                    scn->MyRotate(4, glm::vec3(0,1,0), 0);
                    break;
                case GLFW_KEY_RIGHT:
                    //scn->shapeTransformation(scn->xGlobalRotate,-5.f);
                    //cout<< "down: "<<endl;
                    scn->MyRotate(-4, glm::vec3(0,1,0), 0);
                    break;
                case GLFW_KEY_R:
                    scn->RotateRightWall();
                    break;
                case GLFW_KEY_L:
                    scn->RotateLeftWall();
                    break;
                case GLFW_KEY_U:
                    scn->RotateUpperWall();
                    break;
                case GLFW_KEY_D:
                    scn->RotateDownWall();
                    break;
                case GLFW_KEY_F:
                    scn->RotateFrontWall();
                    break;
                case GLFW_KEY_B:
                    scn->RotateBackWall();
                    break;
                case GLFW_KEY_SPACE:
                    scn->changeClockwise();
                    break;
                case GLFW_KEY_N:
                    scn->Randomizer();
                    break;
                case GLFW_KEY_0:
                    scn->ZeroTrans();
                    break;
                case GLFW_KEY_Z:
                    scn->DivideAngle();
                    break;
                case GLFW_KEY_A:
                    scn->MultiplyAngle();
                    break;

			default:
				break;
			}
		}
	}
	
	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
	{
		Game *scn = (Game*)glfwGetWindowUserPointer(window);

		scn->UpdatePosition((float)xpos,(float)ypos);
		if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			scn->MouseProccessing(GLFW_MOUSE_BUTTON_RIGHT);
		}
		else if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			scn->MouseProccessing(GLFW_MOUSE_BUTTON_LEFT);
		}

	}

	void window_size_callback(GLFWwindow* window, int width, int height)
	{
		Game *scn = (Game*)glfwGetWindowUserPointer(window);

		scn->Resize(width,height);
		
	}

	void Init(Display &display)
	{
		display.AddKeyCallBack(key_callback);
		display.AddMouseCallBacks(mouse_callback,scroll_callback,cursor_position_callback);
		display.AddResizeCallBack(window_size_callback);
	}
