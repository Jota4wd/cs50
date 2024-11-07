def main():

    while True:
        user_input = input("Change owed: ")
        if user_input.strip() == "":
            continue

        try:
            change = float(user_input)
            if change > 0:
                break
        except ValueError:
            continue

    cents = round(change * 100)
    coins = 0

    while cents > 0:
        if cents >= 25:
            cents -= 25
        elif cents >= 10:
            cents -= 10
        elif cents >= 5:
            cents -=5
        else:
            cents -= 1
        coins += 1

    print(coins)

main()


# formatado para usar a ide cs50
#  import cs50

#  def main():

    #  while True:
        #  change = cs50.get_float("Change owed: ")
        #  if change > 0:
                #  break

    #  cents = round(change * 100)
    #  coins = 0

    #  while cents > 0:
        #  if cents >= 25:
            #  cents -= 25
        #  elif cents >= 10:
            #  cents -= 10
        #  elif cents >= 5:
            #  cents -=5
        #  else:
            #  cents -= 1
        #  coins += 1

    #  print(coins)

#  main()

