#include <iostream>

int main(int argc, char* argv[]) 
{
    std::cout << "\nYou have entered " << argc << " arguments\n";
    std::cout << "Arguments passed:\n";

    for (int i = 0; i < argc; i++)
    {
        std::cout << argv[i] << "\n";
    }

    return 0;
}