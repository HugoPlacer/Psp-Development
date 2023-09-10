#include "Enemy_RedBat.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

#include "SDL/include/SDL.h"

Enemy_RedBat::Enemy_RedBat(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 401,2,34,40 });
	fly.PushBack({ 401,2,34,40 });
	fly.PushBack({ 401,2,34,40 });
	fly.PushBack({ 401,2,34,40 });
	fly.PushBack({ 401,2,34,40 });
	fly.PushBack({ 401,2,34,40 });
	fly.PushBack({ 401,2,34,40 });
	fly.PushBack({ 570,2,34,40 });
	fly.PushBack({ 529,2,34,40 });
	fly.PushBack({ 481,2,34,40 });
	fly.PushBack({ 438,2,42,40 });
	
	
	
	fly.speed = 0.5f;
	fly.loop = false;


	currentAnim = &fly;

	path.PushBack({ 0.0f, -2.0f }, 20);
	path.PushBack({ 0.0f, 2.0f }, 200);
	path.loop = false;

	collider = App->collisions->AddCollider({ 0, 0, 34, 40 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedBat::Update()
{
	if (position.y > App->render->camera.y - 24) {
		path.Update();
	}

	position = spawnPos + path.GetRelativePosition();


	iPoint d = App->player->position;
	iPoint o = { position.x, position.y };
	float mag = d.DistanceTo(o);

	iPoint dir = d - o;
	fPoint dirN = { dir.x / mag, dir.y / mag };

	App->particles->fireBall.speed = { dirN.x * 2, dirN.y * 2 };

	if ((SDL_GetTicks() + position.y + position.x) % 1355 == 0)
	{
		Particle* fireBall = App->particles->AddParticle(App->particles->fireBall, position.x, position.y, Collider::Type::ENEMY_SHOT);
		if (fireBall != nullptr)
		{
			fireBall->collider->AddListener((Module*)App->player);
		}
	}


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
