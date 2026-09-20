# Input

there are just helper functions here for *Inputs*  
- read_int for inputing ints  
- read_double for inputing doubles  
- read_char to input a char  
- read_string to input a string  

**every one of them checks if your pointer to a variable and string arent NULL**  
**also if everything goes right they return true if not false so remember to make if conditions**  
example program:  
`int var = 0;`  
`if(read_int("type a int: ",&var) == true) printf("%d\n",var); // (or you can make it read_int("type a int: ",&var)) same thing they check for true`
