/*
** $Id: llex.h,v 1.79.1.1 2017/04/19 17:20:42 roberto Exp $
** Lexical Analyzer
** See Copyright Notice in lua.h
*/

#ifndef llex_h
#define llex_h

#include "lobject.h"
#include "lzio.h"


#define FIRST_RESERVED	257


#if !defined(LUA_ENV)
#define LUA_ENV		"_ENV"
#endif


/*
* WARNING: if you change the order of this enumeration,
* grep "ORDER RESERVED"
*/
enum RESERVED {
  /* terminal symbols denoted by reserved words */
  TK_AUTO = FIRST_RESERVED, TK_BREAK, TK_CONTINUE,
  TK_DO, TK_ELSE, TK_FALSE, TK___FILE__, TK_FOR, TK_FUNCTION,
  TK_GOTO, TK_IDIV, TK_IF, TK_IN, TK_LET, TK___LINE__, TK_LOCAL, TK_NIL,
  TK_RETURN, TK_TRUE, TK_VAR, TK_WHILE,
  /* other terminal symbols */
  TK_AND, TK_NOT, TK_OR, TK_POW,
  TK_CONCAT, TK_DOTS, TK_EQ, TK_GE, TK_LE, TK_NE,
  TK_CADD, TK_CSUB, TK_CMUL, TK_CDIV, TK_CMOD, TK_CCONCAT, 
  TK_PLUSPLUS, TK_MINUSMINUS,
  TK_SHL, TK_SHR,
  TK_ARROW, TK_DBCOLON, TK_EOS,
  TK_FLT, TK_INT, TK_NAME, TK_STRING
};

/* number of reserved words */
#define NUM_RESERVED	(cast(int, TK_WHILE-FIRST_RESERVED+1))


typedef union {
  lua_Number r;
  lua_Integer i;
  TString *ts;
} SemInfo;  /* semantics information */


typedef struct Token {
  int token;
  SemInfo seminfo;
} Token;


/* state of the lexer plus state of the parser when shared by all
   functions */
typedef struct LexState {
  int current;  /* current character (charint) */
  int linenumber;  /* input line counter */
  int lastline;  /* line of last token 'consumed' */
  Token t;  /* current token */
  Token lookahead;  /* look ahead token */
  struct FuncState *fs;  /* current function (parser) */
  struct lua_State *L;
  ZIO *z;  /* input stream */
  Mbuffer *buff;  /* buffer for tokens */
  Table *h;  /* to avoid collection/reuse strings */
  struct Dyndata *dyd;  /* dynamic structures used by the parser */
  TString *source;  /* current source name */
  TString *envn;  /* environment variable name */
} LexState;


LUAI_FUNC void lxx_init (lua_State *L);
LUAI_FUNC void lxx_setinput (lua_State *L, LexState *ls, ZIO *z,
                              TString *source, int firstchar);
LUAI_FUNC TString *lxx_newstring (LexState *ls, const char *str, size_t l);
LUAI_FUNC void lxx_next (LexState *ls);
LUAI_FUNC int lxx_lookahead (LexState *ls);
LUAI_FUNC l_noret lxx_syntaxerror (LexState *ls, const char *s);
LUAI_FUNC const char *lxx_token2str (LexState *ls, int token);


#endif
