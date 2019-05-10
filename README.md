# AgencyProject
University PROG second project
***
#### PROGRAMA FEITO INTEIRAMENTE EM LINUX, NO EDITOR DE TEXTO
:point_right: sublime-text + Atom
#### COMPILACAO DE PROGRAMA
- Ter todos os ficheiros necessarios no mesmo directory e abrir um terminal nesse mesmo directory.
- Ficheiros necessarios: Agency.txt, Clients.txt, Packs.txt
- Comando usado para compilar:
        g++ -o test main.cpp    (se nao tiver g++, trate de o instalar)
- Comando usado para o abrir:
        ./test

#### OBSERVACOES  
- Se tiver a bugar algumas opcoes, ter em conta que eu nao testei infinitas vezes para ver se está tudo bem ou nao, se tiver alguns problemas(o que eu nao encontrei enquanto testava), inicialize ja com clientes e packs
- Nao usar NUNCA characters speciais no packs.txt e no clients.txt porque lixa-me o std::set(w), cada char especial ocupa 2 espacos..
        
#### BUGS
- As vezes encontro bugs a reescrever a morada depois de apagar ou adicionar clientes, ou entao bug a criar um cliente perfeito e diz aquele erro do bumped 0 nao sei que

#### MENU PROGRESS
- [x] menuClient
- [x] menuPack
- [x] menuInformation
  - [x] showClient
  - [x] showClients
  - [x] showTravelPack
  - [ ] showTravelPacks
    - [ ] showTravelPacksByPlace
    - [ ] showTravelPacksByDates
    - [ ] showTravelPacksByDatesAndPlace
    - [ ] showTravelPacksFromClient
    - [ ] showTravelPacksFromAllClients
- [x] buyTravelPacks
- [x] menuHelp
