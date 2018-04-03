#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern FILE *popen( const char *command, const char *modes);
extern int pclose(FILE *stream); 
void Sin();
void Cos();
double Taylor(double valor, int i);
double fatorial(double valor);