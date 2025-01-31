#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

#include "customWarning.h"
#include "colorPrint.h"

enum bufferError {
    NO_BUFFER_ERROR =  0,
    POINTER_IS_NULL =  1,
    DOUBLE_IS_NAN   =  2,
    FILE_OPEN_ERROR =  3,
    FILE_READ_ERROR =  4,
    STAT_ERROR      =  5,
    CALLOC_ERROR    =  6,
    VALUE_ERROR     =  7,
    INPUT_ERROR     =  8,
    PROGRAM_ERROR   =  9,
    BUFFER_ENDED    = 10,
    NO_BUFFER       = 11
};

template <typename T>
struct Buffer {
    size_t capacity     = 0;
    size_t currentIndex = 0;

    T *data             = NULL;
};

#define FREE_(ptr) { \
    free(ptr);       \
    ptr = NULL;      \
}

// FUNCTION PROTOTYPES //
template<typename T>
bufferError bufferInitialize     (Buffer<T>    *buffer, size_t      capacity = 0);
template<typename T>
bufferError bufferDestruct       (Buffer<T>    *buffer);
template<typename T>
bufferError writeDataToBuffer    (Buffer<T>    *buffer, const void *data, size_t dataSize);
template<typename T>
bufferError bufferCopy           (Buffer<T>    *src,    Buffer<T>  *dest);
template<typename T> 
bufferError bufferExpand         (Buffer<T>    *buffer, size_t      dataSize);
inline
bufferError writeStringToBuffer  (Buffer<char> *buffer, const char *string);
inline
bufferError writeFileDataToBuffer(Buffer<char> *buffer, const char *fileName);
// FUNCTION PROTOTYPES //

template<typename T>
bufferError bufferInitialize(Buffer<T> *buffer, size_t capacity) {
    customWarning(buffer != NULL, bufferError::POINTER_IS_NULL);

    buffer->capacity = capacity;

    buffer->data = (T *)calloc(buffer->capacity, sizeof(T));
    customWarning(buffer->data != NULL, bufferError::CALLOC_ERROR);

    return bufferError::NO_BUFFER_ERROR;
}

template<typename T>
bufferError bufferDestruct(Buffer<T> *buffer) {
    customWarning(buffer != NULL, bufferError::POINTER_IS_NULL);

    FREE_(buffer->data);

    return bufferError::NO_BUFFER_ERROR;
}

template<typename T>
bufferError writeDataToBuffer(Buffer<T> *buffer, const void *data, size_t dataSize) {
    customWarning(buffer != NULL, bufferError::POINTER_IS_NULL);
    customWarning(data   != NULL, bufferError::POINTER_IS_NULL);

    if (buffer->capacity == 0) {
        buffer->capacity = 1;
    }

    bufferExpand(buffer, dataSize);

    for (size_t dataIndex = 0; dataIndex < dataSize; dataIndex++) {
        buffer->data[buffer->currentIndex++] = ((const T *)data)[dataIndex];
    }

    return bufferError::NO_BUFFER_ERROR;
}

template<typename T>
bufferError bufferCopy(Buffer<T> *src, Buffer<T> *dest) {
    customWarning(src  != NULL, bufferError::POINTER_IS_NULL);
    customWarning(dest != NULL, bufferError::POINTER_IS_NULL);

    dest->capacity     = src->capacity;
    dest->currentIndex = src->currentIndex;

    dest->data = (T *)calloc(dest->capacity, sizeof(T));
    customWarning(dest->data != NULL, bufferError::CALLOC_ERROR);

    memcpy(dest->data, src->data, src->currentIndex * sizeof(T));

    return bufferError::NO_BUFFER_ERROR;
}

template<typename T>
bufferError bufferExpand(Buffer<T> *buffer, size_t dataSize) {
    customWarning(buffer != NULL, bufferError::POINTER_IS_NULL);

    while (dataSize > buffer->capacity - buffer->currentIndex) {
        buffer->capacity *= 2;
    }

    buffer->data = (T *)realloc(buffer->data, buffer->capacity * sizeof(T));
    customWarning(buffer->data != NULL, bufferError::CALLOC_ERROR);

    return bufferError::NO_BUFFER_ERROR;
}

inline bufferError writeStringToBuffer(Buffer<char> *buffer, const char *string) {
    return writeDataToBuffer(buffer, string, strlen(string));
}

inline bufferError writeFileDataToBuffer(Buffer<char> *buffer, const char *fileName) {
    customWarning(buffer   != NULL, bufferError::POINTER_IS_NULL);
    customWarning(fileName != NULL, bufferError::POINTER_IS_NULL);

    if (buffer->capacity == 0) {
        buffer->capacity = 1;
    }

    struct stat bufferInfo = {};

    int statCheck = stat(fileName, &bufferInfo);
    customWarning(statCheck != -1, bufferError::STAT_ERROR);

    int fileSize = bufferInfo.st_size;

    int openFile = open(fileName, O_RDONLY);
    customWarning(openFile != -1, bufferError::FILE_OPEN_ERROR);

    bufferExpand(buffer, fileSize);

    int readFile = read(openFile, buffer->data + buffer->currentIndex, fileSize);
    customWarning(readFile == fileSize, bufferError::FILE_READ_ERROR);

    buffer->currentIndex += fileSize;

    return bufferError::NO_BUFFER_ERROR;
}

#endif // BUFFER_H_