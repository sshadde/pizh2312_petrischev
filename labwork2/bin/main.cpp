#include <lib/number.h>
#include <iostream>

int main() {
    // Создаем максимально возможное значение, где все слова = 0xFFFFFFFF
    uint2022_t max_value;
    for (int i = 0; i < uint2022_t::SIZE; ++i) {
        max_value.data[i] = 0xFFFFFFFF;
    }

    // Создаем единицу
    uint2022_t one = from_uint(1);

    // Складываем: max_value + 1
    uint2022_t result = max_value + one;

    // Выводим результат
    std::cout << "Max value: ";
    std::cout << max_value << std::endl;

    std::cout << "One: ";
    std::cout << one << std::endl;

    std::cout << "Result (Max + 1): ";
    std::cout << result << std::endl;

    // Проверка: Max + 1 == 0 (переполнение)
    if (result == from_uint(0)) {
        std::cout << "Переполнение работает правильно!" << std::endl;
    } else {
        std::cout << "Что-то пошло не так..." << std::endl;
    }

    return 0;
}
