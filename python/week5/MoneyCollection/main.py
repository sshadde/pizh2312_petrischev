from money import Money
from MoneyCollection import MoneyCollection

if __name__ == "__main__":
    collection = MoneyCollection()
    
    money1 = Money(100, "USD")
    money2 = Money(50, "USD")
    money3 = Money(200, "EUR")
    
    collection.add(money1)
    collection.add(money2)
    collection.add(money3)
    
    print("Содержимое коллекции:")
    print(collection)
    
    print("\nУдаление второго элемента (индекс 1)")
    collection.remove(1)
    print(collection)
    
    print("\nСохранение коллекции в файл...")
    collection.save("MoneyCollection.json")
    
    print("\nСоздание новой коллекции и загрузка из файла...")
    new_collection = MoneyCollection()
    new_collection.load("MoneyCollection.json")
    print(new_collection)

#----------------
# Пример вывода:
#----------------
# Содержимое коллекции:
# 100.00 USD
# 50.00 USD
# 200.00 EUR
#
# Удаление второго элемента (индекс 1)
# 100.00 USD
# 200.00 EUR
#
# Сохранение коллекции в файл...
#
# Создание новой коллекции и загрузка из файла...
# 100.00 USD
# 200.00 EUR