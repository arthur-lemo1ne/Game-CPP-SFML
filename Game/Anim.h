#include "Dependencies.h"

class anim : public sf::Drawable
{
    private:
        sf::CircleShape circle;
        float currentRadius;
        float baseRadius;
    public:
        anim(int x, int y, float Start_Size)
        {
            circle.setPosition(x,y);
            circle.setRadius(Start_Size);
            circle.setFillColor(sf::Color::Transparent);
            circle.setOutlineThickness(3);
            circle.setOutlineColor(sf::Color::White);
            currentRadius = Start_Size;
            baseRadius = Start_Size;
        }
        void NextFrame()
        {
            currentRadius += 0.1f;
            circle.setRadius(currentRadius);
            circle.setOrigin(currentRadius,currentRadius);
        }
        bool NeedClear()
        {
            if(currentRadius > 80)
            {
                return true;
            }
            return false;
        }
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(circle, states);
        }
};