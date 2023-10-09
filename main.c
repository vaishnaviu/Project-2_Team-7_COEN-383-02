#include <stdio.h>
#include "process.h"
#include "queue.h"
#include "algos.h"


int main(int argc,char **argv) {
    Queue * processList = generateProcesses(10);
    displayQueue(processList);
    firstComeFirstServe(processList);
}