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
li $t0, 5
sw $t0, -12($fp)
li $t0, 1
sw $t0, -8($fp)
sub $sp, $sp, 8
lw $t0, -8($fp)
sw $t0, ($sp)
sub $sp, $sp, 4
lw $t0, -12($fp)
sw $t0, ($sp)
sub $sp, $sp, 4
jal compute
move $t0, $v1
sw $t0, -16($fp)
move $v1, $t0
j mainTail
mainTail:
