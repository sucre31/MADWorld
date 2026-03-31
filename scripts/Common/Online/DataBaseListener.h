//#include "DxLib.h"
//#include "firebase/app.h"
//#include "firebase/database.h"
//
//// データを監視するクラス（ValueListenerを継承）
//class DatabaseListener : public firebase::database::ValueListener {
//public:
//    int current_value = 0; // ここに最新の値を保存する
//
//    // Firebase側でデータが変わると自動で呼ばれる
//    void OnValueChanged(const firebase::database::DataSnapshot& snapshot) override;
//    void OnCancelled(const firebase::database::Error& error, const char* msg) override;
//};