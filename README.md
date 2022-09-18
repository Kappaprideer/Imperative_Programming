# Imperatywne

Aby skompilować program/ To comile a file: 
gcc -std=gnu11 -O2 -Wall -Wconversion -o nazwa_programu nazwa_pliku.c -lm

Alias:
alias g='function _g(){ name="$(echo $1 | cut -d '.' -f1)"; gcc -std=gnu11 -O2 -Wall -Wconversion $1 -o $name -lm && ./$name; rm $name; };_g'
