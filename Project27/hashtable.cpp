#include "hashtable.h"

using namespace std;

size_t StringHashTable::get(const string& key) // Получить значение из хеш-таблицы по ключу
{
	size_t index = table_index(key, true);  // вычисляем хеш и индекс ключа
	return table[index].value;  
}

void StringHashTable::set(const string& key, const size_t value) // Записать значение в хеш-таблицу по ключу
{
	size_t index = table_index(key, true);  // вычисляем хеш и индекс ключа
	table[index].key = key;
	table[index].value = value;
}

bool StringHashTable::check(const string& key) // Проверить наличие ключа в хеш-таблице
{
	try 
	{
		table_index(key, false);  // поиск индекса
	}
	catch (EHashException) 
	{
		return false;  // произошло исключение, элемент отсутствует
	}
	return true;  // если исключения не произошло, ключ есть
}

size_t StringHashTable::hash(const string& key) // Вычислить хеш ключа
{
	const size_t N = 13;
	const double A = 0.618033;
	const size_t M = 7;
	size_t h = 0;  // хеш
	
	for (char ch : key)
	{
		h *= M;  // умножение после очередного символа
		h += N * fmod(ch * A, 1);  // вычисление хеша для текущего символа
	}
	return h;
}

size_t StringHashTable::table_index(const string& key, bool add) // Получить индекс таблицы для указанного ключа
{
	size_t h = hash(key);  
	for (size_t i = 0; i < MAX_ITERS; ++i) 
	{
		size_t index = (h + i * i) % HASH_SIZE;  
		if (table[index].key == key) 
		{ 
			return index;  // если ключ совпадает, возвращаем индекс
		}  
		else if (add && table[index].key.empty()) 
		{ 
			return index; // если ключ пуст и add = true, возвращаем индекс
		}  
	}
	throw EHashException();  // генерируем исключение, если кол-во итераций больше указанного числа
}
