#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

struct Node
{
	char ch;
	int parent;
	int zero;
	int one;
	bool branch;
};
/*
int main()
{
	setlocale(LC_ALL, "Russian");
	vector <Node> tree;int c = 0;
	ifstream f("C:\\Users\\HP\\Source\\Repos\\ProjectsCplusPromo\\HuffmanAlg\\HuffmanAlg\\ос.huff");
	if (!f.is_open())
	{
		cerr << "File not found\n";
		exit(1);
	}
	else
	{
		int treeSize;
		f.read((char*)&treeSize, sizeof(treeSize));
		for (int i = 0; i < treeSize; ++i)
		{
			Node n;
			f.read((char *)&n, sizeof(n));
			tree.push_back(n);
		}
		vector<bool>data;
		if (f.eof())
			f.clear();

		while (!f.eof())
		{
			unsigned char ch;
			f.read((char*)&ch, sizeof(ch));
			for (int i = 0; i < 8; ++i)
				data.push_back((ch &(1 << i)) != 0);
		}
		auto n = tree.size() - 1;
		for (auto i : data)
		{
			if (i)
				n = tree[n].one;
			else
				n = tree[n].zero;
			if (tree[n].one == -1)
			{
				cout << tree[n].ch;
				n = tree.size() - 1;
			}
		}
	}
	f.close();
	return 0;
}
*/