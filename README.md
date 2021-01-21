# esempio_eRPC

Piccolo esempio d'uso di eRPC, versione 1.8.0 (vedi anche https://gist.github.com/mazent/77718a8dbbc9554726ca4bcf00f9e068)

Il file `prova.erpc` contiene una minuscola interfaccia rpc: per generare i file usare `erpcgen`

La cartella `prova` implementa il client e il server in python con trasporto tcp.
La sottocartella `prog` contiene i file generati

La cartella `cpp` implementa il client e il server in C++ con trasporto seriale.
La sottocartella `prog` contiene i file generati mentre la `erpc_c` è quella della libreria meno i file inutili
