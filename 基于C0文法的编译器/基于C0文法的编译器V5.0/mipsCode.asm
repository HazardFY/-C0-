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
sub $sp, $sp, 4
sub $sp, $sp, 4
sub $sp, $sp, 4
sub $sp, $sp, 4
sub $sp, $sp, 4
sub $sp, $sp, 4
sub $sp, $sp, 4
sub $sp, $sp, 4
sub $sp, $sp, 4
li $t0, 3
sw $t0, -24($fp)
li $t0, 2
sw $t0, -20($fp)
lw $t1, -20($fp)
lw $t2, -24($fp)
sub $t0, $t1, $t2
sw $t0, -32($fp)
lw $t1, -20($fp)
lw $t2, -24($fp)
add $t0, $t1, $t2
sw $t0, -16($fp)
li $t0, 5
sw $t0, -8($fp)
li $t1, 2
lw $t2, -8($fp)
mul $t0, $t1, $t2
sw $t0, -12($fp)
lw $t1, -12($fp)
lw $t2, -16($fp)
mul $t0, $t1, $t2
sw $t0, -28($fp)
lw $t1, -28($fp)
lw $t2, -32($fp)
mul $t0, $t1, $t2
sw $t0, -36($fp)
sub $sp, $sp, 8
lw $t0, -12($fp)
sw $t0, ($sp)
sub $sp, $sp, 4
lw $t0, -16($fp)
sw $t0, ($sp)
sub $sp, $sp, 4
jal compute
move $t0, $v1
sw $t0, -40($fp)
move $v1, $t0
j mainTail
mainTail:
