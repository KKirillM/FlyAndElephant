#pragma once

class Dictionary
{
public:
	Dictionary(void);
	~Dictionary(void);

	//�������� ������� �� �����
	static int GetDictFromFile(const std::string path, Dictionary& d);

	//���������� ������ ����� � �������
	void AddWord(const std::string word);

	//�������� ������ ����� �� �������
	const std::string& operator[](const size_t indx) const;

	//�������� ���-�� ���� � �������
	size_t GetCount() const;

	//�������� �������
	void EraseDictionary();

private:
	std::vector<std::string> dict;
};

