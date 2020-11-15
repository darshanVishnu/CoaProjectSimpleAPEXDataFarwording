/*
 * main.c
 *
 * Author:
 * Copyright (c) 2020, Gaurav Kothari (gkothar1@binghamton.edu)
 * State University of New York at Binghamton
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apex_cpu.h"

int main(int argc, char const *argv[])
{
    APEX_CPU *cpu;

    fprintf(stderr, "APEX CPU Pipeline Simulator v%0.1lf\n", VERSION);

    if (argc != 4)
    {
        fprintf(stderr, "APEX_Help: Usage %s <input_file> display/simulate function cycles\n", argv[0]);
        exit(1);
    }

    cpu = APEX_cpu_init(argv[1]);

    int cyclesnumber = strtol(argv[3], NULL, 0);
    const char *sim_dis = argv[2];
    const char *dis = "display";
    const char *sim = "simulate";
    int display = 0;
    if (strcmp(sim_dis, dis) == 0)
    {
        printf("Display is going to run %d cycles and Stop.It displays each cycle pipelines",cyclesnumber);
        display = 1;
    }
    else if (strcmp(sim_dis, sim) == 0)
    {
        printf("Simulate is going to run for --- >%d cycles and Stop\n",cyclesnumber);
        display = 0;
    }
    else
    {
        fprintf(stderr, "APEX_Help: Usage %s <input_file> display/simulate function cycles\n", argv[0]);
        exit(1);
    }

    if (!cpu)
    {
        fprintf(stderr, "APEX_Error: Unable to initialize CPU\n");
        exit(1);
    }

    APEX_cpu_run(cpu, display, cyclesnumber);
    APEX_cpu_stop(cpu);
    return 0;
}