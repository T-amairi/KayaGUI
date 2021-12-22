#pragma once
#include <SFML/Graphics.hpp>

class Window : public sf::RenderWindow
{
    public:
        //Constructor for abstract Window class
        Window();

        //virtual method to render the window
        virtual void run() = 0;
};