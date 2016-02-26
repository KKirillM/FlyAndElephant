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

//çàãðóçêà íà÷àëüíîãî è êîíå÷íîãî ñëîâ èç ôàéëà
int WordChain::GetWordsFromFile(const string path, WordChain& w)
{
	ifstream f(path);
	int wordCounter = 0;

	if (!f.is_open())
		return 1;

	if (getline(f, w.startWord) && !f.eof())
		wordCounter++;

	if (getline(f, w.endWord))
		wordCounter++;

	//åñëè â ôàéëå ìåíüøå áûëî ìåíüøå äâóõ ñëîâ èëè ñëîâà ðàçíîé äëèíû, òî îøèáêà
	if (wordCounter < 2 || w.startWord.size() != w.endWord.size())
		return 1;

	return 0;
}

//çàïèñü íà÷àëüíîãî è êîíå÷íîãî ñëîâ
void WordChain::SetSourceWords(const string w1, const string w2)
{
	startWord = w1;
	endWord = w2;
}

//ïîëó÷èòü ïóòü îò èñõîäíîãî ñëîâà ê êîíå÷íîìó â âåêòîðå resultChain
void WordChain::MakeChain(Dictionary& d)
{
	vector<string> filteredDictionary; 
	size_t filteredDictSize = 0;
	size_t wordLen = startWord.size();
	size_t dictSize = d.GetCount();
	string dictWord, word;
	size_t symbolNumber = 0;

	//ïðîâåðÿåì èñõîäíûå ñëîâà íà ðàâåíñòâî äëèíû
	if (startWord.size() != endWord.size())
		throw exception("Source words have different length");

	//ïðîâåðÿåì ñëîâàðü íà íàëè÷èå ñëîâ
	if (!d.GetCount())
		throw exception("Dictionary is empty");

	//ïîëó÷àåì â filteredDictionary ôèëüòðîâàíûé ñëîâàðü ñî ñëîâàìè, äëèíà êîòîðûõ ñîâïàäàåò ñ äëèíîé èñõîäíîãî ñëîâà
	for (; dictSize > 0; --dictSize)
	{
		dictWord = d[dictSize-1];

		if (dictWord.size() == wordLen)
			filteredDictionary.push_back(dictWord);
	}

	filteredDictSize = filteredDictionary.size();

	resultChain.push_back(startWord);

	/* Àëãîðèòì çàïîëíåíèÿ öåïî÷êè ñëîâàìè:
	*  1. èùåì êîë-âî îòëè÷àþùèõñÿ ñèìâîëîâ â êàæäîì ñëîâå èç ôèëüòðîâàííîãî ñëîâàðÿ  
	*     è ïîñëåäíèì íàéäåííûì ñëîâîì â öåïî÷êå
	*  2. åñëè êîë-âî îòëè÷àþùèõñÿ ñèìâîëîâ ðàâíî 1, òî ïðîâåðÿåì íà ðàâåíñòâî ýòîò
	*     ñèìâîë ñèìâîëó â òîé æå ïîçèöèè ó êîíå÷íîãî ñëîâà
	*  3. åñëè ñèìâîëû ðàâíû, òî çàíîñèì ñëîâî èç ôèëüòðîâàííîãî ñëîâàðÿ â öåïî÷êó
	*     è ïðîäîëæàåì ïîèñê
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

//âûâåñòè íà êîíñîëü öåïî÷êó ñëîâ
void WordChain::PrintChain() const
{
	for (auto it = resultChain.begin(); it != resultChain.end(); ++it)
		cout << *it << endl;
}

//âñïîìîãàòåëüíàÿ ô-öèÿ äëÿ ïîäñ÷åòà êîë-âà ðàçëè÷àþùèõñÿ ñèìâîëîâ â äâóõ ñëîâàõ
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
