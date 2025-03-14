#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "mylib.h"

int main(int argc, char *argv[]) {

    if (argc < 3) {
        fprintf(stderr, "Not enough arguments\n");
        return -1;
    }

    FILE* file = fopen(argv[1], "rb");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for reading\n");
        return -1;
    }

    char key[20];
    char mode[20];

    strcpy(key, argv[2]);

    processor p;

    if (!strcmp(key, "-f")) {
        while (fread(&p, sizeof(processor), 1, file) == 1) {
            printf("%s:%s:%d cores:%d threads:%.1f-%.1f GHz:%s:%d nm:%d MB:%d W\n", p.Name, p.Codename, p.Cores, p.Threads, p.minClock, p.maxClock, p.Socket, p.Process, p.L3_Cache, p.TDP);
        }
    }

    else if (!strcmp(key, "-p")) {
        strcpy(mode, argv[3]);
        if (!strcmp(mode, "first")) {
            printf("\n====  First Processor  ====\n");
            printf("\n%s (%d cores, %d threads, %.1f-%.1f GHz, L3 Cache %d MB, %d W)\n\n",
                   p.Name, p.Cores, p.Threads, p.minClock, p.maxClock, p.L3_Cache, p.TDP);
        }

        else {

            int count = 0;
            double sum_minClock = 0.0;
            double sum_maxClock = 0.0;
            double sum_Cores = 0.0;
            double sum_Threads = 0.0;

            while (fread(&p, sizeof(processor), 1, file) == 1) {

                count++;
                sum_minClock += p.minClock;
                sum_maxClock += p.maxClock;
                sum_Cores += p.Cores;
                sum_Threads += p.Threads;

            }

            double avg_minClock = sum_minClock / count;
            double avg_maxClock = sum_maxClock / count;
            double avg_Cores = sum_Cores / count;
            double avg_Threads = sum_Threads / count;

            if (!strcmp(mode, "statistics")) {

                printf("\n====    Statistics     ====\n");
                printf("\nTotal processors: %d\n", count);
                printf("Average min clock: %.2f GHz\n", avg_minClock);
                printf("Average max clock: %.2f GHz\n", avg_maxClock);
                printf("Average cores: %.2f\n", avg_Cores);
                printf("Average threads: %.2f\n\n", avg_Threads);

            }

            else if (!strcmp(mode, "target")) {

                processor target_processor;
                double target_minClock = 0.0;
                double target_maxClock = 0.0;
                int target_Cores = 0;
                int target_Threads = 0;

                int min_TDP = INT_MAX;

                rewind(file);

                while (fread(&p, sizeof(processor), 1, file) == 1) {

                    if (p.minClock < avg_minClock) continue;
                    if (p.maxClock < avg_maxClock) continue;
                    if (p.Cores < avg_Cores) continue;
                    if (p.Threads < avg_Threads) continue;
                    if (p.TDP > min_TDP) continue;

                    if (p.TDP == min_TDP) {
                        if (p.minClock < target_minClock) continue;
                        if (p.maxClock < target_maxClock) continue;
                        if (p.Cores < target_Cores) continue;
                        if (p.Threads < target_Threads) continue;
                    }

                    min_TDP = p.TDP;
                    target_processor = p;
                    target_minClock = p.minClock;
                    target_maxClock = p.maxClock;
                    target_Cores = p.Cores;
                    target_Threads = p.Threads;
                }

                if (min_TDP == INT_MAX) {
                    printf("\nNo suitable processor found.\n");
                } else {
                    printf("\n==== Target  Processor ====\n");
                    printf("\nWe were looking for a processor with:\n\tminClock\n\tmaxClock\n\tcores\n\tthreads\nabove average, ");
                    printf("and its TDP should be minimal.\n");
                    printf("This is our processor:\n%s (%d cores, %d threads, %.1f-%.1f GHz, L3 Cache %d MB, %d W)\n\n",
                           target_processor.Name, target_processor.Cores, target_processor.Threads,
                           target_processor.minClock, target_processor.maxClock, target_processor.L3_Cache, target_processor.TDP);
                }
            } else {
                fprintf(stderr, "Invalid mode: %s\n", mode);
                fclose(file);
                return -1;
            }
        }
    } else {
        fprintf(stderr, "Invalid key: %s\n", key);
        fclose(file);
        return -1;
    }

    fclose(file);
}