#include "init.h"

bool errorCheck(SDL_Surface* surface)
{
    if (surface == NULL)
        return false;
    else
        return true;
}

bool errorCheck(SDL_Texture* texture)
{
    if (texture == NULL )
        return false;
    else
        return true;
}

bool errorCheck(SDL_Renderer* renderer)
{
    if (renderer == NULL)
        return false;
    else
        return false;
}
