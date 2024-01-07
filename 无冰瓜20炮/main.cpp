#include "avz.h"

/*
冰代奏P6-2I | PPDD | PPDD | PP-I | PPDD | PPDD | PP-I | (6, 6, 6, 6, 6, 6)
PPDD: 1, 2, 4, 5, 7, 8, 10, 11, 13, 14, 16, 17, 19, 20
PP-I: 3, 6, 9, 12, 15, 18
*/

ATickRunner tickRunner;
APlantFixer pumpkinFixer;

void AFK() {
    // 挂机
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    // 十倍速
    ASetGameSpeed(10);
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

    // PPDD
    for (int wave : {1, 2, 4, 5, 7, 8, 10, 11, 13, 14, 16, 17, 19, 20}) {
        AConnect(ATime(wave, 296 - 373), [=]{
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        AConnect(ATime(wave, 296 - 373 + 110), [=]{
            aCobManager.Fire({{1, 9}, {5, 9}});
        });
    }

    // PP-I
    for (int wave : {3, 6, 9, 12, 15, 18}) {
        AConnect(ATime(wave, 296 - 373), [=]{
            aCobManager.Fire({{2, 9}, {5, 9}});
        });        
        AConnect(ATime(wave, 296 - 100 - 198), [=]{
            aIceFiller.Coffee();
        });
    }

    // 收尾
    AConnect(ATime(9, 296 - 373), [=]{
        aCobManager.RecoverFire({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    });
    AConnect(ATime(19, 296 - 373 + 110), [=]{
        aCobManager.RecoverFire({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    });
    AConnect(ATime(20, 814 - 373), [=]{
        aCobManager.RecoverFire({{2, 8.8}, {5, 8.8}, {2, 8.8}, {5, 8.8}});
    });

    // 炮消珊瑚
    AConnect(ATime(20, 250 - 378), []{ aCobManager.Fire(4, 7.625); });

}