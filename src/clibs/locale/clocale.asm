;File .\clocale.c
;Compiler version 5.0.1.1
	SECTION code align=2 CLASS=CODE USE32
	SECTION data align=8 CLASS=DATA USE32
	SECTION bss  align=8 CLASS=BSS USE32
	SECTION const  align=8 CLASS=CONST USE32
	SECTION string  align=2 CLASS=STRING USE32
	SECTION tls  align=2 CLASS=TLS USE32
	SECTION cstartup align=2 CLASS=INITDATA USE32
	SECTION crundown align=2 CLASS=EXITDATA USE32
SECTION code
[GLOBAL	___locale_reinit]
___locale_reinit:
; Line 167:	void __locale_reinit()

; Line 168:	{

L_1:
; Line 169:	    memcpy(__locale_data, __init_locale_data, sizeof(__locale_data));

	PUSH	BYTE 020H
	PUSH	DWORD ___init_locale_data
	PUSH	DWORD ___locale_data
	CALL	_memcpy
	ADD	ESP,BYTE 0CH
; Line 170:	    __ctype_init();

	CALL	___ctype_init
; Line 171:	}

L_2:
	RET
SECTION data

_C_qualified_name	DB	043H
	DB	00H
	RESB	01H

_C_unqualified_name	DB	043H
	DB	00H
	RESB	01H

_C_collate_data	DD	_C_qualified_name+0
	DB	00H
	DB	00H
	DB	01H
	DB	00H
	DB	025H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	02H
	DB	02H
	DB	00H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	01H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	0CH
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	067H
	DB	068H
	DB	00H
	DB	00H
	DB	0DH
	DB	0EH
	DB	0BH
	DB	00H
	DB	01H
	DB	02H
	DB	03H
	DB	04H
	DB	05H
	DB	06H
	DB	07H
	DB	08H
	DB	09H
	DB	0AH
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	010H
	DB	012H
	DB	014H
	DB	016H
	DB	018H
	DB	01AH
	DB	01CH
	DB	01EH
	DB	020H
	DB	022H
	DB	024H
	DB	026H
	DB	028H
	DB	02AH
	DB	02CH
	DB	02EH
	DB	030H
	DB	032H
	DB	034H
	DB	036H
	DB	038H
	DB	03AH
	DB	03CH
	DB	03EH
	DB	040H
	DB	042H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	0FH
	DB	011H
	DB	013H
	DB	015H
	DB	017H
	DB	019H
	DB	01BH
	DB	01DH
	DB	01FH
	DB	021H
	DB	023H
	DB	025H
	DB	027H
	DB	029H
	DB	02BH
	DB	02DH
	DB	02FH
	DB	031H
	DB	033H
	DB	035H
	DB	037H
	DB	039H
	DB	03BH
	DB	03DH
	DB	03FH
	DB	041H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	04EH
	DB	064H
	DB	04FH
	DB	046H
	DB	049H
	DB	045H
	DB	047H
	DB	04DH
	DB	052H
	DB	053H
	DB	051H
	DB	057H
	DB	056H
	DB	055H
	DB	04AH
	DB	048H
	DB	050H
	DB	04BH
	DB	04CH
	DB	05DH
	DB	05EH
	DB	05CH
	DB	063H
	DB	062H
	DB	066H
	DB	05FH
	DB	065H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	044H
	DB	054H
	DB	05BH
	DB	061H
	DB	058H
	DB	059H
	DB	043H
	DB	05AH
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	060H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H

	RESB	042H

_C_monetary_data	DD	_C_qualified_name+0
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	07FH
	DB	07FH
	DB	07FH
	DB	07FH
	DB	07FH
	DB	07FH
	DB	07FH
	DB	07FH
	DB	07FH
	DB	07FH
	DB	07FH
	DB	07FH
	DB	07FH
	DB	07FH

_C_message_data	DD	_C_qualified_name+0
	DB	079H
	DB	00H
	DB	00H
	DB	00H
	DB	00H
	DB	06EH
	DB	00H
	DB	00H
	DB	00H
	DB	00H

_C_userdef_data	DD	_C_qualified_name+0
	DD	00H

	RESB	01H
[GLOBAL	__C_locale_data]

__C_locale_data	DD	_C_unqualified_name+0

	DD	_C_qualified_name+0
	DD	_C_ctype_data+0
	DD	_C_numeric_data+0
	DD	_C_time_data+0
	DD	_C_message_data+0
	DD	_C_userdef_data+0
	RESB	08H
	RESB	01H

___init_locale_data	DD	00H
	DD	_C_collate_data+0

	DD	_C_ctype_data+0
	DD	_C_monetary_data+0
	DD	_C_numeric_data+0
	DD	_C_time_data+0
	DD	_C_message_data+0
	DD	_C_userdef_data+0
SECTION code
SECTION cstartup
	DB	0,230
	DD	___locale_reinit
SECTION const

SECTION code
[EXTERN	___ctype_init]
[EXTERN	_memcpy]
[EXTERN	_C_numeric_data]
[EXTERN	_C_time_data]
[EXTERN	_C_ctype_data]
[EXTERN	___locale_data]