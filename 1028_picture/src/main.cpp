
#include <GLFW/glfw3.h>
#include <cstdlib>
// C++でファイルを扱うライブラリ
#include <fstream>
// C++で動的配列を扱うライブラリ
#include <vector>


// 指定テクスチャ識別子へ、
// ファイルから読み込んだデータを与える
// ※処理が成功すると true を返す
bool setupTexture(const GLuint id, const char* file) {

	
	// ファイルをバイナリモードで開く
	std::ifstream fstr(file, std::ios::binary);
	// ファイルが見つからない等のエラーがあれば
	// 処理を中断
	if (!fstr) return false;

	// ファイルサイズを取得
	//   読み込み位置をファイル末尾へ移動
	//   →ファイル先頭から読み込み位置までのオフセット
	//   ＝ファイルサイズ
	const size_t file_size
		= static_cast<size_t>(fstr.seekg(0, fstr.end).tellg());

	// 読み込み位置をファイル先頭へ戻す
	fstr.seekg(0, fstr.beg);

	// 動的配列を使ってファイルを読み込む場所を確保
	// charをfile_size個、メモリに確保する
	std::vector<char> texture_buffer(file_size);

	// 確保した場所へファイルの内容を全て読み込む
	fstr.read(&texture_buffer[0], file_size);

	
	// OpenGLに
	// 「これから、テクスチャ識別子idに対して指示を与えます」
	// と指示
	glBindTexture(GL_TEXTURE_2D, id);

	// １ピクセルに「赤、緑、青、アルファ」の情報を持つ
	// 幅512ピクセル、高さ512ピクセルの画像データをOpenGLへ転送
	glTexImage2D(GL_TEXTURE_2D,
		0, GL_RGBA, 512, 512,
		0, GL_RGBA, GL_UNSIGNED_BYTE,
		&texture_buffer[0]);

	// 画像が拡大された場合にどう振る舞うか指定
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 画像が縮小された場合にどう振る舞うか指定
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	return true;
}



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

  // OpenGLにテクスチャ識別子を１つ作ってもらう
  GLuint texture_id;
  glGenTextures(1, &texture_id);

  // 画像ファイルを読み込んで
  // テクスチャ識別子に設定する
  if (!setupTexture(texture_id, "sample.raw")) {
	  // 画像の読み込みに失敗したら、
	  // テクスチャ識別子を削除、GLFWの後始末をして終了
	  glDeleteTextures(1, &texture_id);
	  glfwTerminate();
	  return EXIT_FAILURE;
  }

  /*GLint* texture_width;
  GLint* texture_height;

  glGetTexLevelParameteriv(
	  GL_TEXTURE_2D, 0,
	  GL_TEXTURE_WIDTH, texture_width
	  );
  glGetTexLevelParameteriv(
	  GL_TEXTURE_2D, 0,
	  GL_TEXTURE_HEIGHT, texture_height
	  );
*/

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

	// 描画する矩形の４頂点を配列で用意    
	static const GLfloat vtx[] = {
		-256.f, -256.f,
		256.f, -256.f,
		256.f, 256.f,
		-256.f, 256.f
	};
	glVertexPointer(2, GL_FLOAT, 0, vtx);

	// 頂点ごとのテクスチャ座標を配列で準備
	static const GLfloat texture_uv[] = {
		0.0f, 2.0f,
		2.0f, 2.0f,
		2.0f, 0.0f,
		0.0f, 0.0f
	};

	static const GLfloat color[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f
	};

	// 色配列をOpenGLに指示
	glColorPointer(3, GL_FLOAT, 0, color);

	glTexCoordPointer(2, GL_FLOAT, 0, texture_uv);

	// OpenGLにテクスチャによる描画を有効にすると指示
	glEnable(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glEnableClientState(GL_VERTEX_ARRAY);

	// 色配列を使った描画を有効にする
	glEnableClientState(GL_COLOR_ARRAY);

	// 描画の時にテクスチャ座標配列も使うと指示
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// 矩形を１つ描画
	glDrawArrays(GL_QUADS, 0, 4);

	// 描画が済んだら使った機能を全て無効にする
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisable(GL_TEXTURE_2D);

	glfwSwapBuffers(window);
	glfwPollEvents();
  }

  // 使い終わったテクスチャ識別子を削除
  glDeleteTextures(1, &texture_id);

  glfwTerminate();

  return EXIT_SUCCESS;

}
