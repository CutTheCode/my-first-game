#include "Sprite.h"
#include "init.h"
#include "Box2D.h"

#define HOR_FRAMES 16
#define VER_FRAMES 16

enum Actions{
    IDLE,
    WALK,
    JUMP,
    SPIN,
    TOTAL
};

// These variables are for the game window
SDL_Window* mainWindow = NULL;
SDL_Renderer* sceneRenderer = NULL;

// These are for the images and sprites
Sprite catGif;
SDL_Rect catRect[VER_FRAMES][HOR_FRAMES];

LTexture background(SCREEN_WIDTH, SCREEN_HEIGHT);
SDL_Rect bgRect;

LTexture foreground(SCREEN_WIDTH, SCREEN_HEIGHT);
SDL_Rect fgRect;

int frame = 0;
int maxFrame = 0;
SDL_RendererFlip flipType;
int main(int argc, char* argv[])
{
    init();
    load();

    int action;

    bool quitFlag = false;
    bool isMoving = false;
    bool isLeft = false;
    SDL_Event event;

    while (!quitFlag)
    {
        action = IDLE;
        maxFrame = 4;
        while (SDL_PollEvent(&event) != 0) // Handle events in queue
        {
            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
                quitFlag = true;
        }

        const Uint8* states = SDL_GetKeyboardState(NULL);

        if (states[SDL_SCANCODE_A])
        {
            maxFrame = 8;
            action = WALK;
            isMoving = true;
            isLeft = true;
            flipType = SDL_FLIP_HORIZONTAL;
            catGif.moveLeft();
        }
        else if (states[SDL_SCANCODE_D])
        {
            maxFrame = 8;
            action = WALK;
            isMoving = true;
            isLeft = false;
            flipType = SDL_FLIP_NONE;
            catGif.moveRight();

        }
        else if (states[SDL_SCANCODE_SPACE])
        {
            isMoving = true;
            maxFrame = 10;
            action = SPIN;
            if (isLeft)
                flipType = SDL_FLIP_HORIZONTAL;
            else
                flipType = SDL_FLIP_NONE;
        }
        else if (isMoving == true)
        {
            isMoving = false;
            maxFrame = 4;
            frame = 0;
            action = IDLE;
        }

        // Drawing
        background.clipRender(0, 0, sceneRenderer, &bgRect);
        foreground.clipRender(0, SCREEN_HEIGHT / 2, sceneRenderer, &fgRect);

        SDL_Rect* currFrame = &catRect[action][frame / 8];
        int x = catGif.xGetter();
        int y = catGif.yGetter();

        catGif.render(x, y, sceneRenderer, currFrame, NULL, 0, flipType);

        // Update
        SDL_RenderPresent(sceneRenderer);

        frame++;
        if (frame / 8  == maxFrame)
        {
            frame = 0;
        }
    }

    clean();

    return 0;
}

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }
        // Create window
        mainWindow = SDL_CreateWindow("The Adventure of Tuot",
                                  SDL_WINDOWPOS_UNDEFINED, // x coordinate
                                  SDL_WINDOWPOS_UNDEFINED, // y coordinate
                                  SCREEN_WIDTH,
                                  SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);        // make sure the window will show up
        if (mainWindow == NULL)
        {
            printf("Window creation failed:  %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            // Init image load
            int imgFlags = IMG_INIT_PNG;
            // Error check
            if (!(IMG_Init(imgFlags) && imgFlags))
            {
                printf("SDL_image could not initialize, error: %s\n", IMG_GetError());
                success = false;
            }

            // Create renderer for our main window
            sceneRenderer = SDL_CreateRenderer(mainWindow, -1,
                                               SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            // Error check
            if (sceneRenderer == NULL)
            {
                printf("Could not create renderer %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(sceneRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                imgFlags = IMG_INIT_PNG;
                // Error check
                if (!(IMG_Init(imgFlags) && imgFlags))
                {
                    printf("Could not initialize SDL_Image, %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}


bool load()
{
    bool success = true;

    // Load background
    if (!background.loadFromFile("./assets/scenes/far.png", sceneRenderer, 0xFF, 0xFF, 0xFF))
    {
        printf("SDL error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        bgRect.x = 0;
        bgRect.y = 0;
        bgRect.w = SCREEN_WIDTH;
        bgRect.h = SCREEN_HEIGHT;
    }

        // Load foreground
    if (!foreground.loadFromFile("./assets/scenes/foreground-merged.png", sceneRenderer, 0x00, 0x00, 0x00))
    {
        printf("SDL error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        fgRect.x = 0;
        fgRect.y = 0;
        fgRect.w = SCREEN_WIDTH;
        fgRect.h = SCREEN_HEIGHT / 2;
    }

    // Load cat sprite sheets
    if (!catGif.loadFromFile("./assets/pets/fighter_cat_sprite/cat_sprite_base_64.png",
                            sceneRenderer, 0X00, 0x00, 0x00))
    {
        printf("%s", SDL_GetError());
        success = false;
    }
    else
    {
        int initX = 0;
        int initY = 0;
        for (int ver = 0; ver < VER_FRAMES; ver++)
        {

            for (int hor = 0; hor < HOR_FRAMES; hor++)
            {
                catRect[ver][hor].x = initX;
                catRect[ver][hor].y = initY;
                catRect[ver][hor].w = 64;
                catRect[ver][hor].h = 64;
                initX += 64;
            }
            initX = 0;
            initY += 64;
        }
        initX = 0;
        initY = 0;
    }
    return success;
}

void clean()
{
    background.free();
    foreground.free();

    catGif.free();

    SDL_DestroyRenderer(sceneRenderer);
    sceneRenderer = NULL;

    SDL_DestroyWindow(mainWindow);
    mainWindow = NULL;
    SDL_Quit();
}
