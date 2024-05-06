#include <Novice.h>
#include "MyNovice.h"
#include<memory>
#include "SceneManager.h"

const char kWindowTitle[] = "LE2A_06_オオハラアオイ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	int windowX = 1280;
	int windowY = 720;
	Novice::Initialize(kWindowTitle, windowX, windowY);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	std::unique_ptr<SceneManager> scene = std::make_unique<SceneManager>();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///------------------///
		/// ↓更新処理ここから
		///------------------///

		MyNovice::Updata();

		scene->Update();

		Vec2f mousePos = MyNovice::GetMousePosf();

		Vec2 mouseAddress = { int(mousePos.x / 64.0f) , int(mousePos.y / 64.0f)  };


		///------------------///
		/// ↑更新処理ここまで
		///------------------///

		///------------------///
		/// ↓描画処理ここから
		///------------------///


		Novice::ScreenPrintf(100, 100, "mousePos:%f, %f", MyNovice::GetMousePosf().x, MyNovice::GetMousePosf().y);
		Novice::ScreenPrintf(100, 120, "mouseAddress row:col %d, %d", mouseAddress.y, mouseAddress.x);

		///------------------///
		/// ↑描画処理ここまで
		///------------------///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
