#include "Anim.h"

#include "Application.h"

#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"


Anim::Anim(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Anim::~Anim()
{

}


void Anim::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

}

void Anim::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));

}

//
//void Anim::SetToDelete()
//{
//	pendingToDelete = true;
//	if (collider != nullptr)
//		collider->pendingToDelete = true;
//}