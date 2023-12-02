.MODEL SMALL
.STACK 100H
.DATA
    LF EQU 0AH
    CR EQU 0DH
    PROMPT1 DB 'Enter any single character : $' 
    NEW_LINE DB CR,LF,'$'  
    
    UPPER DB  'Uppercase Letter$' 
    LOWER DB  'Lowercase Letter$'
    NUMBER DB 'Number$'
    NON_ALPHA DB  'Non Alphanumeric$'
    CHAR_INPUT DB ?

.CODE
    MAIN PROC
        MOV AX, @DATA 
        MOV DS, AX   
        
        LEA DX,PROMPT1
        MOV AH,9
        INT 21H  
        
        MOV AH,1
        INT 21H
        MOV CHAR_INPUT,AL    
        
        
        MOV AH,9
        LEA DX,NEW_LINE
        INT 21H 
        
        CMP CHAR_INPUT,'A'
        JL SMALLER_THAN_CAP_A
        CMP CHAR_INPUT,'Z'
        JG GREATER_THAN_CAP_Z 
        
        BETWEEN_A_TO_Z:
            LEA DX,UPPER  
            MOV AH,9
            INT 21H 
            JMP EXIT_DOS   
            
        SMALLER_THAN_CAP_A:
            CMP CHAR_INPUT,'0'
            JL NON_ALPHANUMERIC
            CMP CHAR_INPUT,'9'
            JG NON_ALPHANUMERIC
            
            LEA DX, NUMBER 
            MOV AH,9
            INT 21H    
            JMP EXIT_DOS
            
        GREATER_THAN_CAP_Z:
            CMP CHAR_INPUT,'a'
            JL NON_ALPHANUMERIC
            CMP CHAR_INPUT,'z'
            JG NON_ALPHANUMERIC
            
            LEA DX, LOWER 
            MOV AH,9
            INT 21H 
            JMP EXIT_DOS
        NON_ALPHANUMERIC:
            LEA DX,NON_ALPHA  
            MOV AH,9
            INT 21H
        
        
    EXIT_DOS:
        MOV AH,4CH
        INT 21H
    MAIN ENDP
END MAIN