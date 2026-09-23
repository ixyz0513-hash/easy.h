# String_view

this is a struct that owns a pointer to a string and a size_t len heres what it can do  
- sv_cstr(const char *data) converts a c string into struct string_view  
- sv_set_string(string_view *str,char *data) sets str to data for data you can just pass in a char * like "hello" or the string_view data member  
- sv_swap_string(string_view *str,string_view *str2) sets str to str2 and sets str2 to str nothing more  
- sv_substr(string_view *str,const size_t pos_start,const size_t pos_end) str is the pointer for the member data pos_start makes where data starts in the str->data string and pos_end is the end of the string so when to stop printing  
- sv_chop_right(string_view *str,const size_t amount) moves the data member pointer to the left by the amount substracts length with amount
- sv_chop_left(string_view *str,const size_t amount) substracts length with amount if you just do `printf("%s\n",str.data);` it only prints hello even though you already chopped to the right but if you do `printf("%.*s\n",str.len,str.data);` you need to pass in the length parameter so printf knows how many times to print the chars so if you have chopped to the left by 2 it would be hel  
- sv_back(const string_view *str) returns the last data member like data[len - 1] the return type is char_result if the function succeeds then the member error is 1 else 0
- sv_front(const string_view *str) returns the first data member like data[0] the return type is char_result if the function succeeds then the member error is 1 else 0
- sv_at(const string_view *str,const size_t index) returns the data member at index the return type is char_result you know the rodeo
- sv_try_at(const string_view *str,const size_t index,char *out) returns the result to out the return type is bool if it fails false otherwise true  