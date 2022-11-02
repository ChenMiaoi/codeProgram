DATA SEGMENT;
    MYWORD DB "hello world!$";
DATA ENDS

CODE SEGMENT;
    ASSUME CS:CODE, DS:DATA;

start:
    MOV AX, DATA;
    MOV DS, AX;
    LEA DX, MYWORD;
    MOV AH, 09h;
    INT 21h;
    MOV AX, 4c00h;
    INT 21h;
CODE ENDS

END start;