#ifndef __SCENE_STORY_H__
#define __SCENE_STORY_H__

#include "Module.h"
#include "Animation.h"
#include "Path.h"

struct SDL_Texture;

class SceneStory : public Module
{
public:
	//Constructor
	SceneStory(bool startEnabled);

	//Destructor
	~SceneStory();

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
	SDL_Texture* dragonstexture = nullptr;

	Uint32 timeout; 

	Animation letras1;
	Animation goblins;
	Animation letras2;
	Animation cielo;
	Animation dragones; 
	Animation dragon;

	Animation black;

	Path path;
	Path path1;
	Path path2;
	Path path3;

};

#endif
