#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#pragma once
#pragma comment(lib,"dll/glut.dll")
#pragma comment(lib,"dll/glfw3.lib")
#pragma comment(lib,"dll/glfw3dll.lib")
#pragma comment(lib,"dll/glew32.lib")
//#pragma comment(lib,"dll/glew32s.lib")
#pragma comment(lib,"opengl32.dll")
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
// GLFW
#include <GLFW/glfw3.h>

void draw_cube(double,double,double);
void key_callback(GLFWwindow*,int,int,int,int);

int win_high=600,win_length=600;
double time,last_time;
int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(win_high, win_length, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Needed in core profile
	if( glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	/* Loop until the user closes the window */
	/*
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit  100 units
	//glm::mat4 Projection = glm::ortho(-4.0f/3.0f, 4.0f/3.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	glm::mat4 Projection = glm::perspective(45.0f,4.0f/3.0f,0.1f,100.f);
	glm::mat4 View = glm::lookAt(
		glm::vec3(4,3,-3), // Camera is at (4,3,3), in World Space
		glm::vec3(0,0,0), // and looks at the origin
		glm::vec3(0,1,0) // Head is up (set to 0,-1,0 to look upside-down)		
		);

	//Model matrix : an identity matrix (model will be at the origin)
		glm::mat4 Model = glm::mat4(1.0f);
		
		// Our ModelViewProjection : multiplication of our 3 matrices
		glm::mat4 MVP = Projection * View * Model;// Remember, matrix multiplication is the other way around
		*/
	glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glShadeModel( GL_SMOOTH );
    // 黑色背景
    glClearColor( 0.5, 0.8, 0.9, 0.0 );
    // 设置深度缓存
    glClearDepth( 1.0 );
    // 启用深度测试
    glEnable( GL_DEPTH_TEST );
    // 所作深度测试的类型
    glDepthFunc( GL_LEQUAL );
    // 告诉系统对透视进行修正
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	

	//glTranslatef(0.0f,-4.0f,0.5f);
	glOrtho(-2.0,2.0,-2.0,2.0,-20.0,20.0);
	glRotatef(90.0f,0.9f  ,0.9f  ,0.8f  );
	glMatrixMode(GL_MODELVIEW);
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		//glTranslatef(0.0f  ,0.0f  ,0.5f  );
	    //glRotatef(0.2f,0.9f  ,0.9f  ,0.9f  );

		for(int x=0;x<60;x++)
		{
			for(int y=0;y<5;y++)
			{
				for(int z=0;z<60;z++)
				{
					draw_cube(x,y,z);
				}
			}
		}
		glfwSwapBuffers(window);
		last_time=time;
		time = glfwGetTime();
		double min=time-last_time;
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
GLdouble get_half(){			//单位长度的一半，相当于半格
	return 0.5f;
}
void draw_cube(double x,double y,double z){
	//front
	GLdouble half=0.5f,half_high=0.5f;
	glBegin(GL_QUADS);
	glColor3f(0.8f,0.4f,0.0f);
	glVertex3f(x-half,y+half_high,z+half);
	glVertex3f(x+half,y+half_high,z+half);
	glVertex3f(x+half,y-half_high,z+half);
	glVertex3f(x-half,y-half_high,z+half);
	glEnd();

	//back
	glBegin(GL_QUADS);
	glColor3f(0.8f,0.4f,0.0f);
	glVertex3f(x-half,y+half_high,z-half);
	glVertex3f(x+half,y+half_high,z-half);
	glVertex3f(x+half,y-half_high,z-half);
	glVertex3f(x-half,y-half_high,z-half);
	glEnd();

	//up
	glBegin(GL_QUADS);
	glColor3f(0.2f,0.8f,0.2f);
	glVertex3f(x-half,y+half_high,z+half);
	glVertex3f(x+half,y+half_high,z+half);
	glVertex3f(x+half,y+half_high,z-half);
	glVertex3f(x-half,y+half_high,z-half);
	glEnd();

	//down
	glBegin(GL_QUADS);
	glColor3f(0.8f,0.4f,0.0f);
	glVertex3f(x-half,y-half_high,z+half);
	glVertex3f(x+half,y-half_high,z+half);
	glVertex3f(x+half,y-half_high,z-half);
	glVertex3f(x-half,y-half_high,z-half);
	glEnd();

	//left
	glBegin(GL_QUADS);
	glColor3f(0.8f,0.4f,0.0f);
	glVertex3f(x-half,y-half_high,z+half);
	glVertex3f(x-half,y+half_high,z+half);
	glVertex3f(x-half,y+half_high,z-half);
	glVertex3f(x-half,y-half_high,z-half);
	glEnd();

	//right
	glBegin(GL_QUADS);
	glColor3f(0.8f,0.4f,0.0f);
	glVertex3f(x+half,y-half_high,z+half);
	glVertex3f(x+half,y+half_high,z+half);
	glVertex3f(x+half,y+half_high,z-half);
	glVertex3f(x+half,y-half_high,z-half);
	glEnd();
}
#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
	std::cout<<key<<" w="<<(int)'w'<<" ";
	switch(key)
	{
	case 87: //w
		glTranslatef(0.0f,0.0f,-0.05f);
		break;
	case 65: //a
		glTranslatef(-0.05f,0.0f,0.0f);
		break;
	case 83: //s
		glTranslatef(0.0f,0.0f,0.05f);
		break;
	case 68: //d
		glTranslatef(0.05f,0.0f,0.0f);
		break;
	case 340: //shift
		glTranslatef(0.0f,-0.05f,0.0f);
		break;
	case 341: //ctrl
		glTranslatef(0.0f,0.05f,0.0f);
		break;
	}
}