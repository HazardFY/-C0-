.data

.text
j main

compute:
sw $fp,16($sp)
add $fp, $sp,16
sw $ra,12($sp)
sub $sp, $sp, 4
lw $t1, -8($fp)
lw $t2, -12($fp)
add $t0, $t1, $t2
sw $t0, -16($fp)
lw $t0, -16($fp)
move $v1, $t0
j computeTail
computeTail:
lw $ra, -4($fp)
move $sp, $fp
lw $fp, ($sp)
jr $ra

main:
sw $fp, ($sp)
move $fp, $sp
sub $sp, $sp, 8
sub $sp, $sp, 12
sub $sp, $sp, 4
sub $sp, $sp, 4
sub $sp, $sp, 4
sub $sp, $sp, 4
sub $sp, $sp, 4
sub $sp, $sp, 4
sub $sp, $sp, 4
sub $sp, $sp, 4
sub $sp, $sp, 4
sub $sp, $sp, 4
sub $sp, $sp, 4
li $t0, 2
sw $t0, -32($fp)
li $t1, 3
lw $t2, -32($fp)
add $t0, $t1, $t2
sw $t0, -36($fp)
lw $t1, -32($fp)
lw $t2, -36($fp)
sub $t0, $t1, $t2
sw $t0, -48($fp)
lw $t1, -32($fp)
lw $t2, -36($fp)
add $t0, $t1, $t2
sw $t0, -28($fp)
li $t0, 5
sw $t0, -20($fp)
li $t1, 2
lw $t2, -20($fp)
mul $t0, $t1, $t2
sw $t0, -24($fp)
lw $t1, -24($fp)
lw $t2, -28($fp)
mul $t0, $t1, $t2
sw $t0, -44($fp)
lw $t1, -44($fp)
lw $t2, -48($fp)
mul $t0, $t1, $t2
sw $t0, -52($fp)
lw $t1, -52($fp)
li $t2, 2
div $t0, $t1, $t2
sw $t0, -56($fp)
lw $t1, -24($fp)
li $t2, 4
mul $t0, $t1, $t2
sw $t0, -40($fp)
sub $sp, $sp, 8
lw $t0, -24($fp)
sw $t0, ($sp)
sub $sp, $sp, 4
lw $t0, -28($fp)
sw $t0, ($sp)
sub $sp, $sp, 4
jal compute
move $t0, $v1
sw $t0, -60($fp)
move $v1, $t0
j mainTail
mainTail:
