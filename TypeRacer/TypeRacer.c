#include <conio.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define TEXT_SIZE 201
#define WORD_SIZE 10

int RandomNumber(const int min, const int max) {
    return min + rand() % (max - min + 1);
}

void AddNewWord(char* newWord, const size_t newWordSize, const bool startWithUpperCase, const char* alphabet) {
    int randomLength = RandomNumber(1, WORD_SIZE - 1); // Ensure there's space for null terminator
    int alphabetLength = strlen(alphabet);
    for (int i = 0; i < randomLength; i++) {
        int alphabetIndex = RandomNumber(0, alphabetLength - 1);
        char newCharacter = alphabet[alphabetIndex];
        if (i == 0 && startWithUpperCase) {
            newCharacter = toupper(newCharacter);
        }
        newWord[i] = newCharacter;
    }
    newWord[randomLength] = '\0'; // Null-terminate the new word
}

const char* GetRandomWordEnding(const char* wordEndings[]) {
    int rndmNmbr = RandomNumber(0, 100);
    if (rndmNmbr <= 65) {
        return wordEndings[0];
    }
    else if (rndmNmbr <= 88) {
        return wordEndings[1];
    }
    else {
        return wordEndings[2];
    }
}

int main()
{
    srand(time(NULL));
    const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    const char* wordEndings[] = { " ", ". ", ", " };

    char outputText[TEXT_SIZE] = "";
    char newWord[WORD_SIZE] = "";
    double wpm = 0;

    bool startWithUppercase = true;
    while (strlen(outputText) + WORD_SIZE < TEXT_SIZE) {
        AddNewWord(newWord, WORD_SIZE, startWithUppercase, alphabet);
        startWithUppercase = false;
        strcat(outputText, newWord);

        const char* wordEnding = GetRandomWordEnding(wordEndings);
        if (wordEnding == wordEndings[1]) {
            startWithUppercase = true;
        }
        strcat(outputText, wordEnding);

        if (strlen(outputText) + strlen(wordEnding) >= TEXT_SIZE - 1) break;
    }

    clock_t start = clock();
    int wordsTyped = 0;
    bool updateWPN = true;
    while (strlen(outputText) != 0) {
        system("cls");
        printf("WPM: ");
        printf("%f", wpm);
        updateWPN = false;
        printf("\n\n");

        printf(outputText);
        printf("\n\n");

        int keyInt = _getch();
        char keyChar = (char)keyInt;

        if (keyChar == outputText[0]) {
            if (outputText[0] == ' ') {
                wordsTyped++;
                updateWPN = true;
            }
            memmove(outputText, outputText + 1, strlen(outputText));
        }
        else {
            printf("False");
        }

        if (updateWPN) {
            clock_t temp = clock();
            double elapsed_time = (double)(temp - start) / CLOCKS_PER_SEC;
            wpm = (double)(wordsTyped / elapsed_time) * 60;
        }
    }

    // Stop timer
    printf("Final WPM: ");
    printf("%f", wpm);
}