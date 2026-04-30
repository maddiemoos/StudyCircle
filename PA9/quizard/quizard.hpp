#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Quizard
{
public:
	Quizard(sf::Font& font);

	void checkInput(const sf::Event& event);
	void draw(sf::RenderWindow& window);

private:
	std::vector<std::pair<std::string, std::string>> flashcards;

	int currentCard;
	bool showAnswer;

	sf::Text displayText;
	sf::RectangleShape displayBox;
};