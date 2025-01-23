unit VirtualizerAsmSDK;

interface

procedure VIRTUALIZER_START();
procedure VIRTUALIZER_END();
procedure VIRTUALIZER_STR_ENCRYPT_START();
procedure VIRTUALIZER_STR_ENCRYPT_END();
procedure VIRTUALIZER_STR_ENCRYPTW_START();
procedure VIRTUALIZER_STR_ENCRYPTW_END();
procedure VIRTUALIZER_UNPROTECTED_START();
procedure VIRTUALIZER_UNPROTECTED_END();

{$I VirtualizerAsmSDK_CustomVMsInterface.pas}

implementation

{$IFDEF MACOS64}

const 
OBJFILE = 'VirtualizerSDKMacrosMacos64.o';

procedure VIRTUALIZER_START(); external OBJFILE name 'VIRTUALIZER_START_ASM';
procedure VIRTUALIZER_END(); external OBJFILE name 'VIRTUALIZER_END_ASM';
procedure VIRTUALIZER_STR_ENCRYPT_START(); external OBJFILE name 'VIRTUALIZER_STR_ENCRYPT_START_ASM';
procedure VIRTUALIZER_STR_ENCRYPT_END(); external OBJFILE name 'VIRTUALIZER_STR_ENCRYPT_END_ASM';
procedure VIRTUALIZER_STR_ENCRYPTW_START(); external OBJFILE name 'VIRTUALIZER_STR_ENCRYPTW_START_ASM';
procedure VIRTUALIZER_STR_ENCRYPTW_END(); external OBJFILE name 'VIRTUALIZER_STR_ENCRYPTW_END_ASM';
procedure VIRTUALIZER_UNPROTECTED_START(); external OBJFILE name 'VIRTUALIZER_UNPROTECTED_START_ASM';
procedure VIRTUALIZER_UNPROTECTED_END(); external OBJFILE name 'VIRTUALIZER_UNPROTECTED_END_ASM';

{$I VirtualizerAsmSDK_CustomVMsImplementationMacos64.pas}

{$ELSE}
procedure VIRTUALIZER_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 1
    mov     ecx, 'CV'
    db      03, $D8
    db      03, $C8

    pop     rcx
    pop     rbx
    pop     rax
    ret
end;
{$ELSE}

asm
    push    eax
    push    ebx
    push    ecx

    mov     eax, 'CV'
    mov     ebx, 1
    mov     ecx, 'CV'
    db      03, $D8
    db      03, $C8
    pop     ecx
    pop     ebx
    pop     eax
    ret
end;

{$ENDIF}

procedure VIRTUALIZER_END();
{$IFDEF WIN64}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 2
    mov     ecx, 'CV'
    db      03, $D8
    db      03, $C8

    pop     rcx
    pop     rbx
    pop     rax
    ret
end;
{$ELSE}

asm
    push    eax
    push    ebx
    push    ecx

    mov     eax, 'CV'
    mov     ebx, 2
    mov     ecx, 'CV'
    db      03, $D8
    db      03, $C8
    pop     ecx
    pop     ebx
    pop     eax
    ret
end;

{$ENDIF}

procedure VIRTUALIZER_STR_ENCRYPT_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 23
    mov     ecx, 'CV'
    db      03, $D8
    db      03, $C8

    pop     rcx
    pop     rbx
    pop     rax
    ret
end;
{$ELSE}

asm
    push    eax
    push    ebx
    push    ecx

    mov     eax, 'CV'
    mov     ebx, 23
    mov     ecx, 'CV'
    db      03, $D8
    db      03, $C8
    pop     ecx
    pop     ebx
    pop     eax
    ret
end;

{$ENDIF}

procedure VIRTUALIZER_STR_ENCRYPT_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 24
    mov     ecx, 'CV'
    db      03, $D8
    db      03, $C8

    pop     rcx
    pop     rbx
    pop     rax
    ret
end;
{$ELSE}

asm
    push    eax
    push    ebx
    push    ecx

    mov     eax, 'CV'
    mov     ebx, 24
    mov     ecx, 'CV'
    db      03, $D8
    db      03, $C8
    pop     ecx
    pop     ebx
    pop     eax
    ret
end;

{$ENDIF}

procedure VIRTUALIZER_STR_ENCRYPTW_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 27
    mov     ecx, 'CV'
    db      03, $D8
    db      03, $C8

    pop     rcx
    pop     rbx
    pop     rax
    ret
end;
{$ELSE}

asm
    push    eax
    push    ebx
    push    ecx

    mov     eax, 'CV'
    mov     ebx, 27
    mov     ecx, 'CV'
    db      03, $D8
    db      03, $C8
    pop     ecx
    pop     ebx
    pop     eax
    ret
end;

{$ENDIF}

procedure VIRTUALIZER_STR_ENCRYPTW_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 28
    mov     ecx, 'CV'
    db      03, $D8
    db      03, $C8

    pop     rcx
    pop     rbx
    pop     rax
    ret
end;
{$ELSE}

asm
    push    eax
    push    ebx
    push    ecx

    mov     eax, 'CV'
    mov     ebx, 28
    mov     ecx, 'CV'
    db      03, $D8
    db      03, $C8
    pop     ecx
    pop     ebx
    pop     eax
    ret
end;

{$ENDIF}

procedure VIRTUALIZER_UNPROTECTED_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 18
    mov     ecx, 'CV'
    db      03, $D8
    db      03, $C8

    pop     rcx
    pop     rbx
    pop     rax
    ret
end;
{$ELSE}

asm
    push    eax
    push    ebx
    push    ecx

    mov     eax, 'CV'
    mov     ebx, 18
    mov     ecx, 'CV'
    db      03, $D8
    db      03, $C8
    pop     ecx
    pop     ebx
    pop     eax
    ret
end;

{$ENDIF}

procedure VIRTUALIZER_UNPROTECTED_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 19
    mov     ecx, 'CV'
    db      03, $D8
    db      03, $C8

    pop     rcx
    pop     rbx
    pop     rax
    ret
end;
{$ELSE}

asm
    push    eax
    push    ebx
    push    ecx

    mov     eax, 'CV'
    mov     ebx, 19
    mov     ecx, 'CV'
    db      03, $D8
    db      03, $C8
    pop     ecx
    pop     ebx
    pop     eax
    ret
end;

{$ENDIF}

{$I VirtualizerAsmSDK_CustomVMsImplementationInlineAsm.pas}

{$ENDIF}
end.

