#ifndef SPRITE_H
#define SPRITE_H

#include "textureWrapper.h"

class Sprite : public LTexture
{
    public:
        Sprite();

        Sprite(int x, int y);

        ~Sprite();

        void moveLeft();

        void moveRight();

        void moveUp();

        void moveDown();

        void stop();

        int xGetter();

        int yGetter();

        void free();

    protected:

    private:
        int m_x, m_y; // Sprite's coordinate
};

#endif // SPRITE_H
