#include "vm.h"

bool VM::execute()
{
    //*
    //* FETCH
    //*
    IR = (mem[PC] << 8) | mem[PC + 1];
    PC += 2;

    //*
    //* DECODE
    //*
    uint8_t dst = (IR >> 8) & 0xF;
    uint8_t imm = IR & 0xFF;
    uint8_t src = (IR >> 4) & 0xF;
    uint8_t op = (IR >> 12) & 0xF;

    //*
    //* EXECUTE
    //*
    switch (static_cast<INST>(op))
    {
    case INST::NOP:
        break;

    case INST::LDI:
        R[dst] = imm;
        break;

    case INST::LDR:
        R[dst] = mem[imm];
        break;

    case INST::STR:
        mem[imm] = R[dst];
        break;

    case INST::ADD:
    {
        uint16_t result = R[dst] + imm;
        if (result == 0)
            FG |= static_cast<uint32_t>(FLAGS::Z);
        if (result > 0xFF)
            FG |= static_cast<uint32_t>(FLAGS::C);
        R[dst] += imm;
    }
    break;

    case INST::SUB:
    {
        int16_t result = R[dst] - imm;
        if (result == 0)
            FG |= static_cast<uint32_t>(FLAGS::Z);
        if (R[dst] < imm)
            FG |= static_cast<uint32_t>(FLAGS::C);
        R[dst] -= imm;
    }
    break;

    case INST::JMP:
        PC = imm;
        break;

    case INST::JZ:
        if (FG | static_cast<uint32_t>(FLAGS::Z))
            PC = imm;
        break;

    case INST::JC:
        if (FG | static_cast<uint32_t>(FLAGS::C))
            PC = imm;
        break;

    case INST::PSH:
    {
        if (imm != 1)
        {
            mem[SP--] = R[dst];
        }
        else
        {
            mem[SP--] = PC;
            mem[SP--] = (PC >> 8) & 0xFF;
        }
    }
    break;

    case INST::PLL:
    {
        if (imm != 1)
        {
            R[dst] = mem[++SP];
        }
        else
        {
            PC = mem[++SP];
            PC |= (mem[++SP] << 8);
        }
    }
    break;

    case INST::OUT:
    {
        std::cout << "\033[32m\n\tLOG printed by software : " << std::hex << "R" << static_cast<uint32_t>(dst) << " = " << std::setw(2) << std::setfill('0') << static_cast<uint32_t>(R[dst]) << std::dec << "\n\033[0m";
    }
    break;

    case INST::AND:
    {
        R[dst] &= imm;
        if (R[dst] == 0)
            FG |= static_cast<uint32_t>(FLAGS::Z);
    }
    break;

    case INST::OR:
    {
        R[dst] |= imm;
        if (R[dst] == 0)
            FG |= static_cast<uint32_t>(FLAGS::Z);
    }
    break;

    case INST::NOT:
    {
        R[dst] = ~R[dst];
        if (R[dst] == 0)
            FG |= static_cast<uint32_t>(FLAGS::Z);
    }
    break;

    case INST::HLT:
        return false;

    default:
    {
        fprintf(stderr, "Unknown opcode : %02X", (uint32_t)op);
        return false;
    }
    }

    return true;
}