#include "Window.hpp"

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::Font font;
    font.loadFromFile("fonts/font.ttf");
    sf::Color font_color = sf::Color::White;
    sf::Color axes_color = sf::Color::White;
    sf::Color scale_color = sf::Color(100.f, 100.f, 100.f);

    auto vid = sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    
    WindowPlot window(vid,"Test",settings,axes_color,scale_color,font,font_color);
    window.run();

    return 0;
}