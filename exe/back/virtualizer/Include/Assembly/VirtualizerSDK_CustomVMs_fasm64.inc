; ******************************************************************************
; Header: VirtualizerSDK_CustomVMs_fasm64.inc
; Description: FASM64 macros definitions
;
; Author/s: Oreans Technologies 
; (c) 2021 Oreans Technologies
;
; --- File generated automatically from Oreans VM Generator (14/5/2021) ---
; ******************************************************************************

; ******************************************************************************
;                                 Macros definition
; ******************************************************************************

macro VIRTUALIZER_TIGER_WHITE_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    103
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_TIGER_WHITE_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    503
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_TIGER_RED_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    104
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_TIGER_RED_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    504
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_TIGER_BLACK_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    105
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_TIGER_BLACK_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    505
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_FISH_WHITE_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    107
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_FISH_WHITE_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    507
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_FISH_RED_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    109
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_FISH_RED_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    509
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_FISH_BLACK_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    111
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_FISH_BLACK_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    511
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_PUMA_WHITE_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    113
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_PUMA_WHITE_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    513
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_PUMA_RED_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    115
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_PUMA_RED_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    515
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_PUMA_BLACK_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    117
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_PUMA_BLACK_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    517
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_SHARK_WHITE_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    119
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_SHARK_WHITE_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    519
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_SHARK_RED_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    121
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_SHARK_RED_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    521
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_SHARK_BLACK_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    123
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_SHARK_BLACK_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    523
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_DOLPHIN_WHITE_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    135
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_DOLPHIN_WHITE_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    535
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_DOLPHIN_RED_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    137
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_DOLPHIN_RED_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    537
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_DOLPHIN_BLACK_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    139
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_DOLPHIN_BLACK_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    539
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_EAGLE_WHITE_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    147
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_EAGLE_WHITE_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    547
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_EAGLE_RED_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    149
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_EAGLE_RED_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    549
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_EAGLE_BLACK_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    151
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_EAGLE_BLACK_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    551
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_LION_WHITE_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    161
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_LION_WHITE_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    561
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_LION_RED_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    163
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_LION_RED_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    563
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_LION_BLACK_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    165
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_LION_BLACK_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    565
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_MUTATE_ONLY_START
{
    db    0ebh, 10h
    dd    20205643h
    dd    16
    dd    0
    dd    20205643h
}


macro VIRTUALIZER_MUTATE_ONLY_END
{
    db    0ebh, 10h
    dd    20205643h
    dd    17
    dd    0
    dd    20205643h
}


