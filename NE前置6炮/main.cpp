#include "avz.h"
#include "AutoFodder/main.h"

/*
双冰变奏C7u | I-PP | I-PP | PP | N | PP | (18, 18, 6, 6, 6)
PP I-PP I'-PP PP N PP I-PP I'-PP PP
PP I-PP I'-PP PP N PP I-PP I'-PP PP N
PP
*/

APlantFixer pumpkinFixer;
//ATickRunner tickRunner;
AGrid tomb;

void AFK() {
    // 挂机
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    // 十倍速
    ASetGameSpeed(10);
}

void normalWaveFire() {
    aCobManager.Fire(2, 9);
    aCobManager.Fire(4, 9);
}

void delayWaveFire() {
    aCobManager.Fire(2, 8.7);
    aCobManager.Fire(4, 8.7);
}

void lastWaveFire() {
    aCobManager.RecoverFire({{2, 8.7}, {4, 8.7}});
    aCobManager.RecoverFire({{2, 8.7}, {4, 8.7}});
}

void solveGraveZombie() {
    // 试探出墓碑生成的位置
    AConnect(ATime(20, 113), [=] mutable {
        std::vector<AGrid> grave_generate_pos = {{0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {0, 8}, {1, 8}, {2, 3}, {3, 8}, {4, 8}};
        for (AGrid i : grave_generate_pos) {
            if (AAsm::GetPlantRejectType(AGRAVE_BUSTER, i.row, i.col) == AAsm::NIL) {
                //msgBoxLogger.SetLevel({ALogLevel::DEBUG, ALogLevel::WARNING});
                //msgBoxLogger.Debug("墓碑位置是:(#, #)", i.row, i.col);     // 显示
                tomb = i;
                break;
            }
        }
    });
    // 消除墓碑
    AConnect(ATime(20, 396), [=]{
        ACard(AGRAVE_BUSTER, tomb.row + 1, tomb.col + 1);
    });
}

void AScript() {
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    ASetZombies({AZOMBIE,
                 APOLE_VAULTING_ZOMBIE,
                 AFOOTBALL_ZOMBIE,
                 ADANCING_ZOMBIE,
                 //AZOMBONI,
                 AJACK_IN_THE_BOX_ZOMBIE,
                 ADIGGER_ZOMBIE,
                 APOGO_ZOMBIE,
                 ALADDER_ZOMBIE,
                 ABUNGEE_ZOMBIE,
                 ACATAPULT_ZOMBIE,
                 ABALLOON_ZOMBIE,
                 //ADOLPHIN_RIDER_ZOMBIE,
                 AGARGANTUAR,
                 AGIGA_GARGANTUAR
    });

    // 选卡
    ASelectCards({AM_ICE_SHROOM,
                  ASUN_SHROOM,
                  APUFF_SHROOM,
                  APUMPKIN,
                  AFLOWER_POT,
                  ASQUASH,
                  ASCAREDY_SHROOM,
                  AGRAVE_BUSTER,
                  AICE_SHROOM,
                  ADOOM_SHROOM});

    // 开启10倍速挂机
     AFK();

    // 初始化炮位
    AConnect(ATime(1, -599), []{ aCobManager.AutoSetList(); });

    // 自动修补底线南瓜
    pumpkinFixer.Start(APUMPKIN, {{1, 1}, {2, 1}, {4, 1}, {5, 1}}, 4000 / 3 * 2);

    // 自动垫材
    AConnect([=]{return true;}, [=]{
        AAutoFodder({{1, 7}, {2, 7}, {4, 7}, {5, 7}}, {}, {APUFF_SHROOM, ASUN_SHROOM, AFLOWER_POT, ASCAREDY_SHROOM}, 79);
    });

    // 6s波长 PP(1, 4, 6, 9, 10, 13, 15, 18, 20)
    for (int wave : {1, 4, 6, 9, 10, 13, 15, 18, 20}) {
        AConnect(ATime(wave, 341 - 373), [=]{
            normalWaveFire();
        });
    }
    // 6s波长 N(5, 14, 19)
    AConnect(ATime(5, 341 - 100), [=]{
        ACard(ADOOM_SHROOM, 3, 9);
    });
    AConnect(ATime(14, 341 - 100), [=]{
        ACard(ADOOM_SHROOM, 2, 9);
        //ACard(ASQUASH, 1, 9);
    });
    AConnect(ATime(19, 341 - 100), [=]{
        ACard(ADOOM_SHROOM, 3, 8);
    });

    // 18s波长 原版I-PP(2, 7, 11, 16)
    for (int wave : {2, 7, 11, 16}) {
        AConnect(ATime(wave, -99), [=]{
            ACard(AICE_SHROOM, 3, 7);
        });
        AConnect(ATime(wave, 1600 - 373), [=]{
            delayWaveFire();
        });
        // 激活模仿者冰
        AConnect(ATime(wave, 1800 - 100 + 1 - 319), [=]{
            ACard(AM_ICE_SHROOM, 3, 7);
        });
    }
    // 18s波长 模仿者I-PP(3, 8, 12, 17)
    for (int wave : {3, 8, 12, 17}) {

        AConnect(ATime(wave, 1600 - 373), [=]{
            delayWaveFire();
        });     
    }

    // 收尾
    for (int wave : {9}) {
        AConnect(ATime(wave, 1600 - 373), [=]{
            lastWaveFire();
        });
    }
    // 因为要炮杀墓碑，所以第19波得鳖一会；20是因为炮炸墓碑已经炸过一轮了
    for (int wave : {19, 20}) {
        AConnect(ATime(wave, 1600 - 373), [=]{
            aCobManager.RecoverFire({{2, 8.3}, {4, 8.3}});
        });         
    }
    for (int wave : {19}) {
        AConnect(ATime(wave, 4000 - 373), [=]{
            aCobManager.RecoverFire({{2, 8.3}, {4, 8.3}});
        });        
    }

    // 处理墓碑
    // 炮炸
    AConnect(ATime(20, 395 - 373), [=]{
        aCobManager.Fire(2, 8.5);
        aCobManager.Fire(4, 8.5);
    });
    solveGraveZombie();
}