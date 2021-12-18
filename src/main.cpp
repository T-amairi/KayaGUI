#include <cstdlib>
#include <exception>
#include "CartesianChart.hpp"
#include "Utility.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    sf::ContextSettings settings;

    sf::RenderWindow window(sf::VideoMode(1600, 1200), "SFPlot-Sample", sf::Style::Default, settings);

    sf::Font font;
    if (!font.loadFromFile("fonts/font.ttf"))
    {
        throw std::runtime_error("Failed to load resource/ipaexm.ttf");
    }

    sf::Color font_color = sf::Color::White;
    sf::Color axes_color = sf::Color::White;
    sf::Color scale_color = sf::Color(100.f, 100.f, 100.f);
    sf::Color back_ground_color = sf::Color(30.f, 30.f, 30.f);

    sf::CartesianChart chart(back_ground_color,axes_color,scale_color,font,font_color);
    //auto data1 = chart.addData();
    //data1->data = {{1.0, 2.0}, {2.0, 3.0}, {3.0, 2.0}, {4.0, -1.0}};
    //data1->type = sf::CartesianData::PLOT_TYPE::POINT;
    auto data2 = chart.addData();
    data2->data = {{1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}, {4.0, 4.0}};
    data2->type = sf::CartesianData::PLOT_TYPE::LINE;
    chart.setPosition(50, 50);
    chart.autoRange();

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