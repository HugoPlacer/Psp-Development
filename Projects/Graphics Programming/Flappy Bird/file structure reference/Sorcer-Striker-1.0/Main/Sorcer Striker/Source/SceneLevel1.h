#ifndef __SCENE_LEVEL1_H__
#define __SCENE_LEVEL1_H__

#include "Module.h"
#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel1 : public Module
{
public:
	//Constructor
	SceneLevel1(bool startEnabled);

	//Destructor
	~SceneLevel1();

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
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* warning = nullptr;
	uint warningTimer;
	bool warningSelected;
	int bgPos = 0;
	int bgSpeed = 10;

	bool spawnMode = false;
	uint selectedSpawnItem = 1;

	SDL_Rect bgSize;
	Collider* screenBoundingBox = nullptr;

	iPoint mousePos;
	Uint32 mouseState;

	int warningFx = 0;

};

#endif