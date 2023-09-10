#include "SceneFinal.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL.h"

SceneFinal::SceneFinal(bool startEnabled) : Module(startEnabled)
{
	cuadrado.PushBack({ 251,59,14,14 });
	cuadrado.PushBack({ 272,59,14,14 });
	cuadrado.PushBack({ 293,59,14,14 });
	cuadrado.PushBack({ 313,59,14,14 });
	cuadrado.PushBack({ 333,59,14,14 });
	cuadrado.speed = 1.0f;
	cuadrado.loop;

	letras.PushBack({264,114,7,7});
	letras.PushBack({274,84,7,7});
	letras.PushBack({274,104,7,7});
	letras.PushBack({244,84,7,7});
	letras.PushBack({274,124,7,7});
	letras.PushBack({244,104,7,7});
	letras.speed = 0.5f;
	letras.loop = true;

	n.PushBack({ 244,95,7,6 });
	u.PushBack({275,105,6,6});
	b.PushBack({ 254,84,7,7 });
}

SceneFinal::~SceneFinal()
{

}

// Load assets
bool SceneFinal::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	textura = App->textures->Load("Assets/Sprites/Final.png");
	App->audio->PlayMusic("Assets/Music/Final.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	timeout = SDL_GetTicks() + 1000;

	cuadrado.Reset();
	letras.Reset();
	n.Reset();
	u.Reset();
	b.Reset();
	return ret;
}

update_status SceneFinal::Update()
{
	if (App->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 15000)) {
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	cuadrado.Update();
	letras.Update();
	n.Update();
	u.Update();
	b.Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneFinal::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(textura, 0, 0, NULL);

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout - 1000) != SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000)) {
		SDL_Rect rect = cuadrado.GetCurrentFrame();
		App->render->Blit(textura, 4, 32, &rect);
		SDL_Rect rect1 = letras.GetCurrentFrame();
		App->render->Blit(textura, 7, 35, &rect1);
	}
	else if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000) != SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 7000)) {
		SDL_Rect rect = cuadrado.GetCurrentFrame();
		App->render->Blit(textura, 20, 32, &rect);
		SDL_Rect rect1 = letras.GetCurrentFrame();
		App->render->Blit(textura, 23, 35, &rect1);
	}
	else if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 7000) != SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 9000)) {
		SDL_Rect rect = cuadrado.GetCurrentFrame();
		App->render->Blit(textura, 36, 32, &rect);
		SDL_Rect rect1 = letras.GetCurrentFrame();
		App->render->Blit(textura, 39, 35, &rect1);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 3000)) {
		SDL_Rect rect = n.GetCurrentFrame();
		App->render->Blit(textura, 7, 35, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 7000)) {
		SDL_Rect rect = u.GetCurrentFrame();
		App->render->Blit(textura, 23, 35, &rect);
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 9000)) {
		SDL_Rect rect = b.GetCurrentFrame();
		App->render->Blit(textura, 39, 35, &rect);
	}

	return update_status::UPDATE_CONTINUE;
}

bool SceneFinal::CleanUp()
{
	App->textures->Unload(textura);

	return true;
}