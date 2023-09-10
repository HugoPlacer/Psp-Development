#ifndef __SCENE_STORY3_H__
#define __SCENE_STORY3_H__

#include "Module.h"
#include "Animation.h"
#include "Path.h"

struct SDL_Texture;

class SceneStory3 : public Module
{
public:
	//Constructor
	SceneStory3(bool startEnabled);

	//Destructor
	~SceneStory3();

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

	Uint32 timeout;

	Path path;


};

#endif
