#include <iostream>

int main()
{
    // unsigned char is 1 BYTE in size can use uint8_t
    unsigned char a = 0b00001100; // 12 in binary
    unsigned char b = 0b00000001; //  1 in binary

    unsigned char c = a | b; // logical or

    std::cout << (int)c; // result 13

    return 0;
}
