#include "string_.h"
#include <ctype.h>

size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;

    return end - begin;
}

char *find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;

    return begin;
}

char *findNonSpace(char *begin) {
    char *end = begin;
    while (*end != '\0') {
        if (!isspace(*end))
            return end;
        end++;
    }

    return end;
}

char *findSpace(char *begin) {
    char *end = begin;
    while (*end != '\0') {
        if (isspace(*end))
            return end;
        end++;
    }

    return end;
}

char *findNonSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin != rend) {
        if (!isspace(*rbegin))
            return rbegin;
        rbegin--;
    }

    return rbegin;
}

char *findSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin != rend) {
        if (isspace(*rbegin))
            return rbegin;
        rbegin--;
    }

    return rbegin;
}

int strcmp(const char *lhs, const char *rhs) {
    while (*lhs != 0 && *lhs == *rhs) {
        lhs++, rhs++;
    }

    return *lhs - *rhs;
}

char *copy(const char *beginSource, const char *endSource, char *beginDestination) {
    char *end = beginSource;
    while (end < endSource) {
        *beginDestination = *end;
        beginDestination++;
        end++;
    }

    return beginDestination;
}

char *copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)) {
    char *end = beginSource;
    while (end != endSource) {
        if (f(*end)) {
            *beginDestination = *end;
            beginDestination++;
        }
        end++;
    }
    return beginDestination;
}

char *copyIfReverse(char *rbeginSource, const char *rendSource, char *beginDestination, int (*f)(int)) {
    char *end = rbeginSource;
    while (end != rendSource) {
        if (f(*end)) {
            *beginDestination = *end;
            beginDestination++;
        }
        end--;
    }
    return beginDestination;
}