#include "Enemy_Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"

#include "SDL/include/SDL.h"

Enemy_Boss::Enemy_Boss(int x, int y) : Enemy(x, y)
{
	destroyed = false;
	currentHead[0] = nullptr;
	currentHead[1] = nullptr;
	currentHead[2] = nullptr;
	redBatSpawnTimer = 0;


	head.PushBack({ 691,164,44,58 });
	head.PushBack({ 583,164,44,58 });
	head.PushBack({ 476,164,44,58 });
	head.speed = 0.09f;

	for (int i = 0; i < 3; i++)
	{
		currentHead[i] = &head;
	}

	headDamaged.PushBack({ 645,164,44,58 });
	headDamaged.PushBack({ 539,164,44,58 });
	headDamaged.PushBack({ 433,164,44,58 });
	headDamaged.speed = 0.09f;

	propeller.PushBack({ 490,233,37,29 });
	propeller.PushBack({ 453,233,37,29 });
	propeller.speed = 0.09f;

	fullBody = { 24,344,287,126 };
	leftBodyPart = { 24, 485, 287, 126 };
	rightBodyPart = { 430, 465, 287, 126 };
	middleBodyPart = { 430, 339, 287, 126 };

	currentBody = &fullBody;

	idle.PushBack({ -1.0f, 0.0f }, 30);
	idle.PushBack({ 1.0f, -2.0f }, 30);

	boss_state = IDLE;
	currentPath = &idle;

	throwingfire.PushBack({ 0.0f, -1.0f }, 45);
	throwingfire.PushBack({ 0.0f, -2.1f }, 45);
	throwingfire.PushBack({ 0.2f, 0.0f }, 45); //cal acabar de tocar aixo perque ara s'enva una mica cap a la dreta amb el temps

	collider = App->collisions->AddCollider({ 0, 0, 281,124 }, Collider::Type::ENEMY, (Module*)App->enemies);

	head1 = App->collisions->AddCollider({ 60, 84, 39,54 }, Collider::Type::ENEMY, (Module*)App->enemies);
	head2 = App->collisions->AddCollider({ 127, 84, 39,54 }, Collider::Type::ENEMY, (Module*)App->enemies);
	head3 = App->collisions->AddCollider({ 198, 84, 39,54 }, Collider::Type::ENEMY, (Module*)App->enemies);

	head1Health = 100;
	head2Health = 200;
	head3Health = 100;

}

void Enemy_Boss::Update()
{

	if (!destroyed)
	{
		if (redBatSpawnTimer >= 30)
		{
			App->enemies->AddEnemy(ENEMY_TYPE::REDBAT, position.x + 120 + sin(SDL_GetTicks()) * 80, position.y);
			redBatSpawnTimer = 0;
		}
		else
		{
			redBatSpawnTimer++;
		}
	}
	else
	{
		App->player->win = true;
	}

	head.Update();
	headDamaged.Update();
	propeller.Update();


	head1->SetPos(position.x + 50, position.y + 75);
	head2->SetPos(position.x + 121, position.y + 75);
	head3->SetPos(position.x + 193, position.y + 75);


	switch (boss_state)
	{
	case NONE:
		break;
	case IDLE:
		idle.Update();
		stateChangerTimer++;
		break;
	case THROWINGFIRE:
		throwingfire.Update();
		stateChangerTimer++;

		if (!(stateChangerTimer % 5) && stateChangerTimer > 45 && stateChangerTimer < 90) //spawn dragon fire
		{
			if (currentHead[0] != nullptr) App->particles->AddParticle(App->particles->bossFire, position.x + 50, position.y + 100, Collider::Type::ENEMY_SHOT);
			if (currentHead[1] != nullptr) App->particles->AddParticle(App->particles->bossFire, position.x + 121, position.y + 100, Collider::Type::ENEMY_SHOT);
			if (currentHead[2] != nullptr) App->particles->AddParticle(App->particles->bossFire, position.x + 193, position.y + 100, Collider::Type::ENEMY_SHOT);
		}
		break;
	case MAX:
		break;
	default:
		break;
	}

	if (stateChangerTimer >= STATEDURATION)
	{
		if (boss_state == IDLE)
		{
			boss_state = THROWINGFIRE;
			currentPath = &throwingfire;
			throwingfire.Reset();
			throwingfire.ResetRelativePosition();
			stateChangerTimer = 0;
			spawnPos = position;
			STATEDURATION = 135;
		}
		else if (boss_state == THROWINGFIRE)
		{
			boss_state = IDLE;
			currentPath = &idle;
			idle.Reset();
			idle.ResetRelativePosition();
			stateChangerTimer = 0;
			spawnPos = position;
			STATEDURATION = 240;
		}
	}

	//position.y = (App->render->camera.y + 49) + (cos((SDL_GetTicks() / 3)) * 5);

	//position.x = spawnPos.x + sin(SDL_GetTicks() / 3) * 5;

	position = { spawnPos.x + currentPath->GetRelativePosition().x, spawnPos.y + currentPath->GetRelativePosition().y };

	//LOG("(%d,%d)", position.x, position.y);

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}

void Enemy_Boss::Draw()
{
	if (currentBody != nullptr)
	{
		App->render->Blit(texture, position.x, position.y, currentBody);
	}

	if(currentHead[0] != nullptr) App->render->Blit(texture, position.x + 50, position.y + 75, &(currentHead[0]->GetCurrentFrame()));
	if(currentHead[1] != nullptr) App->render->Blit(texture, position.x + 121, position.y + 75, &(currentHead[1]->GetCurrentFrame()));
	if(currentHead[2] != nullptr) App->render->Blit(texture, position.x + 193, position.y + 75, &(currentHead[2]->GetCurrentFrame()));

	for (int i = 0; i < 3; i++)
	{
		if (currentHead[i] == &headDamaged) currentHead[i] = &head;
	}

	if (currentHead[0] != nullptr) App->render->Blit(texture, position.x + 17, position.y + 83, &(propeller.GetCurrentFrame()));
	if (currentHead[1] != nullptr) App->render->Blit(texture, position.x + 90, position.y + 82, &(propeller.GetCurrentFrame()));
	if (currentHead[1] != nullptr) App->render->Blit(texture, position.x + 156, position.y + 83, &(propeller.GetCurrentFrame()));
	if (currentHead[2] != nullptr)	App->render->Blit(texture, position.x + 240, position.y + 84, &(propeller.GetCurrentFrame()));


}

void Enemy_Boss::OnCollision(Collider* collider) {}

void Enemy_Boss::OnCollision(Collider* c1, Collider* c2) {


	if (c1 == head1 && c2->type == Collider::Type::PLAYER_SHOT)
	{
		LOG("head1 HIT!");
		LOG("%d", head1Health);
		App->input->ShakeController(0, 100, 0.33f);
		if (head1Health > 0)
		{
			//if(SDL_GetTicks() % 13 == 0) head1Health -= 10;
			head1Health -= 10;
			currentHead[0] = &headDamaged;
		}
		else
		{
			currentHead[0] = nullptr;
			head1->pendingToDelete = true;
			App->particles->AddParticle(App->particles->bigExplosion, position.x + 40, position.y - 40, Collider::Type::PARTICLE);
			App->particles->AddParticle(App->particles->bigExplosion, position.x + 10, position.y - 10, Collider::Type::PARTICLE);
			if (currentBody == &fullBody)
			{
				currentBody = &leftBodyPart;
			}
			else
			{
				currentBody = &middleBodyPart;
			}
		}
	}
	if (c1 == head2 && c2->type == Collider::Type::PLAYER_SHOT)
	{
		LOG("head2 HIT!");
		LOG("%d", head2Health);
		App->input->ShakeController(0, 100, 0.33f);
		if (head2Health > 0)
		{
			//if (SDL_GetTicks() % 13 == 0) head2Health -= 10;
			head2Health -= 10;
			currentHead[1] = &headDamaged;
		}
		else
		{
			currentHead[0] = nullptr;
			head1->pendingToDelete = true;

			currentHead[1] = nullptr;
			head3->pendingToDelete = true;

			currentHead[2] = nullptr;
			head2->pendingToDelete = true;

			head1Health = 0;
			head3Health = 0;

			destroyed = true;
			App->input->ShakeController(0, 2000, 0.2f);

			App->particles->AddParticle(App->particles->bigExplosion, position.x + 70, position.y + 40, Collider::Type::PARTICLE);
			App->particles->AddParticle(App->particles->bigExplosion, position.x + 100, position.y + 50, Collider::Type::PARTICLE);
			App->particles->AddParticle(App->particles->bigExplosion, position.x + 130, position.y + 60, Collider::Type::PARTICLE);
			App->audio->PlayFx(destroyedFx);

			currentBody = nullptr;
		}
	}
	if (c1 == head3 && c2->type == Collider::Type::PLAYER_SHOT)
	{
		LOG("head3 HIT!");
		LOG("%d", head3Health);
		App->input->ShakeController(0, 100, 0.4f);
		if (head3Health > 0)
		{
			//if (SDL_GetTicks() % 13 == 0) head3Health -= 10;
			head3Health -= 10;
			currentHead[2] = &headDamaged;
		}
		else
		{
			currentHead[2] = nullptr;
			head3->pendingToDelete = true;

			App->particles->AddParticle(App->particles->bigExplosion, position.x + 198, position.y + 84, Collider::Type::PARTICLE);
			App->particles->AddParticle(App->particles->bigExplosion, position.x + 178, position.y + 74, Collider::Type::PARTICLE);

			App->audio->PlayFx(destroyedFx);

			if (currentBody == &fullBody)
			{
				currentBody = &rightBodyPart;
			}
			else
			{
				currentBody = &middleBodyPart;
			}
		}
	}


	/*if (collider->type != Collider::Type::SCREENBOUNDINGBOX && lives <= 0) {
		App->particles->AddParticle(App->particles->explosion, position.x, position.y);
		App->audio->PlayFx(destroyedFx);

		SetToDelete();
	}
	else if (collider->type != Collider::Type::SCREENBOUNDINGBOX && lives > 0) {
		App->particles->AddParticle(App->particles->explosion, position.x + 44, position.y + 90);
		App->audio->PlayFx(destroyedFx);
		lives--;
	}*/
}

bool Enemy_Boss::ContainsCollider(Collider* c1)
{
	bool ret = false;
	ret = Enemy::ContainsCollider(c1);

	if (head1 == c1)
	{
		c1 = head1;
		ret = true;
	}
	else if (head2 == c1)
	{
		c1 = head2;
		ret = true;
	}
	else if (head3 == c1)
	{
		c1 = head3;
		ret = true;
	}
	return ret;
}
