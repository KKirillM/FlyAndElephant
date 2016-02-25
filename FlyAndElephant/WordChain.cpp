#include "stdafx.h"
#include "Dictionary.h"
#include "WordChain.h"

using namespace std;

WordChain::WordChain(void)
{
}


WordChain::~WordChain(void)
{
}

//�������� ���������� � ��������� ���� �� �����
int WordChain::GetWordsFromFile(const string path, WordChain& w)
{
	ifstream f(path);
	string str;
	int wordCounter = 0;

	if (!f.is_open())
		return 1;

	if (getline(f, w.startWord) && !f.eof())
		wordCounter++;

	if (getline(f, w.endWord))
		wordCounter++;

	//���� � ����� ������ ���� ������ ���� ���� ��� ����� ������ �����, �� ������
	if (wordCounter < 2 || w.startWord.size() != w.endWord.size())
		return 1;

	return 0;
}

//������ ���������� � ��������� ����
void WordChain::SetSourceWords(const string w1, const string w2)
{
	startWord = w1;
	endWord = w2;
}

//�������� ���� �� ��������� ����� � ��������� � ������� resultChain
void WordChain::MakeChain(Dictionary& d)
{
	vector<string> filteredDictionary; 
	size_t filteredDictSize = 0;
	size_t wordLen = startWord.size();
	size_t dictSize = d.GetCount();
	string dictWord, word;
	size_t symbolNumber = 0;

	//��������� �������� ����� �� ��������� �����
	if (startWord.size() != endWord.size())
		throw exception("Source words have different length");

	//��������� ������� �� ������� ����
	if (!d.GetCount())
		throw exception("Dictionary is empty");

	//�������� � filteredDictionary ������������ ������� �� �������, ����� ������� ��������� � ������ ��������� �����
	for (; dictSize > 0; --dictSize)
	{
		dictWord = d[dictSize-1];

		if (dictWord.size() == wordLen)
			filteredDictionary.push_back(dictWord);
	}

	filteredDictSize = filteredDictionary.size();

	resultChain.push_back(startWord);

	/* �������� ���������� ������� �������:
	*  1. ���� ���-�� ������������ �������� � ������ ����� �� �������������� �������  
	*     � ��������� ��������� ������ � �������
	*  2. ���� ���-�� ������������ �������� ����� 1, �� ��������� �� ��������� ����
	*     ������ ������� � ��� �� ������� � ��������� �����
	*  3. ���� ������� �����, �� ������� ����� �� �������������� ������� � �������
	*     � ���������� �����
	*/
	for (; filteredDictSize > 0; --filteredDictSize)
	{
		word = resultChain.back();
		dictWord = filteredDictionary.at(filteredDictSize-1);

		if (GetDiffCount(word, dictWord) == 1)
		{
			while (word[symbolNumber] == dictWord[symbolNumber])
				symbolNumber++;
			
			if (dictWord[symbolNumber] == endWord[symbolNumber])
				resultChain.push_back(dictWord);

			symbolNumber = 0;
		}
	}

	if (GetDiffCount(endWord, resultChain.back()) != 1)
		throw exception("Not enough words in dictionary");

	resultChain.push_back(endWord);
}

//������� �� ������� ������� ����
void WordChain::PrintChain() const
{
	for (auto it = resultChain.begin(); it != resultChain.end(); ++it)
		cout << *it << endl;
}

//��������������� �-��� ��� �������� ���-�� ������������� �������� � ���� ������
size_t WordChain::GetDiffCount(const std::string w1, const std::string w2)
{
	size_t diffCount = 0;

	for(auto i = w1.begin(), j = w2.begin(); i < w1.end(); ++i, ++j)
	{
		if (*i != *j) 
			++diffCount;
	}

	return diffCount;
}
