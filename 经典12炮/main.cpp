#include <avz.h>
ATickRunner tickRunner;
void AScript()
{
    // ASetZombies({

    //     ACG_3,  // 撑杆
    //     ATT_4,  // 铁桶
    //     ABC_12, // 冰车
    //     AXC_15, // 小丑
    //     AQQ_16, // 气球
    //     AFT_21, // 扶梯
    //     ATL_22, // 投篮
    //     ABY_23, // 白眼
    //     AHY_32, // 红眼
    //     ATT_18, // 跳跳
    // });
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    ASelectCards({
        AICE_SHROOM,   // 寒冰菇
        AM_ICE_SHROOM, // 模仿寒冰菇
        ACOFFEE_BEAN,  // 咖啡豆
        ADOOM_SHROOM,  // 毁灭菇
        ALILY_PAD,     // 荷叶
        ASQUASH,       // 倭瓜
        ACHERRY_BOMB,  // 樱桃炸弹
        ABLOVER,       // 三叶草
        APUMPKIN,      // 南瓜头
        APUFF_SHROOM,  // 小喷菇
    });

    AConnect(ATime(1, -599), []
             { aCobManager.AutoSetList(); });

    // 吹气球（从AvZ教程直接粘的）
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

    // P6
    // 主体节奏
    for (auto wave : {1, 2, 3, 4, 5, 6, 7, 8, 11, 12, 13, 14, 15, 16, 17, 18})
    {
        AConnect(ATime(wave, 341 - 373), []
                 { aCobManager.Fire({{2, 9}, {5, 9}}); });
    }

    // wave 9 19 20的附加操作
    // 收尾发四门炮
    for (auto wave : {9, 19, 20})
    {
        AConnect(ATime(wave, 341 - 373), []
                 { aCobManager.Fire({{2, 9}, {5, 9}}); });
        AConnect(ATime(wave, 341 + 20), []
                 {
                if (AIsZombieExist(-1, 1) || AIsZombieExist(-1, 2) || AIsZombieExist(-1, 3)) {
                    aCobManager.RecoverFire(2, 9);
                }
                if (AIsZombieExist(-1, 4) || AIsZombieExist(-1, 5) || AIsZombieExist(-1, 6))
                {
                    aCobManager.RecoverFire(5, 9);
                }
                // if (AIsZombieExist(AGIGA_GARGANTUAR, -1) || AIsZombieExist(AGIGA_GARGANTUAR, -1)) {
                //     aCobManager.RecoverFire({{2, 9}, {5, 9}});
                // } 
                });
        AConnect(ATime(wave, 500+373), []
                 {
                     if (AIsZombieExist(-1, 3) || AIsZombieExist(-1, 4))
                     {
                         aCobManager.RecoverFire(3, 9);
                     }
                 });
        AConnect(ATime(wave, 800+373), []
                 {
                     if (AIsZombieExist(AGIGA_GARGANTUAR, 1) || AIsZombieExist(AGIGA_GARGANTUAR, 2)) {
                    aCobManager.RecoverFire(2, 8.7);
                }
                if (AIsZombieExist(AGIGA_GARGANTUAR, 5) || AIsZombieExist(AGIGA_GARGANTUAR, 6))
                {
                    aCobManager.RecoverFire(5, 8.7);
                } });

        // AConnect(ATime(wave, 1000 + 373), []
        //          {
        //              if (AIsZombieExist(-1, 1) || AIsZombieExist(-1, 2)) {
        //             aCobManager.RecoverFire(2, 8);
        //         }
        //         if (AIsZombieExist(-1, 4) || AIsZombieExist(-1, 5))
        //         {
        //             aCobManager.RecoverFire(5, 8);
        //         } });
    }

    // wave 10 的附加操作
    // 樱桃消延迟
    // 解决僵尸出生点靠右的问题
    AConnect(ATime(10, 341 - 100), []
             { ACard(ACHERRY_BOMB, 2, 9); });
    AConnect(ATime(10, 341 - 373), []
             { aCobManager.Fire({{2, 9}, {5, 9}}); });

    // wave 20 的附加操作
    // 咆哮珊瑚(炮消)
    // 解决僵尸出生点靠右的问题

    AConnect(ATime(20, 250 - 378), []
             { aCobManager.Fire(4, 7.625); });
    // AConnect(ATime(20, 341 - 373), []
    //          { aCobManager.Fire({{2, 9}, {5, 9}}); });
}