#ifndef __Intro1_H__
#define __Intro1H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class Intro1 : public Module
{
public:
	//Constructor
	Intro1(bool startEnabled);

	//Destructor
	~Intro1();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* textura = nullptr;
};

#endif