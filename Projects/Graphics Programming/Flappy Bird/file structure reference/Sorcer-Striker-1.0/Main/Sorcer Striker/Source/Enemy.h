#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy(int x, int y);

	// Destructor
	virtual ~Enemy();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	virtual void OnCollision(Collider* collider);
	virtual void OnCollision(Collider* c1, Collider* c2);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

	virtual bool ContainsCollider(Collider* c1);

public:
	// The current position in the world
	iPoint position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;
	SDL_Texture* texture2 = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;
	int killedByPlayer = false;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	int lives = 0;

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __ENEMY_H_;_