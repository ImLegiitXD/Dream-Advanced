; ****************************************************************************
; Module: VirtualizerSDKCustomVmMacros.inc
; Description: Another way to link with the SecureEngine SDK via an ASM module
;
; Author/s: Oreans Technologies 
; (c) 2021 Oreans Technologies
;
; --- File generated automatically from Oreans VM Generator (14/5/2021) ---
; ****************************************************************************


BITS 64

section .text

global _VIRTUALIZER_TIGER_WHITE_START_ASM
global _VIRTUALIZER_TIGER_WHITE_END_ASM
global _VIRTUALIZER_TIGER_RED_START_ASM
global _VIRTUALIZER_TIGER_RED_END_ASM
global _VIRTUALIZER_TIGER_BLACK_START_ASM
global _VIRTUALIZER_TIGER_BLACK_END_ASM
global _VIRTUALIZER_FISH_WHITE_START_ASM
global _VIRTUALIZER_FISH_WHITE_END_ASM
global _VIRTUALIZER_FISH_RED_START_ASM
global _VIRTUALIZER_FISH_RED_END_ASM
global _VIRTUALIZER_FISH_BLACK_START_ASM
global _VIRTUALIZER_FISH_BLACK_END_ASM
global _VIRTUALIZER_PUMA_WHITE_START_ASM
global _VIRTUALIZER_PUMA_WHITE_END_ASM
global _VIRTUALIZER_PUMA_RED_START_ASM
global _VIRTUALIZER_PUMA_RED_END_ASM
global _VIRTUALIZER_PUMA_BLACK_START_ASM
global _VIRTUALIZER_PUMA_BLACK_END_ASM
global _VIRTUALIZER_SHARK_WHITE_START_ASM
global _VIRTUALIZER_SHARK_WHITE_END_ASM
global _VIRTUALIZER_SHARK_RED_START_ASM
global _VIRTUALIZER_SHARK_RED_END_ASM
global _VIRTUALIZER_SHARK_BLACK_START_ASM
global _VIRTUALIZER_SHARK_BLACK_END_ASM
global _VIRTUALIZER_DOLPHIN_WHITE_START_ASM
global _VIRTUALIZER_DOLPHIN_WHITE_END_ASM
global _VIRTUALIZER_DOLPHIN_RED_START_ASM
global _VIRTUALIZER_DOLPHIN_RED_END_ASM
global _VIRTUALIZER_DOLPHIN_BLACK_START_ASM
global _VIRTUALIZER_DOLPHIN_BLACK_END_ASM
global _VIRTUALIZER_EAGLE_WHITE_START_ASM
global _VIRTUALIZER_EAGLE_WHITE_END_ASM
global _VIRTUALIZER_EAGLE_RED_START_ASM
global _VIRTUALIZER_EAGLE_RED_END_ASM
global _VIRTUALIZER_EAGLE_BLACK_START_ASM
global _VIRTUALIZER_EAGLE_BLACK_END_ASM
global _VIRTUALIZER_LION_WHITE_START_ASM
global _VIRTUALIZER_LION_WHITE_END_ASM
global _VIRTUALIZER_LION_RED_START_ASM
global _VIRTUALIZER_LION_RED_END_ASM
global _VIRTUALIZER_LION_BLACK_START_ASM
global _VIRTUALIZER_LION_BLACK_END_ASM
global _VIRTUALIZER_MUTATE_ONLY_START_ASM
global _VIRTUALIZER_MUTATE_ONLY_END_ASM

; ****************************************************************************
; VIRTUALIZER_TIGER_WHITE definition
; ****************************************************************************

_VIRTUALIZER_TIGER_WHITE_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 103
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_TIGER_WHITE_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 503
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_TIGER_RED definition
; ****************************************************************************

_VIRTUALIZER_TIGER_RED_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 104
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_TIGER_RED_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 504
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_TIGER_BLACK definition
; ****************************************************************************

_VIRTUALIZER_TIGER_BLACK_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 105
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_TIGER_BLACK_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 505
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_FISH_WHITE definition
; ****************************************************************************

_VIRTUALIZER_FISH_WHITE_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 107
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_FISH_WHITE_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 507
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_FISH_RED definition
; ****************************************************************************

_VIRTUALIZER_FISH_RED_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 109
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_FISH_RED_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 509
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_FISH_BLACK definition
; ****************************************************************************

_VIRTUALIZER_FISH_BLACK_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 111
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_FISH_BLACK_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 511
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_PUMA_WHITE definition
; ****************************************************************************

_VIRTUALIZER_PUMA_WHITE_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 113
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_PUMA_WHITE_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 513
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_PUMA_RED definition
; ****************************************************************************

_VIRTUALIZER_PUMA_RED_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 115
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_PUMA_RED_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 515
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_PUMA_BLACK definition
; ****************************************************************************

_VIRTUALIZER_PUMA_BLACK_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 117
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_PUMA_BLACK_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 517
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_SHARK_WHITE definition
; ****************************************************************************

_VIRTUALIZER_SHARK_WHITE_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 119
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_SHARK_WHITE_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 519
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_SHARK_RED definition
; ****************************************************************************

_VIRTUALIZER_SHARK_RED_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 121
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_SHARK_RED_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 521
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_SHARK_BLACK definition
; ****************************************************************************

_VIRTUALIZER_SHARK_BLACK_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 123
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_SHARK_BLACK_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 523
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_DOLPHIN_WHITE definition
; ****************************************************************************

_VIRTUALIZER_DOLPHIN_WHITE_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 135
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_DOLPHIN_WHITE_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 535
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_DOLPHIN_RED definition
; ****************************************************************************

_VIRTUALIZER_DOLPHIN_RED_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 137
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_DOLPHIN_RED_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 537
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_DOLPHIN_BLACK definition
; ****************************************************************************

_VIRTUALIZER_DOLPHIN_BLACK_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 139
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_DOLPHIN_BLACK_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 539
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_EAGLE_WHITE definition
; ****************************************************************************

_VIRTUALIZER_EAGLE_WHITE_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 147
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_EAGLE_WHITE_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 547
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_EAGLE_RED definition
; ****************************************************************************

_VIRTUALIZER_EAGLE_RED_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 149
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_EAGLE_RED_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 549
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_EAGLE_BLACK definition
; ****************************************************************************

_VIRTUALIZER_EAGLE_BLACK_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 151
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_EAGLE_BLACK_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 551
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_LION_WHITE definition
; ****************************************************************************

_VIRTUALIZER_LION_WHITE_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 161
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_LION_WHITE_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 561
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_LION_RED definition
; ****************************************************************************

_VIRTUALIZER_LION_RED_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 163
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_LION_RED_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 563
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_LION_BLACK definition
; ****************************************************************************

_VIRTUALIZER_LION_BLACK_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 165
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_LION_BLACK_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 565
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret


; ****************************************************************************
; VIRTUALIZER_MUTATE_ONLY definition
; ****************************************************************************

_VIRTUALIZER_MUTATE_ONLY_START_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 16
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

_VIRTUALIZER_MUTATE_ONLY_END_ASM:

    push    rax
    push    rbx
    push    rcx

    mov     eax, 'VC'
    mov     ebx, 17
    mov     ecx, 'VC'
    db      03, 0d8h ; add     ebx, eax
    db      03, 0c8h ; add     ecx, eax

    pop     rcx
    pop     rbx
    pop     rax
    ret

