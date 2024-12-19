#ifndef BUFFER_DEFINITIONS_H_
#define BUFFER_DEFINITIONS_H_

enum bufferError {
    NO_ERRORS       = 0,
    POINTER_IS_NULL = 1,
    DOUBLE_IS_NAN   = 2,
    FILE_OPEN_ERROR = 3,
    FILE_READ_ERROR = 4,
    STAT_ERROR      = 5,
    CALLOC_ERROR    = 6,
    VALUE_ERROR     = 7,
    INPUT_ERROR     = 8,
    PROGRAM_ERROR   = 9,
};

template <typename T>
struct Buffer {
    T  *data = NULL;
    int size = 0;
};

template <typename T> inline bufferError readFile                  (Buffer<T>*      bufferStruct,  const char   *filename);
template <typename T> inline bufferError scanFileToBuffer          (Buffer<T>*      bufferStruct,  const char   *filename);
template <          > inline bufferError scanFileToBuffer<char>    (Buffer<char>   *bufferStruct,  const char   *filename);
bufferError           inline             getSizeOfBuffer           (int*            size,          const char   *filename);
template <typename T> inline int         countLines                (Buffer<T>      *bufferStruct);
template <typename T> inline bufferError bufferDestruct            (Buffer<T>      *bufferStruct);

#endif
