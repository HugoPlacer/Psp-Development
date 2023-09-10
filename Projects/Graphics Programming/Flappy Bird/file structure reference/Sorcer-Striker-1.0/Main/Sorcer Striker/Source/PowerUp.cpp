#include "PowerUp.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"

PowerUp::PowerUp(int x, int y) : position(x, y)
{
	spawnPos = position;
	PowerUpCollectFx = App->audio->LoadFx("Assets/Fx/powerUp.wav");
}

PowerUp::~PowerUp()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* PowerUp::GetCollider() const
{
	return collider;
}

void PowerUp::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void PowerUp::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void PowerUp::OnCollision(Collider* collider)
{
	if (collider->type == Collider::Type::PLAYER) {
		SetToDelete();
		App->audio->PlayFx(PowerUpCollectFx);
		App->input->ShakeController(0, 50, 0.2f);
	}
}

void PowerUp::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}