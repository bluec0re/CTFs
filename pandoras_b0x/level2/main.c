#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

int list_size;

struct Note {
    int length;
    char* text;
};

struct Note* create_struct() {
    struct Note* note = (struct Note*)malloc(8);
    note->length = 64;
    note->text = malloc(note->length);

    mprotect(note->text & 0xFFFFF000, note->length, PROT_READ | PROT_WRITE | PROT_EXEC);
    return note;
}

void free_struct(struct Note* note) {
    free(note->text);
    free(note);
}

int slot_exists(struct Note** noteList, int noteId) {
    if(noteId > list_size)
        return 0;

    if(noteList[noteId])
        return 0;
    else
        return 1;
}

int get_empty_slot(struct Note** noteList) {
    int noteId = 0;

    for(noteId = 0; noteId < list_size; noteId++) {
        if(!noteList[noteId])
            return noteId;
    }
    return -1;
}

void stripnewline(char* buffer) {
    char* p = strchr(buffer, '\n');
    if(p) {
        *p = 0;
    }
    p = strchr(buffer, '\r');
    if(p) {
        *p = 0;
    }
}

int readline(char* buffer, int buffLen, char* prompt, int maxLen) {
    write(1, prompt, strlen(prompt));
    bzero(buffer, buffLen);

    if(maxLen) {
        fgets(buffer, maxLen, stdin);
    } else {
        fgets(buffer, buffLen, stdin);
    }
    stripnewline(buffer);
    return strlen(buffer);
}

int main() {
    // stack setup
    /*
    int local_0; // saved ebp
    int local_1; // saved ebx
    int local_2; // saved ecx
    */
    int listSize; // -c
    int local_4;  // -10
    struct Note** noteList; // -14
    int noteId;   // -18
    int local_7;  // -1c
    int local_8;  // -20
    int local_9;  // -24
    char inputBuffer[128]; // -a4
    int foo;      // -a8
    int local_10; // -ac
    // -c8 @ 80489b6
    // -f8 @ 80489f8
    int ebp = 0xffffcac8;
    noteList = (((ebp-0xf8+0x10) + 3) >> 2) << 2;


    // 0x8048a0a
    show_welcome();

    for(listSize = 0; listSize < list_size; listSize++) {
        noteList[listSize] = 0;
    }

    while(1) {
        readline(inputBuffer, 128, "> ", 10);

        if(inputBuffer[0]) {
            if(strcmp(inputBuffer, "exit") == 0) {
                puts("[*] Goodbye");
                break;
            }
            else if(strcmp(inputBuffer, "help") == 0) {
                show_help();
            }
            else if(strcmp(inputBuffer, "new") == 0) {
                noteId = get_empty_slot();
                if(noteId != -1) {
                    noteList[noteId] = create_struct();
                    printf("[*] New note created with id %d\n", noteId);
                } else {
                    puts("[!] Note list is full, please free any");
                }
            }
            else if(strcmp(inputBuffer, "set") == 0) {
                readline(inputBuffer, 128, "> id: ", 10);
                noteId = strtol(inputBuffer, 0, 10);
                if(slot_exists(noteList, noteId) == 1) {
                    readline(inputBuffer, 128, "> text(32 max): ", 0);
                    noteList[noteId]->length = strlen(inputBuffer);
                    memcpy(noteList[noteId]->text, inputBuffer, noteList[noteId]->length);
                    printf("[*] Note %d set\n", noteId);
                } else {
                    printf("[!] Note id %d doesnt exist\n", noteId);
                }
            }
            else if(strcmp(inputBuffer, "show") == 0) {
                readline(inputBuffer, 128, "> id: ", 10);
                noteId = strtol(inputBuffer, 0, 10);
                if(slot_exists(noteList, noteId) == 1) {
                    printf("[*] Note %d text: %s\n", noteId, noteList[noteId]->text);
                } else {
                    printf("[!] Note id %d doesnt exist\n", noteId);
                }
            }
            else if(strcmp(inputBuffer, "del") == 0) {
                readline(inputBuffer, 128, "> id: ", 10);
                noteId = strtol(inputBuffer, 0, 10);
                if(slot_exists(noteList, noteId) == 1) {
                    free_struct(noteList[noteId]);
                    noteList[noteId] = 0;
                    printf("[*] Note %d deleted\n", noteId);
                } else {
                    printf("[!] Note id %d doesnt exist\n", noteId);
                }
            } else {
                puts("[!] Invalid command, try help");
            }

        }
        fflush(stdout);
    }
}
