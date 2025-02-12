from random import randint

class Person:
    count = 0
    def __init__(self, c):
        self.id = Person.count
        Person.count += 1
        self.command = c

class Hero(Person):
    def __init__(self, c):
        Person.__init__(self, c)
        self.lvl = 1
    def LvlUp(self):
        self.lvl += 1

class Soldier(Person):
    def __init__(self, c):
        Person.__init__(self, c)
        self.hero = None
    def FollowHero(self, h):
        self.hero = h.id

h1 = Hero(1)
h2 = Hero(2)
command1 = []
command2 = []

for i in range(20):
    a = randint(1, 2)
    if a == 1:
        command1.append(Soldier(a))
    else:
        command2.append(Soldier(a))

print(len(command1), len(command2))

if len(command1) > len(command2):
    h1.LvlUp()
else:
    h2.LvlUp()

command1[0].FollowHero(h1)
print(command1[0].id, h1.id)