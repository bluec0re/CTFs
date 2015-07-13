#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pwd.h>


int main()
{
    char buffer[1024];
    struct passwd *pw;
    FILE* fp;
    fgets(buffer, 1024, stdin);
    setuid(0);
    seteuid(0);
    pw = getpwuid(getuid());
    if(!pw)
        return 1;
    sprintf(buffer, "%s/flag", pw->pw_dir);
    printf("%s\n", buffer);/*
    fp = fopen(buffer, "r");
    fgets(buffer, 1024, fp);
    printf("%s\n", buffer);
    fclose(fp);*/
    return 0;
}
