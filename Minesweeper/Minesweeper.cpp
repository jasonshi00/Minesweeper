#include <SFML\Graphics.hpp>
#include <iostream>
#include <utility>
#include <vector>
#include <random>
void clearEmptySpaces(int x, int y, sf::RectangleShape tileListShow[][16], int tileListHide[][16], sf::Texture* numTexture, sf::Texture &emptyTile);
int main()
{

    //16 tiles x 16 tiles
    sf::RenderWindow window(sf::VideoMode(800, 800), "Minesweeper", sf::Style::Close | sf::Style::Titlebar);
    window.setTitle("Minesweeper Window");
    window.setPosition(sf::Vector2i(500, 100));

    sf::Texture tilesTexture;
    sf::Texture bombTexture;
    sf::Texture emptyTileTexture;
    sf::Texture flagTexture;
    sf::Texture numTexture[8];
    tilesTexture.loadFromFile("sprites/tile.png");
    bombTexture.loadFromFile("sprites/bomb.png");
    emptyTileTexture.loadFromFile("sprites/emptytile.png");
    numTexture[0].loadFromFile("sprites/1.png");
    numTexture[1].loadFromFile("sprites/2.png");
    numTexture[2].loadFromFile("sprites/3.png");
    numTexture[3].loadFromFile("sprites/4.png");
    numTexture[4].loadFromFile("sprites/5.png");
    numTexture[5].loadFromFile("sprites/6.png");
    numTexture[6].loadFromFile("sprites/7.png");
    numTexture[7].loadFromFile("sprites/8.png");
    flagTexture.loadFromFile("sprites/flag.png");
    
    sf::RectangleShape tiles(sf::Vector2f(50.0f, 50.0f));
    tiles.setTexture(&tilesTexture);

    sf::Text gameOverText;
    sf::Font font;
    font.loadFromFile("font/pixel.ttf");
    gameOverText.setFont(font);
    gameOverText.setCharacterSize(60);
    gameOverText.setFillColor(sf::Color::Red);

    sf::RectangleShape tileListShow[16][16];
    int tileListHidden[16][16]; // 0: emptyTile, 1-8: nums, 9: bombs
    std::vector<std::pair<int, int>> bombLoc;

    bool gameOver = false;

    int bombAmount = 20;
    srand(time(0));

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            tileListShow[i][j] = tiles;
            bombLoc.push_back(std::make_pair(i, j));
            tileListHidden[i][j] = 0;
        }
    }

    //creating bombs
    for (int i = 0; i < bombAmount; i++) {
        int randomInt = rand() % bombLoc.size();
        std::pair<int, int> p = bombLoc[randomInt];
        //tileListShow[p.first][p.second].setTexture(&bombTexture);
        tileListHidden[p.first][p.second] = 9;
        bombLoc.erase(std::remove(bombLoc.begin(), bombLoc.end(), p), bombLoc.end());
        std::cout << "bomb at: " << p.first << " " << p.second << std::endl;
    }
    //creates number on board
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            int totalBomb = 0;
            if (tileListHidden[i][j] == 9) continue;
            if (i == 0 && j == 0) {
                totalBomb += (tileListHidden[i + 1][j] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i + 1][j + 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i][j + 1] == 9) ? 1 : 0;
            }
            else if (i == 0 && j == 15) {
                totalBomb += (tileListHidden[i + 1][j] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i + 1][j - 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i][j - 1] == 9) ? 1 : 0;
            }
            else if (i == 15 && j == 0) {
                totalBomb += (tileListHidden[i][j + 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i - 1][j] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i - 1][j + 1] == 9) ? 1 : 0;
            }
            else if (i == 15 && j == 15) {
                totalBomb += (tileListHidden[i - 1][j] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i][j - 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i - 1][j - 1] == 9) ? 1 : 0;
            }
            else if (i == 0) {
                totalBomb += (tileListHidden[i][j - 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i][j + 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i + 1][j - 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i + 1][j] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i + 1][j + 1] == 9) ? 1 : 0;
            }
            else if (i == 15) {
                totalBomb += (tileListHidden[i][j - 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i][j + 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i - 1][j - 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i - 1][j] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i - 1][j + 1] == 9) ? 1 : 0;
            }
            else if (j == 0) {
                totalBomb += (tileListHidden[i - 1][j] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i + 1][j] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i - 1][j + 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i][j + 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i + 1][j + 1] == 9) ? 1 : 0;
            }
            else if (j == 15) {
                totalBomb += (tileListHidden[i - 1][j] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i + 1][j] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i - 1][j - 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i][j - 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i + 1][j - 1] == 9) ? 1 : 0;
            }
            else {
                totalBomb += (tileListHidden[i - 1][j - 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i][j - 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i + 1][j - 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i - 1][j] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i + 1][j] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i - 1][j + 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i][j + 1] == 9) ? 1 : 0;
                totalBomb += (tileListHidden[i + 1][j + 1] == 9) ? 1 : 0;
            }
            tileListHidden[i][j] = totalBomb;
            totalBomb = 0;
        }
    }

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            std::cout << tileListHidden[i][j];
        }
        std::cout << std::endl;
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
                    if (evnt.mouseButton.button == sf::Mouse::Left && !gameOver)
                    {
                        int x = int(evnt.mouseButton.x) / 50;
                        int y = int(evnt.mouseButton.y) / 50;
                        switch (tileListHidden[y][x])
                        {
                            case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
                                clearEmptySpaces(x, y, tileListShow, tileListHidden, numTexture, emptyTileTexture);
                                break;
                            case 9:
                                tileListShow[y][x].setTexture(&bombTexture);
                                gameOverText.setString("Game Over: You Lose");
                                gameOverText.setPosition(window.getSize().x / 2.0f - gameOverText.getGlobalBounds().width / 2.0f,
                                                         window.getSize().y / 2.0f - gameOverText.getGlobalBounds().height / 2.0f);
                                gameOver = true;
                                break;
                        }
                    }
                    if (evnt.mouseButton.button == sf::Mouse::Right && !gameOver)
                    {
                        int x = int(evnt.mouseButton.x) / 50;
                        int y = int(evnt.mouseButton.y) / 50;
                        if (tileListShow[y][x].getTexture() == &tilesTexture) {
                            tileListShow[y][x].setTexture(&flagTexture);
                        }
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
                    tileListShow[i][j].setPosition(j * 50, i * 50);
                    window.draw(tileListShow[i][j]);
                }
            }
            if (gameOver) {
                window.draw(gameOverText);
            }

            window.display();
        }
    }
    return 0;
}

void clearEmptySpaces(int x, int y, sf::RectangleShape tileListShow[][16], int tileListHide[][16], sf::Texture* numTexture, sf::Texture &emptyTile) {
    if (x == -1 || x == 16 || y == -1 || y == 16) {
        return;
    }
    else if (tileListHide[y][x] > 0 && tileListHide[y][x] < 9) {
        tileListShow[y][x].setTexture(&numTexture[tileListHide[y][x] - 1]);
        return;
    }
    else if (tileListShow[y][x].getTexture() == &emptyTile) {
        return;
    }
    else {
        tileListShow[y][x].setTexture(&emptyTile);
        
        clearEmptySpaces(x - 1, y - 1, tileListShow, tileListHide, numTexture, emptyTile);
        clearEmptySpaces(x, y - 1, tileListShow, tileListHide, numTexture, emptyTile);
        clearEmptySpaces(x + 1, y - 1, tileListShow, tileListHide, numTexture, emptyTile);
        clearEmptySpaces(x - 1, y, tileListShow, tileListHide, numTexture, emptyTile);
        clearEmptySpaces(x + 1, y, tileListShow, tileListHide, numTexture, emptyTile);
        clearEmptySpaces(x - 1, y + 1, tileListShow, tileListHide, numTexture, emptyTile);
        clearEmptySpaces(x, y + 1, tileListShow, tileListHide, numTexture, emptyTile);
        clearEmptySpaces(x + 1, y + 1, tileListShow, tileListHide, numTexture, emptyTile);
        
    }
}


