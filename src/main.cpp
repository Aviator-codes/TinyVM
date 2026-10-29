#include "config.h"
#include "vm.h"

int main()
{
    VM vm;
    // TODO: Implement an Assembler to produce bin
    // TODO: Implement a binary loader
    vm.mem[0] = 0x10;
    vm.mem[1] = 5;
    vm.mem[2] = 0x40;
    vm.mem[3] = 3;
    vm.mem[4] = 0xB0;
    vm.mem[5] = 0;
    vm.mem[6] = 0xF0;
    vm.mem[7] = 0x00;

    while (vm.execute())
    {
        // TODO: Do stuff
    }

    return 0;
}