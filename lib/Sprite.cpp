#include "Sprite.h"

Sprite::Sprite()
{
    // Constructor
}

Sprite::Sprite(int x, int y)
{
    m_x = x;
    m_y = y;

    SDL_RendererFlip mFlipType;
}

Sprite::~Sprite()
{
    // Destructor
}

void Sprite::moveLeft()
{
    --m_x;
}

void Sprite::moveRight()
{
    ++m_x;
}

void Sprite::moveUp()
{
    --m_y;
}

void Sprite:: moveDown()
{
    ++m_y;
}

int Sprite::xGetter()
{
    return m_x;
}

int Sprite::yGetter()
{
    return m_y;
}

void Sprite::free()
{
    LTexture::free();
    m_x = 0;
    m_y = 0;
}
