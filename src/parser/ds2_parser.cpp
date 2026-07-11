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
  YYSYMBOL_distinct_alias = 412,           /* distinct_alias  */
  YYSYMBOL_optional_public_or_private_enum = 413, /* optional_public_or_private_enum  */
  YYSYMBOL_enum_name = 414,                /* enum_name  */
  YYSYMBOL_optional_enum_basic_type_declaration = 415, /* optional_enum_basic_type_declaration  */
  YYSYMBOL_optional_commas = 416,          /* optional_commas  */
  YYSYMBOL_emit_commas = 417,              /* emit_commas  */
  YYSYMBOL_optional_emit_commas = 418,     /* optional_emit_commas  */
  YYSYMBOL_enum_declaration = 419,         /* enum_declaration  */
  YYSYMBOL_420_51 = 420,                   /* $@51  */
  YYSYMBOL_421_52 = 421,                   /* $@52  */
  YYSYMBOL_422_53 = 422,                   /* $@53  */
  YYSYMBOL_optional_structure_parent = 423, /* optional_structure_parent  */
  YYSYMBOL_optional_sealed = 424,          /* optional_sealed  */
  YYSYMBOL_structure_name = 425,           /* structure_name  */
  YYSYMBOL_class_or_struct = 426,          /* class_or_struct  */
  YYSYMBOL_optional_public_or_private_structure = 427, /* optional_public_or_private_structure  */
  YYSYMBOL_optional_struct_variable_declaration_list = 428, /* optional_struct_variable_declaration_list  */
  YYSYMBOL_structure_declaration = 429,    /* structure_declaration  */
  YYSYMBOL_430_54 = 430,                   /* $@54  */
  YYSYMBOL_431_55 = 431,                   /* $@55  */
  YYSYMBOL_432_56 = 432,                   /* $@56  */
  YYSYMBOL_variable_name_with_pos_list = 433, /* variable_name_with_pos_list  */
  YYSYMBOL_basic_type_declaration = 434,   /* basic_type_declaration  */
  YYSYMBOL_enum_basic_type_declaration = 435, /* enum_basic_type_declaration  */
  YYSYMBOL_structure_type_declaration = 436, /* structure_type_declaration  */
  YYSYMBOL_auto_type_declaration = 437,    /* auto_type_declaration  */
  YYSYMBOL_bitfield_bits = 438,            /* bitfield_bits  */
  YYSYMBOL_bitfield_alias_bits = 439,      /* bitfield_alias_bits  */
  YYSYMBOL_bitfield_basic_type_declaration = 440, /* bitfield_basic_type_declaration  */
  YYSYMBOL_bitfield_type_declaration = 441, /* bitfield_type_declaration  */
  YYSYMBOL_442_57 = 442,                   /* $@57  */
  YYSYMBOL_443_58 = 443,                   /* $@58  */
  YYSYMBOL_c_or_s = 444,                   /* c_or_s  */
  YYSYMBOL_table_type_pair = 445,          /* table_type_pair  */
  YYSYMBOL_dim_list = 446,                 /* dim_list  */
  YYSYMBOL_type_declaration_no_options = 447, /* type_declaration_no_options  */
  YYSYMBOL_optional_expr_list_in_braces = 448, /* optional_expr_list_in_braces  */
  YYSYMBOL_type_declaration_no_options_no_dim = 449, /* type_declaration_no_options_no_dim  */
  YYSYMBOL_450_59 = 450,                   /* $@59  */
  YYSYMBOL_451_60 = 451,                   /* $@60  */
  YYSYMBOL_452_61 = 452,                   /* $@61  */
  YYSYMBOL_453_62 = 453,                   /* $@62  */
  YYSYMBOL_454_63 = 454,                   /* $@63  */
  YYSYMBOL_455_64 = 455,                   /* $@64  */
  YYSYMBOL_456_65 = 456,                   /* $@65  */
  YYSYMBOL_457_66 = 457,                   /* $@66  */
  YYSYMBOL_458_67 = 458,                   /* $@67  */
  YYSYMBOL_459_68 = 459,                   /* $@68  */
  YYSYMBOL_460_69 = 460,                   /* $@69  */
  YYSYMBOL_461_70 = 461,                   /* $@70  */
  YYSYMBOL_462_71 = 462,                   /* $@71  */
  YYSYMBOL_463_72 = 463,                   /* $@72  */
  YYSYMBOL_464_73 = 464,                   /* $@73  */
  YYSYMBOL_465_74 = 465,                   /* $@74  */
  YYSYMBOL_466_75 = 466,                   /* $@75  */
  YYSYMBOL_467_76 = 467,                   /* $@76  */
  YYSYMBOL_468_77 = 468,                   /* $@77  */
  YYSYMBOL_469_78 = 469,                   /* $@78  */
  YYSYMBOL_470_79 = 470,                   /* $@79  */
  YYSYMBOL_471_80 = 471,                   /* $@80  */
  YYSYMBOL_472_81 = 472,                   /* $@81  */
  YYSYMBOL_473_82 = 473,                   /* $@82  */
  YYSYMBOL_474_83 = 474,                   /* $@83  */
  YYSYMBOL_475_84 = 475,                   /* $@84  */
  YYSYMBOL_476_85 = 476,                   /* $@85  */
  YYSYMBOL_477_86 = 477,                   /* $@86  */
  YYSYMBOL_type_declaration = 478,         /* type_declaration  */
  YYSYMBOL_tuple_alias_declaration = 479,  /* tuple_alias_declaration  */
  YYSYMBOL_480_87 = 480,                   /* $@87  */
  YYSYMBOL_481_88 = 481,                   /* $@88  */
  YYSYMBOL_482_89 = 482,                   /* $@89  */
  YYSYMBOL_483_90 = 483,                   /* $@90  */
  YYSYMBOL_variant_alias_declaration = 484, /* variant_alias_declaration  */
  YYSYMBOL_485_91 = 485,                   /* $@91  */
  YYSYMBOL_486_92 = 486,                   /* $@92  */
  YYSYMBOL_487_93 = 487,                   /* $@93  */
  YYSYMBOL_488_94 = 488,                   /* $@94  */
  YYSYMBOL_bitfield_alias_declaration = 489, /* bitfield_alias_declaration  */
  YYSYMBOL_490_95 = 490,                   /* $@95  */
  YYSYMBOL_491_96 = 491,                   /* $@96  */
  YYSYMBOL_492_97 = 492,                   /* $@97  */
  YYSYMBOL_493_98 = 493,                   /* $@98  */
  YYSYMBOL_make_decl = 494,                /* make_decl  */
  YYSYMBOL_make_decl_no_bracket = 495,     /* make_decl_no_bracket  */
  YYSYMBOL_make_struct_fields = 496,       /* make_struct_fields  */
  YYSYMBOL_make_variant_dim = 497,         /* make_variant_dim  */
  YYSYMBOL_make_struct_single = 498,       /* make_struct_single  */
  YYSYMBOL_make_struct_dim_list = 499,     /* make_struct_dim_list  */
  YYSYMBOL_make_struct_dim_decl = 500,     /* make_struct_dim_decl  */
  YYSYMBOL_optional_make_struct_dim_decl = 501, /* optional_make_struct_dim_decl  */
  YYSYMBOL_use_initializer = 502,          /* use_initializer  */
  YYSYMBOL_make_struct_decl = 503,         /* make_struct_decl  */
  YYSYMBOL_504_99 = 504,                   /* $@99  */
  YYSYMBOL_505_100 = 505,                  /* $@100  */
  YYSYMBOL_506_101 = 506,                  /* $@101  */
  YYSYMBOL_507_102 = 507,                  /* $@102  */
  YYSYMBOL_508_103 = 508,                  /* $@103  */
  YYSYMBOL_509_104 = 509,                  /* $@104  */
  YYSYMBOL_510_105 = 510,                  /* $@105  */
  YYSYMBOL_511_106 = 511,                  /* $@106  */
  YYSYMBOL_512_107 = 512,                  /* $@107  */
  YYSYMBOL_513_108 = 513,                  /* $@108  */
  YYSYMBOL_make_tuple_call = 514,          /* make_tuple_call  */
  YYSYMBOL_515_109 = 515,                  /* $@109  */
  YYSYMBOL_516_110 = 516,                  /* $@110  */
  YYSYMBOL_make_dim_decl = 517,            /* make_dim_decl  */
  YYSYMBOL_518_111 = 518,                  /* $@111  */
  YYSYMBOL_519_112 = 519,                  /* $@112  */
  YYSYMBOL_520_113 = 520,                  /* $@113  */
  YYSYMBOL_521_114 = 521,                  /* $@114  */
  YYSYMBOL_522_115 = 522,                  /* $@115  */
  YYSYMBOL_523_116 = 523,                  /* $@116  */
  YYSYMBOL_524_117 = 524,                  /* $@117  */
  YYSYMBOL_525_118 = 525,                  /* $@118  */
  YYSYMBOL_526_119 = 526,                  /* $@119  */
  YYSYMBOL_527_120 = 527,                  /* $@120  */
  YYSYMBOL_expr_map_tuple_list = 528,      /* expr_map_tuple_list  */
  YYSYMBOL_push_table_nesting = 529,       /* push_table_nesting  */
  YYSYMBOL_make_table_decl = 530,          /* make_table_decl  */
  YYSYMBOL_make_table_call = 531,          /* make_table_call  */
  YYSYMBOL_array_comprehension_where = 532, /* array_comprehension_where  */
  YYSYMBOL_optional_comma = 533,           /* optional_comma  */
  YYSYMBOL_table_comprehension = 534,      /* table_comprehension  */
  YYSYMBOL_array_comprehension = 535       /* array_comprehension  */
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
#define YYLAST   9854

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  210
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  326
/* YYNRULES -- Number of rules.  */
#define YYNRULES  964
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1738

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
    1492,  1492,  1509,  1512,  1514,  1512,  1526,  1528,  1526,  1543,
    1561,  1579,  1597,  1608,  1609,  1610,  1611,  1612,  1613,  1614,
    1615,  1616,  1617,  1618,  1619,  1620,  1621,  1622,  1623,  1624,
    1625,  1626,  1627,  1629,  1627,  1644,  1649,  1655,  1661,  1662,
    1666,  1667,  1671,  1675,  1682,  1683,  1694,  1698,  1701,  1709,
    1709,  1709,  1712,  1718,  1721,  1725,  1729,  1736,  1743,  1749,
    1753,  1757,  1760,  1763,  1771,  1774,  1782,  1788,  1789,  1790,
    1794,  1795,  1799,  1800,  1804,  1809,  1817,  1824,  1837,  1840,
    1843,  1853,  1853,  1853,  1856,  1856,  1856,  1861,  1861,  1861,
    1869,  1869,  1869,  1875,  1885,  1896,  1911,  1914,  1917,  1920,
    1926,  1927,  1934,  1945,  1946,  1947,  1951,  1952,  1953,  1954,
    1955,  1959,  1964,  1972,  1973,  1977,  1984,  1988,  1995,  1996,
    1997,  1998,  1999,  2000,  2001,  2005,  2006,  2007,  2008,  2009,
    2010,  2011,  2012,  2013,  2014,  2015,  2016,  2017,  2018,  2019,
    2020,  2021,  2022,  2023,  2024,  2025,  2029,  2035,  2042,  2054,
    2060,  2068,  2076,  2087,  2099,  2103,  2110,  2113,  2113,  2113,
    2118,  2118,  2118,  2131,  2135,  2139,  2145,  2153,  2161,  2172,
    2181,  2187,  2195,  2195,  2195,  2202,  2206,  2215,  2223,  2231,
    2235,  2238,  2246,  2247,  2248,  2255,  2256,  2257,  2258,  2259,
    2260,  2261,  2262,  2263,  2264,  2265,  2266,  2267,  2268,  2269,
    2270,  2271,  2272,  2273,  2274,  2275,  2276,  2277,  2278,  2279,
    2280,  2281,  2282,  2283,  2284,  2285,  2286,  2287,  2288,  2289,
    2290,  2296,  2297,  2298,  2299,  2300,  2315,  2324,  2325,  2326,
    2327,  2328,  2329,  2330,  2331,  2332,  2333,  2334,  2335,  2336,
    2337,  2340,  2340,  2340,  2343,  2348,  2352,  2356,  2356,  2356,
    2361,  2364,  2368,  2368,  2368,  2373,  2376,  2377,  2378,  2379,
    2380,  2381,  2382,  2383,  2384,  2386,  2390,  2391,  2396,  2402,
    2408,  2417,  2420,  2423,  2432,  2433,  2434,  2435,  2436,  2437,
    2438,  2442,  2446,  2450,  2454,  2458,  2462,  2466,  2470,  2474,
    2481,  2482,  2486,  2487,  2488,  2492,  2493,  2497,  2498,  2499,
    2503,  2504,  2508,  2520,  2523,  2524,  2528,  2528,  2547,  2546,
    2561,  2560,  2577,  2589,  2598,  2608,  2609,  2610,  2611,  2612,
    2616,  2619,  2628,  2629,  2633,  2636,  2640,  2653,  2662,  2663,
    2667,  2670,  2674,  2687,  2688,  2692,  2698,  2704,  2713,  2716,
    2723,  2726,  2732,  2733,  2734,  2738,  2739,  2743,  2750,  2755,
    2764,  2770,  2774,  2785,  2792,  2801,  2804,  2807,  2814,  2818,
    2824,  2836,  2839,  2844,  2856,  2857,  2861,  2862,  2863,  2867,
    2870,  2873,  2873,  2893,  2896,  2896,  2914,  2919,  2927,  2928,
    2932,  2935,  2948,  2965,  2966,  2967,  2972,  2972,  2998,  2999,
    3006,  3019,  3020,  3021,  3025,  3035,  3038,  3044,  3045,  3049,
    3050,  3054,  3055,  3059,  3061,  3066,  3059,  3082,  3083,  3087,
    3088,  3092,  3098,  3099,  3100,  3101,  3105,  3106,  3107,  3111,
    3114,  3120,  3122,  3127,  3120,  3148,  3155,  3160,  3169,  3175,
    3179,  3190,  3191,  3192,  3193,  3194,  3195,  3196,  3197,  3198,
    3199,  3200,  3201,  3202,  3203,  3204,  3205,  3206,  3207,  3208,
    3209,  3210,  3211,  3212,  3213,  3214,  3215,  3216,  3220,  3221,
    3222,  3223,  3224,  3225,  3226,  3227,  3231,  3242,  3246,  3253,
    3265,  3272,  3278,  3287,  3292,  3302,  3312,  3322,  3335,  3336,
    3337,  3338,  3339,  3343,  3347,  3347,  3347,  3361,  3362,  3366,
    3370,  3377,  3380,  3383,  3386,  3392,  3395,  3409,  3410,  3414,
    3415,  3416,  3417,  3418,  3418,  3418,  3422,  3427,  3434,  3441,
    3441,  3448,  3448,  3455,  3459,  3463,  3468,  3473,  3478,  3483,
    3487,  3491,  3496,  3500,  3504,  3509,  3509,  3509,  3515,  3522,
    3522,  3522,  3527,  3527,  3527,  3533,  3533,  3533,  3538,  3543,
    3543,  3543,  3548,  3548,  3548,  3557,  3562,  3562,  3562,  3567,
    3567,  3567,  3576,  3581,  3581,  3581,  3586,  3586,  3586,  3595,
    3595,  3595,  3601,  3601,  3601,  3610,  3613,  3624,  3640,  3642,
    3647,  3652,  3640,  3678,  3680,  3685,  3691,  3678,  3717,  3719,
    3724,  3729,  3717,  3770,  3771,  3772,  3773,  3774,  3775,  3776,
    3780,  3781,  3782,  3783,  3784,  3788,  3795,  3802,  3808,  3814,
    3821,  3828,  3834,  3843,  3846,  3852,  3860,  3865,  3872,  3877,
    3883,  3884,  3888,  3889,  3893,  3893,  3893,  3901,  3901,  3901,
    3908,  3908,  3908,  3919,  3919,  3919,  3926,  3926,  3926,  3937,
    3943,  3943,  3943,  3957,  3976,  3976,  3976,  3986,  3986,  3986,
    4000,  4000,  4000,  4014,  4023,  4023,  4023,  4043,  4050,  4050,
    4050,  4060,  4063,  4074,  4080,  4103,  4111,  4131,  4156,  4157,
    4161,  4162,  4167,  4170,  4180
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
  "alias_declaration", "distinct_alias", "optional_public_or_private_enum",
  "enum_name", "optional_enum_basic_type_declaration", "optional_commas",
  "emit_commas", "optional_emit_commas", "enum_declaration", "$@51",
  "$@52", "$@53", "optional_structure_parent", "optional_sealed",
  "structure_name", "class_or_struct",
  "optional_public_or_private_structure",
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

#define YYPACT_NINF (-1566)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-857)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1566,    39, -1566, -1566,    83,   -74,   -70,   691, -1566,    50,
   -1566, -1566, -1566, -1566,   206,   236, -1566, -1566, -1566, -1566,
     140,   140,   140, -1566,   321, -1566,    64, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566,   -67, -1566,   -58,
     -50,    13, -1566,   299,   299, -1566, -1566, -1566,    85,   140,
     140, -1566, -1566,    64,   691,   691,   691,   163,   192, -1566,
   -1566, -1566, -1566,   236,   236,   236,   247, -1566,   582,   -62,
   -1566, -1566, -1566, -1566,   242, -1566,   597, -1566,   775,    84,
      83,   327,   -74,   205, -1566,   283,   319,   560,    54,   343,
   -1566, -1566,   814,   359,   377,   427, -1566,   451,   470, -1566,
   -1566,   161,    83,   236,   236,   236,   236,   408, -1566,   835,
     838,   449,   556,   840, -1566, -1566,   488, -1566, -1566,   551,
   -1566, -1566, -1566,   805,   117, -1566, -1566, -1566, -1566,   299,
     299,   547,   299,   601,   625,   643, -1566, -1566,   639,   718,
   -1566, -1566,   636,   666,   408,   408, -1566, -1566,   733, -1566,
     248, -1566,   730,   774,   582, -1566,   752, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566,   760, -1566, -1566, -1566, -1566, -1566,
   -1566,   787, -1566, -1566, -1566, -1566,   819, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566,   251,   547,   547,   547, -1566, -1566,
     876,  8794,  8794,   873, -1566,   633,   797, -1566, -1566, -1566,
   -1566, -1566,  9538, -1566,   766,   859,   224,    83,   801,   802,
   -1566, -1566, -1566,   117, -1566, -1566,   798,   804,   809,   781,
     812,   817, -1566, -1566, -1566,   782, -1566, -1566, -1566, -1566,
   -1566,    95, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566, -1566,   818, -1566, -1566, -1566,   827,   830, -1566,
   -1566, -1566, -1566,   844,   845,   826,   206,   378, -1566, -1566,
   -1566, -1566,   339,   829,   852,   852, -1566, -1566, -1566, -1566,
   -1566, -1566,   866, -1566,   828,   831,  8891, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566,   998,   999, -1566,   834, -1566,   408,  1025,   797,
   -1566,   872,   408, -1566, -1566,   787,   408,    83, -1566,   599,
   -1566, -1566, -1566, -1566, -1566,  7567, -1566, -1566,   882,   867,
     -49,   -48,   -32, -1566, -1566,  7567,   389, -1566,  5637, -1566,
   -1566, -1566,    23, -1566, -1566, -1566,    10, -1566,  5830,   841,
    8602, -1566,   847, -1566, -1566,  9476,  9631, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566,   886,   851, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566,  1033, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566,   891,   860, -1566, -1566,   -35,   -11,
     -34, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
     853,   885, -1566,    31, -1566,   408,   899,  8794, -1566,   392,
    8794,  8794,  8794,   884,   887, -1566, -1566,   131,   206,   890,
      55, -1566,   424,   877,   896,   898,   880,   901,   889,   445,
     906, -1566,   497,    38,   910,  8333,  8333,   443,   892,   894,
     900,   903,   905,   911, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566, -1566,  8333,  8333,  8333,  8333,  8333,  3707,  4479,
   -1566, -1566, -1566, -1566, -1566, -1566,   912, -1566, -1566, -1566,
   -1566,   893, -1566, -1566,   178,   178, -1566,   178,   178,   913,
    1743, -1566, -1566,   915, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566,  8794,  8794,   917,   920,  8794,   834,  8794,   834,
    8794,   834,  8889,   956,   919, -1566,  5637, -1566,  8794,  7567,
     924,   953, -1566, -1566, -1566, -1566, -1566,   928, -1566, -1566,
     929,  6023, -1566,   339, -1566,  8889,   956, -1566, -1566, -1566,
   -1566, -1566, -1566,  9689,   776,   509,   931, -1566,    74,   934,
     -90,   938,  8794,  8794, -1566,  7951, -1566, -1566, -1566, -1566,
     206, -1566,   594,   935,  1099,   661, -1566, -1566, -1566,   345,
   -1566, -1566, -1566,  7567,   267,   482,   964,   543, -1566, -1566,
   -1566, -1566,   943, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566,   518, -1566,   967,   968,   969, -1566,  5637,  8794,
    7567,  7567, -1566, -1566,  7567, -1566,  7567, -1566,  5637, -1566,
   -1566,  5637,   971, -1566,  8794,   365,   365,   954,   955,    98,
   -1566, -1566,  7567,  7567,  7567,  7567,  7567,  7567,   789,   365,
     365,   -55,   365,   365,   957,  1142,   961,   970,   -21,   953,
     983,   960,   408,  3321,   236,  1165, -1566, -1566,   893, -1566,
   -1566, -1566, -1566, -1566,  9385,  9416,  8333,  8333, -1566, -1566,
    8333,  8333,  8333,  8333,  1011,  8333,    28,  7567,  8333,  8333,
    8333,  8333,  7567,  8333,  8333,  8333,  8333,  8142,  8333,  8333,
    8333,  8333,  8333,  8333,  8333,  8333,  8333,  8333,  9598,  7567,
    4672,   637,   680, -1566, -1566,  1012,   681,   -11,   725,   -11,
     728,   -11,   -31, -1566,   492,   852,  1000, -1566,   575, -1566,
    8794,   953,   616,   852, -1566, -1566,  6216, -1566, -1566, -1566,
   -1566,   982,  1016, -1566,   140, -1566,   140, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566, -1566,  7567, -1566, -1566,   352,   -39,
     -39,   -39, -1566,   852,   852,  8333,  1833, -1566,  1020, -1566,
   -1566, -1566, -1566,  7567,  1022,   563,  8794,   392, -1566,  7567,
     140, -1566, -1566, -1566, -1566, -1566, -1566, -1566,  8794,  8794,
    8794,  8794,  3900,  1027,  7567,  8794, -1566, -1566, -1566,  8794,
     953,  1007, -1566,  1014,   990,  8794,  8794,   991,  8794,   992,
    8794,   953,  8794,  8889,   953, -1566,   956,   309,  7567,  7567,
    8794,   834,   993,   994,   995,  1001,  1003,  1006, -1566,  7567,
     778,   109,  1009, -1566,  7567, -1566,  7567, -1566,  7567,  1015,
     532, -1566, -1566,  6409,   209,  3514, -1566,   259,  1017,   240,
    1010,   834,  2060,  1165,  1032,  1019, -1566, -1566,  1040,  1021,
   -1566, -1566,   980,   980,   552,   552,  1206,  1206,  1023,   190,
    1030, -1566,  1028,   197,   197,   915,   980,   980,  1833, -1566,
   -1566,  9140,  9025,  9111,  1833,  9507,  1513,  1550,  9226,  9255,
     552,   552,   750,   750,   190,   190,   190,   565,  7567,  1035,
    1036,   605,  7567,  1201,  1041,  1044, -1566,   301, -1566, -1566,
   -1566,   104, -1566,  1051, -1566,  1063, -1566,  1084,  8794, -1566,
    8889,  8794, -1566,   956,   631,  1066,  1069,  8794,  7567, -1566,
   -1566,  1096,   335, -1566,  8697, -1566,   237, -1566,  1070,  1073,
    1233, -1566, -1566,   113, -1566, -1566, -1566,  8996,  2285,  1102,
   -1566,   335,    30,  1077, -1566,  1079,  1239,   345,  7567,   140,
   -1566, -1566, -1566, -1566,   852,  1024,  1170,   731,   628,   356,
    1081,  1082,   646,  1083,   747,  8794,  8889,   956,  1244,  1085,
    1087,  8794,  7567,  1092, -1566,  1310,  1376, -1566,  1384, -1566,
    1413,  1093,  1593,   652,  1094,  8794,   687,  1165,  1097,  1098,
    1872,   -11, -1566, -1566, -1566, -1566, -1566,  1088,  1109,  1100,
    1256,  1138,    17,   109,  1107, -1566, -1566, -1566,  1110,   400,
    1111,  1103,  1014,   401, -1566,  1112,   260,  4865, -1566, -1566,
   -1566,   246,   -11, -1566,  6602, -1566,  1113,  6795,  1149,  1151,
   -1566,   140,  1159,  6988,    99,  7181, -1566, -1566, -1566,   140,
     140,  1308, -1566,   941, -1566, -1566,  1306, -1566, -1566,  1312,
   -1566,  1285,   140, -1566,   140,   140,   140,   140,   140, -1566,
    1262, -1566,   140,  8432,   834, -1566,  7567, -1566,  7567,  4093,
    7567, -1566,  1160,  1129, -1566, -1566,  8333,  1143, -1566,  1147,
    7567,  4286,  1148, -1566,  1154, -1566,  5058, -1566,  6216, -1566,
   -1566, -1566,  1184, -1566,  1187, -1566, -1566, -1566, -1566, -1566,
   -1566,   852, -1566, -1566,   852, -1566, -1566,  1069, -1566, -1566,
     852, -1566,  7567, -1566,   578, -1566, -1566, -1566,  1150, -1566,
    1152, -1566,  7567,  1191,   564,  8794, -1566,  7567,  1153,  7567,
     629, -1566,  1192, -1566, -1566,  1351,   787, -1566,  7567,  1197,
   -1566,  7567,   140, -1566, -1566, -1566, -1566,  1161, -1566, -1566,
   -1566,  1163,  1202, -1566, -1566,  1913,   690,   700, -1566, -1566,
    7567,  2214, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566,  2224, -1566,   139, -1566, -1566, -1566,  1183,  5251,
   -1566,  1196,  7567,  1208, -1566,   364,  5637,   165,    27,   403,
    7567,  7567,  7567,   109, -1566, -1566, -1566,   532,  1171,  3514,
     369,  1210,  1211,  1175,  1213,  1215, -1566,   380,   408,  7567,
   -1566,  1368,  7567, -1566,  1207,  1209, -1566,  1217,  1226, -1566,
    1113,  7567, -1566, -1566, -1566, -1566,  1185, -1566, -1566,  1194,
     -57,   -57,  1195, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
     201, -1566,  8333,  8333,  8333,  8333,  8333,  8333,  8333,  8333,
    8333,  8333,  7567,  8333,  8333,  8333,  8333,  8333,  8333,  8333,
     -11,  8794,  1198,  8794,  1199,  3514, -1566,   383,   387,  1200,
   -1566,  7567,  8996,  7567, -1566,  1204,  3514, -1566,   391,   394,
    7567, -1566, -1566, -1566,   406, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566, -1566,  1222, -1566,  1178, -1566, -1566,  1219, -1566,
    1212,  1357,   234, -1566,  1367, -1566, -1566,  1203,  1234,   842,
    1345,   140,  1220, -1566,   140, -1566,  1214,  1218, -1566, -1566,
    7567,  1230, -1566, -1566, -1566, -1566,  1228,  1229,  1231,  1238,
    1240,  1241,  1245,  1371,  1247, -1566,  1248,  7374,  1113,   464,
   -1566, -1566,   407, -1566, -1566,  1249, -1566,  1286, -1566,   410,
    1252,  1412,  1138,  5637,  7567,  7567,  1253, -1566, -1566,    47,
   -1566,   264, -1566, -1566, -1566,  1293, -1566, -1566,   246, -1566,
     -34, -1566,  1113, -1566,  8794,  7567, -1566, -1566, -1566, -1566,
    2493,  7567,  7567,    83,   801,  1258,  1260,  7567,  1138, -1566,
   -1566, -1566,  1743,  1743,  1743,  1743,  1743,  1743,  1743,  1743,
    1743,  1743,  1743, -1566, -1566,  1743,  1743,  1743,  1743,  1743,
    1743,  1743,   408,  2422, -1566,   749, -1566,   265,  5444, -1566,
   -1566, -1566,  8794,  1261,  1263, -1566,   313,  5444, -1566, -1566,
    1265, -1566,  7567, -1566, -1566,  7567,  1298,  7567, -1566, -1566,
   -1566,  8794, -1566, -1566,   664, -1566,    42, -1566, -1566, -1566,
    1371,  1371,  1266,  1268,  1270,  1273,  1274,  5637, -1566,  7567,
    7567,  7567,  7567,  5637, -1566, -1566,  1371,  1275,  1371, -1566,
    1278, -1566, -1566,   464, -1566,  1296, -1566, -1566,  1272,  7567,
    1317,   425,   437, -1566, -1566,   413,  5637,  1280,  1281, -1566,
   -1566, -1566,   852, -1566,  1277,  1289,  1292,   360,   109,  7567,
    1294,   440,   147,   -34, -1566, -1566,  1295,   457,   763, -1566,
   -1566,  1299,   463, -1566, -1566,  1302, -1566, -1566,  1282,   214,
    1455,    42, -1566, -1566,   842,   -16,   -16, -1566,  7567,  1371,
    1371,   628,  1303,  1304,  1307,  1311,  1313,   953,   -16,  1371,
     628, -1566, -1566, -1566,  7567,  1314, -1566, -1566,  1290,  7567,
    7567,   471, -1566, -1566,  1367,  1487,   408, -1566,    60,  1319,
     408,   668, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,  1455,   352,
     628,  1326,  1334, -1566,  1320,  1321,  1322,   -16,   -16,  1326,
    1323, -1566, -1566, -1566, -1566, -1566,  1325,  1327,   628,  1328,
    1305, -1566,  7567, -1566, -1566,  1309, -1566,  7760,   140, -1566,
    5637,   408,  1113,  8794,   392, -1566,  2701,  9538, -1566, -1566,
   -1566, -1566,   473,  1331, -1566, -1566, -1566, -1566,  1333,  1336,
   -1566, -1566, -1566,  1337, -1566,  1489,  1342,  1305,  7567, -1566,
   -1566, -1566, -1566, -1566,  1743, -1566,  1338,   498,  1113, -1566,
     962,  7567,  1339,   140,  9538, -1566,   628, -1566, -1566, -1566,
    7567, -1566,  1343,  1305, -1566,   744,  7760,   408, -1566,  7567,
     140, -1566, -1566,   408,   502, -1566, -1566,  1340, -1566,   408,
   -1566, -1566,  1347, -1566,   140,  1113,   140, -1566,   -34, -1566,
   -1566,  2909, -1566,  7567, -1566, -1566, -1566, -1566,  1346,  1348,
    1353,  1367, -1566, -1566,  7760,   408, -1566, -1566,   140, -1566,
    3117, -1566,  1348,  1354,   744,  1367, -1566, -1566
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,   171,     1,   370,     0,     0,    58,   683,   371,     0,
     878,   868,   873,    20,     0,     0,    19,    16,    15,     3,
       0,     0,     0,     8,   721,     7,   664,     6,    11,     5,
       4,    13,    12,    14,   136,   137,   135,   145,   147,    49,
      67,    64,    65,     0,     0,    50,   685,   684,     0,     0,
       0,    26,    25,   664,   683,   683,   683,     0,   344,    47,
     155,   156,   157,     0,     0,     0,   158,   160,   167,     0,
     154,    21,    10,     9,   293,   703,     0,   665,   666,     0,
       0,     0,     0,     0,    51,     0,     0,    59,    62,   686,
     688,   689,    22,     0,     0,     0,   346,     0,     0,   166,
     161,     0,     0,     0,     0,     0,     0,    76,   294,   296,
     691,   713,   712,   716,   668,   667,   674,   143,   144,     0,
     141,   142,   139,     0,     0,   138,   148,    68,    66,     0,
       0,    52,     0,     0,     0,     0,    63,    60,     0,     0,
      23,    24,    27,   778,    76,    76,   345,    45,    48,   165,
       0,   162,   163,   164,   168,    74,    77,   172,   298,   297,
     300,   295,   693,   692,     0,   715,   714,   718,   717,   722,
     669,   590,   140,    30,    31,    35,     0,   131,   132,   129,
     130,   128,   127,   133,     0,    54,    55,    53,    57,    56,
      62,     0,     0,     0,    29,     0,   701,   869,   874,    46,
     159,    75,     0,   694,   695,   709,   671,     0,   591,     0,
      32,    33,    34,     0,   146,    61,     0,     0,     0,     0,
       0,     0,   731,   751,   732,   767,   733,   737,   738,   739,
     740,   757,   744,   745,   746,   747,   748,   749,   750,   752,
     753,   754,   755,   838,   736,   743,   756,   845,   852,   734,
     741,   735,   742,     0,     0,     0,     0,   766,   799,   802,
     800,   801,   865,   795,   690,   687,    28,   781,   782,   779,
     780,   699,   702,   879,     0,     0,     0,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,     0,     0,   179,   173,   267,    76,     0,   701,
     710,     0,    76,   673,   670,   590,    76,     0,   653,   645,
     675,   134,   803,   829,   832,     0,   835,   825,     0,     0,
     839,   846,   853,   859,   862,     0,   797,   809,   338,   815,
     820,   814,     0,   828,   824,   817,     0,   819,     0,   796,
       0,   700,     0,   870,   875,   258,   259,   256,   182,   183,
     185,   184,   186,   187,   188,   189,   215,   216,   213,   214,
     206,   217,   218,   207,   204,   205,   257,   240,     0,   255,
     219,   220,   221,   222,   193,   194,   195,   190,   191,   192,
     203,     0,   209,   210,   208,   201,   202,   197,   196,   198,
     199,   200,   181,   180,   239,     0,   211,   212,   590,   176,
       0,   758,   761,   764,   765,   759,   762,   760,   763,   696,
       0,   707,   723,     0,   149,    76,     0,     0,   646,     0,
       0,     0,     0,     0,     0,   491,   492,     0,     0,     0,
       0,   485,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   757,     0,     0,     0,     0,     0,   405,     0,     0,
       0,     0,     0,     0,   579,   418,   420,   419,   421,   422,
     423,   424,    41,     0,     0,     0,     0,     0,   338,     0,
     403,   404,   953,   489,   488,   566,   486,   559,   558,   557,
     556,   169,   562,   487,   561,   560,   533,   493,   534,     0,
     482,   538,   494,     0,   490,   890,   892,   891,   483,   894,
     893,   484,     0,     0,     0,   784,     0,   173,     0,   173,
       0,   173,     0,     0,     0,   811,     0,   808,     0,     0,
       0,   960,   396,   822,   823,   816,   818,     0,   821,   792,
       0,     0,   867,   866,   880,   624,   630,   260,   262,   261,
     263,   254,   238,   264,   241,   223,     0,   174,   369,   615,
     616,     0,     0,     0,   299,     0,   306,   400,   301,   704,
       0,   711,     0,     0,   647,   645,   672,   150,   654,     0,
     643,   644,   642,     0,     0,     0,     0,   789,   914,   917,
     349,   766,   353,   352,   358,   883,   889,   884,   885,   886,
     888,   887,     0,   390,     0,     0,     0,   944,     0,     0,
       0,     0,   381,   384,     0,   387,     0,   948,     0,   926,
     930,     0,     0,   920,     0,   521,   522,     0,     0,   457,
     454,   456,     0,     0,     0,     0,     0,     0,     0,   498,
     497,   535,   496,   495,     0,     0,     0,     0,   344,   960,
     960,     0,    76,     0,     0,   413,   405,   335,   169,   312,
     310,   311,   309,   806,     0,     0,     0,     0,   523,   524,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   472,     0,
       0,     0,     0,   768,   783,     0,     0,   176,     0,   176,
       0,   176,   344,   622,     0,   620,     0,   628,     0,   769,
       0,   960,     0,   342,   397,   807,   961,   339,   813,   791,
     794,     0,   773,   625,    94,   631,    94,   265,   266,   243,
     244,   246,   245,   247,   248,   249,   250,   242,   251,   252,
     253,   227,   228,   230,   229,   231,   232,   233,   234,   225,
     226,   235,   236,   237,   224,     0,   367,   368,     0,   590,
     590,   590,   175,   178,   177,     0,   401,   335,   680,   708,
     719,   603,   724,     0,     0,     0,     0,     0,   661,     0,
       0,   804,   830,   833,    18,    17,   787,   788,     0,     0,
       0,     0,   912,     0,     0,     0,   934,   937,   940,     0,
     960,     0,   951,   960,     0,     0,     0,     0,     0,     0,
       0,   960,     0,     0,   960,   923,     0,     0,     0,     0,
       0,   173,     0,     0,     0,     0,     0,     0,    44,     0,
      42,     0,     0,   933,     0,   634,     0,   633,     0,     0,
     961,   905,   526,   340,     0,   338,   475,     0,     0,     0,
       0,   173,     0,   413,     0,     0,   545,   544,     0,     0,
     546,   550,   499,   500,   512,   513,   510,   511,     0,   539,
       0,   531,     0,   563,   564,   565,   501,   502,   568,   569,
     570,   517,   518,   519,   520,     0,     0,   515,   516,   514,
     508,   509,   504,   503,   505,   506,   507,     0,     0,     0,
     463,     0,     0,     0,     0,     0,   480,     0,   836,   826,
     770,     0,   840,     0,   847,     0,   854,     0,     0,   860,
       0,     0,   863,     0,     0,     0,   797,     0,     0,   398,
     793,   774,   697,    92,    95,   871,    95,   876,     0,     0,
     725,   612,   613,   635,   617,   619,   618,   402,     0,   676,
     681,   697,   606,     0,   649,     0,   650,     0,     0,     0,
     663,   805,   831,   834,   790,     0,     0,     0,   913,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   961,     0,   536,     0,     0,   537,     0,   567,
       0,     0,     0,     0,     0,     0,     0,   413,     0,     0,
       0,   176,   574,   575,   576,   577,   578,     0,    38,     0,
     110,     0,     0,     0,     0,   896,   895,   525,     0,     0,
       0,     0,   960,     0,   476,     0,     0,     0,   479,   477,
     170,     0,   176,   337,   361,   359,     0,     0,     0,     0,
     360,     0,     0,     0,    76,     0,   332,   417,   313,     0,
       0,     0,   326,     0,   327,   321,     0,   318,   317,     0,
     319,     0,     0,   336,     0,    90,    91,    88,    89,   328,
     373,   316,     0,   425,   173,   541,     0,   547,     0,     0,
       0,   529,     0,     0,   551,   555,     0,     0,   532,     0,
       0,     0,     0,   464,     0,   473,     0,   527,     0,   481,
     837,   827,     0,   785,     0,   841,   843,   848,   850,   855,
     857,   621,   861,   623,   627,   864,   629,   797,   798,   810,
     343,   399,     0,   678,   698,   881,    93,   626,     0,   632,
       0,   614,     0,     0,     0,     0,   636,     0,     0,     0,
     698,   705,     0,   604,   720,     0,   590,   648,     0,     0,
     658,     0,     0,   662,   915,   918,   350,     0,   355,   356,
     354,     0,     0,   393,   391,     0,     0,     0,   945,   943,
     340,     0,   952,   955,   382,   385,   388,   949,   947,   927,
     931,   929,     0,   921,    76,   455,   589,   458,     0,     0,
      39,     0,     0,     0,   374,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   954,   341,   478,     0,     0,   338,
       0,     0,     0,     0,     0,     0,   411,     0,    76,     0,
     362,     0,     0,   347,     0,     0,   331,     0,     0,    71,
       0,     0,   364,   335,   329,   330,     0,    83,    84,     0,
     151,   151,     0,   320,   315,   322,   323,   324,   325,   372,
       0,   314,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     176,     0,     0,     0,     0,   338,   449,     0,     0,     0,
     552,     0,   540,     0,   530,     0,   338,   465,     0,     0,
       0,   528,   474,   470,     0,   772,   786,   771,   844,   851,
     858,   812,   775,   776,   679,     0,   872,   877,     0,   727,
       0,   728,   638,   637,   302,   677,   682,     0,     0,   597,
     600,     0,     0,   652,     0,   660,     0,     0,   351,   357,
       0,     0,   392,   935,   938,   941,     0,     0,     0,     0,
       0,     0,     0,   912,     0,   924,     0,     0,     0,     0,
     461,   580,     0,    36,    43,     0,   112,     0,   113,     0,
       0,   114,     0,     0,     0,     0,     0,   898,   897,     0,
     446,     0,   448,   408,   409,     0,   407,   406,     0,   414,
       0,   363,     0,   348,     0,     0,    69,    70,   120,   365,
       0,     0,     0,     0,   153,     0,     0,     0,     0,   655,
     379,   378,   437,   438,   440,   439,   441,   431,   432,   433,
     442,   443,   427,   428,   429,   430,   444,   445,   434,   435,
     436,   426,    76,     0,   588,     0,   586,     0,     0,   450,
     453,   583,     0,     0,     0,   582,     0,     0,   466,   469,
       0,   471,     0,   882,   726,     0,     0,     0,   303,   308,
     706,     0,   598,   599,   600,   601,   592,   607,   651,   659,
     912,   912,     0,     0,     0,     0,     0,   338,   956,   340,
       0,     0,     0,     0,   913,   928,   912,     0,   912,   571,
       0,   573,   459,     0,   581,    40,   111,   375,     0,     0,
       0,     0,     0,   900,   899,     0,     0,     0,     0,   412,
     415,   366,   126,   125,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   542,   548,     0,     0,     0,   587,
     585,     0,     0,   584,   777,     0,   730,   639,     0,     0,
     595,   592,   593,   594,   597,   911,   911,   394,     0,   912,
     912,   903,     0,     0,     0,     0,     0,   960,   911,   912,
     903,   572,   462,    37,     0,     0,   116,   117,     0,     0,
       0,     0,   447,   410,   302,    85,    76,   152,     0,     0,
      76,   645,   380,   656,   657,   416,   543,   549,   451,   452,
     553,   467,   468,   729,   335,   605,   596,   608,   595,     0,
       0,   908,   960,   910,     0,     0,     0,   911,   911,   904,
       0,   946,   957,   383,   386,   389,     0,     0,   903,     0,
     958,   115,     0,   902,   901,     0,   334,     0,     0,   107,
       0,    76,     0,     0,     0,   554,     0,     0,   610,   641,
     640,   602,     0,   961,   909,   916,   919,   395,     0,     0,
     942,   950,   932,     0,   922,     0,     0,   958,     0,    86,
      90,    91,    88,    89,    87,   109,    99,     0,     0,   124,
       0,     0,     0,     0,     0,   906,     0,   936,   939,   925,
       0,   962,     0,   958,    96,    78,     0,    76,   122,     0,
       0,   305,   609,    76,     0,   959,   963,     0,   335,    76,
      72,    73,     0,   108,     0,     0,     0,   377,     0,   907,
     964,     0,    79,     0,   100,   119,   376,   611,     0,   104,
       0,   302,   101,    80,     0,    76,    98,   335,     0,    81,
       0,   105,   104,     0,    78,   302,    82,   103
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1566, -1566,  -906,    -1, -1566, -1566, -1566, -1566, -1566,   925,
    1471, -1566, -1566, -1566, -1566, -1566, -1566,  1563, -1566, -1566,
   -1566,    53, -1566, -1566,  1379, -1566, -1566,  1484, -1566, -1566,
   -1566, -1566,  -141,  -164, -1566, -1566, -1566, -1566, -1565,   839,
     843, -1566, -1566, -1566, -1566,  -158, -1566, -1566, -1566, -1566,
   -1566, -1566, -1566, -1005, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566,  1363, -1566, -1566,   -46,   -96,  -280,   326, -1566,
   -1566,   588,   926,   930,   624,  -477,  -679, -1566,  -302, -1566,
   -1566, -1566, -1448, -1566, -1566, -1466, -1566, -1566, -1033, -1566,
   -1566, -1566, -1566, -1566, -1566,  -763,  -333, -1155,   858,   -13,
   -1566, -1566, -1566, -1566, -1566, -1564, -1561, -1559, -1555, -1566,
   -1566,  1586, -1566, -1074, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566,  -444, -1373,   520,
     203, -1566,  -804, -1566,   281, -1566, -1566, -1566, -1566, -1298,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,   371,
     569, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,  -163,
      48,    -6,    51,   134, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566,   227,  -523,  -765, -1566,  -517,  -762, -1566,  -942,     0,
       2, -1566,  -569,  -568, -1566, -1566, -1566, -1227, -1566,  1549,
   -1566, -1566, -1566, -1566, -1566,   454,   644, -1566,   965, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566,   645, -1566,  1300, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566,    25, -1566,  1173, -1566, -1566, -1566,
    1377, -1566, -1566, -1566,  -546, -1566, -1566,  -341,  -891, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,  -168, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566,  -843, -1495,  -622, -1566,
   -1566, -1268, -1257,  1174, -1566, -1566, -1566, -1566, -1566, -1566,
   -1566, -1566, -1566, -1566,  1176, -1566, -1566,  1177, -1566, -1566,
   -1566, -1566, -1566, -1566, -1566, -1566, -1566, -1566,   997, -1566,
    -422,  1179, -1321,  -623,  1180,  -421
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,   796,   797,    18,   142,    53,   194,    19,   176,
     182,  1495,  1201,  1363,   638,   483,   148,   484,    98,    21,
      22,    87,    44,    45,   137,    23,    41,    42,  1059,  1060,
    1702,   156,   157,  1703,  1719,  1732,  1249,  1628,  1061,   944,
     945,  1685,  1698,  1718,  1686,  1723,  1727,  1733,  1724,  1062,
    1063,  1666,  1064,  1022,  1065,  1066,  1067,  1068,  1069,  1070,
    1071,  1072,   183,   184,    37,    38,    39,   208,  1405,    66,
      67,    68,    69,   655,    24,   409,   564,   305,   306,   109,
      25,   160,   307,   161,   202,  1459,  1538,  1672,   567,   777,
    1148,   485,  1073,  1243,  1514,   862,   646,  1031,   722,   486,
    1074,   592,   801,  1338,   487,  1075,  1076,  1077,  1078,  1079,
     768,  1080,  1260,  1205,  1410,  1081,   488,   815,  1349,   816,
    1350,   818,  1351,   489,   805,  1342,   490,   531,   568,   491,
    1226,  1227,   861,   492,   659,   493,  1082,   494,   495,   631,
     496,   830,  1359,   831,  1493,   497,   913,  1302,   498,   532,
     500,  1281,  1586,  1283,  1587,  1442,  1635,   501,   502,   558,
    1544,  1597,  1464,  1466,  1331,   962,  1156,  1637,  1674,   559,
     560,   561,   713,   714,   734,   717,   718,   736,   848,   951,
     952,  1641,   583,   429,   575,   319,  1522,   576,   320,    78,
     116,   206,   315,    27,   171,   960,  1134,   961,    48,    49,
     139,    28,    50,   164,   204,   309,  1135,   272,   273,    29,
     110,   778,  1327,   571,   311,   312,   113,   169,   782,    30,
      76,   205,   572,   953,   503,   419,   259,   260,   921,   942,
     196,   261,   705,  1306,   930,   586,   349,   262,   527,   263,
     430,   971,   528,   720,   513,  1111,   431,   972,   432,   973,
     512,  1110,   516,  1115,   517,  1308,   518,  1117,   519,  1309,
     520,  1119,   521,  1310,   522,  1122,   523,  1125,   715,    31,
      55,   274,   545,  1138,    32,    56,   275,   546,  1140,    33,
      54,   352,   732,  1315,   594,   504,   650,  1610,   651,  1602,
    1603,  1604,   981,   505,   799,  1336,   800,  1337,   826,  1356,
    1005,  1487,   822,  1353,   506,   823,  1354,   507,   985,  1474,
     986,  1475,   987,  1476,   809,  1346,   820,  1352,  1032,   652,
     508,   509,  1656,   727,   510,   511
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      17,    59,    70,   197,   198,   530,   150,   787,   209,   543,
     789,  1147,  1036,  1231,   958,   598,   601,  1510,  1208,    71,
      72,    73,   733,   264,   265,  1347,   849,   851,   923,   735,
     925,   858,   927,  1411,   126,   649,  1133,  1206,  -171,     2,
     707,   798,   709,   535,   711,  1129,     3,  1373,    90,    91,
      70,    70,    70,   548,   550,  1133,   533,   622,  1003,  1084,
     604,  1492,  1659,  1660,  1006,  1619,  1661,  1506,  1662,     4,
    1152,     5,  1663,     6,   676,   677,   135,  -842,  -849,     7,
    1630,   766,   721,   207,    40,   770,   579,  1212,  1542,     8,
      70,    70,    70,    70,  -856,     9,  1485,    88,   935,   117,
     118,   207,    34,    35,   565,   207,   845,    43,  1626,    79,
      97,   136,   846,   106,   556,   562,   771,    80,   556,    10,
      97,  1704,  1660,  1653,   767,  1661,    77,  1662,    81,  -842,
    -849,  1663,   177,   178,  -842,  -849,   433,   434,   131,   107,
     647,    11,    12,  1403,   698,   699,  -856,   928,  1543,  1033,
    1585,  -856,   423,  -842,  -849,   847,   440,   605,   606,  1728,
    1660,   316,   442,  1661,   810,  1662,   410,   563,   557,  1663,
    -856,   422,   933,   566,   821,   424,   937,   824,   257,   257,
     980,   573,   185,   186,   880,   187,  1600,   989,    82,  1673,
     993,   536,  1207,   881,  1220,  1562,   574,  1153,  1001,   449,
     450,  1004,  1207,  1194,   534,   314,    13,  1398,  1379,   857,
     537,   664,   665,  1545,  1546,    51,   258,   258,   968,   538,
     623,  1176,  1207,   119,  -460,  1177,  1693,    14,  1314,  1558,
      15,  1560,  1035,   452,   453,  1207,  1311,   607,  1154,    15,
     845,   133,   120,   336,  1314,    16,  1288,   121,    36,   122,
      89,   738,   123,   134,    52,  1726,   917,   608,  1299,  1019,
     889,   890,   584,   585,   587,   991,   155,  1375,   811,  1737,
      60,   425,    57,   195,  1020,   179,  -460,  -778,  1605,  1112,
     180,  -460,   181,   827,   577,   123,   124,  1113,  1144,   847,
    1617,  1145,  1607,  1608,  1146,  1584,    58,   573,  1501,    61,
    -460,   616,  1618,   103,   104,   105,   155,    13,   668,   669,
    1114,  1021,   574,   590,    13,  1370,   674,   656,   675,   676,
     677,   678,   679,   674,  1553,  1491,   676,   677,    96,    74,
    1371,   478,  1198,    97,  1521,  1717,  1682,   257,   482,  1648,
    1649,  1357,   339,    62,   701,   702,    16,    57,   706,   108,
     708,   573,   710,    16,  1011,  1582,  1167,    75,   979,  1511,
     723,   845,  1697,  1228,   149,   647,   574,  1372,    63,   340,
     341,    58,   339,  1221,  1033,   258,  1381,    57,   339,  1222,
    1457,    13,   480,   481,  1042,   657,   664,   665,   937,   698,
     699,    13,   129,   350,   773,   774,   698,   699,  1161,   340,
     341,    58,   716,  1408,    13,   340,   341,  1123,  1409,  1215,
     847,  1223,  1034,   350,   257,   106,  1126,   257,   257,   257,
      16,  1137,  1224,    80,   591,   602,   213,  1225,    64,  1139,
      16,    83,   313,   342,  1037,  1217,  1172,   343,    65,  1217,
    1217,  1040,  1437,    16,   630,   967,   350,    83,    84,   102,
     791,   200,   258,  1446,   214,   258,   258,   258,   975,   976,
     933,  1218,  1038,   342,    84,  1507,  1526,   343,   988,   342,
     130,    85,   580,   343,   995,   996,  1108,   998,   581,  1000,
    1400,  1002,    86,   668,   669,   127,   344,    85,  1217,  1010,
     345,   674,  1007,   346,   676,   677,   678,   679,    86,   257,
     257,   794,   949,   257,  1109,   257,   132,   257,   138,   257,
     795,   853,    13,  1578,  1531,   257,   344,   950,   347,   580,
     345,   582,   344,   346,   143,   581,   345,   845,   845,   346,
     845,  1108,   257,  1211,   846,    80,  1374,   258,   258,  1367,
     845,   258,   144,   258,  1217,   258,  1569,   258,   347,   257,
     257,    16,   723,   258,   347,  1388,   165,   779,  1438,  1168,
     337,  1577,  1217,  1570,   698,   699,  1447,  1368,   582,  1217,
     258,   525,  1382,   664,   665,   155,   847,   847,   788,   847,
     338,  1108,  1108,  1389,    57,  1108,  1439,   258,   258,   847,
    1440,   526,   145,   627,  1448,  1527,   257,  1449,   628,  1669,
    1367,  1432,   111,   112,  1532,    57,   609,  1280,    58,  1451,
    1494,   257,  1108,  1498,   627,  1367,   146,   751,   752,   753,
     754,   755,   756,   757,   758,   629,   610,   617,  1567,    58,
     974,   933,  1217,   977,   258,  1688,   759,   984,  1217,   147,
    1568,    70,   760,  1581,  1175,  1287,  1108,   618,  1217,   258,
    1181,    99,   100,   101,   761,   762,   763,  1298,   794,    13,
    1589,   350,  1304,   166,  1192,   792,  1592,   795,   666,   667,
     668,   669,  1715,  1108,  1625,   929,  1675,  1217,   674,   620,
     675,   676,   677,   678,   679,   764,   680,   681,  1028,   867,
     871,   151,   152,   153,   154,   170,   499,  1029,    16,   621,
     803,  1687,  1601,  1601,   885,  1709,   524,   257,  1609,   794,
      13,  1540,   267,   965,  1320,  1601,   172,  1609,   795,   540,
     804,  1097,   350,   914,   103,   104,   105,   268,   966,  1321,
    1098,  1465,   269,   943,   270,   943,   693,   694,   695,   696,
     697,   794,    13,  1313,   794,   258,   134,   133,    46,    16,
     795,   698,   699,   795,    47,  1362,  1699,  1642,   932,   134,
    1121,  1102,  1369,  1124,  1601,  1601,   188,  1700,  1701,  1130,
    1103,   664,   665,   257,   426,  1609,   660,   427,   661,   662,
     428,    16,   794,    13,   647,   257,   257,   257,   257,   970,
     189,   795,   257,  1033,   959,   794,   257,   794,    13,   936,
     780,   781,   257,   257,   795,   257,   795,   257,   190,   257,
     257,   258,   794,    13,  1127,   191,   350,   257,   794,    13,
     918,   795,    16,   258,   258,   258,   258,   795,   193,  1171,
     258,  1636,   114,  1694,   258,  1190,   785,    16,   115,   786,
     258,   258,   428,   258,   195,   258,  1633,   258,   258,   428,
    1423,  1424,    16,   794,    13,   258,   794,    13,    16,   350,
     350,  1058,   795,   919,   922,   795,   794,    13,   668,   669,
    1193,   140,   103,  1344,   105,   795,   674,   141,   675,   676,
     677,   678,   679,  1345,   739,   740,   741,   742,   743,   744,
     745,   746,   158,    16,   192,   162,    16,   167,   159,  1462,
     724,   163,   199,   168,   350,  1463,    16,   350,   924,   747,
     350,   926,   731,  1240,  1166,   257,   103,   257,   257,   201,
    1095,   748,   749,   750,   257,   203,   350,   207,   350,  1502,
    1174,   257,  1525,   136,  1616,  1711,   695,   696,   697,   266,
    1433,   317,   350,  1136,   308,  1136,  1590,   210,   211,   698,
     699,  1247,  1248,   258,   790,   258,   258,  1058,   173,   174,
     838,   839,   258,   271,  1730,   310,  1160,   318,  1163,   258,
    1404,  1404,   257,   257,   173,   174,   175,  1322,   257,  1644,
     322,   812,   814,   325,   328,   817,   323,   819,   210,   211,
     212,   324,   257,  1330,   326,   339,   954,   955,   956,   327,
     330,   664,   665,   832,   833,   834,   835,   836,   837,   331,
     258,   258,   332,  1634,   658,   658,   258,   658,   658,    93,
      94,    95,   340,   341,   625,   626,   333,   334,   335,   348,
     258,   350,   351,   406,   407,   353,   408,   421,   354,  1557,
     339,   541,   639,   640,   641,   642,   643,   514,   882,   515,
    1236,   551,   552,  1358,   544,   553,   554,   339,  1244,  1245,
     569,   555,  1571,   570,   578,  1671,   588,   340,   341,   589,
     915,  1253,   603,  1254,  1255,  1256,  1257,  1258,   612,   611,
     613,  1261,   614,   615,   340,   341,   342,  1390,   619,   580,
     343,   616,   624,   654,   632,   581,   633,   939,   668,   669,
     411,  1689,   634,   704,   412,   635,   674,   636,   675,   676,
     677,   678,   679,   637,   653,  1435,   663,   700,   413,   414,
     703,   716,   719,   415,   416,   417,   418,   725,   726,   728,
     729,   342,   257,   765,   776,   343,   948,   783,   582,   344,
     769,   772,   784,   345,  1552,   802,   346,   793,   342,   806,
     807,   808,   343,   825,   963,   842,   828,   829,   850,   841,
     969,  1335,   843,   852,   693,   694,   695,   696,   697,   860,
     258,   347,   844,   794,    13,   983,   878,   920,   931,   698,
     699,   941,   795,   940,   344,   959,  1667,   964,   345,   992,
     990,   346,   982,   994,   997,   999,  1012,  1013,  1014,  1008,
    1009,   344,  1105,   339,  1015,   345,  1016,  1164,   346,  1017,
    1018,  1023,  1041,    16,  1085,  1024,   347,  1025,  1027,  1026,
    1039,  1086,  1087,  1088,   812,  1089,  1512,   664,   665,  1091,
     340,   341,  1090,   347,  1116,   872,   873,  1100,  1101,   874,
     875,   876,   877,  1106,   879,  1107,  1118,   883,   884,   886,
     887,   888,   891,   892,   893,   894,   896,   897,   898,   899,
     900,   901,   902,   903,   904,   905,   906,  1120,   257,  1128,
     257,   526,  1132,  1141,  1528,  1142,  1143,   339,  1149,  1099,
    1157,  1158,  1159,  1104,  1169,  1170,  1173,  1200,  1179,  1180,
    1199,  1523,  1670,  1539,   342,  1183,  1188,  1191,   343,  1203,
    1195,  1196,  1202,  1204,   340,   341,   258,  1517,   258,  1131,
    1209,  1214,  1210,  1213,  1234,  1216,  1235,  1237,  1246,  1250,
     566,  1251,   666,   667,   668,   669,   670,  1252,  1259,   671,
    1467,  1291,   674,  1469,   675,   676,   677,   678,   679,  1162,
     680,   681,  1290,   339,   957,  1293,   630,   344,  1294,  1305,
    1300,   345,  1307,  1165,   346,  1301,  1319,  1328,  1316,  1329,
    1317,  1324,  1333,  1182,  1339,  1340,  1360,  1341,   342,  1364,
     340,   341,   343,  1366,  1380,  1383,  1384,  1385,  1386,   347,
    1387,   257,  1392,  1394,  1397,  1395,  1453,  1401,   691,   692,
     693,   694,   695,   696,   697,  1396,  1402,  1407,  1452,  1058,
    1456,  1434,  1436,  1441,  1458,   698,   699,  1445,   939,   339,
    1461,  1460,  1465,  1473,  1455,  1230,  1470,   339,  1233,   258,
    1471,   344,  1454,  1468,  1239,   345,  1242,  1178,   346,   257,
    1477,  1083,  1478,  1479,   342,  1629,   340,   341,   343,  1632,
    1480,  1484,  1481,  1482,   340,   341,   339,  1483,   257,  1486,
    1488,  1497,  1496,   347,  1499,  1500,  1505,  1282,  1508,  1284,
    1518,  1289,  1519,  1536,  1529,  1563,  1530,   258,  1533,  1547,
    1548,  1295,  1549,   340,   341,  1550,  1551,  1559,  1564,   939,
     630,  1561,  1566,  1572,  1573,  1574,   258,   344,  1596,  1594,
    1668,   345,  1575,  1184,   346,  1576,  1622,  1580,  1588,  1627,
     342,  1217,  1591,  1312,   343,  1593,  1611,  1612,   342,  1643,
    1613,  1655,   343,  1318,  1614,  1658,  1615,  1621,  1323,   347,
    1325,  1583,  1631,  1645,  1646,  1647,  1650,  1083,  1651,  1332,
    1652,  1654,  1334,  1676,   664,   665,  1677,   342,  1595,  1678,
    1679,   343,  1680,  1681,  1696,  1684,  1705,  1691,  1710,  1713,
     125,   812,  1708,   344,  1721,  1722,  1725,   345,  1712,  1185,
     346,   344,  1735,   840,    20,   345,   128,  1186,   346,   215,
    1736,   664,   665,  1365,  1734,   946,   321,  1406,   934,   947,
     859,  1376,  1377,  1378,  1729,   347,  1155,    26,   863,  1598,
     344,  1509,  1638,   347,   345,  1599,  1187,   346,  1541,  1639,
    1391,  1640,    92,  1393,  1326,  1150,  1151,   813,   329,   420,
     593,   595,  1399,   596,   597,     0,   599,   600,     0,     0,
     257,     0,   347,     0,     0,     0,   339,  1665,     0,   666,
     667,   668,   669,   670,     0,  1058,   671,   672,   673,   674,
       0,   675,   676,   677,   678,   679,     0,   680,   681,     0,
       0,   682,     0,   340,   341,   683,   684,   685,   258,     0,
       0,   686,  1443,     0,  1444,  1292,   666,   667,   668,   669,
     670,  1450,  1692,   671,   672,   673,   674,     0,   675,   676,
     677,   678,   679,     0,   680,   681,     0,     0,     0,  1707,
     687,  1096,   688,   689,   690,   691,   692,   693,   694,   695,
     696,   697,     0,  1714,     0,  1716,     0,     0,     0,     0,
    1058,  1472,   698,   699,     0,     0,     0,   342,     0,     0,
       0,   343,     0,     0,     0,     0,     0,  1731,  1490,  1058,
     689,   690,   691,   692,   693,   694,   695,   696,   697,     0,
       0,     0,     0,     0,     0,  1503,  1504,     0,     0,   698,
     699,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   664,   665,  1513,     0,     0,     0,
     344,     0,  1515,  1516,   345,     0,  1189,   346,  1520,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   347,     0,     0,     0,     0,     0,     0,   939,
       0,     0,     0,     0,     0,     0,     0,     0,   939,     0,
       0,     0,     0,  1534,     0,     0,  1535,     0,  1537,     0,
       0,  1412,  1413,  1414,  1415,  1416,  1417,  1418,  1419,  1420,
    1421,  1422,  1425,  1426,  1427,  1428,  1429,  1430,  1431,     0,
     812,  1554,  1555,  1556,   664,   665,     0,     0,     0,   666,
     667,   668,   669,   670,     0,     0,   671,   672,   673,   674,
    1565,   675,   676,   677,   678,   679,     0,   680,   681,     0,
       0,   682,     0,     0,     0,   683,   684,   685,     0,     0,
    1579,   686,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   339,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1606,
     687,     0,   688,   689,   690,   691,   692,   693,   694,   695,
     696,   697,   340,   341,     0,  1620,     0,     0,     0,     0,
    1623,  1624,   698,   699,     0,     0,   339,     0,     0,   666,
     667,   668,   669,   670,     0,     0,   671,   672,   673,   674,
       0,   675,   676,   677,   678,   679,     0,   680,   681,  1083,
       0,  -857,     0,   340,   341,   683,   684,   685,     0,     0,
       0,  -857,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1657,     0,     0,   342,     0,     0,     0,
     343,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     687,     0,   688,   689,   690,   691,   692,   693,   694,   695,
     696,   697,     0,     0,     0,     0,     0,     0,     0,  1683,
       0,     0,   698,   699,     0,     0,     0,   342,     0,     0,
       0,   343,  1690,     0,     0,     0,     0,     0,     0,   344,
       0,  1695,     0,   345,     0,  1197,   346,     0,     0,     0,
    1706,  1043,     0,     0,     0,   433,   434,     3,     0,  -121,
    -106,  -106,     0,  -118,     0,   435,   436,   437,   438,   439,
       0,   347,     0,     0,  1720,   440,  1044,   441,  1045,  1046,
     344,   442,     0,     0,   345,     0,  1343,   346,  1047,   443,
    1048,     0,  -123,     0,  1049,   444,     0,     0,   445,     0,
       8,   446,  1050,     0,  1051,   447,     0,     0,  1052,  1053,
       0,     0,   347,     0,     0,  1054,     0,     0,   449,   450,
       0,   222,   223,   224,     0,   226,   227,   228,   229,   230,
     451,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,     0,   244,   245,   246,     0,     0,   249,   250,
     251,   252,   452,   453,   454,  1055,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   455,   456,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1664,     0,     0,   457,
       0,    57,     0,     0,     0,  1083,     0,     0,     0,   458,
     459,   460,   461,   462,     0,   463,     0,   464,   465,   466,
     467,   468,   469,   470,   471,    58,     0,    13,   472,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   473,   474,   475,   339,    14,     0,
       0,   476,   477,     0,     0,  1664,     0,   339,     0,     0,
     478,     0,   479,     0,   480,   481,    16,  1056,  1057,     0,
       0,     0,     0,     0,   340,   341,     0,     0,     0,     0,
    1083,     0,     0,     0,   340,   341,  1043,     0,     0,     0,
     433,   434,     3,  1664,  -121,  -106,  -106,     0,  -118,  1083,
     435,   436,   437,   438,   439,     0,     0,     0,     0,     0,
     440,  1044,   441,  1045,  1046,     0,   442,     0,     0,     0,
       0,     0,     0,  1047,   443,  1048,     0,  -123,     0,  1049,
     444,     0,     0,   445,     0,     8,   446,  1050,   342,  1051,
     447,     0,   343,  1052,  1053,     0,     0,     0,   342,     0,
    1054,     0,   343,   449,   450,     0,   222,   223,   224,     0,
     226,   227,   228,   229,   230,   451,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,     0,   244,   245,
     246,     0,     0,   249,   250,   251,   252,   452,   453,   454,
    1055,   344,     0,     0,     0,   345,     0,  1348,   346,     0,
       0,   344,     0,   455,   456,   345,     0,  1355,   346,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   347,   457,     0,    57,     0,     0,     0,
       0,     0,     0,   347,   458,   459,   460,   461,   462,     0,
     463,     0,   464,   465,   466,   467,   468,   469,   470,   471,
      58,     0,    13,   472,     0,   339,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   473,
     474,   475,     0,    14,     0,     0,   476,   477,     0,     0,
       0,     0,   340,   341,     0,   478,     0,   479,     0,   480,
     481,    16,  1056,  -307,  1043,     0,     0,     0,   433,   434,
       3,     0,  -121,  -106,  -106,     0,  -118,     0,   435,   436,
     437,   438,   439,     0,     0,     0,     0,     0,   440,  1044,
     441,  1045,  1046,     0,   442,     0,     0,     0,     0,     0,
       0,  1047,   443,  1048,     0,  -123,     0,  1049,   444,     0,
       0,   445,     0,     8,   446,  1050,   342,  1051,   447,     0,
     343,  1052,  1053,     0,     0,     0,     0,     0,  1054,     0,
       0,   449,   450,     0,   222,   223,   224,     0,   226,   227,
     228,   229,   230,   451,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,     0,   244,   245,   246,     0,
       0,   249,   250,   251,   252,   452,   453,   454,  1055,   344,
       0,     0,     0,   345,     0,  1524,   346,     0,     0,     0,
       0,   455,   456,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   347,   457,     0,    57,     0,     0,     0,     0,     0,
       0,     0,   458,   459,   460,   461,   462,     0,   463,     0,
     464,   465,   466,   467,   468,   469,   470,   471,    58,     0,
      13,   472,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   473,   474,   475,
       0,    14,     0,     0,   476,   477,     0,     0,     0,     0,
       0,     0,     0,   478,     0,   479,     0,   480,   481,    16,
    1056,  -333,  1043,     0,     0,     0,   433,   434,     3,     0,
    -121,  -106,  -106,     0,  -118,     0,   435,   436,   437,   438,
     439,     0,     0,     0,     0,     0,   440,  1044,   441,  1045,
    1046,     0,   442,     0,     0,     0,     0,     0,     0,  1047,
     443,  1048,     0,  -123,     0,  1049,   444,     0,     0,   445,
       0,     8,   446,  1050,     0,  1051,   447,     0,     0,  1052,
    1053,     0,     0,     0,     0,     0,  1054,     0,     0,   449,
     450,     0,   222,   223,   224,     0,   226,   227,   228,   229,
     230,   451,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,     0,   244,   245,   246,     0,     0,   249,
     250,   251,   252,   452,   453,   454,  1055,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   455,
     456,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     457,     0,    57,     0,     0,     0,     0,     0,     0,     0,
     458,   459,   460,   461,   462,     0,   463,     0,   464,   465,
     466,   467,   468,   469,   470,   471,    58,     0,    13,   472,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   473,   474,   475,     0,    14,
       0,     0,   476,   477,     0,     0,     0,     0,     0,     0,
       0,   478,     0,   479,     0,   480,   481,    16,  1056,  -304,
    1043,     0,     0,     0,   433,   434,     3,     0,  -121,  -106,
    -106,     0,  -118,     0,   435,   436,   437,   438,   439,     0,
       0,     0,     0,     0,   440,  1044,   441,  1045,  1046,     0,
     442,     0,     0,     0,     0,     0,     0,  1047,   443,  1048,
       0,  -123,     0,  1049,   444,     0,     0,   445,     0,     8,
     446,  1050,     0,  1051,   447,     0,     0,  1052,  1053,     0,
       0,     0,     0,     0,  1054,     0,     0,   449,   450,     0,
     222,   223,   224,     0,   226,   227,   228,   229,   230,   451,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,     0,   244,   245,   246,     0,     0,   249,   250,   251,
     252,   452,   453,   454,  1055,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   455,   456,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   457,     0,
      57,     0,     0,     0,     0,     0,     0,     0,   458,   459,
     460,   461,   462,     0,   463,     0,   464,   465,   466,   467,
     468,   469,   470,   471,    58,     0,    13,   472,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   473,   474,   475,     0,    14,     0,     0,
     476,   477,     0,     0,     0,     0,     0,     0,     0,   478,
       0,   479,     0,   480,   481,    16,  1056,   -97,  1043,     0,
       0,     0,   433,   434,     3,     0,  -121,  -106,  -106,     0,
    -118,     0,   435,   436,   437,   438,   439,     0,     0,     0,
       0,     0,   440,  1044,   441,  1045,  1046,     0,   442,     0,
       0,     0,     0,     0,     0,  1047,   443,  1048,     0,  -123,
       0,  1049,   444,     0,     0,   445,     0,     8,   446,  1050,
       0,  1051,   447,     0,     0,  1052,  1053,     0,     0,     0,
       0,     0,  1054,     0,     0,   449,   450,     0,   222,   223,
     224,     0,   226,   227,   228,   229,   230,   451,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,     0,
     244,   245,   246,     0,     0,   249,   250,   251,   252,   452,
     453,   454,  1055,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   455,   456,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   457,     0,    57,     0,
       0,     0,     0,     0,     0,     0,   458,   459,   460,   461,
     462,     0,   463,     0,   464,   465,   466,   467,   468,   469,
     470,   471,    58,     0,    13,   472,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   473,   474,   475,     0,    14,     0,     0,   476,   477,
       0,     0,     0,     0,     0,     0,     0,   478,     0,   479,
       0,   480,   481,    16,  1056,  -102,   433,   434,     0,     0,
       0,     0,     0,     0,     0,     0,   435,   436,   437,   438,
     439,     0,     0,     0,     0,     0,   440,     0,   441,     0,
       0,     0,   442,     0,     0,     0,     0,     0,     0,     0,
     443,     0,     0,     0,     0,     0,   444,     0,     0,   445,
       0,     0,   446,     0,     0,     0,   447,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   448,     0,     0,   449,
     450,   854,   222,   223,   224,     0,   226,   227,   228,   229,
     230,   451,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,     0,   244,   245,   246,     0,     0,   249,
     250,   251,   252,   452,   453,   454,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   455,
     456,     0,     0,     0,     0,     0,     0,     0,   529,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     457,     0,    57,     0,     0,     0,     0,     0,     0,     0,
     458,   459,   460,   461,   462,     0,   463,   647,   464,   465,
     466,   467,   468,   469,   470,   471,   648,     0,     0,   472,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   473,   474,   475,     0,    14,
       0,     0,   476,   477,     0,     0,     0,     0,     0,   433,
     434,   855,     0,   479,   856,   480,   481,   644,   482,   435,
     436,   437,   438,   439,     0,     0,     0,     0,     0,   440,
       0,   441,     0,     0,     0,   442,     0,     0,     0,     0,
       0,     0,     0,   443,     0,     0,     0,     0,     0,   444,
       0,     0,   445,   645,     0,   446,     0,     0,     0,   447,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   448,
       0,     0,   449,   450,     0,   222,   223,   224,     0,   226,
     227,   228,   229,   230,   451,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,     0,   244,   245,   246,
       0,     0,   249,   250,   251,   252,   452,   453,   454,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   455,   456,     0,     0,     0,     0,     0,     0,
       0,   529,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   457,     0,    57,     0,     0,     0,     0,
       0,     0,     0,   458,   459,   460,   461,   462,     0,   463,
     647,   464,   465,   466,   467,   468,   469,   470,   471,   648,
       0,     0,   472,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   473,   474,
     475,     0,    14,     0,     0,   476,   477,     0,     0,     0,
       0,     0,   433,   434,   478,     0,   479,     0,   480,   481,
     644,   482,   435,   436,   437,   438,   439,     0,     0,     0,
       0,     0,   440,     0,   441,     0,     0,     0,   442,     0,
       0,     0,     0,     0,     0,     0,   443,     0,     0,     0,
       0,     0,   444,     0,     0,   445,   645,     0,   446,     0,
       0,     0,   447,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   448,     0,     0,   449,   450,     0,   222,   223,
     224,     0,   226,   227,   228,   229,   230,   451,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,     0,
     244,   245,   246,     0,     0,   249,   250,   251,   252,   452,
     453,   454,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   455,   456,     0,     0,     0,
       0,     0,     0,     0,   529,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   457,     0,    57,     0,
       0,     0,     0,     0,     0,     0,   458,   459,   460,   461,
     462,     0,   463,     0,   464,   465,   466,   467,   468,   469,
     470,   471,    58,     0,     0,   472,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   473,   474,   475,     0,    14,     0,     0,   476,   477,
       0,     0,     0,     0,     0,   433,   434,   478,     0,   479,
       0,   480,   481,     0,   482,   435,   436,   437,   438,   439,
       0,     0,     0,     0,     0,   440,     0,   441,     0,     0,
       0,   442,     0,     0,     0,     0,     0,     0,     0,   443,
       0,     0,     0,     0,     0,   444,     0,     0,   445,     0,
       0,   446,     0,     0,     0,   447,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   448,     0,     0,   449,   450,
     978,   222,   223,   224,     0,   226,   227,   228,   229,   230,
     451,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,     0,   244,   245,   246,     0,     0,   249,   250,
     251,   252,   452,   453,   454,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   455,   456,
       0,     0,     0,     0,     0,     0,     0,   529,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   457,
       0,    57,     0,     0,     0,     0,     0,     0,     0,   458,
     459,   460,   461,   462,     0,   463,   647,   464,   465,   466,
     467,   468,   469,   470,   471,   648,     0,     0,   472,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   473,   474,   475,     0,    14,     0,
       0,   476,   477,     0,     0,     0,     0,     0,   433,   434,
     478,     0,   479,     0,   480,   481,     0,   482,   435,   436,
     437,   438,   439,     0,     0,     0,     0,     0,   440,     0,
     441,     0,     0,     0,   442,     0,     0,     0,     0,     0,
       0,     0,   443,     0,     0,     0,     0,     0,   444,     0,
       0,   445,     0,     0,   446,     0,     0,     0,   447,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   448,     0,
       0,   449,   450,     0,   222,   223,   224,     0,   226,   227,
     228,   229,   230,   451,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,     0,   244,   245,   246,     0,
       0,   249,   250,   251,   252,   452,   453,   454,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   455,   456,     0,     0,     0,     0,     0,     0,     0,
     529,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   457,     0,    57,     0,     0,     0,     0,     0,
       0,     0,   458,   459,   460,   461,   462,     0,   463,   647,
     464,   465,   466,   467,   468,   469,   470,   471,   648,     0,
       0,   472,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   473,   474,   475,
       0,    14,     0,     0,   476,   477,     0,     0,     0,     0,
       0,   433,   434,  1285,     0,   479,  1286,   480,   481,     0,
     482,   435,   436,   437,   438,   439,     0,     0,     0,     0,
       0,   440,     0,   441,     0,     0,     0,   442,     0,     0,
       0,     0,     0,     0,     0,   443,     0,     0,     0,     0,
       0,   444,     0,     0,   445,     0,     0,   446,     0,     0,
       0,   447,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   448,     0,     0,   449,   450,     0,   222,   223,   224,
       0,   226,   227,   228,   229,   230,   451,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,     0,   244,
     245,   246,     0,     0,   249,   250,   251,   252,   452,   453,
     454,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   455,   456,     0,     0,     0,     0,
       0,     0,     0,   529,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   457,     0,    57,     0,     0,
       0,     0,     0,     0,     0,   458,   459,   460,   461,   462,
       0,   463,   647,   464,   465,   466,   467,   468,   469,   470,
     471,   648,     0,     0,   472,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     473,   474,   475,     0,    14,     0,     0,   476,   477,     0,
       0,     0,     0,     0,   433,   434,  1296,     0,   479,  1297,
     480,   481,     0,   482,   435,   436,   437,   438,   439,     0,
       0,     0,     0,     0,   440,     0,   441,     0,     0,     0,
     442,     0,     0,     0,     0,     0,     0,     0,   443,     0,
       0,     0,     0,     0,   444,     0,     0,   445,     0,     0,
     446,     0,     0,     0,   447,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   448,     0,     0,   449,   450,     0,
     222,   223,   224,     0,   226,   227,   228,   229,   230,   451,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,     0,   244,   245,   246,     0,     0,   249,   250,   251,
     252,   452,   453,   454,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   455,   456,     0,
       0,     0,     0,     0,     0,     0,   529,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   457,     0,
      57,     0,     0,     0,     0,     0,     0,     0,   458,   459,
     460,   461,   462,     0,   463,   647,   464,   465,   466,   467,
     468,   469,   470,   471,   648,     0,     0,   472,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   473,   474,   475,     0,    14,     0,     0,
     476,   477,     0,     0,     0,     0,     0,   433,   434,   478,
       0,   479,     0,   480,   481,     0,   482,   435,   436,   437,
     438,   439,     0,     0,     0,     0,     0,   440,     0,   441,
       0,     0,     0,   442,     0,     0,     0,     0,     0,     0,
       0,   443,     0,     0,     0,     0,     0,   444,     0,     0,
     445,     0,     0,   446,     0,     0,     0,   447,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   448,     0,     0,
     449,   450,     0,   222,   223,   224,     0,   226,   227,   228,
     229,   230,   451,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,     0,   244,   245,   246,     0,     0,
     249,   250,   251,   252,   452,   453,   454,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     455,   456,     0,     0,     0,     0,     0,     0,     0,   529,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   457,     0,    57,     0,     0,     0,     0,     0,     0,
       0,   458,   459,   460,   461,   462,     0,   463,     0,   464,
     465,   466,   467,   468,   469,   470,   471,    58,     0,     0,
     472,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   473,   474,   475,     0,
      14,     0,     0,   476,   477,     0,     0,     0,     0,     0,
     433,   434,   478,     0,   479,   916,   480,   481,     0,   482,
     435,   436,   437,   438,   439,     0,     0,     0,     0,     0,
     440,     0,   441,     0,     0,     0,   442,     0,     0,     0,
       0,     0,     0,     0,   443,     0,     0,     0,     0,     0,
     444,     0,     0,   445,     0,     0,   446,     0,     0,     0,
     447,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     448,     0,     0,   449,   450,     0,   222,   223,   224,     0,
     226,   227,   228,   229,   230,   451,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,     0,   244,   245,
     246,     0,     0,   249,   250,   251,   252,   452,   453,   454,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   455,   456,     0,     0,     0,     0,     0,
       0,     0,   938,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   457,     0,    57,     0,     0,     0,
       0,     0,     0,     0,   458,   459,   460,   461,   462,     0,
     463,   647,   464,   465,   466,   467,   468,   469,   470,   471,
     648,     0,     0,   472,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   473,
     474,   475,     0,    14,     0,     0,   476,   477,     0,     0,
       0,     0,     0,   433,   434,  1219,     0,   479,     0,   480,
     481,     0,   482,   435,   436,   437,   438,   439,     0,     0,
       0,     0,     0,   440,     0,   441,     0,     0,     0,   442,
       0,     0,     0,     0,     0,     0,     0,   443,     0,     0,
       0,     0,     0,   444,     0,     0,   445,     0,     0,   446,
       0,     0,     0,   447,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   448,     0,     0,   449,   450,     0,   222,
     223,   224,     0,   226,   227,   228,   229,   230,   451,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
       0,   244,   245,   246,     0,     0,   249,   250,   251,   252,
     452,   453,   454,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   455,   456,     0,     0,
       0,     0,     0,     0,     0,   529,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   457,     0,    57,
       0,     0,     0,     0,     0,     0,     0,   458,   459,   460,
     461,   462,     0,   463,     0,   464,   465,   466,   467,   468,
     469,   470,   471,    58,     0,     0,   472,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   473,   474,   475,     0,    14,     0,     0,   476,
     477,     0,     0,     0,     0,     0,   433,   434,   478,     0,
     479,  1303,   480,   481,     0,   482,   435,   436,   437,   438,
     439,     0,     0,     0,     0,     0,   440,     0,   441,     0,
       0,     0,   442,     0,     0,     0,     0,     0,     0,     0,
     443,     0,     0,     0,     0,     0,   444,     0,     0,   445,
       0,     0,   446,     0,     0,     0,   447,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   448,     0,     0,   449,
     450,     0,   222,   223,   224,     0,   226,   227,   228,   229,
     230,   451,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,     0,   244,   245,   246,     0,     0,   249,
     250,   251,   252,   452,   453,   454,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   455,
     456,     0,     0,     0,     0,     0,     0,     0,   529,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     457,     0,    57,     0,     0,     0,     0,     0,     0,     0,
     458,   459,   460,   461,   462,     0,   463,     0,   464,   465,
     466,   467,   468,   469,   470,   471,    58,     0,     0,   472,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   473,   474,   475,     0,    14,
       0,     0,   476,   477,     0,     0,     0,     0,     0,   433,
     434,   478,     0,   479,  1361,   480,   481,     0,   482,   435,
     436,   437,   438,   439,     0,     0,     0,     0,     0,   440,
       0,   441,     0,     0,     0,   442,     0,     0,     0,     0,
       0,     0,     0,   443,     0,     0,     0,     0,     0,   444,
       0,     0,   445,     0,     0,   446,     0,     0,     0,   447,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   448,
       0,     0,   449,   450,     0,   222,   223,   224,     0,   226,
     227,   228,   229,   230,   451,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,     0,   244,   245,   246,
       0,     0,   249,   250,   251,   252,   452,   453,   454,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   455,   456,     0,     0,     0,     0,     0,     0,
       0,   938,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   457,     0,    57,     0,     0,     0,     0,
       0,     0,     0,   458,   459,   460,   461,   462,     0,   463,
     647,   464,   465,   466,   467,   468,   469,   470,   471,   648,
       0,     0,   472,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   473,   474,
     475,     0,    14,     0,     0,   476,   477,     0,     0,     0,
       0,     0,   433,   434,   478,     0,   479,     0,   480,   481,
       0,   482,   435,   436,   437,   438,   439,     0,     0,     0,
       0,     0,   440,     0,   441,     0,     0,     0,   442,     0,
       0,     0,     0,     0,     0,     0,   443,     0,     0,     0,
       0,     0,   444,     0,     0,   445,     0,     0,   446,     0,
       0,     0,   447,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   448,     0,     0,   449,   450,     0,   222,   223,
     224,     0,   226,   227,   228,   229,   230,   451,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,     0,
     244,   245,   246,     0,     0,   249,   250,   251,   252,   452,
     453,   454,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   455,   456,     0,     0,     0,
       0,     0,     0,     0,   529,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   457,     0,    57,     0,
       0,     0,     0,     0,     0,     0,   458,   459,   460,   461,
     462,     0,   463,     0,   464,   465,   466,   467,   468,   469,
     470,   471,    58,     0,     0,   472,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   473,   474,   475,     0,    14,     0,     0,   476,   477,
       0,     0,     0,     0,     0,   433,   434,   478,     0,   479,
       0,   480,   481,     0,   482,   435,   436,   437,   438,   439,
       0,     0,     0,     0,     0,   440,     0,   441,     0,     0,
       0,   442,     0,     0,     0,     0,     0,     0,     0,   443,
       0,     0,     0,     0,     0,   444,     0,     0,   445,     0,
       0,   446,     0,     0,     0,   447,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   448,     0,     0,   449,   450,
       0,   222,   223,   224,     0,   226,   227,   228,   229,   230,
     451,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,     0,   244,   245,   246,     0,     0,   249,   250,
     251,   252,   452,   453,   454,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   455,   456,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   457,
       0,    57,     0,     0,     0,     0,     0,     0,     0,   458,
     459,   460,   461,   462,     0,   463,     0,   464,   465,   466,
     467,   468,   469,   470,   471,    58,     0,     0,   472,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   473,   474,   475,     0,    14,     0,
       0,   476,   477,     0,     0,     0,     0,     0,   433,   434,
     478,   539,   479,     0,   480,   481,     0,   482,   435,   436,
     437,   438,   439,     0,     0,     0,     0,     0,   440,     0,
     441,     0,     0,     0,   442,     0,     0,     0,     0,     0,
       0,     0,   443,     0,     0,     0,     0,     0,   444,     0,
       0,   445,     0,     0,   446,     0,     0,     0,   447,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   448,     0,
       0,   449,   450,     0,   222,   223,   224,     0,   226,   227,
     228,   229,   230,   451,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,     0,   244,   245,   246,     0,
       0,   249,   250,   251,   252,   452,   453,   454,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   455,   456,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   457,     0,    57,     0,     0,     0,     0,     0,
       0,     0,   458,   459,   460,   461,   462,     0,   463,     0,
     464,   465,   466,   467,   468,   469,   470,   471,    58,     0,
       0,   472,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   473,   474,   475,
       0,    14,     0,     0,   476,   477,     0,     0,     0,     0,
       0,   433,   434,   478,   730,   479,     0,   480,   481,     0,
     482,   435,   436,   437,   438,   439,     0,     0,     0,     0,
       0,   440,     0,   441,     0,     0,     0,   442,     0,     0,
       0,     0,     0,     0,     0,   443,     0,     0,     0,     0,
       0,   444,     0,     0,   445,     0,     0,   446,     0,     0,
       0,   447,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   448,     0,     0,   449,   450,     0,   222,   223,   224,
       0,   226,   227,   228,   229,   230,   451,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,     0,   244,
     245,   246,     0,     0,   249,   250,   251,   252,   452,   453,
     454,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   455,   456,     0,     0,     0,     0,
       0,     0,     0,   938,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   457,     0,    57,     0,     0,
       0,     0,     0,     0,     0,   458,   459,   460,   461,   462,
       0,   463,     0,   464,   465,   466,   467,   468,   469,   470,
     471,    58,     0,     0,   472,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     473,   474,   475,     0,    14,     0,     0,   476,   477,     0,
       0,     0,     0,     0,   433,   434,   478,     0,   479,     0,
     480,   481,  1030,   482,   435,   436,   437,   438,   439,     0,
       0,     0,     0,     0,   440,     0,   441,     0,     0,     0,
     442,     0,     0,     0,     0,     0,     0,     0,   443,     0,
       0,     0,     0,     0,   444,     0,     0,   445,     0,     0,
     446,     0,     0,     0,   447,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   448,     0,     0,   449,   450,     0,
     222,   223,   224,     0,   226,   227,   228,   229,   230,   451,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,     0,   244,   245,   246,     0,     0,   249,   250,   251,
     252,   452,   453,   454,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   455,   456,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   457,     0,
      57,     0,     0,     0,     0,     0,     0,     0,   458,   459,
     460,   461,   462,     0,   463,     0,   464,   465,   466,   467,
     468,   469,   470,   471,    58,     0,     0,   472,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   473,   474,   475,     0,    14,     0,     0,
     476,   477,     0,     0,     0,     0,     0,   433,   434,   478,
       0,   479,     0,   480,   481,     0,   482,   435,   436,   437,
     438,   439,     0,     0,     0,     0,     0,   440,     0,   441,
       0,     0,     0,   442,     0,     0,     0,     0,     0,     0,
       0,   443,     0,     0,     0,     0,     0,   444,     0,     0,
     445,     0,     0,   446,     0,     0,     0,   447,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   448,     0,     0,
     449,   450,     0,   222,   223,   224,     0,   226,   227,   228,
     229,   230,   451,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,     0,   244,   245,   246,     0,     0,
     249,   250,   251,   252,   452,   453,   454,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     455,   456,     0,     0,     0,     0,     0,     0,     0,  1229,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   457,     0,    57,     0,     0,     0,     0,     0,     0,
       0,   458,   459,   460,   461,   462,     0,   463,     0,   464,
     465,   466,   467,   468,   469,   470,   471,    58,     0,     0,
     472,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   473,   474,   475,     0,
      14,     0,     0,   476,   477,     0,     0,     0,     0,     0,
     433,   434,   478,     0,   479,     0,   480,   481,     0,   482,
     435,   436,   437,   438,   439,     0,     0,     0,     0,     0,
     440,     0,   441,     0,     0,     0,   442,     0,     0,     0,
       0,     0,     0,     0,   443,     0,     0,     0,     0,     0,
     444,     0,     0,   445,     0,     0,   446,     0,     0,     0,
     447,     0,     0,     0,     0,     0,  1232,     0,     0,     0,
     448,     0,     0,   449,   450,     0,   222,   223,   224,     0,
     226,   227,   228,   229,   230,   451,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,     0,   244,   245,
     246,     0,     0,   249,   250,   251,   252,   452,   453,   454,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   455,   456,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   457,     0,    57,     0,     0,     0,
       0,     0,     0,     0,   458,   459,   460,   461,   462,     0,
     463,     0,   464,   465,   466,   467,   468,   469,   470,   471,
      58,     0,     0,   472,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   473,
     474,   475,     0,    14,     0,     0,   476,   477,     0,     0,
       0,     0,     0,   433,   434,   478,     0,   479,     0,   480,
     481,     0,   482,   435,   436,   437,   438,   439,     0,     0,
       0,     0,     0,   440,     0,   441,     0,     0,     0,   442,
       0,     0,     0,     0,     0,     0,     0,   443,     0,     0,
       0,     0,     0,   444,     0,     0,   445,     0,     0,   446,
       0,     0,     0,   447,     0,     0,  1238,     0,     0,     0,
       0,     0,     0,   448,     0,     0,   449,   450,     0,   222,
     223,   224,     0,   226,   227,   228,   229,   230,   451,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
       0,   244,   245,   246,     0,     0,   249,   250,   251,   252,
     452,   453,   454,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   455,   456,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   457,     0,    57,
       0,     0,     0,     0,     0,     0,     0,   458,   459,   460,
     461,   462,     0,   463,     0,   464,   465,   466,   467,   468,
     469,   470,   471,    58,     0,     0,   472,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   473,   474,   475,     0,    14,     0,     0,   476,
     477,     0,     0,     0,     0,     0,   433,   434,   478,     0,
     479,     0,   480,   481,     0,   482,   435,   436,   437,   438,
     439,     0,     0,     0,     0,     0,   440,     0,   441,     0,
       0,     0,   442,     0,     0,     0,     0,     0,     0,     0,
     443,     0,     0,     0,     0,     0,   444,     0,     0,   445,
       0,     0,   446,     0,     0,     0,   447,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   448,     0,     0,   449,
     450,     0,   222,   223,   224,     0,   226,   227,   228,   229,
     230,   451,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,     0,   244,   245,   246,     0,     0,   249,
     250,   251,   252,   452,   453,   454,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   455,
     456,     0,     0,     0,     0,     0,     0,     0,  1241,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     457,     0,    57,     0,     0,     0,     0,     0,     0,     0,
     458,   459,   460,   461,   462,     0,   463,     0,   464,   465,
     466,   467,   468,   469,   470,   471,    58,     0,     0,   472,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   473,   474,   475,     0,    14,
       0,     0,   476,   477,     0,     0,     0,     0,     0,   433,
     434,   478,     0,   479,     0,   480,   481,     0,   482,   435,
     436,   437,   438,   439,     0,     0,     0,     0,     0,   440,
       0,   441,     0,     0,     0,   442,     0,     0,     0,     0,
       0,     0,     0,   443,     0,     0,     0,     0,     0,   444,
       0,     0,   445,     0,     0,   446,     0,     0,     0,   447,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   448,
       0,     0,   449,   450,     0,   222,   223,   224,     0,   226,
     227,   228,   229,   230,   451,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,     0,   244,   245,   246,
       0,     0,   249,   250,   251,   252,   452,   453,   454,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   455,   456,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   457,     0,    57,     0,     0,     0,     0,
       0,     0,     0,   458,   459,   460,   461,   462,     0,   463,
       0,   464,   465,   466,   467,   468,   469,   470,   471,    58,
       0,     0,   472,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   473,   474,
     475,     0,    14,     0,     0,   476,   477,     0,     0,     0,
       0,     0,   433,   434,   478,     0,   479,  1489,   480,   481,
       0,   482,   435,   436,   437,   438,   439,     0,     0,     0,
       0,     0,   440,     0,   441,     0,     0,     0,   442,     0,
       0,     0,     0,     0,     0,     0,   443,     0,     0,     0,
       0,     0,   444,     0,     0,   445,     0,     0,   446,     0,
       0,     0,   447,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   448,     0,     0,   449,   450,     0,   222,   223,
     224,     0,   226,   227,   228,   229,   230,   451,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,     0,
     244,   245,   246,     0,     0,   249,   250,   251,   252,   452,
     453,   454,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   455,   456,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   457,     0,    57,     0,
       0,     0,     0,     0,     0,     0,   458,   459,   460,   461,
     462,     0,   463,     0,   464,   465,   466,   467,   468,   469,
     470,   471,    58,     0,     0,   472,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   473,   474,   475,     0,    14,     0,     0,   476,   477,
       0,     0,     0,     0,     0,   433,   434,   478,     0,   479,
       0,   480,   481,     0,   482,   435,   436,   437,   438,   439,
       0,     0,     0,     0,     0,   440,  1044,   441,  1045,     0,
       0,   442,     0,     0,     0,     0,     0,     0,     0,   443,
       0,     0,     0,     0,     0,   444,     0,     0,   445,     0,
       0,   446,  1050,     0,     0,   447,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   448,     0,     0,   449,   450,
       0,   222,   223,   224,     0,   226,   227,   228,   229,   230,
     451,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,     0,   244,   245,   246,     0,     0,   249,   250,
     251,   252,   452,   453,   454,  1055,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   455,   456,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   457,
       0,    57,     0,     0,     0,     0,     0,     0,     0,   458,
     459,   460,   461,   462,     0,   463,     0,   464,   465,   466,
     467,   468,   469,   470,   471,    58,     0,     0,   472,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   473,   474,   475,     0,    14,     0,
       0,   476,   477,     0,     0,     0,   433,   434,     0,     0,
     478,     0,   479,     0,   480,   481,   435,   436,   437,   438,
     439,     0,     0,     0,     0,     0,   440,     0,   441,     0,
       0,     0,   442,     0,     0,     0,     0,     0,     0,     0,
     443,     0,     0,     0,     0,     0,   444,     0,     0,   445,
       0,     0,   446,     0,     0,     0,   447,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   448,     0,     0,   449,
     450,     0,   222,   223,   224,     0,   226,   227,   228,   229,
     230,   451,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,     0,   244,   245,   246,     0,     0,   249,
     250,   251,   252,   452,   453,   454,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   455,
     456,     0,     0,     0,     0,     0,     0,     0,   775,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     457,     0,    57,     0,     0,     0,     0,     0,     0,     0,
     458,   459,   460,   461,   462,     0,   463,     0,   464,   465,
     466,   467,   468,   469,   470,   471,    58,     0,     0,   472,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   473,   474,   475,     0,    14,
       0,     0,   476,   477,     0,     0,     0,   433,   434,     0,
       0,   478,     0,   479,     0,   480,   481,   435,   436,   437,
     438,   439,     0,     0,   895,     0,     0,   440,     0,   441,
       0,     0,     0,   442,     0,     0,     0,     0,     0,     0,
       0,   443,     0,     0,     0,     0,     0,   444,     0,     0,
     445,     0,     0,   446,     0,     0,     0,   447,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   448,     0,     0,
     449,   450,     0,   222,   223,   224,     0,   226,   227,   228,
     229,   230,   451,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,     0,   244,   245,   246,     0,     0,
     249,   250,   251,   252,   452,   453,   454,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     455,   456,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   457,     0,    57,     0,     0,     0,     0,     0,     0,
       0,   458,   459,   460,   461,   462,     0,   463,     0,   464,
     465,   466,   467,   468,   469,   470,   471,    58,     0,     0,
     472,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   473,   474,   475,     0,
      14,     0,     0,   476,   477,     0,     0,     0,   433,   434,
       0,     0,   478,     0,   479,     0,   480,   481,   435,   436,
     437,   438,   439,     0,     0,     0,     0,     0,   440,     0,
     441,     0,     0,     0,   442,     0,     0,     0,     0,     0,
       0,     0,   443,     0,     0,     0,     0,     0,   444,     0,
       0,   445,     0,     0,   446,     0,     0,     0,   447,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   448,     0,
       0,   449,   450,     0,   222,   223,   224,     0,   226,   227,
     228,   229,   230,   451,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,     0,   244,   245,   246,     0,
       0,   249,   250,   251,   252,   452,   453,   454,     0,     0,
       0,     0,   -87,     0,     0,     0,     0,     0,     0,     0,
       0,   455,   456,   664,   665,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   457,     0,    57,     0,     0,     0,     0,     0,
       0,     0,   458,   459,   460,   461,   462,     0,   463,     0,
     464,   465,   466,   467,   468,   469,   470,   471,    58,     0,
       0,   472,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   473,   474,   475,
       0,    14,     0,     0,   476,   477,     0,     0,     0,     0,
       0,     0,     0,   478,     0,   479,     0,   480,   481,     0,
    1262,  1263,  1264,  1265,  1266,  1267,  1268,  1269,   666,   667,
     668,   669,   670,  1270,  1271,   671,   672,   673,   674,  1272,
     675,   676,   677,   678,   679,  1273,   680,   681,  1274,  1275,
     682,     0,     0,     0,   683,   684,   685,  1276,  1277,  1278,
     686,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1279,   687,
       0,   688,   689,   690,   691,   692,   693,   694,   695,   696,
     697,   216,     0,     0,     0,     0,     0,   217,     0,     0,
       0,   698,   699,   218,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   219,     0,     0,     0,     0,     0,     0,
       0,   220,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   221,     0,     0,     0,
       0,     0,     0,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   231,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   216,     0,     0,     0,
       0,     0,   217,     0,     0,     0,     0,     0,   218,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   219,     0,
       0,     0,     0,    57,     0,     0,   220,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   255,     0,     0,     0,
       0,   221,     0,     0,     0,     0,     0,    58,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,     0,     0,     0,     0,     0,   256,     0,     0,     0,
       0,   542,     0,   216,     0,     0,     0,     0,     0,   217,
       0,     0,     0,     0,     0,   218,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   219,     0,     0,    57,     0,
       0,     0,     0,   220,     0,     0,     0,     0,     0,     0,
       0,   255,     0,     0,     0,     0,     0,     0,   221,     0,
       0,     0,   712,     0,    13,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,     0,     0,
       0,   256,     0,    16,     0,     0,     0,     0,   216,     0,
       0,     0,   355,   356,   217,     0,     0,     0,     0,     0,
     218,     0,     0,     0,     0,     0,     0,     0,     0,   357,
     219,     0,     0,     0,     0,    57,     0,     0,   220,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   255,     0,
       0,     0,     0,   221,     0,     0,     0,     0,     0,    58,
     222,   223,   224,   225,   226,   227,   228,   229,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,     0,     0,     0,     0,     0,   256,   358,
     359,   360,   361,   362,   363,   364,   365,   366,   367,   368,
     369,   370,   371,   372,   373,   374,   375,   664,   665,   376,
     377,   378,     0,     0,   379,   380,   381,   382,   383,     0,
      57,     0,     0,   384,   385,   386,   387,   388,   389,   390,
       0,     0,     0,   255,     0,     0,   664,   665,     0,     0,
       0,     0,     0,     0,   712,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   391,     0,
     392,   393,   394,   395,   396,   397,   398,   399,   400,   401,
       0,     0,   402,   403,     0,     0,     0,     0,     0,     0,
     404,   405,     0,   256,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   666,   667,   668,   669,   670,     0,     0,   671,
     672,   673,   674,     0,   675,   676,   677,   678,   679,     0,
     680,   681,   664,   665,     0,     0,     0,     0,   683,   684,
     685,   666,   667,   668,   669,   670,     0,     0,   671,   672,
     673,   674,     0,   675,   676,   677,   678,   679,     0,   680,
     681,   664,   665,     0,     0,     0,     0,   683,     0,   685,
       0,     0,     0,   687,     0,   688,   689,   690,   691,   692,
     693,   694,   695,   696,   697,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   698,   699,     0,     0,     0,
       0,     0,     0,     0,   688,   689,   690,   691,   692,   693,
     694,   695,   696,   697,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   698,   699,     0,   666,   667,   668,
     669,   670,     0,     0,   671,   672,   673,   674,     0,   675,
     676,   677,   678,   679,     0,   680,   681,   664,   665,     0,
       0,     0,     0,   683,     0,     0,   666,   667,   668,   669,
     670,     0,     0,   671,   672,   673,   674,     0,   675,   676,
     677,   678,   679,     0,   680,   681,   664,   665,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     688,   689,   690,   691,   692,   693,   694,   695,   696,   697,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     698,   699,     0,     0,     0,     0,     0,     0,     0,   688,
     689,   690,   691,   692,   693,   694,   695,   696,   697,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   698,
     699,     0,   666,   667,   668,   669,   670,     0,     0,   671,
     672,   673,   674,     0,   675,   676,   677,   678,   679,     0,
     680,   681,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   666,   667,   668,   669,   670,     0,     0,   671,   672,
     673,   674,     0,   675,   676,   677,   678,   679,     0,   680,
     681,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   864,     0,     0,   690,   691,   692,
     693,   694,   695,   696,   697,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   698,   699,     0,     0,     0,
       0,     0,     0,     0,     0,   868,     0,   691,   692,   693,
     694,   695,   696,   697,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   698,   699,   222,   223,   224,     0,
     226,   227,   228,   229,   230,   451,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,     0,   244,   245,
     246,     0,     0,   249,   250,   251,   252,   222,   223,   224,
       0,   226,   227,   228,   229,   230,   451,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,     0,   244,
     245,   246,     0,     0,   249,   250,   251,   252,     0,     0,
       0,     0,     0,     0,     0,     0,  1092,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   865,     0,     0,     0,     0,     0,   277,     0,   278,
     866,   279,   280,   281,   282,   283,     0,   284,   285,   286,
     287,   288,   289,   290,   291,   292,   293,   294,     0,   295,
     296,   297,   869,   276,   298,   299,   300,   301,   222,   223,
     224,   870,   226,   227,   228,   229,   230,   451,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,     0,
     244,   245,   246,     0,     0,   249,   250,   251,   252,   277,
       0,   278,     0,   279,   280,   281,   282,   283,     0,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
       0,   295,   296,   297,     0,     0,   298,   299,   300,   301,
       0,   547,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   302,   303,     0,     0,
       0,     0,     0,  1093,     0,     0,     0,     0,     0,   222,
     223,   224,  1094,   226,   227,   228,   229,   230,   451,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
       0,   244,   245,   246,     0,     0,   249,   250,   251,   252,
       0,     0,   277,   304,   278,     0,   279,   280,   281,   282,
     283,     0,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   293,   294,     0,   295,   296,   297,   907,   908,   298,
     299,   300,   301,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   909,     0,     0,     0,     0,     0,
     277,     0,   278,   910,   279,   280,   281,   282,   283,     0,
     284,   285,   286,   287,   288,   289,   290,   291,   292,   293,
     294,     0,   295,   296,   297,     0,     0,   298,   299,   300,
     301,     0,     0,     0,     0,     0,   549,   911,   912,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   737
};

static const yytype_int16 yycheck[] =
{
       1,    14,    15,   144,   145,   338,   102,   575,   171,   350,
     579,   953,   855,  1046,   777,   437,   437,  1390,  1023,    20,
      21,    22,   545,   191,   192,  1180,   649,   650,   707,   546,
     709,   653,   711,  1260,    80,   479,   942,    20,     8,     0,
     517,   587,   519,    33,   521,   936,     7,    20,    49,    50,
      63,    64,    65,   355,   356,   961,    33,    19,   823,   863,
       5,  1359,  1627,  1627,   826,  1560,  1627,    20,  1627,    30,
      40,    32,  1627,    34,   129,   130,    22,   126,   126,    40,
      20,     7,   526,   140,   158,   175,   427,  1029,    46,    50,
     103,   104,   105,   106,   126,    56,  1353,    44,   721,    15,
      16,   140,    19,    20,   138,   140,   127,   177,  1574,   176,
     141,    57,   133,   175,   153,   126,   206,   175,   153,    80,
     141,  1686,  1686,  1618,    50,  1686,    62,  1686,   178,   178,
     178,  1686,    15,    16,   183,   183,     5,     6,    85,   201,
     156,   102,   103,   200,   199,   200,   178,   178,   106,   165,
    1523,   183,   315,   202,   202,   176,    25,   102,   103,  1724,
    1724,   207,    31,  1724,   608,  1724,   307,   178,   203,  1724,
     202,   312,   718,   207,   618,   316,   722,   621,   191,   192,
     802,   150,   129,   130,   156,   132,   202,   810,   175,  1637,
     813,   181,   175,   165,  1037,  1493,   165,   167,   821,    68,
      69,   824,   175,  1007,   181,   206,   167,  1240,  1213,   653,
     200,    21,    22,  1470,  1471,   165,   191,   192,   787,   209,
     182,   986,   175,   139,   126,   987,  1674,   188,  1134,  1486,
     200,  1488,   854,   102,   103,   175,  1127,   182,   208,   200,
     127,   187,   158,   256,  1150,   206,  1089,   163,   165,   165,
     165,   553,   168,   199,   204,  1721,   700,   202,  1101,   150,
     682,   682,   430,   431,   432,   811,   167,  1209,   609,  1735,
      34,   317,   141,   178,   165,   158,   178,   182,  1546,   175,
     163,   183,   165,   624,   425,   168,   202,   183,   175,   176,
    1558,   178,  1549,  1550,   181,  1522,   165,   150,  1372,    63,
     202,   202,  1559,   142,   143,   144,   167,   167,   118,   119,
     206,   202,   165,   182,   167,   150,   126,   139,   128,   129,
     130,   131,   132,   126,  1479,  1358,   129,   130,   165,     8,
     165,   200,  1011,   141,  1408,  1708,  1657,   350,   207,  1607,
    1608,   202,    33,   107,   512,   513,   206,   141,   516,   107,
     518,   150,   520,   206,   831,   208,   978,    36,   802,  1392,
     528,   127,  1683,  1042,   203,   156,   165,   202,   132,    60,
      61,   165,    33,   127,   165,   350,  1219,   141,    33,   133,
    1322,   167,   204,   205,   861,   207,    21,    22,   934,   199,
     200,   167,   187,   179,   562,   563,   199,   200,   967,    60,
      61,   165,   165,   202,   167,    60,    61,   930,   207,  1032,
     176,   165,   203,   179,   427,   175,   933,   430,   431,   432,
     206,   944,   176,   175,   437,   438,   175,   181,   192,   946,
     206,   148,   208,   124,   175,   175,   982,   128,   202,   175,
     175,   201,  1285,   206,   457,   786,   179,   148,   165,   202,
     183,   203,   427,  1296,   203,   430,   431,   432,   799,   800,
    1006,   201,   203,   124,   165,   201,   201,   128,   809,   124,
     187,   188,   127,   128,   815,   816,   175,   818,   133,   820,
    1243,   822,   199,   118,   119,   158,   177,   188,   175,   830,
     181,   126,   183,   184,   129,   130,   131,   132,   199,   512,
     513,   166,   150,   516,   203,   518,   187,   520,   165,   522,
     175,   652,   167,  1518,   201,   528,   177,   165,   209,   127,
     181,   176,   177,   184,   165,   133,   181,   127,   127,   184,
     127,   175,   545,   133,   133,   175,   133,   512,   513,   175,
     127,   516,   165,   518,   175,   520,   133,   522,   209,   562,
     563,   206,   720,   528,   209,   175,   107,   570,   175,   203,
     182,   201,   175,  1505,   199,   200,   175,   203,   176,   175,
     545,   182,   203,    21,    22,   167,   176,   176,   579,   176,
     202,   175,   175,   203,   141,   175,   203,   562,   563,   176,
     203,   202,   165,   150,   203,  1438,   609,   203,   155,  1632,
     175,  1280,     5,     6,  1447,   141,   182,  1084,   165,   203,
     203,   624,   175,   203,   150,   175,   165,   108,   109,   110,
     111,   112,   113,   114,   115,   182,   202,   182,   203,   165,
     798,  1177,   175,   801,   609,  1668,   127,   805,   175,   169,
     203,   654,   133,   203,   985,  1089,   175,   202,   175,   624,
     991,    63,    64,    65,   145,   146,   147,  1101,   166,   167,
     203,   179,  1106,   107,  1005,   183,   203,   175,   116,   117,
     118,   119,  1705,   175,   203,   183,   203,   175,   126,   182,
     128,   129,   130,   131,   132,   176,   134,   135,   156,   664,
     665,   103,   104,   105,   106,   207,   325,   165,   206,   202,
     182,   203,  1545,  1546,   679,   203,   335,   720,  1551,   166,
     167,    47,    79,   150,   150,  1558,   165,  1560,   175,   348,
     202,   156,   179,   698,   142,   143,   144,    94,   165,   165,
     165,    67,    99,   734,   101,   736,   184,   185,   186,   187,
     188,   166,   167,   165,   166,   720,   199,   187,    57,   206,
     175,   199,   200,   175,    63,  1199,    12,  1600,   183,   199,
     928,   156,  1206,   931,  1607,  1608,   165,    23,    24,   937,
     165,    21,    22,   786,   175,  1618,   495,   178,   497,   498,
     181,   206,   166,   167,   156,   798,   799,   800,   801,   790,
     165,   175,   805,   165,   165,   166,   809,   166,   167,   183,
     206,   207,   815,   816,   175,   818,   175,   820,   165,   822,
     823,   786,   166,   167,   183,   176,   179,   830,   166,   167,
     183,   175,   206,   798,   799,   800,   801,   175,   192,   183,
     805,  1594,    57,  1676,   809,   183,   175,   206,    63,   178,
     815,   816,   181,   818,   178,   820,   178,   822,   823,   181,
    1272,  1272,   206,   166,   167,   830,   166,   167,   206,   179,
     179,   862,   175,   183,   183,   175,   166,   167,   118,   119,
     183,    57,   142,   183,   144,   175,   126,    63,   128,   129,
     130,   131,   132,   183,   108,   109,   110,   111,   112,   113,
     114,   115,    57,   206,   176,    57,   206,    57,    63,    57,
     529,    63,   169,    63,   179,    63,   206,   179,   183,   133,
     179,   183,   541,  1054,   183,   928,   142,   930,   931,   167,
     895,   145,   146,   147,   937,   165,   179,   140,   179,  1373,
     183,   944,   183,    57,  1557,  1698,   186,   187,   188,    66,
    1281,   140,   179,   944,   178,   946,   183,   169,   170,   199,
     200,    10,    11,   928,   583,   930,   931,   958,   169,   170,
     171,   172,   937,   166,  1727,   106,   967,   165,   969,   944,
    1250,  1251,   985,   986,   169,   170,   171,  1145,   991,  1602,
     182,   610,   611,   202,   202,   614,   182,   616,   169,   170,
     171,   182,  1005,  1156,   182,    33,   769,   770,   771,   182,
     182,    21,    22,   632,   633,   634,   635,   636,   637,   182,
     985,   986,   182,  1581,   494,   495,   991,   497,   498,    54,
      55,    56,    60,    61,   455,   456,   182,   182,   202,   200,
    1005,   179,   166,    35,    35,   207,   202,   165,   207,  1483,
      33,   200,   473,   474,   475,   476,   477,   165,   677,   182,
    1051,   165,   201,  1194,   207,    22,   165,    33,  1059,  1060,
     207,   201,  1506,   178,   165,  1634,   182,    60,    61,   182,
     699,  1072,   182,  1074,  1075,  1076,  1077,  1078,   182,   202,
     182,  1082,   202,   182,    60,    61,   124,  1228,   182,   127,
     128,   202,   182,   200,   202,   133,   202,   726,   118,   119,
      75,  1670,   202,   183,    79,   202,   126,   202,   128,   129,
     130,   131,   132,   202,   202,  1283,   203,   202,    93,    94,
     203,   165,   203,    98,    99,   100,   101,   203,   175,   201,
     201,   124,  1145,   202,   565,   128,   765,   202,   176,   177,
     206,   203,    43,   181,  1477,   202,   184,   183,   124,   182,
     182,   182,   128,   182,   783,    13,   202,   202,   175,   202,
     789,  1162,   201,   203,   184,   185,   186,   187,   188,     4,
    1145,   209,   202,   166,   167,   804,   165,   165,   178,   199,
     200,   165,   175,   201,   177,   165,  1630,   165,   181,   175,
     183,   184,   165,   203,   203,   203,   203,   203,   203,   828,
     829,   177,     1,    33,   203,   181,   203,   183,   184,   203,
     839,   202,   202,   206,   182,   844,   209,   846,   203,   848,
     203,   202,   182,   202,   853,   202,  1394,    21,    22,   201,
      60,    61,   202,   209,   183,   666,   667,   202,   202,   670,
     671,   672,   673,   202,   675,   201,   183,   678,   679,   680,
     681,   682,   683,   684,   685,   686,   687,   688,   689,   690,
     691,   692,   693,   694,   695,   696,   697,   183,  1281,   203,
    1283,   202,   176,   203,  1442,   202,    43,    33,   176,   908,
     203,   202,    43,   912,   203,   203,   203,   178,   203,   202,
     202,  1432,  1633,  1461,   124,   203,   203,   203,   128,    43,
     203,   203,   202,   165,    60,    61,  1281,  1403,  1283,   938,
     203,   208,   202,   202,   165,   203,   165,   158,    10,    13,
     207,     9,   116,   117,   118,   119,   120,    42,    66,   123,
    1331,   202,   126,  1334,   128,   129,   130,   131,   132,   968,
     134,   135,   182,    33,   775,   202,  1359,   177,   201,   165,
     202,   181,   165,   183,   184,   201,   165,   165,   208,     8,
     208,   208,   165,   992,   203,   202,   183,   165,   124,   173,
      60,    61,   128,   165,   203,   165,   165,   202,   165,   209,
     165,  1394,    14,   176,   158,   176,   208,   202,   182,   183,
     184,   185,   186,   187,   188,   178,   202,   202,   176,  1400,
      43,   203,   203,   203,    37,   199,   200,   203,  1037,    33,
     176,   208,    67,   183,   202,  1044,   202,    33,  1047,  1394,
     202,   177,   203,   203,  1053,   181,  1055,   183,   184,  1442,
     202,   862,   203,   202,   124,  1576,    60,    61,   128,  1580,
     202,    70,   202,   202,    60,    61,    33,   202,  1461,   202,
     202,   165,   203,   209,   202,    43,   203,  1086,   165,  1088,
     202,  1090,   202,   165,   203,   169,   203,  1442,   203,   203,
     202,  1100,   202,    60,    61,   202,   202,   202,   206,  1108,
    1493,   203,   165,   203,   203,   208,  1461,   177,    33,   207,
    1631,   181,   203,   183,   184,   203,   206,   203,   203,    12,
     124,   175,   203,  1132,   128,   203,   203,   203,   124,   175,
     203,   206,   128,  1142,   203,   206,   203,   203,  1147,   209,
    1149,  1522,   203,   203,   203,   203,   203,   958,   203,  1158,
     203,   203,  1161,   202,    21,    22,   203,   124,  1539,   203,
     203,   128,    53,   201,   201,   207,  1687,   208,   208,   202,
      79,  1180,  1693,   177,   208,   207,   203,   181,  1699,   183,
     184,   177,   208,   638,     1,   181,    82,   183,   184,   190,
    1734,    21,    22,  1202,  1732,   736,   213,  1251,   720,   736,
     654,  1210,  1211,  1212,  1725,   209,   962,     1,   658,  1541,
     177,  1388,  1598,   209,   181,  1544,   183,   184,  1464,  1599,
    1229,  1599,    53,  1232,  1150,   961,   961,   610,   231,   309,
     437,   437,  1241,   437,   437,    -1,   437,   437,    -1,    -1,
    1633,    -1,   209,    -1,    -1,    -1,    33,  1628,    -1,   116,
     117,   118,   119,   120,    -1,  1636,   123,   124,   125,   126,
      -1,   128,   129,   130,   131,   132,    -1,   134,   135,    -1,
      -1,   138,    -1,    60,    61,   142,   143,   144,  1633,    -1,
      -1,   148,  1291,    -1,  1293,  1096,   116,   117,   118,   119,
     120,  1300,  1673,   123,   124,   125,   126,    -1,   128,   129,
     130,   131,   132,    -1,   134,   135,    -1,    -1,    -1,  1690,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,    -1,  1704,    -1,  1706,    -1,    -1,    -1,    -1,
    1711,  1340,   199,   200,    -1,    -1,    -1,   124,    -1,    -1,
      -1,   128,    -1,    -1,    -1,    -1,    -1,  1728,  1357,  1730,
     180,   181,   182,   183,   184,   185,   186,   187,   188,    -1,
      -1,    -1,    -1,    -1,    -1,  1374,  1375,    -1,    -1,   199,
     200,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    21,    22,  1395,    -1,    -1,    -1,
     177,    -1,  1401,  1402,   181,    -1,   183,   184,  1407,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   209,    -1,    -1,    -1,    -1,    -1,    -1,  1438,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1447,    -1,
      -1,    -1,    -1,  1452,    -1,    -1,  1455,    -1,  1457,    -1,
      -1,  1262,  1263,  1264,  1265,  1266,  1267,  1268,  1269,  1270,
    1271,  1272,  1273,  1274,  1275,  1276,  1277,  1278,  1279,    -1,
    1479,  1480,  1481,  1482,    21,    22,    -1,    -1,    -1,   116,
     117,   118,   119,   120,    -1,    -1,   123,   124,   125,   126,
    1499,   128,   129,   130,   131,   132,    -1,   134,   135,    -1,
      -1,   138,    -1,    -1,    -1,   142,   143,   144,    -1,    -1,
    1519,   148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1548,
     177,    -1,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,    60,    61,    -1,  1564,    -1,    -1,    -1,    -1,
    1569,  1570,   199,   200,    -1,    -1,    33,    -1,    -1,   116,
     117,   118,   119,   120,    -1,    -1,   123,   124,   125,   126,
      -1,   128,   129,   130,   131,   132,    -1,   134,   135,  1400,
      -1,   138,    -1,    60,    61,   142,   143,   144,    -1,    -1,
      -1,   148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1622,    -1,    -1,   124,    -1,    -1,    -1,
     128,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     177,    -1,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1658,
      -1,    -1,   199,   200,    -1,    -1,    -1,   124,    -1,    -1,
      -1,   128,  1671,    -1,    -1,    -1,    -1,    -1,    -1,   177,
      -1,  1680,    -1,   181,    -1,   183,   184,    -1,    -1,    -1,
    1689,     1,    -1,    -1,    -1,     5,     6,     7,    -1,     9,
      10,    11,    -1,    13,    -1,    15,    16,    17,    18,    19,
      -1,   209,    -1,    -1,  1713,    25,    26,    27,    28,    29,
     177,    31,    -1,    -1,   181,    -1,   183,   184,    38,    39,
      40,    -1,    42,    -1,    44,    45,    -1,    -1,    48,    -1,
      50,    51,    52,    -1,    54,    55,    -1,    -1,    58,    59,
      -1,    -1,   209,    -1,    -1,    65,    -1,    -1,    68,    69,
      -1,    71,    72,    73,    -1,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,   119,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1627,    -1,    -1,   139,
      -1,   141,    -1,    -1,    -1,  1636,    -1,    -1,    -1,   149,
     150,   151,   152,   153,    -1,   155,    -1,   157,   158,   159,
     160,   161,   162,   163,   164,   165,    -1,   167,   168,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   184,   185,   186,    33,   188,    -1,
      -1,   191,   192,    -1,    -1,  1686,    -1,    33,    -1,    -1,
     200,    -1,   202,    -1,   204,   205,   206,   207,   208,    -1,
      -1,    -1,    -1,    -1,    60,    61,    -1,    -1,    -1,    -1,
    1711,    -1,    -1,    -1,    60,    61,     1,    -1,    -1,    -1,
       5,     6,     7,  1724,     9,    10,    11,    -1,    13,  1730,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    26,    27,    28,    29,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    -1,    42,    -1,    44,
      45,    -1,    -1,    48,    -1,    50,    51,    52,   124,    54,
      55,    -1,   128,    58,    59,    -1,    -1,    -1,   124,    -1,
      65,    -1,   128,    68,    69,    -1,    71,    72,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
     105,   177,    -1,    -1,    -1,   181,    -1,   183,   184,    -1,
      -1,   177,    -1,   118,   119,   181,    -1,   183,   184,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   209,   139,    -1,   141,    -1,    -1,    -1,
      -1,    -1,    -1,   209,   149,   150,   151,   152,   153,    -1,
     155,    -1,   157,   158,   159,   160,   161,   162,   163,   164,
     165,    -1,   167,   168,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,
     185,   186,    -1,   188,    -1,    -1,   191,   192,    -1,    -1,
      -1,    -1,    60,    61,    -1,   200,    -1,   202,    -1,   204,
     205,   206,   207,   208,     1,    -1,    -1,    -1,     5,     6,
       7,    -1,     9,    10,    11,    -1,    13,    -1,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,    26,
      27,    28,    29,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    -1,    42,    -1,    44,    45,    -1,
      -1,    48,    -1,    50,    51,    52,   124,    54,    55,    -1,
     128,    58,    59,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    68,    69,    -1,    71,    72,    73,    -1,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    -1,    93,    94,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   177,
      -1,    -1,    -1,   181,    -1,   183,   184,    -1,    -1,    -1,
      -1,   118,   119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   209,   139,    -1,   141,    -1,    -1,    -1,    -1,    -1,
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
       1,    -1,    -1,    -1,     5,     6,     7,    -1,     9,    10,
      11,    -1,    13,    -1,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    25,    26,    27,    28,    29,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,
      -1,    42,    -1,    44,    45,    -1,    -1,    48,    -1,    50,
      51,    52,    -1,    54,    55,    -1,    -1,    58,    59,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,    -1,
      71,    72,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,    93,    94,    95,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,   119,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,
     141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,   150,
     151,   152,   153,    -1,   155,    -1,   157,   158,   159,   160,
     161,   162,   163,   164,   165,    -1,   167,   168,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   184,   185,   186,    -1,   188,    -1,    -1,
     191,   192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,
      -1,   202,    -1,   204,   205,   206,   207,   208,     1,    -1,
      -1,    -1,     5,     6,     7,    -1,     9,    10,    11,    -1,
      13,    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    25,    26,    27,    28,    29,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    -1,    42,
      -1,    44,    45,    -1,    -1,    48,    -1,    50,    51,    52,
      -1,    54,    55,    -1,    -1,    58,    59,    -1,    -1,    -1,
      -1,    -1,    65,    -1,    -1,    68,    69,    -1,    71,    72,
      73,    -1,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    -1,
      93,    94,    95,    -1,    -1,    98,    99,   100,   101,   102,
     103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   118,   119,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   139,    -1,   141,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   149,   150,   151,   152,
     153,    -1,   155,    -1,   157,   158,   159,   160,   161,   162,
     163,   164,   165,    -1,   167,   168,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   184,   185,   186,    -1,   188,    -1,    -1,   191,   192,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,    -1,   202,
      -1,   204,   205,   206,   207,   208,     5,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,
      69,    70,    71,    72,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    93,    94,    95,    -1,    -1,    98,
      99,   100,   101,   102,   103,   104,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,
     119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     139,    -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,   150,   151,   152,   153,    -1,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,    -1,    -1,   168,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   184,   185,   186,    -1,   188,
      -1,    -1,   191,   192,    -1,    -1,    -1,    -1,    -1,     5,
       6,   200,    -1,   202,   203,   204,   205,    13,   207,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,
      -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    48,    49,    -1,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,    75,
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
      13,   207,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    45,    -1,    -1,    48,    49,    -1,    51,    -1,
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
     153,    -1,   155,    -1,   157,   158,   159,   160,   161,   162,
     163,   164,   165,    -1,    -1,   168,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   184,   185,   186,    -1,   188,    -1,    -1,   191,   192,
      -1,    -1,    -1,    -1,    -1,     5,     6,   200,    -1,   202,
      -1,   204,   205,    -1,   207,    15,    16,    17,    18,    19,
      -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,
      -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,
      70,    71,    72,    73,    -1,    75,    76,    77,    78,    79,
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
     200,    -1,   202,    -1,   204,   205,    -1,   207,    15,    16,
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
      -1,     5,     6,   200,    -1,   202,   203,   204,   205,    -1,
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
      -1,   155,   156,   157,   158,   159,   160,   161,   162,   163,
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
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
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
      -1,    -1,    -1,    -1,    -1,   127,    -1,    -1,    -1,    -1,
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
     119,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   127,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     139,    -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     149,   150,   151,   152,   153,    -1,   155,    -1,   157,   158,
     159,   160,   161,   162,   163,   164,   165,    -1,    -1,   168,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   184,   185,   186,    -1,   188,
      -1,    -1,   191,   192,    -1,    -1,    -1,    -1,    -1,     5,
       6,   200,    -1,   202,   203,   204,   205,    -1,   207,    15,
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
     153,    -1,   155,    -1,   157,   158,   159,   160,   161,   162,
     163,   164,   165,    -1,    -1,   168,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   184,   185,   186,    -1,   188,    -1,    -1,   191,   192,
      -1,    -1,    -1,    -1,    -1,     5,     6,   200,    -1,   202,
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
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,
      -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,
     150,   151,   152,   153,    -1,   155,    -1,   157,   158,   159,
     160,   161,   162,   163,   164,   165,    -1,    -1,   168,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   184,   185,   186,    -1,   188,    -1,
      -1,   191,   192,    -1,    -1,    -1,    -1,    -1,     5,     6,
     200,   201,   202,    -1,   204,   205,    -1,   207,    15,    16,
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
      -1,     5,     6,   200,   201,   202,    -1,   204,   205,    -1,
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
     204,   205,    13,   207,    15,    16,    17,    18,    19,    -1,
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
       5,     6,   200,    -1,   202,    -1,   204,   205,    -1,   207,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,
      65,    -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   118,   119,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
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
      -1,    -1,    -1,    55,    -1,    -1,    58,    -1,    -1,    -1,
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
      -1,    -1,     5,     6,   200,    -1,   202,   203,   204,   205,
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
      -1,    -1,    -1,    -1,    -1,     5,     6,   200,    -1,   202,
      -1,   204,   205,    -1,   207,    15,    16,    17,    18,    19,
      -1,    -1,    -1,    -1,    -1,    25,    26,    27,    28,    -1,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,
      -1,    51,    52,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,
      -1,    71,    72,    73,    -1,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   118,   119,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,
      -1,   141,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   149,
     150,   151,   152,   153,    -1,   155,    -1,   157,   158,   159,
     160,   161,   162,   163,   164,   165,    -1,    -1,   168,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   184,   185,   186,    -1,   188,    -1,
      -1,   191,   192,    -1,    -1,    -1,     5,     6,    -1,    -1,
     200,    -1,   202,    -1,   204,   205,    15,    16,    17,    18,
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
      -1,    -1,   191,   192,    -1,    -1,    -1,     5,     6,    -1,
      -1,   200,    -1,   202,    -1,   204,   205,    15,    16,    17,
      18,    19,    -1,    -1,    22,    -1,    -1,    25,    -1,    27,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
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
     188,    -1,    -1,   191,   192,    -1,    -1,    -1,     5,     6,
      -1,    -1,   200,    -1,   202,    -1,   204,   205,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    48,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    68,    69,    -1,    71,    72,    73,    -1,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    -1,    93,    94,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,    -1,    -1,
      -1,    -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   118,   119,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   139,    -1,   141,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   149,   150,   151,   152,   153,    -1,   155,    -1,
     157,   158,   159,   160,   161,   162,   163,   164,   165,    -1,
      -1,   168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   184,   185,   186,
      -1,   188,    -1,    -1,   191,   192,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   200,    -1,   202,    -1,   204,   205,    -1,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,    -1,    -1,    -1,   142,   143,   144,   145,   146,   147,
     148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   176,   177,
      -1,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,
      -1,   199,   200,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,
      -1,    -1,    -1,   141,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   154,    -1,    -1,    -1,
      -1,    64,    -1,    -1,    -1,    -1,    -1,   165,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,    -1,    -1,    -1,    -1,    -1,   204,    -1,    -1,    -1,
      -1,   209,    -1,    19,    -1,    -1,    -1,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,   141,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   154,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      -1,    -1,   165,    -1,   167,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,    -1,    -1,
      -1,   204,    -1,   206,    -1,    -1,    -1,    -1,    19,    -1,
      -1,    -1,    21,    22,    25,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      41,    -1,    -1,    -1,    -1,   141,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   154,    -1,
      -1,    -1,    -1,    64,    -1,    -1,    -1,    -1,    -1,   165,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,    -1,   204,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,    21,    22,   128,
     129,   130,    -1,    -1,   133,   134,   135,   136,   137,    -1,
     141,    -1,    -1,   142,   143,   144,   145,   146,   147,   148,
      -1,    -1,    -1,   154,    -1,    -1,    21,    22,    -1,    -1,
      -1,    -1,    -1,    -1,   165,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
      -1,    -1,   191,   192,    -1,    -1,    -1,    -1,    -1,    -1,
     199,   200,    -1,   204,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   116,   117,   118,   119,   120,    -1,    -1,   123,
     124,   125,   126,    -1,   128,   129,   130,   131,   132,    -1,
     134,   135,    21,    22,    -1,    -1,    -1,    -1,   142,   143,
     144,   116,   117,   118,   119,   120,    -1,    -1,   123,   124,
     125,   126,    -1,   128,   129,   130,   131,   132,    -1,   134,
     135,    21,    22,    -1,    -1,    -1,    -1,   142,    -1,   144,
      -1,    -1,    -1,   177,    -1,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   199,   200,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   199,   200,    -1,   116,   117,   118,
     119,   120,    -1,    -1,   123,   124,   125,   126,    -1,   128,
     129,   130,   131,   132,    -1,   134,   135,    21,    22,    -1,
      -1,    -1,    -1,   142,    -1,    -1,   116,   117,   118,   119,
     120,    -1,    -1,   123,   124,   125,   126,    -1,   128,   129,
     130,   131,   132,    -1,   134,   135,    21,    22,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     199,   200,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   199,
     200,    -1,   116,   117,   118,   119,   120,    -1,    -1,   123,
     124,   125,   126,    -1,   128,   129,   130,   131,   132,    -1,
     134,   135,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   116,   117,   118,   119,   120,    -1,    -1,   123,   124,
     125,   126,    -1,   128,   129,   130,   131,   132,    -1,   134,
     135,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    -1,    -1,   181,   182,   183,
     184,   185,   186,   187,   188,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   199,   200,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    -1,   182,   183,   184,
     185,   186,   187,   188,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   199,   200,    71,    72,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    -1,    98,    99,   100,   101,    71,    72,    73,
      -1,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    -1,    93,
      94,    95,    -1,    -1,    98,    99,   100,   101,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   156,    -1,    -1,    -1,    -1,    -1,    71,    -1,    73,
     165,    75,    76,    77,    78,    79,    -1,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    -1,    93,
      94,    95,   156,    35,    98,    99,   100,   101,    71,    72,
      73,   165,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    -1,
      93,    94,    95,    -1,    -1,    98,    99,   100,   101,    71,
      -1,    73,    -1,    75,    76,    77,    78,    79,    -1,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      -1,    93,    94,    95,    -1,    -1,    98,    99,   100,   101,
      -1,   165,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   118,   119,    -1,    -1,
      -1,    -1,    -1,   156,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,   165,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      -1,    93,    94,    95,    -1,    -1,    98,    99,   100,   101,
      -1,    -1,    71,   165,    73,    -1,    75,    76,    77,    78,
      79,    -1,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    93,    94,    95,   129,   130,    98,
      99,   100,   101,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   156,    -1,    -1,    -1,    -1,    -1,
      71,    -1,    73,   165,    75,    76,    77,    78,    79,    -1,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,    93,    94,    95,    -1,    -1,    98,    99,   100,
     101,    -1,    -1,    -1,    -1,    -1,   165,   199,   200,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   165
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   211,     0,     7,    30,    32,    34,    40,    50,    56,
      80,   102,   103,   167,   188,   200,   206,   213,   214,   218,
     227,   229,   230,   235,   284,   290,   321,   403,   411,   419,
     429,   479,   484,   489,    19,    20,   165,   274,   275,   276,
     158,   236,   237,   177,   232,   233,    57,    63,   408,   409,
     412,   165,   204,   216,   490,   480,   485,   141,   165,   309,
      34,    63,   107,   132,   192,   202,   279,   280,   281,   282,
     309,   213,   213,   213,     8,    36,   430,    62,   399,   176,
     175,   178,   175,   148,   165,   188,   199,   231,   231,   165,
     213,   213,   399,   408,   408,   408,   165,   141,   228,   281,
     281,   281,   202,   142,   143,   144,   175,   201,   107,   289,
     420,     5,     6,   426,    57,    63,   400,    15,    16,   139,
     158,   163,   165,   168,   202,   220,   275,   158,   237,   187,
     187,   231,   187,   187,   199,    22,    57,   234,   165,   410,
      57,    63,   215,   165,   165,   165,   165,   169,   226,   203,
     276,   281,   281,   281,   281,   167,   241,   242,    57,    63,
     291,   293,    57,    63,   413,   107,   107,    57,    63,   427,
     207,   404,   165,   169,   170,   171,   219,    15,    16,   158,
     163,   165,   220,   272,   273,   231,   231,   231,   165,   165,
     165,   176,   176,   192,   217,   178,   440,   242,   242,   169,
     203,   167,   294,   165,   414,   431,   401,   140,   277,   369,
     169,   170,   171,   175,   203,   234,    19,    25,    31,    41,
      49,    64,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   154,   204,   309,   434,   436,
     437,   441,   447,   449,   478,   478,    66,    79,    94,    99,
     101,   166,   417,   418,   481,   486,    35,    71,    73,    75,
      76,    77,    78,    79,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    93,    94,    95,    98,    99,
     100,   101,   118,   119,   165,   287,   288,   292,   178,   415,
     106,   424,   425,   208,   213,   402,   275,   140,   165,   395,
     398,   272,   182,   182,   182,   202,   182,   182,   202,   440,
     182,   182,   182,   182,   182,   202,   309,   182,   202,    33,
      60,    61,   124,   128,   177,   181,   184,   209,   200,   446,
     179,   166,   491,   207,   207,    21,    22,    38,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   128,   129,   130,   133,
     134,   135,   136,   137,   142,   143,   144,   145,   146,   147,
     148,   177,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   191,   192,   199,   200,    35,    35,   202,   285,
     242,    75,    79,    93,    94,    98,    99,   100,   101,   435,
     418,   165,   242,   369,   242,   275,   175,   178,   181,   393,
     450,   456,   458,     5,     6,    15,    16,    17,    18,    19,
      25,    27,    31,    39,    45,    48,    51,    55,    65,    68,
      69,    80,   102,   103,   104,   118,   119,   139,   149,   150,
     151,   152,   153,   155,   157,   158,   159,   160,   161,   162,
     163,   164,   168,   184,   185,   186,   191,   192,   200,   202,
     204,   205,   207,   225,   227,   301,   309,   314,   326,   333,
     336,   339,   343,   345,   347,   348,   350,   355,   358,   359,
     360,   367,   368,   434,   495,   503,   514,   517,   530,   531,
     534,   535,   460,   454,   165,   182,   462,   464,   466,   468,
     470,   472,   474,   476,   359,   182,   202,   448,   452,   127,
     306,   337,   359,    33,   181,    33,   181,   200,   209,   201,
     359,   200,   209,   447,   207,   482,   487,   165,   288,   165,
     288,   165,   201,    22,   165,   201,   153,   203,   369,   379,
     380,   381,   126,   178,   286,   138,   207,   298,   338,   207,
     178,   423,   432,   150,   165,   394,   397,   242,   165,   447,
     127,   133,   176,   392,   478,   478,   445,   478,   182,   182,
     182,   309,   311,   436,   494,   503,   514,   517,   530,   531,
     534,   535,   309,   182,     5,   102,   103,   182,   202,   182,
     202,   202,   182,   182,   202,   182,   202,   182,   202,   182,
     182,   202,    19,   182,   182,   360,   360,   150,   155,   182,
     309,   349,   202,   202,   202,   202,   202,   202,   224,   360,
     360,   360,   360,   360,    13,    49,   306,   156,   165,   337,
     496,   498,   529,   202,   200,   283,   139,   207,   339,   344,
     344,   344,   344,   203,    21,    22,   116,   117,   118,   119,
     120,   123,   124,   125,   126,   128,   129,   130,   131,   132,
     134,   135,   138,   142,   143,   144,   148,   177,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   199,   200,
     202,   478,   478,   203,   183,   442,   478,   285,   478,   285,
     478,   285,   165,   382,   383,   478,   165,   385,   386,   203,
     453,   337,   308,   478,   359,   203,   175,   533,   201,   201,
     201,   359,   492,   382,   384,   385,   387,   165,   288,   108,
     109,   110,   111,   112,   113,   114,   115,   133,   145,   146,
     147,   108,   109,   110,   111,   112,   113,   114,   115,   127,
     133,   145,   146,   147,   176,   202,     7,    50,   320,   206,
     175,   206,   203,   478,   478,   127,   360,   299,   421,   309,
     206,   207,   428,   202,    43,   175,   178,   393,   213,   392,
     359,   183,   183,   183,   166,   175,   212,   213,   444,   504,
     506,   312,   202,   182,   202,   334,   182,   182,   182,   524,
     337,   447,   359,   528,   359,   327,   329,   359,   331,   359,
     526,   337,   512,   515,   337,   182,   508,   447,   202,   202,
     351,   353,   359,   359,   359,   359,   359,   359,   171,   172,
     219,   202,    13,   201,   202,   127,   133,   176,   388,   533,
     175,   533,   203,   242,    70,   200,   203,   337,   498,   282,
       4,   342,   305,   283,    19,   156,   165,   434,    19,   156,
     165,   434,   360,   360,   360,   360,   360,   360,   165,   360,
     156,   165,   359,   360,   360,   434,   360,   360,   360,   530,
     535,   360,   360,   360,   360,    22,   360,   360,   360,   360,
     360,   360,   360,   360,   360,   360,   360,   129,   130,   156,
     165,   199,   200,   356,   434,   359,   203,   337,   183,   183,
     165,   438,   183,   286,   183,   286,   183,   286,   178,   183,
     444,   178,   183,   444,   308,   533,   183,   444,   127,   359,
     201,   165,   439,   213,   249,   250,   249,   250,   359,   150,
     165,   389,   390,   433,   381,   381,   381,   360,   305,   165,
     405,   407,   375,   359,   165,   150,   165,   447,   392,   359,
     213,   451,   457,   459,   478,   447,   447,   478,    70,   337,
     498,   502,   165,   359,   478,   518,   520,   522,   447,   533,
     183,   444,   175,   533,   203,   447,   447,   203,   447,   203,
     447,   533,   447,   383,   533,   510,   386,   183,   359,   359,
     447,   285,   203,   203,   203,   203,   203,   203,   359,   150,
     165,   202,   263,   202,   359,   359,   359,   203,   156,   165,
      13,   307,   528,   165,   203,   498,   496,   175,   203,   203,
     201,   202,   285,     1,    26,    28,    29,    38,    40,    44,
      52,    54,    58,    59,    65,   105,   207,   208,   213,   238,
     239,   248,   259,   260,   262,   264,   265,   266,   267,   268,
     269,   270,   271,   302,   310,   315,   316,   317,   318,   319,
     321,   325,   346,   360,   342,   182,   202,   182,   202,   202,
     202,   201,    19,   156,   165,   434,   178,   156,   165,   359,
     202,   202,   156,   165,   359,     1,   202,   201,   175,   203,
     461,   455,   175,   183,   206,   463,   183,   467,   183,   471,
     183,   478,   475,   382,   478,   477,   385,   183,   203,   448,
     478,   359,   176,   212,   406,   416,   213,   382,   483,   385,
     488,   203,   202,    43,   175,   178,   181,   388,   300,   176,
     406,   416,    40,   167,   208,   284,   376,   203,   202,    43,
     213,   392,   359,   213,   183,   183,   183,   498,   203,   203,
     203,   183,   444,   203,   183,   447,   383,   386,   183,   203,
     202,   447,   359,   203,   183,   183,   183,   183,   203,   183,
     183,   203,   447,   183,   342,   203,   203,   183,   286,   202,
     178,   222,   202,    43,   165,   323,    20,   175,   263,   203,
     202,   133,   388,   202,   208,   533,   203,   175,   201,   200,
     496,   127,   133,   165,   176,   181,   340,   341,   286,   127,
     359,   298,    61,   359,   165,   165,   213,   158,    58,   359,
     242,   127,   359,   303,   213,   213,    10,    10,    11,   246,
      13,     9,    42,   213,   213,   213,   213,   213,   213,    66,
     322,   213,   108,   109,   110,   111,   112,   113,   114,   115,
     121,   122,   127,   133,   136,   137,   145,   146,   147,   176,
     285,   361,   359,   363,   359,   200,   203,   337,   496,   359,
     182,   202,   360,   202,   201,   359,   200,   203,   337,   496,
     202,   201,   357,   203,   337,   165,   443,   165,   465,   469,
     473,   448,   359,   165,   212,   493,   208,   208,   359,   165,
     150,   165,   478,   359,   208,   359,   405,   422,   165,     8,
     369,   374,   359,   165,   359,   213,   505,   507,   313,   203,
     202,   165,   335,   183,   183,   183,   525,   307,   183,   328,
     330,   332,   527,   513,   516,   183,   509,   202,   242,   352,
     183,   203,   337,   223,   173,   359,   165,   175,   203,   337,
     150,   165,   202,    20,   133,   388,   359,   359,   359,   263,
     203,   496,   203,   165,   165,   202,   165,   165,   175,   203,
     242,   359,    14,   359,   176,   176,   178,   158,   298,   359,
     305,   202,   202,   200,   277,   278,   278,   202,   202,   207,
     324,   397,   360,   360,   360,   360,   360,   360,   360,   360,
     360,   360,   360,   530,   535,   360,   360,   360,   360,   360,
     360,   360,   286,   447,   203,   478,   203,   496,   175,   203,
     203,   203,   365,   359,   359,   203,   496,   175,   203,   203,
     359,   203,   176,   208,   203,   202,    43,   388,    37,   295,
     208,   176,    57,    63,   372,    67,   373,   213,   203,   213,
     202,   202,   359,   183,   519,   521,   523,   202,   203,   202,
     202,   202,   202,   202,    70,   502,   202,   511,   202,   203,
     359,   298,   349,   354,   203,   221,   203,   165,   203,   202,
      43,   323,   337,   359,   359,   203,    20,   201,   165,   340,
     338,   298,   478,   359,   304,   359,   359,   276,   202,   202,
     359,   323,   396,   242,   183,   183,   201,   496,   478,   203,
     203,   201,   496,   203,   359,   359,   165,   359,   296,   478,
      47,   373,    46,   106,   370,   502,   502,   203,   202,   202,
     202,   202,   306,   307,   359,   359,   359,   337,   502,   202,
     502,   203,   349,   169,   206,   359,   165,   203,   203,   133,
     388,   337,   203,   203,   208,   203,   203,   201,   263,   359,
     203,   203,   208,   213,   397,   338,   362,   364,   203,   203,
     183,   203,   203,   203,   207,   213,    33,   371,   370,   372,
     202,   496,   499,   500,   501,   501,   359,   502,   502,   496,
     497,   203,   203,   203,   203,   203,   533,   501,   502,   497,
     359,   203,   206,   359,   359,   203,   295,    12,   247,   242,
      20,   203,   242,   178,   393,   366,   305,   377,   371,   389,
     390,   391,   496,   175,   533,   203,   203,   203,   501,   501,
     203,   203,   203,   497,   203,   206,   532,   359,   206,   248,
     315,   316,   317,   318,   360,   213,   261,   337,   242,   298,
     447,   392,   297,   292,   378,   203,   202,   203,   203,   203,
      53,   201,   532,   359,   207,   251,   254,   203,   298,   392,
     359,   208,   213,   292,   496,   359,   201,   532,   252,    12,
      23,    24,   240,   243,   248,   242,   359,   213,   242,   203,
     208,   305,   242,   202,   213,   298,   213,   338,   253,   244,
     359,   208,   207,   255,   258,   203,   295,   256,   248,   242,
     305,   213,   245,   257,   255,   208,   243,   295
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
     407,   407,   407,   408,   408,   408,   410,   409,   411,   411,
     412,   413,   413,   413,   414,   415,   415,   416,   416,   417,
     417,   418,   418,   420,   421,   422,   419,   423,   423,   424,
     424,   425,   426,   426,   426,   426,   427,   427,   427,   428,
     428,   430,   431,   432,   429,   433,   433,   433,   433,   433,
     433,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   435,   435,
     435,   435,   435,   435,   435,   435,   436,   437,   437,   437,
     438,   438,   438,   439,   439,   439,   439,   439,   440,   440,
     440,   440,   440,   441,   442,   443,   441,   444,   444,   445,
     445,   446,   446,   446,   446,   447,   447,   448,   448,   449,
     449,   449,   449,   450,   451,   449,   449,   449,   449,   452,
     449,   453,   449,   449,   449,   449,   449,   449,   449,   449,
     449,   449,   449,   449,   449,   454,   455,   449,   449,   456,
     457,   449,   458,   459,   449,   460,   461,   449,   449,   462,
     463,   449,   464,   465,   449,   449,   466,   467,   449,   468,
     469,   449,   449,   470,   471,   449,   472,   473,   449,   474,
     475,   449,   476,   477,   449,   478,   478,   478,   480,   481,
     482,   483,   479,   485,   486,   487,   488,   484,   490,   491,
     492,   493,   489,   494,   494,   494,   494,   494,   494,   494,
     495,   495,   495,   495,   495,   496,   496,   496,   496,   496,
     496,   496,   496,   497,   497,   498,   499,   499,   500,   500,
     501,   501,   502,   502,   504,   505,   503,   506,   507,   503,
     508,   509,   503,   510,   511,   503,   512,   513,   503,   514,
     515,   516,   514,   517,   518,   519,   517,   520,   521,   517,
     522,   523,   517,   517,   524,   525,   517,   517,   526,   527,
     517,   528,   528,   529,   530,   531,   531,   531,   532,   532,
     533,   533,   534,   534,   535
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
       5,     0,     0,     9,     0,     0,     9,     0,     0,     9,
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
       0,     1,     3,     0,     1,     1,     0,     5,     3,     3,
       5,     0,     1,     1,     1,     0,     2,     0,     1,     1,
       2,     0,     1,     0,     0,     0,    13,     0,     2,     0,
       1,     3,     1,     1,     2,     2,     0,     1,     1,     1,
       3,     0,     0,     0,     9,     1,     4,     3,     3,     6,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     4,
       1,     3,     3,     0,     1,     3,     3,     5,     0,     2,
       2,     2,     2,     4,     0,     0,     7,     1,     1,     1,
       3,     3,     2,     4,     3,     1,     2,     0,     4,     1,
       1,     1,     1,     0,     0,     6,     4,     4,     3,     0,
       6,     0,     7,     4,     2,     2,     3,     2,     3,     2,
       2,     3,     3,     3,     2,     0,     0,     6,     2,     0,
       0,     6,     0,     0,     6,     0,     0,     6,     1,     0,
       0,     6,     0,     0,     7,     1,     0,     0,     6,     0,
       0,     7,     1,     0,     0,     6,     0,     0,     7,     0,
       0,     6,     0,     0,     6,     1,     3,     3,     0,     0,
       0,     0,    12,     0,     0,     0,     0,    12,     0,     0,
       0,     0,    13,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     3,     5,     5,     6,
       6,     8,     8,     0,     1,     2,     3,     5,     1,     2,
       1,     0,     0,     1,     0,     0,    10,     0,     0,    10,
       0,     0,    10,     0,     0,    11,     0,     0,     7,     5,
       0,     0,    10,     3,     0,     0,    11,     0,     0,    11,
       0,     0,    10,     5,     0,     0,     9,     5,     0,     0,
      10,     1,     3,     0,     5,     5,     7,     9,     0,     3,
       0,     1,    11,    12,    13
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

  case 308: /* expression_block: '{' $@19 expressions $@20 '}' expression_block_finally  */
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
        (yyval.pVarDecl)->atEnd = tokAt(scanner,(yylsp[-1]));
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
        (yyval.pVarDecl)->atEnd = tokAt(scanner,(yylsp[-1]));
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

  case 383: /* expr_cast: "cast" '<' $@25 type_declaration_no_options '>' $@26 '(' expr ')'  */
                                                                                                                                                        {
        (yyval.pExpression) = new ExprCast(tokAt(scanner,(yylsp[-8])),(yyvsp[-1].pExpression),(yyvsp[-5].pTypeDecl));
    }
    break;

  case 384: /* $@27: %empty  */
                            { yyextra->das_arrow_depth ++; }
    break;

  case 385: /* $@28: %empty  */
                                                                                                   { yyextra->das_arrow_depth --; }
    break;

  case 386: /* expr_cast: "upcast" '<' $@27 type_declaration_no_options '>' $@28 '(' expr ')'  */
                                                                                                                                                          {
        auto pCast = new ExprCast(tokAt(scanner,(yylsp[-8])),(yyvsp[-1].pExpression),(yyvsp[-5].pTypeDecl));
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

  case 389: /* expr_cast: "reinterpret" '<' $@29 type_declaration_no_options '>' $@30 '(' expr ')'  */
                                                                                                                                                               {
        auto pCast = new ExprCast(tokAt(scanner,(yylsp[-8])),(yyvsp[-1].pExpression),(yyvsp[-5].pTypeDecl));
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
        // block span is brace-to-brace (@$), not the statements' span (@block)
        (yyval.pExpression) = ast_makeBlock(scanner,0,nullptr,nullptr,nullptr,new TypeDecl(Type::autoinfer),(yyvsp[-1].pExpression),tokAt(scanner,(yyloc)),tokAt(scanner,(yyloc)),LineInfo());
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
        (yyval.pVarDecl)->atEnd = tokAt(scanner,(yylsp[-1]));
    }
    break;

  case 659: /* let_variable_declaration: let_variable_name_with_pos_list ':' type_declaration_no_options copy_or_move_or_clone expr SEMICOLON  */
                                                                                                                                        {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-5].pNameWithPosList),(yyvsp[-3].pTypeDecl),(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
        (yyval.pVarDecl)->atEnd = tokAt(scanner,(yylsp[-1]));
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
        (yyval.pVarDecl)->atEnd = tokAt(scanner,(yylsp[-1]));
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

  case 690: /* distinct_alias: optional_public_or_private_alias "name" "name" '=' type_declaration  */
                                                                                               {
        if ( *(yyvsp[-3].s) != "distinct" ) {
            das2_yyerror(scanner,"expected 'distinct', got '"+*(yyvsp[-3].s)+"'",tokAt(scanner,(yylsp[-3])),
                CompilationError::invalid_distinct_type);
        } else {
            ast_distinctDeclaration(scanner,(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])),!(yyvsp[-4].b),(yyvsp[0].pTypeDecl));
        }
        delete (yyvsp[-3].s);
        delete (yyvsp[-2].s);
    }
    break;

  case 691: /* optional_public_or_private_enum: %empty  */
                     { (yyval.b) = yyextra->g_Program->thisModule->isPublic; }
    break;

  case 692: /* optional_public_or_private_enum: "private"  */
                     { (yyval.b) = false; }
    break;

  case 693: /* optional_public_or_private_enum: "public"  */
                     { (yyval.b) = true; }
    break;

  case 694: /* enum_name: "name"  */
                   {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto pubename = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeEnumeration(pubename);
        }
        (yyval.pEnum) = ast_addEmptyEnum(scanner, (yyvsp[0].s), tokAt(scanner,(yylsp[0])));
    }
    break;

  case 695: /* optional_enum_basic_type_declaration: %empty  */
        {
        (yyval.type) = Type::tInt;
    }
    break;

  case 696: /* optional_enum_basic_type_declaration: ':' enum_basic_type_declaration  */
                                              {
        (yyval.type) = (yyvsp[0].type);
    }
    break;

  case 703: /* $@51: %empty  */
                                                                     {
        yyextra->push_nesteds(DAS_EMIT_COMMA);
    }
    break;

  case 704: /* $@52: %empty  */
                                                                                                                                {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeEnumerationEntries(tak);
        }
    }
    break;

  case 705: /* $@53: %empty  */
                                    {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterEnumerationEntries(tak);
        }
        yyextra->pop_nesteds();
    }
    break;

  case 706: /* enum_declaration: optional_annotation_list_with_emit_semis "enum" $@51 optional_public_or_private_enum enum_name optional_enum_basic_type_declaration optional_emit_commas '{' $@52 enum_list optional_commas $@53 '}'  */
          {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto pubename = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterEnumeration((yyvsp[-8].pEnum)->name.c_str(),pubename);
        }
        ast_enumDeclaration(scanner,(yyvsp[-12].faList),tokAt(scanner,(yylsp[-12])),(yyvsp[-9].b),(yyvsp[-8].pEnum),(yyvsp[-3].pEnumList),(yyvsp[-7].type));
    }
    break;

  case 707: /* optional_structure_parent: %empty  */
                                        { (yyval.s) = nullptr; }
    break;

  case 708: /* optional_structure_parent: ':' name_in_namespace  */
                                        { (yyval.s) = (yyvsp[0].s); }
    break;

  case 709: /* optional_sealed: %empty  */
                        { (yyval.b) = false; }
    break;

  case 710: /* optional_sealed: "sealed"  */
                        { (yyval.b) = true; }
    break;

  case 711: /* structure_name: optional_sealed "name" optional_structure_parent  */
                                                                           {
        (yyval.pStructure) = ast_structureName(scanner,(yyvsp[-2].b),(yyvsp[-1].s),tokAt(scanner,(yylsp[-1])),(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
    }
    break;

  case 712: /* class_or_struct: "class"  */
                    { (yyval.i) = CorS_Class; }
    break;

  case 713: /* class_or_struct: "struct"  */
                    { (yyval.i) = CorS_Struct; }
    break;

  case 714: /* class_or_struct: "class" "template"  */
                                  { (yyval.i) = CorS_ClassTemplate; }
    break;

  case 715: /* class_or_struct: "struct" "template"  */
                                  { (yyval.i) = CorS_StructTemplate; }
    break;

  case 716: /* optional_public_or_private_structure: %empty  */
                     { (yyval.b) = yyextra->g_Program->thisModule->isPublic; }
    break;

  case 717: /* optional_public_or_private_structure: "private"  */
                     { (yyval.b) = false; }
    break;

  case 718: /* optional_public_or_private_structure: "public"  */
                     { (yyval.b) = true; }
    break;

  case 719: /* optional_struct_variable_declaration_list: ';'  */
            {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 720: /* optional_struct_variable_declaration_list: '{' struct_variable_declaration_list '}'  */
                                                       {
        (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList);
    }
    break;

  case 721: /* $@54: %empty  */
                                                     {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 722: /* $@55: %empty  */
                                                                         {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeStructure(tak);
        }
    }
    break;

  case 723: /* $@56: %empty  */
                                             {
        if ( (yyvsp[-1].pStructure) ) {
            (yyvsp[-1].pStructure)->isClass = (yyvsp[-4].i)==CorS_Class || (yyvsp[-4].i)==CorS_ClassTemplate;
            (yyvsp[-1].pStructure)->isTemplate = (yyvsp[-4].i)==CorS_ClassTemplate || (yyvsp[-4].i)==CorS_StructTemplate;
            (yyvsp[-1].pStructure)->privateStructure = !(yyvsp[-3].b);
        }
    }
    break;

  case 724: /* structure_declaration: optional_annotation_list_with_emit_semis $@54 class_or_struct optional_public_or_private_structure $@55 structure_name optional_emit_semis $@56 optional_struct_variable_declaration_list  */
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

  case 725: /* variable_name_with_pos_list: "name"  */
                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = pSL;
        delete (yyvsp[0].s);
    }
    break;

  case 726: /* variable_name_with_pos_list: "$i" '(' expr ')'  */
                                     {
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = pSL;
    }
    break;

  case 727: /* variable_name_with_pos_list: "name" "aka" "name"  */
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

  case 728: /* variable_name_with_pos_list: variable_name_with_pos_list ',' "name"  */
                                                         {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = (yyvsp[-2].pNameWithPosList);
        delete (yyvsp[0].s);
    }
    break;

  case 729: /* variable_name_with_pos_list: variable_name_with_pos_list ',' "$i" '(' expr ')'  */
                                                                           {
        (yyvsp[-5].pNameWithPosList)->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = (yyvsp[-5].pNameWithPosList);
    }
    break;

  case 730: /* variable_name_with_pos_list: variable_name_with_pos_list ',' "name" "aka" "name"  */
                                                                               {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-4].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[-2].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-2]))));
        (yyval.pNameWithPosList) = (yyvsp[-4].pNameWithPosList);
        delete (yyvsp[-2].s);
        delete (yyvsp[0].s);
    }
    break;

  case 731: /* basic_type_declaration: "bool"  */
                        { (yyval.type) = Type::tBool; }
    break;

  case 732: /* basic_type_declaration: "string"  */
                        { (yyval.type) = Type::tString; }
    break;

  case 733: /* basic_type_declaration: "int"  */
                        { (yyval.type) = Type::tInt; }
    break;

  case 734: /* basic_type_declaration: "int8"  */
                        { (yyval.type) = Type::tInt8; }
    break;

  case 735: /* basic_type_declaration: "int16"  */
                        { (yyval.type) = Type::tInt16; }
    break;

  case 736: /* basic_type_declaration: "int64"  */
                        { (yyval.type) = Type::tInt64; }
    break;

  case 737: /* basic_type_declaration: "int2"  */
                        { (yyval.type) = Type::tInt2; }
    break;

  case 738: /* basic_type_declaration: "int3"  */
                        { (yyval.type) = Type::tInt3; }
    break;

  case 739: /* basic_type_declaration: "int4"  */
                        { (yyval.type) = Type::tInt4; }
    break;

  case 740: /* basic_type_declaration: "uint"  */
                        { (yyval.type) = Type::tUInt; }
    break;

  case 741: /* basic_type_declaration: "uint8"  */
                        { (yyval.type) = Type::tUInt8; }
    break;

  case 742: /* basic_type_declaration: "uint16"  */
                        { (yyval.type) = Type::tUInt16; }
    break;

  case 743: /* basic_type_declaration: "uint64"  */
                        { (yyval.type) = Type::tUInt64; }
    break;

  case 744: /* basic_type_declaration: "uint2"  */
                        { (yyval.type) = Type::tUInt2; }
    break;

  case 745: /* basic_type_declaration: "uint3"  */
                        { (yyval.type) = Type::tUInt3; }
    break;

  case 746: /* basic_type_declaration: "uint4"  */
                        { (yyval.type) = Type::tUInt4; }
    break;

  case 747: /* basic_type_declaration: "float"  */
                        { (yyval.type) = Type::tFloat; }
    break;

  case 748: /* basic_type_declaration: "float2"  */
                        { (yyval.type) = Type::tFloat2; }
    break;

  case 749: /* basic_type_declaration: "float3"  */
                        { (yyval.type) = Type::tFloat3; }
    break;

  case 750: /* basic_type_declaration: "float4"  */
                        { (yyval.type) = Type::tFloat4; }
    break;

  case 751: /* basic_type_declaration: "void"  */
                        { (yyval.type) = Type::tVoid; }
    break;

  case 752: /* basic_type_declaration: "range"  */
                        { (yyval.type) = Type::tRange; }
    break;

  case 753: /* basic_type_declaration: "urange"  */
                        { (yyval.type) = Type::tURange; }
    break;

  case 754: /* basic_type_declaration: "range64"  */
                        { (yyval.type) = Type::tRange64; }
    break;

  case 755: /* basic_type_declaration: "urange64"  */
                        { (yyval.type) = Type::tURange64; }
    break;

  case 756: /* basic_type_declaration: "double"  */
                        { (yyval.type) = Type::tDouble; }
    break;

  case 757: /* basic_type_declaration: "bitfield"  */
                        { (yyval.type) = Type::tBitfield; }
    break;

  case 758: /* enum_basic_type_declaration: "int"  */
                        { (yyval.type) = Type::tInt; }
    break;

  case 759: /* enum_basic_type_declaration: "int8"  */
                        { (yyval.type) = Type::tInt8; }
    break;

  case 760: /* enum_basic_type_declaration: "int16"  */
                        { (yyval.type) = Type::tInt16; }
    break;

  case 761: /* enum_basic_type_declaration: "uint"  */
                        { (yyval.type) = Type::tUInt; }
    break;

  case 762: /* enum_basic_type_declaration: "uint8"  */
                        { (yyval.type) = Type::tUInt8; }
    break;

  case 763: /* enum_basic_type_declaration: "uint16"  */
                        { (yyval.type) = Type::tUInt16; }
    break;

  case 764: /* enum_basic_type_declaration: "int64"  */
                        { (yyval.type) = Type::tInt64; }
    break;

  case 765: /* enum_basic_type_declaration: "uint64"  */
                        { (yyval.type) = Type::tUInt64; }
    break;

  case 766: /* structure_type_declaration: name_in_namespace  */
                                 {
        (yyval.pTypeDecl) = yyextra->g_Program->makeTypeDeclaration(tokAt(scanner,(yylsp[0])),*(yyvsp[0].s));
        if ( !(yyval.pTypeDecl) ) {
            (yyval.pTypeDecl) = new TypeDecl(Type::tVoid);
            (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
        }
        delete (yyvsp[0].s);
    }
    break;

  case 767: /* auto_type_declaration: "auto"  */
                       {
        (yyval.pTypeDecl) = new TypeDecl(Type::autoinfer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 768: /* auto_type_declaration: "auto" '(' "name" ')'  */
                                            {
        das_checkName(scanner,*(yyvsp[-1].s),tokAt(scanner,(yylsp[-1])));
        (yyval.pTypeDecl) = new TypeDecl(Type::autoinfer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-3]));
        (yyval.pTypeDecl)->alias = *(yyvsp[-1].s);
        delete (yyvsp[-1].s);
    }
    break;

  case 769: /* auto_type_declaration: "$t" '(' expr ')'  */
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

  case 770: /* bitfield_bits: "name"  */
                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<string>();
        pSL->push_back(*(yyvsp[0].s));
        (yyval.pNameList) = pSL;
        delete (yyvsp[0].s);
    }
    break;

  case 771: /* bitfield_bits: bitfield_bits ';' "name"  */
                                           {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameList)->push_back(*(yyvsp[0].s));
        (yyval.pNameList) = (yyvsp[-2].pNameList);
        delete (yyvsp[0].s);
    }
    break;

  case 772: /* bitfield_bits: bitfield_bits ',' "name"  */
                                           {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameList)->push_back(*(yyvsp[0].s));
        (yyval.pNameList) = (yyvsp[-2].pNameList);
        delete (yyvsp[0].s);
    }
    break;

  case 773: /* bitfield_alias_bits: %empty  */
        {
        auto pSL = new vector<tuple<string,Expression *>>();
        (yyval.pNameExprList) = pSL;

    }
    break;

  case 774: /* bitfield_alias_bits: "name"  */
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

  case 775: /* bitfield_alias_bits: "name" '=' expr  */
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

  case 776: /* bitfield_alias_bits: bitfield_alias_bits commas "name"  */
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

  case 777: /* bitfield_alias_bits: bitfield_alias_bits commas "name" '=' expr  */
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

  case 778: /* bitfield_basic_type_declaration: %empty  */
                             { (yyval.type) = Type::tBitfield; }
    break;

  case 779: /* bitfield_basic_type_declaration: ':' "uint8"  */
                             { (yyval.type) = Type::tBitfield8; }
    break;

  case 780: /* bitfield_basic_type_declaration: ':' "uint16"  */
                             { (yyval.type) = Type::tBitfield16; }
    break;

  case 781: /* bitfield_basic_type_declaration: ':' "uint"  */
                             { (yyval.type) = Type::tBitfield; }
    break;

  case 782: /* bitfield_basic_type_declaration: ':' "uint64"  */
                             { (yyval.type) = Type::tBitfield64; }
    break;

  case 783: /* bitfield_type_declaration: "bitfield" bitfield_basic_type_declaration '<' '>'  */
                                                                          {
            (yyval.pTypeDecl) = new TypeDecl((yyvsp[-2].type));
            (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-2]));
    }
    break;

  case 784: /* $@57: %empty  */
                                                                     { yyextra->das_arrow_depth ++; }
    break;

  case 785: /* $@58: %empty  */
                                                                                                                            { yyextra->das_arrow_depth --; }
    break;

  case 786: /* bitfield_type_declaration: "bitfield" bitfield_basic_type_declaration '<' $@57 bitfield_bits '>' $@58  */
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

  case 789: /* table_type_pair: type_declaration  */
                                      {
        (yyval.aTypePair).firstType = (yyvsp[0].pTypeDecl);
        (yyval.aTypePair).secondType = new TypeDecl(Type::tVoid);
    }
    break;

  case 790: /* table_type_pair: type_declaration c_or_s type_declaration  */
                                                                             {
        (yyval.aTypePair).firstType = (yyvsp[-2].pTypeDecl);
        (yyval.aTypePair).secondType = (yyvsp[0].pTypeDecl);
    }
    break;

  case 791: /* dim_list: '[' expr ']'  */
                             {
        (yyval.pTypeDecl) = appendDimExpr(nullptr, (yyvsp[-1].pExpression), tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 792: /* dim_list: '[' ']'  */
                {
        (yyval.pTypeDecl) = appendDimExpr(nullptr, nullptr, tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 793: /* dim_list: dim_list '[' expr ']'  */
                                            {
        (yyval.pTypeDecl) = appendDimExpr((yyvsp[-3].pTypeDecl), (yyvsp[-1].pExpression), tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 794: /* dim_list: dim_list '[' ']'  */
                              {
        (yyval.pTypeDecl) = appendDimExpr((yyvsp[-2].pTypeDecl), nullptr, tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 795: /* type_declaration_no_options: type_declaration_no_options_no_dim  */
                                                     {
        (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl);
    }
    break;

  case 796: /* type_declaration_no_options: type_declaration_no_options_no_dim dim_list  */
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

  case 797: /* optional_expr_list_in_braces: %empty  */
            { (yyval.pExpression) = nullptr; }
    break;

  case 798: /* optional_expr_list_in_braces: '(' expr_list optional_comma ')'  */
                                                { (yyval.pExpression) = (yyvsp[-2].pExpression); }
    break;

  case 799: /* type_declaration_no_options_no_dim: basic_type_declaration  */
                                                            { (yyval.pTypeDecl) = new TypeDecl((yyvsp[0].type)); (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0])); }
    break;

  case 800: /* type_declaration_no_options_no_dim: auto_type_declaration  */
                                                            { (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl); }
    break;

  case 801: /* type_declaration_no_options_no_dim: bitfield_type_declaration  */
                                                            { (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl); }
    break;

  case 802: /* type_declaration_no_options_no_dim: structure_type_declaration  */
                                                            { (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl); }
    break;

  case 803: /* $@59: %empty  */
                     { yyextra->das_arrow_depth ++; }
    break;

  case 804: /* $@60: %empty  */
                                                                                     { yyextra->das_arrow_depth --; }
    break;

  case 805: /* type_declaration_no_options_no_dim: "type" '<' $@59 type_declaration '>' $@60  */
                                                                                                                      {
        (yyvsp[-2].pTypeDecl)->autoToAlias = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 806: /* type_declaration_no_options_no_dim: "typedecl" '(' expr ')'  */
                                               {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeDecl);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-3]),(yylsp[-1]));
        (yyval.pTypeDecl)->typeMacroExpr.push_back((yyvsp[-1].pExpression));
    }
    break;

  case 807: /* type_declaration_no_options_no_dim: name_in_namespace '(' optional_expr_list ')'  */
                                                                      {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeMacro);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-3]), (yylsp[-1]));
        (yyval.pTypeDecl)->typeMacroExpr = sequenceToList((yyvsp[-1].pExpression));
        (yyval.pTypeDecl)->typeMacroExpr.insert((yyval.pTypeDecl)->typeMacroExpr.begin(), new ExprConstString(tokAt(scanner,(yylsp[-3])), *(yyvsp[-3].s)));
        delete (yyvsp[-3].s);
    }
    break;

  case 808: /* type_declaration_no_options_no_dim: '$' name_in_namespace optional_expr_list_in_braces  */
                                                                            {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeMacro);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-1]), (yylsp[0]));
        (yyval.pTypeDecl)->typeMacroExpr = sequenceToList((yyvsp[0].pExpression));
        (yyval.pTypeDecl)->typeMacroExpr.insert((yyval.pTypeDecl)->typeMacroExpr.begin(), new ExprConstString(tokAt(scanner,(yylsp[-1])), *(yyvsp[-1].s)));
        delete (yyvsp[-1].s);
    }
    break;

  case 809: /* $@61: %empty  */
                                    { yyextra->das_arrow_depth ++; }
    break;

  case 810: /* type_declaration_no_options_no_dim: name_in_namespace '<' $@61 type_declaration_no_options_list '>' optional_expr_list_in_braces  */
                                                                                                                                                         {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeMacro);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-5]), (yylsp[0]));
        (yyval.pTypeDecl)->typeMacroExpr = typesAndSequenceToList((yyvsp[-2].pTypeDeclList),(yyvsp[0].pExpression));
        (yyval.pTypeDecl)->typeMacroExpr.insert((yyval.pTypeDecl)->typeMacroExpr.begin(), new ExprConstString(tokAt(scanner,(yylsp[-5])), *(yyvsp[-5].s)));
        delete (yyvsp[-5].s);
    }
    break;

  case 811: /* $@62: %empty  */
                                        { yyextra->das_arrow_depth ++; }
    break;

  case 812: /* type_declaration_no_options_no_dim: '$' name_in_namespace '<' $@62 type_declaration_no_options_list '>' optional_expr_list_in_braces  */
                                                                                                                                                             {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeMacro);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-5]), (yylsp[0]));
        (yyval.pTypeDecl)->typeMacroExpr = typesAndSequenceToList((yyvsp[-2].pTypeDeclList),(yyvsp[0].pExpression));
        (yyval.pTypeDecl)->typeMacroExpr.insert((yyval.pTypeDecl)->typeMacroExpr.begin(), new ExprConstString(tokAt(scanner,(yylsp[-5])), *(yyvsp[-5].s)));
        delete (yyvsp[-5].s);
    }
    break;

  case 813: /* type_declaration_no_options_no_dim: type_declaration_no_options '-' '[' ']'  */
                                                          {
        (yyvsp[-3].pTypeDecl)->removeDim = true;
        (yyval.pTypeDecl) = (yyvsp[-3].pTypeDecl);
    }
    break;

  case 814: /* type_declaration_no_options_no_dim: type_declaration_no_options "explicit"  */
                                                           {
        (yyvsp[-1].pTypeDecl)->isExplicit = true;
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 815: /* type_declaration_no_options_no_dim: type_declaration_no_options "const"  */
                                                        {
        (yyvsp[-1].pTypeDecl)->constant = true;
        (yyvsp[-1].pTypeDecl)->removeConstant = false;
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 816: /* type_declaration_no_options_no_dim: type_declaration_no_options '-' "const"  */
                                                            {
        (yyvsp[-2].pTypeDecl)->constant = false;
        (yyvsp[-2].pTypeDecl)->removeConstant = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 817: /* type_declaration_no_options_no_dim: type_declaration_no_options '&'  */
                                                  {
        (yyvsp[-1].pTypeDecl)->ref = true;
        (yyvsp[-1].pTypeDecl)->removeRef = false;
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 818: /* type_declaration_no_options_no_dim: type_declaration_no_options '-' '&'  */
                                                      {
        (yyvsp[-2].pTypeDecl)->ref = false;
        (yyvsp[-2].pTypeDecl)->removeRef = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 819: /* type_declaration_no_options_no_dim: type_declaration_no_options '#'  */
                                                  {
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
        (yyval.pTypeDecl)->temporary = true;
    }
    break;

  case 820: /* type_declaration_no_options_no_dim: type_declaration_no_options "implicit"  */
                                                           {
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
        (yyval.pTypeDecl)->implicit = true;
    }
    break;

  case 821: /* type_declaration_no_options_no_dim: type_declaration_no_options '-' '#'  */
                                                      {
        (yyvsp[-2].pTypeDecl)->temporary = false;
        (yyvsp[-2].pTypeDecl)->removeTemporary = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 822: /* type_declaration_no_options_no_dim: type_declaration_no_options "==" "const"  */
                                                               {
        (yyvsp[-2].pTypeDecl)->explicitConst = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 823: /* type_declaration_no_options_no_dim: type_declaration_no_options "==" '&'  */
                                                         {
        (yyvsp[-2].pTypeDecl)->explicitRef = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 824: /* type_declaration_no_options_no_dim: type_declaration_no_options '?'  */
                                                  {
        (yyval.pTypeDecl) = new TypeDecl(Type::tPointer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-1]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 825: /* $@63: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 826: /* $@64: %empty  */
                                                                                               { yyextra->das_arrow_depth --; }
    break;

  case 827: /* type_declaration_no_options_no_dim: "smart_ptr" '<' $@63 type_declaration '>' $@64  */
                                                                                                                                {
        (yyval.pTypeDecl) = new TypeDecl(Type::tPointer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->smartPtr = true;
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 828: /* type_declaration_no_options_no_dim: type_declaration_no_options "??"  */
                                                 {
        (yyval.pTypeDecl) = new TypeDecl(Type::tPointer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-1]));
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::tPointer);
        (yyval.pTypeDecl)->firstType->at = tokAt(scanner,(yylsp[-1]));
        (yyval.pTypeDecl)->firstType->firstType = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 829: /* $@65: %empty  */
                           { yyextra->das_arrow_depth ++; }
    break;

  case 830: /* $@66: %empty  */
                                                                                           { yyextra->das_arrow_depth --; }
    break;

  case 831: /* type_declaration_no_options_no_dim: "array" '<' $@65 type_declaration '>' $@66  */
                                                                                                                            {
        (yyval.pTypeDecl) = new TypeDecl(Type::tArray);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 832: /* $@67: %empty  */
                           { yyextra->das_arrow_depth ++; }
    break;

  case 833: /* $@68: %empty  */
                                                                                     { yyextra->das_arrow_depth --; }
    break;

  case 834: /* type_declaration_no_options_no_dim: "table" '<' $@67 table_type_pair '>' $@68  */
                                                                                                                      {
        (yyval.pTypeDecl) = new TypeDecl(Type::tTable);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].aTypePair).firstType;
        (yyval.pTypeDecl)->secondType = (yyvsp[-2].aTypePair).secondType;
    }
    break;

  case 835: /* $@69: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 836: /* $@70: %empty  */
                                                                                                 { yyextra->das_arrow_depth --; }
    break;

  case 837: /* type_declaration_no_options_no_dim: "iterator" '<' $@69 type_declaration '>' $@70  */
                                                                                                                                  {
        (yyval.pTypeDecl) = new TypeDecl(Type::tIterator);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 838: /* type_declaration_no_options_no_dim: "block"  */
                        {
        (yyval.pTypeDecl) = new TypeDecl(Type::tBlock);
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::tVoid);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 839: /* $@71: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 840: /* $@72: %empty  */
                                                                                              { yyextra->das_arrow_depth --; }
    break;

  case 841: /* type_declaration_no_options_no_dim: "block" '<' $@71 type_declaration '>' $@72  */
                                                                                                                               {
        (yyval.pTypeDecl) = new TypeDecl(Type::tBlock);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 842: /* $@73: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 843: /* $@74: %empty  */
                                                                                                                                       { yyextra->das_arrow_depth --; }
    break;

  case 844: /* type_declaration_no_options_no_dim: "block" '<' $@73 optional_function_argument_list optional_function_type '>' $@74  */
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

  case 845: /* type_declaration_no_options_no_dim: "function"  */
                           {
        (yyval.pTypeDecl) = new TypeDecl(Type::tFunction);
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::tVoid);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 846: /* $@75: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 847: /* $@76: %empty  */
                                                                                                { yyextra->das_arrow_depth --; }
    break;

  case 848: /* type_declaration_no_options_no_dim: "function" '<' $@75 type_declaration '>' $@76  */
                                                                                                                                 {
        (yyval.pTypeDecl) = new TypeDecl(Type::tFunction);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 849: /* $@77: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 850: /* $@78: %empty  */
                                                                                                                                         { yyextra->das_arrow_depth --; }
    break;

  case 851: /* type_declaration_no_options_no_dim: "function" '<' $@77 optional_function_argument_list optional_function_type '>' $@78  */
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

  case 852: /* type_declaration_no_options_no_dim: "lambda"  */
                         {
        (yyval.pTypeDecl) = new TypeDecl(Type::tLambda);
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::tVoid);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 853: /* $@79: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 854: /* $@80: %empty  */
                                                                                              { yyextra->das_arrow_depth --; }
    break;

  case 855: /* type_declaration_no_options_no_dim: "lambda" '<' $@79 type_declaration '>' $@80  */
                                                                                                                               {
        (yyval.pTypeDecl) = new TypeDecl(Type::tLambda);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 856: /* $@81: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 857: /* $@82: %empty  */
                                                                                                                                       { yyextra->das_arrow_depth --; }
    break;

  case 858: /* type_declaration_no_options_no_dim: "lambda" '<' $@81 optional_function_argument_list optional_function_type '>' $@82  */
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

  case 859: /* $@83: %empty  */
                            { yyextra->das_arrow_depth ++; }
    break;

  case 860: /* $@84: %empty  */
                                                                                       { yyextra->das_arrow_depth --; }
    break;

  case 861: /* type_declaration_no_options_no_dim: "tuple" '<' $@83 tuple_type_list '>' $@84  */
                                                                                                                        {
        (yyval.pTypeDecl) = new TypeDecl(Type::tTuple);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        varDeclToTypeDecl(scanner, (yyval.pTypeDecl), (yyvsp[-2].pVarDeclList), true);
        deleteVariableDeclarationList((yyvsp[-2].pVarDeclList));
    }
    break;

  case 862: /* $@85: %empty  */
                              { yyextra->das_arrow_depth ++; }
    break;

  case 863: /* $@86: %empty  */
                                                                                           { yyextra->das_arrow_depth --; }
    break;

  case 864: /* type_declaration_no_options_no_dim: "variant" '<' $@85 variant_type_list '>' $@86  */
                                                                                                                            {
        (yyval.pTypeDecl) = new TypeDecl(Type::tVariant);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        varDeclToTypeDecl(scanner, (yyval.pTypeDecl), (yyvsp[-2].pVarDeclList), true);
        deleteVariableDeclarationList((yyvsp[-2].pVarDeclList));
    }
    break;

  case 865: /* type_declaration: type_declaration_no_options  */
                                        {
        (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl);
    }
    break;

  case 866: /* type_declaration: type_declaration '|' type_declaration_no_options  */
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

  case 867: /* type_declaration: type_declaration '|' '#'  */
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

  case 868: /* $@87: %empty  */
                   {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 869: /* $@88: %empty  */
                                                                             {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeTuple(atvname);
        }
    }
    break;

  case 870: /* $@89: %empty  */
          {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeTupleEntries(atvname);
        }
    }
    break;

  case 871: /* $@90: %empty  */
                                                 {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-6]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterTupleEntries(atvname);
        }
        yyextra->pop_nesteds();
    }
    break;

  case 872: /* tuple_alias_declaration: "tuple" $@87 optional_public_or_private_alias "name" optional_emit_semis $@88 '{' $@89 tuple_alias_type_list optional_semis $@90 '}'  */
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

  case 873: /* $@91: %empty  */
                     {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 874: /* $@92: %empty  */
                                                                             {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeVariant(atvname);
        }
    }
    break;

  case 875: /* $@93: %empty  */
          {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeVariantEntries(atvname);
        }

    }
    break;

  case 876: /* $@94: %empty  */
                                                   {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-6]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterVariantEntries(atvname);
        }
        yyextra->pop_nesteds();
    }
    break;

  case 877: /* variant_alias_declaration: "variant" $@91 optional_public_or_private_alias "name" optional_emit_semis $@92 '{' $@93 variant_alias_type_list optional_semis $@94 '}'  */
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

  case 878: /* $@95: %empty  */
                      {
        yyextra->push_nesteds(DAS_EMIT_COMMA);
    }
    break;

  case 879: /* $@96: %empty  */
                                                                                                                         {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-2]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeBitfield(atvname);
        }
    }
    break;

  case 880: /* $@97: %empty  */
          {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-4]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeBitfieldEntries(atvname);
        }
    }
    break;

  case 881: /* $@98: %empty  */
                                                {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-7]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterBitfieldEntries(atvname);
        }
        yyextra->pop_nesteds();
    }
    break;

  case 882: /* bitfield_alias_declaration: "bitfield" $@95 optional_public_or_private_alias "name" bitfield_basic_type_declaration optional_emit_commas $@96 '{' $@97 bitfield_alias_bits optional_commas $@98 '}'  */
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

  case 883: /* make_decl: make_struct_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 884: /* make_decl: make_dim_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 885: /* make_decl: make_table_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 886: /* make_decl: make_table_call  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 887: /* make_decl: array_comprehension  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 888: /* make_decl: table_comprehension  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 889: /* make_decl: make_tuple_call  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 890: /* make_decl_no_bracket: make_struct_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 891: /* make_decl_no_bracket: make_dim_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 892: /* make_decl_no_bracket: make_tuple_call  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 893: /* make_decl_no_bracket: table_comprehension  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 894: /* make_decl_no_bracket: make_table_call  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 895: /* make_struct_fields: "name" copy_or_move expr  */
                                               {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-2])),*(yyvsp[-2].s),(yyvsp[0].pExpression),(yyvsp[-1].b),false);
        delete (yyvsp[-2].s);
        auto msd = new MakeStruct();
        msd->push_back(mfd);
        (yyval.pMakeStruct) = msd;
    }
    break;

  case 896: /* make_struct_fields: "name" ":=" expr  */
                                      {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-2])),*(yyvsp[-2].s),(yyvsp[0].pExpression),false,true);
        delete (yyvsp[-2].s);
        auto msd = new MakeStruct();
        msd->push_back(mfd);
        (yyval.pMakeStruct) = msd;
    }
    break;

  case 897: /* make_struct_fields: make_struct_fields ',' "name" copy_or_move expr  */
                                                                           {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-2])),*(yyvsp[-2].s),(yyvsp[0].pExpression),(yyvsp[-1].b),false);
        delete (yyvsp[-2].s);
        ((MakeStruct *)(yyvsp[-4].pMakeStruct))->push_back(mfd);
        (yyval.pMakeStruct) = (yyvsp[-4].pMakeStruct);
    }
    break;

  case 898: /* make_struct_fields: make_struct_fields ',' "name" ":=" expr  */
                                                                  {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-2])),*(yyvsp[-2].s),(yyvsp[0].pExpression),false,true);
        delete (yyvsp[-2].s);
        ((MakeStruct *)(yyvsp[-4].pMakeStruct))->push_back(mfd);
        (yyval.pMakeStruct) = (yyvsp[-4].pMakeStruct);
    }
    break;

  case 899: /* make_struct_fields: "$f" '(' expr ')' copy_or_move expr  */
                                                                   {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-3])),"``MACRO``TAG``FIELD``",(yyvsp[0].pExpression),(yyvsp[-1].b),false);
        mfd->tag = (yyvsp[-3].pExpression);
        auto msd = new MakeStruct();
        msd->push_back(mfd);
        (yyval.pMakeStruct) = msd;
    }
    break;

  case 900: /* make_struct_fields: "$f" '(' expr ')' ":=" expr  */
                                                          {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-3])),"``MACRO``TAG``FIELD``",(yyvsp[0].pExpression),false,true);
        mfd->tag = (yyvsp[-3].pExpression);
        auto msd = new MakeStruct();
        msd->push_back(mfd);
        (yyval.pMakeStruct) = msd;
    }
    break;

  case 901: /* make_struct_fields: make_struct_fields ',' "$f" '(' expr ')' copy_or_move expr  */
                                                                                               {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-3])),"``MACRO``TAG``FIELD``",(yyvsp[0].pExpression),(yyvsp[-1].b),false);
        mfd->tag = (yyvsp[-3].pExpression);
        ((MakeStruct *)(yyvsp[-7].pMakeStruct))->push_back(mfd);
        (yyval.pMakeStruct) = (yyvsp[-7].pMakeStruct);
    }
    break;

  case 902: /* make_struct_fields: make_struct_fields ',' "$f" '(' expr ')' ":=" expr  */
                                                                                      {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-3])),"``MACRO``TAG``FIELD``",(yyvsp[0].pExpression),false,true);
        mfd->tag = (yyvsp[-3].pExpression);
        ((MakeStruct *)(yyvsp[-7].pMakeStruct))->push_back(mfd);
        (yyval.pMakeStruct) = (yyvsp[-7].pMakeStruct);
    }
    break;

  case 903: /* make_variant_dim: %empty  */
       {
        (yyval.pExpression) = ast_makeStructToMakeVariant(nullptr, LineInfo());
    }
    break;

  case 904: /* make_variant_dim: make_struct_fields  */
                              {
        (yyval.pExpression) = ast_makeStructToMakeVariant((yyvsp[0].pMakeStruct), tokAt(scanner,(yylsp[0])));
    }
    break;

  case 905: /* make_struct_single: make_struct_fields optional_comma  */
                                               {
        auto msd = new ExprMakeStruct();
        msd->structs.push_back(MakeStructPtr((yyvsp[-1].pMakeStruct)));
        (yyval.pExpression) = msd;
    }
    break;

  case 906: /* make_struct_dim_list: '(' make_struct_fields ')'  */
                                        {
        auto msd = new ExprMakeStruct();
        msd->structs.push_back(MakeStructPtr((yyvsp[-1].pMakeStruct)));
        (yyval.pExpression) = msd;
    }
    break;

  case 907: /* make_struct_dim_list: make_struct_dim_list ',' '(' make_struct_fields ')'  */
                                                                     {
        ((ExprMakeStruct *) (yyvsp[-4].pExpression))->structs.push_back(MakeStructPtr((yyvsp[-1].pMakeStruct)));
        (yyval.pExpression) = (yyvsp[-4].pExpression);
    }
    break;

  case 908: /* make_struct_dim_decl: make_struct_fields  */
                                {
        auto msd = new ExprMakeStruct();
        msd->structs.push_back(MakeStructPtr((yyvsp[0].pMakeStruct)));
        (yyval.pExpression) = msd;
    }
    break;

  case 909: /* make_struct_dim_decl: make_struct_dim_list optional_comma  */
                                                 {
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 910: /* optional_make_struct_dim_decl: make_struct_dim_decl  */
                                  { (yyval.pExpression) = (yyvsp[0].pExpression);  }
    break;

  case 911: /* optional_make_struct_dim_decl: %empty  */
        {   (yyval.pExpression) = new ExprMakeStruct(); }
    break;

  case 912: /* use_initializer: %empty  */
                            { (yyval.b) = true; }
    break;

  case 913: /* use_initializer: "uninitialized"  */
                            { (yyval.b) = false; }
    break;

  case 914: /* $@99: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 915: /* $@100: %empty  */
                                                                                                   { yyextra->das_arrow_depth --; }
    break;

  case 916: /* make_struct_decl: "struct" '<' $@99 type_declaration_no_options '>' $@100 '(' use_initializer optional_make_struct_dim_decl ')'  */
                                                                                                                                                                                                      {
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-9]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-6].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = (yyvsp[-2].b);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->forceStruct = true;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 917: /* $@101: %empty  */
                            { yyextra->das_arrow_depth ++; }
    break;

  case 918: /* $@102: %empty  */
                                                                                                  { yyextra->das_arrow_depth --; }
    break;

  case 919: /* make_struct_decl: "class" '<' $@101 type_declaration_no_options '>' $@102 '(' use_initializer optional_make_struct_dim_decl ')'  */
                                                                                                                                                                                                     {
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-9]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-6].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = (yyvsp[-2].b);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->forceClass = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 920: /* $@103: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 921: /* $@104: %empty  */
                                                                                            { yyextra->das_arrow_depth --; }
    break;

  case 922: /* make_struct_decl: "variant" '<' $@103 variant_type_list '>' $@104 '(' use_initializer make_variant_dim ')'  */
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

  case 923: /* $@105: %empty  */
                                        { yyextra->das_arrow_depth ++; }
    break;

  case 924: /* $@106: %empty  */
                                                                                                              { yyextra->das_arrow_depth --; }
    break;

  case 925: /* make_struct_decl: "variant" "type" '<' $@105 type_declaration_no_options '>' $@106 '(' use_initializer make_variant_dim ')'  */
                                                                                                                                                                                                    {
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-10]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-6].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = (yyvsp[-2].b);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->forceVariant = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 926: /* $@107: %empty  */
                              { yyextra->das_arrow_depth ++; }
    break;

  case 927: /* $@108: %empty  */
                                                                                                    { yyextra->das_arrow_depth --; }
    break;

  case 928: /* make_struct_decl: "default" '<' $@107 type_declaration_no_options '>' $@108 use_initializer  */
                                                                                                                                                           {
        auto msd = new ExprMakeStruct();
        msd->at = tokAt(scanner,(yylsp[-6]));
        msd->makeType = (yyvsp[-3].pTypeDecl);
        msd->useInitializer = (yyvsp[0].b);
        msd->alwaysUseInitializer = true;
        (yyval.pExpression) = msd;
    }
    break;

  case 929: /* make_tuple_call: "tuple" '(' expr_list optional_comma ')'  */
                                                                    {
        auto mkt = new ExprMakeTuple(tokAt(scanner,(yylsp[-4])));
        mkt->values = sequenceToList((yyvsp[-2].pExpression));
        mkt->makeType = new TypeDecl(Type::autoinfer);
        (yyval.pExpression) = mkt;
    }
    break;

  case 930: /* $@109: %empty  */
                             { yyextra->das_force_oxford_comma=true; yyextra->das_arrow_depth ++; }
    break;

  case 931: /* $@110: %empty  */
                                                                                                                              { yyextra->das_arrow_depth --; }
    break;

  case 932: /* make_tuple_call: "tuple" '<' $@109 tuple_type_list '>' $@110 '(' use_initializer optional_make_struct_dim_decl ')'  */
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

  case 933: /* make_dim_decl: '[' optional_expr_list ']'  */
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

  case 934: /* $@111: %empty  */
                                       { yyextra->das_arrow_depth ++; }
    break;

  case 935: /* $@112: %empty  */
                                                                                                             { yyextra->das_arrow_depth --; }
    break;

  case 936: /* make_dim_decl: "array" "struct" '<' $@111 type_declaration_no_options '>' $@112 '(' use_initializer optional_make_struct_dim_decl ')'  */
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

  case 937: /* $@113: %empty  */
                                       { yyextra->das_arrow_depth ++; }
    break;

  case 938: /* $@114: %empty  */
                                                                                                  { yyextra->das_arrow_depth --; }
    break;

  case 939: /* make_dim_decl: "array" "tuple" '<' $@113 tuple_type_list '>' $@114 '(' use_initializer optional_make_struct_dim_decl ')'  */
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

  case 940: /* $@115: %empty  */
                                         { yyextra->das_arrow_depth ++; }
    break;

  case 941: /* $@116: %empty  */
                                                                                                      { yyextra->das_arrow_depth --; }
    break;

  case 942: /* make_dim_decl: "array" "variant" '<' $@115 variant_type_list '>' $@116 '(' make_variant_dim ')'  */
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

  case 943: /* make_dim_decl: "array" '(' expr_list optional_comma ')'  */
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

  case 944: /* $@117: %empty  */
                           { yyextra->das_arrow_depth ++; }
    break;

  case 945: /* $@118: %empty  */
                                                                                                 { yyextra->das_arrow_depth --; }
    break;

  case 946: /* make_dim_decl: "array" '<' $@117 type_declaration_no_options '>' $@118 '(' optional_expr_list ')'  */
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

  case 947: /* make_dim_decl: "fixed_array" '(' expr_list optional_comma ')'  */
                                                                         {
        auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-4])));
        mka->values = sequenceToList((yyvsp[-2].pExpression));
        mka->makeType = new TypeDecl(Type::autoinfer);
        mka->gen2 = true;
        (yyval.pExpression) = mka;
    }
    break;

  case 948: /* $@119: %empty  */
                                 { yyextra->das_arrow_depth ++; }
    break;

  case 949: /* $@120: %empty  */
                                                                                                       { yyextra->das_arrow_depth --; }
    break;

  case 950: /* make_dim_decl: "fixed_array" '<' $@119 type_declaration_no_options '>' $@120 '(' expr_list optional_comma ')'  */
                                                                                                                                                                                    {
        auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-9])));
        mka->values = sequenceToList((yyvsp[-2].pExpression));
        mka->makeType = (yyvsp[-6].pTypeDecl);
        mka->gen2 = true;
        (yyval.pExpression) = mka;
    }
    break;

  case 951: /* expr_map_tuple_list: expr  */
                      {
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 952: /* expr_map_tuple_list: expr_map_tuple_list ',' expr  */
                                                      {
            (yyval.pExpression) = new ExprSequence(tokAt(scanner,(yylsp[-2])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
    }
    break;

  case 953: /* push_table_nesting: %empty  */
                    {
        yyextra->das_nested_parentheses ++;
    }
    break;

  case 954: /* make_table_decl: '{' push_table_nesting optional_emit_semis optional_expr_map_tuple_list '}'  */
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

  case 955: /* make_table_call: "table" '(' expr_map_tuple_list optional_comma ')'  */
                                                                             {
        auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-4])));
        mka->values = sequenceToList((yyvsp[-2].pExpression));
        mka->makeType = new TypeDecl(Type::autoinfer);
        auto ttm = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-4])),"to_table_move");
        ttm->arguments.push_back(mka);
        (yyval.pExpression) = ttm;
    }
    break;

  case 956: /* make_table_call: "table" '<' type_declaration_no_options '>' '(' optional_expr_map_tuple_list ')'  */
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

  case 957: /* make_table_call: "table" '<' type_declaration_no_options c_or_s type_declaration_no_options '>' '(' optional_expr_map_tuple_list ')'  */
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

  case 958: /* array_comprehension_where: %empty  */
                                    { (yyval.pExpression) = nullptr; }
    break;

  case 959: /* array_comprehension_where: ';' "where" expr  */
                                    { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 960: /* optional_comma: %empty  */
                { (yyval.b) = false; }
    break;

  case 961: /* optional_comma: ','  */
                { (yyval.b) = true; }
    break;

  case 962: /* table_comprehension: '[' "for" '(' for_variable_name_with_pos_list "in" expr_list ')' ';' expr array_comprehension_where ']'  */
                                                                                                                                                               {
        (yyval.pExpression) = ast_arrayComprehension(scanner,tokAt(scanner,(yylsp[-9])),(yyvsp[-7].pNameWithPosList),(yyvsp[-5].pExpression),(yyvsp[-2].pExpression),(yyvsp[-1].pExpression),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),false,false);
    }
    break;

  case 963: /* table_comprehension: '[' "iterator" "for" '(' for_variable_name_with_pos_list "in" expr_list ')' ';' expr array_comprehension_where ']'  */
                                                                                                                                                                            {
        (yyval.pExpression) = ast_arrayComprehension(scanner,tokAt(scanner,(yylsp[-9])),(yyvsp[-7].pNameWithPosList),(yyvsp[-5].pExpression),(yyvsp[-2].pExpression),(yyvsp[-1].pExpression),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),true,false);
    }
    break;

  case 964: /* array_comprehension: '{' push_table_nesting optional_emit_semis "for" '(' for_variable_name_with_pos_list "in" expr_list ')' ';' expr array_comprehension_where '}'  */
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


