/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_DAS2_YY_DS2_PARSER_HPP_INCLUDED
# define YY_DAS2_YY_DS2_PARSER_HPP_INCLUDED
/* Debug traces.  */
#ifndef DAS2_YYDEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define DAS2_YYDEBUG 1
#  else
#   define DAS2_YYDEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define DAS2_YYDEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined DAS2_YYDEBUG */
#if DAS2_YYDEBUG
extern int das2_yydebug;
#endif
/* "%code requires" blocks.  */

    #include "daScript/misc/platform.h"
    #include "daScript/ast/ast.h"
    #include "daScript/ast/ast_generate.h"
    #include "daScript/ast/ast_expressions.h"

    #include "parser_state.h"

#if defined(_MSC_VER) && !defined(__clang__)
    #if !defined(_DEBUG)
        #pragma optimize( "", off )
        #pragma optimize( "s", on )
    #endif
#endif

    enum {
        CorM_COPY   = 0,
        CorM_MOVE   = (1<<0),
        CorM_CLONE  = (1<<1)
    };

    enum {
        CorS_Struct = 0,
        CorS_Class  = 1,
        CorS_StructTemplate = 2,
        CorS_ClassTemplate  = 3
    };

    using namespace das;

    #include "parser_impl.h"

    LineInfo tokAt ( yyscan_t scanner, const struct DAS2_YYLTYPE & li );
    LineInfo tokRangeAt ( yyscan_t scanner, const struct DAS2_YYLTYPE & li, const struct DAS2_YYLTYPE & lie );

    struct TypePair {
        TypeDecl * firstType;
        TypeDecl * secondType;
    };

    struct EnumPair {
        string name;
        ExpressionPtr expr = nullptr;
        LineInfo at;
        EnumPair ( string * n, Expression * e, const LineInfo & l )
            : name(*n), expr(e), at(l) {};
        EnumPair ( string * n, const LineInfo & l )
            : name(*n), expr(nullptr), at(l) {};
    };


/* Token kinds.  */
#ifndef DAS2_YYTOKENTYPE
# define DAS2_YYTOKENTYPE
  enum das2_yytokentype
  {
    DAS2_YYEMPTY = -2,
    DAS2_YYEOF = 0,                /* "end of file"  */
    DAS2_YYerror = 256,            /* error  */
    DAS2_YYUNDEF = 257,            /* "invalid token"  */
    LEXER_ERROR = 258,             /* "lexer error"  */
    DAS_CAPTURE = 259,             /* "capture"  */
    DAS_STRUCT = 260,              /* "struct"  */
    DAS_CLASS = 261,               /* "class"  */
    DAS_LET = 262,                 /* "let"  */
    DAS_DEF = 263,                 /* "def"  */
    DAS_WHILE = 264,               /* "while"  */
    DAS_IF = 265,                  /* "if"  */
    DAS_STATIC_IF = 266,           /* "static_if"  */
    DAS_ELSE = 267,                /* "else"  */
    DAS_FOR = 268,                 /* "for"  */
    DAS_CATCH = 269,               /* "recover"  */
    DAS_TRUE = 270,                /* "true"  */
    DAS_FALSE = 271,               /* "false"  */
    DAS_NEWT = 272,                /* "new"  */
    DAS_TYPEINFO = 273,            /* "typeinfo"  */
    DAS_TYPE = 274,                /* "type"  */
    DAS_IN = 275,                  /* "in"  */
    DAS_IS = 276,                  /* "is"  */
    DAS_AS = 277,                  /* "as"  */
    DAS_ELIF = 278,                /* "elif"  */
    DAS_STATIC_ELIF = 279,         /* "static_elif"  */
    DAS_ARRAY = 280,               /* "array"  */
    DAS_RETURN = 281,              /* "return"  */
    DAS_NULL = 282,                /* "null"  */
    DAS_BREAK = 283,               /* "break"  */
    DAS_TRY = 284,                 /* "try"  */
    DAS_OPTIONS = 285,             /* "options"  */
    DAS_TABLE = 286,               /* "table"  */
    DAS_EXPECT = 287,              /* "expect"  */
    DAS_CONST = 288,               /* "const"  */
    DAS_REQUIRE = 289,             /* "require"  */
    DAS_OPERATOR = 290,            /* "operator"  */
    DAS_ENUM = 291,                /* "enum"  */
    DAS_FINALLY = 292,             /* "finally"  */
    DAS_DELETE = 293,              /* "delete"  */
    DAS_DEREF = 294,               /* "deref"  */
    DAS_TYPEDEF = 295,             /* "typedef"  */
    DAS_DISTINCT = 296,            /* "distinct"  */
    DAS_TYPEDECL = 297,            /* "typedecl"  */
    DAS_WITH = 298,                /* "with"  */
    DAS_AKA = 299,                 /* "aka"  */
    DAS_ASSUME = 300,              /* "assume"  */
    DAS_CAST = 301,                /* "cast"  */
    DAS_OVERRIDE = 302,            /* "override"  */
    DAS_ABSTRACT = 303,            /* "abstract"  */
    DAS_UPCAST = 304,              /* "upcast"  */
    DAS_ITERATOR = 305,            /* "iterator"  */
    DAS_VAR = 306,                 /* "var"  */
    DAS_ADDR = 307,                /* "addr"  */
    DAS_CONTINUE = 308,            /* "continue"  */
    DAS_WHERE = 309,               /* "where"  */
    DAS_PASS = 310,                /* "pass"  */
    DAS_REINTERPRET = 311,         /* "reinterpret"  */
    DAS_MODULE = 312,              /* "module"  */
    DAS_PUBLIC = 313,              /* "public"  */
    DAS_LABEL = 314,               /* "label"  */
    DAS_GOTO = 315,                /* "goto"  */
    DAS_IMPLICIT = 316,            /* "implicit"  */
    DAS_EXPLICIT = 317,            /* "explicit"  */
    DAS_SHARED = 318,              /* "shared"  */
    DAS_PRIVATE = 319,             /* "private"  */
    DAS_SMART_PTR = 320,           /* "smart_ptr"  */
    DAS_UNSAFE = 321,              /* "unsafe"  */
    DAS_INSCOPE = 322,             /* "inscope"  */
    DAS_STATIC = 323,              /* "static"  */
    DAS_FIXED_ARRAY = 324,         /* "fixed_array"  */
    DAS_DEFAULT = 325,             /* "default"  */
    DAS_UNINITIALIZED = 326,       /* "uninitialized"  */
    DAS_TBOOL = 327,               /* "bool"  */
    DAS_TVOID = 328,               /* "void"  */
    DAS_TSTRING = 329,             /* "string"  */
    DAS_TAUTO = 330,               /* "auto"  */
    DAS_TINT = 331,                /* "int"  */
    DAS_TINT2 = 332,               /* "int2"  */
    DAS_TINT3 = 333,               /* "int3"  */
    DAS_TINT4 = 334,               /* "int4"  */
    DAS_TUINT = 335,               /* "uint"  */
    DAS_TBITFIELD = 336,           /* "bitfield"  */
    DAS_TUINT2 = 337,              /* "uint2"  */
    DAS_TUINT3 = 338,              /* "uint3"  */
    DAS_TUINT4 = 339,              /* "uint4"  */
    DAS_TFLOAT = 340,              /* "float"  */
    DAS_TFLOAT2 = 341,             /* "float2"  */
    DAS_TFLOAT3 = 342,             /* "float3"  */
    DAS_TFLOAT4 = 343,             /* "float4"  */
    DAS_TRANGE = 344,              /* "range"  */
    DAS_TURANGE = 345,             /* "urange"  */
    DAS_TRANGE64 = 346,            /* "range64"  */
    DAS_TURANGE64 = 347,           /* "urange64"  */
    DAS_TBLOCK = 348,              /* "block"  */
    DAS_TINT64 = 349,              /* "int64"  */
    DAS_TUINT64 = 350,             /* "uint64"  */
    DAS_TDOUBLE = 351,             /* "double"  */
    DAS_TFUNCTION = 352,           /* "function"  */
    DAS_TLAMBDA = 353,             /* "lambda"  */
    DAS_TINT8 = 354,               /* "int8"  */
    DAS_TUINT8 = 355,              /* "uint8"  */
    DAS_TINT16 = 356,              /* "int16"  */
    DAS_TUINT16 = 357,             /* "uint16"  */
    DAS_TTUPLE = 358,              /* "tuple"  */
    DAS_TVARIANT = 359,            /* "variant"  */
    DAS_GENERATOR = 360,           /* "generator"  */
    DAS_YIELD = 361,               /* "yield"  */
    DAS_SEALED = 362,              /* "sealed"  */
    DAS_TEMPLATE = 363,            /* "template"  */
    ADDEQU = 364,                  /* "+="  */
    SUBEQU = 365,                  /* "-="  */
    DIVEQU = 366,                  /* "/="  */
    MULEQU = 367,                  /* "*="  */
    MODEQU = 368,                  /* "%="  */
    ANDEQU = 369,                  /* "&="  */
    OREQU = 370,                   /* "|="  */
    XOREQU = 371,                  /* "^="  */
    SHL = 372,                     /* "<<"  */
    SHR = 373,                     /* ">>"  */
    ADDADD = 374,                  /* "++"  */
    SUBSUB = 375,                  /* "--"  */
    LEEQU = 376,                   /* "<="  */
    SHLEQU = 377,                  /* "<<="  */
    SHREQU = 378,                  /* ">>="  */
    GREQU = 379,                   /* ">="  */
    EQUEQU = 380,                  /* "=="  */
    NOTEQU = 381,                  /* "!="  */
    RARROW = 382,                  /* "->"  */
    LARROW = 383,                  /* "<-"  */
    QQ = 384,                      /* "??"  */
    QDOT = 385,                    /* "?."  */
    QBRA = 386,                    /* "?["  */
    LPIPE = 387,                   /* "<|"  */
    RPIPE = 388,                   /* "|>"  */
    CLONEEQU = 389,                /* ":="  */
    ROTL = 390,                    /* "<<<"  */
    ROTR = 391,                    /* ">>>"  */
    ROTLEQU = 392,                 /* "<<<="  */
    ROTREQU = 393,                 /* ">>>="  */
    MAPTO = 394,                   /* "=>"  */
    DOUBLE_AT = 395,               /* "@@"  */
    AT_FIELD = 396,                /* "@field"  */
    COLCOL = 397,                  /* "::"  */
    ANDAND = 398,                  /* "&&"  */
    OROR = 399,                    /* "||"  */
    XORXOR = 400,                  /* "^^"  */
    ANDANDEQU = 401,               /* "&&="  */
    OROREQU = 402,                 /* "||="  */
    XORXOREQU = 403,               /* "^^="  */
    DOTDOT = 404,                  /* ".."  */
    MTAG_E = 405,                  /* "$$"  */
    MTAG_I = 406,                  /* "$i"  */
    MTAG_V = 407,                  /* "$v"  */
    MTAG_B = 408,                  /* "$b"  */
    MTAG_A = 409,                  /* "$a"  */
    MTAG_T = 410,                  /* "$t"  */
    MTAG_C = 411,                  /* "$c"  */
    MTAG_F = 412,                  /* "$f"  */
    MTAG_DOTDOTDOT = 413,          /* "..."  */
    INTEGER = 414,                 /* "integer constant"  */
    LONG_INTEGER = 415,            /* "long integer constant"  */
    UNSIGNED_INTEGER = 416,        /* "unsigned integer constant"  */
    UNSIGNED_LONG_INTEGER = 417,   /* "unsigned long integer constant"  */
    UNSIGNED_INT8 = 418,           /* "unsigned int8 constant"  */
    DAS_FLOAT = 419,               /* "floating point constant"  */
    DOUBLE = 420,                  /* "double constant"  */
    NAME = 421,                    /* "name"  */
    DAS_EMIT_COMMA = 422,          /* "new line, comma"  */
    DAS_EMIT_SEMICOLON = 423,      /* "new line, semicolon"  */
    BEGIN_STRING = 424,            /* "start of the string"  */
    STRING_CHARACTER = 425,        /* STRING_CHARACTER  */
    STRING_CHARACTER_ESC = 426,    /* STRING_CHARACTER_ESC  */
    END_STRING = 427,              /* "end of the string"  */
    BEGIN_STRING_EXPR = 428,       /* "{"  */
    END_STRING_EXPR = 429,         /* "}"  */
    END_OF_READ = 430,             /* "end of failed eader macro"  */
    UNARY_MINUS = 431,             /* UNARY_MINUS  */
    UNARY_PLUS = 432,              /* UNARY_PLUS  */
    PRE_INC = 433,                 /* PRE_INC  */
    PRE_DEC = 434,                 /* PRE_DEC  */
    LLPIPE = 435,                  /* LLPIPE  */
    POST_INC = 436,                /* POST_INC  */
    POST_DEC = 437,                /* POST_DEC  */
    DEREF = 438                    /* DEREF  */
  };
  typedef enum das2_yytokentype das2_yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined DAS2_YYSTYPE && ! defined DAS2_YYSTYPE_IS_DECLARED
union DAS2_YYSTYPE
{

    char                            ch;
    bool                            b;
    int32_t                         i;
    uint32_t                        ui;
    int64_t                         i64;
    uint64_t                        ui64;
    double                          d;
    double                          fd;
    string *                        s;
    vector<string> *                pNameList;
    vector<tuple<string,Expression *>> *  pNameExprList;
    vector<VariableNameAndPosition> * pNameWithPosList;
    VariableDeclaration *           pVarDecl;
    vector<VariableDeclaration*> *  pVarDeclList;
    TypeDecl *                      pTypeDecl;
    vector<Expression *> *          pTypeDeclList;
    Expression *                    pExpression;
    Type                            type;
    AnnotationArgument *            aa;
    AnnotationArgumentList *        aaList;
    AnnotationDeclaration *         fa;
    AnnotationList *                faList;
    MakeStruct *                    pMakeStruct;
    Enumeration *                   pEnum;
    Enumeration *                   pEnumList;
    EnumPair *                      pEnumPair;
    Structure *                     pStructure;
    Function *                      pFuncDecl;
    CaptureEntry *                  pCapt;
    vector<CaptureEntry> *          pCaptList;
    TypePair                        aTypePair;


};
typedef union DAS2_YYSTYPE DAS2_YYSTYPE;
# define DAS2_YYSTYPE_IS_TRIVIAL 1
# define DAS2_YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined DAS2_YYLTYPE && ! defined DAS2_YYLTYPE_IS_DECLARED
typedef struct DAS2_YYLTYPE DAS2_YYLTYPE;
struct DAS2_YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define DAS2_YYLTYPE_IS_DECLARED 1
# define DAS2_YYLTYPE_IS_TRIVIAL 1
#endif




int das2_yyparse (yyscan_t scanner);


#endif /* !YY_DAS2_YY_DS2_PARSER_HPP_INCLUDED  */
