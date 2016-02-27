// Lucas Rosa
// lu599305

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    algorithms use;
    process *processes;
} control;

// rr
void round_robin() {

}

// fcfs
void first_come_first_serve() {

}

// sjf
void shortest_job_first() {

}

control *init() {


    return NULL;
}

void error() {
    printf("scheduler not initialized\n");
    exit(0);
}

void run(control *scheduler) {
    if (scheduler != NULL) {
        switch (scheduler->use) {
            case fcfs:
                first_come_first_serve();
            case sjf:
                shortest_job_first();
            case rr:
                round_robin();
            default:
                ;
        }
    } else {
        error();
    }
}

int main(int argc, char const *argv[]) {
    control *scheduler = init();

    run(scheduler);

    return 0;
}
