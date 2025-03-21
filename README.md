# 5_IRC_Serv

## Description

Ce projet consiste à développer un serveur IRC (Internet Relay Chat) conforme aux spécifications du protocole IRC. L'objectif est de permettre à plusieurs clients de se connecter, de rejoindre des canaux, d'échanger des messages et d'interagir selon les commandes standard du protocole IRC.

## Fonctionnalités

- Gestion des connexions simultanées de multiples clients
- Création et gestion des canaux de discussion publics et privés
- Implémentation des commandes IRC (JOIN, PART, PRIVMSG, NICK...)
- Gestion des utilisateurs, pseudonymes et droits d'accès
- Échange de messages privés entre utilisateurs

## Prérequis

- Système d'exploitation : Linux ou macOS
- Compilateur C++ compatible avec le standard C++98

## Installation

1. Cloner le dépôt :

```
git clone https://github.com/qbnt/5_IRC_Serv.git
cd 5_IRC_Serv
```

2. Compiler le projet :

```
make
```

## Utilisation

- Lancer le serveur :

```
./irc_server <port> <password>
```

- Se connecter avec un client IRC :
  - Hôte : localhost ou adresse IP du serveur
  - Port : Port spécifié au lancement
  - Mot de passe : Mot de passe spécifié

- Commandes basiques :
  - Rejoindre un canal : `/join #nom_canal`
  - Message privé : `/msg pseudo message`
  - Changer de pseudo : `/nick nouveau_pseudo`


## Licence

Projet sous licence MIT. Voir le fichier [LICENSE](LICENSE).
