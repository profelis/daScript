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
  YYSYMBOL_DAS_DISTINCT = 41,              /* "distinct"  */
  YYSYMBOL_DAS_TYPEDECL = 42,              /* "typedecl"  */
  YYSYMBOL_DAS_WITH = 43,                  /* "with"  */
  YYSYMBOL_DAS_AKA = 44,                   /* "aka"  */
  YYSYMBOL_DAS_ASSUME = 45,                /* "assume"  */
  YYSYMBOL_DAS_CAST = 46,                  /* "cast"  */
  YYSYMBOL_DAS_OVERRIDE = 47,              /* "override"  */
  YYSYMBOL_DAS_ABSTRACT = 48,              /* "abstract"  */
  YYSYMBOL_DAS_UPCAST = 49,                /* "upcast"  */
  YYSYMBOL_DAS_ITERATOR = 50,              /* "iterator"  */
  YYSYMBOL_DAS_VAR = 51,                   /* "var"  */
  YYSYMBOL_DAS_ADDR = 52,                  /* "addr"  */
  YYSYMBOL_DAS_CONTINUE = 53,              /* "continue"  */
  YYSYMBOL_DAS_WHERE = 54,                 /* "where"  */
  YYSYMBOL_DAS_PASS = 55,                  /* "pass"  */
  YYSYMBOL_DAS_REINTERPRET = 56,           /* "reinterpret"  */
  YYSYMBOL_DAS_MODULE = 57,                /* "module"  */
  YYSYMBOL_DAS_PUBLIC = 58,                /* "public"  */
  YYSYMBOL_DAS_LABEL = 59,                 /* "label"  */
  YYSYMBOL_DAS_GOTO = 60,                  /* "goto"  */
  YYSYMBOL_DAS_IMPLICIT = 61,              /* "implicit"  */
  YYSYMBOL_DAS_EXPLICIT = 62,              /* "explicit"  */
  YYSYMBOL_DAS_SHARED = 63,                /* "shared"  */
  YYSYMBOL_DAS_PRIVATE = 64,               /* "private"  */
  YYSYMBOL_DAS_SMART_PTR = 65,             /* "smart_ptr"  */
  YYSYMBOL_DAS_UNSAFE = 66,                /* "unsafe"  */
  YYSYMBOL_DAS_INSCOPE = 67,               /* "inscope"  */
  YYSYMBOL_DAS_STATIC = 68,                /* "static"  */
  YYSYMBOL_DAS_FIXED_ARRAY = 69,           /* "fixed_array"  */
  YYSYMBOL_DAS_DEFAULT = 70,               /* "default"  */
  YYSYMBOL_DAS_UNINITIALIZED = 71,         /* "uninitialized"  */
  YYSYMBOL_DAS_TBOOL = 72,                 /* "bool"  */
  YYSYMBOL_DAS_TVOID = 73,                 /* "void"  */
  YYSYMBOL_DAS_TSTRING = 74,               /* "string"  */
  YYSYMBOL_DAS_TAUTO = 75,                 /* "auto"  */
  YYSYMBOL_DAS_TINT = 76,                  /* "int"  */
  YYSYMBOL_DAS_TINT2 = 77,                 /* "int2"  */
  YYSYMBOL_DAS_TINT3 = 78,                 /* "int3"  */
  YYSYMBOL_DAS_TINT4 = 79,                 /* "int4"  */
  YYSYMBOL_DAS_TUINT = 80,                 /* "uint"  */
  YYSYMBOL_DAS_TBITFIELD = 81,             /* "bitfield"  */
  YYSYMBOL_DAS_TUINT2 = 82,                /* "uint2"  */
  YYSYMBOL_DAS_TUINT3 = 83,                /* "uint3"  */
  YYSYMBOL_DAS_TUINT4 = 84,                /* "uint4"  */
  YYSYMBOL_DAS_TFLOAT = 85,                /* "float"  */
  YYSYMBOL_DAS_TFLOAT2 = 86,               /* "float2"  */
  YYSYMBOL_DAS_TFLOAT3 = 87,               /* "float3"  */
  YYSYMBOL_DAS_TFLOAT4 = 88,               /* "float4"  */
  YYSYMBOL_DAS_TRANGE = 89,                /* "range"  */
  YYSYMBOL_DAS_TURANGE = 90,               /* "urange"  */
  YYSYMBOL_DAS_TRANGE64 = 91,              /* "range64"  */
  YYSYMBOL_DAS_TURANGE64 = 92,             /* "urange64"  */
  YYSYMBOL_DAS_TBLOCK = 93,                /* "block"  */
  YYSYMBOL_DAS_TINT64 = 94,                /* "int64"  */
  YYSYMBOL_DAS_TUINT64 = 95,               /* "uint64"  */
  YYSYMBOL_DAS_TDOUBLE = 96,               /* "double"  */
  YYSYMBOL_DAS_TFUNCTION = 97,             /* "function"  */
  YYSYMBOL_DAS_TLAMBDA = 98,               /* "lambda"  */
  YYSYMBOL_DAS_TINT8 = 99,                 /* "int8"  */
  YYSYMBOL_DAS_TUINT8 = 100,               /* "uint8"  */
  YYSYMBOL_DAS_TINT16 = 101,               /* "int16"  */
  YYSYMBOL_DAS_TUINT16 = 102,              /* "uint16"  */
  YYSYMBOL_DAS_TTUPLE = 103,               /* "tuple"  */
  YYSYMBOL_DAS_TVARIANT = 104,             /* "variant"  */
  YYSYMBOL_DAS_GENERATOR = 105,            /* "generator"  */
  YYSYMBOL_DAS_YIELD = 106,                /* "yield"  */
  YYSYMBOL_DAS_SEALED = 107,               /* "sealed"  */
  YYSYMBOL_DAS_TEMPLATE = 108,             /* "template"  */
  YYSYMBOL_ADDEQU = 109,                   /* "+="  */
  YYSYMBOL_SUBEQU = 110,                   /* "-="  */
  YYSYMBOL_DIVEQU = 111,                   /* "/="  */
  YYSYMBOL_MULEQU = 112,                   /* "*="  */
  YYSYMBOL_MODEQU = 113,                   /* "%="  */
  YYSYMBOL_ANDEQU = 114,                   /* "&="  */
  YYSYMBOL_OREQU = 115,                    /* "|="  */
  YYSYMBOL_XOREQU = 116,                   /* "^="  */
  YYSYMBOL_SHL = 117,                      /* "<<"  */
  YYSYMBOL_SHR = 118,                      /* ">>"  */
  YYSYMBOL_ADDADD = 119,                   /* "++"  */
  YYSYMBOL_SUBSUB = 120,                   /* "--"  */
  YYSYMBOL_LEEQU = 121,                    /* "<="  */
  YYSYMBOL_SHLEQU = 122,                   /* "<<="  */
  YYSYMBOL_SHREQU = 123,                   /* ">>="  */
  YYSYMBOL_GREQU = 124,                    /* ">="  */
  YYSYMBOL_EQUEQU = 125,                   /* "=="  */
  YYSYMBOL_NOTEQU = 126,                   /* "!="  */
  YYSYMBOL_RARROW = 127,                   /* "->"  */
  YYSYMBOL_LARROW = 128,                   /* "<-"  */
  YYSYMBOL_QQ = 129,                       /* "??"  */
  YYSYMBOL_QDOT = 130,                     /* "?."  */
  YYSYMBOL_QBRA = 131,                     /* "?["  */
  YYSYMBOL_LPIPE = 132,                    /* "<|"  */
  YYSYMBOL_RPIPE = 133,                    /* "|>"  */
  YYSYMBOL_CLONEEQU = 134,                 /* ":="  */
  YYSYMBOL_ROTL = 135,                     /* "<<<"  */
  YYSYMBOL_ROTR = 136,                     /* ">>>"  */
  YYSYMBOL_ROTLEQU = 137,                  /* "<<<="  */
  YYSYMBOL_ROTREQU = 138,                  /* ">>>="  */
  YYSYMBOL_MAPTO = 139,                    /* "=>"  */
  YYSYMBOL_DOUBLE_AT = 140,                /* "@@"  */
  YYSYMBOL_AT_FIELD = 141,                 /* "@field"  */
  YYSYMBOL_COLCOL = 142,                   /* "::"  */
  YYSYMBOL_ANDAND = 143,                   /* "&&"  */
  YYSYMBOL_OROR = 144,                     /* "||"  */
  YYSYMBOL_XORXOR = 145,                   /* "^^"  */
  YYSYMBOL_ANDANDEQU = 146,                /* "&&="  */
  YYSYMBOL_OROREQU = 147,                  /* "||="  */
  YYSYMBOL_XORXOREQU = 148,                /* "^^="  */
  YYSYMBOL_DOTDOT = 149,                   /* ".."  */
  YYSYMBOL_MTAG_E = 150,                   /* "$$"  */
  YYSYMBOL_MTAG_I = 151,                   /* "$i"  */
  YYSYMBOL_MTAG_V = 152,                   /* "$v"  */
  YYSYMBOL_MTAG_B = 153,                   /* "$b"  */
  YYSYMBOL_MTAG_A = 154,                   /* "$a"  */
  YYSYMBOL_MTAG_T = 155,                   /* "$t"  */
  YYSYMBOL_MTAG_C = 156,                   /* "$c"  */
  YYSYMBOL_MTAG_F = 157,                   /* "$f"  */
  YYSYMBOL_MTAG_DOTDOTDOT = 158,           /* "..."  */
  YYSYMBOL_INTEGER = 159,                  /* "integer constant"  */
  YYSYMBOL_LONG_INTEGER = 160,             /* "long integer constant"  */
  YYSYMBOL_UNSIGNED_INTEGER = 161,         /* "unsigned integer constant"  */
  YYSYMBOL_UNSIGNED_LONG_INTEGER = 162,    /* "unsigned long integer constant"  */
  YYSYMBOL_UNSIGNED_INT8 = 163,            /* "unsigned int8 constant"  */
  YYSYMBOL_DAS_FLOAT = 164,                /* "floating point constant"  */
  YYSYMBOL_DOUBLE = 165,                   /* "double constant"  */
  YYSYMBOL_NAME = 166,                     /* "name"  */
  YYSYMBOL_DAS_EMIT_COMMA = 167,           /* "new line, comma"  */
  YYSYMBOL_DAS_EMIT_SEMICOLON = 168,       /* "new line, semicolon"  */
  YYSYMBOL_BEGIN_STRING = 169,             /* "start of the string"  */
  YYSYMBOL_STRING_CHARACTER = 170,         /* STRING_CHARACTER  */
  YYSYMBOL_STRING_CHARACTER_ESC = 171,     /* STRING_CHARACTER_ESC  */
  YYSYMBOL_END_STRING = 172,               /* "end of the string"  */
  YYSYMBOL_BEGIN_STRING_EXPR = 173,        /* "{"  */
  YYSYMBOL_END_STRING_EXPR = 174,          /* "}"  */
  YYSYMBOL_END_OF_READ = 175,              /* "end of failed eader macro"  */
  YYSYMBOL_176_ = 176,                     /* ','  */
  YYSYMBOL_177_ = 177,                     /* '='  */
  YYSYMBOL_178_ = 178,                     /* '?'  */
  YYSYMBOL_179_ = 179,                     /* ':'  */
  YYSYMBOL_180_ = 180,                     /* '|'  */
  YYSYMBOL_181_ = 181,                     /* '^'  */
  YYSYMBOL_182_ = 182,                     /* '&'  */
  YYSYMBOL_183_ = 183,                     /* '<'  */
  YYSYMBOL_184_ = 184,                     /* '>'  */
  YYSYMBOL_185_ = 185,                     /* '-'  */
  YYSYMBOL_186_ = 186,                     /* '+'  */
  YYSYMBOL_187_ = 187,                     /* '*'  */
  YYSYMBOL_188_ = 188,                     /* '/'  */
  YYSYMBOL_189_ = 189,                     /* '%'  */
  YYSYMBOL_UNARY_MINUS = 190,              /* UNARY_MINUS  */
  YYSYMBOL_UNARY_PLUS = 191,               /* UNARY_PLUS  */
  YYSYMBOL_192_ = 192,                     /* '~'  */
  YYSYMBOL_193_ = 193,                     /* '!'  */
  YYSYMBOL_PRE_INC = 194,                  /* PRE_INC  */
  YYSYMBOL_PRE_DEC = 195,                  /* PRE_DEC  */
  YYSYMBOL_LLPIPE = 196,                   /* LLPIPE  */
  YYSYMBOL_POST_INC = 197,                 /* POST_INC  */
  YYSYMBOL_POST_DEC = 198,                 /* POST_DEC  */
  YYSYMBOL_DEREF = 199,                    /* DEREF  */
  YYSYMBOL_200_ = 200,                     /* '.'  */
  YYSYMBOL_201_ = 201,                     /* '['  */
  YYSYMBOL_202_ = 202,                     /* ']'  */
  YYSYMBOL_203_ = 203,                     /* '('  */
  YYSYMBOL_204_ = 204,                     /* ')'  */
  YYSYMBOL_205_ = 205,                     /* '$'  */
  YYSYMBOL_206_ = 206,                     /* '@'  */
  YYSYMBOL_207_ = 207,                     /* ';'  */
  YYSYMBOL_208_ = 208,                     /* '{'  */
  YYSYMBOL_209_ = 209,                     /* '}'  */
  YYSYMBOL_210_ = 210,                     /* '#'  */
  YYSYMBOL_YYACCEPT = 211,                 /* $accept  */
  YYSYMBOL_program = 212,                  /* program  */
  YYSYMBOL_COMMA = 213,                    /* COMMA  */
  YYSYMBOL_SEMICOLON = 214,                /* SEMICOLON  */
  YYSYMBOL_top_level_reader_macro = 215,   /* top_level_reader_macro  */
  YYSYMBOL_optional_public_or_private_module = 216, /* optional_public_or_private_module  */
  YYSYMBOL_module_name = 217,              /* module_name  */
  YYSYMBOL_optional_not_required = 218,    /* optional_not_required  */
  YYSYMBOL_module_declaration = 219,       /* module_declaration  */
  YYSYMBOL_character_sequence = 220,       /* character_sequence  */
  YYSYMBOL_string_constant = 221,          /* string_constant  */
  YYSYMBOL_format_string = 222,            /* format_string  */
  YYSYMBOL_optional_format_string = 223,   /* optional_format_string  */
  YYSYMBOL_224_1 = 224,                    /* $@1  */
  YYSYMBOL_string_builder_body = 225,      /* string_builder_body  */
  YYSYMBOL_string_builder = 226,           /* string_builder  */
  YYSYMBOL_reader_character_sequence = 227, /* reader_character_sequence  */
  YYSYMBOL_expr_reader = 228,              /* expr_reader  */
  YYSYMBOL_229_2 = 229,                    /* $@2  */
  YYSYMBOL_options_declaration = 230,      /* options_declaration  */
  YYSYMBOL_require_declaration = 231,      /* require_declaration  */
  YYSYMBOL_require_module_name = 232,      /* require_module_name  */
  YYSYMBOL_optional_require_guard = 233,   /* optional_require_guard  */
  YYSYMBOL_require_module = 234,           /* require_module  */
  YYSYMBOL_is_public_module = 235,         /* is_public_module  */
  YYSYMBOL_expect_declaration = 236,       /* expect_declaration  */
  YYSYMBOL_expect_list = 237,              /* expect_list  */
  YYSYMBOL_expect_error = 238,             /* expect_error  */
  YYSYMBOL_expression_label = 239,         /* expression_label  */
  YYSYMBOL_expression_goto = 240,          /* expression_goto  */
  YYSYMBOL_elif_or_static_elif = 241,      /* elif_or_static_elif  */
  YYSYMBOL_emit_semis = 242,               /* emit_semis  */
  YYSYMBOL_optional_emit_semis = 243,      /* optional_emit_semis  */
  YYSYMBOL_expression_else = 244,          /* expression_else  */
  YYSYMBOL_245_3 = 245,                    /* $@3  */
  YYSYMBOL_246_4 = 246,                    /* $@4  */
  YYSYMBOL_if_or_static_if = 247,          /* if_or_static_if  */
  YYSYMBOL_expression_else_one_liner = 248, /* expression_else_one_liner  */
  YYSYMBOL_expression_if_one_liner = 249,  /* expression_if_one_liner  */
  YYSYMBOL_semis = 250,                    /* semis  */
  YYSYMBOL_optional_semis = 251,           /* optional_semis  */
  YYSYMBOL_expression_if_block = 252,      /* expression_if_block  */
  YYSYMBOL_253_5 = 253,                    /* $@5  */
  YYSYMBOL_254_6 = 254,                    /* $@6  */
  YYSYMBOL_255_7 = 255,                    /* $@7  */
  YYSYMBOL_expression_else_block = 256,    /* expression_else_block  */
  YYSYMBOL_257_8 = 257,                    /* $@8  */
  YYSYMBOL_258_9 = 258,                    /* $@9  */
  YYSYMBOL_259_10 = 259,                   /* $@10  */
  YYSYMBOL_expression_if_then_else = 260,  /* expression_if_then_else  */
  YYSYMBOL_261_11 = 261,                   /* $@11  */
  YYSYMBOL_262_12 = 262,                   /* $@12  */
  YYSYMBOL_expression_if_then_else_oneliner = 263, /* expression_if_then_else_oneliner  */
  YYSYMBOL_for_variable_name_with_pos_list = 264, /* for_variable_name_with_pos_list  */
  YYSYMBOL_expression_for_loop = 265,      /* expression_for_loop  */
  YYSYMBOL_266_13 = 266,                   /* $@13  */
  YYSYMBOL_expression_unsafe = 267,        /* expression_unsafe  */
  YYSYMBOL_expression_while_loop = 268,    /* expression_while_loop  */
  YYSYMBOL_269_14 = 269,                   /* $@14  */
  YYSYMBOL_expression_with = 270,          /* expression_with  */
  YYSYMBOL_271_15 = 271,                   /* $@15  */
  YYSYMBOL_expression_with_alias = 272,    /* expression_with_alias  */
  YYSYMBOL_annotation_argument_value = 273, /* annotation_argument_value  */
  YYSYMBOL_annotation_argument_value_list = 274, /* annotation_argument_value_list  */
  YYSYMBOL_annotation_argument_name = 275, /* annotation_argument_name  */
  YYSYMBOL_annotation_argument = 276,      /* annotation_argument  */
  YYSYMBOL_annotation_argument_list = 277, /* annotation_argument_list  */
  YYSYMBOL_metadata_argument_list = 278,   /* metadata_argument_list  */
  YYSYMBOL_optional_for_annotations = 279, /* optional_for_annotations  */
  YYSYMBOL_annotation_declaration_name = 280, /* annotation_declaration_name  */
  YYSYMBOL_annotation_declaration_basic = 281, /* annotation_declaration_basic  */
  YYSYMBOL_annotation_declaration = 282,   /* annotation_declaration  */
  YYSYMBOL_annotation_list = 283,          /* annotation_list  */
  YYSYMBOL_optional_annotation_list = 284, /* optional_annotation_list  */
  YYSYMBOL_optional_annotation_list_with_emit_semis = 285, /* optional_annotation_list_with_emit_semis  */
  YYSYMBOL_optional_function_argument_list = 286, /* optional_function_argument_list  */
  YYSYMBOL_optional_function_type = 287,   /* optional_function_type  */
  YYSYMBOL_function_name = 288,            /* function_name  */
  YYSYMBOL_das_type_name = 289,            /* das_type_name  */
  YYSYMBOL_optional_template = 290,        /* optional_template  */
  YYSYMBOL_global_function_declaration = 291, /* global_function_declaration  */
  YYSYMBOL_optional_public_or_private_function = 292, /* optional_public_or_private_function  */
  YYSYMBOL_function_declaration_header = 293, /* function_declaration_header  */
  YYSYMBOL_function_declaration = 294,     /* function_declaration  */
  YYSYMBOL_295_16 = 295,                   /* $@16  */
  YYSYMBOL_expression_block_finally = 296, /* expression_block_finally  */
  YYSYMBOL_297_17 = 297,                   /* $@17  */
  YYSYMBOL_298_18 = 298,                   /* $@18  */
  YYSYMBOL_expression_block = 299,         /* expression_block  */
  YYSYMBOL_300_19 = 300,                   /* $@19  */
  YYSYMBOL_301_20 = 301,                   /* $@20  */
  YYSYMBOL_expr_call_pipe_no_bracket = 302, /* expr_call_pipe_no_bracket  */
  YYSYMBOL_expression_any = 303,           /* expression_any  */
  YYSYMBOL_304_21 = 304,                   /* $@21  */
  YYSYMBOL_305_22 = 305,                   /* $@22  */
  YYSYMBOL_expressions = 306,              /* expressions  */
  YYSYMBOL_optional_expr_list = 307,       /* optional_expr_list  */
  YYSYMBOL_optional_expr_map_tuple_list = 308, /* optional_expr_map_tuple_list  */
  YYSYMBOL_type_declaration_no_options_list = 309, /* type_declaration_no_options_list  */
  YYSYMBOL_name_in_namespace = 310,        /* name_in_namespace  */
  YYSYMBOL_expression_delete = 311,        /* expression_delete  */
  YYSYMBOL_new_type_declaration = 312,     /* new_type_declaration  */
  YYSYMBOL_313_23 = 313,                   /* $@23  */
  YYSYMBOL_314_24 = 314,                   /* $@24  */
  YYSYMBOL_expr_new = 315,                 /* expr_new  */
  YYSYMBOL_expression_break = 316,         /* expression_break  */
  YYSYMBOL_expression_continue = 317,      /* expression_continue  */
  YYSYMBOL_expression_return = 318,        /* expression_return  */
  YYSYMBOL_expression_yield = 319,         /* expression_yield  */
  YYSYMBOL_expression_try_catch = 320,     /* expression_try_catch  */
  YYSYMBOL_kwd_let_var_or_nothing = 321,   /* kwd_let_var_or_nothing  */
  YYSYMBOL_kwd_let = 322,                  /* kwd_let  */
  YYSYMBOL_optional_in_scope = 323,        /* optional_in_scope  */
  YYSYMBOL_tuple_expansion = 324,          /* tuple_expansion  */
  YYSYMBOL_tuple_expansion_variable_declaration = 325, /* tuple_expansion_variable_declaration  */
  YYSYMBOL_expression_let = 326,           /* expression_let  */
  YYSYMBOL_expr_cast = 327,                /* expr_cast  */
  YYSYMBOL_328_25 = 328,                   /* $@25  */
  YYSYMBOL_329_26 = 329,                   /* $@26  */
  YYSYMBOL_330_27 = 330,                   /* $@27  */
  YYSYMBOL_331_28 = 331,                   /* $@28  */
  YYSYMBOL_332_29 = 332,                   /* $@29  */
  YYSYMBOL_333_30 = 333,                   /* $@30  */
  YYSYMBOL_expr_type_decl = 334,           /* expr_type_decl  */
  YYSYMBOL_335_31 = 335,                   /* $@31  */
  YYSYMBOL_336_32 = 336,                   /* $@32  */
  YYSYMBOL_expr_type_info = 337,           /* expr_type_info  */
  YYSYMBOL_expr_list = 338,                /* expr_list  */
  YYSYMBOL_block_or_simple_block = 339,    /* block_or_simple_block  */
  YYSYMBOL_block_or_lambda = 340,          /* block_or_lambda  */
  YYSYMBOL_capture_entry = 341,            /* capture_entry  */
  YYSYMBOL_capture_list = 342,             /* capture_list  */
  YYSYMBOL_optional_capture_list = 343,    /* optional_capture_list  */
  YYSYMBOL_expr_full_block = 344,          /* expr_full_block  */
  YYSYMBOL_expr_full_block_assumed_piped = 345, /* expr_full_block_assumed_piped  */
  YYSYMBOL_expr_numeric_const = 346,       /* expr_numeric_const  */
  YYSYMBOL_expr_assign_no_bracket = 347,   /* expr_assign_no_bracket  */
  YYSYMBOL_expr_named_call = 348,          /* expr_named_call  */
  YYSYMBOL_expr_method_call_no_bracket = 349, /* expr_method_call_no_bracket  */
  YYSYMBOL_func_addr_name = 350,           /* func_addr_name  */
  YYSYMBOL_func_addr_expr = 351,           /* func_addr_expr  */
  YYSYMBOL_352_33 = 352,                   /* $@33  */
  YYSYMBOL_353_34 = 353,                   /* $@34  */
  YYSYMBOL_354_35 = 354,                   /* $@35  */
  YYSYMBOL_355_36 = 355,                   /* $@36  */
  YYSYMBOL_expr_field_no_bracket = 356,    /* expr_field_no_bracket  */
  YYSYMBOL_357_37 = 357,                   /* $@37  */
  YYSYMBOL_358_38 = 358,                   /* $@38  */
  YYSYMBOL_expr_call = 359,                /* expr_call  */
  YYSYMBOL_expr = 360,                     /* expr  */
  YYSYMBOL_expr_no_bracket = 361,          /* expr_no_bracket  */
  YYSYMBOL_362_39 = 362,                   /* $@39  */
  YYSYMBOL_363_40 = 363,                   /* $@40  */
  YYSYMBOL_364_41 = 364,                   /* $@41  */
  YYSYMBOL_365_42 = 365,                   /* $@42  */
  YYSYMBOL_366_43 = 366,                   /* $@43  */
  YYSYMBOL_367_44 = 367,                   /* $@44  */
  YYSYMBOL_expr_generator = 368,           /* expr_generator  */
  YYSYMBOL_expr_mtag_no_bracket = 369,     /* expr_mtag_no_bracket  */
  YYSYMBOL_optional_field_annotation = 370, /* optional_field_annotation  */
  YYSYMBOL_optional_override = 371,        /* optional_override  */
  YYSYMBOL_optional_constant = 372,        /* optional_constant  */
  YYSYMBOL_optional_public_or_private_member_variable = 373, /* optional_public_or_private_member_variable  */
  YYSYMBOL_optional_static_member_variable = 374, /* optional_static_member_variable  */
  YYSYMBOL_structure_variable_declaration = 375, /* structure_variable_declaration  */
  YYSYMBOL_struct_variable_declaration_list = 376, /* struct_variable_declaration_list  */
  YYSYMBOL_377_45 = 377,                   /* $@45  */
  YYSYMBOL_378_46 = 378,                   /* $@46  */
  YYSYMBOL_379_47 = 379,                   /* $@47  */
  YYSYMBOL_function_argument_declaration_no_type = 380, /* function_argument_declaration_no_type  */
  YYSYMBOL_function_argument_declaration_type = 381, /* function_argument_declaration_type  */
  YYSYMBOL_function_argument_list = 382,   /* function_argument_list  */
  YYSYMBOL_tuple_type = 383,               /* tuple_type  */
  YYSYMBOL_tuple_type_list = 384,          /* tuple_type_list  */
  YYSYMBOL_tuple_alias_type_list = 385,    /* tuple_alias_type_list  */
  YYSYMBOL_variant_type = 386,             /* variant_type  */
  YYSYMBOL_variant_type_list = 387,        /* variant_type_list  */
  YYSYMBOL_variant_alias_type_list = 388,  /* variant_alias_type_list  */
  YYSYMBOL_copy_or_move = 389,             /* copy_or_move  */
  YYSYMBOL_variable_declaration_no_type = 390, /* variable_declaration_no_type  */
  YYSYMBOL_variable_declaration_type = 391, /* variable_declaration_type  */
  YYSYMBOL_variable_declaration = 392,     /* variable_declaration  */
  YYSYMBOL_copy_or_move_or_clone = 393,    /* copy_or_move_or_clone  */
  YYSYMBOL_optional_ref = 394,             /* optional_ref  */
  YYSYMBOL_let_variable_name_with_pos_list = 395, /* let_variable_name_with_pos_list  */
  YYSYMBOL_global_let_variable_name_with_pos_list = 396, /* global_let_variable_name_with_pos_list  */
  YYSYMBOL_variable_declaration_list = 397, /* variable_declaration_list  */
  YYSYMBOL_let_variable_declaration = 398, /* let_variable_declaration  */
  YYSYMBOL_global_let_variable_declaration = 399, /* global_let_variable_declaration  */
  YYSYMBOL_optional_shared = 400,          /* optional_shared  */
  YYSYMBOL_optional_public_or_private_variable = 401, /* optional_public_or_private_variable  */
  YYSYMBOL_global_variable_declaration_list = 402, /* global_variable_declaration_list  */
  YYSYMBOL_403_48 = 403,                   /* $@48  */
  YYSYMBOL_global_let = 404,               /* global_let  */
  YYSYMBOL_405_49 = 405,                   /* $@49  */
  YYSYMBOL_enum_expression = 406,          /* enum_expression  */
  YYSYMBOL_commas = 407,                   /* commas  */
  YYSYMBOL_enum_list = 408,                /* enum_list  */
  YYSYMBOL_optional_public_or_private_alias = 409, /* optional_public_or_private_alias  */
  YYSYMBOL_single_alias = 410,             /* single_alias  */
  YYSYMBOL_411_50 = 411,                   /* $@50  */
  YYSYMBOL_alias_declaration = 412,        /* alias_declaration  */
  YYSYMBOL_distinct_declaration = 413,     /* distinct_declaration  */
  YYSYMBOL_optional_public_or_private_enum = 414, /* optional_public_or_private_enum  */
  YYSYMBOL_enum_name = 415,                /* enum_name  */
  YYSYMBOL_optional_enum_basic_type_declaration = 416, /* optional_enum_basic_type_declaration  */
  YYSYMBOL_optional_commas = 417,          /* optional_commas  */
  YYSYMBOL_emit_commas = 418,              /* emit_commas  */
  YYSYMBOL_optional_emit_commas = 419,     /* optional_emit_commas  */
  YYSYMBOL_enum_declaration = 420,         /* enum_declaration  */
  YYSYMBOL_421_51 = 421,                   /* $@51  */
  YYSYMBOL_422_52 = 422,                   /* $@52  */
  YYSYMBOL_423_53 = 423,                   /* $@53  */
  YYSYMBOL_optional_structure_parent = 424, /* optional_structure_parent  */
  YYSYMBOL_optional_sealed = 425,          /* optional_sealed  */
  YYSYMBOL_structure_name = 426,           /* structure_name  */
  YYSYMBOL_class_or_struct = 427,          /* class_or_struct  */
  YYSYMBOL_optional_public_or_private_structure = 428, /* optional_public_or_private_structure  */
  YYSYMBOL_optional_struct_variable_declaration_list = 429, /* optional_struct_variable_declaration_list  */
  YYSYMBOL_structure_declaration = 430,    /* structure_declaration  */
  YYSYMBOL_431_54 = 431,                   /* $@54  */
  YYSYMBOL_432_55 = 432,                   /* $@55  */
  YYSYMBOL_433_56 = 433,                   /* $@56  */
  YYSYMBOL_variable_name_with_pos_list = 434, /* variable_name_with_pos_list  */
  YYSYMBOL_basic_type_declaration = 435,   /* basic_type_declaration  */
  YYSYMBOL_enum_basic_type_declaration = 436, /* enum_basic_type_declaration  */
  YYSYMBOL_structure_type_declaration = 437, /* structure_type_declaration  */
  YYSYMBOL_auto_type_declaration = 438,    /* auto_type_declaration  */
  YYSYMBOL_bitfield_bits = 439,            /* bitfield_bits  */
  YYSYMBOL_bitfield_alias_bits = 440,      /* bitfield_alias_bits  */
  YYSYMBOL_bitfield_basic_type_declaration = 441, /* bitfield_basic_type_declaration  */
  YYSYMBOL_bitfield_type_declaration = 442, /* bitfield_type_declaration  */
  YYSYMBOL_443_57 = 443,                   /* $@57  */
  YYSYMBOL_444_58 = 444,                   /* $@58  */
  YYSYMBOL_c_or_s = 445,                   /* c_or_s  */
  YYSYMBOL_table_type_pair = 446,          /* table_type_pair  */
  YYSYMBOL_dim_list = 447,                 /* dim_list  */
  YYSYMBOL_type_declaration_no_options = 448, /* type_declaration_no_options  */
  YYSYMBOL_optional_expr_list_in_braces = 449, /* optional_expr_list_in_braces  */
  YYSYMBOL_type_declaration_no_options_no_dim = 450, /* type_declaration_no_options_no_dim  */
  YYSYMBOL_451_59 = 451,                   /* $@59  */
  YYSYMBOL_452_60 = 452,                   /* $@60  */
  YYSYMBOL_453_61 = 453,                   /* $@61  */
  YYSYMBOL_454_62 = 454,                   /* $@62  */
  YYSYMBOL_455_63 = 455,                   /* $@63  */
  YYSYMBOL_456_64 = 456,                   /* $@64  */
  YYSYMBOL_457_65 = 457,                   /* $@65  */
  YYSYMBOL_458_66 = 458,                   /* $@66  */
  YYSYMBOL_459_67 = 459,                   /* $@67  */
  YYSYMBOL_460_68 = 460,                   /* $@68  */
  YYSYMBOL_461_69 = 461,                   /* $@69  */
  YYSYMBOL_462_70 = 462,                   /* $@70  */
  YYSYMBOL_463_71 = 463,                   /* $@71  */
  YYSYMBOL_464_72 = 464,                   /* $@72  */
  YYSYMBOL_465_73 = 465,                   /* $@73  */
  YYSYMBOL_466_74 = 466,                   /* $@74  */
  YYSYMBOL_467_75 = 467,                   /* $@75  */
  YYSYMBOL_468_76 = 468,                   /* $@76  */
  YYSYMBOL_469_77 = 469,                   /* $@77  */
  YYSYMBOL_470_78 = 470,                   /* $@78  */
  YYSYMBOL_471_79 = 471,                   /* $@79  */
  YYSYMBOL_472_80 = 472,                   /* $@80  */
  YYSYMBOL_473_81 = 473,                   /* $@81  */
  YYSYMBOL_474_82 = 474,                   /* $@82  */
  YYSYMBOL_475_83 = 475,                   /* $@83  */
  YYSYMBOL_476_84 = 476,                   /* $@84  */
  YYSYMBOL_477_85 = 477,                   /* $@85  */
  YYSYMBOL_478_86 = 478,                   /* $@86  */
  YYSYMBOL_type_declaration = 479,         /* type_declaration  */
  YYSYMBOL_tuple_alias_declaration = 480,  /* tuple_alias_declaration  */
  YYSYMBOL_481_87 = 481,                   /* $@87  */
  YYSYMBOL_482_88 = 482,                   /* $@88  */
  YYSYMBOL_483_89 = 483,                   /* $@89  */
  YYSYMBOL_484_90 = 484,                   /* $@90  */
  YYSYMBOL_variant_alias_declaration = 485, /* variant_alias_declaration  */
  YYSYMBOL_486_91 = 486,                   /* $@91  */
  YYSYMBOL_487_92 = 487,                   /* $@92  */
  YYSYMBOL_488_93 = 488,                   /* $@93  */
  YYSYMBOL_489_94 = 489,                   /* $@94  */
  YYSYMBOL_bitfield_alias_declaration = 490, /* bitfield_alias_declaration  */
  YYSYMBOL_491_95 = 491,                   /* $@95  */
  YYSYMBOL_492_96 = 492,                   /* $@96  */
  YYSYMBOL_493_97 = 493,                   /* $@97  */
  YYSYMBOL_494_98 = 494,                   /* $@98  */
  YYSYMBOL_make_decl = 495,                /* make_decl  */
  YYSYMBOL_make_decl_no_bracket = 496,     /* make_decl_no_bracket  */
  YYSYMBOL_make_struct_fields = 497,       /* make_struct_fields  */
  YYSYMBOL_make_variant_dim = 498,         /* make_variant_dim  */
  YYSYMBOL_make_struct_single = 499,       /* make_struct_single  */
  YYSYMBOL_make_struct_dim_list = 500,     /* make_struct_dim_list  */
  YYSYMBOL_make_struct_dim_decl = 501,     /* make_struct_dim_decl  */
  YYSYMBOL_optional_make_struct_dim_decl = 502, /* optional_make_struct_dim_decl  */
  YYSYMBOL_use_initializer = 503,          /* use_initializer  */
  YYSYMBOL_make_struct_decl = 504,         /* make_struct_decl  */
  YYSYMBOL_505_99 = 505,                   /* $@99  */
  YYSYMBOL_506_100 = 506,                  /* $@100  */
  YYSYMBOL_507_101 = 507,                  /* $@101  */
  YYSYMBOL_508_102 = 508,                  /* $@102  */
  YYSYMBOL_509_103 = 509,                  /* $@103  */
  YYSYMBOL_510_104 = 510,                  /* $@104  */
  YYSYMBOL_511_105 = 511,                  /* $@105  */
  YYSYMBOL_512_106 = 512,                  /* $@106  */
  YYSYMBOL_513_107 = 513,                  /* $@107  */
  YYSYMBOL_514_108 = 514,                  /* $@108  */
  YYSYMBOL_make_tuple_call = 515,          /* make_tuple_call  */
  YYSYMBOL_516_109 = 516,                  /* $@109  */
  YYSYMBOL_517_110 = 517,                  /* $@110  */
  YYSYMBOL_make_dim_decl = 518,            /* make_dim_decl  */
  YYSYMBOL_519_111 = 519,                  /* $@111  */
  YYSYMBOL_520_112 = 520,                  /* $@112  */
  YYSYMBOL_521_113 = 521,                  /* $@113  */
  YYSYMBOL_522_114 = 522,                  /* $@114  */
  YYSYMBOL_523_115 = 523,                  /* $@115  */
  YYSYMBOL_524_116 = 524,                  /* $@116  */
  YYSYMBOL_525_117 = 525,                  /* $@117  */
  YYSYMBOL_526_118 = 526,                  /* $@118  */
  YYSYMBOL_527_119 = 527,                  /* $@119  */
  YYSYMBOL_528_120 = 528,                  /* $@120  */
  YYSYMBOL_expr_map_tuple_list = 529,      /* expr_map_tuple_list  */
  YYSYMBOL_push_table_nesting = 530,       /* push_table_nesting  */
  YYSYMBOL_make_table_decl = 531,          /* make_table_decl  */
  YYSYMBOL_make_table_call = 532,          /* make_table_call  */
  YYSYMBOL_array_comprehension_where = 533, /* array_comprehension_where  */
  YYSYMBOL_optional_comma = 534,           /* optional_comma  */
  YYSYMBOL_table_comprehension = 535,      /* table_comprehension  */
  YYSYMBOL_array_comprehension = 536       /* array_comprehension  */
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
#define YYLAST   9766

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  211
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  326
/* YYNRULES -- Number of rules.  */
#define YYNRULES  964
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1740

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   438


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
       2,     2,     2,   193,     2,   210,   205,   189,   182,     2,
     203,   204,   187,   186,   176,   185,   200,   188,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   179,   207,
     183,   177,   184,   178,   206,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   201,     2,   202,   181,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   208,   180,   209,   192,     2,     2,     2,
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
     175,   190,   191,   194,   195,   196,   197,   198,   199
};

#if DAS2_YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   571,   571,   572,   577,   578,   579,   580,   581,   582,
     583,   584,   585,   586,   587,   588,   589,   590,   594,   595,
     599,   600,   604,   610,   611,   612,   616,   617,   621,   622,
     626,   645,   646,   647,   648,   652,   653,   657,   658,   662,
     663,   663,   667,   672,   681,   696,   712,   717,   725,   725,
     764,   782,   786,   789,   793,   797,   801,   805,   811,   820,
     821,   825,   828,   834,   835,   839,   843,   844,   848,   851,
     857,   863,   866,   872,   873,   877,   878,   882,   883,   887,
     888,   888,   892,   892,   901,   902,   906,   907,   913,   914,
     915,   916,   917,   921,   922,   926,   927,   931,   933,   931,
     945,   945,   953,   955,   953,   967,   967,   975,   977,   975,
     988,   995,  1002,  1007,  1016,  1024,  1030,  1034,  1042,  1052,
    1052,  1061,  1069,  1069,  1083,  1083,  1095,  1099,  1106,  1107,
    1108,  1109,  1110,  1111,  1115,  1120,  1128,  1129,  1130,  1134,
    1135,  1136,  1137,  1138,  1139,  1140,  1141,  1142,  1148,  1151,
    1157,  1160,  1166,  1169,  1172,  1178,  1179,  1180,  1181,  1185,
    1203,  1226,  1229,  1239,  1254,  1269,  1284,  1287,  1294,  1298,
    1305,  1306,  1310,  1311,  1315,  1316,  1317,  1321,  1324,  1328,
    1335,  1339,  1340,  1341,  1342,  1343,  1344,  1345,  1346,  1347,
    1348,  1349,  1350,  1351,  1352,  1353,  1354,  1355,  1356,  1357,
    1358,  1359,  1360,  1361,  1362,  1363,  1364,  1365,  1366,  1367,
    1368,  1369,  1370,  1371,  1372,  1373,  1374,  1375,  1376,  1377,
    1378,  1379,  1380,  1381,  1382,  1383,  1384,  1385,  1386,  1387,
    1388,  1389,  1390,  1391,  1392,  1393,  1394,  1395,  1396,  1397,
    1398,  1399,  1400,  1401,  1402,  1403,  1404,  1405,  1406,  1407,
    1408,  1409,  1410,  1411,  1412,  1413,  1414,  1415,  1416,  1417,
    1418,  1419,  1420,  1421,  1422,  1423,  1424,  1425,  1426,  1430,
    1431,  1432,  1433,  1434,  1435,  1436,  1437,  1438,  1439,  1440,
    1441,  1442,  1443,  1444,  1445,  1446,  1447,  1448,  1449,  1450,
    1451,  1452,  1453,  1454,  1458,  1459,  1463,  1482,  1483,  1484,
    1488,  1494,  1494,  1511,  1514,  1516,  1514,  1524,  1526,  1524,
    1541,  1559,  1577,  1595,  1606,  1607,  1608,  1609,  1610,  1611,
    1612,  1613,  1614,  1615,  1616,  1617,  1618,  1619,  1620,  1621,
    1622,  1623,  1624,  1625,  1627,  1625,  1642,  1647,  1653,  1659,
    1660,  1664,  1665,  1669,  1673,  1680,  1681,  1692,  1696,  1699,
    1707,  1707,  1707,  1710,  1716,  1719,  1723,  1727,  1734,  1741,
    1747,  1751,  1755,  1758,  1761,  1769,  1772,  1780,  1786,  1787,
    1788,  1792,  1793,  1797,  1798,  1802,  1807,  1815,  1821,  1833,
    1836,  1839,  1849,  1849,  1849,  1852,  1852,  1852,  1857,  1857,
    1857,  1865,  1865,  1865,  1871,  1881,  1892,  1907,  1910,  1913,
    1916,  1922,  1923,  1930,  1941,  1942,  1943,  1947,  1948,  1949,
    1950,  1951,  1955,  1960,  1968,  1969,  1973,  1980,  1984,  1990,
    1991,  1992,  1993,  1994,  1995,  1996,  2000,  2001,  2002,  2003,
    2004,  2005,  2006,  2007,  2008,  2009,  2010,  2011,  2012,  2013,
    2014,  2015,  2016,  2017,  2018,  2019,  2020,  2024,  2030,  2037,
    2049,  2055,  2063,  2071,  2082,  2094,  2098,  2105,  2108,  2108,
    2108,  2113,  2113,  2113,  2126,  2130,  2134,  2140,  2148,  2156,
    2167,  2176,  2182,  2190,  2190,  2190,  2197,  2201,  2210,  2218,
    2226,  2230,  2233,  2241,  2242,  2243,  2250,  2251,  2252,  2253,
    2254,  2255,  2256,  2257,  2258,  2259,  2260,  2261,  2262,  2263,
    2264,  2265,  2266,  2267,  2268,  2269,  2270,  2271,  2272,  2273,
    2274,  2275,  2276,  2277,  2278,  2279,  2280,  2281,  2282,  2283,
    2284,  2285,  2291,  2292,  2293,  2294,  2295,  2310,  2319,  2320,
    2321,  2322,  2323,  2324,  2325,  2326,  2327,  2328,  2329,  2330,
    2331,  2332,  2335,  2335,  2335,  2338,  2343,  2347,  2351,  2351,
    2351,  2356,  2359,  2363,  2363,  2363,  2368,  2371,  2372,  2373,
    2374,  2375,  2376,  2377,  2378,  2379,  2381,  2385,  2386,  2391,
    2397,  2403,  2412,  2415,  2418,  2427,  2428,  2429,  2430,  2431,
    2432,  2433,  2437,  2441,  2445,  2449,  2453,  2457,  2461,  2465,
    2469,  2476,  2477,  2481,  2482,  2483,  2487,  2488,  2492,  2493,
    2494,  2498,  2499,  2503,  2515,  2518,  2519,  2523,  2523,  2542,
    2541,  2556,  2555,  2572,  2584,  2593,  2603,  2604,  2605,  2606,
    2607,  2611,  2614,  2623,  2624,  2628,  2631,  2635,  2648,  2657,
    2658,  2662,  2665,  2669,  2682,  2683,  2687,  2693,  2699,  2708,
    2711,  2718,  2721,  2727,  2728,  2729,  2733,  2734,  2738,  2745,
    2750,  2759,  2765,  2769,  2780,  2787,  2796,  2799,  2802,  2809,
    2812,  2817,  2828,  2831,  2836,  2848,  2849,  2853,  2854,  2855,
    2859,  2862,  2865,  2865,  2885,  2888,  2888,  2906,  2911,  2919,
    2920,  2924,  2927,  2940,  2957,  2958,  2959,  2964,  2964,  2990,
    2994,  3001,  3002,  3003,  3007,  3017,  3020,  3026,  3027,  3031,
    3032,  3036,  3037,  3041,  3043,  3048,  3041,  3064,  3065,  3069,
    3070,  3074,  3080,  3081,  3082,  3083,  3087,  3088,  3089,  3093,
    3096,  3102,  3104,  3109,  3102,  3130,  3137,  3142,  3151,  3157,
    3161,  3172,  3173,  3174,  3175,  3176,  3177,  3178,  3179,  3180,
    3181,  3182,  3183,  3184,  3185,  3186,  3187,  3188,  3189,  3190,
    3191,  3192,  3193,  3194,  3195,  3196,  3197,  3198,  3202,  3203,
    3204,  3205,  3206,  3207,  3208,  3209,  3213,  3224,  3228,  3235,
    3247,  3254,  3260,  3269,  3274,  3284,  3294,  3304,  3317,  3318,
    3319,  3320,  3321,  3325,  3329,  3329,  3329,  3343,  3344,  3348,
    3352,  3359,  3362,  3365,  3368,  3374,  3377,  3391,  3392,  3396,
    3397,  3398,  3399,  3400,  3400,  3400,  3404,  3409,  3416,  3423,
    3423,  3430,  3430,  3437,  3441,  3445,  3450,  3455,  3460,  3465,
    3469,  3473,  3478,  3482,  3486,  3491,  3491,  3491,  3497,  3504,
    3504,  3504,  3509,  3509,  3509,  3515,  3515,  3515,  3520,  3525,
    3525,  3525,  3530,  3530,  3530,  3539,  3544,  3544,  3544,  3549,
    3549,  3549,  3558,  3563,  3563,  3563,  3568,  3568,  3568,  3577,
    3577,  3577,  3583,  3583,  3583,  3592,  3595,  3606,  3622,  3624,
    3629,  3634,  3622,  3660,  3662,  3667,  3673,  3660,  3699,  3701,
    3706,  3711,  3699,  3752,  3753,  3754,  3755,  3756,  3757,  3758,
    3762,  3763,  3764,  3765,  3766,  3770,  3777,  3784,  3790,  3796,
    3803,  3810,  3816,  3825,  3828,  3834,  3842,  3847,  3854,  3859,
    3865,  3866,  3870,  3871,  3875,  3875,  3875,  3883,  3883,  3883,
    3890,  3890,  3890,  3901,  3901,  3901,  3908,  3908,  3908,  3919,
    3925,  3925,  3925,  3939,  3958,  3958,  3958,  3968,  3968,  3968,
    3982,  3982,  3982,  3996,  4005,  4005,  4005,  4025,  4032,  4032,
    4032,  4042,  4045,  4056,  4062,  4085,  4093,  4113,  4138,  4139,
    4143,  4144,  4149,  4152,  4162
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
  "\"typedef\"", "\"distinct\"", "\"typedecl\"", "\"with\"", "\"aka\"",
  "\"assume\"", "\"cast\"", "\"override\"", "\"abstract\"", "\"upcast\"",
  "\"iterator\"", "\"var\"", "\"addr\"", "\"continue\"", "\"where\"",
  "\"pass\"", "\"reinterpret\"", "\"module\"", "\"public\"", "\"label\"",
  "\"goto\"", "\"implicit\"", "\"explicit\"", "\"shared\"", "\"private\"",
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
  "alias_declaration", "distinct_declaration",
  "optional_public_or_private_enum", "enum_name",
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

#define YYPACT_NINF (-1592)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-857)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1592,    71, -1592, -1592,    87,   -57,   -68,   379,   379, -1592,
       7, -1592, -1592, -1592, -1592,   181,   119, -1592, -1592, -1592,
   -1592,    24,    24,    24, -1592,   239, -1592,   115, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,    19,
   -1592,    39,   107,   118, -1592,   335,   335, -1592, -1592, -1592,
     167,    24,   226, -1592, -1592,   115,   379,   379,   379,   274,
     263, -1592, -1592, -1592, -1592,   119,   119,   119,   287, -1592,
     891,  -110, -1592, -1592, -1592, -1592,   339, -1592,   958, -1592,
     489,   213,    87,   333,   -57,   314, -1592,   320,   341,   169,
      46, -1592, -1592,   381,   611,   463,   480,   485, -1592,   490,
     452, -1592, -1592,   152,    87,   119,   119,   119,   119,   413,
   -1592,   807,   825,   577,   580,   834, -1592, -1592,   502, -1592,
   -1592,   511, -1592, -1592, -1592,   867,    99, -1592, -1592, -1592,
   -1592,   335,   335,   521,   335,   536,   591,   601, -1592, -1592,
     593,  2151, -1592, -1592,   582,   609,   413,   413, -1592, -1592,
     633, -1592,   104, -1592,   663,   689,   891, -1592,   648, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592,   671, -1592, -1592, -1592,
   -1592, -1592, -1592,   698, -1592, -1592, -1592, -1592,   870, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592,   187,   521,   521,   521,
   -1592, -1592,   797,  2151,   684,   701,   705,   694,   726,   729,
   -1592, -1592, -1592,   699, -1592, -1592, -1592, -1592, -1592,   610,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592,   735, -1592, -1592, -1592,   740,   749, -1592, -1592, -1592,
   -1592,   752,   772,   766,   181,   -95, -1592, -1592, -1592, -1592,
    1803,   751,   254,   805, -1592,   685,   790, -1592, -1592, -1592,
   -1592, -1592,  9469, -1592,   792,   860,   257,    87,   833,   819,
   -1592, -1592, -1592,    99, -1592, -1592,   811, -1592, -1592, -1592,
    7875, -1592, -1592,   831,   817,   -54,   -47,   -43, -1592, -1592,
    7875,   -85, -1592,  5935, -1592, -1592, -1592,    12, -1592, -1592,
   -1592,    66, -1592,  6129,   824,  1122, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592,   854, -1592,   836,   846,  8795, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592,   991,   997, -1592,   852, -1592,   413,   820,
     790, -1592,   890,   413, -1592, -1592,   698,   413,    87, -1592,
     445, -1592, -1592,  2151,  2151,  2151,   874,   876, -1592, -1592,
     304,   181,   877,    76, -1592,   455,   858,   892,   895,   871,
     896,   878,   509,   900, -1592,   516,    40,   903,  8645,  8645,
     377,   885,   886,   887,   888,   893,   894, -1592, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592,  8645,  8645,  8645,  8645,
    8645,  3995,  4771, -1592, -1592, -1592, -1592, -1592, -1592,   901,
   -1592, -1592, -1592, -1592,   904, -1592, -1592,   -63,   -63, -1592,
     -63,   -63,   883,  8901, -1592, -1592,   906, -1592, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592,  2151,  2151,   889,   910,  2151,
     852,  2151,   852,  2151,   852,  8793,   941,   907, -1592,  5935,
   -1592,  2151,  7875,   908,   934, -1592, -1592, -1592, -1592, -1592,
     911, -1592, -1592,   912,  6323, -1592,  1803, -1592,   913, -1592,
   -1592,  9527,  9566, -1592, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592,   950,   916, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592,  1097, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,
     956,   921, -1592, -1592,   -71,   -48,   985, -1592, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592,   917,   947, -1592,   284,
   -1592,   413,   961,  2151, -1592,   136,   673,   676,   944,   427,
   -1592, -1592, -1592, -1592,   927, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592, -1592,   583, -1592,   949,   951,   952, -1592,
    5935,  2151,  7875,  7875, -1592, -1592,  7875, -1592,  7875, -1592,
    5935, -1592, -1592,  5935,   955, -1592,  2151,  1234,  1234,   930,
     936,   -40, -1592, -1592,  7875,  7875,  7875,  7875,  7875,  7875,
     789,  1234,  1234,   151,  1234,  1234,   943,  1131,   946,   948,
     286,   934,   973,   953,   413,  3607,   119,  1146, -1592, -1592,
     904, -1592, -1592, -1592, -1592, -1592,  8975,  9345,  8645,  8645,
   -1592, -1592,  8645,  8645,  8645,  8645,   986,  8645,   382,  7875,
    8645,  8645,  8645,  8645,  7875,  8645,  8645,  8645,  8645,  8261,
    8645,  8645,  8645,  8645,  8645,  8645,  8645,  8645,  8645,  8645,
    9436,  7875,  4965,   719,   724, -1592, -1592,   988,   727,   -48,
     744,   -48,   745,   -48,    -2, -1592,   350,   811,   976, -1592,
     399, -1592,  2151,   934,   442,   811, -1592, -1592,  6517, -1592,
   -1592, -1592, -1592,   954, -1592,  8793,   941, -1592, -1592, -1592,
   -1592, -1592, -1592,  9600,  1760,  2340,   957, -1592,    58,   959,
     -14,   963,  2151,  2151, -1592,  8453, -1592,   960, -1592, -1592,
     181, -1592,   775,   966,  1114,   669, -1592, -1592, -1592,  1350,
   -1592, -1592, -1592,  7875, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592,  2151,  2151,  2151,  2151,  4189,   995,  7875,  2151, -1592,
   -1592, -1592,  2151,   934,  1371, -1592,   987,   967,  2151,  2151,
     969,  2151,   970,  2151,   934,  2151,  8793,   934, -1592,   941,
     415,  7875,  7875,  2151,   852,   971,   972,   974,   975,   977,
     978, -1592,  7875,   818,    21,   980, -1592,  7875, -1592,  7875,
   -1592,  7875,   981,   552, -1592, -1592,  6711,   179,  3801, -1592,
     334,   982,   178,   990,   852,  2342,  1146,   979,  1024, -1592,
   -1592,   994,  1025, -1592, -1592,  1209,  1209,   267,   267,  9215,
    9215,  1026,   459,  1029, -1592,   968,   -10,   -10,   906,  1209,
    1209,  8979, -1592, -1592,   693,  1512,  9099,  8979,  9376,   884,
    1477,  1658,  9186,   267,   267,  1115,  1115,   459,   459,   459,
     602,  7875,  1030,  1035,   625,  7875,  1187,  1037,   989, -1592,
     361, -1592, -1592, -1592,   183, -1592,  1005, -1592,  1006, -1592,
    1059,  2151, -1592,  8793,  2151, -1592,   941,   477,  1045,  1049,
    2151,  7875, -1592, -1592,  1087, -1592,    24, -1592,    24, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592,  7875, -1592, -1592,
     328,   -41,   -41,   -41, -1592,   811,   811,  8645,  8979, -1592,
    1088, -1592, -1592, -1592, -1592,  7875,  1091,   385,  2151,   136,
   -1592,  7875,    24, -1592, -1592, -1592,   811,   494,   788,   754,
     643,   365,  1054,  1055,   506,  1056,   764,  2151,  8793,   941,
     808,  1058,  1060,  2151,  7875,  1061, -1592,  1259,  1793, -1592,
    1990, -1592,  2092,  1062,  2134,   513,  1063,  2151,   549,  1146,
    1064,  1065,  2225,   -48, -1592, -1592, -1592, -1592, -1592,  1068,
    1094,  1069,  1230,  1113,    28,    21,  1076, -1592, -1592, -1592,
    1078,   143,  1079,  1080,   987,   261, -1592,  1081,   234,  5159,
   -1592, -1592, -1592,   227,   -48, -1592,  6905, -1592, -1592,  7099,
    1121,  1124, -1592,    24,  1135,  7293,    81,  7487, -1592, -1592,
   -1592,    24,    24,  1286, -1592,   984, -1592, -1592,  1284, -1592,
   -1592,  1289, -1592,  1256,    24, -1592,    24,    24,    24,    24,
      24, -1592,  1238, -1592,    24,  1962,   852, -1592,  7875, -1592,
    7875,  4383,  7875, -1592,  1118,  1103, -1592, -1592,  8645,  1104,
   -1592,  1106,  7875,  4577,  1107, -1592,  1110, -1592,  5353, -1592,
    6517, -1592, -1592, -1592,  1147, -1592,  1148, -1592, -1592, -1592,
   -1592, -1592, -1592,   811, -1592, -1592,   811, -1592, -1592,  1049,
   -1592, -1592,   811, -1592,  1140,   666, -1592,  1862, -1592,   251,
   -1592,  1119,  1116,  1274, -1592, -1592,   236, -1592, -1592, -1592,
    9070,  2566,  1145, -1592,   666,    29,  1120, -1592,  1123,  1287,
    1350,  7875,    24, -1592, -1592, -1592, -1592,  1126, -1592, -1592,
   -1592,  1130,  1168, -1592, -1592,  2499,   574,   631, -1592, -1592,
    7875,  2704, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592,  2913, -1592,   123, -1592, -1592, -1592,  1151,  5547,
   -1592,  1163,  7875,  1177, -1592,   366,  5935,   103,    38,   323,
    7875,  7875,  7875,    21, -1592, -1592, -1592,   552,  1141,  3801,
     369,  1178,  1180,  1144,  1182,  1183, -1592,   376,   413,  7875,
   -1592,  1336,  7875, -1592,  1174,  1175, -1592,  1184,  1197, -1592,
   -1592,  7875, -1592, -1592, -1592, -1592,  1154, -1592, -1592,  1159,
     -51,   -51,  1165, -1592, -1592, -1592, -1592, -1592, -1592, -1592,
     275, -1592,  8645,  8645,  8645,  8645,  8645,  8645,  8645,  8645,
    8645,  8645,  7875,  8645,  8645,  8645,  8645,  8645,  8645,  8645,
     -48,  2151,  1166,  2151,  1167,  3801, -1592,   378,   392,  1169,
   -1592,  7875,  9070,  7875, -1592,  1170,  3801, -1592,   409,   411,
    7875, -1592, -1592, -1592,   435, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592,  7875, -1592,   629, -1592, -1592, -1592,  1160, -1592,
    1171, -1592,  7875,  1206,   469,  2151, -1592,  7875,  1172,  7875,
     664, -1592,  1210, -1592, -1592,  1367,   698, -1592,  7875,  1212,
   -1592,  7875,    24, -1592,  1176,  1179, -1592, -1592,  7875,  1202,
   -1592, -1592, -1592, -1592,  1186,  1188,  1190,  1196,  1198,  1199,
    1200,  1316,  1203, -1592,  1204,  7681, -1592,   613, -1592, -1592,
     460, -1592, -1592,  1201, -1592,  1224, -1592,   467,  1211,  1356,
    1113,  5935,  7875,  7875,  1213, -1592, -1592,    56, -1592,   283,
   -1592, -1592, -1592,  1247, -1592, -1592,   227, -1592,   985, -1592,
   -1592, -1592,  2151,  7875, -1592, -1592, -1592, -1592,  2775,  7875,
    7875,    87,   833,  1215,  1216,  7875,  1113, -1592, -1592, -1592,
    8901,  8901,  8901,  8901,  8901,  8901,  8901,  8901,  8901,  8901,
    8901, -1592, -1592,  8901,  8901,  8901,  8901,  8901,  8901,  8901,
     413,  3122, -1592,   769, -1592,   330,  5741, -1592, -1592, -1592,
    2151,  1218,  1219, -1592,   396,  5741, -1592, -1592,  1220, -1592,
   -1592,  1243, -1592,  1217, -1592, -1592,  1221, -1592,  1225,  1385,
     -61, -1592,  1378, -1592, -1592,  1227,  1253,   837,  1370,    24,
    1236, -1592,    24, -1592,  1316,  1316,  1242,  1239,  1244,  1246,
    1249,  5935, -1592,  7875,  7875,  7875,  7875,  5935, -1592, -1592,
    1316,  1250,  1316, -1592,  1251, -1592, -1592,   613, -1592,  1280,
   -1592, -1592,  1252,  7875,  1288,   487,   491, -1592, -1592,   337,
    5935,  1254,  1257, -1592, -1592, -1592,   811, -1592,  1248,  1258,
    1260,   440,    21,  7875,  1262,   518,   153,   985, -1592, -1592,
    1263,   520,   774, -1592, -1592,  1266,   530, -1592,  7875, -1592,
   -1592,  7875,  1290,  7875, -1592, -1592, -1592,  2151, -1592, -1592,
     704, -1592,    50, -1592, -1592, -1592,   347,   347, -1592,  7875,
    1316,  1316,   643,  1269,  1270,  1272,  1273,  1276,   934,   347,
    1316,   643, -1592, -1592, -1592,  7875,  1277, -1592, -1592,  1275,
    7875,  7875,   535, -1592, -1592,  1378,  1448,   413, -1592,    69,
    1279,   413,   544, -1592, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592,  1281, -1592, -1592,  1255,   254,
    1454,    50, -1592, -1592,   837,   643,  1312,  1318, -1592,  1291,
    1293,  1297,   347,   347,  1312,  1298, -1592, -1592, -1592, -1592,
   -1592,  1299,  1300,   643,  1302,  1301, -1592,  7875, -1592, -1592,
    1303, -1592,  8069,    24, -1592,  5935,   413, -1592,  2151,   136,
   -1592, -1592, -1592, -1592, -1592, -1592,  1454,   328,   567,  1304,
   -1592, -1592, -1592, -1592,  1305,  1307, -1592, -1592, -1592,  1308,
   -1592,  1460,  1314,  1301,  7875, -1592, -1592, -1592, -1592, -1592,
    8901, -1592,  1311,   569, -1592, -1592,   802,  7875,  2984,  9469,
   -1592, -1592, -1592, -1592, -1592,   643, -1592, -1592, -1592,  7875,
   -1592,  1319,  1301, -1592,   315,  8069,   413, -1592,  7875,    24,
    1313,    24,  9469,   572, -1592, -1592,  1315, -1592,   413, -1592,
   -1592,  1322, -1592,    24, -1592,    24, -1592, -1592, -1592,   413,
   -1592, -1592,  3193, -1592,  7875, -1592, -1592, -1592,   985,  1317,
    1328,  1326, -1592,  1378, -1592, -1592,  8069,   413, -1592, -1592,
      24, -1592,  3402, -1592,  1328,  1331,   315,  1378, -1592, -1592
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,   172,     1,   371,     0,     0,    59,   684,   684,   372,
       0,   878,   868,   873,    21,     0,     0,    20,    17,    16,
       3,     0,     0,     0,     8,   721,     7,   665,     6,    11,
      12,     5,     4,    14,    13,    15,   137,   138,   136,   146,
     148,    50,    68,    65,    66,     0,     0,    51,   686,   685,
       0,     0,     0,    27,    26,   665,   684,   684,   684,     0,
     345,    48,   156,   157,   158,     0,     0,     0,   159,   161,
     168,     0,   155,    22,    10,     9,   294,   703,     0,   666,
     667,     0,     0,     0,     0,     0,    52,     0,     0,    60,
      63,   687,   689,     0,    23,     0,     0,     0,   347,     0,
       0,   167,   162,     0,     0,     0,     0,     0,     0,    77,
     295,   297,   691,   713,   712,   716,   669,   668,   675,   144,
     145,     0,   142,   143,   140,     0,     0,   139,   149,    69,
      67,     0,     0,    53,     0,     0,     0,     0,    64,    61,
       0,     0,    24,    25,    28,   778,    77,    77,   346,    46,
      49,   166,     0,   163,   164,   165,   169,    75,    78,   173,
     299,   298,   301,   296,   693,   692,     0,   715,   714,   718,
     717,   722,   670,   591,   141,    31,    32,    36,     0,   132,
     133,   130,   131,   129,   128,   134,     0,    55,    56,    54,
      58,    57,    63,     0,     0,     0,     0,     0,     0,     0,
     731,   751,   732,   767,   733,   737,   738,   739,   740,   757,
     744,   745,   746,   747,   748,   749,   750,   752,   753,   754,
     755,   838,   736,   743,   756,   845,   852,   734,   741,   735,
     742,     0,     0,     0,     0,   766,   799,   802,   800,   801,
     865,   795,     0,     0,    30,     0,   701,   869,   874,    47,
     160,    76,     0,   694,   695,   709,   672,     0,   592,     0,
      33,    34,    35,     0,   147,    62,   688,   803,   829,   832,
       0,   835,   825,     0,     0,   839,   846,   853,   859,   862,
       0,   797,   809,   339,   815,   820,   814,     0,   828,   824,
     817,     0,   819,     0,   796,     0,   690,    29,   781,   782,
     779,   780,   699,   702,   879,     0,     0,     0,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,     0,     0,   180,   174,   268,    77,     0,
     701,   710,     0,    77,   674,   671,   591,    77,     0,   654,
     646,   676,   135,     0,     0,     0,     0,     0,   492,   493,
       0,     0,     0,     0,   486,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   757,     0,     0,     0,     0,     0,
     406,     0,     0,     0,     0,     0,     0,   580,   419,   421,
     420,   422,   423,   424,   425,    42,     0,     0,     0,     0,
       0,   339,     0,   404,   405,   953,   490,   489,   567,   487,
     560,   559,   558,   557,   170,   563,   488,   562,   561,   534,
     494,   535,     0,   483,   539,   495,     0,   491,   890,   892,
     891,   484,   894,   893,   485,     0,     0,     0,   784,     0,
     174,     0,   174,     0,   174,     0,     0,     0,   811,     0,
     808,     0,     0,     0,   960,   397,   822,   823,   816,   818,
       0,   821,   792,     0,     0,   867,   866,   700,     0,   870,
     875,   259,   260,   257,   183,   184,   186,   185,   187,   188,
     189,   190,   216,   217,   214,   215,   207,   218,   219,   208,
     205,   206,   258,   241,     0,   256,   220,   221,   222,   223,
     194,   195,   196,   191,   192,   193,   204,     0,   210,   211,
     209,   202,   203,   198,   197,   199,   200,   201,   182,   181,
     240,     0,   212,   213,   591,   177,   307,   758,   761,   764,
     765,   759,   762,   760,   763,   696,     0,   707,   723,     0,
     150,    77,     0,     0,   647,     0,     0,     0,     0,   789,
     914,   917,   350,   766,   354,   353,   359,   883,   889,   884,
     885,   886,   888,   887,     0,   391,     0,     0,     0,   944,
       0,     0,     0,     0,   382,   385,     0,   388,     0,   948,
       0,   926,   930,     0,     0,   920,     0,   522,   523,     0,
       0,   458,   455,   457,     0,     0,     0,     0,     0,     0,
       0,   499,   498,   536,   497,   496,     0,     0,     0,     0,
     345,   960,   960,     0,    77,     0,     0,   414,   406,   336,
     170,   313,   311,   312,   310,   806,     0,     0,     0,     0,
     524,   525,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     473,     0,     0,     0,     0,   768,   783,     0,     0,   177,
       0,   177,     0,   177,   345,   623,     0,   621,     0,   629,
       0,   769,     0,   960,     0,   343,   398,   807,   961,   340,
     813,   791,   794,     0,   880,   625,   631,   261,   263,   262,
     264,   255,   239,   265,   242,   224,     0,   175,   370,   616,
     617,     0,     0,     0,   300,     0,   401,     0,   302,   704,
       0,   711,     0,     0,   648,   646,   673,   151,   655,     0,
     644,   645,   643,     0,   804,   830,   833,    19,    18,   787,
     788,     0,     0,     0,     0,   912,     0,     0,     0,   934,
     937,   940,     0,   960,     0,   951,   960,     0,     0,     0,
       0,     0,     0,     0,   960,     0,     0,   960,   923,     0,
       0,     0,     0,     0,   174,     0,     0,     0,     0,     0,
       0,    45,     0,    43,     0,     0,   933,     0,   635,     0,
     634,     0,     0,   961,   905,   527,   341,     0,   339,   476,
       0,     0,     0,     0,   174,     0,   414,     0,     0,   546,
     545,     0,     0,   547,   551,   500,   501,   513,   514,   511,
     512,     0,   540,     0,   532,     0,   564,   565,   566,   502,
     503,   569,   570,   571,   518,   519,   520,   521,     0,     0,
     516,   517,   515,   509,   510,   505,   504,   506,   507,   508,
       0,     0,     0,   464,     0,     0,     0,     0,     0,   481,
       0,   836,   826,   770,     0,   840,     0,   847,     0,   854,
       0,     0,   860,     0,     0,   863,     0,     0,     0,   797,
       0,     0,   399,   793,   773,   626,    95,   632,    95,   266,
     267,   244,   245,   247,   246,   248,   249,   250,   251,   243,
     252,   253,   254,   228,   229,   231,   230,   232,   233,   234,
     235,   226,   227,   236,   237,   238,   225,     0,   368,   369,
       0,   591,   591,   591,   176,   179,   178,     0,   402,   336,
     681,   708,   719,   604,   724,     0,     0,     0,     0,     0,
     662,     0,     0,   805,   831,   834,   790,     0,     0,     0,
     913,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   961,     0,   537,     0,     0,   538,
       0,   568,     0,     0,     0,     0,     0,     0,     0,   414,
       0,     0,     0,   177,   575,   576,   577,   578,   579,     0,
      39,     0,   111,     0,     0,     0,     0,   896,   895,   526,
       0,     0,     0,     0,   960,     0,   477,     0,     0,     0,
     480,   478,   171,     0,   177,   338,   362,   360,   307,     0,
       0,     0,   361,     0,     0,     0,    77,     0,   333,   418,
     314,     0,     0,     0,   327,     0,   328,   322,     0,   319,
     318,     0,   320,     0,     0,   337,     0,    91,    92,    89,
      90,   329,   374,   317,     0,   426,   174,   542,     0,   548,
       0,     0,     0,   530,     0,     0,   552,   556,     0,     0,
     533,     0,     0,     0,     0,   465,     0,   474,     0,   528,
       0,   482,   837,   827,     0,   785,     0,   841,   843,   848,
     850,   855,   857,   622,   861,   624,   628,   864,   630,   797,
     798,   810,   344,   400,   774,   697,    93,    96,   871,    96,
     876,     0,     0,   725,   613,   614,   636,   618,   620,   619,
     403,     0,   677,   682,   697,   607,     0,   650,     0,   651,
       0,     0,     0,   664,   915,   918,   351,     0,   356,   357,
     355,     0,     0,   394,   392,     0,     0,     0,   945,   943,
     341,     0,   952,   955,   383,   386,   389,   949,   947,   927,
     931,   929,     0,   921,    77,   456,   590,   459,     0,     0,
      40,     0,     0,     0,   375,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   954,   342,   479,     0,     0,   339,
       0,     0,     0,     0,     0,     0,   412,     0,    77,     0,
     363,     0,     0,   348,     0,     0,   332,     0,     0,    72,
     307,     0,   365,   336,   330,   331,     0,    84,    85,     0,
     152,   152,     0,   321,   316,   323,   324,   325,   326,   373,
       0,   315,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     177,     0,     0,     0,     0,   339,   450,     0,     0,     0,
     553,     0,   541,     0,   531,     0,   339,   466,     0,     0,
       0,   529,   475,   471,     0,   772,   786,   771,   844,   851,
     858,   812,     0,   679,   698,   881,    94,   627,     0,   633,
       0,   615,     0,     0,     0,     0,   637,     0,     0,     0,
     698,   705,     0,   605,   720,     0,   591,   649,     0,     0,
     659,     0,     0,   663,     0,     0,   352,   358,     0,     0,
     393,   935,   938,   941,     0,     0,     0,     0,     0,     0,
       0,   912,     0,   924,     0,     0,   307,     0,   462,   581,
       0,    37,    44,     0,   113,     0,   114,     0,     0,   115,
       0,     0,     0,     0,     0,   898,   897,     0,   447,     0,
     449,   409,   410,     0,   408,   407,     0,   415,   307,   364,
     307,   349,     0,     0,    70,    71,   121,   366,     0,     0,
       0,     0,   154,     0,     0,     0,     0,   656,   380,   379,
     438,   439,   441,   440,   442,   432,   433,   434,   443,   444,
     428,   429,   430,   431,   445,   446,   435,   436,   437,   427,
      77,     0,   589,     0,   587,     0,     0,   451,   454,   584,
       0,     0,     0,   583,     0,     0,   467,   470,     0,   472,
     775,   776,   680,     0,   872,   877,     0,   727,     0,   728,
     639,   638,   303,   678,   683,     0,     0,   598,   601,     0,
       0,   653,     0,   661,   912,   912,     0,     0,     0,     0,
       0,   339,   956,   341,     0,     0,     0,     0,   913,   928,
     912,     0,   912,   572,     0,   574,   460,     0,   582,    41,
     112,   376,     0,     0,     0,     0,     0,   900,   899,     0,
       0,     0,     0,   413,   416,   367,   127,   126,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   307,   543,   549,
       0,     0,     0,   588,   586,     0,     0,   585,     0,   882,
     726,     0,     0,     0,   304,   309,   706,     0,   599,   600,
     601,   602,   593,   608,   652,   660,   911,   911,   395,     0,
     912,   912,   903,     0,     0,     0,     0,     0,   960,   911,
     912,   903,   573,   463,    38,     0,     0,   117,   118,     0,
       0,     0,     0,   448,   411,   303,    86,    77,   153,     0,
       0,    77,   646,   381,   657,   658,   417,   544,   550,   452,
     453,   554,   468,   469,   777,     0,   730,   640,     0,     0,
     596,   593,   594,   595,   598,     0,   908,   960,   910,     0,
       0,     0,   911,   911,   904,     0,   946,   957,   384,   387,
     390,     0,     0,   903,     0,   958,   116,     0,   902,   901,
       0,   335,     0,     0,   108,     0,    77,   307,     0,     0,
     555,   729,   336,   606,   597,   609,   596,     0,     0,   961,
     909,   916,   919,   396,     0,     0,   942,   950,   932,     0,
     922,     0,     0,   958,     0,    87,    91,    92,    89,    90,
      88,   110,   100,     0,   307,   125,     0,     0,     0,     0,
     611,   642,   641,   603,   906,     0,   936,   939,   925,     0,
     962,     0,   958,    97,    79,     0,    77,   123,     0,     0,
       0,     0,     0,     0,   959,   963,     0,   336,    77,    73,
      74,     0,   109,     0,   307,     0,   378,   306,   610,    77,
     907,   964,     0,    80,     0,   101,   120,   377,   307,     0,
     105,     0,   612,   303,   102,    81,     0,    77,    99,   336,
       0,    82,     0,   106,   105,     0,    79,   303,    83,   104
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1592, -1592, -1049,    -1, -1592, -1592, -1592, -1592, -1592,   937,
    1461, -1592, -1592, -1592, -1592, -1592, -1592,  1540, -1592, -1592,
   -1592,   244, -1592, -1592,  1351, -1592, -1592,  1464, -1592, -1592,
   -1592, -1592,  -140,  -192, -1592, -1592, -1592, -1592, -1562,   657,
     662, -1592, -1592, -1592, -1592,  -183, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592,  -977, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592,  1296, -1592, -1592,   -31,  -103,  -214,   331, -1592,
   -1592,   456,   938,   945,   436,  -416,  -633, -1592,  -429, -1592,
   -1592, -1592, -1510, -1592, -1592, -1521, -1592, -1592,  -999, -1592,
   -1592, -1592, -1592, -1592, -1592,  -895,  -281, -1117,   881,   -12,
   -1592, -1592, -1592, -1592, -1592, -1561, -1559, -1558, -1550, -1592,
   -1592,  1566, -1592, -1088, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592,  -375, -1353,   522,
     202, -1592,  -754, -1592,   557, -1592, -1592, -1592, -1592, -1288,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,   504,
    1093, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,  -161,
     -21,   -65,   -22,    43, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592,   129,  -663,  -725, -1592,  -667,  -723, -1592,  -978,   -62,
     -60, -1592,  -719,  -714, -1592, -1592, -1592, -1195, -1592,  1519,
   -1592, -1592, -1592, -1592, -1592,   279,   458, -1592,   441, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592,   461, -1592,  1240, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592, -1592,  -111, -1592,  1223, -1592, -1592, -1592,
    1377, -1592, -1592, -1592,  -533, -1592, -1592,  -270,  -862, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,  -136, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592,  -759, -1465,  -584, -1592,
   -1592, -1403, -1284,  1229, -1592, -1592, -1592, -1592, -1592, -1592,
   -1592, -1592, -1592, -1592,  1231, -1592, -1592,  1232, -1592, -1592,
   -1592, -1592, -1592, -1592, -1592, -1592, -1592, -1592,  1018, -1592,
    -352,  1233, -1591,  -598,  1245,  -351
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,   739,   740,    19,   144,    55,   244,    20,   178,
     184,  1479,  1171,  1341,   600,   406,   150,   407,   100,    22,
      23,    89,    46,    47,   139,    24,    43,    44,  1031,  1032,
    1701,   158,   159,  1702,  1720,  1734,  1219,  1623,  1033,  1107,
    1108,  1684,  1697,  1719,  1685,  1725,  1729,  1735,  1726,  1034,
    1035,  1662,  1036,   994,  1037,  1038,  1039,  1040,  1041,  1042,
    1043,  1044,   185,   186,    39,    40,    41,   258,  1383,    68,
      69,    70,    71,   617,    25,   525,   714,   336,   337,   111,
      26,   162,   338,   163,   252,  1525,  1588,  1690,   716,   717,
    1298,   408,  1045,  1213,  1498,   805,   608,  1003,   684,   409,
    1046,   554,   744,  1316,   410,  1047,  1048,  1049,  1050,  1051,
     920,  1052,  1230,  1175,  1388,  1053,   411,   758,  1327,   759,
    1328,   761,  1329,   412,   748,  1320,   413,   454,   718,   414,
    1196,  1197,   804,   415,   621,   416,  1054,   417,   418,   593,
     419,   773,  1337,   774,  1477,   420,   856,  1272,   421,   455,
     423,  1251,  1577,  1253,  1578,  1420,  1630,   424,   425,   708,
    1594,  1635,  1530,  1532,  1449,  1125,  1306,  1669,  1692,   709,
     710,   711,   675,   676,   886,   679,   680,   888,   791,  1114,
    1115,  1673,   733,   545,   725,   350,  1506,   726,   351,    80,
     118,   256,   346,    28,   173,  1123,  1284,  1124,    50,    51,
     140,    29,    30,   166,   254,   340,  1285,   303,   304,    31,
     112,   930,  1445,   721,   342,   343,   115,   171,   934,    32,
      78,   255,   722,  1116,   426,   535,   237,   238,   864,  1105,
     246,   239,   667,  1276,   873,   548,   294,   240,   450,   241,
     353,   943,   451,   682,   436,  1083,   354,   944,   355,   945,
     435,  1082,   439,  1087,   440,  1278,   441,  1089,   442,  1279,
     443,  1091,   444,  1280,   445,  1094,   446,  1097,   677,    33,
      57,   305,   695,  1288,    34,    58,   306,   696,  1290,    35,
      56,   468,   884,  1433,   556,   427,   612,  1605,   613,  1597,
    1598,  1599,   953,   428,   742,  1314,   743,  1315,   769,  1334,
     977,  1471,   765,  1331,   429,   766,  1332,   430,   957,  1458,
     958,  1459,   959,  1460,   752,  1324,   763,  1330,  1004,   614,
     431,   432,  1652,   689,   433,   434
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      18,   152,   453,    61,    72,   242,   247,   248,   560,   563,
     941,   939,   259,   792,   794,  1494,   741,  1101,  1178,  1201,
      73,    74,    75,  1182,   669,   466,   671,   611,   673,   887,
     236,   801,   885,  1325,  1121,  1389,   866,  -172,   868,  1008,
     870,   975,   698,   700,  1621,   456,   978,  1469,  1176,  1476,
      92,   128,  1056,    72,    72,    72,  1283,   266,  1351,   584,
    1655,  1656,  1681,  1657,  1658,   918,   108,   788,   137,  1302,
     257,     2,  1659,  -842,   683,  1283,  1490,   618,     3,   712,
    -849,   566,   236,   706,  -856,   878,  1614,  -461,   282,  1625,
     257,  1696,   109,    72,    72,    72,    72,  1592,   448,   458,
     257,     4,    42,     5,   138,     6,    36,    37,   283,   919,
      45,     7,     8,   706,   179,   180,   790,   636,   449,   295,
     638,   639,     9,  1703,  1656,  -842,  1657,  1658,    10,   235,
    -842,   713,  -849,   707,  1600,  1659,  -856,  -849,  1297,  -461,
      99,  -856,   403,   404,  -461,   619,  1612,   876,  1649,  -842,
    1381,   880,    11,    62,  1576,   961,  -849,  1593,   965,  1691,
    -856,   952,   922,  -461,  1730,  1656,   973,  1657,  1658,   976,
    1536,  1537,   991,    53,    12,    13,  1659,   871,    79,   567,
     568,   235,  1709,    63,   236,   539,  1549,   992,  1551,  1553,
     660,   661,    14,   923,   457,   753,    81,  1303,   526,  1644,
    1645,  1353,  1728,   538,  1177,   764,  1357,   540,   767,  1098,
    1095,  1376,    54,  1007,  1177,    82,  1739,   546,   547,   549,
    1131,   963,   281,   585,   993,  1164,   347,    64,   119,   120,
      16,    17,  1177,  1146,   135,  1432,  1147,  1281,  1304,    14,
     800,   296,   236,   236,   236,  1177,   136,    76,   459,   157,
    1190,  1432,    65,    38,  1348,   345,  1602,  1603,   181,   569,
      15,    59,  1485,   182,   730,   183,  1613,   460,   125,  1349,
     731,   788,    16,   729,   890,    77,   461,  1181,    17,   570,
      82,   638,   639,   235,   578,    60,    83,   860,   626,   627,
      90,   157,   832,   833,    84,   105,   106,   107,  1505,   663,
     664,   754,  1258,   668,   723,   670,  1350,   672,   250,   356,
     357,  1575,    66,   732,  1269,   685,   770,   541,  1378,   724,
     790,    14,    67,    59,   236,   236,  1335,  1698,   236,   363,
     236,   133,   236,    91,   236,   365,   609,  1475,  1699,  1700,
     236,   235,   235,   235,   880,  1005,  1544,    60,   553,   564,
    1168,   660,   661,   121,   108,  1191,   151,   135,   983,  1084,
      17,  1192,  1573,   263,   788,  1722,  1137,  1085,   592,   136,
     951,  1495,   122,   372,   373,   187,   188,   123,   189,   124,
    1012,  1198,   125,  1006,   628,   629,   630,   631,  1014,   788,
    1086,   264,    93,  1193,   636,   789,   637,   638,   639,   640,
     641,   727,   642,   643,  1194,    99,  1185,   375,   376,  1195,
    1187,  1311,  1294,   790,   788,  1295,   126,   678,  1296,    14,
     789,  1142,    14,   235,   235,    14,   723,   235,    99,   235,
    1359,   235,   236,   235,   295,   723,  1188,    48,   790,   235,
      98,   724,  1289,    49,  1287,   876,    59,   110,   284,    52,
     724,   788,   655,   656,   657,   658,   659,  1352,    17,  1187,
     236,    17,  1523,   790,    17,   788,   344,   660,   661,    85,
      60,  1560,   947,   948,   796,   236,   285,   286,  1386,  1112,
     626,   627,   960,  1387,    85,  1491,    86,   552,   967,   968,
     104,   970,   129,   972,  1113,   974,  1415,    95,    96,    97,
     790,    86,   131,   982,   609,   401,  1187,  1424,   132,    87,
    1009,  1561,   405,  1005,   790,   810,   814,   737,    14,    59,
      88,   101,   102,   103,    87,  1569,   738,   284,   589,   134,
     828,   235,  1510,   590,   872,    88,  1128,  1080,  1010,   823,
     287,  1080,  1345,    60,   288,  1187,   685,   116,   824,   857,
    1595,  1129,  1366,   117,  1416,   285,   286,    17,   141,   235,
     591,   153,   154,   155,   156,  1081,   737,    14,  1187,  1138,
    1346,   236,  1187,  1360,   235,   738,   925,   926,   630,   631,
    1367,   157,  1417,   875,   236,  1425,   636,  1187,   637,   638,
     639,   640,   641,   289,   737,    14,  1418,   290,  1515,   979,
     291,   236,   236,   738,    72,   946,    17,   295,   949,   737,
      14,  1080,   956,  1426,   876,  1427,    82,  1410,   738,   287,
    1438,   542,   149,   288,   543,   292,   879,   544,  1665,   145,
     236,   236,   236,   236,    17,  1439,  1080,   236,   571,  1429,
    1250,   236,  1568,  1080,   737,    14,   146,   236,   236,    17,
     236,   147,   236,   738,   236,   236,   148,  1511,   572,   660,
     661,  1099,   236,  1345,  1478,  1687,  1516,  1080,  1130,   142,
     235,  1482,   289,   737,    14,   143,   290,   174,  1134,   291,
     737,    14,   738,   235,    17,   167,  1257,  1145,   168,   738,
    1141,  1558,   579,  1151,  1345,  1559,  1187,  1160,  1268,   582,
     235,   235,   190,  1274,   292,  1716,  1187,  1162,   931,  1000,
     172,  1080,   580,    17,   626,   627,   737,    14,  1001,   583,
      17,   136,  1572,  1628,  1580,   738,   544,  1067,   940,   235,
     235,   235,   235,  1163,  1583,  1093,   235,  1668,  1096,  1620,
     235,   737,    14,  1187,  1102,  1080,   235,   235,  1187,   235,
     738,   235,  1590,   235,   235,    59,    17,   191,  1322,  1069,
     236,   235,   236,   236,   589,   298,   746,   192,  1070,   236,
     193,  1674,  1531,  1686,   422,   243,  1710,  1596,  1596,    60,
     299,    17,  1074,  1604,   447,   300,   747,   301,   245,   245,
    1596,  1075,  1604,  -778,  1340,  1431,   737,   463,   737,    14,
     609,  1347,  1712,   249,  1030,   738,   105,   738,   107,  1005,
     628,   629,   630,   631,   632,  1323,   251,   633,   634,   635,
     636,   284,   637,   638,   639,   640,   641,   236,   642,   643,
    1122,   737,   105,   737,  1732,   284,  1638,   253,    17,   257,
     738,   284,   738,  1596,  1596,   937,   236,   236,   938,   285,
     286,   544,   236,   295,  1604,   138,   295,   734,  1629,   235,
     735,   235,   235,   285,   286,   160,   236,   267,   235,   285,
     286,   161,   297,   650,   651,   652,   653,   654,   655,   656,
     657,   658,   659,   164,   268,  1106,  1210,  1106,   269,   165,
    1401,  1402,   169,   660,   661,  1528,   527,   270,   170,   295,
     528,  1529,   273,   861,   295,   626,   627,   295,   862,   271,
    1667,   865,   272,   287,   529,   530,  1693,   288,   275,   531,
     532,   533,   534,   276,   295,   295,   235,   287,   867,   869,
     730,   288,   277,   287,   295,   278,   731,   288,  1136,   620,
     620,  1133,   620,   620,   295,   235,   235,  1688,  1144,   295,
    1611,   235,   293,  1509,   295,   279,   686,   302,  1581,   175,
     176,   781,   782,   113,   114,   235,   289,   341,   693,   280,
     290,   339,  1135,   291,   348,   622,  1486,   623,   624,   732,
     289,  1411,   932,   933,   290,   349,   289,   291,   260,   261,
     290,   295,  1148,   291,  1217,  1218,   236,   437,   292,  1640,
     438,   628,   629,   630,   631,   632,  1382,  1382,   633,   634,
     635,   636,   292,   637,   638,   639,   640,   641,   292,   642,
     643,   467,  1206,   644,  1336,   464,   522,   645,   646,   647,
    1214,  1215,   523,   648,   105,   106,   107,   175,   176,   177,
     260,   261,   262,  1223,   469,  1224,  1225,  1226,  1227,  1228,
    1117,  1118,  1119,  1231,   470,   524,   537,   550,  1368,   551,
     565,   573,   649,  1068,   650,   651,   652,   653,   654,   655,
     656,   657,   658,   659,   576,   574,   755,   757,   575,   577,
     760,   578,   762,   581,   660,   661,   586,   625,   594,   595,
     596,   597,  1548,   665,   666,   235,   598,   599,   775,   776,
     777,   778,   779,   780,   615,   616,  1286,   678,  1286,   662,
     688,   681,   687,   690,   691,  1562,   701,  1413,   702,   703,
    1030,   694,   704,   705,   715,   719,   720,   728,   736,  1310,
     745,  1313,   749,   771,   750,   751,   626,   627,   768,   772,
     236,   194,   236,   825,   785,  1448,   784,   195,   786,   793,
     803,   787,   821,   196,   863,   874,   883,   795,   936,  1440,
     917,   954,  1057,   964,   197,   858,   921,   924,   929,   935,
    1063,   966,   198,   969,   971,   984,   985,  1059,   986,   987,
    1543,   988,   989,   995,   236,   999,  1011,   199,  1077,  1088,
    1090,  1079,   882,  1013,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,  1058,  1060,  1061,
     626,   627,  1062,  1072,   630,   631,  1496,   942,  1073,   235,
    1078,   235,   636,  1092,   637,   638,   639,   640,   641,  1100,
    1663,   955,   449,  1104,  1122,   626,   627,  1127,  1139,  1140,
    1143,   236,  1149,  1150,    59,  1153,  1158,  1161,  1165,  1166,
    1507,  1169,  1172,  1170,  1173,   980,   981,   233,  1501,  1174,
    1179,  1180,  1183,   235,  1512,  1186,   990,  1204,    60,  1184,
    1205,   996,   284,   997,  1207,   998,  1216,  1220,  1221,  1222,
     755,  1260,   657,   658,   659,  1229,  1261,  1263,  1264,   236,
    1270,  1453,  1271,  1275,  1277,   660,   661,  1282,  1293,  1292,
     285,   286,  1299,  1291,  1307,   592,  1308,   234,   630,   631,
    1317,  1309,   465,  1318,  1319,  1338,   636,  1342,   637,   638,
     639,   640,   641,  1344,  1361,  1358,  1362,  1363,  1364,  1365,
    1370,  1372,  1373,   630,   631,  1071,  1375,  1379,  1666,  1076,
     235,   636,  1380,  1374,   638,   639,   640,   641,  1385,  1434,
    1412,  1414,  1437,  1419,  1423,  1447,  1446,  1030,  1451,  1454,
    1435,  1442,  1455,   284,   287,  1103,  1457,  1468,   288,  1461,
    1481,  1589,  1462,  1463,   655,   656,   657,   658,   659,  1464,
    1484,  1465,  1466,  1467,   284,  1480,  1470,  1472,   235,   660,
     661,   285,   286,  1492,  1483,  1524,   236,  1489,  1502,  1503,
    1518,  1111,  1513,  1514,  1517,  1520,  1519,  1624,  1521,  1522,
    1527,  1627,   285,   286,   660,   661,  1526,   289,  1531,  1126,
    1534,   290,  1539,  1154,   291,  1132,  1538,  1540,  1533,  1541,
    1554,  1535,  1542,  1550,  1557,  1552,  1586,  1565,  1563,  1555,
    1622,  1564,  1566,  1632,  1567,   592,  1571,  1579,  1152,   292,
    1582,   587,   588,  1606,  1607,   287,  1608,  1609,   730,   288,
    1610,  1616,  1617,  1626,   731,  1631,  1664,  1634,  1187,   601,
     602,   603,   604,   605,  1639,  1641,   287,  1642,   626,   627,
     288,  1643,  1646,  1647,  1648,  1574,  1650,  1675,  1651,  1676,
    1654,  1677,  1678,   882,  1679,   235,  1680,   236,    14,  1683,
    1200,  1695,  1707,  1203,  1711,  1714,  1723,   732,   289,  1209,
    1727,  1212,   290,   626,   627,   291,  1724,   783,   737,    14,
    1737,    21,   127,   265,  1738,  1109,  1704,   738,   130,   289,
    1110,  1736,  1384,   290,   802,   962,   291,    17,  1713,   352,
     292,  1305,  1252,   877,  1254,   806,  1259,    27,  1493,  1718,
    1636,  1670,  1637,  1591,    94,  1671,  1265,  1672,    17,  1444,
     536,   292,  1300,   555,   882,  1301,   274,  1731,  1633,   557,
     756,   558,   559,   561,   628,   629,   630,   631,   632,     0,
       0,   633,   634,   635,   636,   562,   637,   638,   639,   640,
     641,     0,   642,   643,     0,     0,   235,     0,     0,     0,
       0,     0,  1661,     0,     0,     0,     0,     0,     0,   628,
     629,   630,   631,   632,     0,  1312,   633,   634,   635,   636,
       0,   637,   638,   639,   640,   641,     0,   642,   643,     0,
       0,     0,     0,     0,   755,   645,     0,   647,   651,   652,
     653,   654,   655,   656,   657,   658,   659,  1030,     0,     0,
       0,     0,     0,     0,     0,     0,  1343,   660,   661,   626,
     627,     0,     0,     0,  1354,  1355,  1356,     0,  1706,     0,
    1708,     0,   650,   651,   652,   653,   654,   655,   656,   657,
     658,   659,  1715,  1369,  1717,     0,  1371,     0,     0,     0,
       0,  1030,   660,   661,     0,  1377,     0,     0,     0,     0,
       0,   815,   816,     0,     0,   817,   818,   819,   820,  1733,
     822,  1030,     0,   826,   827,   829,   830,   831,   834,   835,
     836,   837,   839,   840,   841,   842,   843,   844,   845,   846,
     847,   848,   849,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1421,     0,  1422,     0,     0,
       0,     0,     0,     0,  1428,   628,   629,   630,   631,   632,
       0,     0,   633,   634,   635,   636,  1430,   637,   638,   639,
     640,   641,     0,   642,   643,     0,  1436,     0,     0,     0,
       0,  1441,     0,  1443,     0,     0,     0,     0,   928,     0,
       0,     0,  1450,     0,     0,  1452,     0,     0,     0,     0,
       0,     0,  1456,     0,     0,     0,   284,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   284,     0,     0,  1474,
     652,   653,   654,   655,   656,   657,   658,   659,     0,     0,
       0,     0,     0,     0,   285,   286,  1487,  1488,   660,   661,
       0,     0,     0,     0,   285,   286,     0,     0,     0,   891,
     892,   893,   894,   895,   896,   897,   898,  1497,     0,     0,
       0,   194,     0,  1499,  1500,     0,     0,   195,     0,  1504,
       0,     0,     0,   196,   899,     0,     0,     0,  1055,     0,
       0,     0,     0,     0,   197,     0,   900,   901,   902,     0,
       0,     0,   198,     0,     0,     0,     0,     0,   287,     0,
     882,     0,   288,     0,     0,     0,     0,   199,   287,   882,
       0,     0,   288,     0,   200,   201,   202,   203,   204,   205,
     206,   207,   208,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   755,  1545,  1546,
    1547,   289,   -88,     0,     0,   290,     0,  1155,   291,     0,
       0,   289,     0,   626,   627,   290,     0,  1556,   291,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   292,    59,     0,     0,  1570,     0,     0,
       0,     0,     0,   292,     0,     0,     0,   233,     0,     0,
    1120,     0,  1584,   284,     0,  1585,     0,  1587,   674,     0,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1601,     0,     0,     0,     0,     0,     0,
       0,   285,   286,     0,     0,     0,     0,     0,     0,  1615,
       0,     0,     0,     0,  1618,  1619,     0,   234,     0,    17,
       0,  1232,  1233,  1234,  1235,  1236,  1237,  1238,  1239,   628,
     629,   630,   631,   632,  1240,  1241,   633,   634,   635,   636,
    1242,   637,   638,   639,   640,   641,  1243,   642,   643,  1244,
    1245,   644,     0,     0,     0,   645,   646,   647,  1246,  1247,
    1248,   648,     0,     0,     0,   287,     0,     0,     0,   288,
       0,  1653,     0,     0,     0,   284,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1249,
     649,     0,   650,   651,   652,   653,   654,   655,   656,   657,
     658,   659,     0,   285,   286,     0,     0,     0,  1682,     0,
       0,  1262,   660,   661,     0,     0,     0,   284,   289,     0,
     194,  1689,   290,     0,  1156,   291,   195,     0,     0,     0,
       0,     0,   196,  1694,     0,     0,     0,     0,     0,     0,
       0,     0,  1705,   197,     0,   285,   286,     0,     0,     0,
     292,   198,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1055,     0,   199,   287,  1721,     0,
       0,   288,     0,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,     0,     0,   284,   287,
       0,     0,     0,   288,     0,     0,     0,     0,     0,     0,
     289,     0,     0,     0,   290,     0,  1157,   291,     0,     0,
       0,     0,     0,     0,     0,     0,   285,   286,     0,     0,
       0,     0,     0,    59,     0,     0,     0,     0,     0,     0,
       0,     0,   292,     0,     0,     0,   233,     0,     0,     0,
       0,     0,   289,     0,     0,     0,   290,    60,  1159,   291,
       0,     0,     0,     0,     0,  1390,  1391,  1392,  1393,  1394,
    1395,  1396,  1397,  1398,  1399,  1400,  1403,  1404,  1405,  1406,
    1407,  1408,  1409,  1015,   292,     0,     0,   356,   357,     3,
     287,  -122,  -107,  -107,   288,  -119,   234,   358,   359,   360,
     361,   362,     0,     0,     0,     0,     0,   363,  1016,   364,
    1017,  1018,     0,   365,     0,     0,     0,     0,     0,     0,
    1019,   366,  1020,     0,     0,  -124,     0,  1021,   367,     0,
       0,   368,     0,     9,   369,  1022,     0,  1023,   370,     0,
       0,  1024,  1025,   289,     0,     0,     0,   290,  1026,  1167,
     291,   372,   373,     0,   200,   201,   202,     0,   204,   205,
     206,   207,   208,   374,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   292,   222,   223,   224,     0,
       0,   227,   228,   229,   230,   375,   376,   377,  1027,   903,
     904,   905,   906,   907,   908,   909,   910,     0,     0,     0,
       0,   378,   379,     0,     0,     0,     0,     0,   911,     0,
       0,  1055,     0,     0,   912,     0,     0,     0,     0,     0,
       0,     0,   380,     0,    59,     0,   913,   914,   915,     0,
       0,     0,   381,   382,   383,   384,   385,     0,   386,     0,
     387,   388,   389,   390,   391,   392,   393,   394,    60,     0,
      14,   395,     0,     0,     0,     0,     0,   916,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   396,   397,   398,
       0,    15,   284,     0,   399,   400,     0,     0,     0,     0,
       0,     0,     0,   401,     0,   402,     0,   403,   404,    17,
    1028,  1029,     0,     0,     0,     0,     0,     0,     0,     0,
     285,   286,     0,     0,     0,     0,     0,  1015,     0,     0,
       0,   356,   357,     3,     0,  -122,  -107,  -107,     0,  -119,
       0,   358,   359,   360,   361,   362,     0,     0,     0,     0,
       0,   363,  1016,   364,  1017,  1018,     0,   365,     0,     0,
       0,     0,     0,     0,  1019,   366,  1020,     0,     0,  -124,
       0,  1021,   367,     0,     0,   368,     0,     9,   369,  1022,
       0,  1023,   370,     0,   287,  1024,  1025,     0,   288,     0,
       0,     0,  1026,     0,     0,   372,   373,     0,   200,   201,
     202,     0,   204,   205,   206,   207,   208,   374,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,     0,
     222,   223,   224,     0,     0,   227,   228,   229,   230,   375,
     376,   377,  1027,     0,     0,     0,     0,   289,     0,     0,
       0,   290,     0,  1321,   291,   378,   379,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   380,     0,    59,   292,
       0,     0,     0,     0,     0,  1660,   381,   382,   383,   384,
     385,     0,   386,     0,   387,   388,   389,   390,   391,   392,
     393,   394,    60,     0,    14,   395,     0,   284,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   396,   397,   398,     0,    15,     0,     0,   399,   400,
       0,  1055,     0,     0,     0,   285,   286,   401,     0,   402,
       0,   403,   404,    17,  1028,  -308,  1015,     0,  1660,     0,
     356,   357,     3,     0,  -122,  -107,  -107,     0,  -119,     0,
     358,   359,   360,   361,   362,     0,     0,     0,     0,     0,
     363,  1016,   364,  1017,  1018,  1055,   365,     0,     0,     0,
       0,     0,     0,  1019,   366,  1020,     0,     0,  -124,  1660,
    1021,   367,     0,     0,   368,  1055,     9,   369,  1022,   287,
    1023,   370,     0,   288,  1024,  1025,     0,     0,     0,     0,
       0,  1026,     0,     0,   372,   373,     0,   200,   201,   202,
       0,   204,   205,   206,   207,   208,   374,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,     0,   222,
     223,   224,     0,     0,   227,   228,   229,   230,   375,   376,
     377,  1027,   289,     0,     0,     0,   290,     0,  1326,   291,
       0,     0,     0,     0,   378,   379,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   292,   380,     0,    59,     0,     0,
       0,     0,     0,     0,     0,   381,   382,   383,   384,   385,
       0,   386,     0,   387,   388,   389,   390,   391,   392,   393,
     394,    60,     0,    14,   395,     0,   284,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     396,   397,   398,     0,    15,     0,     0,   399,   400,     0,
       0,     0,     0,     0,   285,   286,   401,     0,   402,     0,
     403,   404,    17,  1028,  -334,  1015,     0,     0,     0,   356,
     357,     3,     0,  -122,  -107,  -107,     0,  -119,     0,   358,
     359,   360,   361,   362,     0,     0,     0,     0,     0,   363,
    1016,   364,  1017,  1018,     0,   365,     0,     0,     0,     0,
       0,     0,  1019,   366,  1020,     0,     0,  -124,     0,  1021,
     367,     0,     0,   368,     0,     9,   369,  1022,   287,  1023,
     370,     0,   288,  1024,  1025,     0,     0,     0,     0,     0,
    1026,     0,     0,   372,   373,     0,   200,   201,   202,     0,
     204,   205,   206,   207,   208,   374,   210,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   220,     0,   222,   223,
     224,     0,     0,   227,   228,   229,   230,   375,   376,   377,
    1027,   289,     0,     0,     0,   290,     0,  1333,   291,     0,
       0,     0,     0,   378,   379,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   292,   380,     0,    59,     0,     0,     0,
       0,     0,     0,     0,   381,   382,   383,   384,   385,     0,
     386,     0,   387,   388,   389,   390,   391,   392,   393,   394,
      60,     0,    14,   395,     0,   284,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   396,
     397,   398,     0,    15,     0,     0,   399,   400,     0,     0,
       0,     0,     0,   285,   286,   401,     0,   402,     0,   403,
     404,    17,  1028,  -305,  1015,     0,     0,     0,   356,   357,
       3,     0,  -122,  -107,  -107,     0,  -119,     0,   358,   359,
     360,   361,   362,     0,     0,     0,     0,     0,   363,  1016,
     364,  1017,  1018,     0,   365,     0,     0,     0,     0,     0,
       0,  1019,   366,  1020,     0,     0,  -124,     0,  1021,   367,
       0,     0,   368,     0,     9,   369,  1022,   287,  1023,   370,
       0,   288,  1024,  1025,     0,     0,     0,     0,     0,  1026,
       0,     0,   372,   373,     0,   200,   201,   202,     0,   204,
     205,   206,   207,   208,   374,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,     0,   222,   223,   224,
       0,     0,   227,   228,   229,   230,   375,   376,   377,  1027,
     289,     0,     0,     0,   290,     0,  1508,   291,     0,     0,
       0,     0,   378,   379,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   292,   380,     0,    59,     0,     0,     0,     0,
       0,     0,     0,   381,   382,   383,   384,   385,     0,   386,
       0,   387,   388,   389,   390,   391,   392,   393,   394,    60,
       0,    14,   395,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   396,   397,
     398,     0,    15,     0,     0,   399,   400,     0,     0,     0,
       0,     0,     0,     0,   401,     0,   402,     0,   403,   404,
      17,  1028,   -98,  1015,     0,     0,     0,   356,   357,     3,
       0,  -122,  -107,  -107,     0,  -119,     0,   358,   359,   360,
     361,   362,     0,     0,     0,     0,     0,   363,  1016,   364,
    1017,  1018,     0,   365,     0,     0,     0,     0,     0,     0,
    1019,   366,  1020,     0,     0,  -124,     0,  1021,   367,     0,
       0,   368,     0,     9,   369,  1022,     0,  1023,   370,     0,
       0,  1024,  1025,     0,     0,     0,     0,     0,  1026,     0,
       0,   372,   373,     0,   200,   201,   202,     0,   204,   205,
     206,   207,   208,   374,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,     0,   222,   223,   224,     0,
       0,   227,   228,   229,   230,   375,   376,   377,  1027,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   378,   379,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   380,     0,    59,     0,     0,     0,     0,     0,
       0,     0,   381,   382,   383,   384,   385,     0,   386,     0,
     387,   388,   389,   390,   391,   392,   393,   394,    60,     0,
      14,   395,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   396,   397,   398,
       0,    15,     0,     0,   399,   400,     0,     0,     0,     0,
       0,     0,     0,   401,     0,   402,     0,   403,   404,    17,
    1028,  -103,   356,   357,     0,     0,     0,     0,     0,     0,
       0,     0,   358,   359,   360,   361,   362,     0,     0,     0,
       0,     0,   363,     0,   364,     0,     0,     0,   365,     0,
       0,     0,     0,     0,     0,     0,   366,     0,     0,     0,
       0,     0,     0,   367,     0,     0,   368,     0,     0,   369,
       0,     0,     0,   370,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   371,     0,     0,   372,   373,   797,   200,
     201,   202,     0,   204,   205,   206,   207,   208,   374,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
       0,   222,   223,   224,     0,     0,   227,   228,   229,   230,
     375,   376,   377,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   378,   379,     0,     0,
       0,     0,     0,     0,     0,   452,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   380,     0,    59,
       0,     0,     0,     0,     0,     0,     0,   381,   382,   383,
     384,   385,     0,   386,   609,   387,   388,   389,   390,   391,
     392,   393,   394,   610,     0,     0,   395,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   396,   397,   398,     0,    15,     0,     0,   399,
     400,     0,     0,     0,     0,     0,   356,   357,   798,     0,
     402,   799,   403,   404,   606,   405,   358,   359,   360,   361,
     362,     0,     0,     0,     0,     0,   363,     0,   364,     0,
       0,     0,   365,     0,     0,     0,     0,     0,     0,     0,
     366,     0,     0,     0,     0,     0,     0,   367,     0,     0,
     368,   607,     0,   369,     0,     0,     0,   370,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   371,     0,     0,
     372,   373,     0,   200,   201,   202,     0,   204,   205,   206,
     207,   208,   374,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,     0,   222,   223,   224,     0,     0,
     227,   228,   229,   230,   375,   376,   377,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     378,   379,     0,     0,     0,     0,     0,     0,     0,   452,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   380,     0,    59,     0,     0,     0,     0,     0,     0,
       0,   381,   382,   383,   384,   385,     0,   386,   609,   387,
     388,   389,   390,   391,   392,   393,   394,   610,     0,     0,
     395,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   396,   397,   398,     0,
      15,     0,     0,   399,   400,     0,     0,     0,     0,     0,
     356,   357,   401,     0,   402,     0,   403,   404,   606,   405,
     358,   359,   360,   361,   362,     0,     0,     0,     0,     0,
     363,     0,   364,     0,     0,     0,   365,     0,     0,     0,
       0,     0,     0,     0,   366,     0,     0,     0,     0,     0,
       0,   367,     0,     0,   368,   607,     0,   369,     0,     0,
       0,   370,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   371,     0,     0,   372,   373,     0,   200,   201,   202,
       0,   204,   205,   206,   207,   208,   374,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,     0,   222,
     223,   224,     0,     0,   227,   228,   229,   230,   375,   376,
     377,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   378,   379,     0,     0,     0,     0,
       0,     0,     0,   452,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   380,     0,    59,     0,     0,
       0,     0,     0,     0,     0,   381,   382,   383,   384,   385,
       0,   386,     0,   387,   388,   389,   390,   391,   392,   393,
     394,    60,     0,     0,   395,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     396,   397,   398,     0,    15,     0,     0,   399,   400,     0,
       0,     0,     0,     0,   356,   357,   401,     0,   402,     0,
     403,   404,     0,   405,   358,   359,   360,   361,   362,     0,
       0,     0,     0,     0,   363,     0,   364,     0,     0,     0,
     365,     0,     0,     0,     0,     0,     0,     0,   366,     0,
       0,     0,     0,     0,     0,   367,     0,     0,   368,     0,
       0,   369,     0,     0,     0,   370,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   371,     0,     0,   372,   373,
     950,   200,   201,   202,     0,   204,   205,   206,   207,   208,
     374,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,     0,   222,   223,   224,     0,     0,   227,   228,
     229,   230,   375,   376,   377,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   378,   379,
       0,     0,     0,     0,     0,     0,     0,   452,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   380,
       0,    59,     0,     0,     0,     0,     0,     0,     0,   381,
     382,   383,   384,   385,     0,   386,   609,   387,   388,   389,
     390,   391,   392,   393,   394,   610,     0,     0,   395,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   396,   397,   398,     0,    15,     0,
       0,   399,   400,     0,     0,     0,     0,     0,   356,   357,
     401,     0,   402,     0,   403,   404,     0,   405,   358,   359,
     360,   361,   362,     0,     0,     0,     0,     0,   363,     0,
     364,     0,     0,     0,   365,     0,     0,     0,     0,     0,
       0,     0,   366,     0,     0,     0,     0,     0,     0,   367,
       0,     0,   368,     0,     0,   369,     0,     0,     0,   370,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   371,
       0,     0,   372,   373,     0,   200,   201,   202,     0,   204,
     205,   206,   207,   208,   374,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,     0,   222,   223,   224,
       0,     0,   227,   228,   229,   230,   375,   376,   377,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   378,   379,     0,     0,     0,     0,     0,     0,
       0,   452,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   380,     0,    59,     0,     0,     0,     0,
       0,     0,     0,   381,   382,   383,   384,   385,     0,   386,
     609,   387,   388,   389,   390,   391,   392,   393,   394,   610,
       0,     0,   395,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   396,   397,
     398,     0,    15,     0,     0,   399,   400,     0,     0,     0,
       0,     0,   356,   357,  1255,     0,   402,  1256,   403,   404,
       0,   405,   358,   359,   360,   361,   362,     0,     0,     0,
       0,     0,   363,     0,   364,     0,     0,     0,   365,     0,
       0,     0,     0,     0,     0,     0,   366,     0,     0,     0,
       0,     0,     0,   367,     0,     0,   368,     0,     0,   369,
       0,     0,     0,   370,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   371,     0,     0,   372,   373,     0,   200,
     201,   202,     0,   204,   205,   206,   207,   208,   374,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
       0,   222,   223,   224,     0,     0,   227,   228,   229,   230,
     375,   376,   377,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   378,   379,     0,     0,
       0,     0,     0,     0,     0,   452,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   380,     0,    59,
       0,     0,     0,     0,     0,     0,     0,   381,   382,   383,
     384,   385,     0,   386,   609,   387,   388,   389,   390,   391,
     392,   393,   394,   610,     0,     0,   395,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   396,   397,   398,     0,    15,     0,     0,   399,
     400,     0,     0,     0,     0,     0,   356,   357,  1266,     0,
     402,  1267,   403,   404,     0,   405,   358,   359,   360,   361,
     362,     0,     0,     0,     0,     0,   363,     0,   364,     0,
       0,     0,   365,     0,     0,     0,     0,     0,     0,     0,
     366,     0,     0,     0,     0,     0,     0,   367,     0,     0,
     368,     0,     0,   369,     0,     0,     0,   370,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   371,     0,     0,
     372,   373,     0,   200,   201,   202,     0,   204,   205,   206,
     207,   208,   374,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,     0,   222,   223,   224,     0,     0,
     227,   228,   229,   230,   375,   376,   377,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     378,   379,     0,     0,     0,     0,     0,     0,     0,   452,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   380,     0,    59,     0,     0,     0,     0,     0,     0,
       0,   381,   382,   383,   384,   385,     0,   386,   609,   387,
     388,   389,   390,   391,   392,   393,   394,   610,     0,     0,
     395,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   396,   397,   398,     0,
      15,     0,     0,   399,   400,     0,     0,     0,     0,     0,
     356,   357,   401,     0,   402,     0,   403,   404,     0,   405,
     358,   359,   360,   361,   362,     0,     0,     0,     0,     0,
     363,     0,   364,     0,     0,     0,   365,     0,     0,     0,
       0,     0,     0,     0,   366,     0,     0,     0,     0,     0,
       0,   367,     0,     0,   368,     0,     0,   369,     0,     0,
       0,   370,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   371,     0,     0,   372,   373,     0,   200,   201,   202,
       0,   204,   205,   206,   207,   208,   374,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,     0,   222,
     223,   224,     0,     0,   227,   228,   229,   230,   375,   376,
     377,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   378,   379,     0,     0,     0,     0,
       0,     0,     0,   452,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   380,     0,    59,     0,     0,
       0,     0,     0,     0,     0,   381,   382,   383,   384,   385,
       0,   386,     0,   387,   388,   389,   390,   391,   392,   393,
     394,    60,     0,     0,   395,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     396,   397,   398,     0,    15,     0,     0,   399,   400,     0,
       0,     0,     0,     0,   356,   357,   401,     0,   402,   859,
     403,   404,     0,   405,   358,   359,   360,   361,   362,     0,
       0,     0,     0,     0,   363,     0,   364,     0,     0,     0,
     365,     0,     0,     0,     0,     0,     0,     0,   366,     0,
       0,     0,     0,     0,     0,   367,     0,     0,   368,     0,
       0,   369,     0,     0,     0,   370,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   371,     0,     0,   372,   373,
       0,   200,   201,   202,     0,   204,   205,   206,   207,   208,
     374,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,     0,   222,   223,   224,     0,     0,   227,   228,
     229,   230,   375,   376,   377,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   378,   379,
       0,     0,     0,     0,     0,     0,     0,   881,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   380,
       0,    59,     0,     0,     0,     0,     0,     0,     0,   381,
     382,   383,   384,   385,     0,   386,   609,   387,   388,   389,
     390,   391,   392,   393,   394,   610,     0,     0,   395,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   396,   397,   398,     0,    15,     0,
       0,   399,   400,     0,     0,     0,     0,     0,   356,   357,
    1189,     0,   402,     0,   403,   404,     0,   405,   358,   359,
     360,   361,   362,     0,     0,     0,     0,     0,   363,     0,
     364,     0,     0,     0,   365,     0,     0,     0,     0,     0,
       0,     0,   366,     0,     0,     0,     0,     0,     0,   367,
       0,     0,   368,     0,     0,   369,     0,     0,     0,   370,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   371,
       0,     0,   372,   373,     0,   200,   201,   202,     0,   204,
     205,   206,   207,   208,   374,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,     0,   222,   223,   224,
       0,     0,   227,   228,   229,   230,   375,   376,   377,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   378,   379,     0,     0,     0,     0,     0,     0,
       0,   452,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   380,     0,    59,     0,     0,     0,     0,
       0,     0,     0,   381,   382,   383,   384,   385,     0,   386,
       0,   387,   388,   389,   390,   391,   392,   393,   394,    60,
       0,     0,   395,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   396,   397,
     398,     0,    15,     0,     0,   399,   400,     0,     0,     0,
       0,     0,   356,   357,   401,     0,   402,  1273,   403,   404,
       0,   405,   358,   359,   360,   361,   362,     0,     0,     0,
       0,     0,   363,     0,   364,     0,     0,     0,   365,     0,
       0,     0,     0,     0,     0,     0,   366,     0,     0,     0,
       0,     0,     0,   367,     0,     0,   368,     0,     0,   369,
       0,     0,     0,   370,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   371,     0,     0,   372,   373,     0,   200,
     201,   202,     0,   204,   205,   206,   207,   208,   374,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
       0,   222,   223,   224,     0,     0,   227,   228,   229,   230,
     375,   376,   377,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   378,   379,     0,     0,
       0,     0,     0,     0,     0,   452,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   380,     0,    59,
       0,     0,     0,     0,     0,     0,     0,   381,   382,   383,
     384,   385,     0,   386,     0,   387,   388,   389,   390,   391,
     392,   393,   394,    60,     0,     0,   395,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   396,   397,   398,     0,    15,     0,     0,   399,
     400,     0,     0,     0,     0,     0,   356,   357,   401,     0,
     402,  1339,   403,   404,     0,   405,   358,   359,   360,   361,
     362,     0,     0,     0,     0,     0,   363,     0,   364,     0,
       0,     0,   365,     0,     0,     0,     0,     0,     0,     0,
     366,     0,     0,     0,     0,     0,     0,   367,     0,     0,
     368,     0,     0,   369,     0,     0,     0,   370,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   371,     0,     0,
     372,   373,     0,   200,   201,   202,     0,   204,   205,   206,
     207,   208,   374,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,     0,   222,   223,   224,     0,     0,
     227,   228,   229,   230,   375,   376,   377,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     378,   379,     0,     0,     0,     0,     0,     0,     0,   881,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   380,     0,    59,     0,     0,     0,     0,     0,     0,
       0,   381,   382,   383,   384,   385,     0,   386,   609,   387,
     388,   389,   390,   391,   392,   393,   394,   610,     0,     0,
     395,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   396,   397,   398,     0,
      15,     0,     0,   399,   400,     0,     0,     0,     0,     0,
     356,   357,   401,     0,   402,     0,   403,   404,     0,   405,
     358,   359,   360,   361,   362,     0,     0,     0,     0,     0,
     363,     0,   364,     0,     0,     0,   365,     0,     0,     0,
       0,     0,     0,     0,   366,     0,     0,     0,     0,     0,
       0,   367,     0,     0,   368,     0,     0,   369,     0,     0,
       0,   370,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   371,     0,     0,   372,   373,     0,   200,   201,   202,
       0,   204,   205,   206,   207,   208,   374,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,     0,   222,
     223,   224,     0,     0,   227,   228,   229,   230,   375,   376,
     377,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   378,   379,     0,     0,     0,     0,
       0,     0,     0,   452,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   380,     0,    59,     0,     0,
       0,     0,     0,     0,     0,   381,   382,   383,   384,   385,
       0,   386,     0,   387,   388,   389,   390,   391,   392,   393,
     394,    60,     0,     0,   395,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     396,   397,   398,     0,    15,     0,     0,   399,   400,     0,
       0,     0,     0,     0,   356,   357,   401,     0,   402,     0,
     403,   404,     0,   405,   358,   359,   360,   361,   362,     0,
       0,     0,     0,     0,   363,     0,   364,     0,     0,     0,
     365,     0,     0,     0,     0,     0,     0,     0,   366,     0,
       0,     0,     0,     0,     0,   367,     0,     0,   368,     0,
       0,   369,     0,     0,     0,   370,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   371,     0,     0,   372,   373,
       0,   200,   201,   202,     0,   204,   205,   206,   207,   208,
     374,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,     0,   222,   223,   224,     0,     0,   227,   228,
     229,   230,   375,   376,   377,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   378,   379,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   380,
       0,    59,     0,     0,     0,     0,     0,     0,     0,   381,
     382,   383,   384,   385,     0,   386,     0,   387,   388,   389,
     390,   391,   392,   393,   394,    60,     0,     0,   395,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   396,   397,   398,     0,    15,     0,
       0,   399,   400,     0,     0,     0,     0,     0,   356,   357,
     401,   462,   402,     0,   403,   404,     0,   405,   358,   359,
     360,   361,   362,     0,     0,     0,     0,     0,   363,     0,
     364,     0,     0,     0,   365,     0,     0,     0,     0,     0,
       0,     0,   366,     0,     0,     0,     0,     0,     0,   367,
       0,     0,   368,     0,     0,   369,     0,     0,     0,   370,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   371,
       0,     0,   372,   373,     0,   200,   201,   202,     0,   204,
     205,   206,   207,   208,   374,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,     0,   222,   223,   224,
       0,     0,   227,   228,   229,   230,   375,   376,   377,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   378,   379,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   380,     0,    59,     0,     0,     0,     0,
       0,     0,     0,   381,   382,   383,   384,   385,     0,   386,
       0,   387,   388,   389,   390,   391,   392,   393,   394,    60,
       0,     0,   395,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   396,   397,
     398,     0,    15,     0,     0,   399,   400,     0,     0,     0,
       0,     0,   356,   357,   401,   692,   402,     0,   403,   404,
       0,   405,   358,   359,   360,   361,   362,     0,     0,     0,
       0,     0,   363,     0,   364,     0,     0,     0,   365,     0,
       0,     0,     0,     0,     0,     0,   366,     0,     0,     0,
       0,     0,     0,   367,     0,     0,   368,     0,     0,   369,
       0,     0,     0,   370,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   371,     0,     0,   372,   373,     0,   200,
     201,   202,     0,   204,   205,   206,   207,   208,   374,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
       0,   222,   223,   224,     0,     0,   227,   228,   229,   230,
     375,   376,   377,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   378,   379,     0,     0,
       0,     0,     0,     0,     0,   881,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   380,     0,    59,
       0,     0,     0,     0,     0,     0,     0,   381,   382,   383,
     384,   385,     0,   386,     0,   387,   388,   389,   390,   391,
     392,   393,   394,    60,     0,     0,   395,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   396,   397,   398,     0,    15,     0,     0,   399,
     400,     0,     0,     0,     0,     0,   356,   357,   401,     0,
     402,     0,   403,   404,  1002,   405,   358,   359,   360,   361,
     362,     0,     0,     0,     0,     0,   363,     0,   364,     0,
       0,     0,   365,     0,     0,     0,     0,     0,     0,     0,
     366,     0,     0,     0,     0,     0,     0,   367,     0,     0,
     368,     0,     0,   369,     0,     0,     0,   370,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   371,     0,     0,
     372,   373,     0,   200,   201,   202,     0,   204,   205,   206,
     207,   208,   374,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,     0,   222,   223,   224,     0,     0,
     227,   228,   229,   230,   375,   376,   377,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     378,   379,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   380,     0,    59,     0,     0,     0,     0,     0,     0,
       0,   381,   382,   383,   384,   385,     0,   386,     0,   387,
     388,   389,   390,   391,   392,   393,   394,    60,     0,     0,
     395,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   396,   397,   398,     0,
      15,     0,     0,   399,   400,     0,     0,     0,     0,     0,
     356,   357,   401,     0,   402,     0,   403,   404,     0,   405,
     358,   359,   360,   361,   362,     0,     0,     0,     0,     0,
     363,     0,   364,     0,     0,     0,   365,     0,     0,     0,
       0,     0,     0,     0,   366,     0,     0,     0,     0,     0,
       0,   367,     0,     0,   368,     0,     0,   369,     0,     0,
       0,   370,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   371,     0,     0,   372,   373,     0,   200,   201,   202,
       0,   204,   205,   206,   207,   208,   374,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,     0,   222,
     223,   224,     0,     0,   227,   228,   229,   230,   375,   376,
     377,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   378,   379,     0,     0,     0,     0,
       0,     0,     0,  1199,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   380,     0,    59,     0,     0,
       0,     0,     0,     0,     0,   381,   382,   383,   384,   385,
       0,   386,     0,   387,   388,   389,   390,   391,   392,   393,
     394,    60,     0,     0,   395,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     396,   397,   398,     0,    15,     0,     0,   399,   400,     0,
       0,     0,     0,     0,   356,   357,   401,     0,   402,     0,
     403,   404,     0,   405,   358,   359,   360,   361,   362,     0,
       0,     0,     0,     0,   363,     0,   364,     0,     0,     0,
     365,     0,     0,     0,     0,     0,     0,     0,   366,     0,
       0,     0,     0,     0,     0,   367,     0,     0,   368,     0,
       0,   369,     0,     0,     0,   370,     0,     0,     0,     0,
       0,  1202,     0,     0,     0,   371,     0,     0,   372,   373,
       0,   200,   201,   202,     0,   204,   205,   206,   207,   208,
     374,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,     0,   222,   223,   224,     0,     0,   227,   228,
     229,   230,   375,   376,   377,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   378,   379,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   380,
       0,    59,     0,     0,     0,     0,     0,     0,     0,   381,
     382,   383,   384,   385,     0,   386,     0,   387,   388,   389,
     390,   391,   392,   393,   394,    60,     0,     0,   395,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   396,   397,   398,     0,    15,     0,
       0,   399,   400,     0,     0,     0,     0,     0,   356,   357,
     401,     0,   402,     0,   403,   404,     0,   405,   358,   359,
     360,   361,   362,     0,     0,     0,     0,     0,   363,     0,
     364,     0,     0,     0,   365,     0,     0,     0,     0,     0,
       0,     0,   366,     0,     0,     0,     0,     0,     0,   367,
       0,     0,   368,     0,     0,   369,     0,     0,     0,   370,
       0,     0,  1208,     0,     0,     0,     0,     0,     0,   371,
       0,     0,   372,   373,     0,   200,   201,   202,     0,   204,
     205,   206,   207,   208,   374,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,     0,   222,   223,   224,
       0,     0,   227,   228,   229,   230,   375,   376,   377,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   378,   379,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   380,     0,    59,     0,     0,     0,     0,
       0,     0,     0,   381,   382,   383,   384,   385,     0,   386,
       0,   387,   388,   389,   390,   391,   392,   393,   394,    60,
       0,     0,   395,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   396,   397,
     398,     0,    15,     0,     0,   399,   400,     0,     0,     0,
       0,     0,   356,   357,   401,     0,   402,     0,   403,   404,
       0,   405,   358,   359,   360,   361,   362,     0,     0,     0,
       0,     0,   363,     0,   364,     0,     0,     0,   365,     0,
       0,     0,     0,     0,     0,     0,   366,     0,     0,     0,
       0,     0,     0,   367,     0,     0,   368,     0,     0,   369,
       0,     0,     0,   370,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   371,     0,     0,   372,   373,     0,   200,
     201,   202,     0,   204,   205,   206,   207,   208,   374,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   220,
       0,   222,   223,   224,     0,     0,   227,   228,   229,   230,
     375,   376,   377,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   378,   379,     0,     0,
       0,     0,     0,     0,     0,  1211,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   380,     0,    59,
       0,     0,     0,     0,     0,     0,     0,   381,   382,   383,
     384,   385,     0,   386,     0,   387,   388,   389,   390,   391,
     392,   393,   394,    60,     0,     0,   395,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   396,   397,   398,     0,    15,     0,     0,   399,
     400,     0,     0,     0,     0,     0,   356,   357,   401,     0,
     402,     0,   403,   404,     0,   405,   358,   359,   360,   361,
     362,     0,     0,     0,     0,     0,   363,     0,   364,     0,
       0,     0,   365,     0,     0,     0,     0,     0,     0,     0,
     366,     0,     0,     0,     0,     0,     0,   367,     0,     0,
     368,     0,     0,   369,     0,     0,     0,   370,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   371,     0,     0,
     372,   373,     0,   200,   201,   202,     0,   204,   205,   206,
     207,   208,   374,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,     0,   222,   223,   224,     0,     0,
     227,   228,   229,   230,   375,   376,   377,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     378,   379,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   380,     0,    59,     0,     0,     0,     0,     0,     0,
       0,   381,   382,   383,   384,   385,     0,   386,     0,   387,
     388,   389,   390,   391,   392,   393,   394,    60,     0,     0,
     395,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   396,   397,   398,     0,
      15,     0,     0,   399,   400,     0,     0,     0,     0,     0,
     356,   357,   401,     0,   402,  1473,   403,   404,     0,   405,
     358,   359,   360,   361,   362,     0,     0,     0,     0,     0,
     363,     0,   364,     0,     0,     0,   365,     0,     0,     0,
       0,     0,     0,     0,   366,     0,     0,     0,     0,     0,
       0,   367,     0,     0,   368,     0,     0,   369,     0,     0,
       0,   370,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   371,     0,     0,   372,   373,     0,   200,   201,   202,
       0,   204,   205,   206,   207,   208,   374,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,     0,   222,
     223,   224,     0,     0,   227,   228,   229,   230,   375,   376,
     377,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   378,   379,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   380,     0,    59,     0,     0,
       0,     0,     0,     0,     0,   381,   382,   383,   384,   385,
       0,   386,     0,   387,   388,   389,   390,   391,   392,   393,
     394,    60,     0,     0,   395,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     396,   397,   398,     0,    15,     0,     0,   399,   400,     0,
       0,     0,     0,     0,   356,   357,   401,     0,   402,     0,
     403,   404,     0,   405,   358,   359,   360,   361,   362,     0,
       0,     0,     0,     0,   363,  1016,   364,  1017,     0,     0,
     365,     0,     0,     0,     0,     0,     0,     0,   366,     0,
       0,     0,     0,     0,     0,   367,     0,     0,   368,     0,
       0,   369,  1022,     0,     0,   370,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   371,     0,     0,   372,   373,
       0,   200,   201,   202,     0,   204,   205,   206,   207,   208,
     374,   210,   211,   212,   213,   214,   215,   216,   217,   218,
     219,   220,     0,   222,   223,   224,     0,     0,   227,   228,
     229,   230,   375,   376,   377,  1027,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   378,   379,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   380,
       0,    59,     0,     0,     0,     0,     0,     0,     0,   381,
     382,   383,   384,   385,     0,   386,     0,   387,   388,   389,
     390,   391,   392,   393,   394,    60,     0,     0,   395,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   396,   397,   398,     0,    15,     0,
       0,   399,   400,     0,     0,     0,   356,   357,     0,     0,
     401,     0,   402,     0,   403,   404,   358,   359,   360,   361,
     362,     0,     0,   838,     0,     0,   363,     0,   364,     0,
       0,     0,   365,     0,     0,     0,     0,     0,     0,     0,
     366,     0,     0,     0,     0,     0,     0,   367,     0,     0,
     368,     0,     0,   369,     0,     0,     0,   370,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   371,     0,     0,
     372,   373,     0,   200,   201,   202,     0,   204,   205,   206,
     207,   208,   374,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,     0,   222,   223,   224,     0,     0,
     227,   228,   229,   230,   375,   376,   377,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     378,   379,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   380,     0,    59,     0,     0,     0,     0,     0,     0,
       0,   381,   382,   383,   384,   385,     0,   386,     0,   387,
     388,   389,   390,   391,   392,   393,   394,    60,     0,     0,
     395,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   396,   397,   398,     0,
      15,     0,     0,   399,   400,     0,     0,     0,   356,   357,
       0,     0,   401,     0,   402,     0,   403,   404,   358,   359,
     360,   361,   362,     0,     0,     0,     0,     0,   363,     0,
     364,     0,     0,     0,   365,     0,     0,     0,     0,     0,
       0,     0,   366,     0,     0,     0,     0,     0,     0,   367,
       0,     0,   368,     0,     0,   369,     0,     0,     0,   370,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   371,
       0,     0,   372,   373,     0,   200,   201,   202,     0,   204,
     205,   206,   207,   208,   374,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,     0,   222,   223,   224,
       0,     0,   227,   228,   229,   230,   375,   376,   377,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   378,   379,     0,     0,     0,     0,     0,     0,
       0,   927,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   380,     0,    59,     0,     0,     0,     0,
       0,     0,     0,   381,   382,   383,   384,   385,     0,   386,
       0,   387,   388,   389,   390,   391,   392,   393,   394,    60,
       0,     0,   395,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   396,   397,
     398,     0,    15,     0,     0,   399,   400,     0,     0,     0,
     356,   357,     0,     0,   401,     0,   402,     0,   403,   404,
     358,   359,   360,   361,   362,     0,     0,     0,     0,     0,
     363,     0,   364,     0,     0,     0,   365,     0,     0,     0,
       0,     0,     0,     0,   366,     0,     0,     0,     0,     0,
       0,   367,     0,     0,   368,     0,     0,   369,     0,     0,
       0,   370,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   371,     0,     0,   372,   373,     0,   200,   201,   202,
       0,   204,   205,   206,   207,   208,   374,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,     0,   222,
     223,   224,     0,     0,   227,   228,   229,   230,   375,   376,
     377,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   378,   379,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   380,     0,    59,     0,     0,
       0,     0,     0,     0,     0,   381,   382,   383,   384,   385,
       0,   386,     0,   387,   388,   389,   390,   391,   392,   393,
     394,    60,   194,     0,   395,     0,   471,   472,   195,     0,
       0,     0,     0,     0,   196,     0,     0,     0,     0,     0,
     396,   397,   398,   473,    15,   197,     0,   399,   400,     0,
       0,     0,     0,   198,     0,     0,   401,     0,   402,     0,
     403,   404,     0,     0,     0,     0,     0,     0,   199,     0,
       0,     0,     0,     0,     0,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,     0,     0,
       0,     0,     0,     0,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   485,   486,   487,   488,   489,
     490,   491,   626,   627,   492,   493,   494,     0,     0,   495,
     496,   497,   498,   499,     0,    59,     0,     0,   500,   501,
     502,   503,   504,   505,   506,     0,     0,     0,   233,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   674,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   507,     0,   508,   509,   510,   511,   512,
     513,   514,   515,   516,   517,     0,     0,   518,   519,     0,
       0,     0,     0,     0,   807,   520,   521,     0,   234,     0,
     626,   627,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   628,   629,
     630,   631,   632,     0,     0,   633,   634,   635,   636,     0,
     637,   638,   639,   640,   641,     0,   642,   643,     0,     0,
     644,     0,     0,     0,   645,   646,   647,   200,   201,   202,
     648,   204,   205,   206,   207,   208,   374,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,     0,   222,
     223,   224,     0,     0,   227,   228,   229,   230,     0,   649,
       0,   650,   651,   652,   653,   654,   655,   656,   657,   658,
     659,   626,   627,     0,     0,     0,   628,   629,   630,   631,
     632,   660,   661,   633,   634,   635,   636,     0,   637,   638,
     639,   640,   641,     0,   642,   643,     0,     0,  -857,     0,
     626,   627,   645,   646,   647,     0,     0,     0,  -857,     0,
       0,     0,   808,     0,     0,     0,     0,     0,     0,     0,
       0,   809,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   649,     0,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   660,
     661,     0,     0,     0,     0,     0,     0,   628,   629,   630,
     631,   632,     0,     0,   633,   634,   635,   636,     0,   637,
     638,   639,   640,   641,     0,   642,   643,   626,   627,     0,
       0,     0,     0,   645,   646,   647,   628,   629,   630,   631,
     632,     0,     0,   633,   634,   635,   636,     0,   637,   638,
     639,   640,   641,     0,   642,   643,   626,   627,     0,     0,
       0,     0,   645,     0,     0,     0,     0,     0,   649,     0,
     650,   651,   652,   653,   654,   655,   656,   657,   658,   659,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     660,   661,     0,     0,     0,     0,     0,     0,     0,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   660,
     661,     0,     0,   628,   629,   630,   631,   632,     0,     0,
     633,   634,   635,   636,     0,   637,   638,   639,   640,   641,
       0,   642,   643,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   628,   629,   630,   631,   632,     0,     0,   633,
       0,     0,   636,     0,   637,   638,   639,   640,   641,     0,
     642,   643,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   811,     0,     0,     0,     0,   653,
     654,   655,   656,   657,   658,   659,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   660,   661,     0,     0,
       0,     0,     0,     0,     0,  1064,     0,     0,   653,   654,
     655,   656,   657,   658,   659,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   660,   661,   200,   201,   202,
       0,   204,   205,   206,   207,   208,   374,   210,   211,   212,
     213,   214,   215,   216,   217,   218,   219,   220,     0,   222,
     223,   224,     0,     0,   227,   228,   229,   230,   200,   201,
     202,     0,   204,   205,   206,   207,   208,   374,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,     0,
     222,   223,   224,     0,     0,   227,   228,   229,   230,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   812,     0,   307,     0,     0,     0,   200,   201,
     202,   813,   204,   205,   206,   207,   208,   374,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,     0,
     222,   223,   224,  1065,     0,   227,   228,   229,   230,     0,
       0,   308,  1066,   309,     0,   310,   311,   312,   313,   314,
       0,   315,   316,   317,   318,   319,   320,   321,   322,   323,
     324,   325,     0,   326,   327,   328,   850,   851,   329,   330,
     331,   332,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   333,   334,
       0,     0,     0,   852,     0,     0,     0,     0,     0,   308,
       0,   309,   853,   310,   311,   312,   313,   314,     0,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   324,   325,
       0,   326,   327,   328,     0,     0,   329,   330,   331,   332,
       0,     0,     0,     0,     0,   335,   854,   855,   308,     0,
     309,     0,   310,   311,   312,   313,   314,     0,   315,   316,
     317,   318,   319,   320,   321,   322,   323,   324,   325,     0,
     326,   327,   328,     0,     0,   329,   330,   331,   332,     0,
       0,     0,   308,     0,   309,     0,   310,   311,   312,   313,
     314,     0,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   697,   326,   327,   328,     0,     0,   329,
     330,   331,   332,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   699,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   889
};

static const yytype_int16 yycheck[] =
{
       1,   104,   283,    15,    16,   141,   146,   147,   360,   360,
     729,   725,   173,   611,   612,  1368,   549,   879,   995,  1018,
      21,    22,    23,  1001,   440,   295,   442,   402,   444,   696,
     141,   615,   695,  1150,   929,  1230,   669,     8,   671,   798,
     673,   766,   471,   472,  1565,    33,   769,  1331,    20,  1337,
      51,    82,   806,    65,    66,    67,  1105,   193,    20,    19,
    1622,  1622,  1653,  1622,  1622,     7,   176,   128,    22,    40,
     141,     0,  1622,   127,   449,  1124,    20,   140,     7,   127,
     127,     5,   193,   154,   127,   683,  1551,   127,   183,    20,
     141,  1682,   202,   105,   106,   107,   108,    47,   183,    33,
     141,    30,   159,    32,    58,    34,    19,    20,   203,    51,
     178,    40,    41,   154,    15,    16,   177,   127,   203,   180,
     130,   131,    51,  1685,  1685,   179,  1685,  1685,    57,   141,
     184,   179,   179,   204,  1537,  1685,   179,   184,  1116,   179,
     142,   184,   205,   206,   184,   208,  1549,   680,  1613,   203,
     201,   684,    81,    34,  1507,   753,   203,   107,   756,  1669,
     203,   745,   176,   203,  1726,  1726,   764,  1726,  1726,   767,
    1454,  1455,   151,   166,   103,   104,  1726,   179,    63,   103,
     104,   193,  1692,    64,   295,   346,  1470,   166,  1472,  1477,
     200,   201,   168,   207,   182,   570,   177,   168,   338,  1602,
    1603,  1179,  1723,   343,   176,   580,  1183,   347,   583,   876,
     873,  1210,   205,   797,   176,   176,  1737,   353,   354,   355,
     939,   754,   234,   183,   203,   979,   257,   108,    15,    16,
     201,   207,   176,   958,   188,  1284,   959,  1099,   209,   168,
     615,   242,   353,   354,   355,   176,   200,     8,   182,   168,
    1009,  1300,   133,   166,   151,   256,  1540,  1541,   159,   183,
     189,   142,  1350,   164,   128,   166,  1550,   201,   169,   166,
     134,   128,   201,   543,   703,    36,   210,   134,   207,   203,
     176,   130,   131,   295,   203,   166,   179,   662,    21,    22,
      46,   168,   644,   644,   176,   143,   144,   145,  1386,   435,
     436,   571,  1061,   439,   151,   441,   203,   443,   204,     5,
       6,  1506,   193,   177,  1073,   451,   586,   348,  1213,   166,
     177,   168,   203,   142,   435,   436,   203,    12,   439,    25,
     441,    87,   443,   166,   445,    31,   157,  1336,    23,    24,
     451,   353,   354,   355,   877,   166,  1463,   166,   360,   361,
     983,   200,   201,   140,   176,   128,   204,   188,   774,   176,
     207,   134,   209,   176,   128,  1718,   950,   184,   380,   200,
     745,  1370,   159,    69,    70,   131,   132,   164,   134,   166,
     202,  1014,   169,   204,   117,   118,   119,   120,   804,   128,
     207,   204,   166,   166,   127,   134,   129,   130,   131,   132,
     133,   541,   135,   136,   177,   142,  1004,   103,   104,   182,
     176,  1130,   176,   177,   128,   179,   203,   166,   182,   168,
     134,   954,   168,   435,   436,   168,   151,   439,   142,   441,
    1189,   443,   543,   445,   180,   151,   202,    58,   177,   451,
     166,   166,  1109,    64,  1107,   978,   142,   108,    33,     8,
     166,   128,   185,   186,   187,   188,   189,   134,   207,   176,
     571,   207,  1440,   177,   207,   128,   209,   200,   201,   149,
     166,   134,   742,   743,   614,   586,    61,    62,   203,   151,
      21,    22,   752,   208,   149,   202,   166,   183,   758,   759,
     203,   761,   159,   763,   166,   765,  1255,    56,    57,    58,
     177,   166,   188,   773,   157,   201,   176,  1266,   188,   189,
     176,  1489,   208,   166,   177,   626,   627,   167,   168,   142,
     200,    65,    66,    67,   189,  1502,   176,    33,   151,   188,
     641,   543,   202,   156,   184,   200,   151,   176,   204,   157,
     125,   176,   176,   166,   129,   176,   682,    58,   166,   660,
     203,   166,   176,    64,   176,    61,    62,   207,   177,   571,
     183,   105,   106,   107,   108,   204,   167,   168,   176,   204,
     204,   682,   176,   204,   586,   176,   712,   713,   119,   120,
     204,   168,   204,   184,   695,   176,   127,   176,   129,   130,
     131,   132,   133,   178,   167,   168,   204,   182,   202,   184,
     185,   712,   713,   176,   616,   741,   207,   180,   744,   167,
     168,   176,   748,   204,  1147,   204,   176,  1250,   176,   125,
     151,   176,   170,   129,   179,   210,   184,   182,  1627,   166,
     741,   742,   743,   744,   207,   166,   176,   748,   183,   204,
    1056,   752,   202,   176,   167,   168,   166,   758,   759,   207,
     761,   166,   763,   176,   765,   766,   166,  1416,   203,   200,
     201,   184,   773,   176,   204,  1664,  1425,   176,   938,    58,
     682,   204,   178,   167,   168,    64,   182,   166,   184,   185,
     167,   168,   176,   695,   207,   108,  1061,   957,   108,   176,
     184,   204,   183,   963,   176,   204,   176,   184,  1073,   183,
     712,   713,   166,  1078,   210,  1704,   176,   977,   720,   157,
     208,   176,   203,   207,    21,    22,   167,   168,   166,   203,
     207,   200,   204,   179,   204,   176,   182,   838,   729,   741,
     742,   743,   744,   184,   204,   871,   748,  1632,   874,   204,
     752,   167,   168,   176,   880,   176,   758,   759,   176,   761,
     176,   763,    48,   765,   766,   142,   207,   166,   184,   157,
     871,   773,   873,   874,   151,    80,   183,   166,   166,   880,
     177,   204,    68,   204,   270,   193,   204,  1536,  1537,   166,
      95,   207,   157,  1542,   280,   100,   203,   102,   179,   179,
    1549,   166,  1551,   183,  1169,   166,   167,   293,   167,   168,
     157,  1176,  1697,   170,   805,   176,   143,   176,   145,   166,
     117,   118,   119,   120,   121,   184,   168,   124,   125,   126,
     127,    33,   129,   130,   131,   132,   133,   938,   135,   136,
     166,   167,   143,   167,  1729,    33,  1595,   166,   207,   141,
     176,    33,   176,  1602,  1603,   176,   957,   958,   179,    61,
      62,   182,   963,   180,  1613,    58,   180,   184,  1572,   871,
     184,   873,   874,    61,    62,    58,   977,   183,   880,    61,
      62,    64,    67,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,    58,   183,   886,  1026,   888,   183,    64,
    1242,  1242,    58,   200,   201,    58,    76,   203,    64,   180,
      80,    64,   203,   184,   180,    21,    22,   180,   184,   183,
    1629,   184,   183,   125,    94,    95,  1675,   129,   183,    99,
     100,   101,   102,   183,   180,   180,   938,   125,   184,   184,
     128,   129,   183,   125,   180,   183,   134,   129,   184,   417,
     418,   942,   420,   421,   180,   957,   958,  1666,   184,   180,
    1548,   963,   201,   184,   180,   183,   452,   167,   184,   170,
     171,   172,   173,     5,     6,   977,   178,   107,   464,   203,
     182,   179,   184,   185,   141,   418,  1351,   420,   421,   177,
     178,  1251,   207,   208,   182,   166,   178,   185,   170,   171,
     182,   180,   184,   185,    10,    11,  1107,   166,   210,  1597,
     183,   117,   118,   119,   120,   121,  1220,  1221,   124,   125,
     126,   127,   210,   129,   130,   131,   132,   133,   210,   135,
     136,   167,  1023,   139,  1164,   201,    35,   143,   144,   145,
    1031,  1032,    35,   149,   143,   144,   145,   170,   171,   172,
     170,   171,   172,  1044,   208,  1046,  1047,  1048,  1049,  1050,
     921,   922,   923,  1054,   208,   203,   166,   183,  1198,   183,
     183,   203,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   203,   183,   572,   573,   183,   183,
     576,   203,   578,   183,   200,   201,   183,   204,   203,   203,
     203,   203,  1467,   204,   184,  1107,   203,   203,   594,   595,
     596,   597,   598,   599,   203,   201,  1107,   166,  1109,   203,
     176,   204,   204,   202,   202,  1490,   166,  1253,   202,    22,
    1121,   208,   166,   202,   139,   208,   179,   166,   184,  1130,
     203,  1132,   183,   203,   183,   183,    21,    22,   183,   203,
    1251,    19,  1253,   639,    13,  1306,   203,    25,   202,   176,
       4,   203,   166,    31,   166,   179,   202,   204,    44,  1295,
     203,   166,   183,   176,    42,   661,   207,   204,   208,   203,
     202,   204,    50,   204,   204,   204,   204,   183,   204,   204,
    1461,   204,   204,   203,  1295,   204,   204,    65,     1,   184,
     184,   202,   688,   203,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   203,   203,   203,
      21,    22,   203,   203,   119,   120,  1372,   733,   203,  1251,
     203,  1253,   127,   184,   129,   130,   131,   132,   133,   204,
    1625,   747,   203,   166,   166,    21,    22,   166,   204,   204,
     204,  1372,   204,   203,   142,   204,   204,   204,   204,   204,
    1410,   203,   203,   179,    44,   771,   772,   155,  1381,   166,
     204,   203,   203,  1295,  1420,   204,   782,   166,   166,   209,
     166,   787,    33,   789,   159,   791,    10,    13,     9,    43,
     796,   183,   187,   188,   189,    67,   203,   203,   202,  1420,
     203,  1312,   202,   166,   166,   200,   201,   177,    44,   203,
      61,    62,   177,   204,   204,  1337,   203,   205,   119,   120,
     204,    44,   210,   203,   166,   184,   127,   174,   129,   130,
     131,   132,   133,   166,   166,   204,   166,   203,   166,   166,
      14,   177,   177,   119,   120,   851,   159,   203,  1628,   855,
    1372,   127,   203,   179,   130,   131,   132,   133,   203,   209,
     204,   204,   166,   204,   204,     8,   166,  1378,   166,   203,
     209,   209,   203,    33,   125,   881,   184,    71,   129,   203,
     166,  1527,   204,   203,   185,   186,   187,   188,   189,   203,
      44,   203,   203,   203,    33,   204,   203,   203,  1420,   200,
     201,    61,    62,   166,   203,    37,  1527,   204,   203,   203,
     177,   917,   204,   204,   204,   204,   209,  1567,   203,    44,
     177,  1571,    61,    62,   200,   201,   209,   178,    68,   935,
     204,   182,   203,   184,   185,   941,   204,   203,  1449,   203,
     170,  1452,   203,   203,   166,   204,   166,   209,   204,   207,
      12,   204,   204,   208,   204,  1477,   204,   204,   964,   210,
     204,   378,   379,   204,   204,   125,   204,   204,   128,   129,
     204,   204,   207,   204,   134,   204,  1626,    33,   176,   396,
     397,   398,   399,   400,   176,   204,   125,   204,    21,    22,
     129,   204,   204,   204,   204,  1506,   204,   203,   207,   204,
     207,   204,   204,  1009,    54,  1527,   202,  1628,   168,   208,
    1016,   202,   209,  1019,   209,   203,   209,   177,   178,  1025,
     204,  1027,   182,    21,    22,   185,   208,   600,   167,   168,
     209,     1,    81,   192,  1736,   888,  1686,   176,    84,   178,
     888,  1734,  1221,   182,   616,   184,   185,   207,  1698,   263,
     210,  1125,  1058,   682,  1060,   620,  1062,     1,  1366,  1709,
    1591,  1636,  1594,  1530,    55,  1637,  1072,  1637,   207,  1300,
     340,   210,  1124,   360,  1080,  1124,   209,  1727,  1589,   360,
     572,   360,   360,   360,   117,   118,   119,   120,   121,    -1,
      -1,   124,   125,   126,   127,   360,   129,   130,   131,   132,
     133,    -1,   135,   136,    -1,    -1,  1628,    -1,    -1,    -1,
      -1,    -1,  1623,    -1,    -1,    -1,    -1,    -1,    -1,   117,
     118,   119,   120,   121,    -1,  1131,   124,   125,   126,   127,
      -1,   129,   130,   131,   132,   133,    -1,   135,   136,    -1,
      -1,    -1,    -1,    -1,  1150,   143,    -1,   145,   181,   182,
     183,   184,   185,   186,   187,   188,   189,  1668,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1172,   200,   201,    21,
      22,    -1,    -1,    -1,  1180,  1181,  1182,    -1,  1689,    -1,
    1691,    -1,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,  1703,  1199,  1705,    -1,  1202,    -1,    -1,    -1,
      -1,  1712,   200,   201,    -1,  1211,    -1,    -1,    -1,    -1,
      -1,   628,   629,    -1,    -1,   632,   633,   634,   635,  1730,
     637,  1732,    -1,   640,   641,   642,   643,   644,   645,   646,
     647,   648,   649,   650,   651,   652,   653,   654,   655,   656,
     657,   658,   659,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1261,    -1,  1263,    -1,    -1,
      -1,    -1,    -1,    -1,  1270,   117,   118,   119,   120,   121,
      -1,    -1,   124,   125,   126,   127,  1282,   129,   130,   131,
     132,   133,    -1,   135,   136,    -1,  1292,    -1,    -1,    -1,
      -1,  1297,    -1,  1299,    -1,    -1,    -1,    -1,   715,    -1,
      -1,    -1,  1308,    -1,    -1,  1311,    -1,    -1,    -1,    -1,
      -1,    -1,  1318,    -1,    -1,    -1,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,    -1,  1335,
     182,   183,   184,   185,   186,   187,   188,   189,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    62,  1352,  1353,   200,   201,
      -1,    -1,    -1,    -1,    61,    62,    -1,    -1,    -1,   109,
     110,   111,   112,   113,   114,   115,   116,  1373,    -1,    -1,
      -1,    19,    -1,  1379,  1380,    -1,    -1,    25,    -1,  1385,
      -1,    -1,    -1,    31,   134,    -1,    -1,    -1,   805,    -1,
      -1,    -1,    -1,    -1,    42,    -1,   146,   147,   148,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,   125,    -1,
    1416,    -1,   129,    -1,    -1,    -1,    -1,    65,   125,  1425,
      -1,    -1,   129,    -1,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,  1463,  1464,  1465,
    1466,   178,    10,    -1,    -1,   182,    -1,   184,   185,    -1,
      -1,   178,    -1,    21,    22,   182,    -1,  1483,   185,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   210,   142,    -1,    -1,  1503,    -1,    -1,
      -1,    -1,    -1,   210,    -1,    -1,    -1,   155,    -1,    -1,
     927,    -1,  1518,    33,    -1,  1521,    -1,  1523,   166,    -1,
     168,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1539,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    62,    -1,    -1,    -1,    -1,    -1,    -1,  1555,
      -1,    -1,    -1,    -1,  1560,  1561,    -1,   205,    -1,   207,
      -1,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,    -1,    -1,    -1,   143,   144,   145,   146,   147,
     148,   149,    -1,    -1,    -1,   125,    -1,    -1,    -1,   129,
      -1,  1617,    -1,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,
     178,    -1,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,    -1,    61,    62,    -1,    -1,    -1,  1654,    -1,
      -1,  1068,   200,   201,    -1,    -1,    -1,    33,   178,    -1,
      19,  1667,   182,    -1,   184,   185,    25,    -1,    -1,    -1,
      -1,    -1,    31,  1679,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1688,    42,    -1,    61,    62,    -1,    -1,    -1,
     210,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1121,    -1,    65,   125,  1714,    -1,
      -1,   129,    -1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,    -1,    -1,    33,   125,
      -1,    -1,    -1,   129,    -1,    -1,    -1,    -1,    -1,    -1,
     178,    -1,    -1,    -1,   182,    -1,   184,   185,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    -1,    -1,
      -1,    -1,    -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   210,    -1,    -1,    -1,   155,    -1,    -1,    -1,
      -1,    -1,   178,    -1,    -1,    -1,   182,   166,   184,   185,
      -1,    -1,    -1,    -1,    -1,  1232,  1233,  1234,  1235,  1236,
    1237,  1238,  1239,  1240,  1241,  1242,  1243,  1244,  1245,  1246,
    1247,  1248,  1249,     1,   210,    -1,    -1,     5,     6,     7,
     125,     9,    10,    11,   129,    13,   205,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,    -1,    25,    26,    27,
      28,    29,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    -1,    -1,    43,    -1,    45,    46,    -1,
      -1,    49,    -1,    51,    52,    53,    -1,    55,    56,    -1,
      -1,    59,    60,   178,    -1,    -1,    -1,   182,    66,   184,
     185,    69,    70,    -1,    72,    73,    74,    -1,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,   210,    94,    95,    96,    -1,
      -1,    99,   100,   101,   102,   103,   104,   105,   106,   109,
     110,   111,   112,   113,   114,   115,   116,    -1,    -1,    -1,
      -1,   119,   120,    -1,    -1,    -1,    -1,    -1,   128,    -1,
      -1,  1378,    -1,    -1,   134,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   140,    -1,   142,    -1,   146,   147,   148,    -1,
      -1,    -1,   150,   151,   152,   153,   154,    -1,   156,    -1,
     158,   159,   160,   161,   162,   163,   164,   165,   166,    -1,
     168,   169,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   185,   186,   187,
      -1,   189,    33,    -1,   192,   193,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   201,    -1,   203,    -1,   205,   206,   207,
     208,   209,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    62,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,     5,     6,     7,    -1,     9,    10,    11,    -1,    13,
      -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    25,    26,    27,    28,    29,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    -1,    -1,    43,
      -1,    45,    46,    -1,    -1,    49,    -1,    51,    52,    53,
      -1,    55,    56,    -1,   125,    59,    60,    -1,   129,    -1,
      -1,    -1,    66,    -1,    -1,    69,    70,    -1,    72,    73,
      74,    -1,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      94,    95,    96,    -1,    -1,    99,   100,   101,   102,   103,
     104,   105,   106,    -1,    -1,    -1,    -1,   178,    -1,    -1,
      -1,   182,    -1,   184,   185,   119,   120,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   140,    -1,   142,   210,
      -1,    -1,    -1,    -1,    -1,  1622,   150,   151,   152,   153,
     154,    -1,   156,    -1,   158,   159,   160,   161,   162,   163,
     164,   165,   166,    -1,   168,   169,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   185,   186,   187,    -1,   189,    -1,    -1,   192,   193,
      -1,  1668,    -1,    -1,    -1,    61,    62,   201,    -1,   203,
      -1,   205,   206,   207,   208,   209,     1,    -1,  1685,    -1,
       5,     6,     7,    -1,     9,    10,    11,    -1,    13,    -1,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    26,    27,    28,    29,  1712,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    -1,    -1,    43,  1726,
      45,    46,    -1,    -1,    49,  1732,    51,    52,    53,   125,
      55,    56,    -1,   129,    59,    60,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    69,    70,    -1,    72,    73,    74,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    -1,    94,
      95,    96,    -1,    -1,    99,   100,   101,   102,   103,   104,
     105,   106,   178,    -1,    -1,    -1,   182,    -1,   184,   185,
      -1,    -1,    -1,    -1,   119,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   210,   140,    -1,   142,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   150,   151,   152,   153,   154,
      -1,   156,    -1,   158,   159,   160,   161,   162,   163,   164,
     165,   166,    -1,   168,   169,    -1,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     185,   186,   187,    -1,   189,    -1,    -1,   192,   193,    -1,
      -1,    -1,    -1,    -1,    61,    62,   201,    -1,   203,    -1,
     205,   206,   207,   208,   209,     1,    -1,    -1,    -1,     5,
       6,     7,    -1,     9,    10,    11,    -1,    13,    -1,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,
      26,    27,    28,    29,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    -1,    -1,    43,    -1,    45,
      46,    -1,    -1,    49,    -1,    51,    52,    53,   125,    55,
      56,    -1,   129,    59,    60,    -1,    -1,    -1,    -1,    -1,
      66,    -1,    -1,    69,    70,    -1,    72,    73,    74,    -1,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    -1,    94,    95,
      96,    -1,    -1,    99,   100,   101,   102,   103,   104,   105,
     106,   178,    -1,    -1,    -1,   182,    -1,   184,   185,    -1,
      -1,    -1,    -1,   119,   120,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   210,   140,    -1,   142,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   150,   151,   152,   153,   154,    -1,
     156,    -1,   158,   159,   160,   161,   162,   163,   164,   165,
     166,    -1,   168,   169,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   185,
     186,   187,    -1,   189,    -1,    -1,   192,   193,    -1,    -1,
      -1,    -1,    -1,    61,    62,   201,    -1,   203,    -1,   205,
     206,   207,   208,   209,     1,    -1,    -1,    -1,     5,     6,
       7,    -1,     9,    10,    11,    -1,    13,    -1,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,    26,
      27,    28,    29,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    -1,    -1,    43,    -1,    45,    46,
      -1,    -1,    49,    -1,    51,    52,    53,   125,    55,    56,
      -1,   129,    59,    60,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    69,    70,    -1,    72,    73,    74,    -1,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    -1,    94,    95,    96,
      -1,    -1,    99,   100,   101,   102,   103,   104,   105,   106,
     178,    -1,    -1,    -1,   182,    -1,   184,   185,    -1,    -1,
      -1,    -1,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   210,   140,    -1,   142,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   150,   151,   152,   153,   154,    -1,   156,
      -1,   158,   159,   160,   161,   162,   163,   164,   165,   166,
      -1,   168,   169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   185,   186,
     187,    -1,   189,    -1,    -1,   192,   193,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   201,    -1,   203,    -1,   205,   206,
     207,   208,   209,     1,    -1,    -1,    -1,     5,     6,     7,
      -1,     9,    10,    11,    -1,    13,    -1,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,    -1,    25,    26,    27,
      28,    29,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    -1,    -1,    43,    -1,    45,    46,    -1,
      -1,    49,    -1,    51,    52,    53,    -1,    55,    56,    -1,
      -1,    59,    60,    -1,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    69,    70,    -1,    72,    73,    74,    -1,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    -1,    94,    95,    96,    -1,
      -1,    99,   100,   101,   102,   103,   104,   105,   106,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   140,    -1,   142,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   150,   151,   152,   153,   154,    -1,   156,    -1,
     158,   159,   160,   161,   162,   163,   164,   165,   166,    -1,
     168,   169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   185,   186,   187,
      -1,   189,    -1,    -1,   192,   193,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   201,    -1,   203,    -1,   205,   206,   207,
     208,   209,     5,     6,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    49,    -1,    -1,    52,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    69,    70,    71,    72,
      73,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      -1,    94,    95,    96,    -1,    -1,    99,   100,   101,   102,
     103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   128,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,    -1,   142,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,   151,   152,
     153,   154,    -1,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   185,   186,   187,    -1,   189,    -1,    -1,   192,
     193,    -1,    -1,    -1,    -1,    -1,     5,     6,   201,    -1,
     203,   204,   205,   206,    13,   208,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    50,    -1,    52,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      69,    70,    -1,    72,    73,    74,    -1,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    -1,    94,    95,    96,    -1,    -1,
      99,   100,   101,   102,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   128,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   140,    -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   150,   151,   152,   153,   154,    -1,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,    -1,    -1,
     169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   185,   186,   187,    -1,
     189,    -1,    -1,   192,   193,    -1,    -1,    -1,    -1,    -1,
       5,     6,   201,    -1,   203,    -1,   205,   206,    13,   208,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    49,    50,    -1,    52,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    69,    70,    -1,    72,    73,    74,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    -1,    94,
      95,    96,    -1,    -1,    99,   100,   101,   102,   103,   104,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   119,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   128,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   140,    -1,   142,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   150,   151,   152,   153,   154,
      -1,   156,    -1,   158,   159,   160,   161,   162,   163,   164,
     165,   166,    -1,    -1,   169,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     185,   186,   187,    -1,   189,    -1,    -1,   192,   193,    -1,
      -1,    -1,    -1,    -1,     5,     6,   201,    -1,   203,    -1,
     205,   206,    -1,   208,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    -1,
      -1,    52,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    69,    70,
      71,    72,    73,    74,    -1,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    -1,    94,    95,    96,    -1,    -1,    99,   100,
     101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   128,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,
      -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,
     151,   152,   153,   154,    -1,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,    -1,    -1,   169,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   185,   186,   187,    -1,   189,    -1,
      -1,   192,   193,    -1,    -1,    -1,    -1,    -1,     5,     6,
     201,    -1,   203,    -1,   205,   206,    -1,   208,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    49,    -1,    -1,    52,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    69,    70,    -1,    72,    73,    74,    -1,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    -1,    94,    95,    96,
      -1,    -1,    99,   100,   101,   102,   103,   104,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   128,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   140,    -1,   142,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   150,   151,   152,   153,   154,    -1,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
      -1,    -1,   169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   185,   186,
     187,    -1,   189,    -1,    -1,   192,   193,    -1,    -1,    -1,
      -1,    -1,     5,     6,   201,    -1,   203,   204,   205,   206,
      -1,   208,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    49,    -1,    -1,    52,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    69,    70,    -1,    72,
      73,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      -1,    94,    95,    96,    -1,    -1,    99,   100,   101,   102,
     103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   128,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,    -1,   142,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,   151,   152,
     153,   154,    -1,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   185,   186,   187,    -1,   189,    -1,    -1,   192,
     193,    -1,    -1,    -1,    -1,    -1,     5,     6,   201,    -1,
     203,   204,   205,   206,    -1,   208,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    -1,    -1,    52,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      69,    70,    -1,    72,    73,    74,    -1,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    -1,    94,    95,    96,    -1,    -1,
      99,   100,   101,   102,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   128,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   140,    -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   150,   151,   152,   153,   154,    -1,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,    -1,    -1,
     169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   185,   186,   187,    -1,
     189,    -1,    -1,   192,   193,    -1,    -1,    -1,    -1,    -1,
       5,     6,   201,    -1,   203,    -1,   205,   206,    -1,   208,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    49,    -1,    -1,    52,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    69,    70,    -1,    72,    73,    74,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    -1,    94,
      95,    96,    -1,    -1,    99,   100,   101,   102,   103,   104,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   119,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   128,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   140,    -1,   142,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   150,   151,   152,   153,   154,
      -1,   156,    -1,   158,   159,   160,   161,   162,   163,   164,
     165,   166,    -1,    -1,   169,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     185,   186,   187,    -1,   189,    -1,    -1,   192,   193,    -1,
      -1,    -1,    -1,    -1,     5,     6,   201,    -1,   203,   204,
     205,   206,    -1,   208,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    -1,
      -1,    52,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    69,    70,
      -1,    72,    73,    74,    -1,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    -1,    94,    95,    96,    -1,    -1,    99,   100,
     101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   128,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,
      -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,
     151,   152,   153,   154,    -1,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,    -1,    -1,   169,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   185,   186,   187,    -1,   189,    -1,
      -1,   192,   193,    -1,    -1,    -1,    -1,    -1,     5,     6,
     201,    -1,   203,    -1,   205,   206,    -1,   208,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    49,    -1,    -1,    52,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    69,    70,    -1,    72,    73,    74,    -1,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    -1,    94,    95,    96,
      -1,    -1,    99,   100,   101,   102,   103,   104,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   128,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   140,    -1,   142,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   150,   151,   152,   153,   154,    -1,   156,
      -1,   158,   159,   160,   161,   162,   163,   164,   165,   166,
      -1,    -1,   169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   185,   186,
     187,    -1,   189,    -1,    -1,   192,   193,    -1,    -1,    -1,
      -1,    -1,     5,     6,   201,    -1,   203,   204,   205,   206,
      -1,   208,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    49,    -1,    -1,    52,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    69,    70,    -1,    72,
      73,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      -1,    94,    95,    96,    -1,    -1,    99,   100,   101,   102,
     103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   128,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,    -1,   142,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,   151,   152,
     153,   154,    -1,   156,    -1,   158,   159,   160,   161,   162,
     163,   164,   165,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   185,   186,   187,    -1,   189,    -1,    -1,   192,
     193,    -1,    -1,    -1,    -1,    -1,     5,     6,   201,    -1,
     203,   204,   205,   206,    -1,   208,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    -1,    -1,    52,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      69,    70,    -1,    72,    73,    74,    -1,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    -1,    94,    95,    96,    -1,    -1,
      99,   100,   101,   102,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   128,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   140,    -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   150,   151,   152,   153,   154,    -1,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,    -1,    -1,
     169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   185,   186,   187,    -1,
     189,    -1,    -1,   192,   193,    -1,    -1,    -1,    -1,    -1,
       5,     6,   201,    -1,   203,    -1,   205,   206,    -1,   208,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    49,    -1,    -1,    52,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    69,    70,    -1,    72,    73,    74,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    -1,    94,
      95,    96,    -1,    -1,    99,   100,   101,   102,   103,   104,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   119,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   128,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   140,    -1,   142,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   150,   151,   152,   153,   154,
      -1,   156,    -1,   158,   159,   160,   161,   162,   163,   164,
     165,   166,    -1,    -1,   169,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     185,   186,   187,    -1,   189,    -1,    -1,   192,   193,    -1,
      -1,    -1,    -1,    -1,     5,     6,   201,    -1,   203,    -1,
     205,   206,    -1,   208,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    -1,
      -1,    52,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    69,    70,
      -1,    72,    73,    74,    -1,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    -1,    94,    95,    96,    -1,    -1,    99,   100,
     101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,
      -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,
     151,   152,   153,   154,    -1,   156,    -1,   158,   159,   160,
     161,   162,   163,   164,   165,   166,    -1,    -1,   169,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   185,   186,   187,    -1,   189,    -1,
      -1,   192,   193,    -1,    -1,    -1,    -1,    -1,     5,     6,
     201,   202,   203,    -1,   205,   206,    -1,   208,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    49,    -1,    -1,    52,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    69,    70,    -1,    72,    73,    74,    -1,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    -1,    94,    95,    96,
      -1,    -1,    99,   100,   101,   102,   103,   104,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   140,    -1,   142,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   150,   151,   152,   153,   154,    -1,   156,
      -1,   158,   159,   160,   161,   162,   163,   164,   165,   166,
      -1,    -1,   169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   185,   186,
     187,    -1,   189,    -1,    -1,   192,   193,    -1,    -1,    -1,
      -1,    -1,     5,     6,   201,   202,   203,    -1,   205,   206,
      -1,   208,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    49,    -1,    -1,    52,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    69,    70,    -1,    72,
      73,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      -1,    94,    95,    96,    -1,    -1,    99,   100,   101,   102,
     103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   128,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,    -1,   142,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,   151,   152,
     153,   154,    -1,   156,    -1,   158,   159,   160,   161,   162,
     163,   164,   165,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   185,   186,   187,    -1,   189,    -1,    -1,   192,
     193,    -1,    -1,    -1,    -1,    -1,     5,     6,   201,    -1,
     203,    -1,   205,   206,    13,   208,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    -1,    -1,    52,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      69,    70,    -1,    72,    73,    74,    -1,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    -1,    94,    95,    96,    -1,    -1,
      99,   100,   101,   102,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   140,    -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   150,   151,   152,   153,   154,    -1,   156,    -1,   158,
     159,   160,   161,   162,   163,   164,   165,   166,    -1,    -1,
     169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   185,   186,   187,    -1,
     189,    -1,    -1,   192,   193,    -1,    -1,    -1,    -1,    -1,
       5,     6,   201,    -1,   203,    -1,   205,   206,    -1,   208,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    49,    -1,    -1,    52,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    69,    70,    -1,    72,    73,    74,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    -1,    94,
      95,    96,    -1,    -1,    99,   100,   101,   102,   103,   104,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   119,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   128,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   140,    -1,   142,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   150,   151,   152,   153,   154,
      -1,   156,    -1,   158,   159,   160,   161,   162,   163,   164,
     165,   166,    -1,    -1,   169,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     185,   186,   187,    -1,   189,    -1,    -1,   192,   193,    -1,
      -1,    -1,    -1,    -1,     5,     6,   201,    -1,   203,    -1,
     205,   206,    -1,   208,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    -1,
      -1,    52,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    -1,    -1,    66,    -1,    -1,    69,    70,
      -1,    72,    73,    74,    -1,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    -1,    94,    95,    96,    -1,    -1,    99,   100,
     101,   102,   103,   104,   105,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,
      -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,
     151,   152,   153,   154,    -1,   156,    -1,   158,   159,   160,
     161,   162,   163,   164,   165,   166,    -1,    -1,   169,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   185,   186,   187,    -1,   189,    -1,
      -1,   192,   193,    -1,    -1,    -1,    -1,    -1,     5,     6,
     201,    -1,   203,    -1,   205,   206,    -1,   208,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    49,    -1,    -1,    52,    -1,    -1,    -1,    56,
      -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    69,    70,    -1,    72,    73,    74,    -1,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    -1,    94,    95,    96,
      -1,    -1,    99,   100,   101,   102,   103,   104,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   140,    -1,   142,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   150,   151,   152,   153,   154,    -1,   156,
      -1,   158,   159,   160,   161,   162,   163,   164,   165,   166,
      -1,    -1,   169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   185,   186,
     187,    -1,   189,    -1,    -1,   192,   193,    -1,    -1,    -1,
      -1,    -1,     5,     6,   201,    -1,   203,    -1,   205,   206,
      -1,   208,    15,    16,    17,    18,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    27,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    -1,    -1,    49,    -1,    -1,    52,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    69,    70,    -1,    72,
      73,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      -1,    94,    95,    96,    -1,    -1,    99,   100,   101,   102,
     103,   104,   105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   119,   120,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   128,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,    -1,   142,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,   151,   152,
     153,   154,    -1,   156,    -1,   158,   159,   160,   161,   162,
     163,   164,   165,   166,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   185,   186,   187,    -1,   189,    -1,    -1,   192,
     193,    -1,    -1,    -1,    -1,    -1,     5,     6,   201,    -1,
     203,    -1,   205,   206,    -1,   208,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    -1,    -1,    52,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      69,    70,    -1,    72,    73,    74,    -1,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    -1,    94,    95,    96,    -1,    -1,
      99,   100,   101,   102,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   140,    -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   150,   151,   152,   153,   154,    -1,   156,    -1,   158,
     159,   160,   161,   162,   163,   164,   165,   166,    -1,    -1,
     169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   185,   186,   187,    -1,
     189,    -1,    -1,   192,   193,    -1,    -1,    -1,    -1,    -1,
       5,     6,   201,    -1,   203,   204,   205,   206,    -1,   208,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    49,    -1,    -1,    52,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    69,    70,    -1,    72,    73,    74,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    -1,    94,
      95,    96,    -1,    -1,    99,   100,   101,   102,   103,   104,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   119,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   140,    -1,   142,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   150,   151,   152,   153,   154,
      -1,   156,    -1,   158,   159,   160,   161,   162,   163,   164,
     165,   166,    -1,    -1,   169,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     185,   186,   187,    -1,   189,    -1,    -1,   192,   193,    -1,
      -1,    -1,    -1,    -1,     5,     6,   201,    -1,   203,    -1,
     205,   206,    -1,   208,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    25,    26,    27,    28,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,    49,    -1,
      -1,    52,    53,    -1,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    69,    70,
      -1,    72,    73,    74,    -1,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    -1,    94,    95,    96,    -1,    -1,    99,   100,
     101,   102,   103,   104,   105,   106,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,   120,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   140,
      -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,
     151,   152,   153,   154,    -1,   156,    -1,   158,   159,   160,
     161,   162,   163,   164,   165,   166,    -1,    -1,   169,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   185,   186,   187,    -1,   189,    -1,
      -1,   192,   193,    -1,    -1,    -1,     5,     6,    -1,    -1,
     201,    -1,   203,    -1,   205,   206,    15,    16,    17,    18,
      19,    -1,    -1,    22,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    46,    -1,    -1,
      49,    -1,    -1,    52,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      69,    70,    -1,    72,    73,    74,    -1,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    -1,    94,    95,    96,    -1,    -1,
      99,   100,   101,   102,   103,   104,   105,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     119,   120,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   140,    -1,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   150,   151,   152,   153,   154,    -1,   156,    -1,   158,
     159,   160,   161,   162,   163,   164,   165,   166,    -1,    -1,
     169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   185,   186,   187,    -1,
     189,    -1,    -1,   192,   193,    -1,    -1,    -1,     5,     6,
      -1,    -1,   201,    -1,   203,    -1,   205,   206,    15,    16,
      17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    49,    -1,    -1,    52,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    69,    70,    -1,    72,    73,    74,    -1,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    -1,    94,    95,    96,
      -1,    -1,    99,   100,   101,   102,   103,   104,   105,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   119,   120,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   128,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   140,    -1,   142,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   150,   151,   152,   153,   154,    -1,   156,
      -1,   158,   159,   160,   161,   162,   163,   164,   165,   166,
      -1,    -1,   169,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   185,   186,
     187,    -1,   189,    -1,    -1,   192,   193,    -1,    -1,    -1,
       5,     6,    -1,    -1,   201,    -1,   203,    -1,   205,   206,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    49,    -1,    -1,    52,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    69,    70,    -1,    72,    73,    74,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    -1,    94,
      95,    96,    -1,    -1,    99,   100,   101,   102,   103,   104,
     105,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   119,   120,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   140,    -1,   142,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   150,   151,   152,   153,   154,
      -1,   156,    -1,   158,   159,   160,   161,   162,   163,   164,
     165,   166,    19,    -1,   169,    -1,    21,    22,    25,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
     185,   186,   187,    38,   189,    42,    -1,   192,   193,    -1,
      -1,    -1,    -1,    50,    -1,    -1,   201,    -1,   203,    -1,
     205,   206,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,    -1,    -1,
      -1,    -1,    -1,    -1,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,    21,    22,   129,   130,   131,    -1,    -1,   134,
     135,   136,   137,   138,    -1,   142,    -1,    -1,   143,   144,
     145,   146,   147,   148,   149,    -1,    -1,    -1,   155,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   166,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   178,    -1,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,    -1,    -1,   192,   193,    -1,
      -1,    -1,    -1,    -1,    19,   200,   201,    -1,   205,    -1,
      21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,
     119,   120,   121,    -1,    -1,   124,   125,   126,   127,    -1,
     129,   130,   131,   132,   133,    -1,   135,   136,    -1,    -1,
     139,    -1,    -1,    -1,   143,   144,   145,    72,    73,    74,
     149,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    -1,    94,
      95,    96,    -1,    -1,    99,   100,   101,   102,    -1,   178,
      -1,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,    21,    22,    -1,    -1,    -1,   117,   118,   119,   120,
     121,   200,   201,   124,   125,   126,   127,    -1,   129,   130,
     131,   132,   133,    -1,   135,   136,    -1,    -1,   139,    -1,
      21,    22,   143,   144,   145,    -1,    -1,    -1,   149,    -1,
      -1,    -1,   157,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   178,    -1,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,
     201,    -1,    -1,    -1,    -1,    -1,    -1,   117,   118,   119,
     120,   121,    -1,    -1,   124,   125,   126,   127,    -1,   129,
     130,   131,   132,   133,    -1,   135,   136,    21,    22,    -1,
      -1,    -1,    -1,   143,   144,   145,   117,   118,   119,   120,
     121,    -1,    -1,   124,   125,   126,   127,    -1,   129,   130,
     131,   132,   133,    -1,   135,   136,    21,    22,    -1,    -1,
      -1,    -1,   143,    -1,    -1,    -1,    -1,    -1,   178,    -1,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     200,   201,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   200,
     201,    -1,    -1,   117,   118,   119,   120,   121,    -1,    -1,
     124,   125,   126,   127,    -1,   129,   130,   131,   132,   133,
      -1,   135,   136,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,   118,   119,   120,   121,    -1,    -1,   124,
      -1,    -1,   127,    -1,   129,   130,   131,   132,   133,    -1,
     135,   136,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,    -1,   183,
     184,   185,   186,   187,   188,   189,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   200,   201,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,   183,   184,
     185,   186,   187,   188,   189,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   200,   201,    72,    73,    74,
      -1,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    -1,    94,
      95,    96,    -1,    -1,    99,   100,   101,   102,    72,    73,
      74,    -1,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      94,    95,    96,    -1,    -1,    99,   100,   101,   102,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   157,    -1,    35,    -1,    -1,    -1,    72,    73,
      74,   166,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      94,    95,    96,   157,    -1,    99,   100,   101,   102,    -1,
      -1,    72,   166,    74,    -1,    76,    77,    78,    79,    80,
      -1,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    -1,    94,    95,    96,   130,   131,    99,   100,
     101,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,   120,
      -1,    -1,    -1,   157,    -1,    -1,    -1,    -1,    -1,    72,
      -1,    74,   166,    76,    77,    78,    79,    80,    -1,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      -1,    94,    95,    96,    -1,    -1,    99,   100,   101,   102,
      -1,    -1,    -1,    -1,    -1,   166,   200,   201,    72,    -1,
      74,    -1,    76,    77,    78,    79,    80,    -1,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    -1,
      94,    95,    96,    -1,    -1,    99,   100,   101,   102,    -1,
      -1,    -1,    72,    -1,    74,    -1,    76,    77,    78,    79,
      80,    -1,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,   166,    94,    95,    96,    -1,    -1,    99,
     100,   101,   102,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   166,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   166
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   212,     0,     7,    30,    32,    34,    40,    41,    51,
      57,    81,   103,   104,   168,   189,   201,   207,   214,   215,
     219,   228,   230,   231,   236,   285,   291,   322,   404,   412,
     413,   420,   430,   480,   485,   490,    19,    20,   166,   275,
     276,   277,   159,   237,   238,   178,   233,   234,    58,    64,
     409,   410,   409,   166,   205,   217,   491,   481,   486,   142,
     166,   310,    34,    64,   108,   133,   193,   203,   280,   281,
     282,   283,   310,   214,   214,   214,     8,    36,   431,    63,
     400,   177,   176,   179,   176,   149,   166,   189,   200,   232,
     232,   166,   214,   166,   400,   409,   409,   409,   166,   142,
     229,   282,   282,   282,   203,   143,   144,   145,   176,   202,
     108,   290,   421,     5,     6,   427,    58,    64,   401,    15,
      16,   140,   159,   164,   166,   169,   203,   221,   276,   159,
     238,   188,   188,   232,   188,   188,   200,    22,    58,   235,
     411,   177,    58,    64,   216,   166,   166,   166,   166,   170,
     227,   204,   277,   282,   282,   282,   282,   168,   242,   243,
      58,    64,   292,   294,    58,    64,   414,   108,   108,    58,
      64,   428,   208,   405,   166,   170,   171,   172,   220,    15,
      16,   159,   164,   166,   221,   273,   274,   232,   232,   232,
     166,   166,   166,   177,    19,    25,    31,    42,    50,    65,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   155,   205,   310,   435,   437,   438,   442,
     448,   450,   479,   193,   218,   179,   441,   243,   243,   170,
     204,   168,   295,   166,   415,   432,   402,   141,   278,   370,
     170,   171,   172,   176,   204,   235,   479,   183,   183,   183,
     203,   183,   183,   203,   441,   183,   183,   183,   183,   183,
     203,   310,   183,   203,    33,    61,    62,   125,   129,   178,
     182,   185,   210,   201,   447,   180,   214,    67,    80,    95,
     100,   102,   167,   418,   419,   482,   487,    35,    72,    74,
      76,    77,    78,    79,    80,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    94,    95,    96,    99,
     100,   101,   102,   119,   120,   166,   288,   289,   293,   179,
     416,   107,   425,   426,   209,   214,   403,   276,   141,   166,
     396,   399,   273,   451,   457,   459,     5,     6,    15,    16,
      17,    18,    19,    25,    27,    31,    39,    46,    49,    52,
      56,    66,    69,    70,    81,   103,   104,   105,   119,   120,
     140,   150,   151,   152,   153,   154,   156,   158,   159,   160,
     161,   162,   163,   164,   165,   169,   185,   186,   187,   192,
     193,   201,   203,   205,   206,   208,   226,   228,   302,   310,
     315,   327,   334,   337,   340,   344,   346,   348,   349,   351,
     356,   359,   360,   361,   368,   369,   435,   496,   504,   515,
     518,   531,   532,   535,   536,   461,   455,   166,   183,   463,
     465,   467,   469,   471,   473,   475,   477,   360,   183,   203,
     449,   453,   128,   307,   338,   360,    33,   182,    33,   182,
     201,   210,   202,   360,   201,   210,   448,   167,   492,   208,
     208,    21,    22,    38,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   129,   130,   131,   134,   135,   136,   137,   138,
     143,   144,   145,   146,   147,   148,   149,   178,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   192,   193,
     200,   201,    35,    35,   203,   286,   243,    76,    80,    94,
      95,    99,   100,   101,   102,   436,   419,   166,   243,   370,
     243,   276,   176,   179,   182,   394,   479,   479,   446,   479,
     183,   183,   183,   310,   312,   437,   495,   504,   515,   518,
     531,   532,   535,   536,   310,   183,     5,   103,   104,   183,
     203,   183,   203,   203,   183,   183,   203,   183,   203,   183,
     203,   183,   183,   203,    19,   183,   183,   361,   361,   151,
     156,   183,   310,   350,   203,   203,   203,   203,   203,   203,
     225,   361,   361,   361,   361,   361,    13,    50,   307,   157,
     166,   338,   497,   499,   530,   203,   201,   284,   140,   208,
     340,   345,   345,   345,   345,   204,    21,    22,   117,   118,
     119,   120,   121,   124,   125,   126,   127,   129,   130,   131,
     132,   133,   135,   136,   139,   143,   144,   145,   149,   178,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     200,   201,   203,   479,   479,   204,   184,   443,   479,   286,
     479,   286,   479,   286,   166,   383,   384,   479,   166,   386,
     387,   204,   454,   338,   309,   479,   360,   204,   176,   534,
     202,   202,   202,   360,   208,   483,   488,   166,   289,   166,
     289,   166,   202,    22,   166,   202,   154,   204,   370,   380,
     381,   382,   127,   179,   287,   139,   299,   300,   339,   208,
     179,   424,   433,   151,   166,   395,   398,   243,   166,   448,
     128,   134,   177,   393,   184,   184,   184,   167,   176,   213,
     214,   445,   505,   507,   313,   203,   183,   203,   335,   183,
     183,   183,   525,   338,   448,   360,   529,   360,   328,   330,
     360,   332,   360,   527,   338,   513,   516,   338,   183,   509,
     448,   203,   203,   352,   354,   360,   360,   360,   360,   360,
     360,   172,   173,   220,   203,    13,   202,   203,   128,   134,
     177,   389,   534,   176,   534,   204,   243,    71,   201,   204,
     338,   499,   283,     4,   343,   306,   284,    19,   157,   166,
     435,    19,   157,   166,   435,   361,   361,   361,   361,   361,
     361,   166,   361,   157,   166,   360,   361,   361,   435,   361,
     361,   361,   531,   536,   361,   361,   361,   361,    22,   361,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     130,   131,   157,   166,   200,   201,   357,   435,   360,   204,
     338,   184,   184,   166,   439,   184,   287,   184,   287,   184,
     287,   179,   184,   445,   179,   184,   445,   309,   534,   184,
     445,   128,   360,   202,   493,   383,   385,   386,   388,   166,
     289,   109,   110,   111,   112,   113,   114,   115,   116,   134,
     146,   147,   148,   109,   110,   111,   112,   113,   114,   115,
     116,   128,   134,   146,   147,   148,   177,   203,     7,    51,
     321,   207,   176,   207,   204,   479,   479,   128,   361,   208,
     422,   310,   207,   208,   429,   203,    44,   176,   179,   394,
     214,   393,   360,   452,   458,   460,   479,   448,   448,   479,
      71,   338,   499,   503,   166,   360,   479,   519,   521,   523,
     448,   534,   184,   445,   176,   534,   204,   448,   448,   204,
     448,   204,   448,   534,   448,   384,   534,   511,   387,   184,
     360,   360,   448,   286,   204,   204,   204,   204,   204,   204,
     360,   151,   166,   203,   264,   203,   360,   360,   360,   204,
     157,   166,    13,   308,   529,   166,   204,   499,   497,   176,
     204,   204,   202,   203,   286,     1,    26,    28,    29,    38,
      40,    45,    53,    55,    59,    60,    66,   106,   208,   209,
     214,   239,   240,   249,   260,   261,   263,   265,   266,   267,
     268,   269,   270,   271,   272,   303,   311,   316,   317,   318,
     319,   320,   322,   326,   347,   361,   343,   183,   203,   183,
     203,   203,   203,   202,    19,   157,   166,   435,   179,   157,
     166,   360,   203,   203,   157,   166,   360,     1,   203,   202,
     176,   204,   462,   456,   176,   184,   207,   464,   184,   468,
     184,   472,   184,   479,   476,   383,   479,   478,   386,   184,
     204,   449,   479,   360,   166,   440,   214,   250,   251,   250,
     251,   360,   151,   166,   390,   391,   434,   382,   382,   382,
     361,   306,   166,   406,   408,   376,   360,   166,   151,   166,
     448,   393,   360,   214,   184,   184,   184,   499,   204,   204,
     204,   184,   445,   204,   184,   448,   384,   387,   184,   204,
     203,   448,   360,   204,   184,   184,   184,   184,   204,   184,
     184,   204,   448,   184,   343,   204,   204,   184,   287,   203,
     179,   223,   203,    44,   166,   324,    20,   176,   264,   204,
     203,   134,   389,   203,   209,   534,   204,   176,   202,   201,
     497,   128,   134,   166,   177,   182,   341,   342,   287,   128,
     360,   299,    62,   360,   166,   166,   214,   159,    59,   360,
     243,   128,   360,   304,   214,   214,    10,    10,    11,   247,
      13,     9,    43,   214,   214,   214,   214,   214,   214,    67,
     323,   214,   109,   110,   111,   112,   113,   114,   115,   116,
     122,   123,   128,   134,   137,   138,   146,   147,   148,   177,
     286,   362,   360,   364,   360,   201,   204,   338,   497,   360,
     183,   203,   361,   203,   202,   360,   201,   204,   338,   497,
     203,   202,   358,   204,   338,   166,   444,   166,   466,   470,
     474,   449,   177,   213,   407,   417,   214,   383,   484,   386,
     489,   204,   203,    44,   176,   179,   182,   389,   301,   177,
     407,   417,    40,   168,   209,   285,   377,   204,   203,    44,
     214,   393,   360,   214,   506,   508,   314,   204,   203,   166,
     336,   184,   184,   184,   526,   308,   184,   329,   331,   333,
     528,   514,   517,   184,   510,   203,   243,   353,   184,   204,
     338,   224,   174,   360,   166,   176,   204,   338,   151,   166,
     203,    20,   134,   389,   360,   360,   360,   264,   204,   497,
     204,   166,   166,   203,   166,   166,   176,   204,   243,   360,
      14,   360,   177,   177,   179,   159,   299,   360,   306,   203,
     203,   201,   278,   279,   279,   203,   203,   208,   325,   398,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     361,   531,   536,   361,   361,   361,   361,   361,   361,   361,
     287,   448,   204,   479,   204,   497,   176,   204,   204,   204,
     366,   360,   360,   204,   497,   176,   204,   204,   360,   204,
     360,   166,   213,   494,   209,   209,   360,   166,   151,   166,
     479,   360,   209,   360,   406,   423,   166,     8,   370,   375,
     360,   166,   360,   214,   203,   203,   360,   184,   520,   522,
     524,   203,   204,   203,   203,   203,   203,   203,    71,   503,
     203,   512,   203,   204,   360,   299,   350,   355,   204,   222,
     204,   166,   204,   203,    44,   324,   338,   360,   360,   204,
      20,   202,   166,   341,   339,   299,   479,   360,   305,   360,
     360,   277,   203,   203,   360,   324,   397,   243,   184,   184,
     202,   497,   479,   204,   204,   202,   497,   204,   177,   209,
     204,   203,    44,   389,    37,   296,   209,   177,    58,    64,
     373,    68,   374,   214,   204,   214,   503,   503,   204,   203,
     203,   203,   203,   307,   308,   360,   360,   360,   338,   503,
     203,   503,   204,   350,   170,   207,   360,   166,   204,   204,
     134,   389,   338,   204,   204,   209,   204,   204,   202,   264,
     360,   204,   204,   209,   214,   398,   339,   363,   365,   204,
     204,   184,   204,   204,   360,   360,   166,   360,   297,   479,
      48,   374,    47,   107,   371,   203,   497,   500,   501,   502,
     502,   360,   503,   503,   497,   498,   204,   204,   204,   204,
     204,   534,   502,   503,   498,   360,   204,   207,   360,   360,
     204,   296,    12,   248,   243,    20,   204,   243,   179,   394,
     367,   204,   208,   214,    33,   372,   371,   373,   497,   176,
     534,   204,   204,   204,   502,   502,   204,   204,   204,   498,
     204,   207,   533,   360,   207,   249,   316,   317,   318,   319,
     361,   214,   262,   338,   243,   299,   448,   393,   306,   378,
     372,   390,   391,   392,   204,   203,   204,   204,   204,    54,
     202,   533,   360,   208,   252,   255,   204,   299,   393,   360,
     298,   293,   379,   497,   360,   202,   533,   253,    12,    23,
      24,   241,   244,   249,   243,   360,   214,   209,   214,   293,
     204,   209,   306,   243,   203,   214,   299,   214,   243,   254,
     245,   360,   339,   209,   208,   256,   259,   204,   296,   257,
     249,   243,   306,   214,   246,   258,   256,   209,   244,   296
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   211,   212,   212,   212,   212,   212,   212,   212,   212,
     212,   212,   212,   212,   212,   212,   212,   212,   213,   213,
     214,   214,   215,   216,   216,   216,   217,   217,   218,   218,
     219,   220,   220,   220,   220,   221,   221,   222,   222,   223,
     224,   223,   225,   225,   225,   226,   227,   227,   229,   228,
     230,   231,   232,   232,   232,   232,   232,   232,   232,   233,
     233,   234,   234,   235,   235,   236,   237,   237,   238,   238,
     239,   240,   240,   241,   241,   242,   242,   243,   243,   244,
     245,   244,   246,   244,   247,   247,   248,   248,   249,   249,
     249,   249,   249,   250,   250,   251,   251,   253,   254,   252,
     255,   252,   257,   258,   256,   259,   256,   261,   262,   260,
     263,   264,   264,   264,   264,   264,   264,   264,   264,   266,
     265,   267,   269,   268,   271,   270,   272,   272,   273,   273,
     273,   273,   273,   273,   274,   274,   275,   275,   275,   276,
     276,   276,   276,   276,   276,   276,   276,   276,   277,   277,
     278,   278,   279,   279,   279,   280,   280,   280,   280,   281,
     281,   282,   282,   282,   282,   282,   282,   282,   283,   283,
     284,   284,   285,   285,   286,   286,   286,   287,   287,   287,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   288,
     288,   288,   288,   288,   288,   288,   288,   288,   288,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   289,   289,   289,   289,   289,   289,
     289,   289,   289,   289,   290,   290,   291,   292,   292,   292,
     293,   295,   294,   296,   297,   298,   296,   300,   301,   299,
     302,   302,   302,   302,   303,   303,   303,   303,   303,   303,
     303,   303,   303,   303,   303,   303,   303,   303,   303,   303,
     303,   303,   303,   304,   305,   303,   306,   306,   306,   307,
     307,   308,   308,   309,   309,   310,   310,   310,   311,   311,
     313,   314,   312,   312,   315,   315,   315,   315,   315,   315,
     316,   317,   318,   318,   318,   319,   319,   320,   321,   321,
     321,   322,   322,   323,   323,   324,   324,   325,   325,   326,
     326,   326,   328,   329,   327,   330,   331,   327,   332,   333,
     327,   335,   336,   334,   337,   337,   337,   338,   338,   338,
     338,   339,   339,   339,   340,   340,   340,   341,   341,   341,
     341,   341,   342,   342,   343,   343,   344,   345,   345,   346,
     346,   346,   346,   346,   346,   346,   347,   347,   347,   347,
     347,   347,   347,   347,   347,   347,   347,   347,   347,   347,
     347,   347,   347,   347,   347,   347,   347,   348,   348,   348,
     349,   349,   349,   349,   349,   350,   350,   351,   352,   353,
     351,   354,   355,   351,   356,   356,   356,   356,   356,   356,
     356,   356,   356,   357,   358,   356,   359,   359,   359,   359,
     359,   359,   359,   360,   360,   360,   361,   361,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     361,   361,   362,   363,   361,   361,   361,   361,   364,   365,
     361,   361,   361,   366,   367,   361,   361,   361,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     361,   361,   368,   368,   368,   369,   369,   369,   369,   369,
     369,   369,   369,   369,   369,   369,   369,   369,   369,   369,
     369,   370,   370,   371,   371,   371,   372,   372,   373,   373,
     373,   374,   374,   375,   376,   376,   376,   377,   376,   378,
     376,   379,   376,   380,   381,   381,   382,   382,   382,   382,
     382,   383,   383,   384,   384,   385,   385,   385,   386,   387,
     387,   388,   388,   388,   389,   389,   390,   390,   390,   391,
     391,   392,   392,   393,   393,   393,   394,   394,   395,   395,
     395,   395,   395,   395,   396,   396,   397,   397,   397,   398,
     398,   398,   399,   399,   399,   400,   400,   401,   401,   401,
     402,   402,   403,   402,   404,   405,   404,   406,   406,   407,
     407,   408,   408,   408,   409,   409,   409,   411,   410,   412,
     413,   414,   414,   414,   415,   416,   416,   417,   417,   418,
     418,   419,   419,   421,   422,   423,   420,   424,   424,   425,
     425,   426,   427,   427,   427,   427,   428,   428,   428,   429,
     429,   431,   432,   433,   430,   434,   434,   434,   434,   434,
     434,   435,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   435,   435,   435,   435,   435,   435,   435,
     435,   435,   435,   435,   435,   435,   435,   435,   436,   436,
     436,   436,   436,   436,   436,   436,   437,   438,   438,   438,
     439,   439,   439,   440,   440,   440,   440,   440,   441,   441,
     441,   441,   441,   442,   443,   444,   442,   445,   445,   446,
     446,   447,   447,   447,   447,   448,   448,   449,   449,   450,
     450,   450,   450,   451,   452,   450,   450,   450,   450,   453,
     450,   454,   450,   450,   450,   450,   450,   450,   450,   450,
     450,   450,   450,   450,   450,   455,   456,   450,   450,   457,
     458,   450,   459,   460,   450,   461,   462,   450,   450,   463,
     464,   450,   465,   466,   450,   450,   467,   468,   450,   469,
     470,   450,   450,   471,   472,   450,   473,   474,   450,   475,
     476,   450,   477,   478,   450,   479,   479,   479,   481,   482,
     483,   484,   480,   486,   487,   488,   489,   485,   491,   492,
     493,   494,   490,   495,   495,   495,   495,   495,   495,   495,
     496,   496,   496,   496,   496,   497,   497,   497,   497,   497,
     497,   497,   497,   498,   498,   499,   500,   500,   501,   501,
     502,   502,   503,   503,   505,   506,   504,   507,   508,   504,
     509,   510,   504,   511,   512,   504,   513,   514,   504,   515,
     516,   517,   515,   518,   519,   520,   518,   521,   522,   518,
     523,   524,   518,   518,   525,   526,   518,   518,   527,   528,
     518,   529,   529,   530,   531,   532,   532,   532,   533,   533,
     534,   534,   535,   535,   536
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     2,     2,     2,     2,     2,     3,
       3,     2,     2,     2,     2,     2,     2,     2,     1,     1,
       1,     1,     2,     0,     1,     1,     1,     1,     0,     2,
       5,     1,     1,     2,     2,     3,     2,     0,     2,     0,
       0,     3,     0,     2,     5,     3,     1,     2,     0,     4,
       2,     2,     1,     2,     3,     3,     3,     3,     3,     0,
       2,     3,     5,     0,     1,     2,     1,     3,     1,     3,
       3,     3,     2,     1,     1,     1,     2,     0,     1,     0,
       0,     4,     0,     8,     1,     1,     0,     2,     1,     1,
       1,     1,     1,     1,     2,     0,     1,     0,     0,     6,
       0,     3,     0,     0,     6,     0,     3,     0,     0,     9,
       7,     1,     4,     3,     3,     3,     6,     5,     5,     0,
      10,     3,     0,     8,     0,     7,     4,     4,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     3,
       3,     4,     3,     3,     3,     3,     1,     5,     1,     3,
       3,     4,     0,     3,     1,     1,     1,     1,     1,     1,
       4,     1,     2,     3,     3,     3,     3,     2,     1,     3,
       0,     3,     0,     4,     0,     2,     3,     0,     2,     2,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     3,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
       2,     2,     3,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     3,     2,     2,     2,     2,
       2,     3,     3,     3,     3,     3,     4,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     1,     4,     0,     1,     1,
       3,     0,     5,     0,     0,     0,     6,     0,     0,     6,
       2,     2,     2,     2,     1,     2,     2,     1,     1,     1,
       1,     2,     1,     2,     2,     2,     2,     1,     1,     1,
       2,     2,     2,     0,     0,     6,     0,     2,     2,     0,
       2,     0,     2,     1,     3,     1,     3,     2,     2,     3,
       0,     0,     5,     1,     2,     5,     5,     5,     6,     2,
       1,     1,     1,     2,     3,     2,     3,     4,     1,     1,
       0,     1,     1,     1,     0,     1,     3,     8,     7,     3,
       3,     5,     0,     0,     9,     0,     0,     9,     0,     0,
       9,     0,     0,     6,     5,     8,    10,     1,     2,     3,
       4,     1,     2,     3,     1,     1,     1,     2,     2,     2,
       2,     4,     1,     3,     0,     4,     7,     7,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     6,     8,     6,
       5,     6,     8,     8,     6,     1,     4,     2,     0,     0,
       7,     0,     0,     8,     3,     4,     5,     6,     8,     8,
       6,     5,     6,     0,     0,     5,     3,     4,     4,     5,
       4,     3,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     2,     2,     2,     4,     3,     4,     5,
       4,     5,     3,     4,     1,     1,     2,     4,     4,     1,
       3,     5,     0,     0,     8,     3,     3,     3,     0,     0,
       8,     3,     4,     0,     0,     9,     4,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     1,     4,     3,
       3,     3,     7,     8,     7,     4,     4,     4,     4,     4,
       1,     6,     7,     6,     6,     7,     7,     6,     7,     6,
       5,     0,     1,     0,     1,     1,     0,     1,     0,     1,
       1,     0,     1,     5,     0,     2,     6,     0,     4,     0,
       9,     0,    11,     3,     3,     4,     1,     1,     3,     3,
       3,     1,     3,     1,     3,     0,     1,     3,     3,     1,
       3,     0,     1,     3,     1,     1,     1,     2,     3,     3,
       5,     1,     1,     1,     1,     1,     0,     1,     1,     4,
       3,     3,     6,     5,     1,     3,     0,     2,     2,     4,
       6,     5,     4,     6,     5,     0,     1,     0,     1,     1,
       0,     2,     0,     4,     6,     0,     6,     1,     3,     1,
       2,     0,     1,     3,     0,     1,     1,     0,     5,     3,
       6,     0,     1,     1,     1,     0,     2,     0,     1,     1,
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

  case 12: /* program: program distinct_declaration  */
                                                { yyextra->das_has_type_declarations = true; }
    break;

  case 13: /* program: program variant_alias_declaration  */
                                                { yyextra->das_has_type_declarations = true; }
    break;

  case 14: /* program: program tuple_alias_declaration  */
                                                { yyextra->das_has_type_declarations = true; }
    break;

  case 15: /* program: program bitfield_alias_declaration  */
                                                { yyextra->das_has_type_declarations = true; }
    break;

  case 22: /* top_level_reader_macro: expr_reader SEMICOLON  */
                                   {
        (void)(yyvsp[-1].pExpression); // gc_node — Expression, don't delete
    }
    break;

  case 23: /* optional_public_or_private_module: %empty  */
                        { (yyval.b) = yyextra->g_Program->policies.default_module_public; }
    break;

  case 24: /* optional_public_or_private_module: "public"  */
                        { (yyval.b) = true; }
    break;

  case 25: /* optional_public_or_private_module: "private"  */
                        { (yyval.b) = false; }
    break;

  case 26: /* module_name: '$'  */
                    { (yyval.s) = new string("$"); }
    break;

  case 27: /* module_name: "name"  */
                    { (yyval.s) = (yyvsp[0].s); }
    break;

  case 28: /* optional_not_required: %empty  */
        { (yyval.b) = false; }
    break;

  case 29: /* optional_not_required: '!' "inscope"  */
                        { (yyval.b) = true; }
    break;

  case 30: /* module_declaration: "module" module_name optional_shared optional_public_or_private_module optional_not_required  */
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

  case 31: /* character_sequence: STRING_CHARACTER  */
                                                                                  { (yyval.s) = new string(); *(yyval.s) += (yyvsp[0].ch); }
    break;

  case 32: /* character_sequence: STRING_CHARACTER_ESC  */
                                                                                  { (yyval.s) = new string(); *(yyval.s) += "\\\\"; }
    break;

  case 33: /* character_sequence: character_sequence STRING_CHARACTER  */
                                                                                  { (yyval.s) = (yyvsp[-1].s); *(yyvsp[-1].s) += (yyvsp[0].ch); }
    break;

  case 34: /* character_sequence: character_sequence STRING_CHARACTER_ESC  */
                                                                                  { (yyval.s) = (yyvsp[-1].s); *(yyvsp[-1].s) += "\\\\"; }
    break;

  case 35: /* string_constant: "start of the string" character_sequence "end of the string"  */
                                                           { (yyval.s) = (yyvsp[-1].s); }
    break;

  case 36: /* string_constant: "start of the string" "end of the string"  */
                                                           { (yyval.s) = new string(); }
    break;

  case 37: /* format_string: %empty  */
        { (yyval.s) = new string(); }
    break;

  case 38: /* format_string: format_string STRING_CHARACTER  */
                                                 { (yyval.s) = (yyvsp[-1].s); (yyvsp[-1].s)->push_back((yyvsp[0].ch)); }
    break;

  case 39: /* optional_format_string: %empty  */
        { (yyval.s) = new string(""); }
    break;

  case 40: /* $@1: %empty  */
            { das2_strfmt(scanner); }
    break;

  case 41: /* optional_format_string: ':' $@1 format_string  */
                                                         { (yyval.s) = (yyvsp[0].s); }
    break;

  case 42: /* string_builder_body: %empty  */
        {
        (yyval.pExpression) = new ExprStringBuilder();
        (yyval.pExpression)->at = LineInfo(yyextra->g_FileAccessStack.back(),
            yylloc.first_column,yylloc.first_line,yylloc.last_column,yylloc.last_line);
    }
    break;

  case 43: /* string_builder_body: string_builder_body character_sequence  */
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

  case 44: /* string_builder_body: string_builder_body "{" expr optional_format_string "}"  */
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

  case 45: /* string_builder: "start of the string" string_builder_body "end of the string"  */
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

  case 46: /* reader_character_sequence: STRING_CHARACTER  */
                               {
        if ( !yyextra->g_ReaderMacro->accept(yyextra->g_Program.get(), yyextra->g_Program->thisModule.get(), yyextra->g_ReaderExpr, (yyvsp[0].ch), tokAt(scanner,(yylsp[0]))) ) {
            das2_yyend_reader(scanner);
        }
    }
    break;

  case 47: /* reader_character_sequence: reader_character_sequence STRING_CHARACTER  */
                                                                {
        if ( !yyextra->g_ReaderMacro->accept(yyextra->g_Program.get(), yyextra->g_Program->thisModule.get(), yyextra->g_ReaderExpr, (yyvsp[0].ch), tokAt(scanner,(yylsp[0]))) ) {
            das2_yyend_reader(scanner);
        }
    }
    break;

  case 48: /* $@2: %empty  */
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

  case 49: /* expr_reader: '%' name_in_namespace $@2 reader_character_sequence  */
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

  case 50: /* options_declaration: "options" annotation_argument_list  */
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

  case 52: /* require_module_name: "name"  */
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

  case 57: /* require_module_name: require_module_name '.' "name"  */
                                                {
        *(yyvsp[-2].s) += ".";
        *(yyvsp[-2].s) += *(yyvsp[0].s);
        delete (yyvsp[0].s);
        (yyval.s) = (yyvsp[-2].s);
    }
    break;

  case 58: /* require_module_name: require_module_name '/' "name"  */
                                                {
        *(yyvsp[-2].s) += "/";
        *(yyvsp[-2].s) += *(yyvsp[0].s);
        delete (yyvsp[0].s);
        (yyval.s) = (yyvsp[-2].s);
    }
    break;

  case 59: /* optional_require_guard: %empty  */
                                            { (yyval.s) = nullptr; }
    break;

  case 60: /* optional_require_guard: '?' require_module_name  */
                                            { (yyval.s) = (yyvsp[0].s); }
    break;

  case 61: /* require_module: optional_require_guard require_module_name is_public_module  */
                                                                                       {
        ast_requireModule(scanner,(yyvsp[-1].s),nullptr,(yyvsp[0].b),tokAt(scanner,(yylsp[-1])),(yyvsp[-2].s));
    }
    break;

  case 62: /* require_module: optional_require_guard require_module_name "as" "name" is_public_module  */
                                                                                                            {
        ast_requireModule(scanner,(yyvsp[-3].s),(yyvsp[-1].s),(yyvsp[0].b),tokAt(scanner,(yylsp[-3])),(yyvsp[-4].s));
    }
    break;

  case 63: /* is_public_module: %empty  */
                    { (yyval.b) = false; }
    break;

  case 64: /* is_public_module: "public"  */
                    { (yyval.b) = true; }
    break;

  case 68: /* expect_error: "integer constant"  */
                   {
        yyextra->g_Program->expectErrors[CompilationError((yyvsp[0].i))] ++;
    }
    break;

  case 69: /* expect_error: "integer constant" ':' "integer constant"  */
                                      {
        yyextra->g_Program->expectErrors[CompilationError((yyvsp[-2].i))] += (yyvsp[0].i);
    }
    break;

  case 70: /* expression_label: "label" "integer constant" ':'  */
                                          {
        (yyval.pExpression) = new ExprLabel(tokAt(scanner,(yylsp[-2])),(yyvsp[-1].i));
    }
    break;

  case 71: /* expression_goto: "goto" "label" "integer constant"  */
                                                {
        (yyval.pExpression) = new ExprGoto(tokAt(scanner,(yylsp[-2])),(yyvsp[0].i));
    }
    break;

  case 72: /* expression_goto: "goto" expr  */
                               {
        (yyval.pExpression) = new ExprGoto(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression));
    }
    break;

  case 73: /* elif_or_static_elif: "elif"  */
                          { (yyval.b) = false; }
    break;

  case 74: /* elif_or_static_elif: "static_elif"  */
                          { (yyval.b) = true; }
    break;

  case 79: /* expression_else: %empty  */
                                                           { (yyval.pExpression) = nullptr; }
    break;

  case 80: /* $@3: %empty  */
                                           {
    }
    break;

  case 81: /* expression_else: "else" optional_emit_semis $@3 expression_else_block  */
                                   {
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 82: /* $@4: %empty  */
                                                                        {
    }
    break;

  case 83: /* expression_else: elif_or_static_elif '(' expr ')' optional_emit_semis $@4 expression_else_block expression_else  */
                                                         {
        auto eite = new ExprIfThenElse(tokAt(scanner,(yylsp[-7])),(yyvsp[-5].pExpression),(yyvsp[-1].pExpression),(yyvsp[0].pExpression));
        eite->isStatic = (yyvsp[-7].b);
        (yyval.pExpression) = eite;
    }
    break;

  case 84: /* if_or_static_if: "if"  */
                        { (yyval.b) = false; }
    break;

  case 85: /* if_or_static_if: "static_if"  */
                        { (yyval.b) = true; }
    break;

  case 86: /* expression_else_one_liner: %empty  */
        { (yyval.pExpression) = nullptr; }
    break;

  case 87: /* expression_else_one_liner: "else" expression_if_one_liner  */
                                                      {
            (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 88: /* expression_if_one_liner: expr_no_bracket  */
                                              { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 89: /* expression_if_one_liner: expression_return  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 90: /* expression_if_one_liner: expression_yield  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 91: /* expression_if_one_liner: expression_break  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 92: /* expression_if_one_liner: expression_continue  */
                                            { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 97: /* $@5: %empty  */
                     {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 98: /* $@6: %empty  */
                         {
        yyextra->pop_nesteds();
    }
    break;

  case 99: /* expression_if_block: '{' $@5 expressions $@6 '}' expression_block_finally  */
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

  case 100: /* $@7: %empty  */
       {
        yyextra->das_keyword = false;
    }
    break;

  case 101: /* expression_if_block: $@7 expression_if_one_liner SEMICOLON  */
                                               {
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 102: /* $@8: %empty  */
                     {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 103: /* $@9: %empty  */
                         {
        yyextra->pop_nesteds();
    }
    break;

  case 104: /* expression_else_block: '{' $@8 expressions $@9 '}' expression_block_finally  */
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

  case 105: /* $@10: %empty  */
       {
        yyextra->das_keyword = false;
    }
    break;

  case 106: /* expression_else_block: $@10 expression_if_one_liner SEMICOLON  */
                                               {
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 107: /* $@11: %empty  */
        {
        yyextra->das_keyword = true;
    }
    break;

  case 108: /* $@12: %empty  */
                                                                  {
    }
    break;

  case 109: /* expression_if_then_else: $@11 if_or_static_if '(' expr ')' optional_emit_semis $@12 expression_if_block expression_else  */
                                                       {
        yyextra->das_keyword = false;
        auto blk = (yyvsp[-1].pExpression)->rtti_isBlock() ? static_cast<ExprBlock *>((yyvsp[-1].pExpression)) : ast_wrapInBlock((yyvsp[-1].pExpression));
        auto eite = new ExprIfThenElse(tokAt(scanner,(yylsp[-7])),(yyvsp[-5].pExpression),blk,(yyvsp[0].pExpression));
        eite->isStatic = (yyvsp[-7].b);
        (yyval.pExpression) = eite;
    }
    break;

  case 110: /* expression_if_then_else_oneliner: expression_if_one_liner "if" '(' expr ')' expression_else_one_liner SEMICOLON  */
                                                                                                                      {
        (yyval.pExpression) = new ExprIfThenElse(tokAt(scanner,(yylsp[-5])),(yyvsp[-3].pExpression),ast_wrapInBlock((yyvsp[-6].pExpression)),(yyvsp[-1].pExpression) ? ast_wrapInBlock((yyvsp[-1].pExpression)) : nullptr);
    }
    break;

  case 111: /* for_variable_name_with_pos_list: "name"  */
                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = pSL;
        delete (yyvsp[0].s);
    }
    break;

  case 112: /* for_variable_name_with_pos_list: "$i" '(' expr ')'  */
                                     {
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = pSL;
    }
    break;

  case 113: /* for_variable_name_with_pos_list: "name" "aka" "name"  */
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

  case 114: /* for_variable_name_with_pos_list: '(' tuple_expansion ')'  */
                                       {
        auto pSL = new vector<VariableNameAndPosition>();
        for ( auto & x : *(yyvsp[-1].pNameList) ) {
            das_checkName(scanner,x,tokAt(scanner,(yylsp[-1])));
        }
        pSL->push_back(VariableNameAndPosition((yyvsp[-1].pNameList),tokAt(scanner,(yylsp[-1]))));
        (yyval.pNameWithPosList) = pSL;
    }
    break;

  case 115: /* for_variable_name_with_pos_list: for_variable_name_with_pos_list ',' "name"  */
                                                             {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = (yyvsp[-2].pNameWithPosList);
        delete (yyvsp[0].s);
    }
    break;

  case 116: /* for_variable_name_with_pos_list: for_variable_name_with_pos_list ',' "$i" '(' expr ')'  */
                                                                               {
        (yyvsp[-5].pNameWithPosList)->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = (yyvsp[-5].pNameWithPosList);
    }
    break;

  case 117: /* for_variable_name_with_pos_list: for_variable_name_with_pos_list ',' "name" "aka" "name"  */
                                                                                   {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-4].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[-2].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-2]))));
        (yyval.pNameWithPosList) = (yyvsp[-4].pNameWithPosList);
        delete (yyvsp[-2].s);
        delete (yyvsp[0].s);
    }
    break;

  case 118: /* for_variable_name_with_pos_list: for_variable_name_with_pos_list ',' '(' tuple_expansion ')'  */
                                                                                 {
        for ( auto & x : *(yyvsp[-1].pNameList) ) {
            das_checkName(scanner,x,tokAt(scanner,(yylsp[-1])));
        }
        (yyvsp[-4].pNameWithPosList)->push_back(VariableNameAndPosition((yyvsp[-1].pNameList),tokAt(scanner,(yylsp[-1]))));
        (yyval.pNameWithPosList) = (yyvsp[-4].pNameWithPosList);
    }
    break;

  case 119: /* $@13: %empty  */
        {
        yyextra->das_keyword = true;
    }
    break;

  case 120: /* expression_for_loop: $@13 "for" optional_for_annotations '(' for_variable_name_with_pos_list "in" expr_list ')' optional_emit_semis expression_block  */
                                                                                                                                                                    {
        yyextra->das_keyword = false;
        (yyval.pExpression) = ast_forLoop(scanner,(yyvsp[-5].pNameWithPosList),(yyvsp[-3].pExpression),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[-8])),tokAt(scanner,(yylsp[0])),(yyvsp[-7].aaList));
    }
    break;

  case 121: /* expression_unsafe: "unsafe" optional_emit_semis expression_block  */
                                                                    {
        auto pUnsafe = new ExprUnsafe(tokAt(scanner,(yylsp[-2])));
        pUnsafe->body = (yyvsp[0].pExpression);
        (yyval.pExpression) = pUnsafe;
    }
    break;

  case 122: /* $@14: %empty  */
        {
        yyextra->das_keyword = true;
    }
    break;

  case 123: /* expression_while_loop: $@14 "while" optional_for_annotations '(' expr ')' optional_emit_semis expression_block  */
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

  case 124: /* $@15: %empty  */
        {
        yyextra->das_keyword = true;
    }
    break;

  case 125: /* expression_with: $@15 "with" '(' expr ')' optional_emit_semis expression_block  */
                                                                                   {
        yyextra->das_keyword = false;
        auto pWith = new ExprWith(tokAt(scanner,(yylsp[-5])));
        pWith->with = (yyvsp[-3].pExpression);
        pWith->body = (yyvsp[0].pExpression);
        (yyval.pExpression) = pWith;
    }
    break;

  case 126: /* expression_with_alias: "assume" "name" '=' expr  */
                                                      {
        (yyval.pExpression) = new ExprAssume(tokAt(scanner,(yylsp[-3])), *(yyvsp[-2].s), ExpressionPtr((yyvsp[0].pExpression)));
        delete (yyvsp[-2].s);
    }
    break;

  case 127: /* expression_with_alias: "typedef" "name" '=' type_declaration  */
                                                                {
        (yyval.pExpression) = new ExprAssume(tokAt(scanner,(yylsp[-3])), *(yyvsp[-2].s), TypeDeclPtr((yyvsp[0].pTypeDecl)));
        delete (yyvsp[-2].s);
    }
    break;

  case 128: /* annotation_argument_value: string_constant  */
                                 { (yyval.aa) = new AnnotationArgument("",*(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 129: /* annotation_argument_value: "name"  */
                                 { (yyval.aa) = new AnnotationArgument("",*(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 130: /* annotation_argument_value: "integer constant"  */
                                 { (yyval.aa) = new AnnotationArgument("",(yyvsp[0].i)); }
    break;

  case 131: /* annotation_argument_value: "floating point constant"  */
                                 { (yyval.aa) = new AnnotationArgument("",float((yyvsp[0].fd))); }
    break;

  case 132: /* annotation_argument_value: "true"  */
                                 { (yyval.aa) = new AnnotationArgument("",true); }
    break;

  case 133: /* annotation_argument_value: "false"  */
                                 { (yyval.aa) = new AnnotationArgument("",false); }
    break;

  case 134: /* annotation_argument_value_list: annotation_argument_value  */
                                       {
        (yyval.aaList) = new AnnotationArgumentList();
        (yyval.aaList)->push_back(*(yyvsp[0].aa));
        delete (yyvsp[0].aa);
    }
    break;

  case 135: /* annotation_argument_value_list: annotation_argument_value_list ',' annotation_argument_value  */
                                                                                {
            (yyval.aaList) = (yyvsp[-2].aaList);
            (yyval.aaList)->push_back(*(yyvsp[0].aa));
            delete (yyvsp[0].aa);
    }
    break;

  case 136: /* annotation_argument_name: "name"  */
                    { (yyval.s) = (yyvsp[0].s); }
    break;

  case 137: /* annotation_argument_name: "type"  */
                    { (yyval.s) = new string("type"); }
    break;

  case 138: /* annotation_argument_name: "in"  */
                    { (yyval.s) = new string("in"); }
    break;

  case 139: /* annotation_argument: annotation_argument_name '=' string_constant  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-2]))); delete (yyvsp[0].s); delete (yyvsp[-2].s); }
    break;

  case 140: /* annotation_argument: annotation_argument_name '=' "name"  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-2]))); delete (yyvsp[0].s); delete (yyvsp[-2].s); }
    break;

  case 141: /* annotation_argument: annotation_argument_name '=' "@@" "name"  */
                                                                      { (yyval.aa) = new AnnotationArgument(*(yyvsp[-3].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-3]))); delete (yyvsp[0].s); delete (yyvsp[-3].s); }
    break;

  case 142: /* annotation_argument: annotation_argument_name '=' "integer constant"  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),(yyvsp[0].i),tokAt(scanner,(yylsp[-2]))); delete (yyvsp[-2].s); }
    break;

  case 143: /* annotation_argument: annotation_argument_name '=' "floating point constant"  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),float((yyvsp[0].fd)),tokAt(scanner,(yylsp[-2]))); delete (yyvsp[-2].s); }
    break;

  case 144: /* annotation_argument: annotation_argument_name '=' "true"  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),true,tokAt(scanner,(yylsp[-2]))); delete (yyvsp[-2].s); }
    break;

  case 145: /* annotation_argument: annotation_argument_name '=' "false"  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[-2].s),false,tokAt(scanner,(yylsp[-2]))); delete (yyvsp[-2].s); }
    break;

  case 146: /* annotation_argument: annotation_argument_name  */
                                                                    { (yyval.aa) = new AnnotationArgument(*(yyvsp[0].s),true,tokAt(scanner,(yylsp[0]))); delete (yyvsp[0].s); }
    break;

  case 147: /* annotation_argument: annotation_argument_name '=' '(' annotation_argument_value_list ')'  */
                                                                                          {
        { (yyval.aa) = new AnnotationArgument(*(yyvsp[-4].s),(yyvsp[-1].aaList),tokAt(scanner,(yylsp[-4]))); delete (yyvsp[-4].s); }
    }
    break;

  case 148: /* annotation_argument_list: annotation_argument  */
                                  {
        (yyval.aaList) = ast_annotationArgumentListEntry(scanner,new AnnotationArgumentList(),(yyvsp[0].aa));
    }
    break;

  case 149: /* annotation_argument_list: annotation_argument_list ',' annotation_argument  */
                                                                    {
        (yyval.aaList) = ast_annotationArgumentListEntry(scanner,(yyvsp[-2].aaList),(yyvsp[0].aa));
    }
    break;

  case 150: /* metadata_argument_list: "@field" annotation_argument optional_emit_semis  */
                                                              {
        (yyval.aaList) = ast_annotationArgumentListEntry(scanner,new AnnotationArgumentList(),(yyvsp[-1].aa));
    }
    break;

  case 151: /* metadata_argument_list: metadata_argument_list "@field" annotation_argument optional_emit_semis  */
                                                                                           {
        (yyval.aaList) = ast_annotationArgumentListEntry(scanner,(yyvsp[-3].aaList),(yyvsp[-1].aa));
    }
    break;

  case 152: /* optional_for_annotations: %empty  */
                    {
        (yyval.aaList) = nullptr;
    }
    break;

  case 153: /* optional_for_annotations: '[' annotation_argument_list ']'  */
                                               {
        (yyval.aaList) = (yyvsp[-1].aaList);
    }
    break;

  case 154: /* optional_for_annotations: metadata_argument_list  */
                                     {
        (yyval.aaList) = (yyvsp[0].aaList);
    }
    break;

  case 155: /* annotation_declaration_name: name_in_namespace  */
                                    { (yyval.s) = (yyvsp[0].s); }
    break;

  case 156: /* annotation_declaration_name: "require"  */
                                    { (yyval.s) = new string("require"); }
    break;

  case 157: /* annotation_declaration_name: "private"  */
                                    { (yyval.s) = new string("private"); }
    break;

  case 158: /* annotation_declaration_name: "template"  */
                                    { (yyval.s) = new string("template"); }
    break;

  case 159: /* annotation_declaration_basic: annotation_declaration_name  */
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

  case 160: /* annotation_declaration_basic: annotation_declaration_name '(' annotation_argument_list ')'  */
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

  case 161: /* annotation_declaration: annotation_declaration_basic  */
                                          {
        (yyval.fa) = (yyvsp[0].fa);
    }
    break;

  case 162: /* annotation_declaration: '!' annotation_declaration  */
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

  case 163: /* annotation_declaration: annotation_declaration "&&" annotation_declaration  */
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

  case 164: /* annotation_declaration: annotation_declaration "||" annotation_declaration  */
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

  case 165: /* annotation_declaration: annotation_declaration "^^" annotation_declaration  */
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

  case 166: /* annotation_declaration: '(' annotation_declaration ')'  */
                                            {
        (yyval.fa) = (yyvsp[-1].fa);
    }
    break;

  case 167: /* annotation_declaration: "|>" annotation_declaration  */
                                          {
        (yyval.fa) = (yyvsp[0].fa);
        (yyvsp[0].fa)->inherited = true;
    }
    break;

  case 168: /* annotation_list: annotation_declaration  */
                                    {
            (yyval.faList) = new AnnotationList();
            (yyval.faList)->push_back(AnnotationDeclarationPtr((yyvsp[0].fa)));
    }
    break;

  case 169: /* annotation_list: annotation_list ',' annotation_declaration  */
                                                              {
        (yyval.faList) = (yyvsp[-2].faList);
        (yyval.faList)->push_back(AnnotationDeclarationPtr((yyvsp[0].fa)));
    }
    break;

  case 170: /* optional_annotation_list: %empty  */
                                       { (yyval.faList) = nullptr; }
    break;

  case 171: /* optional_annotation_list: '[' annotation_list ']'  */
                                       { (yyval.faList) = (yyvsp[-1].faList); }
    break;

  case 172: /* optional_annotation_list_with_emit_semis: %empty  */
                                       { (yyval.faList) = nullptr; }
    break;

  case 173: /* optional_annotation_list_with_emit_semis: '[' annotation_list ']' optional_emit_semis  */
                                                          { (yyval.faList) = (yyvsp[-2].faList); }
    break;

  case 174: /* optional_function_argument_list: %empty  */
                                                { (yyval.pVarDeclList) = nullptr; }
    break;

  case 175: /* optional_function_argument_list: '(' ')'  */
                                                { (yyval.pVarDeclList) = nullptr; }
    break;

  case 176: /* optional_function_argument_list: '(' function_argument_list ')'  */
                                                { (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList); }
    break;

  case 177: /* optional_function_type: %empty  */
        {
        (yyval.pTypeDecl) = new TypeDecl(Type::autoinfer);
    }
    break;

  case 178: /* optional_function_type: ':' type_declaration  */
                                        {
        (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 179: /* optional_function_type: "->" type_declaration  */
                                           {
        (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 180: /* function_name: "name"  */
                          {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyval.s) = (yyvsp[0].s);
    }
    break;

  case 181: /* function_name: "operator" '!'  */
                             { (yyval.s) = new string("!"); }
    break;

  case 182: /* function_name: "operator" '~'  */
                             { (yyval.s) = new string("~"); }
    break;

  case 183: /* function_name: "operator" "+="  */
                             { (yyval.s) = new string("+="); }
    break;

  case 184: /* function_name: "operator" "-="  */
                             { (yyval.s) = new string("-="); }
    break;

  case 185: /* function_name: "operator" "*="  */
                             { (yyval.s) = new string("*="); }
    break;

  case 186: /* function_name: "operator" "/="  */
                             { (yyval.s) = new string("/="); }
    break;

  case 187: /* function_name: "operator" "%="  */
                             { (yyval.s) = new string("%="); }
    break;

  case 188: /* function_name: "operator" "&="  */
                             { (yyval.s) = new string("&="); }
    break;

  case 189: /* function_name: "operator" "|="  */
                             { (yyval.s) = new string("|="); }
    break;

  case 190: /* function_name: "operator" "^="  */
                             { (yyval.s) = new string("^="); }
    break;

  case 191: /* function_name: "operator" "&&="  */
                                { (yyval.s) = new string("&&="); }
    break;

  case 192: /* function_name: "operator" "||="  */
                                { (yyval.s) = new string("||="); }
    break;

  case 193: /* function_name: "operator" "^^="  */
                                { (yyval.s) = new string("^^="); }
    break;

  case 194: /* function_name: "operator" "&&"  */
                             { (yyval.s) = new string("&&"); }
    break;

  case 195: /* function_name: "operator" "||"  */
                             { (yyval.s) = new string("||"); }
    break;

  case 196: /* function_name: "operator" "^^"  */
                             { (yyval.s) = new string("^^"); }
    break;

  case 197: /* function_name: "operator" '+'  */
                             { (yyval.s) = new string("+"); }
    break;

  case 198: /* function_name: "operator" '-'  */
                             { (yyval.s) = new string("-"); }
    break;

  case 199: /* function_name: "operator" '*'  */
                             { (yyval.s) = new string("*"); }
    break;

  case 200: /* function_name: "operator" '/'  */
                             { (yyval.s) = new string("/"); }
    break;

  case 201: /* function_name: "operator" '%'  */
                             { (yyval.s) = new string("%"); }
    break;

  case 202: /* function_name: "operator" '<'  */
                             { (yyval.s) = new string("<"); }
    break;

  case 203: /* function_name: "operator" '>'  */
                             { (yyval.s) = new string(">"); }
    break;

  case 204: /* function_name: "operator" ".."  */
                             { (yyval.s) = new string("interval"); }
    break;

  case 205: /* function_name: "operator" "=="  */
                             { (yyval.s) = new string("=="); }
    break;

  case 206: /* function_name: "operator" "!="  */
                             { (yyval.s) = new string("!="); }
    break;

  case 207: /* function_name: "operator" "<="  */
                             { (yyval.s) = new string("<="); }
    break;

  case 208: /* function_name: "operator" ">="  */
                             { (yyval.s) = new string(">="); }
    break;

  case 209: /* function_name: "operator" '&'  */
                             { (yyval.s) = new string("&"); }
    break;

  case 210: /* function_name: "operator" '|'  */
                             { (yyval.s) = new string("|"); }
    break;

  case 211: /* function_name: "operator" '^'  */
                             { (yyval.s) = new string("^"); }
    break;

  case 212: /* function_name: "++" "operator"  */
                             { (yyval.s) = new string("++"); }
    break;

  case 213: /* function_name: "--" "operator"  */
                             { (yyval.s) = new string("--"); }
    break;

  case 214: /* function_name: "operator" "++"  */
                             { (yyval.s) = new string("+++"); }
    break;

  case 215: /* function_name: "operator" "--"  */
                             { (yyval.s) = new string("---"); }
    break;

  case 216: /* function_name: "operator" "<<"  */
                             { (yyval.s) = new string("<<"); }
    break;

  case 217: /* function_name: "operator" ">>"  */
                             { (yyval.s) = new string(">>"); }
    break;

  case 218: /* function_name: "operator" "<<="  */
                             { (yyval.s) = new string("<<="); }
    break;

  case 219: /* function_name: "operator" ">>="  */
                             { (yyval.s) = new string(">>="); }
    break;

  case 220: /* function_name: "operator" "<<<"  */
                             { (yyval.s) = new string("<<<"); }
    break;

  case 221: /* function_name: "operator" ">>>"  */
                             { (yyval.s) = new string(">>>"); }
    break;

  case 222: /* function_name: "operator" "<<<="  */
                             { (yyval.s) = new string("<<<="); }
    break;

  case 223: /* function_name: "operator" ">>>="  */
                             { (yyval.s) = new string(">>>="); }
    break;

  case 224: /* function_name: "operator" '[' ']'  */
                             { (yyval.s) = new string("[]"); }
    break;

  case 225: /* function_name: "operator" '[' ']' '='  */
                                 { (yyval.s) = new string("[]="); }
    break;

  case 226: /* function_name: "operator" '[' ']' "<-"  */
                                    { (yyval.s) = new string("[]<-"); }
    break;

  case 227: /* function_name: "operator" '[' ']' ":="  */
                                      { (yyval.s) = new string("[]:="); }
    break;

  case 228: /* function_name: "operator" '[' ']' "+="  */
                                     { (yyval.s) = new string("[]+="); }
    break;

  case 229: /* function_name: "operator" '[' ']' "-="  */
                                     { (yyval.s) = new string("[]-="); }
    break;

  case 230: /* function_name: "operator" '[' ']' "*="  */
                                     { (yyval.s) = new string("[]*="); }
    break;

  case 231: /* function_name: "operator" '[' ']' "/="  */
                                     { (yyval.s) = new string("[]/="); }
    break;

  case 232: /* function_name: "operator" '[' ']' "%="  */
                                     { (yyval.s) = new string("[]%="); }
    break;

  case 233: /* function_name: "operator" '[' ']' "&="  */
                                     { (yyval.s) = new string("[]&="); }
    break;

  case 234: /* function_name: "operator" '[' ']' "|="  */
                                     { (yyval.s) = new string("[]|="); }
    break;

  case 235: /* function_name: "operator" '[' ']' "^="  */
                                     { (yyval.s) = new string("[]^="); }
    break;

  case 236: /* function_name: "operator" '[' ']' "&&="  */
                                        { (yyval.s) = new string("[]&&="); }
    break;

  case 237: /* function_name: "operator" '[' ']' "||="  */
                                        { (yyval.s) = new string("[]||="); }
    break;

  case 238: /* function_name: "operator" '[' ']' "^^="  */
                                        { (yyval.s) = new string("[]^^="); }
    break;

  case 239: /* function_name: "operator" "?[" ']'  */
                                { (yyval.s) = new string("?[]"); }
    break;

  case 240: /* function_name: "operator" '.'  */
                             { (yyval.s) = new string("."); }
    break;

  case 241: /* function_name: "operator" "?."  */
                             { (yyval.s) = new string("?."); }
    break;

  case 242: /* function_name: "operator" '.' "name"  */
                                       { (yyval.s) = new string(".`"+*(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 243: /* function_name: "operator" '.' "name" ":="  */
                                             { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`clone"); delete (yyvsp[-1].s); }
    break;

  case 244: /* function_name: "operator" '.' "name" "+="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`+="); delete (yyvsp[-1].s); }
    break;

  case 245: /* function_name: "operator" '.' "name" "-="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`-="); delete (yyvsp[-1].s); }
    break;

  case 246: /* function_name: "operator" '.' "name" "*="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`*="); delete (yyvsp[-1].s); }
    break;

  case 247: /* function_name: "operator" '.' "name" "/="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`/="); delete (yyvsp[-1].s); }
    break;

  case 248: /* function_name: "operator" '.' "name" "%="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`%="); delete (yyvsp[-1].s); }
    break;

  case 249: /* function_name: "operator" '.' "name" "&="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`&="); delete (yyvsp[-1].s); }
    break;

  case 250: /* function_name: "operator" '.' "name" "|="  */
                                          { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`|="); delete (yyvsp[-1].s); }
    break;

  case 251: /* function_name: "operator" '.' "name" "^="  */
                                           { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`^="); delete (yyvsp[-1].s); }
    break;

  case 252: /* function_name: "operator" '.' "name" "&&="  */
                                              { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`&&="); delete (yyvsp[-1].s); }
    break;

  case 253: /* function_name: "operator" '.' "name" "||="  */
                                            { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`||="); delete (yyvsp[-1].s); }
    break;

  case 254: /* function_name: "operator" '.' "name" "^^="  */
                                              { (yyval.s) = new string(".`"+*(yyvsp[-1].s)+"`^^="); delete (yyvsp[-1].s); }
    break;

  case 255: /* function_name: "operator" "?." "name"  */
                                       { (yyval.s) = new string("?.`"+*(yyvsp[0].s)); delete (yyvsp[0].s);}
    break;

  case 256: /* function_name: "operator" ":="  */
                                { (yyval.s) = new string("clone"); }
    break;

  case 257: /* function_name: "operator" "delete"  */
                                { (yyval.s) = new string("finalize"); }
    break;

  case 258: /* function_name: "operator" "??"  */
                           { (yyval.s) = new string("??"); }
    break;

  case 259: /* function_name: "operator" "is"  */
                            { (yyval.s) = new string("`is"); }
    break;

  case 260: /* function_name: "operator" "as"  */
                            { (yyval.s) = new string("`as"); }
    break;

  case 261: /* function_name: "operator" "is" "name"  */
                                       { (yyval.s) = (yyvsp[0].s); *(yyvsp[0].s) = "`is`" + *(yyvsp[0].s); }
    break;

  case 262: /* function_name: "operator" "as" "name"  */
                                       { (yyval.s) = (yyvsp[0].s); *(yyvsp[0].s) = "`as`" + *(yyvsp[0].s); }
    break;

  case 263: /* function_name: "operator" "is" das_type_name  */
                                                { (yyval.s) = (yyvsp[0].s); *(yyvsp[0].s) = "`is`" + *(yyvsp[0].s); }
    break;

  case 264: /* function_name: "operator" "as" das_type_name  */
                                                { (yyval.s) = (yyvsp[0].s); *(yyvsp[0].s) = "`as`" + *(yyvsp[0].s); }
    break;

  case 265: /* function_name: "operator" '?' "as"  */
                                { (yyval.s) = new string("?as"); }
    break;

  case 266: /* function_name: "operator" '?' "as" "name"  */
                                           { (yyval.s) = (yyvsp[0].s); *(yyvsp[0].s) = "?as`" + *(yyvsp[0].s); }
    break;

  case 267: /* function_name: "operator" '?' "as" das_type_name  */
                                                    { (yyval.s) = (yyvsp[0].s); *(yyvsp[0].s) = "?as`" + *(yyvsp[0].s); }
    break;

  case 268: /* function_name: das_type_name  */
                            { (yyval.s) = (yyvsp[0].s); }
    break;

  case 269: /* das_type_name: "bool"  */
                     { (yyval.s) = new string("bool"); }
    break;

  case 270: /* das_type_name: "string"  */
                     { (yyval.s) = new string("string"); }
    break;

  case 271: /* das_type_name: "int"  */
                     { (yyval.s) = new string("int"); }
    break;

  case 272: /* das_type_name: "int2"  */
                     { (yyval.s) = new string("int2"); }
    break;

  case 273: /* das_type_name: "int3"  */
                     { (yyval.s) = new string("int3"); }
    break;

  case 274: /* das_type_name: "int4"  */
                     { (yyval.s) = new string("int4"); }
    break;

  case 275: /* das_type_name: "uint"  */
                     { (yyval.s) = new string("uint"); }
    break;

  case 276: /* das_type_name: "uint2"  */
                     { (yyval.s) = new string("uint2"); }
    break;

  case 277: /* das_type_name: "uint3"  */
                     { (yyval.s) = new string("uint3"); }
    break;

  case 278: /* das_type_name: "uint4"  */
                     { (yyval.s) = new string("uint4"); }
    break;

  case 279: /* das_type_name: "float"  */
                     { (yyval.s) = new string("float"); }
    break;

  case 280: /* das_type_name: "float2"  */
                     { (yyval.s) = new string("float2"); }
    break;

  case 281: /* das_type_name: "float3"  */
                     { (yyval.s) = new string("float3"); }
    break;

  case 282: /* das_type_name: "float4"  */
                     { (yyval.s) = new string("float4"); }
    break;

  case 283: /* das_type_name: "range"  */
                     { (yyval.s) = new string("range"); }
    break;

  case 284: /* das_type_name: "urange"  */
                     { (yyval.s) = new string("urange"); }
    break;

  case 285: /* das_type_name: "range64"  */
                     { (yyval.s) = new string("range64"); }
    break;

  case 286: /* das_type_name: "urange64"  */
                     { (yyval.s) = new string("urange64"); }
    break;

  case 287: /* das_type_name: "int64"  */
                     { (yyval.s) = new string("int64"); }
    break;

  case 288: /* das_type_name: "uint64"  */
                     { (yyval.s) = new string("uint64"); }
    break;

  case 289: /* das_type_name: "double"  */
                     { (yyval.s) = new string("double"); }
    break;

  case 290: /* das_type_name: "int8"  */
                     { (yyval.s) = new string("int8"); }
    break;

  case 291: /* das_type_name: "uint8"  */
                     { (yyval.s) = new string("uint8"); }
    break;

  case 292: /* das_type_name: "int16"  */
                     { (yyval.s) = new string("int16"); }
    break;

  case 293: /* das_type_name: "uint16"  */
                     { (yyval.s) = new string("uint16"); }
    break;

  case 294: /* optional_template: %empty  */
                                        { (yyval.b) = false; }
    break;

  case 295: /* optional_template: "template"  */
                                        { (yyval.b) = true; }
    break;

  case 296: /* global_function_declaration: optional_annotation_list_with_emit_semis "def" optional_template function_declaration  */
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

  case 297: /* optional_public_or_private_function: %empty  */
                        { (yyval.b) = yyextra->g_thisStructure ? !yyextra->g_thisStructure->privateStructure : yyextra->g_Program->thisModule->isPublic; }
    break;

  case 298: /* optional_public_or_private_function: "private"  */
                        { (yyval.b) = false; }
    break;

  case 299: /* optional_public_or_private_function: "public"  */
                        { (yyval.b) = true; }
    break;

  case 300: /* function_declaration_header: function_name optional_function_argument_list optional_function_type  */
                                                                                                {
        (yyval.pFuncDecl) = ast_functionDeclarationHeader(scanner,(yyvsp[-2].s),(yyvsp[-1].pVarDeclList),(yyvsp[0].pTypeDecl),tokAt(scanner,(yylsp[-2])));
    }
    break;

  case 301: /* $@16: %empty  */
                                                     {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeFunction(tak);
        }
    }
    break;

  case 302: /* function_declaration: optional_public_or_private_function $@16 function_declaration_header optional_emit_semis block_or_simple_block  */
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

  case 303: /* expression_block_finally: %empty  */
        {
        (yyval.pExpression) = nullptr;
    }
    break;

  case 304: /* $@17: %empty  */
                  {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 305: /* $@18: %empty  */
                             {
        yyextra->pop_nesteds();
    }
    break;

  case 306: /* expression_block_finally: "finally" $@17 '{' expressions $@18 '}'  */
          {
        (yyval.pExpression) = (yyvsp[-2].pExpression);
    }
    break;

  case 307: /* $@19: %empty  */
        {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 308: /* $@20: %empty  */
                                      {
        yyextra->pop_nesteds();
    }
    break;

  case 309: /* expression_block: $@19 '{' expressions $@20 '}' expression_block_finally  */
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

  case 310: /* expr_call_pipe_no_bracket: expr_call expr_full_block_assumed_piped  */
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

  case 311: /* expr_call_pipe_no_bracket: expr_method_call_no_bracket expr_full_block_assumed_piped  */
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

  case 312: /* expr_call_pipe_no_bracket: expr_field_no_bracket expr_full_block_assumed_piped  */
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

  case 313: /* expr_call_pipe_no_bracket: expr_named_call expr_full_block_assumed_piped  */
                                                                 {
        // free-function named call + piped block: pad-aware resolution lands it on the block param
        auto nc = (ExprNamedCall *) (yyvsp[-1].pExpression);
        nc->nonNamedArguments.push_back((yyvsp[0].pExpression));
        nc->pipedCallArgument = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 314: /* expression_any: SEMICOLON  */
                                                  { (yyval.pExpression) = nullptr; }
    break;

  case 315: /* expression_any: expr_assign_no_bracket SEMICOLON  */
                                                    { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 316: /* expression_any: expression_delete SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 317: /* expression_any: expression_let  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 318: /* expression_any: expression_while_loop  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 319: /* expression_any: expression_unsafe  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 320: /* expression_any: expression_with  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 321: /* expression_any: expression_with_alias SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 322: /* expression_any: expression_for_loop  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 323: /* expression_any: expression_break SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 324: /* expression_any: expression_continue SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 325: /* expression_any: expression_return SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 326: /* expression_any: expression_yield SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 327: /* expression_any: expression_if_then_else  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 328: /* expression_any: expression_if_then_else_oneliner  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 329: /* expression_any: expression_try_catch  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 330: /* expression_any: expression_label SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 331: /* expression_any: expression_goto SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 332: /* expression_any: "pass" SEMICOLON  */
                                                  { (yyval.pExpression) = nullptr; }
    break;

  case 333: /* $@21: %empty  */
                     {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 334: /* $@22: %empty  */
                         {
        yyextra->pop_nesteds();
    }
    break;

  case 335: /* expression_any: '{' $@21 expressions $@22 '}' expression_block_finally  */
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

  case 336: /* expressions: %empty  */
        {
        (yyval.pExpression) = new ExprBlock();
        (yyval.pExpression)->at = LineInfo(yyextra->g_FileAccessStack.back(),
            yylloc.first_column,yylloc.first_line,yylloc.last_column,yylloc.last_line);
    }
    break;

  case 337: /* expressions: expressions expression_any  */
                                                        {
        (yyval.pExpression) = (yyvsp[-1].pExpression);
        if ( (yyvsp[0].pExpression) ) {
            static_cast<ExprBlock*>((yyvsp[-1].pExpression))->list.push_back((yyvsp[0].pExpression));
        }
    }
    break;

  case 338: /* expressions: expressions error  */
                                 {
        (void)(yyvsp[-1].pExpression); /* gc_node — don't delete Expression */ (yyval.pExpression) = nullptr; YYABORT;
    }
    break;

  case 339: /* optional_expr_list: %empty  */
        { (yyval.pExpression) = nullptr; }
    break;

  case 340: /* optional_expr_list: expr_list optional_comma  */
                                            { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 341: /* optional_expr_map_tuple_list: %empty  */
        { (yyval.pExpression) = nullptr; }
    break;

  case 342: /* optional_expr_map_tuple_list: expr_map_tuple_list optional_comma  */
                                                      { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 343: /* type_declaration_no_options_list: type_declaration  */
                               {
        (yyval.pTypeDeclList) = new vector<Expression *>();
        (yyval.pTypeDeclList)->push_back(new ExprTypeDecl(tokAt(scanner,(yylsp[0])),(yyvsp[0].pTypeDecl)));
    }
    break;

  case 344: /* type_declaration_no_options_list: type_declaration_no_options_list c_or_s type_declaration  */
                                                                              {
        (yyval.pTypeDeclList) = (yyvsp[-2].pTypeDeclList);
        (yyval.pTypeDeclList)->push_back(new ExprTypeDecl(tokAt(scanner,(yylsp[0])),(yyvsp[0].pTypeDecl)));
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

  case 350: /* $@23: %empty  */
           { yyextra->das_arrow_depth ++; }
    break;

  case 351: /* $@24: %empty  */
                                                                           { yyextra->das_arrow_depth --; }
    break;

  case 352: /* new_type_declaration: '<' $@23 type_declaration '>' $@24  */
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

  case 362: /* expression_return: "return"  */
                        {
        (yyval.pExpression) = new ExprReturn(tokAt(scanner,(yylsp[0])),nullptr);
    }
    break;

  case 363: /* expression_return: "return" expr  */
                                      {
        (yyval.pExpression) = new ExprReturn(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression));
    }
    break;

  case 364: /* expression_return: "return" "<-" expr  */
                                             {
        auto pRet = new ExprReturn(tokAt(scanner,(yylsp[-2])),(yyvsp[0].pExpression));
        pRet->moveSemantics = true;
        (yyval.pExpression) = pRet;
    }
    break;

  case 365: /* expression_yield: "yield" expr  */
                                     {
        (yyval.pExpression) = new ExprYield(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression));
    }
    break;

  case 366: /* expression_yield: "yield" "<-" expr  */
                                            {
        auto pRet = new ExprYield(tokAt(scanner,(yylsp[-2])),(yyvsp[0].pExpression));
        pRet->moveSemantics = true;
        (yyval.pExpression) = pRet;
    }
    break;

  case 367: /* expression_try_catch: "try" expression_block "recover" expression_block  */
                                                                                       {
        (yyval.pExpression) = new ExprTryCatch(tokAt(scanner,(yylsp[-3])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
    }
    break;

  case 368: /* kwd_let_var_or_nothing: "let"  */
                 { (yyval.b) = true; }
    break;

  case 369: /* kwd_let_var_or_nothing: "var"  */
                 { (yyval.b) = false; }
    break;

  case 370: /* kwd_let_var_or_nothing: %empty  */
                    { (yyval.b) = true; }
    break;

  case 371: /* kwd_let: "let"  */
                 { (yyval.b) = true; }
    break;

  case 372: /* kwd_let: "var"  */
                 { (yyval.b) = false; }
    break;

  case 373: /* optional_in_scope: "inscope"  */
                    { (yyval.b) = true; }
    break;

  case 374: /* optional_in_scope: %empty  */
                     { (yyval.b) = false; }
    break;

  case 375: /* tuple_expansion: "name"  */
                    {
        (yyval.pNameList) = new vector<string>();
        (yyval.pNameList)->push_back(*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 376: /* tuple_expansion: tuple_expansion ',' "name"  */
                                             {
        (yyvsp[-2].pNameList)->push_back(*(yyvsp[0].s));
        delete (yyvsp[0].s);
        (yyval.pNameList) = (yyvsp[-2].pNameList);
    }
    break;

  case 377: /* tuple_expansion_variable_declaration: '(' tuple_expansion ')' ':' type_declaration_no_options copy_or_move_or_clone expr SEMICOLON  */
                                                                                                                                {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-6].pNameList),tokAt(scanner,(yylsp[-6])),(yyvsp[-3].pTypeDecl),(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
        (yyval.pVarDecl)->isTupleExpansion = true;
    }
    break;

  case 378: /* tuple_expansion_variable_declaration: '(' tuple_expansion ')' optional_ref copy_or_move_or_clone expr SEMICOLON  */
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

  case 379: /* expression_let: kwd_let optional_in_scope let_variable_declaration  */
                                                                 {
        (yyval.pExpression) = ast_Let(scanner,(yyvsp[-2].b),(yyvsp[-1].b),(yyvsp[0].pVarDecl),tokAt(scanner,(yylsp[-2])),tokAt(scanner,(yylsp[0])));
    }
    break;

  case 380: /* expression_let: kwd_let optional_in_scope tuple_expansion_variable_declaration  */
                                                                             {
        (yyval.pExpression) = ast_Let(scanner,(yyvsp[-2].b),(yyvsp[-1].b),(yyvsp[0].pVarDecl),tokAt(scanner,(yylsp[-2])),tokAt(scanner,(yylsp[0])));
    }
    break;

  case 381: /* expression_let: kwd_let optional_in_scope '{' variable_declaration_list '}'  */
                                                                               {
        (yyval.pExpression) = ast_LetList(scanner,(yyvsp[-4].b),(yyvsp[-3].b),*(yyvsp[-1].pVarDeclList),tokAt(scanner,(yylsp[-4])),tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 382: /* $@25: %empty  */
                          { yyextra->das_arrow_depth ++; }
    break;

  case 383: /* $@26: %empty  */
                                                                                                 { yyextra->das_arrow_depth --; }
    break;

  case 384: /* expr_cast: "cast" '<' $@25 type_declaration_no_options '>' $@26 '(' expr ')'  */
                                                                                                                                                        {
        (yyval.pExpression) = new ExprCast(tokAt(scanner,(yylsp[-8])),(yyvsp[-1].pExpression),(yyvsp[-5].pTypeDecl));
    }
    break;

  case 385: /* $@27: %empty  */
                            { yyextra->das_arrow_depth ++; }
    break;

  case 386: /* $@28: %empty  */
                                                                                                   { yyextra->das_arrow_depth --; }
    break;

  case 387: /* expr_cast: "upcast" '<' $@27 type_declaration_no_options '>' $@28 '(' expr ')'  */
                                                                                                                                                          {
        auto pCast = new ExprCast(tokAt(scanner,(yylsp[-8])),(yyvsp[-1].pExpression),(yyvsp[-5].pTypeDecl));
        pCast->upcast = true;
        (yyval.pExpression) = pCast;
    }
    break;

  case 388: /* $@29: %empty  */
                                 { yyextra->das_arrow_depth ++; }
    break;

  case 389: /* $@30: %empty  */
                                                                                                        { yyextra->das_arrow_depth --; }
    break;

  case 390: /* expr_cast: "reinterpret" '<' $@29 type_declaration_no_options '>' $@30 '(' expr ')'  */
                                                                                                                                                               {
        auto pCast = new ExprCast(tokAt(scanner,(yylsp[-8])),(yyvsp[-1].pExpression),(yyvsp[-5].pTypeDecl));
        pCast->reinterpret = true;
        (yyval.pExpression) = pCast;
    }
    break;

  case 391: /* $@31: %empty  */
                         { yyextra->das_arrow_depth ++; }
    break;

  case 392: /* $@32: %empty  */
                                                                                     { yyextra->das_arrow_depth --; }
    break;

  case 393: /* expr_type_decl: "type" '<' $@31 type_declaration '>' $@32  */
                                                                                                                      {
        (yyval.pExpression) = new ExprTypeDecl(tokAt(scanner,(yylsp[-5])),(yyvsp[-2].pTypeDecl));
    }
    break;

  case 394: /* expr_type_info: "typeinfo" name_in_namespace '(' expr ')'  */
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

  case 395: /* expr_type_info: "typeinfo" name_in_namespace '<' "name" '>' '(' expr ')'  */
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

  case 396: /* expr_type_info: "typeinfo" name_in_namespace '<' "name" c_or_s "name" '>' '(' expr ')'  */
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

  case 397: /* expr_list: expr  */
                      {
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 398: /* expr_list: "<-" expr  */
                             {
            (yyval.pExpression) = ast_makeMoveArgument(scanner, (yyvsp[0].pExpression), tokAt(scanner,(yylsp[0])));
    }
    break;

  case 399: /* expr_list: expr_list ',' expr  */
                                        {
            (yyval.pExpression) = new ExprSequence(tokAt(scanner,(yylsp[-2])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
    }
    break;

  case 400: /* expr_list: expr_list ',' "<-" expr  */
                                                   {
            (yyval.pExpression) = new ExprSequence(tokAt(scanner,(yylsp[-3])),(yyvsp[-3].pExpression),ast_makeMoveArgument(scanner, (yyvsp[0].pExpression), tokAt(scanner,(yylsp[0]))));
    }
    break;

  case 401: /* block_or_simple_block: expression_block  */
                                    { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 402: /* block_or_simple_block: "=>" expr_no_bracket  */
                                                   {
            auto retE = new ExprReturn(tokAt(scanner,(yylsp[-1])), (yyvsp[0].pExpression));
            auto blkE = new ExprBlock();
            blkE->at = tokAt(scanner,(yylsp[-1]));
            blkE->list.push_back(retE);
            (yyval.pExpression) = blkE;
    }
    break;

  case 403: /* block_or_simple_block: "=>" "<-" expr_no_bracket  */
                                                          {
            auto retE = new ExprReturn(tokAt(scanner,(yylsp[-2])), (yyvsp[0].pExpression));
            retE->moveSemantics = true;
            auto blkE = new ExprBlock();
            blkE->at = tokAt(scanner,(yylsp[-2]));
            blkE->list.push_back(retE);
            (yyval.pExpression) = blkE;
    }
    break;

  case 404: /* block_or_lambda: '$'  */
                { (yyval.i) = 0;   /* block */  }
    break;

  case 405: /* block_or_lambda: '@'  */
                { (yyval.i) = 1;   /* lambda */ }
    break;

  case 406: /* block_or_lambda: "@@"  */
                  { (yyval.i) = 2;   /* local function */ }
    break;

  case 407: /* capture_entry: '&' "name"  */
                                    { (yyval.pCapt) = new CaptureEntry(*(yyvsp[0].s),CaptureMode::capture_by_reference); delete (yyvsp[0].s); }
    break;

  case 408: /* capture_entry: '=' "name"  */
                                    { (yyval.pCapt) = new CaptureEntry(*(yyvsp[0].s),CaptureMode::capture_by_copy); delete (yyvsp[0].s); }
    break;

  case 409: /* capture_entry: "<-" "name"  */
                                    { (yyval.pCapt) = new CaptureEntry(*(yyvsp[0].s),CaptureMode::capture_by_move); delete (yyvsp[0].s); }
    break;

  case 410: /* capture_entry: ":=" "name"  */
                                    { (yyval.pCapt) = new CaptureEntry(*(yyvsp[0].s),CaptureMode::capture_by_clone); delete (yyvsp[0].s); }
    break;

  case 411: /* capture_entry: "name" '(' "name" ')'  */
                                    { (yyval.pCapt) = ast_makeCaptureEntry(scanner,tokAt(scanner,(yylsp[-3])),*(yyvsp[-3].s),*(yyvsp[-1].s)); delete (yyvsp[-3].s); delete (yyvsp[-1].s); }
    break;

  case 412: /* capture_list: capture_entry  */
                         {
        (yyval.pCaptList) = new vector<CaptureEntry>();
        (yyval.pCaptList)->push_back(*(yyvsp[0].pCapt));
        delete (yyvsp[0].pCapt);
    }
    break;

  case 413: /* capture_list: capture_list ',' capture_entry  */
                                               {
        (yyvsp[-2].pCaptList)->push_back(*(yyvsp[0].pCapt));
        delete (yyvsp[0].pCapt);
        (yyval.pCaptList) = (yyvsp[-2].pCaptList);
    }
    break;

  case 414: /* optional_capture_list: %empty  */
        { (yyval.pCaptList) = nullptr; }
    break;

  case 415: /* optional_capture_list: "capture" '(' capture_list ')'  */
                                             { (yyval.pCaptList) = (yyvsp[-1].pCaptList); }
    break;

  case 416: /* expr_full_block: block_or_lambda optional_annotation_list optional_capture_list optional_function_argument_list optional_function_type optional_emit_semis block_or_simple_block  */
                                                                                                                {
        (yyval.pExpression) = ast_makeBlock(scanner,(yyvsp[-6].i),(yyvsp[-5].faList),(yyvsp[-4].pCaptList),(yyvsp[-3].pVarDeclList),(yyvsp[-2].pTypeDecl),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[0])),tokAt(scanner,(yylsp[-5])),tokAt(scanner,(yylsp[-4])));
    }
    break;

  case 417: /* expr_full_block_assumed_piped: block_or_lambda optional_annotation_list optional_capture_list optional_function_argument_list optional_function_type optional_emit_semis block_or_simple_block  */
                                                                                                                {
        (yyval.pExpression) = ast_makeBlock(scanner,(yyvsp[-6].i),(yyvsp[-5].faList),(yyvsp[-4].pCaptList),(yyvsp[-3].pVarDeclList),(yyvsp[-2].pTypeDecl),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[0])),tokAt(scanner,(yylsp[-5])),tokAt(scanner,(yylsp[-4])));
    }
    break;

  case 418: /* expr_full_block_assumed_piped: '{' expressions '}'  */
                                   {
        (yyval.pExpression) = ast_makeBlock(scanner,0,nullptr,nullptr,nullptr,new TypeDecl(Type::autoinfer),(yyvsp[-1].pExpression),tokAt(scanner,(yylsp[-1])),tokAt(scanner,(yylsp[-1])),LineInfo());
    }
    break;

  case 419: /* expr_numeric_const: "integer constant"  */
                                              { (yyval.pExpression) = new ExprConstInt(tokAt(scanner,(yylsp[0])),(int32_t)(yyvsp[0].i)); }
    break;

  case 420: /* expr_numeric_const: "unsigned integer constant"  */
                                              { (yyval.pExpression) = new ExprConstUInt(tokAt(scanner,(yylsp[0])),(uint32_t)(yyvsp[0].ui)); }
    break;

  case 421: /* expr_numeric_const: "long integer constant"  */
                                              { (yyval.pExpression) = new ExprConstInt64(tokAt(scanner,(yylsp[0])),(int64_t)(yyvsp[0].i64)); }
    break;

  case 422: /* expr_numeric_const: "unsigned long integer constant"  */
                                              { (yyval.pExpression) = new ExprConstUInt64(tokAt(scanner,(yylsp[0])),(uint64_t)(yyvsp[0].ui64)); }
    break;

  case 423: /* expr_numeric_const: "unsigned int8 constant"  */
                                              { (yyval.pExpression) = new ExprConstUInt8(tokAt(scanner,(yylsp[0])),(uint8_t)(yyvsp[0].ui)); }
    break;

  case 424: /* expr_numeric_const: "floating point constant"  */
                                              { (yyval.pExpression) = new ExprConstFloat(tokAt(scanner,(yylsp[0])),(float)(yyvsp[0].fd)); }
    break;

  case 425: /* expr_numeric_const: "double constant"  */
                                              { (yyval.pExpression) = new ExprConstDouble(tokAt(scanner,(yylsp[0])),(double)(yyvsp[0].d)); }
    break;

  case 426: /* expr_assign_no_bracket: expr_no_bracket  */
                                                        { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 427: /* expr_assign_no_bracket: expr_no_bracket '=' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprCopy(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression)); }
    break;

  case 428: /* expr_assign_no_bracket: expr_no_bracket "<-" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprMove(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 429: /* expr_assign_no_bracket: expr_no_bracket "<-" make_table_decl  */
                                                                   { (yyval.pExpression) = new ExprMove(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 430: /* expr_assign_no_bracket: expr_no_bracket "<-" array_comprehension  */
                                                                     { (yyval.pExpression) = new ExprMove(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 431: /* expr_assign_no_bracket: expr_no_bracket ":=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprClone(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 432: /* expr_assign_no_bracket: expr_no_bracket "&=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"&=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 433: /* expr_assign_no_bracket: expr_no_bracket "|=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"|=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 434: /* expr_assign_no_bracket: expr_no_bracket "^=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"^=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 435: /* expr_assign_no_bracket: expr_no_bracket "&&=" expr_no_bracket  */
                                                                      { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"&&=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 436: /* expr_assign_no_bracket: expr_no_bracket "||=" expr_no_bracket  */
                                                                      { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"||=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 437: /* expr_assign_no_bracket: expr_no_bracket "^^=" expr_no_bracket  */
                                                                      { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"^^=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 438: /* expr_assign_no_bracket: expr_no_bracket "+=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"+=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 439: /* expr_assign_no_bracket: expr_no_bracket "-=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"-=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 440: /* expr_assign_no_bracket: expr_no_bracket "*=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"*=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 441: /* expr_assign_no_bracket: expr_no_bracket "/=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"/=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 442: /* expr_assign_no_bracket: expr_no_bracket "%=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"%=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 443: /* expr_assign_no_bracket: expr_no_bracket "<<=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<<=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 444: /* expr_assign_no_bracket: expr_no_bracket ">>=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">>=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 445: /* expr_assign_no_bracket: expr_no_bracket "<<<=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<<<=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 446: /* expr_assign_no_bracket: expr_no_bracket ">>>=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">>>=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 447: /* expr_named_call: name_in_namespace '(' '[' make_struct_fields ']' ')'  */
                                                                         {
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-5])),*(yyvsp[-5].s));
        nc->arguments = (yyvsp[-2].pMakeStruct);
        delete (yyvsp[-5].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 448: /* expr_named_call: name_in_namespace '(' expr_list ',' '[' make_struct_fields ']' ')'  */
                                                                                                  {
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-7])),*(yyvsp[-7].s));
        nc->nonNamedArguments = sequenceToList((yyvsp[-5].pExpression));
        nc->arguments = (yyvsp[-2].pMakeStruct);
        delete (yyvsp[-7].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 449: /* expr_named_call: name_in_namespace '(' expr_list ',' make_struct_fields ')'  */
                                                                                          {
        // bracket-less mixed named call: foo(pos..., name = value) -- named args are a strict suffix
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-5])),*(yyvsp[-5].s));
        nc->nonNamedArguments = sequenceToList((yyvsp[-3].pExpression));
        nc->arguments = (yyvsp[-1].pMakeStruct);
        delete (yyvsp[-5].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 450: /* expr_method_call_no_bracket: expr_no_bracket "->" "name" '(' ')'  */
                                                                    {
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-3])), (yyvsp[-4].pExpression), *(yyvsp[-2].s));
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-4]),(yyloc));
        delete (yyvsp[-2].s);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 451: /* expr_method_call_no_bracket: expr_no_bracket "->" "name" '(' expr_list ')'  */
                                                                                         {
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-4])), (yyvsp[-5].pExpression), *(yyvsp[-3].s));
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-5]),(yyloc));
        auto callArgs = sequenceToList((yyvsp[-1].pExpression));
        pInvoke->arguments.insert ( pInvoke->arguments.end(), callArgs.begin(), callArgs.end() );
        delete (yyvsp[-3].s);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 452: /* expr_method_call_no_bracket: expr_no_bracket "->" "name" '(' '[' make_struct_fields ']' ')'  */
                                                                                                     {
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-5])),*(yyvsp[-5].s));
        nc->methodCall = true;
        nc->arguments = (yyvsp[-2].pMakeStruct);
        nc->nonNamedArguments.push_back((yyvsp[-7].pExpression));
        delete (yyvsp[-5].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 453: /* expr_method_call_no_bracket: expr_no_bracket "->" "name" '(' expr_list ',' make_struct_fields ')'  */
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

  case 454: /* expr_method_call_no_bracket: expr_no_bracket "->" "name" '(' make_struct_fields ')'  */
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

  case 455: /* func_addr_name: name_in_namespace  */
                                    {
        (yyval.pExpression) = new ExprAddr(tokAt(scanner,(yylsp[0])),*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 456: /* func_addr_name: "$i" '(' expr ')'  */
                                          {
        auto expr = new ExprAddr(tokAt(scanner,(yylsp[-3])),"``MACRO``TAG``ADDR``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression), expr, "i");
    }
    break;

  case 457: /* func_addr_expr: "@@" func_addr_name  */
                                            {
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 458: /* $@33: %empty  */
                      { yyextra->das_arrow_depth ++; }
    break;

  case 459: /* $@34: %empty  */
                                                                                                  { yyextra->das_arrow_depth --; }
    break;

  case 460: /* func_addr_expr: "@@" '<' $@33 type_declaration_no_options '>' $@34 func_addr_name  */
                                                                                                                                                         {
        auto expr = (ExprAddr *) ((yyvsp[0].pExpression)->rtti_isAddr() ? (yyvsp[0].pExpression) : (((ExprTag *) (yyvsp[0].pExpression))->value));
        expr->funcType = (yyvsp[-3].pTypeDecl);
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 461: /* $@35: %empty  */
                      { yyextra->das_arrow_depth ++; }
    break;

  case 462: /* $@36: %empty  */
                                                                                                                                { yyextra->das_arrow_depth --; }
    break;

  case 463: /* func_addr_expr: "@@" '<' $@35 optional_function_argument_list optional_function_type '>' $@36 func_addr_name  */
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

  case 464: /* expr_field_no_bracket: expr_no_bracket '.' "name"  */
                                                         {
        (yyval.pExpression) = new ExprField(tokAt(scanner,(yylsp[-1])), tokAt(scanner,(yylsp[0])), (yyvsp[-2].pExpression), *(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 465: /* expr_field_no_bracket: expr_no_bracket '.' '.' "name"  */
                                                             {
        (yyval.pExpression) = new ExprField(tokAt(scanner,(yylsp[-1])), tokAt(scanner,(yylsp[0])), (yyvsp[-3].pExpression), *(yyvsp[0].s), true);
        delete (yyvsp[0].s);
    }
    break;

  case 466: /* expr_field_no_bracket: expr_no_bracket '.' "name" '(' ')'  */
                                                                 {
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-3])), (yyvsp[-4].pExpression), *(yyvsp[-2].s));
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-4]),(yyloc));
        delete (yyvsp[-2].s);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 467: /* expr_field_no_bracket: expr_no_bracket '.' "name" '(' expr_list ')'  */
                                                                                      {
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-4])), (yyvsp[-5].pExpression), *(yyvsp[-3].s));
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-5]),(yyloc));
        auto callArgs = sequenceToList((yyvsp[-1].pExpression));
        pInvoke->arguments.insert ( pInvoke->arguments.end(), callArgs.begin(), callArgs.end() );
        delete (yyvsp[-3].s);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 468: /* expr_field_no_bracket: expr_no_bracket '.' "name" '(' '[' make_struct_fields ']' ')'  */
                                                                                                  {
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-5])),*(yyvsp[-5].s));
        nc->methodCall = true;
        nc->arguments = (yyvsp[-2].pMakeStruct);
        nc->nonNamedArguments.push_back((yyvsp[-7].pExpression));
        delete (yyvsp[-5].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 469: /* expr_field_no_bracket: expr_no_bracket '.' "name" '(' expr_list ',' make_struct_fields ')'  */
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

  case 470: /* expr_field_no_bracket: expr_no_bracket '.' "name" '(' make_struct_fields ')'  */
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

  case 471: /* expr_field_no_bracket: expr_no_bracket '.' basic_type_declaration '(' ')'  */
                                                                                   {
        auto method_name = das_to_string((yyvsp[-2].type));
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-3])), (yyvsp[-4].pExpression), method_name);
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-4]),(yyloc));
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 472: /* expr_field_no_bracket: expr_no_bracket '.' basic_type_declaration '(' expr_list ')'  */
                                                                                                        {
        auto method_name = das_to_string((yyvsp[-3].type));
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-4])), (yyvsp[-5].pExpression), method_name);
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-5]),(yyloc));
        auto callArgs = sequenceToList((yyvsp[-1].pExpression));
        pInvoke->arguments.insert ( pInvoke->arguments.end(), callArgs.begin(), callArgs.end() );
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 473: /* $@37: %empty  */
                                          { yyextra->das_suppress_errors=true; }
    break;

  case 474: /* $@38: %empty  */
                                                                                       { yyextra->das_suppress_errors=false; }
    break;

  case 475: /* expr_field_no_bracket: expr_no_bracket '.' $@37 error $@38  */
                                                                                                                               {
        (yyval.pExpression) = new ExprField(tokAt(scanner,(yylsp[-3])), tokAt(scanner,(yylsp[-3])), (yyvsp[-4].pExpression), "");
        yyerrok;
    }
    break;

  case 476: /* expr_call: name_in_namespace '(' ')'  */
                                               {
            (yyval.pExpression) = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-2])),tokAt(scanner,(yylsp[0])),*(yyvsp[-2].s));
            delete (yyvsp[-2].s);
    }
    break;

  case 477: /* expr_call: name_in_namespace '(' "uninitialized" ')'  */
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

  case 478: /* expr_call: name_in_namespace '(' make_struct_single ')'  */
                                                               {
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->at = tokAt(scanner,(yylsp[-3]));
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = yyextra->g_Program->makeTypeDeclaration(tokAt(scanner,(yylsp[-3])),*(yyvsp[-3].s));
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = true;
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
            delete (yyvsp[-3].s);
            (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 479: /* expr_call: name_in_namespace '(' "uninitialized" make_struct_single ')'  */
                                                                                 {
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->at = tokAt(scanner,(yylsp[-4]));
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = yyextra->g_Program->makeTypeDeclaration(tokAt(scanner,(yylsp[-4])),*(yyvsp[-4].s));
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = false;
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
            delete (yyvsp[-4].s);
            (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 480: /* expr_call: name_in_namespace '(' expr_list ')'  */
                                                                    {
            (yyval.pExpression) = parseFunctionArguments(yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-3])),tokAt(scanner,(yylsp[0])),*(yyvsp[-3].s)),(yyvsp[-1].pExpression));
            delete (yyvsp[-3].s);
    }
    break;

  case 481: /* expr_call: basic_type_declaration '(' ')'  */
                                                    {
        (yyval.pExpression) = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-2])),tokAt(scanner,(yylsp[0])),das_to_string((yyvsp[-2].type)));
    }
    break;

  case 482: /* expr_call: basic_type_declaration '(' expr_list ')'  */
                                                                         {
        (yyval.pExpression) = parseFunctionArguments(yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-3])),tokAt(scanner,(yylsp[0])),das_to_string((yyvsp[-3].type))),(yyvsp[-1].pExpression));
    }
    break;

  case 483: /* expr: expr_no_bracket  */
                                       { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 484: /* expr: make_table_decl  */
                                     { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 485: /* expr: array_comprehension  */
                                     { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 486: /* expr_no_bracket: "null"  */
                                              { (yyval.pExpression) = new ExprConstPtr(tokAt(scanner,(yylsp[0])),nullptr); }
    break;

  case 487: /* expr_no_bracket: name_in_namespace  */
                                              { (yyval.pExpression) = new ExprVar(tokAt(scanner,(yylsp[0])),*(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 488: /* expr_no_bracket: expr_numeric_const  */
                                              { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 489: /* expr_no_bracket: expr_reader  */
                                              { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 490: /* expr_no_bracket: string_builder  */
                                              { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 491: /* expr_no_bracket: make_decl_no_bracket  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 492: /* expr_no_bracket: "true"  */
                                              { (yyval.pExpression) = new ExprConstBool(tokAt(scanner,(yylsp[0])),true); }
    break;

  case 493: /* expr_no_bracket: "false"  */
                                              { (yyval.pExpression) = new ExprConstBool(tokAt(scanner,(yylsp[0])),false); }
    break;

  case 494: /* expr_no_bracket: expr_field_no_bracket  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 495: /* expr_no_bracket: expr_mtag_no_bracket  */
                                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 496: /* expr_no_bracket: '!' expr_no_bracket  */
                                                         { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"!",(yyvsp[0].pExpression)); }
    break;

  case 497: /* expr_no_bracket: '~' expr_no_bracket  */
                                                         { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"~",(yyvsp[0].pExpression)); }
    break;

  case 498: /* expr_no_bracket: '+' expr_no_bracket  */
                                                             { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"+",(yyvsp[0].pExpression)); }
    break;

  case 499: /* expr_no_bracket: '-' expr_no_bracket  */
                                                             { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"-",(yyvsp[0].pExpression)); }
    break;

  case 500: /* expr_no_bracket: expr_no_bracket "<<" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<<", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 501: /* expr_no_bracket: expr_no_bracket ">>" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">>", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 502: /* expr_no_bracket: expr_no_bracket "<<<" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<<<", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 503: /* expr_no_bracket: expr_no_bracket ">>>" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">>>", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 504: /* expr_no_bracket: expr_no_bracket '+' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"+", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 505: /* expr_no_bracket: expr_no_bracket '-' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"-", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 506: /* expr_no_bracket: expr_no_bracket '*' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"*", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 507: /* expr_no_bracket: expr_no_bracket '/' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"/", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 508: /* expr_no_bracket: expr_no_bracket '%' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"%", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 509: /* expr_no_bracket: expr_no_bracket '<' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 510: /* expr_no_bracket: expr_no_bracket '>' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 511: /* expr_no_bracket: expr_no_bracket "==" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"==", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 512: /* expr_no_bracket: expr_no_bracket "!=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"!=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 513: /* expr_no_bracket: expr_no_bracket "<=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 514: /* expr_no_bracket: expr_no_bracket ">=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 515: /* expr_no_bracket: expr_no_bracket '&' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"&", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 516: /* expr_no_bracket: expr_no_bracket '|' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"|", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 517: /* expr_no_bracket: expr_no_bracket '^' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"^", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 518: /* expr_no_bracket: expr_no_bracket "&&" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"&&", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 519: /* expr_no_bracket: expr_no_bracket "||" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"||", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 520: /* expr_no_bracket: expr_no_bracket "^^" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"^^", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 521: /* expr_no_bracket: expr_no_bracket ".." expr_no_bracket  */
                                                                   {
        auto itv = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-1])),"interval");
        itv->arguments.push_back((yyvsp[-2].pExpression));
        itv->arguments.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = itv;
    }
    break;

  case 522: /* expr_no_bracket: "++" expr_no_bracket  */
                                                            { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"++", (yyvsp[0].pExpression)); }
    break;

  case 523: /* expr_no_bracket: "--" expr_no_bracket  */
                                                            { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"--", (yyvsp[0].pExpression)); }
    break;

  case 524: /* expr_no_bracket: expr_no_bracket "++"  */
                                                            { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[0])),"+++", (yyvsp[-1].pExpression)); }
    break;

  case 525: /* expr_no_bracket: expr_no_bracket "--"  */
                                                            { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[0])),"---", (yyvsp[-1].pExpression)); }
    break;

  case 526: /* expr_no_bracket: '(' expr_list optional_comma ')'  */
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

  case 527: /* expr_no_bracket: '(' make_struct_single ')'  */
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

  case 528: /* expr_no_bracket: expr_no_bracket '[' expr ']'  */
                                                            { (yyval.pExpression) = new ExprAt(tokAt(scanner,(yylsp[-2])), (yyvsp[-3].pExpression), (yyvsp[-1].pExpression)); }
    break;

  case 529: /* expr_no_bracket: expr_no_bracket '.' '[' expr ']'  */
                                                                { (yyval.pExpression) = new ExprAt(tokAt(scanner,(yylsp[-2])), (yyvsp[-4].pExpression), (yyvsp[-1].pExpression), true); }
    break;

  case 530: /* expr_no_bracket: expr_no_bracket "?[" expr ']'  */
                                                            { (yyval.pExpression) = new ExprSafeAt(tokAt(scanner,(yylsp[-2])), (yyvsp[-3].pExpression), (yyvsp[-1].pExpression)); }
    break;

  case 531: /* expr_no_bracket: expr_no_bracket '.' "?[" expr ']'  */
                                                                { (yyval.pExpression) = new ExprSafeAt(tokAt(scanner,(yylsp[-2])), (yyvsp[-4].pExpression), (yyvsp[-1].pExpression), true); }
    break;

  case 532: /* expr_no_bracket: expr_no_bracket "?." "name"  */
                                                            { (yyval.pExpression) = new ExprSafeField(tokAt(scanner,(yylsp[-1])), tokAt(scanner,(yylsp[0])), (yyvsp[-2].pExpression), *(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 533: /* expr_no_bracket: expr_no_bracket '.' "?." "name"  */
                                                                { (yyval.pExpression) = new ExprSafeField(tokAt(scanner,(yylsp[-1])), tokAt(scanner,(yylsp[0])), (yyvsp[-3].pExpression), *(yyvsp[0].s), true); delete (yyvsp[0].s); }
    break;

  case 534: /* expr_no_bracket: func_addr_expr  */
                                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 535: /* expr_no_bracket: expr_call  */
                        { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 536: /* expr_no_bracket: '*' expr_no_bracket  */
                                                              { (yyval.pExpression) = new ExprPtr2Ref(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression)); }
    break;

  case 537: /* expr_no_bracket: "deref" '(' expr ')'  */
                                                   { (yyval.pExpression) = new ExprPtr2Ref(tokAt(scanner,(yylsp[-3])),(yyvsp[-1].pExpression)); }
    break;

  case 538: /* expr_no_bracket: "addr" '(' expr ')'  */
                                                   { (yyval.pExpression) = new ExprRef2Ptr(tokAt(scanner,(yylsp[-3])),(yyvsp[-1].pExpression)); }
    break;

  case 539: /* expr_no_bracket: expr_generator  */
                                                   { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 540: /* expr_no_bracket: expr_no_bracket "??" expr_no_bracket  */
                                                                         { (yyval.pExpression) = new ExprNullCoalescing(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression)); }
    break;

  case 541: /* expr_no_bracket: expr_no_bracket '?' expr_no_bracket ':' expr_no_bracket  */
                                                                                           {
            (yyval.pExpression) = new ExprOp3(tokAt(scanner,(yylsp[-3])),"?",(yyvsp[-4].pExpression),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
        }
    break;

  case 542: /* $@39: %empty  */
                                                          { yyextra->das_arrow_depth ++; }
    break;

  case 543: /* $@40: %empty  */
                                                                                                                                 { yyextra->das_arrow_depth --; }
    break;

  case 544: /* expr_no_bracket: expr_no_bracket "is" "type" '<' $@39 type_declaration_no_options '>' $@40  */
                                                                                                                                                                  {
        (yyval.pExpression) = new ExprIs(tokAt(scanner,(yylsp[-6])),(yyvsp[-7].pExpression),(yyvsp[-2].pTypeDecl));
    }
    break;

  case 545: /* expr_no_bracket: expr_no_bracket "is" basic_type_declaration  */
                                                                          {
        auto vdecl = new TypeDecl((yyvsp[0].type));
        vdecl->at = tokAt(scanner,(yylsp[0]));
        (yyval.pExpression) = new ExprIs(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),vdecl);
    }
    break;

  case 546: /* expr_no_bracket: expr_no_bracket "is" "name"  */
                                                         {
        (yyval.pExpression) = new ExprIsVariant(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 547: /* expr_no_bracket: expr_no_bracket "as" "name"  */
                                                         {
        (yyval.pExpression) = new ExprAsVariant(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 548: /* $@41: %empty  */
                                                          { yyextra->das_arrow_depth ++; }
    break;

  case 549: /* $@42: %empty  */
                                                                                                                      { yyextra->das_arrow_depth --; }
    break;

  case 550: /* expr_no_bracket: expr_no_bracket "as" "type" '<' $@41 type_declaration '>' $@42  */
                                                                                                                                                       {
        auto vname = (yyvsp[-2].pTypeDecl)->describe();
        (yyval.pExpression) = new ExprAsVariant(tokAt(scanner,(yylsp[-6])),(yyvsp[-7].pExpression),vname);
        delete (yyvsp[-2].pTypeDecl);
    }
    break;

  case 551: /* expr_no_bracket: expr_no_bracket "as" basic_type_declaration  */
                                                                          {
        (yyval.pExpression) = new ExprAsVariant(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),das_to_string((yyvsp[0].type)));
    }
    break;

  case 552: /* expr_no_bracket: expr_no_bracket '?' "as" "name"  */
                                                             {
        (yyval.pExpression) = new ExprSafeAsVariant(tokAt(scanner,(yylsp[-1])),(yyvsp[-3].pExpression),*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 553: /* $@43: %empty  */
                                                              { yyextra->das_arrow_depth ++; }
    break;

  case 554: /* $@44: %empty  */
                                                                                                                          { yyextra->das_arrow_depth --; }
    break;

  case 555: /* expr_no_bracket: expr_no_bracket '?' "as" "type" '<' $@43 type_declaration '>' $@44  */
                                                                                                                                                           {
        auto vname = (yyvsp[-2].pTypeDecl)->describe();
        (yyval.pExpression) = new ExprSafeAsVariant(tokAt(scanner,(yylsp[-6])),(yyvsp[-8].pExpression),vname);
        delete (yyvsp[-2].pTypeDecl);
    }
    break;

  case 556: /* expr_no_bracket: expr_no_bracket '?' "as" basic_type_declaration  */
                                                                              {
        (yyval.pExpression) = new ExprSafeAsVariant(tokAt(scanner,(yylsp[-1])),(yyvsp[-3].pExpression),das_to_string((yyvsp[0].type)));
    }
    break;

  case 557: /* expr_no_bracket: expr_type_info  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 558: /* expr_no_bracket: expr_type_decl  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 559: /* expr_no_bracket: expr_cast  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 560: /* expr_no_bracket: expr_new  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 561: /* expr_no_bracket: expr_method_call_no_bracket  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 562: /* expr_no_bracket: expr_named_call  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 563: /* expr_no_bracket: expr_full_block  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 564: /* expr_no_bracket: expr_no_bracket "<|" expr_no_bracket  */
                                                                      { (yyval.pExpression) = ast_lpipe(scanner,(yyvsp[-2].pExpression),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[-1])),true); }
    break;

  case 565: /* expr_no_bracket: expr_no_bracket "|>" expr_no_bracket  */
                                                                      { (yyval.pExpression) = ast_rpipe(scanner,(yyvsp[-2].pExpression),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[-1]))); }
    break;

  case 566: /* expr_no_bracket: expr_no_bracket "|>" basic_type_declaration  */
                                                                     {
        auto fncall = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[0])),tokAt(scanner,(yylsp[0])),das_to_string((yyvsp[0].type)));
        (yyval.pExpression) = ast_rpipe(scanner,(yyvsp[-2].pExpression),fncall,tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 567: /* expr_no_bracket: expr_call_pipe_no_bracket  */
                                        { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 568: /* expr_no_bracket: "unsafe" '(' expr ')'  */
                                         {
            (yyvsp[-1].pExpression)->alwaysSafe = true;
            (yyvsp[-1].pExpression)->userSaidItsSafe = true;
            (yyval.pExpression) = (yyvsp[-1].pExpression);
        }
    break;

  case 569: /* expr_no_bracket: expr_no_bracket "=>" expr_no_bracket  */
                                                               {
        ExprMakeTuple * mt = new ExprMakeTuple(tokAt(scanner,(yylsp[-1])));
        mt->values.push_back((yyvsp[-2].pExpression));
        mt->values.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = mt;
    }
    break;

  case 570: /* expr_no_bracket: expr_no_bracket "=>" make_table_decl  */
                                                               {
        ExprMakeTuple * mt = new ExprMakeTuple(tokAt(scanner,(yylsp[-1])));
        mt->values.push_back((yyvsp[-2].pExpression));
        mt->values.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = mt;
    }
    break;

  case 571: /* expr_no_bracket: expr_no_bracket "=>" array_comprehension  */
                                                                   {
        ExprMakeTuple * mt = new ExprMakeTuple(tokAt(scanner,(yylsp[-1])));
        mt->values.push_back((yyvsp[-2].pExpression));
        mt->values.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = mt;
    }
    break;

  case 572: /* expr_generator: "generator" '<' type_declaration_no_options '>' optional_capture_list '(' ')'  */
                                                                                                              {
        (yyval.pExpression) = ast_makeGenerator(scanner,(yyvsp[-4].pTypeDecl),(yyvsp[-2].pCaptList),nullptr,tokAt(scanner,(yylsp[-6])),tokAt(scanner,(yylsp[-2])));
    }
    break;

  case 573: /* expr_generator: "generator" '<' type_declaration_no_options '>' optional_capture_list '(' expr ')'  */
                                                                                                                            {
        (yyval.pExpression) = ast_makeGenerator(scanner,(yyvsp[-5].pTypeDecl),(yyvsp[-3].pCaptList),(yyvsp[-1].pExpression),tokAt(scanner,(yylsp[-7])),tokAt(scanner,(yylsp[-3])));
    }
    break;

  case 574: /* expr_generator: "generator" '<' type_declaration_no_options '>' optional_capture_list optional_emit_semis expression_block  */
                                                                                                                                                  {
        auto closure = new ExprMakeBlock(tokAt(scanner,(yylsp[0])),(yyvsp[0].pExpression));
        ((ExprBlock *)(yyvsp[0].pExpression))->returnType = new TypeDecl(Type::autoinfer);
        (yyval.pExpression) = ast_makeGenerator(scanner,(yyvsp[-4].pTypeDecl),(yyvsp[-2].pCaptList),closure,tokAt(scanner,(yylsp[-6])),tokAt(scanner,(yylsp[-2])));
    }
    break;

  case 575: /* expr_mtag_no_bracket: "$$" '(' expr ')'  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"e"); }
    break;

  case 576: /* expr_mtag_no_bracket: "$i" '(' expr ')'  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"i"); }
    break;

  case 577: /* expr_mtag_no_bracket: "$v" '(' expr ')'  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"v"); }
    break;

  case 578: /* expr_mtag_no_bracket: "$b" '(' expr ')'  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"b"); }
    break;

  case 579: /* expr_mtag_no_bracket: "$a" '(' expr ')'  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"a"); }
    break;

  case 580: /* expr_mtag_no_bracket: "..."  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[0])),nullptr,"..."); }
    break;

  case 581: /* expr_mtag_no_bracket: "$c" '(' expr ')' '(' ')'  */
                                                            {
            auto ccall = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-5])),tokAt(scanner,(yylsp[0])),"``MACRO``TAG``CALL``");
            (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-5])),(yyvsp[-3].pExpression),ccall,"c");
        }
    break;

  case 582: /* expr_mtag_no_bracket: "$c" '(' expr ')' '(' expr_list ')'  */
                                                                                {
            auto ccall = parseFunctionArguments(yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-6])),tokAt(scanner,(yylsp[0])),"``MACRO``TAG``CALL``"),(yyvsp[-1].pExpression));
            (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-6])),(yyvsp[-4].pExpression),ccall,"c");
        }
    break;

  case 583: /* expr_mtag_no_bracket: expr_no_bracket '.' "$f" '(' expr ')'  */
                                                                           {
        auto cfield = new ExprField(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-1])), (yyvsp[-5].pExpression), "``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 584: /* expr_mtag_no_bracket: expr_no_bracket "?." "$f" '(' expr ')'  */
                                                                            {
        auto cfield = new ExprSafeField(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-1])), (yyvsp[-5].pExpression), "``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 585: /* expr_mtag_no_bracket: expr_no_bracket '.' '.' "$f" '(' expr ')'  */
                                                                               {
        auto cfield = new ExprField(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-1])), (yyvsp[-6].pExpression), "``MACRO``TAG``FIELD``", true);
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 586: /* expr_mtag_no_bracket: expr_no_bracket '.' "?." "$f" '(' expr ')'  */
                                                                                {
        auto cfield = new ExprSafeField(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-1])), (yyvsp[-6].pExpression), "``MACRO``TAG``FIELD``", true);
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 587: /* expr_mtag_no_bracket: expr_no_bracket "as" "$f" '(' expr ')'  */
                                                                              {
        auto cfield = new ExprAsVariant(tokAt(scanner,(yylsp[-4])),(yyvsp[-5].pExpression),"``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 588: /* expr_mtag_no_bracket: expr_no_bracket '?' "as" "$f" '(' expr ')'  */
                                                                                  {
        auto cfield = new ExprSafeAsVariant(tokAt(scanner,(yylsp[-4])),(yyvsp[-6].pExpression),"``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 589: /* expr_mtag_no_bracket: expr_no_bracket "is" "$f" '(' expr ')'  */
                                                                              {
        auto cfield = new ExprIsVariant(tokAt(scanner,(yylsp[-4])),(yyvsp[-5].pExpression),"``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 590: /* expr_mtag_no_bracket: "@@" "$c" '(' expr ')'  */
                                                           {
        auto ccall = new ExprAddr(tokAt(scanner,(yylsp[-4])),"``MACRO``TAG``ADDR``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-3])),(yyvsp[-1].pExpression),ccall,"c");
    }
    break;

  case 591: /* optional_field_annotation: %empty  */
                                      { (yyval.aaList) = nullptr; }
    break;

  case 592: /* optional_field_annotation: metadata_argument_list  */
                                      { (yyval.aaList) = (yyvsp[0].aaList); }
    break;

  case 593: /* optional_override: %empty  */
                      { (yyval.i) = OVERRIDE_NONE; }
    break;

  case 594: /* optional_override: "override"  */
                      { (yyval.i) = OVERRIDE_OVERRIDE; }
    break;

  case 595: /* optional_override: "sealed"  */
                      { (yyval.i) = OVERRIDE_SEALED; }
    break;

  case 596: /* optional_constant: %empty  */
                        { (yyval.b) = false; }
    break;

  case 597: /* optional_constant: "const"  */
                        { (yyval.b) = true; }
    break;

  case 598: /* optional_public_or_private_member_variable: %empty  */
                        { (yyval.b) = false; }
    break;

  case 599: /* optional_public_or_private_member_variable: "public"  */
                        { (yyval.b) = false; }
    break;

  case 600: /* optional_public_or_private_member_variable: "private"  */
                        { (yyval.b) = true; }
    break;

  case 601: /* optional_static_member_variable: %empty  */
                        { (yyval.b) = false; }
    break;

  case 602: /* optional_static_member_variable: "static"  */
                        { (yyval.b) = true; }
    break;

  case 603: /* structure_variable_declaration: optional_field_annotation optional_static_member_variable optional_override optional_public_or_private_member_variable variable_declaration  */
                                                                                                                                                                                      {
        (yyvsp[0].pVarDecl)->override = (yyvsp[-2].i) == OVERRIDE_OVERRIDE;
        (yyvsp[0].pVarDecl)->sealed = (yyvsp[-2].i) == OVERRIDE_SEALED;
        (yyvsp[0].pVarDecl)->annotation = (yyvsp[-4].aaList);
        (yyvsp[0].pVarDecl)->isPrivate = (yyvsp[-1].b);
        (yyvsp[0].pVarDecl)->isStatic = (yyvsp[-3].b);
        (yyval.pVarDecl) = (yyvsp[0].pVarDecl);
    }
    break;

  case 604: /* struct_variable_declaration_list: %empty  */
        {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 605: /* struct_variable_declaration_list: struct_variable_declaration_list "new line, semicolon"  */
                                                                 { (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList); }
    break;

  case 606: /* struct_variable_declaration_list: struct_variable_declaration_list "typedef" "name" '=' type_declaration SEMICOLON  */
                                                                                                                {
        (yyval.pVarDeclList) = (yyvsp[-5].pVarDeclList);
        ast_structureAlias(scanner,(yyvsp[-3].s),(yyvsp[-1].pTypeDecl),tokAt(scanner,(yylsp[-4])));
    }
    break;

  case 607: /* $@45: %empty  */
                                               {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeStructureFields(tak);
        }
    }
    break;

  case 608: /* struct_variable_declaration_list: struct_variable_declaration_list $@45 structure_variable_declaration SEMICOLON  */
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

  case 609: /* $@46: %empty  */
                                                                                                                     {
                if ( !yyextra->g_CommentReaders.empty() ) {
                    auto tak = tokAt(scanner,(yylsp[-2]));
                    for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeFunction(tak);
                }
            }
    break;

  case 610: /* struct_variable_declaration_list: struct_variable_declaration_list optional_annotation_list_with_emit_semis "def" optional_public_or_private_member_variable "abstract" optional_constant $@46 function_declaration_header SEMICOLON  */
                                                          {
                if ( !yyextra->g_CommentReaders.empty() ) {
                    auto tak = tokAt(scanner,(yylsp[-1]));
                    for ( auto & crd : yyextra->g_CommentReaders ) crd->afterFunction((yyvsp[-1].pFuncDecl),tak);
                }
                (yyvsp[-1].pFuncDecl)->isTemplate = yyextra->g_thisStructure ? yyextra->g_thisStructure->isTemplate : false;
                (yyval.pVarDeclList) = ast_structVarDefAbstract(scanner,(yyvsp[-8].pVarDeclList),(yyvsp[-7].faList),(yyvsp[-5].b),(yyvsp[-3].b), (yyvsp[-1].pFuncDecl));
            }
    break;

  case 611: /* $@47: %empty  */
                                                                                                                                                                         {
                if ( !yyextra->g_CommentReaders.empty() ) {
                    auto tak = tokAt(scanner,(yylsp[0]));
                    for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeFunction(tak);
                }
            }
    break;

  case 612: /* struct_variable_declaration_list: struct_variable_declaration_list optional_annotation_list_with_emit_semis "def" optional_public_or_private_member_variable optional_static_member_variable optional_override optional_constant $@47 function_declaration_header optional_emit_semis block_or_simple_block  */
                                                                                                 {
                if ( !yyextra->g_CommentReaders.empty() ) {
                    auto tak = tokAt(scanner,(yylsp[0]));
                    for ( auto & crd : yyextra->g_CommentReaders ) crd->afterFunction((yyvsp[-2].pFuncDecl),tak);
                }
                (yyvsp[-2].pFuncDecl)->isTemplate = yyextra->g_thisStructure ? yyextra->g_thisStructure->isTemplate : false;
                (yyval.pVarDeclList) = ast_structVarDef(scanner,(yyvsp[-10].pVarDeclList),(yyvsp[-9].faList),(yyvsp[-6].b),(yyvsp[-7].b),(yyvsp[-5].i),(yyvsp[-4].b),(yyvsp[-2].pFuncDecl),(yyvsp[0].pExpression),tokRangeAt(scanner,(yylsp[-8]),(yylsp[0])),tokAt(scanner,(yylsp[-9])));
            }
    break;

  case 613: /* function_argument_declaration_no_type: optional_field_annotation kwd_let_var_or_nothing variable_declaration_no_type  */
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

  case 614: /* function_argument_declaration_type: optional_field_annotation kwd_let_var_or_nothing variable_declaration_type  */
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

  case 615: /* function_argument_declaration_type: "$a" '(' expr ')'  */
                                     {
            auto na = new vector<VariableNameAndPosition>();
            na->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1]))));
            auto decl = new VariableDeclaration(na, new TypeDecl(Type::none), (yyvsp[-1].pExpression));
            decl->pTypeDecl->isTag = true;
            (yyval.pVarDecl) = decl;
        }
    break;

  case 616: /* function_argument_list: function_argument_declaration_no_type  */
                                                                                      { (yyval.pVarDeclList) = new vector<VariableDeclaration*>(); (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 617: /* function_argument_list: function_argument_declaration_type  */
                                                                                      { (yyval.pVarDeclList) = new vector<VariableDeclaration*>(); (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 618: /* function_argument_list: function_argument_declaration_no_type ';' function_argument_list  */
                                                                                      { (yyval.pVarDeclList) = (yyvsp[0].pVarDeclList); (yyvsp[0].pVarDeclList)->insert((yyvsp[0].pVarDeclList)->begin(),(yyvsp[-2].pVarDecl)); }
    break;

  case 619: /* function_argument_list: function_argument_declaration_type ';' function_argument_list  */
                                                                                      { (yyval.pVarDeclList) = (yyvsp[0].pVarDeclList); (yyvsp[0].pVarDeclList)->insert((yyvsp[0].pVarDeclList)->begin(),(yyvsp[-2].pVarDecl)); }
    break;

  case 620: /* function_argument_list: function_argument_declaration_type ',' function_argument_list  */
                                                                                      { (yyval.pVarDeclList) = (yyvsp[0].pVarDeclList); (yyvsp[0].pVarDeclList)->insert((yyvsp[0].pVarDeclList)->begin(),(yyvsp[-2].pVarDecl)); }
    break;

  case 621: /* tuple_type: type_declaration  */
                                    {
        (yyval.pVarDecl) = new VariableDeclaration(nullptr,(yyvsp[0].pTypeDecl),nullptr);
    }
    break;

  case 622: /* tuple_type: "name" ':' type_declaration  */
                                                   {
        auto na = new vector<VariableNameAndPosition>();
        na->push_back(VariableNameAndPosition(*(yyvsp[-2].s),"",tokAt(scanner,(yylsp[-2]))));
        (yyval.pVarDecl) = new VariableDeclaration(na,(yyvsp[0].pTypeDecl),nullptr);
        delete (yyvsp[-2].s);
    }
    break;

  case 623: /* tuple_type_list: tuple_type  */
                                                       { (yyval.pVarDeclList) = new vector<VariableDeclaration*>(); (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 624: /* tuple_type_list: tuple_type_list c_or_s tuple_type  */
                                                       { (yyval.pVarDeclList) = (yyvsp[-2].pVarDeclList); (yyvsp[-2].pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 625: /* tuple_alias_type_list: %empty  */
      {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 626: /* tuple_alias_type_list: tuple_type  */
                       {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
        (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl));
    }
    break;

  case 627: /* tuple_alias_type_list: tuple_alias_type_list semis tuple_type  */
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

  case 628: /* variant_type: "name" ':' type_declaration  */
                                                   {
        auto na = new vector<VariableNameAndPosition>();
        na->push_back(VariableNameAndPosition(*(yyvsp[-2].s),"",tokAt(scanner,(yylsp[-2]))));
        (yyval.pVarDecl) = new VariableDeclaration(na,(yyvsp[0].pTypeDecl),nullptr);
        delete (yyvsp[-2].s);
    }
    break;

  case 629: /* variant_type_list: variant_type  */
                                                         { (yyval.pVarDeclList) = new vector<VariableDeclaration*>(); (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 630: /* variant_type_list: variant_type_list c_or_s variant_type  */
                                                            { (yyval.pVarDeclList) = (yyvsp[-2].pVarDeclList); (yyvsp[-2].pVarDeclList)->push_back((yyvsp[0].pVarDecl)); }
    break;

  case 631: /* variant_alias_type_list: %empty  */
        {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 632: /* variant_alias_type_list: variant_type  */
                         {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
        (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl));
    }
    break;

  case 633: /* variant_alias_type_list: variant_alias_type_list semis variant_type  */
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

  case 634: /* copy_or_move: '='  */
                    { (yyval.b) = false; }
    break;

  case 635: /* copy_or_move: "<-"  */
                    { (yyval.b) = true; }
    break;

  case 636: /* variable_declaration_no_type: variable_name_with_pos_list  */
                                          {
        auto autoT = new TypeDecl(Type::autoinfer);
        autoT->at = tokAt(scanner,(yylsp[0]));
        autoT->ref = false;
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[0].pNameWithPosList),autoT,nullptr);
    }
    break;

  case 637: /* variable_declaration_no_type: variable_name_with_pos_list '&'  */
                                              {
        auto autoT = new TypeDecl(Type::autoinfer);
        autoT->at = tokAt(scanner,(yylsp[-1]));
        autoT->ref = true;
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-1].pNameWithPosList),autoT,nullptr);
    }
    break;

  case 638: /* variable_declaration_no_type: variable_name_with_pos_list copy_or_move expr  */
                                                                       {
        auto typeDecl = new TypeDecl(Type::autoinfer);
        typeDecl->at = tokAt(scanner,(yylsp[-2]));
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-2].pNameWithPosList),typeDecl,(yyvsp[0].pExpression));
        (yyval.pVarDecl)->init_via_move = (yyvsp[-1].b);
    }
    break;

  case 639: /* variable_declaration_type: variable_name_with_pos_list ':' type_declaration  */
                                                                          {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-2].pNameWithPosList),(yyvsp[0].pTypeDecl),nullptr);
    }
    break;

  case 640: /* variable_declaration_type: variable_name_with_pos_list ':' type_declaration copy_or_move expr  */
                                                                                                      {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-4].pNameWithPosList),(yyvsp[-2].pTypeDecl),(yyvsp[0].pExpression));
        (yyval.pVarDecl)->init_via_move = (yyvsp[-1].b);
    }
    break;

  case 641: /* variable_declaration: variable_declaration_type  */
                                        {
        (yyval.pVarDecl) = (yyvsp[0].pVarDecl);
    }
    break;

  case 642: /* variable_declaration: variable_declaration_no_type  */
                                           {
        (yyval.pVarDecl) = (yyvsp[0].pVarDecl);
    }
    break;

  case 643: /* copy_or_move_or_clone: '='  */
                    { (yyval.i) = CorM_COPY; }
    break;

  case 644: /* copy_or_move_or_clone: "<-"  */
                    { (yyval.i) = CorM_MOVE; }
    break;

  case 645: /* copy_or_move_or_clone: ":="  */
                    { (yyval.i) = CorM_CLONE; }
    break;

  case 646: /* optional_ref: %empty  */
            { (yyval.b) = false; }
    break;

  case 647: /* optional_ref: '&'  */
            { (yyval.b) = true; }
    break;

  case 648: /* let_variable_name_with_pos_list: "name"  */
                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = pSL;
        delete (yyvsp[0].s);
    }
    break;

  case 649: /* let_variable_name_with_pos_list: "$i" '(' expr ')'  */
                                     {
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = pSL;
    }
    break;

  case 650: /* let_variable_name_with_pos_list: "name" "aka" "name"  */
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

  case 651: /* let_variable_name_with_pos_list: let_variable_name_with_pos_list ',' "name"  */
                                                             {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = (yyvsp[-2].pNameWithPosList);
        delete (yyvsp[0].s);
    }
    break;

  case 652: /* let_variable_name_with_pos_list: let_variable_name_with_pos_list ',' "$i" '(' expr ')'  */
                                                                               {
        (yyvsp[-5].pNameWithPosList)->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = (yyvsp[-5].pNameWithPosList);
    }
    break;

  case 653: /* let_variable_name_with_pos_list: let_variable_name_with_pos_list ',' "name" "aka" "name"  */
                                                                                   {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-4].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[-2].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-2]))));
        (yyval.pNameWithPosList) = (yyvsp[-4].pNameWithPosList);
        delete (yyvsp[-2].s);
        delete (yyvsp[0].s);
    }
    break;

  case 654: /* global_let_variable_name_with_pos_list: "name"  */
                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = pSL;
        delete (yyvsp[0].s);
    }
    break;

  case 655: /* global_let_variable_name_with_pos_list: global_let_variable_name_with_pos_list ',' "name"  */
                                                                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = (yyvsp[-2].pNameWithPosList);
        delete (yyvsp[0].s);
    }
    break;

  case 656: /* variable_declaration_list: %empty  */
        {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 657: /* variable_declaration_list: variable_declaration_list SEMICOLON  */
                                                  {
        (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList);
    }
    break;

  case 658: /* variable_declaration_list: variable_declaration_list let_variable_declaration  */
                                                                       {
        (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList);
        (yyvsp[-1].pVarDeclList)->push_back((yyvsp[0].pVarDecl));
    }
    break;

  case 659: /* let_variable_declaration: let_variable_name_with_pos_list ':' type_declaration_no_options SEMICOLON  */
                                                                                                  {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-3].pNameWithPosList),(yyvsp[-1].pTypeDecl),nullptr);
    }
    break;

  case 660: /* let_variable_declaration: let_variable_name_with_pos_list ':' type_declaration_no_options copy_or_move_or_clone expr SEMICOLON  */
                                                                                                                                        {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-5].pNameWithPosList),(yyvsp[-3].pTypeDecl),(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
    }
    break;

  case 661: /* let_variable_declaration: let_variable_name_with_pos_list optional_ref copy_or_move_or_clone expr SEMICOLON  */
                                                                                                                {
        auto typeDecl = new TypeDecl(Type::autoinfer);
        typeDecl->at = tokAt(scanner,(yylsp[-4]));
        typeDecl->ref = (yyvsp[-3].b);
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-4].pNameWithPosList),typeDecl,(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
    }
    break;

  case 662: /* global_let_variable_declaration: global_let_variable_name_with_pos_list ':' type_declaration_no_options SEMICOLON  */
                                                                                                         {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-3].pNameWithPosList),(yyvsp[-1].pTypeDecl),nullptr);
    }
    break;

  case 663: /* global_let_variable_declaration: global_let_variable_name_with_pos_list ':' type_declaration_no_options copy_or_move_or_clone expr SEMICOLON  */
                                                                                                                                               {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-5].pNameWithPosList),(yyvsp[-3].pTypeDecl),(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
    }
    break;

  case 664: /* global_let_variable_declaration: global_let_variable_name_with_pos_list optional_ref copy_or_move_or_clone expr SEMICOLON  */
                                                                                                                       {
        auto typeDecl = new TypeDecl(Type::autoinfer);
        typeDecl->at = tokAt(scanner,(yylsp[-4]));
        typeDecl->ref = (yyvsp[-3].b);
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-4].pNameWithPosList),typeDecl,(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
    }
    break;

  case 665: /* optional_shared: %empty  */
                     { (yyval.b) = false; }
    break;

  case 666: /* optional_shared: "shared"  */
                     { (yyval.b) = true; }
    break;

  case 667: /* optional_public_or_private_variable: %empty  */
                     { (yyval.b) = yyextra->g_Program->thisModule->isPublic; }
    break;

  case 668: /* optional_public_or_private_variable: "private"  */
                     { (yyval.b) = false; }
    break;

  case 669: /* optional_public_or_private_variable: "public"  */
                     { (yyval.b) = true; }
    break;

  case 670: /* global_variable_declaration_list: %empty  */
        {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 671: /* global_variable_declaration_list: global_variable_declaration_list SEMICOLON  */
                                                         {
        (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList);
    }
    break;

  case 672: /* $@48: %empty  */
                                               {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeGlobalVariables(tak);
        }
    }
    break;

  case 673: /* global_variable_declaration_list: global_variable_declaration_list $@48 optional_field_annotation let_variable_declaration  */
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

  case 674: /* global_let: kwd_let optional_shared optional_public_or_private_variable '{' global_variable_declaration_list '}'  */
                                                                                                                                       {
        ast_globalLetList(scanner,(yyvsp[-5].b),(yyvsp[-4].b),(yyvsp[-3].b),(yyvsp[-1].pVarDeclList));
    }
    break;

  case 675: /* $@49: %empty  */
                                                                                        {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeGlobalVariables(tak);
        }
    }
    break;

  case 676: /* global_let: kwd_let optional_shared optional_public_or_private_variable $@49 optional_field_annotation global_let_variable_declaration  */
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

  case 677: /* enum_expression: "name"  */
                   {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyval.pEnumPair) = new EnumPair((yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        delete (yyvsp[0].s);
    }
    break;

  case 678: /* enum_expression: "name" '=' expr  */
                                   {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        (yyval.pEnumPair) = new EnumPair((yyvsp[-2].s),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[-2])));
        delete (yyvsp[-2].s);
    }
    break;

  case 681: /* enum_list: %empty  */
        {
        (yyval.pEnumList) = new Enumeration();
    }
    break;

  case 682: /* enum_list: enum_expression  */
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

  case 683: /* enum_list: enum_list commas enum_expression  */
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

  case 684: /* optional_public_or_private_alias: %empty  */
                     { (yyval.b) = yyextra->g_Program->thisModule->isPublic; }
    break;

  case 685: /* optional_public_or_private_alias: "private"  */
                     { (yyval.b) = false; }
    break;

  case 686: /* optional_public_or_private_alias: "public"  */
                     { (yyval.b) = true; }
    break;

  case 687: /* $@50: %empty  */
                                                         {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto pubename = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeAlias(pubename);
        }
    }
    break;

  case 688: /* single_alias: optional_public_or_private_alias "name" $@50 '=' type_declaration  */
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

  case 690: /* distinct_declaration: "distinct" optional_public_or_private_alias "name" '=' type_declaration SEMICOLON  */
                                                                                                             {
        ast_distinctDeclaration(scanner,(yyvsp[-3].s),tokAt(scanner,(yylsp[-3])),!(yyvsp[-4].b),(yyvsp[-1].pTypeDecl));
        delete (yyvsp[-3].s);
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


