def main():

    text = input("Text: ")
    letters = 0
    words = 0
    in_word = 0
    sentences = 0

    for char in text:
        if char.isalpha():
            if in_word == 0:
                in_word = 1
                words += 1
            letters += 1
        elif char in ['.', '!', '?']:
            sentences += 1
        elif char == ' ':
            in_word = 0
        
    cs_coleman_liau(letters, words, sentences)

def cs_coleman_liau(letters, words, sentences):
    l = (letters / words) * 100
    s = (sentences / words) * 100
    index = 0.0588 * l - 0.296 * s - 15.8

    rank = cs_round(index)

    if rank > 16:
        print("Grade 16+")
    elif rank < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {rank}")

def cs_round(nbr):
    interger = int(nbr)
    decimal = float(nbr - interger)

    if decimal >= 0.5:
        return interger + 1
    else:
        return interger

main()
