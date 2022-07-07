// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Set result and iterator registers to 0
@R2
M=0
@i
M=1
// Begin multiplication loop
(LOOP)
// Store iterator in d
@i
D=M
// Subtract second number from iterator in order to keep track of how many times
// we need to sum first number
@R1
D=D-M
// Jump to END if i - R1 > 0
@END
D;JGT
// Add first number to result
@R0
D=M
@R2
M=M+D
// Increment iterator
@i
M=M+1
// Jump back to start of multiplication loop
@LOOP
0;JMP
(END)
// Infinite loop
@END
0;JMP