#include <cstdlib>
#include <exception>
//#include "CartesianChart.hpp"
//#include "Utility.hpp"
#include "Plot.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "Test", sf::Style::Default, settings);

    sf::Font font;
    if (!font.loadFromFile("fonts/font.ttf"))
    {
        throw std::runtime_error("Failed to load resource/ipaexm.ttf");
    }

    sf::Color font_color = sf::Color::White;
    sf::Color axes_color = sf::Color::White;
    sf::Color scale_color = sf::Color(100.f, 100.f, 100.f);
    
    Plot chart(axes_color,scale_color,font,font_color);
    PlotData data(sf::Color(255.f, 255.f, 255.f),1);
    sf::Vector2<double> tmp1(1.0,1.0);
    data.addData(tmp1);
    sf::Vector2<double> tmp2(2.0,2.0);
    data.addData(tmp2);
    sf::Vector2<double> tmp3(3.0,3.0);
    data.addData(tmp3);
    sf::Vector2<double> tmp4(4.0,4.0);
    data.addData(tmp4);
    chart.addData(data);

    chart.setPosition(50, 50);
    
    while (window.isOpen())
    {
        if (sf::Event event; window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color(30, 30, 30));
        window.draw(chart);
        window.display();
    }

    return EXIT_SUCCESS;
}