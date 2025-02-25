class Roman:
    """
    Класс для работы с римскими числами.
    Поддерживает преобразование римских чисел в арабские и обратно,
    а также арифметические операции (+, -, *, /) с римскими числами.
    """

    roman_to_int_map = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}
    int_to_roman_map = [
        (1000, 'M'), (900, 'CM'), (500, 'D'), (400, 'CD'),
        (100, 'C'), (90, 'XC'), (50, 'L'), (40, 'XL'),
        (10, 'X'), (9, 'IX'), (5, 'V'), (4, 'IV'), (1, 'I')
    ]
    
    def __init__(self, value):
        """
        Инициализирует объект Roman.
        Параметр value: римское число в виде строки или арабское число (int).
        Возбуждение исключения ValueError: если переданный аргумент не является строкой или целым числом.
        """
        if isinstance(value, str):
            self.value = self.roman_to_int(value)
        elif isinstance(value, int):
            self.value = value
        else:
            raise ValueError("Invalid value type")
    
    @staticmethod
    def roman_to_int(roman: str) -> int:
        """
        Преобразует римское число в арабское.
        Параметр roman: строка с римским числом.
        Возвращаемое значение: целое число (арабское представление римского числа).
        """
        result = 0
        prev_value = 0
        for char in reversed(roman):
            current_value = Roman.roman_to_int_map[char]
            if current_value < prev_value:
                result -= current_value
            else:
                result += current_value
            prev_value = current_value
        return result
    
    @staticmethod
    def int_to_roman(number: int) -> str:
        """
        Преобразует арабское число в римское.
        Параметр number: целое число.
        Возвращаемое значение: строка с римским представлением числа.
        """
        result = ""
        for value, symbol in Roman.int_to_roman_map:
            while number >= value:
                result += symbol
                number -= value
        return result
    
    def __add__(self, other):
        """
        Складывает два римских числа.
        Параметр other: объект класса Roman.
        Возвращаемое значение: новый объект Roman с суммой значений.
        """
        return Roman(self.value + other.value)
    
    def __sub__(self, other):
        """
        Вычитает одно римское число из другого.
        Параметр other: объект класса Roman.
        Возвращаемое значение: новый объект Roman с разностью значений.
        Возбуждение исключения ValueError: если результат отрицательный или нулевой.
        """
        if self.value - other.value <= 0:
            raise ValueError("Resulting Roman numeral must be positive")
        return Roman(self.value - other.value)
    
    def __mul__(self, other):
        """
        Умножает два римских числа.
        Параметр other: объект класса Roman.
        Возвращаемое значение: новый объект Roman с произведением значений.
        """
        return Roman(self.value * other.value)
    
    def __truediv__(self, other):
        """
        Делит одно римское число на другое (целочисленное деление).
        Параметр other: объект класса Roman.
        Возвращаемое значение: новый объект Roman с результатом целочисленного деления.
        Возбуждение исключения ZeroDivisionError: если делитель равен нулю.
        """
        if other.value == 0:
            raise ZeroDivisionError("Cannot divide by zero")
        return Roman(self.value // other.value)
    
    def __str__(self):
        """
        Возвращает строковое представление римского числа.
        Возвращаемое значение: строка с римским числом.
        """
        return self.int_to_roman(self.value)
    
    def __repr__(self):
        """
        Возвращает строковое представление объекта для отладки.
        Возвращаемое значение: строка формата "Roman('X')".
        """
        return f"Roman('{self.int_to_roman(self.value)}')"

# Примеры использования
num1 = Roman("X")  # 10
num2 = Roman("V")  # 5
print(num1 + num2)  # XV (15)
print(num1 - num2)  # V (5)
print(num1 * num2)  # L (50)
print(num1 / num2)  # II (2)