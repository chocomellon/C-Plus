//
// 透視変換 & 行列
//

#include <GLFW/glfw3.h>


int main() {
  if (!glfwInit()) return -1;

  GLFWwindow* window = glfwCreateWindow(640, 480,
                                        "08 Matrix",
                                        nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  
  glfwSwapInterval(1);

  float angle = 0.0f;
  
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // 透視変換行列を操作するよ!! と宣言
    glMatrixMode(GL_PROJECTION);
    // 正規行列を読み込む
    glLoadIdentity();
    
    // 透視変換行列を作成して適用
    // glFrustum(GLdouble left, GLdouble right,
    //           GLdouble bottom, GLdouble top,
    //           GLdouble near, GLdouble far);
    //  左端の座標、右端の座標
    //  下端の座標、上端の座標
    //  最前面までの距離、最遠面までの距離(距離はどちらも0より大きい値)
    glFrustum(-1,  1,
               1, -1,
              0.5,  5.0);

    // モデリング行列を操作するよ!! と宣言
    glMatrixMode(GL_MODELVIEW);
    // 正規行列を読み込む
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, -1.5f);
    // 回転行列を適用
    // angle: 回転量(単位:degrees)
    // x, y, z: 回転軸を表すベクトル(単位ベクトルでなくてよい)
    glRotatef(angle, 1.0f, 1.0f, 1.0f);
    angle += 1.0f;
    
    // 頂点配列を用意
    static const GLfloat vtx[] = { 
       0.0f,  0.433f, 0.0f,
      -0.5f, -0.433f, 0.0f,
       0.5f, -0.433f, 0.0f,
    };

    glVertexPointer(3, GL_FLOAT, 0, vtx);
    
    glEnableClientState(GL_VERTEX_ARRAY);

    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);

    glfwSwapBuffers(window);

    glfwPollEvents();
  }

  glfwTerminate();
  
  return 0;
}
