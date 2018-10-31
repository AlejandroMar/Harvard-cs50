import sys

UPPCASE = 65
LOWCASE = 97
ALPHALENGTH = 26


def main():
    if len(sys.argv) != 2:
        print("Please type two arguments")
        exit(1)

    else:
        # Check if all charaters in argv are alphabetic
        if not sys.argv[1].isalpha():
            print("The key must contain only alphabetic letters")
            exit(1)

        # declare variables
        keyword = sys.argv[1]
        keyword_length = len(sys.argv[1])
        plain_text = input("plaintext: ")
        plain_text_length = len(plain_text)
        # here put the encoded characters
        cipher_text = ''
        keyword_index = 0

        # text gets encripted inside the loop
        for char in plain_text:
            # check plain_text case
            if char.isupper():
                # check keyword[i] case
                if keyword[keyword_index % keyword_length].isupper():
                    # keywordIndex % keywordLength, allows me to wrap around the key, so I never get an index > keyLength
                    encripted_ascii_upper = chr(
                        (ord(char) - UPPCASE + ord(keyword[keyword_index % keyword_length]) - UPPCASE) % ALPHALENGTH + UPPCASE)

                elif keyword[keyword_index % keyword_length].lower():
                    encripted_ascii_upper = chr(
                        (ord(char) - UPPCASE + ord(keyword[keyword_index % keyword_length]) - LOWCASE) % ALPHALENGTH + UPPCASE)

                cipher_text += encripted_ascii_upper
                keyword_index += 1

            elif char.islower():
                if keyword[keyword_index % keyword_length].isupper():
                    encripted_ascii_lower = chr(
                        (ord(char) - LOWCASE + ord(keyword[keyword_index % keyword_length]) - UPPCASE) % ALPHALENGTH + LOWCASE)

                elif keyword[keyword_index % keyword_length].islower():
                    encripted_ascii_lower = chr(
                        (ord(char) - LOWCASE + ord(keyword[keyword_index % keyword_length]) - LOWCASE) % ALPHALENGTH + LOWCASE)

                cipher_text += encripted_ascii_lower
                keyword_index += 1
            else:
                cipher_text += char

        print(f"ciphertext: {cipher_text}")
        exit(0)


if __name__ == "__main__":
    main()