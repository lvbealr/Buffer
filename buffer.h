#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "customWarning.h"
#include "colorPrint.h"
#include "bufferDefinitions.h"

template <typename T>
inline bufferError readFile(Buffer<T> *bufferStruct, const char* filename) {
    customWarning(bufferStruct,  POINTER_IS_NULL);
    customWarning(filename,      POINTER_IS_NULL);

    FILE* file = fopen(filename, "r");
    customWarning(file, POINTER_IS_NULL);

    getSizeOfBuffer(&(bufferStruct->size), filename);

    bufferStruct->data = (T* )calloc(size_t (bufferStruct->size + 1), sizeof(T));
    customWarning(bufferStruct->data, CALLOC_ERROR);

    scanFileToBuffer<T>(bufferStruct, filename);

    return NO_ERRORS;
}

inline bufferError getSizeOfBuffer(int *size, const char *filename) {
    customWarning(size,     POINTER_IS_NULL);
    customWarning(filename, POINTER_IS_NULL);

    struct stat bufferInformation = {};

    int statCheck = stat(filename, &bufferInformation);
    customWarning(statCheck != -1, STAT_ERROR);

    *size = (int) bufferInformation.st_size;

    return NO_ERRORS;
}

template <typename T>
inline bufferError scanFileToBuffer(Buffer<T> *bufferStruct, const char *filename) {
    customWarning(bufferStruct,  POINTER_IS_NULL);
    customWarning(filename,      POINTER_IS_NULL);

    customPrint(red, bold, bgDefault, "Please specialize type for %s | FILE: %s | LINE: %d\n",\
                __func__, __FILE__, __LINE__);

    return NO_ERRORS;
}

template <>
inline bufferError scanFileToBuffer<char>(Buffer<char> *bufferStruct, const char *filename) {
    customWarning(bufferStruct,      POINTER_IS_NULL);
    customWarning(filename,          POINTER_IS_NULL);
    customWarning(bufferStruct != 0, FILE_READ_ERROR);

    FILE *file = fopen(filename, "r");
    customWarning(file, FILE_OPEN_ERROR);

    fread(bufferStruct->data, sizeof(char), (size_t) bufferStruct->size, file);

    fclose(file);

    return NO_ERRORS;
}

inline bufferError getLinePointerFromFile(Buffer<char *> *bufferStruct, Buffer<char> *text) {
    customWarning(bufferStruct, POINTER_IS_NULL);
    customWarning(text,         POINTER_IS_NULL);

    bufferStruct->size = countLines(text);

    bufferStruct->data = (char **)calloc((size_t) (bufferStruct->size + 1), sizeof(char *));
    customWarning(bufferStruct->data, CALLOC_ERROR);

    int lineIndex = 1;
    bufferStruct->data[0] = text->data;
    for(int index = 0; index < text->size; index++) {
        if(text->data[index] == '\n') {
            bufferStruct->data[lineIndex] = &(text->data[index + 1]);
            lineIndex++;
        }
    }

    printf("> %s", bufferStruct->data[0]);

    return NO_ERRORS;
}

template <typename T>
inline int countLines(Buffer<T> *bufferStruct) {
    customWarning(bufferStruct, POINTER_IS_NULL);

    customPrint(red, bold, bgDefault, "Please specialize type for %s | FILE: %s | LINE: %d\n",\
                __func__, __FILE__, __LINE__);

    return NO_ERRORS;
}

template <typename T>
inline bufferError bufferDestruct(Buffer<T> *bufferStruct) {
    customWarning(bufferStruct, POINTER_IS_NULL);

    customPrint(red, bold, bgDefault, "Please specialize type for %s | FILE: %s | LINE: %d\n",\
                __func__, __FILE__, __LINE__);

    return NO_ERRORS;
}

#endif
