#pragma once
#include <string>
#include <array>

#define HASH_SIZE 10

using namespace std;

class StringHashTable // ����� ���-�������
{
public:
	class EHashException {}; // �����-����������
	size_t get(const string& key); // �������� �������� �� ���-������� �� �����
	void set(const string& key, const size_t value); // �������� �������� � ���-������� �� �����
	bool check(const string& key); // ��������� ������� ����� � ���-�������
	size_t hash(const string& key); // ��������� ��� �����
private:
	size_t table_index(const string& key, bool add); // �������� ������ ������� ��� ���������� �����
	struct Element  // ��������� �������� �������
	{
		string key;				// ����
		size_t value;			// ��������
	};
		
	static const size_t MAX_ITERS = HASH_SIZE * 2; // ������������ ���-�� ��������
	array<Element, HASH_SIZE> table; // ���-�������
};