.section .data

str1:
.string "You win"

str2:
.string "You lose"

.section .text
.globl finish_game
.type finish_game, @function

finish_game:

    addi sp, sp, -4
    sw ra, 0(sp)


    #t0 = pscore
    mv t0, a0


    #t1 = cscore
    mv t1, a1


    #LCD_Clear(BLACK);
    li a0, 0x0000
    jal LCD_Clear


    #\if (pscore == 10) LCD_ShowString(50, 24, (u8 *)("You win"), GREEN); 
    li t2, 10
    bne t0, t2, end_if1

    #LCD_ShowString(50, 24, (u8 *)("You win"), GREEN); 
    li a0, 50
    li a1, 24
    la a2, str1
    li a3, 0x07E0
    jal LCD_ShowString

end_if1:


    #\if (cscore == 10) LCD_ShowString(50, 24, (u8 *)("You lose"), RED);
    li t2, 10
    bne t1, t2, end_if2

    #LCD_ShowString(50, 24, (u8 *)("You lose"), RED); 
    li a0, 50
    li a1, 24
    la a2, str2
    li a3, 0xF800
    jal LCD_ShowString

end_if2:

    lw ra, 0(sp)
    addi sp, sp, 4
    ret