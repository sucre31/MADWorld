#include <DxLib.h>
#include "System/Keyboard.h"
//#include "firebase/app.h"
//#include "firebase/database.h"
//#include "Common/Online/DataBaseListener.h"
#include "System/SystemMain.h"
#include "System/Define.h"
#include "System/Looper.h"

/*!
* @brief DXライブラリやゲームの初期処理
*/
bool SystemMain::initialize() const
{

	SetAlwaysRunFlag(TRUE);						//ウィンドウがノンアクティブでも実行
	SetWindowSizeChangeEnableFlag(FALSE);		//ウィンドウサイズを自由に変更できるようにする
	SetOutApplicationLogValidFlag(FALSE);		//ログ出力しない
	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_DESKTOP);	//フルスクリーン時に縦横比を維持する
	SetWindowText("MAD Heaven");				//ウィンドウタイトルを付ける
	ChangeWindowMode(TRUE);					//ウィンドウモードに変更
	SetWaitVSyncFlag(FALSE);					//垂直同期を設定
	SetWindowSizeExtendRate(1.0);				//ウィンドウサイズを変更したい時はここに倍率を指定する
	const int COLOR_BIT = 32;					//色のbit数。通常32で良いが軽くするなら16にする
	SetGraphMode(Define::WIN_W * Define::WIN_EX, Define::WIN_H * Define::WIN_EX, COLOR_BIT);		//ゲーム画面の解像度を設定する
	SetWindowIconID(101);						//アイコン設定
	SetMouseDispFlag(TRUE);					// カーソル表示
	SetUseTransColor(false);
	if (DxLib_Init()) {							//DXライブラリ初期化処理
		return false;							//異常終了したら即座にやめる
	}
	SetDrawScreen(DX_SCREEN_BACK);				//裏画面処理を設定する

	//// サーバー設定
	//firebase::AppOptions options;
	//firebase::App* app = firebase::App::Create(options);
	//firebase::database::Database* database = firebase::database::Database::GetInstance(app);
	//auto db_ref = database->GetReference("game_state/score");

	//DatabaseListener my_listener;
	//db_ref.AddValueListener(&my_listener); // 監視開始

	return true;
}

/*!
* @brief DXライブラリやゲームの終了処理
*/
void SystemMain::finalize() const
{
	DxLib_End();
}

/*!
* @brief メイン処理
*/
void SystemMain::main() const
{
	Looper looper;
	while (!ProcessMessage()) {
		if (!looper.loop()) {
			break;
		}
	}
}