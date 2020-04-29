#include "matrix.h"
// For checking matrix multiplications
// http://matrixmultiplication.xyz/

int main()
{
    matrix::fmat m(1, 4);
    m.dump();

    matrix::fmat m2(4, 4);
    std::vector<float> arr = { 1, 2, 3, 4,
                    5, 6, 7, 8,
                    9, 10, 11, 12,
                    13, 14, 15, 16 };
    m2.set(arr);
    m2.dump();

    auto m3 = m * m2;
    m3.dump();

#ifdef _WIN32
    system("pause");
#endif 

    return 0;
}