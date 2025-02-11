from random import randint

class Warrior:
    def SetHP(self, value):
        self.hp = value;
    def Kick(enemy):
        enemy.hp -= 20

warrior1 = Warrior()
warrior2 = Warrior()
warrior1.SetHP(100)
warrior2.SetHP(100)

while (warrior1.hp != 0 and warrior2.hp !=0):
    c = randint(1, 2)
    if c == 1:
        Warrior.Kick(warrior2)
        print(f"Первый воин атаковал второго.\nОставшееся здоровье второго = {warrior2.hp}\n")
    else:
        Warrior.Kick(warrior1)
        print(f"Второй воин атаковал первого.\nОставшееся здоровье первого = {warrior1.hp}\n")

if warrior1.hp == 0:
    print("Победил второй воин!")
elif warrior2.hp == 0:
    print("Победил первый воин!")