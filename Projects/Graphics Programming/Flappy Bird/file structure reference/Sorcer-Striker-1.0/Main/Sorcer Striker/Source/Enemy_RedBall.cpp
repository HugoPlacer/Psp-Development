#include "Enemy_RedBall.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleRender.h"

Enemy_RedBall::Enemy_RedBall(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 0,0,26,38 });
	fly.PushBack({ 36,0,26,38 });
	fly.speed = 0.3f;
	

	currentAnim = &fly;

	path.PushBack({3.3f, 0.2f}, 65);
	path.PushBack({ 0.3f, 1.3f }, 20);
	path.PushBack({-3.3f, 0.2f}, 65);
	path.PushBack({ -0.3f, 1.3f }, 20);
	path.loop;

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_RedBall::Update()
{
	if (position.y > App->render->camera.y - 24) {
		path.Update();
	}
	
	position = spawnPos + path.GetRelativePosition();
	
	
	
	

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
