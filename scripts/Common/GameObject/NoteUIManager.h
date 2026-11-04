#include "NoteManager.h"
#include "GameObject.h"
#include "SozaiManager.h"

class NoteUIManager : public GameObject{
private:
    NoteManager& noteManager;
    SozaiManager& sozaiManager;
    int appearDurationMs = 1000; // ノーツが画面に出現してから判定されるまでの時間（アプローチ時間）
    int noteImages[8];

public:
    NoteUIManager(NoteManager& nm, SozaiManager& sm);

    bool update() override;
    void draw() const override;
};