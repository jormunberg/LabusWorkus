#ifndef UNTITLED_TASKS_STRING_H
#define UNTITLED_TASKS_STRING_H

#include "../string_.h"

# define MAX_N_WORDS_IN_STRING 100
# define MAX_WORD_SIZE 20
#define MAX_STRING_SIZE 100
#define MAX_UNCHAR 128

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

typedef enum WordBeforeFirstWordWithAReturnCode {
    FIRST_WORD_WITH_A,
    NOT_FOUND_A_WORD_WITH_A,
    WORD_FOUND,
    EMPTY_STRING
} WordBeforeFirstWordWithAReturnCode;


BagOfWords _bag;
BagOfWords _bag2;

char _stringBuffer[MAX_STRING_SIZE + 1];

// Возвращает указатель на последний элемент строки.
char *getEndOfString(char *s);

//удалит из строки все пробельные символы.
void removeNonLetters(char *s);

//Сокращает количество пробелов между словами данного предложения до одного
void removeExtraSpaces(char *s);

//Преобразовывает строку, обратив каждое слово этой строки.
void reverseWorld(char *s);

//
void spaceInsteadOfNumber(char *s);

//
void replace(char *source, char *w1, char *w2);

//Проверка слов слова
int strcmpWord(WordDescriptor w1, WordDescriptor w2);

//Проверяет, упорядочены ли слова в строке по алфавиту.
int orderedAlphabetically(char *s);

//Проверяет, является ли слово палиндромом.
bool isPalindromeWords(WordDescriptor w);

//Определяет количество слов-палиндромов.
int numberPalindromeWords(char *s);

void outputWordsReverse(char *s);

//
void alternatingLines(char *s1, char *s2, char *s3);

void linesReverse(char *s);

void printWordBeforeFirstWordWithA(char *s);

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, WordDescriptor *wordBefore);

void wordDescriptorToString(WordDescriptor w, char *destination);

WordDescriptor lastWordInFirstStringInSecondString(char *s1, char *s2);

bool identicalWordsLine(char *s);

bool wordsMadeIdenticalLetters(char *s);

void allExceptLastOne(char *s);

WordDescriptor precedingFirstOccurrence(char *s1, char *s2);

void deletePalindromeWords(char *s);

void stringAddition(char *s1, char *s2);

bool allLettersInString(char *str, WordDescriptor w);


#endif //UNTITLED_TASKS_STRING_H