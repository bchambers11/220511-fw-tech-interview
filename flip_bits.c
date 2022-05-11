#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// #define VERBOSE

typedef enum {
  STATUS_SUCCESS = 0,
  STATUS_ERROR = 1,
} STATUS_CODE;

#define BITS_IN_A_BYTE 8

// Assumes little endian
void print_bits(void const * const ptr, size_t const size) {
  unsigned char *b = (unsigned char*) ptr;
  unsigned char byte;
  int i, j;
  
  for (i = size-1; i >= 0; i--) {
    for (j = 7; j >= 0; j--) {
      byte = (b[i] >> j) & 1;
      printf("%u", byte);
    }
    if (i > 0) {
      printf(" ");
    }
  }
}

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
// TODO: define get_bit function

/**
 * @brief Sets the bit at the given offset to 1.
 * i.e. for 4-byte buffer, offset=31 is msb, offset=0 is lsb.
 * 
 * @param data - little-endian data buffer
 * @param byte_length - byte length of data buffer
 * @param bit_offset - the offset of the bit to set (0 is lsb)
 * @return STATUS_CODE - STATUS_SUCCESS if request okay, STATUS_ERROR if out of bounds request
 */
// TODO: define set_bit function

/**
 * @brief Sets the bit at the given offset to 0.
 * i.e. for 4-byte buffer, offset=31 is msb, offset=0 is lsb.
 * 
 * @param data - little-endian data buffer
 * @param byte_length - byte length of data buffer
 * @param bit_offset - the offset of the bit to clear (0 is lsb)
 * @return STATUS_CODE - STATUS_SUCCESS if request okay, STATUS_ERROR if out of bounds request
 */
// TODO: define clear_bit function

void get_bit_test() {
  uint8_t pass = 0;
  uint8_t fail = 0;
  enum {
    ARR_LENGTH = 4,
  };
  uint8_t i, offset;
  bool result;
  uint8_t arr0[ARR_LENGTH] = {0x00, 0x00, 0x00, 0x00}; // [lsb --> msb]
  uint8_t arr1[ARR_LENGTH] = {0x55, 0x55, 0xAA, 0xAA}; // [lsb --> msb]
  uint8_t arr2[ARR_LENGTH] = {0xFF, 0xFF, 0xFF, 0xFF}; // [lsb --> msb]
  const uint8_t arr0_copy[ARR_LENGTH] = {0x00, 0x00, 0x00, 0x00}; // [lsb --> msb]
  const uint8_t arr1_copy[ARR_LENGTH] = {0x55, 0x55, 0xAA, 0xAA}; // [lsb --> msb]
  const uint8_t arr2_copy[ARR_LENGTH] = {0xFF, 0xFF, 0xFF, 0xFF}; // [lsb --> msb]
  const uint8_t arr_bit_length = (ARR_LENGTH * sizeof(uint8_t) * BITS_IN_A_BYTE);

  puts("== GET BIT ==");

  printf("\t Test 1: \n");
  {
    STATUS_CODE code = get_bit(arr0, ARR_LENGTH, 40, &result);
    if (code == STATUS_ERROR) {
      pass += 1;
      printf("\t\t PASS: STATUS_CODE==STATUS_ERROR\n");
    } else {
      fail += 1;
      printf("\t\t FAIL: STATUS_CODE!=STATUS_ERROR\n");
    }
  }

  printf("\n\t Test 2: ");
  printf("\n\t\t arr0: ");
  for (i = (arr_bit_length); i > 0; i--) {
    offset = i - 1;
    get_bit(arr0, ARR_LENGTH, offset, &result);
    printf("%u", result);
  }

  puts("");

  for (i = (arr_bit_length); i > 0; i--) {
    offset = i - 1;
    get_bit(arr0, ARR_LENGTH, offset, &result);
    if (result == 0) {
      #ifdef VERBOSE
      printf("\t\t PASS: arr0[%u]==%u\n", offset, result);
      #endif
      pass += 1;
    } else {
      #ifdef VERBOSE
      printf("\t\t FAIL: arr0[%u] should equal %u\n", offset, result);
      #endif
      fail += 1;
    }
  }

  printf("\n\t Test 3: ");
  printf("\n\t\t arr1: ");
  for (i = (arr_bit_length); i > 0; i--) {
    offset = i - 1;
    get_bit(arr1, ARR_LENGTH, offset, &result);
    printf("%u", result);
  }

  puts("");

  for (i = (arr_bit_length); i > 0; i--) {
    offset = i - 1;
    get_bit(arr1, ARR_LENGTH, offset, &result);
    if ((offset < 16 && (offset % 2 == 1) && result == 0)
      || (offset < 16 && (offset % 2 == 0) && result == 1)
      || (offset >= 16 && (offset % 2 == 1) && result == 1)
      || (offset >= 16 && (offset % 2 == 0) && result == 0)
    ) {
      #ifdef VERBOSE
      printf("\t\t PASS: arr1[%u]==%u\n", offset, result);
      #endif
      pass += 1;
    } else {
      #ifdef VERBOSE
      printf("\t\t FAIL: arr1[%u] should equal %u\n", offset, result);
      #endif
      fail += 1;
    }
  }

  printf("\n\t Test 4: ");
  printf("\n\t\t arr2: ");
  for (i = (arr_bit_length); i > 0; i--) {
    offset = i - 1;
    get_bit(arr2, ARR_LENGTH, offset, &result);
    printf("%u", result);
  }

  puts("");

  for (i = (arr_bit_length); i > 0; i--) {
    offset = i - 1;
    get_bit(arr2, ARR_LENGTH, offset, &result);
    if (result == 1) {
      #ifdef VERBOSE
      printf("\t\t PASS: arr2[%u]==%u\n", offset, result);
      #endif
      pass += 1;
    } else {
      #ifdef VERBOSE
      printf("\t\t FAIL: arr2[%u] should equal %u\n", offset, result);
      #endif
      fail += 1;
    }
  }

  printf("\t Test 5: \n");
  {
    printf("\t\t Verify data is unmodified \n\n");
    printf("\t\t Comparing arr0 == arr0_copy: \n\t\t ");
    print_bits(arr0, sizeof(arr0));
    printf("\n\t\t ");
    print_bits(arr0_copy, sizeof(arr0_copy));
    puts("");

    if (memcmp(arr0, arr0_copy, ARR_LENGTH) == 0) {
      puts("\t\t PASS arr0==arr0_copy\n");
      pass += 1;
    } else {
      puts("\t\t FAIL arr0==arr0_copy should be true\n");
      fail += 1;
    }

    printf("\t\t Comparing arr1 == arr1_copy: \n\t\t ");
    print_bits(arr1, sizeof(arr1));
    printf("\n\t\t ");
    print_bits(arr1_copy, sizeof(arr1_copy));
    puts("");

    if (memcmp(arr1, arr1_copy, ARR_LENGTH) == 0) {
      puts("\t\t PASS arr1==arr1_copy\n");
      pass += 1;
    } else {
      puts("\t\t FAIL arr1==arr1_copy should be true\n");
      fail += 1;
    }

    printf("\t\t Comparing arr2 == arr2_copy: \n\t\t ");
    print_bits(arr2, sizeof(arr2));
    printf("\n\t\t ");
    print_bits(arr2_copy, sizeof(arr2_copy));
    puts("");

    if (memcmp(arr2, arr2_copy, ARR_LENGTH) == 0) {
      puts("\t\t PASS arr2==arr2_copy\n");
      pass += 1;
    } else {
      puts("\t\t FAIL arr2==arr2_copy should be true\n");
      fail += 1;
    }
  }

  printf("\n\t GET BIT (%u tests) :: Pass [%u], Fail [%u]\n", pass + fail, pass, fail);
}

void set_bit_test() {
  uint8_t pass = 0;
  uint8_t fail = 0;
  enum {
    ARR_LENGTH = 4,
  };
  const uint8_t test1_arr0_copy[ARR_LENGTH] = {0x00, 0x00, 0x00, 0x00}; // [lsb --> msb]
  uint8_t test1_arr0[ARR_LENGTH] = {0x00, 0x00, 0x00, 0x00}; // [lsb --> msb]
  uint8_t test1_arr1[ARR_LENGTH] = {0xAA, 0xAA, 0xAA, 0xAA}; // [lsb --> msb]
  uint8_t test2_arr0[ARR_LENGTH] = {0x00, 0x00, 0x00, 0x00}; // [lsb --> msb]
  uint8_t test2_arr1[ARR_LENGTH] = {0xFF, 0xFF, 0xFF, 0xFF}; // [lsb --> msb]
  const uint8_t arr_bit_length = (ARR_LENGTH * sizeof(uint8_t) * BITS_IN_A_BYTE);

  puts("\n\n == SET BIT ==\n");

  printf("\t Test 1: \n");
  {
    STATUS_CODE code = set_bit(test1_arr0, ARR_LENGTH, 40);
    if (code == STATUS_ERROR) {
      pass += 1;
      printf("\t\t PASS: STATUS_CODE==STATUS_ERROR\n");
    } else {
      fail += 1;
      printf("\t\t FAIL: STATUS_CODE!=STATUS_ERROR\n");
    }
    if (memcmp(test1_arr0, test1_arr0_copy, ARR_LENGTH) == 0) {
      puts("\t\t PASS test1_arr0==test1_arr0_copy (data unmodified after failure)\n");
      pass += 1;
    } else {
      puts("\t\t FAIL test1_arr0!=test1_arr0_copy (data modified after failure)\n");
      printf("\t\t ");
      print_bits(test1_arr0, sizeof(test1_arr0));
      printf("\n\t\t ");
      print_bits(test1_arr0_copy, sizeof(test1_arr0_copy));
      fail += 1;
    }
  }

  printf("\n\t Test 2: \n");
  for (uint8_t i = (arr_bit_length); i > 0; i--) {
    uint8_t offset = i - 1;
    if (offset % 2 == 1) {
      set_bit(test1_arr0, ARR_LENGTH, offset);
    }
  }

  printf("\t\t Comparing arr0 == arr1: \n\t\t ");
  print_bits(test1_arr0, sizeof(test1_arr0));
  printf("\n\t\t ");
  print_bits(test1_arr1, sizeof(test1_arr1));
  puts("");

  if (memcmp(test1_arr0, test1_arr1, ARR_LENGTH) == 0) {
    puts("\t\t PASS arr0==arr1\n");
    pass += 1;
  } else {
    puts("\t\t FAIL arr0==arr1 should be true\n");
    fail += 1;
  }

  printf("\t Test 3: \n");
  for (uint8_t i = (arr_bit_length); i > 0; i--) {
    uint8_t offset = i - 1;
    set_bit(test2_arr0, ARR_LENGTH, offset);
  }

  printf("\t\t Comparing arr0 == arr1: \n\t\t ");
  print_bits(test2_arr0, sizeof(test2_arr0));
  printf("\n\t\t ");
  print_bits(test2_arr1, sizeof(test2_arr1));
  puts("");

  if (memcmp(test2_arr0, test2_arr1, ARR_LENGTH) == 0) {
    puts("\t\t PASS arr0==arr1\n");
    pass += 1;
  } else {
    puts("\t\t FAIL arr0==arr1 should be true\n");
    fail += 1;
  }

  printf("\n\t SET BIT (%u tests) :: Pass [%u], Fail [%u]\n", pass + fail, pass, fail);
}

void clear_bit_test() {
  uint8_t pass = 0;
  uint8_t fail = 0;
  enum {
    ARR_LENGTH = 4,
  };
  uint8_t test1_arr0[ARR_LENGTH] = {0x55, 0x55, 0x55, 0x55}; // [lsb --> msb]
  uint8_t test1_arr1[ARR_LENGTH] = {0xFF, 0xFF, 0xFF, 0xFF}; // [lsb --> msb]
  uint8_t test2_arr0[ARR_LENGTH] = {0xFF, 0xFF, 0xFF, 0xFF}; // [lsb --> msb]
  uint8_t test2_arr1[ARR_LENGTH] = {0x00, 0x00, 0x00, 0x00}; // [lsb --> msb]
  const uint8_t arr_bit_length = (ARR_LENGTH * sizeof(uint8_t) * BITS_IN_A_BYTE);

  puts("\n\n == CLEAR BIT ==\n");

  printf("\t Test 1: \n");
  for (uint8_t i = (arr_bit_length); i > 0; i--) {
    uint8_t offset = i - 1;
    if (offset % 2 == 1) {
      clear_bit(test1_arr1, ARR_LENGTH, offset);
    }
  }

  printf("\t\t Comparing arr0 == arr1: \n\t\t ");
  print_bits(test1_arr0, sizeof(test1_arr0));
  printf("\n\t\t ");
  print_bits(test1_arr1, sizeof(test1_arr1));
  puts("");

  if (memcmp(test1_arr0, test1_arr1, ARR_LENGTH) == 0) {
    puts("\t\t PASS arr0==arr1\n");
    pass += 1;
  } else {
    puts("\t\t FAIL arr0==arr1 should be true\n");
    fail += 1;
  }

  printf("\t Test 2: \n");
  for (uint8_t i = (arr_bit_length); i > 0; i--) {
    uint8_t offset = i - 1;
    clear_bit(test2_arr0, ARR_LENGTH, offset);
  }

  printf("\t\t Comparing arr0 == arr1: \n\t\t ");
  print_bits(test2_arr0, sizeof(test2_arr0));
  printf("\n\t\t ");
  print_bits(test2_arr1, sizeof(test2_arr1));
  puts("");

  if (memcmp(test2_arr0, test2_arr1, ARR_LENGTH) == 0) {
    puts("\t\t PASS arr0==arr1\n");
    pass += 1;
  } else {
    puts("\t\t FAIL arr0==arr1 should be true\n");
    fail += 1;
  }

  printf("\n\t CLEAR BIT (%u tests) :: Pass [%u], Fail [%u]\n", pass + fail, pass, fail);
}

int main() {
  get_bit_test();
  set_bit_test();
  clear_bit_test();
  puts("");
  return 0;
}
