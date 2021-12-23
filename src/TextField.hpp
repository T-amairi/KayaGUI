#include <SFML/Graphics.hpp>

class TextField 
{
    public:
        //Constructor for TextField class
        TextField(unsigned int maxChar, double x, double y);

        //getter function
        sf::Text getText();
        sf::RectangleShape getRect();
        std::string getStr();
  
        //setter function
        void setOutlineColor(bool focus);

        //to update the text in the rectangle
        void handleInput(sf::Event event);

        //check if the mouse is on the input area
        bool ifContains(sf::Vector2f mouse_coord) const;

    private:
        //the font
        sf::Font font_;
        //the number of char allowed in the input field
        unsigned int size_;
        //the input text
        std::string str_;
        //str_ equivalent in sf::Text
        sf::Text text_;
        //the input area
        sf::RectangleShape rect_;
        //to change the color of the rectangle 
        bool has_focus_;
};