import random

secret_number =  random.randint(0, 20)
number_of_guess = 0


while number_of_guess < 4:
    print("Guess a number between 1 and 20")
    guess = input()
    Guess = int(guess)

    number_of_guess += 1
    
    if Guess == secret_number:
        output = str(secret_number)
        print(f"good job, the random number was {output}")
        break6

else:
    result = str(secret_number)
    print(f"The correct answer was {result}")
    print("Sorry, it looks like you are out of chances")


