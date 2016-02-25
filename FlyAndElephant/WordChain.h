#pragma once

class WordChain
{
public:
	WordChain(void);
	~WordChain(void);

	//загрузка начального и конечного слов из файла
	static int GetWordsFromFile(const std::string path, WordChain& w);

	//запись начального и конечного слов
	void SetSourceWords(const std::string w1, const std::string w2);

	//получить путь от исходного слова к конечному в векторе resultChain, используя полученный словарь
	void MakeChain(Dictionary& d);

	//вывести на консоль цепочку слов
	void PrintChain() const;

private:
	//вспомогательная ф-ция для подсчета кол-ва различающихся символов в двух словах
	size_t GetDiffCount(const std::string w1, const std::string w2);

private:
	std::string startWord;
	std::string endWord;
	std::vector<std::string> resultChain;
};

