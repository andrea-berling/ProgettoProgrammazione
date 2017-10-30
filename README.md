# Alma Mater

Alma Mater e' un gioco rougelike sviluppato come progetto per l'esame di Programmazione presso l'universita' di Bologna,
creato da Andrea Berlingieri, Giacomo Puligheddu e Riccardo Bellelli.

## How to play

Per giocare e' necessario innanzitutto compilare il progetto. Come dipendenze necessarie vi sono la libreria ncurses.h e
la libreria boost. Su alcuni sistemi potrebbe essere necessaria la libreria libtinfo.so.

Per compilare e' necessario il compilatore `gcc` e il programma `make`. Per compilare il gioco e' sufficiente fare un
`make` nella cartella del progetto. Verra' prodotto un eseguibile dal nome `AlmaMater`. Con `make clean` e' possibile
rimuovere l'eseguibile e la cartella `build` di object files.

### libtinfo

Su alcuni sistemi potrebbe essere necessario il linking esplicito alla libreria libtinfo. Su altri sistemi tale linking
esplicito potrebbe essere non necessario, e potrebbe invece dare problemi. In tal caso e' sufficiente rimuovere dal
makefile l'opzione `-ltinfo` nella variabile `CFLAGS`.
