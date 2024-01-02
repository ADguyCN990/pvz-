#include "avz.h"
#include "AutoFodder/main.h"

/*
双冰变奏ch5u | IP-PP | I-PP | PP | (17.5, 12.5, 6)
PP：1, 4, 7, 10, 13, 16, 19, 20
IP-PP: 2, 5, 8, 11*, 14, 17
I-PP: 3, 6, 9, 12, 15, 18
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
                  APUFF_SHROOM,
                  ACOFFEE_BEAN,
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
        windCob.SetList({{2, 1}, {3, 1}, {4, 1}, {3, 3}});
        groudCob.SetList({{2, 6}, {3, 6}, {4, 6}}); 
        ACard(AFLOWER_POT, 1, 1);
    });

    // 自动存冰
    aIceFiller.Start({{2, 3}, {4, 3}, {1, 1}});

    // PP
    for (int wave : {1, 4, 7, 10, 13, 16, 20}) {
        AConnect(ATime(wave, 600 - 200 - 387), [=]{
            windCob.RoofFire(2, 9);
            groudCob.RoofFire(4, 9);
        });
    }
    
    // IP-PP
    for (int wave : {2, 5, 8, 14, 17}) {
        AConnect(ATime(wave, -200), [=]{
            aIceFiller.Coffee();
        });
        AConnect(ATime(wave, 341 - 387), [=]{
            windCob.RoofFire(3, 9);
        });
        AConnect(ATime(wave, 1750 - 200 - 387), [=]{
            windCob.RoofFire(2, 8.5);
            groudCob.RoofFire(4, 8.5);
        });
    }

    // I-PP
    for (int wave : {3, 6, 9, 12, 15, 18, 19}) {
        AConnect(ATime(wave, -200), [=]{
            aIceFiller.Coffee();
        });
        AConnect(ATime(wave, 1250 - 200 - 387), [=]{
            windCob.RoofFire(2, 9);
            groudCob.RoofFire(4, 9);
        });
    }

    //冰杀小偷
    AConnect(ATime(10, 673 - 100 - 198), [=]{
        aIceFiller.Coffee();
    });
    AConnect(ATime(11, 341 - 387), [=]{
            windCob.RoofFire(3, 9);
    });
    AConnect(ATime(11, 1750 - 200 - 387), [=]{
        windCob.RoofFire(2, 8.5);
        groudCob.RoofFire(4, 8.5);
    });
    AConnect(ATime(20, 394 + 1 - 100 - 198), [=]{
        aIceFiller.Coffee();
    });
    
    //收尾
    for (int wave : {9, 19, 20}) {
        AConnect(ATime(wave, 1250 - 200 - 387), [=]{
            windCob.RecoverRoofFire({{2, 9}});
            groudCob.RecoverRoofFire({{4, 9}});
        });
        AConnect(ATime(wave, 1350 - 200 - 387), [=]{
            windCob.RecoverRoofFire({{2, 9}});
            groudCob.RecoverRoofFire({{4, 9}});
        });
        AConnect(ATime(wave, 1500), [=]{
            ACard(AFLOWER_POT, 3, 8);
        });
        AConnect(ATime(wave, 1800 - 100), [=]{
            ACard(ACHERRY_BOMB, 3, 8);
        });
    }

}