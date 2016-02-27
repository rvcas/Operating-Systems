// Lucas Rosa
// lu599305

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INPUT_FILE "processes.in"
#define OUTPUT_FILE "processes.out"

// custom string type
const int STRING_SIZE = 5;
typedef char string[STRING_SIZE];

// possible algorithms to use
// type def makes declaration easier
typedef enum a {
    fcfs, // first come first serve
    sjf, // shortest job first
    rr // round robin
} algorithms;

// represents each process
typedef struct p {
    string name;
    int arrival;
    int burst;
} process;

// represents all the info from
// the input file to execute algorithm
typedef struct c {
    int processcount;
    int runfor;
    int quantum;
    algorithms use;
    process *processes;
} control;

// rr
void round_robin() {
    FILE *out = fopen(OUTPUT_FILE,"r");

    printf("Using Round Robin\n");
}

// fcfs
void first_come_first_serve() {
    FILE *out = fopen(OUTPUT_FILE,"r");

    printf("Using First Come First Serve\n");
}

// sjf
void shortest_job_first() {
    FILE *out = fopen(OUTPUT_FILE,"r");

    printf("Using Shortest Job First\n");
}

void run(control *scheduler) {
    if (scheduler == NULL) {
        printf("scheduler not initialized\n");
        return;
    }

    switch (scheduler->use) {
        case fcfs:
            first_come_first_serve();
            break;
        case sjf:
            shortest_job_first();
            break;
        case rr:
            round_robin();
            break;
        default:
            printf("nothing happened\n");
    }
}

control *init() {
    FILE *in = fopen(INPUT_FILE, "r"); // open file

    // check if file actually opened
    if (in == NULL)
    {
        printf("file failed to open\n"); // yell
        return NULL;
    }

    control *ptr = malloc(sizeof(control));

    if (ptr == NULL) {
        printf("failed to allocate space for control struct\n");
        return NULL;
    }

    char buffer[50]; // buffer to read in strings

    // set process count
    fscanf(in, "%s %d\n", buffer, &ptr->processcount);

    // gut the comment
    fscanf(in, "%s %s %s %s\n", buffer, buffer, buffer, buffer);

    // set runfor
    fscanf(in, "%s %d\n", buffer, &ptr->runfor);

    // gut the comment
    fscanf(in, "%s %s %s %s %s %s\n", buffer, buffer, buffer, buffer, buffer, buffer);

    int quan = 0; // quantum flag

    // set use
    fscanf(in, "%s %s\n", buffer, buffer);
    if (!strcmp(buffer, "rr")) {
        ptr->use = rr;
        quan = 1;
    } else if (!strcmp(buffer, "sjf")) {
        ptr->use = sjf;
    } else if (!strcmp(buffer, "fcfs")) {
        ptr->use = fcfs;
    }

    // gutt the comment
    fscanf(in, "%s %s %s %s %s %s %s\n", buffer, buffer, buffer, buffer, buffer, buffer, buffer);

    if (quan) {
        // set quantum
        fscanf(in, "%s %d\n", buffer, &ptr->quantum);

        // gut the comment
        fscanf(in, "%s %s %s %s %s %s %s %s\n", buffer, buffer, buffer, buffer, buffer, buffer, buffer, buffer);
    } else {
        fgets(buffer, 100,in); // throwaway entire next line
    }

    ptr->processes = malloc(sizeof(process)*ptr->processcount);

    if (ptr->processes == NULL) {
        printf("failed to allocate space for processes struct array\n");
        return NULL;
    }

    for (int i = 0; i < ptr->processcount; i++) {
        // set process name
        fscanf(in, "%s %s %s\n", buffer, buffer, buffer);
        strcpy(ptr->processes[i].name, buffer);

        // set arrival
        fscanf(in, "%s %d\n", buffer, &ptr->processes[i].arrival);

        // set burst
        fscanf(in, "%s %d\n", buffer, &ptr->processes[i].burst);
    }

    fclose (in);

    return ptr;
}

void printInfo(control *scheduler) {
    printf("Process Count: %d\n", scheduler->processcount);
    printf("Run For: %d\n", scheduler->processcount);
    printf("Quantum: %d\n", scheduler->quantum);
    printf("Use: %d\n", scheduler->use);
    printf("Processes:\n");

    for (int i = 0; i < scheduler->processcount; i++) {
        printf("Name: %s Arrival: %d Burst: %d\n", scheduler->processes[i].name, scheduler->processes[i].arrival, scheduler->processes[i].burst);
    }
}

int main(int argc, char const *argv[]) {

    // initialize the data stuctures
    control *scheduler = init();

    printInfo(scheduler);

    // run one of the scheduling algorithms
    run(scheduler);

    // done
    return 0;
}
