/*
 * apex_cpu.h
 * Contains APEX cpu pipeline declarations
 *
 * Author:
 * Copyright (c) 2020, Gaurav Kothari (gkothar1@binghamton.edu)
 * State University of New York at Binghamton
 */
#ifndef _APEX_CPU_H_
#define _APEX_CPU_H_

#include "apex_macros.h"

/* Format of an APEX instruction  */
typedef struct APEX_Instruction
{
    char opcode_str[128];
    int opcode;
    int rd;
    int rs1;
    int rs2;
    int rs3; // usedfor store
    int imm;
} APEX_Instruction;

/* Model of CPU stage latch */
typedef struct CPU_Stage
{
    int pc;
    char opcode_str[128];
    int opcode;
    int rs1;
    int rs2;
    int rs3; // Source-3 Register Address for STR instructions
    int rd;
    int imm;
    int rs1_value;
    int rs2_value;
    int rs3_value; // Source-3 Register Value for STR instructions
    int result_buffer;
    int memory_address;
    int has_insn;
    int stalled; // Flag  stage is stalled
} CPU_Stage;

/* Model of APEX CPU */
typedef struct APEX_CPU
{
    int pc;                              /* Current program counter */
    int clock;                           /* Clock cycles elapsed */
    int insn_completed;                  /* Instructions retired */
    int regs[REG_FILE_SIZE];             /* Integer register file */
    int regs_valid_check[REG_FILE_SIZE]; /* Integer register file to check register valid*/
    int code_memory_size;                /* Number of instruction in the input file */
    APEX_Instruction *code_memory;       /* Code Memory */
    int data_memory[DATA_MEMORY_SIZE];   /* Data Memory */
    int single_step;                     /* Wait for user input after every cycle */
    int zero_flag;                       /* {TRUE, FALSE} Used by BZ and BNZ to branch */
    int fetch_from_next_cycle;

    /* Pipeline stages */
    CPU_Stage fetch;
    CPU_Stage decode;
    CPU_Stage execute;
    CPU_Stage memory;
    CPU_Stage writeback;


    int dataForwardingLines[3]; //0 execute 1memory 
    int dataForwardingLinesdata[3];             //One each for 0-EX, 1-MEM 

} APEX_CPU;

APEX_Instruction *create_code_memory(const char *filename, int *size);
APEX_CPU *APEX_cpu_init(const char *filename);
void APEX_cpu_run(APEX_CPU *cpu, int dispalyIn, int cyclesnumberIn);
void APEX_cpu_stop(APEX_CPU *cpu);
void printdatamemory(APEX_CPU *cpu);
void printregstate(APEX_CPU *cpu);

#endif
