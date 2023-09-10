#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"
#include "ModuleCollisions.h"
#include "ModuleInput.h"
#include "ModuleEnemies.h"
#include "ModulePowerUp.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include <stdio.h>

#include "SDL/include/SDL.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Sprites/background.png");
	warning = App->textures->Load("Assets/Sprites/enemies.png");
	warningFx = App->audio->LoadFx("Assets/Fx/bossWarning.wav");
	App->audio->PlayMusic("Assets/Music/stage1.ogg", 1.0f);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -210);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -220);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -230);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -200);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -210);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -220);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -230);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -240);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -250);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 100, -320);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -510);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -520);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -530);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -540);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -550);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -610);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -620);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -630);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -650);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -620);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -630);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -650);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -660);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -670);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -720);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -730);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -740);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -750);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -760);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -770);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -840);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -850);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -860);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -900);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -910);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -920);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -930);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -940);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -950);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -900);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1000);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1010);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1020);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1030);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1040);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1050);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1110);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1130);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1140);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1150);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -1150);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -1160);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -1170);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1200);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1210);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1220);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1230);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1240);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1250);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1300);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1310);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1320);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1330);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1340);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1350);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1300);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1310);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1320);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1330);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1340);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1350);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -1400);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -1410);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -1420);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1420);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1430);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1440);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1450);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1460);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1470);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -1480);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -1490);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -1500);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 130, -1500);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1510);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1520);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1530);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1540);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1550);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1630);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1650);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1660);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1670);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1680);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1630);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1650);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1660);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1670);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -1680);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -1700);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -1710);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -1720);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1900);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1910);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1920);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1930);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1940);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -1950);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -2000);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -2010);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -2020);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2300);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2310);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2320);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2330);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2340);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2350);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -2610);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -2620);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -2630);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2610);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2620);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2630);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2650);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 100, -2700);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2700);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2710);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2720);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2730);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2740);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2750);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2800);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2810);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2820);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2830);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2840);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -2850);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2900);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2910);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2920);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2930);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2940);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -2950);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -3010);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -3020);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -3030);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3110);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3130);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3140);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3150);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3110);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3130);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3140);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3150);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -3210);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -3220);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -3230);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -3280);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3300);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3310);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3320);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3330);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3340);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3350);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3400);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3410);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3420);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3430);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3440);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3450);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -3500);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -3510);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -3520);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 130, -3500);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3510);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3520);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3530);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3540);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3550);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3610);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3620);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3630);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -3650);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -3700);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -3710);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -3720);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3800);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3810);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3820);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3830);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3840);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -3850);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 100, -3900);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -3900);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -3910);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -3920);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4000);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4010);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4020);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4030);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4040);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4050);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4110);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4130);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4140);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4150);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -4190);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -4200);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -4210);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -4200);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4300);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4310);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4320);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4330);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4340);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4350);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4400);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4410);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4420);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4430);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4440);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4450);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4510);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4520);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4530);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4540);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4550);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4610);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4620);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4630);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4650);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -4700);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -4710);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -4720);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 130, -4600);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4700);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4710);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4720);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4730);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4740);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4750);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4800);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4810);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4820);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4830);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4840);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -4850);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4900);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4910);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4920);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4930);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4940);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -4950);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -4990);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -5000);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -5010);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 100, -5000);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -5100);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -5110);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -5120);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5200);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5210);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5220);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5230);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5240);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5250);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5300);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5310);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5320);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5330);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5340);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5350);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -5450);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -5460);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -5470);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -5500);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5510);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5520);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5530);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5540);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5550);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5610);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5620);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5630);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5650);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -5720);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -5730);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -5740);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5800);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5810);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5820);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5830);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5840);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -5850);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5800);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5810);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5820);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5830);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5840);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -5850);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -5920);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -5930);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -5940);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 130, -6000);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6000);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6010);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6020);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6030);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6040);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6050);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6110);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6130);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6140);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6150);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -6220);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -6230);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -6240);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6200);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6210);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6220);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6230);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6240);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6250);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6300);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6310);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6320);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6330);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6340);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6350);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6300);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6310);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6320);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6330);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6340);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6350);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -6400);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -6410);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -6420);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6450);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6460);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6470);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6480);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6490);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6500);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 100, -6500);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6510);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6520);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6530);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6540);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6550);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6610);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6620);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6630);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6650);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6610);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6620);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6630);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6650);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -6720);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -6730);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -6740);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6800);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6810);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6820);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6830);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6840);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6850);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6800);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6810);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6820);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6830);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6840);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6850);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6900);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6910);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6920);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6930);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6940);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -6950);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -6900);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -6910);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -6920);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6950);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6960);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6970);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6980);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -6990);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7000);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -7000);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -7000);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -7010);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -7020);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7110);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7130);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7140);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7150);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7200);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7210);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7220);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7230);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7240);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7250);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7200);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7210);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7220);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7230);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7240);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7250);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -7320);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -7330);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -7340);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7400);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7410);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7420);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7430);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7440);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7450);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7400);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7410);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7420);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7430);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7440);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7450);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -7490);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -7500);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -7520);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7510);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7520);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7530);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7540);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7550);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 130, -7500);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -7550);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -7560);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -7570);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7610);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7620);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7630);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7650);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7600);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7610);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7620);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7630);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7640);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7650);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7700);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7710);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7720);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7730);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7740);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7750);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -7720);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -7730);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -7740);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7800);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7810);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7820);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7830);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7840);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7850);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7800);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7810);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7820);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7830);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7840);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -7850);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -7890);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -7800);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -7810);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7900);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7910);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7920);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7930);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7940);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -7950);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 100, -8000);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -8050);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -8060);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -8070);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8110);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8130);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8140);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8150);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8100);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8110);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8120);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8130);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8140);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8150);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8200);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8210);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8220);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8230);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8240);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8250);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -8220);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -8230);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -8240);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8300);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8310);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8320);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8330);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8340);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8350);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8400);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8410);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8420);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8430);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8440);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, 5, -8450);

	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 40, -8490);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 80, -8500);
	App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, 120, -8510);

	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8500);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8510);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8520);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8530);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8540);
	App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, 5, -8550);

	App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, 50, -8500);

	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_1, 110, -400);

	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_2, 70, -600);

	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_1, 150, -1000);

	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_2, 110, -2000);

	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_1, 70, -3000);

	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_2, 150, -4000);

	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_1, 70, -5000);

	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_2, 150, -6000);

	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_1, 110, -7000);

	App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_2, 70, -8000);

	

	App->render->camera.x = 0;
	App->render->camera.y = 0;
	screenBoundingBox = App->collisions->AddCollider({ 0, 0, 240, 10 }, Collider::Type::SCREENBOUNDINGBOX, this);

	bgSize = { 518, 1, 240, 340 };
	warningTimer = 30;

	App->UI->Enable();
	App->player->Enable();
	App->enemies->Enable();
	App->powerups->Enable();
	App->collisions->Enable(); 

	return ret;
}

update_status SceneLevel1::Update()
{
	App->render->camera.y -= 1;
	screenBoundingBox->SetPos(0, App->render->camera.y);

	//set mouseState and mouseCoords
	mouseState = App->input->GetMouse(&mousePos.x, &mousePos.y);

	if (spawnMode)
	{
		if (App->input->keys[SDL_SCANCODE_1] == KEY_STATE::KEY_DOWN)
		{
			selectedSpawnItem = 1;
		}
		else if (App->input->keys[SDL_SCANCODE_2] == KEY_STATE::KEY_DOWN)
		{
			selectedSpawnItem = 2;
		}
		else if (App->input->keys[SDL_SCANCODE_3] == KEY_STATE::KEY_DOWN)
		{
			selectedSpawnItem = 3;
		}
		else if (App->input->keys[SDL_SCANCODE_4] == KEY_STATE::KEY_DOWN)
		{
			selectedSpawnItem = 4;
		}
		else if (App->input->keys[SDL_SCANCODE_5] == KEY_STATE::KEY_DOWN)
		{
			selectedSpawnItem = 5;
		}
		else if (App->input->keys[SDL_SCANCODE_6] == KEY_STATE::KEY_DOWN)
		{
			selectedSpawnItem = 6;
		}
		else if (App->input->keys[SDL_SCANCODE_7] == KEY_STATE::KEY_DOWN)
		{
			selectedSpawnItem = 7;
		}


		if (mouseState == 1)
		{
			switch (selectedSpawnItem)
			{
			case 1:
				App->enemies->AddEnemy(ENEMY_TYPE::REDBALL, mousePos.x + App->render->camera.x, mousePos.y + App->render->camera.y);
				break;
			case 2:
				App->enemies->AddEnemy(ENEMY_TYPE::BLUEDRAGON, mousePos.x + App->render->camera.x, mousePos.y + App->render->camera.y);
				break;
			case 3:
				App->enemies->AddEnemy(ENEMY_TYPE::REDBALLSTRAIGHT, mousePos.x + App->render->camera.x, mousePos.y + App->render->camera.y);				
				break;
			case 4:
				App->enemies->AddEnemy(ENEMY_TYPE::WIZZARD, mousePos.x + App->render->camera.x, mousePos.y + App->render->camera.y);
				break;
			case 5:
				App->enemies->AddEnemy(ENEMY_TYPE::REDBAT, mousePos.x + App->render->camera.x, mousePos.y + App->render->camera.y);
				break;
			case 6:
				App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_1, mousePos.x + App->render->camera.x, mousePos.y + App->render->camera.y);
				break;
			case 7:
				App->powerups->AddPowerUp(POWERUP_TYPE::POWERUP_2, mousePos.x + App->render->camera.x, mousePos.y + App->render->camera.y);
				break;
			default:
				break;
			}
		}
	}

	if (App->DEBUG)
	{
		if (App->input->keys[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN && !spawnMode)
		{
			spawnMode = true;
			LOG("Spawn Mode enabled");
		}
		else if (App->input->keys[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN && spawnMode)
		{
			spawnMode = false;
			LOG("Spawn Mode disabled");
		}

		if (App->input->keys[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN && App->render->camera.y > -9000) {
			App->render->camera.y = -8700; //-9000
			App->player->position.y = -8600; //-8900
		}

		if (App->input->keys[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN) {

			if(App->speedMultiplier == 1)App->speedMultiplier = 2;
			else App->speedMultiplier = 1;
			
		}
	}

	if(App->render->camera.y == -9100) App->enemies->AddEnemy(ENEMY_TYPE::BOSS, -15, -9050);

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneLevel1::PostUpdate()
{	
	//LOG( "%d, %d", App->render->camera.y, App->player->position.y);

	if (App->render->camera.y < -5000 && App->render->camera.y > -7500){
		if (bgSize.x != 775) bgSize.x = 775;
	}

	else if (App->render->camera.y < -7500 && App->render->camera.y > -8800){
		if (bgSize.x != 1031) bgSize.x = 1031;
		bgSpeed = 2;
	}

	else if (App->render->camera.y < -8800) {
		if (bgSize.x != 518) bgSize.x = 518;
		bgSpeed = 8;
	}

	//Infinite Background (Hem penso que amb App->render->camera.y es pot fer)
	if (bgPos < 340) {
		App->render->Blit(bgTexture, 0, bgPos, &bgSize, 0);
		App->render->Blit(bgTexture, 0, bgPos - 340, &bgSize, 0);
		bgPos += bgSpeed;
	}
	else {
		bgPos = 0;
		App->render->Blit(bgTexture, 0, bgPos, &bgSize, 0);
		App->render->Blit(bgTexture, 0, bgPos - 340, &bgSize, 0);
	}

	if ((App->render->camera.y < -8800) && (App->render->camera.y > -8900))
	{
		SDL_Rect warningSize = { 163,166,265,44 };
		SDL_Rect warningSize1 = { 168,212,265,44 };
		LOG("Warning");
		if (warningSelected)
		{
			App->audio->PlayFx(warningFx);
			App->render->Blit(warning, 0, App->render->camera.y + 100, &warningSize, 1);
		}
		else
		{
			App->audio->PlayFx(warningFx);
			App->render->Blit(warning, 0, App->render->camera.y + 100, &warningSize1, 1);
		}
		
		if (warningTimer > 0) warningTimer--;
		else
		{
			warningTimer = 30;
			if (warningSelected)
			{
				warningSelected = false;
			}
			else
			{
				warningSelected = true;
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	// TODO 5: Remove all memory leaks
	App->UI->Disable();
	App->player->Disable();
	App->enemies->Disable();
	App->collisions->Disable();
	App->powerups->Disable();
	//App->textures->Unload(bgTexture);

	return true;
}