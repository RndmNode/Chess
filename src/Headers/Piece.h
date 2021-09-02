#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <bitset>
#include "PieceTextures.h"

class Piece: public sf::Drawable {
    public:
        //Constructors
        Piece(){};
        Piece(int type, bool color);

        //objects, vectors, enums
        sf::Sprite m_sprite;

        //Attributes
        bool m_captured = false;
        bool m_updated = false;
        int m_type;
        bool m_player;

        //Methods
        void setPosition(sf::Vector2f coordinates);
        void setTexture();

        ~Piece(){};
    
    private:
        

        //Methods
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif