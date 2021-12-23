#pragma once
#include "WindowPlot.hpp"

class CheckPlot
{
    public:
        //Constructor for CheckPlot class
        CheckPlot();

        //setter function
        void addPlot(WindowPlot* plot);
        void startPlot(int id);
        void stopPlot(int id);
        void addButton(sf::Sprite* button);
        void setColor(int id, sf::Color color);
        void setAllColor(sf::Color color);

        //getter function
        std::vector<sf::Sprite*> getButtons();

        //free
        void free();
        
        //check if the mouse is on a button
        int operator[](sf::Vector2f mouse_coord) const;

    private:
        //list of all buttons
        std::vector<sf::Sprite*> my_buttons_;
        //list of all plots
        std::vector<WindowPlot*> my_plots_;
};