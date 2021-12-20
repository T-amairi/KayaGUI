#include "Window.hpp"

/**
 * \brief Constructor for abstract Window class
 */
Window::Window(sf::VideoMode mode, const string &title, const sf::ContextSettings &settings)
:sf::RenderWindow(mode,title,sf::Style::Default,settings){}

/**
 * \brief Constructor for WindowPlot class
 */
WindowPlot::WindowPlot(sf::VideoMode mode, const string &title, const sf::ContextSettings &settings, 
sf::Color axes_color, sf::Color scale_color, sf::Font font, sf::Color font_color):
Window(mode,title,settings),plot_(axes_color,scale_color,font,font_color){}

/**
 * \brief draw the plot using the draw() method of the sf::RenderWindow class
*/
void WindowPlot::Draw() 
{
    draw(plot_);
}

/**
 * \brief open the window with the corresponding plot
*/
void WindowPlot::run()
{
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
    
    while (isOpen())
    {
        if (sf::Event event; pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                close();
            }
        }

        clear(sf::Color(30, 30, 30));
        Draw();
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