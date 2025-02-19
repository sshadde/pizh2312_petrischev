from abc import ABC, abstractmethod

class AbstractSnowFlake(ABC):
    @abstractmethod
    def thaw(self, steps):
        pass

    @abstractmethod
    def freeze(self, steps):
        pass

    @abstractmethod
    def thicken(self, steps):
        pass

    @abstractmethod
    def __str__(self):
        pass

    @abstractmethod
    def __call__(self):
        pass


class SnowFlakeMatrix:
    """Класс для управления матрицей снежинки."""
    def __init__(self, size):
        if size < 1:
            raise ValueError("Размер должен быть положительным.")
        if size % 2 == 0:
            raise ValueError("Размер должен быть нечётным числом.")
        self.size = size
        self.matrix = self.__generate_matrix()

    def __generate_matrix(self):
        N = self.size
        mid = N // 2
        matrix = []
        for i in range(N):
            row = []
            for j in range(N):
                if i == j or (i + j) == (N - 1) or i == mid or j == mid:
                    row.append('*')
                else:
                    row.append(' ')
            matrix.append(row)
        return matrix

    def update_size(self, new_size):
        """Обновляет размер матрицы и перестраивает снежинку."""
        self.size = new_size
        self.matrix = self.__generate_matrix()

    def __str__(self):
        """Возвращает строковое представление матрицы."""
        return '\n'.join([''.join(row) for row in self.matrix])


class SnowFlake(AbstractSnowFlake):
    def __init__(self, size):
        self.__original_size = size
        self.__matrix_handler = SnowFlakeMatrix(size)

    def thaw(self, steps):
        """Уменьшение снежинки."""
        new_size = self.__matrix_handler.size - 2 * steps
        if new_size < 1:
            new_size = 1
        self.__matrix_handler.update_size(new_size)

    def freeze(self, steps):
        """Увеличение снежинки."""
        new_size = self.__matrix_handler.size + 2 * steps
        self.__matrix_handler.update_size(new_size)

    def thicken(self, steps):
        """Восстановление снежинки."""
        new_size = self.__matrix_handler.size + 2 * steps
        if new_size > self.__original_size:
            new_size = self.__original_size
        self.__matrix_handler.update_size(new_size)

    def __str__(self):
        """Возвращает строковое представление снежинки."""
        return str(self.__matrix_handler)

    def __call__(self):
        """Выводит снежинку при вызове объекта."""
        return str(self)


# Пример использования
flake = SnowFlake(11)
print("Изначальная снежинка (11x11):")
print(flake())

flake.thaw(2)
print("\nПосле thaw(2): (теперь 7x7)")
print(flake())

flake.thicken(1)
print("\nПосле thicken(1): (восстановление до 9x9)")
print(flake())

flake.freeze(2)
print("\nПосле freeze(2): (теперь 13x13)")
print(flake())