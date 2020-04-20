#include "mihaSimpleSFML.h"
#include <vector>

constexpr int SPEED = 100;

struct sSpline
{
    std::vector<sf::Vector2f> points;
    sf::Vector2f getSplinePoint(float t)
    {
        // Check this graph! We can determine which points belong to which curve by looking at the t value 
        // https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline#/media/File:Catmull-Rom_Spline.png
        int p1 = (int)t + 1;
        int p2 = p1 + 1;
        int p3 = p2 + 1;
        int p0 = p1 - 1;

        // If we have more than 4 points we have to map t back to {0, 1}
        // So if we have for example if t=5.3 we only want the 0.3 
        t = t - (int)t;

        // Cache powers of t
        float tt = t * t;
        float ttt = tt * t;

        // Influence graphs
        // Gotten from: https://www.lucidarme.me/catmull-rom-splines/
        // Multiply the scalar with the matrix and then with the 4x4 matrix and you get 4 graphs
        // After that multiply each point by its graph (the Calculate point part)
        float q0 = -0.5*ttt + tt - 0.5*t;
        float q1 = 1.5*ttt - 2.5*tt + 1;
        float q2 = -1.5*ttt + 2*tt + 0.5*t;
        float q3 = 0.5*ttt - 0.5*tt;

        // Calculate point
        float x = points[p0].x * q0 + points[p1].x * q1 + points[p2].x * q2 + points[p3].x * q3;
        float y = points[p0].y * q0 + points[p1].y * q1 + points[p2].y * q2 + points[p3].y * q3;

        return { x, y };
    }
};

class Spline : public mihaSimpleSFML
{
public:
    Spline() {}

private:
    sSpline spline;
    int selectedPoint = 0;

protected:
    void Event(sf::Event e) override
    {
        // Switch control points
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Q)
        {
            selectedPoint += (selectedPoint > 0) ? -1 : 0;
        }
        else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::E)
        {
            selectedPoint += (selectedPoint < spline.points.size() - 1) ? 1 : 0;
        }
    }

protected:
    bool OnUserCreate() override
    {
        spline.points = { {100, 240}, {200, 240}, {300, 240}, {400, 240}, {500, 240}, {600, 240} };

        return true;
    }

    bool OnUserUpdate(sf::Time elapsed) override
    {
        // Draw the curve
        sf::CircleShape pixel;
        pixel.setRadius(1.0f);
        pixel.setFillColor(sf::Color::White);
        // t should be between every 2 points withouth the corner cases so -2.0f
        for (float t = 0.0f; t < spline.points.size() - 3.0f; t += 0.001f)
        {
            pixel.setPosition(spline.getSplinePoint(t));
            Draw(pixel);
        }

        // Draw the control points
        sf::RectangleShape controlPoint;
        controlPoint.setFillColor(sf::Color::Yellow);
        controlPoint.setSize({ 20, 20 });
        controlPoint.setOrigin({ 10, 10 });
        for (int i = 0; i < spline.points.size(); i++)
        {
            controlPoint.setPosition(spline.points[i]);
            if (i == selectedPoint) controlPoint.setFillColor(sf::Color::Red);
            else                    controlPoint.setFillColor(sf::Color::Yellow);
            Draw(controlPoint);
        }

        // Move control points
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            spline.points[selectedPoint].y -= SPEED * elapsed.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            spline.points[selectedPoint].x -= SPEED * elapsed.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            spline.points[selectedPoint].y += SPEED * elapsed.asSeconds();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            spline.points[selectedPoint].x += SPEED * elapsed.asSeconds();
        }

        return true;
    }

};

int main()
{
    Spline app;
    app.Construct(640, 480, L"Spline");
    app.Start();

    return 0;
}