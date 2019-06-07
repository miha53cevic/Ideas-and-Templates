#include <iostream>
#include <vector>

struct sNode
{
	sNode(unsigned int x, unsigned int y)
	{
		this->x = x;
		this->y = y;

		bVisited = false;
	}

	int x, y;
	std::vector<sNode> vecNextMoves;
	bool bVisited;
};

void DrawMap(const std::vector<sNode>& path)
{
	std::cout << "\n\n\n";

	char map[8][8];

	for (int i = 0; i < (int)path.size(); i++)
	{
		map[path.at(i).y][path.at(i).x] = 'o';
	}

	std::cout << "\t";

	for (int i = 0; i < 8; i++)
	{
		std::cout << i + 1 << " ";
	}
	std::cout << "\n";

	for (int i = 0; i < 8; i++)
	{
		std::cout << i + 1 << "\t";

		for (int j = 0; j < 8; j++)
		{
			if (map[i][j] == 'o')	std::cout << "o ";
			else					std::cout << "# ";
		}
		std::cout << "\n";
	}

	std::cout << "\n\n\n";
}

void getMoves(sNode* current, const int BoardX, const int BoardY, const std::vector<sNode>& PlayedMoves)
{
	int x = current->x;
	int y = current->y;

	// Left
	if (x - 2 >= 0)
	{
		// Up
		if (y - 1 >= 0)		current->vecNextMoves.push_back(sNode(x - 2, y - 1));
		// Down
		if (y + 1 < BoardY) current->vecNextMoves.push_back(sNode(x - 2, y + 1));
	}

	// Right
	if (x + 2 < BoardX)
	{
		// Up
		if (y - 1 >= 0)		current->vecNextMoves.push_back(sNode(x + 2, y - 1));
		// Down
		if (y + 1 < BoardY) current->vecNextMoves.push_back(sNode(x + 2, y + 1));
	}
	// Up
	if (y - 2 >= 0)
	{
		// Left
		if (x - 1 >= 0)		current->vecNextMoves.push_back(sNode(x - 1, y - 2));
		// Right
		if (x + 1 < BoardX) current->vecNextMoves.push_back(sNode(x + 1, y - 2));
	}
	// Down
	if (y + 2 < BoardY)
	{
		// Left
		if (x - 1 >= 0)		current->vecNextMoves.push_back(sNode(x - 1, y + 2));
		// Right
		if (x + 1 < BoardX) current->vecNextMoves.push_back(sNode(x + 1, y + 2));
	}

	// Check if any of the nextMoves are the same as any of the previous
	for (auto iter = PlayedMoves.begin(); iter != PlayedMoves.end(); iter++)
	{
		for (auto iter2 = current->vecNextMoves.begin(); iter2 != current->vecNextMoves.end();)
		{
			if (iter->x == iter2->x && iter->y == iter2->y)
			{
				// Erase returns pointer to next element in vector after deletion
				iter2 = current->vecNextMoves.erase(iter2);
			}
			else iter2++;
		}
	}
}

int main()
{
	// Board Size
	int BoardX = 8;
	int BoardY = 8;

	// Current Path of moves
	std::vector<sNode> vecPlayedMoves;

	// Starting move
	sNode current(0, 0);
	int i = 0;
	//while (vecPlayedMoves.size() != BoardX * BoardY)
	while(i < 64)
	{
		i++;
		
		// Get moves from current only if NextMoves weren't already calculated
		if (current.vecNextMoves.empty())
			getMoves(&current, BoardX, BoardY, vecPlayedMoves);

		// No next moves avaiable go back to previous move
		if (current.vecNextMoves.size() == 0)
		{
			// Find last node with avaiable NextMoves
			for (int i = (int)vecPlayedMoves.size() - 1; i >= 0 ; i--)
			{
				if (vecPlayedMoves.at(i).vecNextMoves.size() != 0)
				{
					current = vecPlayedMoves.at(i);

					// Pop because you insert it into the vector later again
					vecPlayedMoves.pop_back();

					break;
				}
				else
				{
					vecPlayedMoves.pop_back();
				}
			}
		}
		else
		{
			for (auto &i : current.vecNextMoves)
			{
				// If the move has already been made in a previous turn skip it
				if (i.bVisited)
					continue;
				else
				{
					i.bVisited = true;

					// Next move becomes the current one
					vecPlayedMoves.push_back(current);

					current = i;

					break;
				}
			}
		}
	}

	std::cout << "Algorithm executed successfully!\n";

	// Ispis kranjeg puta
	for (auto i : vecPlayedMoves)
	{
		std::cout << "X = " << i.x << "\tY = " << i.y << "\n";
	}
	std::cout << "Moves made = " << vecPlayedMoves.size();

	DrawMap(vecPlayedMoves);
	std::cout << vecPlayedMoves.at(vecPlayedMoves.size() - 1).vecNextMoves.size();
	
	system("pause");
	return 0;
}