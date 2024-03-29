/****************************************************/
/* File: parse.c                                    */
/* The parser implementation for the TINY compiler  */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

static TokenType token; /* holds current token */

/* function prototypes for recursive calls */
static TreeNode * stmt_sequence(void);
static TreeNode * statement(void);
static TreeNode * if_stmt(void);
static TreeNode * while_stmt(void);
static TreeNode * repeat_stmt(void);
static TreeNode * assign_stmt(void);
static TreeNode * read_stmt(void);
static TreeNode * write_stmt(void);
static TreeNode * switch_stmt(void);
static TreeNode * case_stmt(void);
static TreeNode * default_stmt(void);
static TreeNode * loop_stmt(void);
static TreeNode * exp(void);
static TreeNode * simple_exp(void);
static TreeNode * term(void);
static TreeNode * factor(void);



/*static void syntaxError(char * message)
*/
static void syntaxError(const char * message)

{ fprintf(listing,"\n--- ");
  fprintf(listing,"ERROR EN LA LINEA %d: %s",lineno,message);
  Error = TRUE;
}

static void match(TokenType expected)
{ if (token == expected) token = getToken();
  else {
    syntaxError("TOKEN INESPERADO MATCH-> ");
    printToken(token,tokenString);
    fprintf(listing,"      ");
  }
}

TreeNode * stmt_sequence(void)
{ TreeNode * t = statement();
  TreeNode * p = t;
  while ((token!=ENDFILE) && (token!=END) &&
         (token!=ELSE)  && (token!=UNTIL) )
  { TreeNode * q;
    match(SEMI);
    q = statement();
    if (q!=NULL) {
      if (t==NULL) t = p = q;
      else /* now p cannot be NULL either */
      { p->sibling = q;
        p = q;
      }
    }
  }
  return t;
}


TreeNode * statement(void)
{ TreeNode * t = NULL;
  switch (token) {
    case IF : t = if_stmt(); break;
    case REPEAT : t = repeat_stmt(); break;
    case ID : t = assign_stmt(); break;
    case READ : t = read_stmt(); break;
    case WRITE : t = write_stmt(); break;
    case SWITCH : t = switch_stmt(); break;
    case WHILE : t = while_stmt(); break;
     
    default : syntaxError("Token Inesperao Primo -> ");
              printToken(token,tokenString);
              token = getToken();
              break;
  } 
  return t;
}

TreeNode * while_stmt(void)
{ TreeNode * t = newStmtNode(WhileK);
  match(WHILE);
  if (t!=NULL) t->child[0] = exp();
  if (t!=NULL) t->child[1] = stmt_sequence();
  match(END);
  return t;
}

TreeNode * if_stmt(void)
{ TreeNode * t = newStmtNode(IfK);
  match(IF);
  if (t!=NULL) t->child[0] = exp();
  match(THEN);
  if (t!=NULL) t->child[1] = stmt_sequence();
  if (token==ELSE) {
    match(ELSE);
    if (t!=NULL) t->child[2] = stmt_sequence();
  }
  match(END);
  return t;
}

TreeNode * repeat_stmt(void)
{ TreeNode * t = newStmtNode(RepeatK);
  match(REPEAT);
  if (t!=NULL) t->child[0] = stmt_sequence();
  match(UNTIL);
  if (t!=NULL) t->child[1] = exp();
  return t;
}

TreeNode * assign_stmt(void)
{ TreeNode * t = newStmtNode(AssignK);
  if ((t!=NULL) && (token==ID))
    t->attr.name = copyString(tokenString);
  match(ID);
  match(ASSIGN);
  if (t!=NULL) t->child[0] = exp();
  return t;
}

TreeNode * read_stmt(void)
{ TreeNode * t = newStmtNode(ReadK);
  match(READ);
  if ((t!=NULL) && (token==ID))
    t->attr.name = copyString(tokenString);
  match(ID);
  return t;
}

TreeNode * write_stmt(void)
{ TreeNode * t = newStmtNode(WriteK);
  match(WRITE);
  if (t!=NULL) t->child[0] = exp();
  return t;
}

TreeNode * loop_stmt(void)
{ TreeNode * t = newStmtNode(LoopK);
   if(token == CASE)
    { 
      if (t!=NULL) t->child[0]= case_stmt();
      if (t!=NULL) t->child[1] = loop_stmt();
    }else //if(token == DEFAULT) NO DEBERIA DE LLEGAR HASTA AQUI
    {
      if (t!=NULL) t->child[0]=  default_stmt();
    }
return t;
}

TreeNode * switch_stmt(void)
{ TreeNode * t = newStmtNode(SwitchK);
  match(SWITCH);
  if (t!=NULL) t->child[0] = exp();
  
  if(token == CASE){
     if (t!=NULL) t->child[1] = loop_stmt();
    }else if(token == DEFAULT){
     if (t!=NULL) t->child[1]=  default_stmt();
    }
    else{
      if (t!=NULL) t->child[1]= loop_stmt();
    }
match(END);
  return t;
}

TreeNode * case_stmt(void)
{ TreeNode * t = newStmtNode(CaseK);
 
  match(CASE);
  if (t!=NULL) t->child[0] = exp();
  match(PUNTO);
  if (t!=NULL) t->child[1] = stmt_sequence();
  match(END);

return t;
}
TreeNode * default_stmt(void)
{ TreeNode * t = newStmtNode(DefaultK);

  match(DEFAULT);
  match(PUNTO);
  if (t!=NULL) t->child[0] = stmt_sequence();
  match(END);

return t;
}



TreeNode * exp(void)
{ TreeNode * t = simple_exp();
  if ((token==LT)||(token==EQ)) {
    TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
    }
    match(token);
    if (t!=NULL)
      t->child[1] = simple_exp();
  }
  return t;
}

TreeNode * simple_exp(void)
{ TreeNode * t = term();
  while ((token==PLUS)||(token==MINUS))
  { TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      t->child[1] = term();
    }
  }
  return t;
}

TreeNode * term(void)
{ TreeNode * t = factor();
  while ((token==TIMES)||(token==OVER))
  { TreeNode * p = newExpNode(OpK);
    if (p!=NULL) {
      p->child[0] = t;
      p->attr.op = token;
      t = p;
      match(token);
      p->child[1] = factor();
    }
  }
  return t;
}

TreeNode * factor(void)
{ TreeNode * t = NULL;
  switch (token) {
    case NUM :
      t = newExpNode(ConstK);
      if ((t!=NULL) && (token==NUM))
        t->attr.val = atoi(tokenString);
      match(NUM);
      break;
    case ID :
      t = newExpNode(IdK);
      if ((t!=NULL) && (token==ID))
        t->attr.name = copyString(tokenString);
      match(ID);
      break;
    case LPAREN :
      match(LPAREN);
      t = exp();
      match(RPAREN);
      break;
    default:
      syntaxError("unexpected token FACTOR-> ");
      printToken(token,tokenString);
      token = getToken();
      break;
    }
  return t;
}

/****************************************/
/* the primary function of the parser   */
/****************************************/
/* Function parse returns the newly 
 * constructed syntax tree
 */
TreeNode * parse(void)
{ TreeNode * t;
  
  token = getToken();
  t = stmt_sequence();
  
  if (token!=ENDFILE)
    syntaxError("Code ends before file\n");
  return t;
  
}
