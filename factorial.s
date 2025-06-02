.data
    Factorial: .asciiz "! = "
    NewLine: .asciiz "\n"

.text
.globl main

main:

    #NewLine
    li $v0, 4
    la $a0, NewLine
    syscall
    
    #Init a1 as n as factorial
    li $a1, 3 #Factorial here is n=3 ans is 6, 3*2*1
    move $a0, $a1
    li $v0, 1
    syscall
    
    #Print
    li $v0, 4
    la $a0, Factorial
    syscall

    # Initialize $t0 to 1
    li $t0, 1
    
	#The loop is recursive 
loop:
    beqz $a1, end
    mul $t0, $t0, $a1
    sub $a1, $a1, 1
    j loop
	
	#Print out final Result
end:
    move $a0, $t0
    li $v0, 1
    syscall
	#NewLine
    li $v0, 4
    la $a0, NewLine
    syscall
	syscall
	
	
exit:
    li $v0, 10
    syscall
