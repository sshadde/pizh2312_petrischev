class SnowFlake:
    def __init__(self, size):
        if size < 1:
            raise ValueError("Размер должен быть положительным.")
        if size % 2 == 0:
            raise ValueError("Размер должен быть нечётным числом.")
        self.size = size
        self._original_size = size
        self._generate_snowflake()
    
    def _generate_snowflake(self):
        """Перестраивает внутреннюю матрицу снежинки для текущего self.size."""
        N = self.size
        mid = N // 2
        self._matrix = []
        for i in range(N):
            row = []
            for j in range(N):
                if i == j or (i + j) == (N - 1) or i == mid or j == mid:
                    row.append('*')
                else:
                    row.append(' ')
            self._matrix.append(row)
    
    def thaw(self, steps):
        """Уменьшение снежинки на 2 * steps (с каждой стороны уходит 1 строка/столбец за шаг)."""
        new_size = self.size - 2 * steps
        if new_size < 1:
            new_size = 1
        self.size = new_size
        self._generate_snowflake()
    
    def freeze(self, steps):
        """Увеличение снежинки на 2 * steps."""
        self.size += 2 * steps
        self._generate_snowflake()
    
    def thicken(self, steps):
        """Восстанавливает снежинку, добавляя звездочки обратно, как было до thaw."""
        new_size = self.size + 2 * steps
        if new_size > self._original_size:
            new_size = self._original_size
        self.size = new_size
        self._generate_snowflake()
    
    def __str__(self):
        """Возвращает строковое представление снежинки, чтобы удобно было печатать."""
        lines = [''.join(row) for row in self._matrix]
        return "\n".join(lines)
    
    def print_snowflake(self):
        """Альтернативный метод печати (если не хотим переопределять __str__)."""
        print(self.__str__())


flake = SnowFlake(11)
print("Изначальная снежинка (11x11):")
print(flake)

flake.thaw(2)
print("\nПосле thaw(2): (теперь 7x7)")
print(flake)
    
flake.thicken(1)
print("\nПосле thicken(1): (восстановление до 9x9)")
print(flake)

flake.freeze(2)
print("\nПосле freeze(2): (теперь 13x13)")
print(flake)