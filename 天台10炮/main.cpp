#include "avz.h"
ATickRunner tickRunner;

/*
天台10炮 P5节奏
| PP | PP | PP | PP | PP | (3475/5, 3475/5, 3475/5, 3475/5, 3475/5)
*/

ACobManager windCob;
ACobManager groudCob;

void normalWaveFire() {
    windCob.RoofFire(2, 9);
    groudCob.RoofFire(4, 9);
}

void lastWaveFire() {
    normalWaveFire();
    // 补两次炮收红眼
    windCob.RecoverRoofFire({{2, 9}, {2, 9}});
    groudCob.RecoverRoofFire({{4, 9}, {4, 9}});
}

void AScript() {
    ASetZombies({
        AZOMBIE,                 // 普通僵尸
        APOLE_VAULTING_ZOMBIE,   // 撑杆
        AFOOTBALL_ZOMBIE,        // 橄榄
        AZOMBONI,                // 冰车
        AJACK_IN_THE_BOX_ZOMBIE, // 小丑
        APOGO_ZOMBIE,            // 跳跳
        ABUNGEE_ZOMBIE,          // 蹦极
        ALADDER_ZOMBIE,          // 梯子
        ACATAPULT_ZOMBIE,        // 投篮
        AGARGANTUAR,             // 白眼
        AGIGA_GARGANTUAR         // 红眼
    });
    ASelectCards({
        AICE_SHROOM,   // 寒冰菇
        AM_ICE_SHROOM, // 模仿寒冰菇
        ACOFFEE_BEAN,  // 咖啡豆
        ADOOM_SHROOM,  // 毁灭菇
        AFLOWER_POT,   // 花盆
        ASQUASH,       // 倭瓜
        ACHERRY_BOMB,  // 樱桃炸弹
        ABLOVER,       // 三叶草
        APUMPKIN,      // 南瓜头
        APUFF_SHROOM,  // 小喷菇
    });

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

    // RE场景的部分炮位存在平地炮和斜地炮，落点时间不同，需要分组管理
    AConnect(ATime(1, -599), []
             {
        windCob.SetList({{1, 1}, {2, 1}, {4, 1}, {5, 1}});
        groudCob.SetList({{1, 6}, {2, 6}, {4, 6}, {5, 6}}); });

    // 主体节奏
    for (int wave : {1, 2, 3, 4, 5, 6, 7, 8, 11, 12, 13, 14, 15, 16, 17, 18}) {
        AConnect(ATime(wave, 3475 / 5 - 200 - 387), []{
            normalWaveFire();
        });
    }

    // 末尾波
    for (int wave: {9, 19}) {
        AConnect(ATime(wave, 3475 / 5 - 200 - 387), []{
            lastWaveFire();
        });
    }

    // 第10波
    AConnect(ATime(10, 3475 / 5 - 200 - 100), []{
        // 使用樱桃避免延迟刷新
        ACard(AFLOWER_POT, 2, 9);
        ACard(ACHERRY_BOMB, 2, 9);
    });
    AConnect(ATime(10, 3475 / 5 - 200 - 387), []{
        normalWaveFire();
    });

    // 第20波
    AConnect(ATime(20, -298 - 1), []{
        // 冰消小偷
        ACard(AFLOWER_POT, 2, 9);
        ACard(AICE_SHROOM, 2, 9);
        ACard(ACOFFEE_BEAN, 2, 9);
    });
    AConnect(ATime(20, 3475 / 5 - 200 - 387), []{
        lastWaveFire();
    });
}