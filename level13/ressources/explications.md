# level13

### Observations

##### Je decompile le programme '~/level13':
```c
char *__cdecl ft_des(char *s)
{
	unsigned int	i;
	int				v3;
	int				j;
	int				k;
	char			*v6;

	v6 = strdup(s);
	v3 = 0;
	for (i = 0; strlen(v6) > i; ++i)
	{
		if (v3 == 6)
			v3 = 0;
		if ((i & 1) != 0)
		{
			for (j = 0; "0123456"[v3] > j; ++j)
			{
				if (++v6[i] == 127)
					v6[i] = 32;
			}
		}
		else
		{
			for (k = 0; "0123456"[v3] > k; ++k)
			{
				if (--v6[i] == 31)
					v6[i] = 126;
			}
		}
		++v3;
	}
	return v6;
}

int __cdecl main(int argc, const char **argv, const char **envp)
{
	__uid_t	v3;
	char	*v4;

	if (getuid() != 4242)
	{
		v3 = getuid();
		printf("UID %d started us but we we expect %d\n", v3, 4242);
		exit(1);
	}
	v4 = ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I");
	return printf("your token is %s\n", v4);
}
```

##### Details du programme:
```bash
-rwsr-sr-x 1 flag13  level13 7303 Aug 30  2015 level13
```

##### Fonctionnement:
C'est un programme simple compose de deux fonctions:
 - La fonction \<main> qui execute la fonction \<ft_des> si l'utilisateur qui execute le programme a l'id 4242.
 - La fonction \<dt_des> qui decrypte une chaine de caracteres encryptee au format 'des'

##### Conclusions:
Le token que nous cherchons est directement present dans le code mais encrypte, \
il nous suffit d'isoler l'effet de la fonction \<ft_des> pour l'obtenir.

### Resolution
Je copie le programme en enlevant la securite qui verifie l'id utilisateur, ensuite je le compile, puis l'execute.

##### /tmp/decrypt.c :
```c
char	*ft_des(char *s)
{
	unsigned int	i;
	int				v3;
	int				j;
	int				k;
	char			*v6;

	v6 = strdup(s);
	v3 = 0;
	for (i = 0; strlen(v6) > i; ++i)
	{
		if (v3 == 6)
			v3 = 0;
		if ((i & 1) != 0)
		{
			for (j = 0; "0123456"[v3] > j; ++j)
			{
				if (++v6[i] == 127)
					v6[i] = 32;
			}
		}
		else
		{
			for (k = 0; "0123456"[v3] > k; ++k)
			{
				if (--v6[i] == 31)
					v6[i] = 126;
			}
		}
		++v3;
	}
	return v6;
}

void	main()
{
	char	*tok = ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I");
	printf("%s\n", tok);
	free(tok);
}
```

#### commandes:
```bash
cd /tmp
gcc decrypt.c
./a.out
```

**token :** 2A31L79asukciNyi8uppkEuSx