# Buffer Library

This library provides a generic buffer implementation in C that supports various operations such as initialization, destruction, data writing, buffer copying, and file data writing.

## Features

- Generic buffer implementation
- Dynamic buffer expansion
- Writing data to buffer
- Writing strings to buffer
- Writing file data to buffer
- Buffer copying
- Error handling

## Installation

To use the buffer library, include the `buffer.h` file in your project:

```c
#include "buffer.h"
```

## Usage

### Buffer Initialization

Initialize a buffer with a specified capacity:

```c
Buffer intBuffer;
bufferInitialize(&intBuffer, 10);
```

### Writing Data to Buffer

Write data to the buffer:

```c
int data[] = {1, 2, 3, 4, 5};
writeDataToBuffer(&intBuffer, data, 5);
```

### Writing Strings to Buffer

Write a string to a character buffer:

```c
Buffer charBuffer;
bufferInitialize(&charBuffer, 10);
const char* str = "Hello, Buffer!";
writeStringToBuffer(&charBuffer, str);
```

### Writing File Data to Buffer

Write the contents of a file to a character buffer:

```c
writeFileDataToBuffer(&charBuffer, "test.txt");
```

### Buffer Copying

Copy the contents of one buffer to another:

```c
Buffer intBufferCopy;
bufferCopy(&intBuffer, &intBufferCopy);
```

### Buffer Destruction

Destruct a buffer to free allocated memory:

```c
bufferDestruct(&intBuffer);
bufferDestruct(&charBuffer);
bufferDestruct(&intBufferCopy);
```

## Error Handling

The library uses an enumeration `bufferError` to handle various error conditions:

- `NO_BUFFER_ERROR`
- `POINTER_IS_NULL`
- `DOUBLE_IS_NAN`
- `FILE_OPEN_ERROR`
- `FILE_READ_ERROR`
- `STAT_ERROR`
- `CALLOC_ERROR`
- `VALUE_ERROR`
- `INPUT_ERROR`
- `PROGRAM_ERROR`

## Example

Here is a complete example demonstrating the usage of the buffer library:

```c
#include "buffer.h"
#include <stdio.h>

int main() {
    Buffer<int> intBuffer;
    Buffer<char> charBuffer;

    // Initialize buffers
    bufferInitialize(&intBuffer, 10);
    bufferInitialize(&charBuffer, 10);

    // Write data to int buffer
    int intData[] = {1, 2, 3, 4, 5};
    writeDataToBuffer(&intBuffer, intData, 5);

    // Write string to char buffer
    const char* str = "Hello, Buffer!";
    writeStringToBuffer(&charBuffer, str);

    // Copy int buffer
    Buffer<int> intBufferCopy;
    bufferCopy(&intBuffer, &intBufferCopy);

    // Write file data to char buffer
    writeFileDataToBuffer(&charBuffer, "test.txt");

    // Destruct buffers
    bufferDestruct(&intBuffer);
    bufferDestruct(&charBuffer);
    bufferDestruct(&intBufferCopy);

    return 0;
}
```
