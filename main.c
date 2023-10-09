#include <stdio.h>
#include "process.h"
#include "queue.h"


int main(int argc,char **argv) {
    Queue * processList = generateProcesses(10);
    displayQueue(processList);
}