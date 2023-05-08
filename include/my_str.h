/*
** EPITECH PROJECT, 2022
** my_str
** File description:
** my_str declarations
*/

#ifndef INCLUDE_MY_STR_
    #define INCLUDE_MY_STR_
    #include <stddef.h>
    #include <string.h>

    #include "my_cstr.h"
    #include "my_vec.h"

    #define STR_TMP_ST (64)

    /**
    * @brief creates a temporary string (max size: 256)
    */
    #define STR(s) ((str_t *) (&(__str_temp_t){strlen(s), STR_TMP_ST, s}))

typedef struct {
    size_t length;
    size_t capacity;
    char data[STR_TMP_ST];
} __str_temp_t;

typedef struct str_s {
    size_t length;
    size_t capacity;
    char data[0];
} str_t;

VEC_DEF(str_t *, str)

/**
 * @brief creates a string with a given capacity
 *
 * @param n the capacity of the string
 * @return the string
 */
str_t *str_screate(size_t n);

/**
 * @brief converts a long int to a string
 *
 * @param nb the long int to convert
 * @return the string
 */
str_t *my_itostr(long int nb);

/**
 * @brief converts a double to a string
 *
 * @param nb the double to convert
 * @param precision the precision of the double
 * @return the string
 */
str_t *my_ftostr(double nb, int precision);

/**
 * @brief null terminates the data to be used as a c string
 *
 * @param str the string to null terminate
 * @return the string data null terminated
 */
char const *str_tocstr(str_t const *str);

/**
 * @brief splits a string into a vector of strings
 *
 * @param str       string to split
 * @param delims    string of delimiters,
 *                  if NULL or delims->length == 0 split by char
 * @return split string as a vector
 */
vec_str_t *str_split(str_t *str, str_t *delims);

/**
 * @brief finds the first occurence of a string in another string
 *
 * @param str  the string to search in
 * @param find  the string to search for
 * @param start  the index to start searching from
 * @return the index of the first occurence of find in str
 */
long str_find(str_t const *str, str_t *find, size_t start);

/**
 * @brief finds the last occurence of a string in another string
 *
 * @param str  the string to search in
 * @param find  the string to search for
 * @return  the index of the last occurence of find in str
 */
long str_findlast(str_t const *str, str_t *find);

/**
 * @brief replace all occurences of old with new in a string
 *
 * @param str   the string to perform the replacement on
 * @param old   the string to replace
 * @param src   the string to replace with
 */
void str_replace(str_t **str, str_t const *old, str_t const *src);

/**
 * @brief joins a vector of strings
 *
 * @param vec   the vector to join
 * @param delim the delimitor to add between each elem
 * @return the string of the joined vector
 */
str_t *str_join(vec_str_t *vec, str_t *delim);

/**
 * @brief checks if a string is composed of only alphanumeric characters
 *
 * @param str   the string to perform the check on
 * @return 1 or 0
 */
int str_isalpha(str_t const *str);

/**
 * @brief checks if a string is composed of only alphanumeric characters
 *
 * @param str  the string to perform the check on
 * @return 1 or 0
 */
int str_isalphanum(str_t const *str);

/**
 * @brief checks if a string is composed of only digits
 *
 * @param str   the string to perform the check on
 * @return 1 or 0
 */
int str_isnum(str_t const *str);

/**
 * @brief checks if a string is composed of only lowercase letters
 *
 * @param str   the string to perform the check on
 * @return 1 or 0
 */
int str_islower(str_t const *str);

/**
 * @brief checks if a string is composed of only uppercase letters
 *
 * @param str   the string to perform the check on
 * @return 1 or 0
 */
int str_isupper(str_t const *str);

/**
 * @brief creates a string
 *
 * @param init      char* to init the string
 * @return a string
 */
str_t *str_create(char const *init);

/**
 * @brief creates a string with given number of characters
 *
 * @param init      char* to init the string
 * @param n         number of characters in init
 * @return a string
 */
str_t *str_ncreate(char const *init, size_t n);

/**
 * @brief checks if str starts with start
 *
 * @param str       string to perform the check on
 * @param start     start string
 * @return 1 if the string starts with start or 0 if it doesn't
 */
int str_startswith(str_t const *str, str_t const *start);

/**
 * @brief checks if str ends with end
 *
 * @param str   string to prerform the check on
 * @param end   end string
 * @return 1 if the string ends with end or 0 if it doesn't
 */
int str_endswith(str_t const *str, str_t const *end);

/**
 * @brief slices a string
 *
 * @param str       string to slice
 * @param start     start of slice
 * @param end       end of slice
 * @return the sliced string
 */
str_t **str_slice(str_t **str, size_t start, size_t end);

/**
 * @brief compares 2 strings
 *
 * @param s1    first string to compare
 * @param s2    second string to compare
 * @return <0, 0 or >0 if s1 is respectively smaller, equal or greater than s2
 */
int str_compare(str_t const *s1, str_t const *s2);

/**
 * @brief compares the n first characters of 2 strings
 *
 * @param s1    first string to compare
 * @param s2    second string to compare
 * @return <0, 0 or >0 if s1 is respectively smaller, equal or greater than s2
 */
int str_ncompare(str_t const *s1, str_t const *s2, size_t n);

/**
 * @brief checks if a string contains a character
 *
 * @param str   string to check
 * @param c     character to check
 * @return 1 or 0 if the character is in the string or isn't
 */
int str_contains(str_t const *str, char c);

/**
 * @brief duplicates a string (with malloc)
 *
 * @param old   string to duplicate
 * @return the duplicate of the old string
 */
str_t *str_dup(str_t const *old);

/**
 * @brief resizes a string
 *
 * @param str       string to resize
 * @param new_size  new size of the string
 * @return the string resized to a longer length
 */
str_t **str_resize(str_t **str, size_t new_size);

/**
 * @brief adds a char* to a string
 *
 * @param str   destination string
 * @param src   char* to add
 * @return the string with the char* added to its content
 */
str_t **str_add(str_t **str, char const *src);

/**
 * @brief adds n characters of a char* to a string
 *
 * @param str   destination string
 * @param src   char* to add
 * @param n     number of characters to add
 * @return the string with n characters added to its content
 */
str_t **str_nadd(str_t **str, char const *src, size_t n);

/**
 * @brief clears a string
 *
 * @param str   string to clear
 * @return the string cleared
 */
str_t **str_clear(str_t **str);

/**
 * @brief trims the left side of a string
 *
 * @param str   string to trim
 * @param pad   character to remove while trimming
 * @return the string with its content trimmed on the left
 */
str_t **str_ltrim(str_t **str, char pad);

/**
 * @brief trims the right side of a string
 *
 * @param str   string to trim
 * @param pad   character to remove while trimming
 * @return the string with its content trimmed on the right
 */
str_t **str_rtrim(str_t **str, char pad);

/**
 * @brief trims both sides of a string
 *
 * @param str   string to trim
 * @param pad   character to remove while trimming
 * @return the string with its content trimmed on both sides
 */
str_t **str_trim(str_t **str, char pad);

/**
 * @brief prints a string to the stdout
 *
 * @param str   string to print
 */
void str_print(str_t const *str);

/**
 * @brief prints a string to the stdout with an added newline
 *
 * @param str   string to print
 */
void str_println(str_t const *str);

/**
 * @brief prints a string to a given fd
 *
 * @param fd  fd to print to
 * @param str string to print
 */
void str_dprint(int fd, str_t const *str);

/**
 * @brief adds mutliple char* to a string
 *
 * @param str   destination string
 * @param argc  number of char* to add
 * @param ...   char* to add
 * @return string with all the char* added to its content
 */
str_t **str_vadd(str_t **str, int argc, ...);

/**
 * @brief adds a character to a string
 *
 * @param str   destination string
 * @param src   character to add
 * @return string with the character added to its content
 */
str_t **str_cadd(str_t **str, char const chr);

/**
 * @brief concatenates a string to another one
 *
 * @param str   destination string
 * @param src   string to add
 * @return the concatenation of the 2 strings stored in str
 */
str_t **str_sadd(str_t **str, str_t const *src);

/**
 * @brief remove a character at a given index
 *
 * @param str  string to remove the character from
 * @param idx  index of the character to remove
 * @return  the string with the character removed
 */
str_t **str_erase_at_idx(str_t **str, size_t idx);

/**
 * @brief checks if 2 strings are equal
 *
 * @param s1    string 1
 * @param s2    string 2
 * @return 1 if string 1 and string 2 are equal or 0
 */
int str_eq(str_t const *s1, str_t const *s2);

/**
 * @brief converts a string to an int
 *
 * @param str   the ADRESS of string to extract the integer from
 * @return the integer represented by the string
 */
long int str_toint(str_t const *str);

/**
 * @brief converts a string to a double
 *
 * @param str   the ADRESS of string to extract the double from
 * @return the double represented by the string
 */
double str_tofloat(str_t const *str);

/**
 * @brief reverses a string in memory
 *
 * @param str   the string to reverse
 * @return the string reversed
 */
str_t *str_reverse(str_t *str);

/**
 * @brief creates a substring of a given string
 *
 * @param str       the string to create the substring from
 * @param start     start index of the substring
 * @param n         length of the substring
 * @return the created substring
 */
str_t *str_substr(str_t const *str, size_t start, size_t n);

/**
 * @brief converts a string to lowercase
 *
 * @param str   the string to convert
 * @return sting in lowercase
 */
str_t *str_tolowcase(str_t *str);

/**
 * @brief converts a string to uppercase
 *
 * @param str   the string to convert
 * @return string in uppercase
 */
str_t *str_toupcase(str_t *str);

#endif /* INCLUDE_MY_STR_ */
