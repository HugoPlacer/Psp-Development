#include "Enemy.h"

#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleInput.h"


Enemy::Enemy(int x, int y) : position(x, y)
{
	spawnPos = position;
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
		
} 

void Enemy::OnCollision(Collider* collider)
{	
	if (collider->type != Collider::Type::SCREENBOUNDINGBOX && (App->player->spawnCountdown <= 0 || App->player->bombActivated)) {
		App->particles->AddParticle(App->particles->explosion, position.x, position.y, Collider::Type::PARTICLE);
		App->audio->PlayFx(destroyedFx);

		if (collider->type == Collider::Type::PLAYER_SHOT || collider->type == Collider::Type::PLAYER)
		{
			killedByPlayer = true;
			App->input->ShakeController(0, 100, 0.33f);
		}
		SetToDelete();
	}
}

void  Enemy::OnCollision(Collider* c1, Collider* c2) {}


void Enemy::SetToDelete()
{
	if (killedByPlayer == true)
	{
		App->player->score += 23;
		App->player->kills++;
		killedByPlayer = false;
	}
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

bool Enemy::ContainsCollider(Collider* c1)
{
	return collider == c1;
}

