#include "utils.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int checkFTP(char* input) {
    if (strstr(input,"ftp://") != input) {
        printf("Invalid URL!");
        return -1;
    };
    return 0;
}

int parseURL(URL *url, char *input) {

    char* URLToken;
    
    // compare to check if ftp:// is substring with checkFTP()
    if (checkFTP(input) == -1) return -1;
    // parse user info
    
    for (int i = 0; i < 6; i++) 
        input++;
    if (strstr(input, "@") == NULL) {
        url->user = "anonymous";
        url->password = "anonymous";
        URLToken = strtok(input, "/");
    }
    else {
        // get name
        if ((URLToken = strtok(input, ":")) == NULL)
            return -1;
        url->user = strdup(URLToken); 

        // get password
        if ((URLToken = strtok(NULL, "@")) == NULL) 
            return -1;
        url->password = strdup(URLToken);
        // move ahead of the password
        URLToken = strtok(NULL, "/");

    }
    // get host
    url->host = strdup(URLToken);

    char* latterToken;
    char* dupPath;
    bool found = false;

    // get path
    if ((URLToken = strtok(NULL, "\0")) == NULL)
        url->path = "";
    else {
        strcpy(url->path, URLToken);
        dupPath = strdup(URLToken);

        // get filename
        URLToken = strtok(dupPath, "/");
        while (!found) {
            latterToken = strdup(URLToken);
            URLToken = strtok(NULL, "/"); 
            found = (URLToken == NULL);
        }
        url->filename = strdup(latterToken);
    }

    return 0;
}