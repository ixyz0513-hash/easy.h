# Math helpers

there are math helpers like  
- clamp_value_int  
- clamp_value_double  
- min_int  
- min_double  
- max_int  
- max_double  

**min and the max versions check if the array your providing isnt NULL**  
the parameters for the clamp functions are  **(min,max,target)** if target is lesser then min then the return value is min else if target is greater then max is the return value else if target is between them then the return value is target  
the parameters for the min/max functions are **(array,length)** min searches through the array and checks what value is the smallest in the array max is the opposite