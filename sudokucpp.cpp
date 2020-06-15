#include <iostream>

using namespace std;

bool recursive(int x, int y);

char origen[9][9];
char map[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };


int main()
{
	bool flag =1; // As the indicator for overlap.
	cout << "Please input a matrix with only 0~9 and '0' for blank space" << endl;
	// Input the matrix
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cin >> origen[i][j];
		}
	}
	flag = recursive(0, 0);
	if (!flag)
	{
		cout << "\n\nNo Answer!\n";
		return 0;
	}
	// Output formation
	cout << "-----------------------" << endl;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << origen[i][j]<<' ';
			if (j % 3 == 2) cout << "| ";
		}
		cout << endl;
		if (i % 3 == 2) cout << "-----------------------" << endl;
	}
	system("pause");
	return 0;
}

bool recursive(int x, int y)
{
	bool flag = true;
	if (origen[x][y] == '0')
	{
		// Recircly try one to nine
		for (int k = 0; k < 9; k++)
		{
			flag = true;
			// Check for row
			for (int i = 0; i < 9; i++)
			{
				if (origen[x][i] == map[k])
				{
					flag = false;
				}
			}
			// Check for line
			for (int i = 0; i < 9; i++)
			{
				if (origen[i][y] == map[k])
				{
					flag = false;
				}
			}
			// Check for 3 by 3
			// Actually, there are 5 times wasted since repeat checked.
			int x_s = x - x%3;
			int y_s = y - y % 3;
			for (int i = x_s; i < x_s + 3; i++)
			{
				for (int j = y_s; j < y_s + 3; j++)
				{
					if (origen[i][j] == map[k])
					{
						flag = false;
					}
				}
			}
			if (!flag)
			{
				if (k != 8) continue;
				else return false;
			}
			origen[x][y] = map[k];
			if (y + 1 < 9) flag = recursive(x, y + 1);
			else  if (x + 1 < 9) flag = recursive(x + 1, 0);
			else return true;
			if (!flag)
			{
				origen[x][y] = '0'; // If didn't work recover the place.
				continue;
			}
			return flag;
		}
		return flag;
	}
	else
	{
		if (y + 1 < 9) flag = recursive(x, y + 1);
		else  if (x + 1 < 9) flag = recursive(x + 1, 0);
		else return true;
		return flag;
	}
}