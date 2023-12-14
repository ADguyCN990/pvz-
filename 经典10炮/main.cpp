#include "avz.h"

/*
| PP | PP | PP | PP | PP | I-PP | (6, 6, 6, 6, 12)
P P P P I-P P P P P(PP) P P P P I-P P P P P I-P P(PP)
*/

ATickRunner tickRunner;
APlantFixer pumpkinFixer;

void AFK() {
    // 挂机
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    // 十倍速
    ASetGameSpeed(10);
}

void normalWaveFire() {
    aCobManager.Fire(2, 9);
    aCobManager.Fire(5, 9);
}

void lastWaveFire() {
    aCobManager.RecoverFire({{2, 9}, {5, 9}});
    aCobManager.RecoverFire({{2, 9}, {5, 9}});
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
    aIceFiller.Start({{3, 7}});

    // 自动修补水路南瓜
    pumpkinFixer.Start(APUMPKIN, {{3, 7}, {4, 7}, {3, 8}, {4, 8}}, 1000);

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
    for (int wave : {1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, 17, 18, 20}) {
        AConnect(ATime(wave, 341 - 373), []{
            normalWaveFire();
        });
    }

    // I-PP
    for (int wave : {5, 14, 19}) {
        AConnect(ATime(wave, -200), []{
            aIceFiller.Coffee();
        });
        AConnect(ATime(wave, -200 + 198 + 100 + 780 - 373), []{
            normalWaveFire();
        });
    }

    // 末尾波
    for (int wave : {9, 19, 20}) {
        if (wave == 19) {
            AConnect(ATime(wave, -200 + 198 + 100 + 780 - 373), []{
                lastWaveFire();
            });
        } else {
            AConnect(ATime(wave, 341 - 373), []{
                lastWaveFire();
            });
        }
    }

    // 冰消珊瑚
    AConnect(ATime(20, -300), []{
        aIceFiller.Coffee();
    });
    
    // 樱桃消刷新延迟
    AConnect(ATime(10, 341 - 100), []{
        ACard(ACHERRY_BOMB, 2, 9);
    });
}