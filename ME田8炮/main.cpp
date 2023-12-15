#include "avz.h"
#include "AutoFodder/main.h"

/*
单冰变奏S5 | I-PP | PP | PP | PP (12.5, 7.5, 7.5, 7.5)
第1波预判炸，第2波预判炸，第10波预判炸，第11波预判炸。4个加速波+15s的波长可以保证在用冰有盈余的前提下实现稳定控丑。
PPPPIPPPI I*PPPIPPPIP I*
*/

ACobManager windCob;
ACobManager groudCob;

void AFK() {
    // 挂机
    ASetReloadMode(AReloadMode::MAIN_UI_OR_FIGHT_UI);
    // 十倍速
    ASetGameSpeed(10);
}

void normalWaveFire() {
    windCob.RoofFire(2, 9);
    groudCob.RoofFire(4, 9);
}

void lastWaveFire() {
    windCob.RecoverRoofFire({{2, 9}, {2, 9}, {2, 9}});
    groudCob.RecoverRoofFire({{4, 9}, {4, 9}, {4, 9}});
}

void AScript() {
    // 全难度极限出怪：普僵、撑杆、橄榄、舞王、冰车、小丑、矿工、跳跳、小偷、扶梯、投篮、白眼、红眼、海豚
    ASetZombies({AZOMBIE,
                 APOLE_VAULTING_ZOMBIE,
                 AFOOTBALL_ZOMBIE,
                 //ADANCING_ZOMBIE,
                 AZOMBONI,
                 AJACK_IN_THE_BOX_ZOMBIE,
                 ABALLOON_ZOMBIE,
                 //ADIGGER_ZOMBIE,
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
                  ASQUASH,
                  AICE_SHROOM,
                  ADOOM_SHROOM});

    // 开启10倍速挂机
    //AFK();

    // RE场景的部分炮位存在平地炮和斜地炮，落点时间不同，需要分组管理
    AConnect(ATime(1, -599), []{
        windCob.SetList({{1, 1}, {2, 1}, {4, 1}, {5, 1}});
        groudCob.SetList({{1, 6}, {2, 6}, {4, 6}, {5, 6}}); 
        AShovel(3, 3);
    });

    // // 自动垫材
    // AConnect([=]{return true;}, [=]{
    //     AAutoFodder({}, {}, {AFLOWER_POT}, 79);
    // });

    // 冰位
    AConnect(ATime(1, 0), [=]{
        ACard(AFLOWER_POT, 3, 3);
    });

    // PP
    for (int wave : {1, 2, 3, 4, 6, 7, 8, 10, 11, 12, 13, 15, 16, 17, 19, 20}) {
        AConnect(ATime(wave, 541 - 387), [=]{
            normalWaveFire();
        });
    }

    // I-PP 使用原版冰
    for (int wave : {5, 18}) {
        AConnect(ATime(wave, 1 - 100), [=]{
            ACard(AICE_SHROOM, 3, 3);
        });
        AConnect(ATime(wave, 1052 - 387), [=]{
            normalWaveFire();
        });
    }
    // I-PP 使用复制者冰
    for (int wave : {9, 14}) {
        AConnect(ATime(wave, -200), [=]{
            ACard(AM_ICE_SHROOM, 3, 3);
        });
        AConnect(ATime(wave, 1052 - 387), [=]{
            normalWaveFire();
        });
    }

    // 第10波使用原版冰杀小偷
    AConnect(ATime(10, 395 - 100), [=]{
        ACard(AICE_SHROOM, 3, 3);
    });

    // 第20波使用复制者冰杀小偷
    AConnect(ATime(20, 395 - 319 - 100), [=]{
        ACard(AM_ICE_SHROOM, 3, 3);
    });
    
    // 第20波炮杀空降三人组
    AConnect(ATime(20, 223 + 375 - 387), [=]{
        windCob.RoofFire(2, 7);
        groudCob.RoofFire(4, 7);
    });

    // 收尾
    for (int wave : {19}) {
        AConnect(ATime(wave, 541 - 387), [=]{
            lastWaveFire();
        });
    }
    for (int wave : {9, 20}) {
        AConnect(ATime(wave, 1052 - 387), [=]{
            lastWaveFire();
        });        
    }
}