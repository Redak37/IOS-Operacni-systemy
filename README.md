# [IOS] Operační systémy
## 2017/18 - 2. semestr
### Projekt 1 - 15/15 bodů
Cílem úlohy je vytvořit skript (tzv. wrapper), který bude spouštět textový editor.
Skript si bude pamatovat, které soubory byly v jakém adresáři prostřednictvím
skriptu wedi editovány. Pokud bude skript spuštěn bez parametrů, vybere skript
soubor, který má být editován.
Specifikace chování skriptu
JMÉNO

• wedi - wrapper textového editoru s možností automatického výběru souboru

POUŽITÍ

• wedi SOUBOR

• wedi [ADRESÁŘ]

• wedi -m [ADRESÁŘ]

• wedi -l [ADRESÁŘ]

• wedi -b|-a DATUM [ADRESÁŘ]

POPIS

• Pokud byl skriptu zadán soubor, bude editován.

• Pokud zadaný argument odpovídá existujícímu adresáři, skript z daného
adresáře vybere soubor pro editaci. Výběr souboru je následující.

– Pokud bylo v daném adresáři editováno skriptem více souborů, vybere
se soubor, který byl pomocí skriptu editován jako poslední. Editací
souboru se myslí třeba i prohlížení jeho obsahu pomocí skriptu (tj.
není nutné, aby byl soubor změněn).

– Pokud byl zadán argument -m, vybere se soubor, který byl pomocí
skriptu editován nejčastěji.

– Pokud nebyl v daném adresáři editován ještě žádný soubor, jedná se
o chybu.

• Pokud nebyl zadán adresář, předpokládá se aktuální adresář.

• Skript dokáže také zobrazit seznam všech souborů (argument -l), které
byly v daném adresáři editovány.

• Pokud byl zadán argument -b resp. -a (before, after), skript zobrazí
seznam souborů, které byly editovány před resp. po zadaném datu v čase
00:00:00.0 včetně. DATUM je formátu YYYY-MM-DD.
NASTAVENÍ A KONFIGURACE

• Skript si pamatuje informace o svém spouštění v souboru, který je dán
proměnnou WEDI_RC. Formát souboru není specifikován.

1

– Pokud není proměnná nastavena, jedná se o chybu.

– Pokud soubor na cestě dané proměnnou WEDI_RC neexistuje, soubor
bude vytvořen včetně cesty k danému souboru (pokud i ta neexistuje).

• Skript spouští editor, který je nastaven v proměnné EDITOR. Pokud není
proměnná EDITOR nastavená, respektuje proměnnou VISUAL. Pokud ani ta
není nastavená, použije se příkaz vi.

NÁVRATOVÁ HODNOTA

• Skript vrací úspěch v případě úspěšné operace nebo v případě úspěšné
editace. Pokud editor vrátí chybu, skript vrátí stejný chybový návratový
kód. Interní chyba skriptu bude doprovázena chybovým hlášením.

POZNÁMKY

• Skript nebere v potaz soubory, se kterými dříve počítal a které jsou nyní
smazané.

• Při rozhodování relativní cesty adresáře je doporučené používat reálnou
cestu (realpath). Důvod např.:

$ wedi .

$ wedi ‘pwd‘

Implementační detaily

• Skript by měl mít v celém běhu nastaveno POSIXLY_CORRECT=yes.

• Skript by měl běžet na všech běžných shellech (dash, ksh, bash). Můžete
použít GNU rozšíření pro sed či awk. Jazyk Perl nebo Python povolen
není.

• Skript by měl ošetřit i chybový případ, že na daném stroji utilita realpath
není dostupná.

• Referenční stroj neexistuje. Skript musí běžet na běžně dostupných OS
GNU/Linux a *BSD. Ve školním prostředí máte k dispozici počítače v
laboratořích (CentOS), stroj merlin (CentOS) a eva (FreeBSD). Pozor, na
stroji merlin je shell /bin/ksh symbolický odkaz na bash (tj. nechová se
jako Korn shell jako na obvyklých strojích).

• Skript nesmí používat dočasné soubory. Povoleny jsou dočasné soubory
nepřímo tvořené příkazem sed (např. argument sed -i).

Příklady použití

Následující příklady předpokládají, že skript wedi je dostupný v jedné z cest v
proměnné PATH.

1. Editace různých souborů:

$ export WEDI_RC=$HOME/.config/wedirc

$ date

Mon 2 Mar 14:45:24 CET 2018

$ wedi ~/.bashrc

$ wedi ~/.ssh/config

$ wedi ~/.local/bin/wedi

$ wedi ~/.bashrc

$ wedi ~/.indent.pro

$ date

Wed 4 Mar 19:51:02 CET 2018

$ wedi ~/.bashrc

$ wedi ~/.vimrc

2. Opětovná editace:

$ cd ~/.ssh

$ wedi

... spustí se editace souboru ~/.ssh/config

$ wedi ~

... spustí se editace souboru ~/.vimrc

$ cd

$ wedi -m

... spustí se editace souboru ~/.bashrc

3. Zobrazení seznamu editovaných souborů:

$ wedi -l $HOME

.bashrc

.indent.pro

.vimrc

$ wedi -b 2018-03-04 $HOME

.bashrc

.indent.pro

$ wedi -a 2018-03-03 $HOME

.bashrc

.vimrc


### Projekt 2 - 13/15 bodů
A. Popis úlohy Implementujte v jazyce C modifikovaný synchronizační problém The Senate Bus Problem. Osoby (riders) přicházejí postupně na zastávku a čekají na autobus (bus). V okamžiku příjezdu autobusu nastoupí všechny čekající osoby. Kapacita autobusu je limitována. Pokud je na nástupišti více osob, než je kapacita autobusu, čekají osoby, které se již do autobusu nevešly, na další autobus. Pokud stojí na zastávce autobus a nastupují osoby přítomné na zastávce, další příchozí osoby vždy čekají na další autobus. Po nastoupení osob autobus odjíždí. Pokud při příjezdu na zastávku nikdo nečeká, autobus odjíždí prázdný. Příklad: Kapacita autobusu je 10, čekajících osob je 8. Přijíždí autobus, osoby nastupují, přicházejí další 3 osoby. Nastoupí pouze 8 čekajících osob, autobus odjíždí a nově příchozí 3 osoby čekají na zastávce. B. Podrobná specifikace úlohy Spuštení ˇ $ ./proj2 R C ART ABT kde • R je počet procesu˚ riders; A > 0. • C je kapacita autobusu; C > 0. • ART je maximální hodnota doby (v milisekundách), po které je generován nový proces rider; ART >= 0 && ART <= 1000. • ABT je maximální hodnota doby (v milisekundách), po kterou proces bus simuluje jízdu; ABT >= 0 && ABT <= 1000. • Všechny parametry jsou celá čísla. Implementační detaily • Pracujte s procesy, ne s vlákny. • Každé osobě odpovídá jeden proces rider. • Autobus je reprezentován procesem bus. V systému je právě jeden autobus. • Hlavní proces vytváří ihned po spuštění jeden proces bus a jeden pomocný proces pro generování procesu˚ rider. Poté čeká na ukončení všech procesu, které aplikace vytváří. Jakmile jsou tyto procesy ukončeny, ukončí se i hlavní proces s kódem (exit code) 0. • Generování procesu˚ – rider: pomocný proces generuje procesy pro osoby; každý nový proces je generován po uplynutí náhodné doby z intervalu <0, ART>; celkem vygeneruje R procesu. Pokud platí ART==0, všechny příslušné procesy se vygenerují ihned. – Každý proces rider bude interně identifikován celým číslem I, začínajícím od 1. Císelná ˇ řada je pro každou kategorii procesu zvlášt’. – Postupně tedy vznikne hlavní proces, jeden pomocný proces, R procesu osob rider a jeden proces bus. 1 • Každý proces bus i rider vykonává své akce a současně zapisuje informace o akcích do souboru s názvem proj2.out. Součástí výstupních informací o akci je pořadové číslo A prováděné akce (viz popis výstupu). Akce se číslují od jedničky. • Použijte sdílenou pamět’ pro implementaci čítače akcí a sdílených proměnných nutných pro synchronizaci. • Použijte semafory pro synchronizaci procesu. • Nepoužívejte aktivní čekání (včetně cyklického časového uspání procesu) pro účely synchronizace. Chybové stavy • Pokud některý ze vstupu nebude odpovídat o čekávanému formátu nebo bude mimo povolený rozsah, program vytiskne chybové hlášení na standardní chybový výstup, uvolní všechny dosud alokované zdroje a ukončí se s kódem (exit code) 1. Popis procesu a jejich výstupů˚ Poznámka k výstupum˚ • A je pořadové číslo prováděné akce, • NAME je zkratka kategorie příslušného procesu, tj. BUS pro bus a RID pro rider, • I je interní identifikátor procesu v rámci příslušné kategorie, • CR je počet procesu˚ rider aktuálně přítomných na zastávce, • při vyhodnocování výstupu budou ignorovány mezery a tabelátory. Proces bus

Po spuštění tiskne A: NAME: start

Proces přijíždí na zastávku. Po příjezdu tiskne A: NAME: arrival. Po příjezdu autobusu na zastávku nemohou nově příchozí procesy rider vstoupit na zastávku a čekají na odjezd autobusu.

Nastupování do autobusu a odjezd (a) Pokud jsou na zastávce osoby (procesy rider) – tiskne A: NAME: start boarding: CR a čeká na nastoupení osob. Jakmile je naplněna kapacita autobusu, příp. již nikdo nemuže nastoupit, tiskne A: NAME: end boarding: CR a odjíždí. (b) Pokud na zastávce nikdo není, autobus odjíždí ihned.

Těsně před odjezdem tiskne A: NAME: depart

Proces simuluje jízdu tak, že se uspí na náhodnou dobu z intervalu <0, ABT> a poté tiskne A: NAME: end. Pokud platí ABT==0, proces se neuspí.

Celý cyklus se opakuje od bodu 2 dokud není splněna podmínka ukončení.

Podmínka ukončení: všechny procesy rider již byly vygenerovány a žádný proces rider nečeká na zastávce ani na vstup na zastávku.

Po splnění podmínky ukončení tiskne proces A: NAME: finish a ukončí se. 2 Proces rider

Po spuštění tiskne A: NAME I: start

Pokud je na zastávce autobus, čeká na jeho odjezd a poté vstoupí na zastávku. Jinak vstoupí na zastávku ihned.

Ihned po vstupu na zastávku tiskne A: NAME I: enter: CR (do CR se započítá i tento proces) a čeká na autobus.

Při vstupování do autobusu tiskne A: NAME I: boarding

Po ukončení jízdy autobusu (= proces bus vytiskl zprávu ...end) se proces ukončí, před ukon- čením tiskne A: NAME I: finish C. Podmínky vypracování Obecné informace • Projekt implementujte v jazyce C. Komentujte zdrojové kódy, programujte přehledně. Součástí hodnocení bude i kvalita zdrojového kódu. • Kontrolujte, zda se všechny procesy ukončují korektně a zda při ukončování správně uvolnujete ˇ všechny alokované zdroje . • Dodržujte syntax zadaných jmen, formát souboru a formát výstupních dat. Použijte základní skript pro ověření korektnosti výstupního formátu (dostupný z webu se zadáním). Informace o skriptu jsou uvedeny v komentáři skriptu. • Dotazy k zadání: Veškeré nejasnosti a dotazy řešte pouze prostřednictvím diskuzního fóra k projektu 2. Překlad • Pro překlad používejte nástroj make. Součástí odevzdání bude soubor Makefile. • Překlad se provede příkazem make v adresáři, kde je umístěn soubor Makefile. • Po překladu vznikne spustitelný soubor se jménem proj2, který bude umístěn ve stejném adresáři jako soubor Makefile • Zdrojové kódy překládejte s přepínači -std=gnu99 -Wall -Wextra -Werror -pedanti

• Pokud to vaše řešení vyžaduje, lze přidat další přepínače pro linker (např. kvuli semaforům). Odevzdání • Součástí odevzdání budou pouze soubory se zdrojovými kódy (*. , *.h) a soubor Makefile. Tyto soubory zabalte pomocí nástoje zip do archivu s názvem proj2.zip. • Archiv vytvořte tak, aby po rozbalení byl soubor Makefile umístěn ve stejném adresáři, jako je archiv. • Archiv proj2.zip odevzdejte prostřednictvím informačního systému, termín Projekt 2. • Pokud nebude dodržena forma odevzdání nebo projekt nepujde přeložit, bude projekt hodnocen 0 body. • Archiv odevzdejte pomocí informačního systému v dostatečném předstihu (odevzdaný soubor mužete před vypršením termínu snadno nahradit jeho novější verzí, kdykoliv budete potřebovat).
