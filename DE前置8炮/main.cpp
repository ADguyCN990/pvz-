#include "avz.h"
#include "AutoFodder/main.h"

/*
双冰变奏ch5 | I-PP | IPP-PP | PP | (14.37, 15.63, 6)
123123123
PP:1, 4, 7, 10, 13, 16, 19, 20
I-PP:2, 5, 8, 11*, 14, 17
IPP-PP:3, 6, 9, 12, 15, 18
冰杀小偷：10, 20
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
                 AGARGANTUAR,
                 AGIGA_GARGANTUAR
    });

    // 选卡
    ASelectCards({AM_ICE_SHROOM,
                  ASUN_SHROOM,
                  APUFF_SHROOM,
                  ASQUASH,
                  AFLOWER_POT,
                  ACHERRY_BOMB,
                  ASCAREDY_SHROOM,
                  ACOFFEE_BEAN,
                  AICE_SHROOM,
                  ADOOM_SHROOM});

    // 开启10倍速挂机
    //AFK();

    // 初始化炮位，
    AConnect(ATime(1, -599), []{ aCobManager.AutoSetList(); });

    // 自动存冰
    aIceFiller.Start({{2, 1}, {4, 1}});

    // 自动垫材
    AConnect([=]{return true;}, [=]{
        AAutoFodder({{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}}, {}, {APUFF_SHROOM, ASUN_SHROOM, AFLOWER_POT, ASCAREDY_SHROOM}, 79);
    });

    // PP
    for (int wave : {1, 4, 7, 10, 13, 16, 19, 20}) {
        AConnect(ATime(wave, 341 - 373), [=]{
            aCobManager.Fire({{2, 9}, {4, 9}});
        });
    }

    // I-PP
    for (int wave : {2, 5, 8, 14, 17}) {
        AConnect(ATime(wave, -200), [=]{
            aIceFiller.Coffee();
        });

        AConnect(ATime(wave, 1437 - 373 - 200), [=]{
            aCobManager.Fire({{2, 9}, {4, 9}});
        });
    }

    // IPP-PP
    for (int wave : {3, 6, 9, 12, 15, 18}) {
        AConnect(ATime(wave, -200), [=]{
            // 冰杀矿工
            aIceFiller.Coffee();
            // 热过渡处理旷工
            aCobManager.Fire({{2, 9}, {4, 9}});
        });

        AConnect(ATime(wave, 1563 - 373 - 200), [=]{
            aCobManager.Fire({{2, 8.7}, {4, 8.7}});
        });
    }

    // 冰杀小偷
    AConnect(ATime(10, 673 - 100 - 198), [=]{
        aIceFiller.Coffee();
    });
    AConnect(ATime(11, 1563 - 373 - 200), [=]{
        aCobManager.Fire({{2, 8.7}, {4, 8.7}});
    });
    AConnect(ATime(20, 394 + 1 - 100 - 198), [=]{
        aIceFiller.Coffee();
    });

    // 第10波樱桃炸弹防止刷新延迟
    AConnect(ATime(10, 341 - 100), [=]{
        ACard(ACHERRY_BOMB, 2, 9);
    });

    // 收尾
    for (int wave : {9, 19, 20}) {
        AConnect(ATime(wave, 3475), [=]{
            aCobManager.RecoverFire({{2, 8}, {4, 8}});
        });
        AConnect(ATime(wave, 1563 - 373 - 200), [=]{
            aCobManager.RecoverFire({{2, 8.7}, {4, 8.7}});
        });
    }
}