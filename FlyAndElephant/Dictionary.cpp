#include "stdafx.h"
#include "Dictionary.h"

using namespace std;


Dictionary::Dictionary(void)
{
}


Dictionary::~Dictionary(void)
{
}


//�������� ������� �� �����
int Dictionary::GetDictFromFile(const string path, Dictionary& d)
{
	ifstream f(path);
	string str;

	if (!f.is_open())
		return 1;

	while (!f.eof())
	{
		getline(f, str);
		d.AddWord(str);
	}

	return 0;
}

//���������� ������ ����� � �������
void Dictionary::AddWord(const string word)
{
	dict.push_back(word);
}

//�������� ������ ����� �� �������
const string& Dictionary::operator[](const size_t indx) const
{
	return dict.at(indx);
}

//�������� ���-�� ���� � �������
size_t Dictionary::GetCount() const
{
	return dict.size();
}

//�������� �������
void Dictionary::EraseDictionary()
{
	dict.clear();
}