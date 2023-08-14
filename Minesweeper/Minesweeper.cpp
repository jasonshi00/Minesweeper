#include <SFML\Graphics.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode(512, 512), "Minesweeper", sf::Style::Close | sf::Style::Resize);

    while (window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == evnt.Closed) {
                window.close();
            }
        }
    }

    return 0;
}
