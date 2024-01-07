#include "avz.h"
#include "AutoFodder/main.h"

/*
ch6 | IPP-PP | PPDD | IPP-PP | PPDD |  (11.5, 6, 11.5, 6)
IPP-PP: 2, 4, 6, 8, 11, 13, 15, 17, 19
PPDD: 1, 3, 5, 7, 9, 10, 12, 14, 16, 18, 20
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
    aIceFiller.Start({{1, 1}, {2, 1}, {5, 1}, {6, 1}});

    // 自动修补水路南瓜
    //pumpkinFixer.Start(APUMPKIN, {{3, 9}, {4, 9}}, 4000 / 3 * 2);

    //自动垫材
    for (int wave : {9, 20}) {
        AConnect([=] { return ANowWave() == wave && ANowTime(wave) >= 295 + 110 + 1; }, [] { 
            AAutoFodder({}, {}, {APUFF_SHROOM, ASUN_SHROOM, AFLOWER_POT, ASCAREDY_SHROOM}, 79);
        });
    }
    for (int wave : {19}) {
        AConnect([=] { return ANowWave() == wave && ANowTime(wave) >= 1150 - 200 + 1; }, [] { 
            AAutoFodder({}, {}, {APUFF_SHROOM, ASUN_SHROOM, AFLOWER_POT, ASCAREDY_SHROOM}, 79);
        });
    }

    // IPP-PP
    for (int wave : {2, 4, 6, 8, 11, 13, 15, 17, 19}) {
        AConnect(ATime(wave - 1, 1 - 100 - 198 + 601), [=]{
            aIceFiller.Coffee();
        });
    }
    for (int wave : {2, 4, 6, 8, 11, 13, 15, 17, 19}) {
        AConnect(ATime(wave, -200), [=]{
            // 热过渡, 8.2625为消灭全部冰车的最左准心列数
            aCobManager.Fire({{2, 8.2625}, {5, 8.2625}});
            //aIceFiller.Coffee();
        });
        AConnect(ATime(wave, 1150 - 200 - 373), [=]{
            aCobManager.Fire({{2, 8.8}, {5, 8.8}});
        });
    }

    // PPDD
    for (int wave : {1, 3, 5, 7, 9, 10, 12, 14, 16, 18, 20}) {
        AConnect(ATime(wave, 295 - 373), [=]{
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
    }
    for (int wave : {1, 3, 5, 7, 10, 12, 14, 16, 18}) {
        AConnect(ATime(wave, 295 - 373 + 110), [=]{
            aCobManager.Fire({{1, 9}, {5, 9}});
        });
    }
    for (int wave : {9, 20}) {
        AConnect(ATime(wave, 295 - 373 + 110), [=]{
            aCobManager.Fire({{1, 9}, {5, 9}});
        });        
    }

    // 收尾
    for (int wave : {9, 20}) {
        AConnect(ATime(wave, 295 - 373 + 110), [=]{
            aCobManager.RecoverFire({{2, 9}, {5, 9}, {2, 9}, {5, 9}});
        });
    }
    for (int wave : {9}) {
        AConnect(ATime(wave, 295 + 110 - 100), [=]{
            aIceFiller.Coffee();
        });        
    }
    for (int wave : {19}) {
        AConnect(ATime(wave, 1150 - 200 - 373), [=]{
            aCobManager.RecoverFire({{2, 9}, {5, 9}, {2, 9}, {5, 9}, {2, 9}, {5, 9}});
        });
    }



    // 炮消珊瑚
    AConnect(ATime(20, 250 - 378), []{ aCobManager.Fire(4, 7.625); });

    // 炮杀小偷
    // for (int wave : {20}) {
    //     AConnect(ATime(wave, 395 - 373), [=]{
    //         aCobManager.Fire(5, 7);
    //     });
    // }

}