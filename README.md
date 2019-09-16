# Lex_Sintactico_C


Programando ...: Prueba.JBG

Analizador Lexico
```C
   1: _/           __          
   2: _/    __ ___/  |________ 
   3: _/   |  |  \   __\___ _ \ 
   4: _/   |  |  /|  |  |  |_> >
   5: _/   |____/ |__|  |   __/ 
   6: _/                |__|  
   7: _/
   8:   _AÑADIENDO 
   9:   _SWITCH Y
  10:   _CASE
  11: 
  12: { Operaciones Basicas 
  13:   entre dos numeros 
  14:   con switch y case
  15: 
  16:   op-> suma=+
  17:        resta=-
  18:        multi=*
  19:        divi=/
  20: }
  21:  
  22:  x:=4;
	22: ID, name= x
	22: :=
	22: NUM, val= 4
	22: ;
  23:  y:=3;
	23: ID, name= y
	23: :=
	23: NUM, val= 3
	23: ;
  24:  op:=divi;
	24: ID, name= op
	24: :=
	24: ID, name= divi
	24: ;
  25: 
  26: switch (op) 
	26: Palabra Reservada: switch
	26: (
	26: ID, name= op
	26: )
  27:       case suma . resu:=x+y;
	27: Palabra Reservada: case
	27: ID, name= suma
	27: .
	27: ID, name= resu
	27: :=
	27: ID, name= x
	27: +
	27: ID, name= y
	27: ;
  28:                   write resu
	28: Palabra Reservada: write
	28: ID, name= resu
  29:                   end
	29: Palabra Reservada: end
  30:       case resta . if op=resta then
	30: Palabra Reservada: case
	30: ID, name= resta
	30: .
	30: Palabra Reservada: if
	30: ID, name= op
	30: =
	30: ID, name= resta
	30: Palabra Reservada: then
  31:                    resu:=x-y;
	31: ID, name= resu
	31: :=
	31: ID, name= x
	31: -
	31: ID, name= y
	31: ;
  32:                    write resu
	32: Palabra Reservada: write
	32: ID, name= resu
  33:                    end
	33: Palabra Reservada: end
  34:                    end
	34: Palabra Reservada: end
  35:       case multi . while(op=multi)
	35: Palabra Reservada: case
	35: ID, name= multi
	35: .
	35: Palabra Reservada: while
	35: (
	35: ID, name= op
	35: =
	35: ID, name= multi
	35: )
  36:                    resu:=x*y;
	36: ID, name= resu
	36: :=
	36: ID, name= x
	36: *
	36: ID, name= y
	36: ;
  37:                    write resu
	37: Palabra Reservada: write
	37: ID, name= resu
  38:                    end
	38: Palabra Reservada: end
  39:                    end
	39: Palabra Reservada: end
  40:       case divi . resu:=x/y;
	40: Palabra Reservada: case
	40: ID, name= divi
	40: .
	40: ID, name= resu
	40: :=
	40: ID, name= x
	40: /
	40: ID, name= y
	40: ;
  41:                   write resu
	41: Palabra Reservada: write
	41: ID, name= resu
  42:                   end
	42: Palabra Reservada: end
  43:                   case suma . resu:=x+y;
	43: Palabra Reservada: case
	43: ID, name= suma
	43: .
	43: ID, name= resu
	43: :=
	43: ID, name= x
	43: +
	43: ID, name= y
	43: ;
  44:                   write resu
	44: Palabra Reservada: write
	44: ID, name= resu
  45:                   end
	45: Palabra Reservada: end
  46:       default . write error 
	46: Palabra Reservada: default
	46: .
	46: Palabra Reservada: write
	46: ID, name= error
  47:                  end
	47: Palabra Reservada: end
  48: 
  49: end	50: Palabra Reservada: end
	51: EOF
```
Analizador Sintactico

El Arbolito :
```txt
  Assign to: x
    Const: 4
  Assign to: y
    Const: 3
  Assign to: op
    Id: divi
  Switch
    Id: op
    Dando Vueltas
      Case
        Id: suma
        Assign to: resu
          Op: +
            Id: x
            Id: y
        Write
          Id: resu
      Dando Vueltas
        Case
          Id: resta
          If
            Op: =
              Id: op
              Id: resta
            Assign to: resu
              Op: -
                Id: x
                Id: y
            Write
              Id: resu
        Dando Vueltas
          Case
            Id: multi
            While
              Op: =
                Id: op
                Id: multi
              Assign to: resu
                Op: *
                  Id: x
                  Id: y
              Write
                Id: resu
          Dando Vueltas
            Case
              Id: divi
              Assign to: resu
                Op: /
                  Id: x
                  Id: y
              Write
                Id: resu
            Dando Vueltas
              Case
                Id: suma
                Assign to: resu
                  Op: +
                    Id: x
                    Id: y
                Write
                  Id: resu
              Dando Vueltas
                Default
                  Write
                    Id: error
 ```
