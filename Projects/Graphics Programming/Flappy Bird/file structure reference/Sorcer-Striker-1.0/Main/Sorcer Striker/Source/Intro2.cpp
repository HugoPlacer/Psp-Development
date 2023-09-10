#include "Intro2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

Intro2::Intro2(bool startEnabled) : Module(startEnabled)
{

}

Intro2::~Intro2()
{

}

// Load assets
bool Intro2::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	textura = App->textures->Load("Assets/Intro/Intro1.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status Intro2::Update()
{
	if (App->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}
	else{App->fade->FadeToBlack(this, (Module*)App->scenestory, 90);}
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status Intro2::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(textura, -246, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}