#pragma once
#include "../quizard/quizard.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

//menu by Madison Manion
//looked up on GeeksforGeeks the best way to do a menu, enum is best way because of the submenus. we need states
enum class State //enum class defines states of the program
{
	MAIN, POMODORO, CHAT, QUIZARD, HEATMAP //main menu screen, pomodoro timer, chat room, and quizzer and heatmap
};

class Menu //handles everything related to menu and screen switching
{
public:

	Menu(); //constructor

	void checkInput(sf::RenderWindow& window, sf::Event& event); //handles the input from user keyboard or mouse

	void draw(sf::RenderWindow& window); //draws/displays on the screen; text, the menu itself, etc.
	
private:

	sf::Font font; //we store what font we are using here

	std::vector<sf::Text> options; //lists menu options
	std::vector<sf::RectangleShape> boxes; //added after menu started working, make it more cosmetic

	int selectedOption; //tracks which menu option is chosen

	State state; //stores current state of the program, so main, pomodoro, etc.

	void centerText(sf::Text& text, sf::RectangleShape& box); //ChatGPT helped with this, was unsure how to do this for cosmetics

	Quizard quizard;
};

