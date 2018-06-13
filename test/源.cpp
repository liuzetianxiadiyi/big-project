#include <iostream>
#include <vector>
#include "class.h"
#include <algorithm>
#include <stdlib.h>

using namespace std;
vector<MyTile> openTile;
vector<MyTile> closeTile;
MyTile colsCheck[10][10];	//´ý³õÊ¼»¯

vector<Position> FindWay(Position start, Position goal)
{
	MyTile& sta = colsCheck[start.x][start.y];
	sta.init(NULL,start, goal);
	openTile.push_back(sta);
	sta.setOpen();
	Position pos = start;
	//cout << "x=" << pos.x << " y=" << pos.y << endl;
	//system("pause");
	int count = 0;
	while (pos != goal)
	{
		cout << "x=" << pos.x << " y=" << pos.y << endl;
		//system("pause");
		colsCheck[pos.x][pos.y].setClose();
		closeTile.push_back(*openTile.begin());
		
		openTile.erase(openTile.begin());
		int flag_x, flag_y;
		for (int i = 0; i < 4; ++i)
		{
			switch (i)
			{
			case 0:
				flag_x = 1;
				flag_y = 0;
				break;
			case 1:
				flag_x = 0;
				flag_y = 1;
				break;
			case 2:
				flag_x = -1;
				flag_y = 0;
				break;
			case 3:
				flag_x = 0;
				flag_y = -1;
				break;
			}
			Position temp;
			temp.x = pos.x + flag_x;
			temp.y = pos.y + flag_y;
			if (colsCheck[temp.x][temp.y].available)
			{
				MyTile nextWay = colsCheck[temp.x][temp.y];
				nextWay.init(&colsCheck[pos.x][pos.y],temp,goal);
				nextWay.f_value -= count;
				vector<MyTile>::iterator iter;
				iter = find(closeTile.begin(), closeTile.end(), nextWay);
				//is not in closeTile
				if (iter == closeTile.end())
				{
					vector<MyTile>::iterator it;

					it = find(openTile.begin(), openTile.end(), nextWay);
					if (it != openTile.end())
					{
						if (nextWay < *it)
						{
							*it = nextWay;
							colsCheck[temp.x][temp.y] = nextWay;
							colsCheck[temp.x][temp.y].setOpen();
						}
					}
					else
					{
						//cout << "pushback in openTile"<<endl;
						colsCheck[temp.x][temp.y] = nextWay;
						colsCheck[temp.x][temp.y].setOpen();
						openTile.push_back(nextWay);
						nextWay.setOpen();
					}
				}
			}
		}
		sort(openTile.begin(), openTile.end());
		pos = openTile.begin()->GetPosition();
		putchar(' ');
		putchar(' ');
		for (int i = 0; i < 10; i++)
		{
			printf(" %2d", i);
		}
		for (int j = 0; j < 10; j++)
		{
			printf("\n\n%2d", j);
			for (int i = 0; i < 10; i++)
			{
				if (!colsCheck[j][i].available)
				{
					printf("  X");
				}
				else if (colsCheck[j][i].inClose)
				{
					printf("  C");
				}
				else if (colsCheck[j][i].inOpen)
				{
					printf("  O");
				}
				else if (colsCheck[j][i].out)
				{
					printf("   ");
				}
			}
		}
		printf("\n\n");
		//system("pause");
		char c;
		cin >> c;
		++count;
	}
	vector<Position> Way;
	Way.push_back(goal);

	MyTile* temp = &closeTile[closeTile.size()-1];
	do
	{
		Way.push_back(temp->GetPosition());
		cout << "x=" << temp->GetPosition().x << " y=" << temp->GetPosition().y << endl;
		temp = temp->GetParent();
	} while (temp!= NULL);

	reverse(Way.begin(), Way.end());

	return Way;
}

int main()
{
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 10; ++j)
		{
			colsCheck[i][j].available = true;
			colsCheck[i][j].serOut();
		}
	}
	colsCheck[3][5].available = false;
	colsCheck[4][5].available = false;
	colsCheck[5][5].available = false;
	cout << "start" << endl;
	//system("pause");
	FindWay(Position(5, 2), Position(4, 7));
	printf("out");
	system("pause");
}