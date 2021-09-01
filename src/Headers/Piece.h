#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <bitset>
#include "PieceTextures.h"

class Piece: public sf::Drawable {
    public:
        Piece(char type='P', bool color= true);

        void setPosition(sf::Vector2f coordinates);

        ~Piece(){};
    
    private:
        //objects, vectors, enums
        sf::Sprite m_sprite;

        //Attributes
        char m_type;
        bool m_player;
        sf::Vector2f m_position;
        std::string m_strPosition;

        //Methods
        void setTexture();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif