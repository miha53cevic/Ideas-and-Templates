/*
    Author: Mihael Petrièeviæ
    Email: miha53cevic@gmail.com
    Date: 29.4.2020.
*/
#pragma once
#include <iostream>
#include <vector>

// https://en.wikipedia.org/wiki/Affine_transformation

namespace matrix
{
    template<typename T>
    class mat
    {
    public:
        mat(int rows, int cols)
        {
            m_rows = rows;
            m_cols = cols;
            m_data.resize(rows * cols);

            identity();
        }

        void dump()
        {
            for (int i = 0; i < m_rows; i++)
            {
                std::cout << "[";
                for (int j = 0; j < m_cols; j++)
                {
                    std::cout << m_data[index(j, i)];
                    if (j != m_cols - 1) std::cout << " ";
                }
                std::cout << "]\n";
            }
            std::cout << "\n";
        }

        void identity()
        {
            for (int i = 0; i < m_rows; i++)
            {
                for (int j = 0; j < m_cols; j++)
                {
                    if (i == j) m_data[index(j, i)] = 1;
                    else        m_data[index(j, i)] = 0;
                }
            }
        }

        void set(std::vector<T> array)  { m_data = std::move(array);   }
        void set(int x, int y, T value) { m_data[index(x, y)] = value; }
        T    get(int x, int y)          { return m_data[index(x, y)];  }

        void mult(T scalar)
        {
            for (int i = 0; i < m_rows; i++)
            {
                for (int j = 0; j < m_cols; j++)
                {
                    m_data[index(j, i)] *= scalar;
                }
            }
        }

        mat<T> mult(mat<T> rb)
        {
            if (m_cols != rb.m_rows)
                std::cout << "Columns of the 1st matrix must equal the number of rows of the 2nd matrix!\n";
            else
            {
                // the result will have the same number of rows as the 1st matrix,
                // and the same number of columns as the 2nd matrix.
                mat<T> result(m_rows, rb.m_cols);
                
                // Korišten algoritam od coding train-a za množenje matrica
                // https://github.com/CodingTrain/website/blob/master/CodingChallenges/CC_112_3D_Rendering/Processing/CC_112_3D_Rendering/matrix.pde
                // Remember that 2DArray[y][x] dok je index(x, y)
                for (int i = 0; i < m_rows; i++)
                {
                    for (int j = 0; j < rb.m_cols; j++)
                    {
                        T sum = 0;
                        for (int k = 0; k < m_cols; k++)
                        {
                            sum += get(k, i) * rb.get(j, k);
                        }
                        result.set(j, i, sum);
                    }
                }

                return result;
            }
            // If error return identity matrix
            return mat<T>(m_rows, rb.m_cols);
        }

        mat<T> operator*(const mat<T>& rb) { return mult(rb);    }
        void operator=  (const mat<T>& rb) { m_data = rb.m_data; }

    private:
        int m_rows;
        int m_cols;
        std::vector<T> m_data;

    private:
        int index(int x, int y) { return (m_cols * y) + x;     }
    };

    typedef mat<int>    imat;
    typedef mat<float>  fmat;
    typedef mat<double> dmat;
};

