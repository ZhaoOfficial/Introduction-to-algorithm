n = 154851
currency = [1, 5, 10, 25, 100]

number = dict(zip(currency, [0 for _ in range(5)]))

for i in range(4, -1, -1):
    number[currency[i]] = n // currency[i]
    n %= currency[i]

print(number)