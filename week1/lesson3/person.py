class Person:
    def __init__(self, n, s, q = 1):
        self.name = n
        self.surname = s
        self.qualify = q
    def getInfo(self):
        print(self.name, self.surname, self.qualify)
    def __del__(self):
        print("До свидания, мистер", self.name, self.surname)

person1 = Person('Jeff', 'Bezos', 3)
person2 = Person('Mark', 'Zuckerberg', 2)
person3 = Person('John', 'Johnson')
person1.getInfo()
person2.getInfo()
person3.getInfo()
del person3
input()