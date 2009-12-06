#include <stdlib.h>
#include <string.h>

#include "8080.h"

static uint8_t inc(uint8_t);

struct instruction_set instruction_set[] = {
  {0x00, 4, cpu_00}, // NOP
  {0x04, 5, cpu_04}, // INR B
  {0x06, 7, cpu_06}, // MVI B, n
  {0x76, 7, cpu_76}, // HLT
  {0xff, 0, 0}
};

cpu_t *cpu_init() {
  cpu_t *cpu = (cpu_t *)malloc(sizeof(struct cpu));
  
  cpu_reset(cpu);

  return cpu;
}

void cpu_reset(cpu_t *cpu) {
  cpu->registers.a = 0;

  cpu->registers.b = 0;
  cpu->registers.c = 0;
  cpu->registers.d = 0;
  cpu->registers.e = 0;
  cpu->registers.h = 0;
  cpu->registers.l = 0;

  cpu->registers.pc = 0;

  cpu->halt = 0;

  cpu->cycles = 0;
}

void cpu_execute(cpu_t *cpu) {
  uint8_t opcode = cpu->rom[cpu->registers.pc++];

  // find handler
  struct instruction_set *p = &instruction_set[0];

  while (p->instruction != 0xff) {
    if (p->instruction == opcode && p->handler) {
      p->handler(cpu);

      cpu->cycles += p->cycles;

      break;
    }
    p++;
  }
}

uint8_t cpu_halted(cpu_t *cpu) {
  return cpu->halt;
}

void cpu_load_program(cpu_t *cpu, uint8_t *data, size_t size) {
  memcpy(cpu->rom, data, size);
}

void cpu_00(cpu_t *cpu) {
  // do nothing
}

void cpu_04(cpu_t *cpu) {
  cpu->registers.b = inc(cpu->registers.b);
}

void cpu_06(cpu_t *cpu) {
  cpu->registers.b = cpu->rom[cpu->registers.pc++];
}

void cpu_76(cpu_t *cpu) {
  cpu->halt = 1;
}

static uint8_t inc(uint8_t val) {
  return ++val; // TODO update flags register
}

