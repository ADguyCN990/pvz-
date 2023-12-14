#include "avz.h"
#include "AutoFodder/main.h"

/*
双冰变奏ch4 | I-PP | I-PP | (17.5, 17.5)
第1波核弹，第2波预判炸，第10波核弹炸，第11波预判炸。4个加速波保证冰不会枯竭。
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

void lastWaveFire() {
    aCobManager.RecoverFire(2, 8.5);
    aCobManager.RecoverFire(5, 8.5);
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
                  ADOOM_SHROOM});

    // 开启10倍速挂机
    AFK();

    // 初始化炮位
    AConnect(ATime(1, -599), []{ aCobManager.AutoSetList(); });

    // 自动存冰
    aIceFiller.Start({{1, 4}, {6, 4}, {3, 5}});

    // 自动修补水路南瓜
    pumpkinFixer.Start(APUMPKIN, {{3, 5}, {4, 5}, {3, 6}, {4, 6}}, 4000 / 3);

    // 自动垫材
    AConnect([=]{return true;}, [=]{
        AAutoFodder({{1, 5}, {2, 6}, {5, 6}, {6, 5}}, {}, {APUFF_SHROOM, ASUN_SHROOM, AFLOWER_POT, ASCAREDY_SHROOM}, 79);
    });


    // 第1波核弹炸
    AConnect(ATime(1, 341 - 198 - 100), [=]{
        ACard(ALILY_PAD, 3, 9);
        ACard(ADOOM_SHROOM, 3, 9);
        ACard(ACOFFEE_BEAN, 3, 9);
    });

    // 第10波的核弹
    AConnect(ATime(10, 400 - 198 - 100), [=]{
        ACard(ALILY_PAD, 3, 8);
        ACard(ADOOM_SHROOM, 3, 8);
        ACard(ACOFFEE_BEAN, 3, 8);
    });

    // 第2, 11波预判炸
    for (int wave : {2, 11}) {
        AConnect(ATime(wave, 341 - 373), [=]{
            preWaveFire();
        });
    }

    // 第20波冰杀小偷
    AConnect(ATime(20, 395 - 100 - 198), [=]{
        aIceFiller.Coffee();
    });

    // 第20波的PP
    AConnect(ATime(20, 1550 - 373), [=]{
        normalWaveFire();
    });

    // 第20波最后再轰一炮
    AConnect(ATime(20, 1550 - 373), [=]{
        aCobManager.RecoverFire(2, 8);
        aCobManager.RecoverFire(5, 8);
    });

    // I-PP
    for (int wave : {3, 4, 5, 6, 7, 8, 9, 12, 13, 14, 15, 16, 17, 18, 19}) {
        AConnect(ATime(wave, -200), [=]{
            aIceFiller.Coffee();
        });
        AConnect(ATime(wave, 1550 - 373), [=]{
            normalWaveFire();
        });
    }

    // 收尾
    for (int wave : {9, 19, 20}) {
        AConnect(ATime(wave, 1550 - 373), [=]{
            lastWaveFire();
        });
    }
}