#include <iostream>

using namespace std;

struct TrieNode
{
public:
	TrieNode *next[26];
	bool is_word; // Whether is the end of a word.
	int count; // count the number of common char.

	TrieNode(bool b = false)
	{
		memset(next, 0, sizeof(next));
		is_word = b;
		count = 0;
	}
};

class Trie
{
public:
	Trie()
	{
		root = new TrieNode();
		num = 0; 
	}
	// Inserts a word into the trie.
	void insert(string s)
	{
		TrieNode *p = root;
		for (int i = 0; i < s.size(); ++i)
		{
			if (p->next[s[i] - 'a'] == NULL)
			{
				TrieNode *node = new TrieNode();
				node->count = 1;
				p->next[s[i] - 'a'] = node;
			}
			else
				p->next[s[i] - 'a']->count += 1;

			p = p->next[s[i] - 'a'];
		}
		p->is_word = true;

		num += 1;
	}
	// Returns if the word is in the trie.
	bool search(const string& s)
	{
		TrieNode *p = _find(s);
		return p != NULL && p->is_word;
	}
	// Returns if there is any word in the trie that starts with the given prefix.
	bool starts_with(const string& s)
	{
		return _find(s) != NULL;
	}

	TrieNode* _find(const string& s)
	{
		TrieNode *p = root;
		for (int i = 0; i < s.size() && p != NULL; ++i)
			p = p->next[s[i] - 'a'];
		return p;
	}

	int longest_common_prefix(const string& s)
	{
		TrieNode *p = root;
		int longest = 0;
		for (int i = 0; i < s.size(); ++i)
		{
			if (p->next[s[i] - 'a'] == NULL)
				break;

			if (p->next[s[i] - 'a']->count == num)
				longest += 1;
			else
				break;

			p = p->next[s[i] - 'a'];
		}
		return longest;
	}
	

private:
	TrieNode *root;
	int num; // number of trie node.
};

int main(int argc, const char * argv[])
{
	Trie t;
	t.insert("a");
	t.insert("abc");
	t.insert("abdd");
	t.insert("adsd");
	
	cout << t.longest_common_prefix("ab");

	return 0;
}