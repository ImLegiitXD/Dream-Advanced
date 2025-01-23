procedure VIRTUALIZER_TIGER_WHITE_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 103
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 100
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_TIGER_WHITE_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 503
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 500
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_TIGER_RED_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 104
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 101
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_TIGER_RED_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 504
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 501
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_TIGER_BLACK_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 105
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 102
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_TIGER_BLACK_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 505
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 502
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_FISH_WHITE_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 107
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 106
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_FISH_WHITE_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 507
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 506
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_FISH_RED_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 109
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 108
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_FISH_RED_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 509
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 508
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_FISH_BLACK_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 111
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 110
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_FISH_BLACK_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 511
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 510
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_PUMA_WHITE_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 113
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 112
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_PUMA_WHITE_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 513
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 512
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_PUMA_RED_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 115
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 114
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_PUMA_RED_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 515
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 514
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_PUMA_BLACK_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 117
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 116
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_PUMA_BLACK_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 517
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 516
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_SHARK_WHITE_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 119
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 118
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_SHARK_WHITE_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 519
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 518
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_SHARK_RED_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 121
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 120
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_SHARK_RED_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 521
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 520
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_SHARK_BLACK_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 123
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 122
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_SHARK_BLACK_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 523
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 522
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_DOLPHIN_WHITE_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 135
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 134
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_DOLPHIN_WHITE_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 535
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 534
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_DOLPHIN_RED_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 137
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 136
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_DOLPHIN_RED_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 537
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 536
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_DOLPHIN_BLACK_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 139
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 138
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_DOLPHIN_BLACK_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 539
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 538
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_EAGLE_WHITE_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 147
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 146
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_EAGLE_WHITE_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 547
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 546
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_EAGLE_RED_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 149
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 148
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_EAGLE_RED_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 549
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 548
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_EAGLE_BLACK_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 151
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 150
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_EAGLE_BLACK_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 551
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 550
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_MUTATE_ONLY_START();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 16
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 16
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

procedure VIRTUALIZER_MUTATE_ONLY_END();
{$IFDEF CPU64BITS}
asm
    push    rax
    push    rbx
    push    rcx

    mov     eax, 'CV'
    mov     ebx, 17
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
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
    mov     ebx, 17
    mov     ecx, 'CV'
    db      03, $d8
    db      03, $c8
    pop     ecx
    pop     ebx
    pop     eax
    ret

end;

{$ENDIF}

