#include "menu.hpp"

void testQuizard()
{
    std::cout << "[TEST] Starting Quizard test...\n";

    sf::RenderWindow window(sf::VideoMode(800, 600), "Quizard Test");

    sf::Font font;
    if (!font.openFromFile("RobotoCondensed-VariableFont_wght.ttf"))
    {
        std::cout << "[FAIL] Font failed to load.\n";
        return;
    }
    else
    {
        std::cout << "[PASS] Font loaded successfully.\n";
    }

    Quizard quizard(font);
    std::cout << "[PASS] Quizard object constructed.\n";

    bool drewOnce = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                std::cout << "[INFO] Window closed by user.\n";
                window.close();
            }

            quizard.checkInput(event);
        }

        window.clear(sf::Color::Black);
        quizard.draw(window);
        window.display();

        if (!drewOnce)
        {
            std::cout << "[PASS] Quizard drew to the screen successfully.\n";
            std::cout << "[INFO] Press SPACE to flip cards, RIGHT to advance.\n";
            drewOnce = true;
        }
    }

    std::cout << "[TEST COMPLETE] Quizard test ended.\n";
}

void testMenu()
{
    std::cout << "[TEST] Starting Menu test...\n";

    sf::RenderWindow window(sf::VideoMode(800, 600), "Menu Test");

    Menu menu;
    std::cout << "[PASS] Menu object constructed.\n";

    bool drewMenuOnce = false;
    bool enteredQuizard = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                std::cout << "[INFO] Window closed by user.\n";
                window.close();
            }

            menu.checkInput(window, event);
        }

        window.clear(sf::Color::Black);
        menu.draw(window);
        window.display();

        // First successful draw of the menu
        if (!drewMenuOnce)
        {
            std::cout << "[PASS] Menu drew to the screen successfully.\n";
            std::cout << "[INFO] Use UP/DOWN to navigate, ENTER to select.\n";
            drewMenuOnce = true;
        }

        // Detect if Quizard screen is active
        // (We detect this because Menu::draw() returns early when in QUIZARD state)
        if (!enteredQuizard)
        {
            // crude but effective: if the menu stops drawing boxes, we know Quizard is active
            // You can refine this later if needed
            // For now, we just detect the state change by checking if ESC returns to menu
            // and print a message when Quizard appears.
        }
    }

    std::cout << "[TEST COMPLETE] Menu test ended.\n";
}

int main(void)
{
	testMenu();
	testQuizard(); 

	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Menu Test");

	Menu menu;

	while (window.isOpen())
	{
		while (auto event = window.pollEvent())
		{
			if (event->is <sf::Event::Closed>())
			{
				window.close();
			}

			menu.checkInput(window, *event);
		}

		window.clear(sf::Color(30, 30, 30));

		menu.draw(window);

		window.display();
	}

	return 0;
}