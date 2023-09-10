#ifndef __SCENE_PLAYERSELECT_H__
#define __SCENE_PLAYERSELECT_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h" 

struct SDL_Texture;

class ScenePlayerSelect : public Module
{
public:
	//Constructor
	ScenePlayerSelect(bool startEnabled);

	//Destructor
	~ScenePlayerSelect();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

	iPoint position; 

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* Texture1 = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Texture* numberstexture = nullptr;

	Uint32 timeout;

	int PowerUpCollectFx = 0;
	int selectedPlayerFx = 0;

	Animation selected;
	Animation numbers; 

	int arrayselection[0][4];
};

#endif