#pragma once
#include "config.h"

struct VM
{
    int8_t R[16] = {};
    uint8_t PC = 0;
    uint16_t IR = 0;
    uint8_t SP = 0xFF; // last 16 bytes is stack page
    uint8_t FG = 0;

    uint8_t mem[256];

    bool execute();
};

enum class INST : int
{
    NOP,
    LDI,
    LDR,
    STR,
    ADD,
    SUB,
    JMP,
    JZ,
    JC,
    PSH,
    PLL,
    OUT,
    AND,
    OR,
    NOT,
    HLT
};

enum class FLAGS : int
{
    Z = 1 << 0,
    C = 1 << 1
};