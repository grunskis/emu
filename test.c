#include <assert.h>

#include "8080.h"

uint8_t program[] = {
  0x06, 0x29, // MVI B, 41
  0x04,       // INR B
  0x76        // HLT (all programs should end with HLT)
};

int main(void) {
  cpu_t *cpu = cpu_init();

  cpu_load_program(cpu, program, sizeof(program));

  while (1) {
    cpu_execute(cpu);

    if (cpu_halted(cpu)) {
      break;
    }
  }

  assert(cpu->registers.b == 42);
}
