def main():
    while True:
        nbr = input("cartao: ")

        if nbr.isdigit() and int(nbr) > 0:
            nbr = int(nbr)
            break

    luhn = cs_luhn(nbr)
    operadora = cs_operadoras(nbr)

    if luhn == 0 or operadora == 0:
        print("INVALID")
    elif operadora == 1:
        print("AMEX")
    elif operadora == 2:
        print("MASTERCARD")
    elif operadora == 3:
        print("VISA")


def cs_digits(nbr):
    qty = 0

    while nbr > 0:
        qty += 1
        nbr //= 10

    return qty


def cs_luhn(nbr):
    multiplos = 0
    simples = 0

    while nbr > 0:
        simples += nbr % 10
        nbr = nbr // 10
        digit = (nbr % 10) * 2
        if digit > 9:
            digit = (digit % 10) + ((digit // 10) % 10)
        multiplos += digit
        nbr = nbr // 10

    total = multiplos + simples

    if total % 10 == 0:
        return True
    else:
        return False


def cs_operadoras(nbr):
    len = cs_digits(nbr)

    while nbr >= 100:
        nbr //= 10

    if (nbr == 34 or nbr == 37) and len == 15:
        return 1
    elif (nbr >= 51 and nbr <= 55) and len == 16:
        return 2
    elif (nbr >= 40 and nbr <= 49) and (len == 13 or len == 16):
        return 3
    else:
        return 0


main()
