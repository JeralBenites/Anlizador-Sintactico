#include "globals.h"

#define NO_PARSE FALSE  // 1.- HACE EL ANALISIS LEXICO
#define NO_ANALYZE TRUE
#define NO_CODE FALSE

#include "util.h"
#if NO_PARSE
	#include "scan.h"
#else
	#include "parse.h"
	#if !NO_ANALYZE
		#include "analyze.h"
		#if !NO_CODE
			#include "cgen.h"
		#endif
	#endif
#endif

/* allocate global variables */
int lineno = 0;
FILE * source;
FILE * listing;
FILE * code;

/* allocate and set tracing flags */
int EchoSource = TRUE;		// 2.- Hace eco (duplica) el programa fuente 
int TraceScan = TRUE;		// 3.- Presenta la información en cada token
int TraceParse = TRUE;
int TraceAnalyze = FALSE;
int TraceCode = FALSE;

int Error = FALSE;

int main( int argc, char * argv[] )
{ TreeNode * syntaxTree;
  char pgm[120]; /* source code file name */
  if (argc != 2)
    { fprintf(stderr,"usage: %s <filename>\n",argv[0]);
      exit(1);
    }
  strcpy(pgm,argv[1]) ;
  if (strchr (pgm, '.') == NULL)
     strcat(pgm,".JBG");
  source = fopen(pgm,"r");
  if (source==NULL)
  { fprintf(stderr,"File %s not found\n",pgm);
    exit(1);
  }
  listing = stdout; /* send listing to screen */
  fprintf(listing,"\nProgramando ...: %s\n\n",pgm);
  printf("Analizador Lexico\n\n");
#if NO_PARSE
  while (getToken()!=ENDFILE);
#else

  syntaxTree = parse();
  if (TraceParse) {
    printf("\nAnalizador Sintactico\n");
    fprintf(listing,"\nEl Arbolito :\n\n");
    printTree(syntaxTree);
  }
#if !NO_ANALYZE
  if (! Error)
  { if (TraceAnalyze) fprintf(listing,"\nBuilding Symbol Table...\n");
    buildSymtab(syntaxTree);
    if (TraceAnalyze) fprintf(listing,"\nChecking Types...\n");
    typeCheck(syntaxTree);
    if (TraceAnalyze) fprintf(listing,"\nType Checking Finished\n");
  }
#if !NO_CODE
  if (! Error)
  { char * codefile;
    int fnlen = strcspn(pgm,".");
    codefile = (char *) calloc(fnlen+4, sizeof(char));
    strncpy(codefile,pgm,fnlen);
    strcat(codefile,".jb");
    code = fopen(codefile,"w");
    if (code == NULL)
    { printf("Unable to open %s\n",codefile);
      exit(1);
    }
    codeGen(syntaxTree,codefile);
    fclose(code);
  }
#endif
#endif
#endif
  fclose(source);
  return 0;
}

