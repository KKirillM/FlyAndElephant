#pragma once

class Dictionary;
class WordChain;

class Test
{
public:
	Test();
	~Test(void);

	//����� �������� � ����������� ����������� �����
	void PrintTest(const std::string testName, Dictionary& d, WordChain& w);

	//��������� ����� ������
	void MakeTests();
};

