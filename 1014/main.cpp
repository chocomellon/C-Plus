////GLFWテスト
//
////ヘッダをインクルード
//#include<GLFW\glfw3.h>
//
////	<	>	システムヘッダ（元から入ってる）
////	"	"	ユーザーヘッダ（書いた）
//
//int main()
//{
//	//初期化
//	glfwInit();
//
//

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include<cmath>
#include<random>

#define _CORNER	100
#define _PI	3.14159265358979323846264338327950288 

static void error_callback(int error, const char* description){
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)        glfwSetWindowShouldClose(window, GL_TRUE);
}

static void changeWindowSize(GLFWwindow* window, const int width, const int height){
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, width, 0.0f, height, -1.0f, 1.0f);
}

int main(void){
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())        exit(EXIT_FAILURE);
	window = glfwCreateWindow(640, 640, "Yagi Sample", NULL, NULL);

	if (!window)    {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);

	float theta = 0;

	glfwSwapInterval(1);
	glViewport(0, 0, 640, 640);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0f, 640.0f, 0.0f, 640.0f, -1.0f, 1.0f);

	int width = 640;
	int height = 640;

	while (!glfwWindowShouldClose(window))    {

		glfwSetWindowSizeCallback(window, changeWindowSize);

		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat vtx[_CORNER * 2];
		GLfloat color[_CORNER * 3];

		for (int i = 0; i < _CORNER; ++i) {
			// 「計算途中、double→floatの変換で精度が落ちますよ」
			// とコンパイラが警告を出すので、
			// 問題ないとコンパイラに伝える為のC++形式のキャスト
			// static_cast<型>(式)
			GLfloat angle
				= static_cast<GLfloat>(((_PI * 2.0 * i) / _CORNER)+theta);

			vtx[i * 2] = width/2+std::sin(angle) * 50.0f;
			vtx[i * 2 + 1] = height/2+std::cos(angle) * 50.0f;

			color[0] = 1.0;
			if (i != 0)color[i * 2] = static_cast<GLfloat>(1.0 / _CORNER)*(i%3);
			color[i * 2 + 1] = 1.0f;
			color[i * 2 + 2] = 1.0f;
		}

		// 色配列をOpenGLに指示
		glColorPointer(3, GL_FLOAT, 0, color);

		// 頂点配列を使った描画を有効にする
		glEnableClientState(GL_VERTEX_ARRAY);

		// 色配列を使った描画を有効にする
		glEnableClientState(GL_COLOR_ARRAY);

		//				次元数、型、、データ位置
		glVertexPointer(2, GL_FLOAT, 0, vtx);

		//	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

		glDrawArrays(GL_TRIANGLE_FAN, 0, _CORNER);

//		glRotatef((float)glfwGetTime(), 0.f, 0.f, 1.f);

		glfwSetWindowSizeCallback(window,changeWindowSize);

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		theta -= 0.1f;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}