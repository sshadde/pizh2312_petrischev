import json
from money import Money

class MoneyCollection:
    """
    Класс-контейнер для хранения и управления набором объектов Money.
    """
    def __init__(self):
        """
        Инициализация контейнера с пустым списком объектов Money.

        Параметры: 
          - _data: Контейнер, содержащий объекты Money.
        """
        self._data = []

    def __str__(self):
        """
        Возвращает строковое представление контейнера.

        Вывод:
          - Строка со списком объектов Money, разделенных переводом строки.
        """
        return "\n".join(str(money) for money in self._data)

    def __getitem__(self, index: int):
        """
        Позволяет получать элементы по индексу.

        Параметры:
          - index (int): Индекс элемента.
        
        Вывод:
          - Объект Money, находящийся по заданному индексу.
        """
        return self._data[index]

    def add(self, value: Money):
        """
        Добавляет объект Money в контейнер.

        Параметры:
          - value (Money): Объект Money для добавления.
        
        Возбуждение исключений:
          - TypeError: Если переданный объект не является экземпляром Money.
        """
        if isinstance(value, Money):
            self._data.append(value)
        else:
            raise TypeError("Можно добавлять только объекты Money")

    def remove(self, index: int):
        """
        Удаляет объект Money по индексу.

         Параметры:
          - index (int): Индекс удаляемого элемента.
        
        Возбуждение исключений:
          - IndexError: Если индекс выходит за границы списка.
        """
        if 0 <= index < len(self._data):
            del self._data[index]
        else:
            raise IndexError("Индекс вне диапазона")

    def save(self, filename: str):
        """
        Сохраняет список объектов Money в JSON-файл.

        Параметры:
          - filename (str): Имя файла для сохранения.
        """
        with open(f"week5/MoneyCollection/{filename}", "w") as file:
            json.dump([{"amount": money.amount, "currency": money.currency} for money in self._data], file)

    def load(self, filename: str):
        """
        Загружает список объектов Money из JSON-файла.

        Параметры:
          - filename (str): Имя файла для загрузки.
        """
        with open(f"week5/MoneyCollection/{filename}", "r") as file:
            data = json.load(file)
            self._data = [Money(item["amount"], item["currency"]) for item in data]
