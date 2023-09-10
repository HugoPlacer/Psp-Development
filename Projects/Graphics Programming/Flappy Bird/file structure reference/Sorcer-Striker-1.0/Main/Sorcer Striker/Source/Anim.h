#ifndef __ANIM_H__
#define __ANIM_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;

class Anim
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Anim(int x, int y);

	// Destructor
	virtual ~Anim();


	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();


	// Sets flag for deletion and for the collider aswell
	//virtual void SetToDelete();

public:
	// The current position in the world
	iPoint position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;
	SDL_Texture* texture2 = nullptr;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;


protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __ENEMY_H__