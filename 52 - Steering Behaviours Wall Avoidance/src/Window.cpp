#include "Window.hpp"

Window::Window(const std::string& windowName) : window(sf::VideoMode(1920, 1080), windowName, sf::Style::Titlebar)
{
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    
    /*
    sf::View v;
    v.setSize(1920, 1080);
    v.zoom(0.5f);
    v.move(0, 250);
    window.setView(v);
     */
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

void Window::Draw(const sf::Vertex* vertices, std::size_t vertexCount, sf::PrimitiveType type)
{
    window.draw(vertices, vertexCount, type);
}

void Window::EndDraw()
{
    window.display();
}

sf::Vector2f Window::GetCentre() const
{
    return window.getView().getCenter();
}

sf::FloatRect Window::GetViewSpace() const
{
    const sf::View& view = GetView();
    const sf::Vector2f& viewCenter = view.getCenter();
    const sf::Vector2f& viewSize = view.getSize();
    sf::Vector2f viewSizeHalf(viewSize.x * 0.5f, viewSize.y * 0.5f);
    sf::FloatRect viewSpace(viewCenter - viewSizeHalf, viewSize);
    return viewSpace;
}

const sf::View& Window::GetView() const
{
    return window.getView();
}

void Window::SetView(const sf::View& view)
{
    window.setView(view);
}

bool Window::IsOpen() const
{
    return window.isOpen();
}
