#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 24

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleAudio;
class ModuleUI;
class ModulePlayer;

class SceneDescription;
class SceneIntro;
class Intro1;
class Intro2;
class SceneStory;
class SceneStory3;
class SceneStory4;
class SceneStory5;
class SceneFinal;

class SceneLevel1;
class ScenePlayerSelect;
class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModulePowerUp;

class ModuleFadeToBlack;
class ModuleFonts;
class ModuleRender;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	update_status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleUI* UI = nullptr;

	ModulePlayer* player = nullptr;

	SceneDescription* scenedescription = nullptr;
	SceneIntro* sceneIntro = nullptr;
	SceneLevel1* sceneLevel_1 = nullptr;
	Intro1* intro1 = nullptr;
	Intro2* intro2 = nullptr;
	SceneStory* scenestory = nullptr;
	SceneStory3* scenestory3 = nullptr;
	SceneStory4* scenestory4 = nullptr;
	SceneStory5* scenestory5 = nullptr;

	SceneFinal* scenefinal = nullptr;

	ScenePlayerSelect* scenePlayerSelect = nullptr;

	ModuleEnemies* enemies = nullptr;
	ModulePowerUp* powerups = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;

	ModuleRender* render = nullptr;

	//DEBUG
	bool DEBUG = false;
	uint speedMultiplier = 1;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__