import math

BASE = 10
# get int from user
while True:
    card_number = input("Credit Card number: ")
    if card_number.isdigit() and int(card_number) >= 1:
        break
number_of_digits = len(card_number)

card_number = int(card_number)

# check if valid

card_sum = 0
isValid = False

for i in range(number_of_digits):
    temp1 = card_number % math.pow(BASE, (i + 1)) // math.pow(BASE, i)
    if i % 2 != 0:
        temp1 *= 2
        # I need to split the number if it has more than one digit
        # add those products' digits (i.e., not the products themselves) together: exm 14, 1 + 4
        if temp1 > 9:
            temp1 = temp1 % BASE + temp1 // BASE
        card_sum += temp1
    else:
        card_sum += temp1
# if the total modulo 10 is congruent to 0, the number is valid!

if card_sum % 10 == 0:
    isValid = True
if isValid == False:
    print("INVALID")
else:
    # every card has a set length and a prefix number
    # check for Visa
    if number_of_digits == 13:
        start_num = card_number // math.pow(BASE, 12)
        if start_num == 4:
            print("VISA")
        else:
            print("INVALID")

        # check for AMEX
    if number_of_digits == 15:
        start_num = card_number // math.pow(BASE, 13)
        if start_num == 34 or start_num == 37:
            print("AMEX")
        else:
            print("INVALID")

    # check visaMasterCard
    if number_of_digits == 16:
        start_num = card_number // math.pow(BASE, 15)
        if start_num == 4:
            print("VISA")
        elif start_num == 5:
            start_num = card_number // math.pow(BASE, 14)
            if start_num == 55 or start_num == 54 or start_num == 53 or start_num == 52 or start_num == 51:
                print("MASTERCARD")
            else:
                print("INVALID")
        else:
            print("INVALID")

