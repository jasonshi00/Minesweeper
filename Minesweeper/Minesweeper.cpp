#include <SFML\Graphics.hpp>
#include <iostream>
int main()
{
    //16 tiles x 16 tiles
    sf::RenderWindow window(sf::VideoMode(800, 800), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);
    window.setTitle("Minesweeper Window");
    window.setPosition(sf::Vector2i(500, 100));

    sf::Texture tilesTexture;
    sf::RectangleShape tiles(sf::Vector2f(50.0f, 50.0f));
    tilesTexture.loadFromFile("sprites/tile.png");
    tiles.setTexture(&tilesTexture);

    while (window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            //events
            switch (evnt.type)
            {
                //mouse click event
                case sf::Event::MouseButtonPressed:
                    if (evnt.mouseButton.button == sf::Mouse::Left)
                    {
                        std::cout << "the right button was pressed" << std::endl;
                        std::cout << "mouse x: " << evnt.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << evnt.mouseButton.y << std::endl;
                    }
                    break;
                //close event
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
            window.clear(sf::Color::White);
            for (int i = 0; i < 16; i++) {
                for (int j = 0; j < 16; j++) {
                    tiles.setPosition(i * 50, j * 50);
                    window.draw(tiles);
                }
            }
            window.display();
        }
    }

    return 0;
}
