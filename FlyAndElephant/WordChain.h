#pragma once

class WordChain
{
public:
	WordChain(void);
	~WordChain(void);

	//�������� ���������� � ��������� ���� �� �����
	static int GetWordsFromFile(const std::string path, WordChain& w);

	//������ ���������� � ��������� ����
	void SetSourceWords(const std::string w1, const std::string w2);

	//�������� ���� �� ��������� ����� � ��������� � ������� resultChain, ��������� ���������� �������
	void MakeChain(Dictionary& d);

	//������� �� ������� ������� ����
	void PrintChain() const;

private:
	//��������������� �-��� ��� �������� ���-�� ������������� �������� � ���� ������
	size_t GetDiffCount(const std::string w1, const std::string w2);

private:
	std::string startWord;
	std::string endWord;
	std::vector<std::string> resultChain;
};

