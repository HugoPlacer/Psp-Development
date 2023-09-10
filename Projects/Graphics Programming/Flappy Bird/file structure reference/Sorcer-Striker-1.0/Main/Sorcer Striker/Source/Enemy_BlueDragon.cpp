#include "Enemy_BlueDragon.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

Enemy_BlueDragon::Enemy_BlueDragon(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,45,91,100 });
	fly.PushBack({ 107,45,92,100 });
	fly.PushBack({ 211,45,88,100 });
	fly.PushBack({ 314,45,87,100 });
	
	fly.speed = 0.07f;

	path.PushBack({ 0.0f, 1.0f }, 15);
	path.PushBack({ 0.3f, -0.9f }, 120);
	path.PushBack({ -0.3f, -0.9f }, 120);
	path.PushBack({ 0.0f, 2.0f }, 25);
	path.PushBack({ 0.3f, -0.9f }, 100);
	path.PushBack({ -0.3f, -0.9f }, 100);
	path.PushBack({ 5.0f, -0.0f }, 100);

	currentAnim = &fly;

	/*path.PushBack({-1.0f, -0.5f}, 100);
	path.PushBack({-1.0f, 0.5f}, 80);
	path.PushBack({-1.0f, 1.0f}, 80);*/

	dragonDamaged.PushBack({ 542,227,91,100 });
	dragonDamaged.PushBack({ 650,233,92,100 });
	dragonDamaged.PushBack({ 752,228,88,100 });
	dragonDamaged.PushBack({ 857,230,87,100 });

	dragonDamaged.speed = 0.07f;

	collider = App->collisions->AddCollider({ 0, 0, 88, 90 }, Collider::Type::ENEMY, (Module*)App->enemies);

}

void Enemy_BlueDragon::Update()
{
	if (position.y > App->render->camera.y - 50) {
		path.Update();
	}
	
	position.y = +1;

	position = spawnPos + path.GetRelativePosition();

	iPoint d = App->player->position;
	iPoint o = { position.x + 33, position.y + 55 };
	float mag = d.DistanceTo(o);

	iPoint dir = d - o;
	fPoint dirN = { dir.x / mag, dir.y / mag };

	App->particles->fireBall.speed = { dirN.x * 2, dirN.y * 2 };

	if (tempTimer == 30)
	{
		Particle* fireBall1 = App->particles->AddParticle(App->particles->fireBall, position.x + 33, position.y + 55, Collider::Type::ENEMY_SHOT);
		if (fireBall1 != nullptr)
		{
			fireBall1->collider->AddListener((Module*)App->player);
		}
	}

	if (tempTimer == 35)
	{
		Particle* fireBall2 = App->particles->AddParticle(App->particles->fireBall, position.x + 58, position.y + 55, Collider::Type::ENEMY_SHOT);
		if (fireBall2 != nullptr)
		{
			fireBall2->collider->AddListener((Module*)App->player);
		}
	}
		

	if (tempTimer == 40)
	{
		Particle* fireBall3 = App->particles->AddParticle(App->particles->fireBall, position.x + 33, position.y + 65, Collider::Type::ENEMY_SHOT);
		if (fireBall3 != nullptr)
		{
			fireBall3->collider->AddListener((Module*)App->player);
		}
	}

	if (tempTimer == 45)
	{
		Particle* fireBall4 = App->particles->AddParticle(App->particles->fireBall, position.x + 58, position.y + 65, Collider::Type::ENEMY_SHOT);
		if (fireBall4 != nullptr)
		{
			fireBall4->collider->AddListener((Module*)App->player);
		}
		tempTimer = 0;
	}
	
	else tempTimer++;
	//App->audio->PlayFx(laserFx);


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_BlueDragon::Draw() {

	Enemy::Draw();
	if (currentAnim != &fly) currentAnim = &fly;
}

void Enemy_BlueDragon::OnCollision(Collider* collider) {

	if (collider->type != Collider::Type::SCREENBOUNDINGBOX && (App->player->spawnCountdown <= 0 || App->player->bombActivated))
	{
		if (lives <= 0) {
			App->particles->AddParticle(App->particles->bigExplosion, position.x, position.y, Collider::Type::PARTICLE);
			App->audio->PlayFx(destroyedFx);
			App->input->ShakeController(0, 100, 0.33f);

			if (collider->type == Collider::Type::PLAYER_SHOT || collider->type == Collider::Type::PLAYER)
			{
				killedByPlayer = true;
			}

			SetToDelete();
		}
		else if (lives > 0) {
			currentAnim = &dragonDamaged;
			lives--;
			App->audio->PlayFx(destroyedFx);
			App->input->ShakeController(0, 100, 0.33f);
		}
	}
}