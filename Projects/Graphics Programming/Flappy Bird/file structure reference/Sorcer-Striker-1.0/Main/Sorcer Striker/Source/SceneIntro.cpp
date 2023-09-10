#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{
	letras.PushBack({ 0,0,0,0 });
	letras.PushBack({ 256,14,146,8 });
	letras.speed = 0.1f;

	ships.PushBack({ 0,0,0,0 });
	ships.PushBack({ 304,49,156,44 });
	ships.speed = 0.3f;

	piedras.PushBack({ 0, 0, 0, 0 });
	piedras.PushBack({ 0, 344, 240, 340 });
	piedras.PushBack({ 252, 142, 240, 340});
	piedras.PushBack({ 502, 34, 240, 340});
	piedras.speed = 0.1f;
}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Intro/initial1.png");
	App->audio->Enable();
	App->audio->PlayMusic("Assets/Music/Intro.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	letras.Reset();
	ships.Reset();
	piedras.Reset();

	return ret;
}

update_status SceneIntro::Update()
{
	GamePad& pad = App->input->pads[0];

	if (App->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a == true)
	{
		App->fade->FadeToBlack(this, (Module*)App->scenePlayerSelect, 90);
	}

	letras.Update();
	ships.Update();
	piedras.Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	SDL_Rect rect = letras.GetCurrentFrame();
	App->render->Blit(bgTexture, 49, 190, &rect);

	SDL_Rect rect1 = ships.GetCurrentFrame();
	App->render->Blit(bgTexture, 52, 204, &rect1);

	SDL_Rect rect2 = piedras.GetCurrentFrame();
	App->render->Blit(bgTexture, 0, 0, &rect2);

	return update_status::UPDATE_CONTINUE;
}