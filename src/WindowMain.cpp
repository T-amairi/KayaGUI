#include "WindowMain.hpp"

/**
 * \brief Constructor for WindowMain class
 */
WindowMain::WindowMain():Window(),font_(),settings_(),checkplot_(),button_texture_plot_(),
equation_texture_(),background_texture_()
{
    settings_.antialiasingLevel = 8;
    font_.loadFromFile("fonts/font.ttf");
    button_texture_plot_.loadFromFile("./images/plot.jpg");
    equation_texture_.loadFromFile("./images/kaya.png");
    background_texture_.loadFromFile("./images/background.png");
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
 * \brief draw a vertical line at the middle of the main window
*/
void WindowMain::drawMiddleLine()
{
    sf::VertexArray line(sf::LinesStrip, 2);
    line[0].position = sf::Vector2f(getSize().x / 2.0, 0);
    line[0].color  = sf::Color::Black;
    line[1].position = sf::Vector2f(getSize().x / 2.0, getSize().y);
    line[1].color  = sf::Color::Black;
    draw(line);
}

/**
 * \brief draw the kaya equation in the main window
*/
void WindowMain::drawEquation()
{
    sf::Sprite equation_sprite_(equation_texture_);
    equation_sprite_.setPosition(0.0f, 40.0f);
    equation_sprite_.scale(1.0f, 1.0f);
    draw(equation_sprite_);
}

/**
 * \brief draw the text present at the left of the main window
*/
void WindowMain::drawTextsLeftPanel()
{
    sf::Text text;
    text.setFont(font_); 
    text.setCharacterSize(30); 
    text.setFillColor(sf::Color::Black);

    text.setString("Kaya identity :");
    text.setPosition(0.0f,0.0f);
    draw(text);

    text.setString("Where :");
    text.setPosition(0.0f,110.0f);
    draw(text);

    std::vector<std::string> var = {"- F is the global CO2 emissions from human sources",
    "- P is the global population", "- G is the world Gross domestic product",
    "- E is the global energy consumption"};

    double offset = 155.0f;

    for(size_t i = 0; i < var.size(); i++)
    {
        text.setString(var[i]);
        text.setPosition(0.0f,offset + 120*i);
        draw(text);
    }
}

/**
 * \brief draw all figures in the main window
*/
void WindowMain::drawAll()
{
    clear(sf::Color(255, 255, 255));

    drawButtons();
    drawMiddleLine();
    drawEquation();
    drawTextsLeftPanel();

    sf::Sprite background(background_texture_);
    draw(background);

    display();
}

/**
 * \brief fill CheckPlot
 */
void WindowMain::preparePlot()
{
    std::vector<std::string> y_labels = {"CO2 emissions","Population","GDP","Energy consumption"};
    std::vector<std::string> titles = {"CO2 emissions","Population","Gross domestic product","Energy consumption"};
    double offset = 207.5f; 

    for(size_t i = 0; i < y_labels.size(); i++)
    {
        sf::Sprite* p_b = new sf::Sprite(button_texture_plot_);
        p_b->setPosition(0.0f, offset + 118 * i);
        p_b->scale(0.25f, 0.25f);
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
    create(sf::VideoMode(1366,768),"KAYA GUI",sf::Style::Default,settings_);
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

        drawAll();
    }
}