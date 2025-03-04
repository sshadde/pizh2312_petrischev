from money import Money

if __name__ == "__main__":
    money1 = Money(100, "USD")
    money2 = Money(50, "USD")
    money3 = Money.from_string("200 USD")
    
    print("Money 1:", money1)
    print("Money 2:", money2)
    print("Money 3 (from string):", money3)
    
    sum_money = money1 + money2
    print("Sum:", sum_money)
    
    diff_money = money1 - money2
    print("Difference:", diff_money)
    
    converted_money = money1.convert(0.85, "EUR")
    print("Converted Money:", converted_money)
    
    multiplied_money = money1.multiply(2)
    print("Multiplied Money:", multiplied_money)
    
    divided_money = money1.divide(4)
    print("Divided Money:", divided_money)
    
    money1.save("money.json")
    
    loaded_money = Money(0, "")
    loaded_money.load("money.json")
    print("Loaded Money:", loaded_money)

# -------------------
# Пример вывода:
# -------------------
# Money 1: 100.00 USD
# Money 2: 50.00 USD
# Money 3 (from string): 200.00 USD
# Sum: 150.00 USD
# Difference: 50.00 USD
# Converted Money: 85.00 EUR
# Multiplied Money: 200.00 USD
# Divided Money: 25.00 USD
# Loaded Money: 100.00 USD

# -------------------
# Значение файла:
# -------------------
# {"amount": 100, "currency": "USD"}