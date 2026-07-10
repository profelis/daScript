/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         DAS_YYSTYPE
#define YYLTYPE         DAS_YYLTYPE
/* Substitute the variable and function names.  */
#define yyparse         das_yyparse
#define yylex           das_yylex
#define yyerror         das_yyerror
#define yydebug         das_yydebug
#define yynerrs         das_yynerrs

/* First part of user prologue.  */

    #define das_yyparse fmt_yyparse // We can't change flex prefix, since we have only one lexer file, seems like to define is the best way

    #include "daScript/misc/platform.h"
    #include "daScript/simulate/debug_info.h"
    #include "daScript/ast/compilation_errors.h"

    #ifdef _MSC_VER
    #pragma warning(disable:4262)
    #pragma warning(disable:4127)
    #pragma warning(disable:4702)
    #endif

    using namespace das;

    union DAS_YYSTYPE;
    struct DAS_YYLTYPE;

    #define YY_NO_UNISTD_H
    #include "../src/parser/lex.yy.h"

    void das_yyerror ( DAS_YYLTYPE * lloc, yyscan_t scanner, const string & error );
    void das_yyfatalerror ( DAS_YYLTYPE * lloc, yyscan_t scanner, const string & error, CompilationError cerr );
    int yylex ( DAS_YYSTYPE *lvalp, DAS_YYLTYPE *llocp, yyscan_t scanner );
    void yybegin ( const char * str );

    void das_yybegin_reader ( yyscan_t yyscanner );
    void das_yyend_reader ( yyscan_t yyscanner );
    void das_accept_sequence ( yyscan_t yyscanner, const char * seq, size_t seqLen, int lineNo, FileInfo * info );

    namespace das { class Module; }
    void das_collect_keywords ( das::Module * mod, yyscan_t yyscanner );
    void das_strfmt ( yyscan_t yyscanner );

    #undef yyextra
    #define yyextra (*((das::DasParserState **)(scanner)))


# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "ds_parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LEXER_ERROR = 3,                /* "lexer error"  */
  YYSYMBOL_DAS_CAPTURE = 4,                /* "capture"  */
  YYSYMBOL_DAS_STRUCT = 5,                 /* "struct"  */
  YYSYMBOL_DAS_CLASS = 6,                  /* "class"  */
  YYSYMBOL_DAS_LET = 7,                    /* "let"  */
  YYSYMBOL_DAS_DEF = 8,                    /* "def"  */
  YYSYMBOL_DAS_WHILE = 9,                  /* "while"  */
  YYSYMBOL_DAS_IF = 10,                    /* "if"  */
  YYSYMBOL_DAS_STATIC_IF = 11,             /* "static_if"  */
  YYSYMBOL_DAS_ELSE = 12,                  /* "else"  */
  YYSYMBOL_DAS_FOR = 13,                   /* "for"  */
  YYSYMBOL_DAS_CATCH = 14,                 /* "recover"  */
  YYSYMBOL_DAS_TRUE = 15,                  /* "true"  */
  YYSYMBOL_DAS_FALSE = 16,                 /* "false"  */
  YYSYMBOL_DAS_NEWT = 17,                  /* "new"  */
  YYSYMBOL_DAS_TYPEINFO = 18,              /* "typeinfo"  */
  YYSYMBOL_DAS_TYPE = 19,                  /* "type"  */
  YYSYMBOL_DAS_IN = 20,                    /* "in"  */
  YYSYMBOL_DAS_IS = 21,                    /* "is"  */
  YYSYMBOL_DAS_AS = 22,                    /* "as"  */
  YYSYMBOL_DAS_ELIF = 23,                  /* "elif"  */
  YYSYMBOL_DAS_STATIC_ELIF = 24,           /* "static_elif"  */
  YYSYMBOL_DAS_ARRAY = 25,                 /* "array"  */
  YYSYMBOL_DAS_RETURN = 26,                /* "return"  */
  YYSYMBOL_DAS_NULL = 27,                  /* "null"  */
  YYSYMBOL_DAS_BREAK = 28,                 /* "break"  */
  YYSYMBOL_DAS_TRY = 29,                   /* "try"  */
  YYSYMBOL_DAS_OPTIONS = 30,               /* "options"  */
  YYSYMBOL_DAS_TABLE = 31,                 /* "table"  */
  YYSYMBOL_DAS_EXPECT = 32,                /* "expect"  */
  YYSYMBOL_DAS_CONST = 33,                 /* "const"  */
  YYSYMBOL_DAS_REQUIRE = 34,               /* "require"  */
  YYSYMBOL_DAS_OPERATOR = 35,              /* "operator"  */
  YYSYMBOL_DAS_ENUM = 36,                  /* "enum"  */
  YYSYMBOL_DAS_FINALLY = 37,               /* "finally"  */
  YYSYMBOL_DAS_DELETE = 38,                /* "delete"  */
  YYSYMBOL_DAS_DEREF = 39,                 /* "deref"  */
  YYSYMBOL_DAS_TYPEDEF = 40,               /* "typedef"  */
  YYSYMBOL_DAS_TYPEDECL = 41,              /* "typedecl"  */
  YYSYMBOL_DAS_WITH = 42,                  /* "with"  */
  YYSYMBOL_DAS_AKA = 43,                   /* "aka"  */
  YYSYMBOL_DAS_ASSUME = 44,                /* "assume"  */
  YYSYMBOL_DAS_CAST = 45,                  /* "cast"  */
  YYSYMBOL_DAS_OVERRIDE = 46,              /* "override"  */
  YYSYMBOL_DAS_ABSTRACT = 47,              /* "abstract"  */
  YYSYMBOL_DAS_UPCAST = 48,                /* "upcast"  */
  YYSYMBOL_DAS_ITERATOR = 49,              /* "iterator"  */
  YYSYMBOL_DAS_VAR = 50,                   /* "var"  */
  YYSYMBOL_DAS_ADDR = 51,                  /* "addr"  */
  YYSYMBOL_DAS_CONTINUE = 52,              /* "continue"  */
  YYSYMBOL_DAS_WHERE = 53,                 /* "where"  */
  YYSYMBOL_DAS_PASS = 54,                  /* "pass"  */
  YYSYMBOL_DAS_REINTERPRET = 55,           /* "reinterpret"  */
  YYSYMBOL_DAS_MODULE = 56,                /* "module"  */
  YYSYMBOL_DAS_PUBLIC = 57,                /* "public"  */
  YYSYMBOL_DAS_LABEL = 58,                 /* "label"  */
  YYSYMBOL_DAS_GOTO = 59,                  /* "goto"  */
  YYSYMBOL_DAS_IMPLICIT = 60,              /* "implicit"  */
  YYSYMBOL_DAS_EXPLICIT = 61,              /* "explicit"  */
  YYSYMBOL_DAS_SHARED = 62,                /* "shared"  */
  YYSYMBOL_DAS_PRIVATE = 63,               /* "private"  */
  YYSYMBOL_DAS_SMART_PTR = 64,             /* "smart_ptr"  */
  YYSYMBOL_DAS_UNSAFE = 65,                /* "unsafe"  */
  YYSYMBOL_DAS_INSCOPE = 66,               /* "inscope"  */
  YYSYMBOL_DAS_STATIC = 67,                /* "static"  */
  YYSYMBOL_DAS_FIXED_ARRAY = 68,           /* "fixed_array"  */
  YYSYMBOL_DAS_DEFAULT = 69,               /* "default"  */
  YYSYMBOL_DAS_UNINITIALIZED = 70,         /* "uninitialized"  */
  YYSYMBOL_DAS_TBOOL = 71,                 /* "bool"  */
  YYSYMBOL_DAS_TVOID = 72,                 /* "void"  */
  YYSYMBOL_DAS_TSTRING = 73,               /* "string"  */
  YYSYMBOL_DAS_TAUTO = 74,                 /* "auto"  */
  YYSYMBOL_DAS_TINT = 75,                  /* "int"  */
  YYSYMBOL_DAS_TINT2 = 76,                 /* "int2"  */
  YYSYMBOL_DAS_TINT3 = 77,                 /* "int3"  */
  YYSYMBOL_DAS_TINT4 = 78,                 /* "int4"  */
  YYSYMBOL_DAS_TUINT = 79,                 /* "uint"  */
  YYSYMBOL_DAS_TBITFIELD = 80,             /* "bitfield"  */
  YYSYMBOL_DAS_TUINT2 = 81,                /* "uint2"  */
  YYSYMBOL_DAS_TUINT3 = 82,                /* "uint3"  */
  YYSYMBOL_DAS_TUINT4 = 83,                /* "uint4"  */
  YYSYMBOL_DAS_TFLOAT = 84,                /* "float"  */
  YYSYMBOL_DAS_TFLOAT2 = 85,               /* "float2"  */
  YYSYMBOL_DAS_TFLOAT3 = 86,               /* "float3"  */
  YYSYMBOL_DAS_TFLOAT4 = 87,               /* "float4"  */
  YYSYMBOL_DAS_TRANGE = 88,                /* "range"  */
  YYSYMBOL_DAS_TURANGE = 89,               /* "urange"  */
  YYSYMBOL_DAS_TRANGE64 = 90,              /* "range64"  */
  YYSYMBOL_DAS_TURANGE64 = 91,             /* "urange64"  */
  YYSYMBOL_DAS_TBLOCK = 92,                /* "block"  */
  YYSYMBOL_DAS_TINT64 = 93,                /* "int64"  */
  YYSYMBOL_DAS_TUINT64 = 94,               /* "uint64"  */
  YYSYMBOL_DAS_TDOUBLE = 95,               /* "double"  */
  YYSYMBOL_DAS_TFUNCTION = 96,             /* "function"  */
  YYSYMBOL_DAS_TLAMBDA = 97,               /* "lambda"  */
  YYSYMBOL_DAS_TINT8 = 98,                 /* "int8"  */
  YYSYMBOL_DAS_TUINT8 = 99,                /* "uint8"  */
  YYSYMBOL_DAS_TINT16 = 100,               /* "int16"  */
  YYSYMBOL_DAS_TUINT16 = 101,              /* "uint16"  */
  YYSYMBOL_DAS_TFLOAT16 = 102,             /* "float16"  */
  YYSYMBOL_DAS_THALF2 = 103,               /* "half2"  */
  YYSYMBOL_DAS_THALF3 = 104,               /* "half3"  */
  YYSYMBOL_DAS_THALF4 = 105,               /* "half4"  */
  YYSYMBOL_DAS_THALF8 = 106,               /* "half8"  */
  YYSYMBOL_DAS_TSHORT2 = 107,              /* "short2"  */
  YYSYMBOL_DAS_TSHORT3 = 108,              /* "short3"  */
  YYSYMBOL_DAS_TSHORT4 = 109,              /* "short4"  */
  YYSYMBOL_DAS_TSHORT8 = 110,              /* "short8"  */
  YYSYMBOL_DAS_TUSHORT2 = 111,             /* "ushort2"  */
  YYSYMBOL_DAS_TUSHORT3 = 112,             /* "ushort3"  */
  YYSYMBOL_DAS_TUSHORT4 = 113,             /* "ushort4"  */
  YYSYMBOL_DAS_TUSHORT8 = 114,             /* "ushort8"  */
  YYSYMBOL_DAS_TBYTE2 = 115,               /* "byte2"  */
  YYSYMBOL_DAS_TBYTE3 = 116,               /* "byte3"  */
  YYSYMBOL_DAS_TBYTE4 = 117,               /* "byte4"  */
  YYSYMBOL_DAS_TBYTE8 = 118,               /* "byte8"  */
  YYSYMBOL_DAS_TBYTE16 = 119,              /* "byte16"  */
  YYSYMBOL_DAS_TUBYTE2 = 120,              /* "ubyte2"  */
  YYSYMBOL_DAS_TUBYTE3 = 121,              /* "ubyte3"  */
  YYSYMBOL_DAS_TUBYTE4 = 122,              /* "ubyte4"  */
  YYSYMBOL_DAS_TUBYTE8 = 123,              /* "ubyte8"  */
  YYSYMBOL_DAS_TUBYTE16 = 124,             /* "ubyte16"  */
  YYSYMBOL_DAS_TTUPLE = 125,               /* "tuple"  */
  YYSYMBOL_DAS_TVARIANT = 126,             /* "variant"  */
  YYSYMBOL_DAS_GENERATOR = 127,            /* "generator"  */
  YYSYMBOL_DAS_YIELD = 128,                /* "yield"  */
  YYSYMBOL_DAS_SEALED = 129,               /* "sealed"  */
  YYSYMBOL_DAS_TEMPLATE = 130,             /* "template"  */
  YYSYMBOL_ADDEQU = 131,                   /* "+="  */
  YYSYMBOL_SUBEQU = 132,                   /* "-="  */
  YYSYMBOL_DIVEQU = 133,                   /* "/="  */
  YYSYMBOL_MULEQU = 134,                   /* "*="  */
  YYSYMBOL_MODEQU = 135,                   /* "%="  */
  YYSYMBOL_ANDEQU = 136,                   /* "&="  */
  YYSYMBOL_OREQU = 137,                    /* "|="  */
  YYSYMBOL_XOREQU = 138,                   /* "^="  */
  YYSYMBOL_SHL = 139,                      /* "<<"  */
  YYSYMBOL_SHR = 140,                      /* ">>"  */
  YYSYMBOL_ADDADD = 141,                   /* "++"  */
  YYSYMBOL_SUBSUB = 142,                   /* "--"  */
  YYSYMBOL_LEEQU = 143,                    /* "<="  */
  YYSYMBOL_SHLEQU = 144,                   /* "<<="  */
  YYSYMBOL_SHREQU = 145,                   /* ">>="  */
  YYSYMBOL_GREQU = 146,                    /* ">="  */
  YYSYMBOL_EQUEQU = 147,                   /* "=="  */
  YYSYMBOL_NOTEQU = 148,                   /* "!="  */
  YYSYMBOL_RARROW = 149,                   /* "->"  */
  YYSYMBOL_LARROW = 150,                   /* "<-"  */
  YYSYMBOL_QQ = 151,                       /* "??"  */
  YYSYMBOL_QDOT = 152,                     /* "?."  */
  YYSYMBOL_QBRA = 153,                     /* "?["  */
  YYSYMBOL_LPIPE = 154,                    /* "<|"  */
  YYSYMBOL_LBPIPE = 155,                   /* " <|"  */
  YYSYMBOL_LLPIPE = 156,                   /* "$ <|"  */
  YYSYMBOL_LAPIPE = 157,                   /* "@ <|"  */
  YYSYMBOL_LFPIPE = 158,                   /* "@@ <|"  */
  YYSYMBOL_RPIPE = 159,                    /* "|>"  */
  YYSYMBOL_CLONEEQU = 160,                 /* ":="  */
  YYSYMBOL_ROTL = 161,                     /* "<<<"  */
  YYSYMBOL_ROTR = 162,                     /* ">>>"  */
  YYSYMBOL_ROTLEQU = 163,                  /* "<<<="  */
  YYSYMBOL_ROTREQU = 164,                  /* ">>>="  */
  YYSYMBOL_MAPTO = 165,                    /* "=>"  */
  YYSYMBOL_COLCOL = 166,                   /* "::"  */
  YYSYMBOL_ANDAND = 167,                   /* "&&"  */
  YYSYMBOL_OROR = 168,                     /* "||"  */
  YYSYMBOL_XORXOR = 169,                   /* "^^"  */
  YYSYMBOL_ANDANDEQU = 170,                /* "&&="  */
  YYSYMBOL_OROREQU = 171,                  /* "||="  */
  YYSYMBOL_XORXOREQU = 172,                /* "^^="  */
  YYSYMBOL_DOTDOT = 173,                   /* ".."  */
  YYSYMBOL_MTAG_E = 174,                   /* "$$"  */
  YYSYMBOL_MTAG_I = 175,                   /* "$i"  */
  YYSYMBOL_MTAG_V = 176,                   /* "$v"  */
  YYSYMBOL_MTAG_B = 177,                   /* "$b"  */
  YYSYMBOL_MTAG_A = 178,                   /* "$a"  */
  YYSYMBOL_MTAG_T = 179,                   /* "$t"  */
  YYSYMBOL_MTAG_C = 180,                   /* "$c"  */
  YYSYMBOL_MTAG_F = 181,                   /* "$f"  */
  YYSYMBOL_MTAG_DOTDOTDOT = 182,           /* "..."  */
  YYSYMBOL_BRABRAB = 183,                  /* "[["  */
  YYSYMBOL_BRACBRB = 184,                  /* "[{"  */
  YYSYMBOL_CBRCBRB = 185,                  /* "{{"  */
  YYSYMBOL_OPEN_BRACE = 186,               /* "new scope"  */
  YYSYMBOL_CLOSE_BRACE = 187,              /* "close scope"  */
  YYSYMBOL_SEMICOLON = 188,                /* SEMICOLON  */
  YYSYMBOL_INTEGER = 189,                  /* "integer constant"  */
  YYSYMBOL_LONG_INTEGER = 190,             /* "long integer constant"  */
  YYSYMBOL_UNSIGNED_INTEGER = 191,         /* "unsigned integer constant"  */
  YYSYMBOL_UNSIGNED_LONG_INTEGER = 192,    /* "unsigned long integer constant"  */
  YYSYMBOL_UNSIGNED_INT8 = 193,            /* "unsigned int8 constant"  */
  YYSYMBOL_DAS_FLOAT = 194,                /* "floating point constant"  */
  YYSYMBOL_DOUBLE = 195,                   /* "double constant"  */
  YYSYMBOL_NAME = 196,                     /* "name"  */
  YYSYMBOL_KEYWORD = 197,                  /* "keyword"  */
  YYSYMBOL_TYPE_FUNCTION = 198,            /* "type function"  */
  YYSYMBOL_BEGIN_STRING = 199,             /* "start of the string"  */
  YYSYMBOL_STRING_CHARACTER = 200,         /* STRING_CHARACTER  */
  YYSYMBOL_STRING_CHARACTER_ESC = 201,     /* STRING_CHARACTER_ESC  */
  YYSYMBOL_END_STRING = 202,               /* "end of the string"  */
  YYSYMBOL_BEGIN_STRING_EXPR = 203,        /* "{"  */
  YYSYMBOL_END_STRING_EXPR = 204,          /* "}"  */
  YYSYMBOL_END_OF_READ = 205,              /* "end of failed eader macro"  */
  YYSYMBOL_206_begin_of_code_block_ = 206, /* "begin of code block"  */
  YYSYMBOL_207_end_of_code_block_ = 207,   /* "end of code block"  */
  YYSYMBOL_208_end_of_expression_ = 208,   /* "end of expression"  */
  YYSYMBOL_SEMICOLON_CUR_CUR = 209,        /* ";}}"  */
  YYSYMBOL_SEMICOLON_CUR_SQR = 210,        /* ";}]"  */
  YYSYMBOL_SEMICOLON_SQR_SQR = 211,        /* ";]]"  */
  YYSYMBOL_COMMA_SQR_SQR = 212,            /* ",]]"  */
  YYSYMBOL_COMMA_CUR_SQR = 213,            /* ",}]"  */
  YYSYMBOL_END_OF_EXPR = 214,              /* END_OF_EXPR  */
  YYSYMBOL_EMPTY = 215,                    /* EMPTY  */
  YYSYMBOL_216_ = 216,                     /* ','  */
  YYSYMBOL_217_ = 217,                     /* '='  */
  YYSYMBOL_218_ = 218,                     /* '?'  */
  YYSYMBOL_219_ = 219,                     /* ':'  */
  YYSYMBOL_220_ = 220,                     /* '|'  */
  YYSYMBOL_221_ = 221,                     /* '^'  */
  YYSYMBOL_222_ = 222,                     /* '&'  */
  YYSYMBOL_223_ = 223,                     /* '<'  */
  YYSYMBOL_224_ = 224,                     /* '>'  */
  YYSYMBOL_225_ = 225,                     /* '-'  */
  YYSYMBOL_226_ = 226,                     /* '+'  */
  YYSYMBOL_227_ = 227,                     /* '*'  */
  YYSYMBOL_228_ = 228,                     /* '/'  */
  YYSYMBOL_229_ = 229,                     /* '%'  */
  YYSYMBOL_UNARY_MINUS = 230,              /* UNARY_MINUS  */
  YYSYMBOL_UNARY_PLUS = 231,               /* UNARY_PLUS  */
  YYSYMBOL_232_ = 232,                     /* '~'  */
  YYSYMBOL_233_ = 233,                     /* '!'  */
  YYSYMBOL_PRE_INC = 234,                  /* PRE_INC  */
  YYSYMBOL_PRE_DEC = 235,                  /* PRE_DEC  */
  YYSYMBOL_POST_INC = 236,                 /* POST_INC  */
  YYSYMBOL_POST_DEC = 237,                 /* POST_DEC  */
  YYSYMBOL_DEREF = 238,                    /* DEREF  */
  YYSYMBOL_239_ = 239,                     /* '.'  */
  YYSYMBOL_240_ = 240,                     /* '['  */
  YYSYMBOL_241_ = 241,                     /* ']'  */
  YYSYMBOL_242_ = 242,                     /* '('  */
  YYSYMBOL_243_ = 243,                     /* ')'  */
  YYSYMBOL_244_ = 244,                     /* '$'  */
  YYSYMBOL_245_ = 245,                     /* '@'  */
  YYSYMBOL_246_ = 246,                     /* '#'  */
  YYSYMBOL_YYACCEPT = 247,                 /* $accept  */
  YYSYMBOL_program = 248,                  /* program  */
  YYSYMBOL_semicolon = 249,                /* semicolon  */
  YYSYMBOL_top_level_reader_macro = 250,   /* top_level_reader_macro  */
  YYSYMBOL_optional_public_or_private_module = 251, /* optional_public_or_private_module  */
  YYSYMBOL_module_name = 252,              /* module_name  */
  YYSYMBOL_optional_not_required = 253,    /* optional_not_required  */
  YYSYMBOL_module_declaration = 254,       /* module_declaration  */
  YYSYMBOL_character_sequence = 255,       /* character_sequence  */
  YYSYMBOL_string_constant = 256,          /* string_constant  */
  YYSYMBOL_format_string = 257,            /* format_string  */
  YYSYMBOL_optional_format_string = 258,   /* optional_format_string  */
  YYSYMBOL_259_1 = 259,                    /* $@1  */
  YYSYMBOL_string_builder_body = 260,      /* string_builder_body  */
  YYSYMBOL_string_builder = 261,           /* string_builder  */
  YYSYMBOL_reader_character_sequence = 262, /* reader_character_sequence  */
  YYSYMBOL_expr_reader = 263,              /* expr_reader  */
  YYSYMBOL_264_2 = 264,                    /* $@2  */
  YYSYMBOL_options_declaration = 265,      /* options_declaration  */
  YYSYMBOL_require_declaration = 266,      /* require_declaration  */
  YYSYMBOL_keyword_or_name = 267,          /* keyword_or_name  */
  YYSYMBOL_require_module_name = 268,      /* require_module_name  */
  YYSYMBOL_require_module = 269,           /* require_module  */
  YYSYMBOL_is_public_module = 270,         /* is_public_module  */
  YYSYMBOL_expect_declaration = 271,       /* expect_declaration  */
  YYSYMBOL_expect_list = 272,              /* expect_list  */
  YYSYMBOL_expect_error = 273,             /* expect_error  */
  YYSYMBOL_expression_label = 274,         /* expression_label  */
  YYSYMBOL_expression_goto = 275,          /* expression_goto  */
  YYSYMBOL_elif_or_static_elif = 276,      /* elif_or_static_elif  */
  YYSYMBOL_expression_else = 277,          /* expression_else  */
  YYSYMBOL_if_or_static_if = 278,          /* if_or_static_if  */
  YYSYMBOL_expression_else_one_liner = 279, /* expression_else_one_liner  */
  YYSYMBOL_280_3 = 280,                    /* $@3  */
  YYSYMBOL_expression_if_one_liner = 281,  /* expression_if_one_liner  */
  YYSYMBOL_expression_if_then_else = 282,  /* expression_if_then_else  */
  YYSYMBOL_283_4 = 283,                    /* $@4  */
  YYSYMBOL_expression_for_loop = 284,      /* expression_for_loop  */
  YYSYMBOL_285_5 = 285,                    /* $@5  */
  YYSYMBOL_286_6 = 286,                    /* $@6  */
  YYSYMBOL_expression_unsafe = 287,        /* expression_unsafe  */
  YYSYMBOL_expression_while_loop = 288,    /* expression_while_loop  */
  YYSYMBOL_expression_with = 289,          /* expression_with  */
  YYSYMBOL_expression_with_alias = 290,    /* expression_with_alias  */
  YYSYMBOL_291_7 = 291,                    /* $@7  */
  YYSYMBOL_292_8 = 292,                    /* $@8  */
  YYSYMBOL_annotation_argument_value = 293, /* annotation_argument_value  */
  YYSYMBOL_annotation_argument_value_list = 294, /* annotation_argument_value_list  */
  YYSYMBOL_annotation_argument_name = 295, /* annotation_argument_name  */
  YYSYMBOL_annotation_argument = 296,      /* annotation_argument  */
  YYSYMBOL_annotation_argument_list = 297, /* annotation_argument_list  */
  YYSYMBOL_metadata_argument_list = 298,   /* metadata_argument_list  */
  YYSYMBOL_annotation_declaration_name = 299, /* annotation_declaration_name  */
  YYSYMBOL_annotation_declaration_basic = 300, /* annotation_declaration_basic  */
  YYSYMBOL_annotation_declaration = 301,   /* annotation_declaration  */
  YYSYMBOL_annotation_list = 302,          /* annotation_list  */
  YYSYMBOL_optional_annotation_list = 303, /* optional_annotation_list  */
  YYSYMBOL_optional_function_argument_list = 304, /* optional_function_argument_list  */
  YYSYMBOL_optional_function_type = 305,   /* optional_function_type  */
  YYSYMBOL_function_name = 306,            /* function_name  */
  YYSYMBOL_optional_template = 307,        /* optional_template  */
  YYSYMBOL_global_function_declaration = 308, /* global_function_declaration  */
  YYSYMBOL_optional_public_or_private_function = 309, /* optional_public_or_private_function  */
  YYSYMBOL_function_declaration_header = 310, /* function_declaration_header  */
  YYSYMBOL_function_declaration = 311,     /* function_declaration  */
  YYSYMBOL_312_9 = 312,                    /* $@9  */
  YYSYMBOL_open_block = 313,               /* open_block  */
  YYSYMBOL_close_block = 314,              /* close_block  */
  YYSYMBOL_expression_block = 315,         /* expression_block  */
  YYSYMBOL_expr_call_pipe = 316,           /* expr_call_pipe  */
  YYSYMBOL_expression_any = 317,           /* expression_any  */
  YYSYMBOL_expressions = 318,              /* expressions  */
  YYSYMBOL_expr_keyword = 319,             /* expr_keyword  */
  YYSYMBOL_optional_expr_list = 320,       /* optional_expr_list  */
  YYSYMBOL_optional_expr_list_in_braces = 321, /* optional_expr_list_in_braces  */
  YYSYMBOL_optional_expr_map_tuple_list = 322, /* optional_expr_map_tuple_list  */
  YYSYMBOL_type_declaration_no_options_list = 323, /* type_declaration_no_options_list  */
  YYSYMBOL_expression_keyword = 324,       /* expression_keyword  */
  YYSYMBOL_325_10 = 325,                   /* $@10  */
  YYSYMBOL_326_11 = 326,                   /* $@11  */
  YYSYMBOL_327_12 = 327,                   /* $@12  */
  YYSYMBOL_328_13 = 328,                   /* $@13  */
  YYSYMBOL_expr_pipe = 329,                /* expr_pipe  */
  YYSYMBOL_name_in_namespace = 330,        /* name_in_namespace  */
  YYSYMBOL_expression_delete = 331,        /* expression_delete  */
  YYSYMBOL_new_type_declaration = 332,     /* new_type_declaration  */
  YYSYMBOL_333_14 = 333,                   /* $@14  */
  YYSYMBOL_334_15 = 334,                   /* $@15  */
  YYSYMBOL_expr_new = 335,                 /* expr_new  */
  YYSYMBOL_expression_break = 336,         /* expression_break  */
  YYSYMBOL_expression_continue = 337,      /* expression_continue  */
  YYSYMBOL_expression_return_no_pipe = 338, /* expression_return_no_pipe  */
  YYSYMBOL_expression_return = 339,        /* expression_return  */
  YYSYMBOL_expression_yield_no_pipe = 340, /* expression_yield_no_pipe  */
  YYSYMBOL_expression_yield = 341,         /* expression_yield  */
  YYSYMBOL_expression_try_catch = 342,     /* expression_try_catch  */
  YYSYMBOL_kwd_let_var_or_nothing = 343,   /* kwd_let_var_or_nothing  */
  YYSYMBOL_kwd_let = 344,                  /* kwd_let  */
  YYSYMBOL_optional_in_scope = 345,        /* optional_in_scope  */
  YYSYMBOL_tuple_expansion = 346,          /* tuple_expansion  */
  YYSYMBOL_tuple_expansion_variable_declaration = 347, /* tuple_expansion_variable_declaration  */
  YYSYMBOL_expression_let = 348,           /* expression_let  */
  YYSYMBOL_expr_cast = 349,                /* expr_cast  */
  YYSYMBOL_350_16 = 350,                   /* $@16  */
  YYSYMBOL_351_17 = 351,                   /* $@17  */
  YYSYMBOL_352_18 = 352,                   /* $@18  */
  YYSYMBOL_353_19 = 353,                   /* $@19  */
  YYSYMBOL_354_20 = 354,                   /* $@20  */
  YYSYMBOL_355_21 = 355,                   /* $@21  */
  YYSYMBOL_expr_type_decl = 356,           /* expr_type_decl  */
  YYSYMBOL_357_22 = 357,                   /* $@22  */
  YYSYMBOL_358_23 = 358,                   /* $@23  */
  YYSYMBOL_expr_type_info = 359,           /* expr_type_info  */
  YYSYMBOL_expr_list = 360,                /* expr_list  */
  YYSYMBOL_block_or_simple_block = 361,    /* block_or_simple_block  */
  YYSYMBOL_block_or_lambda = 362,          /* block_or_lambda  */
  YYSYMBOL_capture_entry = 363,            /* capture_entry  */
  YYSYMBOL_capture_list = 364,             /* capture_list  */
  YYSYMBOL_optional_capture_list = 365,    /* optional_capture_list  */
  YYSYMBOL_expr_block = 366,               /* expr_block  */
  YYSYMBOL_expr_full_block = 367,          /* expr_full_block  */
  YYSYMBOL_expr_full_block_assumed_piped = 368, /* expr_full_block_assumed_piped  */
  YYSYMBOL_369_24 = 369,                   /* $@24  */
  YYSYMBOL_expr_numeric_const = 370,       /* expr_numeric_const  */
  YYSYMBOL_expr_assign = 371,              /* expr_assign  */
  YYSYMBOL_expr_assign_pipe_right = 372,   /* expr_assign_pipe_right  */
  YYSYMBOL_expr_assign_pipe = 373,         /* expr_assign_pipe  */
  YYSYMBOL_expr_named_call = 374,          /* expr_named_call  */
  YYSYMBOL_expr_method_call = 375,         /* expr_method_call  */
  YYSYMBOL_func_addr_name = 376,           /* func_addr_name  */
  YYSYMBOL_func_addr_expr = 377,           /* func_addr_expr  */
  YYSYMBOL_378_25 = 378,                   /* $@25  */
  YYSYMBOL_379_26 = 379,                   /* $@26  */
  YYSYMBOL_380_27 = 380,                   /* $@27  */
  YYSYMBOL_381_28 = 381,                   /* $@28  */
  YYSYMBOL_expr_field = 382,               /* expr_field  */
  YYSYMBOL_383_29 = 383,                   /* $@29  */
  YYSYMBOL_384_30 = 384,                   /* $@30  */
  YYSYMBOL_expr_call = 385,                /* expr_call  */
  YYSYMBOL_expr2 = 386,                    /* expr2  */
  YYSYMBOL_387_31 = 387,                   /* $@31  */
  YYSYMBOL_388_32 = 388,                   /* $@32  */
  YYSYMBOL_389_33 = 389,                   /* $@33  */
  YYSYMBOL_390_34 = 390,                   /* $@34  */
  YYSYMBOL_391_35 = 391,                   /* $@35  */
  YYSYMBOL_392_36 = 392,                   /* $@36  */
  YYSYMBOL_expr = 393,                     /* expr  */
  YYSYMBOL_expr_mtag = 394,                /* expr_mtag  */
  YYSYMBOL_optional_field_annotation = 395, /* optional_field_annotation  */
  YYSYMBOL_optional_override = 396,        /* optional_override  */
  YYSYMBOL_optional_constant = 397,        /* optional_constant  */
  YYSYMBOL_optional_public_or_private_member_variable = 398, /* optional_public_or_private_member_variable  */
  YYSYMBOL_optional_static_member_variable = 399, /* optional_static_member_variable  */
  YYSYMBOL_structure_variable_declaration = 400, /* structure_variable_declaration  */
  YYSYMBOL_opt_sem = 401,                  /* opt_sem  */
  YYSYMBOL_struct_variable_declaration_list = 402, /* struct_variable_declaration_list  */
  YYSYMBOL_403_37 = 403,                   /* $@37  */
  YYSYMBOL_404_38 = 404,                   /* $@38  */
  YYSYMBOL_405_39 = 405,                   /* $@39  */
  YYSYMBOL_406_40 = 406,                   /* $@40  */
  YYSYMBOL_function_argument_declaration_no_type = 407, /* function_argument_declaration_no_type  */
  YYSYMBOL_function_argument_declaration_type = 408, /* function_argument_declaration_type  */
  YYSYMBOL_function_argument_list = 409,   /* function_argument_list  */
  YYSYMBOL_tuple_type = 410,               /* tuple_type  */
  YYSYMBOL_tuple_type_list = 411,          /* tuple_type_list  */
  YYSYMBOL_tuple_alias_type_list = 412,    /* tuple_alias_type_list  */
  YYSYMBOL_variant_type = 413,             /* variant_type  */
  YYSYMBOL_variant_type_list = 414,        /* variant_type_list  */
  YYSYMBOL_variant_alias_type_list = 415,  /* variant_alias_type_list  */
  YYSYMBOL_copy_or_move = 416,             /* copy_or_move  */
  YYSYMBOL_variable_declaration_no_type = 417, /* variable_declaration_no_type  */
  YYSYMBOL_variable_declaration_type = 418, /* variable_declaration_type  */
  YYSYMBOL_variable_declaration = 419,     /* variable_declaration  */
  YYSYMBOL_copy_or_move_or_clone = 420,    /* copy_or_move_or_clone  */
  YYSYMBOL_optional_ref = 421,             /* optional_ref  */
  YYSYMBOL_let_variable_name_with_pos_list = 422, /* let_variable_name_with_pos_list  */
  YYSYMBOL_let_variable_declaration = 423, /* let_variable_declaration  */
  YYSYMBOL_global_variable_declaration_list = 424, /* global_variable_declaration_list  */
  YYSYMBOL_425_41 = 425,                   /* $@41  */
  YYSYMBOL_optional_shared = 426,          /* optional_shared  */
  YYSYMBOL_optional_public_or_private_variable = 427, /* optional_public_or_private_variable  */
  YYSYMBOL_global_let = 428,               /* global_let  */
  YYSYMBOL_429_42 = 429,                   /* $@42  */
  YYSYMBOL_enum_list = 430,                /* enum_list  */
  YYSYMBOL_optional_public_or_private_alias = 431, /* optional_public_or_private_alias  */
  YYSYMBOL_single_alias = 432,             /* single_alias  */
  YYSYMBOL_433_43 = 433,                   /* $@43  */
  YYSYMBOL_alias_list = 434,               /* alias_list  */
  YYSYMBOL_alias_declaration = 435,        /* alias_declaration  */
  YYSYMBOL_436_44 = 436,                   /* $@44  */
  YYSYMBOL_optional_public_or_private_enum = 437, /* optional_public_or_private_enum  */
  YYSYMBOL_enum_name = 438,                /* enum_name  */
  YYSYMBOL_enum_declaration = 439,         /* enum_declaration  */
  YYSYMBOL_optional_structure_parent = 440, /* optional_structure_parent  */
  YYSYMBOL_optional_sealed = 441,          /* optional_sealed  */
  YYSYMBOL_structure_name = 442,           /* structure_name  */
  YYSYMBOL_class_or_struct = 443,          /* class_or_struct  */
  YYSYMBOL_optional_public_or_private_structure = 444, /* optional_public_or_private_structure  */
  YYSYMBOL_optional_struct_variable_declaration_list = 445, /* optional_struct_variable_declaration_list  */
  YYSYMBOL_structure_declaration = 446,    /* structure_declaration  */
  YYSYMBOL_447_45 = 447,                   /* $@45  */
  YYSYMBOL_448_46 = 448,                   /* $@46  */
  YYSYMBOL_variable_name_with_pos_list = 449, /* variable_name_with_pos_list  */
  YYSYMBOL_basic_type_declaration = 450,   /* basic_type_declaration  */
  YYSYMBOL_enum_basic_type_declaration = 451, /* enum_basic_type_declaration  */
  YYSYMBOL_structure_type_declaration = 452, /* structure_type_declaration  */
  YYSYMBOL_auto_type_declaration = 453,    /* auto_type_declaration  */
  YYSYMBOL_bitfield_bits = 454,            /* bitfield_bits  */
  YYSYMBOL_commas = 455,                   /* commas  */
  YYSYMBOL_bitfield_alias_bits = 456,      /* bitfield_alias_bits  */
  YYSYMBOL_bitfield_basic_type_declaration = 457, /* bitfield_basic_type_declaration  */
  YYSYMBOL_bitfield_type_declaration = 458, /* bitfield_type_declaration  */
  YYSYMBOL_459_47 = 459,                   /* $@47  */
  YYSYMBOL_460_48 = 460,                   /* $@48  */
  YYSYMBOL_c_or_s = 461,                   /* c_or_s  */
  YYSYMBOL_table_type_pair = 462,          /* table_type_pair  */
  YYSYMBOL_dim_list = 463,                 /* dim_list  */
  YYSYMBOL_type_declaration_no_options = 464, /* type_declaration_no_options  */
  YYSYMBOL_465_49 = 465,                   /* $@49  */
  YYSYMBOL_466_50 = 466,                   /* $@50  */
  YYSYMBOL_467_51 = 467,                   /* $@51  */
  YYSYMBOL_468_52 = 468,                   /* $@52  */
  YYSYMBOL_469_53 = 469,                   /* $@53  */
  YYSYMBOL_470_54 = 470,                   /* $@54  */
  YYSYMBOL_471_55 = 471,                   /* $@55  */
  YYSYMBOL_472_56 = 472,                   /* $@56  */
  YYSYMBOL_473_57 = 473,                   /* $@57  */
  YYSYMBOL_474_58 = 474,                   /* $@58  */
  YYSYMBOL_475_59 = 475,                   /* $@59  */
  YYSYMBOL_476_60 = 476,                   /* $@60  */
  YYSYMBOL_477_61 = 477,                   /* $@61  */
  YYSYMBOL_478_62 = 478,                   /* $@62  */
  YYSYMBOL_479_63 = 479,                   /* $@63  */
  YYSYMBOL_480_64 = 480,                   /* $@64  */
  YYSYMBOL_481_65 = 481,                   /* $@65  */
  YYSYMBOL_482_66 = 482,                   /* $@66  */
  YYSYMBOL_483_67 = 483,                   /* $@67  */
  YYSYMBOL_484_68 = 484,                   /* $@68  */
  YYSYMBOL_485_69 = 485,                   /* $@69  */
  YYSYMBOL_486_70 = 486,                   /* $@70  */
  YYSYMBOL_487_71 = 487,                   /* $@71  */
  YYSYMBOL_488_72 = 488,                   /* $@72  */
  YYSYMBOL_489_73 = 489,                   /* $@73  */
  YYSYMBOL_490_74 = 490,                   /* $@74  */
  YYSYMBOL_491_75 = 491,                   /* $@75  */
  YYSYMBOL_type_declaration = 492,         /* type_declaration  */
  YYSYMBOL_tuple_alias_declaration = 493,  /* tuple_alias_declaration  */
  YYSYMBOL_494_76 = 494,                   /* $@76  */
  YYSYMBOL_495_77 = 495,                   /* $@77  */
  YYSYMBOL_496_78 = 496,                   /* $@78  */
  YYSYMBOL_497_79 = 497,                   /* $@79  */
  YYSYMBOL_variant_alias_declaration = 498, /* variant_alias_declaration  */
  YYSYMBOL_499_80 = 499,                   /* $@80  */
  YYSYMBOL_500_81 = 500,                   /* $@81  */
  YYSYMBOL_501_82 = 501,                   /* $@82  */
  YYSYMBOL_502_83 = 502,                   /* $@83  */
  YYSYMBOL_bitfield_alias_declaration = 503, /* bitfield_alias_declaration  */
  YYSYMBOL_504_84 = 504,                   /* $@84  */
  YYSYMBOL_505_85 = 505,                   /* $@85  */
  YYSYMBOL_make_decl = 506,                /* make_decl  */
  YYSYMBOL_make_struct_fields = 507,       /* make_struct_fields  */
  YYSYMBOL_make_variant_dim = 508,         /* make_variant_dim  */
  YYSYMBOL_make_struct_single = 509,       /* make_struct_single  */
  YYSYMBOL_make_struct_dim = 510,          /* make_struct_dim  */
  YYSYMBOL_make_struct_dim_list = 511,     /* make_struct_dim_list  */
  YYSYMBOL_make_struct_dim_decl = 512,     /* make_struct_dim_decl  */
  YYSYMBOL_optional_make_struct_dim_decl = 513, /* optional_make_struct_dim_decl  */
  YYSYMBOL_optional_block = 514,           /* optional_block  */
  YYSYMBOL_optional_trailing_semicolon_cur_cur = 515, /* optional_trailing_semicolon_cur_cur  */
  YYSYMBOL_optional_trailing_semicolon_cur_sqr = 516, /* optional_trailing_semicolon_cur_sqr  */
  YYSYMBOL_optional_trailing_semicolon_sqr_sqr = 517, /* optional_trailing_semicolon_sqr_sqr  */
  YYSYMBOL_optional_trailing_delim_sqr_sqr = 518, /* optional_trailing_delim_sqr_sqr  */
  YYSYMBOL_optional_trailing_delim_cur_sqr = 519, /* optional_trailing_delim_cur_sqr  */
  YYSYMBOL_use_initializer = 520,          /* use_initializer  */
  YYSYMBOL_make_struct_decl = 521,         /* make_struct_decl  */
  YYSYMBOL_522_86 = 522,                   /* $@86  */
  YYSYMBOL_523_87 = 523,                   /* $@87  */
  YYSYMBOL_524_88 = 524,                   /* $@88  */
  YYSYMBOL_525_89 = 525,                   /* $@89  */
  YYSYMBOL_526_90 = 526,                   /* $@90  */
  YYSYMBOL_527_91 = 527,                   /* $@91  */
  YYSYMBOL_528_92 = 528,                   /* $@92  */
  YYSYMBOL_529_93 = 529,                   /* $@93  */
  YYSYMBOL_make_tuple = 530,               /* make_tuple  */
  YYSYMBOL_make_map_tuple = 531,           /* make_map_tuple  */
  YYSYMBOL_make_tuple_call = 532,          /* make_tuple_call  */
  YYSYMBOL_533_94 = 533,                   /* $@94  */
  YYSYMBOL_534_95 = 534,                   /* $@95  */
  YYSYMBOL_make_dim = 535,                 /* make_dim  */
  YYSYMBOL_make_dim_decl = 536,            /* make_dim_decl  */
  YYSYMBOL_537_96 = 537,                   /* $@96  */
  YYSYMBOL_538_97 = 538,                   /* $@97  */
  YYSYMBOL_539_98 = 539,                   /* $@98  */
  YYSYMBOL_540_99 = 540,                   /* $@99  */
  YYSYMBOL_541_100 = 541,                  /* $@100  */
  YYSYMBOL_542_101 = 542,                  /* $@101  */
  YYSYMBOL_543_102 = 543,                  /* $@102  */
  YYSYMBOL_544_103 = 544,                  /* $@103  */
  YYSYMBOL_545_104 = 545,                  /* $@104  */
  YYSYMBOL_546_105 = 546,                  /* $@105  */
  YYSYMBOL_make_table = 547,               /* make_table  */
  YYSYMBOL_expr_map_tuple_list = 548,      /* expr_map_tuple_list  */
  YYSYMBOL_make_table_decl = 549,          /* make_table_decl  */
  YYSYMBOL_array_comprehension_where = 550, /* array_comprehension_where  */
  YYSYMBOL_optional_comma = 551,           /* optional_comma  */
  YYSYMBOL_array_comprehension = 552       /* array_comprehension  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined DAS_YYLTYPE_IS_TRIVIAL && DAS_YYLTYPE_IS_TRIVIAL \
             && defined DAS_YYSTYPE_IS_TRIVIAL && DAS_YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   15298

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  247
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  306
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1014
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1874

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   474


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   233,     2,   246,   244,   229,   222,     2,
     242,   243,   227,   226,   216,   225,   239,   228,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   219,   208,
     223,   217,   224,   218,   245,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   240,     2,   241,   221,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   206,   220,   207,   232,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   209,   210,   211,   212,   213,   214,   215,   230,   231,
     234,   235,   236,   237,   238
};

#if DAS_YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   609,   609,   610,   615,   616,   617,   618,   619,   620,
     621,   622,   623,   624,   625,   626,   627,   631,   634,   637,
     643,   644,   645,   649,   650,   654,   655,   659,   678,   679,
     680,   681,   685,   686,   690,   691,   695,   696,   696,   700,
     705,   714,   729,   745,   750,   758,   758,   799,   829,   833,
     834,   835,   839,   842,   846,   850,   854,   858,   864,   873,
     876,   882,   883,   887,   891,   892,   896,   899,   905,   911,
     914,   920,   921,   925,   926,   927,   937,   950,   951,   955,
     956,   956,   962,   963,   964,   965,   966,   970,   980,   990,
     990,   998,   998,  1002,  1002,  1011,  1019,  1031,  1041,  1041,
    1045,  1045,  1051,  1052,  1053,  1054,  1055,  1056,  1060,  1065,
    1073,  1074,  1075,  1079,  1080,  1081,  1082,  1083,  1084,  1085,
    1086,  1087,  1093,  1096,  1102,  1105,  1108,  1114,  1115,  1116,
    1117,  1121,  1134,  1152,  1155,  1163,  1174,  1185,  1196,  1199,
    1206,  1210,  1217,  1218,  1222,  1223,  1224,  1228,  1231,  1235,
    1242,  1246,  1247,  1248,  1249,  1250,  1251,  1252,  1253,  1254,
    1255,  1256,  1257,  1258,  1259,  1260,  1261,  1262,  1263,  1264,
    1265,  1266,  1267,  1268,  1269,  1270,  1271,  1272,  1273,  1274,
    1275,  1276,  1277,  1278,  1279,  1280,  1281,  1282,  1283,  1284,
    1285,  1286,  1287,  1288,  1289,  1290,  1291,  1292,  1293,  1294,
    1295,  1296,  1297,  1298,  1299,  1300,  1301,  1302,  1303,  1304,
    1305,  1306,  1307,  1308,  1309,  1310,  1311,  1312,  1313,  1314,
    1315,  1316,  1317,  1318,  1319,  1320,  1321,  1322,  1323,  1324,
    1325,  1326,  1327,  1328,  1329,  1330,  1331,  1332,  1333,  1334,
    1335,  1336,  1337,  1338,  1339,  1340,  1341,  1342,  1343,  1344,
    1345,  1346,  1347,  1348,  1349,  1350,  1351,  1352,  1353,  1354,
    1355,  1356,  1357,  1358,  1359,  1360,  1361,  1362,  1363,  1364,
    1365,  1366,  1367,  1368,  1369,  1370,  1371,  1372,  1373,  1374,
    1375,  1376,  1380,  1381,  1385,  1404,  1405,  1406,  1410,  1416,
    1416,  1433,  1434,  1437,  1438,  1441,  1448,  1472,  1490,  1499,
    1505,  1506,  1507,  1508,  1509,  1510,  1511,  1512,  1513,  1514,
    1515,  1516,  1517,  1518,  1519,  1520,  1521,  1522,  1523,  1524,
    1525,  1526,  1530,  1535,  1541,  1547,  1559,  1560,  1564,  1565,
    1569,  1570,  1574,  1578,  1585,  1585,  1585,  1591,  1591,  1591,
    1600,  1634,  1642,  1649,  1656,  1662,  1663,  1674,  1678,  1681,
    1689,  1689,  1689,  1692,  1698,  1701,  1705,  1709,  1716,  1723,
    1729,  1733,  1737,  1740,  1743,  1751,  1754,  1757,  1765,  1768,
    1776,  1779,  1782,  1790,  1802,  1803,  1804,  1808,  1809,  1813,
    1814,  1818,  1823,  1831,  1842,  1848,  1863,  1875,  1878,  1884,
    1884,  1884,  1887,  1887,  1887,  1892,  1892,  1892,  1900,  1900,
    1900,  1906,  1920,  1936,  1954,  1964,  1975,  1990,  1993,  1999,
    2000,  2007,  2018,  2019,  2020,  2024,  2025,  2026,  2027,  2028,
    2032,  2037,  2045,  2046,  2059,  2063,  2073,  2080,  2087,  2087,
    2096,  2097,  2098,  2099,  2100,  2101,  2102,  2106,  2107,  2108,
    2109,  2110,  2111,  2112,  2113,  2114,  2115,  2116,  2117,  2118,
    2119,  2120,  2121,  2122,  2123,  2124,  2128,  2138,  2147,  2156,
    2161,  2162,  2163,  2164,  2165,  2166,  2167,  2168,  2169,  2170,
    2171,  2172,  2173,  2174,  2175,  2176,  2177,  2182,  2188,  2199,
    2204,  2214,  2218,  2225,  2228,  2228,  2228,  2233,  2233,  2233,
    2246,  2250,  2254,  2259,  2266,  2274,  2279,  2286,  2286,  2286,
    2293,  2297,  2307,  2316,  2325,  2329,  2332,  2338,  2339,  2340,
    2341,  2342,  2343,  2344,  2345,  2346,  2347,  2348,  2349,  2350,
    2351,  2352,  2353,  2354,  2355,  2356,  2357,  2358,  2359,  2360,
    2361,  2362,  2363,  2364,  2365,  2366,  2373,  2374,  2375,  2376,
    2377,  2378,  2379,  2380,  2381,  2382,  2383,  2384,  2391,  2392,
    2393,  2394,  2395,  2396,  2397,  2398,  2414,  2415,  2416,  2417,
    2418,  2421,  2424,  2425,  2425,  2425,  2428,  2433,  2437,  2441,
    2441,  2441,  2446,  2449,  2453,  2453,  2453,  2458,  2461,  2462,
    2463,  2464,  2465,  2466,  2467,  2468,  2469,  2471,  2475,  2483,
    2488,  2492,  2501,  2502,  2503,  2504,  2505,  2506,  2507,  2511,
    2515,  2519,  2523,  2527,  2531,  2535,  2539,  2543,  2550,  2551,
    2560,  2564,  2565,  2566,  2570,  2571,  2575,  2576,  2577,  2581,
    2582,  2586,  2597,  2598,  2599,  2600,  2605,  2608,  2608,  2612,
    2612,  2631,  2630,  2646,  2645,  2659,  2668,  2680,  2689,  2699,
    2700,  2701,  2702,  2703,  2707,  2710,  2719,  2720,  2724,  2727,
    2730,  2745,  2754,  2755,  2759,  2762,  2765,  2778,  2779,  2783,
    2789,  2795,  2804,  2807,  2814,  2817,  2823,  2824,  2825,  2829,
    2830,  2834,  2841,  2846,  2855,  2861,  2872,  2875,  2880,  2885,
    2893,  2903,  2914,  2917,  2917,  2937,  2938,  2942,  2943,  2944,
    2948,  2955,  2955,  2974,  2977,  2993,  3013,  3014,  3015,  3020,
    3020,  3050,  3053,  3060,  3070,  3070,  3074,  3075,  3076,  3080,
    3090,  3110,  3133,  3134,  3138,  3139,  3143,  3149,  3150,  3151,
    3152,  3156,  3157,  3158,  3162,  3165,  3176,  3181,  3176,  3201,
    3208,  3213,  3222,  3228,  3239,  3240,  3241,  3242,  3243,  3244,
    3245,  3246,  3247,  3248,  3249,  3250,  3251,  3252,  3253,  3254,
    3255,  3256,  3257,  3258,  3259,  3260,  3261,  3262,  3263,  3264,
    3265,  3266,  3267,  3268,  3269,  3270,  3271,  3272,  3273,  3274,
    3275,  3276,  3277,  3278,  3279,  3280,  3281,  3282,  3283,  3284,
    3285,  3286,  3287,  3288,  3292,  3293,  3294,  3295,  3296,  3297,
    3298,  3299,  3303,  3314,  3318,  3325,  3337,  3344,  3350,  3360,
    3361,  3366,  3371,  3385,  3395,  3405,  3415,  3425,  3438,  3439,
    3440,  3441,  3442,  3446,  3450,  3450,  3450,  3464,  3465,  3469,
    3473,  3480,  3483,  3489,  3490,  3491,  3492,  3493,  3503,  3506,
    3506,  3506,  3510,  3515,  3522,  3522,  3529,  3533,  3537,  3542,
    3547,  3552,  3557,  3561,  3565,  3570,  3574,  3578,  3583,  3583,
    3583,  3589,  3596,  3596,  3596,  3601,  3601,  3601,  3607,  3607,
    3607,  3612,  3617,  3617,  3617,  3622,  3622,  3622,  3631,  3636,
    3636,  3636,  3641,  3641,  3641,  3650,  3655,  3655,  3655,  3660,
    3660,  3660,  3669,  3669,  3669,  3675,  3675,  3675,  3684,  3687,
    3698,  3714,  3714,  3719,  3728,  3714,  3757,  3757,  3762,  3772,
    3757,  3801,  3801,  3801,  3854,  3855,  3856,  3857,  3858,  3862,
    3869,  3876,  3882,  3888,  3895,  3902,  3908,  3917,  3920,  3926,
    3934,  3939,  3946,  3951,  3958,  3963,  3969,  3970,  3974,  3975,
    3980,  3981,  3985,  3986,  3990,  3991,  3995,  3996,  3997,  4001,
    4002,  4003,  4007,  4008,  4012,  4045,  4084,  4103,  4123,  4143,
    4164,  4164,  4164,  4172,  4172,  4172,  4179,  4179,  4179,  4190,
    4190,  4190,  4201,  4205,  4211,  4227,  4233,  4239,  4245,  4245,
    4245,  4259,  4264,  4271,  4291,  4319,  4343,  4343,  4343,  4353,
    4353,  4353,  4367,  4367,  4367,  4381,  4390,  4390,  4390,  4410,
    4417,  4417,  4417,  4427,  4432,  4439,  4442,  4448,  4468,  4490,
    4498,  4518,  4543,  4544,  4548,  4549,  4554,  4564,  4567,  4570,
    4573,  4581,  4590,  4602,  4612
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"lexer error\"",
  "\"capture\"", "\"struct\"", "\"class\"", "\"let\"", "\"def\"",
  "\"while\"", "\"if\"", "\"static_if\"", "\"else\"", "\"for\"",
  "\"recover\"", "\"true\"", "\"false\"", "\"new\"", "\"typeinfo\"",
  "\"type\"", "\"in\"", "\"is\"", "\"as\"", "\"elif\"", "\"static_elif\"",
  "\"array\"", "\"return\"", "\"null\"", "\"break\"", "\"try\"",
  "\"options\"", "\"table\"", "\"expect\"", "\"const\"", "\"require\"",
  "\"operator\"", "\"enum\"", "\"finally\"", "\"delete\"", "\"deref\"",
  "\"typedef\"", "\"typedecl\"", "\"with\"", "\"aka\"", "\"assume\"",
  "\"cast\"", "\"override\"", "\"abstract\"", "\"upcast\"", "\"iterator\"",
  "\"var\"", "\"addr\"", "\"continue\"", "\"where\"", "\"pass\"",
  "\"reinterpret\"", "\"module\"", "\"public\"", "\"label\"", "\"goto\"",
  "\"implicit\"", "\"explicit\"", "\"shared\"", "\"private\"",
  "\"smart_ptr\"", "\"unsafe\"", "\"inscope\"", "\"static\"",
  "\"fixed_array\"", "\"default\"", "\"uninitialized\"", "\"bool\"",
  "\"void\"", "\"string\"", "\"auto\"", "\"int\"", "\"int2\"", "\"int3\"",
  "\"int4\"", "\"uint\"", "\"bitfield\"", "\"uint2\"", "\"uint3\"",
  "\"uint4\"", "\"float\"", "\"float2\"", "\"float3\"", "\"float4\"",
  "\"range\"", "\"urange\"", "\"range64\"", "\"urange64\"", "\"block\"",
  "\"int64\"", "\"uint64\"", "\"double\"", "\"function\"", "\"lambda\"",
  "\"int8\"", "\"uint8\"", "\"int16\"", "\"uint16\"", "\"float16\"",
  "\"half2\"", "\"half3\"", "\"half4\"", "\"half8\"", "\"short2\"",
  "\"short3\"", "\"short4\"", "\"short8\"", "\"ushort2\"", "\"ushort3\"",
  "\"ushort4\"", "\"ushort8\"", "\"byte2\"", "\"byte3\"", "\"byte4\"",
  "\"byte8\"", "\"byte16\"", "\"ubyte2\"", "\"ubyte3\"", "\"ubyte4\"",
  "\"ubyte8\"", "\"ubyte16\"", "\"tuple\"", "\"variant\"", "\"generator\"",
  "\"yield\"", "\"sealed\"", "\"template\"", "\"+=\"", "\"-=\"", "\"/=\"",
  "\"*=\"", "\"%=\"", "\"&=\"", "\"|=\"", "\"^=\"", "\"<<\"", "\">>\"",
  "\"++\"", "\"--\"", "\"<=\"", "\"<<=\"", "\">>=\"", "\">=\"", "\"==\"",
  "\"!=\"", "\"->\"", "\"<-\"", "\"??\"", "\"?.\"", "\"?[\"", "\"<|\"",
  "\" <|\"", "\"$ <|\"", "\"@ <|\"", "\"@@ <|\"", "\"|>\"", "\":=\"",
  "\"<<<\"", "\">>>\"", "\"<<<=\"", "\">>>=\"", "\"=>\"", "\"::\"",
  "\"&&\"", "\"||\"", "\"^^\"", "\"&&=\"", "\"||=\"", "\"^^=\"", "\"..\"",
  "\"$$\"", "\"$i\"", "\"$v\"", "\"$b\"", "\"$a\"", "\"$t\"", "\"$c\"",
  "\"$f\"", "\"...\"", "\"[[\"", "\"[{\"", "\"{{\"", "\"new scope\"",
  "\"close scope\"", "SEMICOLON", "\"integer constant\"",
  "\"long integer constant\"", "\"unsigned integer constant\"",
  "\"unsigned long integer constant\"", "\"unsigned int8 constant\"",
  "\"floating point constant\"", "\"double constant\"", "\"name\"",
  "\"keyword\"", "\"type function\"", "\"start of the string\"",
  "STRING_CHARACTER", "STRING_CHARACTER_ESC", "\"end of the string\"",
  "\"{\"", "\"}\"", "\"end of failed eader macro\"",
  "\"begin of code block\"", "\"end of code block\"",
  "\"end of expression\"", "\";}}\"", "\";}]\"", "\";]]\"", "\",]]\"",
  "\",}]\"", "END_OF_EXPR", "EMPTY", "','", "'='", "'?'", "':'", "'|'",
  "'^'", "'&'", "'<'", "'>'", "'-'", "'+'", "'*'", "'/'", "'%'",
  "UNARY_MINUS", "UNARY_PLUS", "'~'", "'!'", "PRE_INC", "PRE_DEC",
  "POST_INC", "POST_DEC", "DEREF", "'.'", "'['", "']'", "'('", "')'",
  "'$'", "'@'", "'#'", "$accept", "program", "semicolon",
  "top_level_reader_macro", "optional_public_or_private_module",
  "module_name", "optional_not_required", "module_declaration",
  "character_sequence", "string_constant", "format_string",
  "optional_format_string", "$@1", "string_builder_body", "string_builder",
  "reader_character_sequence", "expr_reader", "$@2", "options_declaration",
  "require_declaration", "keyword_or_name", "require_module_name",
  "require_module", "is_public_module", "expect_declaration",
  "expect_list", "expect_error", "expression_label", "expression_goto",
  "elif_or_static_elif", "expression_else", "if_or_static_if",
  "expression_else_one_liner", "$@3", "expression_if_one_liner",
  "expression_if_then_else", "$@4", "expression_for_loop", "$@5", "$@6",
  "expression_unsafe", "expression_while_loop", "expression_with",
  "expression_with_alias", "$@7", "$@8", "annotation_argument_value",
  "annotation_argument_value_list", "annotation_argument_name",
  "annotation_argument", "annotation_argument_list",
  "metadata_argument_list", "annotation_declaration_name",
  "annotation_declaration_basic", "annotation_declaration",
  "annotation_list", "optional_annotation_list",
  "optional_function_argument_list", "optional_function_type",
  "function_name", "optional_template", "global_function_declaration",
  "optional_public_or_private_function", "function_declaration_header",
  "function_declaration", "$@9", "open_block", "close_block",
  "expression_block", "expr_call_pipe", "expression_any", "expressions",
  "expr_keyword", "optional_expr_list", "optional_expr_list_in_braces",
  "optional_expr_map_tuple_list", "type_declaration_no_options_list",
  "expression_keyword", "$@10", "$@11", "$@12", "$@13", "expr_pipe",
  "name_in_namespace", "expression_delete", "new_type_declaration", "$@14",
  "$@15", "expr_new", "expression_break", "expression_continue",
  "expression_return_no_pipe", "expression_return",
  "expression_yield_no_pipe", "expression_yield", "expression_try_catch",
  "kwd_let_var_or_nothing", "kwd_let", "optional_in_scope",
  "tuple_expansion", "tuple_expansion_variable_declaration",
  "expression_let", "expr_cast", "$@16", "$@17", "$@18", "$@19", "$@20",
  "$@21", "expr_type_decl", "$@22", "$@23", "expr_type_info", "expr_list",
  "block_or_simple_block", "block_or_lambda", "capture_entry",
  "capture_list", "optional_capture_list", "expr_block", "expr_full_block",
  "expr_full_block_assumed_piped", "$@24", "expr_numeric_const",
  "expr_assign", "expr_assign_pipe_right", "expr_assign_pipe",
  "expr_named_call", "expr_method_call", "func_addr_name",
  "func_addr_expr", "$@25", "$@26", "$@27", "$@28", "expr_field", "$@29",
  "$@30", "expr_call", "expr2", "$@31", "$@32", "$@33", "$@34", "$@35",
  "$@36", "expr", "expr_mtag", "optional_field_annotation",
  "optional_override", "optional_constant",
  "optional_public_or_private_member_variable",
  "optional_static_member_variable", "structure_variable_declaration",
  "opt_sem", "struct_variable_declaration_list", "$@37", "$@38", "$@39",
  "$@40", "function_argument_declaration_no_type",
  "function_argument_declaration_type", "function_argument_list",
  "tuple_type", "tuple_type_list", "tuple_alias_type_list", "variant_type",
  "variant_type_list", "variant_alias_type_list", "copy_or_move",
  "variable_declaration_no_type", "variable_declaration_type",
  "variable_declaration", "copy_or_move_or_clone", "optional_ref",
  "let_variable_name_with_pos_list", "let_variable_declaration",
  "global_variable_declaration_list", "$@41", "optional_shared",
  "optional_public_or_private_variable", "global_let", "$@42", "enum_list",
  "optional_public_or_private_alias", "single_alias", "$@43", "alias_list",
  "alias_declaration", "$@44", "optional_public_or_private_enum",
  "enum_name", "enum_declaration", "optional_structure_parent",
  "optional_sealed", "structure_name", "class_or_struct",
  "optional_public_or_private_structure",
  "optional_struct_variable_declaration_list", "structure_declaration",
  "$@45", "$@46", "variable_name_with_pos_list", "basic_type_declaration",
  "enum_basic_type_declaration", "structure_type_declaration",
  "auto_type_declaration", "bitfield_bits", "commas",
  "bitfield_alias_bits", "bitfield_basic_type_declaration",
  "bitfield_type_declaration", "$@47", "$@48", "c_or_s", "table_type_pair",
  "dim_list", "type_declaration_no_options", "$@49", "$@50", "$@51",
  "$@52", "$@53", "$@54", "$@55", "$@56", "$@57", "$@58", "$@59", "$@60",
  "$@61", "$@62", "$@63", "$@64", "$@65", "$@66", "$@67", "$@68", "$@69",
  "$@70", "$@71", "$@72", "$@73", "$@74", "$@75", "type_declaration",
  "tuple_alias_declaration", "$@76", "$@77", "$@78", "$@79",
  "variant_alias_declaration", "$@80", "$@81", "$@82", "$@83",
  "bitfield_alias_declaration", "$@84", "$@85", "make_decl",
  "make_struct_fields", "make_variant_dim", "make_struct_single",
  "make_struct_dim", "make_struct_dim_list", "make_struct_dim_decl",
  "optional_make_struct_dim_decl", "optional_block",
  "optional_trailing_semicolon_cur_cur",
  "optional_trailing_semicolon_cur_sqr",
  "optional_trailing_semicolon_sqr_sqr", "optional_trailing_delim_sqr_sqr",
  "optional_trailing_delim_cur_sqr", "use_initializer", "make_struct_decl",
  "$@86", "$@87", "$@88", "$@89", "$@90", "$@91", "$@92", "$@93",
  "make_tuple", "make_map_tuple", "make_tuple_call", "$@94", "$@95",
  "make_dim", "make_dim_decl", "$@96", "$@97", "$@98", "$@99", "$@100",
  "$@101", "$@102", "$@103", "$@104", "$@105", "make_table",
  "expr_map_tuple_list", "make_table_decl", "array_comprehension_where",
  "optional_comma", "array_comprehension", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-1611)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-880)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1611,   195, -1611, -1611,    38,   -52,   363,   524, -1611,   -61,
     315,   315,   315, -1611, -1611,    -8,   183, -1611, -1611, -1611,
     566, -1611, -1611, -1611,   706, -1611,   156, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611,    19, -1611,    58,
      61,    81, -1611,    95, -1611, -1611, -1611,   276,   118, -1611,
      40, -1611, -1611, -1611,   315,   315, -1611, -1611,   156, -1611,
   -1611, -1611, -1611, -1611,   141,   223, -1611, -1611, -1611, -1611,
     183,   183,   183,   286, -1611,   879,   205, -1611, -1611,   370,
     407,   416,   645,   727, -1611,   845,    63,    38,   402,   -52,
     363,   363,   399,   363,   465, -1611,   894,   894, -1611,   470,
     604,   147,   566,   916,   517,   550,   587, -1611,   628,   562,
   -1611, -1611,    -4,    38,   183,   183,   183,   183, -1611, -1611,
   -1611, -1611,   918, -1611, -1611,   650, -1611, -1611, -1611, -1611,
   -1611,   524, -1611, -1611, -1611, -1611, -1611,   893,   175,   552,
   -1611, -1611, -1611, -1611,   399,   399,   399,   806, -1611, -1611,
   -1611, -1611,   634, -1611, -1611, -1611, -1611,   604, -1611, -1611,
   -1611,   695, -1611, -1611, -1611, -1611, -1611,   730, -1611,  -140,
   -1611,   532,   775,   879, -1611, -1611, -1611, -1611, -1611,   450,
     803, -1611,   -90, -1611, -1611, -1611,   899, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611,   -24,   762, -1611,   779, -1611, -1611,
     878, -1611,   784,   524,   524, -1611, -1611, 15059,   964, -1611,
   -1611,   812, -1611,   703,    38,    38,   131,    48, -1611, -1611,
   -1611,   175, -1611, -1611, 11946, -1611,   765,   524, -1611, -1611,
   14104, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,   988,
     994, -1611,   819,   524, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611,   524,   713,   847,   524, -1611,   -90,   236, -1611,
      38, -1611,   826,  1026,   744, -1611, -1611,   853,   863,   873,
     837,   874,   880, -1611, -1611, -1611,   860, -1611, -1611, -1611,
   -1611, -1611,   -41, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611,   883, -1611, -1611, -1611,   884,   896,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611,   898,   905,   888,
      -8, -1611, -1611, -1611, -1611, -1611,   180,   902, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611,   935,   938, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611,   942,   892, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611,  1119, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611,   952,   911, -1611, -1611,   169,   -40,
   -1611, -1611, -1611,   140, -1611,    -8, -1611, -1611, -1611,    48,
     913, -1611, 11002,   957,   965, 11946, -1611,   213, -1611, -1611,
   -1611, 11002, -1611, -1611,   967,   941,   -86,   -83,   -80, -1611,
   -1611, 11002,   366, -1611, -1611, -1611,    11, -1611, -1611, -1611,
      27,  6609, -1611,   920, 11596,   719, 11772,   572, -1611, -1611,
   -1611, -1611,   969,   900,  1079,   925, -1611,   182,   960,   253,
     927, 11946, 11946, -1611,  3133,   713, 11002, -1611, -1611,    41,
     604, -1611,   948,   949, -1611, -1611,   581,   -45,   951,    35,
   -1611,   662,   933,   954,   955,   939,   956,   943,   674,   961,
   -1611,   698,   963,   970, 11002, 11002,   950,   953,   958,   959,
     966,   977, -1611,  2627, 11422,  6842, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611,   971,   974, -1611,  1167, 11002, 11002, 11002,
   11002, 11002,  6147, 11002, -1611,   962, -1611, -1611,  7075, -1611,
     149, -1611, -1611, -1611, -1611,   981, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611,  2038, -1611,   983, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611,  1140,   593, -1611, -1611, -1611,  4753, 11946,
   11946, 11946,  2345, 11946, 11946,   984,   978, 11946,   819, 11946,
     819, 11946,   819, 12120,  1002,  2738, -1611, 11002, -1611, -1611,
   -1611, -1611, -1611,   968, -1611, -1611, 13651, 11002, -1611,   180,
     295, -1611,   -38, -1611, -1611,   570, -1611,   902,   703,   987,
     570, -1611,   703, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, 11002,
   -1611, -1611,   322,   217,   217,   217, -1611,   902,   902, -1611,
   11002, -1611, -1611,   995,  4060, -1611,   524,  7306, -1611, 11002,
    1030, -1611,   566,  1041,  7537,   -75,  1015,  4291,   352,   352,
     352, -1611,  7768, -1611,   566,   566, 11002,  1230, -1611, -1611,
   -1611, -1611, -1611, -1611,  1204, -1611, -1611, -1611,   584, -1611,
     566,   566,   566,   566, -1611,   566, -1611, -1611,  1177, -1611,
     -31, -1611, 14280,   979, -1611,   604, -1611,   183,  1236, -1611,
     -90, -1611, -1611, -1611, -1611,  1003, -1611, -1611,    -8,   708,
   -1611,  1023,  1024,  1031, -1611, 11002, 11946, 11002, 11002, -1611,
   -1611, 11002, -1611, 11002, -1611, 11002, -1611, -1611, 11002, -1611,
   11946,   101,   101, 11002, 11002, 11002, 11002, 11002, 11002,   322,
    3364,   322,  3596,   322,  1090, -1611,   673, -1611, -1611,   257,
    1017,   101,   101,   -53,   101,   101,   -92,  1247,  1020,  1054,
   14280,  1054,   439,   322,   703, -1611,  1055, -1611,  4984,    55,
   14681, 14736, 11002, 11002, -1611, -1611, 11002, 11002, 11002, 11002,
    1076, 11002,   -12, 11002, 11002, 11002, 11002, 11002, 11002, 11002,
   11002, 11002,  7999, 11002, 11002, 11002, 11002, 11002, 11002, 11002,
   11002, 11002, 11002, 14916, 11002, -1611,  8230,  1077, -1611,  4753,
   -1611,  1121, 11943,   771,   778,  1053,   553, -1611,   789,   795,
   -1611, -1611,  1082,   796,   -40,   801,   -40,   804,   -40, -1611,
     282, -1611,   347, -1611, 11946,  1063, -1611, -1611, 13686, -1611,
   -1611, 11002,  1065, 11946, -1611, -1611, 11946, -1611, -1611,  2843,
    1040,  1242, -1611, -1611,   215, -1611, -1611, -1611,   524,   322,
    1045,  4753, -1611,  1073,  1925, 15053,  1277, 11002, -1611,  1096,
     524,  1078, -1611,  1080,  1104, -1611, -1611, 11946,  4753, -1611,
   11943,  1051, -1611,   981, -1611, -1611, -1611,   524, -1611, -1611,
     524, -1611,   524, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611,   211,   352, -1611,  5215,  5215,  5215,  5215,  5215,  5215,
    5215,  5215,  5215,  5215,  5215, 11002,  5215,  5215,  5215,  5215,
    5215,  5215, -1611, -1611,  1101,   262,   937,  1233,   566, 11946,
   11946, 11946,  6378,  8461,  1105, 11002, 11946, -1611, -1611, -1611,
   11946,  1054,  1143,  1059,  2880, 11946, 11946, 12108, 11946, 12231,
   11946,  1054, 11946, 12120,  1054,  1002,  1202, 12266, 12373, 12408,
   12515, 12550, 12657,    53,   352,  1061,   249,  3828,  5448,  8692,
    1141,  1089,    12,   422,  1091,   239,    54,  8923,    12,   691,
      69, 11002,  1102, -1611, 11002, -1611, 11946, 11946, -1611, 11002,
     718,   322,   322,    70,   -21, -1611, 11002, -1611,  1067,  1069,
    1070,   -72, -1611, -1611,    75, -1611, 11002, -1611,   179,  5681,
   -1611,   222,  1099,  1084,  1081,   246,   819,  1093,  1087, -1611,
   -1611,  1097,  1088, -1611, -1611,   340,   340,  1389,  1389, 11773,
   11773,  1095,   488,  1103, -1611, 13793,   -67,   -67,   983,   340,
     340, 14470,  2187, 14414, 14375, 14862, 14241, 14509, 11424, 11591,
    1389,  1389,  1115,  1115,   488,   488,   488,   353, 11002,  1106,
    1108,   595, 11002,  1320,  1110, 13828, -1611,   224, -1611, -1611,
    2665, 11002, 11002, 11002, 11002, 11002, 11002, 11002, 11002, 11002,
   11002, 11002, 11002, 11002, 11002, 11002, 11002, 11002, -1611, -1611,
   -1611, -1611, 11946, -1611, -1611, -1611,   374, -1611,  1122, -1611,
    1123, -1611,  1132, -1611, 12120, -1611,  1002,   435,   902, -1611,
    1114, -1611,    21, -1611,   902,   902, -1611, 11002,  1136, -1611,
    1164, -1611, 11946, -1611, 11002, -1611,    78,   322, -1611,  1073,
   11002,   524, -1611,  1145, -1611, -1611, -1611, -1611,  1253, -1611,
   11943, -1611,    55, -1611,    68, 11002, -1611,   981,  1168,  1168,
   -1611, -1611, -1611,   352,   352,   352, -1611, -1611,   584, -1611,
     584, -1611,   584, -1611,   584, -1611,   584, -1611,   584, -1611,
     584, -1611,   584, -1611,   584, -1611,   584, -1611,   584, -1611,
   -1611,   584, -1611,   584, -1611,   584, -1611,   584, -1611,   584,
   -1611,   584,  1146,   566, -1611, -1611,   856, -1611,    79,   604,
    1265,  1531,   835,   671,   335,  1126,  1127,  1170,  1138,   142,
    1142,   857, 11946, 12120,  1002,  1562,  1144,  1137, 11946, -1611,
   -1611,  1579,  1587, -1611,  1708, -1611,  1884,  1148,  2411,   444,
    1150,   509,    55, -1611, -1611, -1611, -1611, -1611,  1153, 11002,
   -1611, 11002, 11002, 11002,  5914, 13651,   148, 11002,   733,   671,
     422, -1611, -1611,  1098, -1611, 11002, -1611,  1156, 11002, -1611,
   11002,   671,   797,  1157, -1611, -1611, 11002, -1611, -1611, -1611,
     510,   547,  1183,    93,    98, 11002,   322,   100, 14280, -1611,
   11002, 11002, 11946,   819, 11002, -1611,   227, -1611,  1165,   405,
   11233, -1611,   733, -1611, -1611,   246,  1217,  1218,  1173,  1223,
    1225, -1611,   559,   -40, -1611, 11002, -1611, 11002,  9154, 11002,
   -1611,  1199,  1181, -1611, -1611, 11002,  1186, -1611, 13935, 11002,
    9385,  1187, -1611, 13970, -1611,  9616, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,   902,
   -1611, -1611,  1234, -1611,  1235, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611,  1190, 11946, -1611, -1611,  1065,
   12692, -1611,  1391,    46, -1611, 11002,   109, -1611, 11946, 11002,
      55,   819,   524, -1611, -1611,   912, 11002, -1611,  1423,  3133,
      55, -1611,   582,   341, -1611, -1611, -1611, 11946,   604,  1403,
      79, -1611, -1611,   937, -1611, -1611, -1611, -1611,  1195, -1611,
   -1611, -1611,   601, -1611,  1197,  1244, -1611, -1611,  2448,   611,
     649, -1611, -1611, 11002,  2620, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611,  1201,  9847,   449, 12799, -1611, -1611,
      12,   422, -1611,  1203,   258,  1089, -1611, -1611, -1611, -1611,
    1091,   507,    12,  1200, -1611, -1611, -1611, -1611,   725, -1611,
   -1611, -1611,  1240, 11002, 11002,   737,   110, 11002, 12834, 12941,
    5212,   -40,   738, -1611,  1206,  5681,   415, -1611, -1611,  1250,
   -1611, -1611,   246,  1209,   152, 11946, 12976, 11946, 13083, -1611,
     489, 13118, -1611, 11002,  1435, 11002, -1611, 13225,  5681, -1611,
     493, 11002, -1611, -1611, -1611,   529, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611,   902, -1611,  1255, 11002,   367, 11002,   268,
     566,   380,   -40, -1611, -1611,   524, -1611,   566, -1611,   819,
    1256,  1212,   746,   268, -1611, -1611, -1611,  1403,   322,  1213,
    1216, -1611, -1611, 11002,  1258, 11002,  1237, -1611, -1611, -1611,
   -1611,  1220,  1221,  1224, 11002, 11002, 11002,  1226,  1390,  1227,
    1228, 10078, -1611,   563, 11002,   291,   422, -1611, 11002, 11002,
   11002, 11002,   797, -1611, 11002, 11002,  1190, -1611, -1611,   615,
     625, 11002, 11002,   748, -1611, -1611, -1611,  1239, 11002, -1611,
     589, -1611,  1222, -1611, -1611, 10309, -1611, -1611,  5363, -1611,
     858, -1611, -1611, -1611, 11946, 13260, 13367, -1611,   597, -1611,
   13402, -1611, -1611, -1611, -1611,   626, -1611, -1611, -1611,   152,
     122,  4522, -1611,   -40, -1611,   834, 11946,   213,   604, 15059,
   -1611, -1611, -1611, -1611,  1390,  1390,  1229,  1243,  1231,  1246,
    1252,  1254,  1259, 11002, -1611, 11002, -1611, -1611, -1611, 11002,
   -1611, -1611,  1390,  1390, -1611, 13509, -1611, 14146, 11002, 11002,
   -1611, 13544, -1611, -1611, 14146, -1611,   566, -1611, -1611,  1273,
    1268,  1274, 14146,   627, 11002,   419, -1611,   566,  1238, -1611,
   11002, -1611, -1611, -1611,   864, -1611, -1611,  1241, -1611,   524,
   -1611,   912, -1611, 10540, 10771, -1611, -1611, -1611, -1611, -1611,
   -1611,   524, 11946,   213,   827, 11002, -1611,   566, 15059,   -28,
     -28, -1611, 11002, -1611, 11002,  1390,  1390,   671,  1257,  1260,
    1054,   -28,   671, -1611,  1432,  1245, -1611, -1611,   304,  1288,
     703, -1611, 11002, 11002,  1261,  1289, 14146, -1611,   419,   703,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, 11002, 11002,
   -1611, -1611,   827, 11002, 11002,   566,   604,   524,   671,  1089,
    1282, -1611,  1263,  1264,  1266,  1269,   -28,   -28,  1089,  1270,
   -1611, -1611,  1275,  1278,  1279, 11002,  1267, 11002, 11002,  1276,
     703,   566, 14146, -1611, 11002,  1283, -1611, -1611, -1611, -1611,
   11002,   566,   566, -1611, -1611,   604,   629,  1262, -1611, -1611,
   -1611, -1611, -1611,  1280,  1290, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611,  1309,  1291, 14146, -1611,   566,
   -1611, -1611, -1611, -1611,   671, -1611, -1611, -1611, -1611,  1293,
   -1611,   632, -1611, -1611
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,   142,     1,   377,     0,     0,     0,   704,   378,     0,
     696,   696,   696,    17,    18,     0,     0,    16,    15,     3,
       0,    10,     9,     8,     0,     7,   685,     6,    11,     5,
       4,    13,    12,    14,   111,   112,   110,   120,   122,    47,
      66,    63,    64,     0,    49,    50,    51,     0,     0,    52,
      61,    48,   292,   291,   696,   696,    24,    23,   685,   698,
     697,   901,   891,   896,     0,   345,    45,   128,   129,   130,
       0,     0,     0,   131,   133,   140,     0,   127,    19,   718,
     717,   282,   706,   721,   686,   687,     0,     0,     0,     0,
       0,     0,    53,     0,     0,    62,     0,     0,    59,     0,
     625,   696,     0,    20,     0,     0,     0,   347,     0,     0,
     139,   134,     0,     0,     0,     0,     0,     0,   143,   720,
     719,   283,   285,   708,   707,     0,   723,   722,   726,   689,
     688,   691,   118,   119,   116,   117,   114,     0,     0,     0,
     113,   123,    67,    65,    55,    56,    54,    61,    58,    57,
     699,   622,   623,   701,   294,   293,   703,   625,   705,    21,
      22,    25,   902,   892,   897,   346,    43,    46,   138,     0,
     135,   136,   137,   141,   287,   286,   289,   284,   709,     0,
     714,   682,   608,    28,    29,    33,     0,   106,   107,   104,
     105,   103,   102,   108,     0,     0,    60,     0,   624,   702,
       0,    27,   808,     0,     0,    44,   132,     0,     0,   693,
     715,     0,   727,   683,     0,     0,   610,     0,    30,    31,
      32,     0,   121,   115,     0,    26,     0,     0,   893,   898,
       0,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   246,   247,   248,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,     0,
       0,   150,   144,     0,   784,   787,   790,   791,   785,   788,
     786,   789,     0,     0,   712,   724,   690,   608,     0,   124,
       0,   126,     0,   671,   669,   692,   109,     0,     0,     0,
       0,     0,     0,   734,   777,   735,   793,   736,   740,   741,
     742,   743,   783,   747,   748,   749,   750,   751,   752,   753,
     778,   779,   780,   781,   861,   739,   746,   782,   868,   875,
     737,   744,   738,   745,   754,   755,   756,   757,   758,   759,
     760,   761,   762,   763,   764,   765,   766,   767,   768,   769,
     770,   771,   772,   773,   774,   775,   776,     0,     0,     0,
       0,   792,   823,   826,   824,   825,   888,   700,   811,   812,
     809,   810,   801,   648,   654,   228,   229,   226,   153,   154,
     156,   155,   157,   158,   159,   160,   186,   187,   184,   185,
     177,   188,   189,   178,   175,   176,   227,   210,     0,   225,
     190,   191,   192,   193,   164,   165,   166,   161,   162,   163,
     174,     0,   180,   181,   179,   172,   173,   168,   167,   169,
     170,   171,   152,   151,   209,     0,   182,   183,   608,   147,
     322,   290,   693,   625,   710,     0,   716,   626,   728,     0,
       0,   125,     0,     0,     0,     0,   670,     0,   829,   852,
     855,     0,   858,   848,     0,     0,   862,   869,   876,   882,
     885,     0,   328,   838,   843,   837,     0,   851,   847,   840,
       0,     0,   842,   827,     0,     0,   894,   899,   230,   231,
     224,   208,   232,   211,   194,     0,   145,   376,   639,   640,
       0,     0,     0,   288,     0,     0,     0,   694,   713,   629,
     625,   609,     0,     0,   553,   554,     0,     0,     0,     0,
     548,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     783,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   597,     0,     0,     0,   430,   432,   431,   433,
     434,   435,   436,     0,     0,    39,   291,     0,     0,     0,
       0,     0,   326,     0,   412,   413,   551,   550,   330,   590,
     507,   581,   580,   579,   578,   142,   584,   549,   583,   582,
     556,   508,   557,     0,   509,     0,   552,   904,   908,   905,
     906,   907,   673,   674,     0,   667,   668,   666,     0,     0,
       0,     0,     0,     0,     0,     0,   814,     0,   144,     0,
     144,     0,   144,     0,     0,     0,   834,   326,   833,   845,
     846,   839,   841,     0,   844,   828,     0,     0,   890,   889,
     804,   903,   345,   817,   818,     0,   649,   644,     0,     0,
       0,   655,     0,   233,   213,   214,   216,   215,   217,   218,
     219,   220,   212,   221,   222,   223,   197,   198,   200,   199,
     201,   202,   203,   204,   195,   196,   205,   206,   207,     0,
     374,   375,     0,   608,   608,   608,   146,   149,   148,   324,
       0,    77,    78,    91,   362,   360,     0,     0,   100,     0,
       0,   361,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   300,     0,   301,     0,     0,     0,     0,   317,   312,
     309,   308,   310,   311,   295,   344,   323,   303,   590,   302,
       0,    85,    86,    83,   315,    84,   316,   318,   380,   307,
       0,   304,   591,   437,   711,   625,   627,     0,     0,   725,
     608,   684,   950,   953,   350,   354,   353,   359,     0,     0,
     398,     0,     0,     0,   986,     0,     0,   330,     0,   389,
     392,     0,   395,     0,   990,     0,   959,   968,     0,   956,
       0,   536,   537,     0,     0,     0,     0,     0,     0,     0,
     928,     0,     0,     0,   966,   993,     0,   334,   337,     0,
       0,   513,   512,   546,   511,   510,     0,     0,     0,  1004,
     407,  1004,   414,     0,     0,   995,  1004,   588,     0,   422,
       0,     0,     0,     0,   538,   539,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   497,     0,   672,     0,     0,   676,     0,
     681,     0,   680,     0,     0,     0,   819,   832,     0,     0,
     794,   813,     0,     0,   147,     0,   147,     0,   147,   646,
       0,   652,     0,   795,     0,  1004,   836,   821,     0,   802,
     799,     0,   803,     0,   650,   895,     0,   656,   900,     0,
       0,   729,   636,   637,   659,   641,   642,   643,     0,     0,
       0,     0,   366,   363,   591,   437,     0,     0,   348,     0,
       0,     0,   321,     0,     0,    70,    95,     0,     0,   371,
     368,   413,   425,   142,   343,   341,   342,     0,   319,   320,
       0,    89,     0,   428,   298,   306,   313,   314,   365,   370,
     379,     0,     0,   305,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   297,   695,     0,     0,   616,   619,     0,     0,
       0,     0,   942,     0,     0,     0,     0,   976,   979,   982,
       0,  1004,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1004,     0,     0,  1004,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   345,     0,     0,     0,
     962,   920,   928,     0,   971,     0,     0,     0,   928,     0,
       0,     0,     0,   931,     0,   998,     0,     0,    42,     0,
      40,     0,     0,     0,     0,   973,  1005,   327,     0,     0,
       0,   484,   481,   483,     0,   997,  1005,   331,     0,   326,
     500,     0,  1004,     0,     0,     0,   144,     0,     0,   567,
     566,     0,     0,   568,   572,   514,   515,   527,   528,   525,
     526,     0,   562,     0,   544,     0,   585,   586,   587,   516,
     517,   532,   533,   534,   535,     0,     0,   530,   531,   529,
     523,   524,   519,   518,   520,   521,   522,     0,     0,     0,
     490,     0,     0,     0,     0,     0,   505,     0,   675,   678,
     437,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   679,   830,
     853,   856,     0,   859,   849,   796,     0,   863,     0,   870,
       0,   877,     0,   883,     0,   886,     0,     0,   332,  1005,
       0,   822,   807,   800,   645,   651,   638,     0,     0,   658,
       0,   657,     0,   660,     0,    96,     0,     0,   367,   364,
       0,     0,   349,     0,    97,    98,    68,    69,     0,   372,
     369,   414,   422,   325,    73,     0,   322,   142,     0,     0,
     388,   387,   340,     0,     0,     0,   459,   468,   447,   469,
     448,   471,   450,   470,   449,   472,   451,   462,   441,   463,
     442,   464,   443,   473,   452,   474,   453,   461,   439,   440,
     475,   454,   476,   455,   465,   444,   466,   445,   467,   446,
     460,   438,     0,   143,   617,   618,   619,   620,   611,   625,
       0,     0,     0,   943,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   999,
     558,     0,     0,   559,     0,   589,     0,     0,     0,     0,
       0,     0,   422,   592,   593,   594,   595,   596,     0,     0,
     929,     0,     0,     0,     0,   407,   928,     0,     0,     0,
       0,   937,   938,     0,   945,     0,   935,     0,     0,   974,
       0,     0,     0,     0,   933,   975,     0,   965,   930,   994,
       0,     0,    36,     0,     0,     0,     0,     0,   408,   555,
       0,     0,     0,   144,     0,   996,     0,   501,     0,     0,
       0,   504,  1005,   919,   502,     0,     0,     0,     0,     0,
       0,   420,     0,   147,   563,     0,   569,     0,     0,     0,
     542,     0,     0,   573,   577,     0,     0,   545,     0,     0,
       0,     0,   491,     0,   498,     0,   540,   506,   677,   447,
     448,   450,   449,   451,   441,   442,   443,   452,   453,   439,
     454,   455,   444,   445,   446,   438,   831,   854,   857,   820,
     860,   850,     0,   815,     0,   864,   866,   871,   873,   878,
     880,   884,   647,   887,   653,   328,     0,   329,   805,   806,
       0,   731,   732,   662,   661,     0,     0,   373,     0,     0,
     422,   144,     0,    71,    72,    73,     0,    88,    79,     0,
     422,   381,     0,     0,   458,   456,   457,     0,   625,   614,
     611,   612,   613,   616,   630,   951,   954,   351,     0,   356,
     357,   355,     0,   401,     0,     0,   404,   399,     0,     0,
       0,   987,   985,   330,     0,   390,   393,   396,   991,   989,
     960,   969,   967,   957,     0,     0,     0,     0,   910,   909,
     928,     0,   963,     0,     0,   921,   944,   936,   964,   934,
     972,     0,   928,     0,   940,   941,   948,   932,     0,   335,
     338,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   147,     0,   503,     0,   326,     0,   417,   418,     0,
     416,   415,     0,     0,     0,     0,     0,     0,     0,   479,
       0,     0,   574,     0,   547,     0,   543,     0,   326,   492,
       0,     0,   541,   499,   495,     0,   798,   816,   797,   867,
     874,   881,   835,   333,   730,     0,     0,     0,     0,     0,
       0,     0,   147,    74,    87,     0,    80,     0,   296,   144,
       0,     0,   669,     0,   635,   615,   631,   614,     0,     0,
       0,   352,   358,     0,     0,     0,     0,   400,   977,   980,
     983,     0,     0,     0,     0,     0,     0,     0,   942,     0,
       0,     0,   598,     0,     0,     0,     0,   946,     0,     0,
       0,     0,     0,   939,     0,     0,   328,    34,    41,     0,
       0,     0,     0,     0,   482,   607,   485,     0,     0,   477,
       0,   424,     0,   421,   423,     0,   409,   427,     0,   606,
       0,   604,   480,   601,     0,     0,     0,   600,     0,   493,
       0,   496,   733,   663,    92,     0,   101,    99,   299,     0,
      73,     0,    90,   147,   382,   669,     0,     0,   625,     0,
     633,   665,   664,   621,   942,   942,     0,     0,     0,     0,
       0,     0,     0,   326,  1000,   330,   391,   394,   397,     0,
     943,   961,   942,   942,   560,     0,   599,  1002,     0,     0,
     947,     0,   912,   911,  1002,   949,  1002,   336,   339,    38,
       0,     0,  1002,     0,     0,     0,   488,  1002,     0,   419,
       0,   410,   564,   570,     0,   605,   603,     0,   602,     0,
     426,    73,    75,   362,     0,    81,    85,    86,    83,    84,
      82,     0,     0,     0,     0,     0,   628,     0,     0,   927,
     927,   402,     0,   405,     0,   942,   942,   917,     0,     0,
    1004,   927,   917,   561,     0,     0,   914,   913,     0,     0,
       0,    35,     0,     0,     0,     0,  1002,   486,     0,     0,
     478,   411,   565,   571,   575,   494,    94,    76,     0,     0,
     368,   429,     0,     0,     0,     0,   625,     0,     0,   924,
    1004,   926,     0,     0,     0,     0,   927,   927,   918,     0,
     988,  1001,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1002,  1002,  1006,     0,     0,   489,  1013,   576,   369,
       0,     0,     0,   386,   632,   625,     0,  1005,   925,   952,
     955,   403,   406,     0,     0,   984,   992,   970,   958,  1003,
    1011,   916,   915,  1012,  1014,     0,     0,  1002,  1010,     0,
     385,   384,   634,   922,     0,   978,   981,  1009,  1007,     0,
     383,     0,  1008,   923
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1611, -1611,    -1, -1611, -1611, -1611, -1611, -1611,   731,  1450,
   -1611, -1611, -1611, -1611, -1611, -1611,  1536, -1611, -1611, -1611,
     886,   527, -1611,  1392, -1611, -1611,  1455, -1611, -1611, -1611,
   -1388, -1611, -1611, -1611,  -115, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611,  1326, -1611, -1611,   -39,
     -66, -1611, -1611, -1611,   679,   816,  -487,  -585,  -823, -1611,
   -1611, -1611, -1611, -1605, -1611, -1611,    -5,  -209,  -282,  -490,
   -1611,   368, -1611,  -609, -1351,  -747,    14,  -274, -1611, -1611,
   -1611, -1611,  -565,     0, -1611, -1611, -1611, -1611, -1611,  -112,
    -105,  -104, -1611,   -99, -1611, -1611, -1611,  1564, -1611,   378,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611,  -453,   -96,   178,    47,   233, -1132,  -671,
   -1611,  -707, -1611, -1611,  -495,  1010, -1611, -1611, -1611, -1573,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,  1074,
   -1611, -1611, -1611, -1611, -1611, -1611,  1339, -1611,  -170,   133,
      -6,   136,   344, -1611,  -154, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611,   452,  -448,  -954, -1611,  -457,  -953, -1611,  -874,
       7,    15, -1611,  -587, -1516, -1611,  -415, -1611, -1611,  1532,
   -1611, -1611, -1611,  1163,  1135,   342, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611,  -728,   348, -1611,  1083, -1611, -1611,   446, -1611,
    1285, -1611, -1611, -1611,  -455, -1611, -1611,  -438, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611,  -219, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,  1094,
    -756,  -149,  -936,  -761, -1611, -1611, -1439,  -951, -1611, -1611,
   -1611, -1255,     9, -1179, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611,   321,  -539, -1611, -1611, -1611,   842, -1611,
   -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611, -1611,
   -1611, -1611, -1611, -1610,  -788, -1611
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,   634,    18,   161,    58,   201,    19,   186,   192,
    1709,  1502,  1617,   789,   566,   167,   567,   109,    21,    22,
      49,    50,    51,    98,    23,    41,    42,   704,   705,  1426,
    1427,   706,  1567,  1661,   707,   708,  1185,   709,   899,   900,
     710,   711,   712,   713,  1419,   909,   193,   194,    37,    38,
      39,   216,    73,    74,    75,    76,    24,   439,   503,   282,
     122,    25,   176,   283,   177,   207,   568,   156,   922,  1196,
     716,   504,   717,   798,   618,   804,  1147,   569,  1026,  1615,
    1027,  1616,   719,   570,   720,   745,   971,  1581,   571,   721,
     722,   723,   724,   725,   726,   727,   672,   728,   941,  1432,
    1190,   729,   572,   985,  1594,   986,  1595,   988,  1596,   573,
     976,  1587,   574,   799,  1637,   575,  1341,  1342,  1056,   924,
     576,   962,  1187,   577,   851,  1197,   731,   578,   579,  1043,
     580,  1322,  1715,  1323,  1778,   581,  1103,  1543,   582,   732,
    1525,  1782,  1527,  1783,  1644,  1828,   784,   584,   497,  1443,
    1576,  1236,  1238,   968,   153,   509,   964,   740,  1669,  1748,
     498,   499,   500,   869,   870,   486,   871,   872,   487,  1283,
     892,   893,  1673,   598,   457,   304,   305,   213,   297,    85,
     131,    27,   182,   293,    99,   100,   197,   101,    28,    55,
     125,   179,    29,   446,   211,   212,    83,   128,   448,    30,
     180,   295,   894,   585,   292,   373,   374,  1136,   882,   485,
     227,   375,   862,  1547,  1144,   855,   483,   376,   599,  1386,
     874,   604,  1391,   600,  1387,   601,  1388,   603,  1390,   607,
    1395,   608,  1549,   609,  1397,   610,  1550,   611,  1399,   612,
    1551,   613,  1401,   614,  1403,   637,    31,   105,   203,   383,
     638,    32,   106,   204,   384,   642,    33,   104,   202,   586,
    1799,  1809,  1053,  1012,  1800,  1801,  1802,  1013,  1025,  1305,
    1299,  1294,  1496,  1246,   587,   969,  1579,   970,  1580,   995,
    1600,   992,  1598,  1014,   805,   588,   993,  1599,  1015,   589,
    1252,  1680,  1253,  1681,  1254,  1682,   980,  1591,   990,  1597,
     786,   806,   590,  1765,  1037,   591
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      17,   441,    54,   199,   296,   377,   785,   849,   875,   730,
     983,   934,   217,  1038,   715,    66,    77,   594,  1047,    78,
    1164,  1018,   738,   864,  1011,   866,  1011,   868,   925,   926,
     640,   636,   641,   850,   510,  1486,  1245,  1564,   635,  1269,
     751,  1138,  1271,  1140,   619,  1142,   629,   169,   141,  -142,
    1421,  1003,  1052,  1016,  1552,  1020,  1667,    34,    35,  1054,
     621,  1290,    94,  -865,  1747,  1004,  -872,  1302,  1033,  -879,
      77,    77,    77,  1279,  1300,  1044,    87,  -487,   132,   133,
    1422,   736,   820,   890,   444,   822,   823,  1150,   809,  1306,
    1315,  1423,  1424,   214,  1769,  1324,  1770,    95,  1415,   822,
     823,   158,  1774,   206,   891,   780,   782,  1779,   715,   501,
     801,    52,  1328,  1503,    77,    77,    77,    77,  1504,   902,
    1507,    64,   810,   811,   942,  1441,   181,   449,   108,  1558,
    1622,    53,   919,  -865,  1422,    56,  -872,    40,  -865,  -879,
    1474,  -872,  1777,  1797,  -879,  1423,  1424,  -487,   298,  1743,
    1032,    65,  -487,  1005,   890,   215,  -865,    13,    64,  -872,
     752,   753,  -879,   114,   115,   116,  1825,   763,  1326,  1073,
    -487,  1166,   843,   844,   209,   891,   299,    14,   226,   502,
     884,   883,  -808,    57,  1074,   887,   843,   844,    65,   670,
     187,   188,   221,  1256,   715,     2,  1159,   748,   228,   229,
      13,  1004,     3,  1267,    59,  1826,  1270,   715,  1442,  1408,
      60,  1855,  1856,   473,  1798,   301,  1052,    67,    84,   222,
      14,  1316,   382,   302,   371,     4,  1607,     5,   154,     6,
     718,   903,   671,   620,    36,     7,    86,   880,  1055,   168,
     474,   475,   814,   815,   303,     8,    68,  1869,   155,   622,
     820,     9,   134,   822,   823,   824,  1425,   135,   754,   136,
     825,   451,   137,  1161,  1333,  1708,   484,   623,    96,  1160,
    1160,  1192,  1732,   624,    87,    10,   631,   755,   440,    97,
      88,   737,   677,   678,  1109,  1160,  1160,   442,  1561,   507,
     447,  1160,  1052,  1329,  1160,   714,   734,    89,  1569,  1459,
     739,  1460,   981,  1313,  1314,   138,  1317,  1448,   139,  1160,
    1731,  1803,   991,    69,  1160,   994,  1160,  1635,   982,    13,
      11,    12,  1813,    90,   718,  1160,  1160,   476,   151,  1005,
      13,   477,   996,  1280,   154,  1481,  1168,   107,    52,    14,
     843,   844,    70,  1787,  1326,   807,    93,   495,   152,    64,
      14,  1700,   214,  1179,   155,  1051,   741,   506,    53,   715,
    1005,   810,   811,   595,   189,  1159,  1454,  1843,  1844,   190,
     472,   191,    59,   596,   137,  1326,   300,  1159,    60,    65,
     853,   854,   856,    13,   858,   859,   302,  1282,   863,   108,
     865,   808,   867,  1107,  1188,   495,  1336,   102,   478,  1159,
     214,  1132,   479,    14,   906,   480,  1337,   303,  1159,  1282,
     718,   715,   496,   916,   215,   108,    71,  1146,  1609,  1691,
     481,   117,  1327,   718,    15,    72,   482,    13,   715,   885,
     597,  1160,  1161,   888,  1162,    16,  1182,  1163,  1330,  1416,
    1170,  1159,  1338,   157,  1161,   508,   118,    14,  1169,    43,
    1296,  1698,    87,  1189,  1159,   371,    13,   183,   184,  1028,
    1029,   674,   215,  1339,  1817,  1331,  1161,  1367,  1340,   675,
      13,  1343,    44,    45,    46,  1161,    14,   450,   117,  1178,
    1297,   814,   815,   879,   371,  1309,   371,  1052,   484,   820,
      14,   821,   822,   823,   824,  1749,  1750,   890,   633,   825,
     119,   371,   371,  1233,    91,    47,  1143,  1325,  1161,   810,
     811,   880,   881,  1761,  1762,    48,   371,   749,   891,  1244,
    1524,  1161,  1434,  1435,  1436,  1480,  1191,  1258,   113,  1606,
    1011,  1240,  1241,  1485,  1356,    13,    43,   120,    52,  1556,
    1492,  1612,  1255,   371,   371,  1011,   121,  1261,  1262,  1357,
    1264,  1170,  1266,    52,  1268,    14,   801,  1570,    53,    44,
      45,    46,    13,   633,   801,   838,   839,   840,   841,   842,
     967,  1145,   372,    53,    92,   718,  1806,  1807,  1449,   843,
     844,   963,    14,  1170,  1572,    64,   512,   513,  1506,   616,
    1392,   142,    47,   848,  1039,  1045,   564,   921,  1393,   371,
     371,   371,    48,   371,   371,    64,   519,   371,   617,   371,
    1610,   371,   521,   371,  1039,    65,  1165,   144,   145,  1040,
     146,  1288,  1601,    13,   564,   921,   473,   718,  1174,   814,
     815,  1522,    13,  1291,  1292,    65,    52,   820,    97,   821,
     822,   823,   824,    14,   718,  1183,  1514,   825,  1184,   528,
     529,   633,    14,   474,   475,  1148,    53,  1604,  1631,  1405,
     633,   147,  1041,  1293,  1154,  1170,   150,  1155,  1471,   208,
     718,   718,   718,   718,   718,   718,   718,   718,   718,   718,
     718,   440,   718,   718,   718,   718,   718,   718,  1627,  1404,
     440,   912,  1406,   440,   440,   440,  1402,    13,    13,   114,
    1430,   116,   123,   928,   929,  1170,   531,   532,   124,  1170,
      52,    79,    80,   162,    81,  1611,  1592,    14,    14,   935,
     936,   937,   938,  1170,   939,   633,   633,   843,   844,   943,
      53,  1699,  1642,  1473,  1499,    13,  1649,    77,  1511,  1659,
     476,    13,    82,   595,   477,  1170,   163,    64,   973,   110,
     111,   112,  1242,   596,    13,    14,   371,  1251,    13,  1630,
      13,    14,   166,   633,   543,   544,   545,    52,   639,   633,
     371,  1500,  1651,   484,    14,  1522,  1361,    65,    14,  1170,
      14,    13,  1648,   164,   126,  1024,   633,   556,   633,    13,
     127,  1362,   151,   170,   171,   172,   173,   195,  1570,    13,
    1523,    14,  1042,   372,   744,  1288,  1696,  1148,  1148,    14,
     597,   478,   152,  1288,  1458,   479,  1146,   633,   480,    14,
    1464,   562,   198,  1571,   165,  1583,  1476,   633,   564,   921,
    1718,  1170,   372,   481,   372,  1589,  1562,    13,  1727,   482,
    1741,  1170,  1170,  1170,   378,  1288,   178,  1491,  1288,   372,
     372,  1128,  1005,  1498,  1658,  1406,  1406,    14,  1710,   379,
     473,    13,  1505,    95,   380,   633,   381,  1326,  1711,  1729,
    1775,  1512,  1863,  1590,   371,  1873,   923,   923,   923,    13,
    1022,    14,  1023,   371,  1510,   756,   371,   474,   475,  1417,
     154,   372,   372,   440,  1818,  1530,   933,   764,  1303,    14,
     154,  1304,   129,  1439,   757,   440,   154,  1540,   130,   443,
     155,   933,  1545,  1389,  1483,   630,   765,   371,   218,   219,
     155,   767,   440,  1237,  1422,   440,   155,  1186,   200,  1484,
     205,   974,   210,  1614,   730,  1423,  1424,   440,  1759,   715,
     768,  1170,   114,  1413,   225,  1621,  1628,   372,   372,   372,
     975,   372,   372,  1170,  1170,   372,  1714,   372,   223,   372,
     454,   372,  1557,   455,  1170,  1666,   456,  1239,   456,   371,
     371,   371,  1812,   159,   476,   174,   371,   595,   477,   160,
     371,   175,   148,   149,  1663,   371,   371,   596,   371,   -82,
     371,   484,   371,   371,  1234,  1129,   224,  1584,   484,   440,
    1235,  1808,  1130,   226,  1493,  1146,  1808,  1494,   294,   484,
    1495,  1289,  1838,  1133,  1298,   484,   484,  1289,  1298,  1134,
    1137,   484,  1603,   436,   484,  1139,   371,   371,  1141,   437,
     933,   644,   645,   646,   647,   648,   649,   650,   651,   284,
    1310,  1311,  1836,   285,   597,   478,   114,   115,   116,   479,
    1619,  1620,   480,  1742,  1623,   484,   456,   286,   287,  1447,
     652,   438,   288,   289,   290,   291,   445,   481,   452,   453,
     653,   654,   655,   482,  1758,  1706,   458,   484,   484,   461,
    1745,  1457,  1723,   933,   484,  1444,   459,  1638,  1784,  1717,
      44,    45,    46,   183,   184,   185,   460,   462,   933,   218,
     219,   220,   464,   463,   372,  1655,   466,   467,  1871,  1368,
     944,   945,   946,   947,   948,   949,   950,   951,   372,   468,
     923,   469,   484,   952,   953,   895,   896,   897,   470,   954,
     471,   488,   371,   491,   489,  1394,   810,   811,   490,   955,
    1563,   492,   956,   957,   371,    61,    62,    63,   493,   958,
     959,   960,   494,   592,   511,   718,  1793,  1794,  1060,  1064,
     627,   593,   371,   605,   606,   643,   440,   669,   673,  1713,
     676,   742,   743,  1078,   750,   758,   473,   759,   760,   762,
     790,   761,   923,   847,   766,   763,   769,  1553,   440,   440,
     440,  1104,   773,   770,   787,   774,   961,   788,   639,  1559,
     775,   776,   861,   474,   475,  1830,   886,   802,   777,   876,
     656,   657,   658,   659,   660,   661,   662,   663,  1573,   778,
    1568,    16,   372,   564,   921,   846,   911,   860,  1744,   664,
     913,   372,  1438,  1821,   372,   473,  1760,   -93,   917,   665,
     931,   932,  1636,   940,   966,   972,   977,   978,  1455,   666,
     667,   668,   371,   371,   979,  1021,   814,   815,   371,  1031,
    1034,  1035,   474,   475,   820,   372,   821,   822,   823,   824,
    1036,  1046,  1071,  1108,   825,  1654,   942,  1131,  1135,  1149,
     903,  1153,  1157,  1660,  1574,  1158,   473,  1167,   933,  1170,
     476,  1171,  1173,  1177,   477,  1175,  1181,  1232,   473,  1176,
    1237,  1249,  1259,  1281,  1792,  1288,  1287,  1295,  1640,  1308,
    1319,  1320,  1321,   474,   475,  1332,  1344,   372,   372,   372,
    1346,  1364,   371,  1335,   372,   474,   475,  1334,   372,  1345,
    1347,    13,  1411,   372,   372,  1169,   372,  1348,   372,  1487,
     372,   372,   840,   841,   842,  1349,  1396,  1398,  1359,   476,
    1360,    14,  1365,   477,   843,   844,  1400,  1407,   933,   633,
    1412,   478,  1418,  1437,  1431,   479,  1452,  1257,   480,  1450,
    1451,   923,   923,   923,   372,   372,   933,  1636,   933,  1463,
     933,  1453,   933,   481,   933,  1456,   933,  1462,   933,   482,
     933,  1469,   933,  1472,   933,  1475,   933,  1489,  1497,   933,
     476,   933,  1501,   933,   477,   933,   371,   933,  1513,   933,
     810,   811,   476,  1517,  1518,  1519,   477,   440,   371,  1520,
     478,  1521,  1532,  1533,   479,  1724,  1272,   480,  1535,  1541,
    1546,  1548,   617,  1354,  1555,  1566,  1575,   371,  1582,  1585,
    1586,  1613,   481,  1601,  1618,  1608,  1632,  1786,   482,  1629,
    1634,  1652,  1664,  1665,  1677,  1674,   810,   811,  1675,  1791,
    1690,  1679,  1683,  1716,  1684,  1719,  1685,  1752,  1689,  1692,
    1693,   478,  1751,  1771,  1753,   479,  1772,  1420,   480,  1289,
     372,  1780,  1773,   478,  1785,  1815,  1816,   479,  1754,  1445,
     480,  1289,   372,   481,  1755,  1819,  1756,  1824,  1837,   482,
    1810,  1757,  1823,  1811,  1864,   481,  1839,  1840,  1850,  1841,
     372,   482,  1842,  1845,  1746,  1835,  1867,  1853,  1846,   440,
    1030,  1847,  1848,  1865,  1858,   371,   583,   371,   812,   813,
     814,   815,  1868,  1866,  1872,   602,   140,    20,   820,   196,
     821,   822,   823,   824,   143,   615,  1735,   306,   825,  1736,
     826,   827,   440,   965,  1429,   626,  1737,  1738,  1656,  1657,
     440,  1820,  1739,  1730,   473,    26,  1662,  1433,  1516,  1633,
    1827,  1670,  1668,  1577,   812,   813,   814,   815,   816,  1578,
    1440,   817,   818,   819,   820,  1671,   821,   822,   823,   824,
     103,   474,   475,  1672,   825,   473,   826,   827,  1409,   746,
     372,   372,   828,   829,   830,   505,   372,   465,   771,   772,
     747,  1854,   473,  1814,   838,   839,   840,   841,   842,  1490,
     473,  1705,   474,   475,  1019,     0,     0,     0,   843,   844,
       0,   791,   792,   793,   794,   795,   800,   800,     0,   474,
     475,     0,  1834,     0,   371,     0,     0,   474,   475,     0,
       0,     0,     0,   832,   440,   833,   834,   835,   836,   837,
     838,   839,   840,   841,   842,     0,   371,     0,     0,     0,
     372,     0,     0,     0,   843,   844,     0,     0,   476,     0,
       0,  1862,   477,     0,     0,     0,     0,     0,     0,     0,
       0,   800,     0,     0,     0,     0,  1764,     0,     0,     0,
       0,   878,     0,  1764,     0,  1764,     0,     0,     0,   476,
       0,  1764,     0,   477,     0,  1042,  1764,     0,     0,     0,
       0,     0,     0,     0,   440,     0,   476,     0,     0,     0,
     477,     0,     0,     0,   476,     0,   440,     0,   477,   933,
       0,   473,   371,   889,     0,     0,  1796,     0,     0,   478,
       0,     0,     0,   479,   372,  1446,   480,     0,   904,     0,
       0,     0,     0,     0,     0,     0,   372,     0,   474,   475,
       0,   481,     0,     0,     0,  1764,     0,   482,  1042,     0,
     478,     0,     0,     0,   479,   372,  1461,   480,     0,     0,
       0,     0,   440,     0,  1833,     0,     0,   478,     0,     0,
       0,   479,   481,  1465,   480,   478,     0,     0,   482,   479,
       0,  1466,   480,     0,     0,     0,     0,     0,     0,   481,
    1764,  1764,     0,     0,     0,   482,     0,   481,     0,   800,
    1860,  1861,   984,   482,     0,   987,     0,   989,     0,   800,
       0,     0,   800,   733,     0,   735,     0,   997,   998,   999,
    1000,  1001,  1002,     0,     0,   476,  1764,     0,  1870,   477,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   372,     0,   372,     0,     0,     0,     0,
       0,     0,   800,     0,     0,     0,  1065,  1066,     0,     0,
    1067,  1068,  1069,  1070,     0,  1072,     0,  1075,  1076,  1077,
    1079,  1080,  1081,  1082,  1083,  1084,  1086,  1087,  1088,  1089,
    1090,  1091,  1092,  1093,  1094,  1095,  1096,   473,  1105,     0,
     800,     0,     0,     0,     0,     0,   478,     0,     0,     0,
     479,     0,  1467,   480,     0,  -407,     0,   852,     0,     0,
       0,     0,     0,     0,   474,   475,   810,   811,   481,     0,
       0,     0,     0,     0,   482,  1199,  1201,  1203,  1205,  1207,
    1209,  1211,  1213,  1215,  1217,     0,  1220,  1222,  1224,  1226,
    1228,  1230,     0,     0,     0,   904,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   372,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   372,     0,     0,     0,     0,   898,
       0,     0,     0,   905,     0,     0,   908,     0,   910,     0,
       0,   476,     0,   915,     0,   477,   920,     0,     0,     0,
       0,   927,     0,     0,     0,   930,   800,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   810,
     811,     0,     0,     0,   812,   813,   814,   815,   816,     0,
       0,   817,   818,   819,   820,     0,   821,   822,   823,   824,
       0,   791,  1285,   800,   825,     0,   826,   827,     0,     0,
     372,   800,   828,   829,   830,     0,     0,     0,   831,     0,
       0,     0,   478,     0,     0,     0,   479,     0,  1468,   480,
    1318,     0,     0,  -407,     0,     0,     0,     0,     0,  1010,
       0,  1010,     0,   800,   481,     0,     0,     0,     0,     0,
     482,     0,     0,  -407,     0,     0,     0,     0,     0,     0,
       0,  -407,     0,   832,     0,   833,   834,   835,   836,   837,
     838,   839,   840,   841,   842,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   843,   844,     0,     0,     0,     0,
       0,     0,  1358,     0,     0,     0,  1363,   812,   813,   814,
     815,   816,     0,     0,   817,   818,   819,   820,  1110,   821,
     822,   823,   824,     0,     0,     0,     0,   825,     0,   826,
     827,     0,     0,     0,     0,   828,   829,   830,   810,   811,
       0,   831,     0,     0,     0,     0,     0,     0,     0,     0,
    1152,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1410,     0,     0,     0,     0,     0,     0,     0,     0,
     905,     0,     0,     0,  1318,     0,  1172,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   832,  1180,   833,   834,
     835,   836,   837,   838,   839,   840,   841,   842,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   843,   844,     0,
       0,   845,     0,  1198,  1200,  1202,  1204,  1206,  1208,  1210,
    1212,  1214,  1216,  1218,  1219,  1221,  1223,  1225,  1227,  1229,
    1231,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1248,     0,  1250,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   812,   813,   814,   815,
     816,     0,     0,   817,   818,   819,   820,     0,   821,   822,
     823,   824,     0,     0,     0,     0,   825,     0,   826,   827,
       0,     0,     0,   800,   828,  1477,   830,     0,   800,     0,
    1307,     0,     0,     0,     0,     0,   810,   811,  1312,     0,
       0,     0,     0,     0,   800,     0,     0,     0,     0,     0,
     800,     0,     0,     0,     0,     0,     0,     0,     0,   800,
       0,     0,     0,     0,  1508,  1509,     0,     0,   800,     0,
       0,     0,     0,     0,  1318,     0,     0,   833,   834,   835,
     836,   837,   838,   839,   840,   841,   842,     0,     0,  1526,
       0,  1528,   800,  1531,     0,     0,   843,   844,     0,  1534,
       0,     0,     0,  1537,   800,     0,     0,     0,     0,   800,
       0,     0,     0,     0,   473,     0,     0,     0,     0,     0,
    1369,  1370,  1371,  1372,  1373,  1374,  1375,  1376,  1377,  1378,
    1379,  1380,  1381,  1382,  1383,  1384,  1385,     0,     0,     0,
       0,   474,   475,     0,     0,     0,     0,     0,     0,     0,
       0,   473,     0,     0,   812,   813,   814,   815,   816,   800,
       0,   817,   818,   819,   820,     0,   821,   822,   823,   824,
       0,     0,     0,  1414,   825,     0,   826,   827,   474,   475,
       0,     0,   828,   829,   830,     0,     0,     0,   831,     0,
       0,     0,     0,     0,  1428,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   800,
       0,     0,     0,     0,     0,     0,     0,     0,   476,     0,
       0,     0,   477,   832,     0,   833,   834,   835,   836,   837,
     838,   839,   840,   841,   842,     0,     0,   800,   800,     0,
       0,   800,     0,     0,   843,   844,     0,     0,   857,   800,
       0,     0,     0,     0,     0,   476,     0,     0,     0,   477,
       0,     0,     0,     0,     0,     0,     0,  1645,     0,  1646,
       0,     0,   800,     0,     0,  1650,     0,     0,     0,     0,
       0,  1478,  1479,     0,     0,     0,  1482,     0,     0,   478,
       0,     0,   800,   479,  1488,  1470,   480,  1010,     0,     0,
     779,     0,     0,     0,     0,     0,   307,     0,     0,     0,
       0,   481,   308,   473,     0,     0,     0,   482,   309,     0,
       0,     0,     0,     0,     0,     0,   478,     0,   310,     0,
     479,     0,  1588,   480,     0,  1695,   311,     0,  1697,     0,
     474,   475,  1701,     0,     0,  1704,     0,     0,   481,     0,
       0,   312,     0,     0,   482,  1712,   800,     0,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,     0,     0,     0,   800,  1560,   810,
     811,     0,     0,   800,     0,  1565,     0,   476,   733,     0,
       0,   477,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1776,     0,
       0,     0,     0,    64,     0,     0,  1111,  1112,  1113,  1114,
    1115,  1116,  1117,  1118,     0,     0,   369,   800,     0,  1119,
    1120,     0,     0,     0,     0,  1121,     0,     0,     0,     0,
       0,     0,     0,    65,     0,   955,     0,     0,  1122,  1123,
       0,     0,     0,     0,     0,  1124,  1125,  1126,   478,     0,
       0,     0,   479,     0,  1593,   480,     0,  1822,     0,     0,
       0,     0,     0,    13,     0,     0,     0,     0,     0,     0,
     481,     0,   800,     0,   810,   811,   482,     0,     0,     0,
       0,   370,     0,    14,     0,     0,     0,   812,   813,   814,
     815,   816,  1127,     0,   817,   818,   819,   820,     0,   821,
     822,   823,   824,     0,     0,  1653,     0,   825,  1857,   826,
     827,   810,   811,     0,     0,   828,   829,   830,     0,   564,
     921,   831,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1676,     0,  1678,     0,     0,     0,     0,     0,
       0,     0,     0,  1686,  1687,  1688,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1702,  1703,
       0,     0,     0,     0,  1707,     0,   832,     0,   833,   834,
     835,   836,   837,   838,   839,   840,   841,   842,     0,     0,
       0,     0,     0,     0,  1721,     0,     0,   843,   844,     0,
       0,   873,   812,   813,   814,   815,   816,     0,     0,   817,
     818,   819,   820,     0,   821,   822,   823,   824,     0,     0,
    1740,     0,   825,     0,   826,   827,     0,     0,     0,     0,
     828,   829,   830,     0,     0,     0,   831,     0,     0,   812,
     813,   814,   815,   816,     0,     0,   817,   818,   819,   820,
       0,   821,   822,   823,   824,     0,     0,  1766,  1767,   825,
       0,   826,   827,     0,     0,     0,     0,   828,   829,   830,
       0,     0,     0,   831,     0,     0,     0,     0,     0,  1781,
       0,   832,     0,   833,   834,   835,   836,   837,   838,   839,
     840,   841,   842,  1790,     0,     0,     0,     0,     0,     0,
       0,     0,   843,   844,  1795,     0,  1156,     0,     0,     0,
       0,  1804,     0,  1805,     0,     0,     0,     0,   832,     0,
     833,   834,   835,   836,   837,   838,   839,   840,   841,   842,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   843,
     844,     0,     0,  1260,     0,     0,     0,     0,  1829,     0,
       0,     0,  1831,  1832,   679,     0,     0,     0,   512,   513,
       3,     0,   680,   681,   682,     0,   683,     0,   514,   515,
     516,   517,   518,     0,  1849,     0,  1851,  1852,   519,   684,
     520,   685,   686,     0,   521,     0,     0,     0,     0,  1859,
       0,   687,   522,   688,     0,   689,     0,   690,   523,     0,
       0,   524,     0,     8,   525,   691,     0,   692,   526,     0,
       0,   693,   694,     0,     0,     0,     0,     0,   695,     0,
       0,   528,   529,     0,   313,   314,   315,     0,   317,   318,
     319,   320,   321,   530,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,     0,   335,   336,   337,     0,
       0,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   531,   532,
     696,   697,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   534,   535,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   698,
     699,   700,     0,     0,     0,     0,     0,     0,     0,    64,
       0,     0,     0,     0,     0,     0,     0,   536,   537,   538,
     539,   540,     0,   541,     0,   542,   543,   544,   545,    52,
     154,   701,   546,   547,   548,   549,   550,   551,   552,    65,
     702,   554,   555,     0,     0,     0,     0,     0,     0,   556,
     155,   703,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   557,   558,
     559,     0,    15,     0,     0,   560,   561,     0,     0,   512,
     513,     0,     0,   562,     0,   563,     0,   564,   565,   514,
     515,   516,   517,   518,     0,     0,     0,     0,     0,   519,
       0,   520,     0,     0,     0,   521,     0,   473,     0,     0,
       0,     0,     0,   522,     0,     0,     0,     0,     0,   523,
       0,     0,   524,     0,     0,   525,     0,  1004,     0,   526,
       0,     0,     0,     0,   474,   475,     0,     0,     0,   527,
       0,     0,   528,   529,     0,   313,   314,   315,     0,   317,
     318,   319,   320,   321,   530,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,     0,   335,   336,   337,
       0,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   364,   365,   366,   531,
     532,   533,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   534,   535,     0,     0,     0,
       0,   476,     0,     0,     0,   477,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      64,     0,     0,     0,     0,     0,     0,     0,   536,   537,
     538,   539,   540,     0,   541,  1005,   542,   543,   544,   545,
      52,     0,     0,   546,   547,   548,   549,   550,   551,   552,
    1006,   553,   554,   555,     0,     0,     0,     0,     0,     0,
     556,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   478,     0,     0,     0,   479,     0,     0,  1007,
     558,   559,     0,    15,     0,     0,   560,   561,     0,     0,
       0,   512,   513,     0,  1008,     0,  1009,     0,   564,   565,
     482,   514,   515,   516,   517,   518,     0,     0,     0,     0,
       0,   519,     0,   520,     0,     0,     0,   521,     0,   473,
       0,     0,     0,     0,     0,   522,     0,     0,     0,     0,
       0,   523,     0,     0,   524,     0,     0,   525,     0,     0,
       0,   526,     0,     0,     0,     0,   474,   475,     0,     0,
       0,   527,     0,     0,   528,   529,     0,   313,   314,   315,
       0,   317,   318,   319,   320,   321,   530,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,     0,   335,
     336,   337,     0,     0,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   531,   532,   533,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   534,   535,     0,
       0,     0,     0,   476,     0,     0,     0,   477,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    64,     0,     0,     0,     0,     0,     0,     0,
     536,   537,   538,   539,   540,     0,   541,  1005,   542,   543,
     544,   545,    52,     0,     0,   546,   547,   548,   549,   550,
     551,   552,  1006,   553,   554,   555,     0,     0,     0,     0,
       0,     0,   556,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   478,     0,     0,     0,   479,     0,
       0,  1007,   558,   559,     0,    15,     0,     0,   560,   561,
       0,     0,     0,   512,   513,     0,  1008,     0,  1017,     0,
     564,   565,   482,   514,   515,   516,   517,   518,     0,     0,
       0,     0,     0,   519,     0,   520,     0,     0,     0,   521,
       0,   621,     0,     0,     0,     0,     0,   522,     0,     0,
       0,     0,     0,   523,     0,     0,   524,     0,     0,   525,
       0,     0,     0,   526,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   527,     0,     0,   528,   529,     0,   313,
     314,   315,     0,   317,   318,   319,   320,   321,   530,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
       0,   335,   336,   337,     0,     0,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   358,   359,   360,   361,   362,   363,
     364,   365,   366,   531,   532,   533,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   534,
     535,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    64,     0,     0,     0,     0,     0,
       0,     0,   536,   537,   538,   539,   540,     0,   541,     0,
     542,   543,   544,   545,    52,     0,     0,   546,   547,   548,
     549,   550,   551,   552,    65,   553,   554,   555,     0,     0,
       0,     0,     0,     0,   556,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     622,     0,     0,   557,   558,   559,     0,    15,     0,     0,
     560,   561,     0,     0,     0,   512,   513,     0,  1284,     0,
     563,     0,   564,   565,   624,   514,   515,   516,   517,   518,
       0,     0,     0,     0,     0,   519,     0,   520,     0,     0,
       0,   521,     0,     0,     0,     0,     0,     0,     0,   522,
       0,     0,     0,     0,     0,   523,     0,     0,   524,     0,
       0,   525,     0,     0,     0,   526,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   527,     0,     0,   528,   529,
       0,   313,   314,   315,     0,   317,   318,   319,   320,   321,
     530,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,     0,   335,   336,   337,     0,     0,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,   531,   532,   696,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   534,   535,     0,     0,     0,     0,     0,     0,     0,
     901,     0,     0,     0,     0,     0,   698,   699,   700,     0,
       0,     0,     0,     0,     0,     0,    64,     0,     0,     0,
       0,     0,     0,     0,   536,   537,   538,   539,   540,     0,
     541,     0,   542,   543,   544,   545,    52,     0,     0,   546,
     547,   548,   549,   550,   551,   552,    65,   553,   554,   555,
       0,     0,     0,     0,     0,     0,   556,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   557,   558,   559,     0,    15,
       0,     0,   560,   561,     0,     0,   512,   513,     0,     0,
     562,     0,   563,     0,   564,   565,   514,   515,   516,   517,
     518,     0,     0,     0,     0,     0,   519,     0,   520,     0,
       0,     0,   521,     0,     0,     0,     0,     0,     0,     0,
     522,     0,     0,     0,     0,     0,   523,     0,     0,   524,
       0,     0,   525,     0,     0,     0,   526,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   527,     0,     0,   528,
     529,     0,   313,   314,   315,     0,   317,   318,   319,   320,
     321,   530,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,     0,   335,   336,   337,     0,     0,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   531,   532,   696,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   534,   535,     0,     0,     0,     0,     0,     0,
       0,   918,     0,     0,     0,     0,     0,   698,   699,   700,
       0,     0,     0,     0,     0,     0,     0,    64,     0,     0,
       0,     0,     0,     0,     0,   536,   537,   538,   539,   540,
       0,   541,     0,   542,   543,   544,   545,    52,     0,     0,
     546,   547,   548,   549,   550,   551,   552,    65,   553,   554,
     555,     0,     0,     0,     0,     0,     0,   556,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   557,   558,   559,     0,
      15,     0,     0,   560,   561,     0,     0,   512,   513,     0,
       0,   562,     0,   563,     0,   564,   565,   514,   515,   516,
     517,   518,     0,     0,     0,     0,     0,   519,  1733,   520,
     685,     0,     0,   521,     0,     0,     0,     0,     0,     0,
       0,   522,     0,     0,     0,     0,     0,   523,     0,     0,
     524,     0,     0,   525,   691,     0,     0,   526,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   527,     0,     0,
     528,   529,     0,   313,   314,   315,     0,   317,   318,   319,
     320,   321,   530,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,     0,   335,   336,   337,     0,     0,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   531,   532,   533,
    1734,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   534,   535,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    64,     0,
       0,     0,     0,     0,     0,     0,   536,   537,   538,   539,
     540,     0,   541,     0,   542,   543,   544,   545,    52,     0,
       0,   546,   547,   548,   549,   550,   551,   552,    65,   553,
     554,   555,     0,     0,     0,     0,     0,     0,   556,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   557,   558,   559,
       0,    15,     0,     0,   560,   561,     0,     0,   512,   513,
       0,     0,   562,     0,   563,     0,   564,   565,   514,   515,
     516,   517,   518,     0,     0,     0,     0,     0,   519,     0,
     520,     0,     0,     0,   521,     0,     0,     0,     0,     0,
       0,     0,   522,     0,     0,     0,     0,     0,   523,     0,
       0,   524,     0,     0,   525,     0,     0,     0,   526,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   527,     0,
       0,   528,   529,     0,   313,   314,   315,     0,   317,   318,
     319,   320,   321,   530,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,     0,   335,   336,   337,     0,
       0,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   531,   532,
     696,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   534,   535,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   698,
     699,   700,     0,     0,     0,     0,     0,     0,     0,    64,
       0,     0,     0,     0,     0,     0,     0,   536,   537,   538,
     539,   540,     0,   541,     0,   542,   543,   544,   545,    52,
       0,     0,   546,   547,   548,   549,   550,   551,   552,    65,
     553,   554,   555,     0,     0,     0,     0,     0,     0,   556,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   557,   558,
     559,     0,    15,     0,     0,   560,   561,     0,     0,   512,
     513,     0,     0,   562,     0,   563,     0,   564,   565,   514,
     515,   516,   517,   518,     0,     0,     0,     0,     0,   519,
       0,   520,     0,     0,     0,   521,     0,     0,     0,     0,
       0,     0,     0,   522,     0,     0,     0,     0,     0,   523,
       0,     0,   524,     0,     0,   525,     0,     0,     0,   526,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   527,
       0,     0,   528,   529,  1048,   313,   314,   315,     0,   317,
     318,   319,   320,   321,   530,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,     0,   335,   336,   337,
       0,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   364,   365,   366,   531,
     532,   533,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   534,   535,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      64,     0,     0,     0,     0,     0,     0,     0,   536,   537,
     538,   539,   540,     0,   541,  1005,   542,   543,   544,   545,
      52,     0,     0,   546,   547,   548,   549,   550,   551,   552,
    1006,   553,   554,   555,     0,     0,     0,     0,     0,     0,
     556,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   557,
     558,   559,     0,    15,     0,     0,   560,   561,     0,     0,
     512,   513,     0,     0,  1049,     0,   563,  1050,   564,   565,
     514,   515,   516,   517,   518,     0,     0,     0,     0,     0,
     519,     0,   520,     0,     0,   473,   521,     0,     0,     0,
       0,     0,     0,     0,   522,     0,     0,     0,     0,     0,
     523,     0,     0,   524,     0,     0,   525,     0,     0,     0,
     526,     0,   474,   475,     0,     0,     0,     0,     0,     0,
     527,     0,     0,   528,   529,     0,   313,   314,   315,     0,
     317,   318,   319,   320,   321,   530,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,     0,   335,   336,
     337,     0,     0,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     531,   532,   696,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   534,   535,     0,   476,
       0,     0,     0,   477,     0,     0,     0,     0,     0,     0,
       0,  1193,  1194,  1195,     0,     0,     0,     0,     0,     0,
       0,    64,     0,     0,     0,     0,     0,     0,     0,   536,
     537,   538,   539,   540,     0,   541,   473,   542,   543,   544,
     545,    52,     0,     0,   546,   547,   548,   549,   550,   551,
     552,    65,   553,   554,   555,     0,     0,     0,     0,     0,
       0,   556,     0,   474,   475,     0,     0,     0,     0,     0,
     478,     0,     0,     0,   479,     0,  1626,   480,     0,     0,
     557,   558,   559,     0,    15,     0,     0,   560,   561,     0,
       0,     0,   481,   512,   513,   562,     0,   563,   482,   564,
     565,   796,     0,   514,   515,   516,   517,   518,     0,     0,
       0,     0,     0,   519,     0,   520,     0,     0,     0,   521,
       0,     0,     0,     0,     0,     0,     0,   522,     0,     0,
       0,     0,     0,   523,     0,     0,   524,   797,     0,   525,
       0,     0,     0,   526,     0,     0,     0,     0,     0,     0,
     476,     0,     0,   527,   477,     0,   528,   529,     0,   313,
     314,   315,     0,   317,   318,   319,   320,   321,   530,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
       0,   335,   336,   337,     0,     0,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   358,   359,   360,   361,   362,   363,
     364,   365,   366,   531,   532,   533,     0,     0,     0,     0,
       0,   478,     0,     0,     0,   479,     0,  1722,   480,   534,
     535,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   481,     0,     0,     0,     0,     0,   482,
       0,     0,     0,     0,    64,     0,     0,     0,     0,     0,
       0,     0,   536,   537,   538,   539,   540,     0,   541,     0,
     542,   543,   544,   545,    52,     0,     0,   546,   547,   548,
     549,   550,   551,   552,    65,   553,   554,   555,     0,     0,
       0,     0,     0,     0,   556,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   557,   558,   559,     0,    15,     0,     0,
     560,   561,     0,     0,     0,     0,   512,   513,   562,   625,
     563,     0,   564,   565,   796,     0,   514,   515,   516,   517,
     518,     0,     0,     0,     0,     0,   519,     0,   520,     0,
       0,     0,   521,     0,     0,     0,     0,     0,     0,     0,
     522,     0,     0,     0,     0,     0,   523,     0,     0,   524,
     797,     0,   525,     0,     0,     0,   526,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   527,     0,     0,   528,
     529,     0,   313,   314,   315,     0,   317,   318,   319,   320,
     321,   530,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,     0,   335,   336,   337,     0,     0,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   531,   532,   533,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   534,   535,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    64,     0,     0,
       0,     0,     0,     0,     0,   536,   537,   538,   539,   540,
       0,   541,  1005,   542,   543,   544,   545,    52,     0,     0,
     546,   547,   548,   549,   550,   551,   552,  1006,   553,   554,
     555,     0,     0,     0,     0,     0,     0,   556,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   557,   558,   559,     0,
      15,     0,     0,   560,   561,     0,     0,     0,     0,   512,
     513,   562,     0,   563,     0,   564,   565,   796,     0,   514,
     515,   516,   517,   518,     0,     0,     0,     0,     0,   519,
       0,   520,     0,     0,     0,   521,     0,     0,     0,     0,
       0,     0,     0,   522,     0,     0,     0,     0,     0,   523,
       0,     0,   524,   797,     0,   525,     0,     0,     0,   526,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   527,
       0,     0,   528,   529,     0,   313,   314,   315,     0,   317,
     318,   319,   320,   321,   530,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,     0,   335,   336,   337,
       0,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   364,   365,   366,   531,
     532,   533,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   534,   535,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      64,     0,     0,     0,     0,     0,     0,     0,   536,   537,
     538,   539,   540,     0,   541,     0,   542,   543,   544,   545,
      52,     0,     0,   546,   547,   548,   549,   550,   551,   552,
      65,   553,   554,   555,     0,     0,     0,     0,     0,     0,
     556,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   557,
     558,   559,     0,    15,     0,     0,   560,   561,     0,     0,
       0,     0,   512,   513,   562,   876,   563,     0,   564,   565,
     796,     0,   514,   515,   516,   517,   518,     0,     0,     0,
       0,     0,   519,     0,   520,     0,     0,     0,   521,     0,
       0,     0,     0,     0,     0,     0,   522,     0,     0,     0,
       0,     0,   523,     0,     0,   524,   797,     0,   525,     0,
       0,     0,   526,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   527,     0,     0,   528,   529,     0,   313,   314,
     315,     0,   317,   318,   319,   320,   321,   530,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,     0,
     335,   336,   337,     0,     0,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   531,   532,   533,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   534,   535,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,     0,     0,     0,     0,     0,     0,
       0,   536,   537,   538,   539,   540,     0,   541,     0,   542,
     543,   544,   545,    52,     0,     0,   546,   547,   548,   549,
     550,   551,   552,    65,   553,   554,   555,     0,     0,     0,
       0,     0,     0,   556,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   557,   558,   559,     0,    15,     0,     0,   560,
     561,     0,     0,   512,   513,     0,     0,   562,     0,   563,
       0,   564,   565,   514,   515,   516,   517,   518,     0,     0,
       0,     0,     0,   519,     0,   520,     0,     0,     0,   521,
       0,     0,     0,     0,     0,     0,     0,   522,     0,     0,
       0,     0,     0,   523,     0,     0,   524,     0,     0,   525,
       0,     0,     0,   526,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   527,     0,     0,   528,   529,  1243,   313,
     314,   315,     0,   317,   318,   319,   320,   321,   530,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
       0,   335,   336,   337,     0,     0,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   358,   359,   360,   361,   362,   363,
     364,   365,   366,   531,   532,   533,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   534,
     535,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    64,     0,     0,     0,     0,     0,
       0,     0,   536,   537,   538,   539,   540,     0,   541,  1005,
     542,   543,   544,   545,    52,     0,     0,   546,   547,   548,
     549,   550,   551,   552,  1006,   553,   554,   555,     0,     0,
       0,     0,     0,     0,   556,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   557,   558,   559,     0,    15,     0,     0,
     560,   561,     0,     0,   512,   513,     0,     0,   562,     0,
     563,     0,   564,   565,   514,   515,   516,   517,   518,     0,
       0,     0,     0,     0,   519,     0,   520,     0,     0,     0,
     521,     0,     0,     0,     0,     0,     0,     0,   522,     0,
       0,     0,     0,     0,   523,     0,     0,   524,     0,     0,
     525,     0,     0,     0,   526,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   527,     0,     0,   528,   529,     0,
     313,   314,   315,     0,   317,   318,   319,   320,   321,   530,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,     0,   335,   336,   337,     0,     0,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   531,   532,   533,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     534,   535,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    64,     0,     0,     0,     0,
       0,     0,     0,   536,   537,   538,   539,   540,     0,   541,
       0,   542,   543,   544,   545,    52,     0,     0,   546,   547,
     548,   549,   550,   551,   552,    65,   553,   554,   555,     0,
       0,     0,     0,     0,     0,   556,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   557,   558,   559,     0,    15,     0,
       0,   560,   561,     0,     0,     0,     0,   512,   513,   562,
     625,   563,     0,   564,   565,   783,     0,   514,   515,   516,
     517,   518,     0,     0,     0,     0,     0,   519,     0,   520,
       0,     0,     0,   521,     0,     0,     0,     0,     0,     0,
       0,   522,     0,     0,     0,     0,     0,   523,     0,     0,
     524,     0,     0,   525,     0,     0,     0,   526,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   527,     0,     0,
     528,   529,     0,   313,   314,   315,     0,   317,   318,   319,
     320,   321,   530,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,     0,   335,   336,   337,     0,     0,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   531,   532,   533,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   534,   535,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    64,     0,
       0,     0,     0,     0,     0,     0,   536,   537,   538,   539,
     540,     0,   541,     0,   542,   543,   544,   545,    52,     0,
       0,   546,   547,   548,   549,   550,   551,   552,    65,   553,
     554,   555,     0,     0,     0,     0,     0,     0,   556,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   557,   558,   559,
       0,    15,     0,     0,   560,   561,     0,     0,     0,     0,
     512,   513,   562,     0,   563,     0,   564,   565,   803,     0,
     514,   515,   516,   517,   518,     0,     0,     0,     0,     0,
     519,     0,   520,     0,     0,     0,   521,     0,     0,     0,
       0,     0,     0,     0,   522,     0,     0,     0,     0,     0,
     523,     0,     0,   524,     0,     0,   525,     0,     0,     0,
     526,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     527,     0,     0,   528,   529,     0,   313,   314,   315,     0,
     317,   318,   319,   320,   321,   530,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,     0,   335,   336,
     337,     0,     0,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     531,   532,   533,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   534,   535,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,     0,     0,     0,     0,     0,     0,     0,   536,
     537,   538,   539,   540,     0,   541,     0,   542,   543,   544,
     545,    52,     0,     0,   546,   547,   548,   549,   550,   551,
     552,    65,   553,   554,   555,     0,     0,     0,     0,     0,
       0,   556,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     557,   558,   559,     0,    15,     0,     0,   560,   561,     0,
       0,   512,   513,     0,     0,   562,     0,   563,     0,   564,
     565,   514,   515,   516,   517,   518,     0,     0,     0,     0,
       0,   519,     0,   520,     0,     0,     0,   521,     0,     0,
       0,     0,     0,     0,     0,   522,     0,     0,     0,     0,
       0,   523,     0,     0,   524,     0,     0,   525,     0,     0,
       0,   526,     0,     0,     0,     0,     0,   907,     0,     0,
       0,   527,     0,     0,   528,   529,     0,   313,   314,   315,
       0,   317,   318,   319,   320,   321,   530,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,     0,   335,
     336,   337,     0,     0,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   531,   532,   533,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   534,   535,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    64,     0,     0,     0,     0,     0,     0,     0,
     536,   537,   538,   539,   540,     0,   541,     0,   542,   543,
     544,   545,    52,     0,     0,   546,   547,   548,   549,   550,
     551,   552,    65,   553,   554,   555,     0,     0,     0,     0,
       0,     0,   556,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   557,   558,   559,     0,    15,     0,     0,   560,   561,
       0,     0,   512,   513,     0,     0,   562,     0,   563,     0,
     564,   565,   514,   515,   516,   517,   518,     0,     0,     0,
       0,     0,   519,     0,   520,     0,     0,     0,   521,     0,
       0,     0,     0,     0,     0,     0,   522,     0,     0,     0,
       0,     0,   523,     0,     0,   524,     0,     0,   525,     0,
       0,     0,   526,     0,     0,   914,     0,     0,     0,     0,
       0,     0,   527,     0,     0,   528,   529,     0,   313,   314,
     315,     0,   317,   318,   319,   320,   321,   530,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,     0,
     335,   336,   337,     0,     0,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   531,   532,   533,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   534,   535,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,     0,     0,     0,     0,     0,     0,
       0,   536,   537,   538,   539,   540,     0,   541,     0,   542,
     543,   544,   545,    52,     0,     0,   546,   547,   548,   549,
     550,   551,   552,    65,   553,   554,   555,     0,     0,     0,
       0,     0,     0,   556,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   557,   558,   559,     0,    15,     0,     0,   560,
     561,     0,     0,   512,   513,     0,     0,   562,     0,   563,
       0,   564,   565,   514,   515,   516,   517,   518,     0,     0,
       0,     0,     0,   519,     0,   520,     0,     0,     0,   521,
       0,     0,     0,     0,     0,     0,     0,   522,     0,     0,
       0,     0,     0,   523,     0,     0,   524,     0,     0,   525,
       0,     0,     0,   526,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   527,     0,     0,   528,   529,     0,   313,
     314,   315,     0,   317,   318,   319,   320,   321,   530,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
       0,   335,   336,   337,     0,     0,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   358,   359,   360,   361,   362,   363,
     364,   365,   366,   531,   532,   533,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   534,
     535,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    64,     0,     0,     0,     0,     0,
       0,     0,   536,   537,   538,   539,   540,     0,   541,     0,
     542,   543,   544,   545,    52,     0,     0,   546,   547,   548,
     549,   550,   551,   552,    65,   553,   554,   555,     0,     0,
       0,     0,     0,     0,   556,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   787,     0,   557,   558,   559,     0,    15,     0,     0,
     560,   561,     0,     0,   512,   513,     0,     0,   562,     0,
     563,     0,   564,   565,   514,   515,   516,   517,   518,     0,
       0,  1085,     0,     0,   519,     0,   520,     0,     0,     0,
     521,     0,     0,     0,     0,     0,     0,     0,   522,     0,
       0,     0,     0,     0,   523,     0,     0,   524,     0,     0,
     525,     0,     0,     0,   526,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   527,     0,     0,   528,   529,     0,
     313,   314,   315,     0,   317,   318,   319,   320,   321,   530,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,     0,   335,   336,   337,     0,     0,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   531,   532,   533,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     534,   535,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    64,     0,     0,     0,     0,
       0,     0,     0,   536,   537,   538,   539,   540,     0,   541,
       0,   542,   543,   544,   545,    52,     0,     0,   546,   547,
     548,   549,   550,   551,   552,    65,   553,   554,   555,     0,
       0,     0,     0,     0,     0,   556,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   557,   558,   559,     0,    15,     0,
       0,   560,   561,     0,     0,   512,   513,     0,     0,   562,
       0,   563,     0,   564,   565,   514,   515,   516,   517,   518,
       0,     0,     0,     0,     0,   519,     0,   520,     0,     0,
       0,   521,     0,     0,     0,     0,     0,     0,     0,   522,
       0,     0,     0,     0,     0,   523,     0,     0,   524,     0,
       0,   525,     0,     0,     0,   526,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   527,     0,     0,   528,   529,
       0,   313,   314,   315,     0,   317,   318,   319,   320,   321,
     530,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,     0,   335,   336,   337,     0,     0,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,   531,   532,   533,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   534,   535,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    64,     0,     0,     0,
       0,     0,     0,     0,   536,   537,   538,   539,   540,     0,
     541,     0,   542,   543,   544,   545,    52,     0,     0,   546,
     547,   548,   549,   550,   551,   552,    65,   553,   554,   555,
       0,     0,     0,     0,     0,     0,   556,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   557,   558,   559,     0,    15,
       0,     0,   560,   561,     0,     0,   512,   513,     0,     0,
     562,     0,   563,  1106,   564,   565,   514,   515,   516,   517,
     518,     0,     0,     0,     0,     0,   519,     0,   520,     0,
       0,     0,   521,     0,     0,     0,     0,     0,     0,     0,
     522,     0,     0,     0,     0,     0,   523,     0,     0,   524,
       0,     0,   525,     0,     0,     0,   526,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   527,     0,     0,   528,
     529,     0,   313,   314,   315,     0,   317,   318,   319,   320,
     321,   530,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,     0,   335,   336,   337,     0,     0,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   531,   532,   533,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   534,   535,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    64,     0,     0,
       0,     0,     0,     0,     0,   536,   537,   538,   539,   540,
       0,   541,     0,   542,   543,   544,   545,    52,     0,     0,
     546,   547,   548,   549,   550,   551,   552,    65,   553,   554,
     555,     0,     0,     0,     0,     0,     0,   556,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1247,     0,   557,   558,   559,     0,
      15,     0,     0,   560,   561,     0,     0,   512,   513,     0,
       0,   562,     0,   563,     0,   564,   565,   514,   515,   516,
     517,   518,     0,     0,     0,     0,     0,   519,     0,   520,
       0,     0,     0,   521,     0,     0,     0,     0,     0,     0,
       0,   522,     0,     0,     0,     0,     0,   523,     0,     0,
     524,     0,     0,   525,     0,     0,     0,   526,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   527,     0,     0,
     528,   529,     0,   313,   314,   315,     0,   317,   318,   319,
     320,   321,   530,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,     0,   335,   336,   337,     0,     0,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   531,   532,   533,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   534,   535,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    64,     0,
       0,     0,     0,     0,     0,     0,   536,   537,   538,   539,
     540,     0,   541,     0,   542,   543,   544,   545,    52,     0,
       0,   546,   547,   548,   549,   550,   551,   552,    65,   553,
     554,   555,     0,     0,     0,     0,     0,     0,   556,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   557,   558,   559,
       0,    15,     0,     0,   560,   561,     0,     0,   512,   513,
       0,     0,   562,     0,   563,  1286,   564,   565,   514,   515,
     516,   517,   518,     0,     0,     0,     0,     0,   519,     0,
     520,     0,     0,     0,   521,     0,     0,     0,     0,     0,
       0,     0,   522,     0,     0,     0,     0,     0,   523,     0,
       0,   524,     0,     0,   525,     0,     0,     0,   526,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   527,     0,
       0,   528,   529,     0,   313,   314,   315,     0,   317,   318,
     319,   320,   321,   530,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,     0,   335,   336,   337,     0,
       0,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   531,   532,
     533,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   534,   535,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    64,
       0,     0,     0,     0,     0,     0,     0,   536,   537,   538,
     539,   540,     0,   541,     0,   542,   543,   544,   545,    52,
       0,     0,   546,   547,   548,   549,   550,   551,   552,    65,
     553,   554,   555,     0,     0,     0,     0,     0,     0,   556,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   557,   558,
     559,     0,    15,     0,     0,   560,   561,     0,     0,   512,
     513,     0,     0,   562,     0,   563,  1301,   564,   565,   514,
     515,   516,   517,   518,     0,     0,     0,     0,     0,   519,
       0,   520,     0,     0,     0,   521,     0,     0,     0,     0,
       0,     0,     0,   522,     0,     0,     0,     0,     0,   523,
       0,     0,   524,     0,     0,   525,     0,     0,     0,   526,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   527,
       0,     0,   528,   529,     0,   313,   314,   315,     0,   317,
     318,   319,   320,   321,   530,   323,   324,   325,   326,   327,
     328,   329,   330,   331,   332,   333,     0,   335,   336,   337,
       0,     0,   340,   341,   342,   343,   344,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   356,   357,
     358,   359,   360,   361,   362,   363,   364,   365,   366,   531,
     532,   533,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   534,   535,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      64,     0,     0,     0,     0,     0,     0,     0,   536,   537,
     538,   539,   540,     0,   541,     0,   542,   543,   544,   545,
      52,     0,     0,   546,   547,   548,   549,   550,   551,   552,
      65,   553,   554,   555,     0,     0,     0,     0,     0,     0,
     556,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   557,
     558,   559,     0,    15,     0,     0,   560,   561,     0,     0,
     512,   513,     0,     0,   562,     0,   563,  1529,   564,   565,
     514,   515,   516,   517,   518,     0,     0,     0,     0,     0,
     519,     0,   520,     0,     0,     0,   521,     0,     0,     0,
       0,     0,     0,     0,   522,     0,     0,     0,     0,     0,
     523,     0,     0,   524,     0,     0,   525,     0,     0,     0,
     526,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     527,     0,     0,   528,   529,     0,   313,   314,   315,     0,
     317,   318,   319,   320,   321,   530,   323,   324,   325,   326,
     327,   328,   329,   330,   331,   332,   333,     0,   335,   336,
     337,     0,     0,   340,   341,   342,   343,   344,   345,   346,
     347,   348,   349,   350,   351,   352,   353,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     531,   532,   533,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   534,   535,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,     0,     0,     0,     0,     0,     0,     0,   536,
     537,   538,   539,   540,     0,   541,     0,   542,   543,   544,
     545,    52,     0,     0,   546,   547,   548,   549,   550,   551,
     552,    65,   553,   554,   555,     0,     0,     0,     0,     0,
       0,   556,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     557,   558,   559,     0,    15,     0,     0,   560,   561,     0,
       0,   512,   513,     0,     0,  1538,     0,   563,  1539,   564,
     565,   514,   515,   516,   517,   518,     0,     0,     0,     0,
       0,   519,     0,   520,     0,     0,     0,   521,     0,     0,
       0,     0,     0,     0,     0,   522,     0,     0,     0,     0,
       0,   523,     0,     0,   524,     0,     0,   525,     0,     0,
       0,   526,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   527,     0,     0,   528,   529,     0,   313,   314,   315,
       0,   317,   318,   319,   320,   321,   530,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,     0,   335,
     336,   337,     0,     0,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   531,   532,   533,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   534,   535,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    64,     0,     0,     0,     0,     0,     0,     0,
     536,   537,   538,   539,   540,     0,   541,     0,   542,   543,
     544,   545,    52,     0,     0,   546,   547,   548,   549,   550,
     551,   552,    65,   553,   554,   555,     0,     0,     0,     0,
       0,     0,   556,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   557,   558,   559,     0,    15,     0,     0,   560,   561,
       0,     0,   512,   513,     0,     0,   562,     0,   563,  1544,
     564,   565,   514,   515,   516,   517,   518,     0,     0,     0,
       0,     0,   519,     0,   520,     0,     0,     0,   521,     0,
       0,     0,     0,     0,     0,     0,   522,     0,     0,     0,
       0,     0,   523,     0,     0,   524,     0,     0,   525,     0,
       0,     0,   526,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   527,     0,     0,   528,   529,     0,   313,   314,
     315,     0,   317,   318,   319,   320,   321,   530,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,     0,
     335,   336,   337,     0,     0,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   531,   532,   533,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   534,   535,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    64,     0,     0,     0,     0,     0,     0,
       0,   536,   537,   538,   539,   540,     0,   541,     0,   542,
     543,   544,   545,    52,     0,     0,   546,   547,   548,   549,
     550,   551,   552,    65,   553,   554,   555,     0,     0,     0,
       0,     0,     0,   556,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   557,   558,   559,     0,    15,     0,     0,   560,
     561,     0,     0,   512,   513,     0,     0,   562,     0,   563,
    1602,   564,   565,   514,   515,   516,   517,   518,     0,     0,
       0,     0,     0,   519,     0,   520,     0,     0,     0,   521,
       0,     0,     0,     0,     0,     0,     0,   522,     0,     0,
       0,     0,     0,   523,     0,     0,   524,     0,     0,   525,
       0,     0,     0,   526,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   527,     0,     0,   528,   529,     0,   313,
     314,   315,     0,   317,   318,   319,   320,   321,   530,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
       0,   335,   336,   337,     0,     0,   340,   341,   342,   343,
     344,   345,   346,   347,   348,   349,   350,   351,   352,   353,
     354,   355,   356,   357,   358,   359,   360,   361,   362,   363,
     364,   365,   366,   531,   532,   533,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   534,
     535,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    64,     0,     0,     0,     0,     0,
       0,     0,   536,   537,   538,   539,   540,     0,   541,     0,
     542,   543,   544,   545,    52,     0,     0,   546,   547,   548,
     549,   550,   551,   552,    65,   553,   554,   555,     0,     0,
       0,     0,     0,     0,   556,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   557,   558,   559,     0,    15,     0,     0,
     560,   561,     0,     0,   512,   513,     0,     0,   562,     0,
     563,  1694,   564,   565,   514,   515,   516,   517,   518,     0,
       0,     0,     0,     0,   519,     0,   520,     0,     0,     0,
     521,     0,     0,     0,     0,     0,     0,     0,   522,     0,
       0,     0,     0,     0,   523,     0,     0,   524,     0,     0,
     525,     0,     0,     0,   526,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   527,     0,     0,   528,   529,     0,
     313,   314,   315,     0,   317,   318,   319,   320,   321,   530,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     333,     0,   335,   336,   337,     0,     0,   340,   341,   342,
     343,   344,   345,   346,   347,   348,   349,   350,   351,   352,
     353,   354,   355,   356,   357,   358,   359,   360,   361,   362,
     363,   364,   365,   366,   531,   532,   533,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     534,   535,     0,     0,     0,     0,     0,     0,     0,  1720,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    64,     0,     0,     0,     0,
       0,     0,     0,   536,   537,   538,   539,   540,     0,   541,
       0,   542,   543,   544,   545,    52,     0,     0,   546,   547,
     548,   549,   550,   551,   552,    65,   553,   554,   555,     0,
       0,     0,     0,     0,     0,   556,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   557,   558,   559,     0,    15,     0,
       0,   560,   561,     0,     0,   512,   513,     0,     0,   562,
       0,   563,     0,   564,   565,   514,   515,   516,   517,   518,
       0,     0,     0,     0,     0,   519,     0,   520,     0,     0,
       0,   521,     0,     0,     0,     0,     0,     0,     0,   522,
       0,     0,     0,     0,     0,   523,     0,     0,   524,     0,
       0,   525,     0,     0,     0,   526,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   527,     0,     0,   528,   529,
       0,   313,   314,   315,     0,   317,   318,   319,   320,   321,
     530,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,     0,   335,   336,   337,     0,     0,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,   531,   532,   533,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   534,   535,     0,     0,     0,     0,     0,     0,     0,
    1788,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    64,     0,     0,     0,
       0,     0,     0,     0,   536,   537,   538,   539,   540,     0,
     541,     0,   542,   543,   544,   545,    52,     0,     0,   546,
     547,   548,   549,   550,   551,   552,    65,   553,   554,   555,
       0,     0,     0,     0,     0,     0,   556,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   557,   558,   559,     0,    15,
       0,     0,   560,   561,     0,     0,   512,   513,     0,     0,
     562,     0,   563,     0,   564,   565,   514,   515,   516,   517,
     518,     0,     0,     0,     0,     0,   519,     0,   520,     0,
       0,     0,   521,     0,     0,     0,     0,     0,     0,     0,
     522,     0,     0,     0,     0,     0,   523,     0,     0,   524,
       0,     0,   525,     0,     0,     0,   526,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   527,     0,     0,   528,
     529,     0,   313,   314,   315,     0,   317,   318,   319,   320,
     321,   530,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,     0,   335,   336,   337,     0,     0,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   531,   532,   533,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   534,   535,     0,     0,     0,     0,     0,     0,
       0,  1789,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    64,     0,     0,
       0,     0,     0,     0,     0,   536,   537,   538,   539,   540,
       0,   541,     0,   542,   543,   544,   545,    52,     0,     0,
     546,   547,   548,   549,   550,   551,   552,    65,   553,   554,
     555,     0,     0,     0,     0,     0,     0,   556,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   557,   558,   559,     0,
      15,     0,     0,   560,   561,     0,     0,   512,   513,     0,
       0,   562,     0,   563,     0,   564,   565,   514,   515,   516,
     517,   518,     0,     0,     0,     0,     0,   519,     0,   520,
       0,     0,     0,   521,     0,     0,     0,     0,     0,     0,
       0,   522,     0,     0,     0,     0,     0,   523,     0,     0,
     524,     0,     0,   525,     0,     0,     0,   526,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   527,     0,     0,
     528,   529,     0,   313,   314,   315,     0,   317,   318,   319,
     320,   321,   530,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,     0,   335,   336,   337,     0,     0,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   531,   532,   533,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   534,   535,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    64,     0,
       0,     0,     0,     0,     0,     0,   536,   537,   538,   539,
     540,     0,   541,     0,   542,   543,   544,   545,    52,     0,
       0,   546,   547,   548,   549,   550,   551,   552,    65,   553,
     554,   555,     0,     0,     0,     0,     0,     0,   556,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   557,   558,   559,
       0,    15,     0,     0,   560,   561,     0,     0,   512,   513,
       0,     0,   562,     0,   563,     0,   564,   565,   514,   515,
     516,   517,   518,     0,     0,     0,     0,     0,   519,     0,
     520,     0,     0,     0,   521,     0,     0,     0,     0,     0,
       0,     0,   522,     0,     0,     0,     0,     0,   523,     0,
       0,   524,     0,     0,   525,     0,     0,     0,   526,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   527,     0,
       0,   528,   529,     0,   313,   314,   315,     0,   317,   318,
     319,   320,   321,   530,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,     0,   335,   336,   337,     0,
       0,   340,   341,   342,   343,   344,   345,   346,   347,   348,
     349,   350,   351,   352,   353,   354,   355,   356,   357,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   531,   532,
     533,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   534,   535,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    64,
       0,     0,     0,     0,     0,     0,     0,   536,   537,   538,
     539,   540,     0,   541,     0,   542,   543,   544,   545,    52,
       0,     0,   546,   547,   548,   549,   550,   551,   552,    65,
     553,   554,   555,     0,     0,   781,     0,     0,     0,   556,
       0,   307,     0,     0,     0,   810,   811,   308,     0,     0,
       0,     0,     0,   309,     0,     0,     0,     0,   557,   558,
     559,     0,    15,   310,     0,   560,   561,     0,     0,     0,
       0,   311,     0,  1515,     0,   563,     0,   564,   565,     0,
       0,     0,     0,     0,     0,     0,   312,     0,     0,     0,
       0,     0,     0,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   812,   813,   814,   815,   816,     0,     0,
     817,   818,   819,   820,     0,   821,   822,   823,   824,     0,
       0,     0,     0,   825,     0,   826,   827,     0,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   369,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   810,   811,     0,   307,     0,     0,    65,     0,
       0,   308,     0,     0,     0,     0,     0,   309,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   310,     0,     0,
       0,     0,     0,     0,     0,   311,   835,   836,   837,   838,
     839,   840,   841,   842,     0,     0,     0,     0,     0,     0,
     312,     0,     0,   843,   844,     0,   370,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,     0,     0,     0,     0,     0,     0,     0,
     812,   813,   814,   815,   816,     0,     0,   817,   818,   819,
     820,     0,   821,   822,   823,   824,     0,     0,     0,     0,
     825,     0,   826,   827,     0,     0,     0,     0,     0,     0,
       0,     0,    64,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   369,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   307,    65,     0,   810,   811,     0,   308,     0,     0,
       0,     0,     0,   309,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   310,   836,   837,   838,   839,   840,   841,
     842,   311,     0,     0,     0,     0,     0,     0,     0,     0,
     843,   844,     0,     0,     0,     0,   312,     0,     0,     0,
     370,     0,   628,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   812,   813,   814,   815,   816,     0,     0,   817,
       0,     0,   820,     0,   821,   822,   823,   824,     0,     0,
       0,     0,   825,     0,   826,   827,     0,     0,    64,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   369,     0,     0,     0,     0,     0,     0,     0,     0,
      13,     0,     0,     0,     0,   307,     0,     0,   632,     0,
       0,   308,     0,     0,     0,     0,     0,   309,     0,     0,
      14,     0,     0,     0,     0,     0,     0,   310,   633,     0,
       0,     0,     0,     0,     0,   311,   836,   837,   838,   839,
     840,   841,   842,     0,     0,     0,     0,     0,     0,     0,
     312,     0,   843,   844,     0,     0,   370,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,   367,   368,     0,  1111,  1112,  1113,  1114,  1115,  1116,
    1117,  1118,     0,     0,     0,     0,     0,  1119,  1120,     0,
       0,     0,     0,  1121,     0,     0,     0,     0,  -437,     0,
       0,     0,     0,   955,     0,     0,  1122,  1123,     0,     0,
       0,     0,    64,  1124,  1125,  1126,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   369,     0,     0,     0,   810,
     811,     0,     0,     0,     0,     0,     0,     0,     0,   307,
       0,     0,    65,     0,     0,   308,     0,     0,     0,     0,
       0,   309,     0,     0,     0,     0,     0,     0,     0,     0,
    1127,   310,     0,     0,     0,     0,     0,     0,     0,   311,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   312,     0,     0,   564,   921,     0,
     370,   313,   314,   315,   316,   317,   318,   319,   320,   321,
     322,   323,   324,   325,   326,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   340,   341,
     342,   343,   344,   345,   346,   347,   348,   349,   350,   351,
     352,   353,   354,   355,   356,   357,   358,   359,   360,   361,
     362,   363,   364,   365,   366,   367,   368,   812,   813,   814,
     815,   816,   810,   811,   817,   818,   819,   820,     0,   821,
     822,   823,   824,     0,     0,     0,     0,   825,     0,   826,
     827,     0,     0,     0,     0,   828,   829,   830,     0,     0,
       0,   831,     0,     0,     0,     0,    64,   810,   811,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   369,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   632,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   832,     0,   833,   834,
     835,   836,   837,   838,   839,   840,   841,   842,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   843,   844,     0,
       0,  1263,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   370,     0,     0,     0,     0,     0,
     812,   813,   814,   815,   816,     0,     0,   817,   818,   819,
     820,     0,   821,   822,   823,   824,     0,     0,     0,     0,
     825,     0,   826,   827,   810,   811,     0,     0,   828,   829,
     830,     0,     0,     0,   831,   812,   813,   814,   815,   816,
       0,     0,   817,   818,   819,   820,     0,   821,   822,   823,
     824,     0,     0,     0,     0,   825,     0,   826,   827,   810,
     811,     0,     0,   828,   829,   830,     0,     0,     0,   831,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   832,
       0,   833,   834,   835,   836,   837,   838,   839,   840,   841,
     842,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     843,   844,     0,     0,  1265,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   832,     0,   833,   834,   835,   836,
     837,   838,   839,   840,   841,   842,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   843,   844,     0,     0,  1273,
       0,     0,   812,   813,   814,   815,   816,     0,     0,   817,
     818,   819,   820,     0,   821,   822,   823,   824,     0,     0,
       0,     0,   825,     0,   826,   827,   810,   811,     0,     0,
     828,   829,   830,     0,     0,     0,   831,   812,   813,   814,
     815,   816,     0,     0,   817,   818,   819,   820,     0,   821,
     822,   823,   824,     0,     0,     0,     0,   825,     0,   826,
     827,   810,   811,     0,     0,   828,   829,   830,     0,     0,
       0,   831,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   832,     0,   833,   834,   835,   836,   837,   838,   839,
     840,   841,   842,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   843,   844,     0,     0,  1274,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   832,     0,   833,   834,
     835,   836,   837,   838,   839,   840,   841,   842,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   843,   844,     0,
       0,  1275,     0,     0,   812,   813,   814,   815,   816,     0,
       0,   817,   818,   819,   820,     0,   821,   822,   823,   824,
       0,     0,     0,     0,   825,     0,   826,   827,   810,   811,
       0,     0,   828,   829,   830,     0,     0,     0,   831,   812,
     813,   814,   815,   816,     0,     0,   817,   818,   819,   820,
       0,   821,   822,   823,   824,     0,     0,     0,     0,   825,
       0,   826,   827,   810,   811,     0,     0,   828,   829,   830,
       0,     0,     0,   831,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   832,     0,   833,   834,   835,   836,   837,
     838,   839,   840,   841,   842,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   843,   844,     0,     0,  1276,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   832,     0,
     833,   834,   835,   836,   837,   838,   839,   840,   841,   842,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   843,
     844,     0,     0,  1277,     0,     0,   812,   813,   814,   815,
     816,     0,     0,   817,   818,   819,   820,     0,   821,   822,
     823,   824,     0,     0,     0,     0,   825,     0,   826,   827,
     810,   811,     0,     0,   828,   829,   830,     0,     0,     0,
     831,   812,   813,   814,   815,   816,     0,     0,   817,   818,
     819,   820,     0,   821,   822,   823,   824,     0,     0,     0,
       0,   825,     0,   826,   827,   810,   811,     0,     0,   828,
     829,   830,     0,     0,     0,   831,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   832,     0,   833,   834,   835,
     836,   837,   838,   839,   840,   841,   842,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   843,   844,     0,     0,
    1278,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     832,     0,   833,   834,   835,   836,   837,   838,   839,   840,
     841,   842,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   843,   844,     0,     0,  1554,     0,     0,   812,   813,
     814,   815,   816,     0,     0,   817,   818,   819,   820,     0,
     821,   822,   823,   824,     0,     0,     0,     0,   825,     0,
     826,   827,   810,   811,     0,     0,   828,   829,   830,     0,
       0,     0,   831,   812,   813,   814,   815,   816,     0,     0,
     817,   818,   819,   820,     0,   821,   822,   823,   824,     0,
       0,     0,     0,   825,     0,   826,   827,   810,   811,     0,
       0,   828,   829,   830,     0,     0,     0,   831,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   832,     0,   833,
     834,   835,   836,   837,   838,   839,   840,   841,   842,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   843,   844,
       0,     0,  1605,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   832,     0,   833,   834,   835,   836,   837,   838,
     839,   840,   841,   842,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   843,   844,     0,     0,  1624,     0,     0,
     812,   813,   814,   815,   816,     0,     0,   817,   818,   819,
     820,     0,   821,   822,   823,   824,     0,     0,     0,     0,
     825,     0,   826,   827,   810,   811,     0,     0,   828,   829,
     830,     0,     0,     0,   831,   812,   813,   814,   815,   816,
       0,     0,   817,   818,   819,   820,     0,   821,   822,   823,
     824,     0,     0,     0,     0,   825,     0,   826,   827,   810,
     811,     0,     0,   828,   829,   830,     0,     0,     0,   831,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   832,
       0,   833,   834,   835,   836,   837,   838,   839,   840,   841,
     842,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     843,   844,     0,     0,  1625,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   832,     0,   833,   834,   835,   836,
     837,   838,   839,   840,   841,   842,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   843,   844,     0,     0,  1639,
       0,     0,   812,   813,   814,   815,   816,     0,     0,   817,
     818,   819,   820,     0,   821,   822,   823,   824,     0,     0,
       0,     0,   825,     0,   826,   827,   810,   811,     0,     0,
     828,   829,   830,     0,     0,     0,   831,   812,   813,   814,
     815,   816,     0,     0,   817,   818,   819,   820,     0,   821,
     822,   823,   824,     0,     0,     0,     0,   825,     0,   826,
     827,   810,   811,     0,     0,   828,   829,   830,     0,     0,
       0,   831,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   832,     0,   833,   834,   835,   836,   837,   838,   839,
     840,   841,   842,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   843,   844,     0,     0,  1641,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   832,     0,   833,   834,
     835,   836,   837,   838,   839,   840,   841,   842,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   843,   844,     0,
       0,  1643,     0,     0,   812,   813,   814,   815,   816,     0,
       0,   817,   818,   819,   820,     0,   821,   822,   823,   824,
       0,     0,     0,     0,   825,     0,   826,   827,   810,   811,
       0,     0,   828,   829,   830,     0,     0,     0,   831,   812,
     813,   814,   815,   816,     0,     0,   817,   818,   819,   820,
       0,   821,   822,   823,   824,     0,     0,     0,     0,   825,
       0,   826,   827,   810,   811,     0,     0,   828,   829,   830,
       0,     0,     0,   831,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   832,     0,   833,   834,   835,   836,   837,
     838,   839,   840,   841,   842,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   843,   844,     0,     0,  1647,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   832,     0,
     833,   834,   835,   836,   837,   838,   839,   840,   841,   842,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   843,
     844,     0,     0,  1725,     0,     0,   812,   813,   814,   815,
     816,     0,     0,   817,   818,   819,   820,     0,   821,   822,
     823,   824,     0,     0,     0,     0,   825,     0,   826,   827,
     810,   811,     0,     0,   828,   829,   830,     0,     0,     0,
     831,   812,   813,   814,   815,   816,     0,     0,   817,   818,
     819,   820,     0,   821,   822,   823,   824,     0,     0,     0,
       0,   825,     0,   826,   827,   810,   811,     0,     0,   828,
     829,   830,     0,     0,     0,   831,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   832,     0,   833,   834,   835,
     836,   837,   838,   839,   840,   841,   842,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   843,   844,     0,     0,
    1726,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     832,     0,   833,   834,   835,   836,   837,   838,   839,   840,
     841,   842,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   843,   844,     0,     0,  1728,     0,     0,   812,   813,
     814,   815,   816,     0,     0,   817,   818,   819,   820,     0,
     821,   822,   823,   824,     0,     0,     0,     0,   825,     0,
     826,   827,   810,   811,     0,     0,   828,   829,   830,     0,
       0,     0,   831,   812,   813,   814,   815,   816,     0,     0,
     817,   818,   819,   820,     0,   821,   822,   823,   824,     0,
       0,     0,     0,   825,     0,   826,   827,   810,   811,     0,
       0,   828,   829,   830,     0,     0,     0,   831,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   832,     0,   833,
     834,   835,   836,   837,   838,   839,   840,   841,   842,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   843,   844,
       0,     0,  1763,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   832,     0,   833,   834,   835,   836,   837,   838,
     839,   840,   841,   842,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   843,   844,     0,     0,  1768,     0,     0,
     812,   813,   814,   815,   816,     0,     0,   817,   818,   819,
     820,     0,   821,   822,   823,   824,     0,     0,     0,     0,
     825,     0,   826,   827,   810,   811,     0,     0,   828,   829,
     830,     0,     0,     0,   831,   812,   813,   814,   815,   816,
       0,     0,   817,   818,   819,   820,     0,   821,   822,   823,
     824,     0,     0,     0,     0,   825,     0,   826,   827,   810,
     811,     0,     0,   828,   829,   830,     0,     0,     0,   831,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   832,
       0,   833,   834,   835,   836,   837,   838,   839,   840,   841,
     842,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     843,   844,   877,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   832,     0,   833,   834,   835,   836,
     837,   838,   839,   840,   841,   842,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   843,   844,  1151,     0,     0,
       0,     0,   812,   813,   814,   815,   816,     0,     0,   817,
     818,   819,   820,     0,   821,   822,   823,   824,     0,     0,
       0,     0,   825,     0,   826,   827,   810,   811,     0,     0,
     828,   829,   830,     0,     0,     0,   831,   812,   813,   814,
     815,   816,     0,     0,   817,   818,   819,   820,     0,   821,
     822,   823,   824,     0,     0,     0,     0,   825,     0,   826,
     827,   810,   811,     0,     0,   828,   829,   830,     0,     0,
       0,   831,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   832,     0,   833,   834,   835,   836,   837,   838,   839,
     840,   841,   842,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   843,   844,  1350,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   832,     0,   833,   834,
     835,   836,   837,   838,   839,   840,   841,   842,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   843,   844,  1366,
       0,     0,     0,     0,   812,   813,   814,   815,   816,     0,
       0,   817,   818,   819,   820,     0,   821,   822,   823,   824,
       0,     0,     0,     0,   825,     0,   826,   827,     0,     0,
       0,     0,   828,   829,   830,     0,     0,     0,   831,   812,
     813,   814,   815,   816,     0,     0,   817,   818,   819,   820,
       0,   821,   822,   823,   824,   385,   386,     0,     0,   825,
       0,   826,   827,     0,     0,     0,     0,   828,   829,   830,
       0,     0,   387,   831,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   832,     0,   833,   834,   835,   836,   837,
     838,   839,   840,   841,   842,     0,     0,   810,   811,     0,
       0,     0,     0,     0,   843,   844,  1536,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   832,     0,
     833,   834,   835,   836,   837,   838,   839,   840,   841,   842,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   843,
     844,  1542,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   388,   389,   390,   391,   392,
     393,   394,   395,   396,   397,   398,   399,   400,   401,   402,
     403,   404,   405,     0,     0,   406,   407,   408,     0,     0,
       0,     0,   810,   811,   409,   410,   411,   412,   413,     0,
       0,   414,   415,   416,   417,   418,   419,   420,     0,     0,
       0,     0,     0,     0,     0,   812,   813,   814,   815,   816,
       0,     0,   817,   818,   819,   820,     0,   821,   822,   823,
     824,   810,   811,     0,     0,   825,     0,   826,   827,     0,
       0,     0,     0,   828,   829,   830,     0,     0,     0,   831,
       0,     0,   421,     0,   422,   423,   424,   425,   426,   427,
     428,   429,   430,   431,    13,     0,   432,   433,     0,     0,
       0,     0,     0,   434,   435,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    14,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   832,     0,   833,   834,   835,   836,
     837,   838,   839,   840,   841,   842,     0,     0,     0,     0,
     812,   813,   814,   815,   816,   843,   844,   817,   818,   819,
     820,     0,   821,   822,   823,   824,   810,   811,     0,     0,
     825,     0,   826,   827,     0,     0,     0,     0,   828,   829,
     830,     0,     0,     0,   831,     0,     0,     0,     0,   812,
     813,   814,   815,   816,     0,     0,   817,   818,   819,   820,
       0,   821,   822,   823,   824,   810,   811,     0,     0,   825,
       0,   826,   827,     0,     0,     0,     0,   828,   829,   830,
       0,     0,     0,   831,     0,     0,     0,     0,     0,   832,
    1355,   833,   834,   835,   836,   837,   838,   839,   840,   841,
     842,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     843,   844,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   810,   811,     0,     0,     0,     0,     0,   832,     0,
     833,   834,   835,   836,   837,   838,   839,   840,   841,   842,
       0,     0,     0,     0,   812,   813,   814,   815,   816,   843,
     844,   817,   818,   819,   820,     0,   821,   822,   823,   824,
     810,   811,     0,     0,   825,     0,   826,   827,     0,     0,
       0,     0,   828,   829,   830,     0,     0,     0,  -880,     0,
       0,     0,     0,   812,   813,   814,   815,   816,     0,     0,
     817,   818,   819,   820,     0,   821,   822,   823,   824,     0,
       0,     0,     0,   825,     0,   826,   827,     0,     0,     0,
       0,   828,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   832,     0,   833,   834,   835,   836,   837,
     838,   839,   840,   841,   842,     0,     0,     0,     0,   812,
     813,   814,   815,   816,   843,   844,   817,   818,   819,   820,
       0,   821,   822,   823,   824,     0,     0,     0,     0,   825,
       0,   826,   827,     0,   833,   834,   835,   836,   837,   838,
     839,   840,   841,   842,     0,     0,     0,     0,   812,   813,
     814,   815,   816,   843,   844,   817,   818,   819,   820,     0,
     821,   822,   823,   824,     0,     0,     0,     0,   825,     0,
     826,   827,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     833,   834,   835,   836,   837,   838,   839,   840,   841,   842,
    1057,     0,     0,     0,     0,     0,     0,     0,     0,   843,
     844,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     834,   835,   836,   837,   838,   839,   840,   841,   842,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   843,   844,
       0,     0,   313,   314,   315,  1061,   317,   318,   319,   320,
     321,   530,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,     0,   335,   336,   337,     0,     0,   340,
     341,   342,   343,   344,   345,   346,   347,   348,   349,   350,
     351,   352,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,     0,   313,   314,   315,
       0,   317,   318,   319,   320,   321,   530,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,     0,   335,
     336,   337,     0,     0,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,     0,  1058,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1059,     0,     0,
       0,  1351,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1062,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1063,   313,   314,   315,     0,   317,   318,   319,
     320,   321,   530,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,     0,   335,   336,   337,     0,     0,
     340,   341,   342,   343,   344,   345,   346,   347,   348,   349,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   313,   314,   315,
       0,   317,   318,   319,   320,   321,   530,   323,   324,   325,
     326,   327,   328,   329,   330,   331,   332,   333,     0,   335,
     336,   337,     0,     0,   340,   341,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   355,
     356,   357,   358,   359,   360,   361,   362,   363,   364,   365,
     366,     0,     0,  1352,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1353,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1097,  1098,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   230,     0,     0,  1099,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1100,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     231,     0,   232,     0,   233,   234,   235,   236,   237,     0,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,     0,   249,   250,   251,  1101,  1102,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,  1111,  1112,  1113,  1114,  1115,  1116,
    1117,  1118,     0,     0,     0,     0,     0,  1119,  1120,     0,
     279,   280,     0,  1121,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   955,     0,     0,  1122,  1123,     0,     0,
       0,     0,     0,  1124,  1125,  1126,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   281,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1127,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   564,   921
};

static const yytype_int16 yycheck[] =
{
       1,   283,     7,   157,   213,   224,   545,   594,   617,   504,
     757,   718,   182,   801,   504,    15,    16,   455,   806,    20,
     894,   782,   509,   608,   780,   610,   782,   612,   699,   700,
     487,   486,   487,   598,   449,  1290,   972,  1425,   486,   993,
       5,   864,   995,   866,    33,   868,   484,   113,    87,     8,
    1182,   779,   808,   781,  1405,   783,  1572,    19,    20,     4,
      33,  1012,    22,   149,  1669,    53,   149,  1018,   796,   149,
      70,    71,    72,    20,    20,   803,   216,   149,    15,    16,
      12,    40,   149,   175,   293,   152,   153,   875,   575,    20,
      20,    23,    24,   183,  1704,    20,  1706,    57,    20,   152,
     153,   102,  1712,   243,   196,   543,   544,  1717,   598,   149,
     563,   186,  1048,    20,   114,   115,   116,   117,    20,   684,
      20,   166,    21,    22,   155,    46,   131,   297,   166,    20,
      20,   206,   697,   219,    12,   196,   219,   189,   224,   219,
    1272,   224,  1715,  1748,   224,    23,    24,   219,   214,  1665,
     242,   196,   224,   181,   175,   245,   242,   188,   166,   242,
     125,   126,   242,   167,   168,   169,  1776,   242,   196,   181,
     242,   899,   239,   240,   179,   196,   215,   208,   219,   219,
     635,   219,   223,   244,   196,   640,   239,   240,   196,     7,
      15,    16,   216,   981,   684,     0,   150,   242,   203,   204,
     188,    53,     7,   991,    57,  1778,   994,   697,   129,   188,
      63,  1821,  1822,    33,   242,   216,   972,    34,    62,   243,
     208,   242,   227,   175,   224,    30,  1481,    32,   187,    34,
     504,   684,    50,   222,   196,    40,   217,   216,   183,   243,
      60,    61,   141,   142,   196,    50,    63,  1857,   207,   222,
     149,    56,   189,   152,   153,   154,   188,   194,   223,   196,
     159,   300,   199,   217,  1052,  1616,   220,   240,   228,   216,
     216,   942,  1660,   246,   216,    80,   485,   242,   283,   239,
     219,   240,   501,   502,   849,   216,   216,   292,  1420,   443,
     295,   216,  1048,  1049,   216,   504,   505,   216,  1430,  1253,
     509,  1254,   755,  1031,  1032,   242,  1034,  1243,   245,   216,
     188,  1750,   765,   130,   216,   768,   216,   165,   756,   188,
     125,   126,  1761,   228,   598,   216,   216,   147,   188,   181,
     188,   151,   770,  1004,   187,  1286,   901,   196,   186,   208,
     239,   240,   159,  1731,   196,   196,   228,   178,   208,   166,
     208,  1606,   183,   918,   207,   808,   510,   217,   206,   849,
     181,    21,    22,   150,   189,   150,   224,  1806,  1807,   194,
     370,   196,    57,   160,   199,   196,   245,   150,    63,   196,
     599,   600,   601,   188,   603,   604,   175,   160,   607,   166,
     609,   242,   611,   846,   183,   178,   150,    55,   218,   150,
     183,   856,   222,   208,   686,   225,   160,   196,   150,   160,
     684,   901,   243,   695,   245,   166,   233,   872,   160,  1598,
     240,   216,   243,   697,   229,   242,   246,   188,   918,   638,
     217,   216,   217,   642,   219,   240,   923,   222,   216,  1167,
     216,   150,   196,   101,   217,   445,   241,   208,   901,   173,
     211,   160,   216,   242,   150,   455,   188,   200,   201,   202,
     203,   208,   245,   217,   160,   243,   217,   243,   222,   216,
     188,  1056,   196,   197,   198,   217,   208,   241,   216,   917,
     241,   141,   142,   188,   484,  1024,   486,  1243,   220,   149,
     208,   151,   152,   153,   154,  1674,  1675,   175,   216,   159,
     130,   501,   502,   241,   228,   229,   224,  1046,   217,    21,
      22,   216,   217,  1692,  1693,   239,   516,   517,   196,   972,
    1343,   217,  1193,  1194,  1195,  1286,   941,   982,   242,  1480,
    1286,   969,   970,  1289,   181,   188,   173,   130,   186,  1413,
    1301,  1492,   980,   543,   544,  1301,   130,   985,   986,   196,
     988,   216,   990,   186,   992,   208,  1009,   216,   206,   196,
     197,   198,   188,   216,  1017,   225,   226,   227,   228,   229,
     740,   224,   224,   206,    47,   849,  1755,  1756,   243,   239,
     240,   735,   208,   216,   243,   166,     5,     6,  1316,   223,
     216,   189,   229,   594,   175,   804,   244,   245,   224,   599,
     600,   601,   239,   603,   604,   166,    25,   607,   242,   609,
    1484,   611,    31,   613,   175,   196,   898,    90,    91,   180,
      93,   216,   242,   188,   244,   245,    33,   901,   910,   141,
     142,   216,   188,   211,   212,   196,   186,   149,   239,   151,
     152,   153,   154,   208,   918,   927,   241,   159,   930,    68,
      69,   216,   208,    60,    61,   874,   206,   208,   243,   224,
     216,   196,   223,   241,   883,   216,   196,   886,   224,   219,
     944,   945,   946,   947,   948,   949,   950,   951,   952,   953,
     954,   686,   956,   957,   958,   959,   960,   961,  1511,  1146,
     695,   692,  1147,   698,   699,   700,  1144,   188,   188,   167,
    1187,   169,    57,   704,   705,   216,   125,   126,    63,   216,
     186,     5,     6,   196,     8,   208,  1463,   208,   208,   720,
     721,   722,   723,   216,   725,   216,   216,   239,   240,   730,
     206,  1605,   243,   224,   224,   188,   243,   737,  1323,  1562,
     147,   188,    36,   150,   151,   216,   196,   166,   748,    70,
      71,    72,   971,   160,   188,   208,   756,   976,   188,  1515,
     188,   208,   200,   216,   183,   184,   185,   186,   196,   216,
     770,   224,   243,   220,   208,   216,   181,   196,   208,   216,
     208,   188,  1538,   196,    57,   786,   216,   206,   216,   188,
      63,   196,   188,   114,   115,   116,   117,   245,   216,   188,
     241,   208,   802,   455,   223,   216,   243,  1026,  1027,   208,
     217,   218,   208,   216,  1252,   222,  1271,   216,   225,   208,
    1258,   240,   188,   241,   196,   224,  1279,   216,   244,   245,
     241,   216,   484,   240,   486,   224,  1421,   188,   241,   246,
    1663,   216,   216,   216,    79,   216,   196,  1300,   216,   501,
     502,   852,   181,  1306,  1561,  1310,  1311,   208,   243,    94,
      33,   188,  1315,    57,    99,   216,   101,   196,   243,   243,
     243,  1324,   243,   224,   874,   243,   698,   699,   700,   188,
     207,   208,   209,   883,  1322,   223,   886,    60,    61,  1171,
     187,   543,   544,   898,  1768,  1348,   718,   223,   207,   208,
     187,   210,    57,    47,   242,   910,   187,  1360,    63,   196,
     207,   733,  1365,  1132,   181,   196,   242,   917,   200,   201,
     207,   223,   927,    67,    12,   930,   207,   932,   233,   196,
     200,   223,   129,   208,  1429,    23,    24,   942,  1685,  1429,
     242,   216,   167,  1162,    66,   208,   208,   599,   600,   601,
     242,   603,   604,   216,   216,   607,   208,   609,   196,   611,
     216,   613,  1415,   219,   216,   219,   222,   968,   222,   969,
     970,   971,  1760,    57,   147,    57,   976,   150,   151,    63,
     980,    63,    96,    97,  1569,   985,   986,   160,   988,    10,
     990,   220,   992,   993,    57,   224,   217,  1452,   220,  1004,
      63,  1757,   224,   219,   207,  1460,  1762,   210,   196,   220,
     213,  1012,  1800,   224,  1015,   220,   220,  1018,  1019,   224,
     224,   220,  1475,    35,   220,   224,  1026,  1027,   224,    35,
     852,   131,   132,   133,   134,   135,   136,   137,   138,    75,
    1026,  1027,  1798,    79,   217,   218,   167,   168,   169,   222,
    1503,  1504,   225,   219,  1507,   220,   222,    93,    94,   224,
     160,   242,    98,    99,   100,   101,   219,   240,   242,    43,
     170,   171,   172,   246,  1683,  1614,   223,   220,   220,   242,
    1667,   224,   224,   905,   220,  1239,   223,  1525,   224,  1628,
     196,   197,   198,   200,   201,   202,   223,   223,   920,   200,
     201,   202,   242,   223,   756,  1558,   223,   223,  1864,  1110,
     131,   132,   133,   134,   135,   136,   137,   138,   770,   223,
     942,   223,   220,   144,   145,   673,   674,   675,   223,   150,
     242,   196,  1132,   241,   196,  1136,    21,    22,   196,   160,
    1422,    22,   163,   164,  1144,    10,    11,    12,   196,   170,
     171,   172,   241,   196,   241,  1429,  1743,  1744,   810,   811,
     240,   196,  1162,   196,   223,   196,  1171,   242,   208,  1622,
     243,   223,   223,   825,   223,   242,    33,   223,   223,   223,
      13,   242,  1004,    43,   223,   242,   223,  1406,  1193,  1194,
    1195,   843,   242,   223,   223,   242,   217,   223,   196,  1418,
     242,   242,   224,    60,    61,  1792,   219,   245,   242,   241,
     131,   132,   133,   134,   135,   136,   137,   138,  1437,   242,
    1429,   240,   874,   244,   245,   242,   196,   243,  1666,   150,
     189,   883,  1233,  1772,   886,    33,  1689,   242,   223,   160,
      10,    37,  1524,    66,     8,   242,   223,   223,  1249,   170,
     171,   172,  1252,  1253,   223,   165,   141,   142,  1258,   242,
      13,   241,    60,    61,   149,   917,   151,   152,   153,   154,
     216,   216,   196,   196,   159,  1557,   155,   224,   196,   216,
    1733,   216,   242,  1565,  1438,    43,    33,   242,  1110,   216,
     147,    14,   196,   189,   151,   217,   245,   196,    33,   219,
      67,   196,   243,   242,  1742,   216,   165,   216,  1527,   207,
     243,   242,   242,    60,    61,   216,   223,   969,   970,   971,
     223,     1,  1322,   242,   976,    60,    61,   243,   980,   242,
     242,   188,   196,   985,   986,  1788,   988,   242,   990,   241,
     992,   993,   227,   228,   229,   242,   224,   224,   242,   147,
     242,   208,   242,   151,   239,   240,   224,   243,  1180,   216,
     196,   218,   217,   217,   196,   222,   196,   224,   225,   243,
     243,  1193,  1194,  1195,  1026,  1027,  1198,  1659,  1200,   242,
    1202,   243,  1204,   240,  1206,   243,  1208,   243,  1210,   246,
    1212,   243,  1214,   243,  1216,   242,  1218,   241,   241,  1221,
     147,  1223,   219,  1225,   151,  1227,  1406,  1229,   243,  1231,
      21,    22,   147,   196,   196,   242,   151,  1422,  1418,   196,
     218,   196,   223,   242,   222,  1644,   224,   225,   242,   242,
     196,   196,   242,  1085,    43,    12,    33,  1437,   243,   242,
     196,   241,   240,   242,   204,   242,   196,  1729,   246,   243,
     241,   196,   196,   241,   196,   242,    21,    22,   242,  1741,
      70,   224,   242,   224,   243,   243,   242,   224,   242,   242,
     242,   218,   243,   200,   243,   222,   208,   224,   225,  1480,
    1132,   243,   208,   218,   243,    53,   241,   222,   242,   224,
     225,  1492,  1144,   240,   242,   207,   242,   208,   216,   246,
     243,   242,   241,   243,   242,   240,   243,   243,   241,   243,
    1162,   246,   243,   243,  1668,  1797,   207,   241,   243,  1524,
     789,   243,   243,   243,   241,  1525,   452,  1527,   139,   140,
     141,   142,   241,   243,   241,   461,    86,     1,   149,   147,
     151,   152,   153,   154,    89,   471,  1661,   221,   159,  1661,
     161,   162,  1557,   737,  1186,   481,  1661,  1661,  1559,  1560,
    1565,  1770,  1661,  1659,    33,     1,  1567,  1189,  1335,  1522,
    1779,  1577,  1573,  1440,   139,   140,   141,   142,   143,  1443,
    1236,   146,   147,   148,   149,  1578,   151,   152,   153,   154,
      58,    60,    61,  1578,   159,    33,   161,   162,  1152,   516,
    1252,  1253,   167,   168,   169,   442,  1258,   322,   534,   535,
     516,  1820,    33,  1762,   225,   226,   227,   228,   229,  1298,
      33,  1612,    60,    61,   782,    -1,    -1,    -1,   239,   240,
      -1,   557,   558,   559,   560,   561,   562,   563,    -1,    60,
      61,    -1,  1796,    -1,  1644,    -1,    -1,    60,    61,    -1,
      -1,    -1,    -1,   218,  1659,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,    -1,  1666,    -1,    -1,    -1,
    1322,    -1,    -1,    -1,   239,   240,    -1,    -1,   147,    -1,
      -1,  1835,   151,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   617,    -1,    -1,    -1,    -1,  1697,    -1,    -1,    -1,
      -1,   627,    -1,  1704,    -1,  1706,    -1,    -1,    -1,   147,
      -1,  1712,    -1,   151,    -1,  1715,  1717,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1729,    -1,   147,    -1,    -1,    -1,
     151,    -1,    -1,    -1,   147,    -1,  1741,    -1,   151,  1561,
      -1,    33,  1742,   669,    -1,    -1,  1747,    -1,    -1,   218,
      -1,    -1,    -1,   222,  1406,   224,   225,    -1,   684,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1418,    -1,    60,    61,
      -1,   240,    -1,    -1,    -1,  1776,    -1,   246,  1778,    -1,
     218,    -1,    -1,    -1,   222,  1437,   224,   225,    -1,    -1,
      -1,    -1,  1797,    -1,  1795,    -1,    -1,   218,    -1,    -1,
      -1,   222,   240,   224,   225,   218,    -1,    -1,   246,   222,
      -1,   224,   225,    -1,    -1,    -1,    -1,    -1,    -1,   240,
    1821,  1822,    -1,    -1,    -1,   246,    -1,   240,    -1,   755,
    1831,  1832,   758,   246,    -1,   761,    -1,   763,    -1,   765,
      -1,    -1,   768,   504,    -1,   506,    -1,   773,   774,   775,
     776,   777,   778,    -1,    -1,   147,  1857,    -1,  1859,   151,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1525,    -1,  1527,    -1,    -1,    -1,    -1,
      -1,    -1,   808,    -1,    -1,    -1,   812,   813,    -1,    -1,
     816,   817,   818,   819,    -1,   821,    -1,   823,   824,   825,
     826,   827,   828,   829,   830,   831,   832,   833,   834,   835,
     836,   837,   838,   839,   840,   841,   842,    33,   844,    -1,
     846,    -1,    -1,    -1,    -1,    -1,   218,    -1,    -1,    -1,
     222,    -1,   224,   225,    -1,    10,    -1,   598,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    61,    21,    22,   240,    -1,
      -1,    -1,    -1,    -1,   246,   945,   946,   947,   948,   949,
     950,   951,   952,   953,   954,    -1,   956,   957,   958,   959,
     960,   961,    -1,    -1,    -1,   901,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1644,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1666,    -1,    -1,    -1,    -1,   680,
      -1,    -1,    -1,   684,    -1,    -1,   687,    -1,   689,    -1,
      -1,   147,    -1,   694,    -1,   151,   697,    -1,    -1,    -1,
      -1,   702,    -1,    -1,    -1,   706,   972,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,
      22,    -1,    -1,    -1,   139,   140,   141,   142,   143,    -1,
      -1,   146,   147,   148,   149,    -1,   151,   152,   153,   154,
      -1,  1007,  1008,  1009,   159,    -1,   161,   162,    -1,    -1,
    1742,  1017,   167,   168,   169,    -1,    -1,    -1,   173,    -1,
      -1,    -1,   218,    -1,    -1,    -1,   222,    -1,   224,   225,
    1036,    -1,    -1,   188,    -1,    -1,    -1,    -1,    -1,   780,
      -1,   782,    -1,  1049,   240,    -1,    -1,    -1,    -1,    -1,
     246,    -1,    -1,   208,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   216,    -1,   218,    -1,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   239,   240,    -1,    -1,    -1,    -1,
      -1,    -1,  1098,    -1,    -1,    -1,  1102,   139,   140,   141,
     142,   143,    -1,    -1,   146,   147,   148,   149,   849,   151,
     152,   153,   154,    -1,    -1,    -1,    -1,   159,    -1,   161,
     162,    -1,    -1,    -1,    -1,   167,   168,   169,    21,    22,
      -1,   173,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     881,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     901,    -1,    -1,    -1,  1170,    -1,   907,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   218,   918,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   239,   240,    -1,
      -1,   243,    -1,   944,   945,   946,   947,   948,   949,   950,
     951,   952,   953,   954,   955,   956,   957,   958,   959,   960,
     961,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   973,    -1,   975,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   139,   140,   141,   142,
     143,    -1,    -1,   146,   147,   148,   149,    -1,   151,   152,
     153,   154,    -1,    -1,    -1,    -1,   159,    -1,   161,   162,
      -1,    -1,    -1,  1279,   167,  1281,   169,    -1,  1284,    -1,
    1021,    -1,    -1,    -1,    -1,    -1,    21,    22,  1029,    -1,
      -1,    -1,    -1,    -1,  1300,    -1,    -1,    -1,    -1,    -1,
    1306,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1315,
      -1,    -1,    -1,    -1,  1320,  1321,    -1,    -1,  1324,    -1,
      -1,    -1,    -1,    -1,  1330,    -1,    -1,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,    -1,    -1,  1345,
      -1,  1347,  1348,  1349,    -1,    -1,   239,   240,    -1,  1355,
      -1,    -1,    -1,  1359,  1360,    -1,    -1,    -1,    -1,  1365,
      -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,
    1111,  1112,  1113,  1114,  1115,  1116,  1117,  1118,  1119,  1120,
    1121,  1122,  1123,  1124,  1125,  1126,  1127,    -1,    -1,    -1,
      -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    33,    -1,    -1,   139,   140,   141,   142,   143,  1415,
      -1,   146,   147,   148,   149,    -1,   151,   152,   153,   154,
      -1,    -1,    -1,  1164,   159,    -1,   161,   162,    60,    61,
      -1,    -1,   167,   168,   169,    -1,    -1,    -1,   173,    -1,
      -1,    -1,    -1,    -1,  1185,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1475,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   147,    -1,
      -1,    -1,   151,   218,    -1,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,    -1,    -1,  1503,  1504,    -1,
      -1,  1507,    -1,    -1,   239,   240,    -1,    -1,   243,  1515,
      -1,    -1,    -1,    -1,    -1,   147,    -1,    -1,    -1,   151,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1533,    -1,  1535,
      -1,    -1,  1538,    -1,    -1,  1541,    -1,    -1,    -1,    -1,
      -1,  1282,  1283,    -1,    -1,    -1,  1287,    -1,    -1,   218,
      -1,    -1,  1558,   222,  1295,   224,   225,  1298,    -1,    -1,
      13,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,
      -1,   240,    25,    33,    -1,    -1,    -1,   246,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   218,    -1,    41,    -1,
     222,    -1,   224,   225,    -1,  1601,    49,    -1,  1604,    -1,
      60,    61,  1608,    -1,    -1,  1611,    -1,    -1,   240,    -1,
      -1,    64,    -1,    -1,   246,  1621,  1622,    -1,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,    -1,    -1,    -1,  1683,  1419,    21,
      22,    -1,    -1,  1689,    -1,  1426,    -1,   147,  1429,    -1,
      -1,   151,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1714,    -1,
      -1,    -1,    -1,   166,    -1,    -1,   131,   132,   133,   134,
     135,   136,   137,   138,    -1,    -1,   179,  1733,    -1,   144,
     145,    -1,    -1,    -1,    -1,   150,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   196,    -1,   160,    -1,    -1,   163,   164,
      -1,    -1,    -1,    -1,    -1,   170,   171,   172,   218,    -1,
      -1,    -1,   222,    -1,   224,   225,    -1,  1773,    -1,    -1,
      -1,    -1,    -1,   188,    -1,    -1,    -1,    -1,    -1,    -1,
     240,    -1,  1788,    -1,    21,    22,   246,    -1,    -1,    -1,
      -1,   244,    -1,   208,    -1,    -1,    -1,   139,   140,   141,
     142,   143,   217,    -1,   146,   147,   148,   149,    -1,   151,
     152,   153,   154,    -1,    -1,  1556,    -1,   159,  1824,   161,
     162,    21,    22,    -1,    -1,   167,   168,   169,    -1,   244,
     245,   173,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1583,    -1,  1585,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1594,  1595,  1596,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1609,  1610,
      -1,    -1,    -1,    -1,  1615,    -1,   218,    -1,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,    -1,    -1,
      -1,    -1,    -1,    -1,  1635,    -1,    -1,   239,   240,    -1,
      -1,   243,   139,   140,   141,   142,   143,    -1,    -1,   146,
     147,   148,   149,    -1,   151,   152,   153,   154,    -1,    -1,
    1661,    -1,   159,    -1,   161,   162,    -1,    -1,    -1,    -1,
     167,   168,   169,    -1,    -1,    -1,   173,    -1,    -1,   139,
     140,   141,   142,   143,    -1,    -1,   146,   147,   148,   149,
      -1,   151,   152,   153,   154,    -1,    -1,  1698,  1699,   159,
      -1,   161,   162,    -1,    -1,    -1,    -1,   167,   168,   169,
      -1,    -1,    -1,   173,    -1,    -1,    -1,    -1,    -1,  1720,
      -1,   218,    -1,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,  1734,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   239,   240,  1745,    -1,   243,    -1,    -1,    -1,
      -1,  1752,    -1,  1754,    -1,    -1,    -1,    -1,   218,    -1,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   239,
     240,    -1,    -1,   243,    -1,    -1,    -1,    -1,  1789,    -1,
      -1,    -1,  1793,  1794,     1,    -1,    -1,    -1,     5,     6,
       7,    -1,     9,    10,    11,    -1,    13,    -1,    15,    16,
      17,    18,    19,    -1,  1815,    -1,  1817,  1818,    25,    26,
      27,    28,    29,    -1,    31,    -1,    -1,    -1,    -1,  1830,
      -1,    38,    39,    40,    -1,    42,    -1,    44,    45,    -1,
      -1,    48,    -1,    50,    51,    52,    -1,    54,    55,    -1,
      -1,    58,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    68,    69,    -1,    71,    72,    73,    -1,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    -1,    93,    94,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   141,   142,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,
     157,   158,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,   176,
     177,   178,    -1,   180,    -1,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,    -1,    -1,    -1,    -1,    -1,    -1,   206,
     207,   208,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,
     227,    -1,   229,    -1,    -1,   232,   233,    -1,    -1,     5,
       6,    -1,    -1,   240,    -1,   242,    -1,   244,   245,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,
      -1,    27,    -1,    -1,    -1,    31,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    48,    -1,    -1,    51,    -1,    53,    -1,    55,
      -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    65,
      -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    -1,    93,    94,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   141,   142,    -1,    -1,    -1,
      -1,   147,    -1,    -1,    -1,   151,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,
     176,   177,   178,    -1,   180,   181,   182,   183,   184,   185,
     186,    -1,    -1,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,    -1,    -1,    -1,    -1,    -1,    -1,
     206,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   218,    -1,    -1,    -1,   222,    -1,    -1,   225,
     226,   227,    -1,   229,    -1,    -1,   232,   233,    -1,    -1,
      -1,     5,     6,    -1,   240,    -1,   242,    -1,   244,   245,
     246,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    60,    61,    -1,    -1,
      -1,    65,    -1,    -1,    68,    69,    -1,    71,    72,    73,
      -1,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    -1,    93,
      94,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,   142,    -1,
      -1,    -1,    -1,   147,    -1,    -1,    -1,   151,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     174,   175,   176,   177,   178,    -1,   180,   181,   182,   183,
     184,   185,   186,    -1,    -1,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,    -1,    -1,    -1,    -1,
      -1,    -1,   206,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   218,    -1,    -1,    -1,   222,    -1,
      -1,   225,   226,   227,    -1,   229,    -1,    -1,   232,   233,
      -1,    -1,    -1,     5,     6,    -1,   240,    -1,   242,    -1,
     244,   245,   246,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,
      -1,    33,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    -1,    51,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    68,    69,    -1,    71,
      72,    73,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      -1,    93,    94,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,
     142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,   176,   177,   178,    -1,   180,    -1,
     182,   183,   184,   185,   186,    -1,    -1,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,    -1,    -1,
      -1,    -1,    -1,    -1,   206,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     222,    -1,    -1,   225,   226,   227,    -1,   229,    -1,    -1,
     232,   233,    -1,    -1,    -1,     5,     6,    -1,   240,    -1,
     242,    -1,   244,   245,   246,    15,    16,    17,    18,    19,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,
      -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,
      -1,    71,    72,    73,    -1,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   141,   142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     150,    -1,    -1,    -1,    -1,    -1,   156,   157,   158,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   166,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   174,   175,   176,   177,   178,    -1,
     180,    -1,   182,   183,   184,   185,   186,    -1,    -1,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
      -1,    -1,    -1,    -1,    -1,    -1,   206,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   225,   226,   227,    -1,   229,
      -1,    -1,   232,   233,    -1,    -1,     5,     6,    -1,    -1,
     240,    -1,   242,    -1,   244,   245,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,
      69,    -1,    71,    72,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    93,    94,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   141,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   150,    -1,    -1,    -1,    -1,    -1,   156,   157,   158,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   174,   175,   176,   177,   178,
      -1,   180,    -1,   182,   183,   184,   185,   186,    -1,    -1,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,    -1,    -1,    -1,    -1,    -1,    -1,   206,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   225,   226,   227,    -1,
     229,    -1,    -1,   232,   233,    -1,    -1,     5,     6,    -1,
      -1,   240,    -1,   242,    -1,   244,   245,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,    -1,    25,    26,    27,
      28,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,    -1,    -1,    51,    52,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      68,    69,    -1,    71,    72,    73,    -1,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    -1,    93,    94,    95,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   141,   142,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   174,   175,   176,   177,
     178,    -1,   180,    -1,   182,   183,   184,   185,   186,    -1,
      -1,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,    -1,    -1,    -1,    -1,    -1,    -1,   206,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,   227,
      -1,   229,    -1,    -1,   232,   233,    -1,    -1,     5,     6,
      -1,    -1,   240,    -1,   242,    -1,   244,   245,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    48,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    68,    69,    -1,    71,    72,    73,    -1,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    -1,    93,    94,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   141,   142,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,
     157,   158,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,   176,
     177,   178,    -1,   180,    -1,   182,   183,   184,   185,   186,
      -1,    -1,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,    -1,    -1,    -1,    -1,    -1,    -1,   206,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,
     227,    -1,   229,    -1,    -1,   232,   233,    -1,    -1,     5,
       6,    -1,    -1,   240,    -1,   242,    -1,   244,   245,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,
      -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    48,    -1,    -1,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    68,    69,    70,    71,    72,    73,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    -1,    93,    94,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   141,   142,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,
     176,   177,   178,    -1,   180,   181,   182,   183,   184,   185,
     186,    -1,    -1,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,    -1,    -1,    -1,    -1,    -1,    -1,
     206,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,
     226,   227,    -1,   229,    -1,    -1,   232,   233,    -1,    -1,
       5,     6,    -1,    -1,   240,    -1,   242,   243,   244,   245,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    -1,    33,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,    -1,
      55,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   141,   142,    -1,   147,
      -1,    -1,    -1,   151,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   156,   157,   158,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,
     175,   176,   177,   178,    -1,   180,    33,   182,   183,   184,
     185,   186,    -1,    -1,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,    -1,    -1,    -1,    -1,    -1,
      -1,   206,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,
     218,    -1,    -1,    -1,   222,    -1,   224,   225,    -1,    -1,
     225,   226,   227,    -1,   229,    -1,    -1,   232,   233,    -1,
      -1,    -1,   240,     5,     6,   240,    -1,   242,   246,   244,
     245,    13,    -1,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    49,    -1,    51,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
     147,    -1,    -1,    65,   151,    -1,    68,    69,    -1,    71,
      72,    73,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      -1,    93,    94,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,    -1,    -1,    -1,    -1,
      -1,   218,    -1,    -1,    -1,   222,    -1,   224,   225,   141,
     142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   240,    -1,    -1,    -1,    -1,    -1,   246,
      -1,    -1,    -1,    -1,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,   176,   177,   178,    -1,   180,    -1,
     182,   183,   184,   185,   186,    -1,    -1,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,    -1,    -1,
      -1,    -1,    -1,    -1,   206,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   225,   226,   227,    -1,   229,    -1,    -1,
     232,   233,    -1,    -1,    -1,    -1,     5,     6,   240,   241,
     242,    -1,   244,   245,    13,    -1,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      49,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,
      69,    -1,    71,    72,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    93,    94,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   141,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   174,   175,   176,   177,   178,
      -1,   180,   181,   182,   183,   184,   185,   186,    -1,    -1,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,    -1,    -1,    -1,    -1,    -1,    -1,   206,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   225,   226,   227,    -1,
     229,    -1,    -1,   232,   233,    -1,    -1,    -1,    -1,     5,
       6,   240,    -1,   242,    -1,   244,   245,    13,    -1,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,
      -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    48,    49,    -1,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    -1,    93,    94,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   141,   142,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,
     176,   177,   178,    -1,   180,    -1,   182,   183,   184,   185,
     186,    -1,    -1,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,    -1,    -1,    -1,    -1,    -1,    -1,
     206,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,
     226,   227,    -1,   229,    -1,    -1,   232,   233,    -1,    -1,
      -1,    -1,     5,     6,   240,   241,   242,    -1,   244,   245,
      13,    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    48,    49,    -1,    51,    -1,
      -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    68,    69,    -1,    71,    72,
      73,    -1,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    -1,
      93,    94,    95,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,   142,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   174,   175,   176,   177,   178,    -1,   180,    -1,   182,
     183,   184,   185,   186,    -1,    -1,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,    -1,    -1,    -1,
      -1,    -1,    -1,   206,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   225,   226,   227,    -1,   229,    -1,    -1,   232,
     233,    -1,    -1,     5,     6,    -1,    -1,   240,    -1,   242,
      -1,   244,   245,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    -1,    51,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    68,    69,    70,    71,
      72,    73,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      -1,    93,    94,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,
     142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,   176,   177,   178,    -1,   180,   181,
     182,   183,   184,   185,   186,    -1,    -1,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,    -1,    -1,
      -1,    -1,    -1,    -1,   206,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   225,   226,   227,    -1,   229,    -1,    -1,
     232,   233,    -1,    -1,     5,     6,    -1,    -1,   240,    -1,
     242,    -1,   244,   245,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    -1,
      51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,    -1,
      71,    72,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,    93,    94,    95,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     141,   142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   166,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   174,   175,   176,   177,   178,    -1,   180,
      -1,   182,   183,   184,   185,   186,    -1,    -1,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,    -1,
      -1,    -1,    -1,    -1,    -1,   206,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   225,   226,   227,    -1,   229,    -1,
      -1,   232,   233,    -1,    -1,    -1,    -1,     5,     6,   240,
     241,   242,    -1,   244,   245,    13,    -1,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      68,    69,    -1,    71,    72,    73,    -1,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    -1,    93,    94,    95,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   141,   142,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   174,   175,   176,   177,
     178,    -1,   180,    -1,   182,   183,   184,   185,   186,    -1,
      -1,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,    -1,    -1,    -1,    -1,    -1,    -1,   206,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,   227,
      -1,   229,    -1,    -1,   232,   233,    -1,    -1,    -1,    -1,
       5,     6,   240,    -1,   242,    -1,   244,   245,    13,    -1,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   141,   142,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,
     175,   176,   177,   178,    -1,   180,    -1,   182,   183,   184,
     185,   186,    -1,    -1,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,    -1,    -1,    -1,    -1,    -1,
      -1,   206,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     225,   226,   227,    -1,   229,    -1,    -1,   232,   233,    -1,
      -1,     5,     6,    -1,    -1,   240,    -1,   242,    -1,   244,
     245,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,
      -1,    65,    -1,    -1,    68,    69,    -1,    71,    72,    73,
      -1,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    -1,    93,
      94,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,   142,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     174,   175,   176,   177,   178,    -1,   180,    -1,   182,   183,
     184,   185,   186,    -1,    -1,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,    -1,    -1,    -1,    -1,
      -1,    -1,   206,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   225,   226,   227,    -1,   229,    -1,    -1,   232,   233,
      -1,    -1,     5,     6,    -1,    -1,   240,    -1,   242,    -1,
     244,   245,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    48,    -1,    -1,    51,    -1,
      -1,    -1,    55,    -1,    -1,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    68,    69,    -1,    71,    72,
      73,    -1,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    -1,
      93,    94,    95,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,   142,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   174,   175,   176,   177,   178,    -1,   180,    -1,   182,
     183,   184,   185,   186,    -1,    -1,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,    -1,    -1,    -1,
      -1,    -1,    -1,   206,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   225,   226,   227,    -1,   229,    -1,    -1,   232,
     233,    -1,    -1,     5,     6,    -1,    -1,   240,    -1,   242,
      -1,   244,   245,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    -1,    51,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    68,    69,    -1,    71,
      72,    73,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      -1,    93,    94,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,
     142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,   176,   177,   178,    -1,   180,    -1,
     182,   183,   184,   185,   186,    -1,    -1,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,    -1,    -1,
      -1,    -1,    -1,    -1,   206,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   223,    -1,   225,   226,   227,    -1,   229,    -1,    -1,
     232,   233,    -1,    -1,     5,     6,    -1,    -1,   240,    -1,
     242,    -1,   244,   245,    15,    16,    17,    18,    19,    -1,
      -1,    22,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    -1,
      51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,    -1,
      71,    72,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,    93,    94,    95,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     141,   142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   166,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   174,   175,   176,   177,   178,    -1,   180,
      -1,   182,   183,   184,   185,   186,    -1,    -1,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,    -1,
      -1,    -1,    -1,    -1,    -1,   206,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   225,   226,   227,    -1,   229,    -1,
      -1,   232,   233,    -1,    -1,     5,     6,    -1,    -1,   240,
      -1,   242,    -1,   244,   245,    15,    16,    17,    18,    19,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,
      -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,
      -1,    71,    72,    73,    -1,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   141,   142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   166,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   174,   175,   176,   177,   178,    -1,
     180,    -1,   182,   183,   184,   185,   186,    -1,    -1,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
      -1,    -1,    -1,    -1,    -1,    -1,   206,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   225,   226,   227,    -1,   229,
      -1,    -1,   232,   233,    -1,    -1,     5,     6,    -1,    -1,
     240,    -1,   242,   243,   244,   245,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,
      69,    -1,    71,    72,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    93,    94,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   141,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   174,   175,   176,   177,   178,
      -1,   180,    -1,   182,   183,   184,   185,   186,    -1,    -1,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,    -1,    -1,    -1,    -1,    -1,    -1,   206,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   223,    -1,   225,   226,   227,    -1,
     229,    -1,    -1,   232,   233,    -1,    -1,     5,     6,    -1,
      -1,   240,    -1,   242,    -1,   244,   245,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      68,    69,    -1,    71,    72,    73,    -1,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    -1,    93,    94,    95,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   141,   142,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   174,   175,   176,   177,
     178,    -1,   180,    -1,   182,   183,   184,   185,   186,    -1,
      -1,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,    -1,    -1,    -1,    -1,    -1,    -1,   206,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,   227,
      -1,   229,    -1,    -1,   232,   233,    -1,    -1,     5,     6,
      -1,    -1,   240,    -1,   242,   243,   244,   245,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    48,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    68,    69,    -1,    71,    72,    73,    -1,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    -1,    93,    94,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   141,   142,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,   176,
     177,   178,    -1,   180,    -1,   182,   183,   184,   185,   186,
      -1,    -1,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,    -1,    -1,    -1,    -1,    -1,    -1,   206,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,
     227,    -1,   229,    -1,    -1,   232,   233,    -1,    -1,     5,
       6,    -1,    -1,   240,    -1,   242,   243,   244,   245,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,
      -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    48,    -1,    -1,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    -1,    93,    94,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   141,   142,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,
     176,   177,   178,    -1,   180,    -1,   182,   183,   184,   185,
     186,    -1,    -1,   189,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,    -1,    -1,    -1,    -1,    -1,    -1,
     206,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,
     226,   227,    -1,   229,    -1,    -1,   232,   233,    -1,    -1,
       5,     6,    -1,    -1,   240,    -1,   242,   243,   244,   245,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   141,   142,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,
     175,   176,   177,   178,    -1,   180,    -1,   182,   183,   184,
     185,   186,    -1,    -1,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,    -1,    -1,    -1,    -1,    -1,
      -1,   206,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     225,   226,   227,    -1,   229,    -1,    -1,   232,   233,    -1,
      -1,     5,     6,    -1,    -1,   240,    -1,   242,   243,   244,
     245,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    68,    69,    -1,    71,    72,    73,
      -1,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    -1,    93,
      94,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,   142,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     174,   175,   176,   177,   178,    -1,   180,    -1,   182,   183,
     184,   185,   186,    -1,    -1,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,    -1,    -1,    -1,    -1,
      -1,    -1,   206,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   225,   226,   227,    -1,   229,    -1,    -1,   232,   233,
      -1,    -1,     5,     6,    -1,    -1,   240,    -1,   242,   243,
     244,   245,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    48,    -1,    -1,    51,    -1,
      -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    68,    69,    -1,    71,    72,
      73,    -1,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    -1,
      93,    94,    95,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,   142,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   166,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   174,   175,   176,   177,   178,    -1,   180,    -1,   182,
     183,   184,   185,   186,    -1,    -1,   189,   190,   191,   192,
     193,   194,   195,   196,   197,   198,   199,    -1,    -1,    -1,
      -1,    -1,    -1,   206,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   225,   226,   227,    -1,   229,    -1,    -1,   232,
     233,    -1,    -1,     5,     6,    -1,    -1,   240,    -1,   242,
     243,   244,   245,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    -1,    51,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    68,    69,    -1,    71,
      72,    73,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      -1,    93,    94,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,
     142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   166,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   174,   175,   176,   177,   178,    -1,   180,    -1,
     182,   183,   184,   185,   186,    -1,    -1,   189,   190,   191,
     192,   193,   194,   195,   196,   197,   198,   199,    -1,    -1,
      -1,    -1,    -1,    -1,   206,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   225,   226,   227,    -1,   229,    -1,    -1,
     232,   233,    -1,    -1,     5,     6,    -1,    -1,   240,    -1,
     242,   243,   244,   245,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    -1,
      51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,    -1,
      71,    72,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,    93,    94,    95,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     141,   142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   166,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   174,   175,   176,   177,   178,    -1,   180,
      -1,   182,   183,   184,   185,   186,    -1,    -1,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,    -1,
      -1,    -1,    -1,    -1,    -1,   206,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   225,   226,   227,    -1,   229,    -1,
      -1,   232,   233,    -1,    -1,     5,     6,    -1,    -1,   240,
      -1,   242,    -1,   244,   245,    15,    16,    17,    18,    19,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,
      -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,
      -1,    71,    72,    73,    -1,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   141,   142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     150,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   166,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   174,   175,   176,   177,   178,    -1,
     180,    -1,   182,   183,   184,   185,   186,    -1,    -1,   189,
     190,   191,   192,   193,   194,   195,   196,   197,   198,   199,
      -1,    -1,    -1,    -1,    -1,    -1,   206,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   225,   226,   227,    -1,   229,
      -1,    -1,   232,   233,    -1,    -1,     5,     6,    -1,    -1,
     240,    -1,   242,    -1,   244,   245,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,
      69,    -1,    71,    72,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    93,    94,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   141,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   150,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   174,   175,   176,   177,   178,
      -1,   180,    -1,   182,   183,   184,   185,   186,    -1,    -1,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,    -1,    -1,    -1,    -1,    -1,    -1,   206,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   225,   226,   227,    -1,
     229,    -1,    -1,   232,   233,    -1,    -1,     5,     6,    -1,
      -1,   240,    -1,   242,    -1,   244,   245,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      68,    69,    -1,    71,    72,    73,    -1,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    -1,    93,    94,    95,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   141,   142,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   174,   175,   176,   177,
     178,    -1,   180,    -1,   182,   183,   184,   185,   186,    -1,
      -1,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,    -1,    -1,    -1,    -1,    -1,    -1,   206,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   225,   226,   227,
      -1,   229,    -1,    -1,   232,   233,    -1,    -1,     5,     6,
      -1,    -1,   240,    -1,   242,    -1,   244,   245,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    48,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    68,    69,    -1,    71,    72,    73,    -1,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    -1,    93,    94,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   141,   142,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,   175,   176,
     177,   178,    -1,   180,    -1,   182,   183,   184,   185,   186,
      -1,    -1,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,    -1,    -1,    13,    -1,    -1,    -1,   206,
      -1,    19,    -1,    -1,    -1,    21,    22,    25,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,   225,   226,
     227,    -1,   229,    41,    -1,   232,   233,    -1,    -1,    -1,
      -1,    49,    -1,   240,    -1,   242,    -1,   244,   245,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   139,   140,   141,   142,   143,    -1,    -1,
     146,   147,   148,   149,    -1,   151,   152,   153,   154,    -1,
      -1,    -1,    -1,   159,    -1,   161,   162,    -1,   166,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   179,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    22,    -1,    19,    -1,    -1,   196,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    49,   222,   223,   224,   225,
     226,   227,   228,   229,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    -1,   239,   240,    -1,   244,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     139,   140,   141,   142,   143,    -1,    -1,   146,   147,   148,
     149,    -1,   151,   152,   153,   154,    -1,    -1,    -1,    -1,
     159,    -1,   161,   162,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   179,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    19,   196,    -1,    21,    22,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    41,   223,   224,   225,   226,   227,   228,
     229,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     239,   240,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,
     244,    -1,   246,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   139,   140,   141,   142,   143,    -1,    -1,   146,
      -1,    -1,   149,    -1,   151,   152,   153,   154,    -1,    -1,
      -1,    -1,   159,    -1,   161,   162,    -1,    -1,   166,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   179,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     188,    -1,    -1,    -1,    -1,    19,    -1,    -1,   196,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
     208,    -1,    -1,    -1,    -1,    -1,    -1,    41,   216,    -1,
      -1,    -1,    -1,    -1,    -1,    49,   223,   224,   225,   226,
     227,   228,   229,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    -1,   239,   240,    -1,    -1,   244,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,    -1,   131,   132,   133,   134,   135,   136,
     137,   138,    -1,    -1,    -1,    -1,    -1,   144,   145,    -1,
      -1,    -1,    -1,   150,    -1,    -1,    -1,    -1,   155,    -1,
      -1,    -1,    -1,   160,    -1,    -1,   163,   164,    -1,    -1,
      -1,    -1,   166,   170,   171,   172,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   179,    -1,    -1,    -1,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      -1,    -1,   196,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     217,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    64,    -1,    -1,   244,   245,    -1,
     244,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   139,   140,   141,
     142,   143,    21,    22,   146,   147,   148,   149,    -1,   151,
     152,   153,   154,    -1,    -1,    -1,    -1,   159,    -1,   161,
     162,    -1,    -1,    -1,    -1,   167,   168,   169,    -1,    -1,
      -1,   173,    -1,    -1,    -1,    -1,   166,    21,    22,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   179,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   196,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   218,    -1,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   239,   240,    -1,
      -1,   243,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   244,    -1,    -1,    -1,    -1,    -1,
     139,   140,   141,   142,   143,    -1,    -1,   146,   147,   148,
     149,    -1,   151,   152,   153,   154,    -1,    -1,    -1,    -1,
     159,    -1,   161,   162,    21,    22,    -1,    -1,   167,   168,
     169,    -1,    -1,    -1,   173,   139,   140,   141,   142,   143,
      -1,    -1,   146,   147,   148,   149,    -1,   151,   152,   153,
     154,    -1,    -1,    -1,    -1,   159,    -1,   161,   162,    21,
      22,    -1,    -1,   167,   168,   169,    -1,    -1,    -1,   173,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,
      -1,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     239,   240,    -1,    -1,   243,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   218,    -1,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   239,   240,    -1,    -1,   243,
      -1,    -1,   139,   140,   141,   142,   143,    -1,    -1,   146,
     147,   148,   149,    -1,   151,   152,   153,   154,    -1,    -1,
      -1,    -1,   159,    -1,   161,   162,    21,    22,    -1,    -1,
     167,   168,   169,    -1,    -1,    -1,   173,   139,   140,   141,
     142,   143,    -1,    -1,   146,   147,   148,   149,    -1,   151,
     152,   153,   154,    -1,    -1,    -1,    -1,   159,    -1,   161,
     162,    21,    22,    -1,    -1,   167,   168,   169,    -1,    -1,
      -1,   173,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   218,    -1,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   239,   240,    -1,    -1,   243,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   218,    -1,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   239,   240,    -1,
      -1,   243,    -1,    -1,   139,   140,   141,   142,   143,    -1,
      -1,   146,   147,   148,   149,    -1,   151,   152,   153,   154,
      -1,    -1,    -1,    -1,   159,    -1,   161,   162,    21,    22,
      -1,    -1,   167,   168,   169,    -1,    -1,    -1,   173,   139,
     140,   141,   142,   143,    -1,    -1,   146,   147,   148,   149,
      -1,   151,   152,   153,   154,    -1,    -1,    -1,    -1,   159,
      -1,   161,   162,    21,    22,    -1,    -1,   167,   168,   169,
      -1,    -1,    -1,   173,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   218,    -1,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   239,   240,    -1,    -1,   243,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,    -1,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   239,
     240,    -1,    -1,   243,    -1,    -1,   139,   140,   141,   142,
     143,    -1,    -1,   146,   147,   148,   149,    -1,   151,   152,
     153,   154,    -1,    -1,    -1,    -1,   159,    -1,   161,   162,
      21,    22,    -1,    -1,   167,   168,   169,    -1,    -1,    -1,
     173,   139,   140,   141,   142,   143,    -1,    -1,   146,   147,
     148,   149,    -1,   151,   152,   153,   154,    -1,    -1,    -1,
      -1,   159,    -1,   161,   162,    21,    22,    -1,    -1,   167,
     168,   169,    -1,    -1,    -1,   173,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   218,    -1,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   239,   240,    -1,    -1,
     243,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     218,    -1,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   239,   240,    -1,    -1,   243,    -1,    -1,   139,   140,
     141,   142,   143,    -1,    -1,   146,   147,   148,   149,    -1,
     151,   152,   153,   154,    -1,    -1,    -1,    -1,   159,    -1,
     161,   162,    21,    22,    -1,    -1,   167,   168,   169,    -1,
      -1,    -1,   173,   139,   140,   141,   142,   143,    -1,    -1,
     146,   147,   148,   149,    -1,   151,   152,   153,   154,    -1,
      -1,    -1,    -1,   159,    -1,   161,   162,    21,    22,    -1,
      -1,   167,   168,   169,    -1,    -1,    -1,   173,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,    -1,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   239,   240,
      -1,    -1,   243,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   218,    -1,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   239,   240,    -1,    -1,   243,    -1,    -1,
     139,   140,   141,   142,   143,    -1,    -1,   146,   147,   148,
     149,    -1,   151,   152,   153,   154,    -1,    -1,    -1,    -1,
     159,    -1,   161,   162,    21,    22,    -1,    -1,   167,   168,
     169,    -1,    -1,    -1,   173,   139,   140,   141,   142,   143,
      -1,    -1,   146,   147,   148,   149,    -1,   151,   152,   153,
     154,    -1,    -1,    -1,    -1,   159,    -1,   161,   162,    21,
      22,    -1,    -1,   167,   168,   169,    -1,    -1,    -1,   173,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,
      -1,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     239,   240,    -1,    -1,   243,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   218,    -1,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   239,   240,    -1,    -1,   243,
      -1,    -1,   139,   140,   141,   142,   143,    -1,    -1,   146,
     147,   148,   149,    -1,   151,   152,   153,   154,    -1,    -1,
      -1,    -1,   159,    -1,   161,   162,    21,    22,    -1,    -1,
     167,   168,   169,    -1,    -1,    -1,   173,   139,   140,   141,
     142,   143,    -1,    -1,   146,   147,   148,   149,    -1,   151,
     152,   153,   154,    -1,    -1,    -1,    -1,   159,    -1,   161,
     162,    21,    22,    -1,    -1,   167,   168,   169,    -1,    -1,
      -1,   173,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   218,    -1,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   239,   240,    -1,    -1,   243,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   218,    -1,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   239,   240,    -1,
      -1,   243,    -1,    -1,   139,   140,   141,   142,   143,    -1,
      -1,   146,   147,   148,   149,    -1,   151,   152,   153,   154,
      -1,    -1,    -1,    -1,   159,    -1,   161,   162,    21,    22,
      -1,    -1,   167,   168,   169,    -1,    -1,    -1,   173,   139,
     140,   141,   142,   143,    -1,    -1,   146,   147,   148,   149,
      -1,   151,   152,   153,   154,    -1,    -1,    -1,    -1,   159,
      -1,   161,   162,    21,    22,    -1,    -1,   167,   168,   169,
      -1,    -1,    -1,   173,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   218,    -1,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   239,   240,    -1,    -1,   243,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,    -1,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   239,
     240,    -1,    -1,   243,    -1,    -1,   139,   140,   141,   142,
     143,    -1,    -1,   146,   147,   148,   149,    -1,   151,   152,
     153,   154,    -1,    -1,    -1,    -1,   159,    -1,   161,   162,
      21,    22,    -1,    -1,   167,   168,   169,    -1,    -1,    -1,
     173,   139,   140,   141,   142,   143,    -1,    -1,   146,   147,
     148,   149,    -1,   151,   152,   153,   154,    -1,    -1,    -1,
      -1,   159,    -1,   161,   162,    21,    22,    -1,    -1,   167,
     168,   169,    -1,    -1,    -1,   173,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   218,    -1,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   239,   240,    -1,    -1,
     243,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     218,    -1,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   239,   240,    -1,    -1,   243,    -1,    -1,   139,   140,
     141,   142,   143,    -1,    -1,   146,   147,   148,   149,    -1,
     151,   152,   153,   154,    -1,    -1,    -1,    -1,   159,    -1,
     161,   162,    21,    22,    -1,    -1,   167,   168,   169,    -1,
      -1,    -1,   173,   139,   140,   141,   142,   143,    -1,    -1,
     146,   147,   148,   149,    -1,   151,   152,   153,   154,    -1,
      -1,    -1,    -1,   159,    -1,   161,   162,    21,    22,    -1,
      -1,   167,   168,   169,    -1,    -1,    -1,   173,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,    -1,   220,
     221,   222,   223,   224,   225,   226,   227,   228,   229,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   239,   240,
      -1,    -1,   243,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   218,    -1,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   239,   240,    -1,    -1,   243,    -1,    -1,
     139,   140,   141,   142,   143,    -1,    -1,   146,   147,   148,
     149,    -1,   151,   152,   153,   154,    -1,    -1,    -1,    -1,
     159,    -1,   161,   162,    21,    22,    -1,    -1,   167,   168,
     169,    -1,    -1,    -1,   173,   139,   140,   141,   142,   143,
      -1,    -1,   146,   147,   148,   149,    -1,   151,   152,   153,
     154,    -1,    -1,    -1,    -1,   159,    -1,   161,   162,    21,
      22,    -1,    -1,   167,   168,   169,    -1,    -1,    -1,   173,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,
      -1,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     239,   240,   241,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   218,    -1,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   239,   240,   241,    -1,    -1,
      -1,    -1,   139,   140,   141,   142,   143,    -1,    -1,   146,
     147,   148,   149,    -1,   151,   152,   153,   154,    -1,    -1,
      -1,    -1,   159,    -1,   161,   162,    21,    22,    -1,    -1,
     167,   168,   169,    -1,    -1,    -1,   173,   139,   140,   141,
     142,   143,    -1,    -1,   146,   147,   148,   149,    -1,   151,
     152,   153,   154,    -1,    -1,    -1,    -1,   159,    -1,   161,
     162,    21,    22,    -1,    -1,   167,   168,   169,    -1,    -1,
      -1,   173,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   218,    -1,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   239,   240,   241,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   218,    -1,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   239,   240,   241,
      -1,    -1,    -1,    -1,   139,   140,   141,   142,   143,    -1,
      -1,   146,   147,   148,   149,    -1,   151,   152,   153,   154,
      -1,    -1,    -1,    -1,   159,    -1,   161,   162,    -1,    -1,
      -1,    -1,   167,   168,   169,    -1,    -1,    -1,   173,   139,
     140,   141,   142,   143,    -1,    -1,   146,   147,   148,   149,
      -1,   151,   152,   153,   154,    21,    22,    -1,    -1,   159,
      -1,   161,   162,    -1,    -1,    -1,    -1,   167,   168,   169,
      -1,    -1,    38,   173,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   218,    -1,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,    -1,    -1,    21,    22,    -1,
      -1,    -1,    -1,    -1,   239,   240,   241,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,    -1,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   239,
     240,   241,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,    -1,    -1,   151,   152,   153,    -1,    -1,
      -1,    -1,    21,    22,   160,   161,   162,   163,   164,    -1,
      -1,   167,   168,   169,   170,   171,   172,   173,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   139,   140,   141,   142,   143,
      -1,    -1,   146,   147,   148,   149,    -1,   151,   152,   153,
     154,    21,    22,    -1,    -1,   159,    -1,   161,   162,    -1,
      -1,    -1,    -1,   167,   168,   169,    -1,    -1,    -1,   173,
      -1,    -1,   218,    -1,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   188,    -1,   232,   233,    -1,    -1,
      -1,    -1,    -1,   239,   240,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   208,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   218,    -1,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,    -1,    -1,    -1,    -1,
     139,   140,   141,   142,   143,   239,   240,   146,   147,   148,
     149,    -1,   151,   152,   153,   154,    21,    22,    -1,    -1,
     159,    -1,   161,   162,    -1,    -1,    -1,    -1,   167,   168,
     169,    -1,    -1,    -1,   173,    -1,    -1,    -1,    -1,   139,
     140,   141,   142,   143,    -1,    -1,   146,   147,   148,   149,
      -1,   151,   152,   153,   154,    21,    22,    -1,    -1,   159,
      -1,   161,   162,    -1,    -1,    -1,    -1,   167,   168,   169,
      -1,    -1,    -1,   173,    -1,    -1,    -1,    -1,    -1,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     229,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     239,   240,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    21,    22,    -1,    -1,    -1,    -1,    -1,   218,    -1,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
      -1,    -1,    -1,    -1,   139,   140,   141,   142,   143,   239,
     240,   146,   147,   148,   149,    -1,   151,   152,   153,   154,
      21,    22,    -1,    -1,   159,    -1,   161,   162,    -1,    -1,
      -1,    -1,   167,   168,   169,    -1,    -1,    -1,   173,    -1,
      -1,    -1,    -1,   139,   140,   141,   142,   143,    -1,    -1,
     146,   147,   148,   149,    -1,   151,   152,   153,   154,    -1,
      -1,    -1,    -1,   159,    -1,   161,   162,    -1,    -1,    -1,
      -1,   167,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   218,    -1,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,    -1,    -1,    -1,    -1,   139,
     140,   141,   142,   143,   239,   240,   146,   147,   148,   149,
      -1,   151,   152,   153,   154,    -1,    -1,    -1,    -1,   159,
      -1,   161,   162,    -1,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,    -1,    -1,    -1,    -1,   139,   140,
     141,   142,   143,   239,   240,   146,   147,   148,   149,    -1,
     151,   152,   153,   154,    -1,    -1,    -1,    -1,   159,    -1,
     161,   162,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
      19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   239,
     240,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     221,   222,   223,   224,   225,   226,   227,   228,   229,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   239,   240,
      -1,    -1,    71,    72,    73,    19,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    93,    94,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,    -1,    71,    72,    73,
      -1,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    -1,    93,
      94,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,    -1,   181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,    -1,    -1,
      -1,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   181,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   196,    71,    72,    73,    -1,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    -1,    93,    94,    95,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,    71,    72,    73,
      -1,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    -1,    93,
      94,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,    -1,    -1,   181,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   196,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   152,   153,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    -1,    -1,   181,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   196,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    -1,    73,    -1,    75,    76,    77,    78,    79,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,    93,    94,    95,   239,   240,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   131,   132,   133,   134,   135,   136,
     137,   138,    -1,    -1,    -1,    -1,    -1,   144,   145,    -1,
     141,   142,    -1,   150,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   160,    -1,    -1,   163,   164,    -1,    -1,
      -1,    -1,    -1,   170,   171,   172,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   196,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     217,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   244,   245
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   248,     0,     7,    30,    32,    34,    40,    50,    56,
      80,   125,   126,   188,   208,   229,   240,   249,   250,   254,
     263,   265,   266,   271,   303,   308,   344,   428,   435,   439,
     446,   493,   498,   503,    19,    20,   196,   295,   296,   297,
     189,   272,   273,   173,   196,   197,   198,   229,   239,   267,
     268,   269,   186,   206,   313,   436,   196,   244,   252,    57,
      63,   431,   431,   431,   166,   196,   330,    34,    63,   130,
     159,   233,   242,   299,   300,   301,   302,   330,   249,     5,
       6,     8,    36,   443,    62,   426,   217,   216,   219,   216,
     228,   228,   268,   228,    22,    57,   228,   239,   270,   431,
     432,   434,   432,   426,   504,   494,   499,   196,   166,   264,
     301,   301,   301,   242,   167,   168,   169,   216,   241,   130,
     130,   130,   307,    57,    63,   437,    57,    63,   444,    57,
      63,   427,    15,    16,   189,   194,   196,   199,   242,   245,
     256,   296,   189,   273,   268,   268,   268,   196,   267,   267,
     196,   188,   208,   401,   187,   207,   314,   432,   249,    57,
      63,   251,   196,   196,   196,   196,   200,   262,   243,   297,
     301,   301,   301,   301,    57,    63,   309,   311,   196,   438,
     447,   313,   429,   200,   201,   202,   255,    15,    16,   189,
     194,   196,   256,   293,   294,   245,   270,   433,   188,   401,
     233,   253,   505,   495,   500,   200,   243,   312,   219,   313,
     129,   441,   442,   424,   183,   245,   298,   395,   200,   201,
     202,   216,   243,   196,   217,    66,   219,   457,   313,   313,
      35,    71,    73,    75,    76,    77,    78,    79,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    93,
      94,    95,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   141,
     142,   196,   306,   310,    75,    79,    93,    94,    98,    99,
     100,   101,   451,   430,   196,   448,   314,   425,   297,   296,
     245,   249,   175,   196,   422,   423,   293,    19,    25,    31,
      41,    49,    64,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   179,
     244,   330,   450,   452,   453,   458,   464,   492,    79,    94,
      99,   101,   313,   496,   501,    21,    22,    38,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   151,   152,   153,   160,
     161,   162,   163,   164,   167,   168,   169,   170,   171,   172,
     173,   218,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   232,   233,   239,   240,    35,    35,   242,   304,
     313,   315,   313,   196,   314,   219,   440,   313,   445,   395,
     241,   296,   242,    43,   216,   219,   222,   421,   223,   223,
     223,   242,   223,   223,   242,   457,   223,   223,   223,   223,
     223,   242,   330,    33,    60,    61,   147,   151,   218,   222,
     225,   240,   246,   463,   220,   456,   412,   415,   196,   196,
     196,   241,    22,   196,   241,   178,   243,   395,   407,   408,
     409,   149,   219,   305,   318,   430,   217,   401,   330,   402,
     423,   241,     5,     6,    15,    16,    17,    18,    19,    25,
      27,    31,    39,    45,    48,    51,    55,    65,    68,    69,
      80,   125,   126,   127,   141,   142,   174,   175,   176,   177,
     178,   180,   182,   183,   184,   185,   189,   190,   191,   192,
     193,   194,   195,   197,   198,   199,   206,   225,   226,   227,
     232,   233,   240,   242,   244,   245,   261,   263,   313,   324,
     330,   335,   349,   356,   359,   362,   367,   370,   374,   375,
     377,   382,   385,   386,   394,   450,   506,   521,   532,   536,
     549,   552,   196,   196,   464,   150,   160,   217,   420,   465,
     470,   472,   386,   474,   468,   196,   223,   476,   478,   480,
     482,   484,   486,   488,   490,   386,   223,   242,   321,    33,
     222,    33,   222,   240,   246,   241,   386,   240,   246,   464,
     196,   314,   196,   216,   249,   410,   461,   492,   497,   196,
     413,   461,   502,   196,   131,   132,   133,   134,   135,   136,
     137,   138,   160,   170,   171,   172,   131,   132,   133,   134,
     135,   136,   137,   138,   150,   160,   170,   171,   172,   242,
       7,    50,   343,   208,   208,   216,   243,   492,   492,     1,
       9,    10,    11,    13,    26,    28,    29,    38,    40,    42,
      44,    52,    54,    58,    59,    65,   127,   128,   156,   157,
     158,   188,   197,   208,   274,   275,   278,   281,   282,   284,
     287,   288,   289,   290,   314,   316,   317,   319,   324,   329,
     331,   336,   337,   338,   339,   340,   341,   342,   344,   348,
     371,   373,   386,   393,   314,   393,    40,   240,   303,   314,
     404,   401,   223,   223,   223,   332,   452,   506,   242,   330,
     223,     5,   125,   126,   223,   242,   223,   242,   242,   223,
     223,   242,   223,   242,   223,   242,   223,   223,   242,   223,
     223,   386,   386,   242,   242,   242,   242,   242,   242,    13,
     464,    13,   464,    13,   393,   531,   547,   223,   223,   260,
      13,   386,   386,   386,   386,   386,    13,    49,   320,   360,
     386,   360,   245,    13,   322,   531,   548,   196,   242,   303,
      21,    22,   139,   140,   141,   142,   143,   146,   147,   148,
     149,   151,   152,   153,   154,   159,   161,   162,   167,   168,
     169,   173,   218,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   239,   240,   243,   242,    43,   249,   420,
     329,   371,   393,   492,   492,   462,   492,   243,   492,   492,
     243,   224,   459,   492,   304,   492,   304,   492,   304,   410,
     411,   413,   414,   243,   467,   320,   241,   241,   386,   188,
     216,   217,   455,   219,   461,   314,   219,   461,   314,   386,
     175,   196,   417,   418,   449,   409,   409,   409,   393,   285,
     286,   150,   329,   360,   386,   393,   315,    61,   393,   292,
     393,   196,   249,   189,    58,   393,   315,   223,   150,   329,
     393,   245,   315,   362,   366,   366,   366,   393,   249,   249,
     393,    10,    37,   362,   368,   249,   249,   249,   249,   249,
      66,   345,   155,   249,   131,   132,   133,   134,   135,   136,
     137,   138,   144,   145,   150,   160,   163,   164,   170,   171,
     172,   217,   368,   401,   403,   302,     8,   395,   400,   522,
     524,   333,   242,   330,   223,   242,   357,   223,   223,   223,
     543,   360,   464,   322,   386,   350,   352,   386,   354,   386,
     545,   360,   528,   533,   360,   526,   464,   386,   386,   386,
     386,   386,   386,   449,    53,   181,   196,   225,   240,   242,
     393,   507,   510,   514,   530,   535,   449,   242,   510,   535,
     449,   165,   207,   209,   249,   515,   325,   327,   202,   203,
     255,   242,   242,   449,    13,   241,   216,   551,   551,   175,
     180,   223,   330,   376,   449,   314,   216,   551,    70,   240,
     243,   360,   507,   509,     4,   183,   365,    19,   181,   196,
     450,    19,   181,   196,   450,   386,   386,   386,   386,   386,
     386,   196,   386,   181,   196,   386,   386,   386,   450,   386,
     386,   386,   386,   386,   386,    22,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   152,   153,   181,
     196,   239,   240,   383,   450,   386,   243,   360,   196,   329,
     393,   131,   132,   133,   134,   135,   136,   137,   138,   144,
     145,   150,   163,   164,   170,   171,   172,   217,   249,   224,
     224,   224,   461,   224,   224,   196,   454,   224,   305,   224,
     305,   224,   305,   224,   461,   224,   461,   323,   492,   216,
     551,   241,   393,   216,   492,   492,   243,   242,    43,   150,
     216,   217,   219,   222,   416,   315,   449,   242,   329,   360,
     216,    14,   393,   196,   315,   217,   219,   189,   464,   329,
     393,   245,   303,   315,   315,   283,   313,   369,   183,   242,
     347,   423,   366,   156,   157,   158,   316,   372,   393,   372,
     393,   372,   393,   372,   393,   372,   393,   372,   393,   372,
     393,   372,   393,   372,   393,   372,   393,   372,   393,   393,
     372,   393,   372,   393,   372,   393,   372,   393,   372,   393,
     372,   393,   196,   241,    57,    63,   398,    67,   399,   249,
     464,   464,   492,    70,   360,   509,   520,   223,   393,   196,
     393,   492,   537,   539,   541,   464,   551,   224,   461,   243,
     243,   464,   464,   243,   464,   243,   464,   551,   464,   411,
     551,   414,   224,   243,   243,   243,   243,   243,   243,    20,
     366,   242,   160,   416,   240,   386,   243,   165,   216,   249,
     514,   211,   212,   241,   518,   216,   211,   241,   249,   517,
      20,   243,   514,   207,   210,   516,    20,   393,   207,   531,
     323,   323,   393,   449,   449,    20,   242,   449,   386,   243,
     242,   242,   378,   380,    20,   531,   196,   243,   509,   507,
     216,   243,   216,   551,   243,   242,   150,   160,   196,   217,
     222,   363,   364,   304,   223,   242,   223,   242,   242,   242,
     241,    19,   181,   196,   450,   219,   181,   196,   386,   242,
     242,   181,   196,   386,     1,   242,   241,   243,   249,   393,
     393,   393,   393,   393,   393,   393,   393,   393,   393,   393,
     393,   393,   393,   393,   393,   393,   466,   471,   473,   492,
     475,   469,   216,   224,   249,   477,   224,   481,   224,   485,
     224,   489,   410,   491,   413,   224,   461,   243,   188,   455,
     386,   196,   196,   492,   393,    20,   449,   315,   217,   291,
     224,   365,    12,    23,    24,   188,   276,   277,   393,   318,
     303,   196,   346,   346,   366,   366,   366,   217,   249,    47,
     399,    46,   129,   396,   401,   224,   224,   224,   509,   243,
     243,   243,   196,   243,   224,   249,   243,   224,   464,   411,
     414,   224,   243,   242,   464,   224,   224,   224,   224,   243,
     224,   224,   243,   224,   365,   242,   360,   386,   393,   393,
     510,   514,   393,   181,   196,   507,   518,   241,   393,   241,
     530,   360,   510,   207,   210,   213,   519,   241,   360,   224,
     224,   219,   258,    20,    20,   360,   449,    20,   386,   386,
     464,   304,   360,   243,   241,   240,   364,   196,   196,   242,
     196,   196,   216,   241,   305,   387,   386,   389,   386,   243,
     360,   386,   223,   242,   386,   242,   241,   386,   240,   243,
     360,   242,   241,   384,   243,   360,   196,   460,   196,   479,
     483,   487,   321,   492,   243,    43,   416,   360,    20,   492,
     393,   365,   304,   315,   277,   393,    12,   279,   314,   365,
     216,   241,   243,   492,   401,    33,   397,   396,   398,   523,
     525,   334,   243,   224,   461,   242,   196,   358,   224,   224,
     224,   544,   322,   224,   351,   353,   355,   546,   529,   534,
     527,   242,   243,   360,   208,   243,   514,   518,   242,   160,
     416,   208,   514,   241,   208,   326,   328,   259,   204,   360,
     360,   208,    20,   360,   243,   243,   224,   305,   208,   243,
     507,   243,   196,   363,   241,   165,   315,   361,   464,   243,
     492,   243,   243,   243,   391,   386,   386,   243,   507,   243,
     386,   243,   196,   393,   315,   360,   249,   249,   368,   305,
     315,   280,   249,   304,   196,   241,   219,   421,   249,   405,
     397,   417,   418,   419,   242,   242,   393,   196,   393,   224,
     538,   540,   542,   242,   243,   242,   393,   393,   393,   242,
      70,   520,   242,   242,   243,   386,   243,   386,   160,   416,
     518,   386,   393,   393,   386,   519,   531,   393,   321,   257,
     243,   243,   386,   360,   208,   379,   224,   531,   241,   243,
     150,   393,   224,   224,   492,   243,   243,   241,   243,   243,
     361,   188,   277,    26,   128,   281,   336,   337,   338,   340,
     393,   305,   219,   421,   464,   420,   401,   310,   406,   520,
     520,   243,   224,   243,   242,   242,   242,   242,   320,   322,
     360,   520,   520,   243,   249,   550,   393,   393,   243,   550,
     550,   200,   208,   208,   550,   243,   386,   376,   381,   550,
     243,   393,   388,   390,   224,   243,   315,   277,   150,   150,
     393,   315,   464,   420,   420,   393,   249,   310,   242,   507,
     511,   512,   513,   513,   393,   393,   520,   520,   507,   508,
     243,   243,   551,   513,   508,    53,   241,   160,   416,   207,
     314,   531,   386,   241,   208,   550,   376,   314,   392,   393,
     420,   393,   393,   249,   401,   315,   507,   216,   551,   243,
     243,   243,   243,   513,   513,   243,   243,   243,   243,   393,
     241,   393,   393,   241,   314,   550,   550,   386,   241,   393,
     249,   249,   401,   243,   242,   243,   243,   207,   241,   550,
     249,   507,   241,   243
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   247,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,   248,   248,   248,   248,   248,   249,   249,   250,
     251,   251,   251,   252,   252,   253,   253,   254,   255,   255,
     255,   255,   256,   256,   257,   257,   258,   259,   258,   260,
     260,   260,   261,   262,   262,   264,   263,   265,   266,   267,
     267,   267,   268,   268,   268,   268,   268,   268,   268,   269,
     269,   270,   270,   271,   272,   272,   273,   273,   274,   275,
     275,   276,   276,   277,   277,   277,   277,   278,   278,   279,
     280,   279,   281,   281,   281,   281,   281,   282,   282,   283,
     282,   285,   284,   286,   284,   287,   288,   289,   291,   290,
     292,   290,   293,   293,   293,   293,   293,   293,   294,   294,
     295,   295,   295,   296,   296,   296,   296,   296,   296,   296,
     296,   296,   297,   297,   298,   298,   298,   299,   299,   299,
     299,   300,   300,   301,   301,   301,   301,   301,   301,   301,
     302,   302,   303,   303,   304,   304,   304,   305,   305,   305,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   306,   306,   306,   306,   306,   306,   306,   306,
     306,   306,   307,   307,   308,   309,   309,   309,   310,   312,
     311,   313,   313,   314,   314,   315,   315,   316,   316,   316,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   317,   317,   317,   317,   317,   317,   317,   317,
     317,   317,   318,   318,   318,   319,   320,   320,   321,   321,
     322,   322,   323,   323,   325,   326,   324,   327,   328,   324,
     329,   329,   329,   329,   329,   330,   330,   330,   331,   331,
     333,   334,   332,   332,   335,   335,   335,   335,   335,   335,
     336,   337,   338,   338,   338,   339,   339,   339,   340,   340,
     341,   341,   341,   342,   343,   343,   343,   344,   344,   345,
     345,   346,   346,   347,   347,   347,   347,   348,   348,   350,
     351,   349,   352,   353,   349,   354,   355,   349,   357,   358,
     356,   359,   359,   359,   359,   359,   359,   360,   360,   361,
     361,   361,   362,   362,   362,   363,   363,   363,   363,   363,
     364,   364,   365,   365,   365,   366,   366,   367,   369,   368,
     370,   370,   370,   370,   370,   370,   370,   371,   371,   371,
     371,   371,   371,   371,   371,   371,   371,   371,   371,   371,
     371,   371,   371,   371,   371,   371,   372,   372,   372,   372,
     373,   373,   373,   373,   373,   373,   373,   373,   373,   373,
     373,   373,   373,   373,   373,   373,   373,   374,   374,   375,
     375,   376,   376,   377,   378,   379,   377,   380,   381,   377,
     382,   382,   382,   382,   382,   382,   382,   383,   384,   382,
     385,   385,   385,   385,   385,   385,   385,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   386,   386,   387,   388,   386,   386,   386,   386,   389,
     390,   386,   386,   386,   391,   392,   386,   386,   386,   386,
     386,   386,   386,   386,   386,   386,   386,   386,   386,   386,
     386,   393,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   395,   395,
     395,   396,   396,   396,   397,   397,   398,   398,   398,   399,
     399,   400,   401,   401,   401,   401,   402,   403,   402,   404,
     402,   405,   402,   406,   402,   402,   407,   408,   408,   409,
     409,   409,   409,   409,   410,   410,   411,   411,   412,   412,
     412,   413,   414,   414,   415,   415,   415,   416,   416,   417,
     417,   417,   418,   418,   419,   419,   420,   420,   420,   421,
     421,   422,   422,   422,   422,   422,   423,   423,   423,   423,
     423,   423,   424,   425,   424,   426,   426,   427,   427,   427,
     428,   429,   428,   430,   430,   430,   431,   431,   431,   433,
     432,   434,   434,   435,   436,   435,   437,   437,   437,   438,
     439,   439,   440,   440,   441,   441,   442,   443,   443,   443,
     443,   444,   444,   444,   445,   445,   447,   448,   446,   449,
     449,   449,   449,   449,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   451,   451,   451,   451,   451,   451,
     451,   451,   452,   453,   453,   453,   454,   454,   454,   455,
     455,   456,   456,   456,   456,   456,   456,   456,   457,   457,
     457,   457,   457,   458,   459,   460,   458,   461,   461,   462,
     462,   463,   463,   464,   464,   464,   464,   464,   464,   465,
     466,   464,   464,   464,   467,   464,   464,   464,   464,   464,
     464,   464,   464,   464,   464,   464,   464,   464,   468,   469,
     464,   464,   470,   471,   464,   472,   473,   464,   474,   475,
     464,   464,   476,   477,   464,   478,   479,   464,   464,   480,
     481,   464,   482,   483,   464,   464,   484,   485,   464,   486,
     487,   464,   488,   489,   464,   490,   491,   464,   492,   492,
     492,   494,   495,   496,   497,   493,   499,   500,   501,   502,
     498,   504,   505,   503,   506,   506,   506,   506,   506,   507,
     507,   507,   507,   507,   507,   507,   507,   508,   508,   509,
     510,   510,   511,   511,   512,   512,   513,   513,   514,   514,
     515,   515,   516,   516,   517,   517,   518,   518,   518,   519,
     519,   519,   520,   520,   521,   521,   521,   521,   521,   521,
     522,   523,   521,   524,   525,   521,   526,   527,   521,   528,
     529,   521,   530,   530,   530,   531,   531,   532,   533,   534,
     532,   535,   535,   536,   536,   536,   537,   538,   536,   539,
     540,   536,   541,   542,   536,   536,   543,   544,   536,   536,
     545,   546,   536,   547,   547,   548,   548,   549,   549,   549,
     549,   549,   550,   550,   551,   551,   552,   552,   552,   552,
     552,   552,   552,   552,   552
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     1,     1,     2,
       0,     1,     1,     1,     1,     0,     2,     5,     1,     1,
       2,     2,     3,     2,     0,     2,     0,     0,     3,     0,
       2,     5,     3,     1,     2,     0,     4,     2,     2,     1,
       1,     1,     1,     2,     3,     3,     3,     3,     3,     2,
       4,     0,     1,     2,     1,     3,     1,     3,     3,     3,
       2,     1,     1,     0,     2,     4,     5,     1,     1,     0,
       0,     3,     1,     1,     1,     1,     1,     5,     4,     0,
       6,     0,     6,     0,     8,     2,     3,     3,     0,     6,
       0,     6,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     1,     3,     3,     5,     3,     3,     3,     3,
       1,     5,     1,     3,     2,     3,     2,     1,     1,     1,
       1,     1,     4,     1,     2,     3,     3,     3,     3,     2,
       1,     3,     0,     3,     0,     2,     3,     0,     2,     2,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     3,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,     2,
       2,     3,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,     2,     2,     2,     2,     2,
       3,     3,     3,     4,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     4,     0,     1,     1,     3,     0,
       4,     1,     1,     1,     1,     3,     7,     2,     2,     6,
       1,     1,     1,     1,     1,     2,     2,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     1,     1,     1,     2,
       2,     2,     0,     2,     2,     3,     0,     2,     0,     4,
       0,     2,     1,     3,     0,     0,     7,     0,     0,     7,
       3,     2,     2,     2,     1,     1,     3,     2,     2,     3,
       0,     0,     5,     1,     2,     5,     5,     5,     6,     2,
       1,     1,     1,     2,     3,     2,     2,     3,     2,     3,
       2,     2,     3,     4,     1,     1,     0,     1,     1,     1,
       0,     1,     3,     9,     8,     8,     7,     3,     3,     0,
       0,     7,     0,     0,     7,     0,     0,     7,     0,     0,
       6,     5,     8,    10,     5,     8,    10,     1,     3,     1,
       2,     3,     1,     1,     2,     2,     2,     2,     2,     4,
       1,     3,     0,     4,     4,     1,     6,     6,     0,     7,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     6,     8,     5,
       6,     1,     4,     3,     0,     0,     8,     0,     0,     9,
       3,     4,     5,     6,     8,     5,     6,     0,     0,     5,
       3,     4,     4,     5,     4,     3,     4,     1,     1,     1,
       2,     2,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     2,
       4,     5,     4,     5,     3,     4,     2,     5,     1,     1,
       1,     1,     1,     1,     1,     4,     1,     1,     4,     4,
       7,     8,     3,     0,     0,     8,     3,     3,     3,     0,
       0,     8,     3,     4,     0,     0,     9,     4,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     2,     4,
       1,     1,     4,     4,     4,     4,     4,     1,     6,     7,
       6,     6,     7,     7,     6,     7,     6,     6,     0,     4,
       1,     0,     1,     1,     0,     1,     0,     1,     1,     0,
       1,     5,     1,     1,     2,     0,     0,     0,     8,     0,
       5,     0,    10,     0,    11,     6,     3,     3,     4,     1,
       1,     3,     3,     3,     1,     3,     1,     3,     0,     2,
       3,     3,     1,     3,     0,     2,     3,     1,     1,     1,
       2,     3,     3,     5,     1,     1,     1,     1,     1,     0,
       1,     1,     4,     3,     3,     5,     4,     6,     5,     5,
       4,     4,     0,     0,     5,     0,     1,     0,     1,     1,
       6,     0,     6,     0,     3,     5,     0,     1,     1,     0,
       5,     2,     3,     4,     0,     4,     0,     1,     1,     1,
       7,     9,     0,     2,     0,     1,     3,     1,     1,     2,
       2,     0,     1,     1,     0,     3,     0,     0,     7,     1,
       4,     3,     3,     5,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     4,     1,     3,     3,     1,
       2,     0,     3,     3,     2,     5,     5,     4,     0,     2,
       2,     2,     2,     4,     0,     0,     7,     1,     1,     1,
       3,     3,     4,     1,     1,     1,     1,     2,     3,     0,
       0,     6,     4,     3,     0,     7,     4,     2,     2,     3,
       2,     3,     2,     2,     3,     3,     3,     2,     0,     0,
       6,     2,     0,     0,     6,     0,     0,     6,     0,     0,
       6,     1,     0,     0,     6,     0,     0,     7,     1,     0,
       0,     6,     0,     0,     7,     1,     0,     0,     6,     0,
       0,     7,     0,     0,     6,     0,     0,     6,     1,     3,
       3,     0,     0,     0,     0,    10,     0,     0,     0,     0,
      10,     0,     0,     9,     1,     1,     1,     1,     1,     3,
       3,     5,     5,     6,     6,     8,     8,     0,     1,     2,
       1,     3,     3,     5,     1,     2,     1,     0,     0,     2,
       2,     1,     2,     1,     2,     1,     2,     1,     1,     2,
       1,     1,     0,     1,     5,     4,     6,     7,     5,     7,
       0,     0,    10,     0,     0,    10,     0,     0,    10,     0,
       0,     7,     1,     3,     3,     3,     1,     5,     0,     0,
      10,     1,     3,     3,     4,     4,     0,     0,    11,     0,
       0,    11,     0,     0,    10,     5,     0,     0,     9,     5,
       0,     0,    10,     1,     3,     1,     3,     3,     3,     4,
       7,     9,     0,     3,     0,     1,     9,    11,    12,    11,
      10,    10,    10,     9,    10
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = DAS_YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == DAS_YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use DAS_YYerror or DAS_YYUNDEF. */
#define YYERRCODE DAS_YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if DAS_YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined DAS_YYLTYPE_IS_TRIVIAL && DAS_YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, yyscan_t scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, yyscan_t scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !DAS_YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !DAS_YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, yyscan_t scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yykind)
    {
    case YYSYMBOL_NAME: /* "name"  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_KEYWORD: /* "keyword"  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_TYPE_FUNCTION: /* "type function"  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_module_name: /* module_name  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_character_sequence: /* character_sequence  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_string_constant: /* string_constant  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_format_string: /* format_string  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_optional_format_string: /* optional_format_string  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_string_builder_body: /* string_builder_body  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_string_builder: /* string_builder  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_reader: /* expr_reader  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_keyword_or_name: /* keyword_or_name  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_require_module_name: /* require_module_name  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_expression_label: /* expression_label  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_goto: /* expression_goto  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_else: /* expression_else  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_else_one_liner: /* expression_else_one_liner  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_if_one_liner: /* expression_if_one_liner  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_if_then_else: /* expression_if_then_else  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_for_loop: /* expression_for_loop  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_unsafe: /* expression_unsafe  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_while_loop: /* expression_while_loop  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_with: /* expression_with  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_with_alias: /* expression_with_alias  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_annotation_argument_value: /* annotation_argument_value  */
            { delete ((*yyvaluep).aa); }
        break;

    case YYSYMBOL_annotation_argument_value_list: /* annotation_argument_value_list  */
            { delete ((*yyvaluep).aaList); }
        break;

    case YYSYMBOL_annotation_argument_name: /* annotation_argument_name  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_annotation_argument: /* annotation_argument  */
            { delete ((*yyvaluep).aa); }
        break;

    case YYSYMBOL_annotation_argument_list: /* annotation_argument_list  */
            { delete ((*yyvaluep).aaList); }
        break;

    case YYSYMBOL_metadata_argument_list: /* metadata_argument_list  */
            { delete ((*yyvaluep).aaList); }
        break;

    case YYSYMBOL_annotation_declaration_name: /* annotation_declaration_name  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_annotation_declaration_basic: /* annotation_declaration_basic  */
            { /* gc owns AnnotationDeclaration */ }
        break;

    case YYSYMBOL_annotation_declaration: /* annotation_declaration  */
            { /* gc owns AnnotationDeclaration */ }
        break;

    case YYSYMBOL_annotation_list: /* annotation_list  */
            { delete ((*yyvaluep).faList); }
        break;

    case YYSYMBOL_optional_annotation_list: /* optional_annotation_list  */
            { delete ((*yyvaluep).faList); }
        break;

    case YYSYMBOL_optional_function_argument_list: /* optional_function_argument_list  */
            { deleteVariableDeclarationList(((*yyvaluep).pVarDeclList)); }
        break;

    case YYSYMBOL_optional_function_type: /* optional_function_type  */
            { delete ((*yyvaluep).pTypeDecl); }
        break;

    case YYSYMBOL_function_name: /* function_name  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_function_declaration_header: /* function_declaration_header  */
            { ((*yyvaluep).pFuncDecl)->delRef(); }
        break;

    case YYSYMBOL_function_declaration: /* function_declaration  */
            { ((*yyvaluep).pFuncDecl)->delRef(); }
        break;

    case YYSYMBOL_expression_block: /* expression_block  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_call_pipe: /* expr_call_pipe  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_any: /* expression_any  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expressions: /* expressions  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_keyword: /* expr_keyword  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_optional_expr_list: /* optional_expr_list  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_optional_expr_list_in_braces: /* optional_expr_list_in_braces  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_optional_expr_map_tuple_list: /* optional_expr_map_tuple_list  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_type_declaration_no_options_list: /* type_declaration_no_options_list  */
            { deleteTypeDeclarationList(((*yyvaluep).pTypeDeclList)); }
        break;

    case YYSYMBOL_expression_keyword: /* expression_keyword  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_pipe: /* expr_pipe  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_name_in_namespace: /* name_in_namespace  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_expression_delete: /* expression_delete  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_new_type_declaration: /* new_type_declaration  */
            { delete ((*yyvaluep).pTypeDecl); }
        break;

    case YYSYMBOL_expr_new: /* expr_new  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_break: /* expression_break  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_continue: /* expression_continue  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_return_no_pipe: /* expression_return_no_pipe  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_return: /* expression_return  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_yield_no_pipe: /* expression_yield_no_pipe  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_yield: /* expression_yield  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expression_try_catch: /* expression_try_catch  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_tuple_expansion: /* tuple_expansion  */
            { delete ((*yyvaluep).pNameList); }
        break;

    case YYSYMBOL_tuple_expansion_variable_declaration: /* tuple_expansion_variable_declaration  */
            { delete ((*yyvaluep).pVarDecl); }
        break;

    case YYSYMBOL_expression_let: /* expression_let  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_cast: /* expr_cast  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_type_decl: /* expr_type_decl  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_type_info: /* expr_type_info  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_list: /* expr_list  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_block_or_simple_block: /* block_or_simple_block  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_capture_entry: /* capture_entry  */
            { delete ((*yyvaluep).pCapt); }
        break;

    case YYSYMBOL_capture_list: /* capture_list  */
            { delete ((*yyvaluep).pCaptList); }
        break;

    case YYSYMBOL_optional_capture_list: /* optional_capture_list  */
            { delete ((*yyvaluep).pCaptList); }
        break;

    case YYSYMBOL_expr_block: /* expr_block  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_full_block: /* expr_full_block  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_full_block_assumed_piped: /* expr_full_block_assumed_piped  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_numeric_const: /* expr_numeric_const  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_assign: /* expr_assign  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_assign_pipe_right: /* expr_assign_pipe_right  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_assign_pipe: /* expr_assign_pipe  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_named_call: /* expr_named_call  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_method_call: /* expr_method_call  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_func_addr_name: /* func_addr_name  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_func_addr_expr: /* func_addr_expr  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_field: /* expr_field  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_call: /* expr_call  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr2: /* expr2  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr: /* expr  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_mtag: /* expr_mtag  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_optional_field_annotation: /* optional_field_annotation  */
            { delete ((*yyvaluep).aaList); }
        break;

    case YYSYMBOL_structure_variable_declaration: /* structure_variable_declaration  */
            { delete ((*yyvaluep).pVarDecl); }
        break;

    case YYSYMBOL_struct_variable_declaration_list: /* struct_variable_declaration_list  */
            { deleteVariableDeclarationList(((*yyvaluep).pVarDeclList)); }
        break;

    case YYSYMBOL_function_argument_declaration_no_type: /* function_argument_declaration_no_type  */
            { delete ((*yyvaluep).pVarDecl); }
        break;

    case YYSYMBOL_function_argument_declaration_type: /* function_argument_declaration_type  */
            { delete ((*yyvaluep).pVarDecl); }
        break;

    case YYSYMBOL_function_argument_list: /* function_argument_list  */
            { deleteVariableDeclarationList(((*yyvaluep).pVarDeclList)); }
        break;

    case YYSYMBOL_tuple_type: /* tuple_type  */
            { delete ((*yyvaluep).pVarDecl); }
        break;

    case YYSYMBOL_tuple_type_list: /* tuple_type_list  */
            { deleteVariableDeclarationList(((*yyvaluep).pVarDeclList)); }
        break;

    case YYSYMBOL_tuple_alias_type_list: /* tuple_alias_type_list  */
            { deleteVariableDeclarationList(((*yyvaluep).pVarDeclList)); }
        break;

    case YYSYMBOL_variant_type: /* variant_type  */
            { delete ((*yyvaluep).pVarDecl); }
        break;

    case YYSYMBOL_variant_type_list: /* variant_type_list  */
            { deleteVariableDeclarationList(((*yyvaluep).pVarDeclList)); }
        break;

    case YYSYMBOL_variant_alias_type_list: /* variant_alias_type_list  */
            { deleteVariableDeclarationList(((*yyvaluep).pVarDeclList)); }
        break;

    case YYSYMBOL_variable_declaration_no_type: /* variable_declaration_no_type  */
            { delete ((*yyvaluep).pVarDecl); }
        break;

    case YYSYMBOL_variable_declaration_type: /* variable_declaration_type  */
            { delete ((*yyvaluep).pVarDecl); }
        break;

    case YYSYMBOL_variable_declaration: /* variable_declaration  */
            { delete ((*yyvaluep).pVarDecl); }
        break;

    case YYSYMBOL_let_variable_name_with_pos_list: /* let_variable_name_with_pos_list  */
            { delete ((*yyvaluep).pNameWithPosList); }
        break;

    case YYSYMBOL_let_variable_declaration: /* let_variable_declaration  */
            { delete ((*yyvaluep).pVarDecl); }
        break;

    case YYSYMBOL_global_variable_declaration_list: /* global_variable_declaration_list  */
            { deleteVariableDeclarationList(((*yyvaluep).pVarDeclList)); }
        break;

    case YYSYMBOL_enum_list: /* enum_list  */
            { delete ((*yyvaluep).pEnumList); }
        break;

    case YYSYMBOL_alias_list: /* alias_list  */
            { delete ((*yyvaluep).positions); }
        break;

    case YYSYMBOL_enum_name: /* enum_name  */
            { /* $$->delRef(); // if enum rule returns, module already has the link */ }
        break;

    case YYSYMBOL_optional_structure_parent: /* optional_structure_parent  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_optional_struct_variable_declaration_list: /* optional_struct_variable_declaration_list  */
            { deleteVariableDeclarationList(((*yyvaluep).pVarDeclList)); }
        break;

    case YYSYMBOL_variable_name_with_pos_list: /* variable_name_with_pos_list  */
            { delete ((*yyvaluep).pNameWithPosList); }
        break;

    case YYSYMBOL_structure_type_declaration: /* structure_type_declaration  */
            { delete ((*yyvaluep).pTypeDecl); }
        break;

    case YYSYMBOL_auto_type_declaration: /* auto_type_declaration  */
            { delete ((*yyvaluep).pTypeDecl); }
        break;

    case YYSYMBOL_bitfield_bits: /* bitfield_bits  */
            { delete ((*yyvaluep).pNameList); }
        break;

    case YYSYMBOL_bitfield_alias_bits: /* bitfield_alias_bits  */
            { deleteNameExprList(((*yyvaluep).pNameExprList)); }
        break;

    case YYSYMBOL_bitfield_type_declaration: /* bitfield_type_declaration  */
            { delete ((*yyvaluep).pTypeDecl); }
        break;

    case YYSYMBOL_table_type_pair: /* table_type_pair  */
            { delete ((*yyvaluep).aTypePair).firstType; delete ((*yyvaluep).aTypePair).secondType; }
        break;

    case YYSYMBOL_dim_list: /* dim_list  */
            { delete ((*yyvaluep).pTypeDecl); }
        break;

    case YYSYMBOL_type_declaration_no_options: /* type_declaration_no_options  */
            { delete ((*yyvaluep).pTypeDecl); }
        break;

    case YYSYMBOL_type_declaration: /* type_declaration  */
            { delete ((*yyvaluep).pTypeDecl); }
        break;

    case YYSYMBOL_make_decl: /* make_decl  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_make_struct_fields: /* make_struct_fields  */
            { /* gc owns MakeStruct */ }
        break;

    case YYSYMBOL_make_variant_dim: /* make_variant_dim  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_make_struct_single: /* make_struct_single  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_make_struct_dim: /* make_struct_dim  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_make_struct_dim_list: /* make_struct_dim_list  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_make_struct_dim_decl: /* make_struct_dim_decl  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_optional_make_struct_dim_decl: /* optional_make_struct_dim_decl  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_optional_block: /* optional_block  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_make_struct_decl: /* make_struct_decl  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_make_tuple: /* make_tuple  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_make_map_tuple: /* make_map_tuple  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_make_tuple_call: /* make_tuple_call  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_make_dim: /* make_dim  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_make_dim_decl: /* make_dim_decl  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_make_table: /* make_table  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_expr_map_tuple_list: /* expr_map_tuple_list  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_make_table_decl: /* make_table_decl  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_array_comprehension_where: /* array_comprehension_where  */
            { delete ((*yyvaluep).pExpression); }
        break;

    case YYSYMBOL_array_comprehension: /* array_comprehension  */
            { delete ((*yyvaluep).pExpression); }
        break;

      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (yyscan_t scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined DAS_YYLTYPE_IS_TRIVIAL && DAS_YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = DAS_YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == DAS_YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= DAS_YYEOF)
    {
      yychar = DAS_YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == DAS_YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = DAS_YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = DAS_YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 3: /* program: program module_declaration  */
                                   {
            if ( yyextra->das_has_type_declarations ) {
                das_yyerror(scanner,"module name has to be first declaration",tokAt(scanner,(yylsp[0])), CompilationError::syntax_error);
            }
        }
    break;

  case 4: /* program: program structure_declaration  */
                                                { yyextra->das_has_type_declarations = true; }
    break;

  case 5: /* program: program enum_declaration  */
                                                { yyextra->das_has_type_declarations = true; }
    break;

  case 6: /* program: program global_let  */
                                                { yyextra->das_has_type_declarations = true; }
    break;

  case 7: /* program: program global_function_declaration  */
                                                { yyextra->das_has_type_declarations = true; }
    break;

  case 11: /* program: program alias_declaration  */
                                                { yyextra->das_has_type_declarations = true; }
    break;

  case 12: /* program: program variant_alias_declaration  */
                                                { yyextra->das_has_type_declarations = true; }
    break;

  case 13: /* program: program tuple_alias_declaration  */
                                                { yyextra->das_has_type_declarations = true; }
    break;

  case 14: /* program: program bitfield_alias_declaration  */
                                                { yyextra->das_has_type_declarations = true; }
    break;

  case 17: /* semicolon: SEMICOLON  */
                       {
        format::try_semicolon_at_eol(format::Pos::from_last(tokAt(scanner,(yylsp[0]))));
    }
    break;

  case 18: /* semicolon: "end of expression"  */
          {}
    break;

  case 19: /* top_level_reader_macro: expr_reader semicolon  */
                                   {
        delete (yyvsp[-1].pExpression);    // we do nothing, we don't even attemp to 'visit'
    }
    break;

  case 20: /* optional_public_or_private_module: %empty  */
                        { (yyval.b) = yyextra->g_Program->policies.default_module_public; }
    break;

  case 21: /* optional_public_or_private_module: "public"  */
                        { (yyval.b) = true; }
    break;

  case 22: /* optional_public_or_private_module: "private"  */
                        { (yyval.b) = false; }
    break;

  case 23: /* module_name: '$'  */
                    { (yyval.s) = new string("$"); }
    break;

  case 24: /* module_name: "name"  */
                    { (yyval.s) = (yyvsp[0].s); }
    break;

  case 25: /* optional_not_required: %empty  */
        { (yyval.b) = false; }
    break;

  case 26: /* optional_not_required: '!' "inscope"  */
                        { (yyval.b) = true; }
    break;

  case 27: /* module_declaration: "module" module_name optional_shared optional_public_or_private_module optional_not_required  */
                                                                                                                                    {
        yyextra->g_Program->thisModuleName = *(yyvsp[-3].s);
        yyextra->g_Program->thisModule->isPublic = (yyvsp[-1].b);
        yyextra->g_Program->thisModule->isModule = true;
        yyextra->g_Program->thisModule->visibleEverywhere = (yyvsp[0].b);
        if ( yyextra->g_Program->thisModule->name.empty() ) {
            yyextra->g_Program->library.renameModule(yyextra->g_Program->thisModule.get(),*(yyvsp[-3].s));
        } else if ( yyextra->g_Program->thisModule->name != *(yyvsp[-3].s) ){
            das_yyerror(scanner,"this module already has a name " + yyextra->g_Program->thisModule->name,tokAt(scanner,(yylsp[-3])),
                CompilationError::module_already_has_a_name);
        }
        if ( !yyextra->g_Program->policies.ignore_shared_modules ) {
            yyextra->g_Program->promoteToBuiltin = (yyvsp[-2].b);
        }
        delete (yyvsp[-3].s);
    }
    break;

  case 28: /* character_sequence: STRING_CHARACTER  */
                                                                                  { (yyval.s) = new string(); *(yyval.s) += (yyvsp[0].ch); }
    break;

  case 29: /* character_sequence: STRING_CHARACTER_ESC  */
                                                                                  { (yyval.s) = new string(); *(yyval.s) += "\\\\"; }
    break;

  case 30: /* character_sequence: character_sequence STRING_CHARACTER  */
                                                                                  { (yyval.s) = (yyvsp[-1].s); *(yyvsp[-1].s) += (yyvsp[0].ch); }
    break;

  case 31: /* character_sequence: character_sequence STRING_CHARACTER_ESC  */
                                                                                  { (yyval.s) = (yyvsp[-1].s); *(yyvsp[-1].s) += "\\\\"; }
    break;

  case 32: /* string_constant: "start of the string" character_sequence "end of the string"  */
                                                           { (yyval.s) = (yyvsp[-1].s); }
    break;

  case 33: /* string_constant: "start of the string" "end of the string"  */
                                                           { (yyval.s) = new string(); }
    break;

  case 34: /* format_string: %empty  */
        { (yyval.s) = new string(); }
    break;

  case 35: /* format_string: format_string STRING_CHARACTER  */
                                                 { (yyval.s) = (yyvsp[-1].s); (yyvsp[-1].s)->push_back((yyvsp[0].ch)); }
    break;

  case 36: /* optional_format_string: %empty  */
        { (yyval.s) = new string(""); }
    break;

  case 37: /* $@1: %empty  */
            { das_strfmt(scanner); }
    break;

  case 38: /* optional_format_string: ':' $@1 format_string  */
                                                        { (yyval.s) = (yyvsp[0].s); }
    break;

  case 39: /* string_builder_body: %empty  */
        {
        (yyval.pExpression) = new ExprStringBuilder();
        (yyval.pExpression)->at = LineInfo(yyextra->g_FileAccessStack.back(),
            yylloc.first_column,yylloc.first_line,yylloc.last_column,yylloc.last_line);
    }
    break;

  case 40: /* string_builder_body: string_builder_body character_sequence  */
                                                                                  {
        bool err;
        auto esconst = unescapeString(*(yyvsp[0].s),&err);
        if ( err ) das_yyerror(scanner,"invalid escape sequence",tokAt(scanner,(yylsp[-1])), CompilationError::invalid_escape_sequence);
        auto sc = new ExprConstString(tokAt(scanner,(yylsp[0])),esconst);
        delete (yyvsp[0].s);
        static_cast<ExprStringBuilder *>((yyvsp[-1].pExpression))->elements.push_back(sc);
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 41: /* string_builder_body: string_builder_body "{" expr optional_format_string "}"  */
                                                                                                                                     {
        auto se = (yyvsp[-2].pExpression);
        if ( !(yyvsp[-1].s)->empty() ) {
            auto call_fmt = new ExprCall(tokAt(scanner,(yylsp[-1])), "_::fmt");
            call_fmt->arguments.push_back(new ExprConstString(tokAt(scanner,(yylsp[-1])),":" + *(yyvsp[-1].s)));
            call_fmt->arguments.push_back(se);
            se = call_fmt;
        }
        static_cast<ExprStringBuilder *>((yyvsp[-4].pExpression))->elements.push_back(se);
        (yyval.pExpression) = (yyvsp[-4].pExpression);
        delete (yyvsp[-1].s);
    }
    break;

  case 42: /* string_builder: "start of the string" string_builder_body "end of the string"  */
                                                                   {
        auto strb = static_cast<ExprStringBuilder *>((yyvsp[-1].pExpression));
        if ( strb->elements.size()==0 ) {
            (yyval.pExpression) = new ExprConstString(tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),"");
            delete (yyvsp[-1].pExpression);
        } else if ( strb->elements.size()==1 && strb->elements[0]->rtti_isStringConstant() ) {
            auto sconst = static_cast<ExprConstString*>(strb->elements[0]);
            (yyval.pExpression) = new ExprConstString(tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),sconst->text);
            delete (yyvsp[-1].pExpression);
        } else {
            (yyval.pExpression) = (yyvsp[-1].pExpression);
        }
    }
    break;

  case 43: /* reader_character_sequence: STRING_CHARACTER  */
                               {
        if ( !yyextra->g_ReaderMacro->accept(yyextra->g_Program.get(), yyextra->g_Program->thisModule.get(), yyextra->g_ReaderExpr, (yyvsp[0].ch), tokAt(scanner,(yylsp[0]))) ) {
            das_yyend_reader(scanner);
        }
    }
    break;

  case 44: /* reader_character_sequence: reader_character_sequence STRING_CHARACTER  */
                                                                {
        if ( !yyextra->g_ReaderMacro->accept(yyextra->g_Program.get(), yyextra->g_Program->thisModule.get(), yyextra->g_ReaderExpr, (yyvsp[0].ch), tokAt(scanner,(yylsp[0]))) ) {
            das_yyend_reader(scanner);
        }
    }
    break;

  case 45: /* $@2: %empty  */
                                        {
        auto macros = yyextra->g_Program->getReaderMacro(*(yyvsp[0].s));
        if ( macros.size()==0 ) {
            das_yyerror(scanner,"reader macro " + *(yyvsp[0].s) + " not found",tokAt(scanner,(yylsp[0])),
                CompilationError::unsupported_read_macro);
        } else if ( macros.size()>1 ) {
            string options;
            for ( auto & x : macros ) {
                options += "\t" + x->module->name + "::" + x->name + "\n";
            }
            das_yyerror(scanner,"too many options for the reader macro " + *(yyvsp[0].s) +  "\n" + options, tokAt(scanner,(yylsp[0])),
                CompilationError::unsupported_read_macro);
        } else if ( yychar != '~' ) {
            das_yyerror(scanner,"expecting ~ after the reader macro", tokAt(scanner,(yylsp[0])),
                CompilationError::syntax_error);
        } else {
            yyextra->g_ReaderMacro = macros.back();
            yyextra->g_ReaderExpr = new ExprReader(tokAt(scanner,(yylsp[-1])),yyextra->g_ReaderMacro);
            yyclearin ;
            das_yybegin_reader(scanner);
        }
    }
    break;

  case 46: /* expr_reader: '%' name_in_namespace $@2 reader_character_sequence  */
                                     {
        yyextra->g_ReaderExpr->at = tokRangeAt(scanner,(yylsp[-3]),(yylsp[0]));
        (yyval.pExpression) = yyextra->g_ReaderExpr;
        int thisLine = 0;
        FileInfo * info = nullptr;
        if (!format::is_formatter_enabled()) {
        if ( auto seqt = yyextra->g_ReaderMacro->suffix(yyextra->g_Program.get(), yyextra->g_Program->thisModule.get(), yyextra->g_ReaderExpr, thisLine, info, tokAt(scanner,(yylsp[0]))) ) {
            das_accept_sequence(scanner,seqt,strlen(seqt),thisLine,info);
            yylloc.first_column = (yylsp[0]).first_column;
            yylloc.first_line = (yylsp[0]).first_line;
            yylloc.last_column = (yylsp[0]).last_column;
            yylloc.last_line = (yylsp[0]).last_line;
        }
        }
        delete (yyvsp[-2].s);
        yyextra->g_ReaderMacro = nullptr;
        yyextra->g_ReaderExpr = nullptr;
    }
    break;

  case 47: /* options_declaration: "options" annotation_argument_list  */
                                                   {
        for ( auto & opt : *(yyvsp[0].aaList) ) {
            if ( opt.name=="indenting" && opt.type==Type::tInt ) {
                if (opt.iValue != 0 && opt.iValue != 2 && opt.iValue != 4 && opt.iValue != 8) { //this is error
                    yyextra->das_tab_size = yyextra->das_def_tab_size;
                } else {
                    yyextra->das_tab_size = opt.iValue ? opt.iValue : yyextra->das_def_tab_size;//0 is default
                }
                yyextra->g_FileAccessStack.back()->tabSize = yyextra->das_tab_size;
            } else if ( opt.name=="gen2_make_syntax" && opt.type==Type::tBool ) {
                yyextra->das_gen2_make_syntax = opt.bValue;
            }
        }
        for ( auto & opt : *(yyvsp[0].aaList) ) {
            if ( yyextra->g_Access->isOptionAllowed(opt.name, yyextra->g_Program->thisModule->fileName) ) {
                if ( yyextra->g_Access->isOptionBlocked(opt.name, yyextra->g_Program->thisModule->fileName) ) {
                    // blocked: ok to write, silently ignored (not applied)
                } else {
                    yyextra->g_Program->options.push_back(opt);
                }
            } else {
                das_yyerror(scanner,"option " + opt.name + " is not allowed here",
                    tokAt(scanner,(yylsp[0])), CompilationError::invalid_option);
            }
        }
        delete (yyvsp[0].aaList);
    }
    break;

  case 49: /* keyword_or_name: "name"  */
                            { (yyval.s) = (yyvsp[0].s); }
    break;

  case 50: /* keyword_or_name: "keyword"  */
                            { (yyval.s) = (yyvsp[0].s); }
    break;

  case 51: /* keyword_or_name: "type function"  */
                            { (yyval.s) = (yyvsp[0].s); }
    break;

  case 52: /* require_module_name: keyword_or_name  */
                              {
        (yyval.s) = (yyvsp[0].s);
    }
    break;

  case 53: /* require_module_name: '%' require_module_name  */
                                     {
        *(yyvsp[0].s) = "%" + *(yyvsp[0].s);
        (yyval.s) = (yyvsp[0].s);
    }
    break;

  case 54: /* require_module_name: '.' '/' require_module_name  */
                                         {
        *(yyvsp[0].s) = "./" + *(yyvsp[0].s);
        (yyval.s) = (yyvsp[0].s);
    }
    break;

  case 55: /* require_module_name: ".." '/' require_module_name  */
                                            {
        *(yyvsp[0].s) = "../" + *(yyvsp[0].s);
        (yyval.s) = (yyvsp[0].s);
    }
    break;

  case 56: /* require_module_name: '%' '/' require_module_name  */
                                         {
        *(yyvsp[0].s) = "%/" + *(yyvsp[0].s);
        (yyval.s) = (yyvsp[0].s);
    }
    break;

  case 57: /* require_module_name: require_module_name '.' keyword_or_name  */
                                                           {
        *(yyvsp[-2].s) += ".";
        *(yyvsp[-2].s) += *(yyvsp[0].s);
        delete (yyvsp[0].s);
        (yyval.s) = (yyvsp[-2].s);
    }
    break;

  case 58: /* require_module_name: require_module_name '/' keyword_or_name  */
                                                           {
        *(yyvsp[-2].s) += "/";
        *(yyvsp[-2].s) += *(yyvsp[0].s);
        delete (yyvsp[0].s);
        (yyval.s) = (yyvsp[-2].s);
    }
    break;

  case 59: /* require_module: require_module_name is_public_module  */
                                                         {
        ast_requireModule(scanner,(yyvsp[-1].s),nullptr,(yyvsp[0].b),tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 60: /* require_module: require_module_name "as" "name" is_public_module  */
                                                                              {
        ast_requireModule(scanner,(yyvsp[-3].s),(yyvsp[-1].s),(yyvsp[0].b),tokAt(scanner,(yylsp[-3])));
    }
    break;

  case 61: /* is_public_module: %empty  */
                    { (yyval.b) = false; }
    break;

  case 62: /* is_public_module: "public"  */
                    { (yyval.b) = true; }
    break;

  case 66: /* expect_error: "integer constant"  */
                   {
        yyextra->g_Program->expectErrors[CompilationError((yyvsp[0].i))] ++;
    }
    break;

  case 67: /* expect_error: "integer constant" ':' "integer constant"  */
                                      {
        yyextra->g_Program->expectErrors[CompilationError((yyvsp[-2].i))] += (yyvsp[0].i);
    }
    break;

  case 68: /* expression_label: "label" "integer constant" ':'  */
                                          {
        (yyval.pExpression) = new ExprLabel(tokAt(scanner,(yylsp[-2])),(yyvsp[-1].i));
    }
    break;

  case 69: /* expression_goto: "goto" "label" "integer constant"  */
                                                {
        (yyval.pExpression) = new ExprGoto(tokAt(scanner,(yylsp[-2])),(yyvsp[0].i));
    }
    break;

  case 70: /* expression_goto: "goto" expr  */
                               {
        (yyval.pExpression) = new ExprGoto(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression));
    }
    break;

  case 71: /* elif_or_static_elif: "elif"  */
                          { (yyval.b) = false; }
    break;

  case 72: /* elif_or_static_elif: "static_elif"  */
                          { (yyval.b) = true; }
    break;

  case 73: /* expression_else: %empty  */
                                                           { (yyval.pExpression) = nullptr; }
    break;

  case 74: /* expression_else: "else" expression_block  */
                                                           { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 75: /* expression_else: elif_or_static_elif expr expression_block expression_else  */
                                                                                          {
        format::wrap_par_expr(tokAt(scanner,(yylsp[-2])), (yyvsp[-2].pExpression)->at);
        if (!format::is_else_newline() && (yyvsp[0].pExpression) != nullptr) {
            format::skip_spaces_or_print(tokAt(scanner,(yylsp[-3])), tokAt(scanner,(yylsp[-1])), tokAt(scanner,(yylsp[0])), yyextra->das_tab_size);
        }

        auto eite = new ExprIfThenElse(tokAt(scanner,(yylsp[-3])),(yyvsp[-2].pExpression),(yyvsp[-1].pExpression),(yyvsp[0].pExpression));
        eite->isStatic = (yyvsp[-3].b);
        (yyval.pExpression) = eite;
    }
    break;

  case 76: /* expression_else: elif_or_static_elif expr expression_block SEMICOLON expression_else  */
                                                                                                    {
        format::wrap_par_expr(tokAt(scanner,(yylsp[-3])), (yyvsp[-3].pExpression)->at);
        if (!format::is_else_newline() && (yyvsp[0].pExpression) != nullptr) {
            format::skip_spaces_or_print(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-2])), tokAt(scanner,(yylsp[0])), yyextra->das_tab_size);
        }

        auto eite = new ExprIfThenElse(tokAt(scanner,(yylsp[-4])),(yyvsp[-3].pExpression),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
        eite->isStatic = (yyvsp[-4].b);
        (yyval.pExpression) = eite;
    }
    break;

  case 77: /* if_or_static_if: "if"  */
                        { (yyval.b) = false; }
    break;

  case 78: /* if_or_static_if: "static_if"  */
                        { (yyval.b) = true; }
    break;

  case 79: /* expression_else_one_liner: %empty  */
        { (yyval.pExpression) = nullptr; }
    break;

  case 80: /* $@3: %empty  */
                      { yyextra->das_need_oxford_comma = true; }
    break;

  case 81: /* expression_else_one_liner: "else" $@3 expression_if_one_liner  */
                                                                                                 {
            (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 82: /* expression_if_one_liner: expr  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 83: /* expression_if_one_liner: expression_return_no_pipe  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 84: /* expression_if_one_liner: expression_yield_no_pipe  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 85: /* expression_if_one_liner: expression_break  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 86: /* expression_if_one_liner: expression_continue  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 87: /* expression_if_then_else: if_or_static_if expr expression_block SEMICOLON expression_else  */
                                                                                                {
        format::wrap_par_expr(tokAt(scanner,(yylsp[-3])), (yyvsp[-3].pExpression)->at);
        if (!format::is_else_newline() && (yyvsp[0].pExpression) != nullptr) {
            format::skip_spaces_or_print(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-2])), tokAt(scanner,(yylsp[0])), yyextra->das_tab_size);
        }

        auto eite = new ExprIfThenElse(tokAt(scanner,(yylsp[-4])),(yyvsp[-3].pExpression),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
        eite->isStatic = (yyvsp[-4].b);
        (yyval.pExpression) = eite;
    }
    break;

  case 88: /* expression_if_then_else: if_or_static_if expr expression_block expression_else  */
                                                                                      {
        format::wrap_par_expr(tokAt(scanner,(yylsp[-2])), (yyvsp[-2].pExpression)->at);
        if (!format::is_else_newline() && (yyvsp[0].pExpression) != nullptr) {
            format::skip_spaces_or_print(tokAt(scanner,(yylsp[-3])), tokAt(scanner,(yylsp[-1])), tokAt(scanner,(yylsp[0])), yyextra->das_tab_size);
        }

        auto eite = new ExprIfThenElse(tokAt(scanner,(yylsp[-3])),(yyvsp[-2].pExpression),(yyvsp[-1].pExpression),(yyvsp[0].pExpression));
        eite->isStatic = (yyvsp[-3].b);
        (yyval.pExpression) = eite;
    }
    break;

  case 89: /* $@4: %empty  */
                                                     { yyextra->das_need_oxford_comma = true; }
    break;

  case 90: /* expression_if_then_else: expression_if_one_liner "if" $@4 expr expression_else_one_liner semicolon  */
                                                                                                                                                         {
        format::wrap_par_expr(tokAt(scanner,(yylsp[-2])), (yyvsp[-2].pExpression)->at);

        (yyval.pExpression) = new ExprIfThenElse(tokAt(scanner,(yylsp[-4])),(yyvsp[-2].pExpression),ast_wrapInBlock((yyvsp[-5].pExpression)),(yyvsp[-1].pExpression) ? ast_wrapInBlock((yyvsp[-1].pExpression)) : nullptr);
    }
    break;

  case 91: /* $@5: %empty  */
                     { yyextra->das_need_oxford_comma=false; }
    break;

  case 92: /* expression_for_loop: "for" $@5 variable_name_with_pos_list "in" expr_list expression_block  */
                                                                                                                                                 {
        format::wrap_par_expr(tokRangeAt(scanner, (yylsp[-3]), (yylsp[-1])), tokRangeAt(scanner, (yylsp[-3]), (yylsp[-1])));
        (yyval.pExpression) = ast_forLoop(scanner,(yyvsp[-3].pNameWithPosList),(yyvsp[-1].pExpression),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[-5])),tokAt(scanner,(yylsp[0])));
    }
    break;

  case 93: /* $@6: %empty  */
                     { // Had to add to successfully convert to v2 syntax, just copied from ds2_parser
                             yyextra->das_keyword = true;
     }
    break;

  case 94: /* expression_for_loop: "for" $@6 '(' variable_name_with_pos_list "in" expr_list ')' expression_block  */
                                                                                                  {
        yyextra->das_keyword = false;
        (yyval.pExpression) = ast_forLoop(scanner,(yyvsp[-4].pNameWithPosList),(yyvsp[-2].pExpression),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[-7])),tokAt(scanner,(yylsp[0])));
    }
    break;

  case 95: /* expression_unsafe: "unsafe" expression_block  */
                                                 {
        auto pUnsafe = new ExprUnsafe(tokAt(scanner,(yylsp[-1])));
        pUnsafe->body = (yyvsp[0].pExpression);
        (yyval.pExpression) = pUnsafe;
    }
    break;

  case 96: /* expression_while_loop: "while" expr expression_block  */
                                                               {
        format::wrap_par_expr(tokAt(scanner,(yylsp[-1])), (yyvsp[-1].pExpression)->at);

        auto pWhile = new ExprWhile(tokAt(scanner,(yylsp[-2])));
        pWhile->cond = (yyvsp[-1].pExpression);
        pWhile->body = (yyvsp[0].pExpression);
        ((ExprBlock *)(yyvsp[0].pExpression))->inTheLoop = true;
        (yyval.pExpression) = pWhile;
    }
    break;

  case 97: /* expression_with: "with" expr expression_block  */
                                                         {
        format::wrap_par_expr(tokAt(scanner,(yylsp[-1])), (yyvsp[-1].pExpression)->at);
        auto pWith = new ExprWith(tokAt(scanner,(yylsp[-2])));
        pWith->with = (yyvsp[-1].pExpression);
        pWith->body = (yyvsp[0].pExpression);
        (yyval.pExpression) = pWith;
    }
    break;

  case 98: /* $@7: %empty  */
                                        { yyextra->das_need_oxford_comma=true; }
    break;

  case 99: /* expression_with_alias: "assume" "name" '=' $@7 expr semicolon  */
                                                                                                         {
        (yyval.pExpression) = new ExprAssume(tokAt(scanner,(yylsp[-5])), *(yyvsp[-4].s), ExpressionPtr((yyvsp[-1].pExpression)));
        delete (yyvsp[-4].s);
    }
    break;

  case 100: /* $@8: %empty  */
                         { yyextra->das_force_oxford_comma=true;}
    break;

  case 101: /* expression_with_alias: "typedef" $@8 "name" '=' type_declaration semicolon  */
                                                                                                                   {
        (yyval.pExpression) = new ExprAssume(tokAt(scanner,(yylsp[-5])), *(yyvsp[-3].s), TypeDeclPtr((yyvsp[-1].pTypeDecl)));
    }
    break;

  case 102: /* annotation_argument_value: string_constant  */
                                 { (yyval.aa) = new AnnotationArgument("",*(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 103: /* annotation_argument_value: "name"  */
                                 { (yyval.aa) = new AnnotationArgument("",*(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 104: /* annotation_argument_value: "integer constant"  */
                                 { (yyval.aa) = new AnnotationArgument("",(yyvsp[0].i)); }
    break;

  case 105: /* annotation_argument_value: "floating point constant"  */
                                 { (yyval.aa) = new AnnotationArgument("",float((yyvsp[0].fd))); }
    break;

  case 106: /* annotation_argument_value: "true"  */
                                 { (yyval.aa) = new AnnotationArgument("",true); }
    break;

  case 107: /* annotation_argument_value: "false"  */
                                 { (yyval.aa) = new AnnotationArgument("",false); }
    break;

  case 108: /* annotation_argument_value_list: annotation_argument_value  */
                                       {
        (yyval.aaList) = new AnnotationArgumentList();
        (yyval.aaList)->push_back(*(yyvsp[0].aa));
        delete (yyvsp[0].aa);
    }
    break;

  case 109: /* annotation_argument_value_list: annotation_argument_value_list ',' annotation_argument_value  */
                                                                                {
            (yyval.aaList) = (yyvsp[-2].aaList);
            (yyval.aaList)->push_back(*(yyvsp[0].aa));
            delete (yyvsp[0].aa);
    }
    break;

  case 110: /* annotation_argument_name: "name"  */
                    { (yyval.s) = (yyvsp[0].s); }
    break;

  case 111: /* annotation_argument_name: "type"  */
                    { (yyval.s) = new string("type"); }
    break;

  case 112: /* annotation_argument_name: "in"  */
                    { (yyval.s) = new string("in"); }
    break;

  case 113: /* annotation_argument: annotation_argument_name '=' string_constant  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),*(yyvsp[0].s),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0]))); delete (yyvsp[0].s); delete (yyvsp[-2].s); }
    break;

  case 114: /* annotation_argument: annotation_argument_name '=' "name"  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),*(yyvsp[0].s),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0]))); delete (yyvsp[0].s); delete (yyvsp[-2].s); }
    break;

  case 115: /* annotation_argument: annotation_argument_name '=' '@' '@' "name"  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-4].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-4]))); delete (yyvsp[0].s); delete (yyvsp[-4].s); }
    break;

  case 116: /* annotation_argument: annotation_argument_name '=' "integer constant"  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),(yyvsp[0].i),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0]))); delete (yyvsp[-2].s); }
    break;

  case 117: /* annotation_argument: annotation_argument_name '=' "floating point constant"  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),float((yyvsp[0].fd)),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0]))); delete (yyvsp[-2].s); }
    break;

  case 118: /* annotation_argument: annotation_argument_name '=' "true"  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),true,tokRangeAt(scanner,(yylsp[-2]),(yylsp[0]))); delete (yyvsp[-2].s); }
    break;

  case 119: /* annotation_argument: annotation_argument_name '=' "false"  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),false,tokRangeAt(scanner,(yylsp[-2]),(yylsp[0]))); delete (yyvsp[-2].s); }
    break;

  case 120: /* annotation_argument: annotation_argument_name  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[0].s),true,tokAt(scanner,(yylsp[0]))); delete (yyvsp[0].s); }
    break;

  case 121: /* annotation_argument: annotation_argument_name '=' '(' annotation_argument_value_list ')'  */
                                                                                               {
        { (yyval.aa) = new AnnotationArgument(*(yyvsp[-4].s),(yyvsp[-1].aaList),tokRangeAt(scanner,(yylsp[-4]),(yylsp[0]))); delete (yyvsp[-4].s); }
    }
    break;

  case 122: /* annotation_argument_list: annotation_argument  */
                                  {
        (yyval.aaList) = ast_annotationArgumentListEntry(scanner,new AnnotationArgumentList(),(yyvsp[0].aa));
    }
    break;

  case 123: /* annotation_argument_list: annotation_argument_list ',' annotation_argument  */
                                                                    {
        (yyval.aaList) = ast_annotationArgumentListEntry(scanner,(yyvsp[-2].aaList),(yyvsp[0].aa));
    }
    break;

  case 124: /* metadata_argument_list: '@' annotation_argument  */
                                      {
        (yyval.aaList) = ast_annotationArgumentListEntry(scanner,new AnnotationArgumentList(),(yyvsp[0].aa));
    }
    break;

  case 125: /* metadata_argument_list: metadata_argument_list '@' annotation_argument  */
                                                                  {
        (yyval.aaList) = ast_annotationArgumentListEntry(scanner,(yyvsp[-2].aaList),(yyvsp[0].aa));
    }
    break;

  case 126: /* metadata_argument_list: metadata_argument_list semicolon  */
                                               {
        (yyval.aaList) = (yyvsp[-1].aaList);
    }
    break;

  case 127: /* annotation_declaration_name: name_in_namespace  */
                                    { (yyval.s) = (yyvsp[0].s); }
    break;

  case 128: /* annotation_declaration_name: "require"  */
                                    { (yyval.s) = new string("require"); }
    break;

  case 129: /* annotation_declaration_name: "private"  */
                                    { (yyval.s) = new string("private"); }
    break;

  case 130: /* annotation_declaration_name: "template"  */
                                    { (yyval.s) = new string("template"); }
    break;

  case 131: /* annotation_declaration_basic: annotation_declaration_name  */
                                          {
        (yyval.fa) = new AnnotationDeclaration();
        (yyval.fa)->at = tokAt(scanner,(yylsp[0]));
        if ( yyextra->g_Access->isAnnotationAllowed(*(yyvsp[0].s), yyextra->g_Program->thisModuleName) ) {
            if ( auto ann = findAnnotation(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0]))) ) {
                (yyval.fa)->annotation = ann;
            }
        } else {
            das_yyerror(scanner,"annotation " + *(yyvsp[0].s) + " is not allowed here",
                        tokAt(scanner,(yylsp[0])), CompilationError::invalid_annotation);
        }
        delete (yyvsp[0].s);
    }
    break;

  case 132: /* annotation_declaration_basic: annotation_declaration_name '(' annotation_argument_list ')'  */
                                                                                 {
        (yyval.fa) = new AnnotationDeclaration();
        (yyval.fa)->at = tokAt(scanner,(yylsp[-3]));
        if ( yyextra->g_Access->isAnnotationAllowed(*(yyvsp[-3].s), yyextra->g_Program->thisModuleName) ) {
            if ( auto ann = findAnnotation(scanner,*(yyvsp[-3].s),tokAt(scanner,(yylsp[-3]))) ) {
                (yyval.fa)->annotation = ann;
            }
        } else {
            das_yyerror(scanner,"annotation " + *(yyvsp[-3].s) + " is not allowed here",
                        tokAt(scanner,(yylsp[-3])), CompilationError::invalid_annotation);
        }
        swap ( (yyval.fa)->arguments, *(yyvsp[-1].aaList) );
        delete (yyvsp[-1].aaList);
        delete (yyvsp[-3].s);
    }
    break;

  case 133: /* annotation_declaration: annotation_declaration_basic  */
                                          {
        (yyval.fa) = (yyvsp[0].fa);
    }
    break;

  case 134: /* annotation_declaration: '!' annotation_declaration  */
                                              {
        if ( !(yyvsp[0].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[0].fa)->annotation))->isSpecialized() ) {
            das_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[0])),
                CompilationError::invalid_annotation); }
        (yyval.fa) = new AnnotationDeclaration();
        (yyval.fa)->at = tokAt(scanner, (yylsp[-1]));
        (yyval.fa)->annotation = newLogicAnnotation(LogicAnnotationOp::Not,(yyvsp[0].fa),nullptr);
    }
    break;

  case 135: /* annotation_declaration: annotation_declaration "&&" annotation_declaration  */
                                                                              {
        if ( !(yyvsp[-2].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[-2].fa)->annotation))->isSpecialized() ) {
            das_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[-2])),
                CompilationError::invalid_annotation); }
        if ( !(yyvsp[0].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[0].fa)->annotation))->isSpecialized() ) {
            das_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[0])),
                CompilationError::invalid_annotation); }
        (yyval.fa) = new AnnotationDeclaration();
        (yyval.fa)->at = tokAt(scanner, (yylsp[-1]));
        (yyval.fa)->annotation = newLogicAnnotation(LogicAnnotationOp::And,(yyvsp[-2].fa),(yyvsp[0].fa));
    }
    break;

  case 136: /* annotation_declaration: annotation_declaration "||" annotation_declaration  */
                                                                            {
        if ( !(yyvsp[-2].fa)->annotation || !(yyvsp[-2].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[-2].fa)->annotation))->isSpecialized() ) {
            das_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[-2])),
                CompilationError::invalid_annotation); }
        if ( !(yyvsp[0].fa)->annotation || !(yyvsp[0].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[0].fa)->annotation))->isSpecialized() ) {
            das_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[0])),
                CompilationError::invalid_annotation); }
        (yyval.fa) = new AnnotationDeclaration();
        (yyval.fa)->at = tokAt(scanner, (yylsp[-1]));
        (yyval.fa)->annotation = newLogicAnnotation(LogicAnnotationOp::Or,(yyvsp[-2].fa),(yyvsp[0].fa));
    }
    break;

  case 137: /* annotation_declaration: annotation_declaration "^^" annotation_declaration  */
                                                                              {
        if ( !(yyvsp[-2].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[-2].fa)->annotation))->isSpecialized() ) {
            das_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[-2])),
                CompilationError::invalid_annotation); }
        if ( !(yyvsp[0].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[0].fa)->annotation))->isSpecialized() ) {
            das_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[0])),
                CompilationError::invalid_annotation); }
        (yyval.fa) = new AnnotationDeclaration();
        (yyval.fa)->at = tokAt(scanner, (yylsp[-1]));
        (yyval.fa)->annotation = newLogicAnnotation(LogicAnnotationOp::Xor,(yyvsp[-2].fa),(yyvsp[0].fa));
    }
    break;

  case 138: /* annotation_declaration: '(' annotation_declaration ')'  */
                                            {
        (yyval.fa) = (yyvsp[-1].fa);
    }
    break;

  case 139: /* annotation_declaration: "|>" annotation_declaration  */
                                          {
        (yyval.fa) = (yyvsp[0].fa);
        (yyvsp[0].fa)->inherited = true;
    }
    break;

  case 140: /* annotation_list: annotation_declaration  */
                                    {
            (yyval.faList) = new AnnotationList();
            (yyval.faList)->push_back(AnnotationDeclarationPtr((yyvsp[0].fa)));
    }
    break;

  case 141: /* annotation_list: annotation_list ',' annotation_declaration  */
                                                              {
        (yyval.faList) = (yyvsp[-2].faList);
        (yyval.faList)->push_back(AnnotationDeclarationPtr((yyvsp[0].fa)));
    }
    break;

  case 142: /* optional_annotation_list: %empty  */
                                        { (yyval.faList) = nullptr; }
    break;

  case 143: /* optional_annotation_list: '[' annotation_list ']'  */
                                        { (yyval.faList) = (yyvsp[-1].faList); }
    break;

  case 144: /* optional_function_argument_list: %empty  */
                                                { (yyval.pVarDeclList) = nullptr; }
    break;

  case 145: /* optional_function_argument_list: '(' ')'  */
                                                { (yyval.pVarDeclList) = nullptr; }
    break;

  case 146: /* optional_function_argument_list: '(' function_argument_list ')'  */
                                                { (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList); }
    break;

  case 147: /* optional_function_type: %empty  */
        {
        (yyval.pTypeDecl) = new TypeDecl(Type::autoinfer);
    }
    break;

  case 148: /* optional_function_type: ':' type_declaration  */
                                        {
        (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 149: /* optional_function_type: "->" type_declaration  */
                                           {
        (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 150: /* function_name: "name"  */
                          {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyval.s) = (yyvsp[0].s);
    }
    break;

  case 151: /* function_name: "operator" '!'  */
                             { (yyval.s) = new string("!"); }
    break;

  case 152: /* function_name: "operator" '~'  */
                             { (yyval.s) = new string("~"); }
    break;

  case 153: /* function_name: "operator" "+="  */
                             { (yyval.s) = new string("+="); }
    break;

  case 154: /* function_name: "operator" "-="  */
                             { (yyval.s) = new string("-="); }
    break;

  case 155: /* function_name: "operator" "*="  */
                             { (yyval.s) = new string("*="); }
    break;

  case 156: /* function_name: "operator" "/="  */
                             { (yyval.s) = new string("/="); }
    break;

  case 157: /* function_name: "operator" "%="  */
                             { (yyval.s) = new string("%="); }
    break;

  case 158: /* function_name: "operator" "&="  */
                             { (yyval.s) = new string("&="); }
    break;

  case 159: /* function_name: "operator" "|="  */
                             { (yyval.s) = new string("|="); }
    break;

  case 160: /* function_name: "operator" "^="  */
                             { (yyval.s) = new string("^="); }
    break;

  case 161: /* function_name: "operator" "&&="  */
                                { (yyval.s) = new string("&&="); }
    break;

  case 162: /* function_name: "operator" "||="  */
                                { (yyval.s) = new string("||="); }
    break;

  case 163: /* function_name: "operator" "^^="  */
                                { (yyval.s) = new string("^^="); }
    break;

  case 164: /* function_name: "operator" "&&"  */
                             { (yyval.s) = new string("&&"); }
    break;

  case 165: /* function_name: "operator" "||"  */
                             { (yyval.s) = new string("||"); }
    break;

  case 166: /* function_name: "operator" "^^"  */
                             { (yyval.s) = new string("^^"); }
    break;

  case 167: /* function_name: "operator" '+'  */
                             { (yyval.s) = new string("+"); }
    break;

  case 168: /* function_name: "operator" '-'  */
                             { (yyval.s) = new string("-"); }
    break;

  case 169: /* function_name: "operator" '*'  */
                             { (yyval.s) = new string("*"); }
    break;

  case 170: /* function_name: "operator" '/'  */
                             { (yyval.s) = new string("/"); }
    break;

  case 171: /* function_name: "operator" '%'  */
                             { (yyval.s) = new string("%"); }
    break;

  case 172: /* function_name: "operator" '<'  */
                             { (yyval.s) = new string("<"); }
    break;

  case 173: /* function_name: "operator" '>'  */
                             { (yyval.s) = new string(">"); }
    break;

  case 174: /* function_name: "operator" ".."  */
                             { (yyval.s) = new string("interval"); }
    break;

  case 175: /* function_name: "operator" "=="  */
                             { (yyval.s) = new string("=="); }
    break;

  case 176: /* function_name: "operator" "!="  */
                             { (yyval.s) = new string("!="); }
    break;

  case 177: /* function_name: "operator" "<="  */
                             { (yyval.s) = new string("<="); }
    break;

  case 178: /* function_name: "operator" ">="  */
                             { (yyval.s) = new string(">="); }
    break;

  case 179: /* function_name: "operator" '&'  */
                             { (yyval.s) = new string("&"); }
    break;

  case 180: /* function_name: "operator" '|'  */
                             { (yyval.s) = new string("|"); }
    break;

  case 181: /* function_name: "operator" '^'  */
                             { (yyval.s) = new string("^"); }
    break;

  case 182: /* function_name: "++" "operator"  */
                             { (yyval.s) = new string("++"); }
    break;

  case 183: /* function_name: "--" "operator"  */
                             { (yyval.s) = new string("--"); }
    break;

  case 184: /* function_name: "operator" "++"  */
                             { (yyval.s) = new string("+++"); }
    break;

  case 185: /* function_name: "operator" "--"  */
                             { (yyval.s) = new string("---"); }
    break;

  case 186: /* function_name: "operator" "<<"  */
                             { (yyval.s) = new string("<<"); }
    break;

  case 187: /* function_name: "operator" ">>"  */
                             { (yyval.s) = new string(">>"); }
    break;

  case 188: /* function_name: "operator" "<<="  */
                             { (yyval.s) = new string("<<="); }
    break;

  case 189: /* function_name: "operator" ">>="  */
                             { (yyval.s) = new string(">>="); }
    break;

  case 190: /* function_name: "operator" "<<<"  */
                             { (yyval.s) = new string("<<<"); }
    break;

  case 191: /* function_name: "operator" ">>>"  */
                             { (yyval.s) = new string(">>>"); }
    break;

  case 192: /* function_name: "operator" "<<<="  */
                             { (yyval.s) = new string("<<<="); }
    break;

  case 193: /* function_name: "operator" ">>>="  */
                             { (yyval.s) = new string(">>>="); }
    break;

  case 194: /* function_name: "operator" '[' ']'  */
                             { (yyval.s) = new string("[]"); }
    break;

  case 195: /* function_name: "operator" '[' ']' "<-"  */
                                    { (yyval.s) = new string("[]<-"); }
    break;

  case 196: /* function_name: "operator" '[' ']' ":="  */
                                      { (yyval.s) = new string("[]:="); }
    break;

  case 197: /* function_name: "operator" '[' ']' "+="  */
                                     { (yyval.s) = new string("[]+="); }
    break;

  case 198: /* function_name: "operator" '[' ']' "-="  */
                                     { (yyval.s) = new string("[]-="); }
    break;

  case 199: /* function_name: "operator" '[' ']' "*="  */
                                     { (yyval.s) = new string("[]*="); }
    break;

  case 200: /* function_name: "operator" '[' ']' "/="  */
                                     { (yyval.s) = new string("[]/="); }
    break;

  case 201: /* function_name: "operator" '[' ']' "%="  */
                                     { (yyval.s) = new string("[]%="); }
    break;

  case 202: /* function_name: "operator" '[' ']' "&="  */
                                     { (yyval.s) = new string("[]&="); }
    break;

  case 203: /* function_name: "operator" '[' ']' "|="  */
                                     { (yyval.s) = new string("[]|="); }
    break;

  case 204: /* function_name: "operator" '[' ']' "^="  */
                                     { (yyval.s) = new string("[]^="); }
    break;

  case 205: /* function_name: "operator" '[' ']' "&&="  */
                                        { (yyval.s) = new string("[]&&="); }
    break;

  case 206: /* function_name: "operator" '[' ']' "||="  */
                                        { (yyval.s) = new string("[]||="); }
    break;

  case 207: /* function_name: "operator" '[' ']' "^^="  */
                                        { (yyval.s) = new string("[]^^="); }
    break;

  case 208: /* function_name: "operator" "?[" ']'  */
                                { (yyval.s) = new string("?[]"); }
    break;

  case 209: /* function_name: "operator" '.'  */
                             { (yyval.s) = new string("."); }
    break;

  case 210: /* function_name: "operator" "?."  */
                             { (yyval.s) = new string("?."); }
    break;

  case 211: /* function_name: "operator" '.' "name"  */
                                       { (yyval.s) = new string(".`"+*(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 212: /* function_name: "operator" '.' "name" ":="  */
                                             { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`clone"); delete (yyvsp[-1].s); }
    break;

  case 213: /* function_name: "operator" '.' "name" "+="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`+="); delete (yyvsp[-1].s); }
    break;

  case 214: /* function_name: "operator" '.' "name" "-="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`-="); delete (yyvsp[-1].s); }
    break;

  case 215: /* function_name: "operator" '.' "name" "*="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`*="); delete (yyvsp[-1].s); }
    break;

  case 216: /* function_name: "operator" '.' "name" "/="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`/="); delete (yyvsp[-1].s); }
    break;

  case 217: /* function_name: "operator" '.' "name" "%="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`%="); delete (yyvsp[-1].s); }
    break;

  case 218: /* function_name: "operator" '.' "name" "&="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`&="); delete (yyvsp[-1].s); }
    break;

  case 219: /* function_name: "operator" '.' "name" "|="  */
                                          { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`|="); delete (yyvsp[-1].s); }
    break;

  case 220: /* function_name: "operator" '.' "name" "^="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`^="); delete (yyvsp[-1].s); }
    break;

  case 221: /* function_name: "operator" '.' "name" "&&="  */
                                              { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`&&="); delete (yyvsp[-1].s); }
    break;

  case 222: /* function_name: "operator" '.' "name" "||="  */
                                            { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`||="); delete (yyvsp[-1].s); }
    break;

  case 223: /* function_name: "operator" '.' "name" "^^="  */
                                              { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`^^="); delete (yyvsp[-1].s); }
    break;

  case 224: /* function_name: "operator" "?." "name"  */
                                       { (yyval.s) = new string("?.`"+*(yyvsp[0].s)); delete (yyvsp[0].s);}
    break;

  case 225: /* function_name: "operator" ":="  */
                                { (yyval.s) = new string("clone"); }
    break;

  case 226: /* function_name: "operator" "delete"  */
                                { (yyval.s) = new string("finalize"); }
    break;

  case 227: /* function_name: "operator" "??"  */
                           { (yyval.s) = new string("??"); }
    break;

  case 228: /* function_name: "operator" "is"  */
                            { (yyval.s) = new string("`is"); }
    break;

  case 229: /* function_name: "operator" "as"  */
                            { (yyval.s) = new string("`as"); }
    break;

  case 230: /* function_name: "operator" "is" "name"  */
                                       { (yyval.s) = (yyvsp[0].s); *(yyvsp[0].s) = "`is`" + *(yyvsp[0].s); }
    break;

  case 231: /* function_name: "operator" "as" "name"  */
                                       { (yyval.s) = (yyvsp[0].s); *(yyvsp[0].s) = "`as`" + *(yyvsp[0].s); }
    break;

  case 232: /* function_name: "operator" '?' "as"  */
                                { (yyval.s) = new string("?as"); }
    break;

  case 233: /* function_name: "operator" '?' "as" "name"  */
                                           { (yyval.s) = (yyvsp[0].s); *(yyvsp[0].s) = "?as`" + *(yyvsp[0].s); }
    break;

  case 234: /* function_name: "bool"  */
                     { (yyval.s) = new string("bool"); }
    break;

  case 235: /* function_name: "string"  */
                     { (yyval.s) = new string("string"); }
    break;

  case 236: /* function_name: "int"  */
                     { (yyval.s) = new string("int"); }
    break;

  case 237: /* function_name: "int2"  */
                     { (yyval.s) = new string("int2"); }
    break;

  case 238: /* function_name: "int3"  */
                     { (yyval.s) = new string("int3"); }
    break;

  case 239: /* function_name: "int4"  */
                     { (yyval.s) = new string("int4"); }
    break;

  case 240: /* function_name: "uint"  */
                     { (yyval.s) = new string("uint"); }
    break;

  case 241: /* function_name: "uint2"  */
                     { (yyval.s) = new string("uint2"); }
    break;

  case 242: /* function_name: "uint3"  */
                     { (yyval.s) = new string("uint3"); }
    break;

  case 243: /* function_name: "uint4"  */
                     { (yyval.s) = new string("uint4"); }
    break;

  case 244: /* function_name: "float"  */
                     { (yyval.s) = new string("float"); }
    break;

  case 245: /* function_name: "float2"  */
                     { (yyval.s) = new string("float2"); }
    break;

  case 246: /* function_name: "float3"  */
                     { (yyval.s) = new string("float3"); }
    break;

  case 247: /* function_name: "float4"  */
                     { (yyval.s) = new string("float4"); }
    break;

  case 248: /* function_name: "range"  */
                     { (yyval.s) = new string("range"); }
    break;

  case 249: /* function_name: "urange"  */
                     { (yyval.s) = new string("urange"); }
    break;

  case 250: /* function_name: "range64"  */
                     { (yyval.s) = new string("range64"); }
    break;

  case 251: /* function_name: "urange64"  */
                     { (yyval.s) = new string("urange64"); }
    break;

  case 252: /* function_name: "int64"  */
                     { (yyval.s) = new string("int64"); }
    break;

  case 253: /* function_name: "uint64"  */
                     { (yyval.s) = new string("uint64"); }
    break;

  case 254: /* function_name: "double"  */
                     { (yyval.s) = new string("double"); }
    break;

  case 255: /* function_name: "int8"  */
                     { (yyval.s) = new string("int8"); }
    break;

  case 256: /* function_name: "uint8"  */
                     { (yyval.s) = new string("uint8"); }
    break;

  case 257: /* function_name: "int16"  */
                     { (yyval.s) = new string("int16"); }
    break;

  case 258: /* function_name: "uint16"  */
                     { (yyval.s) = new string("uint16"); }
    break;

  case 259: /* function_name: "float16"  */
                     { (yyval.s) = new string("float16"); }
    break;

  case 260: /* function_name: "half2"  */
                     { (yyval.s) = new string("half2"); }
    break;

  case 261: /* function_name: "half3"  */
                     { (yyval.s) = new string("half3"); }
    break;

  case 262: /* function_name: "half4"  */
                     { (yyval.s) = new string("half4"); }
    break;

  case 263: /* function_name: "half8"  */
                     { (yyval.s) = new string("half8"); }
    break;

  case 264: /* function_name: "short2"  */
                     { (yyval.s) = new string("short2"); }
    break;

  case 265: /* function_name: "short3"  */
                     { (yyval.s) = new string("short3"); }
    break;

  case 266: /* function_name: "short4"  */
                     { (yyval.s) = new string("short4"); }
    break;

  case 267: /* function_name: "short8"  */
                     { (yyval.s) = new string("short8"); }
    break;

  case 268: /* function_name: "ushort2"  */
                     { (yyval.s) = new string("ushort2"); }
    break;

  case 269: /* function_name: "ushort3"  */
                     { (yyval.s) = new string("ushort3"); }
    break;

  case 270: /* function_name: "ushort4"  */
                     { (yyval.s) = new string("ushort4"); }
    break;

  case 271: /* function_name: "ushort8"  */
                     { (yyval.s) = new string("ushort8"); }
    break;

  case 272: /* function_name: "byte2"  */
                     { (yyval.s) = new string("byte2"); }
    break;

  case 273: /* function_name: "byte3"  */
                     { (yyval.s) = new string("byte3"); }
    break;

  case 274: /* function_name: "byte4"  */
                     { (yyval.s) = new string("byte4"); }
    break;

  case 275: /* function_name: "byte8"  */
                     { (yyval.s) = new string("byte8"); }
    break;

  case 276: /* function_name: "byte16"  */
                     { (yyval.s) = new string("byte16"); }
    break;

  case 277: /* function_name: "ubyte2"  */
                     { (yyval.s) = new string("ubyte2"); }
    break;

  case 278: /* function_name: "ubyte3"  */
                     { (yyval.s) = new string("ubyte3"); }
    break;

  case 279: /* function_name: "ubyte4"  */
                     { (yyval.s) = new string("ubyte4"); }
    break;

  case 280: /* function_name: "ubyte8"  */
                     { (yyval.s) = new string("ubyte8"); }
    break;

  case 281: /* function_name: "ubyte16"  */
                     { (yyval.s) = new string("ubyte16"); }
    break;

  case 282: /* optional_template: %empty  */
                                        { (yyval.b) = false; }
    break;

  case 283: /* optional_template: "template"  */
                                        { (yyval.b) = true; }
    break;

  case 284: /* global_function_declaration: optional_annotation_list "def" optional_template function_declaration  */
                                                                                                              {
        (yyvsp[0].pFuncDecl)->atDecl = tokRangeAt(scanner,(yylsp[-2]),(yylsp[0]));
        (yyvsp[0].pFuncDecl)->isTemplate = (yyvsp[-1].b);
        assignDefaultArguments((yyvsp[0].pFuncDecl));
        runFunctionAnnotations(scanner, yyextra, (yyvsp[0].pFuncDecl), (yyvsp[-3].faList), tokAt(scanner,(yylsp[-3])));
        if ( (yyvsp[0].pFuncDecl)->isGeneric() ) {
            implAddGenericFunction(scanner,(yyvsp[0].pFuncDecl));
        } else {
            if ( !yyextra->g_Program->addFunction((yyvsp[0].pFuncDecl)) ) {
                das_yyerror(scanner,"function is already defined " +
                    (yyvsp[0].pFuncDecl)->getMangledName(),(yyvsp[0].pFuncDecl)->at,
                        CompilationError::function_already_declared);
            }
        }
        (yyvsp[0].pFuncDecl)->delRef();
    }
    break;

  case 285: /* optional_public_or_private_function: %empty  */
                        { (yyval.b) = yyextra->g_thisStructure ? !yyextra->g_thisStructure->privateStructure : yyextra->g_Program->thisModule->isPublic; }
    break;

  case 286: /* optional_public_or_private_function: "private"  */
                        { (yyval.b) = false; }
    break;

  case 287: /* optional_public_or_private_function: "public"  */
                        { (yyval.b) = true; }
    break;

  case 288: /* function_declaration_header: function_name optional_function_argument_list optional_function_type  */
                                                                                                {
        (yyval.pFuncDecl) = ast_functionDeclarationHeader(scanner,(yyvsp[-2].s),(yyvsp[-1].pVarDeclList),(yyvsp[0].pTypeDecl),tokAt(scanner,(yylsp[-2])));
    }
    break;

  case 289: /* $@9: %empty  */
                                                     {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeFunction(tak);
        }
    }
    break;

  case 290: /* function_declaration: optional_public_or_private_function $@9 function_declaration_header expression_block  */
                                                                {
        (yyvsp[-1].pFuncDecl)->body = (yyvsp[0].pExpression);
        (yyvsp[-1].pFuncDecl)->privateFunction = !(yyvsp[-3].b);
        (yyval.pFuncDecl) = (yyvsp[-1].pFuncDecl);
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterFunction((yyvsp[-1].pFuncDecl),tak);
        }
    }
    break;

  case 291: /* open_block: "begin of code block"  */
          { (yyval.ui) = 0xdeadbeef; }
    break;

  case 292: /* open_block: "new scope"  */
                        { (yyval.ui) = (yyvsp[0].i); }
    break;

  case 293: /* close_block: "end of code block"  */
          { (yyval.ui) = 0xdeadbeef; }
    break;

  case 294: /* close_block: "close scope"  */
                         { (yyval.ui) = (yyvsp[0].i); }
    break;

  case 295: /* expression_block: open_block expressions close_block  */
                                                                  {
        auto prev_loc = format::Pos::from(tokAt(scanner,(yylsp[-2])));
        handle_brace(prev_loc, (yyvsp[-2].ui), format::get_substring(prev_loc, format::Pos::from_last(tokAt(scanner,(yylsp[-1])))),
                     yyextra->das_tab_size, format::Pos::from_last(tokAt(scanner,(yylsp[-1]))));
        (yyval.pExpression) = (yyvsp[-1].pExpression);
        (yyval.pExpression)->at = tokRangeAt(scanner,(yylsp[-2]),(yylsp[0]));
    }
    break;

  case 296: /* expression_block: open_block expressions close_block "finally" open_block expressions close_block  */
                                                                                                                                  {
        auto prev_loc = format::Pos::from(tokAt(scanner,(yylsp[-6])));
        if (format::is_replace_braces() && (yyvsp[-6].ui) != 0xdeadbeef && format::prepare_rule(prev_loc)) {
            handle_brace(prev_loc, (yyvsp[-6].ui), format::get_substring(prev_loc, format::Pos::from_last(tokAt(scanner,(yylsp[-5])))),
                         yyextra->das_tab_size, format::Pos::from_last(tokAt(scanner,(yylsp[-5]))));
            auto prev_loc_f = format::Pos::from(tokAt(scanner,(yylsp[-2])));
            assert((yyvsp[-2].ui) != 0xdeadbeef);
            {
                const auto internal_f = format::get_substring(prev_loc_f, format::Pos::from_last(tokAt(scanner,(yylsp[-1]))));
                format::get_writer() << " finally {" << internal_f << "\n" << string((yyvsp[-2].ui) * yyextra->das_tab_size, ' ') + "}";
                format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[-1]))));
            }
        }

        auto pB = (ExprBlock *) (yyvsp[-5].pExpression);
        auto pF = (ExprBlock *) (yyvsp[-1].pExpression);
        swap ( pB->finalList, pF->list );
        (yyval.pExpression) = (yyvsp[-5].pExpression);
        (yyval.pExpression)->at = tokRangeAt(scanner,(yylsp[-6]),(yylsp[0]));
        delete (yyvsp[-1].pExpression);
    }
    break;

  case 297: /* expr_call_pipe: expr expr_full_block_assumed_piped  */
                                                      {
        if ( (yyvsp[-1].pExpression)->rtti_isCallLikeExpr() ) {
            auto start = format::Pos::from_last(tokAt(scanner, (yylsp[-1])));
            start.column -= 1; // drop )
            if (format::is_replace_braces() && format::prepare_rule(start)) {
                if (!((ExprLooksLikeCall *)(yyvsp[-1].pExpression))->arguments.empty()) {
                    format::get_writer() << ", ";
                }
                format::get_writer() << format::get_substring(tokAt(scanner, (yylsp[0]))) << ");";
                format::finish_rule(format::Pos::from_last(tokAt(scanner, (yylsp[0]))));
            }
            ((ExprLooksLikeCall *)(yyvsp[-1].pExpression))->arguments.push_back((yyvsp[0].pExpression));
            (yyval.pExpression) = (yyvsp[-1].pExpression);
        } else {
            (yyval.pExpression) = (yyvsp[-1].pExpression);
            delete (yyvsp[0].pExpression);
        }
    }
    break;

  case 298: /* expr_call_pipe: expression_keyword expr_full_block_assumed_piped  */
                                                                    {
        if ( (yyvsp[-1].pExpression)->rtti_isCallLikeExpr() ) {
            ((ExprLooksLikeCall *)(yyvsp[-1].pExpression))->arguments.push_back((yyvsp[0].pExpression));
            (yyval.pExpression) = (yyvsp[-1].pExpression);
        } else {
            (yyval.pExpression) = (yyvsp[-1].pExpression);
            delete (yyvsp[0].pExpression);
        }
    }
    break;

  case 299: /* expr_call_pipe: "generator" '<' type_declaration_no_options '>' optional_capture_list expr_full_block_assumed_piped  */
                                                                                                                                             {
        (yyval.pExpression) = ast_makeGenerator(scanner,(yyvsp[-3].pTypeDecl),(yyvsp[-1].pCaptList),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[-5])),tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 300: /* expression_any: SEMICOLON  */
                                            { (yyval.pExpression) = nullptr; }
    break;

  case 301: /* expression_any: "end of expression"  */
                                            { (yyval.pExpression) = nullptr; }
    break;

  case 302: /* expression_any: expr_pipe  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 303: /* expression_any: expr_keyword  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 304: /* expression_any: expr_assign_pipe  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 305: /* expression_any: expr_assign semicolon  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 306: /* expression_any: expression_delete semicolon  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 307: /* expression_any: expression_let  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 308: /* expression_any: expression_while_loop  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 309: /* expression_any: expression_unsafe  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 310: /* expression_any: expression_with  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 311: /* expression_any: expression_with_alias  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 312: /* expression_any: expression_for_loop  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 313: /* expression_any: expression_break semicolon  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 314: /* expression_any: expression_continue semicolon  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 315: /* expression_any: expression_return  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 316: /* expression_any: expression_yield  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 317: /* expression_any: expression_if_then_else  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 318: /* expression_any: expression_try_catch  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 319: /* expression_any: expression_label semicolon  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 320: /* expression_any: expression_goto semicolon  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 321: /* expression_any: "pass" semicolon  */
                                                  { (yyval.pExpression) = nullptr; }
    break;

  case 322: /* expressions: %empty  */
        {
        (yyval.pExpression) = new ExprBlock();
        (yyval.pExpression)->at = LineInfo(yyextra->g_FileAccessStack.back(),
            yylloc.first_column,yylloc.first_line,yylloc.last_column,yylloc.last_line);
    }
    break;

  case 323: /* expressions: expressions expression_any  */
                                                        {
        (yyval.pExpression) = (yyvsp[-1].pExpression);
        if ( (yyvsp[0].pExpression) ) {
            static_cast<ExprBlock*>((yyvsp[-1].pExpression))->list.push_back((yyvsp[0].pExpression));
        }
    }
    break;

  case 324: /* expressions: expressions error  */
                                 {
        delete (yyvsp[-1].pExpression); (yyval.pExpression) = nullptr; YYABORT;
    }
    break;

  case 325: /* expr_keyword: "keyword" expr expression_block  */
                                                           {
        format::wrap_par_expr(tokAt(scanner,(yylsp[-1])), (yyvsp[-1].pExpression)->at); // wrap match (expr)
        auto pCall = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-2])),*(yyvsp[-2].s));
        pCall->arguments.push_back((yyvsp[-1].pExpression));
        auto resT = new TypeDecl(Type::autoinfer);
        auto blk = ast_makeBlock(scanner,0,nullptr,nullptr,nullptr,resT,(yyvsp[0].pExpression),tokAt(scanner,(yylsp[0])),tokAt(scanner,(yylsp[0])),LineInfo());
        pCall->arguments.push_back(blk);
        delete (yyvsp[-2].s);
        (yyval.pExpression) = pCall;
    }
    break;

  case 326: /* optional_expr_list: %empty  */
        { (yyval.pExpression) = nullptr; }
    break;

  case 327: /* optional_expr_list: expr_list optional_comma  */
                                            { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 328: /* optional_expr_list_in_braces: %empty  */
        { (yyval.pExpression) = nullptr; }
    break;

  case 329: /* optional_expr_list_in_braces: '(' optional_expr_list optional_comma ')'  */
                                                             { (yyval.pExpression) = (yyvsp[-2].pExpression); }
    break;

  case 330: /* optional_expr_map_tuple_list: %empty  */
        { (yyval.pExpression) = nullptr; }
    break;

  case 331: /* optional_expr_map_tuple_list: expr_map_tuple_list optional_comma  */
                                                      { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 332: /* type_declaration_no_options_list: type_declaration  */
                               {
        (yyval.pTypeDeclList) = new vector<Expression *>();
        (yyval.pTypeDeclList)->push_back(new ExprTypeDecl(tokAt(scanner,(yylsp[0])),(yyvsp[0].pTypeDecl)));
    }
    break;

  case 333: /* type_declaration_no_options_list: type_declaration_no_options_list c_or_s type_declaration  */
                                                                              {
        (yyval.pTypeDeclList) = (yyvsp[-2].pTypeDeclList);
        (yyval.pTypeDeclList)->push_back(new ExprTypeDecl(tokAt(scanner,(yylsp[0])),(yyvsp[0].pTypeDecl)));
    }
    break;

  case 334: /* $@10: %empty  */
                         { yyextra->das_arrow_depth ++; }
    break;

  case 335: /* $@11: %empty  */
                                                                                                      { yyextra->das_arrow_depth --; }
    break;

  case 336: /* expression_keyword: "keyword" '<' $@10 type_declaration_no_options_list '>' $@11 expr  */
                                                                                                                                                     {
        auto pCall = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-6])),tokAt(scanner,(yylsp[0])),*(yyvsp[-6].s));
        pCall->arguments = typesAndSequenceToList((yyvsp[-3].pTypeDeclList),(yyvsp[0].pExpression));
        delete (yyvsp[-6].s);
        (yyval.pExpression) = pCall;
    }
    break;

  case 337: /* $@12: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 338: /* $@13: %empty  */
                                                                                                            { yyextra->das_arrow_depth --; }
    break;

  case 339: /* expression_keyword: "type function" '<' $@12 type_declaration_no_options_list '>' $@13 optional_expr_list_in_braces  */
                                                                                                                                                                                   {
        auto pCall = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-6])),tokAt(scanner,(yylsp[0])),*(yyvsp[-6].s));
        pCall->arguments = typesAndSequenceToList((yyvsp[-3].pTypeDeclList),(yyvsp[0].pExpression));
        delete (yyvsp[-6].s);
        (yyval.pExpression) = pCall;
    }
    break;

  case 340: /* expr_pipe: expr_assign " <|" expr_block  */
                                                        {
        Expression * pipeCall = (yyvsp[-2].pExpression)->tail();
        if ( pipeCall->rtti_isCallLikeExpr() ) {
            auto pCall = (ExprLooksLikeCall *) pipeCall;
            pCall->arguments.push_back((yyvsp[0].pExpression));
            (yyval.pExpression) = (yyvsp[-2].pExpression);
        } else if ( pipeCall->rtti_isVar() ) {
            // a += b <| c
            auto pVar = (ExprVar *) pipeCall;
            auto pCall = yyextra->g_Program->makeCall(pVar->at,pVar->name);
            pCall->arguments.push_back((yyvsp[0].pExpression));
            if ( !(yyvsp[-2].pExpression)->swap_tail(pVar,pCall) ) {
                delete pVar;
                (yyval.pExpression) = pCall;
            } else {
                (yyval.pExpression) = (yyvsp[-2].pExpression);
            }
        } else if ( pipeCall->rtti_isMakeStruct() ) {
            auto pMS = (ExprMakeStruct *) pipeCall;
            if ( pMS->block ) {
                das_yyerror(scanner,"can't pipe into [[ make structure ]]. it already has where closure",
                    tokAt(scanner,(yylsp[-1])),CompilationError::cant_pipe);
                delete (yyvsp[0].pExpression);
            } else {
                pMS->block = (yyvsp[0].pExpression);
            }
            (yyval.pExpression) = (yyvsp[-2].pExpression);
        } else {
            das_yyerror(scanner,"can only pipe into function call or [[ make structure ]]",
                tokAt(scanner,(yylsp[-1])),CompilationError::cant_pipe);
            delete (yyvsp[0].pExpression);
            (yyval.pExpression) = (yyvsp[-2].pExpression);
        }
    }
    break;

  case 341: /* expr_pipe: "@ <|" expr_block  */
                                     {
        if (format::is_replace_braces() && format::prepare_rule(format::Pos::from(tokAt(scanner, (yylsp[-1]))))) {
            format::get_writer() << "@";
            format::finish_rule(format::Pos::from_last(tokAt(scanner, (yylsp[-1]))));
        }

        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 342: /* expr_pipe: "@@ <|" expr_block  */
                                     {
        if (format::is_replace_braces() && format::prepare_rule(format::Pos::from(tokAt(scanner, (yylsp[-1]))))) {
            format::get_writer() << "@@";
            format::finish_rule(format::Pos::from_last(tokAt(scanner, (yylsp[-1]))));
        }
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 343: /* expr_pipe: "$ <|" expr_block  */
                                     {
        if (format::is_replace_braces() && format::prepare_rule(format::Pos::from(tokAt(scanner, (yylsp[-1]))))) {
            format::get_writer() << "$";
            format::finish_rule(format::Pos::from_last(tokAt(scanner, (yylsp[-1]))));
        }
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 344: /* expr_pipe: expr_call_pipe  */
                             {
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 345: /* name_in_namespace: "name"  */
                                               { (yyval.s) = (yyvsp[0].s); }
    break;

  case 346: /* name_in_namespace: "name" "::" "name"  */
                                               {
            auto ita = yyextra->das_module_alias.find(*(yyvsp[-2].s));
            if ( ita == yyextra->das_module_alias.end() ) {
                *(yyvsp[-2].s) += "::";
            } else {
                *(yyvsp[-2].s) = ita->second + "::";
            }
            *(yyvsp[-2].s) += *(yyvsp[0].s);
            delete (yyvsp[0].s);
            (yyval.s) = (yyvsp[-2].s);
        }
    break;

  case 347: /* name_in_namespace: "::" "name"  */
                                               { *(yyvsp[0].s) = "::" + *(yyvsp[0].s); (yyval.s) = (yyvsp[0].s); }
    break;

  case 348: /* expression_delete: "delete" expr  */
                                      {
        (yyval.pExpression) = new ExprDelete(tokAt(scanner,(yylsp[-1])), (yyvsp[0].pExpression));
    }
    break;

  case 349: /* expression_delete: "delete" "explicit" expr  */
                                                   {
        auto delExpr = new ExprDelete(tokAt(scanner,(yylsp[-2])), (yyvsp[0].pExpression));
        delExpr->native = true;
        (yyval.pExpression) = delExpr;
    }
    break;

  case 350: /* $@14: %empty  */
           { yyextra->das_arrow_depth ++; }
    break;

  case 351: /* $@15: %empty  */
                                                                           { yyextra->das_arrow_depth --; }
    break;

  case 352: /* new_type_declaration: '<' $@14 type_declaration '>' $@15  */
                                                                                                            {
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 353: /* new_type_declaration: structure_type_declaration  */
                                               {
        (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl);
    }
    break;

  case 354: /* expr_new: "new" new_type_declaration  */
                                                       {
        (yyval.pExpression) = new ExprNew(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pTypeDecl),false);
    }
    break;

  case 355: /* expr_new: "new" new_type_declaration '(' use_initializer ')'  */
                                                                                     {
        (yyval.pExpression) = new ExprNew(tokAt(scanner,(yylsp[-4])),(yyvsp[-3].pTypeDecl),true);
        ((ExprNew *)(yyval.pExpression))->initializer = (yyvsp[-1].b);
    }
    break;

  case 356: /* expr_new: "new" new_type_declaration '(' expr_list ')'  */
                                                                                    {
        auto pNew = new ExprNew(tokAt(scanner,(yylsp[-4])),(yyvsp[-3].pTypeDecl),true);
        (yyval.pExpression) = parseFunctionArguments(pNew,(yyvsp[-1].pExpression));
    }
    break;

  case 357: /* expr_new: "new" new_type_declaration '(' make_struct_single ')'  */
                                                                                      {
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->at = tokAt(scanner,(yylsp[-3]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-3].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = true; // $init;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
        (yyval.pExpression) = new ExprAscend(tokAt(scanner,(yylsp[-4])),(yyvsp[-1].pExpression));
    }
    break;

  case 358: /* expr_new: "new" new_type_declaration '(' "uninitialized" make_struct_single ')'  */
                                                                                                        {
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->at = tokAt(scanner,(yylsp[-4]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-4].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = false; // $init;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
        (yyval.pExpression) = new ExprAscend(tokAt(scanner,(yylsp[-5])),(yyvsp[-1].pExpression));
    }
    break;

  case 359: /* expr_new: "new" make_decl  */
                                    {
        (yyval.pExpression) = new ExprAscend(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression));
    }
    break;

  case 360: /* expression_break: "break"  */
                       { (yyval.pExpression) = new ExprBreak(tokAt(scanner,(yylsp[0]))); }
    break;

  case 361: /* expression_continue: "continue"  */
                          { (yyval.pExpression) = new ExprContinue(tokAt(scanner,(yylsp[0]))); }
    break;

  case 362: /* expression_return_no_pipe: "return"  */
                        {
        (yyval.pExpression) = new ExprReturn(tokAt(scanner,(yylsp[0])),nullptr);
    }
    break;

  case 363: /* expression_return_no_pipe: "return" expr_list  */
                                           {
        (yyval.pExpression) = new ExprReturn(tokAt(scanner,(yylsp[-1])),sequenceToTuple((yyvsp[0].pExpression)));
    }
    break;

  case 364: /* expression_return_no_pipe: "return" "<-" expr_list  */
                                                  {
        auto pRet = new ExprReturn(tokAt(scanner,(yylsp[-2])),sequenceToTuple((yyvsp[0].pExpression)));
        pRet->moveSemantics = true;
        (yyval.pExpression) = pRet;
    }
    break;

  case 365: /* expression_return: expression_return_no_pipe semicolon  */
                                                    {
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 366: /* expression_return: "return" expr_pipe  */
                                           {
        (yyval.pExpression) = new ExprReturn(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression));
    }
    break;

  case 367: /* expression_return: "return" "<-" expr_pipe  */
                                                  {
        auto pRet = new ExprReturn(tokAt(scanner,(yylsp[-2])),(yyvsp[0].pExpression));
        pRet->moveSemantics = true;
        (yyval.pExpression) = pRet;
    }
    break;

  case 368: /* expression_yield_no_pipe: "yield" expr  */
                                     {
        (yyval.pExpression) = new ExprYield(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression));
    }
    break;

  case 369: /* expression_yield_no_pipe: "yield" "<-" expr  */
                                            {
        auto pRet = new ExprYield(tokAt(scanner,(yylsp[-2])),(yyvsp[0].pExpression));
        pRet->moveSemantics = true;
        (yyval.pExpression) = pRet;
    }
    break;

  case 370: /* expression_yield: expression_yield_no_pipe semicolon  */
                                                   {
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 371: /* expression_yield: "yield" expr_pipe  */
                                          {
        (yyval.pExpression) = new ExprYield(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression));
    }
    break;

  case 372: /* expression_yield: "yield" "<-" expr_pipe  */
                                                 {
        auto pRet = new ExprYield(tokAt(scanner,(yylsp[-2])),(yyvsp[0].pExpression));
        pRet->moveSemantics = true;
        (yyval.pExpression) = pRet;
    }
    break;

  case 373: /* expression_try_catch: "try" expression_block "recover" expression_block  */
                                                                                              {
        const auto end_block = format::Pos::from_last(tokAt(scanner, (yylsp[-2])));
        const auto start = format::Pos::from(tokAt(scanner, (yylsp[-3])));
        if (format::is_replace_braces()) {
            format::skip_spaces_or_print(tokAt(scanner, (yylsp[-3])), tokAt(scanner, (yylsp[-2])), tokAt(scanner, (yylsp[-1])), yyextra->das_tab_size);
        }

        (yyval.pExpression) = new ExprTryCatch(tokAt(scanner,(yylsp[-3])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
    }
    break;

  case 374: /* kwd_let_var_or_nothing: "let"  */
                 { (yyval.b) = true; }
    break;

  case 375: /* kwd_let_var_or_nothing: "var"  */
                 { (yyval.b) = false; }
    break;

  case 376: /* kwd_let_var_or_nothing: %empty  */
                    { (yyval.b) = true; }
    break;

  case 377: /* kwd_let: "let"  */
                 { (yyval.b) = true; }
    break;

  case 378: /* kwd_let: "var"  */
                 { (yyval.b) = false; }
    break;

  case 379: /* optional_in_scope: "inscope"  */
                    { (yyval.b) = true; }
    break;

  case 380: /* optional_in_scope: %empty  */
                     { (yyval.b) = false; }
    break;

  case 381: /* tuple_expansion: "name"  */
                    {
        (yyval.pNameList) = new vector<string>();
        (yyval.pNameList)->push_back(*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 382: /* tuple_expansion: tuple_expansion ',' "name"  */
                                             {
        (yyvsp[-2].pNameList)->push_back(*(yyvsp[0].s));
        delete (yyvsp[0].s);
        (yyval.pNameList) = (yyvsp[-2].pNameList);
    }
    break;

  case 383: /* tuple_expansion_variable_declaration: "[[" tuple_expansion ']' ']' ':' type_declaration_no_options copy_or_move_or_clone expr semicolon  */
                                                                                                                                                                            {
        // std::cout << "case11" << std::endl;
        format::replace_with(false,
                             format::Pos::from(tokAt(scanner,(yylsp[-8]))),
                             format::substring_between(tokAt(scanner, (yylsp[-8])), tokAt(scanner, (yylsp[-6]))),
                             format::Pos::from_last(tokAt(scanner,(yylsp[-5]))), "(", ")");
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-7].pNameList),tokAt(scanner,(yylsp[-7])),(yyvsp[-3].pTypeDecl),(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
        (yyval.pVarDecl)->isTupleExpansion = true;
    }
    break;

  case 384: /* tuple_expansion_variable_declaration: '(' tuple_expansion ')' ':' type_declaration_no_options copy_or_move_or_clone expr semicolon  */
                                                                                                                                {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-6].pNameList),tokAt(scanner,(yylsp[-6])),(yyvsp[-3].pTypeDecl),(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
        (yyval.pVarDecl)->isTupleExpansion = true;
    }
    break;

  case 385: /* tuple_expansion_variable_declaration: "[[" tuple_expansion ']' ']' optional_ref copy_or_move_or_clone expr semicolon  */
                                                                                                                                                {
        // std::cout << "case12" << std::endl;
        format::replace_with(false,
                              format::Pos::from(tokAt(scanner,(yylsp[-7]))),
                              format::substring_between(tokAt(scanner, (yylsp[-7])), tokAt(scanner, (yylsp[-5]))),
                              format::Pos::from_last(tokAt(scanner,(yylsp[-4]))), "(", ")");

        auto typeDecl = new TypeDecl(Type::autoinfer);
        typeDecl->at = tokAt(scanner,(yylsp[-6]));
        typeDecl->ref = (yyvsp[-3].b);
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-6].pNameList),tokAt(scanner,(yylsp[-6])),typeDecl,(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
        (yyval.pVarDecl)->isTupleExpansion = true;
    }
    break;

  case 386: /* tuple_expansion_variable_declaration: '(' tuple_expansion ')' optional_ref copy_or_move_or_clone expr semicolon  */
                                                                                                        {
        auto typeDecl = new TypeDecl(Type::autoinfer);
        typeDecl->at = tokAt(scanner,(yylsp[-5]));
        typeDecl->ref = (yyvsp[-3].b);
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-5].pNameList),tokAt(scanner,(yylsp[-5])),typeDecl,(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
        (yyval.pVarDecl)->isTupleExpansion = true;
    }
    break;

  case 387: /* expression_let: kwd_let optional_in_scope let_variable_declaration  */
                                                                 {
        (yyval.pExpression) = ast_Let(scanner,(yyvsp[-2].b),(yyvsp[-1].b),(yyvsp[0].pVarDecl),tokAt(scanner,(yylsp[-2])),tokAt(scanner,(yylsp[0])));
    }
    break;

  case 388: /* expression_let: kwd_let optional_in_scope tuple_expansion_variable_declaration  */
                                                                             {
        (yyval.pExpression) = ast_Let(scanner,(yyvsp[-2].b),(yyvsp[-1].b),(yyvsp[0].pVarDecl),tokAt(scanner,(yylsp[-2])),tokAt(scanner,(yylsp[0])));
    }
    break;

  case 389: /* $@16: %empty  */
                          { yyextra->das_arrow_depth ++; }
    break;

  case 390: /* $@17: %empty  */
                                                                                                 { yyextra->das_arrow_depth --; }
    break;

  case 391: /* expr_cast: "cast" '<' $@16 type_declaration_no_options '>' $@17 expr  */
                                                                                                                                                {
        (yyval.pExpression) = new ExprCast(tokAt(scanner,(yylsp[-6])),(yyvsp[0].pExpression),(yyvsp[-3].pTypeDecl));
    }
    break;

  case 392: /* $@18: %empty  */
                            { yyextra->das_arrow_depth ++; }
    break;

  case 393: /* $@19: %empty  */
                                                                                                   { yyextra->das_arrow_depth --; }
    break;

  case 394: /* expr_cast: "upcast" '<' $@18 type_declaration_no_options '>' $@19 expr  */
                                                                                                                                                  {
        auto pCast = new ExprCast(tokAt(scanner,(yylsp[-6])),(yyvsp[0].pExpression),(yyvsp[-3].pTypeDecl));
        pCast->upcast = true;
        (yyval.pExpression) = pCast;
    }
    break;

  case 395: /* $@20: %empty  */
                                 { yyextra->das_arrow_depth ++; }
    break;

  case 396: /* $@21: %empty  */
                                                                                                        { yyextra->das_arrow_depth --; }
    break;

  case 397: /* expr_cast: "reinterpret" '<' $@20 type_declaration_no_options '>' $@21 expr  */
                                                                                                                                                       {
        auto pCast = new ExprCast(tokAt(scanner,(yylsp[-6])),(yyvsp[0].pExpression),(yyvsp[-3].pTypeDecl));
        pCast->reinterpret = true;
        (yyval.pExpression) = pCast;
    }
    break;

  case 398: /* $@22: %empty  */
                         { yyextra->das_arrow_depth ++; }
    break;

  case 399: /* $@23: %empty  */
                                                                                     { yyextra->das_arrow_depth --; }
    break;

  case 400: /* expr_type_decl: "type" '<' $@22 type_declaration '>' $@23  */
                                                                                                                      {
        (yyval.pExpression) = new ExprTypeDecl(tokAt(scanner,(yylsp[-5])),(yyvsp[-2].pTypeDecl));
    }
    break;

  case 401: /* expr_type_info: "typeinfo" '(' name_in_namespace expr ')'  */
                                                                                {
            format::replace_with(false,
                                 format::Pos::from(tokAt(scanner,(yylsp[-3]))),
                                 format::get_substring(tokAt(scanner,(yylsp[-2]))),
                                 format::Pos::from(tokAt(scanner,(yylsp[-1]))), " ", "(");
            if ( (yyvsp[-1].pExpression)->rtti_isTypeDecl() ) {
                auto ptd = (ExprTypeDecl *)(yyvsp[-1].pExpression);
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-4])),*(yyvsp[-2].s),ptd->typeexpr);
                delete (yyvsp[-1].pExpression);
            } else {
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-4])),*(yyvsp[-2].s),(yyvsp[-1].pExpression));
            }
            delete (yyvsp[-2].s);
    }
    break;

  case 402: /* expr_type_info: "typeinfo" '(' name_in_namespace '<' "name" '>' expr ')'  */
                                                                                                             {
            format::replace_with(false,
                                 format::Pos::from(tokAt(scanner,(yylsp[-6]))),
                                 format::get_substring(tokRangeAt(scanner,(yylsp[-5]),(yylsp[-2]))),
                                 format::Pos::from(tokAt(scanner,(yylsp[-1]))), " ", "(");

            if ( (yyvsp[-1].pExpression)->rtti_isTypeDecl() ) {
                auto ptd = (ExprTypeDecl *)(yyvsp[-1].pExpression);
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-7])),*(yyvsp[-5].s),ptd->typeexpr,*(yyvsp[-3].s));
                delete (yyvsp[-1].pExpression);
            } else {
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-7])),*(yyvsp[-5].s),(yyvsp[-1].pExpression),*(yyvsp[-3].s));
            }
            delete (yyvsp[-5].s);
            delete (yyvsp[-3].s);
    }
    break;

  case 403: /* expr_type_info: "typeinfo" '(' name_in_namespace '<' "name" c_or_s "name" '>' expr ')'  */
                                                                                                                                    {
            format::replace_with(false,
                                 format::Pos::from(tokAt(scanner,(yylsp[-8]))),
                                 format::get_substring(tokRangeAt(scanner,(yylsp[-7]),(yylsp[-2]))),
                                 format::Pos::from(tokAt(scanner,(yylsp[-1]))), " ", "(");

            if ( (yyvsp[-1].pExpression)->rtti_isTypeDecl() ) {
                auto ptd = (ExprTypeDecl *)(yyvsp[-1].pExpression);
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-9])),*(yyvsp[-7].s),ptd->typeexpr,*(yyvsp[-5].s),*(yyvsp[-3].s));
                delete (yyvsp[-1].pExpression);
            } else {
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-9])),*(yyvsp[-7].s),(yyvsp[-1].pExpression),*(yyvsp[-5].s),*(yyvsp[-3].s));
            }
            delete (yyvsp[-7].s);
            delete (yyvsp[-5].s);
            delete (yyvsp[-3].s);
    }
    break;

  case 404: /* expr_type_info: "typeinfo" name_in_namespace '(' expr ')'  */
                                                                          {
            if ( (yyvsp[-1].pExpression)->rtti_isTypeDecl() ) {
                auto ptd = (ExprTypeDecl *)(yyvsp[-1].pExpression);
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-4])),*(yyvsp[-3].s),ptd->typeexpr);
                delete (yyvsp[-1].pExpression);
            } else {
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-4])),*(yyvsp[-3].s),(yyvsp[-1].pExpression));
            }
            delete (yyvsp[-3].s);
    }
    break;

  case 405: /* expr_type_info: "typeinfo" name_in_namespace '<' "name" '>' '(' expr ')'  */
                                                                                                {
            if ( (yyvsp[-1].pExpression)->rtti_isTypeDecl() ) {
                auto ptd = (ExprTypeDecl *)(yyvsp[-1].pExpression);
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-7])),*(yyvsp[-6].s),ptd->typeexpr,*(yyvsp[-4].s));
                delete (yyvsp[-1].pExpression);
            } else {
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-7])),*(yyvsp[-6].s),(yyvsp[-1].pExpression),*(yyvsp[-4].s));
            }
            delete (yyvsp[-6].s);
            delete (yyvsp[-4].s);
    }
    break;

  case 406: /* expr_type_info: "typeinfo" name_in_namespace '<' "name" semicolon "name" '>' '(' expr ')'  */
                                                                                                                           {
            if ( (yyvsp[-1].pExpression)->rtti_isTypeDecl() ) {
                auto ptd = (ExprTypeDecl *)(yyvsp[-1].pExpression);
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-9])),*(yyvsp[-8].s),ptd->typeexpr,*(yyvsp[-6].s),*(yyvsp[-4].s));
                delete (yyvsp[-1].pExpression);
            } else {
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-9])),*(yyvsp[-8].s),(yyvsp[-1].pExpression),*(yyvsp[-6].s),*(yyvsp[-4].s));
            }
            delete (yyvsp[-8].s);
            delete (yyvsp[-6].s);
            delete (yyvsp[-4].s);
    }
    break;

  case 407: /* expr_list: expr2  */
                       {
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 408: /* expr_list: expr_list ',' expr2  */
                                             {
            (yyval.pExpression) = new ExprSequence(tokAt(scanner,(yylsp[-2])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
    }
    break;

  case 409: /* block_or_simple_block: expression_block  */
                                    { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 410: /* block_or_simple_block: "=>" expr  */
                                        {
            auto retE = new ExprReturn(tokAt(scanner,(yylsp[-1])), (yyvsp[0].pExpression));
            auto blkE = new ExprBlock();
            blkE->at = tokAt(scanner,(yylsp[-1]));
            blkE->list.push_back(retE);
            (yyval.pExpression) = blkE;
    }
    break;

  case 411: /* block_or_simple_block: "=>" "<-" expr  */
                                               {
            auto retE = new ExprReturn(tokAt(scanner,(yylsp[-2])), (yyvsp[0].pExpression));
            retE->moveSemantics = true;
            auto blkE = new ExprBlock();
            blkE->at = tokAt(scanner,(yylsp[-2]));
            blkE->list.push_back(retE);
            (yyval.pExpression) = blkE;
    }
    break;

  case 412: /* block_or_lambda: '$'  */
                { (yyval.i) = 0;   /* block */  }
    break;

  case 413: /* block_or_lambda: '@'  */
                { (yyval.i) = 1;   /* lambda */ }
    break;

  case 414: /* block_or_lambda: '@' '@'  */
                { (yyval.i) = 2;   /* local function */ }
    break;

  case 415: /* capture_entry: '&' "name"  */
                                    { (yyval.pCapt) = new CaptureEntry(*(yyvsp[0].s),CaptureMode::capture_by_reference); delete (yyvsp[0].s); }
    break;

  case 416: /* capture_entry: '=' "name"  */
                                    { (yyval.pCapt) = new CaptureEntry(*(yyvsp[0].s),CaptureMode::capture_by_copy); delete (yyvsp[0].s); }
    break;

  case 417: /* capture_entry: "<-" "name"  */
                                    { (yyval.pCapt) = new CaptureEntry(*(yyvsp[0].s),CaptureMode::capture_by_move); delete (yyvsp[0].s); }
    break;

  case 418: /* capture_entry: ":=" "name"  */
                                    { (yyval.pCapt) = new CaptureEntry(*(yyvsp[0].s),CaptureMode::capture_by_clone); delete (yyvsp[0].s); }
    break;

  case 419: /* capture_entry: "name" '(' "name" ')'  */
                                    { (yyval.pCapt) = ast_makeCaptureEntry(scanner,tokAt(scanner,(yylsp[-3])),*(yyvsp[-3].s),*(yyvsp[-1].s)); delete (yyvsp[-3].s); delete (yyvsp[-1].s); }
    break;

  case 420: /* capture_list: capture_entry  */
                         {
        (yyval.pCaptList) = new vector<CaptureEntry>();
        (yyval.pCaptList)->push_back(*(yyvsp[0].pCapt));
        delete (yyvsp[0].pCapt);
    }
    break;

  case 421: /* capture_list: capture_list ',' capture_entry  */
                                               {
        (yyvsp[-2].pCaptList)->push_back(*(yyvsp[0].pCapt));
        delete (yyvsp[0].pCapt);
        (yyval.pCaptList) = (yyvsp[-2].pCaptList);
    }
    break;

  case 422: /* optional_capture_list: %empty  */
        { (yyval.pCaptList) = nullptr; }
    break;

  case 423: /* optional_capture_list: "[[" capture_list ']' ']'  */
                                                              {
        if (format::prepare_rule(format::Pos::from(tokAt(scanner, (yylsp[-3]))))) {
            format::get_writer()
                      << "capture("
                      << format::substring_between(tokAt(scanner, (yylsp[-3])), tokAt(scanner, (yylsp[-2])))
                      << format::get_substring(tokAt(scanner, (yylsp[-2])))
                      << format::substring_between(tokAt(scanner, (yylsp[-2])), tokAt(scanner, (yylsp[-1])))
                      << ")";
            format::finish_rule(format::Pos::from_last(tokAt(scanner, (yylsp[0]))));
        }

         ; (yyval.pCaptList) = (yyvsp[-2].pCaptList);
    }
    break;

  case 424: /* optional_capture_list: "capture" '(' capture_list ')'  */
                                             { (yyval.pCaptList) = (yyvsp[-1].pCaptList); }
    break;

  case 425: /* expr_block: expression_block  */
                                            {
        if (format::is_replace_braces() && format::prepare_rule(format::Pos::from(tokAt(scanner, (yylsp[0]))))) {
            format::get_writer() << "$() ";
            format::finish_rule(format::Pos::from(tokAt(scanner, (yylsp[0]))));
        }

        ExprBlock * closure = (ExprBlock *) (yyvsp[0].pExpression);
        (yyval.pExpression) = new ExprMakeBlock(tokAt(scanner,(yylsp[0])),(yyvsp[0].pExpression));
        closure->returnType = new TypeDecl(Type::autoinfer);
    }
    break;

  case 426: /* expr_block: block_or_lambda optional_annotation_list optional_capture_list optional_function_argument_list optional_function_type block_or_simple_block  */
                                                                                            {
        (yyval.pExpression) = ast_makeBlock(scanner,(yyvsp[-5].i),(yyvsp[-4].faList),(yyvsp[-3].pCaptList),(yyvsp[-2].pVarDeclList),(yyvsp[-1].pTypeDecl),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[0])),tokAt(scanner,(yylsp[-4])),tokAt(scanner,(yylsp[-3])));
    }
    break;

  case 427: /* expr_full_block: block_or_lambda optional_annotation_list optional_capture_list optional_function_argument_list optional_function_type block_or_simple_block  */
                                                                                            {
        (yyval.pExpression) = ast_makeBlock(scanner,(yyvsp[-5].i),(yyvsp[-4].faList),(yyvsp[-3].pCaptList),(yyvsp[-2].pVarDeclList),(yyvsp[-1].pTypeDecl),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[0])),tokAt(scanner,(yylsp[-4])),tokAt(scanner,(yylsp[-3])));
    }
    break;

  case 428: /* $@24: %empty  */
                             {  yyextra->das_need_oxford_comma = false; }
    break;

  case 429: /* expr_full_block_assumed_piped: block_or_lambda $@24 optional_annotation_list optional_capture_list optional_function_argument_list optional_function_type expression_block  */
                                                                                       {
        (yyval.pExpression) = ast_makeBlock(scanner,(yyvsp[-6].i),(yyvsp[-4].faList),(yyvsp[-3].pCaptList),(yyvsp[-2].pVarDeclList),(yyvsp[-1].pTypeDecl),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[0])),tokAt(scanner,(yylsp[-4])),tokAt(scanner,(yylsp[-3])));
    }
    break;

  case 430: /* expr_numeric_const: "integer constant"  */
                                              { (yyval.pExpression) = new ExprConstInt(tokAt(scanner,(yylsp[0])),(int32_t)(yyvsp[0].i)); }
    break;

  case 431: /* expr_numeric_const: "unsigned integer constant"  */
                                              { (yyval.pExpression) = new ExprConstUInt(tokAt(scanner,(yylsp[0])),(uint32_t)(yyvsp[0].ui)); }
    break;

  case 432: /* expr_numeric_const: "long integer constant"  */
                                              { (yyval.pExpression) = new ExprConstInt64(tokAt(scanner,(yylsp[0])),(int64_t)(yyvsp[0].i64)); }
    break;

  case 433: /* expr_numeric_const: "unsigned long integer constant"  */
                                              { (yyval.pExpression) = new ExprConstUInt64(tokAt(scanner,(yylsp[0])),(uint64_t)(yyvsp[0].ui64)); }
    break;

  case 434: /* expr_numeric_const: "unsigned int8 constant"  */
                                              { (yyval.pExpression) = new ExprConstUInt8(tokAt(scanner,(yylsp[0])),(uint8_t)(yyvsp[0].ui)); }
    break;

  case 435: /* expr_numeric_const: "floating point constant"  */
                                              { (yyval.pExpression) = new ExprConstFloat(tokAt(scanner,(yylsp[0])),(float)(yyvsp[0].fd)); }
    break;

  case 436: /* expr_numeric_const: "double constant"  */
                                              { (yyval.pExpression) = new ExprConstDouble(tokAt(scanner,(yylsp[0])),(double)(yyvsp[0].d)); }
    break;

  case 437: /* expr_assign: expr  */
                                             { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 438: /* expr_assign: expr '=' expr  */
                                             { (yyval.pExpression) = new ExprCopy(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression)); }
    break;

  case 439: /* expr_assign: expr "<-" expr  */
                                             { (yyval.pExpression) = new ExprMove(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 440: /* expr_assign: expr ":=" expr  */
                                             { (yyval.pExpression) = new ExprClone(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 441: /* expr_assign: expr "&=" expr  */
                                             { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"&=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 442: /* expr_assign: expr "|=" expr  */
                                             { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"|=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 443: /* expr_assign: expr "^=" expr  */
                                             { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"^=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 444: /* expr_assign: expr "&&=" expr  */
                                                { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"&&=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 445: /* expr_assign: expr "||=" expr  */
                                                { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"||=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 446: /* expr_assign: expr "^^=" expr  */
                                                { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"^^=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 447: /* expr_assign: expr "+=" expr  */
                                             { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"+=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 448: /* expr_assign: expr "-=" expr  */
                                             { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"-=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 449: /* expr_assign: expr "*=" expr  */
                                             { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"*=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 450: /* expr_assign: expr "/=" expr  */
                                             { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"/=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 451: /* expr_assign: expr "%=" expr  */
                                             { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"%=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 452: /* expr_assign: expr "<<=" expr  */
                                             { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<<=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 453: /* expr_assign: expr ">>=" expr  */
                                             { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">>=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 454: /* expr_assign: expr "<<<=" expr  */
                                             { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<<<=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 455: /* expr_assign: expr ">>>=" expr  */
                                             { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">>>=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 456: /* expr_assign_pipe_right: "@ <|" expr_block  */
                                         {
            if (format::is_replace_braces() && format::prepare_rule(format::Pos::from(tokAt(scanner, (yylsp[-1]))))) {
                auto tok = tokAt(scanner, (yylsp[0]));
                tok.column += 1;
                format::get_writer() << "@" << format::get_substring(tok) << ";";
                format::finish_rule(format::Pos::from_last(tok));
            }

            (yyval.pExpression) = (yyvsp[0].pExpression);
        }
    break;

  case 457: /* expr_assign_pipe_right: "@@ <|" expr_block  */
                                         {
            if (format::is_replace_braces() && format::prepare_rule(format::Pos::from(tokAt(scanner, (yylsp[-1]))))) {
                auto tok = tokAt(scanner, (yylsp[0]));
                tok.column += 1;
                format::get_writer() << "@@" << format::get_substring(tok) << ";";
                format::finish_rule(format::Pos::from_last(tok));
            }
            (yyval.pExpression) = (yyvsp[0].pExpression);
        }
    break;

  case 458: /* expr_assign_pipe_right: "$ <|" expr_block  */
                                         {
            if (format::is_replace_braces() && format::prepare_rule(format::Pos::from(tokAt(scanner, (yylsp[-1]))))) {
                auto tok = tokAt(scanner, (yylsp[0]));
                tok.column += 1;
                format::get_writer() << "$" << format::get_substring(tok) << ";";
                format::finish_rule(format::Pos::from_last(tok));
            }
            (yyval.pExpression) = (yyvsp[0].pExpression);
        }
    break;

  case 459: /* expr_assign_pipe_right: expr_call_pipe  */
                                   { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 460: /* expr_assign_pipe: expr '=' expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprCopy(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression)); }
    break;

  case 461: /* expr_assign_pipe: expr "<-" expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprMove(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression)); }
    break;

  case 462: /* expr_assign_pipe: expr "&=" expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"&=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 463: /* expr_assign_pipe: expr "|=" expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"|=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 464: /* expr_assign_pipe: expr "^=" expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"^=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 465: /* expr_assign_pipe: expr "&&=" expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"&&=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 466: /* expr_assign_pipe: expr "||=" expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"||=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 467: /* expr_assign_pipe: expr "^^=" expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"^^=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 468: /* expr_assign_pipe: expr "+=" expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"+=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 469: /* expr_assign_pipe: expr "-=" expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"-=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 470: /* expr_assign_pipe: expr "*=" expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"*=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 471: /* expr_assign_pipe: expr "/=" expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"/=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 472: /* expr_assign_pipe: expr "%=" expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"%=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 473: /* expr_assign_pipe: expr "<<=" expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<<=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 474: /* expr_assign_pipe: expr ">>=" expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">>=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 475: /* expr_assign_pipe: expr "<<<=" expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<<<=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 476: /* expr_assign_pipe: expr ">>>=" expr_assign_pipe_right  */
                                                                  { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">>>=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 477: /* expr_named_call: name_in_namespace '(' '[' make_struct_fields ']' ')'  */
                                                                         {
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-5])),*(yyvsp[-5].s));
        nc->arguments = (yyvsp[-2].pMakeStruct);
        delete (yyvsp[-5].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 478: /* expr_named_call: name_in_namespace '(' expr_list ',' '[' make_struct_fields ']' ')'  */
                                                                                                  {
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-7])),*(yyvsp[-7].s));
        nc->nonNamedArguments = sequenceToList((yyvsp[-5].pExpression));
        nc->arguments = (yyvsp[-2].pMakeStruct);
        delete (yyvsp[-7].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 479: /* expr_method_call: expr2 "->" "name" '(' ')'  */
                                                          {
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-3])), (yyvsp[-4].pExpression), *(yyvsp[-2].s));
        delete (yyvsp[-2].s);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 480: /* expr_method_call: expr2 "->" "name" '(' expr_list ')'  */
                                                                               {
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-4])), (yyvsp[-5].pExpression), *(yyvsp[-3].s));
        auto callArgs = sequenceToList((yyvsp[-1].pExpression));
        pInvoke->arguments.insert ( pInvoke->arguments.end(), callArgs.begin(), callArgs.end() );
        delete (yyvsp[-3].s);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 481: /* func_addr_name: name_in_namespace  */
                                    {
        (yyval.pExpression) = new ExprAddr(tokAt(scanner,(yylsp[0])),*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 482: /* func_addr_name: "$i" '(' expr2 ')'  */
                                           {
        auto expr = new ExprAddr(tokAt(scanner,(yylsp[-3])),"``MACRO``TAG``ADDR``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression), expr, "i");
    }
    break;

  case 483: /* func_addr_expr: '@' '@' func_addr_name  */
                                          {
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 484: /* $@25: %empty  */
                    { yyextra->das_arrow_depth ++; }
    break;

  case 485: /* $@26: %empty  */
                                                                                                { yyextra->das_arrow_depth --; }
    break;

  case 486: /* func_addr_expr: '@' '@' '<' $@25 type_declaration_no_options '>' $@26 func_addr_name  */
                                                                                                                                                       {
        auto expr = (ExprAddr *) ((yyvsp[0].pExpression)->rtti_isAddr() ? (yyvsp[0].pExpression) : (((ExprTag *) (yyvsp[0].pExpression))->value));
        expr->funcType = (yyvsp[-3].pTypeDecl);
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 487: /* $@27: %empty  */
                    { yyextra->das_arrow_depth ++; }
    break;

  case 488: /* $@28: %empty  */
                                                                                                                              { yyextra->das_arrow_depth --; }
    break;

  case 489: /* func_addr_expr: '@' '@' '<' $@27 optional_function_argument_list optional_function_type '>' $@28 func_addr_name  */
                                                                                                                                                                                     {
        auto expr = (ExprAddr *) ((yyvsp[0].pExpression)->rtti_isAddr() ? (yyvsp[0].pExpression) : (((ExprTag *) (yyvsp[0].pExpression))->value));
        expr->funcType = new TypeDecl(Type::tFunction);
        expr->funcType->firstType = (yyvsp[-3].pTypeDecl);
        if ( (yyvsp[-4].pVarDeclList) ) {
            varDeclToTypeDecl(scanner, expr->funcType, (yyvsp[-4].pVarDeclList));
            deleteVariableDeclarationList((yyvsp[-4].pVarDeclList));
        }
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 490: /* expr_field: expr2 '.' "name"  */
                                               {
        (yyval.pExpression) = new ExprField(tokAt(scanner,(yylsp[-1])), tokAt(scanner,(yylsp[0])), (yyvsp[-2].pExpression), *(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 491: /* expr_field: expr2 '.' '.' "name"  */
                                                   {
        (yyval.pExpression) = new ExprField(tokAt(scanner,(yylsp[-1])), tokAt(scanner,(yylsp[0])), (yyvsp[-3].pExpression), *(yyvsp[0].s), true);
        delete (yyvsp[0].s);
    }
    break;

  case 492: /* expr_field: expr2 '.' "name" '(' ')'  */
                                                       {
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-3])), (yyvsp[-4].pExpression), *(yyvsp[-2].s));
        delete (yyvsp[-2].s);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 493: /* expr_field: expr2 '.' "name" '(' expr_list ')'  */
                                                                            {
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-4])), (yyvsp[-5].pExpression), *(yyvsp[-3].s));
        auto callArgs = sequenceToList((yyvsp[-1].pExpression));
        pInvoke->arguments.insert ( pInvoke->arguments.end(), callArgs.begin(), callArgs.end() );
        delete (yyvsp[-3].s);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 494: /* expr_field: expr2 '.' "name" '(' '[' make_struct_fields ']' ')'  */
                                                                                        {
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-5])),*(yyvsp[-5].s));
        nc->methodCall = true;
        nc->arguments = (yyvsp[-2].pMakeStruct);
        nc->nonNamedArguments.push_back((yyvsp[-7].pExpression));
        delete (yyvsp[-5].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 495: /* expr_field: expr2 '.' basic_type_declaration '(' ')'  */
                                                                         {
        auto method_name = das_to_string((yyvsp[-2].type));
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-3])), (yyvsp[-4].pExpression), method_name);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 496: /* expr_field: expr2 '.' basic_type_declaration '(' expr_list ')'  */
                                                                                              {
        auto method_name = das_to_string((yyvsp[-3].type));
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-4])), (yyvsp[-5].pExpression), method_name);
        auto callArgs = sequenceToList((yyvsp[-1].pExpression));
        pInvoke->arguments.insert ( pInvoke->arguments.end(), callArgs.begin(), callArgs.end() );
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 497: /* $@29: %empty  */
                                { yyextra->das_suppress_errors=true; }
    break;

  case 498: /* $@30: %empty  */
                                                                             { yyextra->das_suppress_errors=false; }
    break;

  case 499: /* expr_field: expr2 '.' $@29 error $@30  */
                                                                                                                     {
        (yyval.pExpression) = new ExprField(tokAt(scanner,(yylsp[-3])), tokAt(scanner,(yylsp[-3])), (yyvsp[-4].pExpression), "");
        yyerrok;
    }
    break;

  case 500: /* expr_call: name_in_namespace '(' ')'  */
                                               {
            (yyval.pExpression) = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-2])),tokAt(scanner,(yylsp[0])),*(yyvsp[-2].s));
            delete (yyvsp[-2].s);
    }
    break;

  case 501: /* expr_call: name_in_namespace '(' "uninitialized" ')'  */
                                                          {
            auto dd = new ExprMakeStruct(tokAt(scanner,(yylsp[-3])));
            dd->at = tokAt(scanner,(yylsp[-3]));
            dd->makeType = new TypeDecl(Type::alias);
            dd->makeType->alias = *(yyvsp[-3].s);
            dd->useInitializer = false;
            dd->alwaysUseInitializer = true;
            delete (yyvsp[-3].s);
            (yyval.pExpression) = dd;
    }
    break;

  case 502: /* expr_call: name_in_namespace '(' make_struct_single ')'  */
                                                               {
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->at = tokAt(scanner,(yylsp[-3]));
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = new TypeDecl(Type::alias);
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType->alias = *(yyvsp[-3].s);
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = true;
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
            delete (yyvsp[-3].s);
            (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 503: /* expr_call: name_in_namespace '(' "uninitialized" make_struct_single ')'  */
                                                                                 {
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->at = tokAt(scanner,(yylsp[-4]));
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = new TypeDecl(Type::alias);
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType->alias = *(yyvsp[-4].s);
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = false;
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
            delete (yyvsp[-4].s);
            (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 504: /* expr_call: name_in_namespace '(' expr_list ')'  */
                                                                    {
            (yyval.pExpression) = parseFunctionArguments(yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-3])),tokAt(scanner,(yylsp[0])),*(yyvsp[-3].s)),(yyvsp[-1].pExpression));
            delete (yyvsp[-3].s);
    }
    break;

  case 505: /* expr_call: basic_type_declaration '(' ')'  */
                                                    {
        (yyval.pExpression) = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-2])),tokAt(scanner,(yylsp[0])),das_to_string((yyvsp[-2].type)));
    }
    break;

  case 506: /* expr_call: basic_type_declaration '(' expr_list ')'  */
                                                                         {
        (yyval.pExpression) = parseFunctionArguments(yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-3])),tokAt(scanner,(yylsp[0])),das_to_string((yyvsp[-3].type))),(yyvsp[-1].pExpression));
    }
    break;

  case 507: /* expr2: name_in_namespace  */
                                              { need_wrap_current_expr = true; (yyval.pExpression) = new ExprVar(tokAt(scanner,(yylsp[0])),*(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 508: /* expr2: expr_field  */
                                              { need_wrap_current_expr = true; (yyvsp[0].pExpression)->at = tokAt(scanner,(yylsp[0])); (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 509: /* expr2: expr_mtag  */
                                              { need_wrap_current_expr = true; (yyvsp[0].pExpression)->at = tokAt(scanner,(yylsp[0])); (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 510: /* expr2: '!' expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp1(tokRangeAt(scanner,(yylsp[-1]), (yylsp[0])),"!",(yyvsp[0].pExpression)); }
    break;

  case 511: /* expr2: '~' expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp1(tokRangeAt(scanner,(yylsp[-1]), (yylsp[0])),"~",(yyvsp[0].pExpression)); }
    break;

  case 512: /* expr2: '+' expr2  */
                                                   { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp1(tokRangeAt(scanner,(yylsp[-1]), (yylsp[0])),"+",(yyvsp[0].pExpression)); }
    break;

  case 513: /* expr2: '-' expr2  */
                                                   { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp1(tokRangeAt(scanner,(yylsp[-1]), (yylsp[0])),"-",(yyvsp[0].pExpression)); }
    break;

  case 514: /* expr2: expr2 "<<" expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"<<", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 515: /* expr2: expr2 ">>" expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),">>", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 516: /* expr2: expr2 "<<<" expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"<<<", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 517: /* expr2: expr2 ">>>" expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),">>>", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 518: /* expr2: expr2 '+' expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"+", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 519: /* expr2: expr2 '-' expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"-", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 520: /* expr2: expr2 '*' expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"*", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 521: /* expr2: expr2 '/' expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"/", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 522: /* expr2: expr2 '%' expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"%", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 523: /* expr2: expr2 '<' expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"<", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 524: /* expr2: expr2 '>' expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),">", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 525: /* expr2: expr2 "==" expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"==", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 526: /* expr2: expr2 "!=" expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"!=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 527: /* expr2: expr2 "<=" expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"<=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 528: /* expr2: expr2 ">=" expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),">=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 529: /* expr2: expr2 '&' expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"&", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 530: /* expr2: expr2 '|' expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"|", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 531: /* expr2: expr2 '^' expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"^", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 532: /* expr2: expr2 "&&" expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"&&", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 533: /* expr2: expr2 "||" expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"||", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 534: /* expr2: expr2 "^^" expr2  */
                                               { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp2(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),"^^", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 535: /* expr2: expr2 ".." expr2  */
                                               {
        need_wrap_current_expr = true;
        auto itv = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-1])),"interval");
        itv->arguments.push_back((yyvsp[-2].pExpression));
        itv->arguments.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = itv;
    }
    break;

  case 536: /* expr2: "++" expr2  */
                                                            { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp1(tokRangeAt(scanner,(yylsp[-1]), (yylsp[0])),"++", (yyvsp[0].pExpression)); }
    break;

  case 537: /* expr2: "--" expr2  */
                                                            { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp1(tokRangeAt(scanner,(yylsp[-1]), (yylsp[0])),"--", (yyvsp[0].pExpression)); }
    break;

  case 538: /* expr2: expr2 "++"  */
                                                            { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp1(tokRangeAt(scanner,(yylsp[-1]), (yylsp[0])),"+++", (yyvsp[-1].pExpression)); }
    break;

  case 539: /* expr2: expr2 "--"  */
                                                            { need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp1(tokRangeAt(scanner,(yylsp[-1]), (yylsp[0])),"---", (yyvsp[-1].pExpression)); }
    break;

  case 540: /* expr2: expr2 '[' expr2 ']'  */
                                                            { need_wrap_current_expr = true; (yyval.pExpression) = new ExprAt(tokRangeAt(scanner,(yylsp[-3]), (yylsp[0])), (yyvsp[-3].pExpression), (yyvsp[-1].pExpression)); }
    break;

  case 541: /* expr2: expr2 '.' '[' expr2 ']'  */
                                                            { need_wrap_current_expr = true; (yyval.pExpression) = new ExprAt(tokRangeAt(scanner,(yylsp[-4]), (yylsp[0])), (yyvsp[-4].pExpression), (yyvsp[-1].pExpression), true); }
    break;

  case 542: /* expr2: expr2 "?[" expr2 ']'  */
                                                            { need_wrap_current_expr = true; (yyval.pExpression) = new ExprSafeAt(tokRangeAt(scanner,(yylsp[-3]), (yylsp[0])), (yyvsp[-3].pExpression), (yyvsp[-1].pExpression)); }
    break;

  case 543: /* expr2: expr2 '.' "?[" expr2 ']'  */
                                                            { need_wrap_current_expr = true; (yyval.pExpression) = new ExprSafeAt(tokRangeAt(scanner,(yylsp[-4]), (yylsp[0])), (yyvsp[-4].pExpression), (yyvsp[-1].pExpression), true); }
    break;

  case 544: /* expr2: expr2 "?." "name"  */
                                                            { need_wrap_current_expr = true; (yyval.pExpression) = new ExprSafeField(tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])), tokAt(scanner,(yylsp[0])), (yyvsp[-2].pExpression), *(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 545: /* expr2: expr2 '.' "?." "name"  */
                                                            { need_wrap_current_expr = true; (yyval.pExpression) = new ExprSafeField(tokRangeAt(scanner,(yylsp[-3]),(yylsp[0])), tokAt(scanner,(yylsp[0])), (yyvsp[-3].pExpression), *(yyvsp[0].s), true); delete (yyvsp[0].s); }
    break;

  case 546: /* expr2: '*' expr2  */
                                                            { need_wrap_current_expr = true; (yyval.pExpression) = new ExprPtr2Ref(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression)); }
    break;

  case 547: /* expr2: expr2 '?' expr2 ':' expr2  */
                                                             {
        need_wrap_current_expr = true; (yyval.pExpression) = new ExprOp3(tokRangeAt(scanner,(yylsp[-4]), (yylsp[0])),"?",(yyvsp[-4].pExpression),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
    }
    break;

  case 548: /* expr2: "null"  */
                                              { (yyval.pExpression) = new ExprConstPtr(tokAt(scanner,(yylsp[0])),nullptr); }
    break;

  case 549: /* expr2: expr_numeric_const  */
                                              { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 550: /* expr2: expr_reader  */
                                              { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 551: /* expr2: string_builder  */
                                              { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 552: /* expr2: make_decl  */
                                              { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 553: /* expr2: "true"  */
                                              { (yyval.pExpression) = new ExprConstBool(tokAt(scanner,(yylsp[0])),true); }
    break;

  case 554: /* expr2: "false"  */
                                              { (yyval.pExpression) = new ExprConstBool(tokAt(scanner,(yylsp[0])),false); }
    break;

  case 555: /* expr2: '(' expr_list optional_comma ')'  */
                                                         {
            if ( (yyvsp[-2].pExpression)->rtti_isSequence() ) {
                auto mkt = new ExprMakeTuple(tokAt(scanner,(yylsp[-2])));
                mkt->values = sequenceToList((yyvsp[-2].pExpression));
                mkt->shorthandRecordNames = ast_tupleCollectShorthandNames(mkt->values);
                (yyval.pExpression) = mkt;
            } else if ( (yyvsp[-1].b) ) {
                auto mkt = new ExprMakeTuple(tokAt(scanner,(yylsp[-2])));
                mkt->values.push_back((yyvsp[-2].pExpression));
                mkt->shorthandRecordNames = ast_tupleCollectShorthandNames(mkt->values);
                (yyval.pExpression) = mkt;
            } else {
                (yyvsp[-2].pExpression)->at = tokAt(scanner, (yylsp[-2]));
                (yyval.pExpression) = (yyvsp[-2].pExpression);
            }
        }
    break;

  case 556: /* expr2: func_addr_expr  */
                                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 557: /* expr2: expr_call  */
                        { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 558: /* expr2: "deref" '(' expr2 ')'  */
                                                    { (yyval.pExpression) = new ExprPtr2Ref(tokAt(scanner,(yylsp[-3])),(yyvsp[-1].pExpression)); }
    break;

  case 559: /* expr2: "addr" '(' expr2 ')'  */
                                                    { (yyval.pExpression) = new ExprRef2Ptr(tokAt(scanner,(yylsp[-3])),(yyvsp[-1].pExpression)); }
    break;

  case 560: /* expr2: "generator" '<' type_declaration_no_options '>' optional_capture_list '(' ')'  */
                                                                                                              {
        (yyval.pExpression) = ast_makeGenerator(scanner,(yyvsp[-4].pTypeDecl),(yyvsp[-2].pCaptList),nullptr,tokAt(scanner,(yylsp[-6])),tokAt(scanner,(yylsp[-2])));
    }
    break;

  case 561: /* expr2: "generator" '<' type_declaration_no_options '>' optional_capture_list '(' expr2 ')'  */
                                                                                                                             {
        (yyval.pExpression) = ast_makeGenerator(scanner,(yyvsp[-5].pTypeDecl),(yyvsp[-3].pCaptList),(yyvsp[-1].pExpression),tokAt(scanner,(yylsp[-7])),tokAt(scanner,(yylsp[-3])));
    }
    break;

  case 562: /* expr2: expr2 "??" expr2  */
                                                     { (yyval.pExpression) = new ExprNullCoalescing(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression)); }
    break;

  case 563: /* $@31: %empty  */
                                                { yyextra->das_arrow_depth ++; }
    break;

  case 564: /* $@32: %empty  */
                                                                                                                            { yyextra->das_arrow_depth --; }
    break;

  case 565: /* expr2: expr2 "is" "type" '<' $@31 type_declaration_no_options '>' $@32  */
                                                                                                                                                             {
        (yyval.pExpression) = new ExprIs(tokRangeAt(scanner,(yylsp[-7]), (yylsp[-1])),(yyvsp[-7].pExpression),(yyvsp[-2].pTypeDecl));
    }
    break;

  case 566: /* expr2: expr2 "is" basic_type_declaration  */
                                                                {
        auto vdecl = new TypeDecl((yyvsp[0].type));
        vdecl->at = tokAt(scanner,(yylsp[0]));
        (yyval.pExpression) = new ExprIs(tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),(yyvsp[-2].pExpression),vdecl);
    }
    break;

  case 567: /* expr2: expr2 "is" "name"  */
                                               {
        (yyval.pExpression) = new ExprIsVariant(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),(yyvsp[-2].pExpression),*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 568: /* expr2: expr2 "as" "name"  */
                                               {
        (yyval.pExpression) = new ExprAsVariant(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),(yyvsp[-2].pExpression),*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 569: /* $@33: %empty  */
                                                { yyextra->das_arrow_depth ++; }
    break;

  case 570: /* $@34: %empty  */
                                                                                                                 { yyextra->das_arrow_depth --; }
    break;

  case 571: /* expr2: expr2 "as" "type" '<' $@33 type_declaration '>' $@34  */
                                                                                                                                                  {
        auto vname = (yyvsp[-2].pTypeDecl)->describe();
        (yyval.pExpression) = new ExprAsVariant(tokRangeAt(scanner,(yylsp[-7]), (yylsp[-1])),(yyvsp[-7].pExpression),vname);
        delete (yyvsp[-2].pTypeDecl);
    }
    break;

  case 572: /* expr2: expr2 "as" basic_type_declaration  */
                                                                {
        (yyval.pExpression) = new ExprAsVariant(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),(yyvsp[-2].pExpression),das_to_string((yyvsp[0].type)));
    }
    break;

  case 573: /* expr2: expr2 '?' "as" "name"  */
                                                   {
        (yyval.pExpression) = new ExprSafeAsVariant(tokRangeAt(scanner,(yylsp[-3]), (yylsp[0])),(yyvsp[-3].pExpression),*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 574: /* $@35: %empty  */
                                                    { yyextra->das_arrow_depth ++; }
    break;

  case 575: /* $@36: %empty  */
                                                                                                                     { yyextra->das_arrow_depth --; }
    break;

  case 576: /* expr2: expr2 '?' "as" "type" '<' $@35 type_declaration '>' $@36  */
                                                                                                                                                      {
        auto vname = (yyvsp[-2].pTypeDecl)->describe();
        (yyval.pExpression) = new ExprSafeAsVariant(tokRangeAt(scanner,(yylsp[-8]), (yylsp[-1])),(yyvsp[-8].pExpression),vname);
        delete (yyvsp[-2].pTypeDecl);
    }
    break;

  case 577: /* expr2: expr2 '?' "as" basic_type_declaration  */
                                                                    {
        (yyval.pExpression) = new ExprSafeAsVariant(tokRangeAt(scanner,(yylsp[-3]), (yylsp[0])),(yyvsp[-3].pExpression),das_to_string((yyvsp[0].type)));
    }
    break;

  case 578: /* expr2: expr_type_info  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 579: /* expr2: expr_type_decl  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 580: /* expr2: expr_cast  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 581: /* expr2: expr_new  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 582: /* expr2: expr_method_call  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); (yyval.pExpression)->at = tokAt(scanner, (yylsp[0])); }
    break;

  case 583: /* expr2: expr_named_call  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 584: /* expr2: expr_full_block  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 585: /* expr2: expr2 "<|" expr2  */
                                                  { (yyval.pExpression) = ast_lpipe(scanner,(yyvsp[-2].pExpression),(yyvsp[0].pExpression),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0]))); }
    break;

  case 586: /* expr2: expr2 "|>" expr2  */
                                                  { (yyval.pExpression) = ast_rpipe(scanner,(yyvsp[-2].pExpression),(yyvsp[0].pExpression),tokRangeAt(scanner,(yylsp[-2]), (yylsp[0]))); (yyval.pExpression)->at = tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])); }
    break;

  case 587: /* expr2: expr2 "|>" basic_type_declaration  */
                                                           {
        auto fncall = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[0])),tokAt(scanner,(yylsp[0])),das_to_string((yyvsp[0].type)));
        (yyval.pExpression) = ast_rpipe(scanner,(yyvsp[-2].pExpression),fncall,tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])));
    }
    break;

  case 588: /* expr2: name_in_namespace "name"  */
                                                  {
        if (format::prepare_rule(format::Pos::from_last(tokAt(scanner,(yylsp[-1]))))) {
            format::get_writer() << "." << format::get_substring(tokAt(scanner,(yylsp[0])));
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[0]))));
        }

        (yyval.pExpression) = ast_NameName(scanner,(yyvsp[-1].s),(yyvsp[0].s),tokRangeAt(scanner,(yylsp[-1]),(yylsp[0])),tokAt(scanner,(yylsp[0])));
    }
    break;

  case 589: /* expr2: "unsafe" '(' expr2 ')'  */
                                          {
        (yyvsp[-1].pExpression)->alwaysSafe = true;
        (yyvsp[-1].pExpression)->userSaidItsSafe = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 590: /* expr2: expression_keyword  */
                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 591: /* expr: expr2  */
                                       {
        if (need_wrap_current_expr) {
            format::wrap_par_expr_newline(tokAt(scanner,(yylsp[0])), (yyvsp[0].pExpression)->at);
            need_wrap_current_expr = false;
        }
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 592: /* expr_mtag: "$$" '(' expr2 ')'  */
                                                      { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"e"); }
    break;

  case 593: /* expr_mtag: "$i" '(' expr2 ')'  */
                                                      { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"i"); }
    break;

  case 594: /* expr_mtag: "$v" '(' expr2 ')'  */
                                                      { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"v"); }
    break;

  case 595: /* expr_mtag: "$b" '(' expr2 ')'  */
                                                      { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"b"); }
    break;

  case 596: /* expr_mtag: "$a" '(' expr2 ')'  */
                                                      { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"a"); }
    break;

  case 597: /* expr_mtag: "..."  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[0])),nullptr,"..."); }
    break;

  case 598: /* expr_mtag: "$c" '(' expr2 ')' '(' ')'  */
                                                             {
            auto ccall = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-5])),tokAt(scanner,(yylsp[0])),"``MACRO``TAG``CALL``");
            (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-5])),(yyvsp[-3].pExpression),ccall,"c");
        }
    break;

  case 599: /* expr_mtag: "$c" '(' expr2 ')' '(' expr_list ')'  */
                                                                                 {
            auto ccall = parseFunctionArguments(yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-6])),tokAt(scanner,(yylsp[0])),"``MACRO``TAG``CALL``"),(yyvsp[-1].pExpression));
            (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-6])),(yyvsp[-4].pExpression),ccall,"c");
        }
    break;

  case 600: /* expr_mtag: expr2 '.' "$f" '(' expr2 ')'  */
                                                                  {
        auto cfield = new ExprField(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-1])), (yyvsp[-5].pExpression), "``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 601: /* expr_mtag: expr2 "?." "$f" '(' expr2 ')'  */
                                                                   {
        auto cfield = new ExprSafeField(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-1])), (yyvsp[-5].pExpression), "``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 602: /* expr_mtag: expr2 '.' '.' "$f" '(' expr2 ')'  */
                                                                      {
        auto cfield = new ExprField(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-1])), (yyvsp[-6].pExpression), "``MACRO``TAG``FIELD``", true);
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 603: /* expr_mtag: expr2 '.' "?." "$f" '(' expr2 ')'  */
                                                                       {
        auto cfield = new ExprSafeField(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-1])), (yyvsp[-6].pExpression), "``MACRO``TAG``FIELD``", true);
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 604: /* expr_mtag: expr2 "as" "$f" '(' expr2 ')'  */
                                                                     {
        auto cfield = new ExprAsVariant(tokAt(scanner,(yylsp[-4])),(yyvsp[-5].pExpression),"``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 605: /* expr_mtag: expr2 '?' "as" "$f" '(' expr2 ')'  */
                                                                         {
        auto cfield = new ExprSafeAsVariant(tokAt(scanner,(yylsp[-4])),(yyvsp[-6].pExpression),"``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 606: /* expr_mtag: expr2 "is" "$f" '(' expr2 ')'  */
                                                                     {
        auto cfield = new ExprIsVariant(tokAt(scanner,(yylsp[-4])),(yyvsp[-5].pExpression),"``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 607: /* expr_mtag: '@' '@' "$c" '(' expr2 ')'  */
                                                          {
        auto ccall = new ExprAddr(tokAt(scanner,(yylsp[-4])),"``MACRO``TAG``ADDR``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-3])),(yyvsp[-1].pExpression),ccall,"c");
    }
    break;

  case 608: /* optional_field_annotation: %empty  */
                                                        { (yyval.aaList) = nullptr; }
    break;

  case 609: /* optional_field_annotation: "[[" annotation_argument_list ']' ']'  */
                                                                     {
        if (format::prepare_rule(format::Pos::from(tokAt(scanner, (yylsp[-3]))))) {
            for (const auto &arg: *(yyvsp[-2].aaList)) {
                format::get_writer() << "@" << format::get_substring(arg.at);
            }
            format::finish_rule(format::Pos::from_last(tokAt(scanner, (yylsp[0]))));
        }
        (yyval.aaList) = (yyvsp[-2].aaList); /*this one is gone when BRABRA is disabled*/
    }
    break;

  case 610: /* optional_field_annotation: metadata_argument_list  */
                                                        { (yyval.aaList) = (yyvsp[0].aaList); }
    break;

  case 611: /* optional_override: %empty  */
                      { (yyval.i) = OVERRIDE_NONE; }
    break;

  case 612: /* optional_override: "override"  */
                      { (yyval.i) = OVERRIDE_OVERRIDE; }
    break;

  case 613: /* optional_override: "sealed"  */
                      { (yyval.i) = OVERRIDE_SEALED; }
    break;

  case 614: /* optional_constant: %empty  */
                        { (yyval.b) = false; }
    break;

  case 615: /* optional_constant: "const"  */
                        { (yyval.b) = true; }
    break;

  case 616: /* optional_public_or_private_member_variable: %empty  */
                        { (yyval.b) = false; }
    break;

  case 617: /* optional_public_or_private_member_variable: "public"  */
                        { (yyval.b) = false; }
    break;

  case 618: /* optional_public_or_private_member_variable: "private"  */
                        { (yyval.b) = true; }
    break;

  case 619: /* optional_static_member_variable: %empty  */
                        { (yyval.b) = false; }
    break;

  case 620: /* optional_static_member_variable: "static"  */
                        { (yyval.b) = true; }
    break;

  case 621: /* structure_variable_declaration: optional_field_annotation optional_static_member_variable optional_override optional_public_or_private_member_variable variable_declaration  */
                                                                                                                                                                                      {
        (yyvsp[0].pVarDecl)->override = (yyvsp[-2].i) == OVERRIDE_OVERRIDE;
        (yyvsp[0].pVarDecl)->sealed = (yyvsp[-2].i) == OVERRIDE_SEALED;
        (yyvsp[0].pVarDecl)->annotation = (yyvsp[-4].aaList);
        (yyvsp[0].pVarDecl)->isPrivate = (yyvsp[-1].b);
        (yyvsp[0].pVarDecl)->isStatic = (yyvsp[-3].b);
        (yyval.pVarDecl) = (yyvsp[0].pVarDecl);
    }
    break;

  case 622: /* opt_sem: SEMICOLON  */
                { (yyval.b) = false; }
    break;

  case 623: /* opt_sem: "end of expression"  */
          { (yyval.b) = true; }
    break;

  case 624: /* opt_sem: "end of expression" SEMICOLON  */
                    { (yyval.b) = true; }
    break;

  case 625: /* opt_sem: %empty  */
                  {(yyval.b) = false; }
    break;

  case 626: /* struct_variable_declaration_list: %empty  */
        {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 627: /* $@37: %empty  */
                                                               { yyextra->das_force_oxford_comma=true;}
    break;

  case 628: /* struct_variable_declaration_list: struct_variable_declaration_list "typedef" $@37 "name" '=' type_declaration semicolon opt_sem  */
                                                                                                                                                                 {
        (yyval.pVarDeclList) = (yyvsp[-7].pVarDeclList);
        ast_structureAlias(scanner,(yyvsp[-4].s),(yyvsp[-2].pTypeDecl),tokAt(scanner,(yylsp[-6])));
    }
    break;

  case 629: /* $@38: %empty  */
                                               {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeStructureFields(tak);
        }
    }
    break;

  case 630: /* struct_variable_declaration_list: struct_variable_declaration_list $@38 structure_variable_declaration semicolon opt_sem  */
                                                             {
        (yyval.pVarDeclList) = (yyvsp[-4].pVarDeclList);
        if ( (yyvsp[-2].pVarDecl) ) (yyvsp[-4].pVarDeclList)->push_back((yyvsp[-2].pVarDecl));
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-4]));
            for ( auto & crd : yyextra->g_CommentReaders ) {
                for ( const auto & nl : *((yyvsp[-2].pVarDecl)->pNameList) ) {
                    crd->afterStructureField(nl.name.c_str(), nl.at);
                }
            }
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterStructureFields(tak);
        }
    }
    break;

  case 631: /* $@39: %empty  */
                                                                                                                     {
                yyextra->das_force_oxford_comma=true;
                if ( !yyextra->g_CommentReaders.empty() ) {
                    auto tak = tokAt(scanner,(yylsp[-2]));
                    for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeFunction(tak);
                }
            }
    break;

  case 632: /* struct_variable_declaration_list: struct_variable_declaration_list optional_annotation_list "def" optional_public_or_private_member_variable "abstract" optional_constant $@39 function_declaration_header semicolon opt_sem  */
                                                                  {
                if ( !yyextra->g_CommentReaders.empty() ) {
                    auto tak = tokAt(scanner,(yylsp[-2]));
                    for ( auto & crd : yyextra->g_CommentReaders ) crd->afterFunction((yyvsp[-2].pFuncDecl),tak);
                }
                (yyvsp[-2].pFuncDecl)->isTemplate = yyextra->g_thisStructure->isTemplate;
                (yyval.pVarDeclList) = ast_structVarDefAbstract(scanner,(yyvsp[-9].pVarDeclList),(yyvsp[-8].faList),(yyvsp[-6].b),(yyvsp[-4].b), (yyvsp[-2].pFuncDecl));
            }
    break;

  case 633: /* $@40: %empty  */
                                                                                                                                                                         {
                if ( !yyextra->g_CommentReaders.empty() ) {
                    auto tak = tokAt(scanner,(yylsp[0]));
                    for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeFunction(tak);
                }
            }
    break;

  case 634: /* struct_variable_declaration_list: struct_variable_declaration_list optional_annotation_list "def" optional_public_or_private_member_variable optional_static_member_variable optional_override optional_constant $@40 function_declaration_header expression_block opt_sem  */
                                                                                {
                if ( !yyextra->g_CommentReaders.empty() ) {
                    auto tak = tokAt(scanner,(yylsp[-1]));
                    for ( auto & crd : yyextra->g_CommentReaders ) crd->afterFunction((yyvsp[-2].pFuncDecl),tak);
                }
                (yyvsp[-2].pFuncDecl)->isTemplate = yyextra->g_thisStructure->isTemplate;
                (yyval.pVarDeclList) = ast_structVarDef(scanner,(yyvsp[-10].pVarDeclList),(yyvsp[-9].faList),(yyvsp[-6].b),(yyvsp[-7].b),(yyvsp[-5].i),(yyvsp[-4].b),(yyvsp[-2].pFuncDecl),(yyvsp[-1].pExpression),tokRangeAt(scanner,(yylsp[-8]),(yylsp[-1])),tokAt(scanner,(yylsp[-9])));
            }
    break;

  case 635: /* struct_variable_declaration_list: struct_variable_declaration_list '[' annotation_list ']' semicolon opt_sem  */
                                                                                               {
        das_yyerror(scanner,"structure field or class method annotation expected to remain on the same line with the field or the class",
            tokAt(scanner,(yylsp[-3])), CompilationError::syntax_error);
        delete (yyvsp[-3].faList);
        (yyval.pVarDeclList) = (yyvsp[-5].pVarDeclList);
    }
    break;

  case 636: /* function_argument_declaration_no_type: optional_field_annotation kwd_let_var_or_nothing variable_declaration_no_type  */
                                                                                                          {
            (yyval.pVarDecl) = (yyvsp[0].pVarDecl);
            if ( (yyvsp[-1].b) ) {
                (yyvsp[0].pVarDecl)->pTypeDecl->constant = true;
            } else {
                (yyvsp[0].pVarDecl)->pTypeDecl->removeConstant = true;
            }
            (yyvsp[0].pVarDecl)->annotation = (yyvsp[-2].aaList);
        }
    break;

  case 637: /* function_argument_declaration_type: optional_field_annotation kwd_let_var_or_nothing variable_declaration_type  */
                                                                                                       {
            (yyval.pVarDecl) = (yyvsp[0].pVarDecl);
            if ( (yyvsp[-1].b) ) {
                (yyvsp[0].pVarDecl)->pTypeDecl->constant = true;
            } else {
                (yyvsp[0].pVarDecl)->pTypeDecl->removeConstant = true;
            }
            (yyvsp[0].pVarDecl)->annotation = (yyvsp[-2].aaList);
        }
    break;

  case 638: /* function_argument_declaration_type: "$a" '(' expr2 ')'  */
                                      {
            auto na = new vector<VariableNameAndPosition>();
            na->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1]))));
            auto decl = new VariableDeclaration(na, new TypeDecl(Type::none), (yyvsp[-1].pExpression));
            decl->pTypeDecl->isTag = true;
            (yyval.pVarDecl) = decl;
        }
    break;

  case 639: /* function_argument_list: function_argument_declaration_no_type  */
                                                                                      { (yyval.pVarDeclList) = new vector<VariableDeclaration*>(); (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 640: /* function_argument_list: function_argument_declaration_type  */
                                                                                      { (yyval.pVarDeclList) = new vector<VariableDeclaration*>(); (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 641: /* function_argument_list: function_argument_declaration_no_type "end of expression" function_argument_list  */
                                                                                      { (yyval.pVarDeclList) = (yyvsp[0].pVarDeclList); (yyvsp[0].pVarDeclList)->insert((yyvsp[0].pVarDeclList)->begin(),(yyvsp[-2].pVarDecl)); }
    break;

  case 642: /* function_argument_list: function_argument_declaration_type "end of expression" function_argument_list  */
                                                                                      { (yyval.pVarDeclList) = (yyvsp[0].pVarDeclList); (yyvsp[0].pVarDeclList)->insert((yyvsp[0].pVarDeclList)->begin(),(yyvsp[-2].pVarDecl)); }
    break;

  case 643: /* function_argument_list: function_argument_declaration_type ',' function_argument_list  */
                                                                                      { (yyval.pVarDeclList) = (yyvsp[0].pVarDeclList); (yyvsp[0].pVarDeclList)->insert((yyvsp[0].pVarDeclList)->begin(),(yyvsp[-2].pVarDecl)); }
    break;

  case 644: /* tuple_type: type_declaration  */
                                    {
        (yyval.pVarDecl) = new VariableDeclaration(nullptr,(yyvsp[0].pTypeDecl),nullptr);
    }
    break;

  case 645: /* tuple_type: "name" ':' type_declaration  */
                                                   {
        auto na = new vector<VariableNameAndPosition>();
        na->push_back(VariableNameAndPosition(*(yyvsp[-2].s),"",tokAt(scanner,(yylsp[-2]))));
        (yyval.pVarDecl) = new VariableDeclaration(na,(yyvsp[0].pTypeDecl),nullptr);
        delete (yyvsp[-2].s);
    }
    break;

  case 646: /* tuple_type_list: tuple_type  */
                                                       { (yyval.pVarDeclList) = new vector<VariableDeclaration*>(); (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 647: /* tuple_type_list: tuple_type_list c_or_s tuple_type  */
                                                          { (yyval.pVarDeclList) = (yyvsp[-2].pVarDeclList); (yyvsp[-2].pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 648: /* tuple_alias_type_list: %empty  */
        {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 649: /* tuple_alias_type_list: tuple_alias_type_list c_or_s  */
                                         {
        (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList);
    }
    break;

  case 650: /* tuple_alias_type_list: tuple_alias_type_list tuple_type c_or_s  */
                                                            {
        (yyval.pVarDeclList) = (yyvsp[-2].pVarDeclList); (yyvsp[-2].pVarDeclList)->push_back((yyvsp[-1].pVarDecl));
        /*
        if ( !yyextra->g_CommentReaders.empty() ) {
            for ( auto & crd : yyextra->g_CommentReaders ) {
                for ( const auto & nl : *($decl->pNameList) ) {
                    crd->afterVariantEntry(nl.name.c_str(), nl.at);
                }
            }
        }
        */
    }
    break;

  case 651: /* variant_type: "name" ':' type_declaration  */
                                                   {
        auto na = new vector<VariableNameAndPosition>();
        na->push_back(VariableNameAndPosition(*(yyvsp[-2].s),"",tokAt(scanner,(yylsp[-2]))));
        (yyval.pVarDecl) = new VariableDeclaration(na,(yyvsp[0].pTypeDecl),nullptr);
        delete (yyvsp[-2].s);
    }
    break;

  case 652: /* variant_type_list: variant_type  */
                                                         { (yyval.pVarDeclList) = new vector<VariableDeclaration*>(); (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 653: /* variant_type_list: variant_type_list c_or_s variant_type  */
                                                            { (yyval.pVarDeclList) = (yyvsp[-2].pVarDeclList); (yyvsp[-2].pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 654: /* variant_alias_type_list: %empty  */
        {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 655: /* variant_alias_type_list: variant_alias_type_list c_or_s  */
                                           {
        (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList);
    }
    break;

  case 656: /* variant_alias_type_list: variant_alias_type_list variant_type c_or_s  */
                                                                {
        (yyval.pVarDeclList) = (yyvsp[-2].pVarDeclList); (yyvsp[-2].pVarDeclList)->push_back((yyvsp[-1].pVarDecl));
        if ( !yyextra->g_CommentReaders.empty() ) {
            for ( auto & crd : yyextra->g_CommentReaders ) {
                for ( const auto & nl : *((yyvsp[-1].pVarDecl)->pNameList) ) {
                    crd->afterVariantEntry(nl.name.c_str(), nl.at);
                }
            }
        }
    }
    break;

  case 657: /* copy_or_move: '='  */
                    { (yyval.b) = false; }
    break;

  case 658: /* copy_or_move: "<-"  */
                    { (yyval.b) = true; }
    break;

  case 659: /* variable_declaration_no_type: variable_name_with_pos_list  */
                                          {
        auto autoT = new TypeDecl(Type::autoinfer);
        autoT->at = tokAt(scanner,(yylsp[0]));
        autoT->ref = false;
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[0].pNameWithPosList),autoT,nullptr);
    }
    break;

  case 660: /* variable_declaration_no_type: variable_name_with_pos_list '&'  */
                                              {
        auto autoT = new TypeDecl(Type::autoinfer);
        autoT->at = tokAt(scanner,(yylsp[-1]));
        autoT->ref = true;
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-1].pNameWithPosList),autoT,nullptr);
    }
    break;

  case 661: /* variable_declaration_no_type: variable_name_with_pos_list copy_or_move expr  */
                                                                       {
        auto typeDecl = new TypeDecl(Type::autoinfer);
        typeDecl->at = tokAt(scanner,(yylsp[-2]));
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-2].pNameWithPosList),typeDecl,(yyvsp[0].pExpression));
        (yyval.pVarDecl)->init_via_move = (yyvsp[-1].b);
    }
    break;

  case 662: /* variable_declaration_type: variable_name_with_pos_list ':' type_declaration  */
                                                                          {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-2].pNameWithPosList),(yyvsp[0].pTypeDecl),nullptr);
    }
    break;

  case 663: /* variable_declaration_type: variable_name_with_pos_list ':' type_declaration copy_or_move expr  */
                                                                                                      {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-4].pNameWithPosList),(yyvsp[-2].pTypeDecl),(yyvsp[0].pExpression));
        (yyval.pVarDecl)->init_via_move = (yyvsp[-1].b);
    }
    break;

  case 664: /* variable_declaration: variable_declaration_type  */
                                        {
        (yyval.pVarDecl) = (yyvsp[0].pVarDecl);
    }
    break;

  case 665: /* variable_declaration: variable_declaration_no_type  */
                                           {
        (yyval.pVarDecl) = (yyvsp[0].pVarDecl);
    }
    break;

  case 666: /* copy_or_move_or_clone: '='  */
                    { (yyval.i) = CorM_COPY; }
    break;

  case 667: /* copy_or_move_or_clone: "<-"  */
                    { (yyval.i) = CorM_MOVE; }
    break;

  case 668: /* copy_or_move_or_clone: ":="  */
                    { (yyval.i) = CorM_CLONE; }
    break;

  case 669: /* optional_ref: %empty  */
            { (yyval.b) = false; }
    break;

  case 670: /* optional_ref: '&'  */
            { (yyval.b) = true; }
    break;

  case 671: /* let_variable_name_with_pos_list: "name"  */
                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = pSL;
        delete (yyvsp[0].s);
    }
    break;

  case 672: /* let_variable_name_with_pos_list: "$i" '(' expr2 ')'  */
                                      {
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = pSL;
    }
    break;

  case 673: /* let_variable_name_with_pos_list: "name" "aka" "name"  */
                                         {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition(*(yyvsp[-2].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-2]))));
        (yyval.pNameWithPosList) = pSL;
        delete (yyvsp[-2].s);
        delete (yyvsp[0].s);
    }
    break;

  case 674: /* let_variable_name_with_pos_list: let_variable_name_with_pos_list ',' "name"  */
                                                             {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = (yyvsp[-2].pNameWithPosList);
        delete (yyvsp[0].s);
    }
    break;

  case 675: /* let_variable_name_with_pos_list: let_variable_name_with_pos_list ',' "name" "aka" "name"  */
                                                                                   {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-4].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[-2].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-2]))));
        (yyval.pNameWithPosList) = (yyvsp[-4].pNameWithPosList);
        delete (yyvsp[-2].s);
        delete (yyvsp[0].s);
    }
    break;

  case 676: /* let_variable_declaration: let_variable_name_with_pos_list ':' type_declaration_no_options semicolon  */
                                                                                                  {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-3].pNameWithPosList),(yyvsp[-1].pTypeDecl),nullptr);
    }
    break;

  case 677: /* let_variable_declaration: let_variable_name_with_pos_list ':' type_declaration_no_options copy_or_move_or_clone expr semicolon  */
                                                                                                                                        {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-5].pNameWithPosList),(yyvsp[-3].pTypeDecl),(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
    }
    break;

  case 678: /* let_variable_declaration: let_variable_name_with_pos_list ':' type_declaration_no_options copy_or_move_or_clone expr_pipe  */
                                                                                                                                   {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-4].pNameWithPosList),(yyvsp[-2].pTypeDecl),(yyvsp[0].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-1].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-1].i) & CorM_CLONE) !=0;
    }
    break;

  case 679: /* let_variable_declaration: let_variable_name_with_pos_list optional_ref copy_or_move_or_clone expr semicolon  */
                                                                                                                {
        auto typeDecl = new TypeDecl(Type::autoinfer);
        typeDecl->at = tokAt(scanner,(yylsp[-4]));
        typeDecl->ref = (yyvsp[-3].b);
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-4].pNameWithPosList),typeDecl,(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
    }
    break;

  case 680: /* let_variable_declaration: let_variable_name_with_pos_list optional_ref copy_or_move_or_clone expr  */
                                                                                                                  {
        // Until absence of semicolon with lambda is not fixed
        format::try_semicolon_at_eol(format::Pos::from_last(tokAt(scanner,(yylsp[0]))));
        auto typeDecl = new TypeDecl(Type::autoinfer);
        typeDecl->at = tokAt(scanner,(yylsp[-3]));
        typeDecl->ref = (yyvsp[-2].b);
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-3].pNameWithPosList),typeDecl,(yyvsp[0].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-1].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-1].i) & CorM_CLONE) !=0;
    }
    break;

  case 681: /* let_variable_declaration: let_variable_name_with_pos_list optional_ref copy_or_move_or_clone expr_pipe  */
                                                                                                           {
        auto typeDecl = new TypeDecl(Type::autoinfer);
        typeDecl->at = tokAt(scanner,(yylsp[-3]));
        typeDecl->ref = (yyvsp[-2].b);
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-3].pNameWithPosList),typeDecl,(yyvsp[0].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-1].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-1].i) & CorM_CLONE) !=0;
    }
    break;

  case 682: /* global_variable_declaration_list: %empty  */
        {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 683: /* $@41: %empty  */
                                               {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeGlobalVariables(tak);
        }
    }
    break;

  case 684: /* global_variable_declaration_list: global_variable_declaration_list $@41 optional_field_annotation let_variable_declaration opt_sem  */
                                                                              {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders )
                for ( auto & nl : *((yyvsp[-1].pVarDecl)->pNameList) )
                    crd->afterGlobalVariable(nl.name.c_str(),tak);
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterGlobalVariables(tak);
        }
        (yyval.pVarDeclList) = (yyvsp[-4].pVarDeclList);
        (yyvsp[-1].pVarDecl)->annotation = (yyvsp[-2].aaList);
        (yyvsp[-4].pVarDeclList)->push_back((yyvsp[-1].pVarDecl));
    }
    break;

  case 685: /* optional_shared: %empty  */
                     { (yyval.b) = false; }
    break;

  case 686: /* optional_shared: "shared"  */
                     { (yyval.b) = true; }
    break;

  case 687: /* optional_public_or_private_variable: %empty  */
                     { (yyval.b) = yyextra->g_Program->thisModule->isPublic; }
    break;

  case 688: /* optional_public_or_private_variable: "private"  */
                     { (yyval.b) = false; }
    break;

  case 689: /* optional_public_or_private_variable: "public"  */
                     { (yyval.b) = true; }
    break;

  case 690: /* global_let: kwd_let optional_shared optional_public_or_private_variable open_block global_variable_declaration_list close_block  */
                                                                                                                                                                   {
        handle_brace(format::Pos::from(tokAt(scanner, (yylsp[-2]))), (yyvsp[-2].ui),
                     format::get_substring(tokRangeAt(scanner, (yylsp[-2]), (yylsp[0]))),
                     yyextra->das_tab_size,
                     format::Pos::from_last(tokAt(scanner,(yylsp[0]))));
        ast_globalLetList(scanner,(yyvsp[-5].b),(yyvsp[-4].b),(yyvsp[-3].b),(yyvsp[-1].pVarDeclList));
    }
    break;

  case 691: /* $@42: %empty  */
                                                                                        {
        yyextra->das_force_oxford_comma=true;
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeGlobalVariables(tak);
        }
    }
    break;

  case 692: /* global_let: kwd_let optional_shared optional_public_or_private_variable $@42 optional_field_annotation let_variable_declaration  */
                                                                    {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders )
                for ( auto & nl : *((yyvsp[0].pVarDecl)->pNameList) )
                    crd->afterGlobalVariable(nl.name.c_str(),tak);
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterGlobalVariables(tak);
        }
        ast_globalLet(scanner,(yyvsp[-5].b),(yyvsp[-4].b),(yyvsp[-3].b),(yyvsp[-1].aaList),(yyvsp[0].pVarDecl));
    }
    break;

  case 693: /* enum_list: %empty  */
        {
        (yyval.pEnumList) = new Enumeration();
    }
    break;

  case 694: /* enum_list: enum_list "name" opt_sem  */
                                              {
        format::skip_token(true, false, tokAt(scanner,(yylsp[0])));
        das_checkName(scanner,*(yyvsp[-1].s),tokAt(scanner,(yylsp[-1])));
        if ( !(yyvsp[-2].pEnumList)->add(*(yyvsp[-1].s),nullptr,tokAt(scanner,(yylsp[-1]))) ) {
            das_yyerror(scanner,"enumeration already declared " + *(yyvsp[-1].s), tokAt(scanner,(yylsp[-1])),
                CompilationError::enumeration_value_already_declared);
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tokName = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) {
                crd->afterEnumerationEntry((yyvsp[-1].s)->c_str(), tokName);
            }
        }
        delete (yyvsp[-1].s);
        (yyval.pEnumList) = (yyvsp[-2].pEnumList);
    }
    break;

  case 695: /* enum_list: enum_list "name" '=' expr opt_sem  */
                                                              {
        format::skip_token(true, false, tokAt(scanner,(yylsp[0])));
        das_checkName(scanner,*(yyvsp[-3].s),tokAt(scanner,(yylsp[-3])));
        if ( !(yyvsp[-4].pEnumList)->add(*(yyvsp[-3].s),(yyvsp[-1].pExpression),tokAt(scanner,(yylsp[-3]))) ) {
            das_yyerror(scanner,"enumeration value already declared " + *(yyvsp[-3].s), tokAt(scanner,(yylsp[-3])),
                CompilationError::enumeration_value_already_declared);
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tokName = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) {
                crd->afterEnumerationEntry((yyvsp[-3].s)->c_str(), tokName);
            }
        }
        delete (yyvsp[-3].s);
        (yyval.pEnumList) = (yyvsp[-4].pEnumList);
    }
    break;

  case 696: /* optional_public_or_private_alias: %empty  */
                     { (yyval.b) = yyextra->g_Program->thisModule->isPublic; }
    break;

  case 697: /* optional_public_or_private_alias: "private"  */
                     { (yyval.b) = false; }
    break;

  case 698: /* optional_public_or_private_alias: "public"  */
                     { (yyval.b) = true; }
    break;

  case 699: /* $@43: %empty  */
                                                         {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto pubename = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeAlias(pubename);
        }
    }
    break;

  case 700: /* single_alias: optional_public_or_private_alias "name" $@43 '=' type_declaration  */
                                  {
        das_checkName(scanner,*(yyvsp[-3].s),tokAt(scanner,(yylsp[-3])));
        (yyvsp[0].pTypeDecl)->isPrivateAlias = !(yyvsp[-4].b);
        if ( (yyvsp[0].pTypeDecl)->baseType == Type::alias ) {
            das_yyerror(scanner,"alias cannot be defined in terms of another alias "+*(yyvsp[-3].s),tokAt(scanner,(yylsp[-3])),
                CompilationError::invalid_type);
        }
        (yyvsp[0].pTypeDecl)->alias = *(yyvsp[-3].s);
        if ( !yyextra->g_Program->addAlias((yyvsp[0].pTypeDecl)) ) {
            das_yyerror(scanner,"type alias is already defined "+*(yyvsp[-3].s),tokAt(scanner,(yylsp[-3])),
                CompilationError::type_alias_already_declared);
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto pubename = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterAlias((yyvsp[-3].s)->c_str(),pubename);
        }
        if ((yylsp[-4]).first_column == (yylsp[-4]).last_column) {
            (yyloc).first_line = (yylsp[-3]).first_line;
            (yyloc).first_column = (yylsp[-3]).first_column;
        }
        delete (yyvsp[-3].s);
    }
    break;

  case 701: /* alias_list: single_alias opt_sem  */
                                    {
        (yyval.positions) = new vector<LineInfo>(1, tokAt(scanner, (yylsp[-1])));
    }
    break;

  case 702: /* alias_list: alias_list single_alias opt_sem  */
                                                       {
        (yyvsp[-2].positions)->emplace_back(tokAt(scanner, (yylsp[-1])));
        (yyval.positions) = (yyvsp[-2].positions);
    }
    break;

  case 703: /* alias_declaration: "typedef" open_block alias_list close_block  */
                                                                           {
        if (format::is_replace_braces() && format::prepare_rule(format::Pos::from(tokAt(scanner, (yylsp[-3]))))) {
            // todo: comments here and all such places, same rule
            for (const auto single: *(yyvsp[-1].positions)) {
                format::get_writer() << "typedef " << format::get_substring(single) << '\n';
            }
            format::finish_rule(format::Pos::from_last(tokAt(scanner, (yylsp[0]))));
        }

    }
    break;

  case 704: /* $@44: %empty  */
                    { yyextra->das_force_oxford_comma=true;}
    break;

  case 706: /* optional_public_or_private_enum: %empty  */
                     { (yyval.b) = yyextra->g_Program->thisModule->isPublic; }
    break;

  case 707: /* optional_public_or_private_enum: "private"  */
                     { (yyval.b) = false; }
    break;

  case 708: /* optional_public_or_private_enum: "public"  */
                     { (yyval.b) = true; }
    break;

  case 709: /* enum_name: "name"  */
                   {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto pubename = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeEnumeration(pubename);
        }
        (yyval.pEnum) = ast_addEmptyEnum(scanner, (yyvsp[0].s), tokAt(scanner,(yylsp[0])));
    }
    break;

  case 710: /* enum_declaration: optional_annotation_list "enum" optional_public_or_private_enum enum_name open_block enum_list close_block  */
                                                                                                                                                              {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeEnumerationEntries(tak);
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterEnumerationEntries(tak);
        }
        const auto first_loc = format::Pos::from(tokAt(scanner,(yylsp[-2])));
        handle_brace(first_loc, (yyvsp[-2].ui),
                     format::get_substring(first_loc, format::Pos::from_last(tokAt(scanner,(yylsp[-1])))),
                     yyextra->das_tab_size,
                     format::Pos::from_last(tokAt(scanner,(yylsp[-1]))));
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto pubename = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterEnumeration((yyvsp[-3].pEnum)->name.c_str(),pubename);
        }
        ast_enumDeclaration(scanner,(yyvsp[-6].faList),tokAt(scanner,(yylsp[-6])),(yyvsp[-4].b),(yyvsp[-3].pEnum),(yyvsp[-1].pEnumList),Type::tInt);
    }
    break;

  case 711: /* enum_declaration: optional_annotation_list "enum" optional_public_or_private_enum enum_name ':' enum_basic_type_declaration open_block enum_list close_block  */
                                                                                                                                                                                                  {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-5]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeEnumerationEntries(tak);
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterEnumerationEntries(tak);
        }
        const auto first_loc = format::Pos::from(tokAt(scanner,(yylsp[-2])));
        handle_brace(first_loc, (yyvsp[-2].ui),
                     format::get_substring(first_loc, format::Pos::from_last(tokAt(scanner,(yylsp[-1])))),
                     yyextra->das_tab_size,
                     format::Pos::from_last(tokAt(scanner,(yylsp[-1]))));
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto pubename = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterEnumeration((yyvsp[-5].pEnum)->name.c_str(),pubename);
        }
        ast_enumDeclaration(scanner,(yyvsp[-8].faList),tokAt(scanner,(yylsp[-8])),(yyvsp[-6].b),(yyvsp[-5].pEnum),(yyvsp[-1].pEnumList),(yyvsp[-3].type));
    }
    break;

  case 712: /* optional_structure_parent: %empty  */
                                        { (yyval.s) = nullptr; }
    break;

  case 713: /* optional_structure_parent: ':' name_in_namespace  */
                                        { (yyval.s) = (yyvsp[0].s); }
    break;

  case 714: /* optional_sealed: %empty  */
                        { (yyval.b) = false; }
    break;

  case 715: /* optional_sealed: "sealed"  */
                        { (yyval.b) = true; }
    break;

  case 716: /* structure_name: optional_sealed "name" optional_structure_parent  */
                                                                           {
        (yyval.pStructure) = ast_structureName(scanner,(yyvsp[-2].b),(yyvsp[-1].s),tokAt(scanner,(yylsp[-1])),(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
    }
    break;

  case 717: /* class_or_struct: "class"  */
                    { (yyval.i) = CorS_Class; }
    break;

  case 718: /* class_or_struct: "struct"  */
                    { (yyval.i) = CorS_Struct; }
    break;

  case 719: /* class_or_struct: "class" "template"  */
                                  { (yyval.i) = CorS_ClassTemplate; }
    break;

  case 720: /* class_or_struct: "struct" "template"  */
                                  { (yyval.i) = CorS_StructTemplate; }
    break;

  case 721: /* optional_public_or_private_structure: %empty  */
                     { (yyval.b) = yyextra->g_Program->thisModule->isPublic; }
    break;

  case 722: /* optional_public_or_private_structure: "private"  */
                     { (yyval.b) = false; }
    break;

  case 723: /* optional_public_or_private_structure: "public"  */
                     { (yyval.b) = true; }
    break;

  case 724: /* optional_struct_variable_declaration_list: %empty  */
        {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 725: /* optional_struct_variable_declaration_list: open_block struct_variable_declaration_list close_block  */
                                                                                      {
        const auto prev_loc = format::Pos::from(tokAt(scanner,(yylsp[-2])));
        handle_brace(prev_loc, (yyvsp[-2].ui),
                     format::get_substring(prev_loc, format::Pos::from_last(tokAt(scanner,(yylsp[-1])))),
                     yyextra->das_tab_size,
                     format::Pos::from_last(tokAt(scanner,(yylsp[-1]))));
        (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList);
    }
    break;

  case 726: /* $@45: %empty  */
                                                                                                        {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeStructure(tak);
        }
    }
    break;

  case 727: /* $@46: %empty  */
                         {
        if ( (yyvsp[0].pStructure) ) {
            (yyvsp[0].pStructure)->isClass = (yyvsp[-3].i)==CorS_Class || (yyvsp[-3].i)==CorS_ClassTemplate;
            (yyvsp[0].pStructure)->isTemplate = (yyvsp[-3].i)==CorS_ClassTemplate || (yyvsp[-3].i)==CorS_StructTemplate;
            (yyvsp[0].pStructure)->privateStructure = !(yyvsp[-2].b);
        }
    }
    break;

  case 728: /* structure_declaration: optional_annotation_list class_or_struct optional_public_or_private_structure $@45 structure_name $@46 optional_struct_variable_declaration_list  */
                                                      {
        if ( (yyvsp[-2].pStructure) ) {
            ast_structureDeclaration ( scanner, (yyvsp[-6].faList), tokAt(scanner,(yylsp[-5])), (yyvsp[-2].pStructure), tokAt(scanner,(yylsp[-2])), (yyvsp[0].pVarDeclList) );
            if ( !yyextra->g_CommentReaders.empty() ) {
                auto tak = tokAt(scanner,(yylsp[-5]));
                for ( auto & crd : yyextra->g_CommentReaders ) crd->afterStructure((yyvsp[-2].pStructure),tak);
            }
        } else {
            deleteVariableDeclarationList((yyvsp[0].pVarDeclList));
        }
    }
    break;

  case 729: /* variable_name_with_pos_list: "name"  */
                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = pSL;
        delete (yyvsp[0].s);
    }
    break;

  case 730: /* variable_name_with_pos_list: "$i" '(' expr2 ')'  */
                                      {
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = pSL;
    }
    break;

  case 731: /* variable_name_with_pos_list: "name" "aka" "name"  */
                                         {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition(*(yyvsp[-2].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-2]))));
        (yyval.pNameWithPosList) = pSL;
        delete (yyvsp[-2].s);
        delete (yyvsp[0].s);
    }
    break;

  case 732: /* variable_name_with_pos_list: variable_name_with_pos_list ',' "name"  */
                                                         {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = (yyvsp[-2].pNameWithPosList);
        delete (yyvsp[0].s);
    }
    break;

  case 733: /* variable_name_with_pos_list: variable_name_with_pos_list ',' "name" "aka" "name"  */
                                                                               {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-4].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[-2].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-2]))));
        (yyval.pNameWithPosList) = (yyvsp[-4].pNameWithPosList);
        delete (yyvsp[-2].s);
        delete (yyvsp[0].s);
    }
    break;

  case 734: /* basic_type_declaration: "bool"  */
                        { (yyval.type) = Type::tBool; }
    break;

  case 735: /* basic_type_declaration: "string"  */
                        { (yyval.type) = Type::tString; }
    break;

  case 736: /* basic_type_declaration: "int"  */
                        { (yyval.type) = Type::tInt; }
    break;

  case 737: /* basic_type_declaration: "int8"  */
                        { (yyval.type) = Type::tInt8; }
    break;

  case 738: /* basic_type_declaration: "int16"  */
                        { (yyval.type) = Type::tInt16; }
    break;

  case 739: /* basic_type_declaration: "int64"  */
                        { (yyval.type) = Type::tInt64; }
    break;

  case 740: /* basic_type_declaration: "int2"  */
                        { (yyval.type) = Type::tInt2; }
    break;

  case 741: /* basic_type_declaration: "int3"  */
                        { (yyval.type) = Type::tInt3; }
    break;

  case 742: /* basic_type_declaration: "int4"  */
                        { (yyval.type) = Type::tInt4; }
    break;

  case 743: /* basic_type_declaration: "uint"  */
                        { (yyval.type) = Type::tUInt; }
    break;

  case 744: /* basic_type_declaration: "uint8"  */
                        { (yyval.type) = Type::tUInt8; }
    break;

  case 745: /* basic_type_declaration: "uint16"  */
                        { (yyval.type) = Type::tUInt16; }
    break;

  case 746: /* basic_type_declaration: "uint64"  */
                        { (yyval.type) = Type::tUInt64; }
    break;

  case 747: /* basic_type_declaration: "uint2"  */
                        { (yyval.type) = Type::tUInt2; }
    break;

  case 748: /* basic_type_declaration: "uint3"  */
                        { (yyval.type) = Type::tUInt3; }
    break;

  case 749: /* basic_type_declaration: "uint4"  */
                        { (yyval.type) = Type::tUInt4; }
    break;

  case 750: /* basic_type_declaration: "float"  */
                        { (yyval.type) = Type::tFloat; }
    break;

  case 751: /* basic_type_declaration: "float2"  */
                        { (yyval.type) = Type::tFloat2; }
    break;

  case 752: /* basic_type_declaration: "float3"  */
                        { (yyval.type) = Type::tFloat3; }
    break;

  case 753: /* basic_type_declaration: "float4"  */
                        { (yyval.type) = Type::tFloat4; }
    break;

  case 754: /* basic_type_declaration: "float16"  */
                        { (yyval.type) = Type::tFloat16; }
    break;

  case 755: /* basic_type_declaration: "half2"  */
                        { (yyval.type) = Type::tHalf2; }
    break;

  case 756: /* basic_type_declaration: "half3"  */
                        { (yyval.type) = Type::tHalf3; }
    break;

  case 757: /* basic_type_declaration: "half4"  */
                        { (yyval.type) = Type::tHalf4; }
    break;

  case 758: /* basic_type_declaration: "half8"  */
                        { (yyval.type) = Type::tHalf8; }
    break;

  case 759: /* basic_type_declaration: "short2"  */
                        { (yyval.type) = Type::tShort2; }
    break;

  case 760: /* basic_type_declaration: "short3"  */
                        { (yyval.type) = Type::tShort3; }
    break;

  case 761: /* basic_type_declaration: "short4"  */
                        { (yyval.type) = Type::tShort4; }
    break;

  case 762: /* basic_type_declaration: "short8"  */
                        { (yyval.type) = Type::tShort8; }
    break;

  case 763: /* basic_type_declaration: "ushort2"  */
                        { (yyval.type) = Type::tUShort2; }
    break;

  case 764: /* basic_type_declaration: "ushort3"  */
                        { (yyval.type) = Type::tUShort3; }
    break;

  case 765: /* basic_type_declaration: "ushort4"  */
                        { (yyval.type) = Type::tUShort4; }
    break;

  case 766: /* basic_type_declaration: "ushort8"  */
                        { (yyval.type) = Type::tUShort8; }
    break;

  case 767: /* basic_type_declaration: "byte2"  */
                        { (yyval.type) = Type::tByte2; }
    break;

  case 768: /* basic_type_declaration: "byte3"  */
                        { (yyval.type) = Type::tByte3; }
    break;

  case 769: /* basic_type_declaration: "byte4"  */
                        { (yyval.type) = Type::tByte4; }
    break;

  case 770: /* basic_type_declaration: "byte8"  */
                        { (yyval.type) = Type::tByte8; }
    break;

  case 771: /* basic_type_declaration: "byte16"  */
                        { (yyval.type) = Type::tByte16; }
    break;

  case 772: /* basic_type_declaration: "ubyte2"  */
                        { (yyval.type) = Type::tUByte2; }
    break;

  case 773: /* basic_type_declaration: "ubyte3"  */
                        { (yyval.type) = Type::tUByte3; }
    break;

  case 774: /* basic_type_declaration: "ubyte4"  */
                        { (yyval.type) = Type::tUByte4; }
    break;

  case 775: /* basic_type_declaration: "ubyte8"  */
                        { (yyval.type) = Type::tUByte8; }
    break;

  case 776: /* basic_type_declaration: "ubyte16"  */
                        { (yyval.type) = Type::tUByte16; }
    break;

  case 777: /* basic_type_declaration: "void"  */
                        { (yyval.type) = Type::tVoid; }
    break;

  case 778: /* basic_type_declaration: "range"  */
                        { (yyval.type) = Type::tRange; }
    break;

  case 779: /* basic_type_declaration: "urange"  */
                        { (yyval.type) = Type::tURange; }
    break;

  case 780: /* basic_type_declaration: "range64"  */
                        { (yyval.type) = Type::tRange64; }
    break;

  case 781: /* basic_type_declaration: "urange64"  */
                        { (yyval.type) = Type::tURange64; }
    break;

  case 782: /* basic_type_declaration: "double"  */
                        { (yyval.type) = Type::tDouble; }
    break;

  case 783: /* basic_type_declaration: "bitfield"  */
                        { (yyval.type) = Type::tBitfield; }
    break;

  case 784: /* enum_basic_type_declaration: "int"  */
                        { (yyval.type) = Type::tInt; }
    break;

  case 785: /* enum_basic_type_declaration: "int8"  */
                        { (yyval.type) = Type::tInt8; }
    break;

  case 786: /* enum_basic_type_declaration: "int16"  */
                        { (yyval.type) = Type::tInt16; }
    break;

  case 787: /* enum_basic_type_declaration: "uint"  */
                        { (yyval.type) = Type::tUInt; }
    break;

  case 788: /* enum_basic_type_declaration: "uint8"  */
                        { (yyval.type) = Type::tUInt8; }
    break;

  case 789: /* enum_basic_type_declaration: "uint16"  */
                        { (yyval.type) = Type::tUInt16; }
    break;

  case 790: /* enum_basic_type_declaration: "int64"  */
                        { (yyval.type) = Type::tInt64; }
    break;

  case 791: /* enum_basic_type_declaration: "uint64"  */
                        { (yyval.type) = Type::tUInt64; }
    break;

  case 792: /* structure_type_declaration: name_in_namespace  */
                                 {
        (yyval.pTypeDecl) = yyextra->g_Program->makeTypeDeclaration(tokAt(scanner,(yylsp[0])),*(yyvsp[0].s));
        if ( !(yyval.pTypeDecl) ) {
            (yyval.pTypeDecl) = new TypeDecl(Type::tVoid);
            (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
        }
        delete (yyvsp[0].s);
    }
    break;

  case 793: /* auto_type_declaration: "auto"  */
                       {
        (yyval.pTypeDecl) = new TypeDecl(Type::autoinfer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 794: /* auto_type_declaration: "auto" '(' "name" ')'  */
                                            {
        das_checkName(scanner,*(yyvsp[-1].s),tokAt(scanner,(yylsp[-1])));
        (yyval.pTypeDecl) = new TypeDecl(Type::autoinfer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-3]));
        (yyval.pTypeDecl)->alias = *(yyvsp[-1].s);
        delete (yyvsp[-1].s);
    }
    break;

  case 795: /* auto_type_declaration: "$t" '(' expr2 ')'  */
                                           {
        (yyval.pTypeDecl) = new TypeDecl(Type::alias);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-3]));
        (yyval.pTypeDecl)->alias = "``MACRO``TAG``";
        (yyval.pTypeDecl)->isTag = true;
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::autoinfer);
        (yyval.pTypeDecl)->firstType->at = tokAt(scanner, (yylsp[-1]));
        (yyval.pTypeDecl)->firstType->typeMacroExpr.push_back((yyvsp[-1].pExpression));
    }
    break;

  case 796: /* bitfield_bits: "name"  */
                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<string>();
        pSL->push_back(*(yyvsp[0].s));
        (yyval.pNameList) = pSL;
        delete (yyvsp[0].s);
    }
    break;

  case 797: /* bitfield_bits: bitfield_bits semicolon "name"  */
                                                 {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameList)->push_back(*(yyvsp[0].s));
        (yyval.pNameList) = (yyvsp[-2].pNameList);
        delete (yyvsp[0].s);
    }
    break;

  case 798: /* bitfield_bits: bitfield_bits ',' "name"  */
                                           {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameList)->push_back(*(yyvsp[0].s));
        (yyval.pNameList) = (yyvsp[-2].pNameList);
        delete (yyvsp[0].s);
    }
    break;

  case 801: /* bitfield_alias_bits: %empty  */
       {
        auto pSL = new vector<tuple<string,Expression *>>();
        (yyval.pNameExprList) = pSL;

    }
    break;

  case 802: /* bitfield_alias_bits: bitfield_alias_bits "name" SEMICOLON  */
                                                       {
        if (format::enum_bitfield_with_comma() && format::is_replace_braces() && format::prepare_rule(format::Pos::from_last(tokAt(scanner,(yylsp[-1]))))) {
            format::get_writer() << ",";
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[-1]))));
        }
        das_checkName(scanner,*(yyvsp[-1].s),tokAt(scanner,(yylsp[-1])));
        (yyval.pNameExprList) = (yyvsp[-2].pNameExprList);
        (yyval.pNameExprList)->emplace_back(*(yyvsp[-1].s),nullptr);
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterBitfieldEntry((yyvsp[-1].s)->c_str(),atvname);
        }
        delete (yyvsp[-1].s);
    }
    break;

  case 803: /* bitfield_alias_bits: bitfield_alias_bits "name" commas  */
                                                    {
        das_checkName(scanner,*(yyvsp[-1].s),tokAt(scanner,(yylsp[-1])));
        (yyval.pNameExprList) = (yyvsp[-2].pNameExprList);
        (yyval.pNameExprList)->emplace_back(*(yyvsp[-1].s),nullptr);
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterBitfieldEntry((yyvsp[-1].s)->c_str(),atvname);
        }
        delete (yyvsp[-1].s);
    }
    break;

  case 804: /* bitfield_alias_bits: bitfield_alias_bits "name"  */
                                             {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyval.pNameExprList) = (yyvsp[-1].pNameExprList);
        (yyval.pNameExprList)->emplace_back(*(yyvsp[0].s),nullptr);
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterBitfieldEntry((yyvsp[0].s)->c_str(),atvname);
        }
        delete (yyvsp[0].s);
    }
    break;

  case 805: /* bitfield_alias_bits: bitfield_alias_bits "name" '=' expr SEMICOLON  */
                                                                       {
        das_checkName(scanner,*(yyvsp[-3].s),tokAt(scanner,(yylsp[-3])));
        (yyval.pNameExprList) = (yyvsp[-4].pNameExprList);
        (yyval.pNameExprList)->emplace_back(*(yyvsp[-3].s),(yyvsp[-1].pExpression));
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterBitfieldEntry((yyvsp[-3].s)->c_str(),atvname);
        }
        delete (yyvsp[-3].s);
    }
    break;

  case 806: /* bitfield_alias_bits: bitfield_alias_bits "name" '=' expr commas  */
                                                                    {
        das_checkName(scanner,*(yyvsp[-3].s),tokAt(scanner,(yylsp[-3])));
        (yyval.pNameExprList) = (yyvsp[-4].pNameExprList);
        (yyval.pNameExprList)->emplace_back(*(yyvsp[-3].s),(yyvsp[-1].pExpression));
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterBitfieldEntry((yyvsp[-3].s)->c_str(),atvname);
        }
        delete (yyvsp[-3].s);
    }
    break;

  case 807: /* bitfield_alias_bits: bitfield_alias_bits "name" '=' expr  */
                                                             {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        (yyval.pNameExprList) = (yyvsp[-3].pNameExprList);
        (yyval.pNameExprList)->emplace_back(*(yyvsp[-2].s),(yyvsp[0].pExpression));
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-2]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterBitfieldEntry((yyvsp[-2].s)->c_str(),atvname);
        }
        delete (yyvsp[-2].s);
    }
    break;

  case 808: /* bitfield_basic_type_declaration: %empty  */
                             { (yyval.type) = Type::tBitfield; }
    break;

  case 809: /* bitfield_basic_type_declaration: ':' "uint8"  */
                             { (yyval.type) = Type::tBitfield8; }
    break;

  case 810: /* bitfield_basic_type_declaration: ':' "uint16"  */
                             { (yyval.type) = Type::tBitfield16; }
    break;

  case 811: /* bitfield_basic_type_declaration: ':' "uint"  */
                             { (yyval.type) = Type::tBitfield; }
    break;

  case 812: /* bitfield_basic_type_declaration: ':' "uint64"  */
                             { (yyval.type) = Type::tBitfield64; }
    break;

  case 813: /* bitfield_type_declaration: "bitfield" bitfield_basic_type_declaration '<' '>'  */
                                                                          {
            (yyval.pTypeDecl) = new TypeDecl((yyvsp[-2].type));
            (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-2]));
    }
    break;

  case 814: /* $@47: %empty  */
                                                                     { yyextra->das_arrow_depth ++; }
    break;

  case 815: /* $@48: %empty  */
                                                                                                                            { yyextra->das_arrow_depth --; }
    break;

  case 816: /* bitfield_type_declaration: "bitfield" bitfield_basic_type_declaration '<' $@47 bitfield_bits '>' $@48  */
                                                                                                                                                             {
            (yyval.pTypeDecl) = new TypeDecl((yyvsp[-5].type));
            (yyval.pTypeDecl)->argNames = *(yyvsp[-2].pNameList);
            auto maxBits = (yyval.pTypeDecl)->maxBitfieldBits();
            if ( (yyval.pTypeDecl)->argNames.size()>maxBits ) {
                das_yyerror(scanner,"only " + to_string(maxBits) + " different bits are allowed in a bitfield",tokAt(scanner,(yylsp[-5])),
                    CompilationError::invalid_type);
            }
            (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
            delete (yyvsp[-2].pNameList);
    }
    break;

  case 819: /* table_type_pair: type_declaration  */
                                      {
        (yyval.aTypePair).firstType = (yyvsp[0].pTypeDecl);
        (yyval.aTypePair).secondType = new TypeDecl(Type::tVoid);
    }
    break;

  case 820: /* table_type_pair: type_declaration c_or_s type_declaration  */
                                                                             {
        (yyval.aTypePair).firstType = (yyvsp[-2].pTypeDecl);
        (yyval.aTypePair).secondType = (yyvsp[0].pTypeDecl);
    }
    break;

  case 821: /* dim_list: '[' expr2 ']'  */
                              {
        (yyval.pTypeDecl) = appendDimExpr(nullptr, (yyvsp[-1].pExpression), tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 822: /* dim_list: dim_list '[' expr2 ']'  */
                                             {
        (yyval.pTypeDecl) = appendDimExpr((yyvsp[-3].pTypeDecl), (yyvsp[-1].pExpression), tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 823: /* type_declaration_no_options: basic_type_declaration  */
                                                            { (yyval.pTypeDecl) = new TypeDecl((yyvsp[0].type)); (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0])); }
    break;

  case 824: /* type_declaration_no_options: auto_type_declaration  */
                                                            { (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl); }
    break;

  case 825: /* type_declaration_no_options: bitfield_type_declaration  */
                                                            { (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl); }
    break;

  case 826: /* type_declaration_no_options: structure_type_declaration  */
                                                            { (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl); }
    break;

  case 827: /* type_declaration_no_options: type_declaration_no_options dim_list  */
                                                                {
        if ( (yyvsp[-1].pTypeDecl)->baseType==Type::typeDecl ) {
            das_yyerror(scanner,"type declaration can`t be used as array base type",tokAt(scanner,(yylsp[-1])),
                CompilationError::invalid_type);
        } else if ( (yyvsp[-1].pTypeDecl)->baseType==Type::typeMacro ) {
            das_yyerror(scanner,"macro can`t be used as array base type",tokAt(scanner,(yylsp[-1])),
                CompilationError::invalid_type);
        }
        (yyval.pTypeDecl) = attachDimChain((yyvsp[0].pTypeDecl), (yyvsp[-1].pTypeDecl));
    }
    break;

  case 828: /* type_declaration_no_options: type_declaration_no_options '[' ']'  */
                                                      {
        (yyval.pTypeDecl) = appendAutoDim((yyvsp[-2].pTypeDecl), tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 829: /* $@49: %empty  */
                     { yyextra->das_arrow_depth ++; }
    break;

  case 830: /* $@50: %empty  */
                                                                                     { yyextra->das_arrow_depth --; }
    break;

  case 831: /* type_declaration_no_options: "type" '<' $@49 type_declaration '>' $@50  */
                                                                                                                      {
        (yyvsp[-2].pTypeDecl)->autoToAlias = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 832: /* type_declaration_no_options: "typedecl" '(' expr2 ')'  */
                                                {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeDecl);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-3]),(yylsp[-1]));
        (yyval.pTypeDecl)->typeMacroExpr.push_back((yyvsp[-1].pExpression));
    }
    break;

  case 833: /* type_declaration_no_options: '$' name_in_namespace optional_expr_list_in_braces  */
                                                                            {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeMacro);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-1]), (yylsp[0]));
        (yyval.pTypeDecl)->typeMacroExpr = sequenceToList((yyvsp[0].pExpression));
        (yyval.pTypeDecl)->typeMacroExpr.insert((yyval.pTypeDecl)->typeMacroExpr.begin(), new ExprConstString(tokAt(scanner,(yylsp[-1])), *(yyvsp[-1].s)));
        delete (yyvsp[-1].s);
    }
    break;

  case 834: /* $@51: %empty  */
                                        { yyextra->das_arrow_depth ++; }
    break;

  case 835: /* type_declaration_no_options: '$' name_in_namespace '<' $@51 type_declaration_no_options_list '>' optional_expr_list_in_braces  */
                                                                                                                                                             {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeMacro);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-5]), (yylsp[0]));
        (yyval.pTypeDecl)->typeMacroExpr = typesAndSequenceToList((yyvsp[-2].pTypeDeclList),(yyvsp[0].pExpression));
        (yyval.pTypeDecl)->typeMacroExpr.insert((yyval.pTypeDecl)->typeMacroExpr.begin(), new ExprConstString(tokAt(scanner,(yylsp[-5])), *(yyvsp[-5].s)));
        delete (yyvsp[-5].s);
    }
    break;

  case 836: /* type_declaration_no_options: type_declaration_no_options '-' '[' ']'  */
                                                          {
        (yyvsp[-3].pTypeDecl)->removeDim = true;
        (yyval.pTypeDecl) = (yyvsp[-3].pTypeDecl);
    }
    break;

  case 837: /* type_declaration_no_options: type_declaration_no_options "explicit"  */
                                                           {
        (yyvsp[-1].pTypeDecl)->isExplicit = true;
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 838: /* type_declaration_no_options: type_declaration_no_options "const"  */
                                                        {
        (yyvsp[-1].pTypeDecl)->constant = true;
        (yyvsp[-1].pTypeDecl)->removeConstant = false;
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 839: /* type_declaration_no_options: type_declaration_no_options '-' "const"  */
                                                            {
        (yyvsp[-2].pTypeDecl)->constant = false;
        (yyvsp[-2].pTypeDecl)->removeConstant = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 840: /* type_declaration_no_options: type_declaration_no_options '&'  */
                                                  {
        (yyvsp[-1].pTypeDecl)->ref = true;
        (yyvsp[-1].pTypeDecl)->removeRef = false;
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 841: /* type_declaration_no_options: type_declaration_no_options '-' '&'  */
                                                      {
        (yyvsp[-2].pTypeDecl)->ref = false;
        (yyvsp[-2].pTypeDecl)->removeRef = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 842: /* type_declaration_no_options: type_declaration_no_options '#'  */
                                                  {
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
        (yyval.pTypeDecl)->temporary = true;
    }
    break;

  case 843: /* type_declaration_no_options: type_declaration_no_options "implicit"  */
                                                           {
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
        (yyval.pTypeDecl)->implicit = true;
    }
    break;

  case 844: /* type_declaration_no_options: type_declaration_no_options '-' '#'  */
                                                      {
        (yyvsp[-2].pTypeDecl)->temporary = false;
        (yyvsp[-2].pTypeDecl)->removeTemporary = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 845: /* type_declaration_no_options: type_declaration_no_options "==" "const"  */
                                                               {
        (yyvsp[-2].pTypeDecl)->explicitConst = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 846: /* type_declaration_no_options: type_declaration_no_options "==" '&'  */
                                                         {
        (yyvsp[-2].pTypeDecl)->explicitRef = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 847: /* type_declaration_no_options: type_declaration_no_options '?'  */
                                                  {
        (yyval.pTypeDecl) = new TypeDecl(Type::tPointer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-1]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 848: /* $@52: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 849: /* $@53: %empty  */
                                                                                               { yyextra->das_arrow_depth --; }
    break;

  case 850: /* type_declaration_no_options: "smart_ptr" '<' $@52 type_declaration '>' $@53  */
                                                                                                                                {
        (yyval.pTypeDecl) = new TypeDecl(Type::tPointer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->smartPtr = true;
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 851: /* type_declaration_no_options: type_declaration_no_options "??"  */
                                                 {
        (yyval.pTypeDecl) = new TypeDecl(Type::tPointer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-1]));
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::tPointer);
        (yyval.pTypeDecl)->firstType->at = tokAt(scanner,(yylsp[-1]));
        (yyval.pTypeDecl)->firstType->firstType = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 852: /* $@54: %empty  */
                           { yyextra->das_arrow_depth ++; }
    break;

  case 853: /* $@55: %empty  */
                                                                                           { yyextra->das_arrow_depth --; }
    break;

  case 854: /* type_declaration_no_options: "array" '<' $@54 type_declaration '>' $@55  */
                                                                                                                            {
        (yyval.pTypeDecl) = new TypeDecl(Type::tArray);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 855: /* $@56: %empty  */
                           { yyextra->das_arrow_depth ++; }
    break;

  case 856: /* $@57: %empty  */
                                                                                     { yyextra->das_arrow_depth --; }
    break;

  case 857: /* type_declaration_no_options: "table" '<' $@56 table_type_pair '>' $@57  */
                                                                                                                      {
        (yyval.pTypeDecl) = new TypeDecl(Type::tTable);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].aTypePair).firstType;
        (yyval.pTypeDecl)->secondType = (yyvsp[-2].aTypePair).secondType;
    }
    break;

  case 858: /* $@58: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 859: /* $@59: %empty  */
                                                                                                 { yyextra->das_arrow_depth --; }
    break;

  case 860: /* type_declaration_no_options: "iterator" '<' $@58 type_declaration '>' $@59  */
                                                                                                                                  {
        (yyval.pTypeDecl) = new TypeDecl(Type::tIterator);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 861: /* type_declaration_no_options: "block"  */
                        {
        (yyval.pTypeDecl) = new TypeDecl(Type::tBlock);
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::tVoid);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 862: /* $@60: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 863: /* $@61: %empty  */
                                                                                              { yyextra->das_arrow_depth --; }
    break;

  case 864: /* type_declaration_no_options: "block" '<' $@60 type_declaration '>' $@61  */
                                                                                                                               {
        (yyval.pTypeDecl) = new TypeDecl(Type::tBlock);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 865: /* $@62: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 866: /* $@63: %empty  */
                                                                                                                                       { yyextra->das_arrow_depth --; }
    break;

  case 867: /* type_declaration_no_options: "block" '<' $@62 optional_function_argument_list optional_function_type '>' $@63  */
                                                                                                                                                                        {
        (yyval.pTypeDecl) = new TypeDecl(Type::tBlock);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-6]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
        if ( (yyvsp[-3].pVarDeclList) ) {
            varDeclToTypeDecl(scanner, (yyval.pTypeDecl), (yyvsp[-3].pVarDeclList));
            deleteVariableDeclarationList((yyvsp[-3].pVarDeclList));
        }
    }
    break;

  case 868: /* type_declaration_no_options: "function"  */
                           {
        (yyval.pTypeDecl) = new TypeDecl(Type::tFunction);
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::tVoid);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 869: /* $@64: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 870: /* $@65: %empty  */
                                                                                                { yyextra->das_arrow_depth --; }
    break;

  case 871: /* type_declaration_no_options: "function" '<' $@64 type_declaration '>' $@65  */
                                                                                                                                 {
        (yyval.pTypeDecl) = new TypeDecl(Type::tFunction);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 872: /* $@66: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 873: /* $@67: %empty  */
                                                                                                                                         { yyextra->das_arrow_depth --; }
    break;

  case 874: /* type_declaration_no_options: "function" '<' $@66 optional_function_argument_list optional_function_type '>' $@67  */
                                                                                                                                                                          {
        (yyval.pTypeDecl) = new TypeDecl(Type::tFunction);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-6]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
        if ( (yyvsp[-3].pVarDeclList) ) {
            varDeclToTypeDecl(scanner, (yyval.pTypeDecl), (yyvsp[-3].pVarDeclList));
            deleteVariableDeclarationList((yyvsp[-3].pVarDeclList));
        }
    }
    break;

  case 875: /* type_declaration_no_options: "lambda"  */
                         {
        (yyval.pTypeDecl) = new TypeDecl(Type::tLambda);
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::tVoid);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 876: /* $@68: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 877: /* $@69: %empty  */
                                                                                              { yyextra->das_arrow_depth --; }
    break;

  case 878: /* type_declaration_no_options: "lambda" '<' $@68 type_declaration '>' $@69  */
                                                                                                                               {
        (yyval.pTypeDecl) = new TypeDecl(Type::tLambda);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 879: /* $@70: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 880: /* $@71: %empty  */
                                                                                                                                       { yyextra->das_arrow_depth --; }
    break;

  case 881: /* type_declaration_no_options: "lambda" '<' $@70 optional_function_argument_list optional_function_type '>' $@71  */
                                                                                                                                                                        {
        (yyval.pTypeDecl) = new TypeDecl(Type::tLambda);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-6]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
        if ( (yyvsp[-3].pVarDeclList) ) {
            varDeclToTypeDecl(scanner, (yyval.pTypeDecl), (yyvsp[-3].pVarDeclList));
            deleteVariableDeclarationList((yyvsp[-3].pVarDeclList));
        }
    }
    break;

  case 882: /* $@72: %empty  */
                            { yyextra->das_arrow_depth ++; }
    break;

  case 883: /* $@73: %empty  */
                                                                                       { yyextra->das_arrow_depth --; }
    break;

  case 884: /* type_declaration_no_options: "tuple" '<' $@72 tuple_type_list '>' $@73  */
                                                                                                                        {
        (yyval.pTypeDecl) = new TypeDecl(Type::tTuple);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        varDeclToTypeDecl(scanner, (yyval.pTypeDecl), (yyvsp[-2].pVarDeclList), true);
        deleteVariableDeclarationList((yyvsp[-2].pVarDeclList));
    }
    break;

  case 885: /* $@74: %empty  */
                              { yyextra->das_arrow_depth ++; }
    break;

  case 886: /* $@75: %empty  */
                                                                                           { yyextra->das_arrow_depth --; }
    break;

  case 887: /* type_declaration_no_options: "variant" '<' $@74 variant_type_list '>' $@75  */
                                                                                                                            {
        (yyval.pTypeDecl) = new TypeDecl(Type::tVariant);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        varDeclToTypeDecl(scanner, (yyval.pTypeDecl), (yyvsp[-2].pVarDeclList), true);
        deleteVariableDeclarationList((yyvsp[-2].pVarDeclList));
    }
    break;

  case 888: /* type_declaration: type_declaration_no_options  */
                                        {
        (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl);
    }
    break;

  case 889: /* type_declaration: type_declaration '|' type_declaration_no_options  */
                                                                     {
        if ( (yyvsp[-2].pTypeDecl)->baseType==Type::option ) {
            (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
            (yyval.pTypeDecl)->argTypes.push_back((yyvsp[0].pTypeDecl));
        } else {
            (yyval.pTypeDecl) = new TypeDecl(Type::option);
            (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-2]),(yylsp[0]));
            (yyval.pTypeDecl)->argTypes.push_back((yyvsp[-2].pTypeDecl));
            (yyval.pTypeDecl)->argTypes.push_back((yyvsp[0].pTypeDecl));
        }
    }
    break;

  case 890: /* type_declaration: type_declaration '|' '#'  */
                                             {
        if ( (yyvsp[-2].pTypeDecl)->baseType==Type::option ) {
            (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
            (yyval.pTypeDecl)->argTypes.push_back(new TypeDecl(*(yyvsp[-2].pTypeDecl)->argTypes.back()));
            (yyvsp[-2].pTypeDecl)->argTypes.back()->temporary ^= true;
        } else {
            (yyval.pTypeDecl) = new TypeDecl(Type::option);
            (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-2]),(yylsp[0]));
            (yyval.pTypeDecl)->argTypes.push_back((yyvsp[-2].pTypeDecl));
            (yyval.pTypeDecl)->argTypes.push_back(new TypeDecl(*(yyvsp[-2].pTypeDecl)));
            (yyval.pTypeDecl)->argTypes.back()->temporary ^= true;
        }
    }
    break;

  case 891: /* $@76: %empty  */
                                                          { yyextra->das_need_oxford_comma=false; }
    break;

  case 892: /* $@77: %empty  */
                                                                                                                {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeTuple(atvname);
        }
    }
    break;

  case 893: /* $@78: %empty  */
                      {
        if (format::is_replace_braces() && (yyvsp[0].ui) != 0xdeadbeef && format::prepare_rule(format::Pos::from(tokAt(scanner, (yylsp[0]))))) {
            format::get_writer() << " {";
            format::finish_rule(format::Pos::from(tokAt(scanner,(yylsp[0]))));
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-2]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeTupleEntries(atvname);
        }
    }
    break;

  case 894: /* $@79: %empty  */
                                  {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-4]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterTupleEntries(atvname);
        }
    }
    break;

  case 895: /* tuple_alias_declaration: "tuple" optional_public_or_private_alias $@76 "name" $@77 open_block $@78 tuple_alias_type_list $@79 close_block  */
                         {
        if (format::is_replace_braces() && (yyvsp[-4].ui) != 0xdeadbeef && format::prepare_rule(format::Pos::from(tokAt(scanner, (yylsp[0]))))) {
            format::get_writer() << "\n" << string((yyvsp[0].ui) * yyextra->das_tab_size, ' ') + "}";
            format::finish_rule(format::Pos::from(tokAt(scanner,(yylsp[0]))));
        }
        auto vtype = new TypeDecl(Type::tTuple);
        vtype->alias = *(yyvsp[-6].s);
        vtype->at = tokAt(scanner,(yylsp[-6]));
        vtype->isPrivateAlias = !(yyvsp[-8].b);
        varDeclToTypeDecl(scanner, vtype, (yyvsp[-2].pVarDeclList), true);
        deleteVariableDeclarationList((yyvsp[-2].pVarDeclList));
        if ( !yyextra->g_Program->addAlias(vtype) ) {
            das_yyerror(scanner,"type alias is already defined "+*(yyvsp[-6].s),tokAt(scanner,(yylsp[-6])),
                CompilationError::type_alias_already_declared);
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-6]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterTuple((yyvsp[-6].s)->c_str(),atvname);
        }
        delete (yyvsp[-6].s);
    }
    break;

  case 896: /* $@80: %empty  */
                                                            { yyextra->das_need_oxford_comma=false; }
    break;

  case 897: /* $@81: %empty  */
                                                                                                                  {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeVariant(atvname);
        }
    }
    break;

  case 898: /* $@82: %empty  */
                      {
        if (format::is_replace_braces() && (yyvsp[0].ui) != 0xdeadbeef && format::prepare_rule(format::Pos::from(tokAt(scanner, (yylsp[0]))))) {
            format::get_writer() << " {";
            format::finish_rule(format::Pos::from(tokAt(scanner,(yylsp[0]))));
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-2]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeVariantEntries(atvname);
        }

    }
    break;

  case 899: /* $@83: %empty  */
                                    {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-4]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterVariantEntries(atvname);
        }
    }
    break;

  case 900: /* variant_alias_declaration: "variant" optional_public_or_private_alias $@80 "name" $@81 open_block $@82 variant_alias_type_list $@83 close_block  */
                         {
        if (format::is_replace_braces() && (yyvsp[0].ui) != 0xdeadbeef && format::prepare_rule(format::Pos::from(tokAt(scanner, (yylsp[0]))))) {
            format::get_writer() << "\n" << string((yyvsp[0].ui) * yyextra->das_tab_size, ' ') + "}";
            format::finish_rule(format::Pos::from(tokAt(scanner,(yylsp[0]))));
        }
        auto vtype = new TypeDecl(Type::tVariant);
        vtype->alias = *(yyvsp[-6].s);
        vtype->at = tokAt(scanner,(yylsp[-6]));
        vtype->isPrivateAlias = !(yyvsp[-8].b);
        varDeclToTypeDecl(scanner, vtype, (yyvsp[-2].pVarDeclList), true);
        deleteVariableDeclarationList((yyvsp[-2].pVarDeclList));
        if ( !yyextra->g_Program->addAlias(vtype) ) {
            das_yyerror(scanner,"type alias is already defined "+*(yyvsp[-6].s),tokAt(scanner,(yylsp[-6])),
                CompilationError::type_alias_already_declared);
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-6]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterVariant((yyvsp[-6].s)->c_str(),atvname);
        }
        delete (yyvsp[-6].s);
    }
    break;

  case 901: /* $@84: %empty  */
                                                             { yyextra->das_need_oxford_comma=false; }
    break;

  case 902: /* $@85: %empty  */
                                                                                                                   {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeBitfield(atvname);
        }
    }
    break;

  case 903: /* bitfield_alias_declaration: "bitfield" optional_public_or_private_alias $@84 "name" $@85 bitfield_basic_type_declaration open_block bitfield_alias_bits close_block  */
                                                                                                              {
        const auto prev_loc = format::Pos::from(tokAt(scanner,(yylsp[-2])));
        handle_brace(prev_loc, (yyvsp[-2].ui),
                     format::get_substring(prev_loc, format::Pos::from_last(tokAt(scanner,(yylsp[-1])))),
                     yyextra->das_tab_size,
                     format::Pos::from_last(tokAt(scanner,(yylsp[-1]))));
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-5]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeBitfieldEntries(atvname);
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-5]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterBitfieldEntries(atvname);
        }
        auto btype = new TypeDecl((yyvsp[-3].type));
        btype->alias = *(yyvsp[-5].s);
        btype->at = tokAt(scanner,(yylsp[-5]));
        btype->isPrivateAlias = !(yyvsp[-7].b);
        for ( auto & p : *(yyvsp[-1].pNameExprList) ) {
            if ( !get<1>(p) ) {
                btype->argNames.push_back(get<0>(p));
            }
        }
        auto maxBits = btype->maxBitfieldBits();
        if ( btype->argNames.size()>maxBits ) {
            das_yyerror(scanner,"only " + to_string(maxBits) + " different bits are allowed in a bitfield",tokAt(scanner,(yylsp[-5])),
                CompilationError::invalid_type);
        }
        for ( auto & p : *(yyvsp[-1].pNameExprList) ) {
            if ( get<1>(p) ) {
                ast_globalBitfieldConst ( scanner, btype, (yyvsp[-7].b), get<0>(p), get<1>(p) );
            }
        }
        if ( !yyextra->g_Program->addAlias(btype) ) {
            das_yyerror(scanner,"type alias is already defined "+*(yyvsp[-5].s),tokAt(scanner,(yylsp[-5])),
                CompilationError::type_alias_already_declared);
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-5]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterBitfield((yyvsp[-5].s)->c_str(),atvname);
        }
        delete (yyvsp[-5].s);
        delete (yyvsp[-1].pNameExprList);
    }
    break;

  case 904: /* make_decl: make_struct_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 905: /* make_decl: make_dim_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 906: /* make_decl: make_table_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 907: /* make_decl: array_comprehension  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 908: /* make_decl: make_tuple_call  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 909: /* make_struct_fields: "name" copy_or_move expr  */
                                               {
        auto mfd = new MakeFieldDecl(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),*(yyvsp[-2].s),(yyvsp[0].pExpression),(yyvsp[-1].b),false);
        delete (yyvsp[-2].s);
        auto msd = new MakeStruct();
        msd->push_back(mfd);
        (yyval.pMakeStruct) = msd;
    }
    break;

  case 910: /* make_struct_fields: "name" ":=" expr  */
                                      {
        auto mfd = new MakeFieldDecl(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),*(yyvsp[-2].s),(yyvsp[0].pExpression),false,true);
        delete (yyvsp[-2].s);
        auto msd = new MakeStruct();
        msd->push_back(mfd);
        (yyval.pMakeStruct) = msd;
    }
    break;

  case 911: /* make_struct_fields: make_struct_fields ',' "name" copy_or_move expr  */
                                                                           {
        auto mfd = new MakeFieldDecl(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),*(yyvsp[-2].s),(yyvsp[0].pExpression),(yyvsp[-1].b),false);
        delete (yyvsp[-2].s);
        ((MakeStruct *)(yyvsp[-4].pMakeStruct))->push_back(mfd);
        (yyval.pMakeStruct) = (yyvsp[-4].pMakeStruct);
    }
    break;

  case 912: /* make_struct_fields: make_struct_fields ',' "name" ":=" expr  */
                                                                  {
        auto mfd = new MakeFieldDecl(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])),*(yyvsp[-2].s),(yyvsp[0].pExpression),false,true);
        delete (yyvsp[-2].s);
        ((MakeStruct *)(yyvsp[-4].pMakeStruct))->push_back(mfd);
        (yyval.pMakeStruct) = (yyvsp[-4].pMakeStruct);
    }
    break;

  case 913: /* make_struct_fields: "$f" '(' expr2 ')' copy_or_move expr  */
                                                                            {
        auto mfd = new MakeFieldDecl(tokRangeAt(scanner,(yylsp[-5]), (yylsp[0])),"``MACRO``TAG``FIELD``",(yyvsp[0].pExpression),(yyvsp[-1].b),false);
        mfd->tag = (yyvsp[-3].pExpression);
        auto msd = new MakeStruct();
        msd->push_back(mfd);
        (yyval.pMakeStruct) = msd;
    }
    break;

  case 914: /* make_struct_fields: "$f" '(' expr2 ')' ":=" expr  */
                                                                   {
        auto mfd = new MakeFieldDecl(tokRangeAt(scanner, (yylsp[-5]), (yylsp[0])),"``MACRO``TAG``FIELD``",(yyvsp[0].pExpression),false,true);
        mfd->tag = (yyvsp[-3].pExpression);
        auto msd = new MakeStruct();
        msd->push_back(mfd);
        (yyval.pMakeStruct) = msd;
    }
    break;

  case 915: /* make_struct_fields: make_struct_fields ',' "$f" '(' expr2 ')' copy_or_move expr  */
                                                                                                        {
        auto mfd = new MakeFieldDecl(tokRangeAt(scanner,(yylsp[-5]),(yylsp[0])),"``MACRO``TAG``FIELD``",(yyvsp[0].pExpression),(yyvsp[-1].b),false);
        mfd->tag = (yyvsp[-3].pExpression);
        ((MakeStruct *)(yyvsp[-7].pMakeStruct))->push_back(mfd);
        (yyval.pMakeStruct) = (yyvsp[-7].pMakeStruct);
    }
    break;

  case 916: /* make_struct_fields: make_struct_fields ',' "$f" '(' expr2 ')' ":=" expr  */
                                                                                               {
        auto mfd = new MakeFieldDecl(tokRangeAt(scanner,(yylsp[-5]), (yylsp[0])),"``MACRO``TAG``FIELD``",(yyvsp[0].pExpression),false,true);
        mfd->tag = (yyvsp[-3].pExpression);
        ((MakeStruct *)(yyvsp[-7].pMakeStruct))->push_back(mfd);
        (yyval.pMakeStruct) = (yyvsp[-7].pMakeStruct);
    }
    break;

  case 917: /* make_variant_dim: %empty  */
       {
        (yyval.pExpression) = ast_makeStructToMakeVariant(nullptr, LineInfo());
    }
    break;

  case 918: /* make_variant_dim: make_struct_fields  */
                              {
        (yyval.pExpression) = ast_makeStructToMakeVariant((yyvsp[0].pMakeStruct), tokAt(scanner,(yylsp[0])));
    }
    break;

  case 919: /* make_struct_single: make_struct_fields optional_comma  */
                                               {
        auto msd = new ExprMakeStruct();
        msd->structs.push_back(MakeStructPtr((yyvsp[-1].pMakeStruct)));
        (yyval.pExpression) = msd;
    }
    break;

  case 920: /* make_struct_dim: make_struct_fields  */
                                {
        auto msd = new ExprMakeStruct();
        msd->structs.push_back(MakeStructPtr((yyvsp[0].pMakeStruct)));
        (yyval.pExpression) = msd;
    }
    break;

  case 921: /* make_struct_dim: make_struct_dim semicolon make_struct_fields  */
                                                               {
        ((ExprMakeStruct *) (yyvsp[-2].pExpression))->structs.push_back(MakeStructPtr((yyvsp[0].pMakeStruct)));
        (yyval.pExpression) = (yyvsp[-2].pExpression);
    }
    break;

  case 922: /* make_struct_dim_list: '(' make_struct_fields ')'  */
                                        {
        auto msd = new ExprMakeStruct();
        msd->structs.push_back(MakeStructPtr((yyvsp[-1].pMakeStruct)));
        (yyval.pExpression) = msd;
    }
    break;

  case 923: /* make_struct_dim_list: make_struct_dim_list ',' '(' make_struct_fields ')'  */
                                                                     {
        ((ExprMakeStruct *) (yyvsp[-4].pExpression))->structs.push_back(MakeStructPtr((yyvsp[-1].pMakeStruct)));
        (yyval.pExpression) = (yyvsp[-4].pExpression);
    }
    break;

  case 924: /* make_struct_dim_decl: make_struct_fields  */
                                {
        auto msd = new ExprMakeStruct();
        msd->structs.push_back(MakeStructPtr((yyvsp[0].pMakeStruct)));
        (yyval.pExpression) = msd;
    }
    break;

  case 925: /* make_struct_dim_decl: make_struct_dim_list optional_comma  */
                                                 {
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 926: /* optional_make_struct_dim_decl: make_struct_dim_decl  */
                                  { (yyval.pExpression) = (yyvsp[0].pExpression);  }
    break;

  case 927: /* optional_make_struct_dim_decl: %empty  */
        {   (yyval.pExpression) = new ExprMakeStruct(); }
    break;

  case 928: /* optional_block: %empty  */
        { (yyval.pExpression) = nullptr; }
    break;

  case 929: /* optional_block: "where" expr_block  */
                                  { (yyvsp[0].pExpression)->at = tokAt(scanner, (yylsp[0])); (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 942: /* use_initializer: %empty  */
                            { (yyval.b) = true; }
    break;

  case 943: /* use_initializer: "uninitialized"  */
                            { (yyval.b) = false; }
    break;

  case 944: /* make_struct_decl: "[[" type_declaration_no_options make_struct_dim optional_block optional_trailing_delim_sqr_sqr  */
                                                                                                                                     {
        // std::cout << "case1" << std::endl;
        if (format::prepare_rule(format::Pos::from(tokAt(scanner,(yylsp[-4]))))) {
            auto type = format::type_to_string((yyvsp[-3].pTypeDecl), tokAt(scanner,(yylsp[-3]))).value_or("");
            const bool is_initialized = false;
            const auto before = format::substring_between(tokAt(scanner,(yylsp[-4])), tokAt(scanner, (yylsp[-3])));
            const auto internal = format::handle_msd(tokAt(scanner, (yylsp[-3])),
                                                     static_cast<ExprMakeStruct*>((yyvsp[-2].pExpression)),
                                                     tokAt(scanner, (yyvsp[-1].pExpression) != nullptr ? (yylsp[-1]) : (yylsp[0])),
                                                     type, is_initialized);
            if (static_cast<ExprMakeStruct*>((yyvsp[-2].pExpression))->structs.size() == 1) {
                // single struct
                if (type.find('[') != size_t(-1)) {
                    format::get_writer() << "fixed_array(" << before << internal << ")";
                } else {
                    format::get_writer() << before << internal;
                }
                if ((yyvsp[-1].pExpression) != nullptr) {
                    format::get_writer() << " <| " << format::get_substring((yyvsp[-1].pExpression)->at);
                }
            } else {
                // array of structs
    //            const auto internal = format::get_substring(format::Pos::from(tokAt(scanner,@msd)),
    //                                                          format::Pos::from(tokAt(scanner,@end)));
                format::get_writer() << "fixed_array(" << internal << ")";
            }
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[0]))));
        }
        ((ExprMakeStruct *)(yyvsp[-2].pExpression))->makeType = (yyvsp[-3].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-2].pExpression))->block = (yyvsp[-1].pExpression);
        (yyvsp[-2].pExpression)->at = tokAt(scanner,(yylsp[-4]));
        (yyval.pExpression) = (yyvsp[-2].pExpression);
    }
    break;

  case 945: /* make_struct_decl: "[[" type_declaration_no_options optional_block optional_trailing_delim_sqr_sqr  */
                                                                                                                {
        // // std::cout << "case2" << std::endl;
        if (format::prepare_rule(format::Pos::from(tokAt(scanner,(yylsp[-3]))))) {
            auto type = format::type_to_string((yyvsp[-2].pTypeDecl), tokAt(scanner,(yylsp[-2])));
            das_hash_set<string> always_init = {
                // Is there a method to describe all this types?
                "struct<array<",
                "array<",
                "bitfield",
                "string",
                "int",
                "float",
                "variant",
                "tuple",
            };
            const auto before = format::get_substring(format::Pos::from_last(tokAt(scanner,(yylsp[-3]))),
                                                      format::Pos::from(tokAt(scanner, (yylsp[-2]))));
            const auto after = format::get_substring(format::Pos::from_last(tokAt(scanner,(yylsp[-2]))),
                                                      format::Pos::from(tokAt(scanner, (yylsp[0]))));
            string suffix = ")";
            if ((yyvsp[-2].pTypeDecl)->isPointer()) {
                format::get_writer() << "default<" << type.value() << ">";
                suffix.clear();
            } else if (any_of(always_init.begin(), always_init.end(),
                            [&type](auto t){ return type.value_or("").find(t) == 0; })) {
                format::get_writer() << type.value_or("") << "(";
            } else {
                format::get_writer() << type.value_or("") << "("; // Possible uninitialized
            }
            format::get_writer() << before << after << suffix;
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[0]))));
        }

        auto msd = new ExprMakeStruct();
        msd->makeType = (yyvsp[-2].pTypeDecl);
        msd->block = (yyvsp[-1].pExpression);
        msd->at = tokAt(scanner,(yylsp[-3]));
        (yyval.pExpression) = msd;
    }
    break;

  case 946: /* make_struct_decl: "[[" type_declaration_no_options '(' ')' optional_block optional_trailing_delim_sqr_sqr  */
                                                                                                                                            {
        // std::cout << "case3" << std::endl;
        if (format::prepare_rule(format::Pos::from(tokAt(scanner,(yylsp[-5]))))) {
            const auto type_name = format::type_to_string((yyvsp[-4].pTypeDecl), tokAt(scanner,(yylsp[-4])));
            auto maybe_init = (format::can_default_init(type_name.value_or(""))) ? "" : ""; // Possible uninitialized
            format::get_writer() << type_name.value_or("") << "("
                                 << format::substring_between(tokAt(scanner,(yylsp[-5])), tokAt(scanner, (yylsp[-4])))
                                 << format::substring_between(tokAt(scanner,(yylsp[-3])), tokAt(scanner, (yylsp[-2])))
                                 << format::substring_between(tokAt(scanner,(yylsp[-2])), tokAt(scanner, (yylsp[0])))
                                 << maybe_init << ")";
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[0]))));
        }
        auto msd = new ExprMakeStruct();
        msd->makeType = (yyvsp[-4].pTypeDecl);
        msd->useInitializer = true;
        msd->block = (yyvsp[-1].pExpression);
        msd->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pExpression) = msd;
    }
    break;

  case 947: /* make_struct_decl: "[[" type_declaration_no_options '(' ')' make_struct_dim optional_block optional_trailing_delim_sqr_sqr  */
                                                                                                                                                                {
        // std::cout << "case4" << std::endl;
        if (format::prepare_rule(format::Pos::from(tokAt(scanner,(yylsp[-6]))))) {
            auto type_name = format::type_to_string((yyvsp[-5].pTypeDecl), tokAt(scanner,(yylsp[-5]))).value_or("");
            const auto internal = format::handle_msd(tokAt(scanner, (yylsp[-3])),
                                                     static_cast<ExprMakeStruct*>((yyvsp[-2].pExpression)),
                                                     tokAt(scanner, (yylsp[0])),
                                                     type_name);
            format::get_writer() << format::substring_between(tokAt(scanner, (yylsp[-6])), tokAt(scanner, (yylsp[-5])))
                                 << format::substring_between(tokAt(scanner, (yylsp[-4])), tokAt(scanner, (yylsp[-3])))
                                 << internal;
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[0]))));
        }

        ((ExprMakeStruct *)(yyvsp[-2].pExpression))->makeType = (yyvsp[-5].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-2].pExpression))->useInitializer = true;
        ((ExprMakeStruct *)(yyvsp[-2].pExpression))->block = (yyvsp[-1].pExpression);
        (yyvsp[-2].pExpression)->at = tokAt(scanner,(yylsp[-6]));
        (yyval.pExpression) = (yyvsp[-2].pExpression);
    }
    break;

  case 948: /* make_struct_decl: "[{" type_declaration_no_options make_struct_dim optional_block optional_trailing_delim_cur_sqr  */
                                                                                                                                          {
        // std::cout << "case6" << std::endl;
        if (format::prepare_rule(format::Pos::from(tokAt(scanner,(yylsp[-4]))))) {
            auto type_name = format::type_to_string((yyvsp[-3].pTypeDecl), tokAt(scanner,(yylsp[-3]))).value_or("");
            format::get_writer() << "[" << format::substring_between(tokAt(scanner, (yylsp[-4])), tokAt(scanner, (yylsp[-3])))
                                     << format::handle_msd(tokAt(scanner, (yylsp[-3])),
                                                              static_cast<ExprMakeStruct*>((yyvsp[-2].pExpression)),
                                                              tokAt(scanner, (yylsp[0])),
                                                              type_name)
                                 << "]";
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[0]))));
        }

        ((ExprMakeStruct *)(yyvsp[-2].pExpression))->makeType = (yyvsp[-3].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-2].pExpression))->block = (yyvsp[-1].pExpression);
        (yyvsp[-2].pExpression)->at = tokAt(scanner,(yylsp[-4]));
        auto tam = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-4])),"to_array_move");
        tam->arguments.push_back((yyvsp[-2].pExpression));
        (yyval.pExpression) = tam;
    }
    break;

  case 949: /* make_struct_decl: "[{" type_declaration_no_options '(' ')' make_struct_dim optional_block optional_trailing_delim_cur_sqr  */
                                                                                                                                                          {
        // std::cout << "case7" << std::endl;
        if (format::prepare_rule(format::Pos::from(tokAt(scanner,(yylsp[-6]))))) {
            auto type_name = format::type_to_string((yyvsp[-5].pTypeDecl), tokAt(scanner,(yylsp[-5]))).value_or("");
            format::get_writer() << "[" << format::substring_between(tokAt(scanner, (yylsp[-6])), tokAt(scanner, (yylsp[-5])))
                                   << format::handle_msd(tokAt(scanner, (yylsp[-3])),
                                                         static_cast<ExprMakeStruct*>((yyvsp[-2].pExpression)),
                                                         tokAt(scanner, (yylsp[0])),
                                                         type_name)
                                   << "]";
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[0]))));
        }

        ((ExprMakeStruct *)(yyvsp[-2].pExpression))->makeType = (yyvsp[-5].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-2].pExpression))->useInitializer = true;
        ((ExprMakeStruct *)(yyvsp[-2].pExpression))->block = (yyvsp[-1].pExpression);
        (yyvsp[-2].pExpression)->at = tokAt(scanner,(yylsp[-6]));
        auto tam = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-6])),"to_array_move");
        tam->arguments.push_back((yyvsp[-2].pExpression));
        (yyval.pExpression) = tam;
    }
    break;

  case 950: /* $@86: %empty  */
                             { yyextra->das_force_oxford_comma=true; yyextra->das_arrow_depth ++; }
    break;

  case 951: /* $@87: %empty  */
                                                                                                                                         { yyextra->das_arrow_depth --; }
    break;

  case 952: /* make_struct_decl: "struct" '<' $@86 type_declaration_no_options '>' $@87 '(' use_initializer optional_make_struct_dim_decl ')'  */
                                                                                                                                                                                                                                            {
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-9]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-6].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = (yyvsp[-2].b);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->forceStruct = true;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 953: /* $@88: %empty  */
                            { yyextra->das_force_oxford_comma=true; yyextra->das_arrow_depth ++; }
    break;

  case 954: /* $@89: %empty  */
                                                                                                                                        { yyextra->das_arrow_depth --; }
    break;

  case 955: /* make_struct_decl: "class" '<' $@88 type_declaration_no_options '>' $@89 '(' use_initializer optional_make_struct_dim_decl ')'  */
                                                                                                                                                                                                                                          {
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-9]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-6].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = (yyvsp[-2].b);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->forceClass = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 956: /* $@90: %empty  */
                               { yyextra->das_force_oxford_comma=true; yyextra->das_arrow_depth ++; }
    break;

  case 957: /* $@91: %empty  */
                                                                                                                                  { yyextra->das_arrow_depth --; }
    break;

  case 958: /* make_struct_decl: "variant" '<' $@90 variant_type_list '>' $@91 '(' use_initializer make_variant_dim ')'  */
                                                                                                                                                                                                                        {
        auto mkt = new TypeDecl(Type::tVariant);
        mkt->at = tokAt(scanner,(yylsp[-9]));
        varDeclToTypeDecl(scanner, mkt, (yyvsp[-6].pVarDeclList), true);
        deleteVariableDeclarationList((yyvsp[-6].pVarDeclList));
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-9]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = mkt;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = (yyvsp[-2].b);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->forceVariant = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 959: /* $@92: %empty  */
                              { yyextra->das_arrow_depth ++; }
    break;

  case 960: /* $@93: %empty  */
                                                                                                    { yyextra->das_arrow_depth --; }
    break;

  case 961: /* make_struct_decl: "default" '<' $@92 type_declaration_no_options '>' $@93 use_initializer  */
                                                                                                                                                           {
        auto msd = new ExprMakeStruct();
        msd->at = tokAt(scanner,(yylsp[-6]));
        msd->makeType = (yyvsp[-3].pTypeDecl);
        msd->useInitializer = (yyvsp[0].b);
        msd->alwaysUseInitializer = true;
        (yyval.pExpression) = msd;
    }
    break;

  case 962: /* make_tuple: expr  */
                  {
        (yyvsp[0].pExpression)->at = tokAt(scanner,(yylsp[0]));
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 963: /* make_tuple: expr "=>" expr  */
                                         {
        ExprMakeTuple * mt = new ExprMakeTuple(tokRangeAt(scanner,(yylsp[-2]), (yylsp[0])));
        mt->values.push_back((yyvsp[-2].pExpression));
        mt->values.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = mt;
    }
    break;

  case 964: /* make_tuple: make_tuple ',' expr  */
                                      {
        (yyvsp[0].pExpression)->at = tokAt(scanner,(yylsp[0]));
        ExprMakeTuple * mt;
        if ( (yyvsp[-2].pExpression)->rtti_isMakeTuple() ) {
            mt = static_cast<ExprMakeTuple *>((yyvsp[-2].pExpression));
        } else {
            mt = new ExprMakeTuple(tokAt(scanner,(yylsp[-2])));
            mt->values.push_back((yyvsp[-2].pExpression));
        }
        mt->values.push_back((yyvsp[0].pExpression));
        mt->at = format::concat(mt->at, tokAt(scanner, (yylsp[0])));
        (yyval.pExpression) = mt;
    }
    break;

  case 965: /* make_map_tuple: expr "=>" expr  */
                                         {
        ExprMakeTuple * mt = new ExprMakeTuple(tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])));
        mt->values.push_back((yyvsp[-2].pExpression));
        mt->values.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = mt;
    }
    break;

  case 966: /* make_map_tuple: expr  */
                 {
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 967: /* make_tuple_call: "tuple" '(' expr_list optional_comma ')'  */
                                                                    {
        auto mkt = new ExprMakeTuple(tokAt(scanner,(yylsp[-4])));
        mkt->values = sequenceToList((yyvsp[-2].pExpression));
        mkt->makeType = new TypeDecl(Type::autoinfer);
        (yyval.pExpression) = mkt;
    }
    break;

  case 968: /* $@94: %empty  */
                             { yyextra->das_force_oxford_comma=true; yyextra->das_arrow_depth ++; }
    break;

  case 969: /* $@95: %empty  */
                                                                                                                              { yyextra->das_arrow_depth --; }
    break;

  case 970: /* make_tuple_call: "tuple" '<' $@94 tuple_type_list '>' $@95 '(' use_initializer optional_make_struct_dim_decl ')'  */
                                                                                                                                                                                                                                 {
        auto mkt = new TypeDecl(Type::tTuple);
        mkt->at = tokAt(scanner,(yylsp[-9]));
        varDeclToTypeDecl(scanner, mkt, (yyvsp[-6].pVarDeclList), true);
        deleteVariableDeclarationList((yyvsp[-6].pVarDeclList));
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-9]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = mkt;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = (yyvsp[-2].b);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->forceTuple = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 971: /* make_dim: make_tuple  */
                        {
        auto mka = new ExprMakeArray();
        mka->values.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = mka;
    }
    break;

  case 972: /* make_dim: make_dim semicolon make_tuple  */
                                                {
        ((ExprMakeArray *) (yyvsp[-2].pExpression))->values.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = (yyvsp[-2].pExpression);
    }
    break;

  case 973: /* make_dim_decl: '[' optional_expr_list ']'  */
                                                    {
        if ( (yyvsp[-1].pExpression) ) {
            auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-2])));
            mka->values = sequenceToList((yyvsp[-1].pExpression));
            mka->makeType = new TypeDecl(Type::autoinfer);
            mka->gen2 = true;
            auto tam = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-2])),"to_array_move");
            tam->arguments.push_back(mka);
            (yyval.pExpression) = tam;
        } else {
            auto mks = new ExprMakeStruct();
            mks->at = tokAt(scanner,(yylsp[-2]));
            mks->makeType = new TypeDecl(Type::tArray);
            mks->makeType->firstType = new TypeDecl(Type::autoinfer);
            mks->useInitializer = true;
            mks->alwaysUseInitializer = true;
            (yyval.pExpression) = mks;
        }

    }
    break;

  case 974: /* make_dim_decl: "[[" type_declaration_no_options make_dim optional_trailing_semicolon_sqr_sqr  */
                                                                                                                   {
        // std::cout << "case13" << std::endl;
        if (format::prepare_rule(format::Pos::from(tokAt(scanner,(yylsp[-3]))))) {
            auto type_name = format::type_to_string((yyvsp[-2].pTypeDecl), tokAt(scanner,(yylsp[-2])));
            auto internal = format::handle_mka(tokAt(scanner, (yylsp[-2])),
                                               static_cast<ExprMakeArray*>((yyvsp[-1].pExpression)),
                                               tokAt(scanner, (yylsp[0])));
            const auto before = format::substring_between(tokAt(scanner, (yylsp[-3])), tokAt(scanner, (yylsp[-2])));
            if (static_cast<ExprMakeArray*>((yyvsp[-1].pExpression))->values.size() == 1) {
                // single element
                if (type_name.value_or("").find('[') != size_t(-1)) {
                    format::get_writer() << "fixed_array(" << before << internal << ")";
                } else {
                    format::get_writer() << before << internal;
                }
            } else {
                format::get_writer() << "fixed_array";
                if (!(yyvsp[-2].pTypeDecl)->isAuto()) {
                    format::get_writer() << "<" << type_name.value().substr(0, type_name.value().find('[')) << ">";
                }
                format::get_writer() << "(" << before << internal << ")";
            }
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[0]))));
        }
        ((ExprMakeArray *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-2].pTypeDecl);
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-3]));
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 975: /* make_dim_decl: "[{" type_declaration_no_options make_dim optional_trailing_semicolon_cur_sqr  */
                                                                                                                   {
        // std::cout << "case8" << std::endl;
        if (format::prepare_rule(format::Pos::from(tokAt(scanner,(yylsp[-3]))))) {
            string prefix = "[";
            string suffix = "]";
            if (!(yyvsp[-2].pTypeDecl)->isAuto()) {
                prefix = "array<" + format::get_substring(tokAt(scanner,(yylsp[-2]))) + ">(";
                suffix = ")";
            }
            format::get_writer() << prefix
                                 << format::substring_between(tokAt(scanner, (yylsp[-3])), tokAt(scanner, (yylsp[-2])))
                                 << format::handle_mka(tokAt(scanner, (yylsp[-2])),
                                                                 static_cast<ExprMakeArray*>((yyvsp[-1].pExpression)),
                                                                 tokAt(scanner, (yylsp[0])))
                                 << suffix;
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[0]))));
        }

        ((ExprMakeArray *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-2].pTypeDecl);
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-3]));
        auto tam = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-3])),"to_array_move");
        tam->arguments.push_back((yyvsp[-1].pExpression));
        (yyval.pExpression) = tam;
    }
    break;

  case 976: /* $@96: %empty  */
                                       { yyextra->das_arrow_depth ++; }
    break;

  case 977: /* $@97: %empty  */
                                                                                                             { yyextra->das_arrow_depth --; }
    break;

  case 978: /* make_dim_decl: "array" "struct" '<' $@96 type_declaration_no_options '>' $@97 '(' use_initializer optional_make_struct_dim_decl ')'  */
                                                                                                                                                                                                                {
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-10]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-6].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = (yyvsp[-2].b);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->forceStruct = true;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
        auto tam = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-10])),"to_array_move");
        tam->arguments.push_back((yyvsp[-1].pExpression));
        (yyval.pExpression) = tam;
    }
    break;

  case 979: /* $@98: %empty  */
                                       { yyextra->das_arrow_depth ++; }
    break;

  case 980: /* $@99: %empty  */
                                                                                                  { yyextra->das_arrow_depth --; }
    break;

  case 981: /* make_dim_decl: "array" "tuple" '<' $@98 tuple_type_list '>' $@99 '(' use_initializer optional_make_struct_dim_decl ')'  */
                                                                                                                                                                                                     {
        auto mkt = new TypeDecl(Type::tTuple);
        mkt->at = tokAt(scanner,(yylsp[-10]));
        varDeclToTypeDecl(scanner, mkt, (yyvsp[-6].pVarDeclList), true);
        deleteVariableDeclarationList((yyvsp[-6].pVarDeclList));
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-10]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = mkt;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = (yyvsp[-2].b);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->forceTuple = true;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
        auto tam = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-10])),"to_array_move");
        tam->arguments.push_back((yyvsp[-1].pExpression));
        (yyval.pExpression) = tam;
    }
    break;

  case 982: /* $@100: %empty  */
                                         { yyextra->das_arrow_depth ++; }
    break;

  case 983: /* $@101: %empty  */
                                                                                                      { yyextra->das_arrow_depth --; }
    break;

  case 984: /* make_dim_decl: "array" "variant" '<' $@100 variant_type_list '>' $@101 '(' make_variant_dim ')'  */
                                                                                                                                                                      {
        auto mkt = new TypeDecl(Type::tVariant);
        mkt->at = tokAt(scanner,(yylsp[-9]));
        varDeclToTypeDecl(scanner, mkt, (yyvsp[-5].pVarDeclList), true);
        deleteVariableDeclarationList((yyvsp[-5].pVarDeclList));
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-9]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = mkt;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = true;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->forceVariant = true;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
        auto tam = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-9])),"to_array_move");
        tam->arguments.push_back((yyvsp[-1].pExpression));
        (yyval.pExpression) = tam;
    }
    break;

  case 985: /* make_dim_decl: "array" '(' expr_list optional_comma ')'  */
                                                                   {
        auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-4])));
        mka->values = sequenceToList((yyvsp[-2].pExpression));
        mka->makeType = new TypeDecl(Type::autoinfer);
        mka->gen2 = true;
        auto tam = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-4])),"to_array_move");
        tam->arguments.push_back(mka);
        (yyval.pExpression) = tam;
    }
    break;

  case 986: /* $@102: %empty  */
                           { yyextra->das_arrow_depth ++; }
    break;

  case 987: /* $@103: %empty  */
                                                                                                 { yyextra->das_arrow_depth --; }
    break;

  case 988: /* make_dim_decl: "array" '<' $@102 type_declaration_no_options '>' $@103 '(' optional_expr_list ')'  */
                                                                                                                                                                        {
        if ( (yyvsp[-1].pExpression) ) {
            auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-8])));
            mka->values = sequenceToList((yyvsp[-1].pExpression));
            mka->makeType = (yyvsp[-5].pTypeDecl);
            mka->gen2 = true;
            auto tam = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-8])),"to_array_move");
            tam->arguments.push_back(mka);
            (yyval.pExpression) = tam;
        } else {
            auto msd = new ExprMakeStruct();
            msd->at = tokAt(scanner,(yylsp[-8]));
            msd->makeType = new TypeDecl(Type::tArray);
            msd->makeType->firstType = (yyvsp[-5].pTypeDecl);
            msd->at = tokAt(scanner,(yylsp[-5]));
            msd->useInitializer = true;
            msd->alwaysUseInitializer = true;
            (yyval.pExpression) = msd;
        }
    }
    break;

  case 989: /* make_dim_decl: "fixed_array" '(' expr_list optional_comma ')'  */
                                                                         {
        auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-4])));
        mka->values = sequenceToList((yyvsp[-2].pExpression));
        mka->makeType = new TypeDecl(Type::autoinfer);
        mka->gen2 = true;
        (yyval.pExpression) = mka;
    }
    break;

  case 990: /* $@104: %empty  */
                                 { yyextra->das_arrow_depth ++; }
    break;

  case 991: /* $@105: %empty  */
                                                                                                       { yyextra->das_arrow_depth --; }
    break;

  case 992: /* make_dim_decl: "fixed_array" '<' $@104 type_declaration_no_options '>' $@105 '(' expr_list optional_comma ')'  */
                                                                                                                                                                                    {
        auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-9])));
        mka->values = sequenceToList((yyvsp[-2].pExpression));
        mka->makeType = (yyvsp[-6].pTypeDecl);
        mka->gen2 = true;
        (yyval.pExpression) = mka;
    }
    break;

  case 993: /* make_table: make_map_tuple  */
                            {
        auto mka = new ExprMakeArray();
        mka->values.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = mka;
    }
    break;

  case 994: /* make_table: make_table semicolon make_map_tuple  */
                                                      {
        ((ExprMakeArray *) (yyvsp[-2].pExpression))->values.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = (yyvsp[-2].pExpression);
    }
    break;

  case 995: /* expr_map_tuple_list: make_map_tuple  */
                                {
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 996: /* expr_map_tuple_list: expr_map_tuple_list ',' make_map_tuple  */
                                                                {
            (yyval.pExpression) = new ExprSequence(tokAt(scanner,(yylsp[-2])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
    }
    break;

  case 997: /* make_table_decl: open_block optional_expr_map_tuple_list close_block  */
                                                                              {
        if ( (yyvsp[-1].pExpression) ) {
            auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-2])));
            mka->values = sequenceToList((yyvsp[-1].pExpression));
            mka->makeType = new TypeDecl(Type::autoinfer);
            auto ttm = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-2])),"to_table_move");
            ttm->arguments.push_back(mka);
            (yyval.pExpression) = ttm;
        } else {
            auto mks = new ExprMakeStruct();
            mks->at = tokAt(scanner,(yylsp[-2]));
            mks->makeType = new TypeDecl(Type::tTable);
            mks->makeType->firstType = new TypeDecl(Type::autoinfer);
            mks->makeType->secondType = new TypeDecl(Type::autoinfer);
            mks->useInitializer = true;
            mks->alwaysUseInitializer = true;
            (yyval.pExpression) = mks;
        }

    }
    break;

  case 998: /* make_table_decl: "{{" make_table optional_trailing_semicolon_cur_cur  */
                                                                                {
        // std::cout << "case10" << std::endl;
        if (format::prepare_rule(format::Pos::from(tokAt(scanner,(yylsp[-2]))))) {
            format::get_writer() << "{"
                                 << format::substring_between(tokAt(scanner, (yylsp[-2])), tokAt(scanner, (yylsp[-1])))
                                 << format::convert_to_string(((ExprMakeArray *)(yyvsp[-1].pExpression))->values, ",", ";")
                                 << format::substring_between(tokAt(scanner, (yylsp[-1])), tokAt(scanner, (yylsp[0])))
                                 << "}";
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[0]))));
        }

        auto mkt = new TypeDecl(Type::tFixedArray);
        mkt->fixedDim = TypeDecl::dimAuto;
        mkt->at = tokAt(scanner,(yylsp[-2]));
        mkt->firstType = new TypeDecl(Type::autoinfer);
        mkt->firstType->at = mkt->at;
        ((ExprMakeArray *)(yyvsp[-1].pExpression))->makeType = mkt;
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-2]));
        auto ttm = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-2])),"to_table_move");
        ttm->arguments.push_back((yyvsp[-1].pExpression));
        (yyval.pExpression) = ttm;
    }
    break;

  case 999: /* make_table_decl: "table" '(' optional_expr_map_tuple_list ')'  */
                                                                       {
        auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-3])));
        mka->values = sequenceToList((yyvsp[-1].pExpression));
        mka->makeType = new TypeDecl(Type::autoinfer);
        auto ttm = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-3])),"to_table_move");
        ttm->arguments.push_back(mka);
        (yyval.pExpression) = ttm;
    }
    break;

  case 1000: /* make_table_decl: "table" '<' type_declaration_no_options '>' '(' optional_expr_map_tuple_list ')'  */
                                                                                                                 {
        if ( (yyvsp[-1].pExpression) ) {
            auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-6])));
            mka->values = sequenceToList((yyvsp[-1].pExpression));
            mka->makeType = (yyvsp[-4].pTypeDecl);
            auto ttm = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-6])),"to_table_move");
            ttm->arguments.push_back(mka);
            (yyval.pExpression) = ttm;
        } else {
            auto msd = new ExprMakeStruct();
            msd->at = tokAt(scanner,(yylsp[-6]));
            msd->makeType = new TypeDecl(Type::tTable);
            msd->makeType->firstType = (yyvsp[-4].pTypeDecl);
            msd->makeType->secondType = new TypeDecl(Type::tVoid);
            msd->at = tokAt(scanner,(yylsp[-6]));
            msd->useInitializer = true;
            msd->alwaysUseInitializer = true;
            (yyval.pExpression) = msd;
        }
    }
    break;

  case 1001: /* make_table_decl: "table" '<' type_declaration_no_options c_or_s type_declaration_no_options '>' '(' optional_expr_map_tuple_list ')'  */
                                                                                                                                                             {
        if ( (yyvsp[-1].pExpression) ) {
            auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-8])));
            mka->values = sequenceToList((yyvsp[-1].pExpression));
            mka->makeType = new TypeDecl(Type::tTuple);
            mka->makeType->argTypes.push_back((yyvsp[-6].pTypeDecl));
            mka->makeType->argTypes.push_back((yyvsp[-4].pTypeDecl));
            auto ttm = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-8])),"to_table_move");
            ttm->arguments.push_back(mka);
            (yyval.pExpression) = ttm;
        } else {
            auto msd = new ExprMakeStruct();
            msd->at = tokAt(scanner,(yylsp[-8]));
            msd->makeType = new TypeDecl(Type::tTable);
            msd->makeType->firstType = (yyvsp[-6].pTypeDecl);
            msd->makeType->secondType = (yyvsp[-4].pTypeDecl);
            msd->at = tokAt(scanner,(yylsp[-8]));
            msd->useInitializer = true;
            msd->alwaysUseInitializer = true;
            (yyval.pExpression) = msd;
        }
    }
    break;

  case 1002: /* array_comprehension_where: %empty  */
                                    { (yyval.pExpression) = nullptr; }
    break;

  case 1003: /* array_comprehension_where: semicolon "where" expr  */
                                          { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 1004: /* optional_comma: %empty  */
                { (yyval.b) = false; }
    break;

  case 1005: /* optional_comma: ','  */
                { (yyval.b) = true; }
    break;

  case 1006: /* array_comprehension: '[' "for" variable_name_with_pos_list "in" expr_list "end of expression" expr2 array_comprehension_where ']'  */
                                                                                                                                                     {
        if (format::is_replace_braces() && format::prepare_rule(format::Pos::from(tokAt(scanner,(yylsp[-6]))))) {
            format::get_writer() << "(" << format::get_substring(format::Pos::from(tokAt(scanner,(yylsp[-6]))),
                                                                 format::Pos::from_last(tokAt(scanner,(yylsp[-4])))) << ")";
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[-4]))));
        }

        (yyval.pExpression) = ast_arrayComprehension(scanner,tokAt(scanner,(yylsp[-7])),(yyvsp[-6].pNameWithPosList),(yyvsp[-4].pExpression),(yyvsp[-2].pExpression),(yyvsp[-1].pExpression),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),false,false);
    }
    break;

  case 1007: /* array_comprehension: '[' "for" '(' variable_name_with_pos_list "in" expr_list ')' "end of expression" expr2 array_comprehension_where ']'  */
                                                                                                                                                            {
        (yyval.pExpression) = ast_arrayComprehension(scanner,tokAt(scanner,(yylsp[-9])),(yyvsp[-7].pNameWithPosList),(yyvsp[-5].pExpression),(yyvsp[-2].pExpression),(yyvsp[-1].pExpression),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),false,false);
    }
    break;

  case 1008: /* array_comprehension: '[' "iterator" "for" '(' variable_name_with_pos_list "in" expr_list ')' "end of expression" expr2 array_comprehension_where ']'  */
                                                                                                                                                                         {
        (yyval.pExpression) = ast_arrayComprehension(scanner,tokAt(scanner,(yylsp[-9])),(yyvsp[-7].pNameWithPosList),(yyvsp[-5].pExpression),(yyvsp[-2].pExpression),(yyvsp[-1].pExpression),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),true,false);
    }
    break;

  case 1009: /* array_comprehension: "begin of code block" "for" '(' variable_name_with_pos_list "in" expr_list ')' "end of expression" make_map_tuple array_comprehension_where "end of code block"  */
                                                                                                                                                                     {
        (yyval.pExpression) = ast_arrayComprehension(scanner,tokAt(scanner,(yylsp[-9])),(yyvsp[-7].pNameWithPosList),(yyvsp[-5].pExpression),(yyvsp[-2].pExpression),(yyvsp[-1].pExpression),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),false,true);
    }
    break;

  case 1010: /* array_comprehension: '[' "iterator" "for" variable_name_with_pos_list "in" expr_list "end of expression" expr2 array_comprehension_where ']'  */
                                                                                                                                                                  {
        if (format::is_replace_braces() && format::prepare_rule(format::Pos::from(tokAt(scanner,(yylsp[-6]))))) {
            format::get_writer() << "(" << format::get_substring(format::Pos::from(tokAt(scanner,(yylsp[-6]))),
                                                                 format::Pos::from_last(tokAt(scanner,(yylsp[-4])))) << ")";
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[-4]))));
        }
        (yyval.pExpression) = ast_arrayComprehension(scanner,tokAt(scanner,(yylsp[-7])),(yyvsp[-6].pNameWithPosList),(yyvsp[-4].pExpression),(yyvsp[-2].pExpression),(yyvsp[-1].pExpression),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),true,false);
    }
    break;

  case 1011: /* array_comprehension: "[[" "for" variable_name_with_pos_list "in" expr_list "end of expression" expr2 array_comprehension_where ']' ']'  */
                                                                                                                                                                         {
        // std::cout << "case5" << std::endl;
        if (format::prepare_rule(format::Pos::from(tokAt(scanner,(yylsp[-9]))))) {
            auto internal = format::get_substring(format::Pos::from(tokAt(scanner,(yylsp[-8]))), format::Pos::from_last(tokAt(scanner,(yylsp[-2]))));
            format::get_writer() << "[iterator " << internal << "]";
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[0]))));
        }
        (yyval.pExpression) = ast_arrayComprehension(scanner,tokAt(scanner,(yylsp[-8])),(yyvsp[-7].pNameWithPosList),(yyvsp[-5].pExpression),(yyvsp[-3].pExpression),(yyvsp[-2].pExpression),tokRangeAt(scanner,(yylsp[-3]),(yylsp[0])),true,false);
    }
    break;

  case 1012: /* array_comprehension: "[{" "for" variable_name_with_pos_list "in" expr_list "end of expression" expr2 array_comprehension_where "end of code block" ']'  */
                                                                                                                                                                                 {
        // std::cout << "case9" << std::endl;
        if (format::prepare_rule(format::Pos::from(tokAt(scanner,(yylsp[-9]))))) {
            auto internal = format::get_substring(format::Pos::from(tokAt(scanner,(yylsp[-8]))), format::Pos::from_last(tokAt(scanner,(yylsp[-2]))));
            format::get_writer() << "[" << format::substring_between(tokAt(scanner, (yylsp[-9])), tokAt(scanner, (yylsp[-8])))
                                 << internal
                                 << format::substring_between(tokAt(scanner, (yylsp[-2])), tokAt(scanner, (yylsp[-1]))) << "]";
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[0]))));
        }

        (yyval.pExpression) = ast_arrayComprehension(scanner,tokAt(scanner,(yylsp[-8])),(yyvsp[-7].pNameWithPosList),(yyvsp[-5].pExpression),(yyvsp[-3].pExpression),(yyvsp[-2].pExpression),tokRangeAt(scanner,(yylsp[-3]),(yylsp[0])),false,false);
    }
    break;

  case 1013: /* array_comprehension: open_block "for" variable_name_with_pos_list "in" expr_list "end of expression" make_map_tuple array_comprehension_where close_block  */
                                                                                                                                                                                        {
        if (format::is_replace_braces() && format::prepare_rule(format::Pos::from(tokAt(scanner,(yylsp[-6]))))) {
            format::get_writer() << "(" << format::substring_between(tokAt(scanner, (yylsp[-8])), tokAt(scanner, (yylsp[-7])))
                                 << format::get_substring(format::Pos::from(tokAt(scanner,(yylsp[-6]))),
                                                                 format::Pos::from_last(tokAt(scanner,(yylsp[-4]))))
                                 << format::substring_between(tokAt(scanner, (yylsp[-1])), tokAt(scanner, (yylsp[0]))) << ")";
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[-4]))));
        }
        (yyval.pExpression) = ast_arrayComprehension(scanner,tokAt(scanner,(yylsp[-7])),(yyvsp[-6].pNameWithPosList),(yyvsp[-4].pExpression),(yyvsp[-2].pExpression),(yyvsp[-1].pExpression),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),false,true);
    }
    break;

  case 1014: /* array_comprehension: "{{" "for" variable_name_with_pos_list "in" expr_list "end of expression" make_map_tuple array_comprehension_where close_block close_block  */
                                                                                                                                                                                                       {
        // std::cout << "case12" << std::endl;
        if (format::prepare_rule(format::Pos::from(tokAt(scanner,(yylsp[-9]))))) {
            auto internal = format::get_substring(format::Pos::from(tokAt(scanner,(yylsp[-8]))), format::Pos::from_last(tokAt(scanner,(yylsp[-2]))));
            format::get_writer() << "[" << format::substring_between(tokAt(scanner, (yylsp[-9])), tokAt(scanner, (yylsp[-8])))
                                 << internal
                                 << format::substring_between(tokAt(scanner, (yylsp[-2])), tokAt(scanner, (yylsp[-1]))) << "]";
            format::finish_rule(format::Pos::from_last(tokAt(scanner,(yylsp[0]))));
        }
        (yyval.pExpression) = ast_arrayComprehension(scanner,tokAt(scanner,(yylsp[-8])),(yyvsp[-7].pNameWithPosList),(yyvsp[-5].pExpression),(yyvsp[-3].pExpression),(yyvsp[-2].pExpression),tokRangeAt(scanner,(yylsp[-3]),(yylsp[0])),true,true);
    }
    break;



      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == DAS_YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= DAS_YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == DAS_YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, scanner);
          yychar = DAS_YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != DAS_YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}


