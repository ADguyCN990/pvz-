#include "avz.h"
#include "AutoFodder/main.h"

/*
双冰变奏邻C7u | IP-PP | IP-PP | PA | N | PP | (18,18,6,6,6)
PP：1, 6, 10, 15, 20
IP-PP: 2, 3, 7, 8, 11, 12, 16, 17
PA: 4, 9, 13, 18
N: 5, 14, 19
*/

ACobManager windCob;
ACobManager groudCob;

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
                  AUMBRELLA_LEAF,
                  AJALAPENO,
                  ACOFFEE_BEAN,
                  AFLOWER_POT,
                  ACHERRY_BOMB,
                  ATALL_NUT,
                  ASQUASH,
                  AICE_SHROOM,
                  ADOOM_SHROOM});

    // 开启10倍速挂机
    //AFK();

    // RE场景的部分炮位存在平地炮和斜地炮，落点时间不同，需要分组管理
    AConnect(ATime(1, -599), []{
        windCob.SetList({{2, 1}, {3, 1}, {4, 1}});
        groudCob.SetList({{2, 6}, {3, 6}, {4, 6}}); 
        ACard(AFLOWER_POT, 1, 1);
    });

    AConnect(ATime(1, 152), [=]{
        ACard(AFLOWER_POT, 1, 2);
        ACard(AUMBRELLA_LEAF, 1, 2);
    });

    AConnect(ATime(2, 303), [=]{
        ACard(AFLOWER_POT, 5, 3);
        ACard(ATALL_NUT, 5, 3);
    });
    AConnect(ATime(2, 1054), [=]{
        ACard(AFLOWER_POT, 5, 2);
        ACard(AUMBRELLA_LEAF, 5, 2);
    });
    AConnect(ATime(3, 5), [=]{
        ACard(AFLOWER_POT, 1, 3);
    });
    AConnect(ATime(3, 756), [=]{
        ACard(AFLOWER_POT, 5, 1);
    });
    AConnect(ATime(4, 0), [=]{
        ACard(ATALL_NUT, 1, 3);
    });

    // PP
    for (int wave : {1, 6, 10, 15, 20}) {
        AConnect(ATime(wave, 600 - 200 - 387), [=]{
            windCob.RoofFire(2, 9);
            groudCob.RoofFire(4, 9);
        });
    }
    
    // IP-PP 原版冰
    for (int wave : {2, 7, 11, 16}) {
        AConnect(ATime(wave, 1 - 100), [=]{
            ACard(AICE_SHROOM, 1, 1);
        });
        AConnect(ATime(wave, 1800 - 200 - 387), [=]{
            windCob.RoofFire(2, 8.5);
            groudCob.RoofFire(4, 8.5);
        });
        // 下一波的复制者冰
        AConnect(ATime(wave, 1800 + 10 - 100 - 319), [=]{
            ACard(AM_ICE_SHROOM, 1, 1);
        });
    }
    for (int wave : {2, 11}) {
        AConnect(ATime(wave, 341 - 387), [=]{
            windCob.RoofFire(3, 9);
        });
    }
    for (int wave : {7, 16}) {
        AConnect(ATime(wave, 341 - 387), [=]{
            groudCob.RoofFire(3, 9);
        });
    }

    // I-PP 复制者冰
    for (int wave : {3, 8, 12, 17}) {       
        AConnect(ATime(wave, 1800 - 200 - 387), [=]{
            windCob.RoofFire(2, 9);
            groudCob.RoofFire(4, 9);
        });
    }
    for (int wave : {3, 12}) {
        AConnect(ATime(wave, 341 - 387), [=]{
            groudCob.RoofFire(3, 9);
        });
    }
    for (int wave : {8, 17}) {
        AConnect(ATime(wave, 341 - 387), [=]{
            windCob.RoofFire(3, 9);
        });
    }

    // PA
    for (int wave : {4, 9, 13, 18}) {
        AConnect(ATime(wave, 149), [=]{
            ACard(AFLOWER_POT, 4, 9);
            ACard(ACHERRY_BOMB, 4, 9);
            //ACard(AJALAPENO, 5, 3);
        });
    }
    for (int wave : {4, 13}) {
        AConnect(ATime(wave, 600 - 200 - 387), [=]{
            windCob.RoofFire(2, 9);
        });
    }
    for (int wave : {9, 18}) {
        AConnect(ATime(wave, 600 - 200 - 387), [=]{
            groudCob.RoofFire(2, 9);
        });        
    }

    // N
    AConnect(ATime(5, 300), [=]{
        ACard(AFLOWER_POT, 2, 9);
        ACard(ADOOM_SHROOM, 2, 9);
    });
    AConnect(ATime(14, 300), [=]{
        ACard(AFLOWER_POT, 3, 9);
        ACard(ADOOM_SHROOM, 3, 9);
    });
    AConnect(ATime(19, 300), [=]{
        ACard(AFLOWER_POT, 4, 9);
        ACard(ADOOM_SHROOM, 4, 9);
    });

    // 冰杀三人组
    AConnect(ATime(20, 199 - 100), [=]{
        ACard(AICE_SHROOM, 1, 1);
    });
    
    //收尾
    for (int wave : {9, 19, 20}) {
        AConnect(ATime(wave, 600 - 387), [=]{
            windCob.RecoverRoofFire({{2, 9}, {2, 9}});
            groudCob.RecoverRoofFire({{4, 9}, {4, 9}});
        });
    }

}