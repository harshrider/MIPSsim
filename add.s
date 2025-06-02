.data
	Plus: .asciiz "\t + \t"
	Equal: .asciiz "\t = \t"
	NewLine: .asciiz "\n"

.text
.globl main
main:

	#Init number 1 and number 2
	li $a1, 5
	li $a2, 7

	#NewLine
	li $v0, 4
	la $a0, NewLine
	syscall

	#Get and print First Number
	move $a0, $a1
	li $v0, 1
	syscall
	
	#Plus Sign
	li $v0, 4
	la $a0, Plus
	syscall
	
	#Get and print Second Number
	move $a0, $a2
	li $v0, 1
	syscall
	
	#Equal Sign
	li $v0, 4
	la $a0, Equal
	syscall
	
	#Add the two numbers and print
	add $t0, $a2, $a1
	
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
