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
#define YYSTYPE         DAS2_YYSTYPE
#define YYLTYPE         DAS2_YYLTYPE
/* Substitute the variable and function names.  */
#define yyparse         das2_yyparse
#define yylex           das2_yylex
#define yyerror         das2_yyerror
#define yydebug         das2_yydebug
#define yynerrs         das2_yynerrs

/* First part of user prologue.  */

    #include "daScript/misc/platform.h"
    #include "daScript/simulate/debug_info.h"
    #include "daScript/ast/compilation_errors.h"

    #ifdef _MSC_VER
    #pragma warning(disable:4262)
    #pragma warning(disable:4127)
    #pragma warning(disable:4702)
    #endif

    using namespace das;

    union DAS2_YYSTYPE;
    struct DAS2_YYLTYPE;

    #define YY_NO_UNISTD_H
    #include "lex2.yy.h"

    void das2_yyerror ( DAS2_YYLTYPE * lloc, yyscan_t scanner, const string & error );
    void das2_yyfatalerror ( DAS2_YYLTYPE * lloc, yyscan_t scanner, const string & error, CompilationError cerr );
    int yylex ( DAS2_YYSTYPE *lvalp, DAS2_YYLTYPE *llocp, yyscan_t scanner );
    void yybegin ( const char * str );

    void das2_yybegin_reader ( yyscan_t yyscanner );
    void das2_yyend_reader ( yyscan_t yyscanner );
    void das2_accept_sequence ( yyscan_t yyscanner, const char * seq, size_t seqLen, int lineNo, FileInfo * info );
    void das2_strfmt ( yyscan_t yyscanner );

    namespace das { class Module; }
    void das2_collect_keywords ( das::Module * mod, yyscan_t yyscanner );

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

#include "ds2_parser.hpp"
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
  YYSYMBOL_DAS_TTUPLE = 102,               /* "tuple"  */
  YYSYMBOL_DAS_TVARIANT = 103,             /* "variant"  */
  YYSYMBOL_DAS_GENERATOR = 104,            /* "generator"  */
  YYSYMBOL_DAS_YIELD = 105,                /* "yield"  */
  YYSYMBOL_DAS_SEALED = 106,               /* "sealed"  */
  YYSYMBOL_DAS_TEMPLATE = 107,             /* "template"  */
  YYSYMBOL_ADDEQU = 108,                   /* "+="  */
  YYSYMBOL_SUBEQU = 109,                   /* "-="  */
  YYSYMBOL_DIVEQU = 110,                   /* "/="  */
  YYSYMBOL_MULEQU = 111,                   /* "*="  */
  YYSYMBOL_MODEQU = 112,                   /* "%="  */
  YYSYMBOL_ANDEQU = 113,                   /* "&="  */
  YYSYMBOL_OREQU = 114,                    /* "|="  */
  YYSYMBOL_XOREQU = 115,                   /* "^="  */
  YYSYMBOL_SHL = 116,                      /* "<<"  */
  YYSYMBOL_SHR = 117,                      /* ">>"  */
  YYSYMBOL_ADDADD = 118,                   /* "++"  */
  YYSYMBOL_SUBSUB = 119,                   /* "--"  */
  YYSYMBOL_LEEQU = 120,                    /* "<="  */
  YYSYMBOL_SHLEQU = 121,                   /* "<<="  */
  YYSYMBOL_SHREQU = 122,                   /* ">>="  */
  YYSYMBOL_GREQU = 123,                    /* ">="  */
  YYSYMBOL_EQUEQU = 124,                   /* "=="  */
  YYSYMBOL_NOTEQU = 125,                   /* "!="  */
  YYSYMBOL_RARROW = 126,                   /* "->"  */
  YYSYMBOL_LARROW = 127,                   /* "<-"  */
  YYSYMBOL_QQ = 128,                       /* "??"  */
  YYSYMBOL_QDOT = 129,                     /* "?."  */
  YYSYMBOL_QBRA = 130,                     /* "?["  */
  YYSYMBOL_LPIPE = 131,                    /* "<|"  */
  YYSYMBOL_RPIPE = 132,                    /* "|>"  */
  YYSYMBOL_CLONEEQU = 133,                 /* ":="  */
  YYSYMBOL_ROTL = 134,                     /* "<<<"  */
  YYSYMBOL_ROTR = 135,                     /* ">>>"  */
  YYSYMBOL_ROTLEQU = 136,                  /* "<<<="  */
  YYSYMBOL_ROTREQU = 137,                  /* ">>>="  */
  YYSYMBOL_MAPTO = 138,                    /* "=>"  */
  YYSYMBOL_DOUBLE_AT = 139,                /* "@@"  */
  YYSYMBOL_AT_FIELD = 140,                 /* "@field"  */
  YYSYMBOL_COLCOL = 141,                   /* "::"  */
  YYSYMBOL_ANDAND = 142,                   /* "&&"  */
  YYSYMBOL_OROR = 143,                     /* "||"  */
  YYSYMBOL_XORXOR = 144,                   /* "^^"  */
  YYSYMBOL_ANDANDEQU = 145,                /* "&&="  */
  YYSYMBOL_OROREQU = 146,                  /* "||="  */
  YYSYMBOL_XORXOREQU = 147,                /* "^^="  */
  YYSYMBOL_DOTDOT = 148,                   /* ".."  */
  YYSYMBOL_MTAG_E = 149,                   /* "$$"  */
  YYSYMBOL_MTAG_I = 150,                   /* "$i"  */
  YYSYMBOL_MTAG_V = 151,                   /* "$v"  */
  YYSYMBOL_MTAG_B = 152,                   /* "$b"  */
  YYSYMBOL_MTAG_A = 153,                   /* "$a"  */
  YYSYMBOL_MTAG_T = 154,                   /* "$t"  */
  YYSYMBOL_MTAG_C = 155,                   /* "$c"  */
  YYSYMBOL_MTAG_F = 156,                   /* "$f"  */
  YYSYMBOL_MTAG_DOTDOTDOT = 157,           /* "..."  */
  YYSYMBOL_INTEGER = 158,                  /* "integer constant"  */
  YYSYMBOL_LONG_INTEGER = 159,             /* "long integer constant"  */
  YYSYMBOL_UNSIGNED_INTEGER = 160,         /* "unsigned integer constant"  */
  YYSYMBOL_UNSIGNED_LONG_INTEGER = 161,    /* "unsigned long integer constant"  */
  YYSYMBOL_UNSIGNED_INT8 = 162,            /* "unsigned int8 constant"  */
  YYSYMBOL_DAS_FLOAT = 163,                /* "floating point constant"  */
  YYSYMBOL_DOUBLE = 164,                   /* "double constant"  */
  YYSYMBOL_NAME = 165,                     /* "name"  */
  YYSYMBOL_DAS_EMIT_COMMA = 166,           /* "new line, comma"  */
  YYSYMBOL_DAS_EMIT_SEMICOLON = 167,       /* "new line, semicolon"  */
  YYSYMBOL_BEGIN_STRING = 168,             /* "start of the string"  */
  YYSYMBOL_STRING_CHARACTER = 169,         /* STRING_CHARACTER  */
  YYSYMBOL_STRING_CHARACTER_ESC = 170,     /* STRING_CHARACTER_ESC  */
  YYSYMBOL_END_STRING = 171,               /* "end of the string"  */
  YYSYMBOL_BEGIN_STRING_EXPR = 172,        /* "{"  */
  YYSYMBOL_END_STRING_EXPR = 173,          /* "}"  */
  YYSYMBOL_END_OF_READ = 174,              /* "end of failed eader macro"  */
  YYSYMBOL_175_ = 175,                     /* ','  */
  YYSYMBOL_176_ = 176,                     /* '='  */
  YYSYMBOL_177_ = 177,                     /* '?'  */
  YYSYMBOL_178_ = 178,                     /* ':'  */
  YYSYMBOL_179_ = 179,                     /* '|'  */
  YYSYMBOL_180_ = 180,                     /* '^'  */
  YYSYMBOL_181_ = 181,                     /* '&'  */
  YYSYMBOL_182_ = 182,                     /* '<'  */
  YYSYMBOL_183_ = 183,                     /* '>'  */
  YYSYMBOL_184_ = 184,                     /* '-'  */
  YYSYMBOL_185_ = 185,                     /* '+'  */
  YYSYMBOL_186_ = 186,                     /* '*'  */
  YYSYMBOL_187_ = 187,                     /* '/'  */
  YYSYMBOL_188_ = 188,                     /* '%'  */
  YYSYMBOL_UNARY_MINUS = 189,              /* UNARY_MINUS  */
  YYSYMBOL_UNARY_PLUS = 190,               /* UNARY_PLUS  */
  YYSYMBOL_191_ = 191,                     /* '~'  */
  YYSYMBOL_192_ = 192,                     /* '!'  */
  YYSYMBOL_PRE_INC = 193,                  /* PRE_INC  */
  YYSYMBOL_PRE_DEC = 194,                  /* PRE_DEC  */
  YYSYMBOL_LLPIPE = 195,                   /* LLPIPE  */
  YYSYMBOL_POST_INC = 196,                 /* POST_INC  */
  YYSYMBOL_POST_DEC = 197,                 /* POST_DEC  */
  YYSYMBOL_DEREF = 198,                    /* DEREF  */
  YYSYMBOL_199_ = 199,                     /* '.'  */
  YYSYMBOL_200_ = 200,                     /* '['  */
  YYSYMBOL_201_ = 201,                     /* ']'  */
  YYSYMBOL_202_ = 202,                     /* '('  */
  YYSYMBOL_203_ = 203,                     /* ')'  */
  YYSYMBOL_204_ = 204,                     /* '$'  */
  YYSYMBOL_205_ = 205,                     /* '@'  */
  YYSYMBOL_206_ = 206,                     /* ';'  */
  YYSYMBOL_207_ = 207,                     /* '{'  */
  YYSYMBOL_208_ = 208,                     /* '}'  */
  YYSYMBOL_209_ = 209,                     /* '#'  */
  YYSYMBOL_YYACCEPT = 210,                 /* $accept  */
  YYSYMBOL_program = 211,                  /* program  */
  YYSYMBOL_COMMA = 212,                    /* COMMA  */
  YYSYMBOL_SEMICOLON = 213,                /* SEMICOLON  */
  YYSYMBOL_top_level_reader_macro = 214,   /* top_level_reader_macro  */
  YYSYMBOL_optional_public_or_private_module = 215, /* optional_public_or_private_module  */
  YYSYMBOL_module_name = 216,              /* module_name  */
  YYSYMBOL_optional_not_required = 217,    /* optional_not_required  */
  YYSYMBOL_module_declaration = 218,       /* module_declaration  */
  YYSYMBOL_character_sequence = 219,       /* character_sequence  */
  YYSYMBOL_string_constant = 220,          /* string_constant  */
  YYSYMBOL_format_string = 221,            /* format_string  */
  YYSYMBOL_optional_format_string = 222,   /* optional_format_string  */
  YYSYMBOL_223_1 = 223,                    /* $@1  */
  YYSYMBOL_string_builder_body = 224,      /* string_builder_body  */
  YYSYMBOL_string_builder = 225,           /* string_builder  */
  YYSYMBOL_reader_character_sequence = 226, /* reader_character_sequence  */
  YYSYMBOL_expr_reader = 227,              /* expr_reader  */
  YYSYMBOL_228_2 = 228,                    /* $@2  */
  YYSYMBOL_options_declaration = 229,      /* options_declaration  */
  YYSYMBOL_require_declaration = 230,      /* require_declaration  */
  YYSYMBOL_require_module_name = 231,      /* require_module_name  */
  YYSYMBOL_optional_require_guard = 232,   /* optional_require_guard  */
  YYSYMBOL_require_module = 233,           /* require_module  */
  YYSYMBOL_is_public_module = 234,         /* is_public_module  */
  YYSYMBOL_expect_declaration = 235,       /* expect_declaration  */
  YYSYMBOL_expect_list = 236,              /* expect_list  */
  YYSYMBOL_expect_error = 237,             /* expect_error  */
  YYSYMBOL_expression_label = 238,         /* expression_label  */
  YYSYMBOL_expression_goto = 239,          /* expression_goto  */
  YYSYMBOL_elif_or_static_elif = 240,      /* elif_or_static_elif  */
  YYSYMBOL_emit_semis = 241,               /* emit_semis  */
  YYSYMBOL_optional_emit_semis = 242,      /* optional_emit_semis  */
  YYSYMBOL_expression_else = 243,          /* expression_else  */
  YYSYMBOL_244_3 = 244,                    /* $@3  */
  YYSYMBOL_245_4 = 245,                    /* $@4  */
  YYSYMBOL_if_or_static_if = 246,          /* if_or_static_if  */
  YYSYMBOL_expression_else_one_liner = 247, /* expression_else_one_liner  */
  YYSYMBOL_expression_if_one_liner = 248,  /* expression_if_one_liner  */
  YYSYMBOL_semis = 249,                    /* semis  */
  YYSYMBOL_optional_semis = 250,           /* optional_semis  */
  YYSYMBOL_expression_if_block = 251,      /* expression_if_block  */
  YYSYMBOL_252_5 = 252,                    /* $@5  */
  YYSYMBOL_253_6 = 253,                    /* $@6  */
  YYSYMBOL_254_7 = 254,                    /* $@7  */
  YYSYMBOL_expression_else_block = 255,    /* expression_else_block  */
  YYSYMBOL_256_8 = 256,                    /* $@8  */
  YYSYMBOL_257_9 = 257,                    /* $@9  */
  YYSYMBOL_258_10 = 258,                   /* $@10  */
  YYSYMBOL_expression_if_then_else = 259,  /* expression_if_then_else  */
  YYSYMBOL_260_11 = 260,                   /* $@11  */
  YYSYMBOL_261_12 = 261,                   /* $@12  */
  YYSYMBOL_expression_if_then_else_oneliner = 262, /* expression_if_then_else_oneliner  */
  YYSYMBOL_for_variable_name_with_pos_list = 263, /* for_variable_name_with_pos_list  */
  YYSYMBOL_expression_for_loop = 264,      /* expression_for_loop  */
  YYSYMBOL_265_13 = 265,                   /* $@13  */
  YYSYMBOL_expression_unsafe = 266,        /* expression_unsafe  */
  YYSYMBOL_expression_while_loop = 267,    /* expression_while_loop  */
  YYSYMBOL_268_14 = 268,                   /* $@14  */
  YYSYMBOL_expression_with = 269,          /* expression_with  */
  YYSYMBOL_270_15 = 270,                   /* $@15  */
  YYSYMBOL_expression_with_alias = 271,    /* expression_with_alias  */
  YYSYMBOL_annotation_argument_value = 272, /* annotation_argument_value  */
  YYSYMBOL_annotation_argument_value_list = 273, /* annotation_argument_value_list  */
  YYSYMBOL_annotation_argument_name = 274, /* annotation_argument_name  */
  YYSYMBOL_annotation_argument = 275,      /* annotation_argument  */
  YYSYMBOL_annotation_argument_list = 276, /* annotation_argument_list  */
  YYSYMBOL_metadata_argument_list = 277,   /* metadata_argument_list  */
  YYSYMBOL_optional_for_annotations = 278, /* optional_for_annotations  */
  YYSYMBOL_annotation_declaration_name = 279, /* annotation_declaration_name  */
  YYSYMBOL_annotation_declaration_basic = 280, /* annotation_declaration_basic  */
  YYSYMBOL_annotation_declaration = 281,   /* annotation_declaration  */
  YYSYMBOL_annotation_list = 282,          /* annotation_list  */
  YYSYMBOL_optional_annotation_list = 283, /* optional_annotation_list  */
  YYSYMBOL_optional_annotation_list_with_emit_semis = 284, /* optional_annotation_list_with_emit_semis  */
  YYSYMBOL_optional_function_argument_list = 285, /* optional_function_argument_list  */
  YYSYMBOL_optional_function_type = 286,   /* optional_function_type  */
  YYSYMBOL_function_name = 287,            /* function_name  */
  YYSYMBOL_das_type_name = 288,            /* das_type_name  */
  YYSYMBOL_optional_template = 289,        /* optional_template  */
  YYSYMBOL_global_function_declaration = 290, /* global_function_declaration  */
  YYSYMBOL_optional_public_or_private_function = 291, /* optional_public_or_private_function  */
  YYSYMBOL_function_declaration_header = 292, /* function_declaration_header  */
  YYSYMBOL_function_declaration = 293,     /* function_declaration  */
  YYSYMBOL_294_16 = 294,                   /* $@16  */
  YYSYMBOL_expression_block_finally = 295, /* expression_block_finally  */
  YYSYMBOL_296_17 = 296,                   /* $@17  */
  YYSYMBOL_297_18 = 297,                   /* $@18  */
  YYSYMBOL_expression_block = 298,         /* expression_block  */
  YYSYMBOL_299_19 = 299,                   /* $@19  */
  YYSYMBOL_300_20 = 300,                   /* $@20  */
  YYSYMBOL_expr_call_pipe_no_bracket = 301, /* expr_call_pipe_no_bracket  */
  YYSYMBOL_expression_any = 302,           /* expression_any  */
  YYSYMBOL_303_21 = 303,                   /* $@21  */
  YYSYMBOL_304_22 = 304,                   /* $@22  */
  YYSYMBOL_expressions = 305,              /* expressions  */
  YYSYMBOL_optional_expr_list = 306,       /* optional_expr_list  */
  YYSYMBOL_optional_expr_map_tuple_list = 307, /* optional_expr_map_tuple_list  */
  YYSYMBOL_type_declaration_no_options_list = 308, /* type_declaration_no_options_list  */
  YYSYMBOL_name_in_namespace = 309,        /* name_in_namespace  */
  YYSYMBOL_expression_delete = 310,        /* expression_delete  */
  YYSYMBOL_new_type_declaration = 311,     /* new_type_declaration  */
  YYSYMBOL_312_23 = 312,                   /* $@23  */
  YYSYMBOL_313_24 = 313,                   /* $@24  */
  YYSYMBOL_expr_new = 314,                 /* expr_new  */
  YYSYMBOL_expression_break = 315,         /* expression_break  */
  YYSYMBOL_expression_continue = 316,      /* expression_continue  */
  YYSYMBOL_expression_return = 317,        /* expression_return  */
  YYSYMBOL_expression_yield = 318,         /* expression_yield  */
  YYSYMBOL_expression_try_catch = 319,     /* expression_try_catch  */
  YYSYMBOL_kwd_let_var_or_nothing = 320,   /* kwd_let_var_or_nothing  */
  YYSYMBOL_kwd_let = 321,                  /* kwd_let  */
  YYSYMBOL_optional_in_scope = 322,        /* optional_in_scope  */
  YYSYMBOL_tuple_expansion = 323,          /* tuple_expansion  */
  YYSYMBOL_tuple_expansion_variable_declaration = 324, /* tuple_expansion_variable_declaration  */
  YYSYMBOL_expression_let = 325,           /* expression_let  */
  YYSYMBOL_expr_cast = 326,                /* expr_cast  */
  YYSYMBOL_327_25 = 327,                   /* $@25  */
  YYSYMBOL_328_26 = 328,                   /* $@26  */
  YYSYMBOL_329_27 = 329,                   /* $@27  */
  YYSYMBOL_330_28 = 330,                   /* $@28  */
  YYSYMBOL_331_29 = 331,                   /* $@29  */
  YYSYMBOL_332_30 = 332,                   /* $@30  */
  YYSYMBOL_expr_type_decl = 333,           /* expr_type_decl  */
  YYSYMBOL_334_31 = 334,                   /* $@31  */
  YYSYMBOL_335_32 = 335,                   /* $@32  */
  YYSYMBOL_expr_type_info = 336,           /* expr_type_info  */
  YYSYMBOL_expr_list = 337,                /* expr_list  */
  YYSYMBOL_block_or_simple_block = 338,    /* block_or_simple_block  */
  YYSYMBOL_block_or_lambda = 339,          /* block_or_lambda  */
  YYSYMBOL_capture_entry = 340,            /* capture_entry  */
  YYSYMBOL_capture_list = 341,             /* capture_list  */
  YYSYMBOL_optional_capture_list = 342,    /* optional_capture_list  */
  YYSYMBOL_expr_full_block = 343,          /* expr_full_block  */
  YYSYMBOL_expr_full_block_assumed_piped = 344, /* expr_full_block_assumed_piped  */
  YYSYMBOL_expr_numeric_const = 345,       /* expr_numeric_const  */
  YYSYMBOL_expr_assign_no_bracket = 346,   /* expr_assign_no_bracket  */
  YYSYMBOL_expr_named_call = 347,          /* expr_named_call  */
  YYSYMBOL_expr_method_call_no_bracket = 348, /* expr_method_call_no_bracket  */
  YYSYMBOL_func_addr_name = 349,           /* func_addr_name  */
  YYSYMBOL_func_addr_expr = 350,           /* func_addr_expr  */
  YYSYMBOL_351_33 = 351,                   /* $@33  */
  YYSYMBOL_352_34 = 352,                   /* $@34  */
  YYSYMBOL_353_35 = 353,                   /* $@35  */
  YYSYMBOL_354_36 = 354,                   /* $@36  */
  YYSYMBOL_expr_field_no_bracket = 355,    /* expr_field_no_bracket  */
  YYSYMBOL_356_37 = 356,                   /* $@37  */
  YYSYMBOL_357_38 = 357,                   /* $@38  */
  YYSYMBOL_expr_call = 358,                /* expr_call  */
  YYSYMBOL_expr = 359,                     /* expr  */
  YYSYMBOL_expr_no_bracket = 360,          /* expr_no_bracket  */
  YYSYMBOL_361_39 = 361,                   /* $@39  */
  YYSYMBOL_362_40 = 362,                   /* $@40  */
  YYSYMBOL_363_41 = 363,                   /* $@41  */
  YYSYMBOL_364_42 = 364,                   /* $@42  */
  YYSYMBOL_365_43 = 365,                   /* $@43  */
  YYSYMBOL_366_44 = 366,                   /* $@44  */
  YYSYMBOL_expr_generator = 367,           /* expr_generator  */
  YYSYMBOL_expr_mtag_no_bracket = 368,     /* expr_mtag_no_bracket  */
  YYSYMBOL_optional_field_annotation = 369, /* optional_field_annotation  */
  YYSYMBOL_optional_override = 370,        /* optional_override  */
  YYSYMBOL_optional_constant = 371,        /* optional_constant  */
  YYSYMBOL_optional_public_or_private_member_variable = 372, /* optional_public_or_private_member_variable  */
  YYSYMBOL_optional_static_member_variable = 373, /* optional_static_member_variable  */
  YYSYMBOL_structure_variable_declaration = 374, /* structure_variable_declaration  */
  YYSYMBOL_struct_variable_declaration_list = 375, /* struct_variable_declaration_list  */
  YYSYMBOL_376_45 = 376,                   /* $@45  */
  YYSYMBOL_377_46 = 377,                   /* $@46  */
  YYSYMBOL_378_47 = 378,                   /* $@47  */
  YYSYMBOL_function_argument_declaration_no_type = 379, /* function_argument_declaration_no_type  */
  YYSYMBOL_function_argument_declaration_type = 380, /* function_argument_declaration_type  */
  YYSYMBOL_function_argument_list = 381,   /* function_argument_list  */
  YYSYMBOL_tuple_type = 382,               /* tuple_type  */
  YYSYMBOL_tuple_type_list = 383,          /* tuple_type_list  */
  YYSYMBOL_tuple_alias_type_list = 384,    /* tuple_alias_type_list  */
  YYSYMBOL_variant_type = 385,             /* variant_type  */
  YYSYMBOL_variant_type_list = 386,        /* variant_type_list  */
  YYSYMBOL_variant_alias_type_list = 387,  /* variant_alias_type_list  */
  YYSYMBOL_copy_or_move = 388,             /* copy_or_move  */
  YYSYMBOL_variable_declaration_no_type = 389, /* variable_declaration_no_type  */
  YYSYMBOL_variable_declaration_type = 390, /* variable_declaration_type  */
  YYSYMBOL_variable_declaration = 391,     /* variable_declaration  */
  YYSYMBOL_copy_or_move_or_clone = 392,    /* copy_or_move_or_clone  */
  YYSYMBOL_optional_ref = 393,             /* optional_ref  */
  YYSYMBOL_let_variable_name_with_pos_list = 394, /* let_variable_name_with_pos_list  */
  YYSYMBOL_global_let_variable_name_with_pos_list = 395, /* global_let_variable_name_with_pos_list  */
  YYSYMBOL_variable_declaration_list = 396, /* variable_declaration_list  */
  YYSYMBOL_let_variable_declaration = 397, /* let_variable_declaration  */
  YYSYMBOL_global_let_variable_declaration = 398, /* global_let_variable_declaration  */
  YYSYMBOL_optional_shared = 399,          /* optional_shared  */
  YYSYMBOL_optional_public_or_private_variable = 400, /* optional_public_or_private_variable  */
  YYSYMBOL_global_variable_declaration_list = 401, /* global_variable_declaration_list  */
  YYSYMBOL_402_48 = 402,                   /* $@48  */
  YYSYMBOL_global_let = 403,               /* global_let  */
  YYSYMBOL_404_49 = 404,                   /* $@49  */
  YYSYMBOL_enum_expression = 405,          /* enum_expression  */
  YYSYMBOL_commas = 406,                   /* commas  */
  YYSYMBOL_enum_list = 407,                /* enum_list  */
  YYSYMBOL_optional_public_or_private_alias = 408, /* optional_public_or_private_alias  */
  YYSYMBOL_single_alias = 409,             /* single_alias  */
  YYSYMBOL_410_50 = 410,                   /* $@50  */
  YYSYMBOL_alias_declaration = 411,        /* alias_declaration  */
  YYSYMBOL_optional_public_or_private_enum = 412, /* optional_public_or_private_enum  */
  YYSYMBOL_enum_name = 413,                /* enum_name  */
  YYSYMBOL_optional_enum_basic_type_declaration = 414, /* optional_enum_basic_type_declaration  */
  YYSYMBOL_optional_commas = 415,          /* optional_commas  */
  YYSYMBOL_emit_commas = 416,              /* emit_commas  */
  YYSYMBOL_optional_emit_commas = 417,     /* optional_emit_commas  */
  YYSYMBOL_enum_declaration = 418,         /* enum_declaration  */
  YYSYMBOL_419_51 = 419,                   /* $@51  */
  YYSYMBOL_420_52 = 420,                   /* $@52  */
  YYSYMBOL_421_53 = 421,                   /* $@53  */
  YYSYMBOL_optional_structure_parent = 422, /* optional_structure_parent  */
  YYSYMBOL_optional_sealed = 423,          /* optional_sealed  */
  YYSYMBOL_structure_name = 424,           /* structure_name  */
  YYSYMBOL_class_or_struct = 425,          /* class_or_struct  */
  YYSYMBOL_optional_public_or_private_structure = 426, /* optional_public_or_private_structure  */
  YYSYMBOL_optional_struct_variable_declaration_list = 427, /* optional_struct_variable_declaration_list  */
  YYSYMBOL_structure_declaration = 428,    /* structure_declaration  */
  YYSYMBOL_429_54 = 429,                   /* $@54  */
  YYSYMBOL_430_55 = 430,                   /* $@55  */
  YYSYMBOL_431_56 = 431,                   /* $@56  */
  YYSYMBOL_variable_name_with_pos_list = 432, /* variable_name_with_pos_list  */
  YYSYMBOL_basic_type_declaration = 433,   /* basic_type_declaration  */
  YYSYMBOL_enum_basic_type_declaration = 434, /* enum_basic_type_declaration  */
  YYSYMBOL_structure_type_declaration = 435, /* structure_type_declaration  */
  YYSYMBOL_auto_type_declaration = 436,    /* auto_type_declaration  */
  YYSYMBOL_bitfield_bits = 437,            /* bitfield_bits  */
  YYSYMBOL_bitfield_alias_bits = 438,      /* bitfield_alias_bits  */
  YYSYMBOL_bitfield_basic_type_declaration = 439, /* bitfield_basic_type_declaration  */
  YYSYMBOL_bitfield_type_declaration = 440, /* bitfield_type_declaration  */
  YYSYMBOL_441_57 = 441,                   /* $@57  */
  YYSYMBOL_442_58 = 442,                   /* $@58  */
  YYSYMBOL_c_or_s = 443,                   /* c_or_s  */
  YYSYMBOL_table_type_pair = 444,          /* table_type_pair  */
  YYSYMBOL_dim_list = 445,                 /* dim_list  */
  YYSYMBOL_type_declaration_no_options = 446, /* type_declaration_no_options  */
  YYSYMBOL_optional_expr_list_in_braces = 447, /* optional_expr_list_in_braces  */
  YYSYMBOL_type_declaration_no_options_no_dim = 448, /* type_declaration_no_options_no_dim  */
  YYSYMBOL_449_59 = 449,                   /* $@59  */
  YYSYMBOL_450_60 = 450,                   /* $@60  */
  YYSYMBOL_451_61 = 451,                   /* $@61  */
  YYSYMBOL_452_62 = 452,                   /* $@62  */
  YYSYMBOL_453_63 = 453,                   /* $@63  */
  YYSYMBOL_454_64 = 454,                   /* $@64  */
  YYSYMBOL_455_65 = 455,                   /* $@65  */
  YYSYMBOL_456_66 = 456,                   /* $@66  */
  YYSYMBOL_457_67 = 457,                   /* $@67  */
  YYSYMBOL_458_68 = 458,                   /* $@68  */
  YYSYMBOL_459_69 = 459,                   /* $@69  */
  YYSYMBOL_460_70 = 460,                   /* $@70  */
  YYSYMBOL_461_71 = 461,                   /* $@71  */
  YYSYMBOL_462_72 = 462,                   /* $@72  */
  YYSYMBOL_463_73 = 463,                   /* $@73  */
  YYSYMBOL_464_74 = 464,                   /* $@74  */
  YYSYMBOL_465_75 = 465,                   /* $@75  */
  YYSYMBOL_466_76 = 466,                   /* $@76  */
  YYSYMBOL_467_77 = 467,                   /* $@77  */
  YYSYMBOL_468_78 = 468,                   /* $@78  */
  YYSYMBOL_469_79 = 469,                   /* $@79  */
  YYSYMBOL_470_80 = 470,                   /* $@80  */
  YYSYMBOL_471_81 = 471,                   /* $@81  */
  YYSYMBOL_472_82 = 472,                   /* $@82  */
  YYSYMBOL_473_83 = 473,                   /* $@83  */
  YYSYMBOL_474_84 = 474,                   /* $@84  */
  YYSYMBOL_475_85 = 475,                   /* $@85  */
  YYSYMBOL_476_86 = 476,                   /* $@86  */
  YYSYMBOL_type_declaration = 477,         /* type_declaration  */
  YYSYMBOL_tuple_alias_declaration = 478,  /* tuple_alias_declaration  */
  YYSYMBOL_479_87 = 479,                   /* $@87  */
  YYSYMBOL_480_88 = 480,                   /* $@88  */
  YYSYMBOL_481_89 = 481,                   /* $@89  */
  YYSYMBOL_482_90 = 482,                   /* $@90  */
  YYSYMBOL_variant_alias_declaration = 483, /* variant_alias_declaration  */
  YYSYMBOL_484_91 = 484,                   /* $@91  */
  YYSYMBOL_485_92 = 485,                   /* $@92  */
  YYSYMBOL_486_93 = 486,                   /* $@93  */
  YYSYMBOL_487_94 = 487,                   /* $@94  */
  YYSYMBOL_bitfield_alias_declaration = 488, /* bitfield_alias_declaration  */
  YYSYMBOL_489_95 = 489,                   /* $@95  */
  YYSYMBOL_490_96 = 490,                   /* $@96  */
  YYSYMBOL_491_97 = 491,                   /* $@97  */
  YYSYMBOL_492_98 = 492,                   /* $@98  */
  YYSYMBOL_make_decl = 493,                /* make_decl  */
  YYSYMBOL_make_decl_no_bracket = 494,     /* make_decl_no_bracket  */
  YYSYMBOL_make_struct_fields = 495,       /* make_struct_fields  */
  YYSYMBOL_make_variant_dim = 496,         /* make_variant_dim  */
  YYSYMBOL_make_struct_single = 497,       /* make_struct_single  */
  YYSYMBOL_make_struct_dim_list = 498,     /* make_struct_dim_list  */
  YYSYMBOL_make_struct_dim_decl = 499,     /* make_struct_dim_decl  */
  YYSYMBOL_optional_make_struct_dim_decl = 500, /* optional_make_struct_dim_decl  */
  YYSYMBOL_use_initializer = 501,          /* use_initializer  */
  YYSYMBOL_make_struct_decl = 502,         /* make_struct_decl  */
  YYSYMBOL_503_99 = 503,                   /* $@99  */
  YYSYMBOL_504_100 = 504,                  /* $@100  */
  YYSYMBOL_505_101 = 505,                  /* $@101  */
  YYSYMBOL_506_102 = 506,                  /* $@102  */
  YYSYMBOL_507_103 = 507,                  /* $@103  */
  YYSYMBOL_508_104 = 508,                  /* $@104  */
  YYSYMBOL_509_105 = 509,                  /* $@105  */
  YYSYMBOL_510_106 = 510,                  /* $@106  */
  YYSYMBOL_511_107 = 511,                  /* $@107  */
  YYSYMBOL_512_108 = 512,                  /* $@108  */
  YYSYMBOL_make_tuple_call = 513,          /* make_tuple_call  */
  YYSYMBOL_514_109 = 514,                  /* $@109  */
  YYSYMBOL_515_110 = 515,                  /* $@110  */
  YYSYMBOL_make_dim_decl = 516,            /* make_dim_decl  */
  YYSYMBOL_517_111 = 517,                  /* $@111  */
  YYSYMBOL_518_112 = 518,                  /* $@112  */
  YYSYMBOL_519_113 = 519,                  /* $@113  */
  YYSYMBOL_520_114 = 520,                  /* $@114  */
  YYSYMBOL_521_115 = 521,                  /* $@115  */
  YYSYMBOL_522_116 = 522,                  /* $@116  */
  YYSYMBOL_523_117 = 523,                  /* $@117  */
  YYSYMBOL_524_118 = 524,                  /* $@118  */
  YYSYMBOL_525_119 = 525,                  /* $@119  */
  YYSYMBOL_526_120 = 526,                  /* $@120  */
  YYSYMBOL_expr_map_tuple_list = 527,      /* expr_map_tuple_list  */
  YYSYMBOL_push_table_nesting = 528,       /* push_table_nesting  */
  YYSYMBOL_make_table_decl = 529,          /* make_table_decl  */
  YYSYMBOL_make_table_call = 530,          /* make_table_call  */
  YYSYMBOL_array_comprehension_where = 531, /* array_comprehension_where  */
  YYSYMBOL_optional_comma = 532,           /* optional_comma  */
  YYSYMBOL_table_comprehension = 533,      /* table_comprehension  */
  YYSYMBOL_array_comprehension = 534       /* array_comprehension  */
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
         || (defined DAS2_YYLTYPE_IS_TRIVIAL && DAS2_YYLTYPE_IS_TRIVIAL \
             && defined DAS2_YYSTYPE_IS_TRIVIAL && DAS2_YYSTYPE_IS_TRIVIAL)))

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
#define YYLAST   9847

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  210
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  325
/* YYNRULES -- Number of rules.  */
#define YYNRULES  962
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1727

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   437


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
       2,     2,     2,   192,     2,   209,   204,   188,   181,     2,
     202,   203,   186,   185,   175,   184,   199,   187,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   178,   206,
     182,   176,   183,   177,   205,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   200,     2,   201,   180,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   207,   179,   208,   191,     2,     2,     2,
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
     189,   190,   193,   194,   195,   196,   197,   198
};

#if DAS2_YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   570,   570,   571,   576,   577,   578,   579,   580,   581,
     582,   583,   584,   585,   586,   587,   588,   592,   593,   597,
     598,   602,   608,   609,   610,   614,   615,   619,   620,   624,
     643,   644,   645,   646,   650,   651,   655,   656,   660,   661,
     661,   665,   670,   679,   694,   710,   715,   723,   723,   762,
     780,   784,   787,   791,   795,   799,   803,   809,   818,   819,
     823,   826,   832,   833,   837,   841,   842,   846,   849,   855,
     861,   864,   870,   871,   875,   876,   880,   881,   885,   886,
     886,   890,   890,   899,   900,   904,   905,   911,   912,   913,
     914,   915,   919,   920,   924,   925,   929,   931,   929,   943,
     943,   951,   953,   951,   965,   965,   973,   975,   973,   986,
     993,  1000,  1005,  1014,  1022,  1028,  1032,  1040,  1050,  1050,
    1059,  1067,  1067,  1081,  1081,  1093,  1097,  1104,  1105,  1106,
    1107,  1108,  1109,  1113,  1118,  1126,  1127,  1128,  1132,  1133,
    1134,  1135,  1136,  1137,  1138,  1139,  1140,  1146,  1149,  1155,
    1158,  1164,  1167,  1170,  1176,  1177,  1178,  1179,  1183,  1201,
    1224,  1227,  1237,  1252,  1267,  1282,  1285,  1292,  1296,  1303,
    1304,  1308,  1309,  1313,  1314,  1315,  1319,  1322,  1326,  1333,
    1337,  1338,  1339,  1340,  1341,  1342,  1343,  1344,  1345,  1346,
    1347,  1348,  1349,  1350,  1351,  1352,  1353,  1354,  1355,  1356,
    1357,  1358,  1359,  1360,  1361,  1362,  1363,  1364,  1365,  1366,
    1367,  1368,  1369,  1370,  1371,  1372,  1373,  1374,  1375,  1376,
    1377,  1378,  1379,  1380,  1381,  1382,  1383,  1384,  1385,  1386,
    1387,  1388,  1389,  1390,  1391,  1392,  1393,  1394,  1395,  1396,
    1397,  1398,  1399,  1400,  1401,  1402,  1403,  1404,  1405,  1406,
    1407,  1408,  1409,  1410,  1411,  1412,  1413,  1414,  1415,  1416,
    1417,  1418,  1419,  1420,  1421,  1422,  1423,  1424,  1428,  1429,
    1430,  1431,  1432,  1433,  1434,  1435,  1436,  1437,  1438,  1439,
    1440,  1441,  1442,  1443,  1444,  1445,  1446,  1447,  1448,  1449,
    1450,  1451,  1452,  1456,  1457,  1461,  1480,  1481,  1482,  1486,
    1492,  1492,  1509,  1512,  1514,  1512,  1522,  1524,  1522,  1539,
    1557,  1575,  1593,  1604,  1605,  1606,  1607,  1608,  1609,  1610,
    1611,  1612,  1613,  1614,  1615,  1616,  1617,  1618,  1619,  1620,
    1621,  1622,  1623,  1625,  1623,  1640,  1645,  1651,  1657,  1658,
    1662,  1663,  1667,  1671,  1678,  1679,  1690,  1694,  1697,  1705,
    1705,  1705,  1708,  1714,  1717,  1721,  1725,  1732,  1739,  1745,
    1749,  1753,  1756,  1759,  1767,  1770,  1778,  1784,  1785,  1786,
    1790,  1791,  1795,  1796,  1800,  1805,  1813,  1819,  1831,  1834,
    1837,  1843,  1843,  1843,  1846,  1846,  1846,  1851,  1851,  1851,
    1859,  1859,  1859,  1865,  1875,  1886,  1901,  1904,  1907,  1910,
    1916,  1917,  1924,  1935,  1936,  1937,  1941,  1942,  1943,  1944,
    1945,  1949,  1954,  1962,  1963,  1967,  1974,  1978,  1984,  1985,
    1986,  1987,  1988,  1989,  1990,  1994,  1995,  1996,  1997,  1998,
    1999,  2000,  2001,  2002,  2003,  2004,  2005,  2006,  2007,  2008,
    2009,  2010,  2011,  2012,  2013,  2014,  2018,  2024,  2031,  2043,
    2049,  2057,  2065,  2076,  2088,  2092,  2099,  2102,  2102,  2102,
    2107,  2107,  2107,  2120,  2124,  2128,  2134,  2142,  2150,  2161,
    2170,  2176,  2184,  2184,  2184,  2191,  2195,  2204,  2212,  2220,
    2224,  2227,  2235,  2236,  2237,  2244,  2245,  2246,  2247,  2248,
    2249,  2250,  2251,  2252,  2253,  2254,  2255,  2256,  2257,  2258,
    2259,  2260,  2261,  2262,  2263,  2264,  2265,  2266,  2267,  2268,
    2269,  2270,  2271,  2272,  2273,  2274,  2275,  2276,  2277,  2278,
    2279,  2285,  2286,  2287,  2288,  2289,  2304,  2313,  2314,  2315,
    2316,  2317,  2318,  2319,  2320,  2321,  2322,  2323,  2324,  2325,
    2326,  2329,  2329,  2329,  2332,  2337,  2341,  2345,  2345,  2345,
    2350,  2353,  2357,  2357,  2357,  2362,  2365,  2366,  2367,  2368,
    2369,  2370,  2371,  2372,  2373,  2375,  2379,  2380,  2385,  2391,
    2397,  2406,  2409,  2412,  2421,  2422,  2423,  2424,  2425,  2426,
    2427,  2431,  2435,  2439,  2443,  2447,  2451,  2455,  2459,  2463,
    2470,  2471,  2475,  2476,  2477,  2481,  2482,  2486,  2487,  2488,
    2492,  2493,  2497,  2509,  2512,  2513,  2517,  2517,  2536,  2535,
    2550,  2549,  2566,  2578,  2587,  2597,  2598,  2599,  2600,  2601,
    2605,  2608,  2617,  2618,  2622,  2625,  2629,  2642,  2651,  2652,
    2656,  2659,  2663,  2676,  2677,  2681,  2687,  2693,  2702,  2705,
    2712,  2715,  2721,  2722,  2723,  2727,  2728,  2732,  2739,  2744,
    2753,  2759,  2763,  2774,  2781,  2790,  2793,  2796,  2803,  2806,
    2811,  2822,  2825,  2830,  2842,  2843,  2847,  2848,  2849,  2853,
    2856,  2859,  2859,  2879,  2882,  2882,  2900,  2905,  2913,  2914,
    2918,  2921,  2934,  2951,  2952,  2953,  2958,  2958,  2984,  2988,
    2989,  2990,  2994,  3004,  3007,  3013,  3014,  3018,  3019,  3023,
    3024,  3028,  3030,  3035,  3028,  3051,  3052,  3056,  3057,  3061,
    3067,  3068,  3069,  3070,  3074,  3075,  3076,  3080,  3083,  3089,
    3091,  3096,  3089,  3117,  3124,  3129,  3138,  3144,  3148,  3159,
    3160,  3161,  3162,  3163,  3164,  3165,  3166,  3167,  3168,  3169,
    3170,  3171,  3172,  3173,  3174,  3175,  3176,  3177,  3178,  3179,
    3180,  3181,  3182,  3183,  3184,  3185,  3189,  3190,  3191,  3192,
    3193,  3194,  3195,  3196,  3200,  3211,  3215,  3222,  3234,  3241,
    3247,  3256,  3261,  3271,  3281,  3291,  3304,  3305,  3306,  3307,
    3308,  3312,  3316,  3316,  3316,  3330,  3331,  3335,  3339,  3346,
    3349,  3352,  3355,  3361,  3364,  3378,  3379,  3383,  3384,  3385,
    3386,  3387,  3387,  3387,  3391,  3396,  3403,  3410,  3410,  3417,
    3417,  3424,  3428,  3432,  3437,  3442,  3447,  3452,  3456,  3460,
    3465,  3469,  3473,  3478,  3478,  3478,  3484,  3491,  3491,  3491,
    3496,  3496,  3496,  3502,  3502,  3502,  3507,  3512,  3512,  3512,
    3517,  3517,  3517,  3526,  3531,  3531,  3531,  3536,  3536,  3536,
    3545,  3550,  3550,  3550,  3555,  3555,  3555,  3564,  3564,  3564,
    3570,  3570,  3570,  3579,  3582,  3593,  3609,  3611,  3616,  3621,
    3609,  3647,  3649,  3654,  3660,  3647,  3686,  3688,  3693,  3698,
    3686,  3739,  3740,  3741,  3742,  3743,  3744,  3745,  3749,  3750,
    3751,  3752,  3753,  3757,  3764,  3771,  3777,  3783,  3790,  3797,
    3803,  3812,  3815,  3821,  3829,  3834,  3841,  3846,  3852,  3853,
    3857,  3858,  3862,  3862,  3862,  3870,  3870,  3870,  3877,  3877,
    3877,  3888,  3888,  3888,  3895,  3895,  3895,  3906,  3912,  3912,
    3912,  3926,  3945,  3945,  3945,  3955,  3955,  3955,  3969,  3969,
    3969,  3983,  3992,  3992,  3992,  4012,  4019,  4019,  4019,  4029,
    4032,  4043,  4049,  4072,  4080,  4100,  4125,  4126,  4130,  4131,
    4136,  4139,  4149
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
  "\"int8\"", "\"uint8\"", "\"int16\"", "\"uint16\"", "\"tuple\"",
  "\"variant\"", "\"generator\"", "\"yield\"", "\"sealed\"",
  "\"template\"", "\"+=\"", "\"-=\"", "\"/=\"", "\"*=\"", "\"%=\"",
  "\"&=\"", "\"|=\"", "\"^=\"", "\"<<\"", "\">>\"", "\"++\"", "\"--\"",
  "\"<=\"", "\"<<=\"", "\">>=\"", "\">=\"", "\"==\"", "\"!=\"", "\"->\"",
  "\"<-\"", "\"??\"", "\"?.\"", "\"?[\"", "\"<|\"", "\"|>\"", "\":=\"",
  "\"<<<\"", "\">>>\"", "\"<<<=\"", "\">>>=\"", "\"=>\"", "\"@@\"",
  "\"@field\"", "\"::\"", "\"&&\"", "\"||\"", "\"^^\"", "\"&&=\"",
  "\"||=\"", "\"^^=\"", "\"..\"", "\"$$\"", "\"$i\"", "\"$v\"", "\"$b\"",
  "\"$a\"", "\"$t\"", "\"$c\"", "\"$f\"", "\"...\"",
  "\"integer constant\"", "\"long integer constant\"",
  "\"unsigned integer constant\"", "\"unsigned long integer constant\"",
  "\"unsigned int8 constant\"", "\"floating point constant\"",
  "\"double constant\"", "\"name\"", "\"new line, comma\"",
  "\"new line, semicolon\"", "\"start of the string\"", "STRING_CHARACTER",
  "STRING_CHARACTER_ESC", "\"end of the string\"", "\"{\"", "\"}\"",
  "\"end of failed eader macro\"", "','", "'='", "'?'", "':'", "'|'",
  "'^'", "'&'", "'<'", "'>'", "'-'", "'+'", "'*'", "'/'", "'%'",
  "UNARY_MINUS", "UNARY_PLUS", "'~'", "'!'", "PRE_INC", "PRE_DEC",
  "LLPIPE", "POST_INC", "POST_DEC", "DEREF", "'.'", "'['", "']'", "'('",
  "')'", "'$'", "'@'", "';'", "'{'", "'}'", "'#'", "$accept", "program",
  "COMMA", "SEMICOLON", "top_level_reader_macro",
  "optional_public_or_private_module", "module_name",
  "optional_not_required", "module_declaration", "character_sequence",
  "string_constant", "format_string", "optional_format_string", "$@1",
  "string_builder_body", "string_builder", "reader_character_sequence",
  "expr_reader", "$@2", "options_declaration", "require_declaration",
  "require_module_name", "optional_require_guard", "require_module",
  "is_public_module", "expect_declaration", "expect_list", "expect_error",
  "expression_label", "expression_goto", "elif_or_static_elif",
  "emit_semis", "optional_emit_semis", "expression_else", "$@3", "$@4",
  "if_or_static_if", "expression_else_one_liner",
  "expression_if_one_liner", "semis", "optional_semis",
  "expression_if_block", "$@5", "$@6", "$@7", "expression_else_block",
  "$@8", "$@9", "$@10", "expression_if_then_else", "$@11", "$@12",
  "expression_if_then_else_oneliner", "for_variable_name_with_pos_list",
  "expression_for_loop", "$@13", "expression_unsafe",
  "expression_while_loop", "$@14", "expression_with", "$@15",
  "expression_with_alias", "annotation_argument_value",
  "annotation_argument_value_list", "annotation_argument_name",
  "annotation_argument", "annotation_argument_list",
  "metadata_argument_list", "optional_for_annotations",
  "annotation_declaration_name", "annotation_declaration_basic",
  "annotation_declaration", "annotation_list", "optional_annotation_list",
  "optional_annotation_list_with_emit_semis",
  "optional_function_argument_list", "optional_function_type",
  "function_name", "das_type_name", "optional_template",
  "global_function_declaration", "optional_public_or_private_function",
  "function_declaration_header", "function_declaration", "$@16",
  "expression_block_finally", "$@17", "$@18", "expression_block", "$@19",
  "$@20", "expr_call_pipe_no_bracket", "expression_any", "$@21", "$@22",
  "expressions", "optional_expr_list", "optional_expr_map_tuple_list",
  "type_declaration_no_options_list", "name_in_namespace",
  "expression_delete", "new_type_declaration", "$@23", "$@24", "expr_new",
  "expression_break", "expression_continue", "expression_return",
  "expression_yield", "expression_try_catch", "kwd_let_var_or_nothing",
  "kwd_let", "optional_in_scope", "tuple_expansion",
  "tuple_expansion_variable_declaration", "expression_let", "expr_cast",
  "$@25", "$@26", "$@27", "$@28", "$@29", "$@30", "expr_type_decl", "$@31",
  "$@32", "expr_type_info", "expr_list", "block_or_simple_block",
  "block_or_lambda", "capture_entry", "capture_list",
  "optional_capture_list", "expr_full_block",
  "expr_full_block_assumed_piped", "expr_numeric_const",
  "expr_assign_no_bracket", "expr_named_call",
  "expr_method_call_no_bracket", "func_addr_name", "func_addr_expr",
  "$@33", "$@34", "$@35", "$@36", "expr_field_no_bracket", "$@37", "$@38",
  "expr_call", "expr", "expr_no_bracket", "$@39", "$@40", "$@41", "$@42",
  "$@43", "$@44", "expr_generator", "expr_mtag_no_bracket",
  "optional_field_annotation", "optional_override", "optional_constant",
  "optional_public_or_private_member_variable",
  "optional_static_member_variable", "structure_variable_declaration",
  "struct_variable_declaration_list", "$@45", "$@46", "$@47",
  "function_argument_declaration_no_type",
  "function_argument_declaration_type", "function_argument_list",
  "tuple_type", "tuple_type_list", "tuple_alias_type_list", "variant_type",
  "variant_type_list", "variant_alias_type_list", "copy_or_move",
  "variable_declaration_no_type", "variable_declaration_type",
  "variable_declaration", "copy_or_move_or_clone", "optional_ref",
  "let_variable_name_with_pos_list",
  "global_let_variable_name_with_pos_list", "variable_declaration_list",
  "let_variable_declaration", "global_let_variable_declaration",
  "optional_shared", "optional_public_or_private_variable",
  "global_variable_declaration_list", "$@48", "global_let", "$@49",
  "enum_expression", "commas", "enum_list",
  "optional_public_or_private_alias", "single_alias", "$@50",
  "alias_declaration", "optional_public_or_private_enum", "enum_name",
  "optional_enum_basic_type_declaration", "optional_commas", "emit_commas",
  "optional_emit_commas", "enum_declaration", "$@51", "$@52", "$@53",
  "optional_structure_parent", "optional_sealed", "structure_name",
  "class_or_struct", "optional_public_or_private_structure",
  "optional_struct_variable_declaration_list", "structure_declaration",
  "$@54", "$@55", "$@56", "variable_name_with_pos_list",
  "basic_type_declaration", "enum_basic_type_declaration",
  "structure_type_declaration", "auto_type_declaration", "bitfield_bits",
  "bitfield_alias_bits", "bitfield_basic_type_declaration",
  "bitfield_type_declaration", "$@57", "$@58", "c_or_s", "table_type_pair",
  "dim_list", "type_declaration_no_options",
  "optional_expr_list_in_braces", "type_declaration_no_options_no_dim",
  "$@59", "$@60", "$@61", "$@62", "$@63", "$@64", "$@65", "$@66", "$@67",
  "$@68", "$@69", "$@70", "$@71", "$@72", "$@73", "$@74", "$@75", "$@76",
  "$@77", "$@78", "$@79", "$@80", "$@81", "$@82", "$@83", "$@84", "$@85",
  "$@86", "type_declaration", "tuple_alias_declaration", "$@87", "$@88",
  "$@89", "$@90", "variant_alias_declaration", "$@91", "$@92", "$@93",
  "$@94", "bitfield_alias_declaration", "$@95", "$@96", "$@97", "$@98",
  "make_decl", "make_decl_no_bracket", "make_struct_fields",
  "make_variant_dim", "make_struct_single", "make_struct_dim_list",
  "make_struct_dim_decl", "optional_make_struct_dim_decl",
  "use_initializer", "make_struct_decl", "$@99", "$@100", "$@101", "$@102",
  "$@103", "$@104", "$@105", "$@106", "$@107", "$@108", "make_tuple_call",
  "$@109", "$@110", "make_dim_decl", "$@111", "$@112", "$@113", "$@114",
  "$@115", "$@116", "$@117", "$@118", "$@119", "$@120",
  "expr_map_tuple_list", "push_table_nesting", "make_table_decl",
  "make_table_call", "array_comprehension_where", "optional_comma",
  "table_comprehension", "array_comprehension", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-1555)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-855)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1555,   653, -1555, -1555,    54,   -49,   -51,   575, -1555,   -16,
   -1555, -1555, -1555, -1555,   286,   887, -1555, -1555, -1555, -1555,
     170,   170,   170, -1555,   190, -1555,   134, -1555, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555,    91, -1555,   199,
     219,   232, -1555,   275,   275, -1555, -1555, -1555,   326,   170,
   -1555, -1555,   134,   575,   575,   575,   336,   301, -1555, -1555,
   -1555, -1555,   887,   887,   887,   338, -1555,   815,   -83, -1555,
   -1555, -1555, -1555,   483, -1555,   542, -1555,   772,    44,    54,
     436,   -49,   438, -1555,   -48,   450,   192,    23, -1555, -1555,
     808,   448,   479,   505, -1555,   516,   486, -1555, -1555,   -45,
      54,   887,   887,   887,   887,   519, -1555,   812,   824,   603,
     694,   865, -1555, -1555,   487, -1555, -1555,   654, -1555, -1555,
   -1555,   800,   112, -1555, -1555, -1555, -1555,   275,   275,   553,
     275,   674,   697,   699, -1555, -1555,   634, -1555, -1555,   684,
     737,   519,   519, -1555, -1555,   775, -1555,   196, -1555,   698,
     835,   815, -1555,   780, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555,   844, -1555, -1555, -1555, -1555, -1555, -1555,   873, -1555,
   -1555, -1555, -1555,   855, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555,   214,   553,   553,   553, -1555, -1555,   958,  8667,   951,
   -1555,   724,   861, -1555, -1555, -1555, -1555, -1555,  9531, -1555,
     853,   938,   267,    54,   906,   885, -1555, -1555, -1555,   112,
   -1555, -1555,   877,   878,   880,   859,   881,   882, -1555, -1555,
   -1555,   863, -1555, -1555, -1555, -1555, -1555,   -66, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,   891,
   -1555, -1555, -1555,   896,   898, -1555, -1555, -1555, -1555,   899,
     902,   884,   286,   165, -1555, -1555, -1555, -1555,   746,   888,
     908, -1555, -1555, -1555, -1555, -1555, -1555,   924, -1555,   886,
     889,  8764, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555,  1056,  1062, -1555,
     905, -1555,   519,   715,   861, -1555,   933,   519, -1555, -1555,
     873,   519,    54, -1555,   682, -1555, -1555, -1555, -1555, -1555,
    7561, -1555, -1555,   935,   919,   -47,   105,   166, -1555, -1555,
    7561,   545, -1555,  5631, -1555, -1555, -1555,    13, -1555, -1555,
   -1555,    25, -1555,  5824,   923,  8475, -1555,   901, -1555, -1555,
    9469,  9624, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555, -1555,   954,   928, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555,  1103, -1555, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,   965,
     930, -1555, -1555,   -57,   -18,   994, -1555, -1555, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555,   926,   956, -1555,    28, -1555,
     519,   970,  8667, -1555,   152,  8667,  8667,  8667,   955,   957,
   -1555, -1555,    51,   286,   961,    63, -1555,   547,   934,   962,
     966,   947,   971,   950,   584,   972, -1555,   629,    22,   973,
    8327,  8327,   378,   959,   974,   975,   976,   977,   978, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,  8327,  8327,
    8327,  8327,  8327,  3701,  4473, -1555, -1555, -1555, -1555, -1555,
   -1555,   980, -1555, -1555, -1555, -1555,   940, -1555, -1555,   -72,
     -72, -1555,   -72,   -72,   960,  1604, -1555, -1555,   982, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555,  8667,  8667,   984,
     981,  8667,   905,  8667,   905,  8667,   905,  8762,   992,   985,
   -1555,  5631, -1555,  8667,  7561,   989,  1000, -1555, -1555, -1555,
   -1555, -1555,   993, -1555, -1555,   995,  6017, -1555,   746, -1555,
    8762,   992, -1555, -1555, -1555, -1555, -1555, -1555,  9682,   630,
    1539,   991, -1555,    95,   953,   280,   999,  8667,  8667, -1555,
    7945, -1555,   990, -1555, -1555,   286, -1555,   517,  1005,  1117,
     710, -1555, -1555, -1555,  1014, -1555, -1555, -1555,  7561,   613,
     645,  1025,   391, -1555, -1555, -1555, -1555,  1008, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555,   635, -1555,  1030,
    1031,  1037, -1555,  5631,  8667,  7561,  7561, -1555, -1555,  7561,
   -1555,  7561, -1555,  5631, -1555, -1555,  5631,  1039, -1555,  8667,
     449,   449,  1020,  1023,   204, -1555, -1555,  7561,  7561,  7561,
    7561,  7561,  7561,   851,   449,   449,   226,   449,   449,  1024,
    1203,  1026,  1028,   123,  1000,  1057,  1033,   519,  3315,   887,
    1229, -1555, -1555,   940, -1555, -1555, -1555, -1555, -1555,  9378,
    9409,  8327,  8327, -1555, -1555,  8327,  8327,  8327,  8327,  1069,
    8327,    58,  7561,  8327,  8327,  8327,  8327,  7561,  8327,  8327,
    8327,  8327,  8136,  8327,  8327,  8327,  8327,  8327,  8327,  8327,
    8327,  8327,  8327,  9591,  7561,  4666,   700,   707, -1555, -1555,
    1072,   735,   -18,   770,   -18,   781,   -18,   197, -1555,   499,
     908,  1060, -1555,   531, -1555,  8667,  1000,   587,   908, -1555,
   -1555,  6210, -1555, -1555, -1555, -1555,  1044,  1082, -1555,   170,
   -1555,   170, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,
    7561, -1555, -1555,   388,   248,   248,   248, -1555,   908,   908,
    8327,  8869, -1555,  1084, -1555, -1555, -1555, -1555,  7561,  1085,
     465,  8667,   152, -1555,  7561,   170, -1555, -1555, -1555, -1555,
   -1555, -1555, -1555,  8667,  8667,  8667,  8667,  3894,  1087,  7561,
    8667, -1555, -1555, -1555,  8667,  1000,  1034, -1555,  1079,  1052,
    8667,  8667,  1053,  8667,  1054,  8667,  1000,  8667,  8762,  1000,
   -1555,   992,   671,  7561,  7561,  8667,   905,  1055,  1058,  1059,
    1061,  1063,  1064, -1555,  7561,   831,   104,  1066, -1555,  7561,
   -1555,  7561, -1555,  7561,  1067,   334, -1555, -1555,  6403,    24,
    3508, -1555,   269,  1068,   256,  1071,   905,  2071,  1229,  1077,
    1073, -1555, -1555,  1092,  1074, -1555, -1555,   330,   330,  9248,
    9248,  9218,  9218,  1075,   589,  1076, -1555,  1078,   -15,   -15,
     982,   330,   330,  8869, -1555, -1555,  9018,  8903,  8988,  8869,
    9500,  1279,   986,  9103,  9133,  9248,  9248,   490,   490,   589,
     589,   589,   386,  7561,  1080,  1083,   557,  7561,  1280,  1086,
    1089, -1555,   277, -1555, -1555, -1555,   271, -1555,  1097, -1555,
    1101, -1555,  1104,  8667, -1555,  8762,  8667, -1555,   992,   655,
    1090,  1093,  8667,  7561, -1555, -1555,  1110,   598, -1555,  8570,
   -1555,   278, -1555,  1094,  1096,  1249, -1555, -1555,   202, -1555,
   -1555, -1555,  1743,  2279,  1120, -1555,   598,    32,  1108, -1555,
    1102,  1256,  1014,  7561,   170, -1555, -1555, -1555, -1555,   908,
    1022,  1181,   793,   594,   318,  1111,  1112,   683,  1113,   799,
    8667,  8762,   992,  1312,  1114,  1105,  8667,  7561,  1115, -1555,
    1322,  1412, -1555,  1450, -1555,  1459,  1116,  1585,   750,  1118,
    8667,   768,  1229,  1119,  1121,  1712,   -18, -1555, -1555, -1555,
   -1555, -1555,  1124,  1128,  1125,  1270,  1155,    43,   104,  1126,
   -1555, -1555, -1555,  1129,   157,  1130,  1122,  1079,   288, -1555,
    1131,   306,  4859, -1555, -1555, -1555,   257,   -18, -1555,  6596,
   -1555, -1555,  6789,  1158,  1168, -1555,   170,  1178,  6982,   -89,
    7175, -1555, -1555, -1555,   170,   170,  1327, -1555,  1038, -1555,
   -1555,  1326, -1555, -1555,  1331, -1555,  1300,   170, -1555,   170,
     170,   170,   170,   170, -1555,  1277, -1555,   170,  1860,   905,
   -1555,  7561, -1555,  7561,  4087,  7561, -1555,  1162,  1144, -1555,
   -1555,  8327,  1145, -1555,  1148,  7561,  4280,  1149, -1555,  1151,
   -1555,  5052, -1555,  6210, -1555, -1555, -1555,  1185, -1555,  1188,
   -1555, -1555, -1555, -1555, -1555, -1555,   908, -1555, -1555,   908,
   -1555, -1555,  1093, -1555, -1555,   908, -1555,  7561, -1555,   668,
   -1555, -1555, -1555,  1152, -1555,  1153, -1555,  7561,  1191,   504,
    8667, -1555,  7561,  1159,  7561,   702, -1555,  1192, -1555, -1555,
    1351,   873, -1555,  7561,  1198, -1555,  7561,   170, -1555, -1555,
   -1555, -1555,  1163, -1555, -1555, -1555,  1167,  1205, -1555, -1555,
    1885,   779,   823, -1555, -1555,  7561,  2208, -1555, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555,  2416, -1555,    92,
   -1555, -1555, -1555,  1194,  5245, -1555,  1201,  7561,  1206, -1555,
     328,  5631,   235,    45,   302,  7561,  7561,  7561,   104, -1555,
   -1555, -1555,   334,  1172,  3508,   351,  1213,  1214,  1179,  1215,
    1219, -1555,   380,   519,  7561, -1555,  1371,  7561, -1555,  1210,
    1211, -1555,  1222,  1230, -1555, -1555,  7561, -1555, -1555, -1555,
   -1555,  1187, -1555, -1555,  1189,   -63,   -63,  1199, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555,   -55, -1555,  8327,  8327,  8327,
    8327,  8327,  8327,  8327,  8327,  8327,  8327,  7561,  8327,  8327,
    8327,  8327,  8327,  8327,  8327,   -18,  8667,  1190,  8667,  1209,
    3508, -1555,   384,   396,  1212, -1555,  7561,  1743,  7561, -1555,
    1216,  3508, -1555,   397,   399,  7561, -1555, -1555, -1555,   411,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,  1240, -1555,
    1217, -1555, -1555,  1223, -1555,  1204,  1375,    73, -1555,  1383,
   -1555, -1555,  1220,  1253,   879,  1364,   170,  1232, -1555,   170,
   -1555,  1231,  1236, -1555, -1555,  7561,  1258, -1555, -1555, -1555,
   -1555,  1237,  1239,  1246,  8327,  8327,  8327,  1247,  1362,  1250,
   -1555,  1252,  7368, -1555,   551, -1555, -1555,   421, -1555, -1555,
    1248, -1555,  1304, -1555,   423,  1268,  1428,  1155,  5631,  7561,
    7561,  1271, -1555, -1555,    49, -1555,   321, -1555, -1555, -1555,
    1311, -1555, -1555,   257, -1555,   994, -1555, -1555, -1555,  8667,
    7561, -1555, -1555, -1555, -1555,  2487,  7561,  7561,    54,   906,
    1275,  1278,  7561,  1155, -1555, -1555, -1555,  1604,  1604,  1604,
    1604,  1604,  1604,  1604,  1604,  1604,  1604,  1604, -1555, -1555,
    1604,  1604,  1604,  1604,  1604,  1604,  1604,   519,  2624, -1555,
     805, -1555,   333,  5438, -1555, -1555, -1555,  8667,  1281,  1282,
   -1555,   381,  5438, -1555, -1555,  1284, -1555,  7561, -1555, -1555,
    7561,  1316,  7561, -1555, -1555, -1555,  8667, -1555, -1555,   644,
   -1555,    35, -1555, -1555, -1555,  1362,  1362,  1288,  1292,  1295,
    1296,  1299,  5631, -1555,  7561,  9248,  9248,  9248,  5631, -1555,
   -1555,  1362,  1302,  1362, -1555,  1306, -1555, -1555,   551, -1555,
    1333, -1555, -1555,  1301,  7561,  1347,   426,   430, -1555, -1555,
     303,  5631,  1310,  1314, -1555, -1555, -1555,   908, -1555,  1307,
    1315,  1319,   394,   104,  7561,  1320,   459,   128,   994, -1555,
   -1555,  1321,   470,   820, -1555, -1555,  1323,   472, -1555, -1555,
    1324, -1555, -1555,  1318,   370,  1481,    35, -1555, -1555,   879,
     216,   216, -1555,  7561,  1362,  1362,   594,  1325,  1332,  1000,
     216,  1362,   594, -1555, -1555, -1555,  7561,  1334, -1555, -1555,
    1328,  7561,  7561,   476, -1555, -1555,  1383,  1517,   519, -1555,
      55,  1336,   519,   579, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,
    1481,   388,   594,  1355,  1366, -1555,  1340,  1342,  1343,   216,
     216,  1355,  1345, -1555, -1555,  1348,  1349,   594,  1350,  1353,
   -1555,  7561, -1555, -1555,  1354, -1555,  7754,   170, -1555,  5631,
     519, -1555,  8667,   152, -1555,  2695,  9531, -1555, -1555, -1555,
   -1555,   492,  1352, -1555, -1555, -1555, -1555,  1359,  1360, -1555,
   -1555, -1555,  1361, -1555,  1502,  1356,  1353,  7561, -1555, -1555,
   -1555, -1555, -1555,  1604, -1555,  1358,   493, -1555, -1555,   408,
    7561,  1363,   170,  9531, -1555,   594, -1555, -1555, -1555,  7561,
   -1555,  1365,  1353, -1555,   676,  7754,   519, -1555,  7561,   170,
   -1555, -1555,   519,   509, -1555, -1555,  1367, -1555,   519, -1555,
   -1555,  1368, -1555,   170, -1555,   170, -1555,   994, -1555, -1555,
    2903, -1555,  7561, -1555, -1555, -1555, -1555,  1369,  1372,  1370,
    1383, -1555, -1555,  7754,   519, -1555, -1555,   170, -1555,  3111,
   -1555,  1372,  1373,   676,  1383, -1555, -1555
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,   171,     1,   370,     0,     0,    58,   683,   371,     0,
     876,   866,   871,    20,     0,     0,    19,    16,    15,     3,
       0,     0,     0,     8,   719,     7,   664,     6,    11,     5,
       4,    13,    12,    14,   136,   137,   135,   145,   147,    49,
      67,    64,    65,     0,     0,    50,   685,   684,     0,     0,
      26,    25,   664,   683,   683,   683,     0,   344,    47,   155,
     156,   157,     0,     0,     0,   158,   160,   167,     0,   154,
      21,    10,     9,   293,   701,     0,   665,   666,     0,     0,
       0,     0,     0,    51,     0,     0,    59,    62,   686,   688,
      22,     0,     0,     0,   346,     0,     0,   166,   161,     0,
       0,     0,     0,     0,     0,    76,   294,   296,   689,   711,
     710,   714,   668,   667,   674,   143,   144,     0,   141,   142,
     139,     0,     0,   138,   148,    68,    66,     0,     0,    52,
       0,     0,     0,     0,    63,    60,     0,    23,    24,    27,
     776,    76,    76,   345,    45,    48,   165,     0,   162,   163,
     164,   168,    74,    77,   172,   298,   297,   300,   295,   691,
     690,     0,   713,   712,   716,   715,   720,   669,   590,   140,
      30,    31,    35,     0,   131,   132,   129,   130,   128,   127,
     133,     0,    54,    55,    53,    57,    56,    62,     0,     0,
      29,     0,   699,   867,   872,    46,   159,    75,     0,   692,
     693,   707,   671,     0,   591,     0,    32,    33,    34,     0,
     146,    61,     0,     0,     0,     0,     0,     0,   729,   749,
     730,   765,   731,   735,   736,   737,   738,   755,   742,   743,
     744,   745,   746,   747,   748,   750,   751,   752,   753,   836,
     734,   741,   754,   843,   850,   732,   739,   733,   740,     0,
       0,     0,     0,   764,   797,   800,   798,   799,   863,   793,
     687,    28,   779,   780,   777,   778,   697,   700,   877,     0,
       0,     0,   268,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   292,     0,     0,   179,
     173,   267,    76,     0,   699,   708,     0,    76,   673,   670,
     590,    76,     0,   653,   645,   675,   134,   801,   827,   830,
       0,   833,   823,     0,     0,   837,   844,   851,   857,   860,
       0,   795,   807,   338,   813,   818,   812,     0,   826,   822,
     815,     0,   817,     0,   794,     0,   698,     0,   868,   873,
     258,   259,   256,   182,   183,   185,   184,   186,   187,   188,
     189,   215,   216,   213,   214,   206,   217,   218,   207,   204,
     205,   257,   240,     0,   255,   219,   220,   221,   222,   193,
     194,   195,   190,   191,   192,   203,     0,   209,   210,   208,
     201,   202,   197,   196,   198,   199,   200,   181,   180,   239,
       0,   211,   212,   590,   176,   306,   756,   759,   762,   763,
     757,   760,   758,   761,   694,     0,   705,   721,     0,   149,
      76,     0,     0,   646,     0,     0,     0,     0,     0,     0,
     491,   492,     0,     0,     0,     0,   485,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   755,     0,     0,     0,
       0,     0,   405,     0,     0,     0,     0,     0,     0,   579,
     418,   420,   419,   421,   422,   423,   424,    41,     0,     0,
       0,     0,     0,   338,     0,   403,   404,   951,   489,   488,
     566,   486,   559,   558,   557,   556,   169,   562,   487,   561,
     560,   533,   493,   534,     0,   482,   538,   494,     0,   490,
     888,   890,   889,   483,   892,   891,   484,     0,     0,     0,
     782,     0,   173,     0,   173,     0,   173,     0,     0,     0,
     809,     0,   806,     0,     0,     0,   958,   396,   820,   821,
     814,   816,     0,   819,   790,     0,     0,   865,   864,   878,
     624,   630,   260,   262,   261,   263,   254,   238,   264,   241,
     223,     0,   174,   369,   615,   616,     0,     0,     0,   299,
       0,   400,     0,   301,   702,     0,   709,     0,     0,   647,
     645,   672,   150,   654,     0,   643,   644,   642,     0,     0,
       0,     0,   787,   912,   915,   349,   764,   353,   352,   358,
     881,   887,   882,   883,   884,   886,   885,     0,   390,     0,
       0,     0,   942,     0,     0,     0,     0,   381,   384,     0,
     387,     0,   946,     0,   924,   928,     0,     0,   918,     0,
     521,   522,     0,     0,   457,   454,   456,     0,     0,     0,
       0,     0,     0,     0,   498,   497,   535,   496,   495,     0,
       0,     0,     0,   344,   958,   958,     0,    76,     0,     0,
     413,   405,   335,   169,   312,   310,   311,   309,   804,     0,
       0,     0,     0,   523,   524,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   472,     0,     0,     0,     0,   766,   781,
       0,     0,   176,     0,   176,     0,   176,   344,   622,     0,
     620,     0,   628,     0,   767,     0,   958,     0,   342,   397,
     805,   959,   339,   811,   789,   792,     0,   771,   625,    94,
     631,    94,   265,   266,   243,   244,   246,   245,   247,   248,
     249,   250,   242,   251,   252,   253,   227,   228,   230,   229,
     231,   232,   233,   234,   225,   226,   235,   236,   237,   224,
       0,   367,   368,     0,   590,   590,   590,   175,   178,   177,
       0,   401,   335,   680,   706,   717,   603,   722,     0,     0,
       0,     0,     0,   661,     0,     0,   802,   828,   831,    18,
      17,   785,   786,     0,     0,     0,     0,   910,     0,     0,
       0,   932,   935,   938,     0,   958,     0,   949,   958,     0,
       0,     0,     0,     0,     0,     0,   958,     0,     0,   958,
     921,     0,     0,     0,     0,     0,   173,     0,     0,     0,
       0,     0,     0,    44,     0,    42,     0,     0,   931,     0,
     634,     0,   633,     0,     0,   959,   903,   526,   340,     0,
     338,   475,     0,     0,     0,     0,   173,     0,   413,     0,
       0,   545,   544,     0,     0,   546,   550,   499,   500,   512,
     513,   510,   511,     0,   539,     0,   531,     0,   563,   564,
     565,   501,   502,   568,   569,   570,   517,   518,   519,   520,
       0,     0,   515,   516,   514,   508,   509,   504,   503,   505,
     506,   507,     0,     0,     0,   463,     0,     0,     0,     0,
       0,   480,     0,   834,   824,   768,     0,   838,     0,   845,
       0,   852,     0,     0,   858,     0,     0,   861,     0,     0,
       0,   795,     0,     0,   398,   791,   772,   695,    92,    95,
     869,    95,   874,     0,     0,   723,   612,   613,   635,   617,
     619,   618,   402,     0,   676,   681,   695,   606,     0,   649,
       0,   650,     0,     0,     0,   663,   803,   829,   832,   788,
       0,     0,     0,   911,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   959,     0,   536,
       0,     0,   537,     0,   567,     0,     0,     0,     0,     0,
       0,     0,   413,     0,     0,     0,   176,   574,   575,   576,
     577,   578,     0,    38,     0,   110,     0,     0,     0,     0,
     894,   893,   525,     0,     0,     0,     0,   958,     0,   476,
       0,     0,     0,   479,   477,   170,     0,   176,   337,   361,
     359,   306,     0,     0,     0,   360,     0,     0,     0,    76,
       0,   332,   417,   313,     0,     0,     0,   326,     0,   327,
     321,     0,   318,   317,     0,   319,     0,     0,   336,     0,
      90,    91,    88,    89,   328,   373,   316,     0,   425,   173,
     541,     0,   547,     0,     0,     0,   529,     0,     0,   551,
     555,     0,     0,   532,     0,     0,     0,     0,   464,     0,
     473,     0,   527,     0,   481,   835,   825,     0,   783,     0,
     839,   841,   846,   848,   853,   855,   621,   859,   623,   627,
     862,   629,   795,   796,   808,   343,   399,     0,   678,   696,
     879,    93,   626,     0,   632,     0,   614,     0,     0,     0,
       0,   636,     0,     0,     0,   696,   703,     0,   604,   718,
       0,   590,   648,     0,     0,   658,     0,     0,   662,   913,
     916,   350,     0,   355,   356,   354,     0,     0,   393,   391,
       0,     0,     0,   943,   941,   340,     0,   950,   953,   382,
     385,   388,   947,   945,   925,   929,   927,     0,   919,    76,
     455,   589,   458,     0,     0,    39,     0,     0,     0,   374,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   952,
     341,   478,     0,     0,   338,     0,     0,     0,     0,     0,
       0,   411,     0,    76,     0,   362,     0,     0,   347,     0,
       0,   331,     0,     0,    71,   306,     0,   364,   335,   329,
     330,     0,    83,    84,     0,   151,   151,     0,   320,   315,
     322,   323,   324,   325,   372,     0,   314,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   176,     0,     0,     0,     0,
     338,   449,     0,     0,     0,   552,     0,   540,     0,   530,
       0,   338,   465,     0,     0,     0,   528,   474,   470,     0,
     770,   784,   769,   842,   849,   856,   810,   773,   774,   679,
       0,   870,   875,     0,   725,     0,   726,   638,   637,   302,
     677,   682,     0,     0,   597,   600,     0,     0,   652,     0,
     660,     0,     0,   351,   357,     0,     0,   392,   933,   936,
     939,     0,     0,     0,     0,     0,     0,     0,   910,     0,
     922,     0,     0,   306,     0,   461,   580,     0,    36,    43,
       0,   112,     0,   113,     0,     0,   114,     0,     0,     0,
       0,     0,   896,   895,     0,   446,     0,   448,   408,   409,
       0,   407,   406,     0,   414,   306,   363,   306,   348,     0,
       0,    69,    70,   120,   365,     0,     0,     0,     0,   153,
       0,     0,     0,     0,   655,   379,   378,   437,   438,   440,
     439,   441,   431,   432,   433,   442,   443,   427,   428,   429,
     430,   444,   445,   434,   435,   436,   426,    76,     0,   588,
       0,   586,     0,     0,   450,   453,   583,     0,     0,     0,
     582,     0,     0,   466,   469,     0,   471,     0,   880,   724,
       0,     0,     0,   303,   308,   704,     0,   598,   599,   600,
     601,   592,   607,   651,   659,   910,   910,     0,     0,     0,
       0,     0,   338,   954,   340,   383,   386,   389,     0,   911,
     926,   910,     0,   910,   571,     0,   573,   459,     0,   581,
      40,   111,   375,     0,     0,     0,     0,     0,   898,   897,
       0,     0,     0,     0,   412,   415,   366,   126,   125,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   306,   542,
     548,     0,     0,     0,   587,   585,     0,     0,   584,   775,
       0,   728,   639,     0,     0,   595,   592,   593,   594,   597,
     909,   909,   394,     0,   910,   910,   901,     0,     0,   958,
     909,   910,   901,   572,   462,    37,     0,     0,   116,   117,
       0,     0,     0,     0,   447,   410,   302,    85,    76,   152,
       0,     0,    76,   645,   380,   656,   657,   416,   543,   549,
     451,   452,   553,   467,   468,   727,   335,   605,   596,   608,
     595,     0,     0,   906,   958,   908,     0,     0,     0,   909,
     909,   902,     0,   944,   955,     0,     0,   901,     0,   956,
     115,     0,   900,   899,     0,   334,     0,     0,   107,     0,
      76,   306,     0,     0,   554,     0,     0,   610,   641,   640,
     602,     0,   959,   907,   914,   917,   395,     0,     0,   940,
     948,   930,     0,   920,     0,     0,   956,     0,    86,    90,
      91,    88,    89,    87,   109,    99,     0,   306,   124,     0,
       0,     0,     0,     0,   904,     0,   934,   937,   923,     0,
     960,     0,   956,    96,    78,     0,    76,   122,     0,     0,
     305,   609,    76,     0,   957,   961,     0,   335,    76,    72,
      73,     0,   108,     0,   306,     0,   377,   306,   905,   962,
       0,    79,     0,   100,   119,   376,   611,     0,   104,     0,
     302,   101,    80,     0,    76,    98,   335,     0,    81,     0,
     105,   104,     0,    78,   302,    82,   103
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1555, -1555,  -901,    -1, -1555, -1555, -1555, -1555, -1555,   936,
    1478, -1555, -1555, -1555, -1555, -1555, -1555,  1566, -1555, -1555,
   -1555,   159, -1555, -1555,  1381, -1555, -1555,  1491, -1555, -1555,
   -1555, -1555,  -138,  -141, -1555, -1555, -1555, -1555, -1554,   854,
     857, -1555, -1555, -1555, -1555,  -137, -1555, -1555, -1555, -1555,
   -1555, -1555, -1555, -1000, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555, -1555,  1377, -1555, -1555,   -65,   -95,  -188,   344, -1555,
   -1555,   461,   942,   939,   637,  -486,  -671, -1555,  -307, -1555,
   -1555, -1555, -1261, -1555, -1555, -1513, -1555, -1555, -1014, -1555,
   -1555, -1555, -1555, -1555, -1555,  -750,  -327, -1143,   883,   -13,
   -1555, -1555, -1555, -1555, -1555, -1552, -1550, -1546, -1545, -1555,
   -1555,  1596, -1555, -1233, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555,  -350, -1356,   503,
     217, -1555,  -797, -1555,   512, -1555, -1555, -1555, -1555, -1307,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,   405,
    -365, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,  -160,
      65,     9,    64,   145, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555,   274,  -529,  -764, -1555,  -517,  -769, -1555,  -923,    14,
      15, -1555,  -567,  -561, -1555, -1555, -1555, -1213, -1555,  1555,
   -1555, -1555, -1555, -1555, -1555,   463,   657, -1555,   988, -1555,
   -1555, -1555, -1555, -1555, -1555,   658, -1555,  1313, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555, -1555, -1555,  -154, -1555,  1183, -1555, -1555, -1555,  1392,
   -1555, -1555, -1555,  -569, -1555, -1555,  -328,  -893, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555,  -165, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555,  -668, -1430,  -611, -1555, -1555,
   -1457, -1309,  1196, -1555, -1555, -1555, -1555, -1555, -1555, -1555,
   -1555, -1555, -1555,  1207, -1555, -1555,  1224, -1555, -1555, -1555,
   -1555, -1555, -1555, -1555, -1555, -1555, -1555,  1015, -1555,  -422,
    1225, -1398,  -629,  1226,  -420
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,   791,   792,    18,   139,    52,   190,    19,   173,
     179,  1490,  1196,  1358,   633,   478,   145,   479,    96,    21,
      22,    86,    44,    45,   135,    23,    41,    42,  1054,  1055,
    1691,   153,   154,  1692,  1708,  1721,  1244,  1617,  1056,   939,
     940,  1674,  1687,  1707,  1675,  1712,  1716,  1722,  1713,  1057,
    1058,  1655,  1059,  1017,  1060,  1061,  1062,  1063,  1064,  1065,
    1066,  1067,   180,   181,    37,    38,    39,   204,  1400,    65,
      66,    67,    68,   650,    24,   404,   559,   300,   301,   107,
      25,   157,   302,   158,   198,  1454,  1533,  1661,   561,   562,
    1143,   480,  1068,  1238,  1509,   857,   641,  1026,   717,   481,
    1069,   587,   796,  1333,   482,  1070,  1071,  1072,  1073,  1074,
     763,  1075,  1255,  1200,  1405,  1076,   483,   810,  1344,   811,
    1345,   813,  1346,   484,   800,  1337,   485,   526,   563,   486,
    1221,  1222,   856,   487,   654,   488,  1077,   489,   490,   626,
     491,   825,  1354,   826,  1488,   492,   908,  1297,   493,   527,
     495,  1276,  1578,  1278,  1579,  1437,  1624,   496,   497,   553,
    1539,  1589,  1459,  1461,  1326,   957,  1151,  1626,  1663,   554,
     555,   556,   708,   709,   729,   712,   713,   731,   843,   946,
     947,  1630,   578,   424,   570,   314,  1517,   571,   315,    77,
     114,   202,   310,    27,   168,   955,  1129,   956,    48,    49,
     136,    28,   161,   200,   304,  1130,   267,   268,    29,   108,
     773,  1322,   566,   306,   307,   111,   166,   777,    30,    75,
     201,   567,   948,   498,   414,   255,   256,   916,   937,   192,
     257,   700,  1301,   925,   581,   344,   258,   522,   259,   425,
     966,   523,   715,   508,  1106,   426,   967,   427,   968,   507,
    1105,   511,  1110,   512,  1303,   513,  1112,   514,  1304,   515,
    1114,   516,  1305,   517,  1117,   518,  1120,   710,    31,    54,
     269,   540,  1133,    32,    55,   270,   541,  1135,    33,    53,
     347,   727,  1310,   589,   499,   645,  1602,   646,  1594,  1595,
    1596,   976,   500,   794,  1331,   795,  1332,   821,  1351,  1000,
    1482,   817,  1348,   501,   818,  1349,   502,   980,  1469,   981,
    1470,   982,  1471,   804,  1341,   815,  1347,  1027,   647,   503,
     504,  1645,   722,   505,   506
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      17,    58,    69,   193,   194,   147,   525,   784,   205,   782,
     593,   728,   596,   793,   124,   844,   846,   538,  1203,    70,
      71,    72,   953,   260,   730,  1142,   702,  1226,   704,  1505,
     706,   918,  1342,   920,   254,   922,  1128,   853,  1124,  1480,
    -171,   617,  1406,   543,   545,   133,   528,  1487,    89,    69,
      69,    69,  1001,  1615,   998,  1128,   428,   429,   530,   115,
     116,  1079,  1648,  1201,  1649,  1368,  1650,   651,   599,  1501,
    1651,  1652,  1147,    34,    35,  1619,   435,   203,   152,  -840,
     134,  1537,   437,   203,  1597,   620,   621,   930,    69,    69,
      69,    69,   104,  1606,   574,   568,   551,   101,   102,   103,
      82,  1207,   761,   634,   635,   636,   637,   638,   557,    40,
     569,   669,   191,   611,   671,   672,  -776,    83,   105,   444,
     445,  1693,  1608,  1649,   644,  1650,    43,   174,   175,  1651,
    1652,  -840,   475,   476,  1496,   652,  -840,  1398,   311,   128,
      84,  1538,  1637,  1638,   928,   762,   552,  1403,   932,    50,
     418,    85,  1404,   447,   448,  -840,  1540,  1541,   146,  1717,
     558,  1649,  1577,  1650,   405,   600,   601,  1651,  1652,   417,
    1516,   716,  1550,   419,  1552,   253,   984,  1642,   568,   988,
     642,  1554,  1031,   117,   693,   694,   975,   996,    51,  1028,
     999,   254,    56,   569,   529,   771,    76,  1715,    73,  1148,
     840,   309,   118,    87,   618,  1189,   531,   119,  1374,   120,
     131,  1726,   121,  1172,   875,   963,    57,  1171,  1202,    36,
    1202,  1393,   132,   876,  1202,   532,    74,  1029,  1309,  1306,
    1202,  -847,    15,   585,   533,  1599,  1600,   986,  1030,   331,
    1149,   733,  1607,   129,  1309,   602,   122,   420,  1671,   842,
     840,   473,   345,   805,  1014,   884,   841,   885,   477,   152,
     579,   580,   582,   816,    95,   603,   819,    78,   254,  1015,
     176,   254,   254,   254,  1686,   177,   806,   178,   568,   575,
     121,  1370,   572,  -847,   840,   576,   182,   183,  -847,   184,
    1206,   822,  -854,   569,  1352,    13,   867,   868,   852,   842,
     869,   870,   871,   872,  1576,   874,  1016,  -847,   878,   879,
     881,   882,   883,   886,   887,   888,   889,   891,   892,   893,
     894,   895,   896,   897,   898,   899,   900,   901,   577,   840,
    -460,  1548,   253,   842,    16,  1193,  1574,    13,    95,  1486,
    1006,  1706,   696,   697,  -854,   912,   701,   332,   703,  -854,
     705,   659,   660,   254,   254,   671,   672,   254,   718,   254,
     932,   254,  1162,   254,  1215,  1662,  1223,   333,  -854,   254,
    1037,    79,   642,  1506,    79,   923,    16,  1139,   842,   131,
    1140,  1028,  -460,  1141,  1216,  1365,   254,  -460,   203,   209,
    1217,   132,   768,   769,  1452,  1156,  1118,    80,  1210,   196,
    1366,   551,  1682,   254,   254,   952,  -460,    81,  1167,   253,
    1132,  1121,   253,   253,   253,   840,  1283,   210,  1592,   586,
     597,   841,  1218,    82,  1134,   693,   694,    56,  1294,   840,
     840,   104,   928,  1219,    13,  1369,  1561,  1367,  1220,   625,
      83,   334,    95,   711,  1032,    13,  1107,   974,   663,   664,
     254,    57,  1103,   962,  1108,   765,   669,  1035,   670,   671,
     672,   673,   674,    84,   842,   254,   970,   971,   335,   336,
     659,   660,  1033,    16,    85,   308,   983,  1109,   842,   842,
    1104,  1212,   990,   991,    16,   993,   766,   995,  1395,   997,
    1023,    88,  1078,  1103,   253,   253,  1212,  1005,   253,  1024,
     253,    94,   253,  1362,   253,   862,   866,  1213,  1212,   848,
     253,   659,   660,  1570,   688,   689,   690,   691,   692,    56,
     880,  1163,  1502,    97,    98,    99,  1212,   253,   622,   693,
     694,  1363,   337,   623,  1521,   575,   338,    13,   944,   909,
     100,   576,  1092,    57,   253,   253,  1376,   109,   110,   345,
     718,  1093,   774,   945,  1377,  1383,  1212,   789,    13,  1433,
     624,   254,   148,   149,   150,   151,   790,   663,   664,    79,
     345,  1212,  1442,   783,  1212,   669,    16,  1562,   671,   672,
     673,   674,  1526,  1384,   577,   339,  1103,  1434,  1078,   340,
     106,   253,   341,  1275,   125,  1569,  1103,    16,  1103,  1435,
    1443,  1362,  1444,   928,  1427,  1103,   253,  1658,   663,   664,
     659,   660,  1432,   140,  1446,   960,   669,   342,   670,   671,
     672,   673,   674,  1441,  1489,   127,  1493,   254,   969,  1559,
     961,   972,    46,  1560,  1362,   979,    69,   130,    47,   254,
     254,   254,   254,  1677,   141,  1212,   254,  1212,   693,   694,
     254,  1103,  1170,     2,  1315,   144,   254,   254,  1176,   254,
       3,   254,  1573,   254,   254,   789,    13,  1212,  1103,  1316,
     142,   254,  1187,  1581,   790,  1584,   690,   691,   692,  1614,
    1704,   143,   924,     4,  1212,     5,   152,     6,  1688,   693,
     694,  1535,    56,     7,   167,  1664,  1676,   789,    13,  1689,
    1690,   622,   253,     8,   334,    16,   790,   663,   664,     9,
     162,  1460,  1698,  1097,   927,   669,    57,   670,   671,   672,
     673,   674,  1098,   775,   776,   494,  1287,   520,   938,   604,
     938,   335,   336,    10,  1282,   519,  1090,    16,   734,   735,
     736,   737,   738,   739,   740,   741,  1293,   521,   535,   605,
     642,  1299,   132,   789,    13,    11,    12,  1622,  1116,  1028,
     423,  1119,   790,   742,   789,  1522,   612,  1125,   253,   254,
     931,   254,   254,   790,  1527,   743,   744,   745,   254,   334,
     253,   253,   253,   253,   965,   254,   613,   253,   693,   694,
     406,   253,   345,    16,   407,   337,   786,   253,   253,   338,
     253,   163,   253,   262,   253,   253,   335,   336,   408,   409,
     188,   615,   253,   410,   411,   412,   413,   798,   263,   169,
      13,   789,    13,   264,   345,   265,   254,   254,   787,   112,
     790,   616,   254,  1308,   789,   113,  1625,   799,  1122,   185,
     101,    14,   103,   790,  1357,  1418,   254,  1419,   339,   789,
      13,  1364,   340,    15,  1002,   341,  1053,   421,   790,    16,
     422,    16,   186,   423,   187,   137,  1166,   954,   789,   155,
     337,   138,  1593,  1593,   338,   156,   189,   790,  1601,   345,
     342,   159,  1593,   913,  1601,   780,   345,   160,   781,    16,
     914,   423,  1407,  1408,  1409,  1410,  1411,  1412,  1413,  1414,
    1415,  1416,  1417,  1420,  1421,  1422,  1423,  1424,  1425,  1426,
     253,  1235,   253,   253,   345,   191,   789,    13,   917,   253,
    1605,    59,   164,   339,  1631,   790,   253,   340,   165,   719,
     341,  1593,  1593,  1185,   789,    13,  1457,  1700,  1131,  1601,
    1131,   726,  1458,   790,   195,   789,    13,   197,  1428,   345,
      60,  1188,  1053,   919,   790,   342,    16,   101,   102,   103,
     345,  1155,  1339,  1158,   921,  1633,  1719,   253,   253,   170,
     171,   172,   345,   253,    16,  1317,  1161,   101,   345,  1475,
    1476,  1477,  1169,   785,   345,    16,   254,   253,  1520,   789,
      13,  1325,   653,   653,    61,   653,   653,  1683,   790,   345,
     206,   207,   655,  1582,   656,   657,  1340,   659,   660,   199,
     807,   809,  1623,   203,   812,   134,   814,   261,  1497,    62,
     170,   171,   833,   834,   206,   207,   208,   266,    56,    16,
    1078,   303,   827,   828,   829,   830,   831,   832,   949,   950,
     951,    91,    92,    93,   305,  1231,   312,   334,  1242,  1243,
     313,  1353,    57,  1239,  1240,   334,  1660,  1399,  1399,   317,
     318,   320,   319,   321,   322,   323,  1248,   334,  1249,  1250,
    1251,  1252,  1253,   325,   335,   336,  1256,   877,   326,    63,
     327,   328,   335,   336,   329,  1385,   330,   345,   343,    64,
     346,   401,  1678,   348,   335,   336,   349,   402,   416,   910,
     509,   510,   661,   662,   663,   664,   665,   403,   539,   666,
     667,   668,   669,  1430,   670,   671,   672,   673,   674,   546,
     675,   676,   254,   536,   254,   548,   934,   253,  1549,   547,
     549,   550,   560,   564,   565,   573,   606,   583,   337,   584,
     649,   575,   338,   598,   607,  1547,   337,   576,   608,   609,
     338,  1563,   611,   610,   614,   619,  1330,   711,   337,   764,
     779,   627,   338,   658,   699,   943,   684,   685,   686,   687,
     688,   689,   690,   691,   692,   721,   628,   629,   630,   631,
     632,    13,   648,   958,   695,   693,   694,   698,   714,   964,
     577,   339,   720,   760,   723,   340,   724,   772,   341,   339,
     789,    13,   767,   340,   978,  1159,   341,   778,   788,   790,
     797,   339,   801,   802,   334,   340,   837,   985,   341,   803,
      16,   820,   823,   342,  1507,   824,   836,   838,  1003,  1004,
     839,   342,   845,   855,   873,   254,   847,   915,   926,  1013,
      16,   335,   336,   342,  1019,   935,  1020,   936,  1021,   954,
     959,  1653,   977,   807,   987,   989,   992,   994,  1007,  1080,
    1078,  1008,  1009,   253,  1010,   253,  1011,  1012,  1018,  1656,
    1022,  1034,  1523,  1036,  1082,  1081,  1083,  1084,  1085,  1086,
    1111,  1100,  1095,   254,  1113,  1096,  1127,  1115,  1101,  1518,
    1102,  1534,  1138,  1123,  1659,   521,  1144,  1136,  1137,  1154,
     659,   660,   254,  1512,  1153,   337,  1195,  1175,  1094,   338,
    1653,  1152,  1099,  1198,  1164,  1165,  1168,  1174,  1178,  1183,
    1199,  1186,  1190,  1229,  1191,  1462,  1194,  1197,  1464,  1204,
    1209,  1205,  1208,  1230,  1211,  1078,  1232,  1241,  1126,  1245,
    1246,   625,  1247,  1254,  1285,   334,  1286,  1288,  1653,  1289,
    1300,  1295,  1296,  1302,  1078,   334,  1314,  1323,   339,  1324,
    1311,  1312,   340,  1328,  1160,   341,  1334,  1319,  1157,  1335,
    1336,  1361,   335,   336,  1359,  1375,   253,  1355,  1378,  1379,
    1381,  1380,   335,   336,  1382,  1387,  1389,  1390,  1392,  1396,
     342,  1397,  1177,  1429,  1053,   661,   662,   663,   664,   665,
    1391,  1402,   666,   667,   668,   669,  1450,   670,   671,   672,
     673,   674,  1431,   675,   676,  1436,  1447,   677,  1451,  1440,
    1453,   678,   679,   680,   253,  1448,  1449,   681,  1455,  1456,
    1618,  1460,  1479,  1465,  1621,  1463,   337,   934,  1466,  1472,
     338,  1468,  1473,   253,  1225,   334,   337,  1228,  1474,  1478,
     338,  1491,  1481,  1234,  1483,  1237,   682,  1091,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   254,  1492,
    1494,  1495,   335,   336,  1500,   625,  1503,  1513,   693,   694,
    1514,  1531,  1657,   334,  1524,  1525,  1277,  1528,  1279,   339,
    1284,  1542,   334,   340,  1543,  1173,   341,  1544,  1545,   339,
    1290,  1546,  1555,   340,  1551,  1179,   341,  1556,   934,  1553,
     335,   336,  1558,  1564,  1588,  1566,  1575,  1565,  1567,   335,
     336,   342,  1568,  1572,  1580,  1586,  1583,  1585,  1603,  1616,
    1212,   342,  1307,  1587,  1611,  1604,   337,  1610,  1694,  1620,
     338,  1632,  1313,  1634,  1697,  1635,  1636,  1318,  1639,  1320,
    1701,  1640,  1641,  1643,  1665,  1669,   123,  1670,  1327,  1644,
    1647,  1329,  1666,  1667,  1668,  1673,  1685,    20,   211,   835,
    1702,  1680,   126,  1714,   337,  1699,  1718,  1710,   338,  1711,
     807,  1724,  1725,   337,  1723,   941,   316,   338,   942,   339,
    1401,   854,   858,   340,  1150,  1180,   341,    26,   929,  1627,
    1504,  1590,  1360,  1591,  1536,  1628,  1629,    90,  1321,   253,
    1371,  1372,  1373,  1145,  1146,   588,  1654,   415,   334,   324,
     808,   342,     0,     0,  1053,   659,   660,   339,   590,  1386,
       0,   340,  1388,  1181,   341,     0,   339,     0,     0,   591,
     340,  1394,  1182,   341,     0,   335,   336,   746,   747,   748,
     749,   750,   751,   752,   753,     0,   592,   594,   595,   342,
       0,  1681,     0,     0,     0,     0,   754,     0,   342,     0,
       0,     0,   755,     0,     0,     0,     0,     0,  1696,     0,
       0,     0,     0,     0,   756,   757,   758,     0,     0,     0,
       0,  1438,  1703,  1439,  1705,     0,     0,     0,     0,  1053,
    1445,     0,     0,     0,     0,     0,     0,     0,     0,   337,
       0,     0,     0,   338,     0,   759,  1720,     0,  1053,     0,
     661,   662,   663,   664,   665,     0,     0,   666,   667,   668,
     669,     0,   670,   671,   672,   673,   674,     0,   675,   676,
    1467,     0,   677,     0,     0,   334,   678,   679,   680,     0,
       0,     0,   681,     0,     0,     0,     0,  1485,     0,     0,
       0,     0,   339,     0,   659,   660,   340,     0,  1184,   341,
       0,     0,   335,   336,  1498,  1499,     0,     0,     0,     0,
       0,   682,     0,   683,   684,   685,   686,   687,   688,   689,
     690,   691,   692,     0,   342,  1508,     0,     0,     0,     0,
       0,  1510,  1511,   693,   694,     0,     0,  1515,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   337,     0,   934,     0,
     338,     0,     0,     0,     0,     0,     0,   934,     0,     0,
       0,     0,  1529,     0,     0,  1530,     0,  1532,     0,   661,
     662,   663,   664,   665,     0,     0,   666,   667,   668,   669,
     -87,   670,   671,   672,   673,   674,     0,   675,   676,   807,
       0,   659,   660,     0,     0,   678,   679,   680,     0,   339,
       0,     0,     0,   340,     0,  1192,   341,     0,     0,  1557,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   334,  1571,
     682,   342,   683,   684,   685,   686,   687,   688,   689,   690,
     691,   692,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   693,   694,     0,   335,   336,     0,  1598,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1609,     0,     0,     0,     0,  1612,  1613,  1257,  1258,
    1259,  1260,  1261,  1262,  1263,  1264,   661,   662,   663,   664,
     665,  1265,  1266,   666,   667,   668,   669,  1267,   670,   671,
     672,   673,   674,  1268,   675,   676,  1269,  1270,   677,     0,
       0,     0,   678,   679,   680,  1271,  1272,  1273,   681,   337,
       0,     0,     0,   338,     0,     0,  1646,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1274,   682,     0,   683,
     684,   685,   686,   687,   688,   689,   690,   691,   692,     0,
       0,     0,  1672,     0,     0,     0,     0,     0,     0,   693,
     694,     0,   339,     0,     0,  1679,   340,     0,  1338,   341,
       0,     0,  1038,     0,  1684,     0,   428,   429,     3,     0,
    -121,  -106,  -106,  1695,  -118,     0,   430,   431,   432,   433,
     434,     0,     0,     0,   342,     0,   435,  1039,   436,  1040,
    1041,     0,   437,     0,     0,     0,     0,  1709,     0,  1042,
     438,  1043,     0,  -123,     0,  1044,   439,     0,     0,   440,
       0,     8,   441,  1045,     0,  1046,   442,     0,     0,  1047,
    1048,     0,     0,     0,     0,     0,  1049,     0,     0,   444,
     445,     0,   218,   219,   220,     0,   222,   223,   224,   225,
     226,   446,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,     0,   240,   241,   242,     0,     0,   245,
     246,   247,   248,   447,   448,   449,  1050,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   450,
     451,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     452,     0,    56,     0,     0,     0,     0,     0,     0,     0,
     453,   454,   455,   456,   457,     0,   458,     0,   459,   460,
     461,   462,   463,   464,   465,   466,    57,     0,    13,   467,
       0,   334,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   468,   469,   470,     0,    14,
       0,     0,   471,   472,     0,     0,     0,     0,   335,   336,
       0,   473,     0,   474,     0,   475,   476,    16,  1051,  1052,
    1038,     0,     0,     0,   428,   429,     3,     0,  -121,  -106,
    -106,     0,  -118,     0,   430,   431,   432,   433,   434,     0,
       0,     0,     0,     0,   435,  1039,   436,  1040,  1041,     0,
     437,     0,     0,     0,     0,     0,     0,  1042,   438,  1043,
       0,  -123,     0,  1044,   439,     0,     0,   440,     0,     8,
     441,  1045,   337,  1046,   442,     0,   338,  1047,  1048,     0,
       0,     0,     0,     0,  1049,     0,     0,   444,   445,     0,
     218,   219,   220,     0,   222,   223,   224,   225,   226,   446,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,     0,   240,   241,   242,     0,     0,   245,   246,   247,
     248,   447,   448,   449,  1050,   339,     0,     0,     0,   340,
       0,  1343,   341,     0,     0,     0,     0,   450,   451,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   342,   452,     0,
      56,     0,     0,     0,     0,     0,     0,     0,   453,   454,
     455,   456,   457,     0,   458,     0,   459,   460,   461,   462,
     463,   464,   465,   466,    57,     0,    13,   467,     0,   334,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   468,   469,   470,     0,    14,     0,     0,
     471,   472,     0,     0,     0,     0,   335,   336,     0,   473,
       0,   474,     0,   475,   476,    16,  1051,  -307,  1038,     0,
       0,     0,   428,   429,     3,     0,  -121,  -106,  -106,     0,
    -118,     0,   430,   431,   432,   433,   434,     0,     0,     0,
       0,     0,   435,  1039,   436,  1040,  1041,     0,   437,     0,
       0,     0,     0,     0,     0,  1042,   438,  1043,     0,  -123,
       0,  1044,   439,     0,     0,   440,     0,     8,   441,  1045,
     337,  1046,   442,     0,   338,  1047,  1048,     0,     0,     0,
       0,     0,  1049,     0,     0,   444,   445,     0,   218,   219,
     220,     0,   222,   223,   224,   225,   226,   446,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,     0,
     240,   241,   242,     0,     0,   245,   246,   247,   248,   447,
     448,   449,  1050,   339,     0,     0,     0,   340,     0,  1350,
     341,     0,     0,     0,     0,   450,   451,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   342,   452,     0,    56,     0,
       0,     0,     0,     0,     0,     0,   453,   454,   455,   456,
     457,     0,   458,     0,   459,   460,   461,   462,   463,   464,
     465,   466,    57,     0,    13,   467,     0,   334,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   468,   469,   470,     0,    14,     0,     0,   471,   472,
       0,     0,     0,     0,   335,   336,     0,   473,     0,   474,
       0,   475,   476,    16,  1051,  -333,  1038,     0,     0,     0,
     428,   429,     3,     0,  -121,  -106,  -106,     0,  -118,     0,
     430,   431,   432,   433,   434,     0,     0,     0,     0,     0,
     435,  1039,   436,  1040,  1041,     0,   437,     0,     0,     0,
       0,     0,     0,  1042,   438,  1043,     0,  -123,     0,  1044,
     439,     0,     0,   440,     0,     8,   441,  1045,   337,  1046,
     442,     0,   338,  1047,  1048,     0,     0,     0,     0,     0,
    1049,     0,     0,   444,   445,     0,   218,   219,   220,     0,
     222,   223,   224,   225,   226,   446,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,     0,   240,   241,
     242,     0,     0,   245,   246,   247,   248,   447,   448,   449,
    1050,   339,     0,     0,     0,   340,     0,  1519,   341,     0,
       0,     0,     0,   450,   451,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   342,   452,     0,    56,     0,     0,     0,
       0,     0,     0,     0,   453,   454,   455,   456,   457,     0,
     458,     0,   459,   460,   461,   462,   463,   464,   465,   466,
      57,     0,    13,   467,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   468,
     469,   470,     0,    14,     0,     0,   471,   472,     0,     0,
       0,     0,     0,     0,     0,   473,     0,   474,     0,   475,
     476,    16,  1051,  -304,  1038,     0,     0,     0,   428,   429,
       3,     0,  -121,  -106,  -106,     0,  -118,     0,   430,   431,
     432,   433,   434,     0,     0,     0,     0,     0,   435,  1039,
     436,  1040,  1041,     0,   437,     0,     0,     0,     0,     0,
       0,  1042,   438,  1043,     0,  -123,     0,  1044,   439,     0,
       0,   440,     0,     8,   441,  1045,     0,  1046,   442,     0,
       0,  1047,  1048,     0,     0,     0,     0,     0,  1049,     0,
       0,   444,   445,     0,   218,   219,   220,     0,   222,   223,
     224,   225,   226,   446,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,     0,   240,   241,   242,     0,
       0,   245,   246,   247,   248,   447,   448,   449,  1050,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   450,   451,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   452,     0,    56,     0,     0,     0,     0,     0,
       0,     0,   453,   454,   455,   456,   457,     0,   458,     0,
     459,   460,   461,   462,   463,   464,   465,   466,    57,     0,
      13,   467,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   468,   469,   470,
       0,    14,     0,     0,   471,   472,     0,     0,     0,     0,
       0,     0,     0,   473,     0,   474,     0,   475,   476,    16,
    1051,   -97,  1038,     0,     0,     0,   428,   429,     3,     0,
    -121,  -106,  -106,     0,  -118,     0,   430,   431,   432,   433,
     434,     0,     0,     0,     0,     0,   435,  1039,   436,  1040,
    1041,     0,   437,     0,     0,     0,     0,     0,     0,  1042,
     438,  1043,     0,  -123,     0,  1044,   439,     0,     0,   440,
       0,     8,   441,  1045,     0,  1046,   442,     0,     0,  1047,
    1048,     0,     0,     0,     0,     0,  1049,     0,     0,   444,
     445,     0,   218,   219,   220,     0,   222,   223,   224,   225,
     226,   446,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,     0,   240,   241,   242,     0,     0,   245,
     246,   247,   248,   447,   448,   449,  1050,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   450,
     451,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     452,     0,    56,     0,     0,     0,     0,     0,     0,     0,
     453,   454,   455,   456,   457,     0,   458,     0,   459,   460,
     461,   462,   463,   464,   465,   466,    57,     0,    13,   467,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   468,   469,   470,     0,    14,
       0,     0,   471,   472,     0,     0,     0,     0,     0,     0,
       0,   473,     0,   474,     0,   475,   476,    16,  1051,  -102,
     428,   429,     0,     0,     0,     0,     0,     0,     0,     0,
     430,   431,   432,   433,   434,     0,     0,     0,     0,     0,
     435,     0,   436,     0,     0,     0,   437,     0,     0,     0,
       0,     0,     0,     0,   438,     0,     0,     0,     0,     0,
     439,     0,     0,   440,     0,     0,   441,     0,     0,     0,
     442,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     443,     0,     0,   444,   445,   849,   218,   219,   220,     0,
     222,   223,   224,   225,   226,   446,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,     0,   240,   241,
     242,     0,     0,   245,   246,   247,   248,   447,   448,   449,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   450,   451,     0,     0,     0,     0,     0,
       0,     0,   524,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   452,     0,    56,     0,     0,     0,
       0,     0,     0,     0,   453,   454,   455,   456,   457,     0,
     458,   642,   459,   460,   461,   462,   463,   464,   465,   466,
     643,     0,     0,   467,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   468,
     469,   470,     0,    14,     0,     0,   471,   472,     0,     0,
       0,     0,     0,   428,   429,   850,     0,   474,   851,   475,
     476,   639,   477,   430,   431,   432,   433,   434,     0,     0,
       0,     0,     0,   435,     0,   436,     0,     0,     0,   437,
       0,     0,     0,     0,     0,     0,     0,   438,     0,     0,
       0,     0,     0,   439,     0,     0,   440,   640,     0,   441,
       0,     0,     0,   442,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   443,     0,     0,   444,   445,     0,   218,
     219,   220,     0,   222,   223,   224,   225,   226,   446,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
       0,   240,   241,   242,     0,     0,   245,   246,   247,   248,
     447,   448,   449,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   450,   451,     0,     0,
       0,     0,     0,     0,     0,   524,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   452,     0,    56,
       0,     0,     0,     0,     0,     0,     0,   453,   454,   455,
     456,   457,     0,   458,   642,   459,   460,   461,   462,   463,
     464,   465,   466,   643,     0,     0,   467,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   468,   469,   470,     0,    14,     0,     0,   471,
     472,     0,     0,     0,     0,     0,   428,   429,   473,     0,
     474,     0,   475,   476,   639,   477,   430,   431,   432,   433,
     434,     0,     0,     0,     0,     0,   435,     0,   436,     0,
       0,     0,   437,     0,     0,     0,     0,     0,     0,     0,
     438,     0,     0,     0,     0,     0,   439,     0,     0,   440,
     640,     0,   441,     0,     0,     0,   442,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   443,     0,     0,   444,
     445,     0,   218,   219,   220,     0,   222,   223,   224,   225,
     226,   446,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,     0,   240,   241,   242,     0,     0,   245,
     246,   247,   248,   447,   448,   449,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   450,
     451,     0,     0,     0,     0,     0,     0,     0,   524,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     452,     0,    56,     0,     0,     0,     0,     0,     0,     0,
     453,   454,   455,   456,   457,     0,   458,     0,   459,   460,
     461,   462,   463,   464,   465,   466,    57,     0,     0,   467,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   468,   469,   470,     0,    14,
       0,     0,   471,   472,     0,     0,     0,     0,     0,   428,
     429,   473,     0,   474,     0,   475,   476,     0,   477,   430,
     431,   432,   433,   434,     0,     0,     0,     0,     0,   435,
       0,   436,     0,     0,     0,   437,     0,     0,     0,     0,
       0,     0,     0,   438,     0,     0,     0,     0,     0,   439,
       0,     0,   440,     0,     0,   441,     0,     0,     0,   442,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   443,
       0,     0,   444,   445,   973,   218,   219,   220,     0,   222,
     223,   224,   225,   226,   446,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,     0,   240,   241,   242,
       0,     0,   245,   246,   247,   248,   447,   448,   449,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   450,   451,     0,     0,     0,     0,     0,     0,
       0,   524,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   452,     0,    56,     0,     0,     0,     0,
       0,     0,     0,   453,   454,   455,   456,   457,     0,   458,
     642,   459,   460,   461,   462,   463,   464,   465,   466,   643,
       0,     0,   467,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   468,   469,
     470,     0,    14,     0,     0,   471,   472,     0,     0,     0,
       0,     0,   428,   429,   473,     0,   474,     0,   475,   476,
       0,   477,   430,   431,   432,   433,   434,     0,     0,     0,
       0,     0,   435,     0,   436,     0,     0,     0,   437,     0,
       0,     0,     0,     0,     0,     0,   438,     0,     0,     0,
       0,     0,   439,     0,     0,   440,     0,     0,   441,     0,
       0,     0,   442,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   443,     0,     0,   444,   445,     0,   218,   219,
     220,     0,   222,   223,   224,   225,   226,   446,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,     0,
     240,   241,   242,     0,     0,   245,   246,   247,   248,   447,
     448,   449,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   450,   451,     0,     0,     0,
       0,     0,     0,     0,   524,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   452,     0,    56,     0,
       0,     0,     0,     0,     0,     0,   453,   454,   455,   456,
     457,     0,   458,   642,   459,   460,   461,   462,   463,   464,
     465,   466,   643,     0,     0,   467,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   468,   469,   470,     0,    14,     0,     0,   471,   472,
       0,     0,     0,     0,     0,   428,   429,  1280,     0,   474,
    1281,   475,   476,     0,   477,   430,   431,   432,   433,   434,
       0,     0,     0,     0,     0,   435,     0,   436,     0,     0,
       0,   437,     0,     0,     0,     0,     0,     0,     0,   438,
       0,     0,     0,     0,     0,   439,     0,     0,   440,     0,
       0,   441,     0,     0,     0,   442,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   443,     0,     0,   444,   445,
       0,   218,   219,   220,     0,   222,   223,   224,   225,   226,
     446,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,     0,   240,   241,   242,     0,     0,   245,   246,
     247,   248,   447,   448,   449,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   450,   451,
       0,     0,     0,     0,     0,     0,     0,   524,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   452,
       0,    56,     0,     0,     0,     0,     0,     0,     0,   453,
     454,   455,   456,   457,     0,   458,   642,   459,   460,   461,
     462,   463,   464,   465,   466,   643,     0,     0,   467,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   468,   469,   470,     0,    14,     0,
       0,   471,   472,     0,     0,     0,     0,     0,   428,   429,
    1291,     0,   474,  1292,   475,   476,     0,   477,   430,   431,
     432,   433,   434,     0,     0,     0,     0,     0,   435,     0,
     436,     0,     0,     0,   437,     0,     0,     0,     0,     0,
       0,     0,   438,     0,     0,     0,     0,     0,   439,     0,
       0,   440,     0,     0,   441,     0,     0,     0,   442,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   443,     0,
       0,   444,   445,     0,   218,   219,   220,     0,   222,   223,
     224,   225,   226,   446,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,     0,   240,   241,   242,     0,
       0,   245,   246,   247,   248,   447,   448,   449,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   450,   451,     0,     0,     0,     0,     0,     0,     0,
     524,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   452,     0,    56,     0,     0,     0,     0,     0,
       0,     0,   453,   454,   455,   456,   457,     0,   458,   642,
     459,   460,   461,   462,   463,   464,   465,   466,   643,     0,
       0,   467,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   468,   469,   470,
       0,    14,     0,     0,   471,   472,     0,     0,     0,     0,
       0,   428,   429,   473,     0,   474,     0,   475,   476,     0,
     477,   430,   431,   432,   433,   434,     0,     0,     0,     0,
       0,   435,     0,   436,     0,     0,     0,   437,     0,     0,
       0,     0,     0,     0,     0,   438,     0,     0,     0,     0,
       0,   439,     0,     0,   440,     0,     0,   441,     0,     0,
       0,   442,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   443,     0,     0,   444,   445,     0,   218,   219,   220,
       0,   222,   223,   224,   225,   226,   446,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,     0,   240,
     241,   242,     0,     0,   245,   246,   247,   248,   447,   448,
     449,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   450,   451,     0,     0,     0,     0,
       0,     0,     0,   524,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   452,     0,    56,     0,     0,
       0,     0,     0,     0,     0,   453,   454,   455,   456,   457,
       0,   458,     0,   459,   460,   461,   462,   463,   464,   465,
     466,    57,     0,     0,   467,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     468,   469,   470,     0,    14,     0,     0,   471,   472,     0,
       0,     0,     0,     0,   428,   429,   473,     0,   474,   911,
     475,   476,     0,   477,   430,   431,   432,   433,   434,     0,
       0,     0,     0,     0,   435,     0,   436,     0,     0,     0,
     437,     0,     0,     0,     0,     0,     0,     0,   438,     0,
       0,     0,     0,     0,   439,     0,     0,   440,     0,     0,
     441,     0,     0,     0,   442,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   443,     0,     0,   444,   445,     0,
     218,   219,   220,     0,   222,   223,   224,   225,   226,   446,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,     0,   240,   241,   242,     0,     0,   245,   246,   247,
     248,   447,   448,   449,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   450,   451,     0,
       0,     0,     0,     0,     0,     0,   933,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   452,     0,
      56,     0,     0,     0,     0,     0,     0,     0,   453,   454,
     455,   456,   457,     0,   458,   642,   459,   460,   461,   462,
     463,   464,   465,   466,   643,     0,     0,   467,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   468,   469,   470,     0,    14,     0,     0,
     471,   472,     0,     0,     0,     0,     0,   428,   429,  1214,
       0,   474,     0,   475,   476,     0,   477,   430,   431,   432,
     433,   434,     0,     0,     0,     0,     0,   435,     0,   436,
       0,     0,     0,   437,     0,     0,     0,     0,     0,     0,
       0,   438,     0,     0,     0,     0,     0,   439,     0,     0,
     440,     0,     0,   441,     0,     0,     0,   442,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   443,     0,     0,
     444,   445,     0,   218,   219,   220,     0,   222,   223,   224,
     225,   226,   446,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,     0,   240,   241,   242,     0,     0,
     245,   246,   247,   248,   447,   448,   449,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     450,   451,     0,     0,     0,     0,     0,     0,     0,   524,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   452,     0,    56,     0,     0,     0,     0,     0,     0,
       0,   453,   454,   455,   456,   457,     0,   458,     0,   459,
     460,   461,   462,   463,   464,   465,   466,    57,     0,     0,
     467,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   468,   469,   470,     0,
      14,     0,     0,   471,   472,     0,     0,     0,     0,     0,
     428,   429,   473,     0,   474,  1298,   475,   476,     0,   477,
     430,   431,   432,   433,   434,     0,     0,     0,     0,     0,
     435,     0,   436,     0,     0,     0,   437,     0,     0,     0,
       0,     0,     0,     0,   438,     0,     0,     0,     0,     0,
     439,     0,     0,   440,     0,     0,   441,     0,     0,     0,
     442,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     443,     0,     0,   444,   445,     0,   218,   219,   220,     0,
     222,   223,   224,   225,   226,   446,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,     0,   240,   241,
     242,     0,     0,   245,   246,   247,   248,   447,   448,   449,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   450,   451,     0,     0,     0,     0,     0,
       0,     0,   524,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   452,     0,    56,     0,     0,     0,
       0,     0,     0,     0,   453,   454,   455,   456,   457,     0,
     458,     0,   459,   460,   461,   462,   463,   464,   465,   466,
      57,     0,     0,   467,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   468,
     469,   470,     0,    14,     0,     0,   471,   472,     0,     0,
       0,     0,     0,   428,   429,   473,     0,   474,  1356,   475,
     476,     0,   477,   430,   431,   432,   433,   434,     0,     0,
       0,     0,     0,   435,     0,   436,     0,     0,     0,   437,
       0,     0,     0,     0,     0,     0,     0,   438,     0,     0,
       0,     0,     0,   439,     0,     0,   440,     0,     0,   441,
       0,     0,     0,   442,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   443,     0,     0,   444,   445,     0,   218,
     219,   220,     0,   222,   223,   224,   225,   226,   446,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
       0,   240,   241,   242,     0,     0,   245,   246,   247,   248,
     447,   448,   449,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   450,   451,     0,     0,
       0,     0,     0,     0,     0,   933,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   452,     0,    56,
       0,     0,     0,     0,     0,     0,     0,   453,   454,   455,
     456,   457,     0,   458,   642,   459,   460,   461,   462,   463,
     464,   465,   466,   643,     0,     0,   467,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   468,   469,   470,     0,    14,     0,     0,   471,
     472,     0,     0,     0,     0,     0,   428,   429,   473,     0,
     474,     0,   475,   476,     0,   477,   430,   431,   432,   433,
     434,     0,     0,     0,     0,     0,   435,     0,   436,     0,
       0,     0,   437,     0,     0,     0,     0,     0,     0,     0,
     438,     0,     0,     0,     0,     0,   439,     0,     0,   440,
       0,     0,   441,     0,     0,     0,   442,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   443,     0,     0,   444,
     445,     0,   218,   219,   220,     0,   222,   223,   224,   225,
     226,   446,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,     0,   240,   241,   242,     0,     0,   245,
     246,   247,   248,   447,   448,   449,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   450,
     451,     0,     0,     0,     0,     0,     0,     0,   524,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     452,     0,    56,     0,     0,     0,     0,     0,     0,     0,
     453,   454,   455,   456,   457,     0,   458,     0,   459,   460,
     461,   462,   463,   464,   465,   466,    57,     0,     0,   467,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   468,   469,   470,     0,    14,
       0,     0,   471,   472,     0,     0,     0,     0,     0,   428,
     429,   473,     0,   474,     0,   475,   476,     0,   477,   430,
     431,   432,   433,   434,     0,     0,     0,     0,     0,   435,
       0,   436,     0,     0,     0,   437,     0,     0,     0,     0,
       0,     0,     0,   438,     0,     0,     0,     0,     0,   439,
       0,     0,   440,     0,     0,   441,     0,     0,     0,   442,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   443,
       0,     0,   444,   445,     0,   218,   219,   220,     0,   222,
     223,   224,   225,   226,   446,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,     0,   240,   241,   242,
       0,     0,   245,   246,   247,   248,   447,   448,   449,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   450,   451,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   452,     0,    56,     0,     0,     0,     0,
       0,     0,     0,   453,   454,   455,   456,   457,     0,   458,
       0,   459,   460,   461,   462,   463,   464,   465,   466,    57,
       0,     0,   467,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   468,   469,
     470,     0,    14,     0,     0,   471,   472,     0,     0,     0,
       0,     0,   428,   429,   473,   534,   474,     0,   475,   476,
       0,   477,   430,   431,   432,   433,   434,     0,     0,     0,
       0,     0,   435,     0,   436,     0,     0,     0,   437,     0,
       0,     0,     0,     0,     0,     0,   438,     0,     0,     0,
       0,     0,   439,     0,     0,   440,     0,     0,   441,     0,
       0,     0,   442,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   443,     0,     0,   444,   445,     0,   218,   219,
     220,     0,   222,   223,   224,   225,   226,   446,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,     0,
     240,   241,   242,     0,     0,   245,   246,   247,   248,   447,
     448,   449,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   450,   451,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   452,     0,    56,     0,
       0,     0,     0,     0,     0,     0,   453,   454,   455,   456,
     457,     0,   458,     0,   459,   460,   461,   462,   463,   464,
     465,   466,    57,     0,     0,   467,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   468,   469,   470,     0,    14,     0,     0,   471,   472,
       0,     0,     0,     0,     0,   428,   429,   473,   725,   474,
       0,   475,   476,     0,   477,   430,   431,   432,   433,   434,
       0,     0,     0,     0,     0,   435,     0,   436,     0,     0,
       0,   437,     0,     0,     0,     0,     0,     0,     0,   438,
       0,     0,     0,     0,     0,   439,     0,     0,   440,     0,
       0,   441,     0,     0,     0,   442,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   443,     0,     0,   444,   445,
       0,   218,   219,   220,     0,   222,   223,   224,   225,   226,
     446,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,     0,   240,   241,   242,     0,     0,   245,   246,
     247,   248,   447,   448,   449,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   450,   451,
       0,     0,     0,     0,     0,     0,     0,   933,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   452,
       0,    56,     0,     0,     0,     0,     0,     0,     0,   453,
     454,   455,   456,   457,     0,   458,     0,   459,   460,   461,
     462,   463,   464,   465,   466,    57,     0,     0,   467,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   468,   469,   470,     0,    14,     0,
       0,   471,   472,     0,     0,     0,     0,     0,   428,   429,
     473,     0,   474,     0,   475,   476,  1025,   477,   430,   431,
     432,   433,   434,     0,     0,     0,     0,     0,   435,     0,
     436,     0,     0,     0,   437,     0,     0,     0,     0,     0,
       0,     0,   438,     0,     0,     0,     0,     0,   439,     0,
       0,   440,     0,     0,   441,     0,     0,     0,   442,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   443,     0,
       0,   444,   445,     0,   218,   219,   220,     0,   222,   223,
     224,   225,   226,   446,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,     0,   240,   241,   242,     0,
       0,   245,   246,   247,   248,   447,   448,   449,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   450,   451,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   452,     0,    56,     0,     0,     0,     0,     0,
       0,     0,   453,   454,   455,   456,   457,     0,   458,     0,
     459,   460,   461,   462,   463,   464,   465,   466,    57,     0,
       0,   467,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   468,   469,   470,
       0,    14,     0,     0,   471,   472,     0,     0,     0,     0,
       0,   428,   429,   473,     0,   474,     0,   475,   476,     0,
     477,   430,   431,   432,   433,   434,     0,     0,     0,     0,
       0,   435,     0,   436,     0,     0,     0,   437,     0,     0,
       0,     0,     0,     0,     0,   438,     0,     0,     0,     0,
       0,   439,     0,     0,   440,     0,     0,   441,     0,     0,
       0,   442,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   443,     0,     0,   444,   445,     0,   218,   219,   220,
       0,   222,   223,   224,   225,   226,   446,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,     0,   240,
     241,   242,     0,     0,   245,   246,   247,   248,   447,   448,
     449,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   450,   451,     0,     0,     0,     0,
       0,     0,     0,  1224,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   452,     0,    56,     0,     0,
       0,     0,     0,     0,     0,   453,   454,   455,   456,   457,
       0,   458,     0,   459,   460,   461,   462,   463,   464,   465,
     466,    57,     0,     0,   467,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     468,   469,   470,     0,    14,     0,     0,   471,   472,     0,
       0,     0,     0,     0,   428,   429,   473,     0,   474,     0,
     475,   476,     0,   477,   430,   431,   432,   433,   434,     0,
       0,     0,     0,     0,   435,     0,   436,     0,     0,     0,
     437,     0,     0,     0,     0,     0,     0,     0,   438,     0,
       0,     0,     0,     0,   439,     0,     0,   440,     0,     0,
     441,     0,     0,     0,   442,     0,     0,     0,     0,     0,
    1227,     0,     0,     0,   443,     0,     0,   444,   445,     0,
     218,   219,   220,     0,   222,   223,   224,   225,   226,   446,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,     0,   240,   241,   242,     0,     0,   245,   246,   247,
     248,   447,   448,   449,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   450,   451,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   452,     0,
      56,     0,     0,     0,     0,     0,     0,     0,   453,   454,
     455,   456,   457,     0,   458,     0,   459,   460,   461,   462,
     463,   464,   465,   466,    57,     0,     0,   467,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   468,   469,   470,     0,    14,     0,     0,
     471,   472,     0,     0,     0,     0,     0,   428,   429,   473,
       0,   474,     0,   475,   476,     0,   477,   430,   431,   432,
     433,   434,     0,     0,     0,     0,     0,   435,     0,   436,
       0,     0,     0,   437,     0,     0,     0,     0,     0,     0,
       0,   438,     0,     0,     0,     0,     0,   439,     0,     0,
     440,     0,     0,   441,     0,     0,     0,   442,     0,     0,
    1233,     0,     0,     0,     0,     0,     0,   443,     0,     0,
     444,   445,     0,   218,   219,   220,     0,   222,   223,   224,
     225,   226,   446,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,     0,   240,   241,   242,     0,     0,
     245,   246,   247,   248,   447,   448,   449,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     450,   451,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   452,     0,    56,     0,     0,     0,     0,     0,     0,
       0,   453,   454,   455,   456,   457,     0,   458,     0,   459,
     460,   461,   462,   463,   464,   465,   466,    57,     0,     0,
     467,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   468,   469,   470,     0,
      14,     0,     0,   471,   472,     0,     0,     0,     0,     0,
     428,   429,   473,     0,   474,     0,   475,   476,     0,   477,
     430,   431,   432,   433,   434,     0,     0,     0,     0,     0,
     435,     0,   436,     0,     0,     0,   437,     0,     0,     0,
       0,     0,     0,     0,   438,     0,     0,     0,     0,     0,
     439,     0,     0,   440,     0,     0,   441,     0,     0,     0,
     442,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     443,     0,     0,   444,   445,     0,   218,   219,   220,     0,
     222,   223,   224,   225,   226,   446,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,     0,   240,   241,
     242,     0,     0,   245,   246,   247,   248,   447,   448,   449,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   450,   451,     0,     0,     0,     0,     0,
       0,     0,  1236,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   452,     0,    56,     0,     0,     0,
       0,     0,     0,     0,   453,   454,   455,   456,   457,     0,
     458,     0,   459,   460,   461,   462,   463,   464,   465,   466,
      57,     0,     0,   467,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   468,
     469,   470,     0,    14,     0,     0,   471,   472,     0,     0,
       0,     0,     0,   428,   429,   473,     0,   474,     0,   475,
     476,     0,   477,   430,   431,   432,   433,   434,     0,     0,
       0,     0,     0,   435,     0,   436,     0,     0,     0,   437,
       0,     0,     0,     0,     0,     0,     0,   438,     0,     0,
       0,     0,     0,   439,     0,     0,   440,     0,     0,   441,
       0,     0,     0,   442,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   443,     0,     0,   444,   445,     0,   218,
     219,   220,     0,   222,   223,   224,   225,   226,   446,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
       0,   240,   241,   242,     0,     0,   245,   246,   247,   248,
     447,   448,   449,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   450,   451,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   452,     0,    56,
       0,     0,     0,     0,     0,     0,     0,   453,   454,   455,
     456,   457,     0,   458,     0,   459,   460,   461,   462,   463,
     464,   465,   466,    57,     0,     0,   467,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   468,   469,   470,     0,    14,     0,     0,   471,
     472,     0,     0,     0,     0,     0,   428,   429,   473,     0,
     474,  1484,   475,   476,     0,   477,   430,   431,   432,   433,
     434,     0,     0,     0,     0,     0,   435,     0,   436,     0,
       0,     0,   437,     0,     0,     0,     0,     0,     0,     0,
     438,     0,     0,     0,     0,     0,   439,     0,     0,   440,
       0,     0,   441,     0,     0,     0,   442,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   443,     0,     0,   444,
     445,     0,   218,   219,   220,     0,   222,   223,   224,   225,
     226,   446,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,     0,   240,   241,   242,     0,     0,   245,
     246,   247,   248,   447,   448,   449,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   450,
     451,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     452,     0,    56,     0,     0,     0,     0,     0,     0,     0,
     453,   454,   455,   456,   457,     0,   458,     0,   459,   460,
     461,   462,   463,   464,   465,   466,    57,     0,     0,   467,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   468,   469,   470,     0,    14,
       0,     0,   471,   472,     0,     0,     0,     0,     0,   428,
     429,   473,     0,   474,     0,   475,   476,     0,   477,   430,
     431,   432,   433,   434,     0,     0,     0,     0,     0,   435,
    1039,   436,  1040,     0,     0,   437,     0,     0,     0,     0,
       0,     0,     0,   438,     0,     0,     0,     0,     0,   439,
       0,     0,   440,     0,     0,   441,  1045,     0,     0,   442,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   443,
       0,     0,   444,   445,     0,   218,   219,   220,     0,   222,
     223,   224,   225,   226,   446,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,     0,   240,   241,   242,
       0,     0,   245,   246,   247,   248,   447,   448,   449,  1050,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   450,   451,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   452,     0,    56,     0,     0,     0,     0,
       0,     0,     0,   453,   454,   455,   456,   457,     0,   458,
       0,   459,   460,   461,   462,   463,   464,   465,   466,    57,
       0,     0,   467,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   468,   469,
     470,     0,    14,     0,     0,   471,   472,     0,     0,     0,
     428,   429,     0,     0,   473,     0,   474,     0,   475,   476,
     430,   431,   432,   433,   434,     0,     0,     0,     0,     0,
     435,     0,   436,     0,     0,     0,   437,     0,     0,     0,
       0,     0,     0,     0,   438,     0,     0,     0,     0,     0,
     439,     0,     0,   440,     0,     0,   441,     0,     0,     0,
     442,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     443,     0,     0,   444,   445,     0,   218,   219,   220,     0,
     222,   223,   224,   225,   226,   446,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,     0,   240,   241,
     242,     0,     0,   245,   246,   247,   248,   447,   448,   449,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   450,   451,     0,     0,     0,     0,     0,
       0,     0,   770,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   452,     0,    56,     0,     0,     0,
       0,     0,     0,     0,   453,   454,   455,   456,   457,     0,
     458,     0,   459,   460,   461,   462,   463,   464,   465,   466,
      57,     0,     0,   467,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   468,
     469,   470,     0,    14,     0,     0,   471,   472,     0,     0,
       0,   428,   429,     0,     0,   473,     0,   474,     0,   475,
     476,   430,   431,   432,   433,   434,     0,     0,   890,     0,
       0,   435,     0,   436,     0,     0,     0,   437,     0,     0,
       0,     0,     0,     0,     0,   438,     0,     0,     0,     0,
       0,   439,     0,     0,   440,     0,     0,   441,     0,     0,
       0,   442,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   443,     0,     0,   444,   445,     0,   218,   219,   220,
       0,   222,   223,   224,   225,   226,   446,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,     0,   240,
     241,   242,     0,     0,   245,   246,   247,   248,   447,   448,
     449,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   450,   451,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   452,     0,    56,     0,     0,
       0,     0,     0,     0,     0,   453,   454,   455,   456,   457,
       0,   458,     0,   459,   460,   461,   462,   463,   464,   465,
     466,    57,     0,     0,   467,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     468,   469,   470,     0,    14,     0,     0,   471,   472,     0,
       0,     0,   428,   429,     0,     0,   473,     0,   474,     0,
     475,   476,   430,   431,   432,   433,   434,     0,     0,     0,
       0,     0,   435,     0,   436,     0,     0,     0,   437,     0,
       0,     0,     0,     0,     0,     0,   438,     0,     0,     0,
       0,     0,   439,     0,     0,   440,     0,     0,   441,     0,
       0,     0,   442,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   443,     0,     0,   444,   445,     0,   218,   219,
     220,     0,   222,   223,   224,   225,   226,   446,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,     0,
     240,   241,   242,     0,     0,   245,   246,   247,   248,   447,
     448,   449,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   450,   451,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   452,     0,    56,     0,
       0,     0,     0,     0,     0,     0,   453,   454,   455,   456,
     457,     0,   458,     0,   459,   460,   461,   462,   463,   464,
     465,   466,    57,     0,   212,   467,     0,     0,     0,     0,
     213,     0,     0,     0,     0,     0,   214,     0,     0,     0,
       0,   468,   469,   470,     0,    14,   215,     0,   471,   472,
       0,     0,     0,     0,   216,     0,     0,   473,     0,   474,
       0,   475,   476,     0,     0,     0,     0,     0,     0,   217,
       0,     0,     0,     0,     0,     0,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   212,
       0,     0,     0,     0,     0,   213,     0,     0,     0,     0,
       0,   214,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   215,     0,     0,     0,     0,    56,     0,     0,   216,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   251,
       0,     0,     0,     0,   217,     0,     0,     0,     0,     0,
      57,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,     0,     0,     0,     0,     0,   252,
       0,     0,     0,     0,   537,     0,   212,     0,     0,     0,
       0,     0,   213,     0,     0,     0,     0,     0,   214,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   215,     0,
       0,    56,     0,     0,     0,     0,   216,     0,     0,     0,
       0,     0,     0,     0,   251,     0,     0,     0,     0,     0,
       0,   217,     0,     0,     0,   707,     0,    13,   218,   219,
     220,   221,   222,   223,   224,   225,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   247,   248,   249,
     250,     0,     0,     0,   252,     0,    16,     0,     0,     0,
       0,   212,     0,     0,     0,   350,   351,   213,     0,     0,
       0,     0,     0,   214,     0,     0,     0,     0,     0,     0,
       0,     0,   352,   215,     0,     0,     0,     0,    56,     0,
       0,   216,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   251,     0,     0,     0,     0,   217,     0,     0,     0,
       0,     0,    57,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,     0,     0,     0,     0,
       0,   252,   353,   354,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   364,   365,   366,   367,   368,   369,   370,
     659,   660,   371,   372,   373,     0,     0,   374,   375,   376,
     377,   378,     0,    56,     0,     0,   379,   380,   381,   382,
     383,   384,   385,     0,     0,     0,   251,     0,     0,     0,
       0,     0,     0,     0,   659,   660,     0,   707,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   386,     0,   387,   388,   389,   390,   391,   392,   393,
     394,   395,   396,     0,     0,   397,   398,     0,     0,     0,
       0,     0,     0,   399,   400,     0,   252,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   661,   662,   663,   664,   665,
       0,     0,   666,   667,   668,   669,     0,   670,   671,   672,
     673,   674,     0,   675,   676,     0,     0,  -855,     0,   659,
     660,   678,   679,   680,     0,     0,     0,  -855,     0,   661,
     662,   663,   664,   665,     0,     0,   666,   667,   668,   669,
       0,   670,   671,   672,   673,   674,     0,   675,   676,   659,
     660,     0,     0,     0,     0,   678,   682,   680,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   693,   694,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   683,   684,   685,   686,   687,   688,   689,   690,
     691,   692,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   693,   694,   661,   662,   663,   664,   665,     0,
       0,   666,   667,   668,   669,     0,   670,   671,   672,   673,
     674,     0,   675,   676,   659,   660,     0,     0,     0,     0,
     678,     0,     0,     0,   661,   662,   663,   664,   665,     0,
       0,   666,   667,   668,   669,     0,   670,   671,   672,   673,
     674,     0,   675,   676,   659,   660,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   683,   684,   685,
     686,   687,   688,   689,   690,   691,   692,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   693,   694,     0,
       0,     0,     0,     0,     0,     0,     0,   683,   684,   685,
     686,   687,   688,   689,   690,   691,   692,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   693,   694,   661,
     662,   663,   664,   665,     0,     0,   666,   667,   668,   669,
       0,   670,   671,   672,   673,   674,     0,   675,   676,   659,
     660,     0,     0,     0,     0,     0,     0,     0,     0,   661,
     662,   663,   664,   665,     0,     0,   666,   667,   668,   669,
       0,   670,   671,   672,   673,   674,     0,   675,   676,   659,
     660,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   685,   686,   687,   688,   689,   690,
     691,   692,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   693,   694,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   686,   687,   688,   689,   690,
     691,   692,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   693,   694,   661,   662,   663,   664,   665,     0,
       0,   666,     0,     0,   669,     0,   670,   671,   672,   673,
     674,     0,   675,   676,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   661,   662,   663,   664,     0,     0,
       0,     0,     0,     0,   669,     0,   670,   671,   672,   673,
     674,     0,   675,   676,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   859,     0,     0,
     686,   687,   688,   689,   690,   691,   692,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   693,   694,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   863,     0,
       0,     0,   688,   689,   690,   691,   692,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   693,   694,   218,
     219,   220,     0,   222,   223,   224,   225,   226,   446,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
       0,   240,   241,   242,     0,     0,   245,   246,   247,   248,
     218,   219,   220,     0,   222,   223,   224,   225,   226,   446,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,     0,   240,   241,   242,     0,     0,   245,   246,   247,
     248,     0,     0,     0,     0,     0,     0,     0,     0,  1087,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   860,     0,     0,     0,     0,     0,
     272,     0,   273,   861,   274,   275,   276,   277,   278,     0,
     279,   280,   281,   282,   283,   284,   285,   286,   287,   288,
     289,     0,   290,   291,   292,   864,   271,   293,   294,   295,
     296,   218,   219,   220,   865,   222,   223,   224,   225,   226,
     446,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,     0,   240,   241,   242,     0,     0,   245,   246,
     247,   248,   272,     0,   273,     0,   274,   275,   276,   277,
     278,     0,   279,   280,   281,   282,   283,   284,   285,   286,
     287,   288,   289,     0,   290,   291,   292,     0,     0,   293,
     294,   295,   296,     0,   542,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   297,
     298,     0,     0,     0,     0,     0,  1088,     0,     0,     0,
       0,     0,   218,   219,   220,  1089,   222,   223,   224,   225,
     226,   446,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   237,   238,     0,   240,   241,   242,     0,     0,   245,
     246,   247,   248,     0,     0,   272,   299,   273,     0,   274,
     275,   276,   277,   278,     0,   279,   280,   281,   282,   283,
     284,   285,   286,   287,   288,   289,     0,   290,   291,   292,
     902,   903,   293,   294,   295,   296,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   904,     0,     0,
       0,     0,     0,   272,     0,   273,   905,   274,   275,   276,
     277,   278,     0,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,     0,   290,   291,   292,     0,     0,
     293,   294,   295,   296,     0,     0,     0,     0,     0,   544,
     906,   907,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   732
};

static const yytype_int16 yycheck[] =
{
       1,    14,    15,   141,   142,   100,   333,   574,   168,   570,
     432,   540,   432,   582,    79,   644,   645,   345,  1018,    20,
      21,    22,   772,   188,   541,   948,   512,  1041,   514,  1385,
     516,   702,  1175,   704,   188,   706,   937,   648,   931,  1348,
       8,    19,  1255,   350,   351,    22,    33,  1354,    49,    62,
      63,    64,   821,  1566,   818,   956,     5,     6,    33,    15,
      16,   858,  1616,    20,  1616,    20,  1616,   139,     5,    20,
    1616,  1616,    40,    19,    20,    20,    25,   140,   167,   126,
      57,    46,    31,   140,  1541,   450,   451,   716,   101,   102,
     103,   104,   175,  1550,   422,   150,   153,   142,   143,   144,
     148,  1024,     7,   468,   469,   470,   471,   472,   126,   158,
     165,   126,   178,   202,   129,   130,   182,   165,   201,    68,
      69,  1675,  1552,  1675,   474,  1675,   177,    15,    16,  1675,
    1675,   178,   204,   205,  1367,   207,   183,   200,   203,   187,
     188,   106,  1599,  1600,   713,    50,   203,   202,   717,   165,
     310,   199,   207,   102,   103,   202,  1465,  1466,   203,  1713,
     178,  1713,  1518,  1713,   302,   102,   103,  1713,  1713,   307,
    1403,   521,  1481,   311,  1483,   188,   805,  1607,   150,   808,
     156,  1488,   850,   139,   199,   200,   797,   816,   204,   165,
     819,   345,   141,   165,   181,   560,    62,  1710,     8,   167,
     127,   202,   158,    44,   182,  1002,   181,   163,  1208,   165,
     187,  1724,   168,   982,   156,   782,   165,   981,   175,   165,
     175,  1235,   199,   165,   175,   200,    36,   203,  1129,  1122,
     175,   126,   200,   182,   209,  1544,  1545,   806,   849,   252,
     208,   548,  1551,    84,  1145,   182,   202,   312,  1646,   176,
     127,   200,   179,   603,   150,   677,   133,   677,   207,   167,
     425,   426,   427,   613,   141,   202,   616,   176,   422,   165,
     158,   425,   426,   427,  1672,   163,   604,   165,   150,   127,
     168,  1204,   420,   178,   127,   133,   127,   128,   183,   130,
     133,   619,   126,   165,   202,   167,   661,   662,   648,   176,
     665,   666,   667,   668,  1517,   670,   202,   202,   673,   674,
     675,   676,   677,   678,   679,   680,   681,   682,   683,   684,
     685,   686,   687,   688,   689,   690,   691,   692,   176,   127,
     126,  1474,   345,   176,   206,  1006,   208,   167,   141,  1353,
     826,  1697,   507,   508,   178,   695,   511,   182,   513,   183,
     515,    21,    22,   507,   508,   129,   130,   511,   523,   513,
     929,   515,   973,   517,  1032,  1626,  1037,   202,   202,   523,
     856,   175,   156,  1387,   175,   178,   206,   175,   176,   187,
     178,   165,   178,   181,   127,   150,   540,   183,   140,   175,
     133,   199,   557,   558,  1317,   962,   925,   178,  1027,   203,
     165,   153,  1663,   557,   558,   770,   202,   175,   977,   422,
     939,   928,   425,   426,   427,   127,  1084,   203,   202,   432,
     433,   133,   165,   148,   941,   199,   200,   141,  1096,   127,
     127,   175,  1001,   176,   167,   133,   133,   202,   181,   452,
     165,    33,   141,   165,   175,   167,   175,   797,   118,   119,
     604,   165,   175,   781,   183,   175,   126,   201,   128,   129,
     130,   131,   132,   188,   176,   619,   794,   795,    60,    61,
      21,    22,   203,   206,   199,   208,   804,   206,   176,   176,
     203,   175,   810,   811,   206,   813,   206,   815,  1238,   817,
     156,   165,   857,   175,   507,   508,   175,   825,   511,   165,
     513,   165,   515,   175,   517,   659,   660,   201,   175,   647,
     523,    21,    22,  1513,   184,   185,   186,   187,   188,   141,
     674,   203,   201,    62,    63,    64,   175,   540,   150,   199,
     200,   203,   124,   155,   201,   127,   128,   167,   150,   693,
     202,   133,   156,   165,   557,   558,  1214,     5,     6,   179,
     715,   165,   565,   165,   203,   175,   175,   166,   167,   175,
     182,   715,   101,   102,   103,   104,   175,   118,   119,   175,
     179,   175,   175,   574,   175,   126,   206,  1500,   129,   130,
     131,   132,   201,   203,   176,   177,   175,   203,   953,   181,
     107,   604,   184,  1079,   158,   201,   175,   206,   175,   203,
     203,   175,   203,  1172,  1275,   175,   619,  1621,   118,   119,
      21,    22,  1280,   165,   203,   150,   126,   209,   128,   129,
     130,   131,   132,  1291,   203,   187,   203,   781,   793,   203,
     165,   796,    57,   203,   175,   800,   649,   187,    63,   793,
     794,   795,   796,  1657,   165,   175,   800,   175,   199,   200,
     804,   175,   980,     0,   150,   169,   810,   811,   986,   813,
       7,   815,   203,   817,   818,   166,   167,   175,   175,   165,
     165,   825,  1000,   203,   175,   203,   186,   187,   188,   203,
    1694,   165,   183,    30,   175,    32,   167,    34,    12,   199,
     200,    47,   141,    40,   207,   203,   203,   166,   167,    23,
      24,   150,   715,    50,    33,   206,   175,   118,   119,    56,
     107,    67,   203,   156,   183,   126,   165,   128,   129,   130,
     131,   132,   165,   206,   207,   320,  1091,   182,   729,   182,
     731,    60,    61,    80,  1084,   330,   890,   206,   108,   109,
     110,   111,   112,   113,   114,   115,  1096,   202,   343,   202,
     156,  1101,   199,   166,   167,   102,   103,   178,   923,   165,
     181,   926,   175,   133,   166,  1433,   182,   932,   781,   923,
     183,   925,   926,   175,  1442,   145,   146,   147,   932,    33,
     793,   794,   795,   796,   785,   939,   202,   800,   199,   200,
      75,   804,   179,   206,    79,   124,   183,   810,   811,   128,
     813,   107,   815,    79,   817,   818,    60,    61,    93,    94,
     176,   182,   825,    98,    99,   100,   101,   182,    94,   165,
     167,   166,   167,    99,   179,   101,   980,   981,   183,    57,
     175,   202,   986,   165,   166,    63,  1586,   202,   183,   165,
     142,   188,   144,   175,  1194,  1267,  1000,  1267,   177,   166,
     167,  1201,   181,   200,   183,   184,   857,   175,   175,   206,
     178,   206,   165,   181,   165,    57,   183,   165,   166,    57,
     124,    63,  1540,  1541,   128,    63,   192,   175,  1546,   179,
     209,    57,  1550,   183,  1552,   175,   179,    63,   178,   206,
     183,   181,  1257,  1258,  1259,  1260,  1261,  1262,  1263,  1264,
    1265,  1266,  1267,  1268,  1269,  1270,  1271,  1272,  1273,  1274,
     923,  1049,   925,   926,   179,   178,   166,   167,   183,   932,
    1549,    34,    57,   177,  1592,   175,   939,   181,    63,   524,
     184,  1599,  1600,   183,   166,   167,    57,  1687,   939,  1607,
     941,   536,    63,   175,   169,   166,   167,   167,  1276,   179,
      63,   183,   953,   183,   175,   209,   206,   142,   143,   144,
     179,   962,   183,   964,   183,  1594,  1716,   980,   981,   169,
     170,   171,   179,   986,   206,  1140,   183,   142,   179,  1344,
    1345,  1346,   183,   578,   179,   206,  1140,  1000,   183,   166,
     167,  1151,   489,   490,   107,   492,   493,  1665,   175,   179,
     169,   170,   490,   183,   492,   493,   183,    21,    22,   165,
     605,   606,  1573,   140,   609,    57,   611,    66,  1368,   132,
     169,   170,   171,   172,   169,   170,   171,   166,   141,   206,
    1395,   178,   627,   628,   629,   630,   631,   632,   764,   765,
     766,    53,    54,    55,   106,  1046,   140,    33,    10,    11,
     165,  1189,   165,  1054,  1055,    33,  1623,  1245,  1246,   182,
     182,   202,   182,   182,   182,   202,  1067,    33,  1069,  1070,
    1071,  1072,  1073,   182,    60,    61,  1077,   672,   182,   192,
     182,   182,    60,    61,   182,  1223,   202,   179,   200,   202,
     166,    35,  1659,   207,    60,    61,   207,    35,   165,   694,
     165,   182,   116,   117,   118,   119,   120,   202,   207,   123,
     124,   125,   126,  1278,   128,   129,   130,   131,   132,   165,
     134,   135,  1276,   200,  1278,    22,   721,  1140,  1478,   201,
     165,   201,   138,   207,   178,   165,   202,   182,   124,   182,
     200,   127,   128,   182,   182,  1472,   124,   133,   182,   202,
     128,  1501,   202,   182,   182,   182,  1157,   165,   124,   206,
      43,   202,   128,   203,   183,   760,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   175,   202,   202,   202,   202,
     202,   167,   202,   778,   202,   199,   200,   203,   203,   784,
     176,   177,   203,   202,   201,   181,   201,   207,   184,   177,
     166,   167,   203,   181,   799,   183,   184,   202,   183,   175,
     202,   177,   182,   182,    33,   181,    13,   183,   184,   182,
     206,   182,   202,   209,  1389,   202,   202,   201,   823,   824,
     202,   209,   175,     4,   165,  1389,   203,   165,   178,   834,
     206,    60,    61,   209,   839,   201,   841,   165,   843,   165,
     165,  1616,   165,   848,   175,   203,   203,   203,   203,   182,
    1625,   203,   203,  1276,   203,  1278,   203,   203,   202,  1619,
     203,   203,  1437,   202,   182,   202,   202,   202,   202,   201,
     183,     1,   202,  1437,   183,   202,   176,   183,   202,  1427,
     201,  1456,    43,   203,  1622,   202,   176,   203,   202,    43,
      21,    22,  1456,  1398,   202,   124,   178,   202,   903,   128,
    1675,   203,   907,    43,   203,   203,   203,   203,   203,   203,
     165,   203,   203,   165,   203,  1326,   202,   202,  1329,   203,
     208,   202,   202,   165,   203,  1700,   158,    10,   933,    13,
       9,  1354,    42,    66,   182,    33,   202,   202,  1713,   201,
     165,   202,   201,   165,  1719,    33,   165,   165,   177,     8,
     208,   208,   181,   165,   183,   184,   203,   208,   963,   202,
     165,   165,    60,    61,   173,   203,  1389,   183,   165,   165,
     165,   202,    60,    61,   165,    14,   176,   176,   158,   202,
     209,   202,   987,   203,  1395,   116,   117,   118,   119,   120,
     178,   202,   123,   124,   125,   126,   202,   128,   129,   130,
     131,   132,   203,   134,   135,   203,   176,   138,    43,   203,
      37,   142,   143,   144,  1437,   208,   203,   148,   208,   176,
    1568,    67,    70,   202,  1572,   203,   124,  1032,   202,   202,
     128,   183,   203,  1456,  1039,    33,   124,  1042,   202,   202,
     128,   203,   202,  1048,   202,  1050,   177,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,  1622,   165,
     202,    43,    60,    61,   203,  1488,   165,   202,   199,   200,
     202,   165,  1620,    33,   203,   203,  1081,   203,  1083,   177,
    1085,   203,    33,   181,   202,   183,   184,   202,   202,   177,
    1095,   202,   169,   181,   202,   183,   184,   206,  1103,   203,
      60,    61,   165,   203,    33,   208,  1517,   203,   203,    60,
      61,   209,   203,   203,   203,   207,   203,   203,   203,    12,
     175,   209,  1127,  1534,   206,   203,   124,   203,  1676,   203,
     128,   175,  1137,   203,  1682,   203,   203,  1142,   203,  1144,
    1688,   203,   203,   203,   202,    53,    78,   201,  1153,   206,
     206,  1156,   203,   203,   203,   207,   201,     1,   187,   633,
     202,   208,    81,   203,   124,   208,  1714,   208,   128,   207,
    1175,   208,  1723,   124,  1721,   731,   209,   128,   731,   177,
    1246,   649,   653,   181,   957,   183,   184,     1,   715,  1590,
    1383,  1536,  1197,  1539,  1459,  1591,  1591,    52,  1145,  1622,
    1205,  1206,  1207,   956,   956,   432,  1617,   304,    33,   227,
     605,   209,    -1,    -1,  1625,    21,    22,   177,   432,  1224,
      -1,   181,  1227,   183,   184,    -1,   177,    -1,    -1,   432,
     181,  1236,   183,   184,    -1,    60,    61,   108,   109,   110,
     111,   112,   113,   114,   115,    -1,   432,   432,   432,   209,
      -1,  1662,    -1,    -1,    -1,    -1,   127,    -1,   209,    -1,
      -1,    -1,   133,    -1,    -1,    -1,    -1,    -1,  1679,    -1,
      -1,    -1,    -1,    -1,   145,   146,   147,    -1,    -1,    -1,
      -1,  1286,  1693,  1288,  1695,    -1,    -1,    -1,    -1,  1700,
    1295,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   124,
      -1,    -1,    -1,   128,    -1,   176,  1717,    -1,  1719,    -1,
     116,   117,   118,   119,   120,    -1,    -1,   123,   124,   125,
     126,    -1,   128,   129,   130,   131,   132,    -1,   134,   135,
    1335,    -1,   138,    -1,    -1,    33,   142,   143,   144,    -1,
      -1,    -1,   148,    -1,    -1,    -1,    -1,  1352,    -1,    -1,
      -1,    -1,   177,    -1,    21,    22,   181,    -1,   183,   184,
      -1,    -1,    60,    61,  1369,  1370,    -1,    -1,    -1,    -1,
      -1,   177,    -1,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,    -1,   209,  1390,    -1,    -1,    -1,    -1,
      -1,  1396,  1397,   199,   200,    -1,    -1,  1402,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   124,    -1,  1433,    -1,
     128,    -1,    -1,    -1,    -1,    -1,    -1,  1442,    -1,    -1,
      -1,    -1,  1447,    -1,    -1,  1450,    -1,  1452,    -1,   116,
     117,   118,   119,   120,    -1,    -1,   123,   124,   125,   126,
      10,   128,   129,   130,   131,   132,    -1,   134,   135,  1474,
      -1,    21,    22,    -1,    -1,   142,   143,   144,    -1,   177,
      -1,    -1,    -1,   181,    -1,   183,   184,    -1,    -1,  1494,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,  1514,
     177,   209,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   199,   200,    -1,    60,    61,    -1,  1543,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1556,    -1,    -1,    -1,    -1,  1561,  1562,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,    -1,
      -1,    -1,   142,   143,   144,   145,   146,   147,   148,   124,
      -1,    -1,    -1,   128,    -1,    -1,  1611,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   176,   177,    -1,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,    -1,
      -1,    -1,  1647,    -1,    -1,    -1,    -1,    -1,    -1,   199,
     200,    -1,   177,    -1,    -1,  1660,   181,    -1,   183,   184,
      -1,    -1,     1,    -1,  1669,    -1,     5,     6,     7,    -1,
       9,    10,    11,  1678,    13,    -1,    15,    16,    17,    18,
      19,    -1,    -1,    -1,   209,    -1,    25,    26,    27,    28,
      29,    -1,    31,    -1,    -1,    -1,    -1,  1702,    -1,    38,
      39,    40,    -1,    42,    -1,    44,    45,    -1,    -1,    48,
      -1,    50,    51,    52,    -1,    54,    55,    -1,    -1,    58,
      59,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,
      69,    -1,    71,    72,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    93,    94,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
     119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     139,    -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,   150,   151,   152,   153,    -1,   155,    -1,   157,   158,
     159,   160,   161,   162,   163,   164,   165,    -1,   167,   168,
      -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   184,   185,   186,    -1,   188,
      -1,    -1,   191,   192,    -1,    -1,    -1,    -1,    60,    61,
      -1,   200,    -1,   202,    -1,   204,   205,   206,   207,   208,
       1,    -1,    -1,    -1,     5,     6,     7,    -1,     9,    10,
      11,    -1,    13,    -1,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    25,    26,    27,    28,    29,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      -1,    42,    -1,    44,    45,    -1,    -1,    48,    -1,    50,
      51,    52,   124,    54,    55,    -1,   128,    58,    59,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,    -1,
      71,    72,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,    93,    94,    95,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,   177,    -1,    -1,    -1,   181,
      -1,   183,   184,    -1,    -1,    -1,    -1,   118,   119,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   209,   139,    -1,
     141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,
     151,   152,   153,    -1,   155,    -1,   157,   158,   159,   160,
     161,   162,   163,   164,   165,    -1,   167,   168,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   184,   185,   186,    -1,   188,    -1,    -1,
     191,   192,    -1,    -1,    -1,    -1,    60,    61,    -1,   200,
      -1,   202,    -1,   204,   205,   206,   207,   208,     1,    -1,
      -1,    -1,     5,     6,     7,    -1,     9,    10,    11,    -1,
      13,    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    25,    26,    27,    28,    29,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    -1,    42,
      -1,    44,    45,    -1,    -1,    48,    -1,    50,    51,    52,
     124,    54,    55,    -1,   128,    58,    59,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    68,    69,    -1,    71,    72,
      73,    -1,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    -1,
      93,    94,    95,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,   177,    -1,    -1,    -1,   181,    -1,   183,
     184,    -1,    -1,    -1,    -1,   118,   119,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   209,   139,    -1,   141,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   149,   150,   151,   152,
     153,    -1,   155,    -1,   157,   158,   159,   160,   161,   162,
     163,   164,   165,    -1,   167,   168,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   184,   185,   186,    -1,   188,    -1,    -1,   191,   192,
      -1,    -1,    -1,    -1,    60,    61,    -1,   200,    -1,   202,
      -1,   204,   205,   206,   207,   208,     1,    -1,    -1,    -1,
       5,     6,     7,    -1,     9,    10,    11,    -1,    13,    -1,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    26,    27,    28,    29,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    -1,    42,    -1,    44,
      45,    -1,    -1,    48,    -1,    50,    51,    52,   124,    54,
      55,    -1,   128,    58,    59,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
     105,   177,    -1,    -1,    -1,   181,    -1,   183,   184,    -1,
      -1,    -1,    -1,   118,   119,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   209,   139,    -1,   141,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,   150,   151,   152,   153,    -1,
     155,    -1,   157,   158,   159,   160,   161,   162,   163,   164,
     165,    -1,   167,   168,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,
     185,   186,    -1,   188,    -1,    -1,   191,   192,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   200,    -1,   202,    -1,   204,
     205,   206,   207,   208,     1,    -1,    -1,    -1,     5,     6,
       7,    -1,     9,    10,    11,    -1,    13,    -1,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,    26,
      27,    28,    29,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    -1,    42,    -1,    44,    45,    -1,
      -1,    48,    -1,    50,    51,    52,    -1,    54,    55,    -1,
      -1,    58,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    68,    69,    -1,    71,    72,    73,    -1,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    -1,    93,    94,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   139,    -1,   141,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   149,   150,   151,   152,   153,    -1,   155,    -1,
     157,   158,   159,   160,   161,   162,   163,   164,   165,    -1,
     167,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,   185,   186,
      -1,   188,    -1,    -1,   191,   192,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   200,    -1,   202,    -1,   204,   205,   206,
     207,   208,     1,    -1,    -1,    -1,     5,     6,     7,    -1,
       9,    10,    11,    -1,    13,    -1,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    25,    26,    27,    28,
      29,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    -1,    42,    -1,    44,    45,    -1,    -1,    48,
      -1,    50,    51,    52,    -1,    54,    55,    -1,    -1,    58,
      59,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,
      69,    -1,    71,    72,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    93,    94,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
     119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     139,    -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,   150,   151,   152,   153,    -1,   155,    -1,   157,   158,
     159,   160,   161,   162,   163,   164,   165,    -1,   167,   168,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   184,   185,   186,    -1,   188,
      -1,    -1,   191,   192,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   200,    -1,   202,    -1,   204,   205,   206,   207,   208,
       5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    68,    69,    70,    71,    72,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   118,   119,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   139,    -1,   141,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,   150,   151,   152,   153,    -1,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,
     185,   186,    -1,   188,    -1,    -1,   191,   192,    -1,    -1,
      -1,    -1,    -1,     5,     6,   200,    -1,   202,   203,   204,
     205,    13,   207,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    49,    -1,    51,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    68,    69,    -1,    71,
      72,    73,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      -1,    93,    94,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   118,   119,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,   141,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,   151,
     152,   153,    -1,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,    -1,    -1,   168,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   184,   185,   186,    -1,   188,    -1,    -1,   191,
     192,    -1,    -1,    -1,    -1,    -1,     5,     6,   200,    -1,
     202,    -1,   204,   205,    13,   207,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      49,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,
      69,    -1,    71,    72,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    93,    94,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
     119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     139,    -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,   150,   151,   152,   153,    -1,   155,    -1,   157,   158,
     159,   160,   161,   162,   163,   164,   165,    -1,    -1,   168,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   184,   185,   186,    -1,   188,
      -1,    -1,   191,   192,    -1,    -1,    -1,    -1,    -1,     5,
       6,   200,    -1,   202,    -1,   204,   205,    -1,   207,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,
      -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    48,    -1,    -1,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    68,    69,    70,    71,    72,    73,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    -1,    93,    94,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   139,    -1,   141,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   149,   150,   151,   152,   153,    -1,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
      -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,   185,
     186,    -1,   188,    -1,    -1,   191,   192,    -1,    -1,    -1,
      -1,    -1,     5,     6,   200,    -1,   202,    -1,   204,   205,
      -1,   207,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    48,    -1,    -1,    51,    -1,
      -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    68,    69,    -1,    71,    72,
      73,    -1,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    -1,
      93,    94,    95,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   118,   119,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,   141,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   149,   150,   151,   152,
     153,    -1,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,    -1,    -1,   168,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   184,   185,   186,    -1,   188,    -1,    -1,   191,   192,
      -1,    -1,    -1,    -1,    -1,     5,     6,   200,    -1,   202,
     203,   204,   205,    -1,   207,    15,    16,    17,    18,    19,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,
      -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,
      -1,    71,    72,    73,    -1,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,   119,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,
      -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,
     150,   151,   152,   153,    -1,   155,   156,   157,   158,   159,
     160,   161,   162,   163,   164,   165,    -1,    -1,   168,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   184,   185,   186,    -1,   188,    -1,
      -1,   191,   192,    -1,    -1,    -1,    -1,    -1,     5,     6,
     200,    -1,   202,   203,   204,   205,    -1,   207,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    48,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    68,    69,    -1,    71,    72,    73,    -1,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    -1,    93,    94,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   139,    -1,   141,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   149,   150,   151,   152,   153,    -1,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,    -1,
      -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,   185,   186,
      -1,   188,    -1,    -1,   191,   192,    -1,    -1,    -1,    -1,
      -1,     5,     6,   200,    -1,   202,    -1,   204,   205,    -1,
     207,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    68,    69,    -1,    71,    72,    73,
      -1,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    -1,    93,
      94,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   118,   119,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   139,    -1,   141,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   149,   150,   151,   152,   153,
      -1,   155,    -1,   157,   158,   159,   160,   161,   162,   163,
     164,   165,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     184,   185,   186,    -1,   188,    -1,    -1,   191,   192,    -1,
      -1,    -1,    -1,    -1,     5,     6,   200,    -1,   202,   203,
     204,   205,    -1,   207,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    -1,
      51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,    -1,
      71,    72,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,    93,    94,    95,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,   119,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   127,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,
     141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,
     151,   152,   153,    -1,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,    -1,    -1,   168,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   184,   185,   186,    -1,   188,    -1,    -1,
     191,   192,    -1,    -1,    -1,    -1,    -1,     5,     6,   200,
      -1,   202,    -1,   204,   205,    -1,   207,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      68,    69,    -1,    71,    72,    73,    -1,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    -1,    93,    94,    95,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     118,   119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   139,    -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   149,   150,   151,   152,   153,    -1,   155,    -1,   157,
     158,   159,   160,   161,   162,   163,   164,   165,    -1,    -1,
     168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   184,   185,   186,    -1,
     188,    -1,    -1,   191,   192,    -1,    -1,    -1,    -1,    -1,
       5,     6,   200,    -1,   202,   203,   204,   205,    -1,   207,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   118,   119,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   139,    -1,   141,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,   150,   151,   152,   153,    -1,
     155,    -1,   157,   158,   159,   160,   161,   162,   163,   164,
     165,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,
     185,   186,    -1,   188,    -1,    -1,   191,   192,    -1,    -1,
      -1,    -1,    -1,     5,     6,   200,    -1,   202,   203,   204,
     205,    -1,   207,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    -1,    51,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    68,    69,    -1,    71,
      72,    73,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      -1,    93,    94,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   118,   119,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,   141,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,   151,
     152,   153,    -1,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,    -1,    -1,   168,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   184,   185,   186,    -1,   188,    -1,    -1,   191,
     192,    -1,    -1,    -1,    -1,    -1,     5,     6,   200,    -1,
     202,    -1,   204,   205,    -1,   207,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,
      69,    -1,    71,    72,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    93,    94,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
     119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     139,    -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,   150,   151,   152,   153,    -1,   155,    -1,   157,   158,
     159,   160,   161,   162,   163,   164,   165,    -1,    -1,   168,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   184,   185,   186,    -1,   188,
      -1,    -1,   191,   192,    -1,    -1,    -1,    -1,    -1,     5,
       6,   200,    -1,   202,    -1,   204,   205,    -1,   207,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,
      -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    48,    -1,    -1,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    -1,    93,    94,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   139,    -1,   141,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   149,   150,   151,   152,   153,    -1,   155,
      -1,   157,   158,   159,   160,   161,   162,   163,   164,   165,
      -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,   185,
     186,    -1,   188,    -1,    -1,   191,   192,    -1,    -1,    -1,
      -1,    -1,     5,     6,   200,   201,   202,    -1,   204,   205,
      -1,   207,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    48,    -1,    -1,    51,    -1,
      -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    68,    69,    -1,    71,    72,
      73,    -1,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    -1,
      93,    94,    95,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   118,   119,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,   141,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   149,   150,   151,   152,
     153,    -1,   155,    -1,   157,   158,   159,   160,   161,   162,
     163,   164,   165,    -1,    -1,   168,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   184,   185,   186,    -1,   188,    -1,    -1,   191,   192,
      -1,    -1,    -1,    -1,    -1,     5,     6,   200,   201,   202,
      -1,   204,   205,    -1,   207,    15,    16,    17,    18,    19,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,
      -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,
      -1,    71,    72,    73,    -1,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,   119,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,
      -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,
     150,   151,   152,   153,    -1,   155,    -1,   157,   158,   159,
     160,   161,   162,   163,   164,   165,    -1,    -1,   168,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   184,   185,   186,    -1,   188,    -1,
      -1,   191,   192,    -1,    -1,    -1,    -1,    -1,     5,     6,
     200,    -1,   202,    -1,   204,   205,    13,   207,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    48,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    68,    69,    -1,    71,    72,    73,    -1,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    -1,    93,    94,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   139,    -1,   141,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   149,   150,   151,   152,   153,    -1,   155,    -1,
     157,   158,   159,   160,   161,   162,   163,   164,   165,    -1,
      -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,   185,   186,
      -1,   188,    -1,    -1,   191,   192,    -1,    -1,    -1,    -1,
      -1,     5,     6,   200,    -1,   202,    -1,   204,   205,    -1,
     207,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    68,    69,    -1,    71,    72,    73,
      -1,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    -1,    93,
      94,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   118,   119,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   139,    -1,   141,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   149,   150,   151,   152,   153,
      -1,   155,    -1,   157,   158,   159,   160,   161,   162,   163,
     164,   165,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     184,   185,   186,    -1,   188,    -1,    -1,   191,   192,    -1,
      -1,    -1,    -1,    -1,     5,     6,   200,    -1,   202,    -1,
     204,   205,    -1,   207,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    -1,
      51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      61,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,    -1,
      71,    72,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,    93,    94,    95,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,   119,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,
     141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,
     151,   152,   153,    -1,   155,    -1,   157,   158,   159,   160,
     161,   162,   163,   164,   165,    -1,    -1,   168,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   184,   185,   186,    -1,   188,    -1,    -1,
     191,   192,    -1,    -1,    -1,    -1,    -1,     5,     6,   200,
      -1,   202,    -1,   204,   205,    -1,   207,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      68,    69,    -1,    71,    72,    73,    -1,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    -1,    93,    94,    95,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     118,   119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   139,    -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   149,   150,   151,   152,   153,    -1,   155,    -1,   157,
     158,   159,   160,   161,   162,   163,   164,   165,    -1,    -1,
     168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   184,   185,   186,    -1,
     188,    -1,    -1,   191,   192,    -1,    -1,    -1,    -1,    -1,
       5,     6,   200,    -1,   202,    -1,   204,   205,    -1,   207,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   118,   119,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   139,    -1,   141,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,   150,   151,   152,   153,    -1,
     155,    -1,   157,   158,   159,   160,   161,   162,   163,   164,
     165,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,
     185,   186,    -1,   188,    -1,    -1,   191,   192,    -1,    -1,
      -1,    -1,    -1,     5,     6,   200,    -1,   202,    -1,   204,
     205,    -1,   207,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    -1,    51,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    68,    69,    -1,    71,
      72,    73,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      -1,    93,    94,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   118,   119,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,   141,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,   151,
     152,   153,    -1,   155,    -1,   157,   158,   159,   160,   161,
     162,   163,   164,   165,    -1,    -1,   168,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   184,   185,   186,    -1,   188,    -1,    -1,   191,
     192,    -1,    -1,    -1,    -1,    -1,     5,     6,   200,    -1,
     202,   203,   204,   205,    -1,   207,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,
      69,    -1,    71,    72,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    93,    94,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
     119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     139,    -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,   150,   151,   152,   153,    -1,   155,    -1,   157,   158,
     159,   160,   161,   162,   163,   164,   165,    -1,    -1,   168,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   184,   185,   186,    -1,   188,
      -1,    -1,   191,   192,    -1,    -1,    -1,    -1,    -1,     5,
       6,   200,    -1,   202,    -1,   204,   205,    -1,   207,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,
      26,    27,    28,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    48,    -1,    -1,    51,    52,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    -1,    93,    94,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   139,    -1,   141,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   149,   150,   151,   152,   153,    -1,   155,
      -1,   157,   158,   159,   160,   161,   162,   163,   164,   165,
      -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,   185,
     186,    -1,   188,    -1,    -1,   191,   192,    -1,    -1,    -1,
       5,     6,    -1,    -1,   200,    -1,   202,    -1,   204,   205,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   118,   119,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   139,    -1,   141,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   149,   150,   151,   152,   153,    -1,
     155,    -1,   157,   158,   159,   160,   161,   162,   163,   164,
     165,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,
     185,   186,    -1,   188,    -1,    -1,   191,   192,    -1,    -1,
      -1,     5,     6,    -1,    -1,   200,    -1,   202,    -1,   204,
     205,    15,    16,    17,    18,    19,    -1,    -1,    22,    -1,
      -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,
      -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    68,    69,    -1,    71,    72,    73,
      -1,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    -1,    93,
      94,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   118,   119,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   139,    -1,   141,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   149,   150,   151,   152,   153,
      -1,   155,    -1,   157,   158,   159,   160,   161,   162,   163,
     164,   165,    -1,    -1,   168,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     184,   185,   186,    -1,   188,    -1,    -1,   191,   192,    -1,
      -1,    -1,     5,     6,    -1,    -1,   200,    -1,   202,    -1,
     204,   205,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    48,    -1,    -1,    51,    -1,
      -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    68,    69,    -1,    71,    72,
      73,    -1,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    -1,
      93,    94,    95,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   118,   119,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,   141,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   149,   150,   151,   152,
     153,    -1,   155,    -1,   157,   158,   159,   160,   161,   162,
     163,   164,   165,    -1,    19,   168,    -1,    -1,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,   184,   185,   186,    -1,   188,    41,    -1,   191,   192,
      -1,    -1,    -1,    -1,    49,    -1,    -1,   200,    -1,   202,
      -1,   204,   205,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    -1,    -1,    -1,    -1,   141,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   154,
      -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,
     165,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,    -1,    -1,    -1,    -1,    -1,   204,
      -1,    -1,    -1,    -1,   209,    -1,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,
      -1,   141,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   154,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    -1,    -1,    -1,   165,    -1,   167,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    -1,    -1,    -1,   204,    -1,   206,    -1,    -1,    -1,
      -1,    19,    -1,    -1,    -1,    21,    22,    25,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    41,    -1,    -1,    -1,    -1,   141,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   154,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    -1,   165,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,   204,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
      21,    22,   128,   129,   130,    -1,    -1,   133,   134,   135,
     136,   137,    -1,   141,    -1,    -1,   142,   143,   144,   145,
     146,   147,   148,    -1,    -1,    -1,   154,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    22,    -1,   165,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   177,    -1,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,    -1,    -1,   191,   192,    -1,    -1,    -1,
      -1,    -1,    -1,   199,   200,    -1,   204,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   116,   117,   118,   119,   120,
      -1,    -1,   123,   124,   125,   126,    -1,   128,   129,   130,
     131,   132,    -1,   134,   135,    -1,    -1,   138,    -1,    21,
      22,   142,   143,   144,    -1,    -1,    -1,   148,    -1,   116,
     117,   118,   119,   120,    -1,    -1,   123,   124,   125,   126,
      -1,   128,   129,   130,   131,   132,    -1,   134,   135,    21,
      22,    -1,    -1,    -1,    -1,   142,   177,   144,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   199,   200,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   199,   200,   116,   117,   118,   119,   120,    -1,
      -1,   123,   124,   125,   126,    -1,   128,   129,   130,   131,
     132,    -1,   134,   135,    21,    22,    -1,    -1,    -1,    -1,
     142,    -1,    -1,    -1,   116,   117,   118,   119,   120,    -1,
      -1,   123,   124,   125,   126,    -1,   128,   129,   130,   131,
     132,    -1,   134,   135,    21,    22,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   199,   200,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   199,   200,   116,
     117,   118,   119,   120,    -1,    -1,   123,   124,   125,   126,
      -1,   128,   129,   130,   131,   132,    -1,   134,   135,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   116,
     117,   118,   119,   120,    -1,    -1,   123,   124,   125,   126,
      -1,   128,   129,   130,   131,   132,    -1,   134,   135,    21,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   181,   182,   183,   184,   185,   186,
     187,   188,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   199,   200,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   182,   183,   184,   185,   186,
     187,   188,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   199,   200,   116,   117,   118,   119,   120,    -1,
      -1,   123,    -1,    -1,   126,    -1,   128,   129,   130,   131,
     132,    -1,   134,   135,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   116,   117,   118,   119,    -1,    -1,
      -1,    -1,    -1,    -1,   126,    -1,   128,   129,   130,   131,
     132,    -1,   134,   135,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,
     182,   183,   184,   185,   186,   187,   188,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   199,   200,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,
      -1,    -1,   184,   185,   186,   187,   188,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   199,   200,    71,
      72,    73,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      -1,    93,    94,    95,    -1,    -1,    98,    99,   100,   101,
      71,    72,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,    93,    94,    95,    -1,    -1,    98,    99,   100,
     101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    19,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   156,    -1,    -1,    -1,    -1,    -1,
      71,    -1,    73,   165,    75,    76,    77,    78,    79,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,    93,    94,    95,   156,    35,    98,    99,   100,
     101,    71,    72,    73,   165,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    -1,    98,    99,
     100,   101,    71,    -1,    73,    -1,    75,    76,    77,    78,
      79,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    93,    94,    95,    -1,    -1,    98,
      99,   100,   101,    -1,   165,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
     119,    -1,    -1,    -1,    -1,    -1,   156,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,   165,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    93,    94,    95,    -1,    -1,    98,
      99,   100,   101,    -1,    -1,    71,   165,    73,    -1,    75,
      76,    77,    78,    79,    -1,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    -1,    93,    94,    95,
     129,   130,    98,    99,   100,   101,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   156,    -1,    -1,
      -1,    -1,    -1,    71,    -1,    73,   165,    75,    76,    77,
      78,    79,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    -1,    93,    94,    95,    -1,    -1,
      98,    99,   100,   101,    -1,    -1,    -1,    -1,    -1,   165,
     199,   200,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   165
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   211,     0,     7,    30,    32,    34,    40,    50,    56,
      80,   102,   103,   167,   188,   200,   206,   213,   214,   218,
     227,   229,   230,   235,   284,   290,   321,   403,   411,   418,
     428,   478,   483,   488,    19,    20,   165,   274,   275,   276,
     158,   236,   237,   177,   232,   233,    57,    63,   408,   409,
     165,   204,   216,   489,   479,   484,   141,   165,   309,    34,
      63,   107,   132,   192,   202,   279,   280,   281,   282,   309,
     213,   213,   213,     8,    36,   429,    62,   399,   176,   175,
     178,   175,   148,   165,   188,   199,   231,   231,   165,   213,
     399,   408,   408,   408,   165,   141,   228,   281,   281,   281,
     202,   142,   143,   144,   175,   201,   107,   289,   419,     5,
       6,   425,    57,    63,   400,    15,    16,   139,   158,   163,
     165,   168,   202,   220,   275,   158,   237,   187,   187,   231,
     187,   187,   199,    22,    57,   234,   410,    57,    63,   215,
     165,   165,   165,   165,   169,   226,   203,   276,   281,   281,
     281,   281,   167,   241,   242,    57,    63,   291,   293,    57,
      63,   412,   107,   107,    57,    63,   426,   207,   404,   165,
     169,   170,   171,   219,    15,    16,   158,   163,   165,   220,
     272,   273,   231,   231,   231,   165,   165,   165,   176,   192,
     217,   178,   439,   242,   242,   169,   203,   167,   294,   165,
     413,   430,   401,   140,   277,   369,   169,   170,   171,   175,
     203,   234,    19,    25,    31,    41,    49,    64,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   154,   204,   309,   433,   435,   436,   440,   446,   448,
     477,    66,    79,    94,    99,   101,   166,   416,   417,   480,
     485,    35,    71,    73,    75,    76,    77,    78,    79,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      93,    94,    95,    98,    99,   100,   101,   118,   119,   165,
     287,   288,   292,   178,   414,   106,   423,   424,   208,   213,
     402,   275,   140,   165,   395,   398,   272,   182,   182,   182,
     202,   182,   182,   202,   439,   182,   182,   182,   182,   182,
     202,   309,   182,   202,    33,    60,    61,   124,   128,   177,
     181,   184,   209,   200,   445,   179,   166,   490,   207,   207,
      21,    22,    38,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   128,   129,   130,   133,   134,   135,   136,   137,   142,
     143,   144,   145,   146,   147,   148,   177,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   191,   192,   199,
     200,    35,    35,   202,   285,   242,    75,    79,    93,    94,
      98,    99,   100,   101,   434,   417,   165,   242,   369,   242,
     275,   175,   178,   181,   393,   449,   455,   457,     5,     6,
      15,    16,    17,    18,    19,    25,    27,    31,    39,    45,
      48,    51,    55,    65,    68,    69,    80,   102,   103,   104,
     118,   119,   139,   149,   150,   151,   152,   153,   155,   157,
     158,   159,   160,   161,   162,   163,   164,   168,   184,   185,
     186,   191,   192,   200,   202,   204,   205,   207,   225,   227,
     301,   309,   314,   326,   333,   336,   339,   343,   345,   347,
     348,   350,   355,   358,   359,   360,   367,   368,   433,   494,
     502,   513,   516,   529,   530,   533,   534,   459,   453,   165,
     182,   461,   463,   465,   467,   469,   471,   473,   475,   359,
     182,   202,   447,   451,   127,   306,   337,   359,    33,   181,
      33,   181,   200,   209,   201,   359,   200,   209,   446,   207,
     481,   486,   165,   288,   165,   288,   165,   201,    22,   165,
     201,   153,   203,   369,   379,   380,   381,   126,   178,   286,
     138,   298,   299,   338,   207,   178,   422,   431,   150,   165,
     394,   397,   242,   165,   446,   127,   133,   176,   392,   477,
     477,   444,   477,   182,   182,   182,   309,   311,   435,   493,
     502,   513,   516,   529,   530,   533,   534,   309,   182,     5,
     102,   103,   182,   202,   182,   202,   202,   182,   182,   202,
     182,   202,   182,   202,   182,   182,   202,    19,   182,   182,
     360,   360,   150,   155,   182,   309,   349,   202,   202,   202,
     202,   202,   202,   224,   360,   360,   360,   360,   360,    13,
      49,   306,   156,   165,   337,   495,   497,   528,   202,   200,
     283,   139,   207,   339,   344,   344,   344,   344,   203,    21,
      22,   116,   117,   118,   119,   120,   123,   124,   125,   126,
     128,   129,   130,   131,   132,   134,   135,   138,   142,   143,
     144,   148,   177,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   199,   200,   202,   477,   477,   203,   183,
     441,   477,   285,   477,   285,   477,   285,   165,   382,   383,
     477,   165,   385,   386,   203,   452,   337,   308,   477,   359,
     203,   175,   532,   201,   201,   201,   359,   491,   382,   384,
     385,   387,   165,   288,   108,   109,   110,   111,   112,   113,
     114,   115,   133,   145,   146,   147,   108,   109,   110,   111,
     112,   113,   114,   115,   127,   133,   145,   146,   147,   176,
     202,     7,    50,   320,   206,   175,   206,   203,   477,   477,
     127,   360,   207,   420,   309,   206,   207,   427,   202,    43,
     175,   178,   393,   213,   392,   359,   183,   183,   183,   166,
     175,   212,   213,   443,   503,   505,   312,   202,   182,   202,
     334,   182,   182,   182,   523,   337,   446,   359,   527,   359,
     327,   329,   359,   331,   359,   525,   337,   511,   514,   337,
     182,   507,   446,   202,   202,   351,   353,   359,   359,   359,
     359,   359,   359,   171,   172,   219,   202,    13,   201,   202,
     127,   133,   176,   388,   532,   175,   532,   203,   242,    70,
     200,   203,   337,   497,   282,     4,   342,   305,   283,    19,
     156,   165,   433,    19,   156,   165,   433,   360,   360,   360,
     360,   360,   360,   165,   360,   156,   165,   359,   360,   360,
     433,   360,   360,   360,   529,   534,   360,   360,   360,   360,
      22,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   360,   129,   130,   156,   165,   199,   200,   356,   433,
     359,   203,   337,   183,   183,   165,   437,   183,   286,   183,
     286,   183,   286,   178,   183,   443,   178,   183,   443,   308,
     532,   183,   443,   127,   359,   201,   165,   438,   213,   249,
     250,   249,   250,   359,   150,   165,   389,   390,   432,   381,
     381,   381,   360,   305,   165,   405,   407,   375,   359,   165,
     150,   165,   446,   392,   359,   213,   450,   456,   458,   477,
     446,   446,   477,    70,   337,   497,   501,   165,   359,   477,
     517,   519,   521,   446,   532,   183,   443,   175,   532,   203,
     446,   446,   203,   446,   203,   446,   532,   446,   383,   532,
     509,   386,   183,   359,   359,   446,   285,   203,   203,   203,
     203,   203,   203,   359,   150,   165,   202,   263,   202,   359,
     359,   359,   203,   156,   165,    13,   307,   527,   165,   203,
     497,   495,   175,   203,   203,   201,   202,   285,     1,    26,
      28,    29,    38,    40,    44,    52,    54,    58,    59,    65,
     105,   207,   208,   213,   238,   239,   248,   259,   260,   262,
     264,   265,   266,   267,   268,   269,   270,   271,   302,   310,
     315,   316,   317,   318,   319,   321,   325,   346,   360,   342,
     182,   202,   182,   202,   202,   202,   201,    19,   156,   165,
     433,   178,   156,   165,   359,   202,   202,   156,   165,   359,
       1,   202,   201,   175,   203,   460,   454,   175,   183,   206,
     462,   183,   466,   183,   470,   183,   477,   474,   382,   477,
     476,   385,   183,   203,   447,   477,   359,   176,   212,   406,
     415,   213,   382,   482,   385,   487,   203,   202,    43,   175,
     178,   181,   388,   300,   176,   406,   415,    40,   167,   208,
     284,   376,   203,   202,    43,   213,   392,   359,   213,   183,
     183,   183,   497,   203,   203,   203,   183,   443,   203,   183,
     446,   383,   386,   183,   203,   202,   446,   359,   203,   183,
     183,   183,   183,   203,   183,   183,   203,   446,   183,   342,
     203,   203,   183,   286,   202,   178,   222,   202,    43,   165,
     323,    20,   175,   263,   203,   202,   133,   388,   202,   208,
     532,   203,   175,   201,   200,   495,   127,   133,   165,   176,
     181,   340,   341,   286,   127,   359,   298,    61,   359,   165,
     165,   213,   158,    58,   359,   242,   127,   359,   303,   213,
     213,    10,    10,    11,   246,    13,     9,    42,   213,   213,
     213,   213,   213,   213,    66,   322,   213,   108,   109,   110,
     111,   112,   113,   114,   115,   121,   122,   127,   133,   136,
     137,   145,   146,   147,   176,   285,   361,   359,   363,   359,
     200,   203,   337,   495,   359,   182,   202,   360,   202,   201,
     359,   200,   203,   337,   495,   202,   201,   357,   203,   337,
     165,   442,   165,   464,   468,   472,   447,   359,   165,   212,
     492,   208,   208,   359,   165,   150,   165,   477,   359,   208,
     359,   405,   421,   165,     8,   369,   374,   359,   165,   359,
     213,   504,   506,   313,   203,   202,   165,   335,   183,   183,
     183,   524,   307,   183,   328,   330,   332,   526,   512,   515,
     183,   508,   202,   242,   352,   183,   203,   337,   223,   173,
     359,   165,   175,   203,   337,   150,   165,   202,    20,   133,
     388,   359,   359,   359,   263,   203,   495,   203,   165,   165,
     202,   165,   165,   175,   203,   242,   359,    14,   359,   176,
     176,   178,   158,   298,   359,   305,   202,   202,   200,   277,
     278,   278,   202,   202,   207,   324,   397,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   529,   534,
     360,   360,   360,   360,   360,   360,   360,   286,   446,   203,
     477,   203,   495,   175,   203,   203,   203,   365,   359,   359,
     203,   495,   175,   203,   203,   359,   203,   176,   208,   203,
     202,    43,   388,    37,   295,   208,   176,    57,    63,   372,
      67,   373,   213,   203,   213,   202,   202,   359,   183,   518,
     520,   522,   202,   203,   202,   360,   360,   360,   202,    70,
     501,   202,   510,   202,   203,   359,   298,   349,   354,   203,
     221,   203,   165,   203,   202,    43,   323,   337,   359,   359,
     203,    20,   201,   165,   340,   338,   298,   477,   359,   304,
     359,   359,   276,   202,   202,   359,   323,   396,   242,   183,
     183,   201,   495,   477,   203,   203,   201,   495,   203,   359,
     359,   165,   359,   296,   477,    47,   373,    46,   106,   370,
     501,   501,   203,   202,   202,   202,   202,   306,   307,   337,
     501,   202,   501,   203,   349,   169,   206,   359,   165,   203,
     203,   133,   388,   337,   203,   203,   208,   203,   203,   201,
     263,   359,   203,   203,   208,   213,   397,   338,   362,   364,
     203,   203,   183,   203,   203,   203,   207,   213,    33,   371,
     370,   372,   202,   495,   498,   499,   500,   500,   359,   501,
     501,   495,   496,   203,   203,   532,   500,   501,   496,   359,
     203,   206,   359,   359,   203,   295,    12,   247,   242,    20,
     203,   242,   178,   393,   366,   305,   377,   371,   389,   390,
     391,   495,   175,   532,   203,   203,   203,   500,   500,   203,
     203,   203,   496,   203,   206,   531,   359,   206,   248,   315,
     316,   317,   318,   360,   213,   261,   337,   242,   298,   446,
     392,   297,   292,   378,   203,   202,   203,   203,   203,    53,
     201,   531,   359,   207,   251,   254,   203,   298,   392,   359,
     208,   213,   292,   495,   359,   201,   531,   252,    12,    23,
      24,   240,   243,   248,   242,   359,   213,   242,   203,   208,
     305,   242,   202,   213,   298,   213,   338,   253,   244,   359,
     208,   207,   255,   258,   203,   295,   256,   248,   242,   305,
     213,   245,   257,   255,   208,   243,   295
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   210,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   212,   212,   213,
     213,   214,   215,   215,   215,   216,   216,   217,   217,   218,
     219,   219,   219,   219,   220,   220,   221,   221,   222,   223,
     222,   224,   224,   224,   225,   226,   226,   228,   227,   229,
     230,   231,   231,   231,   231,   231,   231,   231,   232,   232,
     233,   233,   234,   234,   235,   236,   236,   237,   237,   238,
     239,   239,   240,   240,   241,   241,   242,   242,   243,   244,
     243,   245,   243,   246,   246,   247,   247,   248,   248,   248,
     248,   248,   249,   249,   250,   250,   252,   253,   251,   254,
     251,   256,   257,   255,   258,   255,   260,   261,   259,   262,
     263,   263,   263,   263,   263,   263,   263,   263,   265,   264,
     266,   268,   267,   270,   269,   271,   271,   272,   272,   272,
     272,   272,   272,   273,   273,   274,   274,   274,   275,   275,
     275,   275,   275,   275,   275,   275,   275,   276,   276,   277,
     277,   278,   278,   278,   279,   279,   279,   279,   280,   280,
     281,   281,   281,   281,   281,   281,   281,   282,   282,   283,
     283,   284,   284,   285,   285,   285,   286,   286,   286,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   287,   287,
     287,   287,   287,   287,   287,   287,   287,   287,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   289,   289,   290,   291,   291,   291,   292,
     294,   293,   295,   296,   297,   295,   299,   300,   298,   301,
     301,   301,   301,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   302,   302,   302,   302,   302,   302,   302,   302,
     302,   302,   303,   304,   302,   305,   305,   305,   306,   306,
     307,   307,   308,   308,   309,   309,   309,   310,   310,   312,
     313,   311,   311,   314,   314,   314,   314,   314,   314,   315,
     316,   317,   317,   317,   318,   318,   319,   320,   320,   320,
     321,   321,   322,   322,   323,   323,   324,   324,   325,   325,
     325,   327,   328,   326,   329,   330,   326,   331,   332,   326,
     334,   335,   333,   336,   336,   336,   337,   337,   337,   337,
     338,   338,   338,   339,   339,   339,   340,   340,   340,   340,
     340,   341,   341,   342,   342,   343,   344,   344,   345,   345,
     345,   345,   345,   345,   345,   346,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   346,   346,   346,   346,   346,
     346,   346,   346,   346,   346,   346,   347,   347,   347,   348,
     348,   348,   348,   348,   349,   349,   350,   351,   352,   350,
     353,   354,   350,   355,   355,   355,   355,   355,   355,   355,
     355,   355,   356,   357,   355,   358,   358,   358,   358,   358,
     358,   358,   359,   359,   359,   360,   360,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   361,   362,   360,   360,   360,   360,   363,   364,   360,
     360,   360,   365,   366,   360,   360,   360,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   367,   367,   367,   368,   368,   368,   368,   368,   368,
     368,   368,   368,   368,   368,   368,   368,   368,   368,   368,
     369,   369,   370,   370,   370,   371,   371,   372,   372,   372,
     373,   373,   374,   375,   375,   375,   376,   375,   377,   375,
     378,   375,   379,   380,   380,   381,   381,   381,   381,   381,
     382,   382,   383,   383,   384,   384,   384,   385,   386,   386,
     387,   387,   387,   388,   388,   389,   389,   389,   390,   390,
     391,   391,   392,   392,   392,   393,   393,   394,   394,   394,
     394,   394,   394,   395,   395,   396,   396,   396,   397,   397,
     397,   398,   398,   398,   399,   399,   400,   400,   400,   401,
     401,   402,   401,   403,   404,   403,   405,   405,   406,   406,
     407,   407,   407,   408,   408,   408,   410,   409,   411,   412,
     412,   412,   413,   414,   414,   415,   415,   416,   416,   417,
     417,   419,   420,   421,   418,   422,   422,   423,   423,   424,
     425,   425,   425,   425,   426,   426,   426,   427,   427,   429,
     430,   431,   428,   432,   432,   432,   432,   432,   432,   433,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     433,   433,   433,   433,   433,   433,   433,   433,   433,   433,
     433,   433,   433,   433,   433,   433,   434,   434,   434,   434,
     434,   434,   434,   434,   435,   436,   436,   436,   437,   437,
     437,   438,   438,   438,   438,   438,   439,   439,   439,   439,
     439,   440,   441,   442,   440,   443,   443,   444,   444,   445,
     445,   445,   445,   446,   446,   447,   447,   448,   448,   448,
     448,   449,   450,   448,   448,   448,   448,   451,   448,   452,
     448,   448,   448,   448,   448,   448,   448,   448,   448,   448,
     448,   448,   448,   453,   454,   448,   448,   455,   456,   448,
     457,   458,   448,   459,   460,   448,   448,   461,   462,   448,
     463,   464,   448,   448,   465,   466,   448,   467,   468,   448,
     448,   469,   470,   448,   471,   472,   448,   473,   474,   448,
     475,   476,   448,   477,   477,   477,   479,   480,   481,   482,
     478,   484,   485,   486,   487,   483,   489,   490,   491,   492,
     488,   493,   493,   493,   493,   493,   493,   493,   494,   494,
     494,   494,   494,   495,   495,   495,   495,   495,   495,   495,
     495,   496,   496,   497,   498,   498,   499,   499,   500,   500,
     501,   501,   503,   504,   502,   505,   506,   502,   507,   508,
     502,   509,   510,   502,   511,   512,   502,   513,   514,   515,
     513,   516,   517,   518,   516,   519,   520,   516,   521,   522,
     516,   516,   523,   524,   516,   516,   525,   526,   516,   527,
     527,   528,   529,   530,   530,   530,   531,   531,   532,   532,
     533,   533,   534
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     3,
       3,     2,     2,     2,     2,     2,     2,     1,     1,     1,
       1,     2,     0,     1,     1,     1,     1,     0,     2,     5,
       1,     1,     2,     2,     3,     2,     0,     2,     0,     0,
       3,     0,     2,     5,     3,     1,     2,     0,     4,     2,
       2,     1,     2,     3,     3,     3,     3,     3,     0,     2,
       3,     5,     0,     1,     2,     1,     3,     1,     3,     3,
       3,     2,     1,     1,     1,     2,     0,     1,     0,     0,
       4,     0,     8,     1,     1,     0,     2,     1,     1,     1,
       1,     1,     1,     2,     0,     1,     0,     0,     6,     0,
       3,     0,     0,     6,     0,     3,     0,     0,     9,     7,
       1,     4,     3,     3,     3,     6,     5,     5,     0,    10,
       3,     0,     8,     0,     7,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     1,     1,     3,     3,
       4,     3,     3,     3,     3,     1,     5,     1,     3,     3,
       4,     0,     3,     1,     1,     1,     1,     1,     1,     4,
       1,     2,     3,     3,     3,     3,     2,     1,     3,     0,
       3,     0,     4,     0,     2,     3,     0,     2,     2,     1,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     3,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,     2,
       2,     3,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     3,     2,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     4,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     1,     4,     0,     1,     1,     3,
       0,     5,     0,     0,     0,     6,     0,     0,     6,     2,
       2,     2,     2,     1,     2,     2,     1,     1,     1,     1,
       2,     1,     2,     2,     2,     2,     1,     1,     1,     2,
       2,     2,     0,     0,     6,     0,     2,     2,     0,     2,
       0,     2,     1,     3,     1,     3,     2,     2,     3,     0,
       0,     5,     1,     2,     5,     5,     5,     6,     2,     1,
       1,     1,     2,     3,     2,     3,     4,     1,     1,     0,
       1,     1,     1,     0,     1,     3,     8,     7,     3,     3,
       5,     0,     0,     7,     0,     0,     7,     0,     0,     7,
       0,     0,     6,     5,     8,    10,     1,     2,     3,     4,
       1,     2,     3,     1,     1,     1,     2,     2,     2,     2,
       4,     1,     3,     0,     4,     7,     7,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     6,     8,     6,     5,
       6,     8,     8,     6,     1,     4,     2,     0,     0,     7,
       0,     0,     8,     3,     4,     5,     6,     8,     8,     6,
       5,     6,     0,     0,     5,     3,     4,     4,     5,     4,
       3,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     2,     2,     2,     4,     3,     4,     5,     4,
       5,     3,     4,     1,     1,     2,     4,     4,     1,     3,
       5,     0,     0,     8,     3,     3,     3,     0,     0,     8,
       3,     4,     0,     0,     9,     4,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     3,     1,     4,     3,     3,
       3,     7,     8,     7,     4,     4,     4,     4,     4,     1,
       6,     7,     6,     6,     7,     7,     6,     7,     6,     5,
       0,     1,     0,     1,     1,     0,     1,     0,     1,     1,
       0,     1,     5,     0,     2,     6,     0,     4,     0,     9,
       0,    11,     3,     3,     4,     1,     1,     3,     3,     3,
       1,     3,     1,     3,     0,     1,     3,     3,     1,     3,
       0,     1,     3,     1,     1,     1,     2,     3,     3,     5,
       1,     1,     1,     1,     1,     0,     1,     1,     4,     3,
       3,     6,     5,     1,     3,     0,     2,     2,     4,     6,
       5,     4,     6,     5,     0,     1,     0,     1,     1,     0,
       2,     0,     4,     6,     0,     6,     1,     3,     1,     2,
       0,     1,     3,     0,     1,     1,     0,     5,     3,     0,
       1,     1,     1,     0,     2,     0,     1,     1,     2,     0,
       1,     0,     0,     0,    13,     0,     2,     0,     1,     3,
       1,     1,     2,     2,     0,     1,     1,     1,     3,     0,
       0,     0,     9,     1,     4,     3,     3,     6,     5,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     4,     1,     3,
       3,     0,     1,     3,     3,     5,     0,     2,     2,     2,
       2,     4,     0,     0,     7,     1,     1,     1,     3,     3,
       2,     4,     3,     1,     2,     0,     4,     1,     1,     1,
       1,     0,     0,     6,     4,     4,     3,     0,     6,     0,
       7,     4,     2,     2,     3,     2,     3,     2,     2,     3,
       3,     3,     2,     0,     0,     6,     2,     0,     0,     6,
       0,     0,     6,     0,     0,     6,     1,     0,     0,     6,
       0,     0,     7,     1,     0,     0,     6,     0,     0,     7,
       1,     0,     0,     6,     0,     0,     7,     0,     0,     6,
       0,     0,     6,     1,     3,     3,     0,     0,     0,     0,
      12,     0,     0,     0,     0,    12,     0,     0,     0,     0,
      13,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     5,     5,     6,     6,     8,
       8,     0,     1,     2,     3,     5,     1,     2,     1,     0,
       0,     1,     0,     0,    10,     0,     0,    10,     0,     0,
      10,     0,     0,    11,     0,     0,     7,     5,     0,     0,
      10,     3,     0,     0,    11,     0,     0,    11,     0,     0,
      10,     5,     0,     0,     9,     5,     0,     0,    10,     1,
       3,     0,     5,     5,     7,     9,     0,     3,     0,     1,
      11,    12,    13
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = DAS2_YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == DAS2_YYEMPTY)                                        \
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
   Use DAS2_YYerror or DAS2_YYUNDEF. */
#define YYERRCODE DAS2_YYUNDEF

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
#if DAS2_YYDEBUG

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

#  elif defined DAS2_YYLTYPE_IS_TRIVIAL && DAS2_YYLTYPE_IS_TRIVIAL

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
#else /* !DAS2_YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !DAS2_YYDEBUG */


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
            { /* gc_node; */ }
        break;

    case YYSYMBOL_string_builder: /* string_builder  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_reader: /* expr_reader  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_require_module_name: /* require_module_name  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_optional_require_guard: /* optional_require_guard  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_expression_label: /* expression_label  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_goto: /* expression_goto  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_else: /* expression_else  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_else_one_liner: /* expression_else_one_liner  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_if_one_liner: /* expression_if_one_liner  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_if_block: /* expression_if_block  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_else_block: /* expression_else_block  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_if_then_else: /* expression_if_then_else  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_if_then_else_oneliner: /* expression_if_then_else_oneliner  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_for_variable_name_with_pos_list: /* for_variable_name_with_pos_list  */
            { delete ((*yyvaluep).pNameWithPosList); }
        break;

    case YYSYMBOL_expression_for_loop: /* expression_for_loop  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_unsafe: /* expression_unsafe  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_while_loop: /* expression_while_loop  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_with: /* expression_with  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_with_alias: /* expression_with_alias  */
            { /* gc_node; */ }
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

    case YYSYMBOL_optional_for_annotations: /* optional_for_annotations  */
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

    case YYSYMBOL_optional_annotation_list_with_emit_semis: /* optional_annotation_list_with_emit_semis  */
            { delete ((*yyvaluep).faList); }
        break;

    case YYSYMBOL_optional_function_argument_list: /* optional_function_argument_list  */
            { deleteVariableDeclarationList(((*yyvaluep).pVarDeclList)); }
        break;

    case YYSYMBOL_optional_function_type: /* optional_function_type  */
            { /* gc owns TypeDecl */ }
        break;

    case YYSYMBOL_function_name: /* function_name  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_das_type_name: /* das_type_name  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_function_declaration_header: /* function_declaration_header  */
            { ((*yyvaluep).pFuncDecl)->delRef(); }
        break;

    case YYSYMBOL_function_declaration: /* function_declaration  */
            { ((*yyvaluep).pFuncDecl)->delRef(); }
        break;

    case YYSYMBOL_expression_block_finally: /* expression_block_finally  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_block: /* expression_block  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_call_pipe_no_bracket: /* expr_call_pipe_no_bracket  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_any: /* expression_any  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expressions: /* expressions  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_optional_expr_list: /* optional_expr_list  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_optional_expr_map_tuple_list: /* optional_expr_map_tuple_list  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_type_declaration_no_options_list: /* type_declaration_no_options_list  */
            { deleteTypeDeclarationList(((*yyvaluep).pTypeDeclList)); }
        break;

    case YYSYMBOL_name_in_namespace: /* name_in_namespace  */
            { delete ((*yyvaluep).s); }
        break;

    case YYSYMBOL_expression_delete: /* expression_delete  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_new_type_declaration: /* new_type_declaration  */
            { /* gc owns TypeDecl */ }
        break;

    case YYSYMBOL_expr_new: /* expr_new  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_break: /* expression_break  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_continue: /* expression_continue  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_return: /* expression_return  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_yield: /* expression_yield  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expression_try_catch: /* expression_try_catch  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_tuple_expansion: /* tuple_expansion  */
            { delete ((*yyvaluep).pNameList); }
        break;

    case YYSYMBOL_tuple_expansion_variable_declaration: /* tuple_expansion_variable_declaration  */
            { delete ((*yyvaluep).pVarDecl); }
        break;

    case YYSYMBOL_expression_let: /* expression_let  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_cast: /* expr_cast  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_type_decl: /* expr_type_decl  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_type_info: /* expr_type_info  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_list: /* expr_list  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_block_or_simple_block: /* block_or_simple_block  */
            { /* gc_node; */ }
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

    case YYSYMBOL_expr_full_block: /* expr_full_block  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_full_block_assumed_piped: /* expr_full_block_assumed_piped  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_numeric_const: /* expr_numeric_const  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_assign_no_bracket: /* expr_assign_no_bracket  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_named_call: /* expr_named_call  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_method_call_no_bracket: /* expr_method_call_no_bracket  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_func_addr_name: /* func_addr_name  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_func_addr_expr: /* func_addr_expr  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_field_no_bracket: /* expr_field_no_bracket  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_call: /* expr_call  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr: /* expr  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_no_bracket: /* expr_no_bracket  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_generator: /* expr_generator  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_mtag_no_bracket: /* expr_mtag_no_bracket  */
            { /* gc_node; */ }
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

    case YYSYMBOL_global_let_variable_name_with_pos_list: /* global_let_variable_name_with_pos_list  */
            { delete ((*yyvaluep).pNameWithPosList); }
        break;

    case YYSYMBOL_variable_declaration_list: /* variable_declaration_list  */
            { deleteVariableDeclarationList(((*yyvaluep).pVarDeclList)); }
        break;

    case YYSYMBOL_let_variable_declaration: /* let_variable_declaration  */
            { delete ((*yyvaluep).pVarDecl); }
        break;

    case YYSYMBOL_global_let_variable_declaration: /* global_let_variable_declaration  */
            { delete ((*yyvaluep).pVarDecl); }
        break;

    case YYSYMBOL_global_variable_declaration_list: /* global_variable_declaration_list  */
            { deleteVariableDeclarationList(((*yyvaluep).pVarDeclList)); }
        break;

    case YYSYMBOL_enum_expression: /* enum_expression  */
            { delete ((*yyvaluep).pEnumPair); }
        break;

    case YYSYMBOL_enum_list: /* enum_list  */
            { /* gc owns Enumeration */ }
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
            { /* gc owns TypeDecl */ }
        break;

    case YYSYMBOL_auto_type_declaration: /* auto_type_declaration  */
            { /* gc owns TypeDecl */ }
        break;

    case YYSYMBOL_bitfield_bits: /* bitfield_bits  */
            { delete ((*yyvaluep).pNameList); }
        break;

    case YYSYMBOL_bitfield_alias_bits: /* bitfield_alias_bits  */
            { deleteNameExprList(((*yyvaluep).pNameExprList)); }
        break;

    case YYSYMBOL_bitfield_type_declaration: /* bitfield_type_declaration  */
            { /* gc owns TypeDecl */ }
        break;

    case YYSYMBOL_table_type_pair: /* table_type_pair  */
            { /* gc owns TypeDecl */ }
        break;

    case YYSYMBOL_dim_list: /* dim_list  */
            { /* gc owns TypeDecl */ }
        break;

    case YYSYMBOL_type_declaration_no_options: /* type_declaration_no_options  */
            { /* gc owns TypeDecl */ }
        break;

    case YYSYMBOL_optional_expr_list_in_braces: /* optional_expr_list_in_braces  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_type_declaration_no_options_no_dim: /* type_declaration_no_options_no_dim  */
            { /* gc owns TypeDecl */ }
        break;

    case YYSYMBOL_type_declaration: /* type_declaration  */
            { /* gc owns TypeDecl */ }
        break;

    case YYSYMBOL_make_decl: /* make_decl  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_make_decl_no_bracket: /* make_decl_no_bracket  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_make_struct_fields: /* make_struct_fields  */
            { /* gc owns MakeStruct */ }
        break;

    case YYSYMBOL_make_variant_dim: /* make_variant_dim  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_make_struct_single: /* make_struct_single  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_make_struct_dim_list: /* make_struct_dim_list  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_make_struct_dim_decl: /* make_struct_dim_decl  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_optional_make_struct_dim_decl: /* optional_make_struct_dim_decl  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_make_struct_decl: /* make_struct_decl  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_make_tuple_call: /* make_tuple_call  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_make_dim_decl: /* make_dim_decl  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_expr_map_tuple_list: /* expr_map_tuple_list  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_make_table_decl: /* make_table_decl  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_make_table_call: /* make_table_call  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_array_comprehension_where: /* array_comprehension_where  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_table_comprehension: /* table_comprehension  */
            { /* gc_node; */ }
        break;

    case YYSYMBOL_array_comprehension: /* array_comprehension  */
            { /* gc_node; */ }
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
# if defined DAS2_YYLTYPE_IS_TRIVIAL && DAS2_YYLTYPE_IS_TRIVIAL
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

  yychar = DAS2_YYEMPTY; /* Cause a token to be read.  */

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
  if (yychar == DAS2_YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= DAS2_YYEOF)
    {
      yychar = DAS2_YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == DAS2_YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = DAS2_YYUNDEF;
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
  yychar = DAS2_YYEMPTY;
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
                das2_yyerror(scanner,"module name has to be first declaration",tokAt(scanner,(yylsp[0])), CompilationError::invalid_module);
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

  case 21: /* top_level_reader_macro: expr_reader SEMICOLON  */
                                   {
        (void)(yyvsp[-1].pExpression); // gc_node — Expression, don't delete
    }
    break;

  case 22: /* optional_public_or_private_module: %empty  */
                        { (yyval.b) = yyextra->g_Program->policies.default_module_public; }
    break;

  case 23: /* optional_public_or_private_module: "public"  */
                        { (yyval.b) = true; }
    break;

  case 24: /* optional_public_or_private_module: "private"  */
                        { (yyval.b) = false; }
    break;

  case 25: /* module_name: '$'  */
                    { (yyval.s) = new string("$"); }
    break;

  case 26: /* module_name: "name"  */
                    { (yyval.s) = (yyvsp[0].s); }
    break;

  case 27: /* optional_not_required: %empty  */
        { (yyval.b) = false; }
    break;

  case 28: /* optional_not_required: '!' "inscope"  */
                        { (yyval.b) = true; }
    break;

  case 29: /* module_declaration: "module" module_name optional_shared optional_public_or_private_module optional_not_required  */
                                                                                                                                    {
        yyextra->g_Program->thisModuleName = *(yyvsp[-3].s);
        yyextra->g_Program->thisModule->isPublic = (yyvsp[-1].b);
        yyextra->g_Program->thisModule->isModule = true;
        yyextra->g_Program->thisModule->visibleEverywhere = (yyvsp[0].b);
        if ( yyextra->g_Program->thisModule->name.empty() ) {
            yyextra->g_Program->library.renameModule(yyextra->g_Program->thisModule.get(),*(yyvsp[-3].s));
        } else if ( yyextra->g_Program->thisModule->name != *(yyvsp[-3].s) ){
            das2_yyerror(scanner,"this module already has a name " + yyextra->g_Program->thisModule->name,tokAt(scanner,(yylsp[-3])),
                CompilationError::already_declared_module_name);
        }
        if ( !yyextra->g_Program->policies.ignore_shared_modules ) {
            yyextra->g_Program->promoteToBuiltin = (yyvsp[-2].b);
        }
        delete (yyvsp[-3].s);
    }
    break;

  case 30: /* character_sequence: STRING_CHARACTER  */
                                                                                  { (yyval.s) = new string(); *(yyval.s) += (yyvsp[0].ch); }
    break;

  case 31: /* character_sequence: STRING_CHARACTER_ESC  */
                                                                                  { (yyval.s) = new string(); *(yyval.s) += "\\\\"; }
    break;

  case 32: /* character_sequence: character_sequence STRING_CHARACTER  */
                                                                                  { (yyval.s) = (yyvsp[-1].s); *(yyvsp[-1].s) += (yyvsp[0].ch); }
    break;

  case 33: /* character_sequence: character_sequence STRING_CHARACTER_ESC  */
                                                                                  { (yyval.s) = (yyvsp[-1].s); *(yyvsp[-1].s) += "\\\\"; }
    break;

  case 34: /* string_constant: "start of the string" character_sequence "end of the string"  */
                                                           { (yyval.s) = (yyvsp[-1].s); }
    break;

  case 35: /* string_constant: "start of the string" "end of the string"  */
                                                           { (yyval.s) = new string(); }
    break;

  case 36: /* format_string: %empty  */
        { (yyval.s) = new string(); }
    break;

  case 37: /* format_string: format_string STRING_CHARACTER  */
                                                 { (yyval.s) = (yyvsp[-1].s); (yyvsp[-1].s)->push_back((yyvsp[0].ch)); }
    break;

  case 38: /* optional_format_string: %empty  */
        { (yyval.s) = new string(""); }
    break;

  case 39: /* $@1: %empty  */
            { das2_strfmt(scanner); }
    break;

  case 40: /* optional_format_string: ':' $@1 format_string  */
                                                         { (yyval.s) = (yyvsp[0].s); }
    break;

  case 41: /* string_builder_body: %empty  */
        {
        (yyval.pExpression) = new ExprStringBuilder();
        (yyval.pExpression)->at = LineInfo(yyextra->g_FileAccessStack.back(),
            yylloc.first_column,yylloc.first_line,yylloc.last_column,yylloc.last_line);
    }
    break;

  case 42: /* string_builder_body: string_builder_body character_sequence  */
                                                                                  {
        bool err;
        auto esconst = unescapeString(*(yyvsp[0].s),&err);
        if ( err ) das2_yyerror(scanner,"invalid escape sequence",tokAt(scanner,(yylsp[-1])), CompilationError::invalid_escape);
        auto sc = new ExprConstString(tokAt(scanner,(yylsp[0])),esconst);
        delete (yyvsp[0].s);
        static_cast<ExprStringBuilder *>((yyvsp[-1].pExpression))->elements.push_back(sc);
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 43: /* string_builder_body: string_builder_body "{" expr optional_format_string "}"  */
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

  case 44: /* string_builder: "start of the string" string_builder_body "end of the string"  */
                                                                   {
        auto strb = static_cast<ExprStringBuilder *>((yyvsp[-1].pExpression));
        if ( strb->elements.size()==0 ) {
            (yyval.pExpression) = new ExprConstString(tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),"");
            // gc_node — don't delete $sb
        } else if ( strb->elements.size()==1 && strb->elements[0]->rtti_isStringConstant() ) {
            auto sconst = static_cast<ExprConstString*>(strb->elements[0]);
            (yyval.pExpression) = new ExprConstString(tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),sconst->text);
            // gc_node — don't delete $sb
        } else {
            (yyval.pExpression) = (yyvsp[-1].pExpression);
        }
    }
    break;

  case 45: /* reader_character_sequence: STRING_CHARACTER  */
                               {
        if ( !yyextra->g_ReaderMacro->accept(yyextra->g_Program.get(), yyextra->g_Program->thisModule.get(), yyextra->g_ReaderExpr, (yyvsp[0].ch), tokAt(scanner,(yylsp[0]))) ) {
            das2_yyend_reader(scanner);
        }
    }
    break;

  case 46: /* reader_character_sequence: reader_character_sequence STRING_CHARACTER  */
                                                                {
        if ( !yyextra->g_ReaderMacro->accept(yyextra->g_Program.get(), yyextra->g_Program->thisModule.get(), yyextra->g_ReaderExpr, (yyvsp[0].ch), tokAt(scanner,(yylsp[0]))) ) {
            das2_yyend_reader(scanner);
        }
    }
    break;

  case 47: /* $@2: %empty  */
                                        {
        auto macros = yyextra->g_Program->getReaderMacro(*(yyvsp[0].s));
        if ( macros.size()==0 ) {
            das2_yyerror(scanner,"reader macro " + *(yyvsp[0].s) + " not found",tokAt(scanner,(yylsp[0])),
                CompilationError::lookup_macro);
        } else if ( macros.size()>1 ) {
            string options;
            for ( auto & x : macros ) {
                options += "\t" + x->module->name + "::" + x->name + "\n";
            }
            das2_yyerror(scanner,"too many options for the reader macro " + *(yyvsp[0].s) +  "\n" + options, tokAt(scanner,(yylsp[0])),
                CompilationError::ambiguous_macro);
        } else if ( yychar != '~' ) {
            das2_yyerror(scanner,"expecting ~ after the reader macro", tokAt(scanner,(yylsp[0])),
                CompilationError::invalid_macro);
        } else {
            yyextra->g_ReaderMacro = macros.back();
            yyextra->g_ReaderExpr = new ExprReader(tokAt(scanner,(yylsp[-1])),yyextra->g_ReaderMacro);
            yyclearin ;
            das2_yybegin_reader(scanner);
        }
    }
    break;

  case 48: /* expr_reader: '%' name_in_namespace $@2 reader_character_sequence  */
                                     {
        yyextra->g_ReaderExpr->at = tokRangeAt(scanner,(yylsp[-3]),(yylsp[0]));
        (yyval.pExpression) = yyextra->g_ReaderExpr;
        int thisLine = 0;
        FileInfo * info = nullptr;
        if ( auto seqt = yyextra->g_ReaderMacro->suffix(yyextra->g_Program.get(), yyextra->g_Program->thisModule.get(), yyextra->g_ReaderExpr, thisLine, info, tokAt(scanner,(yylsp[0]))) ) {
            das2_accept_sequence(scanner,seqt,strlen(seqt),thisLine,info);
            yylloc.first_column = (yylsp[0]).first_column;
            yylloc.first_line = (yylsp[0]).first_line;
            yylloc.last_column = (yylsp[0]).last_column;
            yylloc.last_line = (yylsp[0]).last_line;
        }
        delete (yyvsp[-2].s);
        yyextra->g_ReaderMacro = nullptr;
        yyextra->g_ReaderExpr = nullptr;
    }
    break;

  case 49: /* options_declaration: "options" annotation_argument_list  */
                                                   {
        for ( auto & opt : *(yyvsp[0].aaList) ) {
            if ( yyextra->g_Access->isOptionAllowed(opt.name, yyextra->g_Program->thisModule->fileName) ) {
                if ( yyextra->g_Access->isOptionBlocked(opt.name, yyextra->g_Program->thisModule->fileName) ) {
                    // blocked: ok to write, silently ignored (not applied)
                } else {
                    yyextra->g_Program->options.push_back(opt);
                }
            } else {
                das2_yyerror(scanner,"option " + opt.name + " is not allowed here",
                    tokAt(scanner,(yylsp[0])), CompilationError::invalid_options);
            }
        }
        delete (yyvsp[0].aaList);
    }
    break;

  case 51: /* require_module_name: "name"  */
                   {
        (yyval.s) = (yyvsp[0].s);
    }
    break;

  case 52: /* require_module_name: '%' require_module_name  */
                                     {
        *(yyvsp[0].s) = "%" + *(yyvsp[0].s);
        (yyval.s) = (yyvsp[0].s);
    }
    break;

  case 53: /* require_module_name: '.' '/' require_module_name  */
                                         {
        *(yyvsp[0].s) = "./" + *(yyvsp[0].s);
        (yyval.s) = (yyvsp[0].s);
    }
    break;

  case 54: /* require_module_name: ".." '/' require_module_name  */
                                            {
        *(yyvsp[0].s) = "../" + *(yyvsp[0].s);
        (yyval.s) = (yyvsp[0].s);
    }
    break;

  case 55: /* require_module_name: '%' '/' require_module_name  */
                                         {
        *(yyvsp[0].s) = "%/" + *(yyvsp[0].s);
        (yyval.s) = (yyvsp[0].s);
    }
    break;

  case 56: /* require_module_name: require_module_name '.' "name"  */
                                                {
        *(yyvsp[-2].s) += ".";
        *(yyvsp[-2].s) += *(yyvsp[0].s);
        delete (yyvsp[0].s);
        (yyval.s) = (yyvsp[-2].s);
    }
    break;

  case 57: /* require_module_name: require_module_name '/' "name"  */
                                                {
        *(yyvsp[-2].s) += "/";
        *(yyvsp[-2].s) += *(yyvsp[0].s);
        delete (yyvsp[0].s);
        (yyval.s) = (yyvsp[-2].s);
    }
    break;

  case 58: /* optional_require_guard: %empty  */
                                            { (yyval.s) = nullptr; }
    break;

  case 59: /* optional_require_guard: '?' require_module_name  */
                                            { (yyval.s) = (yyvsp[0].s); }
    break;

  case 60: /* require_module: optional_require_guard require_module_name is_public_module  */
                                                                                       {
        ast_requireModule(scanner,(yyvsp[-1].s),nullptr,(yyvsp[0].b),tokAt(scanner,(yylsp[-1])),(yyvsp[-2].s));
    }
    break;

  case 61: /* require_module: optional_require_guard require_module_name "as" "name" is_public_module  */
                                                                                                            {
        ast_requireModule(scanner,(yyvsp[-3].s),(yyvsp[-1].s),(yyvsp[0].b),tokAt(scanner,(yylsp[-3])),(yyvsp[-4].s));
    }
    break;

  case 62: /* is_public_module: %empty  */
                    { (yyval.b) = false; }
    break;

  case 63: /* is_public_module: "public"  */
                    { (yyval.b) = true; }
    break;

  case 67: /* expect_error: "integer constant"  */
                   {
        yyextra->g_Program->expectErrors[CompilationError((yyvsp[0].i))] ++;
    }
    break;

  case 68: /* expect_error: "integer constant" ':' "integer constant"  */
                                      {
        yyextra->g_Program->expectErrors[CompilationError((yyvsp[-2].i))] += (yyvsp[0].i);
    }
    break;

  case 69: /* expression_label: "label" "integer constant" ':'  */
                                          {
        (yyval.pExpression) = new ExprLabel(tokAt(scanner,(yylsp[-2])),(yyvsp[-1].i));
    }
    break;

  case 70: /* expression_goto: "goto" "label" "integer constant"  */
                                                {
        (yyval.pExpression) = new ExprGoto(tokAt(scanner,(yylsp[-2])),(yyvsp[0].i));
    }
    break;

  case 71: /* expression_goto: "goto" expr  */
                               {
        (yyval.pExpression) = new ExprGoto(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression));
    }
    break;

  case 72: /* elif_or_static_elif: "elif"  */
                          { (yyval.b) = false; }
    break;

  case 73: /* elif_or_static_elif: "static_elif"  */
                          { (yyval.b) = true; }
    break;

  case 78: /* expression_else: %empty  */
                                                           { (yyval.pExpression) = nullptr; }
    break;

  case 79: /* $@3: %empty  */
                                           {
    }
    break;

  case 80: /* expression_else: "else" optional_emit_semis $@3 expression_else_block  */
                                   {
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 81: /* $@4: %empty  */
                                                                        {
    }
    break;

  case 82: /* expression_else: elif_or_static_elif '(' expr ')' optional_emit_semis $@4 expression_else_block expression_else  */
                                                         {
        auto eite = new ExprIfThenElse(tokAt(scanner,(yylsp[-7])),(yyvsp[-5].pExpression),(yyvsp[-1].pExpression),(yyvsp[0].pExpression));
        eite->isStatic = (yyvsp[-7].b);
        (yyval.pExpression) = eite;
    }
    break;

  case 83: /* if_or_static_if: "if"  */
                        { (yyval.b) = false; }
    break;

  case 84: /* if_or_static_if: "static_if"  */
                        { (yyval.b) = true; }
    break;

  case 85: /* expression_else_one_liner: %empty  */
        { (yyval.pExpression) = nullptr; }
    break;

  case 86: /* expression_else_one_liner: "else" expression_if_one_liner  */
                                                      {
            (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 87: /* expression_if_one_liner: expr_no_bracket  */
                                              { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 88: /* expression_if_one_liner: expression_return  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 89: /* expression_if_one_liner: expression_yield  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 90: /* expression_if_one_liner: expression_break  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 91: /* expression_if_one_liner: expression_continue  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 96: /* $@5: %empty  */
                     {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 97: /* $@6: %empty  */
                         {
        yyextra->pop_nesteds();
    }
    break;

  case 98: /* expression_if_block: '{' $@5 expressions $@6 '}' expression_block_finally  */
                                        {
        (yyval.pExpression) = (yyvsp[-3].pExpression);
        (yyval.pExpression)->at = tokRangeAt(scanner,(yylsp[-5]),(yylsp[0]));
        if ( (yyvsp[0].pExpression) ) {
            auto pF = (ExprBlock *) (yyvsp[0].pExpression);
            auto pB = (ExprBlock *) (yyval.pExpression);
            swap ( pB->finalList, pF->list );
            // gc_node — don't delete Expression
        }
    }
    break;

  case 99: /* $@7: %empty  */
       {
        yyextra->das_keyword = false;
    }
    break;

  case 100: /* expression_if_block: $@7 expression_if_one_liner SEMICOLON  */
                                               {
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 101: /* $@8: %empty  */
                     {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 102: /* $@9: %empty  */
                         {
        yyextra->pop_nesteds();
    }
    break;

  case 103: /* expression_else_block: '{' $@8 expressions $@9 '}' expression_block_finally  */
                                        {
        (yyval.pExpression) = (yyvsp[-3].pExpression);
        (yyval.pExpression)->at = tokRangeAt(scanner,(yylsp[-5]),(yylsp[0]));
        if ( (yyvsp[0].pExpression) ) {
            auto pF = (ExprBlock *) (yyvsp[0].pExpression);
            auto pB = (ExprBlock *) (yyval.pExpression);
            swap ( pB->finalList, pF->list );
            // gc_node — don't delete Expression
        }
    }
    break;

  case 104: /* $@10: %empty  */
       {
        yyextra->das_keyword = false;
    }
    break;

  case 105: /* expression_else_block: $@10 expression_if_one_liner SEMICOLON  */
                                               {
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 106: /* $@11: %empty  */
        {
        yyextra->das_keyword = true;
    }
    break;

  case 107: /* $@12: %empty  */
                                                                  {
    }
    break;

  case 108: /* expression_if_then_else: $@11 if_or_static_if '(' expr ')' optional_emit_semis $@12 expression_if_block expression_else  */
                                                       {
        yyextra->das_keyword = false;
        auto blk = (yyvsp[-1].pExpression)->rtti_isBlock() ? static_cast<ExprBlock *>((yyvsp[-1].pExpression)) : ast_wrapInBlock((yyvsp[-1].pExpression));
        auto eite = new ExprIfThenElse(tokAt(scanner,(yylsp[-7])),(yyvsp[-5].pExpression),blk,(yyvsp[0].pExpression));
        eite->isStatic = (yyvsp[-7].b);
        (yyval.pExpression) = eite;
    }
    break;

  case 109: /* expression_if_then_else_oneliner: expression_if_one_liner "if" '(' expr ')' expression_else_one_liner SEMICOLON  */
                                                                                                                      {
        (yyval.pExpression) = new ExprIfThenElse(tokAt(scanner,(yylsp[-5])),(yyvsp[-3].pExpression),ast_wrapInBlock((yyvsp[-6].pExpression)),(yyvsp[-1].pExpression) ? ast_wrapInBlock((yyvsp[-1].pExpression)) : nullptr);
    }
    break;

  case 110: /* for_variable_name_with_pos_list: "name"  */
                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = pSL;
        delete (yyvsp[0].s);
    }
    break;

  case 111: /* for_variable_name_with_pos_list: "$i" '(' expr ')'  */
                                     {
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = pSL;
    }
    break;

  case 112: /* for_variable_name_with_pos_list: "name" "aka" "name"  */
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

  case 113: /* for_variable_name_with_pos_list: '(' tuple_expansion ')'  */
                                       {
        auto pSL = new vector<VariableNameAndPosition>();
        for ( auto & x : *(yyvsp[-1].pNameList) ) {
            das_checkName(scanner,x,tokAt(scanner,(yylsp[-1])));
        }
        pSL->push_back(VariableNameAndPosition((yyvsp[-1].pNameList),tokAt(scanner,(yylsp[-1]))));
        (yyval.pNameWithPosList) = pSL;
    }
    break;

  case 114: /* for_variable_name_with_pos_list: for_variable_name_with_pos_list ',' "name"  */
                                                             {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = (yyvsp[-2].pNameWithPosList);
        delete (yyvsp[0].s);
    }
    break;

  case 115: /* for_variable_name_with_pos_list: for_variable_name_with_pos_list ',' "$i" '(' expr ')'  */
                                                                               {
        (yyvsp[-5].pNameWithPosList)->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = (yyvsp[-5].pNameWithPosList);
    }
    break;

  case 116: /* for_variable_name_with_pos_list: for_variable_name_with_pos_list ',' "name" "aka" "name"  */
                                                                                   {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-4].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[-2].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-2]))));
        (yyval.pNameWithPosList) = (yyvsp[-4].pNameWithPosList);
        delete (yyvsp[-2].s);
        delete (yyvsp[0].s);
    }
    break;

  case 117: /* for_variable_name_with_pos_list: for_variable_name_with_pos_list ',' '(' tuple_expansion ')'  */
                                                                                 {
        for ( auto & x : *(yyvsp[-1].pNameList) ) {
            das_checkName(scanner,x,tokAt(scanner,(yylsp[-1])));
        }
        (yyvsp[-4].pNameWithPosList)->push_back(VariableNameAndPosition((yyvsp[-1].pNameList),tokAt(scanner,(yylsp[-1]))));
        (yyval.pNameWithPosList) = (yyvsp[-4].pNameWithPosList);
    }
    break;

  case 118: /* $@13: %empty  */
        {
        yyextra->das_keyword = true;
    }
    break;

  case 119: /* expression_for_loop: $@13 "for" optional_for_annotations '(' for_variable_name_with_pos_list "in" expr_list ')' optional_emit_semis expression_block  */
                                                                                                                                                                    {
        yyextra->das_keyword = false;
        (yyval.pExpression) = ast_forLoop(scanner,(yyvsp[-5].pNameWithPosList),(yyvsp[-3].pExpression),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[-8])),tokAt(scanner,(yylsp[0])),(yyvsp[-7].aaList));
    }
    break;

  case 120: /* expression_unsafe: "unsafe" optional_emit_semis expression_block  */
                                                                    {
        auto pUnsafe = new ExprUnsafe(tokAt(scanner,(yylsp[-2])));
        pUnsafe->body = (yyvsp[0].pExpression);
        (yyval.pExpression) = pUnsafe;
    }
    break;

  case 121: /* $@14: %empty  */
        {
        yyextra->das_keyword = true;
    }
    break;

  case 122: /* expression_while_loop: $@14 "while" optional_for_annotations '(' expr ')' optional_emit_semis expression_block  */
                                                                                                                        {
        yyextra->das_keyword = false;
        auto pWhile = new ExprWhile(tokAt(scanner,(yylsp[-6])));
        pWhile->cond = (yyvsp[-3].pExpression);
        pWhile->body = (yyvsp[0].pExpression);
        if ( (yyvsp[-5].aaList) ) { pWhile->annotations = move(*(yyvsp[-5].aaList)); delete (yyvsp[-5].aaList); }
        ((ExprBlock *)(yyvsp[0].pExpression))->inTheLoop = true;
        (yyval.pExpression) = pWhile;
    }
    break;

  case 123: /* $@15: %empty  */
        {
        yyextra->das_keyword = true;
    }
    break;

  case 124: /* expression_with: $@15 "with" '(' expr ')' optional_emit_semis expression_block  */
                                                                                   {
        yyextra->das_keyword = false;
        auto pWith = new ExprWith(tokAt(scanner,(yylsp[-5])));
        pWith->with = (yyvsp[-3].pExpression);
        pWith->body = (yyvsp[0].pExpression);
        (yyval.pExpression) = pWith;
    }
    break;

  case 125: /* expression_with_alias: "assume" "name" '=' expr  */
                                                      {
        (yyval.pExpression) = new ExprAssume(tokAt(scanner,(yylsp[-3])), *(yyvsp[-2].s), ExpressionPtr((yyvsp[0].pExpression)));
        delete (yyvsp[-2].s);
    }
    break;

  case 126: /* expression_with_alias: "typedef" "name" '=' type_declaration  */
                                                                {
        (yyval.pExpression) = new ExprAssume(tokAt(scanner,(yylsp[-3])), *(yyvsp[-2].s), TypeDeclPtr((yyvsp[0].pTypeDecl)));
        delete (yyvsp[-2].s);
    }
    break;

  case 127: /* annotation_argument_value: string_constant  */
                                 { (yyval.aa) = new AnnotationArgument("",*(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 128: /* annotation_argument_value: "name"  */
                                 { (yyval.aa) = new AnnotationArgument("",*(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 129: /* annotation_argument_value: "integer constant"  */
                                 { (yyval.aa) = new AnnotationArgument("",(yyvsp[0].i)); }
    break;

  case 130: /* annotation_argument_value: "floating point constant"  */
                                 { (yyval.aa) = new AnnotationArgument("",float((yyvsp[0].fd))); }
    break;

  case 131: /* annotation_argument_value: "true"  */
                                 { (yyval.aa) = new AnnotationArgument("",true); }
    break;

  case 132: /* annotation_argument_value: "false"  */
                                 { (yyval.aa) = new AnnotationArgument("",false); }
    break;

  case 133: /* annotation_argument_value_list: annotation_argument_value  */
                                       {
        (yyval.aaList) = new AnnotationArgumentList();
        (yyval.aaList)->push_back(*(yyvsp[0].aa));
        delete (yyvsp[0].aa);
    }
    break;

  case 134: /* annotation_argument_value_list: annotation_argument_value_list ',' annotation_argument_value  */
                                                                                {
            (yyval.aaList) = (yyvsp[-2].aaList);
            (yyval.aaList)->push_back(*(yyvsp[0].aa));
            delete (yyvsp[0].aa);
    }
    break;

  case 135: /* annotation_argument_name: "name"  */
                    { (yyval.s) = (yyvsp[0].s); }
    break;

  case 136: /* annotation_argument_name: "type"  */
                    { (yyval.s) = new string("type"); }
    break;

  case 137: /* annotation_argument_name: "in"  */
                    { (yyval.s) = new string("in"); }
    break;

  case 138: /* annotation_argument: annotation_argument_name '=' string_constant  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-2]))); delete (yyvsp[0].s); delete (yyvsp[-2].s); }
    break;

  case 139: /* annotation_argument: annotation_argument_name '=' "name"  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-2]))); delete (yyvsp[0].s); delete (yyvsp[-2].s); }
    break;

  case 140: /* annotation_argument: annotation_argument_name '=' "@@" "name"  */
                                                                      { (yyval.aa) = new AnnotationArgument(*(yyvsp[-3].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-3]))); delete (yyvsp[0].s); delete (yyvsp[-3].s); }
    break;

  case 141: /* annotation_argument: annotation_argument_name '=' "integer constant"  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),(yyvsp[0].i),tokAt(scanner,(yylsp[-2]))); delete (yyvsp[-2].s); }
    break;

  case 142: /* annotation_argument: annotation_argument_name '=' "floating point constant"  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),float((yyvsp[0].fd)),tokAt(scanner,(yylsp[-2]))); delete (yyvsp[-2].s); }
    break;

  case 143: /* annotation_argument: annotation_argument_name '=' "true"  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),true,tokAt(scanner,(yylsp[-2]))); delete (yyvsp[-2].s); }
    break;

  case 144: /* annotation_argument: annotation_argument_name '=' "false"  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),false,tokAt(scanner,(yylsp[-2]))); delete (yyvsp[-2].s); }
    break;

  case 145: /* annotation_argument: annotation_argument_name  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[0].s),true,tokAt(scanner,(yylsp[0]))); delete (yyvsp[0].s); }
    break;

  case 146: /* annotation_argument: annotation_argument_name '=' '(' annotation_argument_value_list ')'  */
                                                                                          {
        { (yyval.aa) = new AnnotationArgument(*(yyvsp[-4].s),(yyvsp[-1].aaList),tokAt(scanner,(yylsp[-4]))); delete (yyvsp[-4].s); }
    }
    break;

  case 147: /* annotation_argument_list: annotation_argument  */
                                  {
        (yyval.aaList) = ast_annotationArgumentListEntry(scanner,new AnnotationArgumentList(),(yyvsp[0].aa));
    }
    break;

  case 148: /* annotation_argument_list: annotation_argument_list ',' annotation_argument  */
                                                                    {
        (yyval.aaList) = ast_annotationArgumentListEntry(scanner,(yyvsp[-2].aaList),(yyvsp[0].aa));
    }
    break;

  case 149: /* metadata_argument_list: "@field" annotation_argument optional_emit_semis  */
                                                              {
        (yyval.aaList) = ast_annotationArgumentListEntry(scanner,new AnnotationArgumentList(),(yyvsp[-1].aa));
    }
    break;

  case 150: /* metadata_argument_list: metadata_argument_list "@field" annotation_argument optional_emit_semis  */
                                                                                           {
        (yyval.aaList) = ast_annotationArgumentListEntry(scanner,(yyvsp[-3].aaList),(yyvsp[-1].aa));
    }
    break;

  case 151: /* optional_for_annotations: %empty  */
                    {
        (yyval.aaList) = nullptr;
    }
    break;

  case 152: /* optional_for_annotations: '[' annotation_argument_list ']'  */
                                               {
        (yyval.aaList) = (yyvsp[-1].aaList);
    }
    break;

  case 153: /* optional_for_annotations: metadata_argument_list  */
                                     {
        (yyval.aaList) = (yyvsp[0].aaList);
    }
    break;

  case 154: /* annotation_declaration_name: name_in_namespace  */
                                    { (yyval.s) = (yyvsp[0].s); }
    break;

  case 155: /* annotation_declaration_name: "require"  */
                                    { (yyval.s) = new string("require"); }
    break;

  case 156: /* annotation_declaration_name: "private"  */
                                    { (yyval.s) = new string("private"); }
    break;

  case 157: /* annotation_declaration_name: "template"  */
                                    { (yyval.s) = new string("template"); }
    break;

  case 158: /* annotation_declaration_basic: annotation_declaration_name  */
                                          {
        (yyval.fa) = new AnnotationDeclaration();
        (yyval.fa)->at = tokAt(scanner,(yylsp[0]));
        if ( yyextra->g_Access->isAnnotationAllowed(*(yyvsp[0].s), yyextra->g_Program->thisModuleName) ) {
            if ( auto ann = findAnnotation(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0]))) ) {
                (yyval.fa)->annotation = ann;
            } else {
                (yyval.fa)->annotation = new Annotation(*(yyvsp[0].s));
                das2_yyerror(scanner,"annotation " + *(yyvsp[0].s) + " is not found",
                            tokAt(scanner,(yylsp[0])), CompilationError::lookup_annotation);
            }
        } else {
            (yyval.fa)->annotation = new Annotation(*(yyvsp[0].s));
            das2_yyerror(scanner,"annotation " + *(yyvsp[0].s) + " is not allowed here",
                        tokAt(scanner,(yylsp[0])), CompilationError::invalid_annotation);
        }
        delete (yyvsp[0].s);
    }
    break;

  case 159: /* annotation_declaration_basic: annotation_declaration_name '(' annotation_argument_list ')'  */
                                                                                 {
        (yyval.fa) = new AnnotationDeclaration();
        (yyval.fa)->at = tokAt(scanner,(yylsp[-3]));
        if ( yyextra->g_Access->isAnnotationAllowed(*(yyvsp[-3].s), yyextra->g_Program->thisModuleName) ) {
            if ( auto ann = findAnnotation(scanner,*(yyvsp[-3].s),tokAt(scanner,(yylsp[-3]))) ) {
                (yyval.fa)->annotation = ann;
            } else {
                (yyval.fa)->annotation = new Annotation(*(yyvsp[-3].s));
                das2_yyerror(scanner,"annotation " + *(yyvsp[-3].s) + " is not found",
                            tokAt(scanner,(yylsp[-3])), CompilationError::lookup_annotation);
            }
        } else {
            (yyval.fa)->annotation = new Annotation(*(yyvsp[-3].s));
            das2_yyerror(scanner,"annotation " + *(yyvsp[-3].s) + " is not allowed here",
                        tokAt(scanner,(yylsp[-3])), CompilationError::invalid_annotation);
        }
        swap ( (yyval.fa)->arguments, *(yyvsp[-1].aaList) );
        delete (yyvsp[-1].aaList);
        delete (yyvsp[-3].s);
    }
    break;

  case 160: /* annotation_declaration: annotation_declaration_basic  */
                                          {
        (yyval.fa) = (yyvsp[0].fa);
    }
    break;

  case 161: /* annotation_declaration: '!' annotation_declaration  */
                                              {
        if ( !(yyvsp[0].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[0].fa)->annotation))->isSpecialized() ) {
            das2_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[0])),
                CompilationError::invalid_annotation);
            delete (yyvsp[0].fa); (yyvsp[0].fa) = nullptr;
        }
        (yyval.fa) = new AnnotationDeclaration();
        (yyval.fa)->at = tokAt(scanner, (yylsp[-1]));
        (yyval.fa)->annotation = newLogicAnnotation(LogicAnnotationOp::Not,(yyvsp[0].fa),nullptr);
    }
    break;

  case 162: /* annotation_declaration: annotation_declaration "&&" annotation_declaration  */
                                                                              {
        if ( !(yyvsp[-2].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[-2].fa)->annotation))->isSpecialized() ) {
            das2_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[-2])),
                CompilationError::invalid_annotation);
            delete (yyvsp[-2].fa); (yyvsp[-2].fa) = nullptr;
        }
        if ( !(yyvsp[0].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[0].fa)->annotation))->isSpecialized() ) {
            das2_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[0])),
                CompilationError::invalid_annotation);
            delete (yyvsp[-2].fa); (yyvsp[-2].fa) = nullptr;
        }
        (yyval.fa) = new AnnotationDeclaration();
        (yyval.fa)->at = tokAt(scanner, (yylsp[-1]));
        (yyval.fa)->annotation = newLogicAnnotation(LogicAnnotationOp::And,(yyvsp[-2].fa),(yyvsp[0].fa));
    }
    break;

  case 163: /* annotation_declaration: annotation_declaration "||" annotation_declaration  */
                                                                            {
        if ( !(yyvsp[-2].fa)->annotation || !(yyvsp[-2].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[-2].fa)->annotation))->isSpecialized() ) {
            das2_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[-2])),
                CompilationError::invalid_annotation);
            delete (yyvsp[-2].fa); (yyvsp[-2].fa) = nullptr;
        }
        if ( !(yyvsp[0].fa)->annotation || !(yyvsp[0].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[0].fa)->annotation))->isSpecialized() ) {
            das2_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[0])),
                CompilationError::invalid_annotation);
            delete (yyvsp[-2].fa); (yyvsp[-2].fa) = nullptr;
        }
        (yyval.fa) = new AnnotationDeclaration();
        (yyval.fa)->at = tokAt(scanner, (yylsp[-1]));
        (yyval.fa)->annotation = newLogicAnnotation(LogicAnnotationOp::Or,(yyvsp[-2].fa),(yyvsp[0].fa));
    }
    break;

  case 164: /* annotation_declaration: annotation_declaration "^^" annotation_declaration  */
                                                                              {
        if ( !(yyvsp[-2].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[-2].fa)->annotation))->isSpecialized() ) {
            das2_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[-2])),
                CompilationError::invalid_annotation);
            delete (yyvsp[-2].fa); (yyvsp[-2].fa) = nullptr;
        }
        if ( !(yyvsp[0].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[0].fa)->annotation))->isSpecialized() ) {
            das2_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[0])),
                CompilationError::invalid_annotation);
            delete (yyvsp[-2].fa); (yyvsp[-2].fa) = nullptr;
        }
        (yyval.fa) = new AnnotationDeclaration();
        (yyval.fa)->at = tokAt(scanner, (yylsp[-1]));
        (yyval.fa)->annotation = newLogicAnnotation(LogicAnnotationOp::Xor,(yyvsp[-2].fa),(yyvsp[0].fa));
    }
    break;

  case 165: /* annotation_declaration: '(' annotation_declaration ')'  */
                                            {
        (yyval.fa) = (yyvsp[-1].fa);
    }
    break;

  case 166: /* annotation_declaration: "|>" annotation_declaration  */
                                          {
        (yyval.fa) = (yyvsp[0].fa);
        (yyvsp[0].fa)->inherited = true;
    }
    break;

  case 167: /* annotation_list: annotation_declaration  */
                                    {
            (yyval.faList) = new AnnotationList();
            (yyval.faList)->push_back(AnnotationDeclarationPtr((yyvsp[0].fa)));
    }
    break;

  case 168: /* annotation_list: annotation_list ',' annotation_declaration  */
                                                              {
        (yyval.faList) = (yyvsp[-2].faList);
        (yyval.faList)->push_back(AnnotationDeclarationPtr((yyvsp[0].fa)));
    }
    break;

  case 169: /* optional_annotation_list: %empty  */
                                       { (yyval.faList) = nullptr; }
    break;

  case 170: /* optional_annotation_list: '[' annotation_list ']'  */
                                       { (yyval.faList) = (yyvsp[-1].faList); }
    break;

  case 171: /* optional_annotation_list_with_emit_semis: %empty  */
                                       { (yyval.faList) = nullptr; }
    break;

  case 172: /* optional_annotation_list_with_emit_semis: '[' annotation_list ']' optional_emit_semis  */
                                                          { (yyval.faList) = (yyvsp[-2].faList); }
    break;

  case 173: /* optional_function_argument_list: %empty  */
                                                { (yyval.pVarDeclList) = nullptr; }
    break;

  case 174: /* optional_function_argument_list: '(' ')'  */
                                                { (yyval.pVarDeclList) = nullptr; }
    break;

  case 175: /* optional_function_argument_list: '(' function_argument_list ')'  */
                                                { (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList); }
    break;

  case 176: /* optional_function_type: %empty  */
        {
        (yyval.pTypeDecl) = new TypeDecl(Type::autoinfer);
    }
    break;

  case 177: /* optional_function_type: ':' type_declaration  */
                                        {
        (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 178: /* optional_function_type: "->" type_declaration  */
                                           {
        (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 179: /* function_name: "name"  */
                          {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyval.s) = (yyvsp[0].s);
    }
    break;

  case 180: /* function_name: "operator" '!'  */
                             { (yyval.s) = new string("!"); }
    break;

  case 181: /* function_name: "operator" '~'  */
                             { (yyval.s) = new string("~"); }
    break;

  case 182: /* function_name: "operator" "+="  */
                             { (yyval.s) = new string("+="); }
    break;

  case 183: /* function_name: "operator" "-="  */
                             { (yyval.s) = new string("-="); }
    break;

  case 184: /* function_name: "operator" "*="  */
                             { (yyval.s) = new string("*="); }
    break;

  case 185: /* function_name: "operator" "/="  */
                             { (yyval.s) = new string("/="); }
    break;

  case 186: /* function_name: "operator" "%="  */
                             { (yyval.s) = new string("%="); }
    break;

  case 187: /* function_name: "operator" "&="  */
                             { (yyval.s) = new string("&="); }
    break;

  case 188: /* function_name: "operator" "|="  */
                             { (yyval.s) = new string("|="); }
    break;

  case 189: /* function_name: "operator" "^="  */
                             { (yyval.s) = new string("^="); }
    break;

  case 190: /* function_name: "operator" "&&="  */
                                { (yyval.s) = new string("&&="); }
    break;

  case 191: /* function_name: "operator" "||="  */
                                { (yyval.s) = new string("||="); }
    break;

  case 192: /* function_name: "operator" "^^="  */
                                { (yyval.s) = new string("^^="); }
    break;

  case 193: /* function_name: "operator" "&&"  */
                             { (yyval.s) = new string("&&"); }
    break;

  case 194: /* function_name: "operator" "||"  */
                             { (yyval.s) = new string("||"); }
    break;

  case 195: /* function_name: "operator" "^^"  */
                             { (yyval.s) = new string("^^"); }
    break;

  case 196: /* function_name: "operator" '+'  */
                             { (yyval.s) = new string("+"); }
    break;

  case 197: /* function_name: "operator" '-'  */
                             { (yyval.s) = new string("-"); }
    break;

  case 198: /* function_name: "operator" '*'  */
                             { (yyval.s) = new string("*"); }
    break;

  case 199: /* function_name: "operator" '/'  */
                             { (yyval.s) = new string("/"); }
    break;

  case 200: /* function_name: "operator" '%'  */
                             { (yyval.s) = new string("%"); }
    break;

  case 201: /* function_name: "operator" '<'  */
                             { (yyval.s) = new string("<"); }
    break;

  case 202: /* function_name: "operator" '>'  */
                             { (yyval.s) = new string(">"); }
    break;

  case 203: /* function_name: "operator" ".."  */
                             { (yyval.s) = new string("interval"); }
    break;

  case 204: /* function_name: "operator" "=="  */
                             { (yyval.s) = new string("=="); }
    break;

  case 205: /* function_name: "operator" "!="  */
                             { (yyval.s) = new string("!="); }
    break;

  case 206: /* function_name: "operator" "<="  */
                             { (yyval.s) = new string("<="); }
    break;

  case 207: /* function_name: "operator" ">="  */
                             { (yyval.s) = new string(">="); }
    break;

  case 208: /* function_name: "operator" '&'  */
                             { (yyval.s) = new string("&"); }
    break;

  case 209: /* function_name: "operator" '|'  */
                             { (yyval.s) = new string("|"); }
    break;

  case 210: /* function_name: "operator" '^'  */
                             { (yyval.s) = new string("^"); }
    break;

  case 211: /* function_name: "++" "operator"  */
                             { (yyval.s) = new string("++"); }
    break;

  case 212: /* function_name: "--" "operator"  */
                             { (yyval.s) = new string("--"); }
    break;

  case 213: /* function_name: "operator" "++"  */
                             { (yyval.s) = new string("+++"); }
    break;

  case 214: /* function_name: "operator" "--"  */
                             { (yyval.s) = new string("---"); }
    break;

  case 215: /* function_name: "operator" "<<"  */
                             { (yyval.s) = new string("<<"); }
    break;

  case 216: /* function_name: "operator" ">>"  */
                             { (yyval.s) = new string(">>"); }
    break;

  case 217: /* function_name: "operator" "<<="  */
                             { (yyval.s) = new string("<<="); }
    break;

  case 218: /* function_name: "operator" ">>="  */
                             { (yyval.s) = new string(">>="); }
    break;

  case 219: /* function_name: "operator" "<<<"  */
                             { (yyval.s) = new string("<<<"); }
    break;

  case 220: /* function_name: "operator" ">>>"  */
                             { (yyval.s) = new string(">>>"); }
    break;

  case 221: /* function_name: "operator" "<<<="  */
                             { (yyval.s) = new string("<<<="); }
    break;

  case 222: /* function_name: "operator" ">>>="  */
                             { (yyval.s) = new string(">>>="); }
    break;

  case 223: /* function_name: "operator" '[' ']'  */
                             { (yyval.s) = new string("[]"); }
    break;

  case 224: /* function_name: "operator" '[' ']' '='  */
                                 { (yyval.s) = new string("[]="); }
    break;

  case 225: /* function_name: "operator" '[' ']' "<-"  */
                                    { (yyval.s) = new string("[]<-"); }
    break;

  case 226: /* function_name: "operator" '[' ']' ":="  */
                                      { (yyval.s) = new string("[]:="); }
    break;

  case 227: /* function_name: "operator" '[' ']' "+="  */
                                     { (yyval.s) = new string("[]+="); }
    break;

  case 228: /* function_name: "operator" '[' ']' "-="  */
                                     { (yyval.s) = new string("[]-="); }
    break;

  case 229: /* function_name: "operator" '[' ']' "*="  */
                                     { (yyval.s) = new string("[]*="); }
    break;

  case 230: /* function_name: "operator" '[' ']' "/="  */
                                     { (yyval.s) = new string("[]/="); }
    break;

  case 231: /* function_name: "operator" '[' ']' "%="  */
                                     { (yyval.s) = new string("[]%="); }
    break;

  case 232: /* function_name: "operator" '[' ']' "&="  */
                                     { (yyval.s) = new string("[]&="); }
    break;

  case 233: /* function_name: "operator" '[' ']' "|="  */
                                     { (yyval.s) = new string("[]|="); }
    break;

  case 234: /* function_name: "operator" '[' ']' "^="  */
                                     { (yyval.s) = new string("[]^="); }
    break;

  case 235: /* function_name: "operator" '[' ']' "&&="  */
                                        { (yyval.s) = new string("[]&&="); }
    break;

  case 236: /* function_name: "operator" '[' ']' "||="  */
                                        { (yyval.s) = new string("[]||="); }
    break;

  case 237: /* function_name: "operator" '[' ']' "^^="  */
                                        { (yyval.s) = new string("[]^^="); }
    break;

  case 238: /* function_name: "operator" "?[" ']'  */
                                { (yyval.s) = new string("?[]"); }
    break;

  case 239: /* function_name: "operator" '.'  */
                             { (yyval.s) = new string("."); }
    break;

  case 240: /* function_name: "operator" "?."  */
                             { (yyval.s) = new string("?."); }
    break;

  case 241: /* function_name: "operator" '.' "name"  */
                                       { (yyval.s) = new string(".`"+*(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 242: /* function_name: "operator" '.' "name" ":="  */
                                             { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`clone"); delete (yyvsp[-1].s); }
    break;

  case 243: /* function_name: "operator" '.' "name" "+="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`+="); delete (yyvsp[-1].s); }
    break;

  case 244: /* function_name: "operator" '.' "name" "-="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`-="); delete (yyvsp[-1].s); }
    break;

  case 245: /* function_name: "operator" '.' "name" "*="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`*="); delete (yyvsp[-1].s); }
    break;

  case 246: /* function_name: "operator" '.' "name" "/="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`/="); delete (yyvsp[-1].s); }
    break;

  case 247: /* function_name: "operator" '.' "name" "%="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`%="); delete (yyvsp[-1].s); }
    break;

  case 248: /* function_name: "operator" '.' "name" "&="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`&="); delete (yyvsp[-1].s); }
    break;

  case 249: /* function_name: "operator" '.' "name" "|="  */
                                          { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`|="); delete (yyvsp[-1].s); }
    break;

  case 250: /* function_name: "operator" '.' "name" "^="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`^="); delete (yyvsp[-1].s); }
    break;

  case 251: /* function_name: "operator" '.' "name" "&&="  */
                                              { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`&&="); delete (yyvsp[-1].s); }
    break;

  case 252: /* function_name: "operator" '.' "name" "||="  */
                                            { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`||="); delete (yyvsp[-1].s); }
    break;

  case 253: /* function_name: "operator" '.' "name" "^^="  */
                                              { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`^^="); delete (yyvsp[-1].s); }
    break;

  case 254: /* function_name: "operator" "?." "name"  */
                                       { (yyval.s) = new string("?.`"+*(yyvsp[0].s)); delete (yyvsp[0].s);}
    break;

  case 255: /* function_name: "operator" ":="  */
                                { (yyval.s) = new string("clone"); }
    break;

  case 256: /* function_name: "operator" "delete"  */
                                { (yyval.s) = new string("finalize"); }
    break;

  case 257: /* function_name: "operator" "??"  */
                           { (yyval.s) = new string("??"); }
    break;

  case 258: /* function_name: "operator" "is"  */
                            { (yyval.s) = new string("`is"); }
    break;

  case 259: /* function_name: "operator" "as"  */
                            { (yyval.s) = new string("`as"); }
    break;

  case 260: /* function_name: "operator" "is" "name"  */
                                       { (yyval.s) = (yyvsp[0].s); *(yyvsp[0].s) = "`is`" + *(yyvsp[0].s); }
    break;

  case 261: /* function_name: "operator" "as" "name"  */
                                       { (yyval.s) = (yyvsp[0].s); *(yyvsp[0].s) = "`as`" + *(yyvsp[0].s); }
    break;

  case 262: /* function_name: "operator" "is" das_type_name  */
                                                { (yyval.s) = (yyvsp[0].s); *(yyvsp[0].s) = "`is`" + *(yyvsp[0].s); }
    break;

  case 263: /* function_name: "operator" "as" das_type_name  */
                                                { (yyval.s) = (yyvsp[0].s); *(yyvsp[0].s) = "`as`" + *(yyvsp[0].s); }
    break;

  case 264: /* function_name: "operator" '?' "as"  */
                                { (yyval.s) = new string("?as"); }
    break;

  case 265: /* function_name: "operator" '?' "as" "name"  */
                                           { (yyval.s) = (yyvsp[0].s); *(yyvsp[0].s) = "?as`" + *(yyvsp[0].s); }
    break;

  case 266: /* function_name: "operator" '?' "as" das_type_name  */
                                                    { (yyval.s) = (yyvsp[0].s); *(yyvsp[0].s) = "?as`" + *(yyvsp[0].s); }
    break;

  case 267: /* function_name: das_type_name  */
                            { (yyval.s) = (yyvsp[0].s); }
    break;

  case 268: /* das_type_name: "bool"  */
                     { (yyval.s) = new string("bool"); }
    break;

  case 269: /* das_type_name: "string"  */
                     { (yyval.s) = new string("string"); }
    break;

  case 270: /* das_type_name: "int"  */
                     { (yyval.s) = new string("int"); }
    break;

  case 271: /* das_type_name: "int2"  */
                     { (yyval.s) = new string("int2"); }
    break;

  case 272: /* das_type_name: "int3"  */
                     { (yyval.s) = new string("int3"); }
    break;

  case 273: /* das_type_name: "int4"  */
                     { (yyval.s) = new string("int4"); }
    break;

  case 274: /* das_type_name: "uint"  */
                     { (yyval.s) = new string("uint"); }
    break;

  case 275: /* das_type_name: "uint2"  */
                     { (yyval.s) = new string("uint2"); }
    break;

  case 276: /* das_type_name: "uint3"  */
                     { (yyval.s) = new string("uint3"); }
    break;

  case 277: /* das_type_name: "uint4"  */
                     { (yyval.s) = new string("uint4"); }
    break;

  case 278: /* das_type_name: "float"  */
                     { (yyval.s) = new string("float"); }
    break;

  case 279: /* das_type_name: "float2"  */
                     { (yyval.s) = new string("float2"); }
    break;

  case 280: /* das_type_name: "float3"  */
                     { (yyval.s) = new string("float3"); }
    break;

  case 281: /* das_type_name: "float4"  */
                     { (yyval.s) = new string("float4"); }
    break;

  case 282: /* das_type_name: "range"  */
                     { (yyval.s) = new string("range"); }
    break;

  case 283: /* das_type_name: "urange"  */
                     { (yyval.s) = new string("urange"); }
    break;

  case 284: /* das_type_name: "range64"  */
                     { (yyval.s) = new string("range64"); }
    break;

  case 285: /* das_type_name: "urange64"  */
                     { (yyval.s) = new string("urange64"); }
    break;

  case 286: /* das_type_name: "int64"  */
                     { (yyval.s) = new string("int64"); }
    break;

  case 287: /* das_type_name: "uint64"  */
                     { (yyval.s) = new string("uint64"); }
    break;

  case 288: /* das_type_name: "double"  */
                     { (yyval.s) = new string("double"); }
    break;

  case 289: /* das_type_name: "int8"  */
                     { (yyval.s) = new string("int8"); }
    break;

  case 290: /* das_type_name: "uint8"  */
                     { (yyval.s) = new string("uint8"); }
    break;

  case 291: /* das_type_name: "int16"  */
                     { (yyval.s) = new string("int16"); }
    break;

  case 292: /* das_type_name: "uint16"  */
                     { (yyval.s) = new string("uint16"); }
    break;

  case 293: /* optional_template: %empty  */
                                        { (yyval.b) = false; }
    break;

  case 294: /* optional_template: "template"  */
                                        { (yyval.b) = true; }
    break;

  case 295: /* global_function_declaration: optional_annotation_list_with_emit_semis "def" optional_template function_declaration  */
                                                                                                                              {
        (yyvsp[0].pFuncDecl)->atDecl = tokRangeAt(scanner,(yylsp[-2]),(yylsp[0]));
        (yyvsp[0].pFuncDecl)->isTemplate = (yyvsp[-1].b);
        assignDefaultArguments((yyvsp[0].pFuncDecl));
        runFunctionAnnotations(scanner, yyextra, (yyvsp[0].pFuncDecl), (yyvsp[-3].faList), tokAt(scanner,(yylsp[-3])));
        if ( (yyvsp[0].pFuncDecl)->isGeneric() ) {
            implAddGenericFunction(scanner,(yyvsp[0].pFuncDecl));
        } else {
            if ( !yyextra->g_Program->addFunction((yyvsp[0].pFuncDecl)) ) {
                das2_yyerror(scanner,"function is already defined " +
                    (yyvsp[0].pFuncDecl)->getMangledName(),(yyvsp[0].pFuncDecl)->at,
                        CompilationError::already_declared_function);
            }
        }
        (yyvsp[0].pFuncDecl)->delRef();
    }
    break;

  case 296: /* optional_public_or_private_function: %empty  */
                        { (yyval.b) = yyextra->g_thisStructure ? !yyextra->g_thisStructure->privateStructure : yyextra->g_Program->thisModule->isPublic; }
    break;

  case 297: /* optional_public_or_private_function: "private"  */
                        { (yyval.b) = false; }
    break;

  case 298: /* optional_public_or_private_function: "public"  */
                        { (yyval.b) = true; }
    break;

  case 299: /* function_declaration_header: function_name optional_function_argument_list optional_function_type  */
                                                                                                {
        (yyval.pFuncDecl) = ast_functionDeclarationHeader(scanner,(yyvsp[-2].s),(yyvsp[-1].pVarDeclList),(yyvsp[0].pTypeDecl),tokAt(scanner,(yylsp[-2])));
    }
    break;

  case 300: /* $@16: %empty  */
                                                     {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeFunction(tak);
        }
    }
    break;

  case 301: /* function_declaration: optional_public_or_private_function $@16 function_declaration_header optional_emit_semis block_or_simple_block  */
                                                                                         {
        (yyvsp[-2].pFuncDecl)->body = (yyvsp[0].pExpression);
        (yyvsp[-2].pFuncDecl)->privateFunction = !(yyvsp[-4].b);
        (yyval.pFuncDecl) = (yyvsp[-2].pFuncDecl);
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterFunction((yyvsp[-2].pFuncDecl),tak);
        }
    }
    break;

  case 302: /* expression_block_finally: %empty  */
        {
        (yyval.pExpression) = nullptr;
    }
    break;

  case 303: /* $@17: %empty  */
                  {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 304: /* $@18: %empty  */
                             {
        yyextra->pop_nesteds();
    }
    break;

  case 305: /* expression_block_finally: "finally" $@17 '{' expressions $@18 '}'  */
          {
        (yyval.pExpression) = (yyvsp[-2].pExpression);
    }
    break;

  case 306: /* $@19: %empty  */
        {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 307: /* $@20: %empty  */
                                      {
        yyextra->pop_nesteds();
    }
    break;

  case 308: /* expression_block: $@19 '{' expressions $@20 '}' expression_block_finally  */
                                        {
        (yyval.pExpression) = (yyvsp[-3].pExpression);
        (yyval.pExpression)->at = tokRangeAt(scanner,(yylsp[-4]),(yylsp[0]));
        if ( (yyvsp[0].pExpression) ) {
            auto pF = (ExprBlock *) (yyvsp[0].pExpression);
            auto pB = (ExprBlock *) (yyval.pExpression);
            swap ( pB->finalList, pF->list );
            // gc_node — don't delete Expression
        }
    }
    break;

  case 309: /* expr_call_pipe_no_bracket: expr_call expr_full_block_assumed_piped  */
                                                           {
        if ( (yyvsp[-1].pExpression)->rtti_isCallLikeExpr() ) {
            auto pCall = (ExprLooksLikeCall *) (yyvsp[-1].pExpression);
            pCall->arguments.push_back((yyvsp[0].pExpression));
            pCall->pipedCallArgument = true;
            (yyval.pExpression) = (yyvsp[-1].pExpression);
        } else if ( (yyvsp[-1].pExpression)->rtti_isNamedCall() ) {
            // piped block on a named call: pad-aware resolution lands it on the block param
            auto nc = (ExprNamedCall *) (yyvsp[-1].pExpression);
            nc->nonNamedArguments.push_back((yyvsp[0].pExpression));
            nc->pipedCallArgument = true;
            (yyval.pExpression) = (yyvsp[-1].pExpression);
        } else {
            das2_yyerror(scanner,"piped block requires a function call",tokAt(scanner,(yylsp[0])),
                CompilationError::cant_pipe);
            (yyval.pExpression) = (yyvsp[-1].pExpression);
        }
    }
    break;

  case 310: /* expr_call_pipe_no_bracket: expr_method_call_no_bracket expr_full_block_assumed_piped  */
                                                                             {
        if ( (yyvsp[-1].pExpression)->rtti_isCallLikeExpr() ) {
            auto pCall = (ExprLooksLikeCall *) (yyvsp[-1].pExpression);
            pCall->arguments.push_back((yyvsp[0].pExpression));
            pCall->pipedCallArgument = true;
            (yyval.pExpression) = (yyvsp[-1].pExpression);
        } else if ( (yyvsp[-1].pExpression)->rtti_isNamedCall() ) {
            // piped block on a named call: pad-aware resolution lands it on the block param
            auto nc = (ExprNamedCall *) (yyvsp[-1].pExpression);
            nc->nonNamedArguments.push_back((yyvsp[0].pExpression));
            nc->pipedCallArgument = true;
            (yyval.pExpression) = (yyvsp[-1].pExpression);
        } else {
            das2_yyerror(scanner,"piped block requires a function call",tokAt(scanner,(yylsp[0])),
                CompilationError::cant_pipe);
            (yyval.pExpression) = (yyvsp[-1].pExpression);
        }
    }
    break;

  case 311: /* expr_call_pipe_no_bracket: expr_field_no_bracket expr_full_block_assumed_piped  */
                                                                       {
        if ( (yyvsp[-1].pExpression)->rtti_isCallLikeExpr() ) {
            auto pCall = (ExprLooksLikeCall *) (yyvsp[-1].pExpression);
            pCall->arguments.push_back((yyvsp[0].pExpression));
            pCall->pipedCallArgument = true;
            (yyval.pExpression) = (yyvsp[-1].pExpression);
        } else if ( (yyvsp[-1].pExpression)->rtti_isNamedCall() ) {
            // piped block on a named call: pad-aware resolution lands it on the block param
            auto nc = (ExprNamedCall *) (yyvsp[-1].pExpression);
            nc->nonNamedArguments.push_back((yyvsp[0].pExpression));
            nc->pipedCallArgument = true;
            (yyval.pExpression) = (yyvsp[-1].pExpression);
        } else {
            das2_yyerror(scanner,"piped block requires a function call",tokAt(scanner,(yylsp[0])),
                CompilationError::cant_pipe);
            (yyval.pExpression) = (yyvsp[-1].pExpression);
        }
    }
    break;

  case 312: /* expr_call_pipe_no_bracket: expr_named_call expr_full_block_assumed_piped  */
                                                                 {
        // free-function named call + piped block: pad-aware resolution lands it on the block param
        auto nc = (ExprNamedCall *) (yyvsp[-1].pExpression);
        nc->nonNamedArguments.push_back((yyvsp[0].pExpression));
        nc->pipedCallArgument = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 313: /* expression_any: SEMICOLON  */
                                                  { (yyval.pExpression) = nullptr; }
    break;

  case 314: /* expression_any: expr_assign_no_bracket SEMICOLON  */
                                                    { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 315: /* expression_any: expression_delete SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 316: /* expression_any: expression_let  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 317: /* expression_any: expression_while_loop  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 318: /* expression_any: expression_unsafe  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 319: /* expression_any: expression_with  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 320: /* expression_any: expression_with_alias SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 321: /* expression_any: expression_for_loop  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 322: /* expression_any: expression_break SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 323: /* expression_any: expression_continue SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 324: /* expression_any: expression_return SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 325: /* expression_any: expression_yield SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 326: /* expression_any: expression_if_then_else  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 327: /* expression_any: expression_if_then_else_oneliner  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 328: /* expression_any: expression_try_catch  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 329: /* expression_any: expression_label SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 330: /* expression_any: expression_goto SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 331: /* expression_any: "pass" SEMICOLON  */
                                                  { (yyval.pExpression) = nullptr; }
    break;

  case 332: /* $@21: %empty  */
                     {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 333: /* $@22: %empty  */
                         {
        yyextra->pop_nesteds();
    }
    break;

  case 334: /* expression_any: '{' $@21 expressions $@22 '}' expression_block_finally  */
                                        {
        (yyval.pExpression) = (yyvsp[-3].pExpression);
        (yyval.pExpression)->at = tokRangeAt(scanner,(yylsp[-5]),(yylsp[0]));
        if ( (yyvsp[0].pExpression) ) {
            auto pF = (ExprBlock *) (yyvsp[0].pExpression);
            auto pB = (ExprBlock *) (yyval.pExpression);
            swap ( pB->finalList, pF->list );
            // gc_node — don't delete Expression
        }
    }
    break;

  case 335: /* expressions: %empty  */
        {
        (yyval.pExpression) = new ExprBlock();
        (yyval.pExpression)->at = LineInfo(yyextra->g_FileAccessStack.back(),
            yylloc.first_column,yylloc.first_line,yylloc.last_column,yylloc.last_line);
    }
    break;

  case 336: /* expressions: expressions expression_any  */
                                                        {
        (yyval.pExpression) = (yyvsp[-1].pExpression);
        if ( (yyvsp[0].pExpression) ) {
            static_cast<ExprBlock*>((yyvsp[-1].pExpression))->list.push_back((yyvsp[0].pExpression));
        }
    }
    break;

  case 337: /* expressions: expressions error  */
                                 {
        (void)(yyvsp[-1].pExpression); /* gc_node — don't delete Expression */ (yyval.pExpression) = nullptr; YYABORT;
    }
    break;

  case 338: /* optional_expr_list: %empty  */
        { (yyval.pExpression) = nullptr; }
    break;

  case 339: /* optional_expr_list: expr_list optional_comma  */
                                            { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 340: /* optional_expr_map_tuple_list: %empty  */
        { (yyval.pExpression) = nullptr; }
    break;

  case 341: /* optional_expr_map_tuple_list: expr_map_tuple_list optional_comma  */
                                                      { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 342: /* type_declaration_no_options_list: type_declaration  */
                               {
        (yyval.pTypeDeclList) = new vector<Expression *>();
        (yyval.pTypeDeclList)->push_back(new ExprTypeDecl(tokAt(scanner,(yylsp[0])),(yyvsp[0].pTypeDecl)));
    }
    break;

  case 343: /* type_declaration_no_options_list: type_declaration_no_options_list c_or_s type_declaration  */
                                                                              {
        (yyval.pTypeDeclList) = (yyvsp[-2].pTypeDeclList);
        (yyval.pTypeDeclList)->push_back(new ExprTypeDecl(tokAt(scanner,(yylsp[0])),(yyvsp[0].pTypeDecl)));
    }
    break;

  case 344: /* name_in_namespace: "name"  */
                                               { (yyval.s) = (yyvsp[0].s); }
    break;

  case 345: /* name_in_namespace: "name" "::" "name"  */
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

  case 346: /* name_in_namespace: "::" "name"  */
                                               { *(yyvsp[0].s) = "::" + *(yyvsp[0].s); (yyval.s) = (yyvsp[0].s); }
    break;

  case 347: /* expression_delete: "delete" expr  */
                                      {
        (yyval.pExpression) = new ExprDelete(tokAt(scanner,(yylsp[-1])), (yyvsp[0].pExpression));
    }
    break;

  case 348: /* expression_delete: "delete" "explicit" expr  */
                                                   {
        auto delExpr = new ExprDelete(tokAt(scanner,(yylsp[-2])), (yyvsp[0].pExpression));
        delExpr->native = true;
        (yyval.pExpression) = delExpr;
    }
    break;

  case 349: /* $@23: %empty  */
           { yyextra->das_arrow_depth ++; }
    break;

  case 350: /* $@24: %empty  */
                                                                           { yyextra->das_arrow_depth --; }
    break;

  case 351: /* new_type_declaration: '<' $@23 type_declaration '>' $@24  */
                                                                                                            {
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 352: /* new_type_declaration: structure_type_declaration  */
                                               {
        (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl);
    }
    break;

  case 353: /* expr_new: "new" new_type_declaration  */
                                                       {
        (yyval.pExpression) = new ExprNew(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pTypeDecl),false);
    }
    break;

  case 354: /* expr_new: "new" new_type_declaration '(' use_initializer ')'  */
                                                                                     {
        (yyval.pExpression) = new ExprNew(tokAt(scanner,(yylsp[-4])),(yyvsp[-3].pTypeDecl),true);
        ((ExprNew *)(yyval.pExpression))->initializer = (yyvsp[-1].b);
    }
    break;

  case 355: /* expr_new: "new" new_type_declaration '(' expr_list ')'  */
                                                                                    {
        auto pNew = new ExprNew(tokAt(scanner,(yylsp[-4])),(yyvsp[-3].pTypeDecl),true);
        (yyval.pExpression) = parseFunctionArguments(pNew,(yyvsp[-1].pExpression));
    }
    break;

  case 356: /* expr_new: "new" new_type_declaration '(' make_struct_single ')'  */
                                                                                      {
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->at = tokAt(scanner,(yylsp[-3]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-3].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = true; // $init;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
        (yyval.pExpression) = new ExprAscend(tokAt(scanner,(yylsp[-4])),(yyvsp[-1].pExpression));
    }
    break;

  case 357: /* expr_new: "new" new_type_declaration '(' "uninitialized" make_struct_single ')'  */
                                                                                                        {
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->at = tokAt(scanner,(yylsp[-4]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-4].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = false; // $init;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
        (yyval.pExpression) = new ExprAscend(tokAt(scanner,(yylsp[-5])),(yyvsp[-1].pExpression));
    }
    break;

  case 358: /* expr_new: "new" make_decl  */
                                    {
        (yyval.pExpression) = new ExprAscend(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression));
    }
    break;

  case 359: /* expression_break: "break"  */
                       { (yyval.pExpression) = new ExprBreak(tokAt(scanner,(yylsp[0]))); }
    break;

  case 360: /* expression_continue: "continue"  */
                          { (yyval.pExpression) = new ExprContinue(tokAt(scanner,(yylsp[0]))); }
    break;

  case 361: /* expression_return: "return"  */
                        {
        (yyval.pExpression) = new ExprReturn(tokAt(scanner,(yylsp[0])),nullptr);
    }
    break;

  case 362: /* expression_return: "return" expr  */
                                      {
        (yyval.pExpression) = new ExprReturn(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression));
    }
    break;

  case 363: /* expression_return: "return" "<-" expr  */
                                             {
        auto pRet = new ExprReturn(tokAt(scanner,(yylsp[-2])),(yyvsp[0].pExpression));
        pRet->moveSemantics = true;
        (yyval.pExpression) = pRet;
    }
    break;

  case 364: /* expression_yield: "yield" expr  */
                                     {
        (yyval.pExpression) = new ExprYield(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression));
    }
    break;

  case 365: /* expression_yield: "yield" "<-" expr  */
                                            {
        auto pRet = new ExprYield(tokAt(scanner,(yylsp[-2])),(yyvsp[0].pExpression));
        pRet->moveSemantics = true;
        (yyval.pExpression) = pRet;
    }
    break;

  case 366: /* expression_try_catch: "try" expression_block "recover" expression_block  */
                                                                                       {
        (yyval.pExpression) = new ExprTryCatch(tokAt(scanner,(yylsp[-3])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
    }
    break;

  case 367: /* kwd_let_var_or_nothing: "let"  */
                 { (yyval.b) = true; }
    break;

  case 368: /* kwd_let_var_or_nothing: "var"  */
                 { (yyval.b) = false; }
    break;

  case 369: /* kwd_let_var_or_nothing: %empty  */
                    { (yyval.b) = true; }
    break;

  case 370: /* kwd_let: "let"  */
                 { (yyval.b) = true; }
    break;

  case 371: /* kwd_let: "var"  */
                 { (yyval.b) = false; }
    break;

  case 372: /* optional_in_scope: "inscope"  */
                    { (yyval.b) = true; }
    break;

  case 373: /* optional_in_scope: %empty  */
                     { (yyval.b) = false; }
    break;

  case 374: /* tuple_expansion: "name"  */
                    {
        (yyval.pNameList) = new vector<string>();
        (yyval.pNameList)->push_back(*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 375: /* tuple_expansion: tuple_expansion ',' "name"  */
                                             {
        (yyvsp[-2].pNameList)->push_back(*(yyvsp[0].s));
        delete (yyvsp[0].s);
        (yyval.pNameList) = (yyvsp[-2].pNameList);
    }
    break;

  case 376: /* tuple_expansion_variable_declaration: '(' tuple_expansion ')' ':' type_declaration_no_options copy_or_move_or_clone expr SEMICOLON  */
                                                                                                                                {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-6].pNameList),tokAt(scanner,(yylsp[-6])),(yyvsp[-3].pTypeDecl),(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
        (yyval.pVarDecl)->isTupleExpansion = true;
    }
    break;

  case 377: /* tuple_expansion_variable_declaration: '(' tuple_expansion ')' optional_ref copy_or_move_or_clone expr SEMICOLON  */
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

  case 378: /* expression_let: kwd_let optional_in_scope let_variable_declaration  */
                                                                 {
        (yyval.pExpression) = ast_Let(scanner,(yyvsp[-2].b),(yyvsp[-1].b),(yyvsp[0].pVarDecl),tokAt(scanner,(yylsp[-2])),tokAt(scanner,(yylsp[0])));
    }
    break;

  case 379: /* expression_let: kwd_let optional_in_scope tuple_expansion_variable_declaration  */
                                                                             {
        (yyval.pExpression) = ast_Let(scanner,(yyvsp[-2].b),(yyvsp[-1].b),(yyvsp[0].pVarDecl),tokAt(scanner,(yylsp[-2])),tokAt(scanner,(yylsp[0])));
    }
    break;

  case 380: /* expression_let: kwd_let optional_in_scope '{' variable_declaration_list '}'  */
                                                                               {
        (yyval.pExpression) = ast_LetList(scanner,(yyvsp[-4].b),(yyvsp[-3].b),*(yyvsp[-1].pVarDeclList),tokAt(scanner,(yylsp[-4])),tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 381: /* $@25: %empty  */
                          { yyextra->das_arrow_depth ++; }
    break;

  case 382: /* $@26: %empty  */
                                                                                                 { yyextra->das_arrow_depth --; }
    break;

  case 383: /* expr_cast: "cast" '<' $@25 type_declaration_no_options '>' $@26 expr_no_bracket  */
                                                                                                                                                           {
        (yyval.pExpression) = new ExprCast(tokAt(scanner,(yylsp[-6])),(yyvsp[0].pExpression),(yyvsp[-3].pTypeDecl));
    }
    break;

  case 384: /* $@27: %empty  */
                            { yyextra->das_arrow_depth ++; }
    break;

  case 385: /* $@28: %empty  */
                                                                                                   { yyextra->das_arrow_depth --; }
    break;

  case 386: /* expr_cast: "upcast" '<' $@27 type_declaration_no_options '>' $@28 expr_no_bracket  */
                                                                                                                                                             {
        auto pCast = new ExprCast(tokAt(scanner,(yylsp[-6])),(yyvsp[0].pExpression),(yyvsp[-3].pTypeDecl));
        pCast->upcast = true;
        (yyval.pExpression) = pCast;
    }
    break;

  case 387: /* $@29: %empty  */
                                 { yyextra->das_arrow_depth ++; }
    break;

  case 388: /* $@30: %empty  */
                                                                                                        { yyextra->das_arrow_depth --; }
    break;

  case 389: /* expr_cast: "reinterpret" '<' $@29 type_declaration_no_options '>' $@30 expr_no_bracket  */
                                                                                                                                                                  {
        auto pCast = new ExprCast(tokAt(scanner,(yylsp[-6])),(yyvsp[0].pExpression),(yyvsp[-3].pTypeDecl));
        pCast->reinterpret = true;
        (yyval.pExpression) = pCast;
    }
    break;

  case 390: /* $@31: %empty  */
                         { yyextra->das_arrow_depth ++; }
    break;

  case 391: /* $@32: %empty  */
                                                                                     { yyextra->das_arrow_depth --; }
    break;

  case 392: /* expr_type_decl: "type" '<' $@31 type_declaration '>' $@32  */
                                                                                                                      {
        (yyval.pExpression) = new ExprTypeDecl(tokAt(scanner,(yylsp[-5])),(yyvsp[-2].pTypeDecl));
    }
    break;

  case 393: /* expr_type_info: "typeinfo" name_in_namespace '(' expr ')'  */
                                                                          {
            if ( (yyvsp[-1].pExpression)->rtti_isTypeDecl() ) {
                auto ptd = (ExprTypeDecl *)(yyvsp[-1].pExpression);
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-4])),*(yyvsp[-3].s),ptd->typeexpr);
                // gc_node — don't delete Expression
            } else {
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-4])),*(yyvsp[-3].s),(yyvsp[-1].pExpression));
            }
            delete (yyvsp[-3].s);
    }
    break;

  case 394: /* expr_type_info: "typeinfo" name_in_namespace '<' "name" '>' '(' expr ')'  */
                                                                                                {
            if ( (yyvsp[-1].pExpression)->rtti_isTypeDecl() ) {
                auto ptd = (ExprTypeDecl *)(yyvsp[-1].pExpression);
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-7])),*(yyvsp[-6].s),ptd->typeexpr,*(yyvsp[-4].s));
                // gc_node — don't delete Expression
            } else {
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-7])),*(yyvsp[-6].s),(yyvsp[-1].pExpression),*(yyvsp[-4].s));
            }
            delete (yyvsp[-6].s);
            delete (yyvsp[-4].s);
    }
    break;

  case 395: /* expr_type_info: "typeinfo" name_in_namespace '<' "name" c_or_s "name" '>' '(' expr ')'  */
                                                                                                                        {
            if ( (yyvsp[-1].pExpression)->rtti_isTypeDecl() ) {
                auto ptd = (ExprTypeDecl *)(yyvsp[-1].pExpression);
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-9])),*(yyvsp[-8].s),ptd->typeexpr,*(yyvsp[-6].s),*(yyvsp[-4].s));
                // gc_node — don't delete Expression
            } else {
                (yyval.pExpression) = new ExprTypeInfo(tokAt(scanner,(yylsp[-9])),*(yyvsp[-8].s),(yyvsp[-1].pExpression),*(yyvsp[-6].s),*(yyvsp[-4].s));
            }
            delete (yyvsp[-8].s);
            delete (yyvsp[-6].s);
            delete (yyvsp[-4].s);
    }
    break;

  case 396: /* expr_list: expr  */
                      {
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 397: /* expr_list: "<-" expr  */
                             {
            (yyval.pExpression) = ast_makeMoveArgument(scanner, (yyvsp[0].pExpression), tokAt(scanner,(yylsp[0])));
    }
    break;

  case 398: /* expr_list: expr_list ',' expr  */
                                        {
            (yyval.pExpression) = new ExprSequence(tokAt(scanner,(yylsp[-2])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
    }
    break;

  case 399: /* expr_list: expr_list ',' "<-" expr  */
                                                   {
            (yyval.pExpression) = new ExprSequence(tokAt(scanner,(yylsp[-3])),(yyvsp[-3].pExpression),ast_makeMoveArgument(scanner, (yyvsp[0].pExpression), tokAt(scanner,(yylsp[0]))));
    }
    break;

  case 400: /* block_or_simple_block: expression_block  */
                                    { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 401: /* block_or_simple_block: "=>" expr_no_bracket  */
                                                   {
            auto retE = new ExprReturn(tokAt(scanner,(yylsp[-1])), (yyvsp[0].pExpression));
            auto blkE = new ExprBlock();
            blkE->at = tokAt(scanner,(yylsp[-1]));
            blkE->list.push_back(retE);
            (yyval.pExpression) = blkE;
    }
    break;

  case 402: /* block_or_simple_block: "=>" "<-" expr_no_bracket  */
                                                          {
            auto retE = new ExprReturn(tokAt(scanner,(yylsp[-2])), (yyvsp[0].pExpression));
            retE->moveSemantics = true;
            auto blkE = new ExprBlock();
            blkE->at = tokAt(scanner,(yylsp[-2]));
            blkE->list.push_back(retE);
            (yyval.pExpression) = blkE;
    }
    break;

  case 403: /* block_or_lambda: '$'  */
                { (yyval.i) = 0;   /* block */  }
    break;

  case 404: /* block_or_lambda: '@'  */
                { (yyval.i) = 1;   /* lambda */ }
    break;

  case 405: /* block_or_lambda: "@@"  */
                  { (yyval.i) = 2;   /* local function */ }
    break;

  case 406: /* capture_entry: '&' "name"  */
                                    { (yyval.pCapt) = new CaptureEntry(*(yyvsp[0].s),CaptureMode::capture_by_reference); delete (yyvsp[0].s); }
    break;

  case 407: /* capture_entry: '=' "name"  */
                                    { (yyval.pCapt) = new CaptureEntry(*(yyvsp[0].s),CaptureMode::capture_by_copy); delete (yyvsp[0].s); }
    break;

  case 408: /* capture_entry: "<-" "name"  */
                                    { (yyval.pCapt) = new CaptureEntry(*(yyvsp[0].s),CaptureMode::capture_by_move); delete (yyvsp[0].s); }
    break;

  case 409: /* capture_entry: ":=" "name"  */
                                    { (yyval.pCapt) = new CaptureEntry(*(yyvsp[0].s),CaptureMode::capture_by_clone); delete (yyvsp[0].s); }
    break;

  case 410: /* capture_entry: "name" '(' "name" ')'  */
                                    { (yyval.pCapt) = ast_makeCaptureEntry(scanner,tokAt(scanner,(yylsp[-3])),*(yyvsp[-3].s),*(yyvsp[-1].s)); delete (yyvsp[-3].s); delete (yyvsp[-1].s); }
    break;

  case 411: /* capture_list: capture_entry  */
                         {
        (yyval.pCaptList) = new vector<CaptureEntry>();
        (yyval.pCaptList)->push_back(*(yyvsp[0].pCapt));
        delete (yyvsp[0].pCapt);
    }
    break;

  case 412: /* capture_list: capture_list ',' capture_entry  */
                                               {
        (yyvsp[-2].pCaptList)->push_back(*(yyvsp[0].pCapt));
        delete (yyvsp[0].pCapt);
        (yyval.pCaptList) = (yyvsp[-2].pCaptList);
    }
    break;

  case 413: /* optional_capture_list: %empty  */
        { (yyval.pCaptList) = nullptr; }
    break;

  case 414: /* optional_capture_list: "capture" '(' capture_list ')'  */
                                             { (yyval.pCaptList) = (yyvsp[-1].pCaptList); }
    break;

  case 415: /* expr_full_block: block_or_lambda optional_annotation_list optional_capture_list optional_function_argument_list optional_function_type optional_emit_semis block_or_simple_block  */
                                                                                                                {
        (yyval.pExpression) = ast_makeBlock(scanner,(yyvsp[-6].i),(yyvsp[-5].faList),(yyvsp[-4].pCaptList),(yyvsp[-3].pVarDeclList),(yyvsp[-2].pTypeDecl),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[0])),tokAt(scanner,(yylsp[-5])),tokAt(scanner,(yylsp[-4])));
    }
    break;

  case 416: /* expr_full_block_assumed_piped: block_or_lambda optional_annotation_list optional_capture_list optional_function_argument_list optional_function_type optional_emit_semis block_or_simple_block  */
                                                                                                                {
        (yyval.pExpression) = ast_makeBlock(scanner,(yyvsp[-6].i),(yyvsp[-5].faList),(yyvsp[-4].pCaptList),(yyvsp[-3].pVarDeclList),(yyvsp[-2].pTypeDecl),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[0])),tokAt(scanner,(yylsp[-5])),tokAt(scanner,(yylsp[-4])));
    }
    break;

  case 417: /* expr_full_block_assumed_piped: '{' expressions '}'  */
                                   {
        (yyval.pExpression) = ast_makeBlock(scanner,0,nullptr,nullptr,nullptr,new TypeDecl(Type::autoinfer),(yyvsp[-1].pExpression),tokAt(scanner,(yylsp[-1])),tokAt(scanner,(yylsp[-1])),LineInfo());
    }
    break;

  case 418: /* expr_numeric_const: "integer constant"  */
                                              { (yyval.pExpression) = new ExprConstInt(tokAt(scanner,(yylsp[0])),(int32_t)(yyvsp[0].i)); }
    break;

  case 419: /* expr_numeric_const: "unsigned integer constant"  */
                                              { (yyval.pExpression) = new ExprConstUInt(tokAt(scanner,(yylsp[0])),(uint32_t)(yyvsp[0].ui)); }
    break;

  case 420: /* expr_numeric_const: "long integer constant"  */
                                              { (yyval.pExpression) = new ExprConstInt64(tokAt(scanner,(yylsp[0])),(int64_t)(yyvsp[0].i64)); }
    break;

  case 421: /* expr_numeric_const: "unsigned long integer constant"  */
                                              { (yyval.pExpression) = new ExprConstUInt64(tokAt(scanner,(yylsp[0])),(uint64_t)(yyvsp[0].ui64)); }
    break;

  case 422: /* expr_numeric_const: "unsigned int8 constant"  */
                                              { (yyval.pExpression) = new ExprConstUInt8(tokAt(scanner,(yylsp[0])),(uint8_t)(yyvsp[0].ui)); }
    break;

  case 423: /* expr_numeric_const: "floating point constant"  */
                                              { (yyval.pExpression) = new ExprConstFloat(tokAt(scanner,(yylsp[0])),(float)(yyvsp[0].fd)); }
    break;

  case 424: /* expr_numeric_const: "double constant"  */
                                              { (yyval.pExpression) = new ExprConstDouble(tokAt(scanner,(yylsp[0])),(double)(yyvsp[0].d)); }
    break;

  case 425: /* expr_assign_no_bracket: expr_no_bracket  */
                                                        { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 426: /* expr_assign_no_bracket: expr_no_bracket '=' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprCopy(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression)); }
    break;

  case 427: /* expr_assign_no_bracket: expr_no_bracket "<-" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprMove(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 428: /* expr_assign_no_bracket: expr_no_bracket "<-" make_table_decl  */
                                                                   { (yyval.pExpression) = new ExprMove(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 429: /* expr_assign_no_bracket: expr_no_bracket "<-" array_comprehension  */
                                                                     { (yyval.pExpression) = new ExprMove(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 430: /* expr_assign_no_bracket: expr_no_bracket ":=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprClone(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 431: /* expr_assign_no_bracket: expr_no_bracket "&=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"&=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 432: /* expr_assign_no_bracket: expr_no_bracket "|=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"|=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 433: /* expr_assign_no_bracket: expr_no_bracket "^=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"^=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 434: /* expr_assign_no_bracket: expr_no_bracket "&&=" expr_no_bracket  */
                                                                      { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"&&=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 435: /* expr_assign_no_bracket: expr_no_bracket "||=" expr_no_bracket  */
                                                                      { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"||=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 436: /* expr_assign_no_bracket: expr_no_bracket "^^=" expr_no_bracket  */
                                                                      { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"^^=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 437: /* expr_assign_no_bracket: expr_no_bracket "+=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"+=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 438: /* expr_assign_no_bracket: expr_no_bracket "-=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"-=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 439: /* expr_assign_no_bracket: expr_no_bracket "*=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"*=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 440: /* expr_assign_no_bracket: expr_no_bracket "/=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"/=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 441: /* expr_assign_no_bracket: expr_no_bracket "%=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"%=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 442: /* expr_assign_no_bracket: expr_no_bracket "<<=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<<=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 443: /* expr_assign_no_bracket: expr_no_bracket ">>=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">>=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 444: /* expr_assign_no_bracket: expr_no_bracket "<<<=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<<<=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 445: /* expr_assign_no_bracket: expr_no_bracket ">>>=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">>>=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 446: /* expr_named_call: name_in_namespace '(' '[' make_struct_fields ']' ')'  */
                                                                         {
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-5])),*(yyvsp[-5].s));
        nc->arguments = (yyvsp[-2].pMakeStruct);
        delete (yyvsp[-5].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 447: /* expr_named_call: name_in_namespace '(' expr_list ',' '[' make_struct_fields ']' ')'  */
                                                                                                  {
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-7])),*(yyvsp[-7].s));
        nc->nonNamedArguments = sequenceToList((yyvsp[-5].pExpression));
        nc->arguments = (yyvsp[-2].pMakeStruct);
        delete (yyvsp[-7].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 448: /* expr_named_call: name_in_namespace '(' expr_list ',' make_struct_fields ')'  */
                                                                                          {
        // bracket-less mixed named call: foo(pos..., name = value) -- named args are a strict suffix
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-5])),*(yyvsp[-5].s));
        nc->nonNamedArguments = sequenceToList((yyvsp[-3].pExpression));
        nc->arguments = (yyvsp[-1].pMakeStruct);
        delete (yyvsp[-5].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 449: /* expr_method_call_no_bracket: expr_no_bracket "->" "name" '(' ')'  */
                                                                    {
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-3])), (yyvsp[-4].pExpression), *(yyvsp[-2].s));
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-4]),(yyloc));
        delete (yyvsp[-2].s);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 450: /* expr_method_call_no_bracket: expr_no_bracket "->" "name" '(' expr_list ')'  */
                                                                                         {
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-4])), (yyvsp[-5].pExpression), *(yyvsp[-3].s));
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-5]),(yyloc));
        auto callArgs = sequenceToList((yyvsp[-1].pExpression));
        pInvoke->arguments.insert ( pInvoke->arguments.end(), callArgs.begin(), callArgs.end() );
        delete (yyvsp[-3].s);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 451: /* expr_method_call_no_bracket: expr_no_bracket "->" "name" '(' '[' make_struct_fields ']' ')'  */
                                                                                                     {
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-5])),*(yyvsp[-5].s));
        nc->methodCall = true;
        nc->arguments = (yyvsp[-2].pMakeStruct);
        nc->nonNamedArguments.push_back((yyvsp[-7].pExpression));
        delete (yyvsp[-5].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 452: /* expr_method_call_no_bracket: expr_no_bracket "->" "name" '(' expr_list ',' make_struct_fields ')'  */
                                                                                                                      {
        // bracket-less mixed named method call: a->m(pos..., name = value)
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-5])),*(yyvsp[-5].s));
        nc->methodCall = true;
        nc->arguments = (yyvsp[-1].pMakeStruct);
        nc->nonNamedArguments.push_back((yyvsp[-7].pExpression));
        auto callArgs = sequenceToList((yyvsp[-3].pExpression));
        nc->nonNamedArguments.insert ( nc->nonNamedArguments.end(), callArgs.begin(), callArgs.end() );
        delete (yyvsp[-5].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 453: /* expr_method_call_no_bracket: expr_no_bracket "->" "name" '(' make_struct_fields ')'  */
                                                                                             {
        // bracket-less all-named method call, no positional: a->m(name = value)
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-3])),*(yyvsp[-3].s));
        nc->methodCall = true;
        nc->arguments = (yyvsp[-1].pMakeStruct);
        nc->nonNamedArguments.push_back((yyvsp[-5].pExpression));
        delete (yyvsp[-3].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 454: /* func_addr_name: name_in_namespace  */
                                    {
        (yyval.pExpression) = new ExprAddr(tokAt(scanner,(yylsp[0])),*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 455: /* func_addr_name: "$i" '(' expr ')'  */
                                          {
        auto expr = new ExprAddr(tokAt(scanner,(yylsp[-3])),"``MACRO``TAG``ADDR``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression), expr, "i");
    }
    break;

  case 456: /* func_addr_expr: "@@" func_addr_name  */
                                            {
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 457: /* $@33: %empty  */
                      { yyextra->das_arrow_depth ++; }
    break;

  case 458: /* $@34: %empty  */
                                                                                                  { yyextra->das_arrow_depth --; }
    break;

  case 459: /* func_addr_expr: "@@" '<' $@33 type_declaration_no_options '>' $@34 func_addr_name  */
                                                                                                                                                         {
        auto expr = (ExprAddr *) ((yyvsp[0].pExpression)->rtti_isAddr() ? (yyvsp[0].pExpression) : (((ExprTag *) (yyvsp[0].pExpression))->value));
        expr->funcType = (yyvsp[-3].pTypeDecl);
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 460: /* $@35: %empty  */
                      { yyextra->das_arrow_depth ++; }
    break;

  case 461: /* $@36: %empty  */
                                                                                                                                { yyextra->das_arrow_depth --; }
    break;

  case 462: /* func_addr_expr: "@@" '<' $@35 optional_function_argument_list optional_function_type '>' $@36 func_addr_name  */
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

  case 463: /* expr_field_no_bracket: expr_no_bracket '.' "name"  */
                                                         {
        (yyval.pExpression) = new ExprField(tokAt(scanner,(yylsp[-1])), tokAt(scanner,(yylsp[0])), (yyvsp[-2].pExpression), *(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 464: /* expr_field_no_bracket: expr_no_bracket '.' '.' "name"  */
                                                             {
        (yyval.pExpression) = new ExprField(tokAt(scanner,(yylsp[-1])), tokAt(scanner,(yylsp[0])), (yyvsp[-3].pExpression), *(yyvsp[0].s), true);
        delete (yyvsp[0].s);
    }
    break;

  case 465: /* expr_field_no_bracket: expr_no_bracket '.' "name" '(' ')'  */
                                                                 {
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-3])), (yyvsp[-4].pExpression), *(yyvsp[-2].s));
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-4]),(yyloc));
        delete (yyvsp[-2].s);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 466: /* expr_field_no_bracket: expr_no_bracket '.' "name" '(' expr_list ')'  */
                                                                                      {
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-4])), (yyvsp[-5].pExpression), *(yyvsp[-3].s));
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-5]),(yyloc));
        auto callArgs = sequenceToList((yyvsp[-1].pExpression));
        pInvoke->arguments.insert ( pInvoke->arguments.end(), callArgs.begin(), callArgs.end() );
        delete (yyvsp[-3].s);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 467: /* expr_field_no_bracket: expr_no_bracket '.' "name" '(' '[' make_struct_fields ']' ')'  */
                                                                                                  {
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-5])),*(yyvsp[-5].s));
        nc->methodCall = true;
        nc->arguments = (yyvsp[-2].pMakeStruct);
        nc->nonNamedArguments.push_back((yyvsp[-7].pExpression));
        delete (yyvsp[-5].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 468: /* expr_field_no_bracket: expr_no_bracket '.' "name" '(' expr_list ',' make_struct_fields ')'  */
                                                                                                                   {
        // bracket-less mixed named method call: a.m(pos..., name = value)
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-5])),*(yyvsp[-5].s));
        nc->methodCall = true;
        nc->arguments = (yyvsp[-1].pMakeStruct);
        nc->nonNamedArguments.push_back((yyvsp[-7].pExpression));
        auto callArgs = sequenceToList((yyvsp[-3].pExpression));
        nc->nonNamedArguments.insert ( nc->nonNamedArguments.end(), callArgs.begin(), callArgs.end() );
        delete (yyvsp[-5].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 469: /* expr_field_no_bracket: expr_no_bracket '.' "name" '(' make_struct_fields ')'  */
                                                                                          {
        // bracket-less all-named method call, no positional: a.m(name = value)
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-3])),*(yyvsp[-3].s));
        nc->methodCall = true;
        nc->arguments = (yyvsp[-1].pMakeStruct);
        nc->nonNamedArguments.push_back((yyvsp[-5].pExpression));
        delete (yyvsp[-3].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 470: /* expr_field_no_bracket: expr_no_bracket '.' basic_type_declaration '(' ')'  */
                                                                                   {
        auto method_name = das_to_string((yyvsp[-2].type));
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-3])), (yyvsp[-4].pExpression), method_name);
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-4]),(yyloc));
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 471: /* expr_field_no_bracket: expr_no_bracket '.' basic_type_declaration '(' expr_list ')'  */
                                                                                                        {
        auto method_name = das_to_string((yyvsp[-3].type));
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-4])), (yyvsp[-5].pExpression), method_name);
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-5]),(yyloc));
        auto callArgs = sequenceToList((yyvsp[-1].pExpression));
        pInvoke->arguments.insert ( pInvoke->arguments.end(), callArgs.begin(), callArgs.end() );
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 472: /* $@37: %empty  */
                                          { yyextra->das_suppress_errors=true; }
    break;

  case 473: /* $@38: %empty  */
                                                                                       { yyextra->das_suppress_errors=false; }
    break;

  case 474: /* expr_field_no_bracket: expr_no_bracket '.' $@37 error $@38  */
                                                                                                                               {
        (yyval.pExpression) = new ExprField(tokAt(scanner,(yylsp[-3])), tokAt(scanner,(yylsp[-3])), (yyvsp[-4].pExpression), "");
        yyerrok;
    }
    break;

  case 475: /* expr_call: name_in_namespace '(' ')'  */
                                               {
            (yyval.pExpression) = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-2])),tokAt(scanner,(yylsp[0])),*(yyvsp[-2].s));
            delete (yyvsp[-2].s);
    }
    break;

  case 476: /* expr_call: name_in_namespace '(' "uninitialized" ')'  */
                                                          {
            auto dd = new ExprMakeStruct(tokAt(scanner,(yylsp[-3])));
            dd->at = tokAt(scanner,(yylsp[-3]));
            dd->makeType = yyextra->g_Program->makeTypeDeclaration(tokAt(scanner,(yylsp[-3])),*(yyvsp[-3].s));
            dd->useInitializer = false;
            dd->alwaysUseInitializer = true;
            delete (yyvsp[-3].s);
            (yyval.pExpression) = dd;
    }
    break;

  case 477: /* expr_call: name_in_namespace '(' make_struct_single ')'  */
                                                               {
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->at = tokAt(scanner,(yylsp[-3]));
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = yyextra->g_Program->makeTypeDeclaration(tokAt(scanner,(yylsp[-3])),*(yyvsp[-3].s));
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = true;
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
            delete (yyvsp[-3].s);
            (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 478: /* expr_call: name_in_namespace '(' "uninitialized" make_struct_single ')'  */
                                                                                 {
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->at = tokAt(scanner,(yylsp[-4]));
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = yyextra->g_Program->makeTypeDeclaration(tokAt(scanner,(yylsp[-4])),*(yyvsp[-4].s));
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = false;
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
            delete (yyvsp[-4].s);
            (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 479: /* expr_call: name_in_namespace '(' expr_list ')'  */
                                                                    {
            (yyval.pExpression) = parseFunctionArguments(yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-3])),tokAt(scanner,(yylsp[0])),*(yyvsp[-3].s)),(yyvsp[-1].pExpression));
            delete (yyvsp[-3].s);
    }
    break;

  case 480: /* expr_call: basic_type_declaration '(' ')'  */
                                                    {
        (yyval.pExpression) = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-2])),tokAt(scanner,(yylsp[0])),das_to_string((yyvsp[-2].type)));
    }
    break;

  case 481: /* expr_call: basic_type_declaration '(' expr_list ')'  */
                                                                         {
        (yyval.pExpression) = parseFunctionArguments(yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-3])),tokAt(scanner,(yylsp[0])),das_to_string((yyvsp[-3].type))),(yyvsp[-1].pExpression));
    }
    break;

  case 482: /* expr: expr_no_bracket  */
                                       { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 483: /* expr: make_table_decl  */
                                     { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 484: /* expr: array_comprehension  */
                                     { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 485: /* expr_no_bracket: "null"  */
                                              { (yyval.pExpression) = new ExprConstPtr(tokAt(scanner,(yylsp[0])),nullptr); }
    break;

  case 486: /* expr_no_bracket: name_in_namespace  */
                                              { (yyval.pExpression) = new ExprVar(tokAt(scanner,(yylsp[0])),*(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 487: /* expr_no_bracket: expr_numeric_const  */
                                              { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 488: /* expr_no_bracket: expr_reader  */
                                              { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 489: /* expr_no_bracket: string_builder  */
                                              { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 490: /* expr_no_bracket: make_decl_no_bracket  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 491: /* expr_no_bracket: "true"  */
                                              { (yyval.pExpression) = new ExprConstBool(tokAt(scanner,(yylsp[0])),true); }
    break;

  case 492: /* expr_no_bracket: "false"  */
                                              { (yyval.pExpression) = new ExprConstBool(tokAt(scanner,(yylsp[0])),false); }
    break;

  case 493: /* expr_no_bracket: expr_field_no_bracket  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 494: /* expr_no_bracket: expr_mtag_no_bracket  */
                                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 495: /* expr_no_bracket: '!' expr_no_bracket  */
                                                         { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"!",(yyvsp[0].pExpression)); }
    break;

  case 496: /* expr_no_bracket: '~' expr_no_bracket  */
                                                         { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"~",(yyvsp[0].pExpression)); }
    break;

  case 497: /* expr_no_bracket: '+' expr_no_bracket  */
                                                             { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"+",(yyvsp[0].pExpression)); }
    break;

  case 498: /* expr_no_bracket: '-' expr_no_bracket  */
                                                             { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"-",(yyvsp[0].pExpression)); }
    break;

  case 499: /* expr_no_bracket: expr_no_bracket "<<" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<<", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 500: /* expr_no_bracket: expr_no_bracket ">>" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">>", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 501: /* expr_no_bracket: expr_no_bracket "<<<" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<<<", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 502: /* expr_no_bracket: expr_no_bracket ">>>" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">>>", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 503: /* expr_no_bracket: expr_no_bracket '+' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"+", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 504: /* expr_no_bracket: expr_no_bracket '-' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"-", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 505: /* expr_no_bracket: expr_no_bracket '*' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"*", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 506: /* expr_no_bracket: expr_no_bracket '/' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"/", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 507: /* expr_no_bracket: expr_no_bracket '%' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"%", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 508: /* expr_no_bracket: expr_no_bracket '<' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 509: /* expr_no_bracket: expr_no_bracket '>' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 510: /* expr_no_bracket: expr_no_bracket "==" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"==", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 511: /* expr_no_bracket: expr_no_bracket "!=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"!=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 512: /* expr_no_bracket: expr_no_bracket "<=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 513: /* expr_no_bracket: expr_no_bracket ">=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 514: /* expr_no_bracket: expr_no_bracket '&' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"&", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 515: /* expr_no_bracket: expr_no_bracket '|' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"|", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 516: /* expr_no_bracket: expr_no_bracket '^' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"^", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 517: /* expr_no_bracket: expr_no_bracket "&&" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"&&", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 518: /* expr_no_bracket: expr_no_bracket "||" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"||", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 519: /* expr_no_bracket: expr_no_bracket "^^" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"^^", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 520: /* expr_no_bracket: expr_no_bracket ".." expr_no_bracket  */
                                                                   {
        auto itv = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-1])),"interval");
        itv->arguments.push_back((yyvsp[-2].pExpression));
        itv->arguments.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = itv;
    }
    break;

  case 521: /* expr_no_bracket: "++" expr_no_bracket  */
                                                            { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"++", (yyvsp[0].pExpression)); }
    break;

  case 522: /* expr_no_bracket: "--" expr_no_bracket  */
                                                            { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"--", (yyvsp[0].pExpression)); }
    break;

  case 523: /* expr_no_bracket: expr_no_bracket "++"  */
                                                            { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[0])),"+++", (yyvsp[-1].pExpression)); }
    break;

  case 524: /* expr_no_bracket: expr_no_bracket "--"  */
                                                            { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[0])),"---", (yyvsp[-1].pExpression)); }
    break;

  case 525: /* expr_no_bracket: '(' expr_list optional_comma ')'  */
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
                (yyval.pExpression) = (yyvsp[-2].pExpression);
            }
        }
    break;

  case 526: /* expr_no_bracket: '(' make_struct_single ')'  */
                                      {
        auto mkt = new ExprMakeTuple(tokAt(scanner,(yylsp[-1])));
        for ( auto & arg : *(((ExprMakeStruct *)(yyvsp[-1].pExpression))->structs.back()) ) {
            mkt->values.push_back(arg->value);
            mkt->recordNames.push_back(arg->name);
        }
        // gc_node — don't delete Expression
        (yyval.pExpression) = mkt;
    }
    break;

  case 527: /* expr_no_bracket: expr_no_bracket '[' expr ']'  */
                                                            { (yyval.pExpression) = new ExprAt(tokAt(scanner,(yylsp[-2])), (yyvsp[-3].pExpression), (yyvsp[-1].pExpression)); }
    break;

  case 528: /* expr_no_bracket: expr_no_bracket '.' '[' expr ']'  */
                                                                { (yyval.pExpression) = new ExprAt(tokAt(scanner,(yylsp[-2])), (yyvsp[-4].pExpression), (yyvsp[-1].pExpression), true); }
    break;

  case 529: /* expr_no_bracket: expr_no_bracket "?[" expr ']'  */
                                                            { (yyval.pExpression) = new ExprSafeAt(tokAt(scanner,(yylsp[-2])), (yyvsp[-3].pExpression), (yyvsp[-1].pExpression)); }
    break;

  case 530: /* expr_no_bracket: expr_no_bracket '.' "?[" expr ']'  */
                                                                { (yyval.pExpression) = new ExprSafeAt(tokAt(scanner,(yylsp[-2])), (yyvsp[-4].pExpression), (yyvsp[-1].pExpression), true); }
    break;

  case 531: /* expr_no_bracket: expr_no_bracket "?." "name"  */
                                                            { (yyval.pExpression) = new ExprSafeField(tokAt(scanner,(yylsp[-1])), tokAt(scanner,(yylsp[0])), (yyvsp[-2].pExpression), *(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 532: /* expr_no_bracket: expr_no_bracket '.' "?." "name"  */
                                                                { (yyval.pExpression) = new ExprSafeField(tokAt(scanner,(yylsp[-1])), tokAt(scanner,(yylsp[0])), (yyvsp[-3].pExpression), *(yyvsp[0].s), true); delete (yyvsp[0].s); }
    break;

  case 533: /* expr_no_bracket: func_addr_expr  */
                                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 534: /* expr_no_bracket: expr_call  */
                        { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 535: /* expr_no_bracket: '*' expr_no_bracket  */
                                                              { (yyval.pExpression) = new ExprPtr2Ref(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression)); }
    break;

  case 536: /* expr_no_bracket: "deref" '(' expr ')'  */
                                                   { (yyval.pExpression) = new ExprPtr2Ref(tokAt(scanner,(yylsp[-3])),(yyvsp[-1].pExpression)); }
    break;

  case 537: /* expr_no_bracket: "addr" '(' expr ')'  */
                                                   { (yyval.pExpression) = new ExprRef2Ptr(tokAt(scanner,(yylsp[-3])),(yyvsp[-1].pExpression)); }
    break;

  case 538: /* expr_no_bracket: expr_generator  */
                                                   { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 539: /* expr_no_bracket: expr_no_bracket "??" expr_no_bracket  */
                                                                         { (yyval.pExpression) = new ExprNullCoalescing(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression)); }
    break;

  case 540: /* expr_no_bracket: expr_no_bracket '?' expr_no_bracket ':' expr_no_bracket  */
                                                                                           {
            (yyval.pExpression) = new ExprOp3(tokAt(scanner,(yylsp[-3])),"?",(yyvsp[-4].pExpression),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
        }
    break;

  case 541: /* $@39: %empty  */
                                                          { yyextra->das_arrow_depth ++; }
    break;

  case 542: /* $@40: %empty  */
                                                                                                                                 { yyextra->das_arrow_depth --; }
    break;

  case 543: /* expr_no_bracket: expr_no_bracket "is" "type" '<' $@39 type_declaration_no_options '>' $@40  */
                                                                                                                                                                  {
        (yyval.pExpression) = new ExprIs(tokAt(scanner,(yylsp[-6])),(yyvsp[-7].pExpression),(yyvsp[-2].pTypeDecl));
    }
    break;

  case 544: /* expr_no_bracket: expr_no_bracket "is" basic_type_declaration  */
                                                                          {
        auto vdecl = new TypeDecl((yyvsp[0].type));
        vdecl->at = tokAt(scanner,(yylsp[0]));
        (yyval.pExpression) = new ExprIs(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),vdecl);
    }
    break;

  case 545: /* expr_no_bracket: expr_no_bracket "is" "name"  */
                                                         {
        (yyval.pExpression) = new ExprIsVariant(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 546: /* expr_no_bracket: expr_no_bracket "as" "name"  */
                                                         {
        (yyval.pExpression) = new ExprAsVariant(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 547: /* $@41: %empty  */
                                                          { yyextra->das_arrow_depth ++; }
    break;

  case 548: /* $@42: %empty  */
                                                                                                                      { yyextra->das_arrow_depth --; }
    break;

  case 549: /* expr_no_bracket: expr_no_bracket "as" "type" '<' $@41 type_declaration '>' $@42  */
                                                                                                                                                       {
        auto vname = (yyvsp[-2].pTypeDecl)->describe();
        (yyval.pExpression) = new ExprAsVariant(tokAt(scanner,(yylsp[-6])),(yyvsp[-7].pExpression),vname);
        delete (yyvsp[-2].pTypeDecl);
    }
    break;

  case 550: /* expr_no_bracket: expr_no_bracket "as" basic_type_declaration  */
                                                                          {
        (yyval.pExpression) = new ExprAsVariant(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),das_to_string((yyvsp[0].type)));
    }
    break;

  case 551: /* expr_no_bracket: expr_no_bracket '?' "as" "name"  */
                                                             {
        (yyval.pExpression) = new ExprSafeAsVariant(tokAt(scanner,(yylsp[-1])),(yyvsp[-3].pExpression),*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 552: /* $@43: %empty  */
                                                              { yyextra->das_arrow_depth ++; }
    break;

  case 553: /* $@44: %empty  */
                                                                                                                          { yyextra->das_arrow_depth --; }
    break;

  case 554: /* expr_no_bracket: expr_no_bracket '?' "as" "type" '<' $@43 type_declaration '>' $@44  */
                                                                                                                                                           {
        auto vname = (yyvsp[-2].pTypeDecl)->describe();
        (yyval.pExpression) = new ExprSafeAsVariant(tokAt(scanner,(yylsp[-6])),(yyvsp[-8].pExpression),vname);
        delete (yyvsp[-2].pTypeDecl);
    }
    break;

  case 555: /* expr_no_bracket: expr_no_bracket '?' "as" basic_type_declaration  */
                                                                              {
        (yyval.pExpression) = new ExprSafeAsVariant(tokAt(scanner,(yylsp[-1])),(yyvsp[-3].pExpression),das_to_string((yyvsp[0].type)));
    }
    break;

  case 556: /* expr_no_bracket: expr_type_info  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 557: /* expr_no_bracket: expr_type_decl  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 558: /* expr_no_bracket: expr_cast  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 559: /* expr_no_bracket: expr_new  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 560: /* expr_no_bracket: expr_method_call_no_bracket  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 561: /* expr_no_bracket: expr_named_call  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 562: /* expr_no_bracket: expr_full_block  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 563: /* expr_no_bracket: expr_no_bracket "<|" expr_no_bracket  */
                                                                      { (yyval.pExpression) = ast_lpipe(scanner,(yyvsp[-2].pExpression),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[-1])),true); }
    break;

  case 564: /* expr_no_bracket: expr_no_bracket "|>" expr_no_bracket  */
                                                                      { (yyval.pExpression) = ast_rpipe(scanner,(yyvsp[-2].pExpression),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[-1]))); }
    break;

  case 565: /* expr_no_bracket: expr_no_bracket "|>" basic_type_declaration  */
                                                                     {
        auto fncall = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[0])),tokAt(scanner,(yylsp[0])),das_to_string((yyvsp[0].type)));
        (yyval.pExpression) = ast_rpipe(scanner,(yyvsp[-2].pExpression),fncall,tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 566: /* expr_no_bracket: expr_call_pipe_no_bracket  */
                                        { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 567: /* expr_no_bracket: "unsafe" '(' expr ')'  */
                                         {
            (yyvsp[-1].pExpression)->alwaysSafe = true;
            (yyvsp[-1].pExpression)->userSaidItsSafe = true;
            (yyval.pExpression) = (yyvsp[-1].pExpression);
        }
    break;

  case 568: /* expr_no_bracket: expr_no_bracket "=>" expr_no_bracket  */
                                                               {
        ExprMakeTuple * mt = new ExprMakeTuple(tokAt(scanner,(yylsp[-1])));
        mt->values.push_back((yyvsp[-2].pExpression));
        mt->values.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = mt;
    }
    break;

  case 569: /* expr_no_bracket: expr_no_bracket "=>" make_table_decl  */
                                                               {
        ExprMakeTuple * mt = new ExprMakeTuple(tokAt(scanner,(yylsp[-1])));
        mt->values.push_back((yyvsp[-2].pExpression));
        mt->values.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = mt;
    }
    break;

  case 570: /* expr_no_bracket: expr_no_bracket "=>" array_comprehension  */
                                                                   {
        ExprMakeTuple * mt = new ExprMakeTuple(tokAt(scanner,(yylsp[-1])));
        mt->values.push_back((yyvsp[-2].pExpression));
        mt->values.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = mt;
    }
    break;

  case 571: /* expr_generator: "generator" '<' type_declaration_no_options '>' optional_capture_list '(' ')'  */
                                                                                                              {
        (yyval.pExpression) = ast_makeGenerator(scanner,(yyvsp[-4].pTypeDecl),(yyvsp[-2].pCaptList),nullptr,tokAt(scanner,(yylsp[-6])),tokAt(scanner,(yylsp[-2])));
    }
    break;

  case 572: /* expr_generator: "generator" '<' type_declaration_no_options '>' optional_capture_list '(' expr ')'  */
                                                                                                                            {
        (yyval.pExpression) = ast_makeGenerator(scanner,(yyvsp[-5].pTypeDecl),(yyvsp[-3].pCaptList),(yyvsp[-1].pExpression),tokAt(scanner,(yylsp[-7])),tokAt(scanner,(yylsp[-3])));
    }
    break;

  case 573: /* expr_generator: "generator" '<' type_declaration_no_options '>' optional_capture_list optional_emit_semis expression_block  */
                                                                                                                                                  {
        auto closure = new ExprMakeBlock(tokAt(scanner,(yylsp[0])),(yyvsp[0].pExpression));
        ((ExprBlock *)(yyvsp[0].pExpression))->returnType = new TypeDecl(Type::autoinfer);
        (yyval.pExpression) = ast_makeGenerator(scanner,(yyvsp[-4].pTypeDecl),(yyvsp[-2].pCaptList),closure,tokAt(scanner,(yylsp[-6])),tokAt(scanner,(yylsp[-2])));
    }
    break;

  case 574: /* expr_mtag_no_bracket: "$$" '(' expr ')'  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"e"); }
    break;

  case 575: /* expr_mtag_no_bracket: "$i" '(' expr ')'  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"i"); }
    break;

  case 576: /* expr_mtag_no_bracket: "$v" '(' expr ')'  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"v"); }
    break;

  case 577: /* expr_mtag_no_bracket: "$b" '(' expr ')'  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"b"); }
    break;

  case 578: /* expr_mtag_no_bracket: "$a" '(' expr ')'  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"a"); }
    break;

  case 579: /* expr_mtag_no_bracket: "..."  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[0])),nullptr,"..."); }
    break;

  case 580: /* expr_mtag_no_bracket: "$c" '(' expr ')' '(' ')'  */
                                                            {
            auto ccall = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-5])),tokAt(scanner,(yylsp[0])),"``MACRO``TAG``CALL``");
            (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-5])),(yyvsp[-3].pExpression),ccall,"c");
        }
    break;

  case 581: /* expr_mtag_no_bracket: "$c" '(' expr ')' '(' expr_list ')'  */
                                                                                {
            auto ccall = parseFunctionArguments(yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-6])),tokAt(scanner,(yylsp[0])),"``MACRO``TAG``CALL``"),(yyvsp[-1].pExpression));
            (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-6])),(yyvsp[-4].pExpression),ccall,"c");
        }
    break;

  case 582: /* expr_mtag_no_bracket: expr_no_bracket '.' "$f" '(' expr ')'  */
                                                                           {
        auto cfield = new ExprField(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-1])), (yyvsp[-5].pExpression), "``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 583: /* expr_mtag_no_bracket: expr_no_bracket "?." "$f" '(' expr ')'  */
                                                                            {
        auto cfield = new ExprSafeField(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-1])), (yyvsp[-5].pExpression), "``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 584: /* expr_mtag_no_bracket: expr_no_bracket '.' '.' "$f" '(' expr ')'  */
                                                                               {
        auto cfield = new ExprField(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-1])), (yyvsp[-6].pExpression), "``MACRO``TAG``FIELD``", true);
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 585: /* expr_mtag_no_bracket: expr_no_bracket '.' "?." "$f" '(' expr ')'  */
                                                                                {
        auto cfield = new ExprSafeField(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-1])), (yyvsp[-6].pExpression), "``MACRO``TAG``FIELD``", true);
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 586: /* expr_mtag_no_bracket: expr_no_bracket "as" "$f" '(' expr ')'  */
                                                                              {
        auto cfield = new ExprAsVariant(tokAt(scanner,(yylsp[-4])),(yyvsp[-5].pExpression),"``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 587: /* expr_mtag_no_bracket: expr_no_bracket '?' "as" "$f" '(' expr ')'  */
                                                                                  {
        auto cfield = new ExprSafeAsVariant(tokAt(scanner,(yylsp[-4])),(yyvsp[-6].pExpression),"``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 588: /* expr_mtag_no_bracket: expr_no_bracket "is" "$f" '(' expr ')'  */
                                                                              {
        auto cfield = new ExprIsVariant(tokAt(scanner,(yylsp[-4])),(yyvsp[-5].pExpression),"``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 589: /* expr_mtag_no_bracket: "@@" "$c" '(' expr ')'  */
                                                           {
        auto ccall = new ExprAddr(tokAt(scanner,(yylsp[-4])),"``MACRO``TAG``ADDR``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-3])),(yyvsp[-1].pExpression),ccall,"c");
    }
    break;

  case 590: /* optional_field_annotation: %empty  */
                                      { (yyval.aaList) = nullptr; }
    break;

  case 591: /* optional_field_annotation: metadata_argument_list  */
                                      { (yyval.aaList) = (yyvsp[0].aaList); }
    break;

  case 592: /* optional_override: %empty  */
                      { (yyval.i) = OVERRIDE_NONE; }
    break;

  case 593: /* optional_override: "override"  */
                      { (yyval.i) = OVERRIDE_OVERRIDE; }
    break;

  case 594: /* optional_override: "sealed"  */
                      { (yyval.i) = OVERRIDE_SEALED; }
    break;

  case 595: /* optional_constant: %empty  */
                        { (yyval.b) = false; }
    break;

  case 596: /* optional_constant: "const"  */
                        { (yyval.b) = true; }
    break;

  case 597: /* optional_public_or_private_member_variable: %empty  */
                        { (yyval.b) = false; }
    break;

  case 598: /* optional_public_or_private_member_variable: "public"  */
                        { (yyval.b) = false; }
    break;

  case 599: /* optional_public_or_private_member_variable: "private"  */
                        { (yyval.b) = true; }
    break;

  case 600: /* optional_static_member_variable: %empty  */
                        { (yyval.b) = false; }
    break;

  case 601: /* optional_static_member_variable: "static"  */
                        { (yyval.b) = true; }
    break;

  case 602: /* structure_variable_declaration: optional_field_annotation optional_static_member_variable optional_override optional_public_or_private_member_variable variable_declaration  */
                                                                                                                                                                                      {
        (yyvsp[0].pVarDecl)->override = (yyvsp[-2].i) == OVERRIDE_OVERRIDE;
        (yyvsp[0].pVarDecl)->sealed = (yyvsp[-2].i) == OVERRIDE_SEALED;
        (yyvsp[0].pVarDecl)->annotation = (yyvsp[-4].aaList);
        (yyvsp[0].pVarDecl)->isPrivate = (yyvsp[-1].b);
        (yyvsp[0].pVarDecl)->isStatic = (yyvsp[-3].b);
        (yyval.pVarDecl) = (yyvsp[0].pVarDecl);
    }
    break;

  case 603: /* struct_variable_declaration_list: %empty  */
        {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 604: /* struct_variable_declaration_list: struct_variable_declaration_list "new line, semicolon"  */
                                                                 { (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList); }
    break;

  case 605: /* struct_variable_declaration_list: struct_variable_declaration_list "typedef" "name" '=' type_declaration SEMICOLON  */
                                                                                                                {
        (yyval.pVarDeclList) = (yyvsp[-5].pVarDeclList);
        ast_structureAlias(scanner,(yyvsp[-3].s),(yyvsp[-1].pTypeDecl),tokAt(scanner,(yylsp[-4])));
    }
    break;

  case 606: /* $@45: %empty  */
                                               {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeStructureFields(tak);
        }
    }
    break;

  case 607: /* struct_variable_declaration_list: struct_variable_declaration_list $@45 structure_variable_declaration SEMICOLON  */
                                                     {
        (yyval.pVarDeclList) = (yyvsp[-3].pVarDeclList);
        if ( (yyvsp[-1].pVarDecl) ) (yyvsp[-3].pVarDeclList)->push_back((yyvsp[-1].pVarDecl));
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) {
                for ( const auto & nl : *((yyvsp[-1].pVarDecl)->pNameList) ) {
                    crd->afterStructureField(nl.name.c_str(), nl.at);
                }
            }
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterStructureFields(tak);
        }
    }
    break;

  case 608: /* $@46: %empty  */
                                                                                                                     {
                if ( !yyextra->g_CommentReaders.empty() ) {
                    auto tak = tokAt(scanner,(yylsp[-2]));
                    for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeFunction(tak);
                }
            }
    break;

  case 609: /* struct_variable_declaration_list: struct_variable_declaration_list optional_annotation_list_with_emit_semis "def" optional_public_or_private_member_variable "abstract" optional_constant $@46 function_declaration_header SEMICOLON  */
                                                          {
                if ( !yyextra->g_CommentReaders.empty() ) {
                    auto tak = tokAt(scanner,(yylsp[-1]));
                    for ( auto & crd : yyextra->g_CommentReaders ) crd->afterFunction((yyvsp[-1].pFuncDecl),tak);
                }
                (yyvsp[-1].pFuncDecl)->isTemplate = yyextra->g_thisStructure ? yyextra->g_thisStructure->isTemplate : false;
                (yyval.pVarDeclList) = ast_structVarDefAbstract(scanner,(yyvsp[-8].pVarDeclList),(yyvsp[-7].faList),(yyvsp[-5].b),(yyvsp[-3].b), (yyvsp[-1].pFuncDecl));
            }
    break;

  case 610: /* $@47: %empty  */
                                                                                                                                                                         {
                if ( !yyextra->g_CommentReaders.empty() ) {
                    auto tak = tokAt(scanner,(yylsp[0]));
                    for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeFunction(tak);
                }
            }
    break;

  case 611: /* struct_variable_declaration_list: struct_variable_declaration_list optional_annotation_list_with_emit_semis "def" optional_public_or_private_member_variable optional_static_member_variable optional_override optional_constant $@47 function_declaration_header optional_emit_semis block_or_simple_block  */
                                                                                                 {
                if ( !yyextra->g_CommentReaders.empty() ) {
                    auto tak = tokAt(scanner,(yylsp[0]));
                    for ( auto & crd : yyextra->g_CommentReaders ) crd->afterFunction((yyvsp[-2].pFuncDecl),tak);
                }
                (yyvsp[-2].pFuncDecl)->isTemplate = yyextra->g_thisStructure ? yyextra->g_thisStructure->isTemplate : false;
                (yyval.pVarDeclList) = ast_structVarDef(scanner,(yyvsp[-10].pVarDeclList),(yyvsp[-9].faList),(yyvsp[-6].b),(yyvsp[-7].b),(yyvsp[-5].i),(yyvsp[-4].b),(yyvsp[-2].pFuncDecl),(yyvsp[0].pExpression),tokRangeAt(scanner,(yylsp[-8]),(yylsp[0])),tokAt(scanner,(yylsp[-9])));
            }
    break;

  case 612: /* function_argument_declaration_no_type: optional_field_annotation kwd_let_var_or_nothing variable_declaration_no_type  */
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

  case 613: /* function_argument_declaration_type: optional_field_annotation kwd_let_var_or_nothing variable_declaration_type  */
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

  case 614: /* function_argument_declaration_type: "$a" '(' expr ')'  */
                                     {
            auto na = new vector<VariableNameAndPosition>();
            na->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1]))));
            auto decl = new VariableDeclaration(na, new TypeDecl(Type::none), (yyvsp[-1].pExpression));
            decl->pTypeDecl->isTag = true;
            (yyval.pVarDecl) = decl;
        }
    break;

  case 615: /* function_argument_list: function_argument_declaration_no_type  */
                                                                                      { (yyval.pVarDeclList) = new vector<VariableDeclaration*>(); (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 616: /* function_argument_list: function_argument_declaration_type  */
                                                                                      { (yyval.pVarDeclList) = new vector<VariableDeclaration*>(); (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 617: /* function_argument_list: function_argument_declaration_no_type ';' function_argument_list  */
                                                                                      { (yyval.pVarDeclList) = (yyvsp[0].pVarDeclList); (yyvsp[0].pVarDeclList)->insert((yyvsp[0].pVarDeclList)->begin(),(yyvsp[-2].pVarDecl)); }
    break;

  case 618: /* function_argument_list: function_argument_declaration_type ';' function_argument_list  */
                                                                                      { (yyval.pVarDeclList) = (yyvsp[0].pVarDeclList); (yyvsp[0].pVarDeclList)->insert((yyvsp[0].pVarDeclList)->begin(),(yyvsp[-2].pVarDecl)); }
    break;

  case 619: /* function_argument_list: function_argument_declaration_type ',' function_argument_list  */
                                                                                      { (yyval.pVarDeclList) = (yyvsp[0].pVarDeclList); (yyvsp[0].pVarDeclList)->insert((yyvsp[0].pVarDeclList)->begin(),(yyvsp[-2].pVarDecl)); }
    break;

  case 620: /* tuple_type: type_declaration  */
                                    {
        (yyval.pVarDecl) = new VariableDeclaration(nullptr,(yyvsp[0].pTypeDecl),nullptr);
    }
    break;

  case 621: /* tuple_type: "name" ':' type_declaration  */
                                                   {
        auto na = new vector<VariableNameAndPosition>();
        na->push_back(VariableNameAndPosition(*(yyvsp[-2].s),"",tokAt(scanner,(yylsp[-2]))));
        (yyval.pVarDecl) = new VariableDeclaration(na,(yyvsp[0].pTypeDecl),nullptr);
        delete (yyvsp[-2].s);
    }
    break;

  case 622: /* tuple_type_list: tuple_type  */
                                                       { (yyval.pVarDeclList) = new vector<VariableDeclaration*>(); (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 623: /* tuple_type_list: tuple_type_list c_or_s tuple_type  */
                                                       { (yyval.pVarDeclList) = (yyvsp[-2].pVarDeclList); (yyvsp[-2].pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 624: /* tuple_alias_type_list: %empty  */
      {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 625: /* tuple_alias_type_list: tuple_type  */
                       {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
        (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl));
    }
    break;

  case 626: /* tuple_alias_type_list: tuple_alias_type_list semis tuple_type  */
                                                         {
        (yyval.pVarDeclList) = (yyvsp[-2].pVarDeclList); (yyvsp[-2].pVarDeclList)->push_back((yyvsp[0].pVarDecl));
        if ( !yyextra->g_CommentReaders.empty() ) {
            for ( auto & crd : yyextra->g_CommentReaders ) {
                for ( const auto & nl : *((yyvsp[0].pVarDecl)->pNameList) ) {
                    crd->afterTupleEntry(nl.name.c_str(), nl.at);
                }
            }
        }
    }
    break;

  case 627: /* variant_type: "name" ':' type_declaration  */
                                                   {
        auto na = new vector<VariableNameAndPosition>();
        na->push_back(VariableNameAndPosition(*(yyvsp[-2].s),"",tokAt(scanner,(yylsp[-2]))));
        (yyval.pVarDecl) = new VariableDeclaration(na,(yyvsp[0].pTypeDecl),nullptr);
        delete (yyvsp[-2].s);
    }
    break;

  case 628: /* variant_type_list: variant_type  */
                                                         { (yyval.pVarDeclList) = new vector<VariableDeclaration*>(); (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 629: /* variant_type_list: variant_type_list c_or_s variant_type  */
                                                            { (yyval.pVarDeclList) = (yyvsp[-2].pVarDeclList); (yyvsp[-2].pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 630: /* variant_alias_type_list: %empty  */
        {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 631: /* variant_alias_type_list: variant_type  */
                         {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
        (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl));
    }
    break;

  case 632: /* variant_alias_type_list: variant_alias_type_list semis variant_type  */
                                                               {
        (yyval.pVarDeclList) = (yyvsp[-2].pVarDeclList); (yyvsp[-2].pVarDeclList)->push_back((yyvsp[0].pVarDecl));
        if ( !yyextra->g_CommentReaders.empty() ) {
            for ( auto & crd : yyextra->g_CommentReaders ) {
                for ( const auto & nl : *((yyvsp[0].pVarDecl)->pNameList) ) {
                    crd->afterVariantEntry(nl.name.c_str(), nl.at);
                }
            }
        }
    }
    break;

  case 633: /* copy_or_move: '='  */
                    { (yyval.b) = false; }
    break;

  case 634: /* copy_or_move: "<-"  */
                    { (yyval.b) = true; }
    break;

  case 635: /* variable_declaration_no_type: variable_name_with_pos_list  */
                                          {
        auto autoT = new TypeDecl(Type::autoinfer);
        autoT->at = tokAt(scanner,(yylsp[0]));
        autoT->ref = false;
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[0].pNameWithPosList),autoT,nullptr);
    }
    break;

  case 636: /* variable_declaration_no_type: variable_name_with_pos_list '&'  */
                                              {
        auto autoT = new TypeDecl(Type::autoinfer);
        autoT->at = tokAt(scanner,(yylsp[-1]));
        autoT->ref = true;
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-1].pNameWithPosList),autoT,nullptr);
    }
    break;

  case 637: /* variable_declaration_no_type: variable_name_with_pos_list copy_or_move expr  */
                                                                       {
        auto typeDecl = new TypeDecl(Type::autoinfer);
        typeDecl->at = tokAt(scanner,(yylsp[-2]));
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-2].pNameWithPosList),typeDecl,(yyvsp[0].pExpression));
        (yyval.pVarDecl)->init_via_move = (yyvsp[-1].b);
    }
    break;

  case 638: /* variable_declaration_type: variable_name_with_pos_list ':' type_declaration  */
                                                                          {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-2].pNameWithPosList),(yyvsp[0].pTypeDecl),nullptr);
    }
    break;

  case 639: /* variable_declaration_type: variable_name_with_pos_list ':' type_declaration copy_or_move expr  */
                                                                                                      {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-4].pNameWithPosList),(yyvsp[-2].pTypeDecl),(yyvsp[0].pExpression));
        (yyval.pVarDecl)->init_via_move = (yyvsp[-1].b);
    }
    break;

  case 640: /* variable_declaration: variable_declaration_type  */
                                        {
        (yyval.pVarDecl) = (yyvsp[0].pVarDecl);
    }
    break;

  case 641: /* variable_declaration: variable_declaration_no_type  */
                                           {
        (yyval.pVarDecl) = (yyvsp[0].pVarDecl);
    }
    break;

  case 642: /* copy_or_move_or_clone: '='  */
                    { (yyval.i) = CorM_COPY; }
    break;

  case 643: /* copy_or_move_or_clone: "<-"  */
                    { (yyval.i) = CorM_MOVE; }
    break;

  case 644: /* copy_or_move_or_clone: ":="  */
                    { (yyval.i) = CorM_CLONE; }
    break;

  case 645: /* optional_ref: %empty  */
            { (yyval.b) = false; }
    break;

  case 646: /* optional_ref: '&'  */
            { (yyval.b) = true; }
    break;

  case 647: /* let_variable_name_with_pos_list: "name"  */
                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = pSL;
        delete (yyvsp[0].s);
    }
    break;

  case 648: /* let_variable_name_with_pos_list: "$i" '(' expr ')'  */
                                     {
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = pSL;
    }
    break;

  case 649: /* let_variable_name_with_pos_list: "name" "aka" "name"  */
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

  case 650: /* let_variable_name_with_pos_list: let_variable_name_with_pos_list ',' "name"  */
                                                             {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = (yyvsp[-2].pNameWithPosList);
        delete (yyvsp[0].s);
    }
    break;

  case 651: /* let_variable_name_with_pos_list: let_variable_name_with_pos_list ',' "$i" '(' expr ')'  */
                                                                               {
        (yyvsp[-5].pNameWithPosList)->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = (yyvsp[-5].pNameWithPosList);
    }
    break;

  case 652: /* let_variable_name_with_pos_list: let_variable_name_with_pos_list ',' "name" "aka" "name"  */
                                                                                   {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-4].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[-2].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-2]))));
        (yyval.pNameWithPosList) = (yyvsp[-4].pNameWithPosList);
        delete (yyvsp[-2].s);
        delete (yyvsp[0].s);
    }
    break;

  case 653: /* global_let_variable_name_with_pos_list: "name"  */
                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = pSL;
        delete (yyvsp[0].s);
    }
    break;

  case 654: /* global_let_variable_name_with_pos_list: global_let_variable_name_with_pos_list ',' "name"  */
                                                                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = (yyvsp[-2].pNameWithPosList);
        delete (yyvsp[0].s);
    }
    break;

  case 655: /* variable_declaration_list: %empty  */
        {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 656: /* variable_declaration_list: variable_declaration_list SEMICOLON  */
                                                  {
        (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList);
    }
    break;

  case 657: /* variable_declaration_list: variable_declaration_list let_variable_declaration  */
                                                                       {
        (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList);
        (yyvsp[-1].pVarDeclList)->push_back((yyvsp[0].pVarDecl));
    }
    break;

  case 658: /* let_variable_declaration: let_variable_name_with_pos_list ':' type_declaration_no_options SEMICOLON  */
                                                                                                  {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-3].pNameWithPosList),(yyvsp[-1].pTypeDecl),nullptr);
    }
    break;

  case 659: /* let_variable_declaration: let_variable_name_with_pos_list ':' type_declaration_no_options copy_or_move_or_clone expr SEMICOLON  */
                                                                                                                                        {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-5].pNameWithPosList),(yyvsp[-3].pTypeDecl),(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
    }
    break;

  case 660: /* let_variable_declaration: let_variable_name_with_pos_list optional_ref copy_or_move_or_clone expr SEMICOLON  */
                                                                                                                {
        auto typeDecl = new TypeDecl(Type::autoinfer);
        typeDecl->at = tokAt(scanner,(yylsp[-4]));
        typeDecl->ref = (yyvsp[-3].b);
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-4].pNameWithPosList),typeDecl,(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
    }
    break;

  case 661: /* global_let_variable_declaration: global_let_variable_name_with_pos_list ':' type_declaration_no_options SEMICOLON  */
                                                                                                         {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-3].pNameWithPosList),(yyvsp[-1].pTypeDecl),nullptr);
    }
    break;

  case 662: /* global_let_variable_declaration: global_let_variable_name_with_pos_list ':' type_declaration_no_options copy_or_move_or_clone expr SEMICOLON  */
                                                                                                                                               {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-5].pNameWithPosList),(yyvsp[-3].pTypeDecl),(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
    }
    break;

  case 663: /* global_let_variable_declaration: global_let_variable_name_with_pos_list optional_ref copy_or_move_or_clone expr SEMICOLON  */
                                                                                                                       {
        auto typeDecl = new TypeDecl(Type::autoinfer);
        typeDecl->at = tokAt(scanner,(yylsp[-4]));
        typeDecl->ref = (yyvsp[-3].b);
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-4].pNameWithPosList),typeDecl,(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
    }
    break;

  case 664: /* optional_shared: %empty  */
                     { (yyval.b) = false; }
    break;

  case 665: /* optional_shared: "shared"  */
                     { (yyval.b) = true; }
    break;

  case 666: /* optional_public_or_private_variable: %empty  */
                     { (yyval.b) = yyextra->g_Program->thisModule->isPublic; }
    break;

  case 667: /* optional_public_or_private_variable: "private"  */
                     { (yyval.b) = false; }
    break;

  case 668: /* optional_public_or_private_variable: "public"  */
                     { (yyval.b) = true; }
    break;

  case 669: /* global_variable_declaration_list: %empty  */
        {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 670: /* global_variable_declaration_list: global_variable_declaration_list SEMICOLON  */
                                                         {
        (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList);
    }
    break;

  case 671: /* $@48: %empty  */
                                               {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeGlobalVariables(tak);
        }
    }
    break;

  case 672: /* global_variable_declaration_list: global_variable_declaration_list $@48 optional_field_annotation let_variable_declaration  */
                                                                      {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders )
                for ( auto & nl : *((yyvsp[0].pVarDecl)->pNameList) )
                    crd->afterGlobalVariable(nl.name.c_str(),tak);
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterGlobalVariables(tak);
        }
        (yyval.pVarDeclList) = (yyvsp[-3].pVarDeclList);
        (yyvsp[0].pVarDecl)->annotation = (yyvsp[-1].aaList);
        (yyvsp[-3].pVarDeclList)->push_back((yyvsp[0].pVarDecl));
    }
    break;

  case 673: /* global_let: kwd_let optional_shared optional_public_or_private_variable '{' global_variable_declaration_list '}'  */
                                                                                                                                       {
        ast_globalLetList(scanner,(yyvsp[-5].b),(yyvsp[-4].b),(yyvsp[-3].b),(yyvsp[-1].pVarDeclList));
    }
    break;

  case 674: /* $@49: %empty  */
                                                                                        {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeGlobalVariables(tak);
        }
    }
    break;

  case 675: /* global_let: kwd_let optional_shared optional_public_or_private_variable $@49 optional_field_annotation global_let_variable_declaration  */
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

  case 676: /* enum_expression: "name"  */
                   {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyval.pEnumPair) = new EnumPair((yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        delete (yyvsp[0].s);
    }
    break;

  case 677: /* enum_expression: "name" '=' expr  */
                                   {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        (yyval.pEnumPair) = new EnumPair((yyvsp[-2].s),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[-2])));
        delete (yyvsp[-2].s);
    }
    break;

  case 680: /* enum_list: %empty  */
        {
        (yyval.pEnumList) = new Enumeration();
    }
    break;

  case 681: /* enum_list: enum_expression  */
                            {
        (yyval.pEnumList) = new Enumeration();
        if ( !(yyval.pEnumList)->add((yyvsp[0].pEnumPair)->name,(yyvsp[0].pEnumPair)->expr,(yyvsp[0].pEnumPair)->at) ) {
            das2_yyerror(scanner,"enumeration already declared " + (yyvsp[0].pEnumPair)->name, (yyvsp[0].pEnumPair)->at,
                CompilationError::already_declared_enumerator);
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            for ( auto & crd : yyextra->g_CommentReaders ) {
                crd->afterEnumerationEntry((yyvsp[0].pEnumPair)->name.c_str(), (yyvsp[0].pEnumPair)->at);
            }
        }
        delete (yyvsp[0].pEnumPair);
    }
    break;

  case 682: /* enum_list: enum_list commas enum_expression  */
                                                 {
        if ( !(yyvsp[-2].pEnumList)->add((yyvsp[0].pEnumPair)->name,(yyvsp[0].pEnumPair)->expr,(yyvsp[0].pEnumPair)->at) ) {
            das2_yyerror(scanner,"enumeration already declared " + (yyvsp[0].pEnumPair)->name, (yyvsp[0].pEnumPair)->at,
                CompilationError::already_declared_enumerator);
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            for ( auto & crd : yyextra->g_CommentReaders ) {
                crd->afterEnumerationEntry((yyvsp[0].pEnumPair)->name.c_str(), (yyvsp[0].pEnumPair)->at);
            }
        }
        delete (yyvsp[0].pEnumPair);
        (yyval.pEnumList) = (yyvsp[-2].pEnumList);
    }
    break;

  case 683: /* optional_public_or_private_alias: %empty  */
                     { (yyval.b) = yyextra->g_Program->thisModule->isPublic; }
    break;

  case 684: /* optional_public_or_private_alias: "private"  */
                     { (yyval.b) = false; }
    break;

  case 685: /* optional_public_or_private_alias: "public"  */
                     { (yyval.b) = true; }
    break;

  case 686: /* $@50: %empty  */
                                                         {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto pubename = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeAlias(pubename);
        }
    }
    break;

  case 687: /* single_alias: optional_public_or_private_alias "name" $@50 '=' type_declaration  */
                                  {
        das_checkName(scanner,*(yyvsp[-3].s),tokAt(scanner,(yylsp[-3])));
        (yyvsp[0].pTypeDecl)->isPrivateAlias = !(yyvsp[-4].b);
        if ( (yyvsp[0].pTypeDecl)->baseType == Type::alias ) {
            das2_yyerror(scanner,"alias cannot be defined in terms of another alias "+*(yyvsp[-3].s),tokAt(scanner,(yylsp[-3])),
                CompilationError::invalid_type_alias);
        }
        (yyvsp[0].pTypeDecl)->alias = *(yyvsp[-3].s);
        if ( !yyextra->g_Program->addAlias((yyvsp[0].pTypeDecl)) ) {
            das2_yyerror(scanner,"type alias is already defined "+*(yyvsp[-3].s),tokAt(scanner,(yylsp[-3])),
                CompilationError::already_declared_type_alias);
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto pubename = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterAlias((yyvsp[-3].s)->c_str(),pubename);
        }
        delete (yyvsp[-3].s);
    }
    break;

  case 689: /* optional_public_or_private_enum: %empty  */
                     { (yyval.b) = yyextra->g_Program->thisModule->isPublic; }
    break;

  case 690: /* optional_public_or_private_enum: "private"  */
                     { (yyval.b) = false; }
    break;

  case 691: /* optional_public_or_private_enum: "public"  */
                     { (yyval.b) = true; }
    break;

  case 692: /* enum_name: "name"  */
                   {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto pubename = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeEnumeration(pubename);
        }
        (yyval.pEnum) = ast_addEmptyEnum(scanner, (yyvsp[0].s), tokAt(scanner,(yylsp[0])));
    }
    break;

  case 693: /* optional_enum_basic_type_declaration: %empty  */
        {
        (yyval.type) = Type::tInt;
    }
    break;

  case 694: /* optional_enum_basic_type_declaration: ':' enum_basic_type_declaration  */
                                              {
        (yyval.type) = (yyvsp[0].type);
    }
    break;

  case 701: /* $@51: %empty  */
                                                                     {
        yyextra->push_nesteds(DAS_EMIT_COMMA);
    }
    break;

  case 702: /* $@52: %empty  */
                                                                                                                                {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeEnumerationEntries(tak);
        }
    }
    break;

  case 703: /* $@53: %empty  */
                                    {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterEnumerationEntries(tak);
        }
        yyextra->pop_nesteds();
    }
    break;

  case 704: /* enum_declaration: optional_annotation_list_with_emit_semis "enum" $@51 optional_public_or_private_enum enum_name optional_enum_basic_type_declaration optional_emit_commas '{' $@52 enum_list optional_commas $@53 '}'  */
          {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto pubename = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterEnumeration((yyvsp[-8].pEnum)->name.c_str(),pubename);
        }
        ast_enumDeclaration(scanner,(yyvsp[-12].faList),tokAt(scanner,(yylsp[-12])),(yyvsp[-9].b),(yyvsp[-8].pEnum),(yyvsp[-3].pEnumList),(yyvsp[-7].type));
    }
    break;

  case 705: /* optional_structure_parent: %empty  */
                                        { (yyval.s) = nullptr; }
    break;

  case 706: /* optional_structure_parent: ':' name_in_namespace  */
                                        { (yyval.s) = (yyvsp[0].s); }
    break;

  case 707: /* optional_sealed: %empty  */
                        { (yyval.b) = false; }
    break;

  case 708: /* optional_sealed: "sealed"  */
                        { (yyval.b) = true; }
    break;

  case 709: /* structure_name: optional_sealed "name" optional_structure_parent  */
                                                                           {
        (yyval.pStructure) = ast_structureName(scanner,(yyvsp[-2].b),(yyvsp[-1].s),tokAt(scanner,(yylsp[-1])),(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
    }
    break;

  case 710: /* class_or_struct: "class"  */
                    { (yyval.i) = CorS_Class; }
    break;

  case 711: /* class_or_struct: "struct"  */
                    { (yyval.i) = CorS_Struct; }
    break;

  case 712: /* class_or_struct: "class" "template"  */
                                  { (yyval.i) = CorS_ClassTemplate; }
    break;

  case 713: /* class_or_struct: "struct" "template"  */
                                  { (yyval.i) = CorS_StructTemplate; }
    break;

  case 714: /* optional_public_or_private_structure: %empty  */
                     { (yyval.b) = yyextra->g_Program->thisModule->isPublic; }
    break;

  case 715: /* optional_public_or_private_structure: "private"  */
                     { (yyval.b) = false; }
    break;

  case 716: /* optional_public_or_private_structure: "public"  */
                     { (yyval.b) = true; }
    break;

  case 717: /* optional_struct_variable_declaration_list: ';'  */
            {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 718: /* optional_struct_variable_declaration_list: '{' struct_variable_declaration_list '}'  */
                                                       {
        (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList);
    }
    break;

  case 719: /* $@54: %empty  */
                                                     {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 720: /* $@55: %empty  */
                                                                         {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeStructure(tak);
        }
    }
    break;

  case 721: /* $@56: %empty  */
                                             {
        if ( (yyvsp[-1].pStructure) ) {
            (yyvsp[-1].pStructure)->isClass = (yyvsp[-4].i)==CorS_Class || (yyvsp[-4].i)==CorS_ClassTemplate;
            (yyvsp[-1].pStructure)->isTemplate = (yyvsp[-4].i)==CorS_ClassTemplate || (yyvsp[-4].i)==CorS_StructTemplate;
            (yyvsp[-1].pStructure)->privateStructure = !(yyvsp[-3].b);
        }
    }
    break;

  case 722: /* structure_declaration: optional_annotation_list_with_emit_semis $@54 class_or_struct optional_public_or_private_structure $@55 structure_name optional_emit_semis $@56 optional_struct_variable_declaration_list  */
                                                      {
        yyextra->pop_nesteds();
        if ( (yyvsp[-3].pStructure) ) {
            ast_structureDeclaration ( scanner, (yyvsp[-8].faList), tokAt(scanner,(yylsp[-6])), (yyvsp[-3].pStructure), tokAt(scanner,(yylsp[-3])), (yyvsp[0].pVarDeclList) );
            if ( !yyextra->g_CommentReaders.empty() ) {
                auto tak = tokAt(scanner,(yylsp[-6]));
                for ( auto & crd : yyextra->g_CommentReaders ) crd->afterStructure((yyvsp[-3].pStructure),tak);
            }
        } else {
            deleteVariableDeclarationList((yyvsp[0].pVarDeclList));
        }
    }
    break;

  case 723: /* variable_name_with_pos_list: "name"  */
                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = pSL;
        delete (yyvsp[0].s);
    }
    break;

  case 724: /* variable_name_with_pos_list: "$i" '(' expr ')'  */
                                     {
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = pSL;
    }
    break;

  case 725: /* variable_name_with_pos_list: "name" "aka" "name"  */
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

  case 726: /* variable_name_with_pos_list: variable_name_with_pos_list ',' "name"  */
                                                         {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = (yyvsp[-2].pNameWithPosList);
        delete (yyvsp[0].s);
    }
    break;

  case 727: /* variable_name_with_pos_list: variable_name_with_pos_list ',' "$i" '(' expr ')'  */
                                                                           {
        (yyvsp[-5].pNameWithPosList)->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = (yyvsp[-5].pNameWithPosList);
    }
    break;

  case 728: /* variable_name_with_pos_list: variable_name_with_pos_list ',' "name" "aka" "name"  */
                                                                               {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-4].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[-2].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-2]))));
        (yyval.pNameWithPosList) = (yyvsp[-4].pNameWithPosList);
        delete (yyvsp[-2].s);
        delete (yyvsp[0].s);
    }
    break;

  case 729: /* basic_type_declaration: "bool"  */
                        { (yyval.type) = Type::tBool; }
    break;

  case 730: /* basic_type_declaration: "string"  */
                        { (yyval.type) = Type::tString; }
    break;

  case 731: /* basic_type_declaration: "int"  */
                        { (yyval.type) = Type::tInt; }
    break;

  case 732: /* basic_type_declaration: "int8"  */
                        { (yyval.type) = Type::tInt8; }
    break;

  case 733: /* basic_type_declaration: "int16"  */
                        { (yyval.type) = Type::tInt16; }
    break;

  case 734: /* basic_type_declaration: "int64"  */
                        { (yyval.type) = Type::tInt64; }
    break;

  case 735: /* basic_type_declaration: "int2"  */
                        { (yyval.type) = Type::tInt2; }
    break;

  case 736: /* basic_type_declaration: "int3"  */
                        { (yyval.type) = Type::tInt3; }
    break;

  case 737: /* basic_type_declaration: "int4"  */
                        { (yyval.type) = Type::tInt4; }
    break;

  case 738: /* basic_type_declaration: "uint"  */
                        { (yyval.type) = Type::tUInt; }
    break;

  case 739: /* basic_type_declaration: "uint8"  */
                        { (yyval.type) = Type::tUInt8; }
    break;

  case 740: /* basic_type_declaration: "uint16"  */
                        { (yyval.type) = Type::tUInt16; }
    break;

  case 741: /* basic_type_declaration: "uint64"  */
                        { (yyval.type) = Type::tUInt64; }
    break;

  case 742: /* basic_type_declaration: "uint2"  */
                        { (yyval.type) = Type::tUInt2; }
    break;

  case 743: /* basic_type_declaration: "uint3"  */
                        { (yyval.type) = Type::tUInt3; }
    break;

  case 744: /* basic_type_declaration: "uint4"  */
                        { (yyval.type) = Type::tUInt4; }
    break;

  case 745: /* basic_type_declaration: "float"  */
                        { (yyval.type) = Type::tFloat; }
    break;

  case 746: /* basic_type_declaration: "float2"  */
                        { (yyval.type) = Type::tFloat2; }
    break;

  case 747: /* basic_type_declaration: "float3"  */
                        { (yyval.type) = Type::tFloat3; }
    break;

  case 748: /* basic_type_declaration: "float4"  */
                        { (yyval.type) = Type::tFloat4; }
    break;

  case 749: /* basic_type_declaration: "void"  */
                        { (yyval.type) = Type::tVoid; }
    break;

  case 750: /* basic_type_declaration: "range"  */
                        { (yyval.type) = Type::tRange; }
    break;

  case 751: /* basic_type_declaration: "urange"  */
                        { (yyval.type) = Type::tURange; }
    break;

  case 752: /* basic_type_declaration: "range64"  */
                        { (yyval.type) = Type::tRange64; }
    break;

  case 753: /* basic_type_declaration: "urange64"  */
                        { (yyval.type) = Type::tURange64; }
    break;

  case 754: /* basic_type_declaration: "double"  */
                        { (yyval.type) = Type::tDouble; }
    break;

  case 755: /* basic_type_declaration: "bitfield"  */
                        { (yyval.type) = Type::tBitfield; }
    break;

  case 756: /* enum_basic_type_declaration: "int"  */
                        { (yyval.type) = Type::tInt; }
    break;

  case 757: /* enum_basic_type_declaration: "int8"  */
                        { (yyval.type) = Type::tInt8; }
    break;

  case 758: /* enum_basic_type_declaration: "int16"  */
                        { (yyval.type) = Type::tInt16; }
    break;

  case 759: /* enum_basic_type_declaration: "uint"  */
                        { (yyval.type) = Type::tUInt; }
    break;

  case 760: /* enum_basic_type_declaration: "uint8"  */
                        { (yyval.type) = Type::tUInt8; }
    break;

  case 761: /* enum_basic_type_declaration: "uint16"  */
                        { (yyval.type) = Type::tUInt16; }
    break;

  case 762: /* enum_basic_type_declaration: "int64"  */
                        { (yyval.type) = Type::tInt64; }
    break;

  case 763: /* enum_basic_type_declaration: "uint64"  */
                        { (yyval.type) = Type::tUInt64; }
    break;

  case 764: /* structure_type_declaration: name_in_namespace  */
                                 {
        (yyval.pTypeDecl) = yyextra->g_Program->makeTypeDeclaration(tokAt(scanner,(yylsp[0])),*(yyvsp[0].s));
        if ( !(yyval.pTypeDecl) ) {
            (yyval.pTypeDecl) = new TypeDecl(Type::tVoid);
            (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
        }
        delete (yyvsp[0].s);
    }
    break;

  case 765: /* auto_type_declaration: "auto"  */
                       {
        (yyval.pTypeDecl) = new TypeDecl(Type::autoinfer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 766: /* auto_type_declaration: "auto" '(' "name" ')'  */
                                            {
        das_checkName(scanner,*(yyvsp[-1].s),tokAt(scanner,(yylsp[-1])));
        (yyval.pTypeDecl) = new TypeDecl(Type::autoinfer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-3]));
        (yyval.pTypeDecl)->alias = *(yyvsp[-1].s);
        delete (yyvsp[-1].s);
    }
    break;

  case 767: /* auto_type_declaration: "$t" '(' expr ')'  */
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

  case 768: /* bitfield_bits: "name"  */
                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<string>();
        pSL->push_back(*(yyvsp[0].s));
        (yyval.pNameList) = pSL;
        delete (yyvsp[0].s);
    }
    break;

  case 769: /* bitfield_bits: bitfield_bits ';' "name"  */
                                           {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameList)->push_back(*(yyvsp[0].s));
        (yyval.pNameList) = (yyvsp[-2].pNameList);
        delete (yyvsp[0].s);
    }
    break;

  case 770: /* bitfield_bits: bitfield_bits ',' "name"  */
                                           {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameList)->push_back(*(yyvsp[0].s));
        (yyval.pNameList) = (yyvsp[-2].pNameList);
        delete (yyvsp[0].s);
    }
    break;

  case 771: /* bitfield_alias_bits: %empty  */
        {
        auto pSL = new vector<tuple<string,Expression *>>();
        (yyval.pNameExprList) = pSL;

    }
    break;

  case 772: /* bitfield_alias_bits: "name"  */
                   {
        (yyval.pNameExprList) = new vector<tuple<string,Expression *>>();
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyval.pNameExprList)->emplace_back(*(yyvsp[0].s),nullptr);
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterBitfieldEntry((yyvsp[0].s)->c_str(),atvname);
        }
        delete (yyvsp[0].s);
    }
    break;

  case 773: /* bitfield_alias_bits: "name" '=' expr  */
                                   {
        (yyval.pNameExprList) = new vector<tuple<string,Expression *>>();
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        (yyval.pNameExprList)->emplace_back(*(yyvsp[-2].s),(yyvsp[0].pExpression));
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-2]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterBitfieldEntry((yyvsp[-2].s)->c_str(),atvname);
        }
        delete (yyvsp[-2].s);
    }
    break;

  case 774: /* bitfield_alias_bits: bitfield_alias_bits commas "name"  */
                                                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameExprList)->emplace_back(*(yyvsp[0].s),nullptr);
        (yyval.pNameExprList) = (yyvsp[-2].pNameExprList);
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterBitfieldEntry((yyvsp[0].s)->c_str(),atvname);
        }
        delete (yyvsp[0].s);
    }
    break;

  case 775: /* bitfield_alias_bits: bitfield_alias_bits commas "name" '=' expr  */
                                                                    {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        (yyvsp[-4].pNameExprList)->emplace_back(*(yyvsp[-2].s),(yyvsp[0].pExpression));
        (yyval.pNameExprList) = (yyvsp[-4].pNameExprList);
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-2]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterBitfieldEntry((yyvsp[-2].s)->c_str(),atvname);
        }
        delete (yyvsp[-2].s);
    }
    break;

  case 776: /* bitfield_basic_type_declaration: %empty  */
                             { (yyval.type) = Type::tBitfield; }
    break;

  case 777: /* bitfield_basic_type_declaration: ':' "uint8"  */
                             { (yyval.type) = Type::tBitfield8; }
    break;

  case 778: /* bitfield_basic_type_declaration: ':' "uint16"  */
                             { (yyval.type) = Type::tBitfield16; }
    break;

  case 779: /* bitfield_basic_type_declaration: ':' "uint"  */
                             { (yyval.type) = Type::tBitfield; }
    break;

  case 780: /* bitfield_basic_type_declaration: ':' "uint64"  */
                             { (yyval.type) = Type::tBitfield64; }
    break;

  case 781: /* bitfield_type_declaration: "bitfield" bitfield_basic_type_declaration '<' '>'  */
                                                                          {
            (yyval.pTypeDecl) = new TypeDecl((yyvsp[-2].type));
            (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-2]));
    }
    break;

  case 782: /* $@57: %empty  */
                                                                     { yyextra->das_arrow_depth ++; }
    break;

  case 783: /* $@58: %empty  */
                                                                                                                            { yyextra->das_arrow_depth --; }
    break;

  case 784: /* bitfield_type_declaration: "bitfield" bitfield_basic_type_declaration '<' $@57 bitfield_bits '>' $@58  */
                                                                                                                                                             {
            (yyval.pTypeDecl) = new TypeDecl((yyvsp[-5].type));
            (yyval.pTypeDecl)->argNames = *(yyvsp[-2].pNameList);
            auto maxBits = (yyval.pTypeDecl)->maxBitfieldBits();
            if ( (yyval.pTypeDecl)->argNames.size()>maxBits ) {
                das_yyerror(scanner,"only " + to_string(maxBits) + " different bits are allowed in a bitfield",tokAt(scanner,(yylsp[-5])),
                    CompilationError::exceeds_bitfield);
            }
            (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
            delete (yyvsp[-2].pNameList);
    }
    break;

  case 787: /* table_type_pair: type_declaration  */
                                      {
        (yyval.aTypePair).firstType = (yyvsp[0].pTypeDecl);
        (yyval.aTypePair).secondType = new TypeDecl(Type::tVoid);
    }
    break;

  case 788: /* table_type_pair: type_declaration c_or_s type_declaration  */
                                                                             {
        (yyval.aTypePair).firstType = (yyvsp[-2].pTypeDecl);
        (yyval.aTypePair).secondType = (yyvsp[0].pTypeDecl);
    }
    break;

  case 789: /* dim_list: '[' expr ']'  */
                             {
        (yyval.pTypeDecl) = appendDimExpr(nullptr, (yyvsp[-1].pExpression), tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 790: /* dim_list: '[' ']'  */
                {
        (yyval.pTypeDecl) = appendDimExpr(nullptr, nullptr, tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 791: /* dim_list: dim_list '[' expr ']'  */
                                            {
        (yyval.pTypeDecl) = appendDimExpr((yyvsp[-3].pTypeDecl), (yyvsp[-1].pExpression), tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 792: /* dim_list: dim_list '[' ']'  */
                              {
        (yyval.pTypeDecl) = appendDimExpr((yyvsp[-2].pTypeDecl), nullptr, tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 793: /* type_declaration_no_options: type_declaration_no_options_no_dim  */
                                                     {
        (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl);
    }
    break;

  case 794: /* type_declaration_no_options: type_declaration_no_options_no_dim dim_list  */
                                                                       {
        if ( (yyvsp[-1].pTypeDecl)->baseType==Type::typeDecl ) {
            das2_yyerror(scanner,"type declaration can`t be used as array base type",tokAt(scanner,(yylsp[-1])),
                CompilationError::invalid_array_type);
        } else if ( (yyvsp[-1].pTypeDecl)->baseType==Type::typeMacro ) {
            das2_yyerror(scanner,"macro can`t be used as array base type",tokAt(scanner,(yylsp[-1])),
                CompilationError::invalid_array_type);
        }
        (yyval.pTypeDecl) = attachDimChain((yyvsp[0].pTypeDecl), (yyvsp[-1].pTypeDecl));
    }
    break;

  case 795: /* optional_expr_list_in_braces: %empty  */
            { (yyval.pExpression) = nullptr; }
    break;

  case 796: /* optional_expr_list_in_braces: '(' expr_list optional_comma ')'  */
                                                { (yyval.pExpression) = (yyvsp[-2].pExpression); }
    break;

  case 797: /* type_declaration_no_options_no_dim: basic_type_declaration  */
                                                            { (yyval.pTypeDecl) = new TypeDecl((yyvsp[0].type)); (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0])); }
    break;

  case 798: /* type_declaration_no_options_no_dim: auto_type_declaration  */
                                                            { (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl); }
    break;

  case 799: /* type_declaration_no_options_no_dim: bitfield_type_declaration  */
                                                            { (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl); }
    break;

  case 800: /* type_declaration_no_options_no_dim: structure_type_declaration  */
                                                            { (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl); }
    break;

  case 801: /* $@59: %empty  */
                     { yyextra->das_arrow_depth ++; }
    break;

  case 802: /* $@60: %empty  */
                                                                                     { yyextra->das_arrow_depth --; }
    break;

  case 803: /* type_declaration_no_options_no_dim: "type" '<' $@59 type_declaration '>' $@60  */
                                                                                                                      {
        (yyvsp[-2].pTypeDecl)->autoToAlias = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 804: /* type_declaration_no_options_no_dim: "typedecl" '(' expr ')'  */
                                               {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeDecl);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-3]),(yylsp[-1]));
        (yyval.pTypeDecl)->typeMacroExpr.push_back((yyvsp[-1].pExpression));
    }
    break;

  case 805: /* type_declaration_no_options_no_dim: name_in_namespace '(' optional_expr_list ')'  */
                                                                      {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeMacro);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-3]), (yylsp[-1]));
        (yyval.pTypeDecl)->typeMacroExpr = sequenceToList((yyvsp[-1].pExpression));
        (yyval.pTypeDecl)->typeMacroExpr.insert((yyval.pTypeDecl)->typeMacroExpr.begin(), new ExprConstString(tokAt(scanner,(yylsp[-3])), *(yyvsp[-3].s)));
        delete (yyvsp[-3].s);
    }
    break;

  case 806: /* type_declaration_no_options_no_dim: '$' name_in_namespace optional_expr_list_in_braces  */
                                                                            {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeMacro);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-1]), (yylsp[0]));
        (yyval.pTypeDecl)->typeMacroExpr = sequenceToList((yyvsp[0].pExpression));
        (yyval.pTypeDecl)->typeMacroExpr.insert((yyval.pTypeDecl)->typeMacroExpr.begin(), new ExprConstString(tokAt(scanner,(yylsp[-1])), *(yyvsp[-1].s)));
        delete (yyvsp[-1].s);
    }
    break;

  case 807: /* $@61: %empty  */
                                    { yyextra->das_arrow_depth ++; }
    break;

  case 808: /* type_declaration_no_options_no_dim: name_in_namespace '<' $@61 type_declaration_no_options_list '>' optional_expr_list_in_braces  */
                                                                                                                                                         {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeMacro);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-5]), (yylsp[0]));
        (yyval.pTypeDecl)->typeMacroExpr = typesAndSequenceToList((yyvsp[-2].pTypeDeclList),(yyvsp[0].pExpression));
        (yyval.pTypeDecl)->typeMacroExpr.insert((yyval.pTypeDecl)->typeMacroExpr.begin(), new ExprConstString(tokAt(scanner,(yylsp[-5])), *(yyvsp[-5].s)));
        delete (yyvsp[-5].s);
    }
    break;

  case 809: /* $@62: %empty  */
                                        { yyextra->das_arrow_depth ++; }
    break;

  case 810: /* type_declaration_no_options_no_dim: '$' name_in_namespace '<' $@62 type_declaration_no_options_list '>' optional_expr_list_in_braces  */
                                                                                                                                                             {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeMacro);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-5]), (yylsp[0]));
        (yyval.pTypeDecl)->typeMacroExpr = typesAndSequenceToList((yyvsp[-2].pTypeDeclList),(yyvsp[0].pExpression));
        (yyval.pTypeDecl)->typeMacroExpr.insert((yyval.pTypeDecl)->typeMacroExpr.begin(), new ExprConstString(tokAt(scanner,(yylsp[-5])), *(yyvsp[-5].s)));
        delete (yyvsp[-5].s);
    }
    break;

  case 811: /* type_declaration_no_options_no_dim: type_declaration_no_options '-' '[' ']'  */
                                                          {
        (yyvsp[-3].pTypeDecl)->removeDim = true;
        (yyval.pTypeDecl) = (yyvsp[-3].pTypeDecl);
    }
    break;

  case 812: /* type_declaration_no_options_no_dim: type_declaration_no_options "explicit"  */
                                                           {
        (yyvsp[-1].pTypeDecl)->isExplicit = true;
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 813: /* type_declaration_no_options_no_dim: type_declaration_no_options "const"  */
                                                        {
        (yyvsp[-1].pTypeDecl)->constant = true;
        (yyvsp[-1].pTypeDecl)->removeConstant = false;
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 814: /* type_declaration_no_options_no_dim: type_declaration_no_options '-' "const"  */
                                                            {
        (yyvsp[-2].pTypeDecl)->constant = false;
        (yyvsp[-2].pTypeDecl)->removeConstant = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 815: /* type_declaration_no_options_no_dim: type_declaration_no_options '&'  */
                                                  {
        (yyvsp[-1].pTypeDecl)->ref = true;
        (yyvsp[-1].pTypeDecl)->removeRef = false;
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 816: /* type_declaration_no_options_no_dim: type_declaration_no_options '-' '&'  */
                                                      {
        (yyvsp[-2].pTypeDecl)->ref = false;
        (yyvsp[-2].pTypeDecl)->removeRef = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 817: /* type_declaration_no_options_no_dim: type_declaration_no_options '#'  */
                                                  {
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
        (yyval.pTypeDecl)->temporary = true;
    }
    break;

  case 818: /* type_declaration_no_options_no_dim: type_declaration_no_options "implicit"  */
                                                           {
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
        (yyval.pTypeDecl)->implicit = true;
    }
    break;

  case 819: /* type_declaration_no_options_no_dim: type_declaration_no_options '-' '#'  */
                                                      {
        (yyvsp[-2].pTypeDecl)->temporary = false;
        (yyvsp[-2].pTypeDecl)->removeTemporary = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 820: /* type_declaration_no_options_no_dim: type_declaration_no_options "==" "const"  */
                                                               {
        (yyvsp[-2].pTypeDecl)->explicitConst = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 821: /* type_declaration_no_options_no_dim: type_declaration_no_options "==" '&'  */
                                                         {
        (yyvsp[-2].pTypeDecl)->explicitRef = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 822: /* type_declaration_no_options_no_dim: type_declaration_no_options '?'  */
                                                  {
        (yyval.pTypeDecl) = new TypeDecl(Type::tPointer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-1]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 823: /* $@63: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 824: /* $@64: %empty  */
                                                                                               { yyextra->das_arrow_depth --; }
    break;

  case 825: /* type_declaration_no_options_no_dim: "smart_ptr" '<' $@63 type_declaration '>' $@64  */
                                                                                                                                {
        (yyval.pTypeDecl) = new TypeDecl(Type::tPointer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->smartPtr = true;
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 826: /* type_declaration_no_options_no_dim: type_declaration_no_options "??"  */
                                                 {
        (yyval.pTypeDecl) = new TypeDecl(Type::tPointer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-1]));
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::tPointer);
        (yyval.pTypeDecl)->firstType->at = tokAt(scanner,(yylsp[-1]));
        (yyval.pTypeDecl)->firstType->firstType = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 827: /* $@65: %empty  */
                           { yyextra->das_arrow_depth ++; }
    break;

  case 828: /* $@66: %empty  */
                                                                                           { yyextra->das_arrow_depth --; }
    break;

  case 829: /* type_declaration_no_options_no_dim: "array" '<' $@65 type_declaration '>' $@66  */
                                                                                                                            {
        (yyval.pTypeDecl) = new TypeDecl(Type::tArray);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 830: /* $@67: %empty  */
                           { yyextra->das_arrow_depth ++; }
    break;

  case 831: /* $@68: %empty  */
                                                                                     { yyextra->das_arrow_depth --; }
    break;

  case 832: /* type_declaration_no_options_no_dim: "table" '<' $@67 table_type_pair '>' $@68  */
                                                                                                                      {
        (yyval.pTypeDecl) = new TypeDecl(Type::tTable);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].aTypePair).firstType;
        (yyval.pTypeDecl)->secondType = (yyvsp[-2].aTypePair).secondType;
    }
    break;

  case 833: /* $@69: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 834: /* $@70: %empty  */
                                                                                                 { yyextra->das_arrow_depth --; }
    break;

  case 835: /* type_declaration_no_options_no_dim: "iterator" '<' $@69 type_declaration '>' $@70  */
                                                                                                                                  {
        (yyval.pTypeDecl) = new TypeDecl(Type::tIterator);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 836: /* type_declaration_no_options_no_dim: "block"  */
                        {
        (yyval.pTypeDecl) = new TypeDecl(Type::tBlock);
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::tVoid);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 837: /* $@71: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 838: /* $@72: %empty  */
                                                                                              { yyextra->das_arrow_depth --; }
    break;

  case 839: /* type_declaration_no_options_no_dim: "block" '<' $@71 type_declaration '>' $@72  */
                                                                                                                               {
        (yyval.pTypeDecl) = new TypeDecl(Type::tBlock);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 840: /* $@73: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 841: /* $@74: %empty  */
                                                                                                                                       { yyextra->das_arrow_depth --; }
    break;

  case 842: /* type_declaration_no_options_no_dim: "block" '<' $@73 optional_function_argument_list optional_function_type '>' $@74  */
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

  case 843: /* type_declaration_no_options_no_dim: "function"  */
                           {
        (yyval.pTypeDecl) = new TypeDecl(Type::tFunction);
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::tVoid);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 844: /* $@75: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 845: /* $@76: %empty  */
                                                                                                { yyextra->das_arrow_depth --; }
    break;

  case 846: /* type_declaration_no_options_no_dim: "function" '<' $@75 type_declaration '>' $@76  */
                                                                                                                                 {
        (yyval.pTypeDecl) = new TypeDecl(Type::tFunction);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 847: /* $@77: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 848: /* $@78: %empty  */
                                                                                                                                         { yyextra->das_arrow_depth --; }
    break;

  case 849: /* type_declaration_no_options_no_dim: "function" '<' $@77 optional_function_argument_list optional_function_type '>' $@78  */
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

  case 850: /* type_declaration_no_options_no_dim: "lambda"  */
                         {
        (yyval.pTypeDecl) = new TypeDecl(Type::tLambda);
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::tVoid);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 851: /* $@79: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 852: /* $@80: %empty  */
                                                                                              { yyextra->das_arrow_depth --; }
    break;

  case 853: /* type_declaration_no_options_no_dim: "lambda" '<' $@79 type_declaration '>' $@80  */
                                                                                                                               {
        (yyval.pTypeDecl) = new TypeDecl(Type::tLambda);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 854: /* $@81: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 855: /* $@82: %empty  */
                                                                                                                                       { yyextra->das_arrow_depth --; }
    break;

  case 856: /* type_declaration_no_options_no_dim: "lambda" '<' $@81 optional_function_argument_list optional_function_type '>' $@82  */
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

  case 857: /* $@83: %empty  */
                            { yyextra->das_arrow_depth ++; }
    break;

  case 858: /* $@84: %empty  */
                                                                                       { yyextra->das_arrow_depth --; }
    break;

  case 859: /* type_declaration_no_options_no_dim: "tuple" '<' $@83 tuple_type_list '>' $@84  */
                                                                                                                        {
        (yyval.pTypeDecl) = new TypeDecl(Type::tTuple);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        varDeclToTypeDecl(scanner, (yyval.pTypeDecl), (yyvsp[-2].pVarDeclList), true);
        deleteVariableDeclarationList((yyvsp[-2].pVarDeclList));
    }
    break;

  case 860: /* $@85: %empty  */
                              { yyextra->das_arrow_depth ++; }
    break;

  case 861: /* $@86: %empty  */
                                                                                           { yyextra->das_arrow_depth --; }
    break;

  case 862: /* type_declaration_no_options_no_dim: "variant" '<' $@85 variant_type_list '>' $@86  */
                                                                                                                            {
        (yyval.pTypeDecl) = new TypeDecl(Type::tVariant);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        varDeclToTypeDecl(scanner, (yyval.pTypeDecl), (yyvsp[-2].pVarDeclList), true);
        deleteVariableDeclarationList((yyvsp[-2].pVarDeclList));
    }
    break;

  case 863: /* type_declaration: type_declaration_no_options  */
                                        {
        (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl);
    }
    break;

  case 864: /* type_declaration: type_declaration '|' type_declaration_no_options  */
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

  case 865: /* type_declaration: type_declaration '|' '#'  */
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

  case 866: /* $@87: %empty  */
                   {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 867: /* $@88: %empty  */
                                                                             {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeTuple(atvname);
        }
    }
    break;

  case 868: /* $@89: %empty  */
          {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeTupleEntries(atvname);
        }
    }
    break;

  case 869: /* $@90: %empty  */
                                                 {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-6]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterTupleEntries(atvname);
        }
        yyextra->pop_nesteds();
    }
    break;

  case 870: /* tuple_alias_declaration: "tuple" $@87 optional_public_or_private_alias "name" optional_emit_semis $@88 '{' $@89 tuple_alias_type_list optional_semis $@90 '}'  */
          {
        auto vtype = new TypeDecl(Type::tTuple);
        vtype->alias = *(yyvsp[-8].s);
        vtype->at = tokAt(scanner,(yylsp[-8]));
        vtype->isPrivateAlias = !(yyvsp[-9].b);
        varDeclToTypeDecl(scanner, vtype, (yyvsp[-3].pVarDeclList), true);
        deleteVariableDeclarationList((yyvsp[-3].pVarDeclList));
        if ( !yyextra->g_Program->addAlias(vtype) ) {
            das2_yyerror(scanner,"type alias is already defined "+*(yyvsp[-8].s),tokAt(scanner,(yylsp[-8])),
                CompilationError::already_declared_type_alias);
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-8]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterTuple((yyvsp[-8].s)->c_str(),atvname);
        }
        delete (yyvsp[-8].s);
    }
    break;

  case 871: /* $@91: %empty  */
                     {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 872: /* $@92: %empty  */
                                                                             {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeVariant(atvname);
        }
    }
    break;

  case 873: /* $@93: %empty  */
          {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeVariantEntries(atvname);
        }

    }
    break;

  case 874: /* $@94: %empty  */
                                                   {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-6]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterVariantEntries(atvname);
        }
        yyextra->pop_nesteds();
    }
    break;

  case 875: /* variant_alias_declaration: "variant" $@91 optional_public_or_private_alias "name" optional_emit_semis $@92 '{' $@93 variant_alias_type_list optional_semis $@94 '}'  */
          {
        auto vtype = new TypeDecl(Type::tVariant);
        vtype->alias = *(yyvsp[-8].s);
        vtype->at = tokAt(scanner,(yylsp[-8]));
        vtype->isPrivateAlias = !(yyvsp[-9].b);
        varDeclToTypeDecl(scanner, vtype, (yyvsp[-3].pVarDeclList), true);
        deleteVariableDeclarationList((yyvsp[-3].pVarDeclList));
        if ( !yyextra->g_Program->addAlias(vtype) ) {
            das2_yyerror(scanner,"type alias is already defined "+*(yyvsp[-8].s),tokAt(scanner,(yylsp[-8])),
                CompilationError::already_declared_type_alias);
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-8]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterVariant((yyvsp[-8].s)->c_str(),atvname);
        }
        delete (yyvsp[-8].s);
    }
    break;

  case 876: /* $@95: %empty  */
                      {
        yyextra->push_nesteds(DAS_EMIT_COMMA);
    }
    break;

  case 877: /* $@96: %empty  */
                                                                                                                         {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-2]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeBitfield(atvname);
        }
    }
    break;

  case 878: /* $@97: %empty  */
          {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-4]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeBitfieldEntries(atvname);
        }
    }
    break;

  case 879: /* $@98: %empty  */
                                                {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-7]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterBitfieldEntries(atvname);
        }
        yyextra->pop_nesteds();
    }
    break;

  case 880: /* bitfield_alias_declaration: "bitfield" $@95 optional_public_or_private_alias "name" bitfield_basic_type_declaration optional_emit_commas $@96 '{' $@97 bitfield_alias_bits optional_commas $@98 '}'  */
          {
        auto btype = new TypeDecl((yyvsp[-8].type));
        btype->alias = *(yyvsp[-9].s);
        btype->at = tokAt(scanner,(yylsp[-9]));
        btype->isPrivateAlias = !(yyvsp[-10].b);
        for ( auto & p : *(yyvsp[-3].pNameExprList) ) {
            if ( !get<1>(p) ) {
                btype->argNames.push_back(get<0>(p));
            }
        }
        auto maxBits = btype->maxBitfieldBits();
        if ( btype->argNames.size()>maxBits ) {
            das_yyerror(scanner,"only " + to_string(maxBits) + " different bits are allowed in a bitfield",tokAt(scanner,(yylsp[-9])),
                CompilationError::exceeds_bitfield);
        }
        for ( auto & p : *(yyvsp[-3].pNameExprList) ) {
            if ( get<1>(p) ) {
                ast_globalBitfieldConst ( scanner, btype, (yyvsp[-10].b), get<0>(p), get<1>(p) );
            }
        }
        if ( !yyextra->g_Program->addAlias(btype) ) {
            das2_yyerror(scanner,"type alias is already defined "+*(yyvsp[-9].s),tokAt(scanner,(yylsp[-9])),
                CompilationError::already_declared_type_alias);
        }
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-9]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterBitfield((yyvsp[-9].s)->c_str(),atvname);
        }
        delete (yyvsp[-9].s);
        delete (yyvsp[-3].pNameExprList);
    }
    break;

  case 881: /* make_decl: make_struct_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 882: /* make_decl: make_dim_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 883: /* make_decl: make_table_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 884: /* make_decl: make_table_call  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 885: /* make_decl: array_comprehension  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 886: /* make_decl: table_comprehension  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 887: /* make_decl: make_tuple_call  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 888: /* make_decl_no_bracket: make_struct_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 889: /* make_decl_no_bracket: make_dim_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 890: /* make_decl_no_bracket: make_tuple_call  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 891: /* make_decl_no_bracket: table_comprehension  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 892: /* make_decl_no_bracket: make_table_call  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 893: /* make_struct_fields: "name" copy_or_move expr  */
                                               {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-2])),*(yyvsp[-2].s),(yyvsp[0].pExpression),(yyvsp[-1].b),false);
        delete (yyvsp[-2].s);
        auto msd = new MakeStruct();
        msd->push_back(mfd);
        (yyval.pMakeStruct) = msd;
    }
    break;

  case 894: /* make_struct_fields: "name" ":=" expr  */
                                      {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-2])),*(yyvsp[-2].s),(yyvsp[0].pExpression),false,true);
        delete (yyvsp[-2].s);
        auto msd = new MakeStruct();
        msd->push_back(mfd);
        (yyval.pMakeStruct) = msd;
    }
    break;

  case 895: /* make_struct_fields: make_struct_fields ',' "name" copy_or_move expr  */
                                                                           {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-2])),*(yyvsp[-2].s),(yyvsp[0].pExpression),(yyvsp[-1].b),false);
        delete (yyvsp[-2].s);
        ((MakeStruct *)(yyvsp[-4].pMakeStruct))->push_back(mfd);
        (yyval.pMakeStruct) = (yyvsp[-4].pMakeStruct);
    }
    break;

  case 896: /* make_struct_fields: make_struct_fields ',' "name" ":=" expr  */
                                                                  {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-2])),*(yyvsp[-2].s),(yyvsp[0].pExpression),false,true);
        delete (yyvsp[-2].s);
        ((MakeStruct *)(yyvsp[-4].pMakeStruct))->push_back(mfd);
        (yyval.pMakeStruct) = (yyvsp[-4].pMakeStruct);
    }
    break;

  case 897: /* make_struct_fields: "$f" '(' expr ')' copy_or_move expr  */
                                                                   {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-3])),"``MACRO``TAG``FIELD``",(yyvsp[0].pExpression),(yyvsp[-1].b),false);
        mfd->tag = (yyvsp[-3].pExpression);
        auto msd = new MakeStruct();
        msd->push_back(mfd);
        (yyval.pMakeStruct) = msd;
    }
    break;

  case 898: /* make_struct_fields: "$f" '(' expr ')' ":=" expr  */
                                                          {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-3])),"``MACRO``TAG``FIELD``",(yyvsp[0].pExpression),false,true);
        mfd->tag = (yyvsp[-3].pExpression);
        auto msd = new MakeStruct();
        msd->push_back(mfd);
        (yyval.pMakeStruct) = msd;
    }
    break;

  case 899: /* make_struct_fields: make_struct_fields ',' "$f" '(' expr ')' copy_or_move expr  */
                                                                                               {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-3])),"``MACRO``TAG``FIELD``",(yyvsp[0].pExpression),(yyvsp[-1].b),false);
        mfd->tag = (yyvsp[-3].pExpression);
        ((MakeStruct *)(yyvsp[-7].pMakeStruct))->push_back(mfd);
        (yyval.pMakeStruct) = (yyvsp[-7].pMakeStruct);
    }
    break;

  case 900: /* make_struct_fields: make_struct_fields ',' "$f" '(' expr ')' ":=" expr  */
                                                                                      {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-3])),"``MACRO``TAG``FIELD``",(yyvsp[0].pExpression),false,true);
        mfd->tag = (yyvsp[-3].pExpression);
        ((MakeStruct *)(yyvsp[-7].pMakeStruct))->push_back(mfd);
        (yyval.pMakeStruct) = (yyvsp[-7].pMakeStruct);
    }
    break;

  case 901: /* make_variant_dim: %empty  */
       {
        (yyval.pExpression) = ast_makeStructToMakeVariant(nullptr, LineInfo());
    }
    break;

  case 902: /* make_variant_dim: make_struct_fields  */
                              {
        (yyval.pExpression) = ast_makeStructToMakeVariant((yyvsp[0].pMakeStruct), tokAt(scanner,(yylsp[0])));
    }
    break;

  case 903: /* make_struct_single: make_struct_fields optional_comma  */
                                               {
        auto msd = new ExprMakeStruct();
        msd->structs.push_back(MakeStructPtr((yyvsp[-1].pMakeStruct)));
        (yyval.pExpression) = msd;
    }
    break;

  case 904: /* make_struct_dim_list: '(' make_struct_fields ')'  */
                                        {
        auto msd = new ExprMakeStruct();
        msd->structs.push_back(MakeStructPtr((yyvsp[-1].pMakeStruct)));
        (yyval.pExpression) = msd;
    }
    break;

  case 905: /* make_struct_dim_list: make_struct_dim_list ',' '(' make_struct_fields ')'  */
                                                                     {
        ((ExprMakeStruct *) (yyvsp[-4].pExpression))->structs.push_back(MakeStructPtr((yyvsp[-1].pMakeStruct)));
        (yyval.pExpression) = (yyvsp[-4].pExpression);
    }
    break;

  case 906: /* make_struct_dim_decl: make_struct_fields  */
                                {
        auto msd = new ExprMakeStruct();
        msd->structs.push_back(MakeStructPtr((yyvsp[0].pMakeStruct)));
        (yyval.pExpression) = msd;
    }
    break;

  case 907: /* make_struct_dim_decl: make_struct_dim_list optional_comma  */
                                                 {
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 908: /* optional_make_struct_dim_decl: make_struct_dim_decl  */
                                  { (yyval.pExpression) = (yyvsp[0].pExpression);  }
    break;

  case 909: /* optional_make_struct_dim_decl: %empty  */
        {   (yyval.pExpression) = new ExprMakeStruct(); }
    break;

  case 910: /* use_initializer: %empty  */
                            { (yyval.b) = true; }
    break;

  case 911: /* use_initializer: "uninitialized"  */
                            { (yyval.b) = false; }
    break;

  case 912: /* $@99: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 913: /* $@100: %empty  */
                                                                                                   { yyextra->das_arrow_depth --; }
    break;

  case 914: /* make_struct_decl: "struct" '<' $@99 type_declaration_no_options '>' $@100 '(' use_initializer optional_make_struct_dim_decl ')'  */
                                                                                                                                                                                                      {
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-9]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-6].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = (yyvsp[-2].b);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->forceStruct = true;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 915: /* $@101: %empty  */
                            { yyextra->das_arrow_depth ++; }
    break;

  case 916: /* $@102: %empty  */
                                                                                                  { yyextra->das_arrow_depth --; }
    break;

  case 917: /* make_struct_decl: "class" '<' $@101 type_declaration_no_options '>' $@102 '(' use_initializer optional_make_struct_dim_decl ')'  */
                                                                                                                                                                                                     {
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-9]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-6].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = (yyvsp[-2].b);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->forceClass = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 918: /* $@103: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 919: /* $@104: %empty  */
                                                                                            { yyextra->das_arrow_depth --; }
    break;

  case 920: /* make_struct_decl: "variant" '<' $@103 variant_type_list '>' $@104 '(' use_initializer make_variant_dim ')'  */
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

  case 921: /* $@105: %empty  */
                                        { yyextra->das_arrow_depth ++; }
    break;

  case 922: /* $@106: %empty  */
                                                                                                              { yyextra->das_arrow_depth --; }
    break;

  case 923: /* make_struct_decl: "variant" "type" '<' $@105 type_declaration_no_options '>' $@106 '(' use_initializer make_variant_dim ')'  */
                                                                                                                                                                                                    {
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-10]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-6].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = (yyvsp[-2].b);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->forceVariant = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 924: /* $@107: %empty  */
                              { yyextra->das_arrow_depth ++; }
    break;

  case 925: /* $@108: %empty  */
                                                                                                    { yyextra->das_arrow_depth --; }
    break;

  case 926: /* make_struct_decl: "default" '<' $@107 type_declaration_no_options '>' $@108 use_initializer  */
                                                                                                                                                           {
        auto msd = new ExprMakeStruct();
        msd->at = tokAt(scanner,(yylsp[-6]));
        msd->makeType = (yyvsp[-3].pTypeDecl);
        msd->useInitializer = (yyvsp[0].b);
        msd->alwaysUseInitializer = true;
        (yyval.pExpression) = msd;
    }
    break;

  case 927: /* make_tuple_call: "tuple" '(' expr_list optional_comma ')'  */
                                                                    {
        auto mkt = new ExprMakeTuple(tokAt(scanner,(yylsp[-4])));
        mkt->values = sequenceToList((yyvsp[-2].pExpression));
        mkt->makeType = new TypeDecl(Type::autoinfer);
        (yyval.pExpression) = mkt;
    }
    break;

  case 928: /* $@109: %empty  */
                             { yyextra->das_force_oxford_comma=true; yyextra->das_arrow_depth ++; }
    break;

  case 929: /* $@110: %empty  */
                                                                                                                              { yyextra->das_arrow_depth --; }
    break;

  case 930: /* make_tuple_call: "tuple" '<' $@109 tuple_type_list '>' $@110 '(' use_initializer optional_make_struct_dim_decl ')'  */
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

  case 931: /* make_dim_decl: '[' optional_expr_list ']'  */
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

  case 932: /* $@111: %empty  */
                                       { yyextra->das_arrow_depth ++; }
    break;

  case 933: /* $@112: %empty  */
                                                                                                             { yyextra->das_arrow_depth --; }
    break;

  case 934: /* make_dim_decl: "array" "struct" '<' $@111 type_declaration_no_options '>' $@112 '(' use_initializer optional_make_struct_dim_decl ')'  */
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

  case 935: /* $@113: %empty  */
                                       { yyextra->das_arrow_depth ++; }
    break;

  case 936: /* $@114: %empty  */
                                                                                                  { yyextra->das_arrow_depth --; }
    break;

  case 937: /* make_dim_decl: "array" "tuple" '<' $@113 tuple_type_list '>' $@114 '(' use_initializer optional_make_struct_dim_decl ')'  */
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

  case 938: /* $@115: %empty  */
                                         { yyextra->das_arrow_depth ++; }
    break;

  case 939: /* $@116: %empty  */
                                                                                                      { yyextra->das_arrow_depth --; }
    break;

  case 940: /* make_dim_decl: "array" "variant" '<' $@115 variant_type_list '>' $@116 '(' make_variant_dim ')'  */
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

  case 941: /* make_dim_decl: "array" '(' expr_list optional_comma ')'  */
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

  case 942: /* $@117: %empty  */
                           { yyextra->das_arrow_depth ++; }
    break;

  case 943: /* $@118: %empty  */
                                                                                                 { yyextra->das_arrow_depth --; }
    break;

  case 944: /* make_dim_decl: "array" '<' $@117 type_declaration_no_options '>' $@118 '(' optional_expr_list ')'  */
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

  case 945: /* make_dim_decl: "fixed_array" '(' expr_list optional_comma ')'  */
                                                                         {
        auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-4])));
        mka->values = sequenceToList((yyvsp[-2].pExpression));
        mka->makeType = new TypeDecl(Type::autoinfer);
        mka->gen2 = true;
        (yyval.pExpression) = mka;
    }
    break;

  case 946: /* $@119: %empty  */
                                 { yyextra->das_arrow_depth ++; }
    break;

  case 947: /* $@120: %empty  */
                                                                                                       { yyextra->das_arrow_depth --; }
    break;

  case 948: /* make_dim_decl: "fixed_array" '<' $@119 type_declaration_no_options '>' $@120 '(' expr_list optional_comma ')'  */
                                                                                                                                                                                    {
        auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-9])));
        mka->values = sequenceToList((yyvsp[-2].pExpression));
        mka->makeType = (yyvsp[-6].pTypeDecl);
        mka->gen2 = true;
        (yyval.pExpression) = mka;
    }
    break;

  case 949: /* expr_map_tuple_list: expr  */
                      {
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 950: /* expr_map_tuple_list: expr_map_tuple_list ',' expr  */
                                                      {
            (yyval.pExpression) = new ExprSequence(tokAt(scanner,(yylsp[-2])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
    }
    break;

  case 951: /* push_table_nesting: %empty  */
                    {
        yyextra->das_nested_parentheses ++;
    }
    break;

  case 952: /* make_table_decl: '{' push_table_nesting optional_emit_semis optional_expr_map_tuple_list '}'  */
                                                                                                     {
        yyextra->das_nested_parentheses --;
        if ( (yyvsp[-1].pExpression) ) {
            auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-4])));
            mka->values = sequenceToList((yyvsp[-1].pExpression));
            mka->makeType = new TypeDecl(Type::autoinfer);
            auto ttm = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-4])),"to_table_move");
            ttm->arguments.push_back(mka);
            (yyval.pExpression) = ttm;
        } else {
            auto mks = new ExprMakeStruct();
            mks->at = tokAt(scanner,(yylsp[-4]));
            mks->makeType = new TypeDecl(Type::tTable);
            mks->makeType->firstType = new TypeDecl(Type::autoinfer);
            mks->makeType->secondType = new TypeDecl(Type::autoinfer);
            mks->useInitializer = true;
            mks->alwaysUseInitializer = true;
            (yyval.pExpression) = mks;
        }
    }
    break;

  case 953: /* make_table_call: "table" '(' expr_map_tuple_list optional_comma ')'  */
                                                                             {
        auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-4])));
        mka->values = sequenceToList((yyvsp[-2].pExpression));
        mka->makeType = new TypeDecl(Type::autoinfer);
        auto ttm = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-4])),"to_table_move");
        ttm->arguments.push_back(mka);
        (yyval.pExpression) = ttm;
    }
    break;

  case 954: /* make_table_call: "table" '<' type_declaration_no_options '>' '(' optional_expr_map_tuple_list ')'  */
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

  case 955: /* make_table_call: "table" '<' type_declaration_no_options c_or_s type_declaration_no_options '>' '(' optional_expr_map_tuple_list ')'  */
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

  case 956: /* array_comprehension_where: %empty  */
                                    { (yyval.pExpression) = nullptr; }
    break;

  case 957: /* array_comprehension_where: ';' "where" expr  */
                                    { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 958: /* optional_comma: %empty  */
                { (yyval.b) = false; }
    break;

  case 959: /* optional_comma: ','  */
                { (yyval.b) = true; }
    break;

  case 960: /* table_comprehension: '[' "for" '(' for_variable_name_with_pos_list "in" expr_list ')' ';' expr array_comprehension_where ']'  */
                                                                                                                                                               {
        (yyval.pExpression) = ast_arrayComprehension(scanner,tokAt(scanner,(yylsp[-9])),(yyvsp[-7].pNameWithPosList),(yyvsp[-5].pExpression),(yyvsp[-2].pExpression),(yyvsp[-1].pExpression),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),false,false);
    }
    break;

  case 961: /* table_comprehension: '[' "iterator" "for" '(' for_variable_name_with_pos_list "in" expr_list ')' ';' expr array_comprehension_where ']'  */
                                                                                                                                                                            {
        (yyval.pExpression) = ast_arrayComprehension(scanner,tokAt(scanner,(yylsp[-9])),(yyvsp[-7].pNameWithPosList),(yyvsp[-5].pExpression),(yyvsp[-2].pExpression),(yyvsp[-1].pExpression),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),true,false);
    }
    break;

  case 962: /* array_comprehension: '{' push_table_nesting optional_emit_semis "for" '(' for_variable_name_with_pos_list "in" expr_list ')' ';' expr array_comprehension_where '}'  */
                                                                                                                                                                                                      {
        yyextra->das_nested_parentheses --;
        (yyval.pExpression) = ast_arrayComprehension(scanner,tokAt(scanner,(yylsp[-9])),(yyvsp[-7].pNameWithPosList),(yyvsp[-5].pExpression),(yyvsp[-2].pExpression),(yyvsp[-1].pExpression),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),false,true);
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
  yytoken = yychar == DAS2_YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
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

      if (yychar <= DAS2_YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == DAS2_YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, scanner);
          yychar = DAS2_YYEMPTY;
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
  if (yychar != DAS2_YYEMPTY)
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



void das2_yyfatalerror ( DAS2_YYLTYPE * lloc, yyscan_t scanner, const string & error, CompilationError cerr ) {
    yyextra->g_Program->error(error,"","",LineInfo(yyextra->g_FileAccessStack.back(),
        lloc->first_column,lloc->first_line,lloc->last_column,lloc->last_line),cerr);
}

void das2_yyerror ( DAS2_YYLTYPE * lloc, yyscan_t scanner, const string & error ) {
    if ( !yyextra->das_suppress_errors ) {
        yyextra->g_Program->error(error,"","",LineInfo(yyextra->g_FileAccessStack.back(),
            lloc->first_column,lloc->first_line,lloc->last_column,lloc->last_line),
                CompilationError::invalid_expression);
    }
}

LineInfo tokAt ( yyscan_t scanner, const struct DAS2_YYLTYPE & li ) {
    return LineInfo(yyextra->g_FileAccessStack.back(),
        li.first_column,li.first_line,
        li.last_column,li.last_line);
}

LineInfo tokRangeAt ( yyscan_t scanner, const struct DAS2_YYLTYPE & li, const struct DAS2_YYLTYPE & lie ) {
    return LineInfo(yyextra->g_FileAccessStack.back(),
        li.first_column,li.first_line,
        lie.last_column,lie.last_line);
}


