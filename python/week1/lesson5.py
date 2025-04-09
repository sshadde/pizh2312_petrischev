class Rectangle:
    def __init__(self, w, h, s):
        self.width = int(w)
        self.height = int(h)
        self.sign = str(s)
    def __str__(self):
        rectang = []
        for i in range(self.height):
            rectang.append(self.sign * self.width)
        rectang = '\n'.join(rectang)
        return rectang
    def __add__(self, other):
        return Rectangle(self.width + other.width, self.height + other.height, self.sign)
        
a = Rectangle(4, 2, 'w')
print(a)
b = Rectangle(8, 3, 'z')
print(b)
print(a + b)
print(b + a)