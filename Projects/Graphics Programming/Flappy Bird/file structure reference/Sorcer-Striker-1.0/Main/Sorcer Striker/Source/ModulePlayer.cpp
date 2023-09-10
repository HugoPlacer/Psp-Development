#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{
	// idle animation - just one sprite
	idleAnim.PushBack({ 0, 0, 30, 38 });

	leftAnim.PushBack({ 2, 46, 31, 38 });
	leftAnim.PushBack({ 7, 93, 24, 38 });
	leftAnim.loop = false;
	leftAnim.speed = 0.1f;

	rightAnim.PushBack({ 43, 46, 31, 38 });
	rightAnim.PushBack({ 45, 93, 24, 38 });
	rightAnim.loop = false;
	rightAnim.speed = 1.0f;

	powerUp1.PushBack({ 50, 0, 21, 13 });
	powerUp1.PushBack({ 50, 14, 21, 9 });
	powerUp1.PushBack({ 50, 24, 21, 12 });
	powerUp1.speed = 0.1f;

	bombState[0].PushBack({ 19, 291, 28, 28 });
	bombState[0].PushBack({ 52, 291, 28, 28 });
	bombState[0].PushBack({ 75, 291, 28, 28 });
	bombState[0].loop = false;
	bombState[0].speed = 0.16f;

	bombState[1].PushBack({ 104, 285, 129, 38 });

	bombState[1].PushBack({ 8, 326, 71, 71 });
	bombState[1].PushBack({ 83, 326, 86, 86 });
	bombState[1].PushBack({ 172, 326, 130, 130 });
	bombState[1].PushBack({ 305, 324, 102, 102 });

	bombState[1].PushBack({ 15, 423, 78, 81 });

	bombState[1].PushBack({ 90, 425, 78, 81 });

	bombState[1].PushBack({ 296, 435, 77, 80 });
	bombState[1].PushBack({ 389, 435, 77, 81 });
	bombState[1].PushBack({ 296, 435, 77, 80 });
	bombState[1].PushBack({ 389, 435, 77, 81 });
	bombState[1].PushBack({ 296, 435, 77, 80 });
	bombState[1].PushBack({ 389, 435, 77, 81 });
	bombState[1].PushBack({ 296, 435, 77, 80 });
	bombState[1].PushBack({ 389, 435, 77, 81 });
	bombState[1].PushBack({ 296, 435, 77, 80 });
	bombState[1].PushBack({ 389, 435, 77, 81 });
	bombState[1].loop = false;
	bombState[1].speed = 0.16f;

}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Sprites/ship.png");
	bombTexture = App->textures->Load("Assets/Sprites/particles.png");
	currentAnimation = &idleAnim;
	
	laserFx = App->audio->LoadFx("Assets/Fx/laser.wav");
	explosionFx = App->audio->LoadFx("Assets/Fx/explosion.wav");
	bombFx = App->audio->LoadFx("Assets/Fx/bomb.wav");

	position.x = 110;
	position.y = 150;

	backupPosition = position;

	// TODO 4: Retrieve the player when playing a second time
	destroyed = false;
	destroyedCountdown = 120;
	godMode = false;
	spawnCountdown = SPAWNDELAY;
	bombActivatedTimer = 0;
	bombStartedTimer = 0;
	bombAmount = 3;
	bombActivated = false;
	bombStarted = false;
	win = false;
	score = 000;
	lives = 3;
	kills = 0;
	PowerUpActivated[0] = false;
	PowerUpActivated[1] = false;
	transitionTimer = 240;


	collider = App->collisions->AddCollider({ position.x, position.y, 29, 38 }, Collider::Type::PLAYER, this);

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { " 01..........23456789" };
	scoreFont = App->fonts->Load("Assets/Fonts/yb-numbers.png", lookupTable, 1);

	return ret;
}

update_status ModulePlayer::Update()
{
	GamePad& pad = App->input->pads[0];

	// Moving the player with the camera scroll
	position.y -= 1;
	backupPosition.y -= 1;

	if (spawnCountdown > 0) spawnCountdown--;

	if (bombActivated || bombStarted)
	{
		spawnCountdown = 10;
	}

	shipleft.Update();
	shipright.Update();

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || pad.l_x < 0.0f)
	{
		if (position.x >= 0) {
			position.x -= speed;
		}
		if (currentAnimation != &leftAnim)
		{
			leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
		
	}

	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || pad.l_x > 0.0f)
	{
		if (position.x <= 208) {
			position.x += speed;
		}
		if (currentAnimation != &rightAnim)
		{
			rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || pad.l_y > 0.0f)
	{
		if (position.y <= (App->render->camera.y) + 300) {
			position.y += speed;
		}
	}

	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || pad.l_y < 0.0f)
	{
		if (position.y >= App->render->camera.y) {
			position.y -= speed;
		}
	}


	if (((App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a == true) || burst) && shootCooldown <= 0)
	{
		if (!burst && burstCounter == 2) {
			burst = true;
			Particle* laser = App->particles->AddParticle(App->particles->laser, position.x + 11, position.y - 20, Collider::Type::PLAYER_SHOT);
			if (laser != nullptr)
			{
				laser->collider->AddListener((Module*)App->enemies);
			}
			App->audio->PlayFx(laserFx);

			if(PowerUpActivated[0]) PowerUp_1();
			if (PowerUpActivated[1]) PowerUp_2();
			App->input->ShakeController(0, 30, 0.4f);
		}

		if (burstCounter <= 0) {
			burst = false;
			burstCounter = 2;
			shootCooldown = 30;
		}
			
		if (burstCountdown <= 0) {
			Particle* laser = App->particles->AddParticle(App->particles->laser, position.x + 11, position.y - 20, Collider::Type::PLAYER_SHOT);
			if (laser != nullptr)
			{
				laser->collider->AddListener((Module*)App->enemies);
			}
			App->audio->PlayFx(laserFx);

			if(PowerUpActivated[0]) PowerUp_1();
			if (PowerUpActivated[1]) PowerUp_2();
			App->input->ShakeController(0, 30, 0.4f);

			burstCountdown = 5;
			burstCounter--;
		}
		else {
			burstCountdown--;
		}

		
	}

	if(shootCooldown > 0) shootCooldown--;

	if ((App->input->keys[SDL_SCANCODE_B] == KEY_STATE::KEY_DOWN || pad.b == true) && bombAmount > 0 && bombActivated == false && bombStarted == false) {
		App->audio->PlayFx(bombFx);
		bombStarted = true;
		bombPosition = position;
		bombAmount--;
	}
	bomb();

	// If no up/down movement detected, set the current animation back to idle
	//if (pad.enabled)
	//{
	if ((pad.l_x == 0.0f && pad.l_y == 0.0f) && (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE && App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE))
		currentAnimation = &idleAnim;
	//}
	//else if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE && App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
		//currentAnimation = &idleAnim;

	// TODO 4: Update collider position to player position
	collider->SetPos(position.x, position.y);

	currentAnimation->Update();


	//DEBUG

	if (App->DEBUG)
	{
		if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN) {
			win = true;
		}
		if (App->input->keys[SDL_SCANCODE_F4] == KEY_STATE::KEY_DOWN) {
			lives = -1;
		}
		if (App->input->keys[SDL_SCANCODE_F1] == KEY_STATE::KEY_DOWN && !godMode) {
			godMode = true;
			LOG("godmode on");
		}
		else if (App->input->keys[SDL_SCANCODE_F1] == KEY_STATE::KEY_DOWN && godMode) {
			godMode = false;
			LOG("godmode off");
		}
	}


	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	GamePad& pad = App->input->pads[0];

	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}
	else
	{
		if (destroyedCountdown <= 0) {
			position.x = backupPosition.x;
			position.y = backupPosition.y;
			destroyedCountdown = 120;
			spawnCountdown = SPAWNDELAY;
			destroyed = false;
		}
		else {
			position.x = 50000;
			position.y = -50000;
			destroyedCountdown--;
		}
	}

	if (PowerUpActivated[0])
	{
		powerUp1.Update();
		App->render->Blit(texture, position.x - 25, position.y + 12, &(powerUp1.GetCurrentFrame()));
		App->render->Blit(texture, position.x + 33, position.y + 12, &(powerUp1.GetCurrentFrame()));
	}

	if (PowerUpActivated[1])
	{
		SDL_Rect redBat = { 31, 0, 16, 19 };
		App->render->Blit(texture, position.x - 25, position.y + 12, &redBat);
		App->render->Blit(texture, position.x + 33, position.y + 12, &redBat);
	}

	if (bombStarted)
	{
		if (bombStartedTimer == 0)
		{
			bombState[0].Reset();
			App->input->ShakeController(0, 100, 0.4f);
		}
		if (bombStartedTimer < 50)
		{
			App->render->Blit(bombTexture, bombPosition.x, bombPosition.y - bombStartedTimer*3, &(bombState[0].GetCurrentFrame())); //textura provisional, cambiar por la de la bomba
			bombState[0].Update();
			bombStartedTimer++;
			bombPosition.y--;
		}
		else
		{
			bombStarted = false;
			bombActivated = true;
			bombStartedTimer = 0;
		}
	}

	if (bombActivatedTimer < 120 && bombActivatedTimer != 0)
	{
		if (bombActivatedTimer == 1)
		{
			bombState[1].Reset();
			App->input->ShakeController(0, 2000, 0.1f);
		}
		App->render->Blit(bombTexture, bombPosition.x - 40, bombPosition.y - 150, &(bombState[1].GetCurrentFrame()));
		bombState[1].Update();
	}

	if (win && transitionTimer <= 0) {
		App->speedMultiplier = 1;
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->scenefinal, 60);
	}
	else if (win && transitionTimer > 0) transitionTimer--;

	if (lives < 0 && transitionTimer <= 0) {
		App->speedMultiplier = 1;
		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);
	}
	else if (lives < 0 && transitionTimer > 0) transitionTimer--;

	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || pad.l_x < 0.0f) {
		SDL_Rect rect = shipleft.GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}
	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || pad.l_x > 0.0f) {
		SDL_Rect rect = shipright.GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::PLAYER && (c2->type == Collider::Type::ENEMY || c2->type == Collider::Type::ENEMY_SHOT) && lives <= 0)
	{
		lives--;
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::PARTICLE, 9);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, Collider::Type::PARTICLE, 14);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, Collider::Type::PARTICLE, 40);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, Collider::Type::PARTICLE, 28);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, Collider::Type::PARTICLE, 21);

		App->audio->PlayFx(explosionFx);

		destroyed = true;
		App->input->ShakeController(0, 500, 0.33f);
	}
	else if(c1->type == Collider::Type::PLAYER && (c2->type == Collider::Type::ENEMY || c2->type == Collider::Type::ENEMY_SHOT) && destroyed == false && spawnCountdown <= 0 && !godMode){
		destroyed = true;
		App->input->ShakeController(0, 500, 0.33f);
		backupPosition = position;
		PowerUpActivated[0] = false;
		PowerUpActivated[1] = false;
		lives--;
	}

}

void ModulePlayer::PowerUp_1() {
	Particle* batShotL = App->particles->AddParticle(App->particles->bat_shotsR, position.x -20, position.y + 20, Collider::Type::PLAYER_SHOT);
	batShotL = App->particles->AddParticle(App->particles->bat_shotsL, position.x +30, position.y + 20, Collider::Type::PLAYER_SHOT);
	if (batShotL != nullptr)
	{
		batShotL->collider->AddListener(this);
	}

	App->audio->PlayFx(laserFx);
}

void ModulePlayer::PowerUp_2() {
	Particle* redShot = App->particles->AddParticle(App->particles->redShot, position.x - 20, position.y + 20, Collider::Type::PLAYER_SHOT); //CHANGE THE PARTICLE!!!
	redShot = App->particles->AddParticle(App->particles->redShot, position.x + 40, position.y + 20, Collider::Type::PLAYER_SHOT);
	if (redShot != nullptr)
	{
		redShot->collider->AddListener(this);
	}

	App->audio->PlayFx(laserFx);
}

void ModulePlayer::bomb() {
	//Primero tiene un delay inicial en el cual la bomba avanza, luego explota el radio del sprite, dura unos segundos y luego acaba.

	if (bombActivated == true)
	{
		if (bombActivatedTimer == 0)
		{
			bombCollider = App->collisions->AddCollider({ bombPosition.x - 35, bombPosition.y - 200, 100, 100 }, Collider::Type::PLAYER_SHOT, (Module*)App->enemies);
			App->render->Blit(texture, bombPosition.x - 35, bombPosition.y - 200, &(powerUp1.GetCurrentFrame()));
		}

		if (bombActivatedTimer < 120)
		{
			bombActivatedTimer++;
			bombPosition.y--;
			bombCollider->SetPos(bombPosition.x - 35, bombPosition.y - 200);
			App->render->Blit(texture, bombPosition.x - 35, bombPosition.y - 200, &(powerUp1.GetCurrentFrame()));
		}
		else
		{
			bombActivatedTimer = 0;
			bombActivated = false;
			bombCollider->pendingToDelete = true;
		}
	}
}