#include <Dxlib.h>
#include "SnippetSound.h"

SnippetSound::SnippetSound() {
    BackgroundMusic[0] = myLoadSoundMem("Assets/Sounds/Snippet/Music/snippetFix.wav");
    BackgroundMusic[1] = myLoadSoundMem("Assets/Sounds/Snippet/Music/Drum.wav");
    BackgroundMusic[2] = myLoadSoundMem("Assets/Sounds/Snippet/Music/Victorious.wav");
    lucasBattleSounds[0] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/Snippet1.wav");
    lucasBattleSounds[1] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/Snippet2.wav");
    lucasBattleSounds[2] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/Snippet3.wav");
    lucasBattleSounds[3] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/Snippet4.wav");
    lucasBattleSounds[4] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/Snippet5.wav");
    lucasBattleSounds[5] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/Snippet6.wav");
    lucasBattleSounds[6] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/Snippet7.wav");
    lucasBattleSounds[7] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/Snippet8.wav");
    lucasBattleSounds[8] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/SnippetA1.wav");
    lucasBattleSounds[9] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/SnippetB1.wav");
    lucasBattleSounds[10] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/SnippetC1.wav");
    lucasBattleSounds[11] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/SnippetD1.wav");
    lucasBattleSounds[12] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/SnippetA2.wav");
    lucasBattleSounds[13] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/SnippetB2.wav");
    lucasBattleSounds[14] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/SnippetC2.wav");
    lucasBattleSounds[15] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/SnippetD2.wav");
    lucasBattleSounds[16] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/SnippetA3.wav");
    lucasBattleSounds[17] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/SnippetB3.wav");
    lucasBattleSounds[18] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/SnippetC3.wav");
    lucasBattleSounds[19] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/SnippetD3.wav");
    lucasBattleSounds[20] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/SnippetA4.wav");
    lucasBattleSounds[21] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/SnippetB4.wav");
    lucasBattleSounds[22] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/SnippetC4.wav");
    lucasBattleSounds[23] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/SnippetD4.wav");
    lucasBattleSounds[24] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/LucasExtra1.wav");
    lucasBattleSounds[25] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/LucasExtra2.wav");
    lucasBattleSounds[26] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/LucasExtra3.wav");
    lucasBattleSounds[27] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/LucasExtraA.wav");
    lucasBattleSounds[28] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/LucasExtraB.wav");
    lucasBattleSounds[29] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/LucasExtraC.wav");
    lucasBattleSounds[30] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/LucasExtraD.wav");
    lucasBattleSounds[31] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/LucasExtraLast0.wav");
    lucasBattleSounds[32] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/LucasExtraLast1.wav");
    lucasBattleSounds[33] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/LucasExtraLast2.wav");
    lucasBattleSounds[34] = myLoadSoundMem("Assets/Sounds/Snippet/Lucas/LucasExtraLast3.wav");
    kumatoraBattleSounds[0] = myLoadSoundMem("Assets/Sounds/Snippet/Kumatora/Guitar0.wav");
    kumatoraBattleSounds[1] = myLoadSoundMem("Assets/Sounds/Snippet/Kumatora/Guitar1.wav");
    kumatoraBattleSounds[2] = myLoadSoundMem("Assets/Sounds/Snippet/Kumatora/Guitar2.wav");
    kumatoraBattleSounds[3] = myLoadSoundMem("Assets/Sounds/Snippet/Kumatora/Guitar3.wav");
    kumatoraBattleSounds[4] = myLoadSoundMem("Assets/Sounds/Snippet/Kumatora/Guitar4.wav");
    kumatoraBattleSounds[5] = myLoadSoundMem("Assets/Sounds/Snippet/Kumatora/Guitar5.wav");
    kumatoraBattleSounds[6] = myLoadSoundMem("Assets/Sounds/Snippet/Kumatora/Guitar6.wav");
    kumatoraBattleSounds[7] = myLoadSoundMem("Assets/Sounds/Snippet/Kumatora/Guitar7.wav");
    kumatoraBattleSounds[8] = myLoadSoundMem("Assets/Sounds/Snippet/Kumatora/Guitar8.wav");
    kumatoraBattleSounds[9] = myLoadSoundMem("Assets/Sounds/Snippet/Kumatora/Guitar9.wav");
    kumatoraBattleSounds[10] = myLoadSoundMem("Assets/Sounds/Snippet/Kumatora/Guitar10.wav");
    kumatoraBattleSounds[11] = myLoadSoundMem("Assets/Sounds/Snippet/Kumatora/Guitar11.wav");
    kumatoraBattleSounds[12] = myLoadSoundMem("Assets/Sounds/Snippet/Kumatora/Guitar12.wav");
    kumatoraBattleSounds[13] = myLoadSoundMem("Assets/Sounds/Snippet/Kumatora/Guitar13.wav");
    dusterBattleSounds[0] = myLoadSoundMem("Assets/Sounds/Snippet/Duster/DusterBass0.wav");
    dusterBattleSounds[1] = myLoadSoundMem("Assets/Sounds/Snippet/Duster/DusterBass1.wav");
    dusterBattleSounds[2] = myLoadSoundMem("Assets/Sounds/Snippet/Duster/DusterBass2.wav");
    dusterBattleSounds[3] = myLoadSoundMem("Assets/Sounds/Snippet/Duster/DusterBass3.wav");
    dusterBattleSounds[4] = myLoadSoundMem("Assets/Sounds/Snippet/Duster/DusterBass4.wav");
    dusterBattleSounds[5] = myLoadSoundMem("Assets/Sounds/Snippet/Duster/DusterBass5.wav");
    dusterBattleSounds[6] = myLoadSoundMem("Assets/Sounds/Snippet/Duster/DusterBass6.wav");
    dusterBattleSounds[7] = myLoadSoundMem("Assets/Sounds/Snippet/Duster/DusterBass7.wav");
    dusterBattleSounds[8] = myLoadSoundMem("Assets/Sounds/Snippet/Duster/DusterBass8.wav");
    dusterBattleSounds[9] = myLoadSoundMem("Assets/Sounds/Snippet/Duster/DusterBass9.wav");
    dusterBattleSounds[10] = myLoadSoundMem("Assets/Sounds/Snippet/Duster/DusterBass10.wav");
    dusterBattleSounds[11] = myLoadSoundMem("Assets/Sounds/Snippet/Duster/DusterBass11.wav");
    dusterBattleSounds[12] = myLoadSoundMem("Assets/Sounds/Snippet/Duster/DusterBass12.wav");
    dusterBattleSounds[13] = myLoadSoundMem("Assets/Sounds/Snippet/Duster/DusterBass13.wav");
    boneyBattleSounds[0] = myLoadSoundMem("Assets/Sounds/Snippet/Boney/BoneyBark0.wav");
    boneyBattleSounds[1] = myLoadSoundMem("Assets/Sounds/Snippet/Boney/BoneyBark1.wav");
    boneyBattleSounds[2] = myLoadSoundMem("Assets/Sounds/Snippet/Boney/BoneyBark2.wav");
    boneyBattleSounds[3] = myLoadSoundMem("Assets/Sounds/Snippet/Boney/BoneyBark3.wav");
    boneyBattleSounds[4] = myLoadSoundMem("Assets/Sounds/Snippet/Boney/BoneyBark4.wav");
    boneyBattleSounds[5] = myLoadSoundMem("Assets/Sounds/Snippet/Boney/BoneyBark5.wav");
    boneyBattleSounds[6] = myLoadSoundMem("Assets/Sounds/Snippet/Boney/BoneyBark6.wav");
    boneyBattleSounds[7] = myLoadSoundMem("Assets/Sounds/Snippet/Boney/BoneyBark7.wav");
    BattleSE[0] = myLoadSoundMem("Assets/Sounds/Snippet/Battle/Bash.wav");
    BattleSE[1] = myLoadSoundMem("Assets/Sounds/Snippet/Battle/AllyTurn.wav");
    BattleSE[2] = myLoadSoundMem("Assets/Sounds/Snippet/Battle/Smaash.wav");
    BattleSE[3] = myLoadSoundMem("Assets/Sounds/Snippet/Battle/Defeated.wav");
    BattleSE[4] = myLoadSoundMem("Assets/Sounds/Snippet/Battle/AllyDamage.wav");
    BattleSE[5] = myLoadSoundMem("Assets/Sounds/Snippet/Battle/BossDefeated.wav");
    BattleSE[6] = myLoadSoundMem("Assets/Sounds/Snippet/Battle/enemyActive.wav");
    BattleSE[7] = myLoadSoundMem("Assets/Sounds/Snippet/Battle/enemyPsi.wav");
    BattleSE[8] = myLoadSoundMem("Assets/Sounds/Snippet/Battle/Inflicted.wav");
    BattleSE[9] = myLoadSoundMem("Assets/Sounds/Snippet/Battle/MortalDamage.wav");
    EnemySE[0] = myLoadSoundMem("Assets/Sounds/Snippet/Enemy/MrBatty.wav");
    EnemySE[1] = myLoadSoundMem("Assets/Sounds/Snippet/Enemy/RockinGhost.wav");
    EnemySE[2] = myLoadSoundMem("Assets/Sounds/Snippet/Enemy/Rhinocerocket0.wav");
    EnemySE[3] = myLoadSoundMem("Assets/Sounds/Snippet/Enemy/Rhinocerocket1.wav");
    EnemySE[4] = myLoadSoundMem("Assets/Sounds/Snippet/Enemy/Rhinocerocket2.wav");
    EnemySE[5] = myLoadSoundMem("Assets/Sounds/Snippet/Enemy/Rhinocerocket3.wav");
    EnemySE[6] = myLoadSoundMem("Assets/Sounds/Snippet/Enemy/pigMaskCaptain.wav");
    EnemySE[7] = myLoadSoundMem("Assets/Sounds/Snippet/Enemy/spider.wav");
    EnemySE[8] = myLoadSoundMem("Assets/Sounds/Snippet/Enemy/steelMechorilla.wav");
    EnemySE[9] = myLoadSoundMem("Assets/Sounds/Snippet/Enemy/BarrelMan.wav");
    EnemySE[10] = myLoadSoundMem("Assets/Sounds/Snippet/Enemy/ReconMech.wav");
    EnemySE[11] = myLoadSoundMem("Assets/Sounds/Snippet/Enemy/ReconstructedCaribou.wav");
    EnemySE[12] = myLoadSoundMem("Assets/Sounds/Snippet/Enemy/ViolentRoach.wav");
    EnemySE[13] = myLoadSoundMem("Assets/Sounds/Snippet/Enemy/JealousBass.wav");
    EnemySE[14] = myLoadSoundMem("Assets/Sounds/Snippet/Enemy/BeatenDrum.wav");
    EnemySE[15] = myLoadSoundMem("Assets/Sounds/Snippet/Battle/hypnosis.wav");
}


/*!
@brief 今までロードした音声を解放する
*/
void SnippetSound::release()
{
    const int size = sounds.size();
    for (int i = 0; i < size; i++) {
        DeleteSoundMem(sounds[i]);
    }
    sounds.clear();
}

/*!
@brief LoadSoundMemをして、かつそのハンドルをメンバ変数に追加する
*/
int SnippetSound::myLoadSoundMem(char* fileName)
{
    int ret = LoadSoundMem(fileName);
    sounds.push_back(ret);
    return ret;
}

/*!
@brief LoadSoundMemをして、かつそのハンドルをメンバ変数に追加する
*/
int SnippetSound::myLoadSoundMem(const char* fileName)
{
    int ret = LoadSoundMem(fileName);
    sounds.push_back(ret);
    return ret;
}