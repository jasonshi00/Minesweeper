#include <SFML\Graphics.hpp>
#include <iostream>
#include <utility>
#include <vector>
#include <random>
int main()
{
    void spawnBomb(int num);

    //16 tiles x 16 tiles
    sf::RenderWindow window(sf::VideoMode(800, 800), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);
    window.setTitle("Minesweeper Window");
    window.setPosition(sf::Vector2i(500, 100));

    sf::Texture tilesTexture;
    sf::Texture bomb;
    tilesTexture.loadFromFile("sprites/tile.png");
    bomb.loadFromFile("sprites/bomb.png");

    sf::RectangleShape tiles(sf::Vector2f(50.0f, 50.0f));
    tiles.setTexture(&tilesTexture);

    sf::RectangleShape tileList[16][16];
    std::vector<std::pair<int, int>> bombLoc;

    int bombAmount = 256;
    srand(time(0));

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            tileList[i][j] = tiles;
            bombLoc.push_back(std::make_pair(i, j));
        }
    }

    //creating bombs
    for (int i = 0; i < bombAmount; i++) {
        int randomInt = rand() % bombLoc.size();
        std::pair<int, int> p = bombLoc[randomInt];
        tileList[p.first][p.second].setTexture(&bomb);
        bombLoc.erase(std::remove(bombLoc.begin(), bombLoc.end(), p), bombLoc.end());
    }
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
                    tileList[i][j].setPosition(i * 50, j * 50);
                    window.draw(tileList[i][j]);
                }
            }
            window.display();
        }
    }

    return 0;
}
