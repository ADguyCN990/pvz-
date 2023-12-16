#include "avz.h"

/*
| PP | PP | PP | PP | I-PP | (6, 6, 6, 6, 12)
P P P P I-P P P P P(PP) P P P P I-P P P P P I-P P(PP)
*/

ATickRunner tickRunner;
APlantFixer pumpkinFixer;

void AFK() {
    // 挂机
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    // 十倍速
    ASetGameSpeed(10);
}

void normalWaveFire() {
    aCobManager.Fire(2, 9);
    aCobManager.Fire(5, 9);
}

void lastWaveFire() {
    aCobManager.RecoverFire({{2, 9}, {5, 9}});
    aCobManager.RecoverFire({{2, 9}, {5, 9}});
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
                  ACHERRY_BOMB,
                  APUFF_SHROOM,
                  APUMPKIN,
                  AFLOWER_POT,
                  ASCAREDY_SHROOM,
                  ABLOVER,
                  ACOFFEE_BEAN,
                  AICE_SHROOM,
                  AGLOOM_SHROOM});

    // 开启10倍速挂机
    //AFK();

    // 初始化炮位
    AConnect(ATime(1, -599), []{ aCobManager.AutoSetList(); });

    // 自动存冰
    aIceFiller.Start({{4, 9}});

    // 自动修补水路南瓜
    pumpkinFixer.Start(APUMPKIN, {{3, 9}, {4, 9}}, 4000 / 3 * 2);

    for (int i : {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19}) {
        AConnect(ATime(i, 296 - 373), [=]{
            normalWaveFire();
        });
    }

    for (int i : {10}) {
        AConnect(ATime(i, 341 - 373), [=]{
            normalWaveFire();
        });        
    }

    for (int wave : {9, 19, 20}) {
        AConnect(ATime(wave, 296 - 373), [=]{
            lastWaveFire();
        });
    }

    // 樱桃消刷新延迟
    AConnect(ATime(10, 296 - 100), []{
        ACard(ACHERRY_BOMB, 2, 9);
    });

    // 炮消珊瑚
    AConnect(ATime(20, 250 - 378), []{ aCobManager.Fire(4, 7.625); });

    // 冰杀小偷
    for (int wave : {10, 20}) {
        AConnect(ATime(wave, 395 - 198 - 100), [=]{
            aIceFiller.Coffee();
        });
    }
}