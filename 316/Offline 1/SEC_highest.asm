.MODEL SMALL
.STACK 100H
.DATA
    LF EQU 0AH
    CR EQU 0DH
    PROMPT1 DB 'Enter three single lowercase letters : $'
    NEW_LINE DB CR,LF,'$'   
    PROMPT2 DB CR,LF,'First character: $'
    PROMPT3 DB CR,LF,'Second character: $'
    PROMPT4 DB CR,LF,'Third character: $'
    MSG1 DB CR,LF,'Second highest number : $'   
    ALL_EQU DB CR,LF,'All letters are equal.$'
    INVALID_MSG DB CR,LF,'Invalid input.$'

    FIRST_CHAR DB ?
    SEC_CHAR DB ?
    THIRD_CHAR DB ?  
    RES_CHAR DB ?
    

.CODE
    MAIN PROC
        MOV AX, @DATA 
        MOV DS, AX   
        
        LEA DX,PROMPT1
        MOV AH,9
        INT 21H 
        FIRST_INPUT:
            LEA DX,PROMPT2
            MOV AH,9
            INT 21H 
         
            MOV AH,1
            INT 21H
            MOV FIRST_CHAR,AL 
    
            CMP AL, 'a'
            JB INVALID_INPUT
            CMP AL, 'z'
            JA INVALID_INPUT
            
        SECOND_INPUT:
            LEA DX,PROMPT3
            MOV AH,9
            INT 21H 
            
            MOV AH,1
            INT 21H
            MOV SEC_CHAR,AL 
       
            CMP AL, 'a'
            JB INVALID_INPUT
            CMP AL, 'z'
            JA INVALID_INPUT
            
        THIRD_INPUT:
            LEA DX,PROMPT4
            MOV AH,9
            INT 21H  
            
            MOV AH,1
            INT 21H
            MOV THIRD_CHAR,AL
         
            CMP AL, 'a'
            JB INVALID_INPUT
            CMP AL, 'z'
            JA INVALID_INPUT
                              
        MOV AL,FIRST_CHAR
        CMP AL,SEC_CHAR
        JE  A_EQU_B
        JG  A_GREAT_B
        
        CMP AL,THIRD_CHAR
        JGE A_ANS
        JMP A_SMALLEST
        
        A_SMALLEST:
            MOV AL,SEC_CHAR
            CMP AL,THIRD_CHAR
            JE A_ANS
            JG C_ANS
            JMP B_ANS
         
        A_GREAT_B:
            MOV AL,SEC_CHAR
            CMP AL,THIRD_CHAR
            JGE B_ANS 
            MOV AL,FIRST_CHAR
            CMP AL,THIRD_CHAR
            JG C_ANS
            JE B_ANS
            JMP A_ANS  
            
        A_EQU_B: 
            MOV AL,FIRST_CHAR
            CMP AL,THIRD_CHAR
            JG C_ANS
            JL A_ANS 
            MOV AH,9
            LEA DX,ALL_EQU
            INT 21H
            JMP EXIT_DOS 
            
        DISPLAY:
            MOV AH,9
            LEA DX,MSG1
            INT 21H
              
            MOV AH,2 
            MOV DL,RES_CHAR
            INT 21H
            JMP EXIT_DOS 
            
        A_ANS: 
            
            MOV AL,FIRST_CHAR   
            MOV RES_CHAR,AL
            JMP DISPLAY 
            
        B_ANS:
            MOV AL,SEC_CHAR   
            MOV RES_CHAR,AL
            JMP DISPLAY
            
        C_ANS: 
            MOV AL,THIRD_CHAR 
            MOV RES_CHAR,AL
            JMP DISPLAY             
        
        INVALID_INPUT:
            MOV AH, 9
            LEA DX, INVALID_MSG
            INT 21H
            JMP EXIT_DOS
            
    EXIT_DOS:
        MOV AH,4CH
        INT 21H
    MAIN ENDP
END MAIN
