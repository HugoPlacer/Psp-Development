#include "ModuleUI.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include "SceneLevel1.h"
#include "ModuleAudio.h"

#include <stdio.h>

#include "SDL/include/SDL.h"

ModuleUI::ModuleUI(bool startEnabled) : Module(startEnabled)
{
	stage.PushBack({ 56, 43, 94, 40 });
	one.PushBack({ 160,35,14,39 });
	cinta.PushBack({ 197,67,112,23 });

	pathstage.PushBack({ 2.0f, 0.0f }, 50);
	pathone.PushBack({ 0.0f, 2.0f }, 50);
	pathcinta.PushBack({ -2.0f, 0.0f }, 50);

	type.PushBack({ 4,8,91,132 });
	type.PushBack({ 102,8,91,132 });
	type.PushBack({ 201,8,91,132 });
	type.PushBack({ 298,8,91,132 });
	type.PushBack({ 396,8,91,132 });
	type.PushBack({ 495,8,91,132 });
	type.PushBack({ 592,8,91,132 });
	type.PushBack({ 690,8,91,132 });

	type.PushBack({ 5,149,91,132 });
	type.PushBack({ 101,149,91,132 });
	type.PushBack({ 200,149,91,132 });
	type.PushBack({ 297,149,91,132 });
	type.PushBack({ 395,149,91,132 });
	type.PushBack({ 494,149,91,132 });
	type.PushBack({ 591,149,91,132 });
	type.PushBack({ 689,149,91,132 });

	type.PushBack({ 4,287,91,132 });
	type.PushBack({ 102,287,91,132 });
	type.PushBack({ 201,287,91,132 });
	type.PushBack({ 298,287,91,132 });
	type.PushBack({ 396,287,91,132 });
	type.PushBack({ 495,287,91,132 });
	type.PushBack({ 592,287,91,132 });
	type.PushBack({ 690,287,91,132 });
	type.speed = 0.1f;
	type.loop = false;
}

ModuleUI::~ModuleUI()
{

}

bool ModuleUI::Start()
{

	UIElements = App->textures->Load("Assets/UI/gp-ui.png");
	wintexture = App->textures->Load("Assets/Sprites/stageclear1.png");
	stage1texture = App->textures->Load("Assets/Sprites/stage.png");
	typingtexture = App->textures->Load("Assets/Sprites/typing.png");

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { " 01&........x23456789" };
	scoreFont = App->fonts->Load("Assets/Fonts/yb-numbers.png", lookupTable, 1);

	char lookupTable2[] = { "! #$%&'()*+,-./0123456789:;<=>? ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^- abcdefghijklmnopqrstuvwxyz | _" };
	debugFont = App->fonts->Load("Assets/Fonts/ddrtiny.bmp", lookupTable2, 1);
	
	stage.Reset();
	one.Reset();
	cinta.Reset();
	type.Reset();
	pathstage.Reset();
	pathone.Reset();
	pathcinta.Reset();

	return true;
}

update_status ModuleUI::Update() {
	stage.Update(); 
	one.Update();
	cinta.Update();
	type.Update();
	if (App->render->camera.y < -100 && App->render->camera.y > -300) pathstage.Update();
	if (App->render->camera.y < -100 && App->render->camera.y > -300) pathone.Update();
	if (App->render->camera.y < -100 && App->render->camera.y > -300) pathcinta.Update();
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleUI::PostUpdate()
{

	SDL_Rect Player1 = { 35, 1, 55, 8 };
	SDL_Rect livesIcon = { 145, 46, 15, 16 };
	SDL_Rect bombsIcon = { 163, 47, 16, 16 };
	SDL_Rect HighScore = { 93, 1, 64, 8 };
	SDL_Rect Player2 = { 1, 29, 56, 8 };
	SDL_Rect InsertCoinPlayer2 = { 192,45,55,16 };

	SDL_Rect GameOver = { 1, 47, 143, 16 };
	


	App->render->Blit(UIElements, 5, 5, &Player1, 0);
	App->render->Blit(UIElements, 5, 25, &livesIcon, 0);
	App->render->Blit(UIElements, 35, 25, &bombsIcon, 0);
	App->render->Blit(UIElements, 90, 5, &HighScore, 0);
	App->render->Blit(UIElements, 170, 5, &Player2, 0);
	App->render->Blit(UIElements, 170, 20, &InsertCoinPlayer2, 0);


	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%7d", App->player->score);
	sprintf_s(livesText, 10, "x%1d", App->player->lives >= 0 ? App->player->lives : 0);
	sprintf_s(bombsText, 10, "x%1d", App->player->bombAmount);

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(0, 13, scoreFont, scoreText);
	App->fonts->BlitText(20, 30, scoreFont, livesText);
	App->fonts->BlitText(50, 30, scoreFont, bombsText);
	App->fonts->BlitText(100, 13, scoreFont, scoreText);
	App->fonts->BlitText(220, 13, scoreFont, "0");

	//App->fonts->BlitText(50, 300, scoreFont, "0123456789");

	//DEBUG
	if (App->DEBUG == true)
	{
		App->fonts->BlitText(0, 220, debugFont, "F8-GAMESPEED:");
		App->fonts->BlitText(120, 220, debugFont, App->speedMultiplier == 1 ? "1" : "2");

		App->fonts->BlitText(0, 235, debugFont, "F3-WIN");

		App->fonts->BlitText(0, 250, debugFont, "F4-LOSE");

		App->fonts->BlitText(0, 265, debugFont, "F5-GO TO BOSS");

		if (!App->sceneLevel_1->spawnMode)
		{
			App->fonts->BlitText(0, 280, debugFont, "F6-SPAWNMODE:");
			App->fonts->BlitText(120, 280, debugFont, App->sceneLevel_1->spawnMode ? "ON" : "OFF");
		}
		else
		{
			sprintf_s(selectedObjectText, 10, "<%1d>", App->sceneLevel_1->selectedSpawnItem);

			App->fonts->BlitText(0, 280, debugFont, "SELECTED-OBJECT:");
			App->fonts->BlitText(145, 280, debugFont, selectedObjectText);
		}

		App->fonts->BlitText(0, 295, debugFont, "F2-COLLISIONS:");
		App->fonts->BlitText(130, 295, debugFont, App->collisions->debug ? "SHOW" : "HIDE");

		App->fonts->BlitText(0, 310, debugFont, "F1-GODMODE:");
		App->fonts->BlitText(110, 310, debugFont, App->player->godMode ? "ON" : "OFF");

		App->fonts->BlitText(0, 325, debugFont, "Q-QUIT");

		if (App->input->keys[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN) App->DEBUG = false;
	}

	if (App->input->keys[SDL_SCANCODE_F1] == KEY_STATE::KEY_DOWN) App->DEBUG = true;


	if (App->player->win) {
		App->render->Blit(wintexture, 0, 0, NULL, 0);
	}

	if (App->player->lives < 0) {
		App->render->Blit(UIElements, 50, 150, &GameOver, 0);
	}

	if (App->render->camera.y < -100 && App->render->camera.y > -300) {
		SDL_Rect rect = stage.GetCurrentFrame();
		//App->render->Blit(stage1texture, 50, App->render->camera.y + 50, &rect);
		position.x = pathstage.GetRelativePosition().x;
		if (position.x <= 50.0) {
			App->render->Blit(stage1texture, position.x, App->render->camera.y + 50, &rect);
		}
		else{App->render->Blit(stage1texture, 56, App->render->camera.y + 50, &rect); }
	}
	if (App->render->camera.y < -100 && App->render->camera.y > -300) {
		SDL_Rect rect = one.GetCurrentFrame();
		position.y = pathone.GetRelativePosition().y;
		if (position.y <= 42) {
			App->render->Blit(stage1texture, 160, App->render->camera.y + position.y, &rect);
		}
		else{App->render->Blit(stage1texture, 160, App->render->camera.y + 42, &rect);
		}
	}
	if (App->render->camera.y < -100 && App->render->camera.y > -300) {
		SDL_Rect rect = cinta.GetCurrentFrame();
		position.x = pathcinta.GetRelativePosition().x;
		if (position.x >= -62.0) {
			App->render->Blit(stage1texture, 130 + position.x, App->render->camera.y + 77, &rect);
		}
		else { App->render->Blit(stage1texture, 62, App->render->camera.y + 77, &rect); }
	}

	if (App->render->camera.y > -200) {
		SDL_Rect rect = type.GetCurrentFrame();
		App->render->Blit(typingtexture, 10, 150 + App->render->camera.y, &rect);
	}
	return update_status::UPDATE_CONTINUE;
}