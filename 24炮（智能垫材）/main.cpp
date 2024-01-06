#include "avz.h"
#include "AutoFodder/main.h"

/*
未完成
P6 | PDc | PDc | PDc | PDc | PDc | PDc | (6, 6, 6, 6, 6, 6)
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
    ASelectCards({AM_PUFF_SHROOM,
                  ASUNFLOWER,
                  APUFF_SHROOM,
                  AFUME_SHROOM,
                  AFLOWER_POT,
                  ASCAREDY_SHROOM,
                  AGARLIC,
                  AWALL_NUT,
                  ACHERRY_BOMB,
                  ASUN_SHROOM});

    // 开启10倍速挂机
    //AFK();

    // 初始化炮位
    AConnect(ATime(1, -599), []{ 
        aCobManager.AutoSetList(); 
    });

    // 自动存冰
    // aIceFiller.Start({{3, 9}, {4, 9}});

    // 自动修补水路南瓜
    // pumpkinFixer.Start(APUMPKIN, {{3, 9}, {4, 9}}, 4000 / 3 * 2);

    //自动垫材
    // for (int wave : {9, 19, 20}) {
    //     AConnect([=] { return ANowWave() == wave && ANowTime(wave) >= 218 + 601 - 373 + 1; }, [] { 
    //         AAutoFodder({}, {}, {}, 79);
    //     });
    // }

    // P
    for (int wave : {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19}) {
        AConnect(ATime(wave, 218 - 373), [=]{
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
    }

    // D
    for (int wave : {1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17, 18}) {
        AConnect(ATime(wave, 218 - 373 + 110), [=]{
            aCobManager.Fire({{1, 7.8}, {5, 7.8}});
        });
    }

    // c
    for (int wave : {2, 4, 6, 8, 11, 13, 15, 17, 19}) {
        AConnect(ATime(wave, 522), [=]{            
            ACard(ASUNFLOWER, 1, 9);
            ACard(AFUME_SHROOM, 2, 9);
            ACard(AGARLIC, 5, 9);
            ACard(ASUN_SHROOM, 6, 9);
        });
        AConnect(ATime(wave, 599), [=]{
            ARemovePlant(1, 9);
            ARemovePlant(2, 9);
            ARemovePlant(5, 9);
            ARemovePlant(6, 9);
        });
    }
    for (int wave : {1, 3, 5, 7, 9, 12, 14, 16, 18}) {
        AConnect(ATime(wave, 522), [=]{
            ACard(AM_PUFF_SHROOM, 1, 9);
            ACard(AFLOWER_POT, 2, 9);
            ACard(APUFF_SHROOM, 5, 9);
            ACard(ASCAREDY_SHROOM, 6, 9);
        });
        AConnect(ATime(wave, 599), [=]{
            ARemovePlant(1, 9);
            ARemovePlant(2, 9);
            ARemovePlant(5, 9);
            ARemovePlant(6, 9);
        });
    }

    // 收尾处理
    for (int wave : {9, 19}) {
        AConnect(ATime(wave, 218 - 373 + 110), [=]{
            aCobManager.Fire({{1, 7.8}, {5, 8.8}});
        });
        AConnect(ATime(wave, 218 + 600 - 373), [=]{
            aCobManager.Fire({{2, 9}, {5, 9}});
        });    
        AConnect(ATime(wave, 218 + 600 - 373 + 110), [=]{
            aCobManager.Fire({{1, 9}, {5, 9}});
        });   
        AConnect(ATime(wave, 218 + 600 - 373 + 110), [=]{
            aCobManager.RecoverFire({{2, 9}, {5, 9}});
        });  
    }
    for (int wave : {20}) {
        AConnect(ATime(wave, 295 + 110), [=]{
            aCobManager.RecoverFire({{2, 9}, {5, 9}});
        });
    }

    // 炮消珊瑚
    AConnect(ATime(20, 250 - 378), []{ aCobManager.Fire(4, 7.625); });

    // 收1路小偷单独处理
    for (int wave : {10, 20}) {
        // PS/PS
        AConnect(ATime(wave, 295 - 373), [=]{
            aCobManager.Fire({{2, 9}, {5, 9}, {2, 9}, {5, 9}});
        });
        // A/D
        AConnect(ATime(wave, 295 - 100 + 110), [=]{
            ACard(ACHERRY_BOMB, 1, 9);
        });
        AConnect(ATime(wave, 295 - 373 + 110), [=]{
            aCobManager.Fire({{5, 9}});
        });
    }

}