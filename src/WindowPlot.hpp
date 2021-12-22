#pragma once
#include "Plot.hpp"
#include "Window.hpp"

class WindowPlot : public Window
{
    public:        
        //Constructor for WindowPlot class
        WindowPlot(std::string title, sf::Color axes_color, sf::Color scale_color, sf::Font font, 
        sf::Color font_color, std::string x_label, std::string y_label);

        //Open the window with a plot
        void run();

        //setter function
        void addData(PlotData data);
        void setPosition(double x, double y);

    private:
        //the plot to be shown in the window
        Plot plot_;
        //window title;
        std::string title_;
};
