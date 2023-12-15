#include "avz.h"
#include "AutoFodder/main.h"

/*
单冰变奏S4 | I-PP | PP | PP | (20, 7.5, 7.5)
PPIPPIPPI NPIPPIPPIP I*
*/

APlantFixer tallnutFixer;

void AFK() {
    // 挂机
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    // 十倍速
    ASetGameSpeed(10);
}

void preWaveFire() {
    aCobManager.Fire(2, 9);
    aCobManager.Fire(5, 9);
}

void normalWaveFire() {
    aCobManager.Fire(2, 8);
    aCobManager.Fire(5, 8);
}

void lastWaveFire() {
    aCobManager.RecoverFire(2, 8);
    aCobManager.RecoverFire(5, 8);
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
                  ATALL_NUT,
                  AFLOWER_POT,
                  ALILY_PAD,
                  ASCAREDY_SHROOM,
                  ACOFFEE_BEAN,
                  AICE_SHROOM,
                  ADOOM_SHROOM});

    // 开启10倍速挂机
    //AFK();

    // 初始化炮位
    AConnect(ATime(1, -599), []{ aCobManager.AutoSetList(); });

    // 自动修补水路高坚果
    tallnutFixer.Start(ATALL_NUT, {{3, 7}, {4, 7}}, 8000 / 3 * 2);

    // 自动存冰
    aIceFiller.Start({{1, 5}});

    // 自动垫材
    AConnect([=]{return true;}, [=]{
        AAutoFodder({{1, 6}, {2, 6}, {5, 6}}, {}, {APUFF_SHROOM, ASUN_SHROOM, AFLOWER_POT, ASCAREDY_SHROOM}, 79);
    });

    // PP
    for (int wave : {1, 2, 4, 5, 7, 8, 11, 13, 14, 16, 17, 19}) {
        AConnect(ATime(wave, 550 - 373), [=]{
            preWaveFire();
        });
    }

    // I-PP
    for (int wave : {3, 6, 9, 12, 15, 18}) {
        AConnect(ATime(wave, -200), [=]{
            aIceFiller.Coffee();
        });
        AConnect(ATime(wave, 1800 - 373), [=]{
            normalWaveFire();
        });
    }

    // 第10波的核弹
    AConnect(ATime(10, 400 - 198 - 100), [=]{
        ACard(ALILY_PAD, 3, 8);
        ACard(ADOOM_SHROOM, 3, 8);
        ACard(ACOFFEE_BEAN, 3, 8);
    });

    // 第20波冰杀小偷
    AConnect(ATime(20, 395 - 100 - 198), [=]{
        aIceFiller.Coffee();
        aIceFiller.Stop();
    });
    AConnect(ATime(20, 395 - 373), [=]{
        aCobManager.Fire(3, 7);
    });
    // 第20波炮消珊瑚
    AConnect(ATime(20, 250 - 378), []{ 
        aCobManager.Fire(4, 7.625); 
    });
    // 第20波预判炮
        AConnect(ATime(20, 341 - 373), [=]{
        preWaveFire();
    });

    // 收尾
    for (int wave : {9, 20}) {
        AConnect(ATime(wave, 1800 - 373), [=]{
            lastWaveFire();
        });
    }
    for (int wave : {19}) {
        AConnect(ATime(wave, 550 - 373), [=]{
            lastWaveFire();
        });
    }
    // 第20, 19波最后再轰一炮
    AConnect(ATime(20, 1800 - 373), [=]{
        aCobManager.RecoverFire(2, 8);
        aCobManager.RecoverFire(5, 8);
    });
    AConnect(ATime(19, 550 - 373), [=]{
        aCobManager.RecoverFire(2, 8);
        aCobManager.RecoverFire(5, 8);
    });


}