#ifndef __SCENE_STORY5_H__
#define __SCENE_STORY5_H__

#include "Module.h"
#include "Animation.h"
#include "Path.h"

struct SDL_Texture;

class SceneStory5 : public Module
{
public:
	//Constructor
	SceneStory5(bool startEnabled);

	//Destructor
	~SceneStory5();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	bool CleanUp();

public:

	// The scene sprite sheet loaded into an SDL_Texture
	//SDL_Texture* bgTexture = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Texture* texture2 = nullptr;
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* shiptexture = nullptr;
	SDL_Texture* shiptexture2 = nullptr;
	SDL_Texture* shiptexture3 = nullptr;

	int bgPos = 0;
	int bgSpeed = 10;

	SDL_Rect bgSize;

	Uint32 timeout;

	Animation letras;
	Animation man;
	Animation explosion;

	Animation ships;
	Animation ships2;
	Animation ships3;

	Path path;
	Path pathscroll;
	Path pathship;
	Path pathship3;
};

#endif