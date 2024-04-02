# TODO
def main():
    # User input
    text = input("Text: ")

    # Counting
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Coleman-Liau index
    index = round(
        0.0588 * ((letters / words) * 100) - 0.296 * ((sentences / words) * 100) - 15.8
    )

    # Printing
    if index > 16:
        print("Grade 16+")
    elif index < 1:
        print("Before Grade 1")
    else:
        print(f"Grade {index}")


def count_letters(text):
    n = len(text)
    letters = 0
    for i in range(n):
        if text[i].isalpha():
            letters += 1
    return letters


def count_words(text):
    n = len(text)
    words = 1
    for i in range(n):
        if text[i].isspace():
            words += 1
    return words


def count_sentences(text):
    n = len(text)
    sentences = 0
    for i in range(n):
        if text[i] in [".", "!", "?"]:
            sentences += 1
    return sentences


main()
