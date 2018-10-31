# find a way to replace the do while loop
while True:
    """this is a valid way of doing it"""
    height = input("please enter a number: ")
    if height.isdigit() and int(height) >= 0 and int(height) <= 23:
        height = int(height)
        break
# the range function is very interesting and deserves more study
for i in range(1, height + 1):
    # this loop prints spaces
    for j in range(height - i):
        print(' ', end='')
    # this loop prints the #
    for k in range(i):
        print("#", end='')
    print('  ', end='')
    for k in range(i):
        print("#", end='')
    print()