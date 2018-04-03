#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define GNUPLOT "gnuplot -persist"
#define NOF 125664 //termos a serem calculados para gerar 4PI de gráfico
#include "lib.h"



void Sin(){
	int i;
	FILE *file0, *file1, *gate;
	double arrayY[NOF];
	double s=0,x=0,errordx, errordy;

	file0=fopen("seno.dat", "wb");
	file1=fopen("seno.txt", "wb");
	gate=popen(GNUPLOT,"w");
	
	if (file0 == NULL) {
        printf("O arquivo para geracao do grafico nao pode ser criado\n");
   		exit(1);
    }


	for(i=0; i<NOF;i++){
		s=s+0.0001; // step do grau 360 = 6.28319
		x=x+0.0001; // valor eixo x
		
        arrayY[i]=Taylor(s,1);
		
        if(s>6.28) s=0;//360 graus- 2PI

		errordx = sin(x)- arrayY[i];
		if(errordx<0) errordx*=-1; //corrige dX negativo 
		
		errordy = errordx/arrayY[i];
		if(errordy<0) errordy*=-1; //corrige dY negativo

		//printf("sink: %lf\t", sin(k));
		//printf("k:%.5lf\t array[i]:%lf\t dx:%lf\t dy:%lf\n", k, array[i], errordx, errordxy);
		
		fprintf(file0,"%lf\t %lf\t  %lf\t %lf\n",x,arrayY[i], errordx, errordy);
		fprintf(file1,"%lf %lf\n",x,arrayY[i]);
	}
	fprintf(gate, "set terminal png size 720,480\n");
    fprintf(gate, "set title'seno'\n");
    fprintf(gate, "set xlabel'eixo X'\n");
    fprintf(gate, "set ylabel'eixo Y'\n");
    fprintf(gate, "set output'seno.png'\n");
    fprintf(gate, "plot'seno.txt' title'Gráfico Seno' with lines\n");
	fclose(file0);
	fclose(file1);
	pclose(gate);

}

void Cos(){
	int i;
	FILE *file0, *file1, *gate;
	double arrayY[NOF];
	double s=0,x=0,errordx, errordy;

	file0=fopen("cosseno.dat", "wb");
	file1=fopen("cosseno.txt", "wb");
	gate=popen(GNUPLOT,"w");
	
	if (file0 == NULL){
        printf("O arquivo para geracao do grafico nao pode ser criado\n");
   		exit(1);
    }

	for(i=0; i<NOF;i++){
		s=s+0.0001; // step do grau 360 = 6.28319
		x=x+0.0001; // valor eixo x
		arrayY[i]=Taylor(s,0); //valor eixo y
		if(s>6.28) s=0;
		
		errordx= cos(s)- arrayY[i];
		if(errordx<0) errordx*=-1;
		
		errordy= errordx/arrayY[i];
		if(errordy<0) errordy*=-1;
		
		fprintf(file0,"%lf\t %lf\t  %lf\t %lf\n",x,arrayY[i], errordx, errordy);
		fprintf(file1,"%lf %lf\n",x,arrayY[i]);
	}
	fprintf(gate, "set terminal png size 720,480\n");
    fprintf(gate, "set title'cosseno'\n");
    fprintf(gate, "set xlabel 'eixo X'\n");
    fprintf(gate, "set ylabel 'eixo Y'\n");
    fprintf(gate, "set output'cosseno.png'\n");
    fprintf(gate, "plot'cosseno.txt' title'Gráfico Cosseno' with lines\n");
	fclose(file0);
	fclose(file1);
	pclose(gate);

}

double Taylor(double val, int i){
	double sign=-1, fat, result = 0;
	if (i == 0){
		for(i=i;i<=22;i=i+2){
			if (i==0){
				result = 1;
			} else{
				fat = fatorial(i);
				result+=(pow(val,i)/fat)*sign;
				sign=sign*(-1);
			}
		}
	}
	if (i == 1){
		for(i=i;i<=22;i=i+2){
			fat = fatorial(i);
			result-=(pow(val,i)/fat)*sign;
			sign=sign*(-1);
		}
	}
	return result;
}

double fatorial(double val){
	unsigned long int i;
	double result=1;

	for(i=0;i<val;i++) 
	result*=(val-i);

	return result;
}