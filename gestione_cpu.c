/**************************************************************************************************/
/* Programma per la stampa e la ricerca di valori legati ad una specifica CPU da un file di testo */
/**************************************************************************************************/

/*****************************/
/* Inclusione delle librerie */
/*****************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/********************************/
/* Dichiarazione strutture dati */
/********************************/

/* Struttura per salvataggio dei dati dal file */
typedef struct dati
{
    int    tempo;
    char   nome_cpu[6];
    double potenza;
    double temperatura;
    double processi;
    double memoria;
} data_t;

/* Struttura per la costruzione dell'albero*/
typedef struct nodo
{
    data_t valore;
    struct nodo *figlio_sx;
    struct nodo *figlio_dx;
} nodo_t;

/********************************/
/* Dichiarazione delle funzioni */
/********************************/

/* Funzione per inserimento del numero di CPU*/
int inserimento_numero_cpu();

/* Funzione per la generazione casuali dei valori del file */
void generazione_casuale_cpu(int);  /* Intero riferito al numero delle CPU nel file di testo */

/* Funzione per stampa del menu di selezione */
int messaggio ();

/* Funzione per puliza buffer nelle validazioni strette degli input */
void pulizia_buffer();

/**********************/
/* Funzioni per array */
/**********************/

/* Funzione per salvataggio dei dati nella struttura array */
void leggi_da_file_array(data_t [],     /* Struttura contenente i dati del file di testo */
                              int);	/* Intero riferito al numero delle CPU nel file di testo */ 

/* Funzione per la stampa dei file salvati nella struttura array */      
void stampa_array(data_t [], /* Struttura contenente i dati del file di testo */
		       int); /* Intero riferito al numero di dati presenti nel file di testo */

/* Funzione per la ricerca della CPU nella struttura array */	   
void cerca_elemento_array(data_t [], /* Struttura contenente i dati del file di testo */
                               int); /* Intero riferito al numero di dati presenti nel file di testo */

/***********************/
/* Funzioni per albero */
/***********************/

/* Funzione per acquisizione dati e salvataggio nell'albero */
nodo_t *leggi_da_file_alberi(nodo_t *); /* Nodo che fa riferimento alla radice dell'albero */

/* Funzione per creare nuovi nodi */							  
int aggiungi_nodo(nodo_t **,  /* Nuovo nodo che verrà allocato */
		        int,  /* Intero riferito al valore tempo del file di testo */
		      char*,  /* Stringa riferita al nome della CPU del file di testo */
		     double,  /* Double riferito al valore della potenza del file di testo */
		     double,  /* Double riferito al valore della temperatura del file di testo */
		     double,  /* Double riferito al valore dei processi del file di testo */
		    double);  /* Double riferito al valore della memoria del file di testo */

/* Funzione per la stampa dell'albero*/
void stampa_albero(nodo_t *); /* Nodo che fa riferimento alla radice dell'albero */

/* Funzione per ricerca della CPU nell'albero */								 
void cerca_in_albero(nodo_t *,  /* Nodo che fa riferimento alla radice dell'albero */
		       char *,  /* Stringa riferita al nome della CPU da cercare */
			 int);	/* Intero che identifica se la ricerca sia andata a buon fine o meno */		

/******************************/
/* Definizione delle funzioni */
/******************************/				  

/* Definizione della funzione main */
int main (void){
	
	/* Dichiarazione delle variabili locali alla funzione */
	int numero_cpu       = 0,     /* Intero riferito al numero di CPU nel file */
	    trovato          = 0,     /* Intero per controllo della ricerca della CPU per alberi */
            esito_selezione  = 0,     /* Intero per  selezione nel menu di scelta */
            esito_stringa    = 0;     /* Intero per controllo dell'input della CPU da cercare */
        char stringa[6];              /* Stringa avente sei spazi riferiti ai nomi che la CPU da cercare può assumere */
	data_t *array;                /* Array per l'acquisizione dei dati presenti nel file */
	nodo_t *radice       = NULL;  /* Radice dell'albero inizializzata a NULL*/

	    
	/* acquisizione del numero di CPU che saranno presenti nel file di testo */
	numero_cpu = inserimento_numero_cpu();

        /* Allocazione dello spazio necessario alla struttura array */
        array = malloc(numero_cpu*sizeof(data_t));

        /* Generazione casuale dei dati nel file di testo */
        generazione_casuale_cpu(numero_cpu);
		
	/* Inizio ciclo per validazione input delle selezione dell'utente */
        do{    
		printf("Vuoi selezionare la stampa e la ricerca per array o per alberi?\n");
                /* Acquisizione della selezione effettuata dall'utente */
	        esito_selezione = messaggio();
                if(esito_selezione != 0 && esito_selezione != 1 && esito_selezione != 2)
           		/* Messaggio in caso di input errato */
           		printf("Input non ammesso. Riprova...\n");
           	pulizia_buffer();
        }while(esito_selezione != 0 && esito_selezione != 1 && esito_selezione != 2);

	if(esito_selezione == 2){
        	printf("\nProgramma terminato...\n");
        }

	/* Inizio istruzione switch per utilizzo della struttura albero o array */
	switch(esito_selezione){
        /* Caso di utilizzo della struttura array */
    	case 0: 
                /* Vado a caricare la struttura array dei dati presenti nel file di testo */
    		leggi_da_file_array(array, numero_cpu);
    		printf("La stampa contenente la lista delle cpu e': \n\n");
                /* Stampo i dati precedentemente caricati */
    	   	stampa_array(array, numero_cpu); 
                /* Vado a cercare nella struttura array il nome della CPU inserita dall'utente nei dati acquisiti */
    	   	cerca_elemento_array(array, numero_cpu);
    	break;
    	case 1:
                /* Vado a creare l'albero partendo dalla radice */
    	   	radice = leggi_da_file_alberi(radice);
    	   	printf("La stampa contenente la lista delle cpu e': \n\n");
                /* Stampo i dati precedentemente caricati*/
    	   	stampa_albero(radice);

                /* Inizio ciclo di validazione per */
    	        do{
    	       		printf("Inserisci la CPU da ricercare: \n");
                	/* Acquisisco la stringa da cercare */
    	       		esito_stringa = scanf("%6s", stringa);
    	                if(esito_stringa != 1){
                        	/* Messaggio di errore */
    	                	printf("Input non ammesso. Riprova...\n");
    	                }
    	        	pulizia_buffer();
    	        }while(esito_stringa != 1);

		/* Vado a cercare nella struttura albero il nome della CPU inserita dall'utente nei dati acquisiti*/
    	        cerca_in_albero(radice, stringa, trovato);
    	break;
	}
	
	/* Valore di controllo restituito dalla funzione main al SO */
	return(0);
}

/* Funzione per l'acquisizione del numero delle CPU */
int inserimento_numero_cpu()
{

	/* Dichiarazione variabili locali alla funzione */
    	int numero_cpu   = 0,      /* Numero di CPU */
            esito_numero = 0;      /* Esito acquisizione input */

	/* Inizio ciclo per validazione input delle selezione dell'utente */
        do{
        	printf("Specificare il numero di CPU da inserire (>0):\n"); 
        	/* Acquisizione numero di CPU da inserire */
        	esito_numero = scanf ("%d", &numero_cpu);
        	pulizia_buffer();
        	if (esito_numero != 1 || numero_cpu <= 0)   
                	/* Messaggio di errore nel caso l'input non fosse valido */
                	printf ("ERRORE!! Inserire un numero maggiore di 0.\n\n");  
    	}while(esito_numero != 1 || numero_cpu <= 0);

	/* Ritorno del valore acquisito */
    	return(numero_cpu);  
}

/* Funzione per la generazione casuale dei dati */
void generazione_casuale_cpu(int numero_cpu)
{

	/* Dichiarazione variabili locali alla funzione */
    	FILE *lista_cpu             = NULL;                          /* Variabile puntatore al file lista_cpu  */
    	int i                       = 0,                             /* Variabile di lavoro per ciclo for */
            j                       = 0,                             /* Variabile di lavoro per ciclo for */
            tempo                   = 0;                             /* Variabile riferita al dato del tempo */
    	double potenza              = 0,                             /* Variabile riferita al dato della potenza*/
               temperatura          = 0,                             /* Variabile riferita al dato della temperatura */
               processi             = 0,                             /* Variabile riferita al dato dei processi */
               memoria              = 0;                             /* Variabile riferita al dato della memoria */
    	char nome_cpu[7]            = {0},                           /* Stringa che conterrà il nome della CPU */
             array_numeri_finale[4] = {0},                           /* Stringa che conterrà i valori generati casualmente */
             array_numeri[10]       = "0123456789",                  /* Stringa che contiene i possibili numeri selezionabili casualmente */
             array_lettere[27]      = "ABCDEFGHIJKLMNOPQRSTUWXYVZ";  /* Stringa che contiene le possibili lettere selezionabili casualmente*/

      	/* Apertura file in scrittura */
      	lista_cpu = fopen("lista_cpu.txt", "w");  

      	/* Seme per generazione valori casuali */
      	srand(time(NULL));  


      	/* Ciclo per la generazione dei dati casuali */
      	for(i = 0; i < numero_cpu; i++){ 
        	/* Generazione dell'intero tempo nello spazio [1, 24] */
        	tempo = 1 + rand() % 24;

        	/* Ciclo per creazione delle 3 lettere e delle 3 cifre numeriche */
        	for(j = 0; j < 3; j++){
        		/* Salvataggio nei primi tre posti di tre lettere casuali */
            		nome_cpu[j] = array_lettere[rand() % (sizeof(array_lettere)-1)];
            		/* Salvataggio nei primi tre posti di 3 cifre casuali*/
            		array_numeri_finale[j] = array_numeri[rand() % (sizeof(array_numeri)-1)];
        	}

        	/* Concatenazione delle tre cifre e tre lettere precedentemente generate nella stringa nome_cpu */
        	strcat(nome_cpu, array_numeri_finale);
        
        	/* Generazione casuale del valore della potenza */
        	potenza = ((rand()/(double)RAND_MAX) + (rand() % 30));
        	/* Generazione casuale del valore della temperatura */
        	temperatura = ((rand()/(double)RAND_MAX) + (rand() % 110));
        	/* Generazione casuale del valore dei processsi */
        	processi = ((rand()/(double)RAND_MAX) + (rand() % 50));
        	/* Generazione casuale del valore della memoria */
        	memoria = (double)rand() / 100;

        	/* Scrittura dei dati generati nel file di testo */
        	fprintf(lista_cpu, "%d %s %f %f %f %f\n", tempo,
                                                       nome_cpu,
                                                        potenza,
                                                    temperatura,
                                                       processi,
                                                       memoria);

		/* Pulizia delle ultime tre caselle della stringa cosi da poter ricaricare altri numeri casuali */
        	for(j = 3; j <= 5; j++)
        		nome_cpu[j] = '\0';
        }

	/* Stampa messaggio per scrittura andata a buon fine */
    	printf("Operazione terminata con successo. Generate %d CPU\n\n", numero_cpu);

    	/* Chiusura del file e salvataggio */
    	fclose(lista_cpu);  
}

/* Funzione per stampa del menu di scelta */
int messaggio ()
{

	/* Dichiarazione delle variabili locali alla funzione */
	int selezione;		/* Valore di tipo intero per la selezione dell'utente */
	int esito_lettura;	/* Valore che definisce la validazione dell'input  */

	/* Inizio ciclo di acquisizione e validazione input con stampa del menu */
	do{
		printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");	
		printf("\n* (Digitare: 0) Stampa e ricerca utilizzando la struttura di tipo array                   *");
		printf("\n* (Digitare: 1) Stampa e ricerca utilizzando la struttura di tipo albero                  *");
		printf("\n* (Digitare: 2) Per terminare il programma                                                *");
		printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
        	/* Acquisizione della selezione dell'utente */
		esito_lettura = scanf("%d", 
		                      &selezione);
		if((esito_lettura != 1) || (selezione > 2 || selezione < 0)){
            		/* Stampa messaggio di errore nel caso di input errato */
			printf("Input di selezione errato!\n");	
			while(getchar() != '\n');			
		}	
	}while((esito_lettura != 1) || (selezione > 2 || selezione < 0));
	
	/* Valore restituito dalla funzione */
	return (selezione);		
}

/* Funzione per il caricamento dei dati nella struttura array */
void leggi_da_file_array(data_t array[], int numero_cpu)
{

	FILE *lista_cpu;    /* Variabile puntatore al file lista_cpu  */
    	int i     = 0,      /* Variabile di lavoro per ciclo for */
            esito = 0;      /* Variabile per controllo esito fscanf */

    	/* Apertura del file di testo il lettura */
    	lista_cpu = fopen("lista_cpu.txt", "r");

    	/* Controllo se il file di testo è vuoto */
    	if (lista_cpu == NULL)
		/* Stampa messaggio di errore */
        	printf("Apertura FILE non riuscita...\n");  
    	else{
        	/* Ciclo per il caricamento dei dati nella struttura array */
        	for(i = 0; i < numero_cpu; i++)
            		/* Caricamento dato per dato nella struttura array, con validazione */
            		esito = fscanf(lista_cpu, "%d%s%lf%lf%lf%lf", &array[i].tempo,
                                          	                      array[i].nome_cpu,
		                                                      &array[i].potenza,
								      &array[i].temperatura,
								      &array[i].processi,
								      &array[i].memoria);
        	/* Gestione della variabile di ritorno della fscanf */
        	if(esito == EOF)
            	/* Messaggio di errore */
            	printf("Non riesco a leggere qualcosa: il file e' finito...\n");        
    	}
	
	/* Chiusura del file e salvataggio */
    	fclose(lista_cpu);

}

/* Funzione per la stampa dei dati contenuti nella struttra array */
void stampa_array(data_t array[], int n_righe)
{

	int i = 0;      /* Variabile di lavoro per ciclo for */

    	/* Ciclo for per la stampa di tutte le CPU presenti nel file di testo */
    	for(i = 0; i < n_righe; i++){
        	/* Stampa dei dati caricati nella struttura array */
       		 printf("TEMPO: %d\tCPU: %s\tPOTENZA: %.2lf\tTEMPERATURA: %.2lf\tPROCESSI: %.2lf\t\tMEMORIA: %.2lf\n\n", array[i].tempo,
                                          						   				 array[i].nome_cpu,
											                                 array[i].potenza,
															 array[i].temperatura,
															 array[i].processi,
															 array[i].memoria);	
   	}
}

/* Funzioner per la ricerca della CPU nella struttura array */
void cerca_elemento_array(data_t array[], int n_righe)
{
	
	int i             = 0;  /* Variabile di lavoro per passare tutti gli elementi della struttura array */
    	char ricerca[6];        /* Array per salvare la stringa cercata dall'utente */
    	int trovato       = 0,  /* Variabile per controllo dell'esito della ricerca */
    	    esito_ricerca = 0;  /* Variabile per il controllo dell'input da parte dell'utente */

    	/* Ciclo per la validazione dell'input nell'inserimento della stringa da cercare */
    	do{
    		printf("\nDigitare il nome della cpu che si vuole cercare: \n");
    		esito_ricerca = scanf("%6s", ricerca);;
    		if(esito_ricerca != 1){
            		/* Messaggio nel caso di errore */
    			printf("Input non ammesso. Riprova...\n"); 
    		}
    		pulizia_buffer();
	}while(esito_ricerca != 1);

    	/* Inizio ciclo per scorrimento celle array alla ricerca del valore richiesto */
    	for(i = 0; i < n_righe; i++){
        	/* Caso di corrispondenza della stringa richiesta dall'utente */
        	if((strcmp(array[i].nome_cpu, ricerca)) == 0){
            		/* Stampa della riga dove è presente la CPU richiesta */
            		printf("\nNella riga %d sono presenti:\n", i);
            		printf("TEMPO: %d\tCPU: %s\tPOTENZA: %.2lf\tTEMPERATURA: %.2lf\tPROCESSI: %.2lf\t\tMEMORIA: %.2lf\n", array[i].tempo,
                                                                                                                              array[i].nome_cpu,
                                                                                                                              array[i].potenza,
        									                                              array[i].temperatura,
        									                                              array[i].processi,
        									                                              array[i].memoria);
            	/* Variabile settata ad 1 grazie alla ricerca andata a buon fine */
            	trovato = 1;
        	}
    	}

	/* Caso in cui non si fosse trovata la CPU richiesta */
    	if(trovato == 0)
        	/* Stampa messaggio di errore */
        	printf("\nL'elemento non e' stato trovato...\n");
}

/* Funzione per il caricamento dei dati nella struttura albero */
nodo_t *leggi_da_file_alberi(nodo_t *radice)
{

	FILE *lista_cpu;     /* Variabile puntatore al file lista_cpu */
    	int tempo;           /* Variabile riferita al dato tempo */
    	char nome_cpu[6];    /* Variabile riferita al nome della CPU */
    	double potenza,      /* Variabile riferita al dato della potenza */
    	       temperatura,  /* Variabile riferita alla temperatura */
    	       processi,     /* Variabile riferita al dato dei processi */
    	       memoria;      /* Variabile riferita al dato della memoria */

    	/* Apertura del file in lettura */
    	lista_cpu = fopen("lista_cpu.txt", "r");

    	/* Caso in cui il file non esistesse */
    	if (lista_cpu == NULL)
        	printf("Apertura FILE non riuscita...\n");
    	else
    	{
        	/* Ciclo dove si vanno a prendere i dati e caricarli nodo per nodo finchè non si arriva alla fine del file di testo  */
        	while(fscanf(lista_cpu, "%d%s%lf%lf%lf%lf", &tempo, nome_cpu, &potenza, &temperatura, &processi, &memoria) != EOF){
            		/* Funzione che va ad aggiungere nodi con dentro i dati prensenti nelle righe del file di testo */
            		aggiungi_nodo(&radice, tempo, nome_cpu, potenza, temperatura, processi, memoria);
        	}
    	}

	/* Chiusura del file di testo lista_cpu*/
    	fclose(lista_cpu);

    	/* Ritorno della funzione che sarà la radice della struttura albero appena creato */
    	return(radice);
}

/* Funzione per la stampa della struttura albero */
void stampa_albero(nodo_t *radice)
{

	/* Se la radice non è vuota */
    	if(radice != NULL)
    	{
        	/* Stampa dell'albero a partire dai figli di sinistra */
        	stampa_albero(radice->figlio_sx);
        	printf("TEMPO: %d\tCPU: %s\tPOTENZA: %.2lf\tTEMPERATURA: %.1lf\tPROCESSI: %.2lf\tMEMORIA: %.2lf\n\n", radice->valore.tempo,
                                                                                                                      radice->valore.nome_cpu,
                                                                                                                      radice->valore.potenza,
														      radice->valore.temperatura,
														      radice->valore.processi,
														      radice->valore.memoria);
        	stampa_albero(radice->figlio_dx);
    	}
}

/* Funzione per aggiungere i nodi alla struttura albero */
int aggiungi_nodo(nodo_t **cella, int tempo, char nome_cpu[6], double potenza, double temperatura, double processi, double memoria)
{
	
	int ris = 0;    /* Variabile che indica il successo dell'inserimento dei dati */

    	/* Caso dove ancora non sia stato creato nulla */
    	if(*cella == NULL)
    	{
        	/* Si crea la struttura allocando la memoria necessaria e i relativi dati presenti nel file di testo */
        	*cella = (nodo_t *)malloc(sizeof(nodo_t));
        	(*cella)->valore.tempo = tempo;
        	(*cella)->valore.nome_cpu[0] = nome_cpu[0];
        	(*cella)->valore.nome_cpu[1] = nome_cpu[1];
        	(*cella)->valore.nome_cpu[2] = nome_cpu[2];
        	(*cella)->valore.nome_cpu[3] = nome_cpu[3];
        	(*cella)->valore.nome_cpu[4] = nome_cpu[4];
        	(*cella)->valore.nome_cpu[5] = nome_cpu[5];
        	(*cella)->valore.nome_cpu[6] = nome_cpu[6];
        	(*cella)->valore.potenza = potenza;
        	(*cella)->valore.temperatura = temperatura;
        	(*cella)->valore.processi = processi;
        	(*cella)->valore.memoria = memoria;
        	(*cella)->figlio_sx = (*cella)->figlio_dx = NULL;
        	/* Inserimento nella struttura avvenuta con successo */
        	ris = 1;
    	}
    	/* Comparazione della stringa da inserire con quella precedente valutando se è piu piccola */
    	else if(strcmp(nome_cpu, (*cella)->valore.nome_cpu) <= 0)
        	/* Se la nuova stringa è piu piccola verrà inserita nel nodo sinistro */
        	aggiungi_nodo(&(*cella)->figlio_sx, tempo, nome_cpu, potenza, temperatura, processi, memoria);
    	/* Comparazione della stringa da inserire con quella precedente valutando se è piu grande */
    	else if(strcmp(nome_cpu, (*cella)->valore.nome_cpu) > 0)
        	/* Se la nuova stringa è piu grande verrà inserita nel nodo di destra */
        	aggiungi_nodo(&(*cella)->figlio_dx, tempo, nome_cpu, potenza, temperatura, processi, memoria);
    
	/* Ritorno della funzione */
    	return(ris);
}

/* Funzione per la ricerca della stringa nella struttura albero */
void cerca_in_albero(nodo_t *radice, char *valore, int trovato)
{

	if(radice != NULL){
        	if(strcmp(valore, radice->valore.nome_cpu) == 0){ /* trovato elemento */
            	printf("TEMPO: %d\tCPU: %s\tPOTENZA: %.2f\tTEMPERATURA: %.1f\tPROCESSI: %.2f\t\tMEMORIA: %.2f\n", radice->valore.tempo,
                                                                                                                  radice->valore.nome_cpu,
                                                                                                                  radice->valore.potenza,
                                                                                                                  radice->valore.temperatura,
                                                                                                                  radice->valore.processi,
                                                                                                                  radice->valore.memoria);
            	trovato = 1;
            	cerca_in_albero(radice->figlio_sx, valore, trovato);
        	}else if(strcmp(valore, radice->valore.nome_cpu) < 0){
            		cerca_in_albero(radice->figlio_sx, valore, trovato);
        	}else
        		cerca_in_albero(radice->figlio_dx, valore, trovato);
    	}else{
        	if(trovato == 0)
            		printf("\nNome cpu non trovata...\n");
    	}
}

void pulizia_buffer()
{
	while(getchar() != '\n');
}
