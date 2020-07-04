
# `void exit(int);` system call#comments
	.text                   #text
exit:                       #function for exit
	mv	a1, a0              #exit num
	li	a0, 17              #exit num
	ecall                   #system call
# entry point
	.globl  main
main:
    la  s0, input_size      #s0 = input_size
    lw  s0, 0(s0)           #s0 = input_size
    la  s1, input_inorder   #s1 = input_inorder
    la  s2, input_postorder #s2 = input_postorder
    mv  a0, x0              #first argument, start of inorder
    addi t0, s0, -1         #t0 = s0 - 1
    mv  a1, t0              #second argument, end of inorder
    mv  a2, x0              #third argument, start of postorder
    mv  a3, t0              #fourth argument, end of postorder
    jal preorder            #jump&link
    mv a0, x0               #exit successfully
	call	exit            #exit

preorder:                   #function of print preorder (start of inorder, end of inorder, start of postorder, end of postorder)
    blt a1, a0, return      #if(a0>a1) return 0;
    slli t0, a3, 2
    add t2, s2, t0          #t2 is temp of s2 = input_postorder, get input_postorder[a3]
#store a0, a1
    addi sp, sp, -8         #store a0, a1
    sw  a0, 4(sp)           #store a0, a1
    sw  a1, 0(sp)           #store a0, a1
#get and print input_postorder[a3]
    addi a0, x0, 1          #get and print input_postorder[a3]
    lw  a1, 0(t2)           #get and print input_postorder[a3]
    ecall                   # print integer ecall
#restore a0, a1
    lw  a0, 4(sp)           #restore a0, a1
    lw  a1, 0(sp)           #restore a0, a1
    addi sp, sp, 8          #restore a0, a1
    beq a1, a0, return      #if(a0==a1) return 0;
#for (t3=a0;t3<=a1;t3++) if (a[t3]==b[a3]) break;
    mv  t3, a0              #init t3=0
for:
    blt a1, t3, endfor      #condition
    slli t0, t3, 2          #get a[t3]
    add t1, s1, t0          #get a[t3]
    lw  t1, 0(t1)           #get a[t3] in t1
    slli t0, a3, 2          #get b[a3]
    add t2, s2, t0          #get b[a3]
    lw  t2, 0(t2)           #get b[a3] in t2
    beq t1, t2, endfor      #if (a[t3]==b[a3]) break;
    addi t3, t3, 1          #t3++
    j for                   #loop
endfor:
#t4=a2+(t3-a0)-1;
    add t4, a2, t3          #t4=a2+(t3-a0)-1;
    sub t4, t4, a0          #t4=a2+(t3-a0)-1;
    addi t4, t4, -1         #t4=a2+(t3-a0)-1;
#recursive
#store ra, a1, a3, t3 ,t4
    addi sp, sp, -20        #add sp
    sw ra 16(sp)            #store ra
    sw a1 12(sp)            #store a1
    sw a3 8(sp)             #store a3
    sw t3 4(sp)             #store t3
    sw t4 0(sp)             #store t4
#call preorder(a0,t3-1,a2,t4)
    addi a1, t3, -1        #second argument, t3-1
    addi a3, t4, 0         #fourth argument, t4
    jal preorder           #comments
#restore a1, a3, t3, t4
    lw a1 12(sp)           #load a1
    lw a3 8(sp)            #load a3
    lw t3 4(sp)            #load t3
    lw t4 0(sp)            #load t4
    addi sp, sp, 16        #pop
#call preorder(t3+1,a1,t4+1,a3-1)
    addi a0, t3, 1        #first argument, t3+1
    addi a2, t4, 1        #third argument, t4+1
    addi a3, a3, -1       #fourth argument, a3-1
    jal preorder          #jump
#restore ra
    lw ra 0(sp)           #load rqqa
    addi sp, sp, 4        #pop
return:
    jr ra                 #jump back