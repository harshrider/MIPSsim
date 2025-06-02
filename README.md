# MIPS Processor Simulator

A cycle-accurate MIPS processor simulator implemented in C that executes MIPS assembly instructions and maintains processor state.

## Overview

This simulator implements a subset of the MIPS instruction set architecture (ISA) and provides a virtual environment for executing MIPS assembly programs. The simulator processes instructions sequentially, updating processor state including registers, program counter, and memory.

## Features

### Supported Instruction Types
- **R-Type Instructions**: Register-to-register operations
- **I-Type Instructions**: Immediate and memory operations  
- **J-Type Instructions**: Jump operations

### Implemented Instructions

#### Arithmetic Operations
- `ADD`, `ADDU` - Addition (signed/unsigned)
- `SUB`, `SUBU` - Subtraction (signed/unsigned)
- `ADDI`, `ADDIU` - Add immediate (signed/unsigned)

#### Logical Operations
- `AND`, `OR`, `XOR`, `NOR` - Bitwise operations
- `ANDI`, `ORI`, `XORI` - Bitwise operations with immediate

#### Shift Operations
- `SLL`, `SRL`, `SRA` - Shift left/right logical/arithmetic
- `SLLV`, `SRLV`, `SRAV` - Variable shift operations

#### Multiplication and Division
- `MULT`, `MULTU` - Multiplication (signed/unsigned)
- `DIV`, `DIVU` - Division (signed/unsigned)
- `MFHI`, `MTHI` - Move from/to HI register
- `MFLO`, `MTLO` - Move from/to LO register

#### Comparison Operations
- `SLT`, `SLTU` - Set on less than (signed/unsigned)
- `SLTI`, `SLTIU` - Set on less than immediate (signed/unsigned)

#### Branch Instructions
- `BEQ`, `BNE` - Branch on equal/not equal
- `BLEZ`, `BGTZ` - Branch on less/greater than zero
- `BLTZ`, `BGEZ` - Branch on less/greater than or equal to zero
- `BLTZAL`, `BGEZAL` - Branch and link variants

#### Jump Instructions
- `J` - Jump to address
- `JAL` - Jump and link
- `JR` - Jump register
- `JALR` - Jump and link register

#### Memory Operations
- `LW`, `SW` - Load/store word (32-bit)
- `LH`, `LHU`, `SH` - Load/store halfword (16-bit, signed/unsigned)
- `LB`, `LBU`, `SB` - Load/store byte (8-bit, signed/unsigned)
- `LUI` - Load upper immediate

#### System Operations
- `SYSCALL` - System call interface

## Architecture Details

### Processor State
The simulator maintains the following processor state:
- **32 General Purpose Registers** (`$0-$31`)
- **Program Counter (PC)** - Current instruction address
- **HI/LO Registers** - For multiplication/division results
- **Memory System** - Instruction and data memory

### State Management
The simulator uses a dual-state system:
- `CURRENT_STATE` - Current processor state
- `NEXT_STATE` - State after instruction execution

This approach ensures proper timing simulation and prevents race conditions.

## Usage

### Prerequisites
- GCC or compatible C compiler
- Custom `shell.h` header file (contains processor state definitions and memory functions)

### Compilation
```bash
gcc -o mips_sim sim.c [additional_files.c] -I[include_directory]
```

### Running
The simulator expects the processor state and memory to be initialized through the shell interface. The main execution function is:

```c
void process_instruction();
```

### System Calls
The simulator supports basic system calls through the `SYSCALL` instruction:
- **Code 4**: Print integer (value in `$a0`/`$4`)
- **Code 10**: Exit program

## Code Structure

### Key Components
- **Opcode Enums**: Define instruction opcodes and function codes
- **Instruction Decoder**: Extracts instruction fields (opcode, registers, immediate values)
- **Execution Engine**: Implements instruction semantics
- **State Update**: Manages processor state transitions

### Memory Interface
The simulator interfaces with memory through external functions:
- `mem_read_32(address)` - Read 32-bit word from memory
- `mem_write_32(address, data)` - Write 32-bit word to memory

## Debugging Features

The simulator includes extensive debugging output that prints:
- Instruction being executed
- Register values and operations
- Memory addresses and data
- Branch/jump target addresses

To disable debug output, remove or comment out the `printf` statements.

## Example Usage

```c
// Initialize processor state
CURRENT_STATE.PC = 0x00400000;  // Starting address
CURRENT_STATE.REGS[0] = 0;      // $zero always 0

// Execute instructions
while (RUN_BIT) {
    process_instruction();
    // Copy NEXT_STATE to CURRENT_STATE
    CURRENT_STATE = NEXT_STATE;
}
```

## Limitations

- Limited instruction set (subset of full MIPS ISA)
- No pipeline simulation
- No cache simulation
- No floating-point unit
- Basic syscall interface

## Contributing

To add new instructions:
1. Add opcode/function code to the appropriate enum
2. Implement instruction logic in the switch statement
3. Handle register decoding and state updates
4. Add appropriate debug output

## Development

This MIPS processor simulator was built from scratch as a learning exercise, with guidance from **"Computer Organization and Design: The Hardware/Software Interface"** by David A. Patterson and John L. Hennessy. This classic textbook provided the theoretical foundation and detailed explanations of MIPS architecture that made this implementation possible.

The simulator demonstrates practical application of computer architecture concepts including instruction encoding, processor state management, and the fetch-decode-execute cycle as described in the Patterson-Hennessy text.

## Technical Notes

### Sign Extension
The simulator properly handles sign extension for:
- Immediate values in I-type instructions
- Branch offsets
- Memory address calculations

### Jump Address Calculation
- **J/JAL**: Combines PC upper bits with instruction target
- **JR/JALR**: Uses register value directly
- **Branches**: PC-relative with sign-extended offset

### Memory Alignment
The simulator assumes word-aligned memory access for 32-bit operations. Byte and halfword operations extract appropriate portions of 32-bit memory words.
