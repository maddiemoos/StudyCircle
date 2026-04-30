#include "quizard.hpp"

Quizard::Quizard(sf::Font& font) : currentCard(0), showAnswer(false), displayText(font), displayBox(sf::Vector2f(500.f, 200.f))
{
    flashcards.push_back({ "2 + 2?", "4" });
    flashcards.push_back({ "Capital of France?", "Paris" });
    flashcards.push_back({ "5 * 5?", "25" });

    displayText.setFont(font);
    displayText.setCharacterSize(40);
    displayText.setFillColor(sf::Color::White);

    displayBox.setPosition(sf::Vector2f(150.f, 200.f));
    displayBox.setOrigin(displayBox.getSize() / 2.f);
    displayBox.setPosition(sf::Vector2f(400.f, 300.f));
    displayBox.setFillColor(sf::Color(60, 60, 60));
    displayBox.setOutlineThickness(2.f);
    displayBox.setOutlineColor(sf::Color::White);
}

void Quizard::checkInput(const sf::Event& event)
{
    if (const auto* key = event.getIf<sf::Event::KeyPressed>())
    {
        if (key->code == sf::Keyboard::Key::Space)
        {
            showAnswer = !showAnswer;
        }

        if (key->code == sf::Keyboard::Key::Right)
        {
            currentCard++;

            if (currentCard >= flashcards.size())
                currentCard = 0;

            showAnswer = false;
        }
    }
}

void Quizard::draw(sf::RenderWindow& window)
{
    if (flashcards.empty())
        return;

    std::string content;

    if (showAnswer)
    {
        content = flashcards[currentCard].second;
    }
    else
    {
        content = flashcards[currentCard].first;
    }

    displayText.setString(content);
 
    displayText.setString(content);

    auto bounds = displayText.getLocalBounds();

    displayText.setOrigin(bounds.getCenter());
    displayText.setPosition(displayBox.getPosition());

    window.draw(displayBox);
    window.draw(displayText);
}