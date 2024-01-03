#include "avz.h"
#include "AutoFodder/main.h"

/*
单冰变奏S6 | I-PP | PP | PPDD | PP | PP | (11, 6, 6, 6, 6)
PP: 1, 2, 4, 6, 7, 9, 11, 12, 14, 16, 17, 19, 20
I-PP: 3, 8, 13, 18
PPDD: 5, 15
N: 10
*/

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
                 ABALLOON_ZOMBIE,
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
                  ADOOM_SHROOM,
                  AFLOWER_POT,
                  ALILY_PAD,
                  ASCAREDY_SHROOM,
                  ACOFFEE_BEAN,
                  AICE_SHROOM,
                  ASQUASH});

    // 开启10倍速挂机
    //AFK();

    // 初始化炮位
    AConnect(ATime(1, -599), []{ aCobManager.AutoSetList(); });

    //自动垫材
    for (int wave : {9, 19, 20}) {
        AConnect([=] { return ANowWave() == wave && ANowTime(wave) >= 600; }, [] { 
            AAutoFodder({{1, 7}, {2, 7}, {5, 7}, {6, 7}}, {}, {APUFF_SHROOM, ASUN_SHROOM, AFLOWER_POT, ASCAREDY_SHROOM}, 79);
        });
    }

    // PP
    for (int wave : {1, 2, 4, 6, 7, 9, 11, 12, 14, 16, 17, 19, 20}) {
        AConnect(ATime(wave, 341 - 373), [=]{
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
    }
    // 第10波核代PP，不然cd不够
    AConnect(ATime(10, 341 - 100 - 198), [=]{
        ACard(ALILY_PAD, 3, 9);
        ACard(ADOOM_SHROOM, 3, 9);
        ACard(ACOFFEE_BEAN, 3, 9);
    });
    AConnect(ATime(10, 599), [=]{
        AShovel(3, 9);
    });

    // I-PP
    for (int wave : {3, 8, 13, 18}) {
        AConnect(ATime(wave, 1100 - 200 - 373), [=]{
            aCobManager.Fire({{2, 8.8}, {5, 8.8}});
        });
    } 
    // 激活原版冰
    for (int wave : {2, 12}) {
        AConnect(ATime(wave, 600 + 50 - 100 - 198), [=]{
            ACard(AICE_SHROOM, 1, 4);
            ACard(ACOFFEE_BEAN, 1, 4);
        });
    }
    // 激活复制冰
    for (int wave : {7, 17}) {
        AConnect(ATime(wave, -200), [=]{
            ACard(AM_ICE_SHROOM, 1, 4);
        });
        AConnect(ATime(wave, 600 + 50 - 100 - 198), [=]{
            ACard(ACOFFEE_BEAN, 1, 4);
        });        
    }

    // PPDD
    for (int wave : {5, 15}) {
        AConnect(ATime(wave, 341 - 373), [=]{
            aCobManager.Fire({{2, 9}, {5, 9}});
        });
        AConnect(ATime(wave, 341 - 373 + 110), [=]{
            aCobManager.Fire({{1, 7.7}, {5, 7.7}});
        });
    }
    
    // 收尾
    for (int wave : {9}) {
        AConnect(ATime(wave, 600 - 373), [=]{
            aCobManager.RecoverFire({{2, 9}, {5, 9}, {2, 9}, {5, 9}, {2, 9}, {5, 9}});
        });      
    }
    for (int wave : {19, 20}) {
        AConnect(ATime(wave, 600 - 373), [=]{
            aCobManager.RecoverFire({{2, 9}, {5, 9}, {2, 9}, {5, 9}, {3, 9}, {5, 9}});
        });          
    }

    // 冰消珊瑚
    AConnect(ATime(20, 200 - 1 - 198 - 100), [=]{
        ACard(AICE_SHROOM, 1, 4);
        ACard(ACOFFEE_BEAN, 1, 4);
    });

    // 炮炸小偷
    for (int wave : {10, 20}) {
        AConnect(ATime(wave, 395 - 373), [=]{
            aCobManager.Fire({{2, 2}, {5, 2}});
        });
    }

}