gestione_cpu: gestione_cpu.c Makefile 
	gcc -ansi -Wall -O gestione_cpu.c -o gestione_cpu
pulisci: 
	rm -f gestione_cpu.o 
