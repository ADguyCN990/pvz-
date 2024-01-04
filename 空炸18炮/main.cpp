#include "avz.h"
#include "AutoFodder/main.h"

/*
P6 | PD/P | PD/P | PD/P | PD/P | PD/P | PD/P | (6, 6, 6, 6, 6, 6)
*/

ATickRunner tickRunner;
APlantFixer pumpkinFixer;

void AFK() {
    // 挂机
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    // 十倍速
    ASetGameSpeed(10);
}

void plantTrash() {
    ACard(APUFF_SHROOM, 1, 9);
    ACard(AM_PUFF_SHROOM, 2, 9);
    ACard(AFLOWER_POT, 5, 9);
    ACard(ASCAREDY_SHROOM, 6, 9);
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
                  ACHERRY_BOMB,
                  APUFF_SHROOM,
                  ASQUASH,
                  AFLOWER_POT,
                  ASCAREDY_SHROOM,
                  AWALL_NUT,
                  ACOFFEE_BEAN,
                  AICE_SHROOM,
                  ASUN_SHROOM});

    // 开启10倍速挂机
    //AFK();

    // 初始化炮位
    AConnect(ATime(1, -599), []{ 
        aCobManager.AutoSetList(); 
    });

    // 自动存冰
    //aIceFiller.Start({{3, 9}, {4, 9}});

    // 自动修补水路南瓜
    //pumpkinFixer.Start(APUMPKIN, {{3, 9}, {4, 9}}, 4000 / 3 * 2);

    //自动垫材
    // for (int wave : {9, 19, 20}) {
    //     AConnect([=] { return ANowWave() == wave && ANowTime(wave) >= 341 - 373 + 601; }, [] { 
    //         AAutoFodder({{5, 8}, {6, 8}}, {}, {APUFF_SHROOM, ASUN_SHROOM, AFLOWER_POT, ASCAREDY_SHROOM}, 79);
    //     });
    // }

    // PD/P
    for (int wave : {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}) {
        AConnect(ATime(wave, 341 - 373), [=]{
            aCobManager.Fire({{2, 9}});
        });
        AConnect(ATime(wave, 341 - 373), [=]{
            aCobManager.Fire({{5, 9}});
        });
        AConnect(ATime(wave, 341 - 373 + 110), [=]{
            aCobManager.Fire({{1, 7.7}});
        });
    }

    // 旗帜波特殊处理，不然cd不够
    for (int wave : {10}) {
        AConnect(ATime(wave, 191), [=]{
            plantTrash();
        });
        AConnect(ATime(wave, 395 - 373), [=]{
            aCobManager.Fire({{2, 9}, {5, 8.8}});
        });
        AConnect(ATime(wave, 395), [=]{
            ARemovePlant(1, 9);
            ARemovePlant(2, 9);
            ARemovePlant(5, 9);
            ARemovePlant(6, 9);
        });
        AConnect(ATime(wave, 395 - 373 + 110), [=]{
            aCobManager.Fire({{1, 7.7}});
        });
    }

    // 收尾
    for (int wave : {9, 19, 20}) {
        AConnect(ATime(wave, 341 - 373 + 601), [=]{
            aCobManager.Fire({{2, 9}});
        });
        AConnect(ATime(wave, 341 - 373 + 601), [=]{
            aCobManager.Fire({{5, 9}});
        });
        AConnect(ATime(wave, 341 - 373 + 601 + 110), [=]{
            aCobManager.Fire(1, 7.7);
        });
        AConnect(ATime(wave, 341 - 373 + 601 + 110), [=]{
            aCobManager.RecoverFire({{2, 9}, {5, 9}, {5, 9}});
        });
    }

    


    // 炮消珊瑚
    AConnect(ATime(20, 250 - 378), []{ aCobManager.Fire(4, 7.625); });

    // 炮杀小偷
    for (int wave : {20}) {
        AConnect(ATime(wave, 395 - 373), [=]{
            aCobManager.Fire(5, 7);
        });
    }

}