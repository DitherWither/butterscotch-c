# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot_header
    .align 4
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .bss
    .align 16
    stack_bottom:
        .skip 16384 # 16 KiB
    stack_top:

# The kernel entry point.
.section .text
.code32

.global _start
.type _start, @function
_start:
    movl $0x2f4b2f4f, (0xb8000)
    call hcf

    call check_cpuid
    call check_long_mode
    call setup_paging
    movl $stack_top, %esp

    # Call the global constructors.
    call _init

    # Transfer control to the main kernel.
    call kernel_main

    # Hang if kernel_main unexpectedly returns.
    call hcf

## Check if CPUID is supported by attempting to flip the ID bit (bit 21) in
## the FLAGS register. If we can flip it, CPUID is available.
check_cpuid:
    # Copy FLAGS in to EAX via stack
    pushfl
    popl %eax

    # Copy to ECX as well for comparing
    movl %eax, %ecx

    # Flip the ID bit
    xorl $(1 << 21), %eax

    # Copy EAX to flags via stack
    pushl %eax
    popfl

    # Copy FLAGS back to EAX (with the flipped bit if CPUID is available)
    pushfl
    popl %eax

    # Restore flags from the old version in ECX
    pushl %ecx
    popfl

    # Check if the bit was flipped. If it was, then CPUID is supported
    xorl %ecx, %eax
    jz .no_cpuid
    ret

    .no_cpuid:
        call hcf

## Checks if long mode is supported
check_long_mode:
    # Check if CPUID > 0x80000000
    movl $0x80000000, %eax
    cpuid
    cmpl $0x80000001, %eax
    jb .no_long_mode

    movl $(0x80000001), %eax
    cpuid
    test 1 << 28, %edx
    jz .no_long_mode
    ret

    .no_long_mode:
        call hcf

setup_paging:
    # Clear page tables
    movl 0x1000, %edi # edi = Destination Index
    movl %edi, %cr3
    xorl %eax, %eax
    movl 4096, %ecx 
    rep stosl         # Clear Memory
    movl %cr3, %edi
    ret


## Halt and catch fire
hcf:
    cli
    .loop:	
        hlt
        jmp .loop

.size _start, . - _start
