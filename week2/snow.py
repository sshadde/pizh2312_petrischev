class SnowFlake:
    def __init__(self, size):
        if size < 1:
            raise ValueError("Размер должен быть положительным.")
        if size % 2 == 0:
            raise ValueError("Размер должен быть нечётным числом.")
        self.size = size
        self._matrix = []
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
    
    def thicken(self):
        """Утолщение снежинки: добавление линий звёздочек рядом с существующими."""
        N = self.size
        new_matrix = [[' ' for a in range(N)] for a in range(N)]
        for i in range(N):
            for j in range(N):
                if self._matrix[i][j] == '*':
                    new_matrix[i][j] = '*'
                    if i > 0: new_matrix[i - 1][j] = '*'
                    if i < N - 1: new_matrix[i + 1][j] = '*'
                    if j > 0: new_matrix[i][j - 1] = '*'
                    if j < N - 1: new_matrix[i][j + 1] = '*'
        self._matrix = new_matrix
    
    def __str__(self):
        """Возвращает строковое представление снежинки, чтобы удобно было печатать."""
        lines = [''.join(row) for row in self._matrix]
        return "\n".join(lines)

flake = SnowFlake(19)
print("Изначальная снежинка (19x19):")
print(flake)

flake.thicken()
print("\nПосле thicken(): (утолщённая снежинка)")
print(flake)

flake.thaw(3)
print("\nПосле thaw(1): (теперь 13x13)")
print(flake)

flake.freeze(1)
print("\nПосле freeze(1): (теперь 15x15)")
print(flake)