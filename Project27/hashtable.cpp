#include "hashtable.h"

using namespace std;

size_t StringHashTable::get(const string& key) // �������� �������� �� ���-������� �� �����
{
	size_t index = table_index(key, true);  // ��������� ��� � ������ �����
	return table[index].value;  
}

void StringHashTable::set(const string& key, const size_t value) // �������� �������� � ���-������� �� �����
{
	size_t index = table_index(key, true);  // ��������� ��� � ������ �����
	table[index].key = key;
	table[index].value = value;
}

bool StringHashTable::check(const string& key) // ��������� ������� ����� � ���-�������
{
	try 
	{
		table_index(key, false);  // ����� �������
	}
	catch (EHashException) 
	{
		return false;  // ��������� ����������, ������� �����������
	}
	return true;  // ���� ���������� �� ���������, ���� ����
}

size_t StringHashTable::hash(const string& key) // ��������� ��� �����
{
	const size_t N = 13;
	const double A = 0.618033;
	const size_t M = 7;
	size_t h = 0;  // ���
	
	for (char ch : key)
	{
		h *= M;  // ��������� ����� ���������� �������
		h += N * fmod(ch * A, 1);  // ���������� ���� ��� �������� �������
	}
	return h;
}

size_t StringHashTable::table_index(const string& key, bool add) // �������� ������ ������� ��� ���������� �����
{
	size_t h = hash(key);  
	for (size_t i = 0; i < MAX_ITERS; ++i) 
	{
		size_t index = (h + i * i) % HASH_SIZE;  
		if (table[index].key == key) 
		{ 
			return index;  // ���� ���� ���������, ���������� ������
		}  
		else if (add && table[index].key.empty()) 
		{ 
			return index; // ���� ���� ���� � add = true, ���������� ������
		}  
	}
	throw EHashException();  // ���������� ����������, ���� ���-�� �������� ������ ���������� �����
}
