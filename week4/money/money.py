import json

class Money:
    """
    Класс для представления денежных средств с возможностью выполнения базовых арифметических операций.
    """
    def __init__(self, amount: float, currency: str):
        """
        Инициализация объекта Money.
        
        Параметры:
          - amount: Сумма денежных средств.
          - currency: Валюта денежных средств.
        """
        self.amount = amount
        self.currency = currency
    
    def __str__(self):
        """
        Возвращает строковое представление объекта Money.
        
        Вывод: Строка в формате '<сумма> <валюта>'.
        """
        return f"{self.amount:.2f} {self.currency}"
    
    def __add__(self, other):
        """
        Складывает два объекта Money с одинаковой валютой.
        
        Параметры:
          - other: Другой объект Money.

        Вывод: Новый объект Money с суммированной величиной.
        
        Возбуждение исключений ValueError: Если валюты не совпадают.
        """
        if isinstance(other, Money) and self.currency == other.currency:
            return Money(self.amount + other.amount, self.currency)
        raise ValueError("Разные валюты не могут быть суммированы")
    
    def __sub__(self, other):
        """
        Вычитает один объект Money из другого с одинаковой валютой.
        
        Параметры:
          - other: Другой объект Money.
        
        Вывод: Новый объект Money с уменьшенной величиной.
        
        Возбуждение исключений ValueError: Если валюты не совпадают.
        """
        if isinstance(other, Money) and self.currency == other.currency:
            return Money(self.amount - other.amount, self.currency)
        raise ValueError("Разные валюты не могут вычитаться друг из друга")
    
    @classmethod
    def from_string(cls, str_value: str):
        """
        Создает объект Money из строки формата '<сумма> <валюта>'.
        
        Параметры:
          - str_value: Строковое представление денежных средств.
        
        Вывод: Новый объект Money.
        """
        amount, currency = str_value.split()
        return cls(float(amount), currency)
    
    def save(self, filename: str):
        """
        Сохраняет объект Money в JSON-файл.
        
        Параметры:
          - filename: Имя файла для сохранения.
        """
        with open(f"week4/money/{filename}", "w") as file:
            json.dump({"amount": self.amount, "currency": self.currency}, file)
    
    def load(self, filename: str):
        """
        Загружает объект Money из JSON-файла.
        
        Параметры:
          - filename: Имя файла для загрузки.
        """
        with open(f"week4/money/{filename}", "r") as file:
            data = json.load(file)
            self.amount = data["amount"]
            self.currency = data["currency"]
    
    def convert(self, rate: float, new_currency: str):
        """
        Конвертирует объект Money в новую валюту.
        
        Параметры:
          - rate: Курс обмена.
          - new_currency: Новая валюта.
        
        Вывод: Новый объект Money с конвертированной суммой.
        """
        return Money(self.amount * rate, new_currency)
    
    def multiply(self, factor: float):
        """
        Умножает сумму денежных средств на заданный коэффициент.
        
        Параметры:
          - factor: Множитель.
        
        Вывод: Новый объект Money с измененной суммой.
        """
        return Money(self.amount * factor, self.currency)
    
    def divide(self, divisor: float):
        """
        Делит сумму денежных средств на заданный делитель.
        
        Параметры:
          - divisor: Делитель.
        
        Вывод: Новый объект Money с уменьшенной суммой.
        
        Возбуждение исключений ValueError: Если делитель равен 0.
        """
        if divisor == 0:
            raise ValueError("Не делится на ноль")
        return Money(self.amount / divisor, self.currency)
