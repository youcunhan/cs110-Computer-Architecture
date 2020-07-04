.section .text
.globl update
.type update, @function

update:

    addi sp, sp, -4
    sw ra, 0(sp)


    #t0 = cscore
    mv t0, a0
    

    #t1 = pscore
    mv t1, a1


    #LCD_ShowNum(68,10,cscore,1,GRAY);
    li a0, 68
    li a1, 10
    mv a2, t0
    li a3, 1
    li a4, 0X8430
    jal LCD_ShowNum


    #LCD_ShowNum(84,10,pscore,1,GRAY);
    li a0, 84
    li a1, 10
    mv a2, t1
    li a3, 1
    li a4, 0X8430
    jal LCD_ShowNum


    #LCD_DrawRectangle(10, 5, 149, 74, WHITE);
    li a0, 10
    li a1, 5
    li a2, 149
    li a3, 74
    li a4, 0xFFFF
    jal LCD_DrawRectangle


    #LCD_DrawLine(80, 5, 80, 74, GRAY);
    li a0, 80
    li a1, 5
    li a2, 80
    li a3, 74
    li a4, 0X8430
    jal LCD_DrawLine
    
    
    lw ra, 0(sp)
    addi sp, sp, 4
    ret