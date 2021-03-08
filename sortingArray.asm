.data
	array: .word 0:5 # 5 is length of array
	message1: .asciiz "Enter the array[5] of integers:\n"
	space: .asciiz " "
	message2: .asciiz "Array : "
	newLine: .asciiz "\n"
.text
main:
	
	jal scanArray
	jal printArray
	jal println
	jal sortArray
	jal printArray
	
	li $v0, 10
	syscall

println:
	li $v0, 4
	la $a0, newLine
	syscall
	
	jr $ra

printArray:
	addi $t0, $zero, 0
	li $v0,4
	la $a0, message2
	syscall
	
	while1:
		beq $t0, 20, exit1
		
		lw $t2, array($t0)
		li $v0, 1
		move $a0, $t2
		syscall
		
		li $v0, 4
		la $a0, space
		syscall
		
		addi $t0, $t0, 4
		
		j while1
	exit1:
	
	jr $ra

scanArray:
	addi $t0, $zero, 0
	li $v0, 4
	la $a0, message1
	syscall
	
	while:
		beq $t0, 20, exit
		li $v0, 5
		syscall
		move $t1, $v0
		
		sw $t1, array($t0)
		addi $t0, $t0, 4
		
		j while
		 
	exit:
	
	jr $ra

	
sortArray:
	addi $t0, $zero,0 # i = 0
	addi $t1, $zero,0 # j = 0
	
	while4:
		beq $t0, 16, exit4 # while(i < 16)
		add $t2, $t0, -16  # i -16
		mul $t2, $t2, -1   # 16 - i
		while5: # while(j<16 - i)
			beq $t1, $t2, exit5
			lw $t3, array($t1) # array[j]
			addi $t4, $t1, 4 # $t4 = j + 1
			lw $t5, array($t4) # array[j + 1]
			
			bgt $t3, $t5, swap 
			
			addi $t1, $t1, 4 #j++
			j while5
		exit5:
		addi $t0, $t0, 4  # i++
		addi $t1, $zero, 0# j = 0
		
		j while4
			
	
	exit4:
	
	jr $ra
	
	swap:
		sw $t5, array($t1)
		sw $t3, array($t4)
		addi $t1, $t1, 4  #j++
		j while5
	
	
	
		
	
	