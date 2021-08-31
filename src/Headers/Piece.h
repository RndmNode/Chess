#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <bitset>

class Piece: public sf::Drawable {
    public:
        Piece(char type, bool color);
        void setPosition(sf::Vector2f coordinates);
        void setTexture();
        ~Piece(){};
    
    private:
        sf::Sprite m_sprite;

        char m_type;
        bool m_player;
        std::string m_position;
        std::bitset<64> board;

        void toString(sf::Vector2f coordinates);
        
        
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif