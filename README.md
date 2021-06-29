Specifiche di progetto

Si supponga di dover progettare un programma per la gestione dei dati delle CPU di un datacenter. Il
sistema di monitoraggio permette di rilevare, una volta all’ora per ogni CPU: la potenza richiesta (in [W]),
la temperatura del chip (in [oC]), il numero di processi attivi, la quantita di memoria RAM occupata (in
[MB]). L’intero log viene poi scritto (una volta al giorno) su un ﬁle in formato testo, secondo il seguente
formato (si assumano campi separati da tabulazione o spazio):
• Tempo: un numero intero ∈[1, 24] che rappresenta l’ora del giorno a cui si riferisce il rilevamento.
• CPU: un codice alfanumerico che risulta dalla concatenazione di tre lettere e tre numeri che identiﬁcano
la singola CPU.
• Potenza: un numero reale che rappresenta il consumo di potenza (medio) nell’ora di rilevamento.
• Temperatura: un numero reale che rappresenta la temperatura (media) nell’ora di rilevamento.
• Processi: un numero reale che rappresenta il numero (medio) di processi attivi nell’ora di rilevamen-
to.
• Memoria: un numero reale che rappresenta la quantita (media) di memoria RAM richiesta nell’ora di
rilevamento.

Ad esempio:

Tempo CPU Potenza Temperatura Processi Memoria
3 ABC020 8.36 32.70 23.7 10455.7
3 ABC176 9.24 22.43 3.70 12465.8
3 AAF184 10.11 32.14 11.20 20425.9
... ... ... ... ... ...
12 ABC020 4.60 30.43 20.1 12855.7
12 ABC176 12.24 24.55 3.70 265.8
12 AAF184 10.34 22.83 15.2 17523.8
... ... ... ... ... ...
21 ABC176 13.32 42.21 30.4 22585.5
... ... ... ... ... ...
Si scriva un programma ANSI C che esegue le seguenti elaborazioni:

1. Acquisisce il ﬁle e memorizza le relative informazioni in una struttura dati di tipo albero.
2. Ricerca e restituisce i dati relativi alle rilevazioni di una data CPU nel giorno. Ad esempio: se l’utente
chiede i dati relativi alla CPU ABC176, il programma deve restituire le informazioni contenute nella
righe corrispondenti:

Tempo CPU Potenza Temperatura Processi Memoria
3 ABC176 9.24 22.43 3.70 12465.8
12 ABC176 12.24 24.55 3.70 265.8
21 ABC176 13.32 42.21 30.4 22585.5
... ... ... ... ... ...

Il programma deve inoltre prevedere una modalita che implementa le stesse funzionalita utilizzando un
array al posto dell’albero.
Per quanto riguarda l’analisi teorica si deve fornire la complessita dell’algoritmo di ricerca per la versio-
ne basata su albero e per quella basata su array. Oltre all’analisi teorica della complessita si deve effettuare
uno studio sperimentale della stessa per le operazioni di ricerca. Come suggerimento si puo operare ge-
nerando un numero N di rilevazioni casuali (dove N rappresenta il numero di CPU monitorate). L’analisi
sperimentale deve quindi valutare la complessita al variare di N e confrontare l’algoritmo di ricerca che
lavora su albero con il corrispondente che lavora su array.
