#ifndef __ENEMY_BOSS_H__
#define __ENEMY_BOSS_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Boss : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Boss(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;
	void Draw() override;
	void OnCollision(Collider* collider) override;
	void OnCollision(Collider* c1, Collider* c2) override;

	bool ContainsCollider(Collider* c1) override;

private:

	enum State
	{
		NONE = -1,
		IDLE,
		THROWINGFIRE,

		MAX
	}boss_state;

	bool destroyed = false;

	// A set of steps that define the position in the screen
	// And an animation for each step
	Path idle;
	Path throwingfire;
	
	Path* currentPath = nullptr;

	int stateChangerTimer = 0;
	int STATEDURATION = 240;

	SDL_Rect fullBody;
	SDL_Rect leftBodyPart;
	SDL_Rect rightBodyPart;
	SDL_Rect middleBodyPart;

	SDL_Rect* currentBody;


	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation head;
	Animation headDamaged;

	Animation* currentHead[3] = { nullptr };

	Animation propeller;

	Collider* head1 = nullptr;
	Collider* head2 = nullptr;
	Collider* head3 = nullptr;

	uint head1Health;
	uint head2Health;
	uint head3Health;

	int redBatSpawnTimer = 0;
};

#endif // __ENEMY_BOSS_H__
