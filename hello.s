.data
	Message: .asciiz "Hello World\n"

.text
.globl main
main:
	li $v0, 4	#exit
	la $a0, Message
	syscall
exit:
	li $v0, 10
	syscall
