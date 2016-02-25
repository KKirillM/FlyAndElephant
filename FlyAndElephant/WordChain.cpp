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

//загрузка начального и конечного слов из файла
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

	//если в файле меньше было меньше двух слов или слова разной длины, то ошибка
	if (wordCounter < 2 || w.startWord.size() != w.endWord.size())
		return 1;

	return 0;
}

//запись начального и конечного слов
void WordChain::SetSourceWords(const string w1, const string w2)
{
	startWord = w1;
	endWord = w2;
}

//получить путь от исходного слова к конечному в векторе resultChain
void WordChain::MakeChain(Dictionary& d)
{
	vector<string> filteredDictionary; 
	size_t filteredDictSize = 0;
	size_t wordLen = startWord.size();
	size_t dictSize = d.GetCount();
	string dictWord, word;
	size_t symbolNumber = 0;

	//проверяем исходные слова на равенство длины
	if (startWord.size() != endWord.size())
		throw exception("Source words have different length");

	//проверяем словарь на наличие слов
	if (!d.GetCount())
		throw exception("Dictionary is empty");

	//получаем в filteredDictionary фильтрованый словарь со словами, длина которых совпадает с длиной исходного слова
	for (; dictSize > 0; --dictSize)
	{
		dictWord = d[dictSize-1];

		if (dictWord.size() == wordLen)
			filteredDictionary.push_back(dictWord);
	}

	filteredDictSize = filteredDictionary.size();

	resultChain.push_back(startWord);

	/* Алгоритм заполнения цепочки словами:
	*  1. ищем кол-во отличающихся символов в каждом слове из фильтрованного словаря  
	*     и последним найденным словом в цепочке
	*  2. если кол-во отличающихся символов равно 1, то проверяем на равенство этот
	*     символ символу в той же позиции у конечного слова
	*  3. если символы равны, то заносим слово из фильтрованного словаря в цепочку
	*     и продолжаем поиск
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

//вывести на консоль цепочку слов
void WordChain::PrintChain() const
{
	for (auto it = resultChain.begin(); it != resultChain.end(); ++it)
		cout << *it << endl;
}

//вспомогательная ф-ция для подсчета кол-ва различающихся символов в двух словах
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
