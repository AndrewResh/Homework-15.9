#pragma once
#include <string>
#include <array>

#define HASH_SIZE 10

using namespace std;

class StringHashTable // Класс хеш-таблицы
{
public:
	class EHashException {}; // Класс-исключение
	size_t get(const string& key); // Получить значение из хеш-таблицы по ключу
	void set(const string& key, const size_t value); // Записать значение в хеш-таблицу по ключу
	bool check(const string& key); // Проверить наличие ключа в хеш-таблице
	size_t hash(const string& key); // Вычислить хеш ключа
private:
	size_t table_index(const string& key, bool add); // Получить индекс таблицы для указанного ключа
	struct Element  // Структура элемента таблицы
	{
		string key;				// ключ
		size_t value;			// значение
	};
		
	static const size_t MAX_ITERS = HASH_SIZE * 2; // Максимальное кол-во итераций
	array<Element, HASH_SIZE> table; // Хеш-таблица
};