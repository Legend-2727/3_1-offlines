.MODEL SMALL
.STACK 100H
.DATA
    LF EQU 0AH
    CR EQU 0DH
    PROMPT1 DB 'Enter value of n : $' 
    NEW_LINE DB CR,LF,'$'  
    ARR_N DW 10 DUP(?)  
    N DW 0 
    RES DW 0  
    ANS_STRING DB 10 DUP('$')

.CODE
    MAIN PROC
        MOV AX, @DATA 
        MOV DS, AX   
        
        LEA DX,PROMPT1
        MOV AH,9
        INT 21H  
        
        LEA SI,ARR_N  
        
        
        READ_N:
            MOV AH,1
            INT 21H
            
            CMP AL,CR
            JE  SUM
            MOV [SI],AL
            INC SI
            JMP READ_N
        SUM:
            LEA SI,ARR_N
            MOV DX,0 
            MOV AX,0
            CALL DIGIT_SUM
            MOV RES,DX
       
          GENERATE_ANS:
            MOV BX,10  
            LEA SI,ANS_STRING  
            MOV CX,0 
            LOOP3:
                MOV DX,0
                MOV AX,RES 
                DIV BX 
                MOV [SI],DX 
                ADD [SI],48
                CMP AX,0
                JE  PRINT_ANS
                
                MOV RES,AX
                INC SI 
                INC CX
                JMP LOOP3
           PRINT_ANS:
            MOV AH,9
            LEA DX,NEW_LINE
            INT 21H
            MOV DX,0
            LOOP4:
                MOV DL,[SI]
                MOV AH,2
                INT 21H
                DEC SI
                DEC CX
                CMP CX,0
                JL EXIT_DOS
                JMP LOOP4 
                
                                      
    EXIT_DOS:
        MOV AH,4CH
        INT 21H
    MAIN ENDP
    
    DIGIT_SUM PROC NEAR:
         
        MOV AL,[SI]
        SUB AX,48
        PUSH AX
        INC SI 
        CMP [SI],0
        JE DONE
        CALL DIGIT_SUM
        DONE:
            POP AX
            ADD DX,AX
            RET 
     DIGIT_SUM ENDP 
END MAIN
