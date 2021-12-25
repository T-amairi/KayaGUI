#pragma once
#include "WindowPlot.hpp"
#include <memory>

class CheckPlot
{
    public:
        //Constructor for CheckPlot class
        CheckPlot();

        //setter function
        void addPlot(std::shared_ptr<WindowPlot> pTrplot);
        void startPlot(int id);
        void stopPlot(int id);
        void addButton(std::shared_ptr<sf::Sprite> pTrbutton);
        void setColor(int id, sf::Color color);
        void setAllColor(sf::Color color);

        //getter function
        std::vector<std::shared_ptr<sf::Sprite>> getButtons();
        
        //check if the mouse is on a button
        int operator[](sf::Vector2f mouse_coord) const;

    private:
        //list of all buttons
        std::vector<std::shared_ptr<sf::Sprite>> my_buttons_;
        //list of all plots
        std::vector<std::shared_ptr<WindowPlot>> my_plots_;
};