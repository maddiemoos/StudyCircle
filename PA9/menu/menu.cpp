#include "menu.hpp"
#include <iostream>

//menu by Madison Manion
//used SFML tutorials to make menu
//used GeeksforGeeks and GameFromScratch examples to help make menu
//had to find tutorials for sfml version 3 since the sfml website uses some different logic/versions than what we needed, also asked chatgpt to "translate" if I wrote stuff in version 2 initially
//ChatGPT wrote numbers for positioning for graphics. asked "please provide correct positioning numbers for the SFML for (provide code) so it is centered on screen"
//asked "Please write a a function to center the words inside the rectangles of this menu (provide code)"
Menu::Menu() : quizard(font) 
{
    selectedOption = 0; //starting index of the currently selected menu option
    state = State::MAIN; //first state is the main menu

    if (!font.openFromFile("RobotoCondensed-VariableFont_wght.ttf")) //loads the font file in, provides error message if it didnt work
    {
        std::cout << "Failed to load font\n";
    }

    //each block below has the same features:
    //font
    //string(basically what it is going to display)
    //what is the size
    //what is the position on screen, doesn't really matter now because of later functions
    sf::Text pomodoro(font); 
    pomodoro.setString("Pomodoro Timer"); //text that is shown
    pomodoro.setCharacterSize(40); //font size
    pomodoro.setPosition(sf::Vector2f(200.f, 150.f)); //what is screen position, again doesnt matter

    sf::Text chat(font);
    chat.setString("Chat Room");
    chat.setCharacterSize(40);
    chat.setPosition(sf::Vector2f(200.f, 220.f));

    sf::Text quizard(font);
    quizard.setString("Quizard");
    quizard.setCharacterSize(40);
    quizard.setPosition(sf::Vector2f(200.f, 290.f));

    sf::Text heatmap(font);
    heatmap.setString("Heatmap");
    heatmap.setCharacterSize(40);
    heatmap.setPosition(sf::Vector2f(200.f, 360.f));

    sf::Text exit(font);
    exit.setString("Exit");
    exit.setCharacterSize(40);
    exit.setPosition(sf::Vector2f(200.f, 430.f));

    //each of these stores all of the menu options in a vector, which lets us loop through later
    options.push_back(pomodoro);

    options.push_back(chat);

    options.push_back(quizard);

    options.push_back(heatmap);

    options.push_back(exit);

    //new create rectangles function
    for (int i = 0; i < options.size(); i++) 
    {
        sf::Vector2f pos = options[i].getPosition(); //gets the text position to line up the rectangle with the text properly

        sf::RectangleShape box; 
        box.setSize(sf::Vector2f(300.f, 50.f)); //this is the size of each button 
        box.setPosition(sf::Vector2f(400.f - 150.f, pos.y - 10.f)); //centering the box by subtracting half of box width

        box.setFillColor(sf::Color(60, 60, 60)); // gray background
        box.setOutlineThickness(2.f); //outline around each button so it is more clean
        box.setOutlineColor(sf::Color::White); //set the color

        boxes.push_back(box); //stores the rectangle in a vector
    }

    for (int i = 0; i < options.size(); i++)
    {
        centerText(options[i], boxes[i]); //centers text in box
    }
}

void Menu::checkInput(sf::RenderWindow& window, sf::Event& event)
{
    if (state == State::QUIZARD)
    {
        quizard.checkInput(event);

        if (const auto* key = event.getIf<sf::Event::KeyPressed>())
        {
            if (key->code == sf::Keyboard::Key::Escape)
            {
                state = State::MAIN;
            }
        }
        return;
    }

    if (const auto* key = event.getIf<sf::Event::KeyPressed>()) //checks if a key is pressed
    {
        if (key->code == sf::Keyboard::Key::Down) //if the down arrow key is pressed
        {
            selectedOption++; //move down

            //had to do statice_cast because of mixing signed and unsigned
            if (selectedOption >= static_cast<int>(options.size())) //go back up to the top if we go to the last option
            {
                selectedOption = 0;
            }
        }

        if (key->code == sf::Keyboard::Key::Up) //if the up arrow is pressed
        {
            selectedOption--; //go up

            if (selectedOption < 0) //go to bottom option if we reach end of top
            {
                selectedOption = static_cast<int>(options.size()) - 1;
            }
        }

        if (key->code == sf::Keyboard::Key::Enter) //if the enter key is pressed
        {
            if (state == State::MAIN) //must be done in main menu
            {
                switch (selectedOption) 
                {
                case 0:
                    state = State::POMODORO; //go to pomodoro screen
                    break;

                case 1:
                    state = State::CHAT; //go to chat screen
                    break;

                case 2:
                    state = State::QUIZARD; //go to quizard screen
                    break;

                case 3:
                    state = State::HEATMAP; //go to heatmap screen
                    break;

                case 4:
                    window.close(); //exit
                    break;

                default:
                    break; //just in case
                }
            }

            else
            {
                state = State::MAIN; //return to main menu if we arent already
            }


        }
    }
}

void Menu::draw(sf::RenderWindow& window)
{

    if (state == State::QUIZARD)
    {
        quizard.draw(window);
        return;
    }

    // normal menu draw
    for (int i = 0; i < options.size(); i++)
    {
        if (i == selectedOption)
            boxes[i].setOutlineColor(sf::Color::Red);
        else
            boxes[i].setOutlineColor(sf::Color::White);

        window.draw(boxes[i]);
        options[i].setFillColor(sf::Color::White);
        window.draw(options[i]);
    }
}

void Menu::centerText(sf::Text& text, sf::RectangleShape& box)
{
    sf::FloatRect textBounds = text.getLocalBounds(); //gets the bounds of box

    //sets the origin to the center of the text
    text.setOrigin(sf::Vector2f(textBounds.position.x + textBounds.size.x / 2.f, textBounds.position.y + textBounds.size.y / 2.f));

    //gets the position/size of rectangle
    sf::FloatRect boxBounds = box.getGlobalBounds();

    //automatically moves the text to the center of the rectangle
    text.setPosition(sf::Vector2f(boxBounds.position.x + boxBounds.size.x / 2.f, boxBounds.position.y + boxBounds.size.y / 2.f ));
}
