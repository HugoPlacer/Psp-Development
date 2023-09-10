#include "SceneDescription.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

SceneDescription::SceneDescription(bool startEnabled) : Module(startEnabled)
{

}

SceneDescription::~SceneDescription()
{

}

// Load assets
bool SceneDescription::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	textura = App->textures->Load("Assets/Intro/DescriptionScene.png");
	App->audio->PlayMusic("Assets/Music/Intaro.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	return ret;
}

update_status SceneDescription::Update()
{
	//680 porque serian dos paginas de 240x340, cuando acaba de pasar esa pagina se va solo a la intro
	//App->fade->FadeToBlack(this, (Module*)App->scenestory4, 90);

	if (App->render->camera.y < 340) {
		App->render->camera.y += 1;
	}
	if (App->render->camera.y >= 340) {
		App->fade->FadeToBlack(this, (Module*)App->intro1, 90);	
	}
	if (App->input->keys[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scenefinal, 0);
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN) 
	{
		App->fade->FadeToBlack(this, (Module*)App->intro1, 90);
	}
	//pa ir directo al gameplay xd
	if (App->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 0);
	}

	if (App->input->keys[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN) 
	{
		App->fade->FadeToBlack(this, (Module*)App->scenePlayerSelect, 0);
	}
	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneDescription::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(textura, 0, 0, NULL);

	return update_status::UPDATE_CONTINUE;
}