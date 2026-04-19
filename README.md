音と映像のリアルタイムな同期


### サーバー通信について
- Firebaseを利用したhttp通信
1. unityで構成したwebGLアプリでサーバーにhttp通信
2. firebaseのrealtime databaseが更新
3. Dxlibのゲーム側で更新検知
↓
大体400~500msくらいの遅延
→リアルタイムで音ゲー的に観客に操作させるには厳しそう

- webSocketの利用
1. Renderでサーバーを構成
2. DxlibでwebSocket通信
- ixwebsocketはDxlibとの依存解消に手間取ったので  
  最終的にwinHTTPを利用した。  
↓  
Dxlibのみでsend-recieveすると大体80~100msくらいの遅延
→かなり遅延を抑えられたので、スマホをコントローラにできそう  
ただ会場の環境や、webGLでの通信を行ったときにに生じるラグが気になる...



### 素材動画のロードについて
今mp4だと読み込めず落ちてしまうことがある
デコード周りを直す必要がありそう

とりあえず素材側で対応