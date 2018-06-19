#include "Window.hpp"

Window::Window(const std::string& windowName) : window(sf::VideoMode(1920, 1080), windowName, sf::Style::Titlebar)
{
    window.setVerticalSyncEnabled(true);
}

void Window::Update()
{
    sf::Event event;
    if (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void Window::BeginDraw()
{
    window.clear(sf::Color::White);
}

void Window::Draw(const sf::Drawable& drawable)
{
    window.draw(drawable);
}

void Window::EndDraw()
{
    window.display();
}

sf::Vector2u Window::GetCentre() const
{
    sf::Vector2u size = window.getSize();
    
    return sf::Vector2u(size.x / 2, size.y / 2);
}

sf::FloatRect Window::GetViewSpace() const
{
    sf::Vector2f viewCenter(window.getView().getCenter());
    sf::Vector2f viewSize(window.getView().getSize());
    sf::Vector2f viewSizeHalf(viewSize.x / 2, viewSize.y / 2);
    sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
    
    return viewSpace;
}

bool Window::IsOpen() const
{
    return window.isOpen();
}
