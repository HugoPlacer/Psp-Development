#include "Anim_Goblins.h"

#include "Application.h"

Anim_Goblins::Anim_Goblins(int x, int y) : Anim(x, y)
{
	fly.PushBack({ -877, -201, 431, 45 });
	fly.PushBack({ -877, -290, 431, 45 });
	fly.speed = 0.3f;
	//fly.loop;

	currentAnim = &fly;

	path.PushBack({ 0.9f, 0.5f }, 200);
	path.PushBack({ 0.0f, 0.0f }, 10);
	path.PushBack({ -0.9f, 0.5f }, 200);
	path.loop;

}

void Anim_Goblins::Update()
{
	path.Update();


	position = spawnPos + path.GetRelativePosition();

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Anim::Update();
}