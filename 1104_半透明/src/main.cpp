#define _USE_MATH_DEFINES   // Widnows:M_PIとかを使う

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>


int window_width  = 640;
int window_height = 480;


// Windowのサイズが変更された
void changeWindowSize(GLFWwindow* window, 
                      const int width, const int height) {
  window_width  = width;
  window_height = height;
}


int main(void)
{
  /* Initialize the library */
  if (!glfwInit())
    return -1;

  /* Create a windowed mode window and its OpenGL context */
  GLFWwindow* window = glfwCreateWindow(window_width, window_height,
                                        "Yagiiiiiiii", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  // GLFWにサイズ変更のコールバックを登録
  glfwSetWindowSizeCallback(window, changeWindowSize);

  // Swap間隔を設定(60fps)
  glfwSwapInterval(1);

  while (!glfwWindowShouldClose(window))
  {
	  float ratio;

    glViewport(0, 0, window_width, window_height);

	ratio = window_width / (float)window_height;


    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 正投影行列を作り、現在の行列に掛け合わせる
    // glOrtho(左X座標, 右X座標, 下Y座標, 上Y座標, 
    //         手前Z座標, 奥Z座標)
    glOrtho(-window_width / 2, window_width / 2, 
            -window_height / 2, window_height / 2,
            -1.0f, 1.0f);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	//ブレンディングを有効にする
	glEnable(GL_BLEND);	
	//ブレンディングの計算方法を指示
	glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
//	glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.f);

	glBegin(GL_QUADS);
	glColor4f(1.f, 0.f, 0.f,0.5f);
	glVertex3f(-0.5f, -0.5f, 0.f);
	glColor4f(0.f, 1.f, 0.f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.f);
	glColor4f(1.f, 0.f, 1.f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.f);
	glColor4f(0.f, 0.f, 1.f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.f);
	glEnd();


	glBegin(GL_TRIANGLES);
	glColor4f(1.f, 0.f, 0.f, 0.5f);
	glVertex3f(-0.6f, -0.4f, 0.f);
	glColor4f(0.f, 1.f, 0.f, 0.5f);
	glVertex3f(0.6f, -0.4f, 0.f);
	glColor4f(0.f, 0.f, 1.f, 0.5f);
	glVertex3f(0.f, 0.6f, 0.f);
	glEnd();



	glfwSwapBuffers(window);
	glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
