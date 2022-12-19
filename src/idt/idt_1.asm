; compile with NASM
extern exception_handler
%macro isr_err_stub 1
isr_stub_%+%1:
	call exception_handler
	iretq
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
	call exception_handler
	iretq
%endmacro

isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31

global isr_stub_table
isr_stub_table:
%assign i 0 
%rep    32 
    dq isr_stub_%+i
%assign i i+1 
%endrep

global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

irq0:
	push byte 0
	push byte 32
	

irq1:
	push byte 1
	push byte 33
	
irq2:
	push byte 2
	push byte 34
	
irq3:
	push byte 3
	push byte 35
	
irq4:
	push byte 4
	push byte 36
	
irq5:
	push byte 5
	push byte 37
	
irq6:
	push byte 6
	push byte 38
	
irq7:
	push byte 7
	push byte 39
	
irq8:
	push byte 8
	push byte 40
	
irq9:
	push byte 9
	push byte 41
	
irq10:
	push byte 10
	push byte 42
	
irq11:
	push byte 11
	push byte 43
	
irq12:
	push byte 12
	push byte 44
	
irq13:
	push byte 13
	push byte 45
	
irq14:
	push byte 14
	push byte 46
	
irq15:
	push byte 15
	push byte 47
