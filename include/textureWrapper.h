#ifndef TEXTUREWRAPPER_H
#define TEXTUREWRAPPER_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "gif_lib.h"

#include <stdio.h>
#include <string>

class LTexture
{
    private:
        SDL_Texture* mTexture;
        SDL_Surface* mSurface;
        int mWidth;
        int mHeight;

    public:
        // Contructors
        LTexture();

        LTexture(int width, int height);

        // Destructor
        ~LTexture();

        // Load texture from file at provided path
        bool loadFromFile(std::string path,
                          SDL_Renderer* renderer,
                          Uint8 r, Uint8 g, Uint8 b); // Hex values for red, green and blue

        // Same as the above function
        bool loadGIF(std::string path,
                                     bool colorKey,
                                     int r, int g, int b,
                                     int alpha);

        // Deallocate them
        void free();

        // Render textures at given point
        void render(int x, int y, // Position to render
                    SDL_Renderer* renderer, // Where to render
                    SDL_Rect* clip,         // What size
                    SDL_Point* center,      // The center to flip around
                    double angle,           // The angle to rotate
                    SDL_RendererFlip flipType); // Flip type

        // Render 1 specific part of a sprite sheet
        void clipRender(int x, int y,           // Rendering position
                        SDL_Renderer* renderer, // Where to render
                        SDL_Rect* clip);        // Determine the size of the rendered part

        // Get image dimensions
        int getWidth();
        int getHeight();
};
#endif // TEXTUREWRAPPER_H
