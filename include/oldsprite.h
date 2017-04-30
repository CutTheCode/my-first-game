#ifndef SPRITE_H
#define SPRITE_H

#include "textureWrapper.h"

class sprite : public LTexture
{
    public:
        sprite();
        virtual ~sprite();
         public:

        Sprite();
        Sprite(int x, int y);

        ~Sprite();

        void moveLeft()
        {
            --m_x;
        }

        void moveRight()
        {
            ++m_x;
        }

        void moveUp()
        {
            --m_y;
        }

        void moveDown()
        {
            ++m_y;
        }

        int xGetter()
        {
            return m_x;
        }

        int yGetter()
        {
            return m_y;
        }

    protected:

    private:
         int m_x, m_y; // Sprite's coordinate

};

#endif // SPRITE_H
