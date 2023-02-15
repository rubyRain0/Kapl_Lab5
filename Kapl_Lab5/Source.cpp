#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <vector>

struct NODE
{
	NODE* ptrs[26];
	int count = 0;
	NODE()
	{
		for (int i = 0; i < 26; ++i)
			ptrs[i] = nullptr;
	}
};

using TrieTree = NODE*;

void init(TrieTree& root)
{
	root = nullptr;
}

bool empty(TrieTree root)
{
	return root == nullptr;
}

void add(TrieTree& t, const std::string word, size_t i)
{
	if (!t)
	{
		t = new NODE;

	}
	if ((word.length()) - 1 < i)
		t->count++;
	else
		add(t->ptrs[word[i] - 'a'], word, i + 1);
}

bool all_ptr_empty(TrieTree t)
{
	bool res = true;
	size_t i = 0;
	while (i < 26 && res)
		if (!t->ptrs[i])
			++i;
		else
			res = false;
	return res;
}

void del(TrieTree& t, const std::string word, size_t i)
{
	if (t)
		if (i <= word.length() - 1)
			del(t->ptrs[word[i] - 'a'], word, i + 1);
		else
		{
			t->count = 0;
			if (all_ptr_empty(t))
			{
				delete t;
				t = nullptr;
			}
		}
}

void clear(TrieTree& t)
{
	for (size_t i = 0; i < 26; ++i)

		if (t->ptrs[i])
			clear(t->ptrs[i]);
	delete t;
	t = nullptr;
}

void findDictWords(TrieTree t, std::vector<std::string>& dict, std::string word)
{	
	bool foundInTrie = false;
	for (size_t i = 0; i < dict.size(); ++i)
	{
		if (dict[i] == word)
		{
			foundInTrie = true;
			dict.erase(dict.begin() + i);
		}
	}
	if (t->count && foundInTrie)
	{
		std::cout << word << " " << t->count << '\n';
	}
	for (size_t i = 0; i < 26; ++i)
	{
		if (t->ptrs[i])
		{
			findDictWords(t->ptrs[i], dict, word + char(i + 'a'));
		}
	}

}

bool task5(TrieTree t, std::vector<std::string>& dict, std::string word)
{
	int sizeBefore = dict.size();
	findDictWords(t, dict, word);
	bool res = false;
	if (sizeBefore != dict.size())
		res = true;
	for (size_t i = 0; i < dict.size(); ++i)
	{
		std::cout << dict[i] << " " << '0' << '\n';
	}
	return res;
}

int main()
{
	std::ifstream file("trieWords.txt");
	std::ifstream file2("searchForWords.txt");
	std::vector<std::string> wordsDictionary;
	std::string word;

	TrieTree root;
	init(root);

	while (std::getline(file, word))
	{
		if (word.length())
		{
			add(root, word, 0);
		}
	}
	file.close();

	while (std::getline(file2, word))
	{
		if (word.length())
		{
			wordsDictionary.push_back(word);
		}
	}
	file2.close();

	if (!task5(root, wordsDictionary, ""))
	{
		std::cout << "No words were found in trie tree...\n";
	}

	clear(root);
	std::cin.ignore();
}