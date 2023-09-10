#ifndef __SceneFinal_H__
#define __SceneFinalH__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneFinal : public Module
{
public:
	//Constructor
	SceneFinal(bool startEnabled);

	//Destructor
	~SceneFinal();

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
	Uint32 timeout;

	SDL_Texture* textura = nullptr;

	Animation cuadrado;
	Animation letras; 
	Animation n;
	Animation u;
	Animation b;
};

#endif
