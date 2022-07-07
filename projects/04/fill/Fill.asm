// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Initialize current screen index variable
@i
M=0

(LOOP)
// Get keyboard input
@KBD
D=M
// If key not pressed jump to code that whites out the screen
@WHITE
D;JEQ
// Else jump to code that blacks out the screen
@BLACK
0;JMP

(BLACK)
// If we have reached the end of the screen then stop
@i
D=M
@8192
D=D-A
// Jump back to start of main loop if end of screen is reached
@LOOP
D;JEQ
// Change value of current block of screen to black
@SCREEN
D=A
@i
D=D+M
// Set A to screen offset
A=D
// Change value of current screen offset
M=-1
// Increment index
@i
M=M+1
// Repeat
@BLACK
0;JMP

(WHITE)
// If we have reached beginning of screen, then stop
@i
D=M
@LOOP
D;JLT

// Change value of current block of screen to white
@SCREEN
D=A
@i
D=D+M
// Set A to screen offset
A=D
// Change value of current screen offset
M=0
// Decrement index
@i
M=M-1
// Repeat
@WHITE
0;JMP

(FILL)