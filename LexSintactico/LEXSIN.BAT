set PATH=C:\Borland\BCC55\Bin
bcc32 -eJB_LEXSIN main.c util.c scan.c parse.c symtab.c analyze.c code.c cgen.c 

JB_LEXSIN Prueba.JBG > LEXSIN.txt
LEXSIN.txt