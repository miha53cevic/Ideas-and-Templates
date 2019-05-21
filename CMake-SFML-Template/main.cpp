#include "mihaSimpleSFML.hpp"

class demo : public mihaSimpleSFML
{
public:
private:
protected:
    virtual bool OnUserCreate()
    {
        return true;
    }

    virtual bool OnUserUpdate(sf::Time fElapsed)
    {

        return true;
    }
};

int main()
{
    demo a;
    a.Start();
    return 0;
}