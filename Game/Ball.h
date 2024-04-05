#include "Dependencies.h"

class ball : public sf::Drawable, public sf::Transformable
{
    private:
        float Size;
        int Divisions;
        float Min_Speed;
        float Max_Speed;
        float Speed;
        sf::VertexArray Vertices;
    public:

        float X_Speed;
        float Y_Speed;
        int direction;
        ball();
        ball(float xsize, int Difficulty, int xid, int width, int hight, sf::Color c)
        {
            Min_Speed = Difficulty * 10;
            Max_Speed = Difficulty+1 * 10 ;
            Size = xsize;


            direction = rand()%360;
            Speed = (rand() % (int)(Max_Speed-Min_Speed) + Min_Speed);

            X_Speed = (Speed * cos(direction)) / 10000.f ;
            Y_Speed = (Speed * sin(direction)) / 10000.f ;


            /*

            if(rand()%100 < 50)
            {
                X_Speed = (rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
            }
            else
            {
                X_Speed = -(rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
            }
            if(rand()%100 > 50)
            {
                Y_Speed = (rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
            }
            else
            {
                Y_Speed = -(rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
            }
            while(Y_Speed == X_Speed)
            {
               Y_Speed = (rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
            }

            */


            Divisions = 50;
            sf::VertexArray V(sf::TriangleFan, Divisions);
            float total = (2 * M_PI / (Divisions));
            Vertices = V;

            for(int i = 0; i < Divisions ; i++)
            {
                Vertices[i].position = sf::Vector2f(Size * cos ((total * i)),Size * sin((total * i)));
            }

            for (int i = 0; i < Divisions; i++)
            {
                Vertices[i].color = c;
            }
            this->setPosition(rand()%(int)(width-Size*2) + Size, rand()%(int)(hight-Size*2) + Size);
            
        }
        int GetDirection()
        {
            return direction;
        }
        void NextFrame(int width, int height)
        {
            if(this->getPosition().x < Size)
            {
                /*X_Speed = (rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
                if(rand()%100 < 50)
                {
                    Y_Speed = -(rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
                }
                else
                {
                    Y_Speed = (rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
                }*/
                direction = rand()%90 + (-45);

                
            }
            if(this->getPosition().x > width-Size)
            {
                /*X_Speed = -(rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
                if(rand()%100 < 50)
                {
                    Y_Speed = -(rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
                }
                else
                {
                    Y_Speed = (rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
                }*/
                direction = rand()%90 + 135;

            }
            if(this->getPosition().y < Size )
            {
                /*Y_Speed = (rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
                if(rand()%100 < 50)
                {
                    X_Speed = -(rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
                }
                else
                {
                    X_Speed = (rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
                }*/
                direction = rand()%90 + 45 ;

            }
            if(this->getPosition().y > height-Size)
            {
                /*Y_Speed = -(rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
                if(rand()%100 < 50)
                {
                    X_Speed = -(rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
                }
                else
                {
                    X_Speed = (rand() % (int)Max_Speed + (int)Min_Speed)/10000.f;
                }*/
                direction = rand()%90 + 225;
            }

            Speed = rand() % (int)(Max_Speed-Min_Speed) + Min_Speed;

            X_Speed = (Speed * cos(direction)) / 1000.f ;
            Y_Speed = (Speed * sin(direction)) / 1000.f ;

            this->move(X_Speed, Y_Speed);
        }
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform *= getTransform();
            target.draw(Vertices, states);
        }
        bool Collide(float x, float y)
        {
            // get distance between the point and circle's center
            // using the Pythagorean Theorem
            float distX = x - this->getPosition().x;
            float distY = y - this->getPosition().y;
            float distance = sqrt( (distX*distX) + (distY*distY) );

            // if the distance is less than the circle's
            // radius the point is inside!
            if (distance <= Size) {
                return true;
            }
            return false;
        }
        void ChangeColor(sf::Color c)
        {
            for (int i = 0; i < Size; i++)
            {
                Vertices[i].color = c;
            }
            
        }
};

class board : public sf::Drawable
{
    private:
        int Number;
        std::vector<ball> balls;        
    public:
        board();
        board(int xnumber, int Level, int width, int height)
        {            
            Number = xnumber;
            for (int i = 0; i < Number; i++)
            {
                int r = rand()%5;
                switch (r)
                {
                case 0:
                    balls.push_back(ball(rand()% 20+(40-Level), (Level), i, width, height, sf::Color::Magenta));
                    break;
                case 1:
                    balls.push_back(ball(rand()% 20+(40-Level), (Level), i, width, height, sf::Color::Red));
                    break;
                case 2:
                    balls.push_back(ball(rand()% 20+(40-Level), (Level), i, width, height, sf::Color::Blue));
                    break;
                case 3:
                    balls.push_back(ball(rand()% 20+(40-Level), (Level), i, width, height, sf::Color::Green));
                    break;
                case 4:
                    balls.push_back(ball(rand()% 20+(40-Level), (Level), i, width, height, sf::Color::Yellow));
                    break;
                default:
                    balls.push_back(ball(rand()% 20+(40-Level), (Level), i, width, height, sf::Color::Cyan));
                    break;
                }
            }
            
        }
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            for (int i = 0; i < Number; i++)
            {
                balls[i].draw(target, states);
            }
        }
        void NextFrame(int width, int height)
        {
            for (int i = 0; i < Number; i++)
            {
                balls[i].NextFrame(width, height);
            }
        }
        sf::Vector2i Click(int x, int y)
        {
            bool flag = false;
            int Score;
            for (int i = 0; i < Number; i++)
            {
                if(balls[i].Collide(x,y))
                {
                    flag = true;
                }
                if(flag && i < Number-1)
                {
                    balls[i] = balls[i+1];
                }
            }

            if(flag)
            {
                balls.pop_back();
                Number --;
                Score = true;
                
            }

            if(Number == 0)
            {
                return sf::Vector2i(true,Score);
            }
            else
            {
                return sf::Vector2i(false,Score);
            }
            
        }
};

class Game : public sf::Drawable
{
private:
    bool Is_alive;
    bool Win;
    int Score;
    int Combo;
    int Current_Level;
    float Time_left;
    sf::Clock Timer;
    std::vector<board> Game_Board;
public:
    Game(int width, int height)
    {
        Time_left = 10;
        Timer = sf::Clock();
        Current_Level = 1;
        Score = 0;
        Is_alive = true;
        Win = false;
        Combo = 0;

        Game_Board.push_back(board(Current_Level*5, Current_Level, width, height));
    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {    
        Game_Board[0].draw(target, states);
    }
    int GetScore()
    {
        return Score;
    }
    int GetLevel()
    {
        return Current_Level;
    }
    float GetTimer()
    {
        return Time_left = Time_left - Timer.restart().asSeconds();
    }
    bool GetLife()
    {
        return Is_alive;
    }
    void NextLevel(int width, int height)
    {
        Time_left = 10 + (Current_Level * 2);
        Current_Level ++;
        Game_Board[0] = board((5 + Current_Level*2), Current_Level, width, height);
    }
    int Click(int x, int y)
    {
        sf::Vector2i result = Game_Board[0].Click(x, y); 
        Win = result.x;

        if(result.y)
        {
            //res = true;
            Combo ++;
            Score += 100 * Combo;
        }
        else
        {
            //res = false;
            Combo = 0;
        }
        
        return result.y;//res;
    }
    int GetCombo()
    {
        return Combo;
    }
    void NextFrame(int width, int height)
    {
        if(Time_left > 0)
        {
            if(Win)
            {
                this->NextLevel(width, height);
                Win = false;
            }
            else
            {
                Game_Board[0].NextFrame(width, height);
            }
        }
        else
        {
            Is_alive = false;
        }
        
        
    }
};
