/*
** EPITECH PROJECT, 2023
** my_cstr
** File description:
** cstring functions
*/

#ifndef MY_CSTR_
    #define MY_CSTR_


char *my_strlowcase(char *str);
char *my_strupcase(char *str);

char *my_revstr(char *str);
int my_streq(char const *s1, char const *s2);

int my_str_isalpha(char const *str);
int my_str_isfloat(char const *str);
int my_str_isint(char const *str);
int my_str_isnum(char const *str);
int my_str_islower(char const *str);
int my_str_isupper(char const *str);


#endif /* MY_CSTR_ */
