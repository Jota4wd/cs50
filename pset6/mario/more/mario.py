def main():
    while True:
        height = int(input("Height: "))
        if height < 1 or height > 8:
            break

        for i in range(height):
            print(" " * (height - i - 1), end="")
            print("#" * (i + 1))
