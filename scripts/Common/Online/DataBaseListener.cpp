//#include "DataBaseListener.h"

//void DatabaseListener::OnValueChanged(const firebase::database::DataSnapshot& snapshot){
//    if (snapshot.exists() && snapshot.value().is_int64()) {
//        current_value = (int)snapshot.value().int64_value();
//    }
//}
//
//void DatabaseListener::OnCancelled(const firebase::database::Error& error, const char* msg){
//    // エラー時の処理（必要なら）
//}