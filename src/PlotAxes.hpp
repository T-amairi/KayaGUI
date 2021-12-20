#pragma once
#include <SFML/Graphics.hpp>
#include <utility>

using namespace std;

class PlotAxes : virtual public sf::Transformable, virtual public sf::Drawable
{
    public:
        //dimension of the plot
        static const sf::Vector2f DIMENSION;
        static const sf::Vector2f MARGIN;

        //Constructor for PlotAxes class
        PlotAxes(sf::Color axes_color,sf::Color scale_color,sf::Font font, sf::Color font_color);

        //Drawing functions
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void drawAxes(sf::RenderTarget& target, sf::RenderStates states) const;
        void drawLegend(sf::RenderTarget& target, sf::RenderStates states) const;

        //setter functions
        void setRangeX(const pair<double, double>& x_range);
        void setRangeY(const pair<double, double>& y_range);
 
        //getter functions 
        pair<double, double> getRangeX() const;
        pair<double, double> getRangeY() const;
        
    private:
        //axes par
        sf::Color back_ground_color_;
        sf::Color axes_color_;
        sf::Color scale_color_;
        sf::Font font_;
        sf::Color font_color_;

        //min/max for each axis
        pair<double, double> x_range_;
        pair<double, double> y_range_;
};