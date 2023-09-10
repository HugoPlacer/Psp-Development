#ifndef __Anim_Goblins_H__
#define __Anim_Goblins_H__

#include "Anim.h"
#include "Path.h"

class Anim_Goblins : public Anim
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Anim_Goblins(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	// This enemy has one sprite and one frame
	// We are keeping it an animation for consistency with other enemies
	Animation fly;
};

#endif // __Enemy_RedBall_H__
