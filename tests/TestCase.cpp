#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "WindowMain.hpp"

TEST_CASE("1: Tests on Functions")
{
    REQUIRE(Linear(5,1,10) == 51);
    REQUIRE(Log(0,0,50) == 1);
    REQUIRE(Sqrt(0,0.5,50) == 0.25);
    REQUIRE(computePercentage(100,10) == 110);

    auto v = split("a,b,c",',');
    REQUIRE(v[0] == "a");
    REQUIRE(v[1] == "b");
    REQUIRE(v[2] == "c");
}

TEST_CASE("2: Tests on TextField")
{
    TextField T(5,5.0,5.0);
    REQUIRE(T.getStr().empty()); 
    REQUIRE(T.ifContains(sf::Vector2f(7.5f,7.5f)));
    REQUIRE(!T.ifContains(sf::Vector2f(0.0f,0.0f)));
    REQUIRE(T.getText().getString().isEmpty());
    REQUIRE(T.getText().getCharacterSize() == 20);
    REQUIRE(T.getText().getFillColor() == sf::Color::Black);
    REQUIRE(T.getText().getPosition().x == 5.0);
    REQUIRE(T.getText().getPosition().y == 5.0);
}

TEST_CASE("3: Tests on PlotData")
{
    PlotData d(sf::Color::White,1);
    d.addData(sf::Vector2<double>(-6.0,1.0));
    d.addData(sf::Vector2<double>(10.0,45.0));
    d.addData(sf::Vector2<double>(13.0,28.0));
    REQUIRE(d.getColor() == sf::Color::White);
    REQUIRE(d.getType() == 1);
    REQUIRE(d.getDataSize() == 3);
    REQUIRE(d(0).x == -6.0);
    REQUIRE(d(2).y == 28.0);
    REQUIRE(d.getRangeX().first == -6.0);
    REQUIRE(d.getRangeX().second == 13.0);
    REQUIRE(d.getRangeY().first == 1.0);
    REQUIRE(d.getRangeY().second == 45.0);
}

TEST_CASE("4: Tests on PlotAxes")
{
    sf::Font f;
    f.loadFromFile("../fonts/font.ttf");

    PlotAxes a(sf::Color::White,sf::Color::White,f,sf::Color::White,"x","y");
    std::pair<double,double> x(1.0,1.0);
    std::pair<double,double> y(2.0,2.0);
    a.setRangeX(x);
    a.setRangeY(y);
    REQUIRE(a.DIMENSION.x == 800.0);
    REQUIRE(a.DIMENSION.y == 600.0);
    REQUIRE(a.MARGIN.x == 40.0);
    REQUIRE(a.MARGIN.y == 20.0);
    REQUIRE(a.getRangeX() == x);
    REQUIRE(a.getRangeY() == y);
}

TEST_CASE("5: Tests on Plot")
{
    sf::Font f;
    f.loadFromFile("../fonts/font.ttf");

    PlotData d(sf::Color::White,1);
    d.addData(sf::Vector2<double>(-6.0,1.0));
    d.addData(sf::Vector2<double>(10.0,45.0));
    d.addData(sf::Vector2<double>(13.0,28.0));

    Plot p(sf::Color::White,sf::Color::White,f,sf::Color::White,"x","y");
    p.addData(d);
    REQUIRE(p.getDataSet().size() == 1);
    p.resetData();
    REQUIRE(p.getDataSet().size() == 0);
}

TEST_CASE("6: Tests on CheckCompute (extend to CheckPlot)")
{
    sf::Texture texture;
    texture.loadFromFile("../images/compute.png");

    CheckCompute c;
    std::shared_ptr<sf::Sprite> p_c(new sf::Sprite(texture));
    p_c->setPosition(50.0f, 50.0f);
    p_c->scale(0.22f, 0.22f);
    c.setButton(p_c);
    REQUIRE(c[sf::Vector2f(50.0f,50.0f)]);
    REQUIRE(!c[sf::Vector2f(7.5f,7.5f)]);

    auto ptr = c.getButton();
    REQUIRE(ptr->getPosition() == sf::Vector2f(50.0f,50.0f));
    REQUIRE(ptr->getScale() == sf::Vector2f(0.22f,0.22f));
}

TEST_CASE("7: Tests on WindowPlot")
{
    sf::Font f;
    f.loadFromFile("../fonts/font.ttf");

    WindowPlot w((variable) 0,"test",sf::Color::White,sf::Color::White,f,sf::Color::White,"x","y");
    REQUIRE(w.getPath() == "../data/population_fitted.csv");
    REQUIRE(w.getCoeff().first == 0.0826622448979592);
    REQUIRE(w.getCoeff().second == -159.187505102041);
    REQUIRE(!w.isOpen());
}