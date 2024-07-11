.MODEL SMALL
.STACK 100H
.DATA
    LF EQU 0AH
    CR EQU 0DH
    PROMPT1 DB 'Enter value of n and k respectively : $' 
    NEW_LINE DB CR,LF,'$'  
    ARR_N DW 5 DUP(?)  
    ARR_K DW 5 DUP(?) 
    N DW 0
    K DW 0 
    REMAIN DW 0
    RES DW 0  
    CHAR_OUT DB ? 
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
            
            CMP AL,' '
            JE  BUILT_N
            MOV [SI],AL
            INC SI
            JMP READ_N
        BUILT_N:  
            LEA SI,ARR_N
            MOV CX,0
            
            GENERATE_N:
                
               MOV CL,[SI]
               
               CMP CL,0
               JE READ_K
               
               SUB CL,48 
               MOV AX,N 
               MOV BX,10
               MUL BX
               ADD AX,CX
               MOV N,AX
               INC SI
               JMP GENERATE_N
         READ_K:
            LEA SI,ARR_K
            LOOP_K:
                MOV AH,1
                INT 21H
            
                CMP AL,CR
                JE  BUILT_K
                MOV [SI],AL
                INC SI
                JMP LOOP_K 
         BUILT_K:  
            LEA SI,ARR_K
            MOV CX,0
            
            GENERATE_K:
                
               MOV CL,[SI]
               
               CMP CL,0
               JE DIVIDE
               
               SUB CL,48 
               MOV AX,K 
               MOV BX,10
               MUL BX
               ADD AX,CX
               MOV K,AX
               INC SI
               JMP GENERATE_K  
          DIVIDE: 
            MOV AX,N
            MOV REMAIN,AX 
            MOV BX,K 
            ADD RES,AX
            
            LOOP2:
                MOV DX,0
                MOV AX,REMAIN
                DIV BX  
                CMP AX,0
                JE GENERATE_ANS
                ADD RES,AX
                ADD AX,DX
                MOV REMAIN,AX 
                JMP LOOP2
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
END MAIN
