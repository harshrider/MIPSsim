.data
    Prime: .asciiz " is a prime number.\n\n"
    NotPrime: .asciiz " is not a prime number.\n\n"
    NewLine: .asciiz "\n"

.text
.globl main
main:

    #NewLine
    li $v0, 4
    la $a0, NewLine
    syscall
    
    #Init a1 as n
    li $a1, 7 # Here n is 7 which is a prime number Change number
    move $a0, $a1
    li $v0, 1
    syscall
    
    #Print
    li $v0, 4
    la $a0, NewLine
    syscall

    # Initialize $t0 to 2
    li $t0, 2
    
loop:
    beq $t0, $a1, isPrime #If t0 is equal to a1, it is prime
	
    rem $t1, $a1, $t0 # Devide and get the remainder 
	
    beqz $t1, notPrime # If Remander is 0 number is not prime
	
    add $t0, $t0, 1 #add + 1 to t0
    j loop

isPrime:
    li $v0, 4
    la $a0, Prime
    syscall
    j exit

notPrime:
    li $v0, 4
    la $a0, NotPrime
    syscall

exit:
    li $v0, 10
    syscall
