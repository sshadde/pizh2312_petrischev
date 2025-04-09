class TimeDeposit:
    """Абстрактный класс - срочный вклад.

    https://ru.wikipedia.org/wiki/Срочный_вклад.

    Поля:
      - self.name (str): наименование;
      - self._interest_rate (float): процент по вкладу (0; 100];
      - self._period_limit (tuple (int, int)):
            допустимый срок вклада в месяцах [от; до);
      - self._sum_limit (tuple (float, float)):
            допустимая сумма вклада [от; до).
    Свойства:
      - self.currency (str): знак/наименование валюты.
    Методы:
      - self._check_self(): проверяет корректность ограничений вклада;
      - self._check_user_params(initial_sum, period):
            проверяет, что параметры клиента вписываются в ограничения;
      - self.get_profit(initial_sum, period): возвращает прибыль по вкладу;
      - self.get_sum(initial_sum, period):
            возвращает сумму по окончании вклада.
    """

    def __init__(self, name: str, interest_rate: float, period_limit: tuple, sum_limit: tuple):
        """Инициализировать атрибуты класса."""
        self.name = name
        self._interest_rate = interest_rate
        self._period_limit = period_limit
        self._sum_limit = sum_limit
        # Проверяем правильность заданных параметров
        self._check_self()

    def __str__(self):
        """Вернуть строковое представление депозита.

        Формат вывода (пример):
            Наименование:       Срочный Вклад
            Валюта:             руб.
            Процентная ставка:  5
            Срок (мес.):        [6; 18)
            Сумма:              [1,000; 100,000)
        """
        return (
            f"Наименование:       {self.name}\n"
            f"Валюта:             {self.currency}\n"
            f"Процентная ставка:  {self._interest_rate}\n"
            f"Срок (мес.):        [{self._period_limit[0]}; {self._period_limit[1]})\n"
            f"Сумма:              [{self._sum_limit[0]:,.0f}; {self._sum_limit[1]:,.0f})"
        )

    @property
    def currency(self) -> str:
        return "руб."  # Не изменяется

    def _check_self(self):
        """Проверить, что данные депозита являются допустимыми."""
        assert 0 < self._interest_rate <= 100, \
            "Неверно указан процент по вкладу!"
        assert 1 <= self._period_limit[0] < self._period_limit[1], \
            "Неверно указаны ограничения по сроку вклада!"
        assert 0 < self._sum_limit[0] <= self._sum_limit[1], \
            "Неверно указаны ограничения по сумме вклада!"

    def _check_user_params(self, initial_sum: float, period: int):
        """Проверить, что данные клиента соответствуют ограничениям вклада."""
        is_sum_ok = self._sum_limit[0] <= initial_sum < self._sum_limit[1]
        is_period_ok = self._period_limit[0] <= period < self._period_limit[1]
        assert is_sum_ok and is_period_ok, "Условия вклада не соблюдены!"

    def get_profit(self, initial_sum: float, period: int) -> float:
        """Вернуть прибыль по вкладу клиента.

        Параметры:
          - initial_sum (float): первоначальная сумма;
          - period (int): количество месяцев размещения вклада.
        
        Формула для простых процентов:
          прибыль = (начальная_сумма * % / 100) * (кол-во_месяцев / 12)
        """
        self._check_user_params(initial_sum, period)
        return initial_sum * self._interest_rate / 100 * period / 12

    def get_sum(self, initial_sum: float, period: int) -> float:
        """Вернуть сумму вклада клиента после начисления прибыли.
        
        Параметры:
          - initial_sum (float): первоначальная сумма;
          - period (int): количество месяцев размещения вклада.
        """
        # Проверка параметров уже есть в get_profit
        return initial_sum + self.get_profit(initial_sum, period)


class BonusTimeDeposit(TimeDeposit):
    """Cрочный вклад c получением бонуса к концу срока вклада.

    Бонус начисляется как % от прибыли, если вклад больше определенной суммы.

    Атрибуты:
      - self._bonus (dict: {"percent": int, "sum": float}):
            'percent' - % от прибыли, 
            'sum'     - минимальная сумма вклада для получения бонуса.
    """

    def __init__(self, name: str, interest_rate: float, period_limit: tuple, sum_limit: tuple, bonus: dict):
        """Инициализировать атрибуты класса."""
        self._bonus = bonus
        super().__init__(name, interest_rate, period_limit, sum_limit)
        # Дополнительная проверка уже в _check_self

    def __str__(self):
        """Вернуть строковое представление депозита.

        Формат вывода (пример):
            Наименование:       Бонусный Вклад
            Валюта:             руб.
            Процентная ставка:  5
            Срок (мес.):        [6; 18)
            Сумма:              [1,000; 100,000)
            Бонус (%):          5
            Бонус (мин. сумма): 2,000
        """
        return (
            f"Наименование:       {self.name}\n"
            f"Валюта:             {self.currency}\n"
            f"Процентная ставка:  {self._interest_rate}\n"
            f"Срок (мес.):        [{self._period_limit[0]}; {self._period_limit[1]})\n"
            f"Сумма:              [{self._sum_limit[0]:,.0f}; {self._sum_limit[1]:,.0f})\n"
            f"Бонус (%):          {self._bonus['percent']}\n"
            f"Бонус (мин. сумма): {self._bonus['sum']:,.0f}"
        )

    def _check_self(self):
        """Проверить, что данные депозита являются допустимыми.
        
        Дополняем родительский метод проверкой бонуса.
        """
        super()._check_self()
        assert 0 < self._bonus["percent"] <= 100, \
            "Неверно указан процент бонуса!"
        assert self._bonus["sum"] > 0, \
            "Неверно указана минимальная сумма для бонуса!"

    def get_profit(self, initial_sum: float, period: int) -> float:
        """Вернуть прибыль по вкладу клиента с учётом бонуса.

        Параметры:
          - initial_sum (float): первоначальная сумма;
          - period (int): количество месяцев размещения вклада.

        Бонус добавляется к прибыли, если initial_sum > self._bonus["sum"].
        """
        # Используем расчёт родительского класса:
        profit = super().get_profit(initial_sum, period)
        # Добавляем бонус, если вклад больше установленного порога:
        if initial_sum > self._bonus["sum"]:
            profit += profit * (self._bonus["percent"] / 100)
        return profit


class CompoundTimeDeposit(TimeDeposit):
    """Cрочный вклад c ежемесячной капитализацией процентов."""

    def __str__(self):
        """Вернуть строковое представление депозита.

        Формат вывода (пример):
            Наименование:       Вклад с Капитализацией
            Валюта:             руб.
            Процентная ставка:  5
            Срок (мес.):        [6; 18)
            Сумма:              [1,000; 100,000)
            Капитализация %   : Да
        """
        return (
            f"Наименование:       {self.name}\n"
            f"Валюта:             {self.currency}\n"
            f"Процентная ставка:  {self._interest_rate}\n"
            f"Срок (мес.):        [{self._period_limit[0]}; {self._period_limit[1]})\n"
            f"Сумма:              [{self._sum_limit[0]:,.0f}; {self._sum_limit[1]:,.0f})\n"
            f"Капитализация %   : Да"
        )

    def get_profit(self, initial_sum: float, period: int) -> float:
        """Вернуть прибыль по вкладу клиента с учётом капитализации.

        Параметры:
          - initial_sum (float): первоначальная сумма;
          - period (int): количество месяцев размещения вклада.

        Формула для ежемесячной капитализации:
            прибыль = initial_sum * (1 + (процент/100)/12)^period - initial_sum
        """
        # Проверяем, что параметры клиента вписываются в ограничения
        self._check_user_params(initial_sum, period)
        return (
            initial_sum * (1 + self._interest_rate / 100 / 12) ** period
            - initial_sum
        )


# -----------------------------------------------------------------------------

# Пример словаря для быстрого задания общих параметров
deposits_data = dict(
    interest_rate=5,
    period_limit=(6, 18),
    sum_limit=(1000, 100000)
)

# Список имеющихся депозитов
deposits = (
    TimeDeposit("Сохраняй", **deposits_data),
    BonusTimeDeposit("Бонусный", **deposits_data, bonus=dict(percent=5, sum=2000)),
    CompoundTimeDeposit("С капитализацией", **deposits_data),
    
    BonusTimeDeposit(
        "Бонус Премиум",
        interest_rate=8,
        period_limit=(6, 24),
        sum_limit=(5000, 500000),
        bonus=dict(percent=10, sum=10000)
    ),
    TimeDeposit(
        "Надёжный",
        interest_rate=6,
        period_limit=(3, 36),
        sum_limit=(1000, 500000)
    )
)
