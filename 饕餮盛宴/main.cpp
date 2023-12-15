#include "avz.h"
#include "AutoFodder/main.h"

/*
双冰变奏ch6 | I-PP | PP | I-PP | PP | (11.5, 6, 11.5, 6)
第1波预判炸，第2波预判炸。10个加速波+11.5s的波长可以保证在用冰有盈余的前提下实现稳定控丑。
PPIPIPIPI IPIPIPIPIP I
*/

APlantFixer pumpkinFixer;

void AFK() {
    // 挂机
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    // 十倍速
    ASetGameSpeed(10);
}


void preWaveFire() {
    aCobManager.Fire(2, 9);
    aCobManager.Fire(5, 9);
}

void normalWaveFire() {
    aCobManager.Fire(2, 9);
    aCobManager.Fire(5, 9);
}

void lastWaveFire() {
    aCobManager.RecoverFire(2, 9);
    aCobManager.RecoverFire(5, 9);
}

void AScript() {
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    ASetZombies({AZOMBIE,
                 APOLE_VAULTING_ZOMBIE,
                 AFOOTBALL_ZOMBIE,
                 ADANCING_ZOMBIE,
                 AZOMBONI,
                 AJACK_IN_THE_BOX_ZOMBIE,
                 ABALLOON_ZOMBIE,
                 ADIGGER_ZOMBIE,
                 APOGO_ZOMBIE,
                 ALADDER_ZOMBIE,
                 ABUNGEE_ZOMBIE,
                 ACATAPULT_ZOMBIE,
                 ADOLPHIN_RIDER_ZOMBIE,
                 AGARGANTUAR,
                 AGIGA_GARGANTUAR
    });

    // 选卡
    ASelectCards({AM_ICE_SHROOM,
                  ASUN_SHROOM,
                  APUFF_SHROOM,
                  APUMPKIN,
                  AFLOWER_POT,
                  ALILY_PAD,
                  ASCAREDY_SHROOM,
                  ACOFFEE_BEAN,
                  AICE_SHROOM,
                  ACHERRY_BOMB});

    // 开启10倍速挂机
    //AFK();

    // 初始化炮位
    AConnect(ATime(1, -599), []{ aCobManager.AutoSetList(); });

    // 自动存冰
    aIceFiller.Start({{3, 9}, {4, 9}});

    // 自动修补南瓜
    pumpkinFixer.Start(APUMPKIN, {{3, 9}, {4, 9}, {1, 1}, {2, 1}, {5, 1}, {6, 1}}, 4000 / 3 * 2);

    // 自动垫材
    AConnect([=]{return true;}, [=]{
        AAutoFodder({{1, 7}, {2, 7}, {5, 7}, {6, 7}}, {}, {APUFF_SHROOM, ASUN_SHROOM, AFLOWER_POT, ASCAREDY_SHROOM}, 79);
    });

    // PP
    for (int wave : {1, 2, 4, 6, 8, 11, 13, 15, 17, 19}) {
        AConnect(ATime(wave, 341 - 373), [=]{
            preWaveFire();
        });
    }

    // I-PP
    for (int wave : {3, 5, 7, 9, 12, 14, 16, 18}) {
        AConnect(ATime(wave, -200), [=]{
            aIceFiller.Coffee();
        });
        AConnect(ATime(wave, 950 - 373), [=]{
            normalWaveFire();
        });
    } 

    // 第10, 20波冰杀小偷特殊处理
    for (int wave : {10, 20}) {
        AConnect(ATime(wave, 395 - 100 - 198), [=]{
            aIceFiller.Coffee();
        });
        AConnect(ATime(wave, 395 + 300 - 373), [=]{
            aCobManager.RecoverFire(2, 8.7);
            aCobManager.RecoverFire(5, 8.7);
        });
    }

    // 第10波樱桃炸弹防止刷新延迟
    AConnect(ATime(10, 341 - 100), [=]{
        ACard(ACHERRY_BOMB, 2, 9);
    });

    // 炮炸珊瑚
    AConnect(ATime(20, 250 - 378), []{ 
        aCobManager.Fire(4, 7.625); 
    });
    
    // 收尾
    for (int wave : {9, 19, 20}) {
        AConnect(ATime(wave, 950 - 373), [=]{
            lastWaveFire();
        });
        // 最后再补一炮
        AConnect(ATime(wave, 3600 - 373 + 950), [=]{
            aCobManager.RecoverFire(2, 8);
            aCobManager.RecoverFire(5, 8);
        });
    }
}