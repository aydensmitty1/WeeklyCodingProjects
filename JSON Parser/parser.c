#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_JSON_FILESIZE 1000

int getType(char *);

char* createSubStr(char *original, int newSize, int newStart){
    char* substr = calloc(newSize+1, sizeof(char));
    if (!substr){
        printf("Memmory Failed to Allocate! Exiting.....\n");
        return NULL;
    }
    strncpy(substr, &original[newStart], newSize);
    substr[newSize] = '\0';
    return substr;
}

void removeSpaces(char* s) {
    char* d = s;
    do{ while (*d == ' ') {++d;}
    }while(*s++ = *d++);
}

void removeNewline(char *str){
    for (int i = 0; i < strlen(str); i++){
        if(str[i] == '\n'){
            str[i] = ' ';
        }
    }
}

int isValidString(char *buff){
    // printf("char:%c\n", buff[strlen(buff)-1]);
    if (buff[0]== '"' && buff[strlen(buff)-1]=='"'){
                return 0;
            }
        // printf("Not a Valid String Value\n");
        return 1;
}

int isValidArray(char *buff){
    if (buff[0]== '[' && buff[strlen(buff)-1]==']'){
        if (strlen(buff) == 2){
                return 0;
            }
        int vstart = 1;
        int result = 0;
        for (int i = 0; i < strlen(buff); i++){
                if (buff[i]==',' || i == strlen(buff)-1){
                    char * vsubstr = createSubStr(buff, i-vstart, vstart);
                    if (vsubstr[0] == '\0'){
                        free(vsubstr);
                        result = 1;
                        return 1;
                    }
                    
                    // printf("attribute substr: %s\n", asubstr);
                    if (getType(vsubstr)){
                        // printf("Not a Valid Object, Attribute Failed\n");
                        free(vsubstr);
                        result = 1;
                        return 1;
                    }
                    vstart = i+1;
                    free(vsubstr);
                    result = 0;
                }
                
            }
        return result;
    }
    return 1;
}

int isValidInt(char *buff){
    int i = 0;
    while (buff[i]){
        if (!isdigit(buff[i])){
            // printf("LastDigit: %d\n", buff[i-1]);
        }
        i++;
    }
    return 0;
}
int isValidNull(char *buff){
    if (!strcmp(buff, "null")){
        return 0;
    }
    // printf("Not Valid Null Value\n");
    return 1;
}

int isValidBool(char *buff){
    if (!strcmp(buff, "true") || !strcmp(buff, "false")){
        return 0;
    }
    // printf("Not a Valid Bool Value\n");
    return 1;
}

int isValidKey(char * buff){
    char* substr = createSubStr(buff, strlen(buff)-1, 0);
    // printf("Substring: %s\n", substr);
    if (!isValidString(substr) && buff[strlen(buff)-1]==':'){
        free(substr);
        return 0;
    }
    // printf("Not a Valid Key\n");
    free(substr);
    return 1;
}



int isValidAttribute(char *buff){
    // printf("BUFF: %s\n", buff);
    int i = 0;
    while (buff[i]!= ':'){i++;}
    char * ksubstr = createSubStr(buff, i+1, 0);
    char * vsubstr = createSubStr(buff, strlen(buff) - i-1, i+1);
    // printf("Key:%s Value:%s\n", ksubstr, vsubstr);
    if (!isValidKey(ksubstr) && !getType(vsubstr)){
        free(ksubstr);
        free(vsubstr);
        return 0;
    }
    // printf("Not a Valid Attribute\n");
    free(ksubstr);
    free(vsubstr);
    return 1;
}

int isValidObject(char *buff){
        int result = 1;
        // printf("BUFFER: %s\n", buff);
        if (buff[0]== '{' && buff[strlen(buff)-1]=='}'){
            if (strlen(buff) == 2){
                return 0;
            }
            int astart = 1;
            int result = 0;
            // printf("char: %c\n", buff[strlen(buff)-1]);
            for (int i = 0; i < strlen(buff); i++){
                if (buff[i]==',' || i == strlen(buff)-1){
                    char * asubstr = createSubStr(buff, i-astart, astart);
                    if (asubstr[0] == '\0'){
                        free(asubstr);
                        result = 1;
                        return 1;
                    }
                    
                    // printf("attribute substr: %s\n", asubstr);
                    if (isValidAttribute(asubstr)){
                        // printf("Not a Valid Object, Attribute Failed\n");
                        free(asubstr);
                        result = 1;
                        return 1;
                    }
                    astart = i+1;
                    free(asubstr);
                    result = 0;
                }
                
            }
            return result;
            
        }
        // printf("char: %c\n", buff[strlen(buff)-1]);
        return 1;
}

int getType(char *buff){
    switch (buff[0]){
    case '"':
       return isValidString(buff);
    case '[':
       return isValidArray(buff);
    case '{':
        return isValidObject(buff);
    case '0' ... '9':
        return isValidInt(buff);
    case 'n':
        return isValidNull(buff);
    case 't':
        return isValidBool(buff);
    case 'f':
        return isValidBool(buff);
    default:
        // printf("What the Hell did you Enter!\n");
        return 1;
        break;
    }
}

int isValidJSON(FILE *fp){

    char *fbuff = calloc(MAX_JSON_FILESIZE, sizeof(char));

    fread(fbuff, MAX_JSON_FILESIZE, 1, fp);
    
    removeNewline(fbuff);
    removeSpaces(fbuff);
    int result = isValidObject(fbuff);
    free(fbuff);
    return result;
}

int main(int argc, char * argv[]){
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
       printf("Failed to open file.\n");
       return 1;
    }
    if (!isValidJSON(fp)){
        printf("VALID JSON FILE!\n");
        return 0;
    }
    printf("INVALID JSON FILE!\n");
    return 1;
     
}