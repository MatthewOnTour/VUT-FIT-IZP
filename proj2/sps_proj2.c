/* **********************************************************************************
                created by: MatĂşĹĄ JuĹĄtik (xjusti00)
********************************************************************************** */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* ********************************************************************************** */
//vytvorenie struktur
typedef struct bunk {
    char chars[200];
}t_bunk;

typedef struct line{
    t_bunk bunk[50];
}t_line;

typedef struct table {
    t_line *line;
    int count_line;
    int last_bunk_number;
}t_table;
/* ********************************************************************************** */
int is_delim(char delim[10], int sign);
void print(t_table *table, char *delim);
/* ********************************************************************************** */
int main(int argc, char **argv) {
    char delim[10] = " ";   //delim ak nie je zadany iny
    char file_name[25];     //pole pre nacitanie suboru
    char cmd_sp[125];       //pole pre prikazy
    for (int i = 0; i < argc; ++i) {
        //zistenie delimiteru
        if(strcmp(argv[i], "-d") == 0){
            strcpy(delim, argv[i+1]);
            i++;
        }
        //zistenie nazvu suboru
        if(i == argc-1){
            strcpy(file_name, argv[i]);
        }
        //zistenie prikazov na upravu
        if(i == argc-2){
            strcpy(cmd_sp, argv[i]);
        }
    }

    t_table table;
    table.count_line = 1;
    table.line = malloc(sizeof(t_line));
    if (table.line == NULL){
        fprintf(stderr,"\nmalloc error\n");
        return 1;   //error
    }
    FILE *tab;
    tab = fopen(file_name, "r");
    if (tab == NULL) {
        fprintf(stderr,"\nprazdny subor\n");
        return 1;   //error
    }
    int sign;
    char temp_bunk[200];
    int temp_count_collum =0;
    int dl = 0;
    while ((sign = fgetc(tab)) != EOF){
        if (sign == '\n'){
            if (table.last_bunk_number < temp_count_collum){
                table.last_bunk_number = temp_count_collum+1;
            }
            temp_count_collum = 0;
            table.count_line++;
            table.line = realloc(table.line, table.count_line * sizeof(t_line));
            if (table.line == NULL){
                fprintf(stderr,"\nmalloc error\n");
                return 1;   //error
            }
        }
        if (is_delim(delim, sign) == 1){
            strcpy(table.line[table.count_line-1].bunk[temp_count_collum].chars, temp_bunk);
            dl = 0;
            temp_count_collum ++;
        }else {
            // zapisat char do bunky
            temp_bunk[dl] = (char)sign;
            temp_bunk[dl+1] = 0;
            dl++;
        }
    }
    print (&table, delim);
    free(table.line);
    fclose(tab);
    return 0;
}
/* ********************************************************************************** */
//zistujem ci dany znak je delimiter
int is_delim(char delim[10], int sign){
    int temp;
    for (temp = 0; temp < (int)strlen(delim); temp++) {
        if (sign == delim[temp]){
            return 1;
        }
    }
    return 0;
}
//vypis tabulky
void print(t_table *table, char *delim) {
    for(int j = 0; j < table->count_line  ; ++j){
        for (int i = 0; i < table->last_bunk_number ; ++i) {
            if (i != 0){
                printf("%c", delim[0]);
            }
            printf("%s", table->line[j].bunk[i].chars);
        }
    }
    printf("\n");
}
/* ********************************************************************************** */
/* ********************************************************************************** */