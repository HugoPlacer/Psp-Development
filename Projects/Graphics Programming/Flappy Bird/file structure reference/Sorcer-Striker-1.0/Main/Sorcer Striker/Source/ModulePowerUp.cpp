#include "ModulePowerUp.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "PowerUp.h"
#include "PowerUp_1.h"
#include "PowerUp_2.h"

#define SPAWN_MARGIN 50


ModulePowerUp::ModulePowerUp(bool startEnabled) : Module(startEnabled)
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
		powerups[i] = nullptr;
}

ModulePowerUp::~ModulePowerUp()
{

}

bool ModulePowerUp::Start()
{
	texture = App->textures->Load("Assets/Sprites/powerups.png");
	PowerUpDestroyedFx = App->audio->LoadFx("Assets/Fx/explosion.wav");
	
	return true;
}


update_status ModulePowerUp::PreUpdate()
{
	// Remove all powerups scheduled for deletion
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr && powerups[i]->pendingToDelete)
		{
			delete powerups[i];
			powerups[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePowerUp::Update()
{
	HandlePowerUpSpawn();

	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
			powerups[i]->Update();
	}

	HandlePowerUpDespawn();

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePowerUp::PostUpdate()
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
			powerups[i]->Draw();
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePowerUp::CleanUp()
{
	LOG("Freeing all powerups");

	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			delete powerups[i];
			powerups[i] = nullptr;
		}
	}

	return true;
}

bool ModulePowerUp::AddPowerUp(POWERUP_TYPE type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (spawnQueue[i].type == POWERUP_TYPE::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModulePowerUp::HandlePowerUpSpawn()
{
	// Iterate all the powerups queue
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (spawnQueue[i].type != POWERUP_TYPE::NO_TYPE)
		{
			// Spawn a new powerup if the screen has reached a spawn position
			if (spawnQueue[i].y * SCREEN_SIZE > (App->render->camera.y * SCREEN_SIZE) - SPAWN_MARGIN)
			{
				LOG("Spawning powerup at %d", spawnQueue[i].y * SCREEN_SIZE);

				SpawnPowerUp(spawnQueue[i]);
				spawnQueue[i].type = POWERUP_TYPE::NO_TYPE; // Removing the newly spawned powerup from the queue
			}
		}
	}
}

void ModulePowerUp::HandlePowerUpDespawn()
{
	// Iterate existing powerups
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			// Delete the powerup when it has reached the end of the screen
			if (powerups[i]->position.y * SCREEN_SIZE > (App->render->camera.y * SCREEN_SIZE) + (App->render->camera.h * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("DeSpawning powerup at %d", powerups[i]->position.y * SCREEN_SIZE);

				powerups[i]->SetToDelete();
			}
		}
	}
}

void ModulePowerUp::SpawnPowerUp(const PowerUpSpawnpoint& info)
{
	// Find an empty slot in the powerups array
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] == nullptr)
		{
			switch (info.type)
			{
			case POWERUP_TYPE::POWERUP_1:
				powerups[i] = new PowerUp_1(info.x, info.y);
				break;

			case POWERUP_TYPE::POWERUP_2:
				powerups[i] = new PowerUp_2(info.x, info.y);
				break;
			}
			powerups[i]->texture = texture;
			powerups[i]->destroyedFx = PowerUpDestroyedFx;
			break;
		}
	}
}

void ModulePowerUp::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr && powerups[i]->GetCollider() == c1)
		{
			powerups[i]->OnCollision(c2); //Notify the powerup of a collision
			break;
		}
	}
}