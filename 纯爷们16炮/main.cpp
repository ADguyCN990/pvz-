#include "avz.h"
#include "AutoFodder/main.h"

/*
P6 | PP | PP | PPSS | PP | PP | PPSS | (6, 6, 6, 6, 6, 6)
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
    for (int wave : {9, 19, 20}) {
        AConnect([=] { return ANowWave() == wave && ANowTime(wave) >= 600; }, [] { 
            AAutoFodder({}, {}, {APUFF_SHROOM, ASUN_SHROOM, AFLOWER_POT, ASCAREDY_SHROOM}, 79);
        });
    }

    // PP
    for (int wave : {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}) {
        AConnect(ATime(wave, 296 - 373), [=]{
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
    }

    // SS
    for (int wave : {3, 6, 9, 13, 16, 19}) {
        AConnect(ATime(wave, 296 - 373), [=]{
            aCobManager.Fire({{2, 9}, {5, 9}});
        });        
    }


    // 收尾
    for (int wave : {9, 19, 20}) {
        AConnect(ATime(wave, 296 - 373), [=]{
            aCobManager.RecoverFire({{2, 9}, {5, 9}, {2, 9}, {5, 9}});
        });
    }
    AConnect(ATime(20, 296 - 373), [=]{
        aCobManager.RecoverFire({{2, 9}, {5, 9}});
    });


    // 炮消珊瑚
    AConnect(ATime(20, 250 - 378), []{ aCobManager.Fire(4, 7.625); });

    // 冰杀小偷
    for (int wave : {10, 20}) {
        AConnect(ATime(wave, 395 - 100 - 198), [=]{
            ACard(AICE_SHROOM, 1, 7);
            ACard(ACOFFEE_BEAN, 1, 7);
        });
    }

}