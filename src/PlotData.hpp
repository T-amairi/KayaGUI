#pragma once
#include <vector>
#include <utility>
#include <SFML/Graphics.hpp>

class PlotData
{
    public:
        //Constructor for PlotData class
        PlotData(sf::Color color, int type);

        //getter function
        size_t getDataSize() const;
        int getType() const;
        sf::Color getColor() const;  
        std::pair<double, double> getRangeX() const;
        std::pair<double, double> getRangeY() const; 

        //setter function
        void addData(sf::Vector2<double> data);

        //access data operator with index i
        sf::Vector2<double> operator()(size_t i) const;
                    
    private:
        //coord of the points (x,y)
        std::vector<sf::Vector2<double>> data_;
        //the color of the plot
        sf::Color color_; 
        //type of data : i.e 0 for points, 1 for a line
        int type_;
};