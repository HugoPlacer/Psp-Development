#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	void OnCollision(Collider* c1, Collider* c2) override;
	void PowerUp_1();
	void PowerUp_2();
	void bomb();

public:

	int lives = 3;
	
	bool godMode = false;

	// Position of the player in the map
	iPoint position;
	iPoint backupPosition;

	// The speed in which we move the player (pixels per frame)
	int speed = 3;

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	SDL_Texture* bombTexture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	const uint SPAWNDELAY = 180;
	uint spawnCountdown = SPAWNDELAY;

	bool burst = false;
	uint burstCountdown = 5;
	uint burstCounter = 2;
	uint shootCooldown = 0;

	bool PowerUpActivated[2] = { false };

	int transitionTimer = 240;

	uint bombActivatedTimer = 0;
	uint bombStartedTimer = 0;
	bool bombActivated = false;
	bool bombStarted = false;
	Collider* bombCollider = nullptr;
	iPoint bombPosition;
	int bombAmount = 3;
	int bombFx = 0;

	// A set of animations
	Animation idleAnim;
	Animation leftAnim;
	Animation rightAnim;
	Animation powerUp1;
	Animation shipleft;
	Animation shipright;

	Animation bombState[2];


	Collider* collider = nullptr;

	bool destroyed = false;
	uint destroyedCountdown = 120;

	uint laserFx = 0;
	uint explosionFx = 0;

	uint kills = 0;
	bool win = false;

	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };
};

#endif //!__MODULE_PLAYER_H__