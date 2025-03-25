from random import randint
import pygame

SCREEN_WIDTH, SCREEN_HEIGHT = 640, 480
GRID_SIZE = 20
GRID_WIDTH = SCREEN_WIDTH // GRID_SIZE
GRID_HEIGHT = SCREEN_HEIGHT // GRID_SIZE
GRID_COLOR = (40, 40, 40)
UP = (0, -1)
DOWN = (0, 1)
LEFT = (-1, 0)
RIGHT = (1, 0)
BOARD_BACKGROUND_COLOR = (0, 0, 0)
BORDER_COLOR = (0, 0, 0)
APPLE_COLOR = (255, 0, 0)
SNAKE_COLOR = (0, 255, 0)
TEXT_COLOR = (255, 255, 255)
SPEED = 10
FONT_SIZE = 24
SCORE_FILE = "highscore.txt"

screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT), 0, 32)
pygame.display.set_caption('Змейка')
clock = pygame.time.Clock()
pygame.font.init()
font = pygame.font.Font(None, FONT_SIZE)

class GameObject: 
    """
    Базовый класс для игровых объектов.

    Поля:
    - position: Положение объекта на экране.
    - body_color: Цвет объекта.

    Методы:
    - draw(): Отрисовка объекта.
    """
    def __init__(self, position = (0, 0), body_color = (255, 255, 255)):
        """
        Инициализирует игровой объект с заданным положением и цветом.
        Результат: Создание экземпляра GameObject.
        """
        self.position = position
        self.body_color = body_color
    
    def draw(self):
        """
        Отрисовка объекта.
        Результат: Отрисовывает объект на экране (метод-заглушка).
        """
        pass
    
class Apple(GameObject):
    """
    Класс яблока, наследуемый от GameObject, представляет яблоко на игровом поле.

    Поля:
    - position: Положение яблока.
    - body_color: Цвет яблока.

    Методы:
    - randomize_position(snake_positions): Назначает новое случайное положение яблока, не совпадающее с позицией змейки.
    - draw(): Отрисовывает яблоко на экране.
    """
    def __init__(self):
        """
        Инициализирует объект Apple, устанавливая случайное положение.
        Результат: Создание объекта Apple с заданным положением и цветом.
        """
        super().__init__((0, 0), APPLE_COLOR)
        self.randomize_position([])
    
    def randomize_position(self, snake_positions):
        """
        Случайно назначает положение яблока, не совпадающее с частями змейки.
        
        Параметры:
        - snake_positions: Список позиций частей змейки.
        
        Результат: Обновляет атрибут position, устанавливая новое положение яблока.
        """
        while True:
            new_position = (randint(0, GRID_WIDTH - 1) * GRID_SIZE, randint(0, GRID_HEIGHT - 1) * GRID_SIZE)
            if new_position not in snake_positions:
                self.position = new_position
                break

    def draw(self):
        """
        Отрисовывает яблоко на экране.
        Результат: Рисует прямоугольник яблока и его рамку на игровом экране.
        """
        rect = pygame.Rect(self.position, (GRID_SIZE, GRID_SIZE))
        pygame.draw.rect(screen, self.body_color, rect)
        pygame.draw.rect(screen, BORDER_COLOR, rect, 1)

class Snake(GameObject):
    """
    Класс змейки, наследуемый от GameObject, управляет логикой движения и отображения змейки.

    Поля\Атрибуты:
    - length: Длина змейки.
    - positions: Список позиций сегментов змейки, где первая позиция – голова.
    - direction: Текущее направление движения змейки.
    - next_direction: Следующее направление движения, ожидающее обновления.

    Методы:
    - reset(): Сбрасывает состояние змейки при столкновении с собой, обновляя рекорд если необходимо.
    - update_direction(): Обновляет направление змейки, если задано новое направление.
    - move(): Перемещает змейку, обновляя положение головы и удаляя последний сегмент при необходимости.
    - get_head_position(): Возвращает позицию головы змейки.
    - draw(): Отрисовывает змейку на экране.
    """
    def __init__(self):
        """
        Инициализирует змейку с начальной позицией в центре экрана, длиной 1 и направлением вправо.
        Результат: Создание объекта Snake.
        """
        super().__init__((SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2), SNAKE_COLOR)
        self.length = 1
        self.positions = [self.position]
        self.direction = RIGHT
        self.next_direction = None
    
    def reset(self):
        """
        Сбрасывает состояние змейки при столкновении с собой, обновляя рекорд если необходимо.
        Результат: Сбрасывает длину и позиции змейки, устанавливая начальное направление.
        """
        global high_score
        if self.length > high_score:
            high_score = self.length
            save_high_score(high_score)
        self.length = 1
        self.positions = [self.position]
        self.direction = RIGHT
        self.next_direction = None

    def update_direction(self):
        """
        Обновляет направление змейки, если задано новое направление.
        Результат: Переназначает значение атрибута direction из next_direction и сбрасывает next_direction.
        """
        if self.next_direction:
            self.direction = self.next_direction
            self.next_direction = None

    def move(self):
        """
        Перемещает змейку, обновляя положение головы и удаляя последний сегмент, если длина превышена.
        Результат: Обновляет список позиций змейки; при столкновении с собой вызывает сброс змейки.
        """
        head_x, head_y = self.positions[0]
        dir_x, dir_y = self.direction
        new_position = ((head_x + dir_x * GRID_SIZE) % SCREEN_WIDTH, 
                        (head_y + dir_y * GRID_SIZE) % SCREEN_HEIGHT)
        
        if new_position in self.positions:
            self.reset()
        else:
            self.positions.insert(0, new_position)
            if len(self.positions) > self.length:
                self.positions.pop()

    def get_head_position(self):
        """
        Возвращает текущую позицию головы змейки.
        Результат: Позиция головы змейки в виде кортежа (x, y).
        """
        return self.positions[0]

    def draw(self):
        """
        Отрисовывает змейку на экране.
        Результат: Рисует каждый сегмент змейки с рамкой.
        """
        for position in self.positions:
            rect = (pygame.Rect(position, (GRID_SIZE, GRID_SIZE)))
            pygame.draw.rect(screen, self.body_color, rect)
            pygame.draw.rect(screen, BORDER_COLOR, rect, 1)

def draw_grid():
    """
    Рисует сетку на игровом экране.
    Результат: Отрисовывает линии сетки на экране.
    """
    for x in range(0, SCREEN_WIDTH, GRID_SIZE):
        pygame.draw.line(screen, GRID_COLOR, (x, 0), (x, SCREEN_HEIGHT))
    for y in range(0, SCREEN_HEIGHT, GRID_SIZE):
        pygame.draw.line(screen, GRID_COLOR, (0, y), (SCREEN_WIDTH, y))

def draw_score(score, high_score):
    """
    Отрисовывает текущий счет и рекорд на экране.
    
    Параметры:
    - score: Текущий счет змейки.
    - high_score: Рекорд.
    
    Результат: Рисует текст с информацией о счете на экране.
    """
    score_text = font.render(f"Счет: {score}  Рекорд: {high_score}", True, TEXT_COLOR)
    screen.blit(score_text, (10, 10))

def load_high_score():
    """
    Загружает рекорд из файла.
    Результат: Возвращает рекордное значение в виде целого числа.
    """
    with open(SCORE_FILE, "r") as f:
        return int(f.read().strip())

def save_high_score(score):
    """
    Сохраняет новый рекорд в файл.
    
    Параметры:
    - score: Новый рекорд.
    
    Результат: Обновляет содержимое файла рекордов.
    """
    with open(SCORE_FILE, "w") as f:
        f.write(str(score))

high_score = load_high_score()

def handle_keys(game_object):
    """
    Обрабатывает события клавиатуры для управления змейкой и завершения игры.
    
    Параметры:
    - game_object: Объект змейки, для которого обрабатываются события.
    
    Результат: Обновляет направление змейки или завершает игру при нажатии клавиши.
    """
    global high_score
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            raise SystemExit
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                if game_object.length > high_score:
                    high_score = game_object.length
                    save_high_score(high_score)
                pygame.quit()
                raise SystemExit
            if event.key == pygame.K_UP and game_object.direction != DOWN:
                game_object.next_direction = UP
            elif event.key == pygame.K_DOWN and game_object.direction != UP:
                game_object.next_direction = DOWN
            elif event.key == pygame.K_LEFT and game_object.direction != RIGHT:
                game_object.next_direction = LEFT
            elif event.key == pygame.K_RIGHT and game_object.direction != LEFT:
                game_object.next_direction = RIGHT

def main():
    """
    Основной цикл игры, в котором происходит обновление состояния игры и отрисовка объектов.
    Результат: Запускает игровой цикл, обновляет экран и обрабатывает события до выхода из игры.
    """

    pygame.init()
    apple = Apple()
    snake = Snake()
    while True:
        clock.tick(SPEED)
        handle_keys(snake)
        snake.update_direction()
        snake.move()
        
        if snake.get_head_position() == apple.position:
            snake.length += 1
            apple.randomize_position(snake.positions)
        
        screen.fill(BOARD_BACKGROUND_COLOR)
        draw_grid()
        snake.draw()
        apple.draw()
        draw_score(snake.length, high_score)
        pygame.display.update()

if __name__ == '__main__':
    main()