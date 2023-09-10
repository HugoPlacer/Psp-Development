#include "ScenePlayerSelect.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL.h"


ScenePlayerSelect::ScenePlayerSelect(bool startEnabled) : Module(startEnabled)
{
    selected.PushBack({ 1009, 32, 39, 50 });
    selected.PushBack({ 1009, 92, 39, 50 });
    selected.PushBack({ 1009, 152, 39, 50 });
    selected.PushBack({ 1009, 214, 39, 50 });
    selected.speed = 0.2f;
    
    numbers.PushBack({ 9,8,28,15 });
    numbers.PushBack({ 9,25,28,15 });
    numbers.PushBack({ 9,42,28,15 });
    numbers.PushBack({ 9,59,28,15 });
    numbers.PushBack({ 9,76,28,15 });
    numbers.PushBack({ 9,93,28,15 });
    numbers.PushBack({ 9,110,28,15 });
    numbers.PushBack({ 9,127,28,15 });
    numbers.PushBack({ 9,144,28,15 });
    numbers.PushBack({ 8,161,28,15 });
    numbers.PushBack({ 9,178,28,15 });

    numbers.PushBack({ 44,8,35,15 });
    numbers.PushBack({ 44,25,35,15 });
    numbers.PushBack({ 44,42,35,15 });
    numbers.PushBack({ 44,59,35,15 });
    numbers.PushBack({ 44,76,35,15 });
    numbers.PushBack({ 44,93,35,15 });
    numbers.PushBack({ 44,110,35,15 });
    numbers.PushBack({ 44,127,35,15 });
    numbers.PushBack({ 44,144,35,15 });
    numbers.PushBack({ 44,161,35,15 });
    numbers.speed = 0.018f;
    numbers.loop = false;
}

ScenePlayerSelect::~ScenePlayerSelect()
{

}

// Load assets
bool ScenePlayerSelect::Start()
{
    LOG("Loading background assets");

    bool ret = true;

    Texture1 = App->textures->Load("Assets/Sprites/PlayerSelect.png");
    numberstexture = App->textures->Load("Assets/Sprites/numbers.png");

    App->audio->PlayMusic("Assets/Music/characterSelect.ogg", 1.0f);
    PowerUpCollectFx = App->audio->LoadFx("Assets/Fx/character_confirm.wav");
    selectedPlayerFx = App->audio->LoadFx("Assets/Fx/charSelectMovement.wav");

    App->render->camera.x = 0;
    App->render->camera.y = 0;

    position.x = 0;
    position.y = 0;

    timeout = SDL_GetTicks();

    numbers.Reset();

    return ret;
}

update_status ScenePlayerSelect::Update()
{
    GamePad& pad = App->input->pads[0];

    if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN || pad.a == true)
    {
        App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
        App->audio->PlayFx(PowerUpCollectFx);
    }

    if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || pad.l_x < 0.0f)
    {
        App->audio->PlayFx(selectedPlayerFx);
       if (position.x == 0) {
        position.x == 0;
       }
       else {
           position.x += 246;
       }
    }

    if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || pad.l_x > 0.0f)
    {
        App->audio->PlayFx(selectedPlayerFx);
        if (position.x == -738) {
            position.x == 0;
        }
        else {
            position.x -= 246;
        }
    }

    if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout + 19000)) {
        App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
    }

    selected.Update();
    numbers.Update();

    return update_status::UPDATE_CONTINUE;
}

// Update: draw background

update_status ScenePlayerSelect::PostUpdate()
{
    // Draw everything --------------------------------------
    App->render->Blit(Texture1, position.x, 0, NULL); 

    if (position.x == 0) {
        SDL_Rect rect = selected.GetCurrentFrame(); 
        App->render->Blit(Texture1, 28, 78, &rect); 
    }
    else if (position.x == -246) {
        SDL_Rect rect = selected.GetCurrentFrame();
        App->render->Blit(Texture1, 77, 78, &rect);
    }
    else if (position.x == -492) {
        SDL_Rect rect = selected.GetCurrentFrame();
        App->render->Blit(Texture1, 125, 78, &rect);
    }
    else if (position.x == -738) {
        SDL_Rect rect = selected.GetCurrentFrame();
        App->render->Blit(Texture1, 173, 78, &rect);
    }

    if (SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {
        SDL_Rect rect = numbers.GetCurrentFrame();
        App->render->Blit(numberstexture, 106, 52, &rect);
    }

    return update_status::UPDATE_CONTINUE;
}