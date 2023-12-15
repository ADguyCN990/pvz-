#include "avz.h"
#include "AutoFodder/main.h"

/*
双冰变奏ch5 | I-PP | I-PP | PP | (15, 15, 6)
第1波预判炸，第2波预判炸，第10波预判炸，第11波预判炸。4个加速波+15s的波长可以保证在用冰有盈余的前提下实现稳定控丑。
11221 2212 11221 22122 1
*/

APlantFixer pumpkinFixer;

void AFK() {
    // 挂机
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    // 十倍速
    ASetGameSpeed(10);
}

void preWaveFire() {
    aCobManager.Fire(2, 9);
    aCobManager.Fire(4, 9);
}

void normalWaveFire() {
    aCobManager.Fire(2, 8.5);
    aCobManager.Fire(4, 8.5);
}

void lastWaveFire() {
    aCobManager.RecoverFire(2, 8.5);
    aCobManager.RecoverFire(4, 8.5);
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
                  APUMPKIN,
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
    aIceFiller.Start({{1, 1}, {5, 1}});

    // 自动修补底线南瓜
    pumpkinFixer.Start(APUMPKIN, {{1, 1}, {2, 1}, {4, 1}, {5, 1}}, 4000 / 3 * 2);

    // 自动垫材
    AConnect([=]{return true;}, [=]{
        AAutoFodder({{1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}}, {}, {APUFF_SHROOM, ASUN_SHROOM, AFLOWER_POT, ASCAREDY_SHROOM}, 79);
    });


    // PP
    for (int wave : {1, 2, 5, 8, 10, 11, 14, 17, 20}) {
        AConnect(ATime(wave, 341 - 373), [=]{
            preWaveFire();
        });
    }

    // I-PP
    for (int wave : {3, 4, 6, 7, 9, 12, 13, 15, 16, 18, 19}) {
        AConnect(ATime(wave, -200), [=]{
            aIceFiller.Coffee();
        });
        AConnect(ATime(wave, 1300 - 373), [=]{
            normalWaveFire();
        });
    }

    // 收尾
    for (int wave : {9, 19, 20}) {
        AConnect(ATime(wave, 1300 - 373), [=]{
            lastWaveFire();
        });
    }

    // 第20波最后再轰一炮
    AConnect(ATime(20, 1300 - 373), [=]{
        aCobManager.RecoverFire(2, 8);
        aCobManager.RecoverFire(5, 8);
    });

    // 第10波樱桃炸弹防止刷新延迟
    AConnect(ATime(10, 341 - 100), [=]{
        ACard(ACHERRY_BOMB, 2, 9);
    });
}