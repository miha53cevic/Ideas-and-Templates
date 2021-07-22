#include <vector>
#include <cstdio>
#include <queue>
#include <utility>

#define W 16
#define H 8

// Globals
std::string map;
int R[4] = { 0, 1, 0, -1 };
int C[4] = { -1, 0, 1, 0 };
std::vector<bool> visited;

int index(int x, int y)
{
    return (y * W) + x;
}

bool hitEdge(int x, int y)
{
    if (x < 0 || x >= W || y < 0 || y >= H)
        return true;
    else return false;
}

bool BFS(int x, int y)
{
    std::queue<std::pair<int, int>> q;
    q.push({ x, y });
    visited[index(x, y)] = true;

    while (!q.empty())
    {
        printf("Queue.size: %d\n", q.size());

        auto p = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int xx = p.first + R[i];
            int yy = p.second + C[i];

            if (hitEdge(xx, yy))
                return false;

            if (!visited[index(xx, yy)] && map[index(xx, yy)] == '.')
            {
                visited[index(xx, yy)] = true;
                q.push({ xx, yy });
            }
        }
    }

    return true;
}

int main()
{
    map += "###########.....";
    map += "#.........#.....";
    map += "#..#......#.....";
    map += "#..######.#.....";
    map += "####....#.#.....";
    map += "........#.#.....";
    map += "........###.....";
    map += "................";

    visited.resize(map.length(), false);

    // Draw map
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
            printf("%c", map.at(index(j, i)));

        printf("\n");
    }

    // If BFS returns false that menas a hole exists
    if (!BFS(1, 1))
        printf("Found hole");

#ifdef _WIN32
    system("pause");
#endif
    return 0;
}