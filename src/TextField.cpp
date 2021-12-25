#include "TextField.hpp"

/**
 * \brief Constructor for TextField class
 */
TextField::TextField(unsigned int maxChar, double x, double y):font_(),size_(maxChar),str_(),text_(),
rect_(sf::Vector2f(5 * maxChar, 20)),has_focus_(false)
{
    font_.loadFromFile("fonts/font.ttf");

    text_.setFont(font_); 
    text_.setCharacterSize(15); 
    text_.setFillColor(sf::Color::Black);
    text_.setPosition(x,y);
    
    rect_.setOutlineThickness(2);
    rect_.setFillColor(sf::Color::White);
    rect_.setOutlineColor(sf::Color::Black);
    rect_.setPosition(text_.getPosition());
}

/**
 * \brief get text_ attribute
 * @return the text in the input field
 */
sf::Text TextField::getText() const
{
    return text_;
}

/**
 * \brief get str_ attribute
 * @return the string in the input field 
 */
std::string TextField::getStr() const
{
    return str_;
}

/**
 * \brief get rect_ attribute
 * @return the rectangle shape
 */
sf::RectangleShape TextField::getRect() const
{
    return rect_;
}

/**
 * \brief check if the mouse cursor is on the input field
 * @param mouse_coord x,y coord of the mouse
 * @return true if it's the case, false otherwise
*/
bool TextField::ifContains(sf::Vector2f mouse_coord) const
{
    return rect_.getGlobalBounds().contains(mouse_coord);
}

/**
 * \brief change the outline color of the input field depending on focus
 * @param focus a boolean, if true a red color, black otherwise
*/
void TextField::setOutlineColor(bool focus)
{
    has_focus_ = focus;

    if(focus)
    {
        rect_.setOutlineColor(sf::Color::Red);
    }

    else
    {
        rect_.setOutlineColor(sf::Color::White); 
    }
}

/**
 * \brief update the text in the input field depending on the keyboard output
 * @param event the keyboard output
*/
void TextField::handleInput(sf::Event event)
{
    if(!has_focus_ || event.type != sf::Event::TextEntered)
    {
        return;
    }

    else if(event.text.unicode == 8 && !str_.empty())
    {   
        str_ = str_.substr(0, str_.size() - 1);
        text_.setString(str_);
    }

    else if(str_.size() < size_ && event.text.unicode != 8)
    {
        str_ += event.text.unicode;
        text_.setString(str_);
    }
}