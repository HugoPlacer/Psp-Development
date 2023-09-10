#include "../common/common-sce.h"
#include "game.h"

#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>
#include <string.h>
#include <math.h>

int Init(){
    Texture *texture = load_texture("DELETE!!.png", GU_TRUE, GU_TRUE);
    if (!texture)
        return 1;

    Sprite *sprite = create_sprite(-0.5f, 0.0f, 1.0f, 0.5f, texture);
    if (!sprite)
        return 1;

    Camera2D camera =
        {
            .x = 0,
            .y = 0,
            .rot = 0.0f};
    
    return 0
}

int Input(){

    return 0
}

int Process(){
    apply_camera(&camera);

    return 0
}

int Render(){

    draw_sprite(sprite);
    return 0
}

int CleanUp(){

    return 0
}