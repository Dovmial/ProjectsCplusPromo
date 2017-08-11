#include <list>
#include <vector>
#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
using namespace std;

/*using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::map;
using std::list;

class Node
{
public:
	Node(Node * L,Node *R):left(L),right(R),
		num(L->num+R->num),ch(' '){}
	Node(){}
	int num;
	char ch;
	Node *left, *right;
};
struct MyCompare
{
	bool operator()(Node * l, Node * r)const
	{
		return l->num < r->num;
	}
};

void print(Node* root, unsigned k = 0)
{
	if (root != NULL)
	{
		print(root->left, k + 3);
		for (unsigned int i = 0; i < k; i++)
			cout << "   ";
		if (root->ch) cout << root->num << " (" << root->ch << ")\n";
		else cout << root->num << endl;
		print(root->right, k + 3);
	}
}
vector<bool>code;
map<char, vector<bool> >table;

void BuildTable(Node *root)
{
	if (root->left != NULL)
	{
		code.push_back(0);
		BuildTable(root->left);
	}
	if (root->right != NULL)
	{
		code.push_back(1);
		BuildTable(root->right);
	}
	if (root->ch) table[root->ch] = code;
	code.pop_back();
}

int main()
{
	string str = "it is my striiiiing!!!!";
	map <char, int> map1;
	//Counting chars
	for (int i = 0; i < str.length(); ++i)
	{
		char ch = str[i];
		map1[ch]++;
	}

	list <Node*> list1;
	map<char, int>::iterator itr;
	for (itr = map1.begin(); itr != map1.end(); ++itr)
	{
		cout << itr->first << ": " << itr->second << endl;
		Node *ptr = new Node;
		ptr->ch = itr->first;
		ptr->num = itr->second;
		list1.push_back(ptr);
		delete ptr;
	}
	while (list1.size() != 1)
	{
		list1.sort(MyCompare());
		Node *SonL = list1.front();
		list1.pop_front();
		Node *SonR = list1.front();
		list1.pop_front();
		Node *parent = new Node(SonL, SonR);
		list1.push_back(parent);
		delete parent;
	}
	Node * root = list1.front();

//	print(root);
	BuildTable(root);
	map<char, vector<bool> >::iterator im;
	for (im = table.begin(); im != table.end(); ++im)
	{
		cout << im->first << ": ";
		vector<bool>::iterator ib;
		for (ib = (im->second).begin(); ib != (im->second).end(); ++ib)
			cout << *ib;
		cout << endl;
	}
	return 0;
}
*/

struct Node
{
	
	char ch;
	int parent;
	int zero;
	int one;
	bool branch;
};

int main()
{
	setlocale(LC_ALL, "Russian");
	int weight[0x100];
	for (auto &i : weight)
		i = 0;
	{
		ifstream f("");
		if (!f.is_open())
		{
			cerr << "File not found\n";
			exit(1);
		}
		else
		{
			while (!f.eof())
			{
				unsigned char ch;
				f.read((char *)&ch, sizeof(ch));
				++weight[ch];
			}
			/*
			for (int i = 0; i < 0x100; ++i)
				if (weight[i] > 0)
					cout << weight[i] << ' ' << (char)i << endl;
			*/
		}
		f.close();
	}
	multimap<int, int>sortWeight;
	/*for (int i = 0; i < 0x100; ++i)

	for (auto i : sortWeight)
		if (i.first > 0)
			cout << i.first << ": " << i.second << endl;

	*/
	vector<Node> tree;
	map<char, int> charMap;
	for (size_t i = 0; i < 0x100; ++i)
		if (weight[i] > 0)
		{
			tree.push_back(Node{ (char)i,-1,-1,-1,false });
			charMap[i] = tree.size() - 1;
			sortWeight.insert(make_pair(weight[i], tree.size() - 1));
		}
	while (sortWeight.size() > 1)
	{
		int w0 = begin(sortWeight)->first;
		int n0 = begin(sortWeight)->second;
		sortWeight.erase(begin(sortWeight));
		int w1 = begin(sortWeight)->first;
		int n1 = begin(sortWeight)->second;
		sortWeight.erase(begin(sortWeight));
		tree.push_back(Node{ '\0',-1,n0,n1,false });
		tree[n0].parent = tree.size() - 1;
		tree[n0].branch = false;
		tree[n1].parent = tree.size() - 1;
		tree[n1].branch = true;
		sortWeight.insert(make_pair(w0 + w1, tree.size() - 1));
	}
	vector<bool>data;
	{
		ifstream f("");
		if (!f.is_open())
		{
			cerr << "File not found\n";
			exit(1);
		}
		else
		{
			while (!f.eof())
			{
				unsigned char ch;
				f.read((char *)&ch, sizeof(ch));
				auto n = tree[charMap[ch]];
				vector<bool>compressedChar;
				while (n.parent != -1)
				{
					compressedChar.push_back(n.branch);
					n = tree[n.parent];
				}
				data.insert(end(data), compressedChar.rbegin(), compressedChar.rend());
			}
		}
		f.close();
	}
	{
		ofstream f("");
		int treeSize = tree.size();
		f.write((char*)&treeSize, sizeof(treeSize));
		for (auto i : tree)
			f.write((char*)&i, sizeof(i));
		for (size_t i = 0; i < (data.size() / 8); ++i)
		{
			unsigned char ch = 0;
			for (int j = 0; j < 8; ++j)
				if (data.at(i * 8 + j))
					ch |= (1 << j);
			f.write((char*)&ch, sizeof(ch));
		}
		f.close();
	}
	cout << "file is writting!\n";
	return 0;
}


