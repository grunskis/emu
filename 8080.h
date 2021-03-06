#ifndef I8080_H
#define I8080_H

#include <stdint.h>
#include <stdlib.h>

// value of from "9th bit"
#define FLAG_CARRY (1 << 0)

// value from bit 7
#define FLAG_SIGN  (1 << 1)

// flag = accumulator == 0
#define FLAG_ZERO  (1 << 2)

// flag = accumulator == even ? 1 : 0
#define FLAG_PARITY (1 << 3)

#define FLAG_AUX_CARRY (1 << 4)

struct registers {
  uint8_t a; // 8-bit accumulator

  // 8-bit registers
  uint8_t b, c, d, e, h, l;

  // flag register
  uint8_t f;
  
  uint16_t pc; // program counter
};

struct cpu {
  struct registers registers;

  // TODO externalize ROM
  uint8_t rom[0x1fff]; // 8k ROM

  uint8_t halt; // TODO use bit instead of byte
  
  uint16_t cycles;
};

typedef struct cpu cpu_t;

cpu_t *cpu_init();
void cpu_reset(cpu_t *);
void cpu_execute(cpu_t *);

uint8_t cpu_halted(cpu_t *);

void cpu_load_program(cpu_t *, uint8_t *, size_t);

void cpu_00(cpu_t *);
void cpu_04(cpu_t *);
void cpu_06(cpu_t *);
void cpu_76(cpu_t *);

struct instruction_set {
  uint8_t instruction;
  uint8_t cycles;
  void (*handler)(cpu_t *);
};

#endif
