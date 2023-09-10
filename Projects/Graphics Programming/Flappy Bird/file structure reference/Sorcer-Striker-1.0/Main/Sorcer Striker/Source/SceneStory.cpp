#include "SceneStory.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include <stdio.h>


#include "SDL/include/SDL.h"

SceneStory::SceneStory(bool startEnabled) : Module(startEnabled)
{
	goblins.PushBack({ 877, 201, 431, 85 });
	goblins.PushBack({ 877, 290, 431, 85 });
	goblins.speed = 0.1f;

	//letras1.PushBack({ 878, 12, 240, 98 });
	//letras1.PushBack({ 1147, 13, 240, 94 });
	//letras1.speed = 1.0f;
	//letras1.loop = false;

	letras2.PushBack({ 1172, 513, 240, 104 });
	//letras2.PushBack({ 1425, 515, 240, 104 });
	//letras2.PushBack({ 1424, 396, 240, 104 });
	//letras2.speed = 0.5f;
	//letras2.loop = false;

	cielo.PushBack({ 877, 387, 240, 102 });
	dragones.PushBack({ 36, 150, 242, 102 });
	dragon.PushBack({ 289, 41, 39,  28});

	black.PushBack({0, 0, 241, 117});

	path.PushBack({ 0.10f, 0.0f }, 200);
	path1.PushBack({ 0.05f, 0.0f }, 200);
	path2.PushBack({ 1.25f, 0.15f }, 200);
	path3.PushBack({ 1.25f, 0.25f }, 200);
}

SceneStory::~SceneStory()
{

}

// Load assets
bool SceneStory::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	texture = App->textures->Load("Assets/Intro/prueba.png");
	dragonstexture = App->textures->Load("Assets/Intro/dragons.png");
	
	App->render->camera.x = 0;
	App->render->camera.y = 0;


	timeout = SDL_GetTicks() + 1000;

	return ret;
}

update_status SceneStory::Update()
{
	if (App->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scenePlayerSelect, 90);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 8000)) {
		App->fade->FadeToBlack(this, (Module*)App->scenestory3, 90);
	}

	goblins.Update();
	//letras1.Update();
	letras2.Update();
	cielo.Update();
	dragones.Update();
	dragon.Update();
	
	black.Update();

	path.Update();
	path1.Update();
	path2.Update();
	path3.Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneStory::PostUpdate()
{
	App->render->Blit(texture, 0, 0, NULL);
	/*SDL_Rect rect = letras1.GetCurrentFrame();
	App->render->Blit(texture, 0, 115, &rect);*/

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 1000)) {
		SDL_Rect rect = goblins.GetCurrentFrame();
		App->render->Blit(texture, -path.GetRelativePosition().x, 16, &rect);
	}
	
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 4350)) {
		SDL_Rect rect = letras2.GetCurrentFrame();
		App->render->Blit(texture, 0, 115, &rect);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 5300)) {
		SDL_Rect rect = cielo.GetCurrentFrame();
		App->render->Blit(texture, 0, 218, &rect);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 5300)) {
		SDL_Rect rect = dragones.GetCurrentFrame();
		App->render->Blit(dragonstexture, 10 - path1.GetRelativePosition().x, 220, &rect);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 5300)) {
		SDL_Rect rect = dragon.GetCurrentFrame();
		App->render->Blit(dragonstexture, 800 - path2.GetRelativePosition().x, 310 - path2.GetRelativePosition().y, &rect);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 5300)) {
		SDL_Rect rect = dragon.GetCurrentFrame();
		App->render->Blit(dragonstexture, 650 - path2.GetRelativePosition().x, 330 - path2.GetRelativePosition().y, &rect);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 5300)) {
		SDL_Rect rect = dragon.GetCurrentFrame();
		App->render->Blit(dragonstexture, 550 - path3.GetRelativePosition().x, 370 - path3.GetRelativePosition().y, &rect);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 7500)) {
		SDL_Rect rect = black.GetCurrentFrame();
		App->render->Blit(texture, 0, 0, &rect);
		//goblins.fadein(56455);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 7700)) {
		SDL_Rect rect = black.GetCurrentFrame();
		App->render->Blit(texture, 0, 115, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 7900)) {
		SDL_Rect rect = black.GetCurrentFrame();
		App->render->Blit(texture, 0, 218, &rect);
	}
	return update_status::UPDATE_CONTINUE;
}

bool SceneStory::CleanUp()
{
	//App->textures->Unload(bgTexture);
	App->textures->Unload(texture);
	
	return true;
}