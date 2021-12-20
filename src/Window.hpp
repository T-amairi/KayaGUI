#pragma once
#include "Plot.hpp"
#include <SFML/Window.hpp>

class Window : public sf::RenderWindow
{
    public:
        //Constructor for abstract Window class
        Window(sf::VideoMode mode, const string &title, const sf::ContextSettings &settings);

        //virtual method to render the window
        virtual void run() = 0;
};

class WindowPlot : public Window
{
    public:
        //Constructor for WindowPlot class
        WindowPlot(sf::VideoMode mode, const string &title, const sf::ContextSettings &settings, 
        sf::Color axes_color, sf::Color scale_color, sf::Font font, sf::Color font_color);

        //Draw function
        void Draw();

        //Open the window with a plot
        void run();

        //setter function
        void addData(PlotData data);
        void setPosition(double x, double y);

    private:
        Plot plot_;
};