#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
bool flag[7] = { false };
int val = 100;			//initializing some terms globally to use them in recursive function
int temp = 0;
int getBestPath(int** graph, int s, int dest, int b) {
	flag[s] = true;					//marking visited nodes
	if (graph[s][dest] == 0) {
		for (int i = 1; i < b; ++i) {
			if (flag[i] == false && graph[s][i] != 0) {
				if (val > graph[s][i])
				{
					val = graph[s][i];
				}
				getBestPath(graph, i, dest, b);
				flag[i] = false;
			}
		}
	}
	else if (graph[s][dest] != 0)
	{
		if (graph[s][dest] < val)
		{
			val = graph[s][dest];
		}
		if (temp < val)
		{
			temp = val;
		}
		val = 100;
	}
	return temp;
}
void makegraph(int** graph, int i, int j, int k)
{
	graph[i - 1][j - 1] = k;
	graph[j - 1][i - 1] = k;
}
void display(int** graph, int b)
{
	cout << setw(6) << " ";
	for (int i = 0; i < b; i++)
	{
		cout << i + 1 << setw(4) << " ";
	}
	cout << endl;
	for (int i = 0; i < b; i++)
	{
		cout << setw(3) << i + 1 << " ";
		for (int j = 0; j < b; j++)
		{
			cout << setw(3) << graph[i][j] << "  ";
		}
		cout << endl;
	}
}
int main()
{
	int a = 0;
	int b = 0;
	ifstream read;
	read.open("Input.txt");
	int s = 0;
	int i = 0;
	while (!read.eof())
	{
		read >> s;
		if (i == 0)
		{
			b = s;
		}
		else if (i == 1)
		{
			a = s;
			break;
		}
		i++;
	}
	i = 0;
	ifstream r;
	r.open("Input.txt");
	int c = (a + 1) * 3;
	int* g = new int[c];
	int j = 0;
	while (!r.eof())
	{

		r >> s;
		if (i > 1)
		{
			g[j] = s;
			j++;
		}
		i++;
	}
	int** graph = new int* [b];
	for (i = 0; i < b; i++)
	{
		graph[i] = new int[b];//allocating memory on heap
	}
	for (int i = 0; i < b; i++)
	{
		for (int j = 0; j < b; j++)
		{
			graph[i][j] = 0;//initializing whole array with zeros
		}
	}
	for (int i = 0; i < j - 3; i++)
	{
		makegraph(graph, g[i], g[i + 1], g[i + 2]);
		i++;
		i++;
	}
	display(graph, b);
	cout << endl << endl;
	s = g[c - 3];
	int d = g[c - 2];
	int total = g[c - 1];
	int count = 0;
	int smallest = getBestPath(graph, s - 1, d - 1, b);
	while (total > 0)
	{
		total = total - smallest;
		count++;
	}
	cout <<endl<<"Total Number of Trips in the given source and destination : "<< count<<endl<<endl;
	return 0;
}