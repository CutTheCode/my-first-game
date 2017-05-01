#include "textureWrapper.h"
#include "init.h"

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::LTexture(int width, int height)
{
    mTexture = NULL;
    mWidth = width;
    mHeight = height;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, r, g, b));

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if(newTexture == NULL)
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

bool LTexture::loadGIF(std::string path, bool colorKey, int r, int g, int b, int alpha)
{
    SDL_Surface* result = IMG_Load(path.c_str());

    if (!errorCheck(result))
    {
        printf("%s\n", SDL_GetError());
    }

    if (colorKey)
    {
        SDL_SetColorKey(result, SDL_TRUE, SDL_MapRGB(result->format, r, g, b));
    }

    if (alpha)
    {
        SDL_SetSurfaceAlphaMod(result, 255 - alpha);
    }

    result = SDL_ConvertSurfaceFormat(result, SDL_PIXELFORMAT_RGBA8888, SDL_TRUE);
    mSurface = result;
    return result != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;

		if (mSurface != NULL)
        {
            SDL_FreeSurface(mSurface);
            mSurface = NULL;
        }
	}

}

void LTexture::render(int x, int y, // Position to render
						SDL_Renderer* renderer, // Where to render
						SDL_Rect* clip,         // What size
						SDL_Point* center,      // The center to flip around, set to NULL for automactically calculated
						double angle,           // The angle to rotate
						SDL_RendererFlip flipType) // Flip type
{
		SDL_Rect renderQuad = {x, y, mWidth, mHeight};

		if (mTexture != NULL)
		{
				renderQuad.w = clip->w;
				renderQuad.h = clip->h;
		}

		SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flipType);
}

// Render specific part of a sprite sheet
void LTexture::clipRender(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};

    // Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    else
    {
        printf("Could not render clipped texture!");
    }

    SDL_RenderCopy(renderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
