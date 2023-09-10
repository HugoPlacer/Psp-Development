#include "SceneStory4.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleUI.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include <stdio.h>

#include "SDL/include/SDL.h"

SceneStory4::SceneStory4(bool startEnabled) : Module(startEnabled)
{
	//1172 638 719 1252
	character1.PushBack({ 1172, 639, 80, 80 });
	character2.PushBack({ 1255, 639, 80, 80 });
	character3.PushBack({ 1338, 639, 80, 80 });
	character4.PushBack({ 1421, 639, 80, 80 });

	path1.PushBack({ -1.0f, -1.2f }, 200);
	path2.PushBack({ 1.0f, -1.2f }, 200);
	path3.PushBack({ -1.0f, 1.2f }, 200);
	path4.PushBack({ 1.0f, 1.2f }, 200);
}

SceneStory4::~SceneStory4()
{

}

// Load assets
bool SceneStory4::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	texture = App->textures->Load("Assets/Intro/prueba.png");

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	timeout = SDL_GetTicks() + 1000;

	return ret;
}

update_status SceneStory4::Update()
{
	if (App->input->keys[SDL_SCANCODE_G] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}
	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scenePlayerSelect, 90);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2900)) {
		App->fade->FadeToBlack(this, (Module*)App->scenestory5, 20);
	}

	character1.Update();
	character2.Update();
	character3.Update();
	character4.Update();

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2800))path1.Update();
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2800))path2.Update();
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2800))path3.Update();
	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2800))path4.Update();

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status SceneStory4::PostUpdate()
{
	App->render->Blit(texture, 0, -694, NULL);

	SDL_Rect rect1 = character1.GetCurrentFrame();
	SDL_Rect rect2 = character2.GetCurrentFrame();
	SDL_Rect rect3 = character3.GetCurrentFrame();
	SDL_Rect rect4 = character4.GetCurrentFrame();

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout) != SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2800)) {	
		App->render->Blit(texture, 15, 10, &rect1);
	}
	else if(SDL_TICKS_PASSED(SDL_GetTicks(), timeout)){
		//App->render->Blit(texture, 245 + path1.GetRelativePosition().x,  path1.GetRelativePosition().y + 290, &rect1); 
		App->render->Blit(texture, 15 + path1.GetRelativePosition().x, path1.GetRelativePosition().y + 10, &rect1);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 400 ) != SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2800)) {
		App->render->Blit(texture, 145, 10, &rect2);
	}
	else if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 400)) {
		//App->render->Blit(texture, path2.GetRelativePosition().x - 90, path2.GetRelativePosition().y + 290, &rect2);
		App->render->Blit(texture, 145 + path2.GetRelativePosition().x, 10 + path2.GetRelativePosition().y, &rect2);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 300) != SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2800)) {
		App->render->Blit(texture, 15, 241, &rect3);
	}
	else if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 300)) {
		//App->render->Blit(texture, 245 + path3.GetRelativePosition().x, path3.GetRelativePosition().y - 35, &rect3);
		App->render->Blit(texture, 15 + path3.GetRelativePosition().x, 241 + path3.GetRelativePosition().y, &rect3);
	}

	if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 200) != SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 2800)) {
		App->render->Blit(texture, 145, 241, &rect4);
	}
	else if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 200)) {
		//App->render->Blit(texture, path4.GetRelativePosition().x - 90, path4.GetRelativePosition().y - 35, &rect4);
		App->render->Blit(texture, 145 + path4.GetRelativePosition().x, 241 + path4.GetRelativePosition().y, &rect4);
	}

	return update_status::UPDATE_CONTINUE;
}

bool SceneStory4::CleanUp()
{
	App->textures->Unload(texture);

	return true;
}