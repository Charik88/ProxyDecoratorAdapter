/* Задание 2
 
 В дополнение к классам-заместителям VeryHeavyDatabase, реализованным на лекции, реализуйте класс

 class OneShotDB : VeryHeavyDatabase {
   explicit OneShotDB (VeryHeavyDatabase* real_object, size_t shots=1) : ...
 }

 Он должен возвращать данные по ключу из реального объекта то количество раз, которое указано в конструкторе. Исчерпав лимит получения данных, метод GetData всегда возвращает строку error. Пример использования:

 auto real_db = VeryHeavyDatabase();
 auto limit_db = OneShotDB(std::addressof(real_db), 2);
 std::cout << limit_db.GetData("key") << std::endl;
 std::cout << limit_db.GetData("key") << std::endl;
 std::cout << limit_db.GetData("key") << std::endl;

 Output:
 >>> value
 >>> value
 >>> error
 */

#include <map>
#include <string>
#include <iostream>

// PROXY (заместитель)

class VeryHeavyDatabase {
public:
    std::string GetData(const std::string& key) const noexcept { // override
        return "Very Big Data String: " + key; // возвращаем строку с данными
    }
};

class CacheProxyDB : public VeryHeavyDatabase { // класс для кэширования данных который наследуется от класса VeryHeavyDatabase
public:
    explicit CacheProxyDB(VeryHeavyDatabase* real_object) : real_db_(real_object) {} // конструктор класса

    std::string GetData(const std::string& key) noexcept { // переопределение метода GetData
        if (cache_.find(key) == cache_.end()) { // если ключа нет в кэше
            std::cout << "Get from real object\n"; // выводим сообщение об обращении к реальному обьекту
            cache_[key] = real_db_->GetData(key); // добавляем ключ и значение в кэш
        } else {
            std::cout << "Get from cache\n";
        }
        return cache_.at(key); // возвращаем значение ключа из кэша
    }

private:
    std::map<std::string, std::string> cache_; // кэш данных
    VeryHeavyDatabase* real_db_; // указатель на реальный обьект
};

class OneShotDB : public VeryHeavyDatabase { // класс для однократного обращения к базе данных который наследуется от класса VeryHeavyDatabase
public:
    explicit OneShotDB(VeryHeavyDatabase* real_object, size_t shots = 1) // контруктор который принимает указатель на реальный обьект и количество раз которое можно обращаться к бд
        : real_db_(real_object), remaining_shots_(shots) {}

    std::string GetData(const std::string& key) noexcept { // переопределение метода GetData
        if (remaining_shots_ > 0) { // если обращений больше 0
            --remaining_shots_; // уменьшаем количество обращений на 1
            return real_db_->GetData(key); // возвращаем результат к бд
        }
        return "error"; // если обращений меньше 0 возвращаем строку error
    }

private:
    VeryHeavyDatabase* real_db_; // указатель на реальный обьект
    size_t remaining_shots_; // количество оставшихся обращений
};

int main() {
    auto real_db = VeryHeavyDatabase(); // создаем обьект класса VeryHeavyDatabase
    auto cached_db = CacheProxyDB(&real_db); // создаем обьект класса CacheProxyDB
    auto limit_db = OneShotDB(&real_db, 2); // создаем обьект класса OneShotDB

    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;
    std::cout << limit_db.GetData("key") << std::endl;

    return 0;
}


/*

    Конструктор:
        Конструктор принимает указатель на реальный объект VeryHeavyDatabase и количество разрешенных вызовов shots. Он инициализирует указатель на реальный объект и устанавливает количество оставшихся вызовов remaining_shots_.

    Метод GetData:
        Метод проверяет, осталось ли количество разрешенных вызовов (remaining_shots_). Если да, он уменьшает счетчик и вызывает метод GetData у реального объекта, возвращая его результат.
        Если количество вызовов исчерпано, метод возвращает строку "error".



В main создается объект OneShotDB с лимитом в 2 вызова. При первом и втором вызовах возвращается строка "Very Big Data String: key", а при третьем вызове возвращается "error", как и ожидалось.
 */
