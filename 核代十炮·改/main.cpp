#include "avz.h"

/*
| PP | PP | PP | PP | PP | N | (6, 6, 6, 6, 6, 6)
*/

ATickRunner tickRunner;

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

void lastWaveFire() {
    aCobManager.RecoverFire({{2, 9}, {4, 9}});
    aCobManager.RecoverFire({{2, 9}, {4, 9}});
    aCobManager.RecoverFire({{2, 9}, {4, 9}});
}

AGrid tomb;
ALogger<AMsgBox> msgBoxLogger;  
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
                 AGARGANTUAR,
                 AGIGA_GARGANTUAR
    });

    // 选卡
    ASelectCards({AM_ICE_SHROOM,
                  ACHERRY_BOMB,
                  APUFF_SHROOM,
                  AGRAVE_BUSTER,
                  AFLOWER_POT,
                  ASCAREDY_SHROOM,
                  ABLOVER,
                  ADOOM_SHROOM,
                  AICE_SHROOM,
                  ASQUASH});

    // 开启10倍速挂机
    AFK();

    // 初始化炮位
    AConnect(ATime(1, -599), []{ aCobManager.AutoSetList(); });

    // 配合tickRunner吹气球
    tickRunner.Start([]{
        for (auto&& zombie : aAliveZombieFilter) {
            if (zombie.Type() == ABALLOON_ZOMBIE && zombie.Abscissa() <= 100) { // 如果有气球僵尸的横坐标小于50 (快飞到家了)
                // 这句话是获得三叶草卡片的内存指针
                // AGetCardIndex 函数就是从卡片名称得到卡片在卡槽位置的函数
                auto blover = AGetMainObject()->SeedArray() + AGetCardIndex(ABLOVER);
                if (blover->IsUsable()) { // 三叶草可用时才能吹气球
                    AShovel(5, 9);
                    ACard(ABLOVER, 5, 9);
                    return; // 吹一次就结束了，因为再循环遍历也没用了
                }
            }
        } 
    });

    // PP
    for (int wave : {1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 19, 20}) {
        AConnect(ATime(wave, 341 - 373), []{
            normalWaveFire();
        });
    }

    // N
    for (int wave : {6, 15}) {
        
        AConnect(ATime(wave, 341 - 100), [=]{
            if (wave == 6) {
                ACard(ADOOM_SHROOM, 3, 9);
            } else {
                ACard(ADOOM_SHROOM, 2, 9);
            }
        });
    }

    // 末尾波
    for (int wave : {9, 19, 20}) {
        AConnect(ATime(wave, 341 - 373), []{
            lastWaveFire();
        });
    }

    // 冰杀小偷
    for (int wave : {10, 20}) {
        AConnect(ATime(wave, 395 - 100), []{
            ACard(AICE_SHROOM, 1, 9);
        });
    }
    
    // 樱桃消刷新延迟
    AConnect(ATime(10, 341 - 100), []{
        ACard(ACHERRY_BOMB, 2, 9);
    });

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
    // 炮炸不到7列，需要补种一个倭瓜杀僵尸
    if ((int)(tomb.col) + 1 <= 7) {
        AConnect(ATime(20, 471 + 396), [=]{
            ACard(ASQUASH, tomb.row + 1, tomb.col + 1);
        });
    }

}