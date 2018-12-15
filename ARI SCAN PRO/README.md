# C++ Port scanner

Application client / serveur contenant un programme client et un programme serveur. 

## Client

Les clients se connectent au serveur en fournissant l'adresse IP et le port d'écoute du serveur. 

## Serveur 

On commence par démarrer le serveur qui écoute sur un port spécifique. Le serveur récupère les adresses IP des clients connectés.

### Scan

Il est possible de lancer un scan en spécifiant la plage de ports à scanner puis consulter les résultats dans la zone prévue une fois le scan 
achevé. Les résultats se présentent sous cette forme (exemple avec trois clients connectés) : 

```
 * ------------------------------------------------------
 * Client       |  Port             | Etat              |
 * ------------------------------------------------------
 * 198.168.8.45 (Ports ouverts : 5  | Ports fermés : 4) |
 * ------------------------------------------------------
 *              |        5          |      OUVERT       |
 * ------------------------------------------------------
 *              |        6          |       FERME       |
 * ------------------------------------------------------
 * 198.168.8.45 (Ports ouverts : 5  | Ports fermés : 4) |
 * ------------------------------------------------------
 *              |        5          |      OUVERT       |
 * ------------------------------------------------------
 *              |        6          |       FERME       |
 * ------------------------------------------------------
 * 198.168.8.45 (Ports ouverts : 5  | Ports fermés : 4) |
 * ------------------------------------------------------
 *              |        5          |      OUVERT       |
 * ------------------------------------------------------
 *              |        6          |       FERME       |
 * ------------------------------------------------------
```


