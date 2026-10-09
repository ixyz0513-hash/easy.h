#ifndef EASY_H
#define EASY_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

extern unsigned short alloc_counter;

typedef struct
{
    char *data;
    size_t len;
} string_view;

typedef struct 
{
    char *data;
    size_t length;
    size_t capacity;
    uint8_t element_size;
}   string;

typedef struct 
{
    uint8_t error;
    char result;
}   char_result;

void success_log(const char *string);
void info_log(const char *string);
void warning_log(const char *string);
void error_log(const char *string);
bool check_if_null(const void *ptr);
void clear_stdin(void);
bool read_int(const char *string,int *p);
bool read_double(const char *string,double *p);
bool read_char(const char *string,char *p);
bool read_string(const char *string,char *p);
int clamp_value_int(const int min, const int max,int target);
double clamp_value_double(const double min,const double max,double target);
int min_int(int array[],const size_t len);
double min_double(double array[],const size_t len);
int max_int(int array[],const size_t len);
double max_double(double array[],const size_t len);
bool check_sign(int value);
char_result char_error();
bool index_out_bounds(size_t index,size_t len,const char *string);
string_view sv_dummy();
string_view sv_cstr(char *data);
void sv_set_string(string_view *str,char *data);
void sv_swap_string(string_view *str,string_view *str2);
string_view sv_substr(string_view *str,const size_t pos_start,const size_t pos_end);
void sv_chop_right(string_view *str,const size_t amount);
void sv_chop_left(string_view *str,const size_t amount);
char_result sv_back(const string_view *str);
char_result sv_front(const string_view *str);
char_result sv_at(const string_view *str,const size_t index);
bool sv_try_at(const string_view *str,const size_t index,char *out);
string *string_init(const char *data);
void string_set(string *str,string *str2);
void string_swap(string *str, string *str2);
void string_clear(string *str);
void string_add(string *str,const char *data);
void string_push(string *str,const char element);
void string_pop(string *str,const size_t amount);
void string_insert(string *str,const size_t index,const char element);
void string_remove(string *str,const size_t index);
void resize_string(string *str,size_t capacity);
void string_free(string **str);
char *return_string(string *str);
size_t return_string_length(string *str);
size_t return_string_capacity(string *str);
void check_if_free();

#define PRINT_DEBUGSTR(str) printf("string: %s   length: %zu   capacity: %zu   element_size: %u\n",(str)->data,(str)->length,(str)->capacity,(str)->element_size);
#define SUCCESS_RESULT 1
#define ERROR_RESULT 0
#define CHECK_NULL_ERROR -29345

//DYNAMIC ARRAY

#define DEFINE_ARRAY(T,name)                                         \
    typedef struct {                                                 \
        T *data;                                                     \
        size_t capacity;                                             \
        size_t length;                                               \
        size_t element_size;                                         \
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
    


#define resize_array(array,new_capacity) do\
{                                                                            \
    if(check_if_null(array)) break;                                          \
    else if(check_if_null((array)->data)) break;                             \
                                                                             \
    else if(new_capacity != (array)->capacity)                               \
    {                                                                        \
        if(new_capacity <= (array)->length) (array)->length = new_capacity;  \
                                                                             \
        (array)->capacity = new_capacity;                                    \
        void *p = realloc((array)->data,(array)->capacity * (array)->element_size);      \
        if(!p) {                                                             \
            error_log("Error: Memory allocation failed\n");                  \
            break;                                                           \
        }                                                                    \
        (array)->data = p;                                                   \
    }                                                                        \
}  while(0)
    

#define push_back(array,element) do\
{                                                                \
    if(check_if_null(array)) break;                              \
    else if(check_if_null((array)->data)) break;                 \
                                                                 \
    else if((array)->length == (array)->capacity) {              \
        (array)->capacity *= 2;                                  \
        void *p = realloc((array)->data,(array)->capacity * (array)->element_size);      \
        if(!p) {                                                 \
            error_log("Error: Memory allocation failed\n");      \
            break;                                               \
        }                                                        \
        (array)->data = p;                                       \
    }                                                            \
    (array)->data[(array)->length] = element;                    \
    (array)->length += 1;                                        \
                                                                 \
}  while(0)



#define pop_back(array) do \
{                                                    \
    if(check_if_null(array)) break;                  \
    else if((array)->length != 0) (array)->length -= 1;   \
} while(0)


#define array_set(destination,source)   do\
{                                                                \
    if(check_if_null(destination)) break;                        \
    else if(check_if_null((destination)->data)) break;           \
    else if(check_if_null(source)) break;                        \
    else if(check_if_null((source)->data)) break;                \
                                                                 \
    if(destination == source) break;                             \
                                                                 \
    else if((destination)->capacity < (source)->capacity) {      \
      void *p = realloc((destination)->data,(source)->capacity * (destination)->element_size);      \
                                                                 \
      if(!p) {                                                   \
        error_log("Error: Memory allocation failed\n");          \
        break;                                                   \
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
    if(check_if_null(array)) break;                                      \
    else if(check_if_null((array)->data)) break;                         \
                                                                         \
    else if((array)->length > 1)                                         \
    {                                                                    \
        size_t p1 = 0;                                                   \
        size_t p2 = (array)->length - 1;                                 \
                                                                         \
        while(p1 < p2) {                                                 \
                                                                         \
            typeof((array)->data[p1]) temp = (array)->data[p1];          \
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
    if(check_if_null(array)) break;                                  \
    if(check_if_null((array)->data)) break;                          \
                                                                     \
                                                                     \
    else if(index == (array)->length)                                \
    {                                                                \
        push_back(array,value);                                      \
        break;                                                       \
    }                                                                \
                                                                     \
    else if(index > (array)->length || index < 0) {                  \
        error_log("Error: Index out of bounds\n");                   \
        break;                                                       \
    }                                                                \
                                                                     \
    if((array)->length == (array)->capacity) {                       \
        (array)->capacity *= 2;                                      \
        void *p = realloc((array)->data,(array)->capacity * (array)->element_size);      \
        if(!p) {                                                     \
            error_log("Error: Memory allocation failed\n");          \
            break;                                                   \
        }                                                            \
        (array)->data = p;                                           \
    }                                                                \
    (array)->length += 1;                                            \
                                                                     \
    for(size_t i = array->length; i > index; --i) (array)->data[i] = (array)->data[i - 1];  \
    (array)->data[index] = value;                                      \
}  while(0)

#define array_remove(array,index) do\
{                                                                                                    \
    if(check_if_null(array)) break;                                                                  \
    else if(check_if_null((array)->data)) break;                                                     \
                                                                                                     \
    if(!index_out_bounds(index,(array)->length,"failed index (array_remove)")) break;                \
                                                                                                     \
    else if(index == (array)->length - 1)                                                            \
    {                                                                                                \
        pop_back(array);                                                                             \
        break;                                                                                       \
    }                                                                                                \
                                                                                                     \
    for(size_t i = 0; i < (array)->length; ++i) if(i > index) (array)->data[i - 1] = (array)->data[i]; \
    (array)->length -= 1;                                                                            \
                                                                                                     \
} while(0)

#define array_clear(array) do\
{                                                                \
    if(check_if_null(array)) break;                              \
    (array)->length = 0;                                         \
} while(0)

#define free_array(array) do\
{                         \
    if(check_if_null(array)) break; \
    else if(check_if_null((array)->data)) break; \
    free((array)->data);  \
    free(array);          \
    array = NULL;         \
    --alloc_counter;      \
} while(0)

#define array_front 0

#define array_back(array) ((array)->length - 1)


#define for_each(length,i) for(size_t i = 0; i < length; ++i)



#ifdef EASY_IMPLEMENTATION

// LOG

void success_log(const char *string) 
{
    if(!string) 
    {
        fprintf(stderr,"\033[31m string equals NULL in (success_log) \33[0m\n"); 
        return;
    }

    printf("\033[32m%s \33[0m\n",string);
}

void info_log(const char *string) 
{
    if(!string) 
    {
        fprintf(stderr,"\033[31m string equals NULL in (info_log) \33[0m\n"); 
        return;
    }

    printf("\033[34m%s \33[0m\n",string);
}

void warning_log(const char *string) 
{
    if(!string) 
    {
        fprintf(stderr,"\033[31m string equals NULL in (warning_log) \33[0m\n"); 
        return;
    }

    printf("\033[33m%s \33[0m\n",string); 
}

void error_log(const char *string) 
{
    if(!string) 
    {
        fprintf(stderr,"\033[31m string equals NULL in (error_log) \33[0m\n"); 
        return;
    }
    fprintf(stderr,"\033[31m%s \33[0m\n",string); 
}

bool check_if_null(const void *ptr) 
{
    if(!ptr) 
    {
        error_log("\nError: Pointer is NULL\n");
        return true;
    }
    return false;
}

//INPUT

void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

bool read_int(const char *string,int *p) 
{
    if(!string) 
    {
        error_log("string equals NULL in (read_int)");
        return false;
    }

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
    if(!string) 
    {
        error_log("string equals NULL in (read_double)");
        return false;
    }

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
    if(!string) 
    {
        error_log("string equals NULL in (read_char)");
        return false;
    }

    printf("%s",string);

    char character;
    character = getchar();

    *p = character;
    clear_stdin();
    
    return true;
}

bool read_string(const char *string,char *p) 
{
    if(!string) 
    {
        error_log("string equals NULL in (read_string)");
        return false;
    }

    else if(!p) 
    {
        error_log("p equals NULL in (read_string)");
        return false;
    }

    printf("%s",string);

    char buffer[1024];
    fgets(buffer,sizeof(buffer),stdin);

    size_t len = strlen(buffer);
    buffer[len] = '\0';

    strcpy(p,buffer);
    
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
    if(check_if_null(array)) return CHECK_NULL_ERROR;

    int min = array[0];

    for(size_t i = 1; i < len; ++i) 
    {
        if(array[i] < min) min = array[i];
    }
    return min;
}

double min_double(double array[],const size_t len) 
{
    if(check_if_null(array)) return CHECK_NULL_ERROR;

    double min = array[0];

    for(size_t i = 1; i < len; ++i) 
    {
        if(array[i] < min) min = array[i];
    }
    return min;
}

int max_int(int array[],const size_t len) 
{
    if(check_if_null(array)) return CHECK_NULL_ERROR;

    int max = array[0];

    for(size_t i = 1; i < len; ++i) 
    {
        if(array[i] > max) max = array[i];
    }
    return max;
}

double max_double(double array[],const size_t len) 
{
    if(check_if_null(array)) return CHECK_NULL_ERROR;

    double max = array[0];

    for(size_t i = 1; i < len; ++i) 
    {
        if(array[i] > max) max = array[i];
    }
    return max;
}

bool check_sign(int value) 
{
    if(value < 0) return false;
    return true;
}


// datastructures

bool index_out_bounds(size_t index,size_t len,const char *string) 
{
    if(index >= len) 
    {
        fprintf(stderr,"\033[31m index is greater or equal to str->len in (%s) \033[0m\n",string);
        return false;
    }

    return true;
}

char_result char_error(void) 
{
    return (char_result) 
    {
        ERROR_RESULT,
        0
    };
}

string_view sv_dummy(void) 
{
    return (string_view) 
    {
        NULL,
        0
    };
}


string_view sv_cstr(char *data) 
{
    if(!data) 
    {
        error_log("data equals NULL in (sv_cstr)");
        return sv_dummy();
    }

    return (string_view) 
    {
        data,
        strlen(data)
    };
}

void sv_set_string(string_view *str,char *data) 
{
    if(!str) 
    {
        error_log("str equals NULL in (sv_set_string)");
        return;
    }

    else if(!data) 
    {
        error_log("data equals NULL in (sv_string_set)");
        return;
    }

    else if(str->data == data) 
    {
        error_log("same pointers in (sv_string_set)");
        return;
    }

    str->data = data;
    str->len = strlen(data);
}

void sv_swap_string(string_view *str,string_view *str2)
{
    if(!str || !str2) 
    {
        error_log("str or str2 equals NULL in (sv_swap_string)");
        return;
    }

    else if(str == str2) 
    {
        error_log("str and str2 are the same pointers in (sv_swap_string)");
        return;
    }

    string_view temp;
    sv_set_string(&temp,str->data);
    sv_set_string(str,str2->data);
    sv_set_string(str2,temp.data);
}



string_view sv_substr(string_view *str,const size_t pos_start,const size_t pos_end) 
{
    if(!str) 
    {
        error_log("str equals NULL in (sv_substr)");
        return sv_dummy();
    }

    else if(str->len <= pos_start) 
    {
        error_log("pos_start is equal or greater then str->len in (sv_substr)");
        return sv_dummy();
    }

    else if(str->len < pos_end) 
    {
        error_log("pos_end is greater then str->len in (sv_substr)");
        return sv_dummy();
    }

    else if(pos_end <= pos_start) 
    {
        error_log("pos_end is equal or lesser then pos_start in (sv_substr)");
        return sv_dummy();
    }

    

    
    return (string_view)
    {
        .data = str->data + pos_start,
        .len = pos_end - pos_start
    };
}
	
	

void sv_chop_right(string_view *str,const size_t amount) 
{
    if(!str) 
    {
        error_log("str equals NULL in (sv_chop_left)");
        return;
    }

    if(!index_out_bounds(amount,str->len,"(sv_chop_left)")) return;

    str->data += amount;
    str->len -= amount;
}

void sv_chop_left(string_view *str,const size_t amount) 
{
    if(!str) 
    {
        error_log("str equals NULL in (sv_chop_left)");
        return;
    }

    if(!index_out_bounds(amount,str->len,"(sv_chop_right)")) return;

    str->len -= amount;
}

char_result sv_back(const string_view *str) 
{
    if(!str) 
    {
        error_log("str equals NULL in (sv_front)");
        return char_error();
    }

    return (char_result) {SUCCESS_RESULT,str->data[str->len - 1]};
}

char_result sv_front(const string_view *str) 
{
    if(!str) 
    {
        error_log("str equals NULL in (sv_front)");
        return char_error();
    }

    return (char_result) {SUCCESS_RESULT,str->data[0]};
}




char_result sv_at(const string_view *str,const size_t index) 
{
    if(!str) 
    {
        error_log("str equals NULL in (sv_at)");
        return char_error();
    }
    
    if(!index_out_bounds(index,str->len,"(sv_at)")) return char_error();
    

    return (char_result) {SUCCESS_RESULT,str->data[index]};
}

bool sv_try_at(const string_view *str,const size_t index,char *out) 
{
    if(!str || !out)
    {
        error_log("str or out equals NULL in (sv_try_at)");
        return false;
    }
    
    if(!index_out_bounds(index,str->len,"(sv_try_at)")) return false;
        

    *out = str->data[index];
    return true;
}


string *string_init(const char *data) 
{
    if(!data) 
    {
        error_log("data is equal to NULL (string_init)");
        return NULL;
    }
    string *str = malloc(sizeof(string));

    if(!str) 
    {
        error_log("str equals NULL from malloc error (string_init)");
        return NULL;
    }
    size_t len = strlen(data);

    str->data = malloc(len * 2 + 1);

    if(!str->data) 
    {
        free(str);
        error_log("data equals NULL from malloc error (string_init)");
        return NULL;
    }

    strncpy(str->data,data,len);
    str->capacity = len * 2 + 1;
    str->length = len;
    str->data[str->length] = '\0';
    str->element_size = 1;

    ++alloc_counter;
    return str;
}

string *string_init_array(size_t *len,const char *data) 
{
    string *p = string_init(data);
    if(p) *len += 1;
    return p;
}


void string_set(string *destination,string *source) 
{
    if(!destination || !source) 
    {
        error_log("destination or source equals NULL in (string_set)");
        return;
    }

    else if(destination == source) 
    {
        error_log("passed in the same pointers in (string_set)");
        return;
    }

    array_set(destination,source);
    destination->data[destination->length] = '\0';
}

bool string_set_char(string *destination,char *source) 
{
    string *p = string_init(source);
    if(!p) return false;
    string_set(destination,p);
    string_free(&p);
    return true;
}


void string_swap(string *str, string *str2) 
{
    if(!str || !str2) 
    {
        error_log("str or str2 equals NULL in (string_set)");
        return;
    }

    else if(str == str2) 
    {
        error_log("passed in the same pointers in (string_set)");
        return;
    }
    string *temp = string_init(str->data);
    string_set(str,str2);
    string_set(str2,temp);
    string_free(&temp);
}


void string_clear(string *str) 
{
    if(!str) 
    {
        error_log("str equals NULL in (string_clear)");
        return;
    } 
    str->length = 0;
    str->data[0] = '\0';
}

void string_add(string *str,const char *data) 
{
    size_t len = strlen(data);
    if(str->length + len >= str->capacity) 
    {
        str->capacity = str->capacity * 2 + len;
        void *p = realloc(str->data,str->capacity);

        if(!p) 
        {
            error_log("p equals NULL because of a realloc error in (string_add)");
            return;
        }
        str->data = p;
    }
    str->length += len;
    strcat(str->data,data);
}

void string_push(string *str,const char element) 
{
    if(str->length >= str->capacity) 
    {
        str->capacity *= 2;
        void *p = realloc(str->data,str->capacity);

        if(!p) 
        {
            error_log("p equals NULL because of a realloc error in (string_add)");
            return;
        }
        str->data = p;
    }
    str->data[str->length] = element;
    str->length += 1;
    str->data[str->length] = '\0';
}

void string_pop(string *str,const size_t amount) 
{
    if(!str) 
    {
        error_log("str equals NULL in (string_pop)");
        return;
    }

    else if(!index_out_bounds(amount,str->length,"(string_pop)")) return;
    

    str->length -= amount;
    str->data[str->length] = '\0';
}

void string_insert(string *str,const size_t index,const char element) 
{
    array_insert(str,index,element);
}

void string_remove(string *str,const size_t index) 
{
    if(!index_out_bounds(index,str->length,"(string_remove)")) return;

    array_remove(str,index);
    str->data[str->length] = '\0';
}

void resize_string(string *str,size_t capacity) 
{
    if(!str) 
    {
        error_log("str equals NULL in (resize_string)");
        return;
    }
    resize_array(str,capacity);
}

char_result string_at(string *str,size_t index) 
{
    if(!index_out_bounds(index,str->length,"string_at")) return char_error();

    return (char_result) {SUCCESS_RESULT,str->data[index]};
}

char *return_string(string *str) 
{
    return str->data;
}

size_t return_string_length(string *str) 
{
    return str->length;
}

size_t return_string_capacity(string *str) 
{
    return str->capacity;
}

void string_free(string **str) 
{
    free_array(*str);
}


void check_if_free() 
{
   if(alloc_counter != 0) fprintf(stderr, "\033[31mMemory leak detected: %d allocations not freed\033[0m\n",alloc_counter);
}

#endif

#endif  
