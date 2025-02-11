from room import Room

print("Размеры помещения:")
l = float(input("Длина - "))
w = float(input("Ширина - "))
h = float(input("Высота - "))
r1 = Room(l, w, h)
flag = input("Есть неоклеиваемая поверхность? (1 - да, 2 - нет) ")

while flag == '1':
    w = float(input("Ширина - "))
    h = float(input("Высота - "))
    r1.addWD(w, h) 
    flag = input("Добавить еще? (1 - да, 2 - нет) ")

print("Размеры рулона:")
l = float(input("Длина - "))
w = float(input("Ширина - "))
print("Площадь оклейки", r1.workSurface())
print("Количество рулонов", r1.wallpapers(l, w))