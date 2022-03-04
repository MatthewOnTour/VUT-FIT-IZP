/* **********************************************************************************
                created by: MatĂşĹĄ JuĹĄtik (xjusti00)
********************************************************************************** */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* ********************************************************************************** */
#define MAX_LEN 10242   //maximum char na riadok
#define MAX_BUNK 100    //maximum argumentov na bunku
#define DELIM " "       //povodny delim ak sa nemeni v argumente
/* ********************************************************************************** */
//meni delim na prvy zadany delim
void change(char *delim, char *buffer);
/* ********************************************************************************** */
// funkcia na pocitanie delimiteru v prvom riadku
void counting(const char *str, int *counter,const char *delim);
/* ********************************************************************************** */
//vloĹžĂ­ ĹĂĄdek tabulky pĹed ĹĂĄdek R > 0 (insert-row)
void irow(int countRow,int countCol,char **argv, int helpCount, char *delim, int *ERROR_R);
//pĹidĂĄ novĂ˝ ĹĂĄdek tabulky na konec tabulky (append-row)
void arow(int countCol, char *delim,const char *buffer);
//odstranĂ­ ĹĂĄdek ÄĂ­slo R > 0 (delete-row)
void drow(int *countRow, char **argv, int helpCount, char *buffer, int *ERROR_R);
//odstranĂ­ ĹĂĄdky N aĹž M (N <= M). V pĹĂ­padÄ N=M se pĹĂ­kaz chovĂĄ stejnÄ jako drow N
void drows(int *countRow, char **argv, int helpCount, char *buffer, int *ERROR_M, int *ERROR_N);
//vloĹžĂ­ prĂĄzdnĂ˝ sloupec pĹed sloupec danĂ˝ ÄĂ­slem C
void icol(const char *delim, int helpCount, char **argv, char *buffer, int *ERROR_C);
//pĹidĂĄ prĂĄzdnĂ˝ sloupec za poslednĂ­ sloupec
void acol(const char *delim, char *buffer);
//odstranĂ­ sloupec ÄĂ­slo C
void dcol(const char *delim, int helpCount, char **argv, char *buffer, int *ERROR_C);
//odstranĂ­ sloupce N aĹž M (N <= M). V pĹĂ­padÄ N=M se pĹĂ­kaz chovĂĄ stejnÄ jako dcol N
void dcols(const char *delim, int helpCount, char **argv, char *buffer, int *differ, int countRow,
           int *ERROR_M, int *ERROR_N);
/* ********************************************************************************** */
//do buĹky ve sloupci C bude nastaven ĹetÄzec STR.
void cset(const char *delim, int helpCount, char **argv, char *buffer, int *ERROR_C, int countRow);
//ĹetÄzec ve sloupci C bude pĹeveden na malĂĄ pĂ­smena.
void tolowerC(const char *delim, int helpCount, char **argv, char *buffer, int *ERROR_C);
//ĹetÄzec ve sloupce C bude pĹeveden na velkĂĄ pĂ­smena.
void toupperC(const char *delim, int helpCount, char **argv, char *buffer, int *ERROR_C);
//ve sloupci C zaokrouhlĂ­ ÄĂ­slo na celĂŠ ÄĂ­slo.
void roundC(const char *delim, int helpCount, char **argv, char *buffer, int *ERROR_C);
//odstranĂ­ desetinnou ÄĂĄst ÄĂ­sla ve sloupci C.
void intC(const char *delim, int helpCount, char **argv, char *buffer, int *ERROR_C);
//pĹepĂ­ĹĄe obsah bunÄk ve sloupci M hodnotami ze sloupce N.
void copy(const char *delim, int helpCount, char **argv, char *buffer, int *ERROR_M,  int *ERROR_N);
/* **********************************************************************************
//zamÄnĂ­ hodnoty bunÄk ve sloupcĂ­ch N a M.
void swap();
//pĹesune sloupec N pĹed sloupec M.
void move();
 **********************************************************************************
//procesor bude zpracovĂĄvat pouze ĹĂĄdky N aĹž M vÄetnÄ (N <= M). N=1 znamenĂĄ zpracovĂĄnĂ­ od prvnĂ­ho ĹĂĄdku. Pokud
// je mĂ­sto ÄĂ­sla M zadĂĄn znak - (pomlÄka), ta reprezentuje poslednĂ­ ĹĂĄdek vstupnĂ­ho souboru. Pokud je pomlÄka
// takĂŠ mĂ­sto sloupce N, myslĂ­ se tĂ­m vĂ˝bÄr pouze poslednĂ­ho ĹĂĄdku. Pokud nenĂ­ tento pĹĂ­kaz zadĂĄn, uvaĹžuje
// se implicitnÄ o vĹĄech ĹĂĄdcĂ­ch.
void rows();
//procesor bude zpracovĂĄvat pouze ty ĹĂĄdky, jejichĹž obsah buĹky ve sloupci C zaÄĂ­nĂĄ ĹetÄzcem STR.
void beginswith();
//procesor bude zpracovĂĄvat pouze ty ĹĂĄdky, jejichĹž buĹky ve sloupci C obsahujĂ­ ĹetÄzec STR.
void contains();
 ********************************************************************************** */
int main(int argc, char *argv[]){
    //zistim delim ak je zadanĂ˝ inĂ˝ tak ho zmenĂ­m
    char delim[MAX_BUNK] = DELIM;
    if (argc > 2) {
        if ((strcmp(argv[1], "-d") == 0) && (argc >= 3)) {
            strcpy(delim, argv[2]);
        }
    }
    char buffer[MAX_LEN];
    int countRow = 1;                  //counter riadkov
    int countCol = 0;                  //counter stlpcov
    int ERROR_R = 0;                   //error na rows error 1
    int ERROR_C = 0;                   //error na col error 2
    int ERROR_N = 0;                   //error na M error 3
    int ERROR_M = 0;                   //error na N error 3
    int differ = 0;                    //udava rozdiel ak odpocitavam stlpce
        while (fgets(buffer, MAX_LEN, stdin) != NULL) {
            if (countRow == 1){
                counting(buffer, &countCol, delim);
            }
            change(delim, buffer);
            for (int helpCount = 0; helpCount < argc; helpCount++) {
                if (strcmp(argv[helpCount], "irow") == 0) {
                    irow(countRow, countCol, argv, helpCount, delim, &ERROR_R);
                    // ak sa vrati nespravna hodnota ukonci program a vypise error
                    if (ERROR_R <= 0) {
                        fprintf(stderr,"\nincorrect number value\n");
                        return 1;
                    }
                }
                if (strcmp(argv[helpCount], "drow") == 0){
                    drow(&countRow, argv, helpCount, buffer, &ERROR_R);
                    // ak sa vrati nespravna hodnota ukonci program a vypise error
                    if (ERROR_R <= 0) {
                        fprintf(stderr,"\nincorrect number value\n");
                        return 1;
                    }
                }
                if (strcmp(argv[helpCount], "drows") == 0) {
                    drows(&countRow, argv, helpCount, buffer, &ERROR_M, &ERROR_N);
                    // ak sa vrati nespravna hodnota ukonci program a vypise error
                    if (ERROR_N <= 0) {
                        fprintf(stderr,"\nincorrect number value\n");
                        return 3;
                    }
                    if (ERROR_M <= 0) {
                        fprintf(stderr,"\nincorrect number value\n");
                        return 3;
                    }
                    if (ERROR_N < ERROR_M){
                        fprintf(stderr,"\nincorrect number value\n");
                        return 3;
                    }
                }
                if (strcmp(argv[helpCount], "icol") == 0) {
                    icol(delim, helpCount ,argv, buffer, &ERROR_C);
                    // ak sa vrati nespravna hodnota ukonci program a vypise error
                    if (ERROR_C <= 0){
                        fprintf(stderr,"\nincorrect number value\n");
                        return 2;
                    }
                    // ak funkcia prebehne bez erroru tak sa pripocita / odpocita counter na stlpce
                    if (countRow == 1) countCol++;
                }
                if (strcmp(argv[helpCount], "acol") == 0) {
                    acol(delim, buffer);
                    // ak funkcia prebehne bez erroru tak sa pripocita / odpocita counter na stlpce
                    if (countRow == 1) countCol++;
                }
                if (strcmp(argv[helpCount], "dcol") == 0) {
                    dcol(delim, helpCount ,argv, buffer, &ERROR_C);
                    // ak sa vrati nespravna hodnota ukonci program a vypise error
                    if (ERROR_C <= 0){
                        fprintf(stderr,"\nincorrect number value\n");
                        return 2;
                    }
                    // ak funkcia prebehne bez erroru tak sa pripocita / odpocita counter na stlpce
                    if (countRow == 1) countCol--;
                }
                if (strcmp(argv[helpCount], "dcols") == 0) {
                    dcols(delim, helpCount ,argv, buffer, &differ, countRow, &ERROR_M, &ERROR_N);
                    // ak sa vrati nespravna hodnota ukonci program a vypise error
                    if (ERROR_N <= 0) {
                        fprintf(stderr,"\nincorrect number value\n");
                        return 3;
                    }
                    if (ERROR_M <= 0) {
                        fprintf(stderr,"\nincorrect number value\n");
                        return 3;
                    }
                    if (ERROR_N < ERROR_M){
                        fprintf(stderr,"\nincorrect number value\n");
                        return 3;
                    }
                    // ak funkcia prebehne bez erroru tak sa pripocita / odpocita counter na stlpce
                    if (countRow == 1) countCol -= differ+1;
                }
                if (strcmp(argv[helpCount], "cset") == 0) {
                    cset(delim, helpCount, argv, buffer, &ERROR_C, countRow);
                    // ak sa vrati nespravna hodnota ukonci program a vypise error
                    if (ERROR_C <= 0){
                        fprintf(stderr,"\nincorrect number value\n");
                        return 2;
                    }
                }
                if (strcmp(argv[helpCount], "tolower") == 0) {
                    tolowerC(delim, helpCount ,argv, buffer, &ERROR_C);
                    // ak sa vrati nespravna hodnota ukonci program a vypise error
                    if (ERROR_C <= 0){
                        fprintf(stderr,"\nincorrect number value\n");
                        return 2;
                    }
                }
                if (strcmp(argv[helpCount], "toupper") == 0) {
                    toupperC(delim, helpCount ,argv, buffer, &ERROR_C);
                    // ak sa vrati nespravna hodnota ukonci program a vypise error
                    if (ERROR_C <= 0){
                        fprintf(stderr,"\nincorrect number value\n");
                        return 2;
                    }
                }
                if (strcmp(argv[helpCount], "round") == 0) {
                    roundC(delim, helpCount, argv, buffer, &ERROR_C);
                    // ak sa vrati nespravna hodnota ukonci program a vypise error
                    if (ERROR_C <= 0){
                        fprintf(stderr,"\nincorrect number value\n");
                        return 2;
                    }
                }
                if (strcmp(argv[helpCount], "int") == 0) {
                    intC(delim, helpCount, argv, buffer, &ERROR_C);
                    // ak sa vrati nespravna hodnota ukonci program a vypise error
                    if (ERROR_C <= 0){
                        fprintf(stderr,"\nincorrect number value\n");
                        return 2;
                    }
                }
                if (strcmp(argv[helpCount], "copy") == 0) {
                    copy(delim, helpCount, argv, buffer, &ERROR_M,&ERROR_N);
                    // ak sa vrati nespravna hodnota ukonci program a vypise error
                    if (ERROR_N <= 0) {
                        fprintf(stderr,"\nincorrect number value\n");
                        return 3;
                    }
                    if (ERROR_M <= 0) {
                        fprintf(stderr,"\nincorrect number value\n");
                        return 3;
                    }
                    if (ERROR_N < ERROR_M){
                        fprintf(stderr,"\nincorrect number value\n");
                        return 3;
                    }
                }
                /*
                if (strcmp(argv[helpCount], "swap") == 0) {
                    swap();
                }
                if (strcmp(argv[helpCount], "move") == 0) {
                    move();
                }
                 */
            }
            printf("%s", buffer);           // vypisanie upraveneho riadku
            countRow++;                            // pripocitanie riadku/counter
        }

    for(int i = 0; i < argc; i++){
        if(strcmp(argv[i], "arow") == 0) {
            arow(countCol, delim, buffer);
        }
    }
    printf("\n");
    return 0;
}
/* ********************************************************************************** */
int is_delim(char *delims, char znak) {

    for (int temp = 0; temp < (int)(strlen(delims)); temp++)
        if (znak == delims[temp]) return 1;
    return 0;

}
/* ********************************************************************************** */
void change(char *delim, char *buffer){
    for (int j = 0; buffer[j] != '\0'; j++) {
            if (is_delim(delim, buffer[j])) {   // premena delim v aktualnom riadku
                buffer[j] = delim[0];;
            }
    }
}
/* ********************************************************************************** */
//spocitanie delim v prvom riadku
void counting(const char *str, int *counter,const char *delim) {
    for (int i = 0; str[i] != '\0'; i++) {
            for (int j = 0; j < (int) strlen(delim) + i; j++) {    //pozerĂĄm na celĂ˝ delim nie len prvĂ˝ znak
                if (str[i] == delim[j]) *counter +=1;
            }
    }
}
/* ********************************************************************************** */
void irow(int countRow,int countCol,char **argv, int helpCount, char *delim, int *ERROR_R){
    char *end;
    int numberR;
    if (argv[helpCount+1] == NULL){     // kontrola ci sa za prikazom nachadza znak
        numberR = 0;
    } else{
        numberR = strtol(argv[helpCount + 1], &end, 10);// dĂĄvam pozor aj je viaciferne cisla
        if (*end != '\0') return;
    }
    // cez pointer poslem hodnotu a vypisem stderr
    *ERROR_R = numberR;
    if (countRow == numberR) {
        for (int k = 0; k < countCol; ++k) {
            printf("%c", delim[0]);
        }
        printf("\n");
    }
}
void arow(int countCol, char *delim,const char *buffer){
    if (buffer[0] != '\0'){
       printf("\n");
    }
    for (int k = 0; k < countCol; ++k) {
    printf("%c", delim[0]);
    }
}
void drow(int *countRow, char **argv, int helpCount, char *buffer, int *ERROR_R){
    char *end;
    int numberR;
    if (argv[helpCount+1] == NULL){         // pozriem ci sa za drow nachadza platny znak
        numberR = 0;                        // ak ano beriem to ako chybu
    } else{
        numberR = strtol(argv[helpCount + 1], &end, 10);
        if (*end != '\0') return;
    }
    // cez pointer poslem hodnotu a vypisem stderr
    *ERROR_R = numberR;
    if(*countRow == numberR){
        if (fgets(buffer, MAX_LEN, stdin) == NULL || strlen(buffer) == 0)
            buffer[0] = '\0';
        *countRow += 1;
    }
}
void drows(int *countRow, char **argv, int helpCount, char *buffer, int *ERROR_M, int *ERROR_N){
    char *end;
    int numberM;
    if (argv[helpCount+1] == NULL){
        numberM = 0;
    } else{
        numberM = strtol(argv[helpCount+1], &end, 10);
        if (*end != '\0') return;
    }
    int numberN;
    if (argv[helpCount+2] == NULL){
        numberN = 0;
    }else{
        numberN = strtol(argv[helpCount+2], &end, 10);
        if (*end != '\0') return;
    }
    // cez pointer poslem hodnotu a vypisem stderr
    *ERROR_N = numberN;
    *ERROR_M = numberM;
    while ((*countRow >= numberM) && (*countRow <= numberN)) {
        if (fgets(buffer, MAX_LEN, stdin) == NULL){
            buffer[0]='\0';
            break;
        }
        *countRow += 1;
        numberM = 0;
    }
}
void icol(const char *delim, int helpCount, char **argv, char *buffer, int *ERROR_C){
    char *end;
    int numberC;
    if (argv[helpCount+1] == NULL){
        numberC = 0;
    } else{
        numberC = strtol(argv[helpCount + 1], &end, 10);
        if (*end != '\0') return;
    }
    // cez pointer poslem hodnotu a vypisem stderr
    *ERROR_C = numberC;
    int countDelim = 1;
    for (int j = 0; buffer[j] != '\0'; ++j) {
        for (int temp3 = 0; temp3 < (int)strlen(delim); temp3++) {
            if (buffer[j] == delim[temp3]) {
                countDelim++;
            }
            if (countDelim == numberC) {
                countDelim++;
                char temp1 = delim[0];
                char temp2;
                int k;
                for (k = j; buffer[k] != '\0' && buffer[k] != '\n'; k++) {
                    temp2 = buffer[k];
                    buffer[k] = temp1;
                    temp1 = temp2;
                }
                int len;
                len =(int) strlen(buffer);
                if (buffer[len - 1] == '\n') {
                    buffer[k] = temp1;
                    buffer[k + 1] = '\n';
                    buffer[k + 2] = '\0';
                } else{
                    buffer[k] = temp1;
                    buffer[k + 1] = '\0';
                }
            }
        }
    }
}
void acol(const char *delim,char *buffer){
    int len;
    len =(int) strlen(buffer);
    if(buffer[len - 1] == '\n') {
        buffer[len - 2] = delim[0];
        buffer[len + 1] = '\0';
    } else{
        buffer[len] = delim[0];
        buffer[len + 1] = '\0';
    }
}
void dcol(const char *delim, int helpCount, char **argv,char *buffer, int *ERROR_C) {
    char *end;
    int numberM;
    if (argv[helpCount+1] == NULL){
        numberM = 0;
    } else{
        numberM = strtol(argv[helpCount + 1], &end, 10);
        if (*end != '\0') return;
    }
    int numberN = numberM;
    // cez pointer poslem hodnotu a vypisem stderr
    *ERROR_C = numberN;
    int momentDelim = 1;
    char buffertemp[MAX_LEN];
    memset(buffertemp, 0, sizeof(buffertemp));
    int j;
    int k = 0;
    int temp2;
    for (j = 0; buffer[j] != '\0'; ++j) {
        for (temp2 = 0; temp2 < (int)strlen(delim); temp2++) {
            if (buffer[j] == delim[temp2]){
                momentDelim++;
                break;
            }
        }
        if (momentDelim < numberM || momentDelim > numberN){
            if (momentDelim != numberN || buffer[j] != delim[temp2]) {
                buffertemp[k++] = buffer[j];
            }
        }
    }

    strcpy(buffer, buffertemp);
}
void dcols(const char *delim, int helpCount, char **argv, char *buffer, int *differ, int countRow,
           int *ERROR_M, int *ERROR_N){

    char *end;
    int numberM;
    if (argv[helpCount+1] == NULL){
        numberM = 0;
    } else{
        numberM = strtol(argv[helpCount+1], &end, 10);
        if (*end != '\0') return;
    }
    int numberN;
    if (argv[helpCount+2] == NULL){
        numberN = 0;
    }else{
        numberN = strtol(argv[helpCount+2], &end, 10);
        if (*end != '\0') return;
    }
    // cez pointer poslem hodnotu a vypisem stderr
    *ERROR_N = numberN;
    *ERROR_M = numberM;
    *differ = numberN- numberM;
    int momentDelim = 1;
    char buffertemp[MAX_LEN];
    memset(buffertemp, 0, sizeof(buffertemp));
    int j;
    int k = 0;
    int temp2;
    for (j = 0; buffer[j] != '\0'; ++j) {
        for (temp2 = 0; temp2 < (int)strlen(delim); temp2++) {
            if (buffer[j] == delim[temp2]){
                momentDelim++;
                break;
            }
        }
        if (momentDelim < numberM || momentDelim > numberN){
            if (momentDelim != numberN || buffer[j] != delim[temp2]) {
                buffertemp[k++] = buffer[j];
            }
        }
    }
    if (helpCount+1 == numberN && numberM != 1 && countRow !=1) {
        printf("%c", '\n');
    }
    strcpy(buffer, buffertemp);
}
/* ********************************************************************************** */
void cset(const char *delim, int helpCount, char **argv, char *buffer, int *ERROR_C, int countRow){
    char str[MAX_BUNK];
    char buffertemp[MAX_LEN];
    char *end;
    int j;
    int i = 0;
    memset(buffertemp, 0, sizeof(buffertemp));
    int numberC;
    if (argv[helpCount+1] == NULL){
        numberC = 0;
    } else{
        numberC = strtol(argv[helpCount + 1], &end, 10);
        if (*end != '\0') return;
    }
    if (argv[helpCount+2] == NULL){
        numberC = 0;
    } else{strcpy(str, argv[helpCount + 2]);}
    // cez pointer poslem hodnotu a vypisem stderr
    *ERROR_C = numberC;
    int momentDelim = 1;
    if (numberC == momentDelim) {
        strcpy(buffertemp, str);
        for (;(delim[0] != buffer[i]) && buffer[i] != '\0'; i++);
        j = (int) strlen(str);
    } else j = 0;
    for (; buffer[i] != '\0'; i++){
        if (delim[0] == buffer[i]) {
            momentDelim++;
            if (momentDelim == numberC){
                for (int q = 0; q < 1; q++) buffertemp[j++] = delim[0];
                for (int k = 0; k < (int) strlen(str); k++) buffertemp[j++] = str[k];
                for (;(delim[0] != buffer[i]) && buffer[i] != '\0'; i++);
            }
        }
        if (momentDelim != numberC) buffertemp[j++] = buffer[i];
    }
    if (helpCount+1 == numberC && numberC != 1 && countRow !=1) {
        printf("%c", '\n');
    }
    strcpy(buffer, buffertemp);
}
void tolowerC(const char *delim, int helpCount, char **argv, char *buffer, int *ERROR_C){
    char *end;
    int numberC;
    if (argv[helpCount+1] == NULL){
        numberC = 0;
    } else{
        numberC = strtol(argv[helpCount + 1], &end, 10);
        if (*end != '\0') return;
    }
    // cez pointer poslem hodnotu a vypisem stderr
    *ERROR_C = numberC;
    int temp;
    int j;
    int momentDelim = 1;
    for (j = 0; buffer[j] != '\0'; ++j) {
        for (temp = 0; temp < (int)strlen(delim); temp++) {
            if (buffer[j] == delim[temp]) {
                momentDelim++;
            }
        }
        if (momentDelim == numberC){
            if (buffer[j] >= 'A' && buffer[j] <= 'Z') {
                buffer[j] = buffer[j] + ('a' - 'A');
            }
        }
    }
}
void toupperC(const char *delim, int helpCount, char **argv, char *buffer, int *ERROR_C){
    char *end;
    int numberC;
    if (argv[helpCount+1] == NULL){
        numberC = 0;
    } else{
        numberC = strtol(argv[helpCount + 1], &end, 10);
        if (*end != '\0') return;
    }
    // cez pointer poslem hodnotu a vypisem stderr
    *ERROR_C = numberC;
    int temp;
    int j;
    int momentDelim = 1;
    for (j = 0; buffer[j] != '\0'; ++j) {
        for (temp = 0; temp < (int)strlen(delim); temp++) {
            if (buffer[j] == delim[temp]) {
                momentDelim++;
            }
        }
        if (momentDelim == numberC){
            if (buffer[j] >= 'a' && buffer[j] <= 'z') {
                buffer[j] = buffer[j] - ('a' - 'A');
            }
        }
    }
}
void roundC(const char *delim, int helpCount, char **argv, char *buffer, int *ERROR_C){ // oprava
    char *bin;
    double temp;
    char str1[MAX_BUNK];
    char str[MAX_BUNK];
    char buffertemp[MAX_LEN];
    char *end;
    int q;
    int j = 0;
    int i = 0;
    memset(buffertemp, 0, sizeof(buffertemp));
    memset(str, 0, sizeof(str));
    int numberC;
    if (argv[helpCount+1] == NULL){
        numberC = 0;
    } else{
        numberC = strtol(argv[helpCount + 1], &end, 10);
        if (*end != '\0') return;
    }
    // cez pointer poslem hodnotu a vypisem stderr
    *ERROR_C = numberC;
    int momentDelim = 1;
    if (numberC == momentDelim) {
        for (q = 0; buffer[i] != '\n' && buffer[i] != delim[0];  ++i) str[q++] = buffer[i];
        temp = strtod(str, &bin);
        if (*bin == '\0'){
            if (temp < 0){
                temp = temp -0.5;
            }
            if (temp > 0){
                temp = temp +0.5;
            }
            sprintf(str1, "%d", (int)temp);
            strcpy(str, str1);
        }
        for (int k = 0; k < (int) strlen(str); k++) buffertemp[j++] = str[k];
    } else j = 0;
    for (; buffer[i] != '\0'; i++){
        if (delim[0] == buffer[i]) {
            momentDelim++;
            if (momentDelim == numberC){
                buffertemp[j++] = delim[0];
                i++;
                for (q = 0; buffer[i] != '\n' && buffer[i] != delim[0] ;  ++i) str[q++] = buffer[i];
                temp = strtod(str, &bin);
                if (*bin == '\0'){
                    if (temp < 0){
                        temp = temp -0.5;
                    }
                    if (temp > 0){
                        temp = temp +0.5;
                    }
                    sprintf(str1, "%d", (int)temp);
                    strcpy(str, str1);
                }
                momentDelim++;
                for (int k = 0; k < (int) strlen(str); k++) buffertemp[j++] = str[k];
            }
        }
        if (momentDelim != numberC) buffertemp[j++] = buffer[i];
    }

    strcpy(buffer, buffertemp);
    
}
void intC(const char *delim, int helpCount, char **argv, char *buffer, int *ERROR_C){
    char *bin;
    double temp;
    char str1[MAX_BUNK];
    char str[MAX_BUNK];
    char buffertemp[MAX_LEN];
    char *end;
    int q;
    int j = 0;
    int i = 0;
    memset(buffertemp, 0, sizeof(buffertemp));
    memset(str, 0, sizeof(str));
    int numberC;
    if (argv[helpCount+1] == NULL){
        numberC = 0;
    } else{
        numberC = strtol(argv[helpCount + 1], &end, 10);
        if (*end != '\0') return;
    }
    // cez pointer poslem hodnotu a vypisem stderr
    *ERROR_C = numberC;
    int momentDelim = 1;
    if (numberC == momentDelim) {
        for (q = 0; buffer[i] != '\n' && buffer[i] != delim[0];  ++i) str[q++] = buffer[i];
        temp = strtod(str, &bin);
        if (*bin == '\0'){
            sprintf(str1, "%d", (int)temp);
            strcpy(str, str1);
        }
        for (int k = 0; k < (int) strlen(str); k++) buffertemp[j++] = str[k];
    } else j = 0;
    for (; buffer[i] != '\0'; i++){
        if (delim[0] == buffer[i]) {
            momentDelim++;
            if (momentDelim == numberC){
                buffertemp[j++] = delim[0];
                i++;
                for (q = 0; buffer[i] != '\n' && buffer[i] != delim[0] ;  ++i) str[q++] = buffer[i];
                temp = strtod(str, &bin);
                if (*bin == '\0'){
                    sprintf(str1, "%d", (int)temp);
                    strcpy(str, str1);
                }
                momentDelim++;
                for (int k = 0; k < (int) strlen(str); k++) buffertemp[j++] = str[k];
            }
        }
        if (momentDelim != numberC) buffertemp[j++] = buffer[i];
    }
    strcpy(buffer, buffertemp);
}
void copy(const char *delim, int helpCount, char **argv, char *buffer, int *ERROR_M,  int *ERROR_N){
    char str[MAX_BUNK];
    char buffertemp[MAX_LEN];
    char *end;
    int q;
    int j = 0;
    int i = 0;
    memset(buffertemp, 0, sizeof(buffertemp));
    memset(str, 0, sizeof(str));
    int numberM;
    if (argv[helpCount+1] == NULL){
        numberM = 0;
    } else{
        numberM = strtol(argv[helpCount+1], &end, 10);
        if (*end != '\0') return;
    }
    int numberN;
    if (argv[helpCount+2] == NULL){
        numberN = 0;
    }else{
        numberN = strtol(argv[helpCount+2], &end, 10);
        if (*end != '\0') return;
    }
    // cez pointer poslem hodnotu a vypisem stderr
    *ERROR_N = numberN;
    *ERROR_M = numberM;
    int momentDelim = 1;
    if (numberM == momentDelim) {
        for (q = 0; buffer[i] != '\n' && buffer[i] != delim[0];  ++i) str[q++] = buffer[i];
        for (int k = 0; k < (int) strlen(str); k++) buffertemp[j++] = str[k];
    } else j = 0;
    for (; buffer[i] != '\0'; i++){
        if (delim[0] == buffer[i]) {
            momentDelim++;
            if (momentDelim == numberN){
                buffertemp[j++] = delim[0];
                i++;
                momentDelim++;
                for (int k = 0; k < (int) strlen(str); k++) buffertemp[j++] = str[k];

            }
        }
        if (momentDelim != numberN) buffertemp[j++] = buffer[i];
    }
    strcpy(buffer, buffertemp);
}
/* **********************************************************************************
void swap(){

}
void move(){

}
 **********************************************************************************
void rows(){

}
void beginswith(){

}
void contains(){

}
 ********************************************************************************** */