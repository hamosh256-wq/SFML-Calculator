#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

double calculate(double a, double b, char op)
{
    switch (op)
    {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return (b != 0) ? a / b : 0;
    default: return 0;
    }
}

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({600, 400}),
        "SFML Calculator"
    );

    double a = 0, b = 0;
    char op = '+';
    bool editingA = true;

    sf::Font font;
    if (!font.openFromFile("arial.ttf"))
    {
        std::cout << "Font not found!\n";
        return 1;
    }

    sf::Text text(font, "", 20);
    text.setFillColor(sf::Color::White);
    text.setPosition({30.f, 30.f});

    sf::RectangleShape button({160.f, 50.f});
    button.setPosition({30.f, 250.f});
    button.setFillColor(sf::Color::Blue);

    sf::Text buttonText(font, "CALCULATE", 18);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setPosition({55.f, 262.f});

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            // إدخال من الكيبورد
            if (auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                // TAB
                if (key->code == sf::Keyboard::Key::Tab)
                    editingA = !editingA;

                // BACKSPACE
                if (key->code == sf::Keyboard::Key::Backspace)
                {
                    if (editingA) a = 0;
                    else b = 0;
                }

                // العمليات
                if (key->code == sf::Keyboard::Key::Add) op = '+';
                if (key->code == sf::Keyboard::Key::Subtract) op = '-';
                if (key->code == sf::Keyboard::Key::Multiply) op = '*';
                if (key->code == sf::Keyboard::Key::Divide) op = '/';

                // أرقام 0-9
                for (int i = 0; i <= 9; i++)
                {
                    if (key->code == static_cast<sf::Keyboard::Key>(
                        static_cast<int>(sf::Keyboard::Key::Num0) + i))
                    {
                        if (editingA)
                            a = a * 10 + i;
                        else
                            b = b * 10 + i;
                    }
                }
            }

            // زر الحساب
            if (auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
            {
                sf::Vector2f pos(
                    mouse->position.x,
                    mouse->position.y
                );

                if (button.getGlobalBounds().contains(pos))
                {
                    double result = calculate(a, b, op);

                    text.setString(
                        "Editing: " + std::string(editingA ? "A" : "B") +
                        "\nA = " + std::to_string(a) +
                        "\nB = " + std::to_string(b) +
                        "\nOperation = " + std::string(1, op) +
                        "\nResult = " + std::to_string(result) +
                        "\n\n[TAB] Switch A/B\n[+ - * /] Change Op"
                    );
                }
            }
        }

        window.clear(sf::Color::Black);
        window.draw(button);
        window.draw(buttonText);
        window.draw(text);
        window.display();
    }

    return 0;
}
؛