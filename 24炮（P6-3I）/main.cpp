#include "avz.h"
#include "AutoFodder/main.h"

/*
冰代奏P6-3I | PPSSDD | PPI | PPSSDD | PPI | PPSSDD | PPI | (6, 6, 6, 6, 6, 6)
PPSSDD: 1, 3, 5, 7, 9, 10, 12, 14, 16, 18, 20
PP-I: 2*, 4*, 6, 8, 11, 13, 15, 17, 19
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
        ACard(AM_ICE_SHROOM, 2, 9);
    });

    // 自动存冰
    aIceFiller.Start({{3, 9}, {4, 9}});

    // 自动修补水路南瓜
    //pumpkinFixer.Start(APUMPKIN, {{3, 9}, {4, 9}}, 4000 / 3 * 2);

    //自动垫材
    for (int wave : {9, 19, 20}) {
        AConnect([=] { return ANowWave() == wave && ANowTime(wave) >= 600; }, [] { 
            AAutoFodder({{1, 9}, {6, 9}}, {}, {APUFF_SHROOM, ASUN_SHROOM, AFLOWER_POT, ASCAREDY_SHROOM}, 79);
        });
    }

    // PPSSDD
    for (int wave : {1, 3, 5, 7, 9, 10, 12, 14, 16, 18, 20}) {
        AConnect(ATime(wave, 296 - 373), [=]{
            aCobManager.Fire({{2, 9}, {5, 9}, {2, 9}, {5, 9}});
        });
        AConnect(ATime(wave, 296 - 373 + 110), [=]{
            aCobManager.Fire({{1, 9}, {5, 9}});
        });
    }

    // PP-I
    for (int wave : {2, 4, 6, 8, 11, 13, 15, 17, 19}) {
        AConnect(ATime(wave, 296 - 373), [=]{
            aCobManager.Fire({{2, 9}, {5, 9}});
        });        
    }
    for (int wave : {4, 6, 8, 13, 15, 17, 19}) {
        AConnect(ATime(wave, 296 - 100 - 198), [=]{
            aIceFiller.Coffee();
        });        
    }
    AConnect(ATime(1, 296 - 100), [=]{
        ACard(ACHERRY_BOMB, 1, 9);
    });
    AConnect(ATime(2, 296 - 198 - 100), [=]{
        ACard(ACOFFEE_BEAN, 2, 9);
    });
    // AConnect(ATime(10, 278), [=]{
    //     ACard(AM_ICE_SHROOM, 1, 9);
    // });
    AConnect(ATime(11, 296 - 100 - 198), [=]{
        ACard(ACOFFEE_BEAN, 1, 9);
    });


    // 收尾
    AConnect(ATime(9, 296 - 373 + 110), [=]{
        aCobManager.RecoverFire({{3, 9}, {4, 9}});
    });
    // *** 处理白眼，激活红眼投掷 ***
    AConnect(ATime(19, 296 - 373 + 600), [=]{
        aCobManager.Fire({{2, 9}, {5, 9}});
    });
    // 空炸红眼
    AConnect(ATime(19, 296 + 600 + 220 - 373), [=]{
        aCobManager.Fire({{1, 9}, {5, 9}});
    });
    // 补刀红眼
    AConnect(ATime(19, 296 + 600 + 220 - 373 + 1), [=]{
        aCobManager.RecoverFire({{3, 9}, {4, 9}});
    });


    AConnect(ATime(20, 814 - 373), [=]{
        aCobManager.RecoverFire({{2, 9}, {5, 9}});
    });

    // 炮消珊瑚
    AConnect(ATime(20, 250 - 378), []{ aCobManager.Fire(4, 7.625); });

    // 樱桃炸弹杀3路小偷
    for (int wave : {10, 20}) {
        AConnect(ATime(wave, 296 + 110 - 100), [=]{
            ACard(ACHERRY_BOMB, 2, 9);
        });
    }

}