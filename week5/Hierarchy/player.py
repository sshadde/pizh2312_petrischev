class Player:
    """
    Базовый класс плеера.

    Открытые поля:
      - title (str): Название контента.

    Защищённые поля:
      - _playing (bool): Флаг, указывающий, запущен ли плеер.

    Закрытые поля:
      - __secret_key (str): Закрытый ключ, не доступен вне класса.

    Открытые методы:
      - запустить(): Запускает воспроизведение.
      - остановить(): Останавливает воспроизведение.

    Защищённые методы:
      - _info(): Выводит служебную информацию (не предназначен для вызова извне).

    Закрытые методы:
      - __secret_method(): Демонстрация закрытого метода (не виден за пределами класса).
    """

    def __init__(self, title: str):
        """
        Инициализация плеера.

        Параметры:
          - title (str): Название или идентификатор воспроизводимого контента.
        """
        self.title = title           # открытое поле
        self._playing = False        # защищённое поле
        self.__secret_key = "XYZ123" # закрытое поле

    def запустить(self):
        """
        Открытый метод: Запускает воспроизведение.
        """
        if not self._playing:
            self._playing = True
            print(f"Плеер запущен: {self.title}")
        else:
            print(f"Плеер уже запущен: {self.title}")

        self._info()  # Вызов защищённого метода
        # Вызов закрытого метода внутри класса
        self.__secret_method()

    def остановить(self):
        """
        Открытый метод: Останавливает воспроизведение.
        """
        if self._playing:
            self._playing = False
            print(f"Плеер остановлен: {self.title}")
        else:
            print(f"Плеер уже остановлен: {self.title}")

    def _info(self):
        """
        Защищённый метод: выводит служебную информацию о плеере.
        """
        print("Вызван защищённый метод _info в Player")

    def __secret_method(self):
        """
        Закрытый метод: демонстрирует, что он не доступен вне класса.
        """
        print("Вызван закрытый метод __secret_method в Player\n")


class AudioPlayer(Player):
    """
    Класс аудиоплеера, наследуется от Player.

    Открытые поля:
      - audio_format (str): Формат аудио (mp3, wav и т.д.).

    Защищённые поля:
      - _bitrate (int): Битрейт аудио.

    Закрытые поля:
      - __license_key (str): Лицензионный ключ, не доступен извне класса.

    Переопределённые методы:
      - запустить()
      - остановить()

    Собственные методы:
      - set_format() — открытый метод
      - _check_bitrate() — защищённый метод
      - __validate_license() — закрытый метод
    """

    def __init__(self, title: str, audio_format: str, bitrate: int = 320):
        """
        Инициализация аудиоплеера.

        Параметры:
          - title (str): Название трека или альбома.
          - audio_format (str): Формат аудио (mp3, wav, и т.д.).
          - bitrate (int): Битрейт (по умолчанию 320 кбит/с).
        """
        super().__init__(title)
        self.audio_format = audio_format  # открытое поле
        self._bitrate = bitrate           # защищённое поле
        self.__license_key = "AUDIO-123"  # закрытое поле

    def запустить(self):
        """
        Открытый метод: Запускает воспроизведение аудио, добавляя логику аудиоплеера.
        """
        print(f"Подготовка аудиоплеера с форматом: {self.audio_format}")
        self._check_bitrate()       # защищённый метод
        self.__validate_license()   # закрытый метод
        super().запустить()

    def остановить(self):
        """
        Открытый метод: Останавливает воспроизведение аудио.
        """
        print(f"Остановка аудиоплеера (формат: {self.audio_format})")
        super().остановить()

    def set_format(self, new_format: str):
        """
        Открытый метод: Устанавливает новый аудиоформат.
        """
        self.audio_format = new_format
        print(f"Новый формат аудио: {self.audio_format}")

    def _check_bitrate(self):
        """
        Защищённый метод: Проверяет корректность битрейта.
        """
        if self._bitrate <= 0:
            print("Некорректный битрейт!")
        else:
            print(f"Проверка битрейта: {self._bitrate} кбит/с")

    def __validate_license(self):
        """
        Закрытый метод: Проверка лицензионного ключа.
        """
        print(f"Проверка лицензионного ключа: {self.__license_key}")


class VideoPlayer(Player):
    """
    Класс видеоплеера, наследуется от Player.

    Открытые поля:
      - resolution (str): Разрешение видео (например, 1080p).

    Защищённые поля:
      - _framerate (int): Количество кадров в секунду.

    Закрытые поля:
      - __video_code (str): Внутренний код для обработки видео.

    Переопределённые методы:
      - запустить()
      - остановить()

    Собственные методы:
      - set_resolution() — открытый метод
      - _check_framerate() — защищённый метод
      - __decode_video() — закрытый метод
    """

    def __init__(self, title: str, resolution: str, framerate: int = 30):
        """
        Инициализация видеоплеера.

        Параметры:
          - title (str): Название видео.
          - resolution (str): Разрешение видео (720p, 1080p, 4K и т.д.).
          - framerate (int): Частота кадров (по умолчанию 30).
        """
        super().__init__(title)
        self.resolution = resolution     # открытое поле
        self._framerate = framerate      # защищённое поле
        self.__video_code = "VIDEO-999"  # закрытое поле

    def запустить(self):
        """
        Открытый метод: Запускает воспроизведение видео, добавляя логику видеоплеера.
        """
        print(f"Подготовка видеоплеера с разрешением: {self.resolution}")
        self._check_framerate()   # защищённый метод
        self.__decode_video()     # закрытый метод
        super().запустить()

    def остановить(self):
        """
        Открытый метод: Останавливает воспроизведение видео.
        """
        print(f"Остановка видеоплеера (разрешение: {self.resolution})")
        super().остановить()

    def set_resolution(self, new_resolution: str):
        """
        Открытый метод: Устанавливает новое разрешение видео.
        """
        self.resolution = new_resolution
        print(f"Новое разрешение: {self.resolution}")

    def _check_framerate(self):
        """
        Защищённый метод: Проверяет корректность частоты кадров.
        """
        if self._framerate <= 0:
            print("Некорректная частота кадров!")
        else:
            print(f"Частота кадров: {self._framerate} fps")

    def __decode_video(self):
        """
        Закрытый метод: Декодирует видео (условно).
        """
        print(f"Декодирование с кодом: {self.__video_code}")


class DvdPlayer(VideoPlayer):
    """
    Класс DVD-плеера, наследуется от VideoPlayer.
    (Можно было напрямую от Player, но логично расширять функционал VideoPlayer.)

    Открытые поля:
      - disk_title (str): Название (или основное содержимое) DVD.

    Защищённые поля:
      - _region_code (int): Региональный код DVD.

    Закрытые поля:
      - __dvd_key (str): Закрытый ключ DVD.

    Переопределённые методы:
      - запустить()
      - остановить()

    Собственные методы:
      - set_disk() — открытый метод
      - _check_region() — защищённый метод
      - __unlock_dvd() — закрытый метод
    """

    def __init__(self, title: str, resolution: str, disk_title: str, region_code: int = 1):
        """
        Инициализация DVD-плеера.

        Параметры:
          - title (str): Название воспроизводимого видео.
          - resolution (str): Разрешение (например, 1080p).
          - disk_title (str): Название (или путь к) DVD-диску.
          - region_code (int): Региональный код DVD (по умолчанию 1).
        """
        super().__init__(title, resolution)
        self.disk_title = disk_title      # открытое поле
        self._region_code = region_code   # защищённое поле
        self.__dvd_key = "DVD-777"        # закрытое поле

    def запустить(self):
        """
        Открытый метод: Запускает воспроизведение DVD, учитывая особенности DVD-плеера.
        """
        print(f"Подготовка DVD-плеера. Диск: {self.disk_title}")
        self._check_region()   # защищённый метод
        self.__unlock_dvd()    # закрытый метод
        super().запустить()

    def остановить(self):
        """
        Открытый метод: Останавливает воспроизведение DVD.
        """
        print(f"Завершение работы с DVD: {self.disk_title}")
        super().остановить()

    def set_disk(self, new_disk_title: str):
        """
        Открытый метод: Заменяет DVD-диск.
        """
        self.disk_title = new_disk_title
        print(f"Новый DVD-диск: {self.disk_title}")

    def _check_region(self):
        """
        Защищённый метод: Проверяет региональный код DVD.
        """
        if self._region_code not in (1, 2, 3, 4, 5, 6):
            print(f"Неизвестный региональный код: {self._region_code}")
        else:
            print(f"Региональный код DVD: {self._region_code}")

    def __unlock_dvd(self):
        """
        Закрытый метод: Разблокирует DVD (условно).
        """
        print(f"Разблокировка с ключом: {self.__dvd_key}")
