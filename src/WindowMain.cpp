#include "WindowMain.hpp"

/**
 * \brief Constructor for WindowMain class
 */
WindowMain::WindowMain():Window(),font_(),settings_(),checkplot_(),textures_(),
sprites_(),texts_(),fields_()
{
    settings_.antialiasingLevel = 8;
    create(sf::VideoMode(1366,768),"KAYA GUI",sf::Style::Default,settings_);
    font_.loadFromFile("fonts/font.ttf");
    prepareTextsRightPanel();
    prepareTextsLeftPanel();
    prepareTextures();
    prepareSprites();
    preparePlot();
    prepareTextFields();
};

/**
 * \brief draws all the buttons in the CheckPlot class in the main window
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
 * \brief draws all the images in the main window
*/
void WindowMain::drawImages()
{
    for(const auto& sprite : sprites_)
    {
        draw(sprite);
    } 
}

/**
 * \brief draws all the text in the main window
*/
void WindowMain::drawTexts()
{
    for(const auto& text : texts_)
    {
        draw(text);
    } 
}

/**
 * \brief draws all the text fields in the main window
*/
void WindowMain::drawTextFields()
{
    for(auto& field : fields_)
    {
        draw(field->getRect());
        draw(field->getText());
    }
}

/**
 * \brief draws all figures in the main window
*/
void WindowMain::drawAll()
{
    drawImages();
    drawButtons();
    drawTexts();
    drawTextFields();
}

/**
 * \brief loads all images into the textures_ vector
*/
void WindowMain::prepareTextures()
{
    std::vector<std::string> fileNames = {"plot.png","compute.png","kaya.png","earth.png","space.png"};

    for(const auto& fileName : fileNames)
    {
        sf::Texture texture;
        texture.loadFromFile("./images/" + fileName);
        textures_.push_back(texture);
    }
}

/**
 * \brief creates all sprites into the sprites_ vector
*/
void WindowMain::prepareSprites()
{
    /*sf::Sprite compute(textures_[1]);
    compute.setPosition(0.0f, 40.0f);
    compute.scale(1.0f, 1.0f);
    sprites_.push_back(compute);*/

    sf::Sprite space(textures_[4]);
    sprites_.push_back(space);

    sf::Sprite earth(textures_[3]);
    sprites_.push_back(earth);

    sf::Sprite equation(textures_[2]);
    equation.setPosition(0.0f, 40.0f);
    equation.scale(1.0f, 1.0f);
    sprites_.push_back(equation);
}

/**
 * \brief creates all the texts to be drawn at the left of the window into the texts_ vector
*/
void WindowMain::prepareTextsLeftPanel()
{
    sf::Text text;
    text.setFont(font_); 
    text.setCharacterSize(30); 
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

    text.setString("Kaya identity:");
    text.setPosition(0.0f,0.0f);
    texts_.push_back(text);

    text.setString("Where:");
    text.setPosition(0.0f,110.0f);
    texts_.push_back(text);

    std::vector<std::string> var = {"- F is the global CO2 emissions from human sources",
    "- P is the global population", "- G is the world Gross domestic product",
    "- E is the global energy consumption"};

    double offset = 155.0f;
    text.setStyle(sf::Text::Regular);

    for(size_t i = 0; i < var.size(); i++)
    {
        text.setString(var[i]);
        text.setPosition(0.0f,offset + 120*i);
        texts_.push_back(text);
        
    }
}

/**
 * \brief creates all the texts to be drawn at the right of the window into the texts_ vector
*/
void WindowMain::prepareTextsRightPanel()
{
    sf::Text text;
    text.setFont(font_); 
    text.setCharacterSize(30); 
    text.setFillColor(sf::Color::White);

    std::vector<std::string> fact = {"Factors:",
    "- G/P is the production per person", "- E/G is the energy intensity of the economy",
    "- F/E is the carbon footprint of energy","Kaya Identity Scenario Prognosticator:",
    "P:","G/P:","E/G:","F/E:","%/year"};

    double offset = 40.0f;

    for(size_t i = 0; i < fact.size() - 1; i++)
    {
        if(i == 0 || i == 4)
        {
            text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        }

        if(i > 4)
        {
            text.setString(fact[fact.size() - 1]);
            text.setPosition(getSize().x / 2.0 + 120, offset*i);
            texts_.push_back(text);
        }

        text.setString(fact[i]);
        text.setPosition(getSize().x / 2.0, offset*i);
        texts_.push_back(text);
        text.setStyle(sf::Text::Regular);
    }
}

/**
 * \brief fills CheckPlot
 */
void WindowMain::preparePlot()
{
    std::vector<std::string> y_labels = {"CO2 emissions","Population","GDP","Energy consumption"};
    std::vector<std::string> titles = {"CO2 emissions","Population","Gross domestic product","Energy consumption"};
    double offset = 207.5f; 

    for(size_t i = 0; i < y_labels.size(); i++)
    {
        sf::Sprite* p_b = new sf::Sprite(textures_[0]);
        p_b->setPosition(0.0f, offset + 118 * i);
        p_b->scale(0.25f, 0.25f);
        checkplot_.addButton(p_b);
        checkplot_.addPlot(new WindowPlot(titles[i],sf::Color::White,sf::Color(100.f, 100.f, 100.f),font_,sf::Color::White,"Year",y_labels[i]));
    }
}

/**
 * \brief creates all the text fields to be drawn into the fields_ vector
*/
void WindowMain::prepareTextFields()
{
    double offset = 40.0f;

    for(size_t i = 0; i < 4; i++)
    {
        fields_.push_back(new TextField(10,getSize().x / 2.0 + 60,offset*i + 210));   
    }
}

/**
 * \brief returns the position of the mouse
 */
sf::Vector2f WindowMain::getMousePos()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*this);
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y));
    return mousePosF;
}

/**
 * \brief calls the handleInput function for each text fields in the vector fields
 * @param event the event
*/
void WindowMain::checkInput(sf::Event& event)
{
    for(auto& field : fields_)
    {
        field->handleInput(event);
    }
}

/**
 * \brief handles the outline color change for each text fields in the vector fields
 * @param ifPressed to get at which switch case the function is called
*/
void WindowMain::outlineColor(bool ifPressed)
{
    for(auto& field : fields_)
    {
        if(field->ifContains(getMousePos()))
        {
            field->setOutlineColor(true);
        }

        else if(!ifPressed)
        {
            field->setOutlineColor(false);
        }
    }
}

/**
 * \brief opens the main GUI window
*/
void WindowMain::run()
{
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
                       checkplot_.setColor(res,sf::Color::Red);
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

                    outlineColor(true);
                }

                    break;
                case sf::Event::MouseButtonReleased:
                {
                    outlineColor(false);
                }
                    break;
                default:
                    break;
            }

            checkInput(Event);
        }

        clear(sf::Color(255, 255, 255));
        drawAll();
        display();
    }
}