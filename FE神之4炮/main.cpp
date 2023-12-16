#include "avz.h"
#include "AutoFodder/main.h"

/*
双冰变奏c6u | I-PP | I-PP | N | PP | (18, 18, 9, 9)
PP I'-PP I-PP N PP I'-PP I-PP N PP 
I'-PP I-PP N PP I'-PP I-PP N PP I'-PP I-PP
I(冰杀小偷)-PP
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
    aCobManager.Fire(2, 8.5);
    aCobManager.Fire(5, 8.5);
}

void delayWaveFire() {
    aCobManager.Fire(2, 8);
    aCobManager.Fire(5, 8);
}

void lastWaveFire() {
    aCobManager.RecoverFire({{2, 7.5}, {5, 7.5}});
    aCobManager.RecoverFire({{2, 7.5}, {5, 7.5}});
}

void AScript() {
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    ASetZombies({AZOMBIE,
                 APOLE_VAULTING_ZOMBIE,
                 AFOOTBALL_ZOMBIE,
                 ADANCING_ZOMBIE,
                 AZOMBONI,
                 AJACK_IN_THE_BOX_ZOMBIE,
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
                  ASUNFLOWER,
                  AICE_SHROOM,
                  ADOOM_SHROOM});

    // 开启10倍速挂机
    //AFK();

    // 初始化炮位
    AConnect(ATime(1, -599), []{ aCobManager.AutoSetList(); });

    // 自动修补水路南瓜
    pumpkinFixer.Start(APUMPKIN, {{3, 5}, {4, 5}, {3, 6}, {4, 6}}, 4000 / 3 * 2);

    // 自动垫材
    AConnect([=]{return true;}, [=]{
        AAutoFodder({{1, 5}, {2, 6}, {5, 6}, {6, 5}}, {}, {APUFF_SHROOM, ASUN_SHROOM, AFLOWER_POT, ASCAREDY_SHROOM}, 79);
    });

    // 9s波长 PP
    for (int wave : {1, 5, 9, 13, 17}) {
        AConnect(ATime(wave, 700 - 373), [=]{
            normalWaveFire();
        });
    }
    // 9s波长 N(4, 8, 12, 16)
    AConnect(ATime(4, 700 - 100), [=]{
        ACard(ALILY_PAD, 3, 9);
        ACard(ADOOM_SHROOM, 3, 9);
    });
    AConnect(ATime(8, 700 - 100), [=]{
        ACard(ALILY_PAD, 4, 9);
        ACard(ADOOM_SHROOM, 4, 9);
    });
    AConnect(ATime(12, 700 - 100), [=]{
        ACard(ALILY_PAD, 3, 8);
        ACard(ADOOM_SHROOM, 3, 8);
    });
    AConnect(ATime(16, 700 - 100), [=]{
        ACard(ALILY_PAD, 4, 8);
        ACard(ADOOM_SHROOM, 4, 8);
    });

    // 18s波长 原版I-PP
    for (int wave : {3, 7, 11, 15, 19}) {
        AConnect(ATime(wave, -99), [=]{
            ACard(AICE_SHROOM, 2, 1);
        });
        AConnect(ATime(wave, 1600 - 373), [=]{
            delayWaveFire();
        });
    }
    // 18s波长 模仿者I-PP
    for (int wave : {2, 6, 14, 18}) {
        AConnect(ATime(wave, -200), [=]{
            ACard(AM_ICE_SHROOM, 2, 1);
        });
        AConnect(ATime(wave, 1600 - 373), [=]{
            delayWaveFire();
        });     
    }

    // 第10波模仿者冰杀小偷
    for (int wave : {10}) {
        AConnect(ATime(wave, 395 - 319 - 100), []{
            ACard(AM_ICE_SHROOM, 2, 1);
        });
        AConnect(ATime(wave, 1600 - 373), []{
            delayWaveFire();
        });
    }

    // 第20波冰杀小偷
    AConnect(ATime(20, 395 - 100), [=]{
        ACard(AICE_SHROOM, 2, 1);
    });

    // 第20波的PP
    AConnect(ATime(20, 1600 - 373), [=]{
        normalWaveFire();
    });

    // 收尾
    for (int wave : {9, 19, 20}) {
        AConnect(ATime(wave, 1600 - 373), [=]{
            lastWaveFire();
        });
    }
}