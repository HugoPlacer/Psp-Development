#ifndef __MODULE_POWER_UP_H__
#define __MODULE_POWER_UP_H__

#include "Module.h"

#define MAX_POWERUPS 50


enum class POWERUP_TYPE
{
	NO_TYPE,
	POWERUP_1,
	POWERUP_2,
};

struct PowerUpSpawnpoint
{
	POWERUP_TYPE type = POWERUP_TYPE::NO_TYPE;
	int x, y;
};

class PowerUp;
struct SDL_Texture;

class ModulePowerUp : public Module
{
public:
	// Constructor
	ModulePowerUp(bool startEnabled);

	// Destructor
	~ModulePowerUp();

	// Called when the module is activated
	// Loads the necessary textures for the enemies
	bool Start() override;

	// Called at the beginning of the application loop
	// Removes all enemies pending to delete
	update_status PreUpdate() override;

	// Called at the middle of the application loop
	// Handles all enemies logic and spawning/despawning
	update_status Update() override;

	// Called at the end of the application loop
	// Iterates all the enemies and draws them
	update_status PostUpdate() override;

	// Called on application exit
	// Destroys all active enemies left in the array
	bool CleanUp() override;

	// Called when an enemi collider hits another collider
	// The PowerUp is destroyed and an explosion particle is fired
	void OnCollision(Collider* c1, Collider* c2) override;

	// Add an PowerUp into the queue to be spawned later
	bool AddPowerUp(POWERUP_TYPE type, int x, int y);

	// Iterates the queue and checks for camera position
	void HandlePowerUpSpawn();

	// Destroys any enemies that have moved outside the camera limits
	void HandlePowerUpDespawn();

private:
	// Spawns a new PowerUp using the data from the queue
	void SpawnPowerUp(const PowerUpSpawnpoint& info);

private:
	// A queue with all spawn points information
	PowerUpSpawnpoint spawnQueue[MAX_POWERUPS];

	// All spawned enemies in the scene
	PowerUp* powerups[MAX_POWERUPS] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;

	// The audio fx for destroying an PowerUp
	int PowerUpDestroyedFx = 0;
};

#endif // __MODULE_POWER_UP_H__