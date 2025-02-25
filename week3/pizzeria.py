class Pizza:
    """
    Базовый класс для пиццы.
    Описывает основные характеристики пиццы и методы её приготовления.
    """
    def __init__(self, name: str, dough: str, sauce: str, topping: str, price: int):
        """
        Инициализация пиццы.
        Параметр name: название пиццы
        Параметр dough: тип теста
        Параметр sauce: вид соуса
        Параметр topping: начинка
        Параметр price: цена
        """
        self.name = name
        self.dough = dough
        self.sauce = sauce
        self.topping = topping
        self.price = price
    
    def prepare(self):
        """
        Подготовка пиццы к выпеканию.
        Результат: строка с описанием подготовки
        """
        return f"Готовим {self.name}: замешиваем {self.dough}, добавляем {self.sauce} и {self.topping}."
    
    def bake(self):
        """
        Выпекание пиццы.
        Результат: строка с описанием выпекания
        """
        return f"Выпекаем {self.name}."
    
    def cut(self):
        """
        Нарезка пиццы.
        Результат: строка с описанием нарезки
        """
        return f"Режем {self.name}."
    
    def pack(self):
        """
        Упаковка пиццы.
        Результат: строка с описанием упаковки
        """
        return f"Упаковываем {self.name}."
    
    def __str__(self):
        """
        Представление пиццы в строковом формате.
        Результат: строка с характеристиками пиццы
        """
        return f"{self.name}: {self.dough}, {self.sauce}, {self.topping} - {self.price} руб."


class PizzaPepperoni(Pizza):
    """
    Класс пиццы Пепперони.
    """
    def __init__(self):
        super().__init__("Пепперони", "тонкое тесто", "томатный соус", "пепперони и сыр", 500)


class PizzaBBQ(Pizza):
    """
    Класс пиццы Барбекю.
    """
    def __init__(self):
        super().__init__("Барбекю", "толстое тесто", "BBQ соус", "курица, лук и сыр", 550)


class PizzaSeafood(Pizza):
    """
    Класс пиццы Дары Моря.
    """
    def __init__(self):
        super().__init__("Дары Моря", "тонкое тесто", "сливочный соус", "креветки и мидии", 600)


class Order:
    """
    Класс заказа, содержащий список пицц и их общую стоимость.
    """
    def __init__(self):
        """
        Инициализация заказа.
        """
        self.pizzas = []
        self.total = 0
    
    def add_pizza(self, pizza):
        """
        Добавление пиццы в заказ.
        Параметр pizza: объект пиццы
        """
        self.pizzas.append(pizza)
        self.total += pizza.price
    
    def calculate_total(self):
        """
        Подсчет общей стоимости заказа.
        Результат: общая сумма заказа
        """
        return self.total
    
    def __str__(self):
        """
        Представление заказа в строковом формате.
        Результат: строка со списком пицц и итоговой суммой
        """
        return "\n".join([str(pizza) for pizza in self.pizzas]) + f"\nИтого: {self.total} руб."


class Terminal:
    """
    Класс терминала, управляющий меню и обработкой заказов.
    """
    def __init__(self):
        """
        Инициализация терминала с меню пицц.
        """
        self.menu = [PizzaPepperoni(), PizzaBBQ(), PizzaSeafood()]
    
    def show_menu(self):
        """
        Выводит меню пицц на экран.
        """
        print("Меню:")
        for idx, pizza in enumerate(self.menu, start=1):
            print(f"{idx}. {pizza}")
    
    def process_order(self):
        """
        Обрабатывает заказ пользователя, предоставляя интерфейс выбора пиццы.
        """
        order = Order()
        while True:
            self.show_menu()
            choice = input("Введите номер пиццы для заказа (0 для завершения): ")
            if choice == '0':
                break
            try:
                selected_pizza = self.menu[int(choice) - 1]
                order.add_pizza(selected_pizza)
                print(f"Добавлена: {selected_pizza.name}")
            except (IndexError, ValueError):
                print("Некорректный ввод, попробуйте снова.")
        
        print("Ваш заказ:")
        print(order)
        input("Нажмите Enter для оплаты...")
        print("Оплата принята. Ваш заказ готовится!")

# Пример использования
terminal = Terminal()
terminal.process_order()
# Меню:
# 1. Пепперони: тонкое тесто, томатный соус, пепперони и сыр - 500 руб.
# 2. Барбекю: толстое тесто, BBQ соус, курица, лук и сыр - 550 руб.
# 3. Дары Моря: тонкое тесто, сливочный соус, креветки и мидии - 600 руб.
# Введите номер пиццы для заказа (0 для завершения):