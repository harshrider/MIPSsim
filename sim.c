#include <stdio.h>
#include "shell.h"

enum Opcodes {
	
	BLTZ = 0,
    BGEZ = 1,
    BLTZAL = 16,
    BGEZAL = 17,
	
    J = 2,
    JAL = 3,
    BEQ = 4,
    BNE = 5,
    BLEZ = 6,
    BGTZ = 7,
    ADDI = 8,
    ADDIU = 9,
    SLTI = 10,
    SLTIU = 11,
    ANDI = 12,
    ORI = 13,
    XORI = 14,
    LUI = 15,
	
    LB = 32,
    LH = 33,
    LW = 35,
    LBU = 36,
    LHU = 37,
    SB = 40,
    SH = 41,
    SW = 43,
	
};

enum Functions {
	
    SLL = 0,
    SRL = 2,
    SRA = 3,
    SLLV = 4,
    SRLV = 6,
    SRAV = 7,
    JR = 8,
    JALR = 9,
	
	MFHI = 16,
	MTHI = 17,
    MFLO = 18,
    MTLO = 19,
	MULT = 24,
    MULTU = 25,
    DIV = 26,
    DIVU = 27,
	
    ADD = 32,
    ADDU = 33,
    SUB = 34,
    SUBU = 35,
    AND = 36,
    OR = 37,
    XOR = 38,
    NOR = 39,
    SLT = 42,
    SLTU = 43,
	
    SYSCALL = 12
};

void process_instruction() {
    uint32_t instruction = mem_read_32(CURRENT_STATE.PC);
    uint32_t opcode = instruction >> 26;
	int jumped = 0;
	
    switch (opcode) {
        case 0: { //R format
            uint32_t function = instruction & 0x3F;
            
			switch (function) {
                
				
				case SYSCALL: {
					printf("SYSCALL case: %d\n", CURRENT_STATE.REGS[2]);
                    switch (CURRENT_STATE.REGS[2]) {
						
                        case 4://Print
						printf("prints %d \n", CURRENT_STATE.REGS[4]);
						break;
                        case 10://Exit
						printf(" Exiting \n");
						RUN_BIT = FALSE;
						break;
                        default:
						printf("Case: %d\n", CURRENT_STATE.REGS[2]);
						break;
					}
                    break;
				}
				
				
		        case ADDU: {
					printf("Adding using ADDU \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					uint32_t rt = (instruction >> 16) & 0x1F;
					uint32_t rd = (instruction >> 11) & 0x1F;
					NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
					break;
				}
				
				
				case SLL: {
					printf("Shifting left using SLL \n");
					uint32_t rt = (instruction >> 16) & 0x1F;  // Source register
					uint32_t rd = (instruction >> 11) & 0x1F;  // Destination register
					uint32_t sa = (instruction >> 6) & 0x1F;   // Shift amount
					
					// Perform the shift left logical 
					NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << sa;
					break;
				}
				
				case SUBU: {
					printf("Subtracting using SUBU \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					uint32_t rt = (instruction >> 16) & 0x1F;
					uint32_t rd = (instruction >> 11) & 0x1F;
					NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
					break;
				}
				
				case XOR: {
					printf("using XOR  \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					uint32_t rt = (instruction >> 16) & 0x1F;
					uint32_t rd = (instruction >> 11) & 0x1F;
					NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] ^ CURRENT_STATE.REGS[rt];
					break;
				}
				
				case SRL: {
					printf("using SRL  \n");
					uint32_t rt = (instruction >> 16) & 0x1F;
					uint32_t rd = (instruction >> 11) & 0x1F;
					uint32_t sa = (instruction >> 6) & 0x1F;
					NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> sa;
					break;
				}
				
				case SRA: {
					printf("using SRA  \n");
					uint32_t rt = (instruction >> 16) & 0x1F;
					uint32_t rd = (instruction >> 11) & 0x1F;
					uint32_t sa = (instruction >> 6) & 0x1F;
					int32_t value = (int32_t) CURRENT_STATE.REGS[rt];  // Cast to signed int to preserve sign during shift
					NEXT_STATE.REGS[rd] = value >> sa;
					break;
				}
				
				case AND: {
					printf("using AND  \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					uint32_t rt = (instruction >> 16) & 0x1F;
					uint32_t rd = (instruction >> 11) & 0x1F;
					NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] & CURRENT_STATE.REGS[rt];
					break;
				}
				
				case SUB: {
					printf("Subtracting using SUB \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					uint32_t rt = (instruction >> 16) & 0x1F;
					uint32_t rd = (instruction >> 11) & 0x1F;
					NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] - CURRENT_STATE.REGS[rt];
					break;
				}
				
				case ADD: {
					printf("Adding using ADD \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					uint32_t rt = (instruction >> 16) & 0x1F;
					uint32_t rd = (instruction >> 11) & 0x1F;
					NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] + CURRENT_STATE.REGS[rt];
					break;
				}
				
				// Need to Test These Functions
				case MFHI: {
					printf("Moving from HI using MFHI \n");
					uint32_t rd = (instruction >> 11) & 0x1F;
					NEXT_STATE.REGS[rd] = CURRENT_STATE.HI;
					break;
				}
				
				case MTHI: {
					printf("Moving to HI using MTHI \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					NEXT_STATE.HI = CURRENT_STATE.REGS[rs];
					break;
				}
				
				case MFLO: {
					printf("Moving from LO using MFLO \n");
					uint32_t rd = (instruction >> 11) & 0x1F;
					NEXT_STATE.REGS[rd] = CURRENT_STATE.LO;
					break;
				}
				
				case MTLO: {
					printf("Moving to LO using MTLO \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					NEXT_STATE.LO = CURRENT_STATE.REGS[rs];
					break;
				}
				
				case MULT: {
					printf("Multiplying using MULT \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					uint32_t rt = (instruction >> 16) & 0x1F;
					int64_t result = (int64_t)CURRENT_STATE.REGS[rs] * (int64_t)CURRENT_STATE.REGS[rt];
					NEXT_STATE.LO = result & 0xFFFFFFFF;
					NEXT_STATE.HI = result >> 32;
					break;
				}
				
				case MULTU: {
					printf("Multiplying unsigned using MULTU \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					uint32_t rt = (instruction >> 16) & 0x1F;
					uint64_t result = (uint64_t)CURRENT_STATE.REGS[rs] * (uint64_t)CURRENT_STATE.REGS[rt];
					NEXT_STATE.LO = result & 0xFFFFFFFF;
					NEXT_STATE.HI = result >> 32;
					break;
				}
				
				case DIV: {
					printf("Dividing using DIV \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					uint32_t rt = (instruction >> 16) & 0x1F;
					if (CURRENT_STATE.REGS[rt] != 0) {
						NEXT_STATE.LO = CURRENT_STATE.REGS[rs] / CURRENT_STATE.REGS[rt];
						NEXT_STATE.HI = CURRENT_STATE.REGS[rs] % CURRENT_STATE.REGS[rt];
					}
					break;
				}
				
				case DIVU: {
					printf("Dividing unsigned using DIVU \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					uint32_t rt = (instruction >> 16) & 0x1F;
					if (CURRENT_STATE.REGS[rt] != 0) {
						NEXT_STATE.LO = CURRENT_STATE.REGS[rs] / CURRENT_STATE.REGS[rt];
						NEXT_STATE.HI = CURRENT_STATE.REGS[rs] % CURRENT_STATE.REGS[rt];
					}
					break;
				}
				
				case OR: {
					printf("Performing bitwise OR \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					uint32_t rt = (instruction >> 16) & 0x1F;
					uint32_t rd = (instruction >> 11) & 0x1F;
					NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt];
					break;
				}
				
				case NOR: {
					printf("Performing bitwise NOR \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					uint32_t rt = (instruction >> 16) & 0x1F;
					uint32_t rd = (instruction >> 11) & 0x1F;
					NEXT_STATE.REGS[rd] = ~(CURRENT_STATE.REGS[rs] | CURRENT_STATE.REGS[rt]);
					break;
				}
				
				case JR: {
					printf("Jumping to address in register using JR \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					// Perform the jump
					printf("Jumping to address 0x%08X\n", CURRENT_STATE.REGS[rs]);
					NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
					jumped = 1;
					break;
				}
				
				
				case JALR: {
					printf("Jumping and linking to address in register using JALR \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					// Store return address in register 31
					NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
					// Perform the jump
					NEXT_STATE.PC = CURRENT_STATE.REGS[rs];
					jumped = 1;
					break;
				}
				//Need to test the function
				case SLLV: {
					printf("Shift left logical variable using SLLV \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					uint32_t rt = (instruction >> 16) & 0x1F;
					uint32_t rd = (instruction >> 11) & 0x1F;
					
					// Perform the shift operation and store the result in the destination register
					NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] << (CURRENT_STATE.REGS[rs] & 0x1F);
					break;
				}
				
				case SRLV: {
					printf("Shift right logical variable using SRLV \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					uint32_t rt = (instruction >> 16) & 0x1F;
					uint32_t rd = (instruction >> 11) & 0x1F;
					
					// Perform the shift operation and store the result in the destination register
					NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rt] >> (CURRENT_STATE.REGS[rs] & 0x1F);
					break;
				}
				
				case SLT: {
					printf("Set on less than using SLT \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					uint32_t rt = (instruction >> 16) & 0x1F;
					uint32_t rd = (instruction >> 11) & 0x1F;
					
					// Perform the comparison and set the destination register
					if ((int32_t)CURRENT_STATE.REGS[rs] < (int32_t)CURRENT_STATE.REGS[rt]) {
						NEXT_STATE.REGS[rd] = 1;
						} else {
						NEXT_STATE.REGS[rd] = 0;
					}
					break;
				}
				
				case SLTU: {
					printf("Set on less than unsigned using SLTU \n");
					uint32_t rs = (instruction >> 21) & 0x1F;
					uint32_t rt = (instruction >> 16) & 0x1F;
					uint32_t rd = (instruction >> 11) & 0x1F;
					
					// Perform the comparison and set the destination register
					if (CURRENT_STATE.REGS[rs] < CURRENT_STATE.REGS[rt]) {
						NEXT_STATE.REGS[rd] = 1;
						} else {
						NEXT_STATE.REGS[rd] = 0;
					}
					break;
				}
				
				
				
				
				
				
				
				
				
                default://Should never pop up, Mainly for debuging and finding out what to implement next
				printf("Function %d \n", function);
				//RUN_BIT = FALSE;
				break;
			}
            break;
		}
		
		case 1: { // This is the opcode for all four functions
			uint32_t rs = (instruction >> 21) & 0x1F;
			uint32_t rt = (instruction >> 16) & 0x1F;
			int32_t offset = (int32_t)(int16_t)(instruction & 0xFFFF);  // Sign-extended
			switch (rt) {
				case 0: { // BLTZ
					printf("Branching if less than zero using BLTZ \n");
					if ((int32_t)CURRENT_STATE.REGS[rs] < 0) {
						NEXT_STATE.PC = CURRENT_STATE.PC + (offset << 2);
						jumped = 1;
					}
					break;
				}
				case 1: { // BGEZ
					printf("Branching if greater than or equal to zero using BGEZ \n");
					if ((int32_t)CURRENT_STATE.REGS[rs] >= 0) {
						NEXT_STATE.PC = CURRENT_STATE.PC + (offset << 2);
						jumped = 1;
					}
					break;
				}
				case 16: { // BLTZAL
					printf("Branching if less than zero and linking using BLTZAL \n");
					if ((int32_t)CURRENT_STATE.REGS[rs] < 0) {
						NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
						NEXT_STATE.PC = CURRENT_STATE.PC + (offset << 2);
						jumped = 1;
					}
					break;
				}
				case 17: { // BGEZAL
					printf("Branching if greater than or equal to zero and linking using BGEZAL \n");
					if ((int32_t)CURRENT_STATE.REGS[rs] >= 0) {
						NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
						NEXT_STATE.PC = CURRENT_STATE.PC + (offset << 2);
						jumped = 1;
					}
					break;
				}
				default:
				printf("Unknown function with opcode 1: %d\n", rt);
				//RUN_BIT = FALSE;
				break;
			}
			break;
		}
		
		
		
		
		
		
		
		
		case ADDIU: {
			printf("Adding using ADDIU \n");
			uint32_t rs = (instruction >> 21) & 0x1F;
			uint32_t rt = (instruction >> 16) & 0x1F;
			uint16_t immediate = instruction & 0xFFFF;
			int32_t sign_extended_immediate = (int32_t)(int16_t)immediate; // Sign extend
			NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + sign_extended_immediate;  // addition is modulo 2^32
			break;
		}
		
		case ORI: {
			printf("using ORI \n");
			uint32_t rs = (instruction >> 21) & 0x1F;
			uint32_t rd = (instruction >> 16) & 0x1F;
			uint32_t immediate = instruction & 0xFFFF; 
			NEXT_STATE.REGS[rd] = CURRENT_STATE.REGS[rs] | immediate;
			break;
		}
		
		case LUI: {
			printf("using LUI \n");
			uint32_t rd = (instruction >> 16) & 0x1F;
			uint32_t immediate = instruction & 0xFFFF;  
			NEXT_STATE.REGS[rd] = immediate << 16;
			break;
		}
		
		case ADDI: {
			printf("Adding immediate using ADDI \n");
			uint32_t rs = (instruction >> 21) & 0x1F;
			uint32_t rt = (instruction >> 16) & 0x1F;  
			int32_t immediate = (int32_t)(int16_t)(instruction & 0xFFFF);  // Sign-extended
			NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] + immediate;
			break;
		}
		
		case XORI: {
			printf("using XORI  \n");
			uint32_t rs = (instruction >> 21) & 0x1F;
			uint32_t rt = (instruction >> 16) & 0x1F;
			uint32_t immediate = instruction & 0xFFFF; 
			NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] ^ immediate;
			break;
		}
		
		case ANDI: {
			printf("using ANDI  \n");
			uint32_t rs = (instruction >> 21) & 0x1F;
			uint32_t rt = (instruction >> 16) & 0x1F;
			uint32_t immediate = instruction & 0xFFFF;  
			NEXT_STATE.REGS[rt] = CURRENT_STATE.REGS[rs] & immediate;
			break;
		}
		
		
		case J: {
			printf("Jumping to ");
			uint32_t target = instruction & 0x03FFFFFF;  // Extract the target field (bits 0-25)
			printf("Before sign extension: 0x%08X\n", target);
			// Form the actual target address
			uint32_t jumpAddress = (CURRENT_STATE.PC & 0xF0000000) | (target << 2);
			printf("Jump address: 0x%08X\n", jumpAddress);
			// Perform the jump
			NEXT_STATE.PC = jumpAddress;
			printf("address 0x%08X\n", jumpAddress);
			jumped = 1;
			break;
		}
		
		
		
		case JAL: {
			printf("Jumping and linking to ");
			uint32_t target = instruction & 0x03FFFFFF;  // Extract the target field (bits 0-25)
			
			printf("Before sign extension: 0x%08X\n", target);
			
			// Cast to a signed integer and perform the sign extension
			int32_t signExtendedTarget = ((int32_t)(target << 2)) >> 2;
			
			printf("After sign extension: 0x%08X\n\n\n", signExtendedTarget);
			
			// Form the actual target address
			uint32_t jumpAddress = (CURRENT_STATE.PC & 0xF0000000) | (signExtendedTarget << 2);
			
			printf("Jump address: 0x%08X\n", jumpAddress);
			
			// Store in 31
			NEXT_STATE.REGS[31] = CURRENT_STATE.PC + 4;
			
			// Perform the jump
			NEXT_STATE.PC = jumpAddress;
			printf("address 0x%08X\n", jumpAddress);
			jumped = 1;
			break;
		}
		
		
		
		
		
		case BNE: {
			printf("Branching using BNE \n");
			uint32_t rs = (instruction >> 21) & 0x1F;
			uint32_t rt = (instruction >> 16) & 0x1F;
			uint16_t offset = instruction & 0xFFFF;  // Extract the immediate value
			int32_t signExtendedOffset = (int32_t)(int16_t)offset;  // Sign-extend the immediate value
			
			if (CURRENT_STATE.REGS[rs] != CURRENT_STATE.REGS[rt]) {
				NEXT_STATE.PC = CURRENT_STATE.PC + (signExtendedOffset << 2);
				jumped = 1;
			}
			break;
		}
		
		case BEQ: {
			printf("Branching using BEQ \n");
			uint32_t rs = (instruction >> 21) & 0x1F;
			uint32_t rt = (instruction >> 16) & 0x1F;
			uint16_t offset = instruction & 0xFFFF;  // Extract the immediate value
			int32_t signExtendedOffset = (int32_t)(int16_t)offset;  // Sign-extend the immediate value
			
			if (CURRENT_STATE.REGS[rs] == CURRENT_STATE.REGS[rt]) {
				NEXT_STATE.PC = CURRENT_STATE.PC + (signExtendedOffset << 2);
				jumped = 1;
			}
			
			break;
		}
		
		case BLEZ: {
			printf("Branching using BLEZ \n");
			uint32_t rs = (instruction >> 21) & 0x1F;
			uint16_t offset = instruction & 0xFFFF;  // Extract the immediate value
			int32_t signExtendedOffset = (int32_t)(int16_t)offset;  // Sign-extend the immediate value
			
			if ((int32_t)CURRENT_STATE.REGS[rs] <= 0) {
				NEXT_STATE.PC = CURRENT_STATE.PC + (signExtendedOffset << 2);
				jumped = 1;
			}
			break;
		}
		
		case BGTZ: {
			printf("Branching if greater than or equal to zero using BGTZ \n");
			uint32_t rs = (instruction >> 21) & 0x1F;
			uint16_t offset = instruction & 0xFFFF;  // Extract the immediate value
			int32_t signExtendedOffset = (int32_t)(int16_t)offset;  // Sign-extend the immediate value
			
			if (CURRENT_STATE.REGS[rs] > 0) {
				NEXT_STATE.PC = CURRENT_STATE.PC + (signExtendedOffset << 2);
				jumped = 1;
			}
			break;
		}
		
		
		case SW: {
			printf("Storing word using SW \n");
			uint32_t base = (instruction >> 21) & 0x1F;  // Base register
			uint32_t rt = (instruction >> 16) & 0x1F;  // Source register
			uint16_t offset = instruction & 0xFFFF;  // Extract the immediate value
			int32_t signExtendedOffset = (int32_t)(int16_t)offset;  // Sign-extend the immediate value
			
			// Calculate the memory address
			uint32_t address = CURRENT_STATE.REGS[base] + signExtendedOffset;
			
			// Store the word from the source register to memory
			mem_write_32(address, CURRENT_STATE.REGS[rt]);
			
			break;
		}
		
		case LW: {
			printf("Loading word using LW \n");
			uint32_t base = (instruction >> 21) & 0x1F;  // Base register
			uint32_t rt = (instruction >> 16) & 0x1F;  // Destination register
			uint16_t offset = instruction & 0xFFFF;  // Extract the immediate value
			int32_t signExtendedOffset = (int32_t)(int16_t)offset;  // Sign-extend the immediate value
			
			// Calculate the memory address
			uint32_t address = CURRENT_STATE.REGS[base] + signExtendedOffset;
			
			// Load the word from memory and store it in the destination register
			NEXT_STATE.REGS[rt] = mem_read_32(address);
			
			break;
		}
		
		case SB: {
			printf("Storing byte using SB \n");
			uint32_t base = (instruction >> 21) & 0x1F;  // Base register
			uint32_t rt = (instruction >> 16) & 0x1F;  // Source register
			uint16_t offset = instruction & 0xFFFF;  // Extract the immediate value
			int32_t signExtendedOffset = (int32_t)(int16_t)offset;  // Sign-extend the immediate value
			
			// Calculate the memory address
			uint32_t address = CURRENT_STATE.REGS[base] + signExtendedOffset;
			
			// Store the byte from the source register to memory
			uint8_t byte = CURRENT_STATE.REGS[rt] & 0xFF;  // Extract the least significant byte
			mem_write_32(address, byte);  // Note: You might need to modify this line if your memory system doesn't support byte-level writes
			
			break;
		}
		
		
		case LBU: {
			printf("Loading byte unsigned using LBU \n");
			uint32_t base = (instruction >> 21) & 0x1F;  // Base register
			uint32_t rt = (instruction >> 16) & 0x1F;  // Destination register
			uint16_t offset = instruction & 0xFFFF;  // Extract the immediate value
			int32_t signExtendedOffset = (int32_t)(int16_t)offset;  // Sign-extend the immediate value
			
			// Calculate the memory address
			uint32_t address = CURRENT_STATE.REGS[base] + signExtendedOffset;
			
			// Load the byte from memory, zero-extend it to 32 bits, and store it in the destination register
			uint8_t byte = mem_read_32(address) & 0xFF;  // Load the byte and zero-extend it
			NEXT_STATE.REGS[rt] = byte;
			
			break;
		}
		
		
		case LB: {
			printf("Loading byte using LB \n");
			uint32_t base = (instruction >> 21) & 0x1F;  // Base register
			uint32_t rt = (instruction >> 16) & 0x1F;  // Destination register
			uint16_t offset = instruction & 0xFFFF;  // Extract the immediate value
			int32_t signExtendedOffset = (int32_t)(int16_t)offset;  // Sign-extend the immediate value
			
			// Calculate the memory address
			uint32_t address = CURRENT_STATE.REGS[base] + signExtendedOffset;
			
			// Load the byte from memory, sign-extend it to 32 bits, and store it in the destination register
			int8_t byte = mem_read_32(address) & 0xFF;  // Load the byte and sign-extend it
			NEXT_STATE.REGS[rt] = (int32_t)byte;
			
			break;
		}
		
		case SH: {
			printf("Storing halfword using SH \n");
			uint32_t base = (instruction >> 21) & 0x1F;  // Base register
			uint32_t rt = (instruction >> 16) & 0x1F;  // Source register
			uint16_t offset = instruction & 0xFFFF;  // Extract the immediate value
			int32_t signExtendedOffset = (int32_t)(int16_t)offset;  // Sign-extend the immediate value
			
			// Calculate the memory address
			uint32_t address = CURRENT_STATE.REGS[base] + signExtendedOffset;
			
			// Store the halfword from the source register to memory
			uint16_t halfword = CURRENT_STATE.REGS[rt] & 0xFFFF;  // Extract the least significant halfword
			mem_write_32(address, halfword);  // Note: You might need to modify this line if your memory system doesn't support halfword-level writes
			
			break;
		}
		
		case LH: {
			printf("Loading halfword using LH \n");
			uint32_t base = (instruction >> 21) & 0x1F;  // Base register
			uint32_t rt = (instruction >> 16) & 0x1F;  // Destination register
			uint16_t offset = instruction & 0xFFFF;  // Extract the immediate value
			int32_t signExtendedOffset = (int32_t)(int16_t)offset;  // Sign-extend the immediate value
			
			// Calculate the memory address
			uint32_t address = CURRENT_STATE.REGS[base] + signExtendedOffset;
			
			// Load the halfword from memory, sign-extend it to 32 bits, and store it in the destination register
			int16_t halfword = mem_read_32(address) & 0xFFFF;  // Load the halfword and sign-extend it
			NEXT_STATE.REGS[rt] = (int32_t)halfword;
			
			break;
		}
		
		case LHU: {
			printf("Loading halfword unsigned using LHU \n");
			uint32_t base = (instruction >> 21) & 0x1F;  // Base register
			uint32_t rt = (instruction >> 16) & 0x1F;  // Destination register
			uint16_t offset = instruction & 0xFFFF;  // Extract the immediate value
			int32_t signExtendedOffset = (int32_t)(int16_t)offset;  // Sign-extend the immediate value
			
			// Calculate the memory address
			uint32_t address = CURRENT_STATE.REGS[base] + signExtendedOffset;
			
			// Load the halfword from memory, zero-extend it to 32 bits, and store it in the destination register
			uint16_t halfword = mem_read_32(address) & 0xFFFF;  // Load the halfword and zero-extend it
			NEXT_STATE.REGS[rt] = halfword;
			
			break;
		}
		
		case SLTI: {
			printf("Setting on less than immediate using SLTI \n");
			uint32_t rs = (instruction >> 21) & 0x1F;
			uint32_t rt = (instruction >> 16) & 0x1F;
			uint16_t immediate = instruction & 0xFFFF;  // Extract the immediate value
			int32_t signExtendedImmediate = (int32_t)(int16_t)immediate;  // Sign-extend the immediate value
			
			// Perform the comparison and set the destination register
			if ((int32_t)CURRENT_STATE.REGS[rs] < signExtendedImmediate) 
			{
				NEXT_STATE.REGS[rt] = 1;
				} else {
				NEXT_STATE.REGS[rt] = 0;
			}
			break;
		}
		
		case SLTIU: {
			printf("Setting on less than immediate unsigned using SLTIU \n");
			uint32_t rs = (instruction >> 21) & 0x1F;
			uint32_t rt = (instruction >> 16) & 0x1F;
			uint16_t immediate = instruction & 0xFFFF;  // Zero-extend the immediate value
			
			// Perform the comparison and set the destination register
			if (CURRENT_STATE.REGS[rs] < immediate) 
			{
				NEXT_STATE.REGS[rt] = 1;
				} else {
				NEXT_STATE.REGS[rt] = 0;
			}
			break;
		}
		
		
		
        default:
			printf("OPCODE %d \n", opcode);
			//RUN_BIT = FALSE;
			break;
	}
	if(!jumped) 
	{
		
		NEXT_STATE.PC = CURRENT_STATE.PC + 4;
	}
	else
	{
		jumped = 0;
	}
	
}
