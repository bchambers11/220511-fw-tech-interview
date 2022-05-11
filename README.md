# Firmware Engineering Tech Interview

## Overview

Clone this repo and make your changes how you see fit. Submit changes via pull requests to `main` in this repo.

## Checksums

Write a Markdown file called `checksums.md` answering the following question:

> What are checksums and what are they useful for?

__Submit your changes via a pull request to this repository.__

## Debugging

Write a Markdown file called `debugging.md` answering the following question:

> How would you go about locating the cause of a stack overflow or watchdog timer reset?

__Submit your changes via a pull request to this repository.__

## Fun with bits

In this repo you'll find [./flip_bits.c](./flip_bits.c). This file contains 3 sets of tests for functions that need to be defined. Each function has to do with bit manipulation of a data buffer. Each function's return value should be of type `STATUS_CODE`.

```c
typedef enum {
  STATUS_SUCCESS = 0,
  STATUS_ERROR = 1,
} STATUS_CODE;
```

### `get_bit`

Function Documentation:

```c
/**
 * @brief Gets result of the value of the bit at the bit_offset for the given
 * data buffer of byte_length. i.e. for 4-byte buffer, offset=31 is msb, offset=0 is lsb.
 * 
 * @param data - little-endian data buffer
 * @param byte_length - byte length of data buffer
 * @param bit_offset - the offset of the bit to retrieve (0 is lsb)
 * @param result - binary value to store the result
 * @return STATUS_CODE - STATUS_SUCCESS if request okay, STATUS_ERROR if out of bounds request
 */
```

Example:

```c
uint8_t data = 0b1;
bool result = 0;

STATUS_CODE code = get_bit(&data, sizeof(data), 0, &result);
printf("result: %u, code: %s\n", result, code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR"); // result=1, code == STATUS_SUCCESS
code = get_bit(&data, sizeof(data), 1, &result);
printf("result: %u, code: %s\n", result, code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR"); // result=0, code == STATUS_SUCCESS
code = get_bit(&data, sizeof(data), 8, &result);
printf("result: %u, code: %s\n", result, code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR"); // result=0 (unchanged), code == STATUS_ERROR

data = 0b10;
code = get_bit(&data, sizeof(data), 0, &result);
printf("result: %u, code: %s\n", result, code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR"); // result=0, code == STATUS_SUCCESS
code = get_bit(&data, sizeof(data), 1, &result);
printf("result: %u, code: %s\n", result, code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR"); // result=1, code == STATUS_SUCCESS
code = get_bit(&data, sizeof(data), 8, &result);
printf("result: %u, code: %s\n", result, code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR"); // result=1 (unchanged), code == STATUS_ERROR
```

### `set_bit`

Function Documentation:

```c
/**
 * @brief Sets the bit at the given offset to 1.
 * i.e. for 4-byte buffer, offset=31 is msb, offset=0 is lsb.
 * 
 * @param data - little-endian data buffer
 * @param byte_length - byte length of data buffer
 * @param bit_offset - the offset of the bit to set (0 is lsb)
 * @return STATUS_CODE - STATUS_SUCCESS if request okay, STATUS_ERROR if out of bounds request
 */
```

Example:

```c
uint8_t data = 0b1;

STATUS_CODE code = set_bit(&data, sizeof(data), 0);
printf("code: %s, data: %u\n", code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR", data); // code == STATUS_SUCCESS, data=1
code = set_bit(&data, sizeof(data), 1);
printf("code: %s, data: %u\n", code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR", data); // code == STATUS_SUCCESS, data=3
code = set_bit(&data, sizeof(data), 8);
printf("code: %s, data: %u\n", code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR", data); // code == STATUS_ERROR, data=3 (unchanged)

data = 0b10;
code = set_bit(&data, sizeof(data), 0);
printf("code: %s, data: %u\n", code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR", data); // code == STATUS_SUCCESS, data=3
code = set_bit(&data, sizeof(data), 1);
printf("code: %s, data: %u\n", code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR", data); // code == STATUS_SUCCESS, data=3
code = set_bit(&data, sizeof(data), 8);
printf("code: %s, data: %u\n", code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR", data); // code == STATUS_ERROR, data=3 (unchanged)
```

### `clear_bit`

Function Documentation:

```c
/**
 * @brief Sets the bit at the given offset to 0.
 * i.e. for 4-byte buffer, offset=31 is msb, offset=0 is lsb.
 * 
 * @param data - little-endian data buffer
 * @param byte_length - byte length of data buffer
 * @param bit_offset - the offset of the bit to clear (0 is lsb)
 * @return STATUS_CODE - STATUS_SUCCESS if request okay, STATUS_ERROR if out of bounds request
 */
```

Example:

```c
uint8_t data = 0b1;

STATUS_CODE code = clear_bit(&data, sizeof(data), 0);
printf("code: %s, data: %u\n", code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR", data); // code == STATUS_SUCCESS, data=0
code = clear_bit(&data, sizeof(data), 1);
printf("code: %s, data: %u\n", code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR", data); // code == STATUS_SUCCESS, data=0
code = get_bit(&data, sizeof(data), 8);
printf("code: %s, data: %u\n", code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR", data); // code == STATUS_ERROR, data=0 (unchanged)

data = 0b10;
code = clear_bit(&data, sizeof(data), 0);
printf("code: %s, data: %u\n", code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR", data); // code == STATUS_SUCCESS, data=2
code = clear_bit(&data, sizeof(data), 1);
printf("code: %s, data: %u\n", code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR", data); // code == STATUS_SUCCESS, data=0
code = clear_bit(&data, sizeof(data), 8);
printf("code: %s, data: %u\n", code == STATUS_SUCCESS ? "STATUS_SUCCESS" : "STATUS_ERROR", data); // code == STATUS_ERROR, data=0 (unchanged)
```

Define the 3 functions above however you see fit to get the tests found in `flip_bits.c` to pass. The tests should be unchanged and there are is a helper function `print_bits` that can print the binary bits of a data buffer for you. You can also uncomment the `#define VERBOSE` to print out all of the tests in the `get_bit` tests.

__Submit your changes via a pull request to this repository.__
