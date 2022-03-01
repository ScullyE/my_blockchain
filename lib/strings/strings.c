#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

bool get_word(const char* _input, char* _output, int word){
    int walk = 0;
    int out_walk = 0;
    int count = 0;
    bool exit = false;
    while(!exit){
        if (*(_input+walk) == '\0' || *(_input+walk) == '\n'){
            return false;
        }
        if (*(_input+walk) == ' '){
            count++;
        }
        if (count == word){
            if (count == 0){
                break;
            }
            exit = true;
        }
        walk++;
    }
    while(*(_input+walk) != '\0' && *(_input+walk) != '\n' && *(_input+walk) != ' '){
        *(_output+out_walk) = *(_input+walk);
        walk++;
        out_walk++;
    }
    *(_output+out_walk) = '\0';
    return true;
}

int my_strcmp(char* str1, char* str2){
    if(*str1 != *str2){
        return *str1 - *str2;
    }
    while(*str1 != '\0' && *str2 != '\0')
    {
        if(*str1 > *str2 || *str1 < *str2){
            return *str1 - *str2;
        }

        str1++;
        str2++;
    }
    if(*str1 != *str2){
        return -1;
    }
    return 0;
}

int my_atoi(const char* _name){
    int walk = 0;
    int out = 0;
    while(*(_name+walk) != '\0'){
        if(*(_name+walk) >= '0' && *(_name+walk) <= '9'){
            out = (out*10)+(*(_name+walk) - '0');
        }
        walk++;
    }

    return out;
}

long long my_atoll(const char* _name){
    long long walk = 0;
    long long out = 0;
    while(*(_name+walk) != '\0'){
        if(*(_name+walk) > '0' && *(_name+walk) <= '9'){
            out = (out*10)+(*(_name+walk) - '0');
        }
        walk++;
    }

    return out;
}

int my_strcpy(char* _to, const char* _from){
    int walk = 0;
    while(_from[walk] != '\0')
    {
        _to[walk] = _from[walk];
        walk++;
    }
    
    _to[walk] = '\0';

    return 0;
}

int my_strlen(const char* _str){
    int i = 0;

    if(_str == NULL){
        return 0;
    }

    while(_str[i] != '\0'){
        i++;
    }

    return i;
}

bool is_alphanum(char* _str){
    while(*_str != '\0'){
        if(*_str < '0' && *_str > '9'){
            if(*_str < 'a' && *_str > 'z'){
                if(*_str < 'A' && *_str > 'Z'){
                    return false;
                }
            }
        }
        _str++;
    }
    
    return true;
}

void printf_nr(const char* _str){
    int walk = 0;
    while(*(_str+walk) != '\0'){
        char c = *(_str+walk);
        fflush(stdout);
        write(1, &c, 1);
        walk++;
    }
}

