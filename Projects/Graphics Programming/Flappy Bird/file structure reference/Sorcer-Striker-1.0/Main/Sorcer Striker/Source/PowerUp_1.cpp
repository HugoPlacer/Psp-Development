#include "PowerUp_1.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"

PowerUp_1::PowerUp_1(int x, int y) : PowerUp(x, y)
{
	flyAnim.PushBack({ 0,0,17,22 });

	flyAnim.speed = 0.2f;

	currentAnim = &flyAnim;

	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::POWERUP, (Module*)App->powerups);
}

void PowerUp_1::Update()
{
	waveRatio += waveRatioSpeed;

	position.x = spawnPos.x + (waveHeight * sinf(waveRatio));
	position.y += 1;

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	PowerUp::Update();
}

void PowerUp_1::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER)
	{
		for (int i = 0; i < 2; i++)
		{
			if (App->player->PowerUpActivated[i])
			{
				App->player->PowerUpActivated[i] = false;
			}
		}

		App->player->PowerUpActivated[0] = true;
		PowerUp::OnCollision(collider);
	}
}
