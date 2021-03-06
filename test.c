#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "8080.h"

#define IS_FLAG_SET(cpu, flag) (cpu->registers.f & flag) == flag
#define IS_FLAG_UNSET(cpu, flag) (cpu->registers.f & flag) != flag

cpu_t *load_and_execute(uint8_t *program, size_t size) {
  cpu_t *cpu = cpu_init();

  cpu_load_program(cpu, program, size);

  while (1) {
    cpu_execute(cpu);

    if (cpu_halted(cpu)) {
      break;
    }
  }

  return cpu;
}

int main(void) {
  cpu_t *cpu;

  uint8_t nop[] = {
    0x00, // NOP
    0x00, // NOP
    0x76  // HTL (all programs should end with HLT)
  };
  cpu = load_and_execute(nop, sizeof(nop));
  assert(cpu->cycles == 15);

  uint8_t move_and_increment[] = {
    0x06, 0x29, // MVI B, 41
    0x04,       // INR B
    0x76        // HLT
  };
  cpu = load_and_execute(move_and_increment, sizeof(move_and_increment));
  assert(cpu->registers.b == 42);
  assert(IS_FLAG_SET(cpu, FLAG_PARITY));

  printf("all good...\n");
  return 0;
}
