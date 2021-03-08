.data
	message1: .asciiz "Enter coefficients of the equation(a,b,c)\n"
	twoRoots: .asciiz "Equation has 2 roots\n"
	oneRoot: .asciiz "Equation has 1 root\n"
	noRoots: .asciiz "Equation has no roots\n"
	newLine: .asciiz "\n"
	D: .double 0.0
	four: .double 4.0
	two: .double 2.0 
	minusOne: .double -1.0
.text
main:
	li $v0, 4
	la $a0, message1
	syscall
	
	li $v0, 7
	syscall
	mov.d $f2, $f0     # $f2 = a
	
	li $v0, 7
	syscall
	mov.d $f4, $f0     # $f4 = b
	
	li $v0, 7
	syscall
	mov.d $f6, $f0     # $f6 = c
	
	ldc1 $f8, four      # $f8 = 4
	mul.d $f10, $f4, $f4 # $f10 = b^2
	mul.d $f14, $f2, $f8 # $f14 = 4a
	mul.d $f14, $f14, $f6 # $f14 = 4ac
	sub.d $f10, $f10, $f14 # $f10 = b^2 - 4ac  -- disc
	sub.d $f8, $f8, $f8 # $f8 = 0
	
	
	c.le.d $f10, $f8
	ldc1 $f28, minusOne
	mul.d $f4, $f4, $f28 # -b
	 
	bc1f hasTwoRoots
	bc1t has1or0roots
	
	hasTwoRoots:
		li $v0, 4
		la $a0, twoRoots
		syscall
		
		sqrt.d $f10, $f10 # $f10 = sqrt(D)
		ldc1 $f8, two
		mul.d $f2, $f2, $f8 # $f2 = 2a
		sub.d $f14, $f4, $f10 # $f14 = b - sqrt(D)
		
		li $v0, 3
		div.d $f12, $f14, $f2 #root1
		syscall
		jal println
		
		add.d $f14, $f4, $f10
		li $v0, 3
		div.d $f12, $f14, $f2 #root2
		syscall
		
		li $v0, 10
		syscall
	has1or0roots:
		c.eq.d $f10, $f8
		bc1t has1root
		
		#has no root
		li $v0, 4
		la $a0, noRoots
		syscall
		
		li $v0, 10
		syscall
	has1root:
		li $v0, 4
		la $a0, oneRoot
		syscall
		
		ldc1 $f8, two
		mul.d $f2, $f2, $f8 # $f2 = 2a
		li $v0, 3
		div.d $f12, $f4, $f2 #root1
		syscall	
	
	li $v0,10
	syscall
	
println:
	li $v0, 4
	la $a0, newLine
	syscall
	
	jr $ra