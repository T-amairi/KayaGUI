#include "WindowMain.hpp"

/**
 * \brief Constructor for WindowMain class
 */
WindowMain::WindowMain():Window(),font_(),settings_(),checkplot_(),button_texture_plot_()
{
    settings_.antialiasingLevel = 8;
    font_.loadFromFile("fonts/font.ttf");
    button_texture_plot_.loadFromFile("./images/plot.jpg");
    preparePlot();
};

/**
 * \brief draw all the buttons in the CheckPlot class in the main window
*/
void WindowMain::drawButtons()
{
    auto buttons = checkplot_.getButtons();

    for(const auto& button : buttons)
    {
        draw(*button);
    }
}

/**
 * \brief fill CheckPlot
 */
void WindowMain::preparePlot()
{
    std::vector<std::string> y_labels = {"CO2 emissions","Population","GDP","Energy consumption"};
    std::vector<std::string> titles = {"CO2 emissions","Population","Gross domestic product","Energy consumption"};
    double distance = 150.0f; 

    for(size_t i = 0; i < y_labels.size(); i++)
    {
        sf::Sprite* p_b = new sf::Sprite;
        p_b->setTexture(button_texture_plot_);
        p_b->setPosition(0.0f,distance*i);
        p_b->scale(0.5f, 0.5f);
        checkplot_.addButton(p_b);
        checkplot_.addPlot(new WindowPlot(titles[i],sf::Color::White,sf::Color(100.f, 100.f, 100.f),font_,sf::Color::White,"Year",y_labels[i]));
    }
}

/**
 * \brief return the position of the mouse
 */
sf::Vector2f WindowMain::getMousePos()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y));
    return mousePosF;
}

/**
 * \brief open the main GUI window
*/
void WindowMain::run()
{
    create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height),"KAYA GUI",sf::Style::Default,settings_);

    while(isOpen())
    {
        sf::Event Event;
        
        while(pollEvent(Event))
        {
            switch(Event.type)
            {
                case sf::Event::Closed:
                    close();
                    checkplot_.free();
                    break;
                case sf::Event::MouseMoved:
                {
                    int res = checkplot_[getMousePos()];

                    if(res != -1)
                    {
                       checkplot_.setColor(res,sf::Color(250,20,20));
                    }

                    else
                    {
                        checkplot_.setAllColor(sf::Color(255,255,255));
                    }
                }
                    break;
                case sf::Event::MouseButtonPressed:
                {
                    int res = checkplot_[getMousePos()];

                    if(res != -1)
                    {
                        checkplot_.startPlot(res);
                    }
                }
                    break;
                default:
                    break;
            }
        }

        clear(sf::Color(255, 255, 255));
        drawButtons();
        display();
    }
}