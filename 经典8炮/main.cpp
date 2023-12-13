#include "avz.h"
/*
经典8炮 P4节奏
| PP | PP | PP | PP | (3475 / 4, 3475 / 4, 3475 / 4, 3475 / 4)
*/
ATickRunner tickRunner;
APlantFixer pumpkinFixer;

void normalWaveFire() {
    aCobManager.Fire(2, 8.8);
    aCobManager.Fire(5, 8.8);
}

void lastWaveFire() {
    normalWaveFire();
    aCobManager.RecoverFire({{2, 8.8}, {5, 8.8}});
    aCobManager.RecoverFire({{2, 8.8}, {5, 8.8}});
}

void plantTrash() {
    ACard(APUFF_SHROOM, 1, 9);
    ACard(AM_PUFF_SHROOM, 2, 9);
    ACard(AFLOWER_POT, 5, 9);
    ACard(ASCAREDY_SHROOM, 6, 9);
}

void AScript(){
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    ASetZombies({
        AZOMBIE,
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
    ASelectCards({
        APUMPKIN, 
        ACHERRY_BOMB, 
        APUFF_SHROOM, 
        AM_PUFF_SHROOM, 
        AFLOWER_POT, 
        ASCAREDY_SHROOM, 
        ASUNFLOWER, 
        ACOFFEE_BEAN, 
        AFUME_SHROOM, 
        AGLOOM_SHROOM
    });

    AConnect(ATime(1, -599), []
             { aCobManager.AutoSetList(); });

    // 自动修补水路南瓜
    pumpkinFixer.Start(APUMPKIN, {{3, 5}, {4, 5}, {3, 6}, {4, 6}, {3, 7}, {4, 7}}, 1000);

    // 配合tickRunner吹气球
    tickRunner.Start([]
                        {
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
        } });
    
    for (int wave = 1; wave <= 20; wave++) {
        // 没波开头种垫材逮捕舞王
        AConnect(ATime(wave, 191), []{
            plantTrash();
        });
    }

    // 主体节奏
    for (int wave : {1, 2, 3, 4, 5, 6, 7, 8, 11, 12, 13, 14, 15, 16, 17, 18, }) {
        AConnect(ATime(wave, 3476 / 4 - 373 - 200), []{
            normalWaveFire();
        });
    }

    // 末尾波
    for (int wave : {9, 19, 20}) {
        AConnect(ATime(wave, 3476 / 4 - 373 - 200), []{
            lastWaveFire();
        });
    }

    // 第10波
    // 使用樱桃防止刷新延迟
    AConnect(ATime(10, 3476 / 4 - 200 - 100), []{ 
        ACard(ACHERRY_BOMB, 2, 9); 
    });
    AConnect(ATime(10, 3476 / 4 - 373 - 200), []{
        normalWaveFire(); 
    });
}