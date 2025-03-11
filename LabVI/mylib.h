#pragma once

typedef struct {
    char Name[50];
    char Codename[50];
    int Cores;
    int Threads;
    float minClock;
    float maxClock;
    char Socket[50];
    int Process;
    int L3_Cache;
    int TDP;
} processor;