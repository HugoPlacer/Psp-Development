#ifndef __ENEMY_BLUEDRAGON_H__
#define __ENEMY_BLUEDRAGON_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_BlueDragon : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_BlueDragon(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;
	void Draw() override;
	void OnCollision(Collider* collider) override;

	int lives = 20;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	int tempTimer = 0; //solo para probar

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation fly;
	Animation dragonDamaged;

};

#endif // __ENEMY_BLUEDRAGON_H__
