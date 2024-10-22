#include "nascimento.h"
#include <stdio.h>
#include <time.h>


int eh_bissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int dias_no_mes(int mes, int ano) {
    int dias[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mes == 2 && eh_bissexto(ano)) {
        return 29; 
    }
    return dias[mes - 1];
}

int dias_de_vida(data_t nasc) {
    time_t t = time(NULL);
    struct tm hoje = *localtime(&t);

    int dias_total = 0;

    for (int ano = nasc.ano; ano < hoje.tm_year + 1900; ano++) {
        dias_total += eh_bissexto(ano) ? 366 : 365;
    }

    for (int mes = nasc.mes; mes <= 12; mes++) {
        dias_total += dias_no_mes(mes, nasc.ano);
        if (mes == nasc.mes) {
            dias_total -= nasc.dia; 
        }
    }

    
    for (int mes = 1; mes < hoje.tm_mon + 1; mes++) {
        dias_total += dias_no_mes(mes, hoje.tm_year + 1900);
        if (mes == hoje.tm_mon + 1) {
            dias_total -= hoje.tm_mday; 
        }
    }

    return dias_total;
}
