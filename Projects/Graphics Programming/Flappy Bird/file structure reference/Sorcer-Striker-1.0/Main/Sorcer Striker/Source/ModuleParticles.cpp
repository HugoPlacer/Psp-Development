#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Sprites/particles.png");

	// Explosion particle
	explosion.anim.PushBack({ 0, 18, 33, 30 });
	explosion.anim.PushBack({ 39, 18, 33, 30 });
	explosion.anim.PushBack({ 65, 18, 33, 30 });
	explosion.anim.PushBack({ 100, 18, 33, 30 });
	explosion.anim.PushBack({ 137, 18, 33, 30 });
	explosion.anim.PushBack({ 175, 18, 33, 30 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.7f;

	bigExplosion.anim.PushBack({ 5, 186, 83, 85 });
	bigExplosion.anim.PushBack({ 90, 172, 101, 93 });
	bigExplosion.anim.PushBack({ 196, 156, 123, 111 });
	bigExplosion.anim.PushBack({ 90, 172, 101, 93 });
	bigExplosion.anim.PushBack({ 5, 186, 83, 85 });
	bigExplosion.anim.loop = false;
	bigExplosion.anim.speed = 1.0f;
	//bigExplosion.lifetime = 500;

	bossFire.anim.PushBack({ 77, 67, 30, 41 });
	bossFire.anim.PushBack({ 107, 67, 39, 41 });
	bossFire.anim.PushBack({ 146, 67, 39, 41 });
	bossFire.anim.PushBack({ 190, 67, 39, 41 });
	bossFire.anim.PushBack({ 237, 67, 41, 41 });
	bossFire.anim.PushBack({ 287, 67, 41, 41 });
	bossFire.anim.loop = false;
	bossFire.anim.speed = 0.16f;
	bossFire.speed.y = 2;

	// TODO 2:	Create the template for a new particle "laser"
	//			Remember: not all the code goes here!
	//			Follow the example with the "explosion" particle
	laser.lifetime = 180;
	laser.anim.PushBack({ 0, 0, 9, 20});
	laser.anim.loop = true;
	laser.anim.speed = 0.3f;
	laser.speed.y = -6;
	
	laserR.lifetime = 180;
	laserR.anim.PushBack({ 0, 0, 16, 33 });
	laserR.anim.loop = true;
	laserR.anim.speed = 0.3f;
	laserR.speed.y = -6;
	laserR.speed.x = 1;

	laserL.lifetime = 180;
	laserL.anim.PushBack({ 0, 0, 16, 33 });
	laserL.anim.loop = true;
	laserL.anim.speed = 0.3f;
	laserL.speed.y = -6;
	laserL.speed.x = -1;

	bat_shotsR.lifetime = 180;
	bat_shotsR.anim.PushBack({ 10, 0, 24, 16 });
	bat_shotsR.anim.loop = true;
	bat_shotsR.anim.speed = 0.3f;
	bat_shotsR.speed.y = -6;
	bat_shotsR.speed.x = 0;

	bat_shotsL.lifetime = 180;
	bat_shotsL.anim.PushBack({ 10, 0, 24, 16 });
	bat_shotsL.anim.loop = true;
	bat_shotsL.anim.speed = 0.3f;
	bat_shotsL.speed.y = -6;
	bat_shotsL.speed.x = 0;

	fireBall.lifetime = 180;
	fireBall.anim.PushBack({ 34, 1, 9, 9 });
	fireBall.speed.y = 6;

	redShot.lifetime = 180;
	redShot.anim.PushBack({ 47, 0, 6, 17 });
	redShot.anim.loop = true;
	redShot.anim.speed = 0.3f;
	redShot.speed.y = -6;
	
	return true;
}

update_status ModuleParticles::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return update_status::UPDATE_CONTINUE;
}
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			//spawn a explosion particle if the collider is not the screenboundingbox
			if (c2->type != Collider::Type::SCREENBOUNDINGBOX)
			{
				AddParticle(explosion, particles[i]->position.x, particles[i]->position.y, Collider::Type::PARTICLE);
			}

			delete particles[i];
			particles[i] = nullptr;
			break;
		}
	}
	//for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	//{
	//	// Always destroy particles that collide
	//	if (particles[i] != nullptr && particles[i]->collider == c1 && particles[i]->collider->type != Collider::Type::SCREENBOUNDINGBOX)
	//	{
	//		AddParticle(explosion, particles[i]->position.x, particles[i]->position.y);

	//		//delete particles[i];
	//		//particles[i] = nullptr;

 //			particles[i]->pendingToDelete = true;
	//		particles[i]->collider->pendingToDelete = true;
	//		break;
	//	}
	//}
}

update_status ModuleParticles::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
		else if (particle->position.y < App->render->camera.y)
		{
			particles[i]->SetToDelete();
		}
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleParticles::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return update_status::UPDATE_CONTINUE;
}

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;

			//Adding the particle's collider
			//if (colliderType != Collider::Type::NONE)
				newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);

			if (newParticle->collider == nullptr)
			{
				delete newParticle;
				return nullptr;
			}

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}