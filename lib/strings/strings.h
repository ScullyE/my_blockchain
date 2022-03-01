#ifndef STRINGS_H
#define STRINGS_H

bool get_word(const char* _input, char* _output, int word);
int my_strcmp(char* str1, char* str2);
int my_atoi(const char* _name);
long long my_atoll(const char* _name);
int my_strcpy(char* _to, const char* _from);
int my_strlen(const char* _str);
bool is_alphanum(char* _str);
void printf_nr(const char* _str);

#endif