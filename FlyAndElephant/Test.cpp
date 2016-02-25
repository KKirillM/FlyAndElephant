#include "stdafx.h"
#include "Test.h"
#include "Dictionary.h"
#include "WordChain.h"

using namespace std;


Test::Test(void)
{
}

Test::~Test(void)
{
}

//����� �������� � ����������� ����������� �����
void Test::PrintTest(const string testName, Dictionary& d, WordChain& w)
{
	cout << "��� �����: " << testName << endl;

	try
	{
		w.MakeChain(d);
	}
	catch (exception& e)
	{
		cout << "��������� �����: " << e.what() << endl << endl;
		return;
	}

	w.PrintChain();	
	cout << "���� �������!" << endl << endl;
}

//��������� ����� ������
void Test::MakeTests()
{
	Dictionary d;
	WordChain c;

	c.SetSourceWords("���", "���");
	PrintTest("������ �������", d, c);

	c.SetSourceWords("����", "�������");
	d.EraseDictionary();
	d.AddWord("����");
	d.AddWord("���");
	PrintTest("�������� ����� ��������� �����", d, c);

	c.SetSourceWords("���", "���");
	d.EraseDictionary();
	d.AddWord("����");
	d.AddWord("���");
	d.AddWord("���");
	d.AddWord("�����");
	PrintTest("������������ ���� � �������", d, c);

	c.SetSourceWords("���", "���");
	d.EraseDictionary();
	d.AddWord("���");
	d.AddWord("���");
	d.AddWord("����");
	d.AddWord("����");
	d.AddWord("���");
	d.AddWord("����");
	d.AddWord("���");
	PrintTest("���������� �������� ������", d, c);	
}
