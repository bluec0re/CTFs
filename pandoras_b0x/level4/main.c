#include <string.h>
#include <stdio.h>

struct FileData {
    int length;
    void* data;
};

struct FileData* read_file(const char* filename) {
    FILE* fp;
    int size;
    struct FileData* fileData;

    fp = __new_fopen(filename, "rb");

    fseek(fp, 0, 2);
    size = ftell(fp);
    fseek(fp, 0, 0);
    fileData = __libc_malloc(8);
    fileData->length = size;
    fileData->data = __libc_malloc(fileData->length);
    fread(fp, 1, fileData->length, fileData->data);
    fclose(fp);
    return fileData;
}

int get_checksum(char* data, int length) {
    int idx = 0;
    int idx2;
    int checksum = -1;
    int value;
    int tmp;

    while(idx < length) {
        char c = data[idx];
        value = c;

        checksum ^= value;
        idx2 = 7;

        while(idx2 > 0) {
            tmp = ~(checksum & 1);
            checksum = (tmp & 0xedb88320) ^ (checksum >> 1);
            idx2--;
        }
    }

    return ~checksum;
}

void xcrypt(char* data, int length, const char* password) {
    int idx;
    int pwLen;

    pwLen = strlen(password);

    for(idx = 0; idx < length; idx++) {
        int d = data[idx];
        int p = password[idx % pwLen];
        data[idx] = idx ^ d ^ p;
    }
}


struct FileData* fileobj;
int decrypt_file(const char* filename, const char* password) {
    int *checksums;
    int length;
    char* data;
    char* data2;
    char msg[0x1000];

    if(!*password || strlen(password) > 10) {
        _IO_puts("Error: Invalid password length");
        return 0;
    }

    fileobj = read_file(filename);

    if(!fileobj) {
        _IO_puts("Error: Failed to open file");
        return 0;
    }

    if(fileobj->length > 9) {
        checksums = (int*)fileobj->data;
        length = fileobj->length - 4;
        data = fileobj->data + 4;
        if(get_checksum(data, length) != checksums[0]) {
            _IO_puts("Error: Invalid or corrupted file");
            free_Filedata(fileobj);
            return 0;
        }

        xcrypt(data, length, password);

        length -= 4;
        data += 4;

        if(get_checksum(data, length) != checksums[1]) {
            _IO_puts("Error: File data corrupted. bad password maybe?");
            free_Filedata(fileobj);
            return 0;
        }

        data2 = data;
        bzero(msg, 0x1000);

        memcpy(msg, data + 2, (char)data2[0]);

        _IO_printf("Message: %s\n", msg);
    }

    free_Filedata(fileobj);
    return 0;
}
