#include <stdio.h>


void show_welcome() {
    fwrite("#########################\n# Simple Number Manager #\n#########################\n", 1, 0x4e, stderr);
    fwrite("This tool allows you to store and view upto 10 numbers\n", 1, 0x37, stderr);
    fwrite("in a array\n", 1, 0xc, stderr);
    fwrite("Type exit to close or help for a command list\n", 1, 0x2e, stderr);
    fflush(stderr);
}

int nrmanager() {
    // push 4 regs
    // sub esp, 0x5c
    int stackcookie; // esp + 0x4c
    char buffer[]; // esp + 0x3c
    int array[]; // esp + 0x14

    while(1) {
        if(!readline(buffer, 16, "> "))
            continue;

        if(strcmp("exit", buffer) == 0) {
            fwrite("Goodbye\n", 1, 8, stderr);
            return 0;
        }
        else if(strcmp("help", buffer) == 0) {
            show_help();
        }
        else if(strcmp("get", buffer) == 0) {
            if(!readline(buffer, 16, "> id: ")) {
                fwrite("id not found\n", 1, 0xd, stderr);
                continue;
            }

            int idx = strtoul(buffer, 0, 10);
            if(idx > 9) {
                fwrite("The array only has 10 entry's, use index 0..9\n", 1, 0x2e, stderr);
                continue;
            }

            fprintf(stderr, "value: %u\n", array[idx & 0xff]);
        }
        else if(strcmp("set", buffer) == 0) {
            if(!readline(buffer, 16, "> id: ")) {
                fwrite("id not found\n", 1, 0xd, stderr);
                continue;
            }

            int idx = strtoul(buffer, 0, 10);
            if(idx > 9) {
                fwrite("The array only has 10 entry's, use index 0..9\n", 1, 0x2e, stderr);
                continue;
            }

            if(!readline(buffer, 16, "> value: ")) {
                fwrite("Bad value\n", 1, 10, stderr);
                continue;
            }

            array[idx] = strtoul(buffer, 0, 10);
            fwrite("Value stored\n", 1, 0xd, stderr);
        }
    }
}

void main() {
    dup2(1, 2);
    nrmanager();
}
