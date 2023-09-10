#ifndef __SCENE_STORY4_H__
#define __SCENE_STORY4_H__

#include "Module.h"
#include "Animation.h"
#include "Path.h"

struct SDL_Texture;

class SceneStory4 : public Module
{
public:
	//Constructor
	SceneStory4(bool startEnabled);

	//Destructor
	~SceneStory4();

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
	Animation character1; 
	Animation character2; 
	Animation character3; 
	Animation character4; 

	Path path1;
	Path path2;
	Path path3;
	Path path4;


};

#endif
