#include "WindowPlot.hpp"

/**
 * \brief Constructor for WindowPlot class
 */
WindowPlot::WindowPlot(std::string title, sf::Color axes_color, sf::Color scale_color, sf::Font font, sf::Color font_color, 
std::string x_label, std::string y_label):Window(),plot_(axes_color,scale_color,font,font_color,x_label,y_label),title_(title){}

/**
 * \brief open the window with the corresponding plot
*/
void WindowPlot::run()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    create(sf::VideoMode(875, 700),title_,sf::Style::Default,settings);

    PlotData data(sf::Color(255.f, 255.f, 255.f),1);
    sf::Vector2<double> tmp1(1.0,1.0);
    data.addData(tmp1);
    sf::Vector2<double> tmp2(2.0,2.0);
    data.addData(tmp2);
    sf::Vector2<double> tmp3(3.0,3.0);
    data.addData(tmp3);
    sf::Vector2<double> tmp4(4.0,4.0);
    data.addData(tmp4);
    addData(data);
    setPosition(50, 50);

    while(isOpen())
    {
        if(sf::Event event; pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                close();
            }
        }

        clear(sf::Color(30, 30, 30));
        draw(plot_);
        display();
    }
}

/**
 * \brief add plotting data to the plot_ class
 * @param data the data to be added
*/
void WindowPlot::addData(PlotData data)
{
    plot_.addData(data);
}

/**
 * \brief set the position of plot_ in the window
 * @param x coord
 * @param y y coord
*/
void WindowPlot::setPosition(double x, double y)
{
    plot_.setPosition(x,y);
}