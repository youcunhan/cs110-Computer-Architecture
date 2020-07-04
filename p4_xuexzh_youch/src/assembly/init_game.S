.section .text
.globl init_game
.type init_game, @function

init_game:

    addi sp, sp, -4
    sw ra, 0(sp)


    li s2, 30  #s0: location of player's paddle (y)
    li s3, 30  #s1: location of cpu's paddle (ynow1,ynow2)


    #draw table
    #Margins:10,5
    #LCD_DrawRectangle(10, 5, 149, 74, white)
    li a0, 10
    li a1, 5
    li a2, 149
    li a3, 74
    li a4, 0xffff
    jal LCD_DrawRectangle


    #draw mid line
    #LCD_DrawLine(80, 5, 80, 74, gray)
    li a0, 80
    li a1, 5
    li a2, 80
    li a3, 74
    li a4, 0x8430
    jal LCD_DrawLine


    #draw player's score
    li a0, 68
    li a1, 10
    mv a2, s2
    li a3, 1
    li a4, 0x8430
    jal LCD_ShowNum


    #draw cpu's score
    li a0, 84
    li a1, 10
    mv a2, s3
    li a3, 1
    li a4, 0x8430
    jal LCD_ShowNum

    li a0, 84
    li a1, 10
    mv a2, s3
    li a3, 1
    li a4, 0x8430
    jal LCD_ShowNum

    li a0, 84
    li a1, 10
    mv a2, s3
    li a3, 1
    li a4, 0x8430
    jal LCD_ShowNum
    li a0, 84
    li a1, 10
    mv a2, s3
    li a3, 1
    li a4, 0x8430
    jal LCD_ShowNum


    #start_game()
    jal start_game


    #
    #
    #
    #
    #
    #
    #
    #
    #
    #
    #
    #
    #
    #
    #
    #
    #
    #
    #
    #
    #

    lw ra, 0(sp)
    addi sp, sp, 4
    ret