#include "Enemy_Wizzard.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

Enemy_Wizzard::Enemy_Wizzard(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 219,0,50,45 });
	fly.PushBack({ 278,0,50,45 });
	fly.PushBack({ 334,0,50,45 });
	fly.speed = 0.02f;


	currentAnim = &fly;

	path.PushBack({ 0.03f, 2.0f }, 30);
	path.PushBack({ 0.03f, 0.0f }, 70);
	path.PushBack({ 4.0f, -4.0f }, 100);
	path.PushBack({ 10.0f, -10.0f }, 100);
	

	path.loop;

	collider = App->collisions->AddCollider({ 0, 0, 50, 40 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Wizzard::Update()
{
	if (position.y > App->render->camera.y - 24) {
		path.Update();
	}

	position = spawnPos + path.GetRelativePosition();





	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
