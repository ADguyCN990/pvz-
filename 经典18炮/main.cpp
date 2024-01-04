#include "avz.h"
#include "AutoFodder/main.h"

/*
P6 | PP | BBPP | PP | BBPP | PP | BBPP | (6, 6, 6, 6, 6, 6)
BBPP中的BB用于收上一波露的撑杆，同时分离本波的快速僵尸，PP则用于收本波的撑杆，同时对巨人造成伤害
PP: 1, 3, 5, 7, 9, 10, 12, 14, 16, 18, 20
BBPP: 2*, 4*, 6, 8, 11, 13, 15, 17, 19
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
                  AJALAPENO,
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

    // 自动垫材
    // for (int wave : {9, 19, 20}) {
    //     AConnect([=] { return ANowWave() == wave && ANowTime(wave) >= 600; }, [] { 
    //         AAutoFodder({{1, 9}, {2, 9}, {5, 9}, {6, 9}}, {}, {APUFF_SHROOM, ASUN_SHROOM, AFLOWER_POT, ASCAREDY_SHROOM}, 79);
    //     });
    // }

    // PP
    for (int wave : {1, 3, 5, 7, 9, 10, 12, 14, 16, 18, 20}) {
        AConnect(ATime(wave, 296 - 373), [=]{
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
    }

    // BBPP
    // 610cs为撑杆僵尸对着8列炮起跳的最早时机
    // 180cs为撑杆僵尸从起跳到落地的时长
    for (int wave : {2, 4, 6, 8, 11, 13, 15, 17, 19}) {
        AConnect(ATime(wave, 610 + 180 - 1 - 601 - 373), [=]{
            aCobManager.Fire({{2, 8.8}, {5, 8.8}});
        });

        AConnect(ATime(wave, 400 - 373), [=]{
            aCobManager.Fire({{2, 9}, {5, 9}});
        });        
    }


    // 收尾
    for (int wave : {9, 19, 20}) {
        AConnect(ATime(wave, 400 - 373), [=]{
            aCobManager.RecoverFire({{2, 9}, {5, 9}, {2, 9}, {5, 9}, {2, 9}, {5, 9}});
        });
    }

    // 炮消珊瑚
    AConnect(ATime(20, 250 - 378), []{ aCobManager.Fire(4, 7.625); });

    // 冰杀小偷
    for (int wave : {10, 20}) {
        AConnect(ATime(wave, 395 - 100 - 198), [=]{
            ACard(AICE_SHROOM, 1, 1);
            ACard(ACOFFEE_BEAN, 1, 1);
        });
    }

}