#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>

class Piece: public sf::Drawable {
    public:
        Piece(){};
        ~Piece(){};
    
    private:
        sf::Sprite a_sprite;

        char a_type;
        bool a_player;
        std::string a_position;

        void toString(sf::Vector2f coordinates);
        void setTexture();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif