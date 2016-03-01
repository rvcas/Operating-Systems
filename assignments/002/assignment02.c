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
    int wait;
    int turnaround;
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
void round_robin(control *scheduler) {
    printf("%d processes\n", scheduler->processcount);
    printf("Using Round Robin\n");
    printf("Quantum %d\n\n", scheduler->quantum);

    FILE *out = fopen(OUTPUT_FILE,"r");

    if (out == NULL) {
        printf("output file failed to open\n"); // yell
        return;
    }

    int remaining_burst[scheduler->processcount];

    for (int i = 0; i < scheduler->processcount; i++) {
        remaining_burst[i] = scheduler->processes[i].burst;
        scheduler->processes[i].wait = 0;
        scheduler->processes[i].turnaround = 0;
    }

    int flag = 0;
    int time = 0, count = 0, remain = scheduler->processcount;
    while (remain != 0) {
        if (remaining_burst[count] <= scheduler->quantum && remaining_burst[count] > 0) {
            time += remaining_burst[count];
            remaining_burst[count] = 0;
            flag = 1;
        } else if (remaining_burst[count] > 0) {
            remaining_burst[count] -= scheduler->quantum;
            time += scheduler->quantum;
        }

        if (remaining_burst[count] == 0 && flag == 1) {
            remain--;
            printf("%s %d %d\n", scheduler->processes[count].name, (time - scheduler->processes[count].arrival), (time - scheduler->processes[count].arrival - scheduler->processes[count].burst));
            scheduler->processes[count].wait += scheduler->processes[count].burst - scheduler->processes[count].arrival;
            scheduler->processes[count].turnaround += time - scheduler->processes[count].arrival;
            flag = 0;
        }

        if (count == (scheduler->processcount - 1)) {
            count = 0;
        } else if (scheduler->processes[count+1].arrival <= time) {
            count++;
        } else {
            count = 0;
        }
    }

    // print process info
    for (int i = 0; i < scheduler->processcount; i++) {
        printf("%s wait %d turnaround %d\n", scheduler->processes[i].name,   scheduler->processes[i].wait, scheduler->processes[i].turnaround);
    }
}

// fcfs
void first_come_first_serve(control *scheduler) {
    printf("%d processes\n", scheduler->processcount);
    printf("Using First Come First Serve\n\n");

    FILE *out = fopen(OUTPUT_FILE,"w");

    if (out == NULL) {
        printf("output file failed to open\n"); // yell
        return;
    }

    // wait for first is 0
    scheduler->processes[0].wait = 0;

    // calc wait time
    for (int i = 0; i < scheduler->processcount; i++) {
        scheduler->processes[i].wait = 0;

        if (i > 0) {
            for (int j = 0; j < i; j++) {
                scheduler->processes[i].wait += scheduler->processes[j].burst;
            }

            scheduler->processes[i].wait -= scheduler->processes[i].arrival;
        }

        scheduler->processes[i].turnaround = scheduler->processes[i].burst + scheduler->processes[i].wait;
    }

    // keeps track time for next burst
    int next_burst = 0;

    // run for
    for (int i = 0; i <= scheduler->runfor; i++) {
        // check if any processes arrived
        for (int j = 0; j < scheduler->processcount; j++) {
            // arrived
            if (scheduler->processes[j].arrival == i) {
                printf("Time %d: %s arrived\n", i, scheduler->processes[j].name);
            }

            // finished
            if ((scheduler->processes[j].turnaround + scheduler->processes[j].arrival) == i) {
                printf("Time %d: %s finished\n", i, scheduler->processes[j].name);
            }

            // select
            if ((scheduler->processes[j].wait + scheduler->processes[j].arrival) == i) {
                printf("Time %d: %s selected (burst %d)\n", i, scheduler->processes[j].name, scheduler->processes[j].burst);
            }
        }
    }
    printf("Finished at time %d\n\n", scheduler->runfor);

    // print process info
    for (int i = 0; i < scheduler->processcount; i++) {
        printf("%s wait %d turnaround %d\n", scheduler->processes[i].name,   scheduler->processes[i].wait, scheduler->processes[i].turnaround);
    }
}

// sjf
void shortest_job_first(control *scheduler) {
    printf("%d processes\n", scheduler->processcount);
    printf("Using Shortest Job First (pre)\n\n");

    FILE *out = fopen(OUTPUT_FILE,"r");


}

// choose which algorithm to execute
void run(control *scheduler) {
    if (scheduler == NULL) {
        printf("scheduler not initialized\n");
        return;
    }

    switch (scheduler->use) {
        case fcfs:
            first_come_first_serve(scheduler);
            break;
        case sjf:
            shortest_job_first(scheduler);
            break;
        case rr:
            round_robin(scheduler);
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
        printf("input file failed to open\n"); // yell
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

    // allocate space for the number of processes
    ptr->processes = malloc(sizeof(process)*ptr->processcount);

    // check if malloc worked
    if (ptr->processes == NULL) {
        printf("failed to allocate space for processes struct array\n");
        return NULL;
    }

    // array of process structs:
    // name, arrival, & burst
    for (int i = 0; i < ptr->processcount; i++) {
        // set process name
        fscanf(in, "%s %s %s\n", buffer, buffer, buffer);
        strcpy(ptr->processes[i].name, buffer);

        // set arrival
        fscanf(in, "%s %d\n", buffer, &ptr->processes[i].arrival);

        // set burst
        fscanf(in, "%s %d\n", buffer, &ptr->processes[i].burst);
    }

    fclose (in); // close file

    return ptr; // return the scheduler
}

int main(int argc, char const *argv[]) {

    // initialize the data stuctures
    control *scheduler = init();

    // run one of the scheduling algorithms
    run(scheduler);

    // done
    return 0;
}
