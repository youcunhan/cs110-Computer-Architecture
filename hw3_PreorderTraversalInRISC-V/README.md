Homework 3  
Computer Architecture I ShanghaiTech University  
HW2 HW3 HW4  

Instructions  
In this homework you will write a program to generate a preorder traversal of a binary search tree from given inorder and postorder traversals using RISC-V. Here is a very simple template.  

Input  
The input is given by one integer and two array of integers in form of data in data section,  

input_size:        
    .word   4      
input_inorder:     
    .word   1      
    .word   2      
    .word   3      
    .word   4      
input_postorder:    
    .word   1      
    .word   2      
    .word   4      
    .word   3      
or in equivalent form of global variable in c language.  

int input_size = 4;                   
int input_inorder[] = {1, 2, 3, 4};   
int input_postorder[] = {1, 2, 4, 3};   
input_size is the size of both input_inorder and input_postorder, which contain inorder and postorder of a same tree respectively. For example, the previous input specify the following tree.  

        3       
       / \      
      2   4     
     /          
    1           
The numbers representing nodes are not necessarily continuous or positive.  

Output  
The output will consist of one single line with input_size number of integers representing the preorder traversal of the binary search tree.  

For example the output of the program given the input above would be  

3 2 1 4   
 
Notice that each number is separated by exactly one space, and at the end of the line, there are exactly one space and one line break ('\n'). Any output in other format will be rejected.  

Some advice  
learn recursive functions  
learn save and Load from Memory using RISC-V  
it is helpful writing in C first  
write comments  
Execution  
We will test your program using RISC-V emulator venus. You probably want to read this before you started.  

Submission  
You need to follow the RISC-V integer register convention and the RISC-V integer calling convention.  
You need to have meaningful comments not less than 50% of the total lines of code you wrote. A comment is defined by a sentence followed by #.  
You should submit exactly one file, hw3.s. Any other file found will result in a score of zero. Submission containing any of input_size, input_inorder or input_postorder label will be rejected.  
