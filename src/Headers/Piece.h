#ifndef PIECE_H
#define PIECE_H

#include "PieceTextures.h"

class Piece: public sf::Drawable {
    public:
        //Constructors
        Piece(){};
        Piece(int type, bool color);

        //objects, vectors, enums
        sf::Sprite m_sprite;

        //Attributes
        sf::Vector2f originOffset;
        bool m_selected = false;
        bool m_updated = false;
        int m_type;
        bool m_player;
        int m_squarePosition;

        //Methods
        void setPosition(sf::RenderTarget& target, sf::Vector2f coordinates);
        int getPosition(sf::RenderTarget& target, sf::Vector2f coordinates);
        void setTexture();

        ~Piece(){};
    
    private:
        

        //Methods
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif