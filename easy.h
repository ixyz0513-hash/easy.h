#ifndef EASY_H
#define EASY_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

unsigned short alloc_counter = 0;

// LOG

void success_log(const char *string) 
{
    assert(string != NULL);
    printf("\033[32m%s \33[0m\n",string);
}

void info_log(const char *string) 
{
    assert(string != NULL);
    printf("\033[34m%s \33[0m\n",string);
}

void warning_log(const char *string) 
{
    assert(string != NULL);
    printf("\033[33m%s \33[0m\n",string); 
}

void error_log(const char *string) 
{
    assert(string != NULL);
    fprintf(stderr,"\033[31m%s \33[0m\n",string); 
}

void check_if_null(const void *ptr) 
{
    if(ptr == NULL) 
    {
        error_log("Error: Array is NULL\n");
        exit(1);
    }
}

//INPUT

void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool read_int(const char *string,int *p) 
{
    assert(string != NULL);
    assert(p != NULL);

    printf("%s",string);

    char buffer[1024];
    fgets(buffer,sizeof(buffer),stdin);

    char *end = NULL;
    *p = strtol(buffer,&end,10);

    if(*end != '\n') 
    {
        clear_stdin();
        return false;
    }
    
    
    return true;
}

bool read_double(const char *string,double *p) 
{
    assert(string != NULL);
    assert(p != NULL);

    printf("%s",string);

    char buffer[1024];
    fgets(buffer,sizeof(buffer),stdin);

    char *end = NULL;
    *p = strtod(buffer,&end);

    if(*end != '\n') 
    {
        clear_stdin();
        return false;
    }
    
    return true;
}

bool read_char(const char *string,char *p) 
{
    assert(string != NULL);
    assert(p != NULL);

    printf("%s",string);

    char character;
    character = getchar();

    *p = character;
    clear_stdin();
    
    return true;
}

bool read_string(const char *string,char *p) 
{
    assert(string != NULL);
    assert(p != NULL);

    printf("%s",string);

    char buffer[1024];
    fgets(buffer,sizeof(buffer),stdin);

    size_t len = strlen(buffer);

    buffer[len - 1] = '\0';

    strncpy(p,buffer,len);
    
    return true;
}

// math helpers

int clamp_value_int(const int min,const int max,int target) 
{
    if(min > target) target = min;

    else if(max < target) target = max;


    return target;
}

double clamp_value_double(const double min,const double max,double target) 
{
    if(min > target) target = min;

    else if(max < target) target = max;


    return target;
}

int min_int(int array[],const size_t len) 
{

    int min = 400000000;

    for(size_t i = 0; i < len; ++i) 
    {
        if(array[i] < min) min = array[i];
    }
    return min;
}

double min_double(double array[],const size_t len) 
{

    double min = 400000000.0;

    for(size_t i = 0; i < len; ++i) 
    {
        if(array[i] < min) min = array[i];
    }
    return min;
}

int max_int(int array[],const size_t len) 
{

    int max = 400000000;

    for(size_t i = 0; i < len; ++i) 
    {
        if(array[i] > max) max = array[i];
    }
    return max;
}

double max_double(double array[],const size_t len) 
{

    double max = -400000000.0;

    for(size_t i = 0; i < len; ++i) 
    {
        if(array[i] > max) max = array[i];
    }
    return max;
}


// datastructures

//DYNAMIC ARRAY

#define DEFINE_ARRAY(T,name)                                         \
    typedef struct {                                                 \
        T *data;                                                     \
        size_t capacity;                                             \
        size_t length;                                               \
        uint8_t element_size;                                        \
    } name;                                                          \
                                                                     \
                                                                     \
    name *name##_init(const size_t capacity) {                       \
        name *vec = malloc(sizeof(name));                            \
        if(!vec) return NULL;                                        \
        vec->length = 0;                                             \
        vec->element_size = sizeof(T);                               \
        if(capacity == 0) vec->capacity = 1;                         \
                                                                     \
        else vec->capacity = capacity;                               \
                                                                     \
        vec->data = calloc(vec->capacity, sizeof(T));                \
        if(!vec->data) {                                             \
            free(vec);                                               \
            return NULL;                                             \
        }                                                            \
        ++alloc_counter;                                             \
        return vec;                                                  \
    }



#define char_arr_init(vec,string) do\
{                                                                \
    check_if_null(vec);                                          \
    long long len;                                               \
    if((len = strlen(string) + 1) == 0) len = 0;                 \
    (vec)->length = len;                                         \
    (vec)->element_size = sizeof(char);                          \
                                                                 \
    if(len == 0) (vec)->capacity = 1;                            \
                                                                 \
    else (vec)->capacity = len * 2;                              \
                                                                 \
    (vec)->data = malloc((vec)->capacity * (vec)->element_size); \
    if(*(vec)->data)                                             \
    {                                                            \
        strcpy((vec)->data,string);                              \
        ++alloc_counter;                                         \
    }                                                            \
                                                                 \
    else                                                         \
    {                                                            \
        free(vec);                                               \
        error_log("Error: Memory allocation failed\n");          \
        exit(1);                                                 \
    }                                                            \
}   while(0)
    


#define resize_array(array,new_capacity) do\
{                                                                            \
    check_if_null(array);                                                    \
    check_if_null((array)->data);                                            \
    if(new_capacity != (array)->capacity)                                    \
    {                                                                        \
        if(new_capacity <= (array)->length) (array)->length = new_capacity;  \
                                                                             \
        (array)->capacity = new_capacity;                                    \
        void *p = realloc((array)->data,(array)->capacity * (array)->element_size);      \
        if(!p) {                                                             \
            error_log("Error: Memory allocation failed\n");                  \
            exit(1);                                                         \
        }                                                                    \
        (array)->data = p;                                                   \
    }                                                                        \
}  while(0)
    

#define push_back(array,element) do\
{                                                                \
    check_if_null(array);                                        \
    check_if_null((array)->data);                                \
    if((array)->length == (array)->capacity) {                   \
        (array)->capacity *= 2;                                  \
        void *p = realloc((array)->data,(array)->capacity * (array)->element_size);      \
        if(!p) {                                                 \
            error_log("Error: Memory allocation failed\n");      \
            exit(1);                                             \
        }                                                        \
        (array)->data = p;                                       \
    }                                                            \
    (array)->data[(array)->length] = element;                    \
    (array)->length += 1;                                        \
                                                                 \
}  while(0)



#define pop_back(array) do \
{                                                    \
    check_if_null(array);                            \
    if((array)->length != 0) (array)->length -= 1;   \
} while(0)


#define array_set(destination,source)   do\
{                                                                \
    check_if_null(destination);                                  \
    check_if_null((destination)->data);                          \
    check_if_null(source);                                       \
    check_if_null((source)->data);                               \
                                                                 \
    if(destination == source) break;                             \
                                                                 \
    else if((destination)->capacity < (source)->capacity) {      \
      void *p = realloc((destination)->data,(source)->capacity * (destination)->element_size);      \
                                                                 \
      if(!p) {                                                   \
        error_log("Error: Memory allocation failed\n");          \
        exit(1);                                                 \
      }                                                          \
      (destination)->data = p;                                   \
    }                                                            \
                                                                 \
    (destination)->capacity = (source)->capacity;                \
    (destination)->length = (source)->length;                    \
                                                                 \
    for(size_t i = 0; i < (destination)->length; ++i) {          \
        (destination)->data[i] = (source)->data[i];              \
    }                                                            \
}  while(0)



#define array_reverse(array) do\
{                                                                        \
    check_if_null(array);                                                \
    check_if_null((array)->data);                                        \
    if((array)->length > 1)                                              \
    {                                                                    \
        size_t p1 = 0;                                                   \
        size_t p2 = (array)->length - 1;                                 \
                                                                         \
        while(p1 < p2) {                                                 \
                                                                         \
            typeof(*array->data) temp = (array)->data[p1];               \
            (array)->data[p1] = (array)->data[p2];                       \
            (array)->data[p2] = temp;                                    \
                                                                         \
            ++p1;                                                        \
            --p2;                                                        \
        }                                                                \
    }                                                                    \
                                                                         \
}   while(0)



#define array_insert(array,index,value) do\
{                                                                    \
    check_if_null(array);                                            \
    check_if_null((array)->data);                                    \
    if(index < 0 || index > (array)->length) {                       \
        error_log("Error: Index out of bounds\n");                   \
        exit(1);                                                     \
    }                                                                \
                                                                     \
    if((array)->length == (array)->capacity) {                       \
        (array)->capacity *= 2;                                      \
        void *p = realloc((array)->data,(array)->capacity * (array)->element_size);      \
        if(!p) {                                                     \
            error_log("Error: Memory allocation failed\n");          \
            exit(1);                                                 \
        }                                                            \
        (array)->data = p;                                           \
    }                                                                \
    (array)->length += 1;                                            \
                                                                     \
    for(long long i = (array)->length; i >= 0; --i) {                \
                                                                     \
        if(i == index) (array)->data[i] = value;                     \
                                                                     \
        else if(i > index) (array)->data[i] = (array)->data[i - 1];  \
    }                                                                \
}  while(0)

#define array_remove(array,index) do\
{                                                                                                    \
    check_if_null(array);                                                                            \
    check_if_null((array)->data);                                                                    \
    if((array)->length != 0) {                                                                       \
        for(size_t i = 0; i < (array)->length; ++i) if(i > index) (array)->data[i - 1] = (array)->data[i]; \
        (array)->length -= 1;                                                                        \
    }                                                                                                \
} while(0)

#define array_clear(array) do\
{                                                                \
    check_if_null(array);                                        \
    (array)->length = 0;                                         \
} while(0)

#define free_array(array) do\
{                         \
    check_if_null(array); \
    check_if_null((array)->data); \
    free((array)->data);  \
    free(array);          \
    array = NULL;         \
    --alloc_counter;      \
} while(0)

#define array_front 0

#define array_back(array) ((array)->length - 1)


#define array_for_each(length,i) for(size_t i = 0; i < length; ++i)



typedef struct
{
    char *data;
    size_t len;
} string_view;


string_view cstr(char *data) 
{
    assert(data != NULL);

    return (string_view) 
    {
        data,
        strlen(data)
    };
}

void set_stringv(string_view *str,char *data) 
{
    assert(str != NULL);
    assert(data != NULL);
    str->data = data;
    str->len = strlen(data);
}

void swap_stringv(string_view *str,string_view *str2)
{
    assert(str != NULL);
    assert(str2 != NULL);
    string_view temp;
    set_stringv(&temp,str->data);
    set_stringv(str,str2->data);
    set_stringv(str2,temp.data);
}

string_view dummy() 
{
    return (string_view) 
    {
        NULL,
        0
    };
}

#define str_null() do\
{                                       \
    error_log("string_view is NULL");   \
    return dummy();                     \
} while(0)

string_view substr(string_view *str,size_t pos_start,size_t pos_end) 
{
    if(str->len <= pos_start) 
    {
        error_log("pos_start is equal or greater then str->len");
        return dummy();
    }

    else if(str->len < pos_end) 
    {
        error_log("pos_end is greater then str->len");
        return dummy();
    }

    else if(pos_start < 0) 
    {
        error_log("pos_start is lesser then 0");
        return dummy();
    }

    else if(pos_end <= pos_start) 
    {
        error_log("pos_end is equal or lesser then pos_start");
        return dummy();
    }

    assert(str != NULL);
    str->data += pos_start;
    string_view s;
    s.len = pos_end - pos_start;
    strncpy(s.data,str->data,pos_end);
    return s;
}
	
	

void chop_left(string_view *str,size_t amount) 
{
    assert(str != NULL);
    if(amount < 0) 
    {
        error_log("amount to chop_left is lesser then 0");
        exit(1);
    }

    
    size_t len = str->len - amount;

    if(len < 0) 
    {
        error_log("len is lesser then 0");
        exit(1);
    }
    
    str->data += amount;
    str->len = len;
}

void chop_right(string_view *str,size_t amount) 
{
    assert(str != NULL);
    if(amount < 0) 
    {
        error_log("amount to chop_left is lesser then 0");
        exit(1);
    }
    
    size_t len = str->len - amount;

    if(len < 0) 
    {
        error_log("len is lesser then 0");
        exit(1);
    }

    str->len = len;
}

char back(string_view *str) 
{
    assert(str != NULL);	
    return str->data[str->len - 1];
}

char front(string_view *str) 
{
    assert(str != NULL);
    return str->data[0];
}




char at(string_view *str,size_t index) 
{
    assert(str != NULL);
    if(index >= str->len) 
    {
        error_log("index is greater or equal to str->len");
        exit(1);
    }

    else if(index < 0) 
    {
        error_log("index is lesser then 0");
        exit(1);
    }

    return str->data[index];
}




void check_if_free() 
{
   if(alloc_counter != 0) 
   {
       fprintf(stderr, "\033[31mMemory leak detected: %d allocations not freed\033[0m\n",alloc_counter);
       exit(1);
   }
}


#endif
