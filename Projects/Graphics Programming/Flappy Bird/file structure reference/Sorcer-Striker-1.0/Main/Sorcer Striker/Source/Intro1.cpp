#include "Intro1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

Intro1::Intro1(bool startEnabled) : Module(startEnabled)
{

}

Intro1::~Intro1()
{

}

// Load assets
bool Intro1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	textura = App->textures->Load("Assets/Intro/Intro1.png");
	//NO HA DE SONAR MUSICA EN AQUESTA PANTALLA
	App->audio->PlayMusic("Assets/Music/Intro.ogg", 1.0f);
	//App->audio->Disable();

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status Intro1::Update()
{
	if (App->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}
	else{ App->fade->FadeToBlack(this, (Module*)App->intro2, 20); }
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status Intro1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(textura, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}