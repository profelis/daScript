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
  YYSYMBOL_RPIPE = 155,                    /* "|>"  */
  YYSYMBOL_CLONEEQU = 156,                 /* ":="  */
  YYSYMBOL_ROTL = 157,                     /* "<<<"  */
  YYSYMBOL_ROTR = 158,                     /* ">>>"  */
  YYSYMBOL_ROTLEQU = 159,                  /* "<<<="  */
  YYSYMBOL_ROTREQU = 160,                  /* ">>>="  */
  YYSYMBOL_MAPTO = 161,                    /* "=>"  */
  YYSYMBOL_DOUBLE_AT = 162,                /* "@@"  */
  YYSYMBOL_AT_FIELD = 163,                 /* "@field"  */
  YYSYMBOL_COLCOL = 164,                   /* "::"  */
  YYSYMBOL_ANDAND = 165,                   /* "&&"  */
  YYSYMBOL_OROR = 166,                     /* "||"  */
  YYSYMBOL_XORXOR = 167,                   /* "^^"  */
  YYSYMBOL_ANDANDEQU = 168,                /* "&&="  */
  YYSYMBOL_OROREQU = 169,                  /* "||="  */
  YYSYMBOL_XORXOREQU = 170,                /* "^^="  */
  YYSYMBOL_DOTDOT = 171,                   /* ".."  */
  YYSYMBOL_MTAG_E = 172,                   /* "$$"  */
  YYSYMBOL_MTAG_I = 173,                   /* "$i"  */
  YYSYMBOL_MTAG_V = 174,                   /* "$v"  */
  YYSYMBOL_MTAG_B = 175,                   /* "$b"  */
  YYSYMBOL_MTAG_A = 176,                   /* "$a"  */
  YYSYMBOL_MTAG_T = 177,                   /* "$t"  */
  YYSYMBOL_MTAG_C = 178,                   /* "$c"  */
  YYSYMBOL_MTAG_F = 179,                   /* "$f"  */
  YYSYMBOL_MTAG_DOTDOTDOT = 180,           /* "..."  */
  YYSYMBOL_INTEGER = 181,                  /* "integer constant"  */
  YYSYMBOL_LONG_INTEGER = 182,             /* "long integer constant"  */
  YYSYMBOL_UNSIGNED_INTEGER = 183,         /* "unsigned integer constant"  */
  YYSYMBOL_UNSIGNED_LONG_INTEGER = 184,    /* "unsigned long integer constant"  */
  YYSYMBOL_UNSIGNED_INT8 = 185,            /* "unsigned int8 constant"  */
  YYSYMBOL_DAS_FLOAT = 186,                /* "floating point constant"  */
  YYSYMBOL_DAS_FLOAT16_CONST = 187,        /* "float16 constant"  */
  YYSYMBOL_DOUBLE = 188,                   /* "double constant"  */
  YYSYMBOL_NAME = 189,                     /* "name"  */
  YYSYMBOL_DAS_EMIT_COMMA = 190,           /* "new line, comma"  */
  YYSYMBOL_DAS_EMIT_SEMICOLON = 191,       /* "new line, semicolon"  */
  YYSYMBOL_BEGIN_STRING = 192,             /* "start of the string"  */
  YYSYMBOL_STRING_CHARACTER = 193,         /* STRING_CHARACTER  */
  YYSYMBOL_STRING_CHARACTER_ESC = 194,     /* STRING_CHARACTER_ESC  */
  YYSYMBOL_END_STRING = 195,               /* "end of the string"  */
  YYSYMBOL_BEGIN_STRING_EXPR = 196,        /* "{"  */
  YYSYMBOL_END_STRING_EXPR = 197,          /* "}"  */
  YYSYMBOL_END_OF_READ = 198,              /* "end of failed eader macro"  */
  YYSYMBOL_199_ = 199,                     /* ','  */
  YYSYMBOL_200_ = 200,                     /* '='  */
  YYSYMBOL_201_ = 201,                     /* '?'  */
  YYSYMBOL_202_ = 202,                     /* ':'  */
  YYSYMBOL_203_ = 203,                     /* '|'  */
  YYSYMBOL_204_ = 204,                     /* '^'  */
  YYSYMBOL_205_ = 205,                     /* '&'  */
  YYSYMBOL_206_ = 206,                     /* '<'  */
  YYSYMBOL_207_ = 207,                     /* '>'  */
  YYSYMBOL_208_ = 208,                     /* '-'  */
  YYSYMBOL_209_ = 209,                     /* '+'  */
  YYSYMBOL_210_ = 210,                     /* '*'  */
  YYSYMBOL_211_ = 211,                     /* '/'  */
  YYSYMBOL_212_ = 212,                     /* '%'  */
  YYSYMBOL_UNARY_MINUS = 213,              /* UNARY_MINUS  */
  YYSYMBOL_UNARY_PLUS = 214,               /* UNARY_PLUS  */
  YYSYMBOL_215_ = 215,                     /* '~'  */
  YYSYMBOL_216_ = 216,                     /* '!'  */
  YYSYMBOL_PRE_INC = 217,                  /* PRE_INC  */
  YYSYMBOL_PRE_DEC = 218,                  /* PRE_DEC  */
  YYSYMBOL_LLPIPE = 219,                   /* LLPIPE  */
  YYSYMBOL_POST_INC = 220,                 /* POST_INC  */
  YYSYMBOL_POST_DEC = 221,                 /* POST_DEC  */
  YYSYMBOL_DEREF = 222,                    /* DEREF  */
  YYSYMBOL_223_ = 223,                     /* '.'  */
  YYSYMBOL_224_ = 224,                     /* '['  */
  YYSYMBOL_225_ = 225,                     /* ']'  */
  YYSYMBOL_226_ = 226,                     /* '('  */
  YYSYMBOL_227_ = 227,                     /* ')'  */
  YYSYMBOL_228_ = 228,                     /* '$'  */
  YYSYMBOL_229_ = 229,                     /* '@'  */
  YYSYMBOL_230_ = 230,                     /* ';'  */
  YYSYMBOL_231_ = 231,                     /* '{'  */
  YYSYMBOL_232_ = 232,                     /* '}'  */
  YYSYMBOL_233_ = 233,                     /* '#'  */
  YYSYMBOL_YYACCEPT = 234,                 /* $accept  */
  YYSYMBOL_program = 235,                  /* program  */
  YYSYMBOL_COMMA = 236,                    /* COMMA  */
  YYSYMBOL_SEMICOLON = 237,                /* SEMICOLON  */
  YYSYMBOL_top_level_reader_macro = 238,   /* top_level_reader_macro  */
  YYSYMBOL_optional_public_or_private_module = 239, /* optional_public_or_private_module  */
  YYSYMBOL_module_name = 240,              /* module_name  */
  YYSYMBOL_optional_not_required = 241,    /* optional_not_required  */
  YYSYMBOL_module_declaration = 242,       /* module_declaration  */
  YYSYMBOL_character_sequence = 243,       /* character_sequence  */
  YYSYMBOL_string_constant = 244,          /* string_constant  */
  YYSYMBOL_format_string = 245,            /* format_string  */
  YYSYMBOL_optional_format_string = 246,   /* optional_format_string  */
  YYSYMBOL_247_1 = 247,                    /* $@1  */
  YYSYMBOL_string_builder_body = 248,      /* string_builder_body  */
  YYSYMBOL_string_builder = 249,           /* string_builder  */
  YYSYMBOL_reader_character_sequence = 250, /* reader_character_sequence  */
  YYSYMBOL_expr_reader = 251,              /* expr_reader  */
  YYSYMBOL_252_2 = 252,                    /* $@2  */
  YYSYMBOL_options_declaration = 253,      /* options_declaration  */
  YYSYMBOL_require_declaration = 254,      /* require_declaration  */
  YYSYMBOL_require_module_name = 255,      /* require_module_name  */
  YYSYMBOL_optional_require_guard = 256,   /* optional_require_guard  */
  YYSYMBOL_require_module = 257,           /* require_module  */
  YYSYMBOL_is_public_module = 258,         /* is_public_module  */
  YYSYMBOL_expect_declaration = 259,       /* expect_declaration  */
  YYSYMBOL_expect_list = 260,              /* expect_list  */
  YYSYMBOL_expect_error = 261,             /* expect_error  */
  YYSYMBOL_expression_label = 262,         /* expression_label  */
  YYSYMBOL_expression_goto = 263,          /* expression_goto  */
  YYSYMBOL_elif_or_static_elif = 264,      /* elif_or_static_elif  */
  YYSYMBOL_emit_semis = 265,               /* emit_semis  */
  YYSYMBOL_optional_emit_semis = 266,      /* optional_emit_semis  */
  YYSYMBOL_expression_else = 267,          /* expression_else  */
  YYSYMBOL_268_3 = 268,                    /* $@3  */
  YYSYMBOL_269_4 = 269,                    /* $@4  */
  YYSYMBOL_if_or_static_if = 270,          /* if_or_static_if  */
  YYSYMBOL_expression_else_one_liner = 271, /* expression_else_one_liner  */
  YYSYMBOL_expression_if_one_liner = 272,  /* expression_if_one_liner  */
  YYSYMBOL_semis = 273,                    /* semis  */
  YYSYMBOL_optional_semis = 274,           /* optional_semis  */
  YYSYMBOL_expression_if_block = 275,      /* expression_if_block  */
  YYSYMBOL_276_5 = 276,                    /* $@5  */
  YYSYMBOL_277_6 = 277,                    /* $@6  */
  YYSYMBOL_278_7 = 278,                    /* $@7  */
  YYSYMBOL_expression_else_block = 279,    /* expression_else_block  */
  YYSYMBOL_280_8 = 280,                    /* $@8  */
  YYSYMBOL_281_9 = 281,                    /* $@9  */
  YYSYMBOL_282_10 = 282,                   /* $@10  */
  YYSYMBOL_expression_if_then_else = 283,  /* expression_if_then_else  */
  YYSYMBOL_284_11 = 284,                   /* $@11  */
  YYSYMBOL_285_12 = 285,                   /* $@12  */
  YYSYMBOL_expression_if_then_else_oneliner = 286, /* expression_if_then_else_oneliner  */
  YYSYMBOL_for_variable_name_with_pos_list = 287, /* for_variable_name_with_pos_list  */
  YYSYMBOL_expression_for_loop = 288,      /* expression_for_loop  */
  YYSYMBOL_289_13 = 289,                   /* $@13  */
  YYSYMBOL_expression_unsafe = 290,        /* expression_unsafe  */
  YYSYMBOL_expression_while_loop = 291,    /* expression_while_loop  */
  YYSYMBOL_292_14 = 292,                   /* $@14  */
  YYSYMBOL_expression_with = 293,          /* expression_with  */
  YYSYMBOL_294_15 = 294,                   /* $@15  */
  YYSYMBOL_expression_with_alias = 295,    /* expression_with_alias  */
  YYSYMBOL_annotation_argument_value = 296, /* annotation_argument_value  */
  YYSYMBOL_annotation_argument_value_list = 297, /* annotation_argument_value_list  */
  YYSYMBOL_annotation_argument_name = 298, /* annotation_argument_name  */
  YYSYMBOL_annotation_argument = 299,      /* annotation_argument  */
  YYSYMBOL_annotation_argument_list = 300, /* annotation_argument_list  */
  YYSYMBOL_metadata_argument_list = 301,   /* metadata_argument_list  */
  YYSYMBOL_optional_for_annotations = 302, /* optional_for_annotations  */
  YYSYMBOL_annotation_declaration_name = 303, /* annotation_declaration_name  */
  YYSYMBOL_annotation_declaration_basic = 304, /* annotation_declaration_basic  */
  YYSYMBOL_annotation_declaration = 305,   /* annotation_declaration  */
  YYSYMBOL_annotation_list = 306,          /* annotation_list  */
  YYSYMBOL_optional_annotation_list = 307, /* optional_annotation_list  */
  YYSYMBOL_optional_annotation_list_with_emit_semis = 308, /* optional_annotation_list_with_emit_semis  */
  YYSYMBOL_optional_function_argument_list = 309, /* optional_function_argument_list  */
  YYSYMBOL_optional_function_type = 310,   /* optional_function_type  */
  YYSYMBOL_function_name = 311,            /* function_name  */
  YYSYMBOL_das_type_name = 312,            /* das_type_name  */
  YYSYMBOL_optional_template = 313,        /* optional_template  */
  YYSYMBOL_global_function_declaration = 314, /* global_function_declaration  */
  YYSYMBOL_optional_public_or_private_function = 315, /* optional_public_or_private_function  */
  YYSYMBOL_function_declaration_header = 316, /* function_declaration_header  */
  YYSYMBOL_function_declaration = 317,     /* function_declaration  */
  YYSYMBOL_318_16 = 318,                   /* $@16  */
  YYSYMBOL_expression_block_finally = 319, /* expression_block_finally  */
  YYSYMBOL_320_17 = 320,                   /* $@17  */
  YYSYMBOL_321_18 = 321,                   /* $@18  */
  YYSYMBOL_expression_block = 322,         /* expression_block  */
  YYSYMBOL_323_19 = 323,                   /* $@19  */
  YYSYMBOL_324_20 = 324,                   /* $@20  */
  YYSYMBOL_expr_call_pipe_no_bracket = 325, /* expr_call_pipe_no_bracket  */
  YYSYMBOL_expression_any = 326,           /* expression_any  */
  YYSYMBOL_327_21 = 327,                   /* $@21  */
  YYSYMBOL_328_22 = 328,                   /* $@22  */
  YYSYMBOL_expressions = 329,              /* expressions  */
  YYSYMBOL_optional_expr_list = 330,       /* optional_expr_list  */
  YYSYMBOL_optional_expr_map_tuple_list = 331, /* optional_expr_map_tuple_list  */
  YYSYMBOL_type_declaration_no_options_list = 332, /* type_declaration_no_options_list  */
  YYSYMBOL_name_in_namespace = 333,        /* name_in_namespace  */
  YYSYMBOL_expression_delete = 334,        /* expression_delete  */
  YYSYMBOL_new_type_declaration = 335,     /* new_type_declaration  */
  YYSYMBOL_336_23 = 336,                   /* $@23  */
  YYSYMBOL_337_24 = 337,                   /* $@24  */
  YYSYMBOL_expr_new = 338,                 /* expr_new  */
  YYSYMBOL_expression_break = 339,         /* expression_break  */
  YYSYMBOL_expression_continue = 340,      /* expression_continue  */
  YYSYMBOL_expression_return = 341,        /* expression_return  */
  YYSYMBOL_expression_yield = 342,         /* expression_yield  */
  YYSYMBOL_expression_try_catch = 343,     /* expression_try_catch  */
  YYSYMBOL_kwd_let_var_or_nothing = 344,   /* kwd_let_var_or_nothing  */
  YYSYMBOL_kwd_let = 345,                  /* kwd_let  */
  YYSYMBOL_optional_in_scope = 346,        /* optional_in_scope  */
  YYSYMBOL_tuple_expansion = 347,          /* tuple_expansion  */
  YYSYMBOL_tuple_expansion_variable_declaration = 348, /* tuple_expansion_variable_declaration  */
  YYSYMBOL_expression_let = 349,           /* expression_let  */
  YYSYMBOL_expr_cast = 350,                /* expr_cast  */
  YYSYMBOL_351_25 = 351,                   /* $@25  */
  YYSYMBOL_352_26 = 352,                   /* $@26  */
  YYSYMBOL_353_27 = 353,                   /* $@27  */
  YYSYMBOL_354_28 = 354,                   /* $@28  */
  YYSYMBOL_355_29 = 355,                   /* $@29  */
  YYSYMBOL_356_30 = 356,                   /* $@30  */
  YYSYMBOL_expr_type_decl = 357,           /* expr_type_decl  */
  YYSYMBOL_358_31 = 358,                   /* $@31  */
  YYSYMBOL_359_32 = 359,                   /* $@32  */
  YYSYMBOL_expr_type_info = 360,           /* expr_type_info  */
  YYSYMBOL_expr_list = 361,                /* expr_list  */
  YYSYMBOL_block_or_simple_block = 362,    /* block_or_simple_block  */
  YYSYMBOL_block_or_lambda = 363,          /* block_or_lambda  */
  YYSYMBOL_capture_entry = 364,            /* capture_entry  */
  YYSYMBOL_capture_list = 365,             /* capture_list  */
  YYSYMBOL_optional_capture_list = 366,    /* optional_capture_list  */
  YYSYMBOL_expr_full_block = 367,          /* expr_full_block  */
  YYSYMBOL_expr_full_block_assumed_piped = 368, /* expr_full_block_assumed_piped  */
  YYSYMBOL_expr_numeric_const = 369,       /* expr_numeric_const  */
  YYSYMBOL_expr_assign_no_bracket = 370,   /* expr_assign_no_bracket  */
  YYSYMBOL_expr_named_call = 371,          /* expr_named_call  */
  YYSYMBOL_expr_method_call_no_bracket = 372, /* expr_method_call_no_bracket  */
  YYSYMBOL_func_addr_name = 373,           /* func_addr_name  */
  YYSYMBOL_func_addr_expr = 374,           /* func_addr_expr  */
  YYSYMBOL_375_33 = 375,                   /* $@33  */
  YYSYMBOL_376_34 = 376,                   /* $@34  */
  YYSYMBOL_377_35 = 377,                   /* $@35  */
  YYSYMBOL_378_36 = 378,                   /* $@36  */
  YYSYMBOL_expr_field_no_bracket = 379,    /* expr_field_no_bracket  */
  YYSYMBOL_380_37 = 380,                   /* $@37  */
  YYSYMBOL_381_38 = 381,                   /* $@38  */
  YYSYMBOL_expr_call = 382,                /* expr_call  */
  YYSYMBOL_expr = 383,                     /* expr  */
  YYSYMBOL_expr_no_bracket = 384,          /* expr_no_bracket  */
  YYSYMBOL_385_39 = 385,                   /* $@39  */
  YYSYMBOL_386_40 = 386,                   /* $@40  */
  YYSYMBOL_387_41 = 387,                   /* $@41  */
  YYSYMBOL_388_42 = 388,                   /* $@42  */
  YYSYMBOL_389_43 = 389,                   /* $@43  */
  YYSYMBOL_390_44 = 390,                   /* $@44  */
  YYSYMBOL_expr_generator = 391,           /* expr_generator  */
  YYSYMBOL_expr_mtag_no_bracket = 392,     /* expr_mtag_no_bracket  */
  YYSYMBOL_optional_field_annotation = 393, /* optional_field_annotation  */
  YYSYMBOL_optional_override = 394,        /* optional_override  */
  YYSYMBOL_optional_constant = 395,        /* optional_constant  */
  YYSYMBOL_optional_public_or_private_member_variable = 396, /* optional_public_or_private_member_variable  */
  YYSYMBOL_optional_static_member_variable = 397, /* optional_static_member_variable  */
  YYSYMBOL_structure_variable_declaration = 398, /* structure_variable_declaration  */
  YYSYMBOL_struct_variable_declaration_list = 399, /* struct_variable_declaration_list  */
  YYSYMBOL_400_45 = 400,                   /* $@45  */
  YYSYMBOL_401_46 = 401,                   /* $@46  */
  YYSYMBOL_402_47 = 402,                   /* $@47  */
  YYSYMBOL_function_argument_declaration_no_type = 403, /* function_argument_declaration_no_type  */
  YYSYMBOL_function_argument_declaration_type = 404, /* function_argument_declaration_type  */
  YYSYMBOL_function_argument_list = 405,   /* function_argument_list  */
  YYSYMBOL_tuple_type = 406,               /* tuple_type  */
  YYSYMBOL_tuple_type_list = 407,          /* tuple_type_list  */
  YYSYMBOL_tuple_alias_type_list = 408,    /* tuple_alias_type_list  */
  YYSYMBOL_variant_type = 409,             /* variant_type  */
  YYSYMBOL_variant_type_list = 410,        /* variant_type_list  */
  YYSYMBOL_variant_alias_type_list = 411,  /* variant_alias_type_list  */
  YYSYMBOL_copy_or_move = 412,             /* copy_or_move  */
  YYSYMBOL_variable_declaration_no_type = 413, /* variable_declaration_no_type  */
  YYSYMBOL_variable_declaration_type = 414, /* variable_declaration_type  */
  YYSYMBOL_variable_declaration = 415,     /* variable_declaration  */
  YYSYMBOL_copy_or_move_or_clone = 416,    /* copy_or_move_or_clone  */
  YYSYMBOL_optional_ref = 417,             /* optional_ref  */
  YYSYMBOL_let_variable_name_with_pos_list = 418, /* let_variable_name_with_pos_list  */
  YYSYMBOL_global_let_variable_name_with_pos_list = 419, /* global_let_variable_name_with_pos_list  */
  YYSYMBOL_variable_declaration_list = 420, /* variable_declaration_list  */
  YYSYMBOL_let_variable_declaration = 421, /* let_variable_declaration  */
  YYSYMBOL_global_let_variable_declaration = 422, /* global_let_variable_declaration  */
  YYSYMBOL_optional_shared = 423,          /* optional_shared  */
  YYSYMBOL_optional_public_or_private_variable = 424, /* optional_public_or_private_variable  */
  YYSYMBOL_global_variable_declaration_list = 425, /* global_variable_declaration_list  */
  YYSYMBOL_426_48 = 426,                   /* $@48  */
  YYSYMBOL_global_let = 427,               /* global_let  */
  YYSYMBOL_428_49 = 428,                   /* $@49  */
  YYSYMBOL_enum_expression = 429,          /* enum_expression  */
  YYSYMBOL_commas = 430,                   /* commas  */
  YYSYMBOL_enum_list = 431,                /* enum_list  */
  YYSYMBOL_optional_public_or_private_alias = 432, /* optional_public_or_private_alias  */
  YYSYMBOL_single_alias = 433,             /* single_alias  */
  YYSYMBOL_434_50 = 434,                   /* $@50  */
  YYSYMBOL_alias_declaration = 435,        /* alias_declaration  */
  YYSYMBOL_distinct_alias = 436,           /* distinct_alias  */
  YYSYMBOL_optional_public_or_private_enum = 437, /* optional_public_or_private_enum  */
  YYSYMBOL_enum_name = 438,                /* enum_name  */
  YYSYMBOL_optional_enum_basic_type_declaration = 439, /* optional_enum_basic_type_declaration  */
  YYSYMBOL_optional_commas = 440,          /* optional_commas  */
  YYSYMBOL_emit_commas = 441,              /* emit_commas  */
  YYSYMBOL_optional_emit_commas = 442,     /* optional_emit_commas  */
  YYSYMBOL_enum_declaration = 443,         /* enum_declaration  */
  YYSYMBOL_444_51 = 444,                   /* $@51  */
  YYSYMBOL_445_52 = 445,                   /* $@52  */
  YYSYMBOL_446_53 = 446,                   /* $@53  */
  YYSYMBOL_optional_structure_parent = 447, /* optional_structure_parent  */
  YYSYMBOL_optional_sealed = 448,          /* optional_sealed  */
  YYSYMBOL_structure_name = 449,           /* structure_name  */
  YYSYMBOL_class_or_struct = 450,          /* class_or_struct  */
  YYSYMBOL_optional_public_or_private_structure = 451, /* optional_public_or_private_structure  */
  YYSYMBOL_optional_struct_variable_declaration_list = 452, /* optional_struct_variable_declaration_list  */
  YYSYMBOL_structure_declaration = 453,    /* structure_declaration  */
  YYSYMBOL_454_54 = 454,                   /* $@54  */
  YYSYMBOL_455_55 = 455,                   /* $@55  */
  YYSYMBOL_456_56 = 456,                   /* $@56  */
  YYSYMBOL_variable_name_with_pos_list = 457, /* variable_name_with_pos_list  */
  YYSYMBOL_basic_type_declaration = 458,   /* basic_type_declaration  */
  YYSYMBOL_enum_basic_type_declaration = 459, /* enum_basic_type_declaration  */
  YYSYMBOL_structure_type_declaration = 460, /* structure_type_declaration  */
  YYSYMBOL_auto_type_declaration = 461,    /* auto_type_declaration  */
  YYSYMBOL_bitfield_bits = 462,            /* bitfield_bits  */
  YYSYMBOL_bitfield_alias_bits = 463,      /* bitfield_alias_bits  */
  YYSYMBOL_bitfield_basic_type_declaration = 464, /* bitfield_basic_type_declaration  */
  YYSYMBOL_bitfield_type_declaration = 465, /* bitfield_type_declaration  */
  YYSYMBOL_466_57 = 466,                   /* $@57  */
  YYSYMBOL_467_58 = 467,                   /* $@58  */
  YYSYMBOL_c_or_s = 468,                   /* c_or_s  */
  YYSYMBOL_table_type_pair = 469,          /* table_type_pair  */
  YYSYMBOL_dim_list = 470,                 /* dim_list  */
  YYSYMBOL_type_declaration_no_options = 471, /* type_declaration_no_options  */
  YYSYMBOL_optional_expr_list_in_braces = 472, /* optional_expr_list_in_braces  */
  YYSYMBOL_type_declaration_no_options_no_dim = 473, /* type_declaration_no_options_no_dim  */
  YYSYMBOL_474_59 = 474,                   /* $@59  */
  YYSYMBOL_475_60 = 475,                   /* $@60  */
  YYSYMBOL_476_61 = 476,                   /* $@61  */
  YYSYMBOL_477_62 = 477,                   /* $@62  */
  YYSYMBOL_478_63 = 478,                   /* $@63  */
  YYSYMBOL_479_64 = 479,                   /* $@64  */
  YYSYMBOL_480_65 = 480,                   /* $@65  */
  YYSYMBOL_481_66 = 481,                   /* $@66  */
  YYSYMBOL_482_67 = 482,                   /* $@67  */
  YYSYMBOL_483_68 = 483,                   /* $@68  */
  YYSYMBOL_484_69 = 484,                   /* $@69  */
  YYSYMBOL_485_70 = 485,                   /* $@70  */
  YYSYMBOL_486_71 = 486,                   /* $@71  */
  YYSYMBOL_487_72 = 487,                   /* $@72  */
  YYSYMBOL_488_73 = 488,                   /* $@73  */
  YYSYMBOL_489_74 = 489,                   /* $@74  */
  YYSYMBOL_490_75 = 490,                   /* $@75  */
  YYSYMBOL_491_76 = 491,                   /* $@76  */
  YYSYMBOL_492_77 = 492,                   /* $@77  */
  YYSYMBOL_493_78 = 493,                   /* $@78  */
  YYSYMBOL_494_79 = 494,                   /* $@79  */
  YYSYMBOL_495_80 = 495,                   /* $@80  */
  YYSYMBOL_496_81 = 496,                   /* $@81  */
  YYSYMBOL_497_82 = 497,                   /* $@82  */
  YYSYMBOL_498_83 = 498,                   /* $@83  */
  YYSYMBOL_499_84 = 499,                   /* $@84  */
  YYSYMBOL_500_85 = 500,                   /* $@85  */
  YYSYMBOL_501_86 = 501,                   /* $@86  */
  YYSYMBOL_type_declaration = 502,         /* type_declaration  */
  YYSYMBOL_tuple_alias_declaration = 503,  /* tuple_alias_declaration  */
  YYSYMBOL_504_87 = 504,                   /* $@87  */
  YYSYMBOL_505_88 = 505,                   /* $@88  */
  YYSYMBOL_506_89 = 506,                   /* $@89  */
  YYSYMBOL_507_90 = 507,                   /* $@90  */
  YYSYMBOL_variant_alias_declaration = 508, /* variant_alias_declaration  */
  YYSYMBOL_509_91 = 509,                   /* $@91  */
  YYSYMBOL_510_92 = 510,                   /* $@92  */
  YYSYMBOL_511_93 = 511,                   /* $@93  */
  YYSYMBOL_512_94 = 512,                   /* $@94  */
  YYSYMBOL_bitfield_alias_declaration = 513, /* bitfield_alias_declaration  */
  YYSYMBOL_514_95 = 514,                   /* $@95  */
  YYSYMBOL_515_96 = 515,                   /* $@96  */
  YYSYMBOL_516_97 = 516,                   /* $@97  */
  YYSYMBOL_517_98 = 517,                   /* $@98  */
  YYSYMBOL_make_decl = 518,                /* make_decl  */
  YYSYMBOL_make_decl_no_bracket = 519,     /* make_decl_no_bracket  */
  YYSYMBOL_make_struct_fields = 520,       /* make_struct_fields  */
  YYSYMBOL_make_variant_dim = 521,         /* make_variant_dim  */
  YYSYMBOL_make_struct_single = 522,       /* make_struct_single  */
  YYSYMBOL_make_struct_dim_list = 523,     /* make_struct_dim_list  */
  YYSYMBOL_make_struct_dim_decl = 524,     /* make_struct_dim_decl  */
  YYSYMBOL_optional_make_struct_dim_decl = 525, /* optional_make_struct_dim_decl  */
  YYSYMBOL_use_initializer = 526,          /* use_initializer  */
  YYSYMBOL_make_struct_decl = 527,         /* make_struct_decl  */
  YYSYMBOL_528_99 = 528,                   /* $@99  */
  YYSYMBOL_529_100 = 529,                  /* $@100  */
  YYSYMBOL_530_101 = 530,                  /* $@101  */
  YYSYMBOL_531_102 = 531,                  /* $@102  */
  YYSYMBOL_532_103 = 532,                  /* $@103  */
  YYSYMBOL_533_104 = 533,                  /* $@104  */
  YYSYMBOL_534_105 = 534,                  /* $@105  */
  YYSYMBOL_535_106 = 535,                  /* $@106  */
  YYSYMBOL_536_107 = 536,                  /* $@107  */
  YYSYMBOL_537_108 = 537,                  /* $@108  */
  YYSYMBOL_make_tuple_call = 538,          /* make_tuple_call  */
  YYSYMBOL_539_109 = 539,                  /* $@109  */
  YYSYMBOL_540_110 = 540,                  /* $@110  */
  YYSYMBOL_make_dim_decl = 541,            /* make_dim_decl  */
  YYSYMBOL_542_111 = 542,                  /* $@111  */
  YYSYMBOL_543_112 = 543,                  /* $@112  */
  YYSYMBOL_544_113 = 544,                  /* $@113  */
  YYSYMBOL_545_114 = 545,                  /* $@114  */
  YYSYMBOL_546_115 = 546,                  /* $@115  */
  YYSYMBOL_547_116 = 547,                  /* $@116  */
  YYSYMBOL_548_117 = 548,                  /* $@117  */
  YYSYMBOL_549_118 = 549,                  /* $@118  */
  YYSYMBOL_550_119 = 550,                  /* $@119  */
  YYSYMBOL_551_120 = 551,                  /* $@120  */
  YYSYMBOL_expr_map_tuple_list = 552,      /* expr_map_tuple_list  */
  YYSYMBOL_push_table_nesting = 553,       /* push_table_nesting  */
  YYSYMBOL_make_table_decl = 554,          /* make_table_decl  */
  YYSYMBOL_make_table_call = 555,          /* make_table_call  */
  YYSYMBOL_array_comprehension_where = 556, /* array_comprehension_where  */
  YYSYMBOL_optional_comma = 557,           /* optional_comma  */
  YYSYMBOL_table_comprehension = 558,      /* table_comprehension  */
  YYSYMBOL_array_comprehension = 559       /* array_comprehension  */
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
#define YYLAST   11121

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  234
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  326
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1011
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  1785

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   461


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
       2,     2,     2,   216,     2,   233,   228,   212,   205,     2,
     226,   227,   210,   209,   199,   208,   223,   211,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   202,   230,
     206,   200,   207,   201,   229,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   224,     2,   225,   204,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   231,   203,   232,   215,     2,     2,     2,
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
     195,   196,   197,   198,   213,   214,   217,   218,   219,   220,
     221,   222
};

#if DAS2_YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   594,   594,   595,   600,   601,   602,   603,   604,   605,
     606,   607,   608,   609,   610,   611,   612,   616,   617,   621,
     622,   626,   632,   633,   634,   638,   639,   643,   644,   648,
     667,   668,   669,   670,   674,   675,   679,   680,   684,   685,
     685,   689,   694,   703,   718,   734,   739,   747,   747,   786,
     804,   808,   811,   815,   819,   823,   827,   833,   842,   843,
     847,   850,   856,   857,   861,   865,   866,   870,   873,   879,
     885,   888,   894,   895,   899,   900,   904,   905,   909,   910,
     910,   914,   914,   923,   924,   928,   929,   935,   936,   937,
     938,   939,   943,   944,   948,   949,   953,   955,   953,   967,
     967,   975,   977,   975,   989,   989,   997,   999,   997,  1010,
    1017,  1024,  1029,  1038,  1046,  1052,  1056,  1064,  1074,  1074,
    1083,  1091,  1091,  1105,  1105,  1117,  1121,  1128,  1129,  1130,
    1131,  1132,  1133,  1137,  1142,  1150,  1151,  1152,  1156,  1157,
    1158,  1159,  1160,  1161,  1162,  1163,  1164,  1170,  1173,  1179,
    1182,  1188,  1191,  1194,  1200,  1201,  1202,  1203,  1207,  1225,
    1248,  1251,  1261,  1276,  1291,  1306,  1309,  1316,  1320,  1327,
    1328,  1332,  1333,  1337,  1338,  1339,  1343,  1346,  1350,  1357,
    1361,  1362,  1363,  1364,  1365,  1366,  1367,  1368,  1369,  1370,
    1371,  1372,  1373,  1374,  1375,  1376,  1377,  1378,  1379,  1380,
    1381,  1382,  1383,  1384,  1385,  1386,  1387,  1388,  1389,  1390,
    1391,  1392,  1393,  1394,  1395,  1396,  1397,  1398,  1399,  1400,
    1401,  1402,  1403,  1404,  1405,  1406,  1407,  1408,  1409,  1410,
    1411,  1412,  1413,  1414,  1415,  1416,  1417,  1418,  1419,  1420,
    1421,  1422,  1423,  1424,  1425,  1426,  1427,  1428,  1429,  1430,
    1431,  1432,  1433,  1434,  1435,  1436,  1437,  1438,  1439,  1440,
    1441,  1442,  1443,  1444,  1445,  1446,  1447,  1448,  1452,  1453,
    1454,  1455,  1456,  1457,  1458,  1459,  1460,  1461,  1462,  1463,
    1464,  1465,  1466,  1467,  1468,  1469,  1470,  1471,  1472,  1473,
    1474,  1475,  1476,  1477,  1478,  1479,  1480,  1481,  1482,  1483,
    1484,  1485,  1486,  1487,  1488,  1489,  1490,  1491,  1492,  1493,
    1494,  1495,  1496,  1497,  1498,  1499,  1503,  1504,  1508,  1527,
    1528,  1529,  1533,  1539,  1539,  1556,  1559,  1561,  1559,  1573,
    1575,  1573,  1590,  1608,  1626,  1644,  1655,  1656,  1657,  1658,
    1659,  1660,  1661,  1662,  1663,  1664,  1665,  1666,  1667,  1668,
    1669,  1670,  1671,  1672,  1673,  1674,  1676,  1674,  1691,  1696,
    1702,  1708,  1709,  1713,  1714,  1718,  1722,  1729,  1730,  1741,
    1745,  1748,  1756,  1756,  1756,  1759,  1765,  1768,  1772,  1776,
    1783,  1790,  1796,  1800,  1804,  1807,  1810,  1818,  1821,  1829,
    1835,  1836,  1837,  1841,  1842,  1846,  1847,  1851,  1856,  1864,
    1871,  1884,  1887,  1890,  1900,  1900,  1900,  1903,  1903,  1903,
    1908,  1908,  1908,  1916,  1916,  1916,  1922,  1932,  1943,  1958,
    1961,  1964,  1967,  1973,  1974,  1981,  1992,  1993,  1994,  1998,
    1999,  2000,  2001,  2002,  2006,  2011,  2019,  2020,  2024,  2031,
    2035,  2042,  2043,  2044,  2045,  2046,  2047,  2048,  2049,  2053,
    2054,  2055,  2056,  2057,  2058,  2059,  2060,  2061,  2062,  2063,
    2064,  2065,  2066,  2067,  2068,  2069,  2070,  2071,  2072,  2073,
    2077,  2083,  2090,  2102,  2108,  2116,  2124,  2135,  2147,  2151,
    2158,  2161,  2161,  2161,  2166,  2166,  2166,  2179,  2183,  2187,
    2193,  2201,  2209,  2220,  2229,  2235,  2243,  2243,  2243,  2250,
    2254,  2263,  2271,  2279,  2283,  2286,  2294,  2295,  2296,  2303,
    2304,  2305,  2306,  2307,  2308,  2309,  2310,  2311,  2312,  2313,
    2314,  2315,  2316,  2317,  2318,  2319,  2320,  2321,  2322,  2323,
    2324,  2325,  2326,  2327,  2328,  2329,  2330,  2331,  2332,  2333,
    2334,  2335,  2336,  2337,  2338,  2344,  2345,  2346,  2347,  2348,
    2363,  2372,  2373,  2374,  2375,  2376,  2377,  2378,  2379,  2380,
    2381,  2382,  2383,  2384,  2385,  2388,  2388,  2388,  2391,  2396,
    2400,  2404,  2404,  2404,  2409,  2412,  2416,  2416,  2416,  2421,
    2424,  2425,  2426,  2427,  2428,  2429,  2430,  2431,  2432,  2434,
    2438,  2439,  2444,  2450,  2456,  2465,  2468,  2471,  2480,  2481,
    2482,  2483,  2484,  2485,  2486,  2490,  2494,  2498,  2502,  2506,
    2510,  2514,  2518,  2522,  2529,  2530,  2534,  2535,  2536,  2540,
    2541,  2545,  2546,  2547,  2551,  2552,  2556,  2568,  2571,  2572,
    2576,  2576,  2595,  2594,  2609,  2608,  2625,  2637,  2646,  2656,
    2657,  2658,  2659,  2660,  2664,  2667,  2676,  2677,  2681,  2684,
    2688,  2701,  2710,  2711,  2715,  2718,  2722,  2735,  2736,  2740,
    2746,  2752,  2761,  2764,  2771,  2774,  2780,  2781,  2782,  2786,
    2787,  2791,  2798,  2803,  2812,  2818,  2822,  2833,  2840,  2849,
    2852,  2855,  2862,  2866,  2872,  2884,  2887,  2892,  2904,  2905,
    2909,  2910,  2911,  2915,  2918,  2921,  2921,  2941,  2944,  2944,
    2962,  2967,  2975,  2976,  2980,  2983,  2996,  3013,  3014,  3015,
    3020,  3020,  3046,  3047,  3054,  3067,  3068,  3069,  3073,  3083,
    3086,  3092,  3093,  3097,  3098,  3102,  3103,  3107,  3109,  3114,
    3107,  3130,  3131,  3135,  3136,  3140,  3146,  3147,  3148,  3149,
    3153,  3154,  3155,  3159,  3162,  3168,  3170,  3175,  3168,  3196,
    3203,  3208,  3217,  3223,  3227,  3238,  3239,  3240,  3241,  3242,
    3243,  3244,  3245,  3246,  3247,  3248,  3249,  3250,  3251,  3252,
    3253,  3254,  3255,  3256,  3257,  3258,  3259,  3260,  3261,  3262,
    3263,  3264,  3265,  3266,  3267,  3268,  3269,  3270,  3271,  3272,
    3273,  3274,  3275,  3276,  3277,  3278,  3279,  3280,  3281,  3282,
    3283,  3284,  3285,  3286,  3287,  3291,  3292,  3293,  3294,  3295,
    3296,  3297,  3298,  3302,  3313,  3317,  3324,  3336,  3343,  3349,
    3358,  3363,  3373,  3383,  3393,  3406,  3407,  3408,  3409,  3410,
    3414,  3418,  3418,  3418,  3432,  3433,  3437,  3441,  3448,  3451,
    3454,  3457,  3463,  3466,  3480,  3481,  3485,  3486,  3487,  3488,
    3489,  3489,  3489,  3493,  3498,  3505,  3512,  3512,  3519,  3519,
    3526,  3530,  3534,  3539,  3544,  3549,  3554,  3558,  3562,  3567,
    3571,  3575,  3580,  3580,  3580,  3586,  3593,  3593,  3593,  3598,
    3598,  3598,  3604,  3604,  3604,  3609,  3614,  3614,  3614,  3619,
    3619,  3619,  3628,  3633,  3633,  3633,  3638,  3638,  3638,  3647,
    3652,  3652,  3652,  3657,  3657,  3657,  3666,  3666,  3666,  3672,
    3672,  3672,  3681,  3684,  3695,  3711,  3713,  3718,  3723,  3711,
    3749,  3751,  3756,  3762,  3749,  3788,  3790,  3795,  3800,  3788,
    3841,  3842,  3843,  3844,  3845,  3846,  3847,  3851,  3852,  3853,
    3854,  3855,  3859,  3866,  3873,  3879,  3885,  3892,  3899,  3905,
    3914,  3917,  3923,  3931,  3936,  3943,  3948,  3954,  3955,  3959,
    3960,  3964,  3964,  3964,  3972,  3972,  3972,  3979,  3979,  3979,
    3990,  3990,  3990,  3997,  3997,  3997,  4008,  4014,  4014,  4014,
    4028,  4047,  4047,  4047,  4057,  4057,  4057,  4071,  4071,  4071,
    4085,  4094,  4094,  4094,  4114,  4121,  4121,  4121,  4131,  4134,
    4145,  4151,  4174,  4182,  4202,  4227,  4228,  4232,  4233,  4238,
    4241,  4251
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
  "\"|>\"", "\":=\"", "\"<<<\"", "\">>>\"", "\"<<<=\"", "\">>>=\"",
  "\"=>\"", "\"@@\"", "\"@field\"", "\"::\"", "\"&&\"", "\"||\"", "\"^^\"",
  "\"&&=\"", "\"||=\"", "\"^^=\"", "\"..\"", "\"$$\"", "\"$i\"", "\"$v\"",
  "\"$b\"", "\"$a\"", "\"$t\"", "\"$c\"", "\"$f\"", "\"...\"",
  "\"integer constant\"", "\"long integer constant\"",
  "\"unsigned integer constant\"", "\"unsigned long integer constant\"",
  "\"unsigned int8 constant\"", "\"floating point constant\"",
  "\"float16 constant\"", "\"double constant\"", "\"name\"",
  "\"new line, comma\"", "\"new line, semicolon\"",
  "\"start of the string\"", "STRING_CHARACTER", "STRING_CHARACTER_ESC",
  "\"end of the string\"", "\"{\"", "\"}\"",
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

#define YYPACT_NINF (-1605)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-904)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1605,    39, -1605, -1605,    61,   -56,   -87,   753, -1605,   -71,
   -1605, -1605, -1605, -1605,    22,   199, -1605, -1605, -1605, -1605,
      23,    23,    23, -1605,   299, -1605,   151, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605,    40, -1605,    85,
      99,   178, -1605,   138,   138, -1605, -1605, -1605,   117,    23,
      23, -1605, -1605,   151,   753,   753,   753,   197,   236, -1605,
   -1605, -1605, -1605,   199,   199,   199,   185, -1605,   694,    -9,
   -1605, -1605, -1605, -1605,   315, -1605,   347, -1605,   768,    84,
      61,   273,   -56,   257, -1605,   284,   294,   401,    60,   324,
   -1605, -1605,   781,   412,   420,   447, -1605,   552,   328, -1605,
   -1605,   157,    61,   199,   199,   199,   199,   337, -1605,   790,
     819,   437,   489,   840, -1605, -1605,   465, -1605, -1605,   606,
   -1605, -1605, -1605,   763,   108, -1605, -1605, -1605, -1605,   138,
     138,   604,   138,   696,   701,   712, -1605, -1605,   674,   683,
   -1605, -1605,   689,   697,   337,   337, -1605, -1605,   718, -1605,
     208, -1605,   657,   760,   694, -1605,   776, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605,   802, -1605, -1605, -1605, -1605, -1605,
   -1605,   837, -1605, -1605, -1605, -1605,   833, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605,   219,   604,   604,   604, -1605, -1605,
     946,  2657,  2657,   939, -1605,   698,   824, -1605, -1605, -1605,
   -1605, -1605, 10713, -1605,   815,   889,   309,    61,   866,   848,
   -1605, -1605, -1605,   108, -1605, -1605,   832,   842,   843,   804,
     844,   845, -1605, -1605, -1605,   821, -1605, -1605, -1605, -1605,
   -1605,   564, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605,   846, -1605, -1605, -1605,   847,   849, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605,   850,   851,   834,    22,
     226, -1605, -1605, -1605, -1605,    80,   830,   855,   855, -1605,
   -1605, -1605, -1605, -1605, -1605,   869, -1605,   836,   838,  1766,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,  1026,  1028,
   -1605,   839, -1605,   337,   908,   824, -1605,   875,   337, -1605,
   -1605,   837,   337,    61, -1605,   553, -1605, -1605, -1605, -1605,
   -1605,  8772, -1605, -1605,   877,   870,   -72,   -51,   -34, -1605,
   -1605,  8772,   278, -1605,  6602, -1605, -1605, -1605,    21, -1605,
   -1605, -1605,    14, -1605,  6819,   857,  2234, -1605,   856, -1605,
   -1605, 10428, 10543, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605,   886,   865, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605,  1069, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
     903,   868, -1605, -1605,   -67,   -15,   -59, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605,   863,   893, -1605,   -61,
   -1605,   337,   907,  2657, -1605,    20,  2657,  2657,  2657,   895,
     896, -1605, -1605,    36,    22,   897,    33, -1605,   293,   873,
     898,   901,   885,   906,   887,   397,   909, -1605,   578,    26,
     910,  9634,  9634,   405,   888,   891,   899,   900,   904,   918,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
    9634,  9634,  9634,  9634,  9634,  4432,  5300, -1605, -1605, -1605,
   -1605, -1605, -1605,   919, -1605, -1605, -1605, -1605,   905, -1605,
   -1605,    62,    62, -1605,    62,    62,   920,  9956, -1605, -1605,
     922, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,  2657,
    2657,   923,   942,  2657,   839,  2657,   839,  2657,   839,  9967,
     938,   924, -1605,  6602, -1605,  2657,  8772,   925,   954, -1605,
   -1605, -1605, -1605, -1605,   932, -1605, -1605,   935,  7036, -1605,
      80, -1605,  9967,   938, -1605, -1605, -1605, -1605, -1605, -1605,
   10932,  1079,  1410,   930, -1605,   184,   933,   175,   934,  2657,
    2657, -1605,  9204, -1605, -1605, -1605, -1605,    22, -1605,   615,
     936,  1121,   589, -1605, -1605, -1605,  1406, -1605, -1605, -1605,
    8772,   685,   703,   958,   354, -1605, -1605, -1605, -1605,   940,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,   581,
   -1605,   961,   964,   965, -1605,  6602,  2657,  8772,  8772, -1605,
   -1605,  8772, -1605,  8772, -1605,  6602, -1605, -1605,  6602,   966,
   -1605,  2657,    54,    54,   948,   949,   183, -1605, -1605,  8772,
    8772,  8772,  8772,  8772,  8772,   828,    54,    54,   -26,    54,
      54,   950,  1164,   953,   955,   191,   954,   981,   956,   337,
    3998,   199,  1178, -1605, -1605,   905, -1605, -1605, -1605, -1605,
   -1605, 10374, 10489,  9634,  9634, -1605, -1605,  9634,  9634,  9634,
    9634,   995,  9634,   370,  8772,  9634,  9634,  9634,  9634,  8772,
    9634,  9634,  9634,  9634,  9419,  9634,  9634,  9634,  9634,  9634,
    9634,  9634,  9634,  9634,  9634, 10805,  8772,  5517,   710,   740,
   -1605, -1605,   998,   743,   -15,   748,   -15,   756,   -15,   -99,
   -1605,   409,   855,   986, -1605,   430, -1605,  2657,   954,   450,
     855, -1605, -1605,  7253, -1605, -1605, -1605, -1605,   967,  1000,
   -1605,    23, -1605,    23, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605,  8772, -1605, -1605,   522,   392,   392,   392, -1605,
     855,   855,  9634, 10079, -1605,  1001, -1605, -1605, -1605, -1605,
    8772,  1002,   587,  2657,    20, -1605,  8772,    23, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605,  2657,  2657,  2657,  2657,  4649,
    1004,  8772,  2657, -1605, -1605, -1605,  2657,   954,   679, -1605,
     999,   970,  2657,  2657,   972,  2657,   975,  2657,   954,  2657,
    9967,   954, -1605,   938,   310,  8772,  8772,  2657,   839,   976,
     978,   980,   982,   991,   992, -1605,  8772,   786,   132,   968,
   -1605,  8772, -1605,  8772, -1605,  8772,   993,   426, -1605, -1605,
    7470,   119,  4215, -1605,   260,   994,   198,  1005,   839,  2481,
    1178,  1022,  1006, -1605, -1605,  1027,  1008, -1605, -1605,  1088,
    1088,  1111,  1111,   513,   513,  1010,   422,  1012, -1605,  1020,
     196,   196,   922,  1088,  1088, 10079, -1605, -1605, 10220, 10191,
    1803, 10079, 10604,  1249,   931,  1364,   787,  1111,  1111,   227,
     227,   422,   422,   422,   521,  8772,  1029,  1030,   688,  8772,
    1253,  1031,  1033, -1605,   302, -1605, -1605, -1605,   259, -1605,
    1052, -1605,  1054, -1605,  1066,  2657, -1605,  9967,  2657, -1605,
     938,   483,  1047,  1049,  2657,  8772, -1605, -1605,  1077,   -68,
   -1605,  9806, -1605,   212, -1605,  1051,  1053,  1238, -1605, -1605,
     222, -1605, -1605, -1605, 10112,  2842,  1083, -1605,   -68,    32,
    1057, -1605,  1059,  1244,  1406,  8772,    23, -1605, -1605, -1605,
   -1605,   855,   500,   835,   766,   700,   321,  1061,  1063,   487,
    1064,   767,  2657,  9967,   938,  1125,  1065,  1067,  2657,  8772,
    1068, -1605,  1135,  1408, -1605,  1557, -1605,  1602,  1074,  2059,
     539,  1075,  2657,   560,  1178,  1076,  1078,  2225,   -15, -1605,
   -1605, -1605, -1605, -1605,  1080,  1092,  1081,  1261,  1119,    38,
     132,  1082, -1605, -1605, -1605,  1084,   306,  1087,  1086,   999,
     322, -1605,  1097,   209,  5734, -1605, -1605, -1605,   297,   -15,
   -1605,  7687, -1605,  1094,  7904,  1140,  1142, -1605,    23,  1133,
    8121,    88,  8338, -1605, -1605, -1605,    23,    23,  1327, -1605,
     974, -1605, -1605,  1326, -1605, -1605,  1332, -1605,  1302,    23,
   -1605,    23,    23,    23,    23,    23, -1605,  1279, -1605,    23,
    2031,   839, -1605,  8772, -1605,  8772,  4866,  8772, -1605,  1143,
    1120, -1605, -1605,  9634,  1122, -1605,  1126,  8772,  5083,  1124,
   -1605,  1127, -1605,  5951, -1605,  7253, -1605, -1605, -1605,  1165,
   -1605,  1167, -1605, -1605, -1605, -1605, -1605, -1605,   855, -1605,
   -1605,   855, -1605, -1605,  1049, -1605, -1605,   855, -1605,  8772,
   -1605,   676, -1605, -1605, -1605,  1128, -1605,  1129, -1605,  8772,
    1170,   616,  2657, -1605,  8772,  1130,  8772,   682, -1605,  1174,
   -1605, -1605,  1356,   837, -1605,  8772,  1176, -1605,  8772,    23,
   -1605, -1605, -1605, -1605,  1139, -1605, -1605, -1605,  1141,  1180,
   -1605, -1605,  2230,   566,   612, -1605, -1605,  8772,  4429, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,  4646,
   -1605,   134, -1605, -1605, -1605,  1163,  6168, -1605,  1175,  8772,
    1182, -1605,   338,  6602,   147,    44,   332,  8772,  8772,  8772,
     132, -1605, -1605, -1605,   426,  1147,  4215,   339,  1186,  1187,
    1152,  1192,  1193, -1605,   383,   337,  8772, -1605,  1369,  8772,
   -1605,  1184,  1199, -1605,  1185,  1227, -1605,  1094,  8772, -1605,
   -1605, -1605, -1605,  1183, -1605, -1605,  1191,   -75,   -75,  1195,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605,   107, -1605,  9634,
    9634,  9634,  9634,  9634,  9634,  9634,  9634,  9634,  9634,  8772,
    9634,  9634,  9634,  9634,  9634,  9634,  9634,   -15,  2657,  1196,
    2657,  1198,  4215, -1605,   387,   390,  1200, -1605,  8772, 10112,
    8772, -1605,  1203,  4215, -1605,   399,   423,  8772, -1605, -1605,
   -1605,   445, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
    1211, -1605,  1181, -1605, -1605,  1204, -1605,  1206,  1379,   -64,
   -1605,  1375, -1605, -1605,  1194,  1233,   841,  1368,    23,  1210,
   -1605,    23, -1605,  1214,  1216, -1605, -1605,  8772,  1237, -1605,
   -1605, -1605, -1605,  1219,  1220,  1222,  1223,  1236,  1239,  1245,
    1393,  1248, -1605,  1251,  8555,  1094,   648, -1605, -1605,   449,
   -1605, -1605,  1243, -1605,  1275, -1605,   470,  1252,  1432,  1119,
    6602,  8772,  8772,  1254, -1605, -1605,    46, -1605,   464, -1605,
   -1605, -1605,  1290, -1605, -1605,   297, -1605,   -59, -1605,  1094,
   -1605,  2657,  8772, -1605, -1605, -1605, -1605,  3074,  8772,  8772,
      61,   866,  1257,  1258,  8772,  1119, -1605, -1605, -1605,  9956,
    9956,  9956,  9956,  9956,  9956,  9956,  9956,  9956,  9956,  9956,
   -1605, -1605,  9956,  9956,  9956,  9956,  9956,  9956,  9956,   337,
    4863, -1605,   769, -1605,   493,  6385, -1605, -1605, -1605,  2657,
    1260,  1262, -1605,   546,  6385, -1605, -1605,  1263, -1605,  8772,
   -1605, -1605,  8772,  1291,  8772, -1605, -1605, -1605,  2657, -1605,
   -1605,   751, -1605,    16, -1605, -1605, -1605,  1393,  1393,  1264,
    1259,  1266,  1267,  1268,  6602, -1605,  8772,  8772,  8772,  8772,
    6602, -1605, -1605,  1393,  1270,  1393, -1605,  1272, -1605, -1605,
     648, -1605,  1295, -1605, -1605,  1271,  8772,  1308,   482,   499,
   -1605, -1605,   342,  6602,  1273,  1281, -1605, -1605, -1605,   855,
   -1605,  1277,  1287,  1293,   549,   132,  8772,  1296,   504,   237,
     -59, -1605, -1605,  1297,   505,   774, -1605, -1605,  1298,   507,
   -1605, -1605,  1299, -1605, -1605,  1300,    -2,  1496,    16, -1605,
   -1605,   841,   -73,   -73, -1605,  8772,  1393,  1393,   700,  1303,
    1305,  1306,  1307,  1309,   954,   -73,  1393,   700, -1605, -1605,
   -1605,  8772,  1311, -1605, -1605,  1310,  8772,  8772,   515, -1605,
   -1605,  1375,  1523,   337, -1605,    58,  1312,   337,   228, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605,  1496,   522,   700,  1350,  1351,
   -1605,  1324,  1325,  1334,   -73,   -73,  1350,  1336, -1605, -1605,
   -1605, -1605, -1605,  1337,  1338,   700,  1340,  1347, -1605,  8772,
   -1605, -1605,  1353, -1605,  8989,    23, -1605,  6602,   337,  1094,
    2657,    20, -1605,  3306, 10713, -1605, -1605, -1605, -1605,   516,
    1328, -1605, -1605, -1605, -1605,  1354,  1357, -1605, -1605, -1605,
    1359, -1605,  1536,  1366,  1347,  8772, -1605, -1605, -1605, -1605,
   -1605,  9956, -1605,  1361,   517,  1094, -1605,   380,  8772,  1362,
      23, 10713, -1605,   700, -1605, -1605, -1605,  8772, -1605,  1370,
    1347, -1605,   817,  8989,   337, -1605,  8772,    23, -1605, -1605,
     337,   548, -1605, -1605,  1371, -1605,   337, -1605, -1605,  1372,
   -1605,    23,  1094,    23, -1605,   -59, -1605, -1605,  3538, -1605,
    8772, -1605, -1605, -1605, -1605,  1376,  1373,  1374,  1375, -1605,
   -1605,  8989,   337, -1605, -1605,    23, -1605,  3770, -1605,  1373,
    1380,   817,  1375, -1605, -1605
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,   171,     1,   393,     0,     0,    58,   707,   394,     0,
     925,   915,   920,    20,     0,     0,    19,    16,    15,     3,
       0,     0,     0,     8,   745,     7,   688,     6,    11,     5,
       4,    13,    12,    14,   136,   137,   135,   145,   147,    49,
      67,    64,    65,     0,     0,    50,   709,   708,     0,     0,
       0,    26,    25,   688,   707,   707,   707,     0,   367,    47,
     155,   156,   157,     0,     0,     0,   158,   160,   167,     0,
     154,    21,    10,     9,   316,   727,     0,   689,   690,     0,
       0,     0,     0,     0,    51,     0,     0,    59,    62,   710,
     712,   713,    22,     0,     0,     0,   369,     0,     0,   166,
     161,     0,     0,     0,     0,     0,     0,    76,   317,   319,
     715,   737,   736,   740,   692,   691,   698,   143,   144,     0,
     141,   142,   139,     0,     0,   138,   148,    68,    66,     0,
       0,    52,     0,     0,     0,     0,    63,    60,     0,     0,
      23,    24,    27,   825,    76,    76,   368,    45,    48,   165,
       0,   162,   163,   164,   168,    74,    77,   172,   321,   320,
     323,   318,   717,   716,     0,   739,   738,   742,   741,   746,
     693,   614,   140,    30,    31,    35,     0,   131,   132,   129,
     130,   128,   127,   133,     0,    54,    55,    53,    57,    56,
      62,     0,     0,     0,    29,     0,   725,   916,   921,    46,
     159,    75,     0,   718,   719,   733,   695,     0,   615,     0,
      32,    33,    34,     0,   146,    61,     0,     0,     0,     0,
       0,     0,   755,   798,   756,   814,   757,   761,   762,   763,
     764,   804,   768,   769,   770,   771,   772,   773,   774,   799,
     800,   801,   802,   885,   760,   767,   803,   892,   899,   758,
     765,   759,   766,   775,   776,   777,   778,   779,   780,   781,
     782,   783,   784,   785,   786,   787,   788,   789,   790,   791,
     792,   793,   794,   795,   796,   797,     0,     0,     0,     0,
     813,   846,   849,   847,   848,   912,   842,   714,   711,    28,
     828,   829,   826,   827,   723,   726,   926,     0,     0,     0,
     268,   269,   270,   271,   272,   273,   274,   275,   276,   277,
     278,   279,   280,   281,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,     0,     0,
     179,   173,   267,    76,     0,   725,   734,     0,    76,   697,
     694,   614,    76,     0,   677,   669,   699,   134,   850,   876,
     879,     0,   882,   872,     0,     0,   886,   893,   900,   906,
     909,     0,   844,   856,   361,   862,   867,   861,     0,   875,
     871,   864,     0,   866,     0,   843,     0,   724,     0,   917,
     922,   258,   259,   256,   182,   183,   185,   184,   186,   187,
     188,   189,   215,   216,   213,   214,   206,   217,   218,   207,
     204,   205,   257,   240,     0,   255,   219,   220,   221,   222,
     193,   194,   195,   190,   191,   192,   203,     0,   209,   210,
     208,   201,   202,   197,   196,   198,   199,   200,   181,   180,
     239,     0,   211,   212,   614,   176,     0,   805,   808,   811,
     812,   806,   809,   807,   810,   720,     0,   731,   747,     0,
     149,    76,     0,     0,   670,     0,     0,     0,     0,     0,
       0,   515,   516,     0,     0,     0,     0,   509,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   804,     0,     0,
       0,     0,     0,   428,     0,     0,     0,     0,     0,     0,
     603,   441,   443,   442,   444,   445,   446,   447,   448,    41,
       0,     0,     0,     0,     0,   361,     0,   426,   427,  1000,
     513,   512,   590,   510,   583,   582,   581,   580,   169,   586,
     511,   585,   584,   557,   517,   558,     0,   506,   562,   518,
       0,   514,   937,   939,   938,   507,   941,   940,   508,     0,
       0,     0,   831,     0,   173,     0,   173,     0,   173,     0,
       0,     0,   858,     0,   855,     0,     0,     0,  1007,   419,
     869,   870,   863,   865,     0,   868,   839,     0,     0,   914,
     913,   927,   648,   654,   260,   262,   261,   263,   254,   238,
     264,   241,   223,     0,   174,   392,   639,   640,     0,     0,
       0,   322,     0,   329,   423,   324,   728,     0,   735,     0,
       0,   671,   669,   696,   150,   678,     0,   667,   668,   666,
       0,     0,     0,     0,   836,   961,   964,   372,   813,   376,
     375,   381,   930,   936,   931,   932,   933,   935,   934,     0,
     413,     0,     0,     0,   991,     0,     0,     0,     0,   404,
     407,     0,   410,     0,   995,     0,   973,   977,     0,     0,
     967,     0,   545,   546,     0,     0,   481,   478,   480,     0,
       0,     0,     0,     0,     0,     0,   522,   521,   559,   520,
     519,     0,     0,     0,     0,   367,  1007,  1007,     0,    76,
       0,     0,   436,   428,   358,   169,   335,   333,   334,   332,
     853,     0,     0,     0,     0,   547,   548,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   496,     0,     0,     0,     0,
     815,   830,     0,     0,   176,     0,   176,     0,   176,   367,
     646,     0,   644,     0,   652,     0,   816,     0,  1007,     0,
     365,   420,   854,  1008,   362,   860,   838,   841,     0,   820,
     649,    94,   655,    94,   265,   266,   243,   244,   246,   245,
     247,   248,   249,   250,   242,   251,   252,   253,   227,   228,
     230,   229,   231,   232,   233,   234,   225,   226,   235,   236,
     237,   224,     0,   390,   391,     0,   614,   614,   614,   175,
     178,   177,     0,   424,   358,   704,   732,   743,   627,   748,
       0,     0,     0,     0,     0,   685,     0,     0,   851,   877,
     880,    18,    17,   834,   835,     0,     0,     0,     0,   959,
       0,     0,     0,   981,   984,   987,     0,  1007,     0,   998,
    1007,     0,     0,     0,     0,     0,     0,     0,  1007,     0,
       0,  1007,   970,     0,     0,     0,     0,     0,   173,     0,
       0,     0,     0,     0,     0,    44,     0,    42,     0,     0,
     980,     0,   658,     0,   657,     0,     0,  1008,   952,   550,
     363,     0,   361,   499,     0,     0,     0,     0,   173,     0,
     436,     0,     0,   569,   568,     0,     0,   570,   574,   523,
     524,   536,   537,   534,   535,     0,   563,     0,   555,     0,
     587,   588,   589,   525,   526,   592,   593,   594,   541,   542,
     543,   544,     0,     0,   539,   540,   538,   532,   533,   528,
     527,   529,   530,   531,     0,     0,     0,   487,     0,     0,
       0,     0,     0,   504,     0,   883,   873,   817,     0,   887,
       0,   894,     0,   901,     0,     0,   907,     0,     0,   910,
       0,     0,     0,   844,     0,     0,   421,   840,   821,   721,
      92,    95,   918,    95,   923,     0,     0,   749,   636,   637,
     659,   641,   643,   642,   425,     0,   700,   705,   721,   630,
       0,   673,     0,   674,     0,     0,     0,   687,   852,   878,
     881,   837,     0,     0,     0,   960,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1008,
       0,   560,     0,     0,   561,     0,   591,     0,     0,     0,
       0,     0,     0,     0,   436,     0,     0,     0,   176,   598,
     599,   600,   601,   602,     0,    38,     0,   110,     0,     0,
       0,     0,   943,   942,   549,     0,     0,     0,     0,  1007,
       0,   500,     0,     0,     0,   503,   501,   170,     0,   176,
     360,   384,   382,     0,     0,     0,     0,   383,     0,     0,
       0,    76,     0,   355,   440,   336,     0,     0,     0,   349,
       0,   350,   344,     0,   341,   340,     0,   342,     0,     0,
     359,     0,    90,    91,    88,    89,   351,   396,   339,     0,
     449,   173,   565,     0,   571,     0,     0,     0,   553,     0,
       0,   575,   579,     0,     0,   556,     0,     0,     0,     0,
     488,     0,   497,     0,   551,     0,   505,   884,   874,     0,
     832,     0,   888,   890,   895,   897,   902,   904,   645,   908,
     647,   651,   911,   653,   844,   845,   857,   366,   422,     0,
     702,   722,   928,    93,   650,     0,   656,     0,   638,     0,
       0,     0,     0,   660,     0,     0,     0,   722,   729,     0,
     628,   744,     0,   614,   672,     0,     0,   682,     0,     0,
     686,   962,   965,   373,     0,   378,   379,   377,     0,     0,
     416,   414,     0,     0,     0,   992,   990,   363,     0,   999,
    1002,   405,   408,   411,   996,   994,   974,   978,   976,     0,
     968,    76,   479,   613,   482,     0,     0,    39,     0,     0,
       0,   397,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1001,   364,   502,     0,     0,   361,     0,     0,     0,
       0,     0,     0,   434,     0,    76,     0,   385,     0,     0,
     370,     0,     0,   354,     0,     0,    71,     0,     0,   387,
     358,   352,   353,     0,    83,    84,     0,   151,   151,     0,
     343,   338,   345,   346,   347,   348,   395,     0,   337,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   176,     0,     0,
       0,     0,   361,   473,     0,     0,     0,   576,     0,   564,
       0,   554,     0,   361,   489,     0,     0,     0,   552,   498,
     494,     0,   819,   833,   818,   891,   898,   905,   859,   822,
     823,   703,     0,   919,   924,     0,   751,     0,   752,   662,
     661,   325,   701,   706,     0,     0,   621,   624,     0,     0,
     676,     0,   684,     0,     0,   374,   380,     0,     0,   415,
     982,   985,   988,     0,     0,     0,     0,     0,     0,     0,
     959,     0,   971,     0,     0,     0,     0,   485,   604,     0,
      36,    43,     0,   112,     0,   113,     0,     0,   114,     0,
       0,     0,     0,     0,   945,   944,     0,   470,     0,   472,
     431,   432,     0,   430,   429,     0,   437,     0,   386,     0,
     371,     0,     0,    69,    70,   120,   388,     0,     0,     0,
       0,   153,     0,     0,     0,     0,   679,   402,   401,   461,
     462,   464,   463,   465,   455,   456,   457,   466,   467,   451,
     452,   453,   454,   468,   469,   458,   459,   460,   450,    76,
       0,   612,     0,   610,     0,     0,   474,   477,   607,     0,
       0,     0,   606,     0,     0,   490,   493,     0,   495,     0,
     929,   750,     0,     0,     0,   326,   331,   730,     0,   622,
     623,   624,   625,   616,   631,   675,   683,   959,   959,     0,
       0,     0,     0,     0,   361,  1003,   363,     0,     0,     0,
       0,   960,   975,   959,     0,   959,   595,     0,   597,   483,
       0,   605,    40,   111,   398,     0,     0,     0,     0,     0,
     947,   946,     0,     0,     0,     0,   435,   438,   389,   126,
     125,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   566,   572,     0,     0,     0,   611,   609,     0,     0,
     608,   824,     0,   754,   663,     0,     0,   619,   616,   617,
     618,   621,   958,   958,   417,     0,   959,   959,   950,     0,
       0,     0,     0,     0,  1007,   958,   959,   950,   596,   486,
      37,     0,     0,   116,   117,     0,     0,     0,     0,   471,
     433,   325,    85,    76,   152,     0,     0,    76,   669,   403,
     680,   681,   439,   567,   573,   475,   476,   577,   491,   492,
     753,   358,   629,   620,   632,   619,     0,     0,   955,  1007,
     957,     0,     0,     0,   958,   958,   951,     0,   993,  1004,
     406,   409,   412,     0,     0,   950,     0,  1005,   115,     0,
     949,   948,     0,   357,     0,     0,   107,     0,    76,     0,
       0,     0,   578,     0,     0,   634,   665,   664,   626,     0,
    1008,   956,   963,   966,   418,     0,     0,   989,   997,   979,
       0,   969,     0,     0,  1005,     0,    86,    90,    91,    88,
      89,    87,   109,    99,     0,     0,   124,     0,     0,     0,
       0,     0,   953,     0,   983,   986,   972,     0,  1009,     0,
    1005,    96,    78,     0,    76,   122,     0,     0,   328,   633,
      76,     0,  1006,  1010,     0,   358,    76,    72,    73,     0,
     108,     0,     0,     0,   400,     0,   954,  1011,     0,    79,
       0,   100,   119,   399,   635,     0,   104,     0,   325,   101,
      80,     0,    76,    98,   358,     0,    81,     0,   105,   104,
       0,    78,   325,    82,   103
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1605, -1605,  -945,    -1, -1605, -1605, -1605, -1605, -1605,   915,
    1540, -1605, -1605, -1605, -1605, -1605, -1605,  1601, -1605, -1605,
   -1605,   210, -1605, -1605,  1430, -1605, -1605,  1539, -1605, -1605,
   -1605, -1605,  -141,  -159, -1605, -1605, -1605, -1605, -1604,   859,
     861, -1605, -1605, -1605, -1605,  -156, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1042, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605,  1411, -1605, -1605,   -44,   -97,  -309,   327, -1605,
   -1605,   528,   927,   921,   620,  -541,  -732, -1605,  -345, -1605,
   -1605, -1605, -1583, -1605, -1605, -1500, -1605, -1605, -1077, -1605,
   -1605, -1605, -1605, -1605, -1605,  -813,  -378, -1192,   871,   -13,
   -1605, -1605, -1605, -1605, -1605, -1600, -1591, -1590, -1587, -1605,
   -1605,  1629, -1605, -1144, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605,  -518, -1404,   374,
     205, -1605,  -850, -1605,   378, -1605, -1605, -1605, -1605, -1338,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,   543,
    1131, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,  -162,
      59,     1,    57,   139, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605,   216,  -560,  -811, -1605,  -564,  -762, -1605,  -982,     3,
      10, -1605,  -619,  -612, -1605, -1605, -1605, -1270, -1605,  1604,
   -1605, -1605, -1605, -1605, -1605,   461,   651, -1605,   990, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605,   652, -1605,  1313, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605,   -84, -1605,  1188, -1605, -1605, -1605,
    1433, -1605, -1605, -1605,  -617, -1605, -1605,  -353,  -930, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,  -161, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605,  -792, -1510,  -666, -1605,
   -1605, -1461, -1231,  1189, -1605, -1605, -1605, -1605, -1605, -1605,
   -1605, -1605, -1605, -1605,  1190, -1605, -1605,  1201, -1605, -1605,
   -1605, -1605, -1605, -1605, -1605, -1605, -1605, -1605,  1009, -1605,
    -471,  1202,  -977,  -683,  1205,  -468
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,   843,   844,    18,   142,    53,   194,    19,   176,
     182,  1542,  1248,  1410,   685,   530,   148,   531,    98,    21,
      22,    87,    44,    45,   137,    23,    41,    42,  1106,  1107,
    1749,   156,   157,  1750,  1766,  1779,  1296,  1675,  1108,   991,
     992,  1732,  1745,  1765,  1733,  1770,  1774,  1780,  1771,  1109,
    1110,  1713,  1111,  1069,  1112,  1113,  1114,  1115,  1116,  1117,
    1118,  1119,   183,   184,    37,    38,    39,   208,  1452,    66,
      67,    68,    69,   702,    24,   455,   611,   351,   352,   109,
      25,   160,   353,   161,   202,  1506,  1585,  1719,   614,   824,
    1195,   532,  1120,  1290,  1561,   909,   693,  1078,   769,   533,
    1121,   639,   848,  1385,   534,  1122,  1123,  1124,  1125,  1126,
     815,  1127,  1307,  1252,  1457,  1128,   535,   862,  1396,   863,
    1397,   865,  1398,   536,   852,  1389,   537,   578,   615,   538,
    1273,  1274,   908,   539,   706,   540,  1129,   541,   542,   678,
     543,   877,  1406,   878,  1540,   544,   960,  1349,   545,   579,
     547,  1328,  1633,  1330,  1634,  1489,  1682,   548,   549,   605,
    1591,  1644,  1511,  1513,  1378,  1009,  1203,  1684,  1721,   606,
     607,   608,   760,   761,   781,   764,   765,   783,   895,   998,
     999,  1688,   630,   475,   622,   365,  1569,   623,   366,    78,
     116,   206,   361,    27,   171,  1007,  1181,  1008,    48,    49,
     139,    28,    50,   164,   204,   355,  1182,   295,   296,    29,
     110,   825,  1374,   618,   357,   358,   113,   169,   829,    30,
      76,   205,   619,  1000,   550,   465,   282,   283,   968,   989,
     196,   284,   752,  1353,   977,   633,   395,   285,   574,   286,
     476,  1018,   575,   767,   560,  1158,   477,  1019,   478,  1020,
     559,  1157,   563,  1162,   564,  1355,   565,  1164,   566,  1356,
     567,  1166,   568,  1357,   569,  1169,   570,  1172,   762,    31,
      55,   297,   592,  1185,    32,    56,   298,   593,  1187,    33,
      54,   398,   779,  1362,   641,   551,   697,  1657,   698,  1649,
    1650,  1651,  1028,   552,   846,  1383,   847,  1384,   873,  1403,
    1052,  1534,   869,  1400,   553,   870,  1401,   554,  1032,  1521,
    1033,  1522,  1034,  1523,   856,  1393,   867,  1399,  1079,   699,
     555,   556,  1703,   774,   557,   558
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      17,    59,    70,   197,   198,   150,   577,   836,   696,   209,
     834,  1005,   645,   896,   898,   648,  1278,   845,  1194,    71,
      72,    73,   970,   754,   972,   756,   974,   758,  1255,   782,
     287,   288,   780,  1557,   905,  1394,   126,  1458,   651,     2,
    -171,   479,   480,   590,  1180,   669,     3,   582,    90,    91,
      70,    70,    70,  1176,   580,   768,   595,   597,  1253,  1050,
    1131,   486,  1589,  1180,  1420,    97,  1553,   488,  1539,     4,
    1706,     5,  1199,     6,  1707,   711,   712,  -889,  1677,     7,
      34,    35,   135,  1708,  1709,   982,   892,  1710,   207,     8,
      70,    70,    70,    70,  1259,     9,   207,  1666,  -896,   117,
     118,  1720,   612,   975,   495,   496,   694,   281,   281,   603,
    1083,  1053,   620,   385,    43,  -903,  1080,   136,    51,    10,
     626,  1673,   841,   177,   178,    40,   723,   724,   621,  1751,
    -889,   842,  1652,  1707,   609,  -889,   894,   857,  1740,   396,
     386,   387,  1708,  1709,  1664,  1590,  1710,   868,   980,  1450,
     871,  -896,   984,  1647,  -889,  1700,  -896,    52,   652,   653,
     604,   498,   499,   362,    11,    12,  1632,  1775,  -903,  1532,
     627,  1707,   613,  -903,  1036,  -896,   628,  1040,   280,   280,
    1708,  1709,   904,  1027,  1710,  1048,    57,   610,  1051,    13,
     106,   813,  -903,  1695,  1696,   715,   716,   745,   746,   469,
      57,   396,  1609,   721,  1241,   360,   723,   724,   725,   726,
    1445,    58,   456,    77,    13,  1015,   107,   468,  1426,   583,
     629,   470,  1223,  1200,   703,    58,   581,   388,    16,   964,
      13,   389,   670,    60,   814,  1082,  1361,  1254,   584,   654,
      79,  1038,   637,  1254,  1358,  1254,   119,   585,   711,   712,
      36,    14,  1361,    16,    88,   785,    15,  1254,   936,   655,
     525,   937,    61,    15,  1201,   120,   382,   529,  1773,    16,
     121,   133,  1224,   122,  1422,  1548,   123,   745,   746,   155,
     620,   390,  1784,   134,    80,   391,  1592,  1593,   392,   179,
     527,   528,  1267,   704,   180,   131,   621,   181,   694,  1631,
     123,    81,  1605,   858,  1607,  1066,    89,    74,  1080,    83,
     124,  1568,   281,   393,   663,   631,   632,   634,   874,   471,
    1417,  1067,   103,   104,   105,   155,  1245,    84,  1538,    62,
     624,  1026,  -484,  1455,  1600,    75,  1418,  1058,  1456,   185,
     186,   892,   187,   385,  1335,   721,  1081,   893,   723,   724,
      85,  1764,   111,   112,    63,    97,  1346,  1275,  1068,  1214,
    1404,    86,  1558,    57,   984,  1654,  1655,  1089,   715,   716,
     386,   387,   892,  1419,   817,  1665,   721,    82,   722,   723,
     724,   725,   726,   280,   149,  -484,    96,  1504,    58,   281,
    -484,   894,   281,   281,   281,  1208,  1262,   106,   748,   749,
      97,   763,   753,    13,   755,   818,   757,    80,  1264,  -484,
     620,   102,  1219,   385,   770,    64,  1173,  1170,   213,   745,
     746,  1191,   894,  1087,  1192,    65,   621,  1193,    13,  1186,
    1680,  1184,   383,   474,  1265,   200,   980,   742,   743,   744,
     386,   387,    16,   711,   712,   108,   214,  1268,   820,   821,
     745,   746,   384,  1269,   127,    83,   892,   388,  1159,  1084,
     280,   389,  1258,   280,   280,   280,  1160,    16,   129,  1629,
     638,   649,   892,    84,  1428,   281,   281,  1447,   893,   281,
    1014,   281,   892,   281,   572,   281,  1270,  1085,  1421,  1161,
     677,   281,   892,  1022,  1023,   130,    85,  1271,  1616,   656,
      13,  1155,  1272,  1035,   573,   132,   894,    86,   281,  1042,
    1043,   390,  1045,   138,  1047,   391,  1049,  1054,   392,   657,
    1155,   147,   894,  1625,  1057,   281,   281,   388,   155,  1156,
     627,   389,   894,   385,   711,   712,   628,  1414,  1264,    16,
    1484,   359,   894,   393,   841,    13,   280,   280,  1215,   927,
     280,  1493,   280,   842,   280,   207,   280,   396,   900,   928,
     386,   387,   280,   715,   716,  1415,  1429,   165,   603,    57,
    1617,   721,   281,   722,   723,   724,   725,   726,   674,   280,
     629,   390,  1435,   675,    16,   391,  1485,   281,   392,  1264,
    1327,    99,   100,   101,    58,  1479,   280,   280,  1494,   841,
      13,   143,  1716,   664,   826,  1075,   770,   980,   842,   144,
    1436,   676,   133,   393,  1486,  1076,   976,  1487,  1334,   166,
     841,    13,  1264,   665,   134,   835,  1495,   914,   918,   842,
    1345,   151,   152,   153,   154,  1351,   145,   979,  1735,    16,
     841,    13,   932,   280,  1155,   745,   746,   388,  1155,   842,
    1496,   389,   713,   714,   715,   716,   717,   983,   280,   718,
      16,   961,   721,  1264,   722,   723,   724,   725,   726,  1155,
     727,   728,  1498,   841,    13,  1762,  1541,   841,    13,  1222,
      16,  1414,   842,   281,  1021,  1228,   842,  1024,    70,  1554,
    1174,  1031,  1264,  1574,  1218,   996,   170,  1545,  1155,  1239,
    1144,   390,  1579,  1414,  1264,   391,  1264,  1211,   392,  1614,
    1145,   997,   385,    16,  1155,  1264,  1155,    16,  1573,   738,
     739,   740,   741,   742,   743,   744,  1615,  1729,  1409,   841,
      13,  1628,  1636,   393,  1639,  1416,   745,   746,   842,   386,
     387,   146,  1672,  1722,  1734,  1264,  1237,  1264,    80,   281,
     841,    13,   472,  1744,   280,   473,   841,    13,   474,   842,
    1012,   281,   281,   281,   281,   842,   195,  1240,   281,    16,
    -825,  1578,   281,  1391,  1624,  1756,  1013,   290,   281,   281,
     990,   281,   990,   281,   667,   281,   281,   850,   832,  1367,
      16,   833,   291,   281,   474,   172,    16,   292,  1587,   293,
    1648,  1648,   841,    13,   668,  1368,  1656,   851,   711,   712,
      46,   842,    57,  1648,  1168,  1656,    47,  1171,  1512,  1392,
     280,   674,   103,  1177,   105,   114,   388,   134,  1683,  1746,
     389,   115,   280,   280,   280,   280,  1017,    58,   140,   280,
    1747,  1748,    16,   280,   141,   827,   828,   158,  1470,   280,
     280,  1471,   280,   159,   280,  1689,   280,   280,  1142,   103,
     104,   105,  1648,  1648,   280,  1360,   841,  1149,   385,   841,
      13,  1006,   841,  1656,   191,   842,   162,  1150,   842,   694,
     390,   842,   163,   192,   391,   188,  1037,   392,   396,  1080,
     189,   281,   838,   281,   281,   386,   387,   167,  1509,   195,
     281,   190,  1549,   168,  1510,   193,   396,   281,  1105,    16,
     839,   199,   393,   396,   546,   705,   705,   965,   705,   705,
     707,  1663,   708,   709,   571,   103,   713,   714,   715,   716,
     717,  1741,  1758,   718,   719,   720,   721,   587,   722,   723,
     724,   725,   726,   396,   727,   728,   396,   966,   281,   281,
     969,   396,   711,   712,   281,   971,   173,   174,   175,   396,
    1287,  1777,   280,   973,   280,   280,  1691,   201,   281,   396,
     396,   280,   396,  1213,  1221,  1480,  1572,   396,   280,   210,
     211,  1637,   388,   457,  1294,  1295,   389,   458,  1451,  1451,
    1183,   203,  1183,   738,   739,   740,   741,   742,   743,   744,
     207,   459,   460,   136,  1105,   289,   461,   462,   463,   464,
     745,   746,  1604,  1207,   294,  1210,  1681,   354,   356,   280,
     280,   173,   174,   885,   886,   280,   210,   211,   212,   363,
     371,  1369,  1001,  1002,  1003,  1618,   390,   364,   368,   280,
     391,  1377,  1212,   392,    93,    94,    95,   374,   369,   370,
     372,   373,   376,   377,   394,   378,   379,   380,   396,   397,
     381,   452,  1718,   453,   467,   454,   561,   399,   393,   400,
     713,   714,   715,   716,   717,   598,   562,   718,   719,   720,
     721,   588,   722,   723,   724,   725,   726,   591,   727,   728,
     599,   600,   601,   602,   616,   617,   625,  1283,  1736,   658,
    1405,   635,   636,   650,   659,  1291,  1292,   660,   281,   711,
     712,   661,   662,   663,   679,   666,   671,   680,  1300,   771,
    1301,  1302,  1303,  1304,  1305,   681,   682,   763,  1308,   701,
     683,   778,   711,   712,  1437,   736,   737,   738,   739,   740,
     741,   742,   743,   744,   684,   700,  1599,   710,   747,   751,
     750,   766,   772,   773,   745,   746,   812,   775,   385,  1714,
     776,   819,   830,   816,   831,   840,   849,   853,   385,  1482,
     854,   855,   872,   837,   875,   876,   888,   889,   890,   280,
     897,   891,   907,   899,   925,   386,   387,   967,   978,   988,
    1006,  1011,   987,  1029,  1070,   386,   387,  1041,  1039,  1044,
     859,   861,  1046,  1059,   864,  1060,   866,  1061,  1382,  1062,
     786,   787,   788,   789,   790,   791,   792,   793,  1063,  1064,
    1074,  1086,   879,   880,   881,   882,   883,   884,  1132,   715,
     716,  1088,  1133,  1134,  1135,   794,  1136,   721,  1137,   722,
     723,   724,   725,   726,   281,  1138,   281,   795,   796,   797,
     713,   714,   715,   716,  1152,  1147,  1148,  1153,  1154,  1163,
     721,  1165,   722,   723,   724,   725,   726,   929,   727,   728,
     711,   712,   388,  1167,  1175,   573,   389,  1179,  1188,  1189,
    1559,  1190,   388,  1196,  1204,  1205,   389,  1206,  1216,   962,
    1217,  1220,  1226,  1227,  1247,  1230,   740,   741,   742,   743,
     744,  1235,  1238,  1242,  1250,  1243,  1246,  1249,  1251,  1256,
    1257,   745,   746,  1260,  1284,   280,   986,   280,  1261,   740,
     741,   742,   743,   744,  1263,   613,   390,  1717,  1575,  1281,
     391,  1282,  1225,   392,   745,   746,   390,  1293,  1570,  1297,
     391,  1298,  1231,   392,  1299,  1306,  1338,  1586,  1340,  1337,
    1347,  1341,  1348,  1564,  1352,   995,  1354,   281,   393,  1366,
    1363,  1364,  1371,  1375,  1376,  1380,  1386,  1387,   393,  1388,
    1407,  1413,  1411,  1010,  1427,  1430,  1431,  1514,  1432,  1016,
    1516,  1433,  1434,  1439,  1441,   711,   712,  1443,   713,   714,
     715,   716,   717,   677,  1030,   718,   719,   720,   721,  1442,
     722,   723,   724,   725,   726,   281,   727,   728,  1444,  1448,
     729,  1499,  1505,  1500,   730,   731,   732,  1449,  1055,  1056,
     733,  1454,  1503,  1481,   281,  1483,  1507,  1488,   280,  1065,
    1492,  1501,  1502,  1508,  1071,  1512,  1072,  1515,  1073,   385,
    1517,   385,  1518,   859,  1520,  1524,  1105,  1525,  1526,  1527,
     734,  1143,   735,   736,   737,   738,   739,   740,   741,   742,
     743,   744,  1528,  1531,  1544,  1529,   386,   387,   386,   387,
    1543,  1530,   745,   746,  1533,  1547,   280,  1535,  1546,  1555,
    1583,  1552,  1676,  1565,  1566,  1595,  1679,  1576,  1610,  1577,
    1580,  1594,  1596,  1597,  1598,   280,  1606,  1613,  1146,  1608,
    1619,  1611,  1151,   713,   714,   715,   716,   717,  1620,  1621,
     718,   719,   720,   721,  1622,   722,   723,   724,   725,   726,
    1623,   727,   728,  1627,  1635,  1638,  1640,   677,  1178,  1643,
    1658,  1641,  1659,  1660,  1661,  1674,  1662,  1715,  1668,  1678,
    1669,   798,   799,   800,   801,   802,   803,   804,   805,  1264,
    1690,  1692,  1693,   388,  1723,   388,   627,   389,  1209,   389,
     806,  1694,   628,  1697,  1698,  1699,   807,  1701,  1630,   737,
     738,   739,   740,   741,   742,   743,   744,  1702,   808,   809,
     810,  1724,  1229,  1705,  1725,  1642,  1726,   745,   746,  1727,
     385,  1728,  1731,  1752,  1738,  1743,   281,    13,  1760,  1755,
     887,  1772,    20,  1757,  1769,  1759,   629,   390,  1768,   390,
     811,   391,  1782,   391,   392,  1232,   392,   386,   387,   125,
     215,   128,  1783,  1781,   367,  1453,   910,   986,   906,  1202,
      26,  1776,   672,   673,  1277,   385,    16,  1280,   981,   393,
    1556,   393,   993,  1286,   994,  1289,  1685,  1645,  1646,  1686,
    1588,   686,   687,   688,   689,   690,  1687,    92,  1373,  1197,
    1198,     0,   386,   387,   375,     0,   860,   280,   466,     0,
       0,   640,   642,   643,  1712,     0,  1329,     0,  1331,     0,
    1336,     0,  1105,     0,   644,   646,     0,     0,   647,     0,
    1342,     0,     0,     0,     0,     0,     0,     0,   986,     0,
       0,     0,     0,     0,   388,     0,     0,     0,   389,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1739,
       0,     0,  1359,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1365,     0,     0,     0,  1754,  1370,     0,  1372,
       0,     0,     0,   823,     0,     0,     0,     0,  1379,   388,
    1761,  1381,  1763,   389,     0,     0,     0,  1105,   390,     0,
       0,     0,   391,     0,  1233,   392,     0,     0,     0,     0,
     859,     0,     0,     0,  1778,     0,  1105,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   401,   402,     0,
     393,     0,  1412,     0,     0,     0,     0,     0,     0,     0,
    1423,  1424,  1425,   390,   403,     0,     0,   391,     0,  1234,
     392,     0,     0,     0,     0,     0,     0,     0,     0,  1438,
       0,     0,  1440,     0,   711,   712,     0,     0,     0,     0,
       0,  1446,     0,     0,     0,   393,     0,     0,     0,     0,
       0,     0,     0,     0,   919,   920,     0,     0,   921,   922,
     923,   924,     0,   926,     0,     0,   930,   931,   933,   934,
     935,   938,   939,   940,   941,   943,   944,   945,   946,   947,
     948,   949,   950,   951,   952,   953,     0,     0,     0,     0,
       0,  1490,     0,  1491,     0,     0,     0,     0,     0,     0,
    1497,     0,     0,     0,     0,     0,     0,   404,   405,   406,
     407,   408,   409,   410,   411,   412,   413,   414,   415,   416,
     417,   418,   419,   420,   421,     0,     0,   422,   423,   424,
       0,     0,   425,   426,   427,   428,   429,     0,     0,     0,
    1519,   430,   431,   432,   433,   434,   435,   436,     0,     0,
       0,     0,   713,   714,   715,   716,   717,  1537,     0,   718,
     719,   720,   721,  1004,   722,   723,   724,   725,   726,     0,
     727,   728,     0,     0,  1550,  1551,     0,   437,   730,   438,
     439,   440,   441,   442,   443,   444,   445,   446,   447,     0,
       0,   448,   449,     0,     0,  1560,     0,     0,     0,   450,
     451,  1562,  1563,     0,     0,     0,     0,  1567,     0,     0,
       0,     0,     0,     0,     0,     0,   735,   736,   737,   738,
     739,   740,   741,   742,   743,   744,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   745,   746,   986,     0,
       0,     0,     0,     0,     0,     0,     0,   986,     0,     0,
    1130,   -87,  1581,     0,     0,  1582,     0,  1584,     0,     0,
       0,     0,   711,   712,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   859,
    1601,  1602,  1603,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1612,
       0,     0,   385,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1626,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   386,
     387,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1130,     0,  1653,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1667,     0,     0,     0,     0,  1670,
    1671,     0,  1309,  1310,  1311,  1312,  1313,  1314,  1315,  1316,
     713,   714,   715,   716,   717,  1317,  1318,   718,   719,   720,
     721,  1319,   722,   723,   724,   725,   726,  1320,   727,   728,
    1321,  1322,   729,     0,     0,     0,   730,   731,   732,  1323,
    1324,  1325,   733,     0,     0,     0,   388,     0,     0,     0,
     389,     0,  1704,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1326,   734,     0,   735,   736,   737,   738,   739,   740,
     741,   742,   743,   744,     0,     0,     0,     0,  1730,     0,
       0,     0,     0,   216,   745,   746,     0,     0,   385,   217,
     390,  1737,     0,   385,   391,   218,  1236,   392,     0,     0,
    1742,     0,     0,     0,  1339,   219,     0,     0,     0,  1753,
       0,     0,     0,   220,     0,   386,   387,     0,     0,     0,
     386,   387,   393,     0,     0,     0,     0,     0,   221,     0,
       0,     0,     0,  1767,     0,   222,   223,   224,   225,   226,
     227,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   244,   245,   246,
     247,   248,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   388,     0,     0,     0,   389,   388,     0,     0,
       0,   389,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    57,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   278,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    58,     0,     0,   390,     0,     0,     0,
     391,   390,  1244,   392,     0,   391,     0,  1390,   392,     0,
    1459,  1460,  1461,  1462,  1463,  1464,  1465,  1466,  1467,  1468,
    1469,  1472,  1473,  1474,  1475,  1476,  1477,  1478,   393,     0,
       0,     0,   279,   393,     0,     0,     0,   589,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1090,     0,     0,     0,   479,   480,     3,     0,
    -121,  -106,  -106,     0,  -118,     0,   481,   482,   483,   484,
     485,     0,     0,     0,     0,     0,   486,  1091,   487,  1092,
    1093,     0,   488,     0,     0,     0,     0,     0,     0,  1094,
     489,  1095,     0,  -123,     0,  1096,   490,     0,     0,   491,
       0,     8,   492,  1097,     0,  1098,   493,     0,     0,  1099,
    1100,     0,     0,     0,     0,     0,  1101,     0,     0,   495,
     496,     0,   222,   223,   224,     0,   226,   227,   228,   229,
     230,   497,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,     0,   244,   245,   246,     0,  1130,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   498,   499,   500,  1102,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   501,   502,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   503,     0,    57,     0,     0,     0,     0,
       0,     0,     0,   504,   505,   506,   507,   508,     0,   509,
       0,   510,   511,   512,   513,   514,   515,   516,   517,   518,
      58,     0,    13,   519,     0,     0,   216,     0,     0,     0,
       0,     0,   217,     0,     0,     0,     0,     0,   218,   520,
     521,   522,     0,    14,     0,     0,   523,   524,   219,     0,
       0,     0,     0,     0,     0,   525,   220,   526,     0,   527,
     528,    16,  1103,  1104,     0,     0,     0,     0,     0,     0,
       0,   221,     0,     0,     0,     0,     0,     0,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1711,     0,     0,     0,     0,
       0,     0,     0,     0,  1130,     0,     0,     0,     0,     0,
       0,    57,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   278,     0,     0,     0,     0,     0,
       0,     0,     0,  1090,     0,     0,    58,   479,   480,     3,
       0,  -121,  -106,  -106,     0,  -118,     0,   481,   482,   483,
     484,   485,     0,     0,  1711,     0,     0,   486,  1091,   487,
    1092,  1093,     0,   488,     0,     0,     0,     0,     0,     0,
    1094,   489,  1095,     0,  -123,   279,  1096,   490,     0,  1130,
     491,     0,     8,   492,  1097,     0,  1098,   493,     0,     0,
    1099,  1100,  1711,     0,     0,     0,     0,  1101,  1130,     0,
     495,   496,     0,   222,   223,   224,     0,   226,   227,   228,
     229,   230,   497,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,     0,   244,   245,   246,     0,     0,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   498,   499,   500,
    1102,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   501,   502,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   503,     0,    57,     0,     0,     0,
       0,     0,     0,     0,   504,   505,   506,   507,   508,     0,
     509,     0,   510,   511,   512,   513,   514,   515,   516,   517,
     518,    58,     0,    13,   519,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     520,   521,   522,     0,    14,     0,     0,   523,   524,     0,
       0,     0,     0,     0,     0,     0,   525,     0,   526,     0,
     527,   528,    16,  1103,  -330,  1090,     0,     0,     0,   479,
     480,     3,     0,  -121,  -106,  -106,     0,  -118,     0,   481,
     482,   483,   484,   485,     0,     0,     0,     0,     0,   486,
    1091,   487,  1092,  1093,     0,   488,     0,     0,     0,     0,
       0,     0,  1094,   489,  1095,     0,  -123,     0,  1096,   490,
       0,     0,   491,     0,     8,   492,  1097,     0,  1098,   493,
       0,     0,  1099,  1100,     0,     0,     0,     0,     0,  1101,
       0,     0,   495,   496,     0,   222,   223,   224,     0,   226,
     227,   228,   229,   230,   497,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,     0,   244,   245,   246,
       0,     0,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   498,
     499,   500,  1102,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   501,   502,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   503,     0,    57,     0,
       0,     0,     0,     0,     0,     0,   504,   505,   506,   507,
     508,     0,   509,     0,   510,   511,   512,   513,   514,   515,
     516,   517,   518,    58,     0,    13,   519,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   520,   521,   522,     0,    14,     0,     0,   523,
     524,     0,     0,     0,     0,     0,     0,     0,   525,     0,
     526,     0,   527,   528,    16,  1103,  -356,  1090,     0,     0,
       0,   479,   480,     3,     0,  -121,  -106,  -106,     0,  -118,
       0,   481,   482,   483,   484,   485,     0,     0,     0,     0,
       0,   486,  1091,   487,  1092,  1093,     0,   488,     0,     0,
       0,     0,     0,     0,  1094,   489,  1095,     0,  -123,     0,
    1096,   490,     0,     0,   491,     0,     8,   492,  1097,     0,
    1098,   493,     0,     0,  1099,  1100,     0,     0,     0,     0,
       0,  1101,     0,     0,   495,   496,     0,   222,   223,   224,
       0,   226,   227,   228,   229,   230,   497,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,     0,   244,
     245,   246,     0,     0,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   498,   499,   500,  1102,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   501,   502,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   503,     0,
      57,     0,     0,     0,     0,     0,     0,     0,   504,   505,
     506,   507,   508,     0,   509,     0,   510,   511,   512,   513,
     514,   515,   516,   517,   518,    58,     0,    13,   519,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   520,   521,   522,     0,    14,     0,
       0,   523,   524,     0,     0,     0,     0,     0,     0,     0,
     525,     0,   526,     0,   527,   528,    16,  1103,  -327,  1090,
       0,     0,     0,   479,   480,     3,     0,  -121,  -106,  -106,
       0,  -118,     0,   481,   482,   483,   484,   485,     0,     0,
       0,     0,     0,   486,  1091,   487,  1092,  1093,     0,   488,
       0,     0,     0,     0,     0,     0,  1094,   489,  1095,     0,
    -123,     0,  1096,   490,     0,     0,   491,     0,     8,   492,
    1097,     0,  1098,   493,     0,     0,  1099,  1100,     0,     0,
       0,     0,     0,  1101,     0,     0,   495,   496,     0,   222,
     223,   224,     0,   226,   227,   228,   229,   230,   497,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
       0,   244,   245,   246,     0,     0,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   498,   499,   500,  1102,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   501,
     502,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     503,     0,    57,     0,     0,     0,     0,     0,     0,     0,
     504,   505,   506,   507,   508,     0,   509,     0,   510,   511,
     512,   513,   514,   515,   516,   517,   518,    58,     0,    13,
     519,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   520,   521,   522,     0,
      14,     0,     0,   523,   524,     0,     0,     0,     0,     0,
       0,     0,   525,     0,   526,     0,   527,   528,    16,  1103,
     -97,  1090,     0,     0,     0,   479,   480,     3,     0,  -121,
    -106,  -106,     0,  -118,     0,   481,   482,   483,   484,   485,
       0,     0,     0,     0,     0,   486,  1091,   487,  1092,  1093,
       0,   488,     0,     0,     0,     0,     0,     0,  1094,   489,
    1095,     0,  -123,     0,  1096,   490,     0,     0,   491,     0,
       8,   492,  1097,     0,  1098,   493,     0,     0,  1099,  1100,
       0,     0,     0,     0,     0,  1101,     0,     0,   495,   496,
       0,   222,   223,   224,     0,   226,   227,   228,   229,   230,
     497,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,     0,   244,   245,   246,     0,     0,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   498,   499,   500,  1102,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   501,   502,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   503,     0,    57,     0,     0,     0,     0,     0,
       0,     0,   504,   505,   506,   507,   508,     0,   509,     0,
     510,   511,   512,   513,   514,   515,   516,   517,   518,    58,
       0,    13,   519,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   520,   521,
     522,     0,    14,     0,     0,   523,   524,     0,     0,     0,
       0,     0,     0,     0,   525,     0,   526,     0,   527,   528,
      16,  1103,  -102,   479,   480,     0,     0,     0,     0,     0,
       0,     0,     0,   481,   482,   483,   484,   485,     0,     0,
       0,     0,     0,   486,     0,   487,     0,     0,     0,   488,
       0,     0,     0,     0,     0,     0,     0,   489,     0,     0,
       0,     0,     0,   490,     0,     0,   491,     0,     0,   492,
       0,     0,     0,   493,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   494,     0,     0,   495,   496,   901,   222,
     223,   224,     0,   226,   227,   228,   229,   230,   497,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
       0,   244,   245,   246,     0,     0,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   498,   499,   500,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   501,
     502,     0,     0,     0,     0,     0,     0,     0,   576,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     503,     0,    57,     0,     0,     0,     0,     0,     0,     0,
     504,   505,   506,   507,   508,     0,   509,   694,   510,   511,
     512,   513,   514,   515,   516,   517,   518,   695,     0,     0,
     519,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   520,   521,   522,     0,
      14,     0,     0,   523,   524,     0,     0,     0,     0,     0,
     479,   480,   902,     0,   526,   903,   527,   528,   691,   529,
     481,   482,   483,   484,   485,     0,     0,     0,     0,     0,
     486,     0,   487,     0,     0,     0,   488,     0,     0,     0,
       0,     0,     0,     0,   489,     0,     0,     0,     0,     0,
     490,     0,     0,   491,   692,     0,   492,     0,     0,     0,
     493,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     494,     0,     0,   495,   496,     0,   222,   223,   224,     0,
     226,   227,   228,   229,   230,   497,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,     0,   244,   245,
     246,     0,     0,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     498,   499,   500,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   501,   502,     0,     0,
       0,     0,     0,     0,     0,   576,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   503,     0,    57,
       0,     0,     0,     0,     0,     0,     0,   504,   505,   506,
     507,   508,     0,   509,   694,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   695,     0,     0,   519,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   520,   521,   522,     0,    14,     0,     0,
     523,   524,     0,     0,     0,     0,     0,   479,   480,   525,
       0,   526,     0,   527,   528,   691,   529,   481,   482,   483,
     484,   485,     0,     0,     0,     0,     0,   486,     0,   487,
       0,     0,   385,   488,     0,     0,     0,     0,     0,     0,
       0,   489,     0,     0,     0,     0,     0,   490,     0,     0,
     491,   692,     0,   492,     0,     0,     0,   493,     0,   386,
     387,     0,     0,     0,     0,     0,     0,   494,     0,     0,
     495,   496,     0,   222,   223,   224,     0,   226,   227,   228,
     229,   230,   497,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,     0,   244,   245,   246,     0,     0,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   498,   499,   500,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   501,   502,     0,   388,     0,     0,     0,
     389,     0,   576,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   503,     0,    57,     0,     0,     0,
       0,     0,     0,     0,   504,   505,   506,   507,   508,     0,
     509,     0,   510,   511,   512,   513,   514,   515,   516,   517,
     518,    58,     0,     0,   519,     0,     0,     0,     0,     0,
     390,     0,     0,     0,   391,     0,  1395,   392,     0,     0,
     520,   521,   522,     0,    14,     0,     0,   523,   524,     0,
       0,     0,     0,     0,   479,   480,   525,     0,   526,     0,
     527,   528,   393,   529,   481,   482,   483,   484,   485,     0,
       0,     0,     0,     0,   486,     0,   487,     0,     0,   385,
     488,     0,     0,     0,     0,     0,     0,     0,   489,     0,
       0,     0,     0,     0,   490,     0,     0,   491,     0,     0,
     492,     0,     0,     0,   493,     0,   386,   387,     0,     0,
       0,     0,     0,     0,   494,     0,     0,   495,   496,  1025,
     222,   223,   224,     0,   226,   227,   228,   229,   230,   497,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,     0,   244,   245,   246,     0,     0,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   498,   499,   500,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     501,   502,     0,   388,     0,     0,     0,   389,     0,   576,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   503,     0,    57,     0,     0,     0,     0,     0,     0,
       0,   504,   505,   506,   507,   508,     0,   509,   694,   510,
     511,   512,   513,   514,   515,   516,   517,   518,   695,     0,
       0,   519,     0,     0,     0,     0,     0,   390,     0,     0,
       0,   391,     0,  1402,   392,     0,     0,   520,   521,   522,
       0,    14,     0,     0,   523,   524,     0,     0,     0,     0,
       0,   479,   480,   525,     0,   526,     0,   527,   528,   393,
     529,   481,   482,   483,   484,   485,     0,     0,     0,     0,
       0,   486,     0,   487,     0,     0,   385,   488,     0,     0,
       0,     0,     0,     0,     0,   489,     0,     0,     0,     0,
       0,   490,     0,     0,   491,     0,     0,   492,     0,     0,
       0,   493,     0,   386,   387,     0,     0,     0,     0,     0,
       0,   494,     0,     0,   495,   496,     0,   222,   223,   224,
       0,   226,   227,   228,   229,   230,   497,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,     0,   244,
     245,   246,     0,     0,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   498,   499,   500,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   501,   502,     0,
     388,     0,     0,     0,   389,     0,   576,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   503,     0,
      57,     0,     0,     0,     0,     0,     0,     0,   504,   505,
     506,   507,   508,     0,   509,   694,   510,   511,   512,   513,
     514,   515,   516,   517,   518,   695,     0,     0,   519,     0,
       0,     0,     0,     0,   390,     0,     0,     0,   391,     0,
    1571,   392,     0,     0,   520,   521,   522,     0,    14,     0,
       0,   523,   524,     0,     0,     0,     0,     0,   479,   480,
    1332,     0,   526,  1333,   527,   528,   393,   529,   481,   482,
     483,   484,   485,     0,     0,     0,     0,     0,   486,     0,
     487,     0,     0,     0,   488,     0,     0,     0,     0,     0,
       0,     0,   489,     0,     0,     0,     0,     0,   490,     0,
       0,   491,     0,     0,   492,     0,     0,     0,   493,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   494,     0,
       0,   495,   496,     0,   222,   223,   224,     0,   226,   227,
     228,   229,   230,   497,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,     0,   244,   245,   246,     0,
       0,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   498,   499,
     500,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   501,   502,     0,     0,     0,     0,
       0,     0,     0,   576,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   503,     0,    57,     0,     0,
       0,     0,     0,     0,     0,   504,   505,   506,   507,   508,
       0,   509,   694,   510,   511,   512,   513,   514,   515,   516,
     517,   518,   695,     0,     0,   519,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   520,   521,   522,     0,    14,     0,     0,   523,   524,
       0,     0,     0,     0,     0,   479,   480,  1343,     0,   526,
    1344,   527,   528,     0,   529,   481,   482,   483,   484,   485,
       0,     0,     0,     0,     0,   486,     0,   487,     0,     0,
       0,   488,     0,     0,     0,     0,     0,     0,     0,   489,
       0,     0,     0,     0,     0,   490,     0,     0,   491,     0,
       0,   492,     0,     0,     0,   493,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   494,     0,     0,   495,   496,
       0,   222,   223,   224,     0,   226,   227,   228,   229,   230,
     497,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,     0,   244,   245,   246,     0,     0,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   498,   499,   500,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   501,   502,     0,     0,     0,     0,     0,     0,     0,
     576,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   503,     0,    57,     0,     0,     0,     0,     0,
       0,     0,   504,   505,   506,   507,   508,     0,   509,   694,
     510,   511,   512,   513,   514,   515,   516,   517,   518,   695,
       0,     0,   519,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   520,   521,
     522,     0,    14,     0,     0,   523,   524,     0,     0,     0,
       0,     0,   479,   480,   525,     0,   526,     0,   527,   528,
       0,   529,   481,   482,   483,   484,   485,     0,     0,     0,
       0,     0,   486,     0,   487,     0,     0,     0,   488,     0,
       0,     0,     0,     0,     0,     0,   489,     0,     0,     0,
       0,     0,   490,     0,     0,   491,     0,     0,   492,     0,
       0,     0,   493,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   494,     0,     0,   495,   496,     0,   222,   223,
     224,     0,   226,   227,   228,   229,   230,   497,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,     0,
     244,   245,   246,     0,     0,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   498,   499,   500,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   501,   502,
       0,     0,     0,     0,     0,     0,     0,   576,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   503,
       0,    57,     0,     0,     0,     0,     0,     0,     0,   504,
     505,   506,   507,   508,     0,   509,     0,   510,   511,   512,
     513,   514,   515,   516,   517,   518,    58,     0,     0,   519,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   520,   521,   522,     0,    14,
       0,     0,   523,   524,     0,     0,     0,     0,     0,   479,
     480,   525,     0,   526,   963,   527,   528,     0,   529,   481,
     482,   483,   484,   485,     0,     0,     0,     0,     0,   486,
       0,   487,     0,     0,     0,   488,     0,     0,     0,     0,
       0,     0,     0,   489,     0,     0,     0,     0,     0,   490,
       0,     0,   491,     0,     0,   492,     0,     0,     0,   493,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   494,
       0,     0,   495,   496,     0,   222,   223,   224,     0,   226,
     227,   228,   229,   230,   497,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,     0,   244,   245,   246,
       0,     0,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   498,
     499,   500,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   501,   502,     0,     0,     0,
       0,     0,     0,     0,   985,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   503,     0,    57,     0,
       0,     0,     0,     0,     0,     0,   504,   505,   506,   507,
     508,     0,   509,   694,   510,   511,   512,   513,   514,   515,
     516,   517,   518,   695,     0,     0,   519,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   520,   521,   522,     0,    14,     0,     0,   523,
     524,     0,     0,     0,     0,     0,   479,   480,  1266,     0,
     526,     0,   527,   528,     0,   529,   481,   482,   483,   484,
     485,     0,     0,     0,     0,     0,   486,     0,   487,     0,
       0,     0,   488,     0,     0,     0,     0,     0,     0,     0,
     489,     0,     0,     0,     0,     0,   490,     0,     0,   491,
       0,     0,   492,     0,     0,     0,   493,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   494,     0,     0,   495,
     496,     0,   222,   223,   224,     0,   226,   227,   228,   229,
     230,   497,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,     0,   244,   245,   246,     0,     0,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   498,   499,   500,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   501,   502,     0,     0,     0,     0,     0,     0,
       0,   576,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   503,     0,    57,     0,     0,     0,     0,
       0,     0,     0,   504,   505,   506,   507,   508,     0,   509,
       0,   510,   511,   512,   513,   514,   515,   516,   517,   518,
      58,     0,     0,   519,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   520,
     521,   522,     0,    14,     0,     0,   523,   524,     0,     0,
       0,     0,     0,   479,   480,   525,     0,   526,  1350,   527,
     528,     0,   529,   481,   482,   483,   484,   485,     0,     0,
       0,     0,     0,   486,     0,   487,     0,     0,     0,   488,
       0,     0,     0,     0,     0,     0,     0,   489,     0,     0,
       0,     0,     0,   490,     0,     0,   491,     0,     0,   492,
       0,     0,     0,   493,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   494,     0,     0,   495,   496,     0,   222,
     223,   224,     0,   226,   227,   228,   229,   230,   497,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
       0,   244,   245,   246,     0,     0,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   498,   499,   500,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   501,
     502,     0,     0,     0,     0,     0,     0,     0,   576,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     503,     0,    57,     0,     0,     0,     0,     0,     0,     0,
     504,   505,   506,   507,   508,     0,   509,     0,   510,   511,
     512,   513,   514,   515,   516,   517,   518,    58,     0,     0,
     519,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   520,   521,   522,     0,
      14,     0,     0,   523,   524,     0,     0,     0,     0,     0,
     479,   480,   525,     0,   526,  1408,   527,   528,     0,   529,
     481,   482,   483,   484,   485,     0,     0,     0,     0,     0,
     486,     0,   487,     0,     0,     0,   488,     0,     0,     0,
       0,     0,     0,     0,   489,     0,     0,     0,     0,     0,
     490,     0,     0,   491,     0,     0,   492,     0,     0,     0,
     493,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     494,     0,     0,   495,   496,     0,   222,   223,   224,     0,
     226,   227,   228,   229,   230,   497,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,     0,   244,   245,
     246,     0,     0,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     498,   499,   500,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   501,   502,     0,     0,
       0,     0,     0,     0,     0,   985,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   503,     0,    57,
       0,     0,     0,     0,     0,     0,     0,   504,   505,   506,
     507,   508,     0,   509,   694,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   695,     0,     0,   519,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   520,   521,   522,     0,    14,     0,     0,
     523,   524,     0,     0,     0,     0,     0,   479,   480,   525,
       0,   526,     0,   527,   528,     0,   529,   481,   482,   483,
     484,   485,     0,     0,     0,     0,     0,   486,     0,   487,
       0,     0,     0,   488,     0,     0,     0,     0,     0,     0,
       0,   489,     0,     0,     0,     0,     0,   490,     0,     0,
     491,     0,     0,   492,     0,     0,     0,   493,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   494,     0,     0,
     495,   496,     0,   222,   223,   224,     0,   226,   227,   228,
     229,   230,   497,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,     0,   244,   245,   246,     0,     0,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   498,   499,   500,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   501,   502,     0,     0,     0,     0,     0,
       0,     0,   576,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   503,     0,    57,     0,     0,     0,
       0,     0,     0,     0,   504,   505,   506,   507,   508,     0,
     509,     0,   510,   511,   512,   513,   514,   515,   516,   517,
     518,    58,     0,     0,   519,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     520,   521,   522,     0,    14,     0,     0,   523,   524,     0,
       0,     0,     0,     0,   479,   480,   525,     0,   526,     0,
     527,   528,     0,   529,   481,   482,   483,   484,   485,     0,
       0,     0,     0,     0,   486,     0,   487,     0,     0,     0,
     488,     0,     0,     0,     0,     0,     0,     0,   489,     0,
       0,     0,     0,     0,   490,     0,     0,   491,     0,     0,
     492,     0,     0,     0,   493,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   494,     0,     0,   495,   496,     0,
     222,   223,   224,     0,   226,   227,   228,   229,   230,   497,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,     0,   244,   245,   246,     0,     0,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   498,   499,   500,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     501,   502,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   503,     0,    57,     0,     0,     0,     0,     0,     0,
       0,   504,   505,   506,   507,   508,     0,   509,     0,   510,
     511,   512,   513,   514,   515,   516,   517,   518,    58,     0,
       0,   519,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   520,   521,   522,
       0,    14,     0,     0,   523,   524,     0,     0,     0,     0,
       0,   479,   480,   525,   586,   526,     0,   527,   528,     0,
     529,   481,   482,   483,   484,   485,     0,     0,     0,     0,
       0,   486,     0,   487,     0,     0,     0,   488,     0,     0,
       0,     0,     0,     0,     0,   489,     0,     0,     0,     0,
       0,   490,     0,     0,   491,     0,     0,   492,     0,     0,
       0,   493,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   494,     0,     0,   495,   496,     0,   222,   223,   224,
       0,   226,   227,   228,   229,   230,   497,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,     0,   244,
     245,   246,     0,     0,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   498,   499,   500,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   501,   502,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   503,     0,
      57,     0,     0,     0,     0,     0,     0,     0,   504,   505,
     506,   507,   508,     0,   509,     0,   510,   511,   512,   513,
     514,   515,   516,   517,   518,    58,     0,     0,   519,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   520,   521,   522,     0,    14,     0,
       0,   523,   524,     0,     0,     0,     0,     0,   479,   480,
     525,   777,   526,     0,   527,   528,     0,   529,   481,   482,
     483,   484,   485,     0,     0,     0,     0,     0,   486,     0,
     487,     0,     0,     0,   488,     0,     0,     0,     0,     0,
       0,     0,   489,     0,     0,     0,     0,     0,   490,     0,
       0,   491,     0,     0,   492,     0,     0,     0,   493,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   494,     0,
       0,   495,   496,     0,   222,   223,   224,     0,   226,   227,
     228,   229,   230,   497,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,     0,   244,   245,   246,     0,
       0,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   273,   274,   275,   498,   499,
     500,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   501,   502,     0,     0,     0,     0,
       0,     0,     0,   985,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   503,     0,    57,     0,     0,
       0,     0,     0,     0,     0,   504,   505,   506,   507,   508,
       0,   509,     0,   510,   511,   512,   513,   514,   515,   516,
     517,   518,    58,     0,     0,   519,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   520,   521,   522,     0,    14,     0,     0,   523,   524,
       0,     0,     0,     0,     0,   479,   480,   525,     0,   526,
       0,   527,   528,  1077,   529,   481,   482,   483,   484,   485,
       0,     0,     0,     0,     0,   486,     0,   487,     0,     0,
       0,   488,     0,     0,     0,     0,     0,     0,     0,   489,
       0,     0,     0,     0,     0,   490,     0,     0,   491,     0,
       0,   492,     0,     0,     0,   493,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   494,     0,     0,   495,   496,
       0,   222,   223,   224,     0,   226,   227,   228,   229,   230,
     497,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,     0,   244,   245,   246,     0,     0,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   498,   499,   500,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   501,   502,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   503,     0,    57,     0,     0,     0,     0,     0,
       0,     0,   504,   505,   506,   507,   508,     0,   509,     0,
     510,   511,   512,   513,   514,   515,   516,   517,   518,    58,
       0,     0,   519,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   520,   521,
     522,     0,    14,     0,     0,   523,   524,     0,     0,     0,
       0,     0,   479,   480,   525,     0,   526,     0,   527,   528,
       0,   529,   481,   482,   483,   484,   485,     0,     0,     0,
       0,     0,   486,     0,   487,     0,     0,     0,   488,     0,
       0,     0,     0,     0,     0,     0,   489,     0,     0,     0,
       0,     0,   490,     0,     0,   491,     0,     0,   492,     0,
       0,     0,   493,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   494,     0,     0,   495,   496,     0,   222,   223,
     224,     0,   226,   227,   228,   229,   230,   497,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,     0,
     244,   245,   246,     0,     0,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   498,   499,   500,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   501,   502,
       0,     0,     0,     0,     0,     0,     0,  1276,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   503,
       0,    57,     0,     0,     0,     0,     0,     0,     0,   504,
     505,   506,   507,   508,     0,   509,     0,   510,   511,   512,
     513,   514,   515,   516,   517,   518,    58,     0,     0,   519,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   520,   521,   522,     0,    14,
       0,     0,   523,   524,     0,     0,     0,     0,     0,   479,
     480,   525,     0,   526,     0,   527,   528,     0,   529,   481,
     482,   483,   484,   485,     0,     0,     0,     0,     0,   486,
       0,   487,     0,     0,     0,   488,     0,     0,     0,     0,
       0,     0,     0,   489,     0,     0,     0,     0,     0,   490,
       0,     0,   491,     0,     0,   492,     0,     0,     0,   493,
       0,     0,     0,     0,     0,  1279,     0,     0,     0,   494,
       0,     0,   495,   496,     0,   222,   223,   224,     0,   226,
     227,   228,   229,   230,   497,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,     0,   244,   245,   246,
       0,     0,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   498,
     499,   500,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   501,   502,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   503,     0,    57,     0,
       0,     0,     0,     0,     0,     0,   504,   505,   506,   507,
     508,     0,   509,     0,   510,   511,   512,   513,   514,   515,
     516,   517,   518,    58,     0,     0,   519,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   520,   521,   522,     0,    14,     0,     0,   523,
     524,     0,     0,     0,     0,     0,   479,   480,   525,     0,
     526,     0,   527,   528,     0,   529,   481,   482,   483,   484,
     485,     0,     0,     0,     0,     0,   486,     0,   487,     0,
       0,     0,   488,     0,     0,     0,     0,     0,     0,     0,
     489,     0,     0,     0,     0,     0,   490,     0,     0,   491,
       0,     0,   492,     0,     0,     0,   493,     0,     0,  1285,
       0,     0,     0,     0,     0,     0,   494,     0,     0,   495,
     496,     0,   222,   223,   224,     0,   226,   227,   228,   229,
     230,   497,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,     0,   244,   245,   246,     0,     0,   249,
     250,   251,   252,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   498,   499,   500,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   501,   502,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   503,     0,    57,     0,     0,     0,     0,
       0,     0,     0,   504,   505,   506,   507,   508,     0,   509,
       0,   510,   511,   512,   513,   514,   515,   516,   517,   518,
      58,     0,     0,   519,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   520,
     521,   522,     0,    14,     0,     0,   523,   524,     0,     0,
       0,     0,     0,   479,   480,   525,     0,   526,     0,   527,
     528,     0,   529,   481,   482,   483,   484,   485,     0,     0,
       0,     0,     0,   486,     0,   487,     0,     0,     0,   488,
       0,     0,     0,     0,     0,     0,     0,   489,     0,     0,
       0,     0,     0,   490,     0,     0,   491,     0,     0,   492,
       0,     0,     0,   493,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   494,     0,     0,   495,   496,     0,   222,
     223,   224,     0,   226,   227,   228,   229,   230,   497,   232,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
       0,   244,   245,   246,     0,     0,   249,   250,   251,   252,
     253,   254,   255,   256,   257,   258,   259,   260,   261,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   498,   499,   500,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   501,
     502,     0,     0,     0,     0,     0,     0,     0,  1288,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     503,     0,    57,     0,     0,     0,     0,     0,     0,     0,
     504,   505,   506,   507,   508,     0,   509,     0,   510,   511,
     512,   513,   514,   515,   516,   517,   518,    58,     0,     0,
     519,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   520,   521,   522,     0,
      14,     0,     0,   523,   524,     0,     0,     0,     0,     0,
     479,   480,   525,     0,   526,     0,   527,   528,     0,   529,
     481,   482,   483,   484,   485,     0,     0,     0,     0,     0,
     486,     0,   487,     0,     0,     0,   488,     0,     0,     0,
       0,     0,     0,     0,   489,     0,     0,     0,     0,     0,
     490,     0,     0,   491,     0,     0,   492,     0,     0,     0,
     493,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     494,     0,     0,   495,   496,     0,   222,   223,   224,     0,
     226,   227,   228,   229,   230,   497,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,     0,   244,   245,
     246,     0,     0,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
     498,   499,   500,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   501,   502,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   503,     0,    57,
       0,     0,     0,     0,     0,     0,     0,   504,   505,   506,
     507,   508,     0,   509,     0,   510,   511,   512,   513,   514,
     515,   516,   517,   518,    58,     0,     0,   519,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   520,   521,   522,     0,    14,     0,     0,
     523,   524,     0,     0,     0,     0,     0,   479,   480,   525,
       0,   526,  1536,   527,   528,     0,   529,   481,   482,   483,
     484,   485,     0,     0,     0,     0,     0,   486,     0,   487,
       0,     0,     0,   488,     0,     0,     0,     0,     0,     0,
       0,   489,     0,     0,     0,     0,     0,   490,     0,     0,
     491,     0,     0,   492,     0,     0,     0,   493,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   494,     0,     0,
     495,   496,     0,   222,   223,   224,     0,   226,   227,   228,
     229,   230,   497,   232,   233,   234,   235,   236,   237,   238,
     239,   240,   241,   242,     0,   244,   245,   246,     0,     0,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     269,   270,   271,   272,   273,   274,   275,   498,   499,   500,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   501,   502,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   503,     0,    57,     0,     0,     0,
       0,     0,     0,     0,   504,   505,   506,   507,   508,     0,
     509,     0,   510,   511,   512,   513,   514,   515,   516,   517,
     518,    58,     0,     0,   519,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     520,   521,   522,     0,    14,     0,     0,   523,   524,     0,
       0,     0,     0,     0,   479,   480,   525,     0,   526,     0,
     527,   528,     0,   529,   481,   482,   483,   484,   485,     0,
       0,     0,     0,     0,   486,  1091,   487,  1092,     0,     0,
     488,     0,     0,     0,     0,     0,     0,     0,   489,     0,
       0,     0,     0,     0,   490,     0,     0,   491,     0,     0,
     492,  1097,     0,     0,   493,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   494,     0,     0,   495,   496,     0,
     222,   223,   224,     0,   226,   227,   228,   229,   230,   497,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,     0,   244,   245,   246,     0,     0,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   498,   499,   500,  1102,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     501,   502,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   503,     0,    57,     0,     0,     0,     0,     0,     0,
       0,   504,   505,   506,   507,   508,     0,   509,     0,   510,
     511,   512,   513,   514,   515,   516,   517,   518,    58,     0,
       0,   519,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   520,   521,   522,
       0,    14,     0,     0,   523,   524,     0,     0,     0,   479,
     480,     0,     0,   525,     0,   526,     0,   527,   528,   481,
     482,   483,   484,   485,     0,     0,     0,     0,     0,   486,
       0,   487,     0,     0,     0,   488,     0,     0,     0,     0,
       0,     0,     0,   489,     0,     0,     0,     0,     0,   490,
       0,     0,   491,     0,     0,   492,     0,     0,     0,   493,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   494,
       0,     0,   495,   496,     0,   222,   223,   224,     0,   226,
     227,   228,   229,   230,   497,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,     0,   244,   245,   246,
       0,     0,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   498,
     499,   500,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   501,   502,     0,     0,     0,
       0,     0,     0,     0,   822,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   503,     0,    57,     0,
       0,     0,     0,     0,     0,     0,   504,   505,   506,   507,
     508,     0,   509,     0,   510,   511,   512,   513,   514,   515,
     516,   517,   518,    58,     0,     0,   519,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   520,   521,   522,     0,    14,     0,     0,   523,
     524,     0,     0,     0,   479,   480,     0,     0,   525,     0,
     526,     0,   527,   528,   481,   482,   483,   484,   485,     0,
       0,   942,     0,     0,   486,     0,   487,     0,     0,     0,
     488,     0,     0,     0,     0,     0,     0,     0,   489,     0,
       0,     0,     0,     0,   490,     0,     0,   491,     0,     0,
     492,     0,     0,     0,   493,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   494,     0,     0,   495,   496,     0,
     222,   223,   224,     0,   226,   227,   228,   229,   230,   497,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,     0,   244,   245,   246,     0,     0,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   498,   499,   500,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     501,   502,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   503,     0,    57,     0,     0,     0,     0,     0,     0,
       0,   504,   505,   506,   507,   508,     0,   509,     0,   510,
     511,   512,   513,   514,   515,   516,   517,   518,    58,     0,
       0,   519,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   520,   521,   522,
       0,    14,     0,     0,   523,   524,     0,     0,     0,   479,
     480,     0,     0,   525,     0,   526,     0,   527,   528,   481,
     482,   483,   484,   485,     0,     0,     0,     0,     0,   486,
       0,   487,     0,     0,     0,   488,     0,     0,     0,     0,
       0,     0,     0,   489,     0,     0,     0,     0,     0,   490,
       0,     0,   491,     0,     0,   492,     0,     0,     0,   493,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   494,
       0,     0,   495,   496,     0,   222,   223,   224,     0,   226,
     227,   228,   229,   230,   497,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,     0,   244,   245,   246,
       0,     0,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   498,
     499,   500,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   501,   502,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   503,     0,    57,     0,
       0,     0,     0,     0,     0,     0,   504,   505,   506,   507,
     508,     0,   509,     0,   510,   511,   512,   513,   514,   515,
     516,   517,   518,    58,     0,   216,   519,     0,     0,     0,
       0,   217,     0,     0,     0,     0,     0,   218,     0,     0,
       0,     0,   520,   521,   522,     0,    14,   219,     0,   523,
     524,     0,     0,     0,     0,   220,     0,     0,   525,     0,
     526,     0,   527,   528,     0,     0,     0,     0,     0,     0,
     221,     0,     0,     0,     0,     0,     0,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,     0,     0,     0,     0,     0,     0,   711,   712,     0,
       0,     0,     0,   278,     0,     0,   216,     0,     0,     0,
       0,     0,   217,     0,     0,   759,     0,    13,   218,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   219,     0,
       0,     0,     0,     0,     0,     0,   220,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   221,     0,     0,   279,     0,    16,     0,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   236,   237,   238,   239,   240,   241,   242,   243,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   259,   260,   261,   262,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   272,   273,
     274,   275,   276,   277,     0,   713,   714,   715,   716,   717,
     711,   712,   718,   719,   720,   721,     0,   722,   723,   724,
     725,   726,     0,   727,   728,     0,     0,   729,     0,     0,
       0,   730,   731,   732,     0,     0,     0,   733,     0,     0,
       0,    57,     0,   711,   712,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   278,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   759,   734,     0,   735,
     736,   737,   738,   739,   740,   741,   742,   743,   744,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   745,
     746,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   279,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   711,   712,     0,     0,     0,     0,   713,   714,
     715,   716,   717,     0,     0,   718,   719,   720,   721,     0,
     722,   723,   724,   725,   726,     0,   727,   728,     0,     0,
    -904,   711,   712,     0,   730,   731,   732,     0,     0,     0,
    -904,   713,   714,   715,   716,   717,     0,     0,   718,   719,
     720,   721,     0,   722,   723,   724,   725,   726,     0,   727,
     728,     0,     0,     0,     0,     0,     0,   730,   731,   732,
     734,     0,   735,   736,   737,   738,   739,   740,   741,   742,
     743,   744,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   745,   746,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   734,     0,   735,   736,   737,   738,   739,
     740,   741,   742,   743,   744,     0,     0,     0,     0,     0,
     713,   714,   715,   716,   717,   745,   746,   718,   719,   720,
     721,     0,   722,   723,   724,   725,   726,     0,   727,   728,
       0,     0,     0,     0,     0,     0,   730,     0,   732,   713,
     714,   715,   716,   717,     0,     0,   718,   719,   720,   721,
       0,   722,   723,   724,   725,   726,     0,   727,   728,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   911,   735,   736,   737,   738,   739,   740,
     741,   742,   743,   744,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   745,   746,     0,     0,     0,     0,
       0,     0,     0,   735,   736,   737,   738,   739,   740,   741,
     742,   743,   744,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   745,   746,   222,   223,   224,     0,   226,
     227,   228,   229,   230,   497,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,     0,   244,   245,   246,
       0,     0,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   300,
       0,   301,     0,   302,   303,   304,   305,   306,   915,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
       0,   318,   319,   320,     0,     0,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   912,     0,     0,     0,     0,     0,     0,
     222,   223,   224,   913,   226,   227,   228,   229,   230,   497,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   241,
     242,     0,   244,   245,   246,     0,     0,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   258,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   300,     0,   301,   594,   302,   303,
     304,   305,   306,  1139,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,     0,   318,   319,   320,     0,
       0,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,   916,     0,
       0,     0,     0,     0,     0,   222,   223,   224,   917,   226,
     227,   228,   229,   230,   497,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,     0,   244,   245,   246,
       0,     0,   249,   250,   251,   252,   253,   254,   255,   256,
     257,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,     0,
       0,     0,   596,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   299,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1140,   300,     0,   301,     0,   302,   303,
     304,   305,   306,  1141,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,     0,   318,   319,   320,     0,
       0,   321,   322,   323,   324,   325,   326,   327,   328,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   343,   344,   345,   346,   347,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   348,   349,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   222,   223,   224,     0,
     226,   227,   228,   229,   230,   497,   232,   233,   234,   235,
     236,   237,   238,   239,   240,   241,   242,     0,   244,   245,
     246,     0,   350,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   272,   273,   274,   275,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   954,   955,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   956,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   957,     0,     0,     0,     0,     0,
       0,     0,     0,   300,     0,   301,     0,   302,   303,   304,
     305,   306,     0,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,     0,   318,   319,   320,   958,   959,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
     341,   342,   343,   344,   345,   346,   347,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   784
};

static const yytype_int16 yycheck[] =
{
       1,    14,    15,   144,   145,   102,   384,   626,   526,   171,
     622,   824,   483,   696,   697,   483,  1093,   634,  1000,    20,
      21,    22,   754,   564,   756,   566,   758,   568,  1070,   593,
     191,   192,   592,  1437,   700,  1227,    80,  1307,     5,     0,
       8,     5,     6,   396,   989,    19,     7,    33,    49,    50,
      63,    64,    65,   983,    33,   573,   401,   402,    20,   870,
     910,    25,    46,  1008,    20,   164,    20,    31,  1406,    30,
    1674,    32,    40,    34,  1674,    21,    22,   149,    20,    40,
      19,    20,    22,  1674,  1674,   768,   150,  1674,   163,    50,
     103,   104,   105,   106,  1076,    56,   163,  1607,   149,    15,
      16,  1684,   161,   202,    68,    69,   179,   191,   192,   176,
     902,   873,   173,    33,   201,   149,   189,    57,   189,    80,
     473,  1621,   190,    15,    16,   181,   152,   153,   189,  1733,
     202,   199,  1593,  1733,   149,   207,   200,   655,  1721,   203,
      60,    61,  1733,  1733,  1605,   129,  1733,   665,   765,   224,
     668,   202,   769,   226,   226,  1665,   207,   228,   125,   126,
     227,   125,   126,   207,   125,   126,  1570,  1771,   202,  1400,
     150,  1771,   231,   207,   857,   226,   156,   860,   191,   192,
    1771,  1771,   700,   849,  1771,   868,   164,   202,   871,   191,
     199,     7,   226,  1654,  1655,   141,   142,   223,   224,   361,
     164,   203,  1540,   149,  1054,   206,   152,   153,   154,   155,
    1287,   189,   353,    62,   191,   834,   225,   358,  1260,   205,
     200,   362,  1033,   191,   162,   189,   205,   147,   230,   747,
     191,   151,   206,    34,    50,   901,  1181,   199,   224,   206,
     200,   858,   206,   199,  1174,   199,   162,   233,    21,    22,
     189,   212,  1197,   230,    44,   600,   224,   199,   729,   226,
     224,   729,    63,   224,   232,   181,   279,   231,  1768,   230,
     186,   211,  1034,   189,  1256,  1419,   192,   223,   224,   191,
     173,   201,  1782,   223,   199,   205,  1517,  1518,   208,   181,
     228,   229,  1084,   231,   186,    85,   189,   189,   179,  1569,
     192,   202,  1533,   656,  1535,   173,   189,     8,   189,   171,
     226,  1455,   396,   233,   226,   476,   477,   478,   671,   363,
     173,   189,   165,   166,   167,   191,  1058,   189,  1405,   130,
     471,   849,   149,   226,  1526,    36,   189,   878,   231,   129,
     130,   150,   132,    33,  1136,   149,   227,   156,   152,   153,
     212,  1755,     5,     6,   155,   164,  1148,  1089,   226,  1025,
     226,   223,  1439,   164,   981,  1596,  1597,   908,   141,   142,
      60,    61,   150,   226,   199,  1606,   149,   199,   151,   152,
     153,   154,   155,   396,   227,   202,   189,  1369,   189,   473,
     207,   200,   476,   477,   478,  1014,  1079,   199,   559,   560,
     164,   189,   563,   191,   565,   230,   567,   199,   199,   226,
     173,   226,  1029,    33,   575,   216,   980,   977,   199,   223,
     224,   199,   200,   225,   202,   226,   189,   205,   191,   993,
     202,   991,   206,   205,   225,   227,  1053,   210,   211,   212,
      60,    61,   230,    21,    22,   130,   227,   150,   609,   610,
     223,   224,   226,   156,   181,   171,   150,   147,   199,   199,
     473,   151,   156,   476,   477,   478,   207,   230,   211,   232,
     483,   484,   150,   189,  1266,   559,   560,  1290,   156,   563,
     833,   565,   150,   567,   206,   569,   189,   227,   156,   230,
     503,   575,   150,   846,   847,   211,   212,   200,   156,   206,
     191,   199,   205,   856,   226,   211,   200,   223,   592,   862,
     863,   201,   865,   189,   867,   205,   869,   207,   208,   226,
     199,   193,   200,  1565,   877,   609,   610,   147,   191,   227,
     150,   151,   200,    33,    21,    22,   156,   199,   199,   230,
    1332,   232,   200,   233,   190,   191,   559,   560,   227,   179,
     563,  1343,   565,   199,   567,   163,   569,   203,   699,   189,
      60,    61,   575,   141,   142,   227,   227,   130,   176,   164,
    1552,   149,   656,   151,   152,   153,   154,   155,   173,   592,
     200,   201,   199,   178,   230,   205,   199,   671,   208,   199,
    1131,    63,    64,    65,   189,  1327,   609,   610,   199,   190,
     191,   189,  1679,   206,   617,   179,   767,  1224,   199,   189,
     227,   206,   211,   233,   227,   189,   207,   227,  1136,   130,
     190,   191,   199,   226,   223,   626,   227,   711,   712,   199,
    1148,   103,   104,   105,   106,  1153,   189,   207,  1715,   230,
     190,   191,   726,   656,   199,   223,   224,   147,   199,   199,
     227,   151,   139,   140,   141,   142,   143,   207,   671,   146,
     230,   745,   149,   199,   151,   152,   153,   154,   155,   199,
     157,   158,   227,   190,   191,  1752,   227,   190,   191,  1032,
     230,   199,   199,   767,   845,  1038,   199,   848,   701,   225,
     207,   852,   199,  1485,   207,   173,   231,   227,   199,  1052,
     179,   201,  1494,   199,   199,   205,   199,   207,   208,   227,
     189,   189,    33,   230,   199,   199,   199,   230,   225,   206,
     207,   208,   209,   210,   211,   212,   227,  1704,  1246,   190,
     191,   227,   227,   233,   227,  1253,   223,   224,   199,    60,
      61,   189,   227,   227,   227,   199,   207,   199,   199,   833,
     190,   191,   199,  1730,   767,   202,   190,   191,   205,   199,
     173,   845,   846,   847,   848,   199,   202,   207,   852,   230,
     206,   225,   856,   207,   225,   227,   189,    79,   862,   863,
     781,   865,   783,   867,   206,   869,   870,   206,   199,   173,
     230,   202,    94,   877,   205,   189,   230,    99,    47,   101,
    1592,  1593,   190,   191,   226,   189,  1598,   226,    21,    22,
      57,   199,   164,  1605,   975,  1607,    63,   978,    67,   207,
     833,   173,   165,   984,   167,    57,   147,   223,  1641,    12,
     151,    63,   845,   846,   847,   848,   837,   189,    57,   852,
      23,    24,   230,   856,    63,   230,   231,    57,  1319,   862,
     863,  1319,   865,    63,   867,  1647,   869,   870,   942,   165,
     166,   167,  1654,  1655,   877,   189,   190,   179,    33,   190,
     191,   189,   190,  1665,   200,   199,    57,   189,   199,   179,
     201,   199,    63,   200,   205,   189,   207,   208,   203,   189,
     189,   975,   207,   977,   978,    60,    61,    57,    57,   202,
     984,   189,  1420,    63,    63,   216,   203,   991,   909,   230,
     207,   193,   233,   203,   371,   541,   542,   207,   544,   545,
     542,  1604,   544,   545,   381,   165,   139,   140,   141,   142,
     143,  1723,  1745,   146,   147,   148,   149,   394,   151,   152,
     153,   154,   155,   203,   157,   158,   203,   207,  1032,  1033,
     207,   203,    21,    22,  1038,   207,   193,   194,   195,   203,
    1101,  1774,   975,   207,   977,   978,  1649,   191,  1052,   203,
     203,   984,   203,   207,   207,  1328,   207,   203,   991,   193,
     194,   207,   147,    75,    10,    11,   151,    79,  1297,  1298,
     991,   189,   993,   206,   207,   208,   209,   210,   211,   212,
     163,    93,    94,    57,  1005,    66,    98,    99,   100,   101,
     223,   224,  1530,  1014,   190,  1016,  1628,   202,   129,  1032,
    1033,   193,   194,   195,   196,  1038,   193,   194,   195,   163,
     226,  1192,   816,   817,   818,  1553,   201,   189,   206,  1052,
     205,  1203,   207,   208,    54,    55,    56,   226,   206,   206,
     206,   206,   206,   206,   224,   206,   206,   206,   203,   190,
     226,    35,  1681,    35,   189,   226,   189,   231,   233,   231,
     139,   140,   141,   142,   143,   189,   206,   146,   147,   148,
     149,   224,   151,   152,   153,   154,   155,   231,   157,   158,
     225,    22,   189,   225,   231,   202,   189,  1098,  1717,   226,
    1241,   206,   206,   206,   206,  1106,  1107,   206,  1192,    21,
      22,   226,   206,   226,   226,   206,   206,   226,  1119,   576,
    1121,  1122,  1123,  1124,  1125,   226,   226,   189,  1129,   224,
     226,   588,    21,    22,  1275,   204,   205,   206,   207,   208,
     209,   210,   211,   212,   226,   226,  1524,   227,   226,   207,
     227,   227,   227,   199,   223,   224,   226,   225,    33,  1677,
     225,   227,   226,   230,    43,   207,   226,   206,    33,  1330,
     206,   206,   206,   630,   226,   226,   226,    13,   225,  1192,
     199,   226,     4,   227,   189,    60,    61,   189,   202,   189,
     189,   189,   225,   189,   226,    60,    61,   227,   199,   227,
     657,   658,   227,   227,   661,   227,   663,   227,  1209,   227,
     131,   132,   133,   134,   135,   136,   137,   138,   227,   227,
     227,   227,   679,   680,   681,   682,   683,   684,   206,   141,
     142,   226,   226,   206,   226,   156,   226,   149,   226,   151,
     152,   153,   154,   155,  1328,   225,  1330,   168,   169,   170,
     139,   140,   141,   142,     1,   226,   226,   226,   225,   207,
     149,   207,   151,   152,   153,   154,   155,   724,   157,   158,
      21,    22,   147,   207,   227,   226,   151,   200,   227,   226,
    1441,    43,   147,   200,   227,   226,   151,    43,   227,   746,
     227,   227,   227,   226,   202,   227,   208,   209,   210,   211,
     212,   227,   227,   227,    43,   227,   226,   226,   189,   227,
     226,   223,   224,   226,   181,  1328,   773,  1330,   232,   208,
     209,   210,   211,   212,   227,   231,   201,  1680,  1489,   189,
     205,   189,   207,   208,   223,   224,   201,    10,  1479,    13,
     205,     9,   207,   208,    42,    66,   226,  1508,   226,   206,
     226,   225,   225,  1450,   189,   812,   189,  1441,   233,   189,
     232,   232,   232,   189,     8,   189,   227,   226,   233,   189,
     207,   189,   197,   830,   227,   189,   189,  1378,   226,   836,
    1381,   189,   189,    14,   200,    21,    22,   202,   139,   140,
     141,   142,   143,  1406,   851,   146,   147,   148,   149,   200,
     151,   152,   153,   154,   155,  1489,   157,   158,   181,   226,
     161,   200,    37,   232,   165,   166,   167,   226,   875,   876,
     171,   226,    43,   227,  1508,   227,   232,   227,  1441,   886,
     227,   227,   226,   200,   891,    67,   893,   227,   895,    33,
     226,    33,   226,   900,   207,   226,  1447,   227,   226,   226,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   226,    70,   189,   226,    60,    61,    60,    61,
     227,   226,   223,   224,   226,    43,  1489,   226,   226,   189,
     189,   227,  1623,   226,   226,   226,  1627,   227,   193,   227,
     227,   227,   226,   226,   226,  1508,   226,   189,   955,   227,
     227,   230,   959,   139,   140,   141,   142,   143,   227,   232,
     146,   147,   148,   149,   227,   151,   152,   153,   154,   155,
     227,   157,   158,   227,   227,   227,   227,  1540,   985,    33,
     227,   231,   227,   227,   227,    12,   227,  1678,   227,   227,
     230,   131,   132,   133,   134,   135,   136,   137,   138,   199,
     199,   227,   227,   147,   226,   147,   150,   151,  1015,   151,
     150,   227,   156,   227,   227,   227,   156,   227,  1569,   205,
     206,   207,   208,   209,   210,   211,   212,   230,   168,   169,
     170,   227,  1039,   230,   227,  1586,   227,   223,   224,    53,
      33,   225,   231,  1734,   232,   225,  1680,   191,   226,  1740,
     685,   227,     1,   232,   231,  1746,   200,   201,   232,   201,
     200,   205,   232,   205,   208,   207,   208,    60,    61,    79,
     190,    82,  1781,  1779,   213,  1298,   705,  1084,   701,  1009,
       1,  1772,   501,   502,  1091,    33,   230,  1094,   767,   233,
    1435,   233,   783,  1100,   783,  1102,  1645,  1588,  1591,  1646,
    1511,   520,   521,   522,   523,   524,  1646,    53,  1197,  1008,
    1008,    -1,    60,    61,   231,    -1,   657,  1680,   355,    -1,
      -1,   483,   483,   483,  1675,    -1,  1133,    -1,  1135,    -1,
    1137,    -1,  1683,    -1,   483,   483,    -1,    -1,   483,    -1,
    1147,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1155,    -1,
      -1,    -1,    -1,    -1,   147,    -1,    -1,    -1,   151,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1720,
      -1,    -1,  1179,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1189,    -1,    -1,    -1,  1737,  1194,    -1,  1196,
      -1,    -1,    -1,   612,    -1,    -1,    -1,    -1,  1205,   147,
    1751,  1208,  1753,   151,    -1,    -1,    -1,  1758,   201,    -1,
      -1,    -1,   205,    -1,   207,   208,    -1,    -1,    -1,    -1,
    1227,    -1,    -1,    -1,  1775,    -1,  1777,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    22,    -1,
     233,    -1,  1249,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1257,  1258,  1259,   201,    38,    -1,    -1,   205,    -1,   207,
     208,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1276,
      -1,    -1,  1279,    -1,    21,    22,    -1,    -1,    -1,    -1,
      -1,  1288,    -1,    -1,    -1,   233,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   713,   714,    -1,    -1,   717,   718,
     719,   720,    -1,   722,    -1,    -1,   725,   726,   727,   728,
     729,   730,   731,   732,   733,   734,   735,   736,   737,   738,
     739,   740,   741,   742,   743,   744,    -1,    -1,    -1,    -1,
      -1,  1338,    -1,  1340,    -1,    -1,    -1,    -1,    -1,    -1,
    1347,    -1,    -1,    -1,    -1,    -1,    -1,   131,   132,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   148,    -1,    -1,   151,   152,   153,
      -1,    -1,   156,   157,   158,   159,   160,    -1,    -1,    -1,
    1387,   165,   166,   167,   168,   169,   170,   171,    -1,    -1,
      -1,    -1,   139,   140,   141,   142,   143,  1404,    -1,   146,
     147,   148,   149,   822,   151,   152,   153,   154,   155,    -1,
     157,   158,    -1,    -1,  1421,  1422,    -1,   201,   165,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,    -1,
      -1,   215,   216,    -1,    -1,  1442,    -1,    -1,    -1,   223,
     224,  1448,  1449,    -1,    -1,    -1,    -1,  1454,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   223,   224,  1485,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1494,    -1,    -1,
     909,    10,  1499,    -1,    -1,  1502,    -1,  1504,    -1,    -1,
      -1,    -1,    21,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1526,
    1527,  1528,  1529,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1546,
      -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1566,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1005,    -1,  1595,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1611,    -1,    -1,    -1,    -1,  1616,
    1617,    -1,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   148,
     149,   150,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,    -1,    -1,    -1,   165,   166,   167,   168,
     169,   170,   171,    -1,    -1,    -1,   147,    -1,    -1,    -1,
     151,    -1,  1669,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   200,   201,    -1,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,    -1,    -1,    -1,    -1,  1705,    -1,
      -1,    -1,    -1,    19,   223,   224,    -1,    -1,    33,    25,
     201,  1718,    -1,    33,   205,    31,   207,   208,    -1,    -1,
    1727,    -1,    -1,    -1,  1143,    41,    -1,    -1,    -1,  1736,
      -1,    -1,    -1,    49,    -1,    60,    61,    -1,    -1,    -1,
      60,    61,   233,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      -1,    -1,    -1,  1760,    -1,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   147,    -1,    -1,    -1,   151,   147,    -1,    -1,
      -1,   151,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   164,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   177,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   189,    -1,    -1,   201,    -1,    -1,    -1,
     205,   201,   207,   208,    -1,   205,    -1,   207,   208,    -1,
    1309,  1310,  1311,  1312,  1313,  1314,  1315,  1316,  1317,  1318,
    1319,  1320,  1321,  1322,  1323,  1324,  1325,  1326,   233,    -1,
      -1,    -1,   228,   233,    -1,    -1,    -1,   233,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,     5,     6,     7,    -1,
       9,    10,    11,    -1,    13,    -1,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    25,    26,    27,    28,
      29,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    -1,    42,    -1,    44,    45,    -1,    -1,    48,
      -1,    50,    51,    52,    -1,    54,    55,    -1,    -1,    58,
      59,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,
      69,    -1,    71,    72,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    -1,    93,    94,    95,    -1,  1447,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   141,   142,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   162,    -1,   164,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   172,   173,   174,   175,   176,    -1,   178,
      -1,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,    -1,   191,   192,    -1,    -1,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    31,   208,
     209,   210,    -1,   212,    -1,    -1,   215,   216,    41,    -1,
      -1,    -1,    -1,    -1,    -1,   224,    49,   226,    -1,   228,
     229,   230,   231,   232,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1674,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1683,    -1,    -1,    -1,    -1,    -1,
      -1,   164,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,   189,     5,     6,     7,
      -1,     9,    10,    11,    -1,    13,    -1,    15,    16,    17,
      18,    19,    -1,    -1,  1733,    -1,    -1,    25,    26,    27,
      28,    29,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      38,    39,    40,    -1,    42,   228,    44,    45,    -1,  1758,
      48,    -1,    50,    51,    52,    -1,    54,    55,    -1,    -1,
      58,    59,  1771,    -1,    -1,    -1,    -1,    65,  1777,    -1,
      68,    69,    -1,    71,    72,    73,    -1,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    -1,    93,    94,    95,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   141,   142,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   162,    -1,   164,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   172,   173,   174,   175,   176,    -1,
     178,    -1,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,    -1,   191,   192,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     208,   209,   210,    -1,   212,    -1,    -1,   215,   216,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   224,    -1,   226,    -1,
     228,   229,   230,   231,   232,     1,    -1,    -1,    -1,     5,
       6,     7,    -1,     9,    10,    11,    -1,    13,    -1,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,
      26,    27,    28,    29,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    -1,    42,    -1,    44,    45,
      -1,    -1,    48,    -1,    50,    51,    52,    -1,    54,    55,
      -1,    -1,    58,    59,    -1,    -1,    -1,    -1,    -1,    65,
      -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    -1,    93,    94,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   141,   142,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,   164,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   172,   173,   174,   175,
     176,    -1,   178,    -1,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,    -1,   191,   192,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   208,   209,   210,    -1,   212,    -1,    -1,   215,
     216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   224,    -1,
     226,    -1,   228,   229,   230,   231,   232,     1,    -1,    -1,
      -1,     5,     6,     7,    -1,     9,    10,    11,    -1,    13,
      -1,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    25,    26,    27,    28,    29,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    -1,    42,    -1,
      44,    45,    -1,    -1,    48,    -1,    50,    51,    52,    -1,
      54,    55,    -1,    -1,    58,    59,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    68,    69,    -1,    71,    72,    73,
      -1,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    -1,    93,
      94,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,   142,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,
     164,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   172,   173,
     174,   175,   176,    -1,   178,    -1,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,    -1,   191,   192,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   208,   209,   210,    -1,   212,    -1,
      -1,   215,   216,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     224,    -1,   226,    -1,   228,   229,   230,   231,   232,     1,
      -1,    -1,    -1,     5,     6,     7,    -1,     9,    10,    11,
      -1,    13,    -1,    15,    16,    17,    18,    19,    -1,    -1,
      -1,    -1,    -1,    25,    26,    27,    28,    29,    -1,    31,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    -1,
      42,    -1,    44,    45,    -1,    -1,    48,    -1,    50,    51,
      52,    -1,    54,    55,    -1,    -1,    58,    59,    -1,    -1,
      -1,    -1,    -1,    65,    -1,    -1,    68,    69,    -1,    71,
      72,    73,    -1,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      -1,    93,    94,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,
     142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     162,    -1,   164,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     172,   173,   174,   175,   176,    -1,   178,    -1,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,    -1,   191,
     192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   208,   209,   210,    -1,
     212,    -1,    -1,   215,   216,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   224,    -1,   226,    -1,   228,   229,   230,   231,
     232,     1,    -1,    -1,    -1,     5,     6,     7,    -1,     9,
      10,    11,    -1,    13,    -1,    15,    16,    17,    18,    19,
      -1,    -1,    -1,    -1,    -1,    25,    26,    27,    28,    29,
      -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      40,    -1,    42,    -1,    44,    45,    -1,    -1,    48,    -1,
      50,    51,    52,    -1,    54,    55,    -1,    -1,    58,    59,
      -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,
      -1,    71,    72,    73,    -1,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    -1,    93,    94,    95,    -1,    -1,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   141,   142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   162,    -1,   164,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   172,   173,   174,   175,   176,    -1,   178,    -1,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
      -1,   191,   192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,   209,
     210,    -1,   212,    -1,    -1,   215,   216,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   224,    -1,   226,    -1,   228,   229,
     230,   231,   232,     5,     6,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    15,    16,    17,    18,    19,    -1,    -1,
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
     142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     162,    -1,   164,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     172,   173,   174,   175,   176,    -1,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,    -1,    -1,
     192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   208,   209,   210,    -1,
     212,    -1,    -1,   215,   216,    -1,    -1,    -1,    -1,    -1,
       5,     6,   224,    -1,   226,   227,   228,   229,    13,   231,
      15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,
      25,    -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      45,    -1,    -1,    48,    49,    -1,    51,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   141,   142,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   150,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,   164,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   172,   173,   174,
     175,   176,    -1,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,    -1,    -1,   192,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   208,   209,   210,    -1,   212,    -1,    -1,
     215,   216,    -1,    -1,    -1,    -1,    -1,     5,     6,   224,
      -1,   226,    -1,   228,   229,    13,   231,    15,    16,    17,
      18,    19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,
      -1,    -1,    33,    31,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,
      48,    49,    -1,    51,    -1,    -1,    -1,    55,    -1,    60,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    65,    -1,    -1,
      68,    69,    -1,    71,    72,    73,    -1,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    -1,    93,    94,    95,    -1,    -1,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   141,   142,    -1,   147,    -1,    -1,    -1,
     151,    -1,   150,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   162,    -1,   164,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   172,   173,   174,   175,   176,    -1,
     178,    -1,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,    -1,    -1,   192,    -1,    -1,    -1,    -1,    -1,
     201,    -1,    -1,    -1,   205,    -1,   207,   208,    -1,    -1,
     208,   209,   210,    -1,   212,    -1,    -1,   215,   216,    -1,
      -1,    -1,    -1,    -1,     5,     6,   224,    -1,   226,    -1,
     228,   229,   233,   231,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    25,    -1,    27,    -1,    -1,    33,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    -1,
      51,    -1,    -1,    -1,    55,    -1,    60,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,    70,
      71,    72,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,    93,    94,    95,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     141,   142,    -1,   147,    -1,    -1,    -1,   151,    -1,   150,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   162,    -1,   164,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   172,   173,   174,   175,   176,    -1,   178,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,    -1,
      -1,   192,    -1,    -1,    -1,    -1,    -1,   201,    -1,    -1,
      -1,   205,    -1,   207,   208,    -1,    -1,   208,   209,   210,
      -1,   212,    -1,    -1,   215,   216,    -1,    -1,    -1,    -1,
      -1,     5,     6,   224,    -1,   226,    -1,   228,   229,   233,
     231,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
      -1,    25,    -1,    27,    -1,    -1,    33,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,
      -1,    45,    -1,    -1,    48,    -1,    -1,    51,    -1,    -1,
      -1,    55,    -1,    60,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    -1,    -1,    68,    69,    -1,    71,    72,    73,
      -1,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    -1,    93,
      94,    95,    -1,    -1,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   141,   142,    -1,
     147,    -1,    -1,    -1,   151,    -1,   150,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,
     164,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   172,   173,
     174,   175,   176,    -1,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,    -1,    -1,   192,    -1,
      -1,    -1,    -1,    -1,   201,    -1,    -1,    -1,   205,    -1,
     207,   208,    -1,    -1,   208,   209,   210,    -1,   212,    -1,
      -1,   215,   216,    -1,    -1,    -1,    -1,    -1,     5,     6,
     224,    -1,   226,   227,   228,   229,   233,   231,    15,    16,
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
      -1,    -1,    -1,   150,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   162,    -1,   164,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   172,   173,   174,   175,   176,
      -1,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,    -1,    -1,   192,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   208,   209,   210,    -1,   212,    -1,    -1,   215,   216,
      -1,    -1,    -1,    -1,    -1,     5,     6,   224,    -1,   226,
     227,   228,   229,    -1,   231,    15,    16,    17,    18,    19,
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
      -1,    -1,   162,    -1,   164,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   172,   173,   174,   175,   176,    -1,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
      -1,    -1,   192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,   209,
     210,    -1,   212,    -1,    -1,   215,   216,    -1,    -1,    -1,
      -1,    -1,     5,     6,   224,    -1,   226,    -1,   228,   229,
      -1,   231,    15,    16,    17,    18,    19,    -1,    -1,    -1,
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
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,   164,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   172,
     173,   174,   175,   176,    -1,   178,    -1,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,    -1,    -1,   192,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   208,   209,   210,    -1,   212,
      -1,    -1,   215,   216,    -1,    -1,    -1,    -1,    -1,     5,
       6,   224,    -1,   226,   227,   228,   229,    -1,   231,    15,
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
      -1,    -1,    -1,    -1,   150,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,   164,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   172,   173,   174,   175,
     176,    -1,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,    -1,    -1,   192,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   208,   209,   210,    -1,   212,    -1,    -1,   215,
     216,    -1,    -1,    -1,    -1,    -1,     5,     6,   224,    -1,
     226,    -1,   228,   229,    -1,   231,    15,    16,    17,    18,
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
      -1,    -1,    -1,   162,    -1,   164,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   172,   173,   174,   175,   176,    -1,   178,
      -1,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,    -1,    -1,   192,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,
     209,   210,    -1,   212,    -1,    -1,   215,   216,    -1,    -1,
      -1,    -1,    -1,     5,     6,   224,    -1,   226,   227,   228,
     229,    -1,   231,    15,    16,    17,    18,    19,    -1,    -1,
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
     142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     162,    -1,   164,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     172,   173,   174,   175,   176,    -1,   178,    -1,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,    -1,    -1,
     192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   208,   209,   210,    -1,
     212,    -1,    -1,   215,   216,    -1,    -1,    -1,    -1,    -1,
       5,     6,   224,    -1,   226,   227,   228,   229,    -1,   231,
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
      -1,    -1,    -1,    -1,    -1,   150,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,   164,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   172,   173,   174,
     175,   176,    -1,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,    -1,    -1,   192,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   208,   209,   210,    -1,   212,    -1,    -1,
     215,   216,    -1,    -1,    -1,    -1,    -1,     5,     6,   224,
      -1,   226,    -1,   228,   229,    -1,   231,    15,    16,    17,
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
      -1,    -1,   150,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   162,    -1,   164,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   172,   173,   174,   175,   176,    -1,
     178,    -1,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,    -1,    -1,   192,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     208,   209,   210,    -1,   212,    -1,    -1,   215,   216,    -1,
      -1,    -1,    -1,    -1,     5,     6,   224,    -1,   226,    -1,
     228,   229,    -1,   231,    15,    16,    17,    18,    19,    -1,
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
      -1,   162,    -1,   164,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   172,   173,   174,   175,   176,    -1,   178,    -1,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,    -1,
      -1,   192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,   209,   210,
      -1,   212,    -1,    -1,   215,   216,    -1,    -1,    -1,    -1,
      -1,     5,     6,   224,   225,   226,    -1,   228,   229,    -1,
     231,    15,    16,    17,    18,    19,    -1,    -1,    -1,    -1,
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
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,
     164,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   172,   173,
     174,   175,   176,    -1,   178,    -1,   180,   181,   182,   183,
     184,   185,   186,   187,   188,   189,    -1,    -1,   192,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   208,   209,   210,    -1,   212,    -1,
      -1,   215,   216,    -1,    -1,    -1,    -1,    -1,     5,     6,
     224,   225,   226,    -1,   228,   229,    -1,   231,    15,    16,
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
      -1,    -1,    -1,   150,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   162,    -1,   164,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   172,   173,   174,   175,   176,
      -1,   178,    -1,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,    -1,    -1,   192,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   208,   209,   210,    -1,   212,    -1,    -1,   215,   216,
      -1,    -1,    -1,    -1,    -1,     5,     6,   224,    -1,   226,
      -1,   228,   229,    13,   231,    15,    16,    17,    18,    19,
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
      -1,    -1,   162,    -1,   164,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   172,   173,   174,   175,   176,    -1,   178,    -1,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
      -1,    -1,   192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,   209,
     210,    -1,   212,    -1,    -1,   215,   216,    -1,    -1,    -1,
      -1,    -1,     5,     6,   224,    -1,   226,    -1,   228,   229,
      -1,   231,    15,    16,    17,    18,    19,    -1,    -1,    -1,
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
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,
      -1,   164,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   172,
     173,   174,   175,   176,    -1,   178,    -1,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,    -1,    -1,   192,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   208,   209,   210,    -1,   212,
      -1,    -1,   215,   216,    -1,    -1,    -1,    -1,    -1,     5,
       6,   224,    -1,   226,    -1,   228,   229,    -1,   231,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    25,
      -1,    27,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,    -1,    45,
      -1,    -1,    48,    -1,    -1,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    65,
      -1,    -1,    68,    69,    -1,    71,    72,    73,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    -1,    93,    94,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   141,   142,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,   164,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   172,   173,   174,   175,
     176,    -1,   178,    -1,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,    -1,    -1,   192,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   208,   209,   210,    -1,   212,    -1,    -1,   215,
     216,    -1,    -1,    -1,    -1,    -1,     5,     6,   224,    -1,
     226,    -1,   228,   229,    -1,   231,    15,    16,    17,    18,
      19,    -1,    -1,    -1,    -1,    -1,    25,    -1,    27,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    48,
      -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    58,
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
      -1,    -1,    -1,   162,    -1,   164,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   172,   173,   174,   175,   176,    -1,   178,
      -1,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,    -1,    -1,   192,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,
     209,   210,    -1,   212,    -1,    -1,   215,   216,    -1,    -1,
      -1,    -1,    -1,     5,     6,   224,    -1,   226,    -1,   228,
     229,    -1,   231,    15,    16,    17,    18,    19,    -1,    -1,
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
     142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     162,    -1,   164,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     172,   173,   174,   175,   176,    -1,   178,    -1,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,    -1,    -1,
     192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   208,   209,   210,    -1,
     212,    -1,    -1,   215,   216,    -1,    -1,    -1,    -1,    -1,
       5,     6,   224,    -1,   226,    -1,   228,   229,    -1,   231,
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
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,   164,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   172,   173,   174,
     175,   176,    -1,   178,    -1,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,    -1,    -1,   192,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   208,   209,   210,    -1,   212,    -1,    -1,
     215,   216,    -1,    -1,    -1,    -1,    -1,     5,     6,   224,
      -1,   226,   227,   228,   229,    -1,   231,    15,    16,    17,
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
      -1,    -1,    -1,    -1,   162,    -1,   164,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   172,   173,   174,   175,   176,    -1,
     178,    -1,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,    -1,    -1,   192,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     208,   209,   210,    -1,   212,    -1,    -1,   215,   216,    -1,
      -1,    -1,    -1,    -1,     5,     6,   224,    -1,   226,    -1,
     228,   229,    -1,   231,    15,    16,    17,    18,    19,    -1,
      -1,    -1,    -1,    -1,    25,    26,    27,    28,    -1,    -1,
      31,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,    -1,    45,    -1,    -1,    48,    -1,    -1,
      51,    52,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    -1,    -1,    68,    69,    -1,
      71,    72,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,    93,    94,    95,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     141,   142,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   162,    -1,   164,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   172,   173,   174,   175,   176,    -1,   178,    -1,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,    -1,
      -1,   192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,   209,   210,
      -1,   212,    -1,    -1,   215,   216,    -1,    -1,    -1,     5,
       6,    -1,    -1,   224,    -1,   226,    -1,   228,   229,    15,
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
      -1,    -1,    -1,    -1,   150,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,   164,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   172,   173,   174,   175,
     176,    -1,   178,    -1,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,    -1,    -1,   192,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   208,   209,   210,    -1,   212,    -1,    -1,   215,
     216,    -1,    -1,    -1,     5,     6,    -1,    -1,   224,    -1,
     226,    -1,   228,   229,    15,    16,    17,    18,    19,    -1,
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
      -1,   162,    -1,   164,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   172,   173,   174,   175,   176,    -1,   178,    -1,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,    -1,
      -1,   192,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   208,   209,   210,
      -1,   212,    -1,    -1,   215,   216,    -1,    -1,    -1,     5,
       6,    -1,    -1,   224,    -1,   226,    -1,   228,   229,    15,
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
      -1,    -1,    -1,    -1,    -1,    -1,   162,    -1,   164,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   172,   173,   174,   175,
     176,    -1,   178,    -1,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,    -1,    19,   192,    -1,    -1,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    -1,   208,   209,   210,    -1,   212,    41,    -1,   215,
     216,    -1,    -1,    -1,    -1,    49,    -1,    -1,   224,    -1,
     226,    -1,   228,   229,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   126,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     164,    -1,    -1,    -1,    -1,    -1,    -1,    21,    22,    -1,
      -1,    -1,    -1,   177,    -1,    -1,    19,    -1,    -1,    -1,
      -1,    -1,    25,    -1,    -1,   189,    -1,   191,    31,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    -1,    -1,   228,    -1,   230,    -1,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,    -1,   139,   140,   141,   142,   143,
      21,    22,   146,   147,   148,   149,    -1,   151,   152,   153,
     154,   155,    -1,   157,   158,    -1,    -1,   161,    -1,    -1,
      -1,   165,   166,   167,    -1,    -1,    -1,   171,    -1,    -1,
      -1,   164,    -1,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   189,   201,    -1,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   223,
     224,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   228,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    21,    22,    -1,    -1,    -1,    -1,   139,   140,
     141,   142,   143,    -1,    -1,   146,   147,   148,   149,    -1,
     151,   152,   153,   154,   155,    -1,   157,   158,    -1,    -1,
     161,    21,    22,    -1,   165,   166,   167,    -1,    -1,    -1,
     171,   139,   140,   141,   142,   143,    -1,    -1,   146,   147,
     148,   149,    -1,   151,   152,   153,   154,   155,    -1,   157,
     158,    -1,    -1,    -1,    -1,    -1,    -1,   165,   166,   167,
     201,    -1,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   223,   224,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   201,    -1,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,    -1,    -1,    -1,    -1,    -1,
     139,   140,   141,   142,   143,   223,   224,   146,   147,   148,
     149,    -1,   151,   152,   153,   154,   155,    -1,   157,   158,
      -1,    -1,    -1,    -1,    -1,    -1,   165,    -1,   167,   139,
     140,   141,   142,   143,    -1,    -1,   146,   147,   148,   149,
      -1,   151,   152,   153,   154,   155,    -1,   157,   158,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    19,   203,   204,   205,   206,   207,   208,
     209,   210,   211,   212,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   223,   224,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   203,   204,   205,   206,   207,   208,   209,
     210,   211,   212,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   223,   224,    71,    72,    73,    -1,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    -1,    93,    94,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,    71,
      -1,    73,    -1,    75,    76,    77,    78,    79,    19,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      -1,    93,    94,    95,    -1,    -1,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   179,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    72,    73,   189,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    -1,    93,    94,    95,    -1,    -1,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,    71,    -1,    73,   189,    75,    76,
      77,    78,    79,    19,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    -1,    93,    94,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   179,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73,   189,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    -1,    93,    94,    95,
      -1,    -1,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,    -1,
      -1,    -1,   189,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   179,    71,    -1,    73,    -1,    75,    76,
      77,    78,    79,   189,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    -1,    93,    94,    95,    -1,
      -1,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   141,   142,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    -1,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    -1,    93,    94,
      95,    -1,   189,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   152,   153,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   179,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   189,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    -1,    73,    -1,    75,    76,    77,
      78,    79,    -1,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    -1,    93,    94,    95,   223,   224,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   189
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   235,     0,     7,    30,    32,    34,    40,    50,    56,
      80,   125,   126,   191,   212,   224,   230,   237,   238,   242,
     251,   253,   254,   259,   308,   314,   345,   427,   435,   443,
     453,   503,   508,   513,    19,    20,   189,   298,   299,   300,
     181,   260,   261,   201,   256,   257,    57,    63,   432,   433,
     436,   189,   228,   240,   514,   504,   509,   164,   189,   333,
      34,    63,   130,   155,   216,   226,   303,   304,   305,   306,
     333,   237,   237,   237,     8,    36,   454,    62,   423,   200,
     199,   202,   199,   171,   189,   212,   223,   255,   255,   189,
     237,   237,   423,   432,   432,   432,   189,   164,   252,   305,
     305,   305,   226,   165,   166,   167,   199,   225,   130,   313,
     444,     5,     6,   450,    57,    63,   424,    15,    16,   162,
     181,   186,   189,   192,   226,   244,   299,   181,   261,   211,
     211,   255,   211,   211,   223,    22,    57,   258,   189,   434,
      57,    63,   239,   189,   189,   189,   189,   193,   250,   227,
     300,   305,   305,   305,   305,   191,   265,   266,    57,    63,
     315,   317,    57,    63,   437,   130,   130,    57,    63,   451,
     231,   428,   189,   193,   194,   195,   243,    15,    16,   181,
     186,   189,   244,   296,   297,   255,   255,   255,   189,   189,
     189,   200,   200,   216,   241,   202,   464,   266,   266,   193,
     227,   191,   318,   189,   438,   455,   425,   163,   301,   393,
     193,   194,   195,   199,   227,   258,    19,    25,    31,    41,
      49,    64,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   177,   228,
     333,   458,   460,   461,   465,   471,   473,   502,   502,    66,
      79,    94,    99,   101,   190,   441,   442,   505,   510,    35,
      71,    73,    75,    76,    77,    78,    79,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    93,    94,
      95,    98,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   141,   142,
     189,   311,   312,   316,   202,   439,   129,   448,   449,   232,
     237,   426,   299,   163,   189,   419,   422,   296,   206,   206,
     206,   226,   206,   206,   226,   464,   206,   206,   206,   206,
     206,   226,   333,   206,   226,    33,    60,    61,   147,   151,
     201,   205,   208,   233,   224,   470,   203,   190,   515,   231,
     231,    21,    22,    38,   131,   132,   133,   134,   135,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   151,   152,   153,   156,   157,   158,   159,   160,
     165,   166,   167,   168,   169,   170,   171,   201,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   215,   216,
     223,   224,    35,    35,   226,   309,   266,    75,    79,    93,
      94,    98,    99,   100,   101,   459,   442,   189,   266,   393,
     266,   299,   199,   202,   205,   417,   474,   480,   482,     5,
       6,    15,    16,    17,    18,    19,    25,    27,    31,    39,
      45,    48,    51,    55,    65,    68,    69,    80,   125,   126,
     127,   141,   142,   162,   172,   173,   174,   175,   176,   178,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   192,
     208,   209,   210,   215,   216,   224,   226,   228,   229,   231,
     249,   251,   325,   333,   338,   350,   357,   360,   363,   367,
     369,   371,   372,   374,   379,   382,   383,   384,   391,   392,
     458,   519,   527,   538,   541,   554,   555,   558,   559,   484,
     478,   189,   206,   486,   488,   490,   492,   494,   496,   498,
     500,   383,   206,   226,   472,   476,   150,   330,   361,   383,
      33,   205,    33,   205,   224,   233,   225,   383,   224,   233,
     471,   231,   506,   511,   189,   312,   189,   312,   189,   225,
      22,   189,   225,   176,   227,   393,   403,   404,   405,   149,
     202,   310,   161,   231,   322,   362,   231,   202,   447,   456,
     173,   189,   418,   421,   266,   189,   471,   150,   156,   200,
     416,   502,   502,   469,   502,   206,   206,   206,   333,   335,
     460,   518,   527,   538,   541,   554,   555,   558,   559,   333,
     206,     5,   125,   126,   206,   226,   206,   226,   226,   206,
     206,   226,   206,   226,   206,   226,   206,   206,   226,    19,
     206,   206,   384,   384,   173,   178,   206,   333,   373,   226,
     226,   226,   226,   226,   226,   248,   384,   384,   384,   384,
     384,    13,    49,   330,   179,   189,   361,   520,   522,   553,
     226,   224,   307,   162,   231,   363,   368,   368,   368,   368,
     227,    21,    22,   139,   140,   141,   142,   143,   146,   147,
     148,   149,   151,   152,   153,   154,   155,   157,   158,   161,
     165,   166,   167,   171,   201,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   223,   224,   226,   502,   502,
     227,   207,   466,   502,   309,   502,   309,   502,   309,   189,
     406,   407,   502,   189,   409,   410,   227,   477,   361,   332,
     502,   383,   227,   199,   557,   225,   225,   225,   383,   516,
     406,   408,   409,   411,   189,   312,   131,   132,   133,   134,
     135,   136,   137,   138,   156,   168,   169,   170,   131,   132,
     133,   134,   135,   136,   137,   138,   150,   156,   168,   169,
     170,   200,   226,     7,    50,   344,   230,   199,   230,   227,
     502,   502,   150,   384,   323,   445,   333,   230,   231,   452,
     226,    43,   199,   202,   417,   237,   416,   383,   207,   207,
     207,   190,   199,   236,   237,   468,   528,   530,   336,   226,
     206,   226,   358,   206,   206,   206,   548,   361,   471,   383,
     552,   383,   351,   353,   383,   355,   383,   550,   361,   536,
     539,   361,   206,   532,   471,   226,   226,   375,   377,   383,
     383,   383,   383,   383,   383,   195,   196,   243,   226,    13,
     225,   226,   150,   156,   200,   412,   557,   199,   557,   227,
     266,    70,   224,   227,   361,   522,   306,     4,   366,   329,
     307,    19,   179,   189,   458,    19,   179,   189,   458,   384,
     384,   384,   384,   384,   384,   189,   384,   179,   189,   383,
     384,   384,   458,   384,   384,   384,   554,   559,   384,   384,
     384,   384,    22,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   152,   153,   179,   189,   223,   224,
     380,   458,   383,   227,   361,   207,   207,   189,   462,   207,
     310,   207,   310,   207,   310,   202,   207,   468,   202,   207,
     468,   332,   557,   207,   468,   150,   383,   225,   189,   463,
     237,   273,   274,   273,   274,   383,   173,   189,   413,   414,
     457,   405,   405,   405,   384,   329,   189,   429,   431,   399,
     383,   189,   173,   189,   471,   416,   383,   237,   475,   481,
     483,   502,   471,   471,   502,    70,   361,   522,   526,   189,
     383,   502,   542,   544,   546,   471,   557,   207,   468,   199,
     557,   227,   471,   471,   227,   471,   227,   471,   557,   471,
     407,   557,   534,   410,   207,   383,   383,   471,   309,   227,
     227,   227,   227,   227,   227,   383,   173,   189,   226,   287,
     226,   383,   383,   383,   227,   179,   189,    13,   331,   552,
     189,   227,   522,   520,   199,   227,   227,   225,   226,   309,
       1,    26,    28,    29,    38,    40,    44,    52,    54,    58,
      59,    65,   128,   231,   232,   237,   262,   263,   272,   283,
     284,   286,   288,   289,   290,   291,   292,   293,   294,   295,
     326,   334,   339,   340,   341,   342,   343,   345,   349,   370,
     384,   366,   206,   226,   206,   226,   226,   226,   225,    19,
     179,   189,   458,   202,   179,   189,   383,   226,   226,   179,
     189,   383,     1,   226,   225,   199,   227,   485,   479,   199,
     207,   230,   487,   207,   491,   207,   495,   207,   502,   499,
     406,   502,   501,   409,   207,   227,   472,   502,   383,   200,
     236,   430,   440,   237,   406,   507,   409,   512,   227,   226,
      43,   199,   202,   205,   412,   324,   200,   430,   440,    40,
     191,   232,   308,   400,   227,   226,    43,   237,   416,   383,
     237,   207,   207,   207,   522,   227,   227,   227,   207,   468,
     227,   207,   471,   407,   410,   207,   227,   226,   471,   383,
     227,   207,   207,   207,   207,   227,   207,   207,   227,   471,
     207,   366,   227,   227,   207,   310,   226,   202,   246,   226,
      43,   189,   347,    20,   199,   287,   227,   226,   156,   412,
     226,   232,   557,   227,   199,   225,   224,   520,   150,   156,
     189,   200,   205,   364,   365,   310,   150,   383,   322,    61,
     383,   189,   189,   237,   181,    58,   383,   266,   150,   383,
     327,   237,   237,    10,    10,    11,   270,    13,     9,    42,
     237,   237,   237,   237,   237,   237,    66,   346,   237,   131,
     132,   133,   134,   135,   136,   137,   138,   144,   145,   150,
     156,   159,   160,   168,   169,   170,   200,   309,   385,   383,
     387,   383,   224,   227,   361,   520,   383,   206,   226,   384,
     226,   225,   383,   224,   227,   361,   520,   226,   225,   381,
     227,   361,   189,   467,   189,   489,   493,   497,   472,   383,
     189,   236,   517,   232,   232,   383,   189,   173,   189,   502,
     383,   232,   383,   429,   446,   189,     8,   393,   398,   383,
     189,   383,   237,   529,   531,   337,   227,   226,   189,   359,
     207,   207,   207,   549,   331,   207,   352,   354,   356,   551,
     537,   540,   207,   533,   226,   266,   376,   207,   227,   361,
     247,   197,   383,   189,   199,   227,   361,   173,   189,   226,
      20,   156,   412,   383,   383,   383,   287,   227,   520,   227,
     189,   189,   226,   189,   189,   199,   227,   266,   383,    14,
     383,   200,   200,   202,   181,   322,   383,   329,   226,   226,
     224,   301,   302,   302,   226,   226,   231,   348,   421,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     554,   559,   384,   384,   384,   384,   384,   384,   384,   310,
     471,   227,   502,   227,   520,   199,   227,   227,   227,   389,
     383,   383,   227,   520,   199,   227,   227,   383,   227,   200,
     232,   227,   226,    43,   412,    37,   319,   232,   200,    57,
      63,   396,    67,   397,   237,   227,   237,   226,   226,   383,
     207,   543,   545,   547,   226,   227,   226,   226,   226,   226,
     226,    70,   526,   226,   535,   226,   227,   383,   322,   373,
     378,   227,   245,   227,   189,   227,   226,    43,   347,   361,
     383,   383,   227,    20,   225,   189,   364,   362,   322,   502,
     383,   328,   383,   383,   300,   226,   226,   383,   347,   420,
     266,   207,   207,   225,   520,   502,   227,   227,   225,   520,
     227,   383,   383,   189,   383,   320,   502,    47,   397,    46,
     129,   394,   526,   526,   227,   226,   226,   226,   226,   330,
     331,   383,   383,   383,   361,   526,   226,   526,   227,   373,
     193,   230,   383,   189,   227,   227,   156,   412,   361,   227,
     227,   232,   227,   227,   225,   287,   383,   227,   227,   232,
     237,   421,   362,   386,   388,   227,   227,   207,   227,   227,
     227,   231,   237,    33,   395,   394,   396,   226,   520,   523,
     524,   525,   525,   383,   526,   526,   520,   521,   227,   227,
     227,   227,   227,   557,   525,   526,   521,   383,   227,   230,
     383,   383,   227,   319,    12,   271,   266,    20,   227,   266,
     202,   417,   390,   329,   401,   395,   413,   414,   415,   520,
     199,   557,   227,   227,   227,   525,   525,   227,   227,   227,
     521,   227,   230,   556,   383,   230,   272,   339,   340,   341,
     342,   384,   237,   285,   361,   266,   322,   471,   416,   321,
     316,   402,   227,   226,   227,   227,   227,    53,   225,   556,
     383,   231,   275,   278,   227,   322,   416,   383,   232,   237,
     316,   520,   383,   225,   556,   276,    12,    23,    24,   264,
     267,   272,   266,   383,   237,   266,   227,   232,   329,   266,
     226,   237,   322,   237,   362,   277,   268,   383,   232,   231,
     279,   282,   227,   319,   280,   272,   266,   329,   237,   269,
     281,   279,   232,   267,   319
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   234,   235,   235,   235,   235,   235,   235,   235,   235,
     235,   235,   235,   235,   235,   235,   235,   236,   236,   237,
     237,   238,   239,   239,   239,   240,   240,   241,   241,   242,
     243,   243,   243,   243,   244,   244,   245,   245,   246,   247,
     246,   248,   248,   248,   249,   250,   250,   252,   251,   253,
     254,   255,   255,   255,   255,   255,   255,   255,   256,   256,
     257,   257,   258,   258,   259,   260,   260,   261,   261,   262,
     263,   263,   264,   264,   265,   265,   266,   266,   267,   268,
     267,   269,   267,   270,   270,   271,   271,   272,   272,   272,
     272,   272,   273,   273,   274,   274,   276,   277,   275,   278,
     275,   280,   281,   279,   282,   279,   284,   285,   283,   286,
     287,   287,   287,   287,   287,   287,   287,   287,   289,   288,
     290,   292,   291,   294,   293,   295,   295,   296,   296,   296,
     296,   296,   296,   297,   297,   298,   298,   298,   299,   299,
     299,   299,   299,   299,   299,   299,   299,   300,   300,   301,
     301,   302,   302,   302,   303,   303,   303,   303,   304,   304,
     305,   305,   305,   305,   305,   305,   305,   306,   306,   307,
     307,   308,   308,   309,   309,   309,   310,   310,   310,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   311,   311,
     311,   311,   311,   311,   311,   311,   311,   311,   312,   312,
     312,   312,   312,   312,   312,   312,   312,   312,   312,   312,
     312,   312,   312,   312,   312,   312,   312,   312,   312,   312,
     312,   312,   312,   312,   312,   312,   312,   312,   312,   312,
     312,   312,   312,   312,   312,   312,   312,   312,   312,   312,
     312,   312,   312,   312,   312,   312,   313,   313,   314,   315,
     315,   315,   316,   318,   317,   319,   320,   321,   319,   323,
     324,   322,   325,   325,   325,   325,   326,   326,   326,   326,
     326,   326,   326,   326,   326,   326,   326,   326,   326,   326,
     326,   326,   326,   326,   326,   327,   328,   326,   329,   329,
     329,   330,   330,   331,   331,   332,   332,   333,   333,   333,
     334,   334,   336,   337,   335,   335,   338,   338,   338,   338,
     338,   338,   339,   340,   341,   341,   341,   342,   342,   343,
     344,   344,   344,   345,   345,   346,   346,   347,   347,   348,
     348,   349,   349,   349,   351,   352,   350,   353,   354,   350,
     355,   356,   350,   358,   359,   357,   360,   360,   360,   361,
     361,   361,   361,   362,   362,   362,   363,   363,   363,   364,
     364,   364,   364,   364,   365,   365,   366,   366,   367,   368,
     368,   369,   369,   369,   369,   369,   369,   369,   369,   370,
     370,   370,   370,   370,   370,   370,   370,   370,   370,   370,
     370,   370,   370,   370,   370,   370,   370,   370,   370,   370,
     371,   371,   371,   372,   372,   372,   372,   372,   373,   373,
     374,   375,   376,   374,   377,   378,   374,   379,   379,   379,
     379,   379,   379,   379,   379,   379,   380,   381,   379,   382,
     382,   382,   382,   382,   382,   382,   383,   383,   383,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   385,   386,   384,   384,   384,
     384,   387,   388,   384,   384,   384,   389,   390,   384,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   391,   391,   391,   392,   392,
     392,   392,   392,   392,   392,   392,   392,   392,   392,   392,
     392,   392,   392,   392,   393,   393,   394,   394,   394,   395,
     395,   396,   396,   396,   397,   397,   398,   399,   399,   399,
     400,   399,   401,   399,   402,   399,   403,   404,   404,   405,
     405,   405,   405,   405,   406,   406,   407,   407,   408,   408,
     408,   409,   410,   410,   411,   411,   411,   412,   412,   413,
     413,   413,   414,   414,   415,   415,   416,   416,   416,   417,
     417,   418,   418,   418,   418,   418,   418,   419,   419,   420,
     420,   420,   421,   421,   421,   422,   422,   422,   423,   423,
     424,   424,   424,   425,   425,   426,   425,   427,   428,   427,
     429,   429,   430,   430,   431,   431,   431,   432,   432,   432,
     434,   433,   435,   435,   436,   437,   437,   437,   438,   439,
     439,   440,   440,   441,   441,   442,   442,   444,   445,   446,
     443,   447,   447,   448,   448,   449,   450,   450,   450,   450,
     451,   451,   451,   452,   452,   454,   455,   456,   453,   457,
     457,   457,   457,   457,   457,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   458,   458,   458,   458,   458,
     458,   458,   458,   458,   458,   459,   459,   459,   459,   459,
     459,   459,   459,   460,   461,   461,   461,   462,   462,   462,
     463,   463,   463,   463,   463,   464,   464,   464,   464,   464,
     465,   466,   467,   465,   468,   468,   469,   469,   470,   470,
     470,   470,   471,   471,   472,   472,   473,   473,   473,   473,
     474,   475,   473,   473,   473,   473,   476,   473,   477,   473,
     473,   473,   473,   473,   473,   473,   473,   473,   473,   473,
     473,   473,   478,   479,   473,   473,   480,   481,   473,   482,
     483,   473,   484,   485,   473,   473,   486,   487,   473,   488,
     489,   473,   473,   490,   491,   473,   492,   493,   473,   473,
     494,   495,   473,   496,   497,   473,   498,   499,   473,   500,
     501,   473,   502,   502,   502,   504,   505,   506,   507,   503,
     509,   510,   511,   512,   508,   514,   515,   516,   517,   513,
     518,   518,   518,   518,   518,   518,   518,   519,   519,   519,
     519,   519,   520,   520,   520,   520,   520,   520,   520,   520,
     521,   521,   522,   523,   523,   524,   524,   525,   525,   526,
     526,   528,   529,   527,   530,   531,   527,   532,   533,   527,
     534,   535,   527,   536,   537,   527,   538,   539,   540,   538,
     541,   542,   543,   541,   544,   545,   541,   546,   547,   541,
     541,   548,   549,   541,   541,   550,   551,   541,   552,   552,
     553,   554,   555,   555,   555,   556,   556,   557,   557,   558,
     558,   559
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     1,     4,     0,
       1,     1,     3,     0,     5,     0,     0,     0,     6,     0,
       0,     6,     2,     2,     2,     2,     1,     2,     2,     1,
       1,     1,     1,     2,     1,     2,     2,     2,     2,     1,
       1,     1,     2,     2,     2,     0,     0,     6,     0,     2,
       2,     0,     2,     0,     2,     1,     3,     1,     3,     2,
       2,     3,     0,     0,     5,     1,     2,     5,     5,     5,
       6,     2,     1,     1,     1,     2,     3,     2,     3,     4,
       1,     1,     0,     1,     1,     1,     0,     1,     3,     8,
       7,     3,     3,     5,     0,     0,     9,     0,     0,     9,
       0,     0,     9,     0,     0,     6,     5,     8,    10,     1,
       2,     3,     4,     1,     2,     3,     1,     1,     1,     2,
       2,     2,     2,     4,     1,     3,     0,     4,     7,     7,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       6,     8,     6,     5,     6,     8,     8,     6,     1,     4,
       2,     0,     0,     7,     0,     0,     8,     3,     4,     5,
       6,     8,     8,     6,     5,     6,     0,     0,     5,     3,
       4,     4,     5,     4,     3,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     2,     2,     4,
       3,     4,     5,     4,     5,     3,     4,     1,     1,     2,
       4,     4,     1,     3,     5,     0,     0,     8,     3,     3,
       3,     0,     0,     8,     3,     4,     0,     0,     9,     4,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       1,     4,     3,     3,     3,     7,     8,     7,     4,     4,
       4,     4,     4,     1,     6,     7,     6,     6,     7,     7,
       6,     7,     6,     5,     0,     1,     0,     1,     1,     0,
       1,     0,     1,     1,     0,     1,     5,     0,     2,     6,
       0,     4,     0,     9,     0,    11,     3,     3,     4,     1,
       1,     3,     3,     3,     1,     3,     1,     3,     0,     1,
       3,     3,     1,     3,     0,     1,     3,     1,     1,     1,
       2,     3,     3,     5,     1,     1,     1,     1,     1,     0,
       1,     1,     4,     3,     3,     6,     5,     1,     3,     0,
       2,     2,     4,     6,     5,     4,     6,     5,     0,     1,
       0,     1,     1,     0,     2,     0,     4,     6,     0,     6,
       1,     3,     1,     2,     0,     1,     3,     0,     1,     1,
       0,     5,     3,     3,     5,     0,     1,     1,     1,     0,
       2,     0,     1,     1,     2,     0,     1,     0,     0,     0,
      13,     0,     2,     0,     1,     3,     1,     1,     2,     2,
       0,     1,     1,     1,     3,     0,     0,     0,     9,     1,
       4,     3,     3,     6,     5,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     1,     3,     3,
       0,     1,     3,     3,     5,     0,     2,     2,     2,     2,
       4,     0,     0,     7,     1,     1,     1,     3,     3,     2,
       4,     3,     1,     2,     0,     4,     1,     1,     1,     1,
       0,     0,     6,     4,     4,     3,     0,     6,     0,     7,
       4,     2,     2,     3,     2,     3,     2,     2,     3,     3,
       3,     2,     0,     0,     6,     2,     0,     0,     6,     0,
       0,     6,     0,     0,     6,     1,     0,     0,     6,     0,
       0,     7,     1,     0,     0,     6,     0,     0,     7,     1,
       0,     0,     6,     0,     0,     7,     0,     0,     6,     0,
       0,     6,     1,     3,     3,     0,     0,     0,     0,    12,
       0,     0,     0,     0,    12,     0,     0,     0,     0,    13,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     5,     5,     6,     6,     8,     8,
       0,     1,     2,     3,     5,     1,     2,     1,     0,     0,
       1,     0,     0,    10,     0,     0,    10,     0,     0,    10,
       0,     0,    11,     0,     0,     7,     5,     0,     0,    10,
       3,     0,     0,    11,     0,     0,    11,     0,     0,    10,
       5,     0,     0,     9,     5,     0,     0,    10,     1,     3,
       0,     5,     5,     7,     9,     0,     3,     0,     1,    11,
      12,    13
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
            (yyvsp[0].fa) = nullptr; // gc_node — don't delete AnnotationDeclaration
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
            (yyvsp[-2].fa) = nullptr; // gc_node — don't delete AnnotationDeclaration
        }
        if ( !(yyvsp[0].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[0].fa)->annotation))->isSpecialized() ) {
            das2_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[0])),
                CompilationError::invalid_annotation);
            (yyvsp[0].fa) = nullptr; // gc_node — don't delete AnnotationDeclaration
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
            (yyvsp[-2].fa) = nullptr; // gc_node — don't delete AnnotationDeclaration
        }
        if ( !(yyvsp[0].fa)->annotation || !(yyvsp[0].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[0].fa)->annotation))->isSpecialized() ) {
            das2_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[0])),
                CompilationError::invalid_annotation);
            (yyvsp[0].fa) = nullptr; // gc_node — don't delete AnnotationDeclaration
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
            (yyvsp[-2].fa) = nullptr; // gc_node — don't delete AnnotationDeclaration
        }
        if ( !(yyvsp[0].fa)->annotation->rtti_isFunctionAnnotation() || !((FunctionAnnotation *)((yyvsp[0].fa)->annotation))->isSpecialized() ) {
            das2_yyerror(scanner,"can only run logical operations on contracts", tokAt(scanner, (yylsp[0])),
                CompilationError::invalid_annotation);
            (yyvsp[0].fa) = nullptr; // gc_node — don't delete AnnotationDeclaration
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

  case 293: /* das_type_name: "float16"  */
                     { (yyval.s) = new string("float16"); }
    break;

  case 294: /* das_type_name: "half2"  */
                     { (yyval.s) = new string("half2"); }
    break;

  case 295: /* das_type_name: "half3"  */
                     { (yyval.s) = new string("half3"); }
    break;

  case 296: /* das_type_name: "half4"  */
                     { (yyval.s) = new string("half4"); }
    break;

  case 297: /* das_type_name: "half8"  */
                     { (yyval.s) = new string("half8"); }
    break;

  case 298: /* das_type_name: "short2"  */
                     { (yyval.s) = new string("short2"); }
    break;

  case 299: /* das_type_name: "short3"  */
                     { (yyval.s) = new string("short3"); }
    break;

  case 300: /* das_type_name: "short4"  */
                     { (yyval.s) = new string("short4"); }
    break;

  case 301: /* das_type_name: "short8"  */
                     { (yyval.s) = new string("short8"); }
    break;

  case 302: /* das_type_name: "ushort2"  */
                     { (yyval.s) = new string("ushort2"); }
    break;

  case 303: /* das_type_name: "ushort3"  */
                     { (yyval.s) = new string("ushort3"); }
    break;

  case 304: /* das_type_name: "ushort4"  */
                     { (yyval.s) = new string("ushort4"); }
    break;

  case 305: /* das_type_name: "ushort8"  */
                     { (yyval.s) = new string("ushort8"); }
    break;

  case 306: /* das_type_name: "byte2"  */
                     { (yyval.s) = new string("byte2"); }
    break;

  case 307: /* das_type_name: "byte3"  */
                     { (yyval.s) = new string("byte3"); }
    break;

  case 308: /* das_type_name: "byte4"  */
                     { (yyval.s) = new string("byte4"); }
    break;

  case 309: /* das_type_name: "byte8"  */
                     { (yyval.s) = new string("byte8"); }
    break;

  case 310: /* das_type_name: "byte16"  */
                     { (yyval.s) = new string("byte16"); }
    break;

  case 311: /* das_type_name: "ubyte2"  */
                     { (yyval.s) = new string("ubyte2"); }
    break;

  case 312: /* das_type_name: "ubyte3"  */
                     { (yyval.s) = new string("ubyte3"); }
    break;

  case 313: /* das_type_name: "ubyte4"  */
                     { (yyval.s) = new string("ubyte4"); }
    break;

  case 314: /* das_type_name: "ubyte8"  */
                     { (yyval.s) = new string("ubyte8"); }
    break;

  case 315: /* das_type_name: "ubyte16"  */
                     { (yyval.s) = new string("ubyte16"); }
    break;

  case 316: /* optional_template: %empty  */
                                        { (yyval.b) = false; }
    break;

  case 317: /* optional_template: "template"  */
                                        { (yyval.b) = true; }
    break;

  case 318: /* global_function_declaration: optional_annotation_list_with_emit_semis "def" optional_template function_declaration  */
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

  case 319: /* optional_public_or_private_function: %empty  */
                        { (yyval.b) = yyextra->g_thisStructure ? !yyextra->g_thisStructure->privateStructure : yyextra->g_Program->thisModule->isPublic; }
    break;

  case 320: /* optional_public_or_private_function: "private"  */
                        { (yyval.b) = false; }
    break;

  case 321: /* optional_public_or_private_function: "public"  */
                        { (yyval.b) = true; }
    break;

  case 322: /* function_declaration_header: function_name optional_function_argument_list optional_function_type  */
                                                                                                {
        (yyval.pFuncDecl) = ast_functionDeclarationHeader(scanner,(yyvsp[-2].s),(yyvsp[-1].pVarDeclList),(yyvsp[0].pTypeDecl),tokAt(scanner,(yylsp[-2])));
    }
    break;

  case 323: /* $@16: %empty  */
                                                     {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeFunction(tak);
        }
    }
    break;

  case 324: /* function_declaration: optional_public_or_private_function $@16 function_declaration_header optional_emit_semis block_or_simple_block  */
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

  case 325: /* expression_block_finally: %empty  */
        {
        (yyval.pExpression) = nullptr;
    }
    break;

  case 326: /* $@17: %empty  */
                  {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 327: /* $@18: %empty  */
                             {
        yyextra->pop_nesteds();
    }
    break;

  case 328: /* expression_block_finally: "finally" $@17 '{' expressions $@18 '}'  */
          {
        (yyval.pExpression) = (yyvsp[-2].pExpression);
    }
    break;

  case 329: /* $@19: %empty  */
                     {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 330: /* $@20: %empty  */
                         {
        yyextra->pop_nesteds();
    }
    break;

  case 331: /* expression_block: '{' $@19 expressions $@20 '}' expression_block_finally  */
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

  case 332: /* expr_call_pipe_no_bracket: expr_call expr_full_block_assumed_piped  */
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

  case 333: /* expr_call_pipe_no_bracket: expr_method_call_no_bracket expr_full_block_assumed_piped  */
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

  case 334: /* expr_call_pipe_no_bracket: expr_field_no_bracket expr_full_block_assumed_piped  */
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

  case 335: /* expr_call_pipe_no_bracket: expr_named_call expr_full_block_assumed_piped  */
                                                                 {
        // free-function named call + piped block: pad-aware resolution lands it on the block param
        auto nc = (ExprNamedCall *) (yyvsp[-1].pExpression);
        nc->nonNamedArguments.push_back((yyvsp[0].pExpression));
        nc->pipedCallArgument = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 336: /* expression_any: SEMICOLON  */
                                                  { (yyval.pExpression) = nullptr; }
    break;

  case 337: /* expression_any: expr_assign_no_bracket SEMICOLON  */
                                                    { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 338: /* expression_any: expression_delete SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 339: /* expression_any: expression_let  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 340: /* expression_any: expression_while_loop  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 341: /* expression_any: expression_unsafe  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 342: /* expression_any: expression_with  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 343: /* expression_any: expression_with_alias SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 344: /* expression_any: expression_for_loop  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 345: /* expression_any: expression_break SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 346: /* expression_any: expression_continue SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 347: /* expression_any: expression_return SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 348: /* expression_any: expression_yield SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 349: /* expression_any: expression_if_then_else  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 350: /* expression_any: expression_if_then_else_oneliner  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 351: /* expression_any: expression_try_catch  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 352: /* expression_any: expression_label SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 353: /* expression_any: expression_goto SEMICOLON  */
                                                  { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 354: /* expression_any: "pass" SEMICOLON  */
                                                  { (yyval.pExpression) = nullptr; }
    break;

  case 355: /* $@21: %empty  */
                     {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 356: /* $@22: %empty  */
                         {
        yyextra->pop_nesteds();
    }
    break;

  case 357: /* expression_any: '{' $@21 expressions $@22 '}' expression_block_finally  */
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

  case 358: /* expressions: %empty  */
        {
        (yyval.pExpression) = new ExprBlock();
        (yyval.pExpression)->at = LineInfo(yyextra->g_FileAccessStack.back(),
            yylloc.first_column,yylloc.first_line,yylloc.last_column,yylloc.last_line);
    }
    break;

  case 359: /* expressions: expressions expression_any  */
                                                        {
        (yyval.pExpression) = (yyvsp[-1].pExpression);
        if ( (yyvsp[0].pExpression) ) {
            static_cast<ExprBlock*>((yyvsp[-1].pExpression))->list.push_back((yyvsp[0].pExpression));
        }
    }
    break;

  case 360: /* expressions: expressions error  */
                                 {
        (void)(yyvsp[-1].pExpression); /* gc_node — don't delete Expression */ (yyval.pExpression) = nullptr; YYABORT;
    }
    break;

  case 361: /* optional_expr_list: %empty  */
        { (yyval.pExpression) = nullptr; }
    break;

  case 362: /* optional_expr_list: expr_list optional_comma  */
                                            { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 363: /* optional_expr_map_tuple_list: %empty  */
        { (yyval.pExpression) = nullptr; }
    break;

  case 364: /* optional_expr_map_tuple_list: expr_map_tuple_list optional_comma  */
                                                      { (yyval.pExpression) = (yyvsp[-1].pExpression); }
    break;

  case 365: /* type_declaration_no_options_list: type_declaration  */
                               {
        (yyval.pTypeDeclList) = new vector<Expression *>();
        (yyval.pTypeDeclList)->push_back(new ExprTypeDecl(tokAt(scanner,(yylsp[0])),(yyvsp[0].pTypeDecl)));
    }
    break;

  case 366: /* type_declaration_no_options_list: type_declaration_no_options_list c_or_s type_declaration  */
                                                                              {
        (yyval.pTypeDeclList) = (yyvsp[-2].pTypeDeclList);
        (yyval.pTypeDeclList)->push_back(new ExprTypeDecl(tokAt(scanner,(yylsp[0])),(yyvsp[0].pTypeDecl)));
    }
    break;

  case 367: /* name_in_namespace: "name"  */
                                               { (yyval.s) = (yyvsp[0].s); }
    break;

  case 368: /* name_in_namespace: "name" "::" "name"  */
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

  case 369: /* name_in_namespace: "::" "name"  */
                                               { *(yyvsp[0].s) = "::" + *(yyvsp[0].s); (yyval.s) = (yyvsp[0].s); }
    break;

  case 370: /* expression_delete: "delete" expr  */
                                      {
        (yyval.pExpression) = new ExprDelete(tokAt(scanner,(yylsp[-1])), (yyvsp[0].pExpression));
    }
    break;

  case 371: /* expression_delete: "delete" "explicit" expr  */
                                                   {
        auto delExpr = new ExprDelete(tokAt(scanner,(yylsp[-2])), (yyvsp[0].pExpression));
        delExpr->native = true;
        (yyval.pExpression) = delExpr;
    }
    break;

  case 372: /* $@23: %empty  */
           { yyextra->das_arrow_depth ++; }
    break;

  case 373: /* $@24: %empty  */
                                                                           { yyextra->das_arrow_depth --; }
    break;

  case 374: /* new_type_declaration: '<' $@23 type_declaration '>' $@24  */
                                                                                                            {
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 375: /* new_type_declaration: structure_type_declaration  */
                                               {
        (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl);
    }
    break;

  case 376: /* expr_new: "new" new_type_declaration  */
                                                       {
        (yyval.pExpression) = new ExprNew(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pTypeDecl),false);
    }
    break;

  case 377: /* expr_new: "new" new_type_declaration '(' use_initializer ')'  */
                                                                                     {
        (yyval.pExpression) = new ExprNew(tokAt(scanner,(yylsp[-4])),(yyvsp[-3].pTypeDecl),true);
        ((ExprNew *)(yyval.pExpression))->initializer = (yyvsp[-1].b);
    }
    break;

  case 378: /* expr_new: "new" new_type_declaration '(' expr_list ')'  */
                                                                                    {
        auto pNew = new ExprNew(tokAt(scanner,(yylsp[-4])),(yyvsp[-3].pTypeDecl),true);
        (yyval.pExpression) = parseFunctionArguments(pNew,(yyvsp[-1].pExpression));
    }
    break;

  case 379: /* expr_new: "new" new_type_declaration '(' make_struct_single ')'  */
                                                                                      {
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->at = tokAt(scanner,(yylsp[-3]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-3].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = true; // $init;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
        (yyval.pExpression) = new ExprAscend(tokAt(scanner,(yylsp[-4])),(yyvsp[-1].pExpression));
    }
    break;

  case 380: /* expr_new: "new" new_type_declaration '(' "uninitialized" make_struct_single ')'  */
                                                                                                        {
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->at = tokAt(scanner,(yylsp[-4]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-4].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = false; // $init;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
        (yyval.pExpression) = new ExprAscend(tokAt(scanner,(yylsp[-5])),(yyvsp[-1].pExpression));
    }
    break;

  case 381: /* expr_new: "new" make_decl  */
                                    {
        (yyval.pExpression) = new ExprAscend(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression));
    }
    break;

  case 382: /* expression_break: "break"  */
                       { (yyval.pExpression) = new ExprBreak(tokAt(scanner,(yylsp[0]))); }
    break;

  case 383: /* expression_continue: "continue"  */
                          { (yyval.pExpression) = new ExprContinue(tokAt(scanner,(yylsp[0]))); }
    break;

  case 384: /* expression_return: "return"  */
                        {
        (yyval.pExpression) = new ExprReturn(tokAt(scanner,(yylsp[0])),nullptr);
    }
    break;

  case 385: /* expression_return: "return" expr  */
                                      {
        (yyval.pExpression) = new ExprReturn(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression));
    }
    break;

  case 386: /* expression_return: "return" "<-" expr  */
                                             {
        auto pRet = new ExprReturn(tokAt(scanner,(yylsp[-2])),(yyvsp[0].pExpression));
        pRet->moveSemantics = true;
        (yyval.pExpression) = pRet;
    }
    break;

  case 387: /* expression_yield: "yield" expr  */
                                     {
        (yyval.pExpression) = new ExprYield(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression));
    }
    break;

  case 388: /* expression_yield: "yield" "<-" expr  */
                                            {
        auto pRet = new ExprYield(tokAt(scanner,(yylsp[-2])),(yyvsp[0].pExpression));
        pRet->moveSemantics = true;
        (yyval.pExpression) = pRet;
    }
    break;

  case 389: /* expression_try_catch: "try" expression_block "recover" expression_block  */
                                                                                       {
        (yyval.pExpression) = new ExprTryCatch(tokAt(scanner,(yylsp[-3])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
    }
    break;

  case 390: /* kwd_let_var_or_nothing: "let"  */
                 { (yyval.b) = true; }
    break;

  case 391: /* kwd_let_var_or_nothing: "var"  */
                 { (yyval.b) = false; }
    break;

  case 392: /* kwd_let_var_or_nothing: %empty  */
                    { (yyval.b) = true; }
    break;

  case 393: /* kwd_let: "let"  */
                 { (yyval.b) = true; }
    break;

  case 394: /* kwd_let: "var"  */
                 { (yyval.b) = false; }
    break;

  case 395: /* optional_in_scope: "inscope"  */
                    { (yyval.b) = true; }
    break;

  case 396: /* optional_in_scope: %empty  */
                     { (yyval.b) = false; }
    break;

  case 397: /* tuple_expansion: "name"  */
                    {
        (yyval.pNameList) = new vector<string>();
        (yyval.pNameList)->push_back(*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 398: /* tuple_expansion: tuple_expansion ',' "name"  */
                                             {
        (yyvsp[-2].pNameList)->push_back(*(yyvsp[0].s));
        delete (yyvsp[0].s);
        (yyval.pNameList) = (yyvsp[-2].pNameList);
    }
    break;

  case 399: /* tuple_expansion_variable_declaration: '(' tuple_expansion ')' ':' type_declaration_no_options copy_or_move_or_clone expr SEMICOLON  */
                                                                                                                                {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-6].pNameList),tokAt(scanner,(yylsp[-6])),(yyvsp[-3].pTypeDecl),(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
        (yyval.pVarDecl)->isTupleExpansion = true;
        (yyval.pVarDecl)->atEnd = tokAt(scanner,(yylsp[-1]));
    }
    break;

  case 400: /* tuple_expansion_variable_declaration: '(' tuple_expansion ')' optional_ref copy_or_move_or_clone expr SEMICOLON  */
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

  case 401: /* expression_let: kwd_let optional_in_scope let_variable_declaration  */
                                                                 {
        (yyval.pExpression) = ast_Let(scanner,(yyvsp[-2].b),(yyvsp[-1].b),(yyvsp[0].pVarDecl),tokAt(scanner,(yylsp[-2])),tokAt(scanner,(yylsp[0])));
    }
    break;

  case 402: /* expression_let: kwd_let optional_in_scope tuple_expansion_variable_declaration  */
                                                                             {
        (yyval.pExpression) = ast_Let(scanner,(yyvsp[-2].b),(yyvsp[-1].b),(yyvsp[0].pVarDecl),tokAt(scanner,(yylsp[-2])),tokAt(scanner,(yylsp[0])));
    }
    break;

  case 403: /* expression_let: kwd_let optional_in_scope '{' variable_declaration_list '}'  */
                                                                               {
        (yyval.pExpression) = ast_LetList(scanner,(yyvsp[-4].b),(yyvsp[-3].b),*(yyvsp[-1].pVarDeclList),tokAt(scanner,(yylsp[-4])),tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 404: /* $@25: %empty  */
                          { yyextra->das_arrow_depth ++; }
    break;

  case 405: /* $@26: %empty  */
                                                                                                 { yyextra->das_arrow_depth --; }
    break;

  case 406: /* expr_cast: "cast" '<' $@25 type_declaration_no_options '>' $@26 '(' expr ')'  */
                                                                                                                                                        {
        (yyval.pExpression) = new ExprCast(tokAt(scanner,(yylsp[-8])),(yyvsp[-1].pExpression),(yyvsp[-5].pTypeDecl));
    }
    break;

  case 407: /* $@27: %empty  */
                            { yyextra->das_arrow_depth ++; }
    break;

  case 408: /* $@28: %empty  */
                                                                                                   { yyextra->das_arrow_depth --; }
    break;

  case 409: /* expr_cast: "upcast" '<' $@27 type_declaration_no_options '>' $@28 '(' expr ')'  */
                                                                                                                                                          {
        auto pCast = new ExprCast(tokAt(scanner,(yylsp[-8])),(yyvsp[-1].pExpression),(yyvsp[-5].pTypeDecl));
        pCast->upcast = true;
        (yyval.pExpression) = pCast;
    }
    break;

  case 410: /* $@29: %empty  */
                                 { yyextra->das_arrow_depth ++; }
    break;

  case 411: /* $@30: %empty  */
                                                                                                        { yyextra->das_arrow_depth --; }
    break;

  case 412: /* expr_cast: "reinterpret" '<' $@29 type_declaration_no_options '>' $@30 '(' expr ')'  */
                                                                                                                                                               {
        auto pCast = new ExprCast(tokAt(scanner,(yylsp[-8])),(yyvsp[-1].pExpression),(yyvsp[-5].pTypeDecl));
        pCast->reinterpret = true;
        (yyval.pExpression) = pCast;
    }
    break;

  case 413: /* $@31: %empty  */
                         { yyextra->das_arrow_depth ++; }
    break;

  case 414: /* $@32: %empty  */
                                                                                     { yyextra->das_arrow_depth --; }
    break;

  case 415: /* expr_type_decl: "type" '<' $@31 type_declaration '>' $@32  */
                                                                                                                      {
        (yyval.pExpression) = new ExprTypeDecl(tokAt(scanner,(yylsp[-5])),(yyvsp[-2].pTypeDecl));
    }
    break;

  case 416: /* expr_type_info: "typeinfo" name_in_namespace '(' expr ')'  */
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

  case 417: /* expr_type_info: "typeinfo" name_in_namespace '<' "name" '>' '(' expr ')'  */
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

  case 418: /* expr_type_info: "typeinfo" name_in_namespace '<' "name" c_or_s "name" '>' '(' expr ')'  */
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

  case 419: /* expr_list: expr  */
                      {
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 420: /* expr_list: "<-" expr  */
                             {
            (yyval.pExpression) = ast_makeMoveArgument(scanner, (yyvsp[0].pExpression), tokAt(scanner,(yylsp[0])));
    }
    break;

  case 421: /* expr_list: expr_list ',' expr  */
                                        {
            (yyval.pExpression) = new ExprSequence(tokAt(scanner,(yylsp[-2])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
    }
    break;

  case 422: /* expr_list: expr_list ',' "<-" expr  */
                                                   {
            (yyval.pExpression) = new ExprSequence(tokAt(scanner,(yylsp[-3])),(yyvsp[-3].pExpression),ast_makeMoveArgument(scanner, (yyvsp[0].pExpression), tokAt(scanner,(yylsp[0]))));
    }
    break;

  case 423: /* block_or_simple_block: expression_block  */
                                    { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 424: /* block_or_simple_block: "=>" expr_no_bracket  */
                                                   {
            auto retE = new ExprReturn(tokAt(scanner,(yylsp[-1])), (yyvsp[0].pExpression));
            auto blkE = new ExprBlock();
            blkE->at = tokAt(scanner,(yylsp[-1]));
            blkE->list.push_back(retE);
            (yyval.pExpression) = blkE;
    }
    break;

  case 425: /* block_or_simple_block: "=>" "<-" expr_no_bracket  */
                                                          {
            auto retE = new ExprReturn(tokAt(scanner,(yylsp[-2])), (yyvsp[0].pExpression));
            retE->moveSemantics = true;
            auto blkE = new ExprBlock();
            blkE->at = tokAt(scanner,(yylsp[-2]));
            blkE->list.push_back(retE);
            (yyval.pExpression) = blkE;
    }
    break;

  case 426: /* block_or_lambda: '$'  */
                { (yyval.i) = 0;   /* block */  }
    break;

  case 427: /* block_or_lambda: '@'  */
                { (yyval.i) = 1;   /* lambda */ }
    break;

  case 428: /* block_or_lambda: "@@"  */
                  { (yyval.i) = 2;   /* local function */ }
    break;

  case 429: /* capture_entry: '&' "name"  */
                                    { (yyval.pCapt) = new CaptureEntry(*(yyvsp[0].s),CaptureMode::capture_by_reference); delete (yyvsp[0].s); }
    break;

  case 430: /* capture_entry: '=' "name"  */
                                    { (yyval.pCapt) = new CaptureEntry(*(yyvsp[0].s),CaptureMode::capture_by_copy); delete (yyvsp[0].s); }
    break;

  case 431: /* capture_entry: "<-" "name"  */
                                    { (yyval.pCapt) = new CaptureEntry(*(yyvsp[0].s),CaptureMode::capture_by_move); delete (yyvsp[0].s); }
    break;

  case 432: /* capture_entry: ":=" "name"  */
                                    { (yyval.pCapt) = new CaptureEntry(*(yyvsp[0].s),CaptureMode::capture_by_clone); delete (yyvsp[0].s); }
    break;

  case 433: /* capture_entry: "name" '(' "name" ')'  */
                                    { (yyval.pCapt) = ast_makeCaptureEntry(scanner,tokAt(scanner,(yylsp[-3])),*(yyvsp[-3].s),*(yyvsp[-1].s)); delete (yyvsp[-3].s); delete (yyvsp[-1].s); }
    break;

  case 434: /* capture_list: capture_entry  */
                         {
        (yyval.pCaptList) = new vector<CaptureEntry>();
        (yyval.pCaptList)->push_back(*(yyvsp[0].pCapt));
        delete (yyvsp[0].pCapt);
    }
    break;

  case 435: /* capture_list: capture_list ',' capture_entry  */
                                               {
        (yyvsp[-2].pCaptList)->push_back(*(yyvsp[0].pCapt));
        delete (yyvsp[0].pCapt);
        (yyval.pCaptList) = (yyvsp[-2].pCaptList);
    }
    break;

  case 436: /* optional_capture_list: %empty  */
        { (yyval.pCaptList) = nullptr; }
    break;

  case 437: /* optional_capture_list: "capture" '(' capture_list ')'  */
                                             { (yyval.pCaptList) = (yyvsp[-1].pCaptList); }
    break;

  case 438: /* expr_full_block: block_or_lambda optional_annotation_list optional_capture_list optional_function_argument_list optional_function_type optional_emit_semis block_or_simple_block  */
                                                                                                                {
        (yyval.pExpression) = ast_makeBlock(scanner,(yyvsp[-6].i),(yyvsp[-5].faList),(yyvsp[-4].pCaptList),(yyvsp[-3].pVarDeclList),(yyvsp[-2].pTypeDecl),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[0])),tokAt(scanner,(yylsp[-5])),tokAt(scanner,(yylsp[-4])));
    }
    break;

  case 439: /* expr_full_block_assumed_piped: block_or_lambda optional_annotation_list optional_capture_list optional_function_argument_list optional_function_type optional_emit_semis block_or_simple_block  */
                                                                                                                {
        (yyval.pExpression) = ast_makeBlock(scanner,(yyvsp[-6].i),(yyvsp[-5].faList),(yyvsp[-4].pCaptList),(yyvsp[-3].pVarDeclList),(yyvsp[-2].pTypeDecl),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[0])),tokAt(scanner,(yylsp[-5])),tokAt(scanner,(yylsp[-4])));
    }
    break;

  case 440: /* expr_full_block_assumed_piped: '{' expressions '}'  */
                                   {
        // block span is brace-to-brace (@$), not the statements' span (@block)
        (yyval.pExpression) = ast_makeBlock(scanner,0,nullptr,nullptr,nullptr,new TypeDecl(Type::autoinfer),(yyvsp[-1].pExpression),tokAt(scanner,(yyloc)),tokAt(scanner,(yyloc)),LineInfo());
    }
    break;

  case 441: /* expr_numeric_const: "integer constant"  */
                                              { (yyval.pExpression) = new ExprConstInt(tokAt(scanner,(yylsp[0])),(int32_t)(yyvsp[0].i)); }
    break;

  case 442: /* expr_numeric_const: "unsigned integer constant"  */
                                              { (yyval.pExpression) = new ExprConstUInt(tokAt(scanner,(yylsp[0])),(uint32_t)(yyvsp[0].ui)); }
    break;

  case 443: /* expr_numeric_const: "long integer constant"  */
                                              { (yyval.pExpression) = new ExprConstInt64(tokAt(scanner,(yylsp[0])),(int64_t)(yyvsp[0].i64)); }
    break;

  case 444: /* expr_numeric_const: "unsigned long integer constant"  */
                                              { (yyval.pExpression) = new ExprConstUInt64(tokAt(scanner,(yylsp[0])),(uint64_t)(yyvsp[0].ui64)); }
    break;

  case 445: /* expr_numeric_const: "unsigned int8 constant"  */
                                              { (yyval.pExpression) = new ExprConstUInt8(tokAt(scanner,(yylsp[0])),(uint8_t)(yyvsp[0].ui)); }
    break;

  case 446: /* expr_numeric_const: "floating point constant"  */
                                              { (yyval.pExpression) = new ExprConstFloat(tokAt(scanner,(yylsp[0])),(float)(yyvsp[0].fd)); }
    break;

  case 447: /* expr_numeric_const: "float16 constant"  */
                                              { (yyval.pExpression) = new ExprConstFloat16(tokAt(scanner,(yylsp[0])),(float)(yyvsp[0].fd)); }
    break;

  case 448: /* expr_numeric_const: "double constant"  */
                                              { (yyval.pExpression) = new ExprConstDouble(tokAt(scanner,(yylsp[0])),(double)(yyvsp[0].d)); }
    break;

  case 449: /* expr_assign_no_bracket: expr_no_bracket  */
                                                        { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 450: /* expr_assign_no_bracket: expr_no_bracket '=' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprCopy(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression)); }
    break;

  case 451: /* expr_assign_no_bracket: expr_no_bracket "<-" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprMove(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 452: /* expr_assign_no_bracket: expr_no_bracket "<-" make_table_decl  */
                                                                   { (yyval.pExpression) = new ExprMove(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 453: /* expr_assign_no_bracket: expr_no_bracket "<-" array_comprehension  */
                                                                     { (yyval.pExpression) = new ExprMove(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 454: /* expr_assign_no_bracket: expr_no_bracket ":=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprClone(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 455: /* expr_assign_no_bracket: expr_no_bracket "&=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"&=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 456: /* expr_assign_no_bracket: expr_no_bracket "|=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"|=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 457: /* expr_assign_no_bracket: expr_no_bracket "^=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"^=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 458: /* expr_assign_no_bracket: expr_no_bracket "&&=" expr_no_bracket  */
                                                                      { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"&&=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 459: /* expr_assign_no_bracket: expr_no_bracket "||=" expr_no_bracket  */
                                                                      { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"||=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 460: /* expr_assign_no_bracket: expr_no_bracket "^^=" expr_no_bracket  */
                                                                      { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"^^=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 461: /* expr_assign_no_bracket: expr_no_bracket "+=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"+=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 462: /* expr_assign_no_bracket: expr_no_bracket "-=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"-=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 463: /* expr_assign_no_bracket: expr_no_bracket "*=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"*=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 464: /* expr_assign_no_bracket: expr_no_bracket "/=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"/=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 465: /* expr_assign_no_bracket: expr_no_bracket "%=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"%=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 466: /* expr_assign_no_bracket: expr_no_bracket "<<=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<<=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 467: /* expr_assign_no_bracket: expr_no_bracket ">>=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">>=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 468: /* expr_assign_no_bracket: expr_no_bracket "<<<=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<<<=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 469: /* expr_assign_no_bracket: expr_no_bracket ">>>=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">>>=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 470: /* expr_named_call: name_in_namespace '(' '[' make_struct_fields ']' ')'  */
                                                                         {
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-5])),*(yyvsp[-5].s));
        nc->arguments = (yyvsp[-2].pMakeStruct);
        delete (yyvsp[-5].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 471: /* expr_named_call: name_in_namespace '(' expr_list ',' '[' make_struct_fields ']' ')'  */
                                                                                                  {
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-7])),*(yyvsp[-7].s));
        nc->nonNamedArguments = sequenceToList((yyvsp[-5].pExpression));
        nc->arguments = (yyvsp[-2].pMakeStruct);
        delete (yyvsp[-7].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 472: /* expr_named_call: name_in_namespace '(' expr_list ',' make_struct_fields ')'  */
                                                                                          {
        // bracket-less mixed named call: foo(pos..., name = value) -- named args are a strict suffix
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-5])),*(yyvsp[-5].s));
        nc->nonNamedArguments = sequenceToList((yyvsp[-3].pExpression));
        nc->arguments = (yyvsp[-1].pMakeStruct);
        delete (yyvsp[-5].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 473: /* expr_method_call_no_bracket: expr_no_bracket "->" "name" '(' ')'  */
                                                                    {
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-3])), (yyvsp[-4].pExpression), *(yyvsp[-2].s));
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-4]),(yyloc));
        delete (yyvsp[-2].s);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 474: /* expr_method_call_no_bracket: expr_no_bracket "->" "name" '(' expr_list ')'  */
                                                                                         {
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-4])), (yyvsp[-5].pExpression), *(yyvsp[-3].s));
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-5]),(yyloc));
        auto callArgs = sequenceToList((yyvsp[-1].pExpression));
        pInvoke->arguments.insert ( pInvoke->arguments.end(), callArgs.begin(), callArgs.end() );
        delete (yyvsp[-3].s);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 475: /* expr_method_call_no_bracket: expr_no_bracket "->" "name" '(' '[' make_struct_fields ']' ')'  */
                                                                                                     {
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-5])),*(yyvsp[-5].s));
        nc->methodCall = true;
        nc->arguments = (yyvsp[-2].pMakeStruct);
        nc->nonNamedArguments.push_back((yyvsp[-7].pExpression));
        delete (yyvsp[-5].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 476: /* expr_method_call_no_bracket: expr_no_bracket "->" "name" '(' expr_list ',' make_struct_fields ')'  */
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

  case 477: /* expr_method_call_no_bracket: expr_no_bracket "->" "name" '(' make_struct_fields ')'  */
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

  case 478: /* func_addr_name: name_in_namespace  */
                                    {
        (yyval.pExpression) = new ExprAddr(tokAt(scanner,(yylsp[0])),*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 479: /* func_addr_name: "$i" '(' expr ')'  */
                                          {
        auto expr = new ExprAddr(tokAt(scanner,(yylsp[-3])),"``MACRO``TAG``ADDR``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression), expr, "i");
    }
    break;

  case 480: /* func_addr_expr: "@@" func_addr_name  */
                                            {
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 481: /* $@33: %empty  */
                      { yyextra->das_arrow_depth ++; }
    break;

  case 482: /* $@34: %empty  */
                                                                                                  { yyextra->das_arrow_depth --; }
    break;

  case 483: /* func_addr_expr: "@@" '<' $@33 type_declaration_no_options '>' $@34 func_addr_name  */
                                                                                                                                                         {
        auto expr = (ExprAddr *) ((yyvsp[0].pExpression)->rtti_isAddr() ? (yyvsp[0].pExpression) : (((ExprTag *) (yyvsp[0].pExpression))->value));
        expr->funcType = (yyvsp[-3].pTypeDecl);
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 484: /* $@35: %empty  */
                      { yyextra->das_arrow_depth ++; }
    break;

  case 485: /* $@36: %empty  */
                                                                                                                                { yyextra->das_arrow_depth --; }
    break;

  case 486: /* func_addr_expr: "@@" '<' $@35 optional_function_argument_list optional_function_type '>' $@36 func_addr_name  */
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

  case 487: /* expr_field_no_bracket: expr_no_bracket '.' "name"  */
                                                         {
        (yyval.pExpression) = new ExprField(tokAt(scanner,(yylsp[-1])), tokAt(scanner,(yylsp[0])), (yyvsp[-2].pExpression), *(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 488: /* expr_field_no_bracket: expr_no_bracket '.' '.' "name"  */
                                                             {
        (yyval.pExpression) = new ExprField(tokAt(scanner,(yylsp[-1])), tokAt(scanner,(yylsp[0])), (yyvsp[-3].pExpression), *(yyvsp[0].s), true);
        delete (yyvsp[0].s);
    }
    break;

  case 489: /* expr_field_no_bracket: expr_no_bracket '.' "name" '(' ')'  */
                                                                 {
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-3])), (yyvsp[-4].pExpression), *(yyvsp[-2].s));
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-4]),(yyloc));
        delete (yyvsp[-2].s);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 490: /* expr_field_no_bracket: expr_no_bracket '.' "name" '(' expr_list ')'  */
                                                                                      {
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-4])), (yyvsp[-5].pExpression), *(yyvsp[-3].s));
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-5]),(yyloc));
        auto callArgs = sequenceToList((yyvsp[-1].pExpression));
        pInvoke->arguments.insert ( pInvoke->arguments.end(), callArgs.begin(), callArgs.end() );
        delete (yyvsp[-3].s);
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 491: /* expr_field_no_bracket: expr_no_bracket '.' "name" '(' '[' make_struct_fields ']' ')'  */
                                                                                                  {
        auto nc = new ExprNamedCall(tokAt(scanner,(yylsp[-5])),*(yyvsp[-5].s));
        nc->methodCall = true;
        nc->arguments = (yyvsp[-2].pMakeStruct);
        nc->nonNamedArguments.push_back((yyvsp[-7].pExpression));
        delete (yyvsp[-5].s);
        (yyval.pExpression) = nc;
    }
    break;

  case 492: /* expr_field_no_bracket: expr_no_bracket '.' "name" '(' expr_list ',' make_struct_fields ')'  */
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

  case 493: /* expr_field_no_bracket: expr_no_bracket '.' "name" '(' make_struct_fields ')'  */
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

  case 494: /* expr_field_no_bracket: expr_no_bracket '.' basic_type_declaration '(' ')'  */
                                                                                   {
        auto method_name = das_to_string((yyvsp[-2].type));
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-3])), (yyvsp[-4].pExpression), method_name);
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-4]),(yyloc));
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 495: /* expr_field_no_bracket: expr_no_bracket '.' basic_type_declaration '(' expr_list ')'  */
                                                                                                        {
        auto method_name = das_to_string((yyvsp[-3].type));
        auto pInvoke = makeInvokeMethod(tokAt(scanner,(yylsp[-4])), (yyvsp[-5].pExpression), method_name);
        pInvoke->atEnclosure = tokRangeAt(scanner,(yylsp[-5]),(yyloc));
        auto callArgs = sequenceToList((yyvsp[-1].pExpression));
        pInvoke->arguments.insert ( pInvoke->arguments.end(), callArgs.begin(), callArgs.end() );
        (yyval.pExpression) = pInvoke;
    }
    break;

  case 496: /* $@37: %empty  */
                                          { yyextra->das_suppress_errors=true; }
    break;

  case 497: /* $@38: %empty  */
                                                                                       { yyextra->das_suppress_errors=false; }
    break;

  case 498: /* expr_field_no_bracket: expr_no_bracket '.' $@37 error $@38  */
                                                                                                                               {
        (yyval.pExpression) = new ExprField(tokAt(scanner,(yylsp[-3])), tokAt(scanner,(yylsp[-3])), (yyvsp[-4].pExpression), "");
        yyerrok;
    }
    break;

  case 499: /* expr_call: name_in_namespace '(' ')'  */
                                               {
            (yyval.pExpression) = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-2])),tokAt(scanner,(yylsp[0])),*(yyvsp[-2].s));
            delete (yyvsp[-2].s);
    }
    break;

  case 500: /* expr_call: name_in_namespace '(' "uninitialized" ')'  */
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

  case 501: /* expr_call: name_in_namespace '(' make_struct_single ')'  */
                                                               {
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->at = tokAt(scanner,(yylsp[-3]));
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = yyextra->g_Program->makeTypeDeclaration(tokAt(scanner,(yylsp[-3])),*(yyvsp[-3].s));
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = true;
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
            delete (yyvsp[-3].s);
            (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 502: /* expr_call: name_in_namespace '(' "uninitialized" make_struct_single ')'  */
                                                                                 {
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->at = tokAt(scanner,(yylsp[-4]));
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = yyextra->g_Program->makeTypeDeclaration(tokAt(scanner,(yylsp[-4])),*(yyvsp[-4].s));
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = false;
            ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
            delete (yyvsp[-4].s);
            (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 503: /* expr_call: name_in_namespace '(' expr_list ')'  */
                                                                    {
            (yyval.pExpression) = parseFunctionArguments(yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-3])),tokAt(scanner,(yylsp[0])),*(yyvsp[-3].s)),(yyvsp[-1].pExpression));
            delete (yyvsp[-3].s);
    }
    break;

  case 504: /* expr_call: basic_type_declaration '(' ')'  */
                                                    {
        (yyval.pExpression) = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-2])),tokAt(scanner,(yylsp[0])),das_to_string((yyvsp[-2].type)));
    }
    break;

  case 505: /* expr_call: basic_type_declaration '(' expr_list ')'  */
                                                                         {
        (yyval.pExpression) = parseFunctionArguments(yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-3])),tokAt(scanner,(yylsp[0])),das_to_string((yyvsp[-3].type))),(yyvsp[-1].pExpression));
    }
    break;

  case 506: /* expr: expr_no_bracket  */
                                       { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 507: /* expr: make_table_decl  */
                                     { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 508: /* expr: array_comprehension  */
                                     { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 509: /* expr_no_bracket: "null"  */
                                              { (yyval.pExpression) = new ExprConstPtr(tokAt(scanner,(yylsp[0])),nullptr); }
    break;

  case 510: /* expr_no_bracket: name_in_namespace  */
                                              { (yyval.pExpression) = new ExprVar(tokAt(scanner,(yylsp[0])),*(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 511: /* expr_no_bracket: expr_numeric_const  */
                                              { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 512: /* expr_no_bracket: expr_reader  */
                                              { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 513: /* expr_no_bracket: string_builder  */
                                              { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 514: /* expr_no_bracket: make_decl_no_bracket  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 515: /* expr_no_bracket: "true"  */
                                              { (yyval.pExpression) = new ExprConstBool(tokAt(scanner,(yylsp[0])),true); }
    break;

  case 516: /* expr_no_bracket: "false"  */
                                              { (yyval.pExpression) = new ExprConstBool(tokAt(scanner,(yylsp[0])),false); }
    break;

  case 517: /* expr_no_bracket: expr_field_no_bracket  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 518: /* expr_no_bracket: expr_mtag_no_bracket  */
                                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 519: /* expr_no_bracket: '!' expr_no_bracket  */
                                                         { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"!",(yyvsp[0].pExpression)); }
    break;

  case 520: /* expr_no_bracket: '~' expr_no_bracket  */
                                                         { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"~",(yyvsp[0].pExpression)); }
    break;

  case 521: /* expr_no_bracket: '+' expr_no_bracket  */
                                                             { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"+",(yyvsp[0].pExpression)); }
    break;

  case 522: /* expr_no_bracket: '-' expr_no_bracket  */
                                                             { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"-",(yyvsp[0].pExpression)); }
    break;

  case 523: /* expr_no_bracket: expr_no_bracket "<<" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<<", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 524: /* expr_no_bracket: expr_no_bracket ">>" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">>", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 525: /* expr_no_bracket: expr_no_bracket "<<<" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<<<", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 526: /* expr_no_bracket: expr_no_bracket ">>>" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">>>", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 527: /* expr_no_bracket: expr_no_bracket '+' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"+", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 528: /* expr_no_bracket: expr_no_bracket '-' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"-", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 529: /* expr_no_bracket: expr_no_bracket '*' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"*", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 530: /* expr_no_bracket: expr_no_bracket '/' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"/", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 531: /* expr_no_bracket: expr_no_bracket '%' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"%", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 532: /* expr_no_bracket: expr_no_bracket '<' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 533: /* expr_no_bracket: expr_no_bracket '>' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 534: /* expr_no_bracket: expr_no_bracket "==" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"==", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 535: /* expr_no_bracket: expr_no_bracket "!=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"!=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 536: /* expr_no_bracket: expr_no_bracket "<=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"<=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 537: /* expr_no_bracket: expr_no_bracket ">=" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),">=", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 538: /* expr_no_bracket: expr_no_bracket '&' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"&", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 539: /* expr_no_bracket: expr_no_bracket '|' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"|", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 540: /* expr_no_bracket: expr_no_bracket '^' expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"^", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 541: /* expr_no_bracket: expr_no_bracket "&&" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"&&", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 542: /* expr_no_bracket: expr_no_bracket "||" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"||", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 543: /* expr_no_bracket: expr_no_bracket "^^" expr_no_bracket  */
                                                                   { (yyval.pExpression) = new ExprOp2(tokAt(scanner,(yylsp[-1])),"^^", (yyvsp[-2].pExpression), (yyvsp[0].pExpression)); }
    break;

  case 544: /* expr_no_bracket: expr_no_bracket ".." expr_no_bracket  */
                                                                   {
        auto itv = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-1])),"interval");
        itv->arguments.push_back((yyvsp[-2].pExpression));
        itv->arguments.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = itv;
    }
    break;

  case 545: /* expr_no_bracket: "++" expr_no_bracket  */
                                                            { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"++", (yyvsp[0].pExpression)); }
    break;

  case 546: /* expr_no_bracket: "--" expr_no_bracket  */
                                                            { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[-1])),"--", (yyvsp[0].pExpression)); }
    break;

  case 547: /* expr_no_bracket: expr_no_bracket "++"  */
                                                            { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[0])),"+++", (yyvsp[-1].pExpression)); }
    break;

  case 548: /* expr_no_bracket: expr_no_bracket "--"  */
                                                            { (yyval.pExpression) = new ExprOp1(tokAt(scanner,(yylsp[0])),"---", (yyvsp[-1].pExpression)); }
    break;

  case 549: /* expr_no_bracket: '(' expr_list optional_comma ')'  */
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

  case 550: /* expr_no_bracket: '(' make_struct_single ')'  */
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

  case 551: /* expr_no_bracket: expr_no_bracket '[' expr ']'  */
                                                            { (yyval.pExpression) = new ExprAt(tokAt(scanner,(yylsp[-2])), (yyvsp[-3].pExpression), (yyvsp[-1].pExpression)); }
    break;

  case 552: /* expr_no_bracket: expr_no_bracket '.' '[' expr ']'  */
                                                                { (yyval.pExpression) = new ExprAt(tokAt(scanner,(yylsp[-2])), (yyvsp[-4].pExpression), (yyvsp[-1].pExpression), true); }
    break;

  case 553: /* expr_no_bracket: expr_no_bracket "?[" expr ']'  */
                                                            { (yyval.pExpression) = new ExprSafeAt(tokAt(scanner,(yylsp[-2])), (yyvsp[-3].pExpression), (yyvsp[-1].pExpression)); }
    break;

  case 554: /* expr_no_bracket: expr_no_bracket '.' "?[" expr ']'  */
                                                                { (yyval.pExpression) = new ExprSafeAt(tokAt(scanner,(yylsp[-2])), (yyvsp[-4].pExpression), (yyvsp[-1].pExpression), true); }
    break;

  case 555: /* expr_no_bracket: expr_no_bracket "?." "name"  */
                                                            { (yyval.pExpression) = new ExprSafeField(tokAt(scanner,(yylsp[-1])), tokAt(scanner,(yylsp[0])), (yyvsp[-2].pExpression), *(yyvsp[0].s)); delete (yyvsp[0].s); }
    break;

  case 556: /* expr_no_bracket: expr_no_bracket '.' "?." "name"  */
                                                                { (yyval.pExpression) = new ExprSafeField(tokAt(scanner,(yylsp[-1])), tokAt(scanner,(yylsp[0])), (yyvsp[-3].pExpression), *(yyvsp[0].s), true); delete (yyvsp[0].s); }
    break;

  case 557: /* expr_no_bracket: func_addr_expr  */
                                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 558: /* expr_no_bracket: expr_call  */
                        { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 559: /* expr_no_bracket: '*' expr_no_bracket  */
                                                              { (yyval.pExpression) = new ExprPtr2Ref(tokAt(scanner,(yylsp[-1])),(yyvsp[0].pExpression)); }
    break;

  case 560: /* expr_no_bracket: "deref" '(' expr ')'  */
                                                   { (yyval.pExpression) = new ExprPtr2Ref(tokAt(scanner,(yylsp[-3])),(yyvsp[-1].pExpression)); }
    break;

  case 561: /* expr_no_bracket: "addr" '(' expr ')'  */
                                                   { (yyval.pExpression) = new ExprRef2Ptr(tokAt(scanner,(yylsp[-3])),(yyvsp[-1].pExpression)); }
    break;

  case 562: /* expr_no_bracket: expr_generator  */
                                                   { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 563: /* expr_no_bracket: expr_no_bracket "??" expr_no_bracket  */
                                                                         { (yyval.pExpression) = new ExprNullCoalescing(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression)); }
    break;

  case 564: /* expr_no_bracket: expr_no_bracket '?' expr_no_bracket ':' expr_no_bracket  */
                                                                                           {
            (yyval.pExpression) = new ExprOp3(tokAt(scanner,(yylsp[-3])),"?",(yyvsp[-4].pExpression),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
        }
    break;

  case 565: /* $@39: %empty  */
                                                          { yyextra->das_arrow_depth ++; }
    break;

  case 566: /* $@40: %empty  */
                                                                                                                                 { yyextra->das_arrow_depth --; }
    break;

  case 567: /* expr_no_bracket: expr_no_bracket "is" "type" '<' $@39 type_declaration_no_options '>' $@40  */
                                                                                                                                                                  {
        (yyval.pExpression) = new ExprIs(tokAt(scanner,(yylsp[-6])),(yyvsp[-7].pExpression),(yyvsp[-2].pTypeDecl));
    }
    break;

  case 568: /* expr_no_bracket: expr_no_bracket "is" basic_type_declaration  */
                                                                          {
        auto vdecl = new TypeDecl((yyvsp[0].type));
        vdecl->at = tokAt(scanner,(yylsp[0]));
        (yyval.pExpression) = new ExprIs(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),vdecl);
    }
    break;

  case 569: /* expr_no_bracket: expr_no_bracket "is" "name"  */
                                                         {
        (yyval.pExpression) = new ExprIsVariant(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 570: /* expr_no_bracket: expr_no_bracket "as" "name"  */
                                                         {
        (yyval.pExpression) = new ExprAsVariant(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 571: /* $@41: %empty  */
                                                          { yyextra->das_arrow_depth ++; }
    break;

  case 572: /* $@42: %empty  */
                                                                                                                      { yyextra->das_arrow_depth --; }
    break;

  case 573: /* expr_no_bracket: expr_no_bracket "as" "type" '<' $@41 type_declaration '>' $@42  */
                                                                                                                                                       {
        auto vname = (yyvsp[-2].pTypeDecl)->describe();
        (yyval.pExpression) = new ExprAsVariant(tokAt(scanner,(yylsp[-6])),(yyvsp[-7].pExpression),vname);
        delete (yyvsp[-2].pTypeDecl);
    }
    break;

  case 574: /* expr_no_bracket: expr_no_bracket "as" basic_type_declaration  */
                                                                          {
        (yyval.pExpression) = new ExprAsVariant(tokAt(scanner,(yylsp[-1])),(yyvsp[-2].pExpression),das_to_string((yyvsp[0].type)));
    }
    break;

  case 575: /* expr_no_bracket: expr_no_bracket '?' "as" "name"  */
                                                             {
        (yyval.pExpression) = new ExprSafeAsVariant(tokAt(scanner,(yylsp[-1])),(yyvsp[-3].pExpression),*(yyvsp[0].s));
        delete (yyvsp[0].s);
    }
    break;

  case 576: /* $@43: %empty  */
                                                              { yyextra->das_arrow_depth ++; }
    break;

  case 577: /* $@44: %empty  */
                                                                                                                          { yyextra->das_arrow_depth --; }
    break;

  case 578: /* expr_no_bracket: expr_no_bracket '?' "as" "type" '<' $@43 type_declaration '>' $@44  */
                                                                                                                                                           {
        auto vname = (yyvsp[-2].pTypeDecl)->describe();
        (yyval.pExpression) = new ExprSafeAsVariant(tokAt(scanner,(yylsp[-6])),(yyvsp[-8].pExpression),vname);
        delete (yyvsp[-2].pTypeDecl);
    }
    break;

  case 579: /* expr_no_bracket: expr_no_bracket '?' "as" basic_type_declaration  */
                                                                              {
        (yyval.pExpression) = new ExprSafeAsVariant(tokAt(scanner,(yylsp[-1])),(yyvsp[-3].pExpression),das_to_string((yyvsp[0].type)));
    }
    break;

  case 580: /* expr_no_bracket: expr_type_info  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 581: /* expr_no_bracket: expr_type_decl  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 582: /* expr_no_bracket: expr_cast  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 583: /* expr_no_bracket: expr_new  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 584: /* expr_no_bracket: expr_method_call_no_bracket  */
                                                  { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 585: /* expr_no_bracket: expr_named_call  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 586: /* expr_no_bracket: expr_full_block  */
                                                { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 587: /* expr_no_bracket: expr_no_bracket "<|" expr_no_bracket  */
                                                                      { (yyval.pExpression) = ast_lpipe(scanner,(yyvsp[-2].pExpression),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[-1])),true); }
    break;

  case 588: /* expr_no_bracket: expr_no_bracket "|>" expr_no_bracket  */
                                                                      { (yyval.pExpression) = ast_rpipe(scanner,(yyvsp[-2].pExpression),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[-1]))); }
    break;

  case 589: /* expr_no_bracket: expr_no_bracket "|>" basic_type_declaration  */
                                                                     {
        auto fncall = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[0])),tokAt(scanner,(yylsp[0])),das_to_string((yyvsp[0].type)));
        (yyval.pExpression) = ast_rpipe(scanner,(yyvsp[-2].pExpression),fncall,tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 590: /* expr_no_bracket: expr_call_pipe_no_bracket  */
                                        { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 591: /* expr_no_bracket: "unsafe" '(' expr ')'  */
                                         {
            (yyvsp[-1].pExpression)->alwaysSafe = true;
            (yyvsp[-1].pExpression)->userSaidItsSafe = true;
            (yyval.pExpression) = (yyvsp[-1].pExpression);
        }
    break;

  case 592: /* expr_no_bracket: expr_no_bracket "=>" expr_no_bracket  */
                                                               {
        ExprMakeTuple * mt = new ExprMakeTuple(tokAt(scanner,(yylsp[-1])));
        mt->values.push_back((yyvsp[-2].pExpression));
        mt->values.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = mt;
    }
    break;

  case 593: /* expr_no_bracket: expr_no_bracket "=>" make_table_decl  */
                                                               {
        ExprMakeTuple * mt = new ExprMakeTuple(tokAt(scanner,(yylsp[-1])));
        mt->values.push_back((yyvsp[-2].pExpression));
        mt->values.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = mt;
    }
    break;

  case 594: /* expr_no_bracket: expr_no_bracket "=>" array_comprehension  */
                                                                   {
        ExprMakeTuple * mt = new ExprMakeTuple(tokAt(scanner,(yylsp[-1])));
        mt->values.push_back((yyvsp[-2].pExpression));
        mt->values.push_back((yyvsp[0].pExpression));
        (yyval.pExpression) = mt;
    }
    break;

  case 595: /* expr_generator: "generator" '<' type_declaration_no_options '>' optional_capture_list '(' ')'  */
                                                                                                              {
        (yyval.pExpression) = ast_makeGenerator(scanner,(yyvsp[-4].pTypeDecl),(yyvsp[-2].pCaptList),nullptr,tokAt(scanner,(yylsp[-6])),tokAt(scanner,(yylsp[-2])));
    }
    break;

  case 596: /* expr_generator: "generator" '<' type_declaration_no_options '>' optional_capture_list '(' expr ')'  */
                                                                                                                            {
        (yyval.pExpression) = ast_makeGenerator(scanner,(yyvsp[-5].pTypeDecl),(yyvsp[-3].pCaptList),(yyvsp[-1].pExpression),tokAt(scanner,(yylsp[-7])),tokAt(scanner,(yylsp[-3])));
    }
    break;

  case 597: /* expr_generator: "generator" '<' type_declaration_no_options '>' optional_capture_list optional_emit_semis expression_block  */
                                                                                                                                                  {
        auto closure = new ExprMakeBlock(tokAt(scanner,(yylsp[0])),(yyvsp[0].pExpression));
        ((ExprBlock *)(yyvsp[0].pExpression))->returnType = new TypeDecl(Type::autoinfer);
        (yyval.pExpression) = ast_makeGenerator(scanner,(yyvsp[-4].pTypeDecl),(yyvsp[-2].pCaptList),closure,tokAt(scanner,(yylsp[-6])),tokAt(scanner,(yylsp[-2])));
    }
    break;

  case 598: /* expr_mtag_no_bracket: "$$" '(' expr ')'  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"e"); }
    break;

  case 599: /* expr_mtag_no_bracket: "$i" '(' expr ')'  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"i"); }
    break;

  case 600: /* expr_mtag_no_bracket: "$v" '(' expr ')'  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"v"); }
    break;

  case 601: /* expr_mtag_no_bracket: "$b" '(' expr ')'  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"b"); }
    break;

  case 602: /* expr_mtag_no_bracket: "$a" '(' expr ')'  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),"a"); }
    break;

  case 603: /* expr_mtag_no_bracket: "..."  */
                                                     { (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[0])),nullptr,"..."); }
    break;

  case 604: /* expr_mtag_no_bracket: "$c" '(' expr ')' '(' ')'  */
                                                            {
            auto ccall = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-5])),tokAt(scanner,(yylsp[0])),"``MACRO``TAG``CALL``");
            (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-5])),(yyvsp[-3].pExpression),ccall,"c");
        }
    break;

  case 605: /* expr_mtag_no_bracket: "$c" '(' expr ')' '(' expr_list ')'  */
                                                                                {
            auto ccall = parseFunctionArguments(yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-6])),tokAt(scanner,(yylsp[0])),"``MACRO``TAG``CALL``"),(yyvsp[-1].pExpression));
            (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-6])),(yyvsp[-4].pExpression),ccall,"c");
        }
    break;

  case 606: /* expr_mtag_no_bracket: expr_no_bracket '.' "$f" '(' expr ')'  */
                                                                           {
        auto cfield = new ExprField(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-1])), (yyvsp[-5].pExpression), "``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 607: /* expr_mtag_no_bracket: expr_no_bracket "?." "$f" '(' expr ')'  */
                                                                            {
        auto cfield = new ExprSafeField(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-1])), (yyvsp[-5].pExpression), "``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 608: /* expr_mtag_no_bracket: expr_no_bracket '.' '.' "$f" '(' expr ')'  */
                                                                               {
        auto cfield = new ExprField(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-1])), (yyvsp[-6].pExpression), "``MACRO``TAG``FIELD``", true);
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 609: /* expr_mtag_no_bracket: expr_no_bracket '.' "?." "$f" '(' expr ')'  */
                                                                                {
        auto cfield = new ExprSafeField(tokAt(scanner,(yylsp[-4])), tokAt(scanner,(yylsp[-1])), (yyvsp[-6].pExpression), "``MACRO``TAG``FIELD``", true);
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 610: /* expr_mtag_no_bracket: expr_no_bracket "as" "$f" '(' expr ')'  */
                                                                              {
        auto cfield = new ExprAsVariant(tokAt(scanner,(yylsp[-4])),(yyvsp[-5].pExpression),"``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 611: /* expr_mtag_no_bracket: expr_no_bracket '?' "as" "$f" '(' expr ')'  */
                                                                                  {
        auto cfield = new ExprSafeAsVariant(tokAt(scanner,(yylsp[-4])),(yyvsp[-6].pExpression),"``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 612: /* expr_mtag_no_bracket: expr_no_bracket "is" "$f" '(' expr ')'  */
                                                                              {
        auto cfield = new ExprIsVariant(tokAt(scanner,(yylsp[-4])),(yyvsp[-5].pExpression),"``MACRO``TAG``FIELD``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression),cfield,"f");
    }
    break;

  case 613: /* expr_mtag_no_bracket: "@@" "$c" '(' expr ')'  */
                                                           {
        auto ccall = new ExprAddr(tokAt(scanner,(yylsp[-4])),"``MACRO``TAG``ADDR``");
        (yyval.pExpression) = new ExprTag(tokAt(scanner,(yylsp[-3])),(yyvsp[-1].pExpression),ccall,"c");
    }
    break;

  case 614: /* optional_field_annotation: %empty  */
                                      { (yyval.aaList) = nullptr; }
    break;

  case 615: /* optional_field_annotation: metadata_argument_list  */
                                      { (yyval.aaList) = (yyvsp[0].aaList); }
    break;

  case 616: /* optional_override: %empty  */
                      { (yyval.i) = OVERRIDE_NONE; }
    break;

  case 617: /* optional_override: "override"  */
                      { (yyval.i) = OVERRIDE_OVERRIDE; }
    break;

  case 618: /* optional_override: "sealed"  */
                      { (yyval.i) = OVERRIDE_SEALED; }
    break;

  case 619: /* optional_constant: %empty  */
                        { (yyval.b) = false; }
    break;

  case 620: /* optional_constant: "const"  */
                        { (yyval.b) = true; }
    break;

  case 621: /* optional_public_or_private_member_variable: %empty  */
                        { (yyval.b) = false; }
    break;

  case 622: /* optional_public_or_private_member_variable: "public"  */
                        { (yyval.b) = false; }
    break;

  case 623: /* optional_public_or_private_member_variable: "private"  */
                        { (yyval.b) = true; }
    break;

  case 624: /* optional_static_member_variable: %empty  */
                        { (yyval.b) = false; }
    break;

  case 625: /* optional_static_member_variable: "static"  */
                        { (yyval.b) = true; }
    break;

  case 626: /* structure_variable_declaration: optional_field_annotation optional_static_member_variable optional_override optional_public_or_private_member_variable variable_declaration  */
                                                                                                                                                                                      {
        (yyvsp[0].pVarDecl)->override = (yyvsp[-2].i) == OVERRIDE_OVERRIDE;
        (yyvsp[0].pVarDecl)->sealed = (yyvsp[-2].i) == OVERRIDE_SEALED;
        (yyvsp[0].pVarDecl)->annotation = (yyvsp[-4].aaList);
        (yyvsp[0].pVarDecl)->isPrivate = (yyvsp[-1].b);
        (yyvsp[0].pVarDecl)->isStatic = (yyvsp[-3].b);
        (yyval.pVarDecl) = (yyvsp[0].pVarDecl);
    }
    break;

  case 627: /* struct_variable_declaration_list: %empty  */
        {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 628: /* struct_variable_declaration_list: struct_variable_declaration_list "new line, semicolon"  */
                                                                 { (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList); }
    break;

  case 629: /* struct_variable_declaration_list: struct_variable_declaration_list "typedef" "name" '=' type_declaration SEMICOLON  */
                                                                                                                {
        (yyval.pVarDeclList) = (yyvsp[-5].pVarDeclList);
        ast_structureAlias(scanner,(yyvsp[-3].s),(yyvsp[-1].pTypeDecl),tokAt(scanner,(yylsp[-4])));
    }
    break;

  case 630: /* $@45: %empty  */
                                               {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeStructureFields(tak);
        }
    }
    break;

  case 631: /* struct_variable_declaration_list: struct_variable_declaration_list $@45 structure_variable_declaration SEMICOLON  */
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

  case 632: /* $@46: %empty  */
                                                                                                                     {
                if ( !yyextra->g_CommentReaders.empty() ) {
                    auto tak = tokAt(scanner,(yylsp[-2]));
                    for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeFunction(tak);
                }
            }
    break;

  case 633: /* struct_variable_declaration_list: struct_variable_declaration_list optional_annotation_list_with_emit_semis "def" optional_public_or_private_member_variable "abstract" optional_constant $@46 function_declaration_header SEMICOLON  */
                                                          {
                if ( !yyextra->g_CommentReaders.empty() ) {
                    auto tak = tokAt(scanner,(yylsp[-1]));
                    for ( auto & crd : yyextra->g_CommentReaders ) crd->afterFunction((yyvsp[-1].pFuncDecl),tak);
                }
                (yyvsp[-1].pFuncDecl)->isTemplate = yyextra->g_thisStructure ? yyextra->g_thisStructure->isTemplate : false;
                (yyval.pVarDeclList) = ast_structVarDefAbstract(scanner,(yyvsp[-8].pVarDeclList),(yyvsp[-7].faList),(yyvsp[-5].b),(yyvsp[-3].b), (yyvsp[-1].pFuncDecl));
            }
    break;

  case 634: /* $@47: %empty  */
                                                                                                                                                                         {
                if ( !yyextra->g_CommentReaders.empty() ) {
                    auto tak = tokAt(scanner,(yylsp[0]));
                    for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeFunction(tak);
                }
            }
    break;

  case 635: /* struct_variable_declaration_list: struct_variable_declaration_list optional_annotation_list_with_emit_semis "def" optional_public_or_private_member_variable optional_static_member_variable optional_override optional_constant $@47 function_declaration_header optional_emit_semis block_or_simple_block  */
                                                                                                 {
                if ( !yyextra->g_CommentReaders.empty() ) {
                    auto tak = tokAt(scanner,(yylsp[0]));
                    for ( auto & crd : yyextra->g_CommentReaders ) crd->afterFunction((yyvsp[-2].pFuncDecl),tak);
                }
                (yyvsp[-2].pFuncDecl)->isTemplate = yyextra->g_thisStructure ? yyextra->g_thisStructure->isTemplate : false;
                (yyval.pVarDeclList) = ast_structVarDef(scanner,(yyvsp[-10].pVarDeclList),(yyvsp[-9].faList),(yyvsp[-6].b),(yyvsp[-7].b),(yyvsp[-5].i),(yyvsp[-4].b),(yyvsp[-2].pFuncDecl),(yyvsp[0].pExpression),tokRangeAt(scanner,(yylsp[-8]),(yylsp[0])),tokAt(scanner,(yylsp[-9])));
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

  case 638: /* function_argument_declaration_type: "$a" '(' expr ')'  */
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

  case 641: /* function_argument_list: function_argument_declaration_no_type ';' function_argument_list  */
                                                                                      { (yyval.pVarDeclList) = (yyvsp[0].pVarDeclList); (yyvsp[0].pVarDeclList)->insert((yyvsp[0].pVarDeclList)->begin(),(yyvsp[-2].pVarDecl)); }
    break;

  case 642: /* function_argument_list: function_argument_declaration_type ';' function_argument_list  */
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

  case 649: /* tuple_alias_type_list: tuple_type  */
                       {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
        (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl));
    }
    break;

  case 650: /* tuple_alias_type_list: tuple_alias_type_list semis tuple_type  */
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

  case 655: /* variant_alias_type_list: variant_type  */
                         {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
        (yyval.pVarDeclList)->push_back((yyvsp[0].pVarDecl));
    }
    break;

  case 656: /* variant_alias_type_list: variant_alias_type_list semis variant_type  */
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

  case 672: /* let_variable_name_with_pos_list: "$i" '(' expr ')'  */
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

  case 675: /* let_variable_name_with_pos_list: let_variable_name_with_pos_list ',' "$i" '(' expr ')'  */
                                                                               {
        (yyvsp[-5].pNameWithPosList)->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = (yyvsp[-5].pNameWithPosList);
    }
    break;

  case 676: /* let_variable_name_with_pos_list: let_variable_name_with_pos_list ',' "name" "aka" "name"  */
                                                                                   {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-4].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[-2].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-2]))));
        (yyval.pNameWithPosList) = (yyvsp[-4].pNameWithPosList);
        delete (yyvsp[-2].s);
        delete (yyvsp[0].s);
    }
    break;

  case 677: /* global_let_variable_name_with_pos_list: "name"  */
                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = pSL;
        delete (yyvsp[0].s);
    }
    break;

  case 678: /* global_let_variable_name_with_pos_list: global_let_variable_name_with_pos_list ',' "name"  */
                                                                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = (yyvsp[-2].pNameWithPosList);
        delete (yyvsp[0].s);
    }
    break;

  case 679: /* variable_declaration_list: %empty  */
        {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 680: /* variable_declaration_list: variable_declaration_list SEMICOLON  */
                                                  {
        (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList);
    }
    break;

  case 681: /* variable_declaration_list: variable_declaration_list let_variable_declaration  */
                                                                       {
        (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList);
        (yyvsp[-1].pVarDeclList)->push_back((yyvsp[0].pVarDecl));
    }
    break;

  case 682: /* let_variable_declaration: let_variable_name_with_pos_list ':' type_declaration_no_options SEMICOLON  */
                                                                                                  {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-3].pNameWithPosList),(yyvsp[-1].pTypeDecl),nullptr);
        (yyval.pVarDecl)->atEnd = tokAt(scanner,(yylsp[-1]));
    }
    break;

  case 683: /* let_variable_declaration: let_variable_name_with_pos_list ':' type_declaration_no_options copy_or_move_or_clone expr SEMICOLON  */
                                                                                                                                        {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-5].pNameWithPosList),(yyvsp[-3].pTypeDecl),(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
        (yyval.pVarDecl)->atEnd = tokAt(scanner,(yylsp[-1]));
    }
    break;

  case 684: /* let_variable_declaration: let_variable_name_with_pos_list optional_ref copy_or_move_or_clone expr SEMICOLON  */
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

  case 685: /* global_let_variable_declaration: global_let_variable_name_with_pos_list ':' type_declaration_no_options SEMICOLON  */
                                                                                                         {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-3].pNameWithPosList),(yyvsp[-1].pTypeDecl),nullptr);
    }
    break;

  case 686: /* global_let_variable_declaration: global_let_variable_name_with_pos_list ':' type_declaration_no_options copy_or_move_or_clone expr SEMICOLON  */
                                                                                                                                               {
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-5].pNameWithPosList),(yyvsp[-3].pTypeDecl),(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
    }
    break;

  case 687: /* global_let_variable_declaration: global_let_variable_name_with_pos_list optional_ref copy_or_move_or_clone expr SEMICOLON  */
                                                                                                                       {
        auto typeDecl = new TypeDecl(Type::autoinfer);
        typeDecl->at = tokAt(scanner,(yylsp[-4]));
        typeDecl->ref = (yyvsp[-3].b);
        (yyval.pVarDecl) = new VariableDeclaration((yyvsp[-4].pNameWithPosList),typeDecl,(yyvsp[-1].pExpression));
        (yyval.pVarDecl)->init_via_move  = ((yyvsp[-2].i) & CorM_MOVE) !=0;
        (yyval.pVarDecl)->init_via_clone = ((yyvsp[-2].i) & CorM_CLONE) !=0;
    }
    break;

  case 688: /* optional_shared: %empty  */
                     { (yyval.b) = false; }
    break;

  case 689: /* optional_shared: "shared"  */
                     { (yyval.b) = true; }
    break;

  case 690: /* optional_public_or_private_variable: %empty  */
                     { (yyval.b) = yyextra->g_Program->thisModule->isPublic; }
    break;

  case 691: /* optional_public_or_private_variable: "private"  */
                     { (yyval.b) = false; }
    break;

  case 692: /* optional_public_or_private_variable: "public"  */
                     { (yyval.b) = true; }
    break;

  case 693: /* global_variable_declaration_list: %empty  */
        {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 694: /* global_variable_declaration_list: global_variable_declaration_list SEMICOLON  */
                                                         {
        (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList);
    }
    break;

  case 695: /* $@48: %empty  */
                                               {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeGlobalVariables(tak);
        }
    }
    break;

  case 696: /* global_variable_declaration_list: global_variable_declaration_list $@48 optional_field_annotation let_variable_declaration  */
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

  case 697: /* global_let: kwd_let optional_shared optional_public_or_private_variable '{' global_variable_declaration_list '}'  */
                                                                                                                                       {
        ast_globalLetList(scanner,(yyvsp[-5].b),(yyvsp[-4].b),(yyvsp[-3].b),(yyvsp[-1].pVarDeclList));
    }
    break;

  case 698: /* $@49: %empty  */
                                                                                        {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeGlobalVariables(tak);
        }
    }
    break;

  case 699: /* global_let: kwd_let optional_shared optional_public_or_private_variable $@49 optional_field_annotation global_let_variable_declaration  */
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

  case 700: /* enum_expression: "name"  */
                   {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyval.pEnumPair) = new EnumPair((yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        delete (yyvsp[0].s);
    }
    break;

  case 701: /* enum_expression: "name" '=' expr  */
                                   {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        (yyval.pEnumPair) = new EnumPair((yyvsp[-2].s),(yyvsp[0].pExpression),tokAt(scanner,(yylsp[-2])));
        delete (yyvsp[-2].s);
    }
    break;

  case 704: /* enum_list: %empty  */
        {
        (yyval.pEnumList) = new Enumeration();
    }
    break;

  case 705: /* enum_list: enum_expression  */
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

  case 706: /* enum_list: enum_list commas enum_expression  */
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

  case 707: /* optional_public_or_private_alias: %empty  */
                     { (yyval.b) = yyextra->g_Program->thisModule->isPublic; }
    break;

  case 708: /* optional_public_or_private_alias: "private"  */
                     { (yyval.b) = false; }
    break;

  case 709: /* optional_public_or_private_alias: "public"  */
                     { (yyval.b) = true; }
    break;

  case 710: /* $@50: %empty  */
                                                         {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto pubename = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeAlias(pubename);
        }
    }
    break;

  case 711: /* single_alias: optional_public_or_private_alias "name" $@50 '=' type_declaration  */
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

  case 714: /* distinct_alias: optional_public_or_private_alias "name" "name" '=' type_declaration  */
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

  case 715: /* optional_public_or_private_enum: %empty  */
                     { (yyval.b) = yyextra->g_Program->thisModule->isPublic; }
    break;

  case 716: /* optional_public_or_private_enum: "private"  */
                     { (yyval.b) = false; }
    break;

  case 717: /* optional_public_or_private_enum: "public"  */
                     { (yyval.b) = true; }
    break;

  case 718: /* enum_name: "name"  */
                   {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto pubename = tokAt(scanner,(yylsp[0]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeEnumeration(pubename);
        }
        (yyval.pEnum) = ast_addEmptyEnum(scanner, (yyvsp[0].s), tokAt(scanner,(yylsp[0])));
    }
    break;

  case 719: /* optional_enum_basic_type_declaration: %empty  */
        {
        (yyval.type) = Type::tInt;
    }
    break;

  case 720: /* optional_enum_basic_type_declaration: ':' enum_basic_type_declaration  */
                                              {
        (yyval.type) = (yyvsp[0].type);
    }
    break;

  case 727: /* $@51: %empty  */
                                                                     {
        yyextra->push_nesteds(DAS_EMIT_COMMA);
    }
    break;

  case 728: /* $@52: %empty  */
                                                                                                                                {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeEnumerationEntries(tak);
        }
    }
    break;

  case 729: /* $@53: %empty  */
                                    {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterEnumerationEntries(tak);
        }
        yyextra->pop_nesteds();
    }
    break;

  case 730: /* enum_declaration: optional_annotation_list_with_emit_semis "enum" $@51 optional_public_or_private_enum enum_name optional_enum_basic_type_declaration optional_emit_commas '{' $@52 enum_list optional_commas $@53 '}'  */
          {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto pubename = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterEnumeration((yyvsp[-8].pEnum)->name.c_str(),pubename);
        }
        ast_enumDeclaration(scanner,(yyvsp[-12].faList),tokAt(scanner,(yylsp[-12])),(yyvsp[-9].b),(yyvsp[-8].pEnum),(yyvsp[-3].pEnumList),(yyvsp[-7].type));
    }
    break;

  case 731: /* optional_structure_parent: %empty  */
                                        { (yyval.s) = nullptr; }
    break;

  case 732: /* optional_structure_parent: ':' name_in_namespace  */
                                        { (yyval.s) = (yyvsp[0].s); }
    break;

  case 733: /* optional_sealed: %empty  */
                        { (yyval.b) = false; }
    break;

  case 734: /* optional_sealed: "sealed"  */
                        { (yyval.b) = true; }
    break;

  case 735: /* structure_name: optional_sealed "name" optional_structure_parent  */
                                                                           {
        (yyval.pStructure) = ast_structureName(scanner,(yyvsp[-2].b),(yyvsp[-1].s),tokAt(scanner,(yylsp[-1])),(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
    }
    break;

  case 736: /* class_or_struct: "class"  */
                    { (yyval.i) = CorS_Class; }
    break;

  case 737: /* class_or_struct: "struct"  */
                    { (yyval.i) = CorS_Struct; }
    break;

  case 738: /* class_or_struct: "class" "template"  */
                                  { (yyval.i) = CorS_ClassTemplate; }
    break;

  case 739: /* class_or_struct: "struct" "template"  */
                                  { (yyval.i) = CorS_StructTemplate; }
    break;

  case 740: /* optional_public_or_private_structure: %empty  */
                     { (yyval.b) = yyextra->g_Program->thisModule->isPublic; }
    break;

  case 741: /* optional_public_or_private_structure: "private"  */
                     { (yyval.b) = false; }
    break;

  case 742: /* optional_public_or_private_structure: "public"  */
                     { (yyval.b) = true; }
    break;

  case 743: /* optional_struct_variable_declaration_list: ';'  */
            {
        (yyval.pVarDeclList) = new vector<VariableDeclaration*>();
    }
    break;

  case 744: /* optional_struct_variable_declaration_list: '{' struct_variable_declaration_list '}'  */
                                                       {
        (yyval.pVarDeclList) = (yyvsp[-1].pVarDeclList);
    }
    break;

  case 745: /* $@54: %empty  */
                                                     {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 746: /* $@55: %empty  */
                                                                         {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto tak = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeStructure(tak);
        }
    }
    break;

  case 747: /* $@56: %empty  */
                                             {
        if ( (yyvsp[-1].pStructure) ) {
            (yyvsp[-1].pStructure)->isClass = (yyvsp[-4].i)==CorS_Class || (yyvsp[-4].i)==CorS_ClassTemplate;
            (yyvsp[-1].pStructure)->isTemplate = (yyvsp[-4].i)==CorS_ClassTemplate || (yyvsp[-4].i)==CorS_StructTemplate;
            (yyvsp[-1].pStructure)->privateStructure = !(yyvsp[-3].b);
        }
    }
    break;

  case 748: /* structure_declaration: optional_annotation_list_with_emit_semis $@54 class_or_struct optional_public_or_private_structure $@55 structure_name optional_emit_semis $@56 optional_struct_variable_declaration_list  */
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

  case 749: /* variable_name_with_pos_list: "name"  */
                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = pSL;
        delete (yyvsp[0].s);
    }
    break;

  case 750: /* variable_name_with_pos_list: "$i" '(' expr ')'  */
                                     {
        auto pSL = new vector<VariableNameAndPosition>();
        pSL->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = pSL;
    }
    break;

  case 751: /* variable_name_with_pos_list: "name" "aka" "name"  */
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

  case 752: /* variable_name_with_pos_list: variable_name_with_pos_list ',' "name"  */
                                                         {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[0].s),"",tokAt(scanner,(yylsp[0]))));
        (yyval.pNameWithPosList) = (yyvsp[-2].pNameWithPosList);
        delete (yyvsp[0].s);
    }
    break;

  case 753: /* variable_name_with_pos_list: variable_name_with_pos_list ',' "$i" '(' expr ')'  */
                                                                           {
        (yyvsp[-5].pNameWithPosList)->push_back(VariableNameAndPosition("``MACRO``TAG``","",tokAt(scanner,(yylsp[-1])),(yyvsp[-1].pExpression)));
        (yyval.pNameWithPosList) = (yyvsp[-5].pNameWithPosList);
    }
    break;

  case 754: /* variable_name_with_pos_list: variable_name_with_pos_list ',' "name" "aka" "name"  */
                                                                               {
        das_checkName(scanner,*(yyvsp[-2].s),tokAt(scanner,(yylsp[-2])));
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-4].pNameWithPosList)->push_back(VariableNameAndPosition(*(yyvsp[-2].s),*(yyvsp[0].s),tokAt(scanner,(yylsp[-2]))));
        (yyval.pNameWithPosList) = (yyvsp[-4].pNameWithPosList);
        delete (yyvsp[-2].s);
        delete (yyvsp[0].s);
    }
    break;

  case 755: /* basic_type_declaration: "bool"  */
                        { (yyval.type) = Type::tBool; }
    break;

  case 756: /* basic_type_declaration: "string"  */
                        { (yyval.type) = Type::tString; }
    break;

  case 757: /* basic_type_declaration: "int"  */
                        { (yyval.type) = Type::tInt; }
    break;

  case 758: /* basic_type_declaration: "int8"  */
                        { (yyval.type) = Type::tInt8; }
    break;

  case 759: /* basic_type_declaration: "int16"  */
                        { (yyval.type) = Type::tInt16; }
    break;

  case 760: /* basic_type_declaration: "int64"  */
                        { (yyval.type) = Type::tInt64; }
    break;

  case 761: /* basic_type_declaration: "int2"  */
                        { (yyval.type) = Type::tInt2; }
    break;

  case 762: /* basic_type_declaration: "int3"  */
                        { (yyval.type) = Type::tInt3; }
    break;

  case 763: /* basic_type_declaration: "int4"  */
                        { (yyval.type) = Type::tInt4; }
    break;

  case 764: /* basic_type_declaration: "uint"  */
                        { (yyval.type) = Type::tUInt; }
    break;

  case 765: /* basic_type_declaration: "uint8"  */
                        { (yyval.type) = Type::tUInt8; }
    break;

  case 766: /* basic_type_declaration: "uint16"  */
                        { (yyval.type) = Type::tUInt16; }
    break;

  case 767: /* basic_type_declaration: "uint64"  */
                        { (yyval.type) = Type::tUInt64; }
    break;

  case 768: /* basic_type_declaration: "uint2"  */
                        { (yyval.type) = Type::tUInt2; }
    break;

  case 769: /* basic_type_declaration: "uint3"  */
                        { (yyval.type) = Type::tUInt3; }
    break;

  case 770: /* basic_type_declaration: "uint4"  */
                        { (yyval.type) = Type::tUInt4; }
    break;

  case 771: /* basic_type_declaration: "float"  */
                        { (yyval.type) = Type::tFloat; }
    break;

  case 772: /* basic_type_declaration: "float2"  */
                        { (yyval.type) = Type::tFloat2; }
    break;

  case 773: /* basic_type_declaration: "float3"  */
                        { (yyval.type) = Type::tFloat3; }
    break;

  case 774: /* basic_type_declaration: "float4"  */
                        { (yyval.type) = Type::tFloat4; }
    break;

  case 775: /* basic_type_declaration: "float16"  */
                        { (yyval.type) = Type::tFloat16; }
    break;

  case 776: /* basic_type_declaration: "half2"  */
                        { (yyval.type) = Type::tHalf2; }
    break;

  case 777: /* basic_type_declaration: "half3"  */
                        { (yyval.type) = Type::tHalf3; }
    break;

  case 778: /* basic_type_declaration: "half4"  */
                        { (yyval.type) = Type::tHalf4; }
    break;

  case 779: /* basic_type_declaration: "half8"  */
                        { (yyval.type) = Type::tHalf8; }
    break;

  case 780: /* basic_type_declaration: "short2"  */
                        { (yyval.type) = Type::tShort2; }
    break;

  case 781: /* basic_type_declaration: "short3"  */
                        { (yyval.type) = Type::tShort3; }
    break;

  case 782: /* basic_type_declaration: "short4"  */
                        { (yyval.type) = Type::tShort4; }
    break;

  case 783: /* basic_type_declaration: "short8"  */
                        { (yyval.type) = Type::tShort8; }
    break;

  case 784: /* basic_type_declaration: "ushort2"  */
                        { (yyval.type) = Type::tUShort2; }
    break;

  case 785: /* basic_type_declaration: "ushort3"  */
                        { (yyval.type) = Type::tUShort3; }
    break;

  case 786: /* basic_type_declaration: "ushort4"  */
                        { (yyval.type) = Type::tUShort4; }
    break;

  case 787: /* basic_type_declaration: "ushort8"  */
                        { (yyval.type) = Type::tUShort8; }
    break;

  case 788: /* basic_type_declaration: "byte2"  */
                        { (yyval.type) = Type::tByte2; }
    break;

  case 789: /* basic_type_declaration: "byte3"  */
                        { (yyval.type) = Type::tByte3; }
    break;

  case 790: /* basic_type_declaration: "byte4"  */
                        { (yyval.type) = Type::tByte4; }
    break;

  case 791: /* basic_type_declaration: "byte8"  */
                        { (yyval.type) = Type::tByte8; }
    break;

  case 792: /* basic_type_declaration: "byte16"  */
                        { (yyval.type) = Type::tByte16; }
    break;

  case 793: /* basic_type_declaration: "ubyte2"  */
                        { (yyval.type) = Type::tUByte2; }
    break;

  case 794: /* basic_type_declaration: "ubyte3"  */
                        { (yyval.type) = Type::tUByte3; }
    break;

  case 795: /* basic_type_declaration: "ubyte4"  */
                        { (yyval.type) = Type::tUByte4; }
    break;

  case 796: /* basic_type_declaration: "ubyte8"  */
                        { (yyval.type) = Type::tUByte8; }
    break;

  case 797: /* basic_type_declaration: "ubyte16"  */
                        { (yyval.type) = Type::tUByte16; }
    break;

  case 798: /* basic_type_declaration: "void"  */
                        { (yyval.type) = Type::tVoid; }
    break;

  case 799: /* basic_type_declaration: "range"  */
                        { (yyval.type) = Type::tRange; }
    break;

  case 800: /* basic_type_declaration: "urange"  */
                        { (yyval.type) = Type::tURange; }
    break;

  case 801: /* basic_type_declaration: "range64"  */
                        { (yyval.type) = Type::tRange64; }
    break;

  case 802: /* basic_type_declaration: "urange64"  */
                        { (yyval.type) = Type::tURange64; }
    break;

  case 803: /* basic_type_declaration: "double"  */
                        { (yyval.type) = Type::tDouble; }
    break;

  case 804: /* basic_type_declaration: "bitfield"  */
                        { (yyval.type) = Type::tBitfield; }
    break;

  case 805: /* enum_basic_type_declaration: "int"  */
                        { (yyval.type) = Type::tInt; }
    break;

  case 806: /* enum_basic_type_declaration: "int8"  */
                        { (yyval.type) = Type::tInt8; }
    break;

  case 807: /* enum_basic_type_declaration: "int16"  */
                        { (yyval.type) = Type::tInt16; }
    break;

  case 808: /* enum_basic_type_declaration: "uint"  */
                        { (yyval.type) = Type::tUInt; }
    break;

  case 809: /* enum_basic_type_declaration: "uint8"  */
                        { (yyval.type) = Type::tUInt8; }
    break;

  case 810: /* enum_basic_type_declaration: "uint16"  */
                        { (yyval.type) = Type::tUInt16; }
    break;

  case 811: /* enum_basic_type_declaration: "int64"  */
                        { (yyval.type) = Type::tInt64; }
    break;

  case 812: /* enum_basic_type_declaration: "uint64"  */
                        { (yyval.type) = Type::tUInt64; }
    break;

  case 813: /* structure_type_declaration: name_in_namespace  */
                                 {
        (yyval.pTypeDecl) = yyextra->g_Program->makeTypeDeclaration(tokAt(scanner,(yylsp[0])),*(yyvsp[0].s));
        if ( !(yyval.pTypeDecl) ) {
            (yyval.pTypeDecl) = new TypeDecl(Type::tVoid);
            (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
        }
        delete (yyvsp[0].s);
    }
    break;

  case 814: /* auto_type_declaration: "auto"  */
                       {
        (yyval.pTypeDecl) = new TypeDecl(Type::autoinfer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 815: /* auto_type_declaration: "auto" '(' "name" ')'  */
                                            {
        das_checkName(scanner,*(yyvsp[-1].s),tokAt(scanner,(yylsp[-1])));
        (yyval.pTypeDecl) = new TypeDecl(Type::autoinfer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-3]));
        (yyval.pTypeDecl)->alias = *(yyvsp[-1].s);
        delete (yyvsp[-1].s);
    }
    break;

  case 816: /* auto_type_declaration: "$t" '(' expr ')'  */
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

  case 817: /* bitfield_bits: "name"  */
                    {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        auto pSL = new vector<string>();
        pSL->push_back(*(yyvsp[0].s));
        (yyval.pNameList) = pSL;
        delete (yyvsp[0].s);
    }
    break;

  case 818: /* bitfield_bits: bitfield_bits ';' "name"  */
                                           {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameList)->push_back(*(yyvsp[0].s));
        (yyval.pNameList) = (yyvsp[-2].pNameList);
        delete (yyvsp[0].s);
    }
    break;

  case 819: /* bitfield_bits: bitfield_bits ',' "name"  */
                                           {
        das_checkName(scanner,*(yyvsp[0].s),tokAt(scanner,(yylsp[0])));
        (yyvsp[-2].pNameList)->push_back(*(yyvsp[0].s));
        (yyval.pNameList) = (yyvsp[-2].pNameList);
        delete (yyvsp[0].s);
    }
    break;

  case 820: /* bitfield_alias_bits: %empty  */
        {
        auto pSL = new vector<tuple<string,Expression *>>();
        (yyval.pNameExprList) = pSL;

    }
    break;

  case 821: /* bitfield_alias_bits: "name"  */
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

  case 822: /* bitfield_alias_bits: "name" '=' expr  */
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

  case 823: /* bitfield_alias_bits: bitfield_alias_bits commas "name"  */
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

  case 824: /* bitfield_alias_bits: bitfield_alias_bits commas "name" '=' expr  */
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

  case 825: /* bitfield_basic_type_declaration: %empty  */
                             { (yyval.type) = Type::tBitfield; }
    break;

  case 826: /* bitfield_basic_type_declaration: ':' "uint8"  */
                             { (yyval.type) = Type::tBitfield8; }
    break;

  case 827: /* bitfield_basic_type_declaration: ':' "uint16"  */
                             { (yyval.type) = Type::tBitfield16; }
    break;

  case 828: /* bitfield_basic_type_declaration: ':' "uint"  */
                             { (yyval.type) = Type::tBitfield; }
    break;

  case 829: /* bitfield_basic_type_declaration: ':' "uint64"  */
                             { (yyval.type) = Type::tBitfield64; }
    break;

  case 830: /* bitfield_type_declaration: "bitfield" bitfield_basic_type_declaration '<' '>'  */
                                                                          {
            (yyval.pTypeDecl) = new TypeDecl((yyvsp[-2].type));
            (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-2]));
    }
    break;

  case 831: /* $@57: %empty  */
                                                                     { yyextra->das_arrow_depth ++; }
    break;

  case 832: /* $@58: %empty  */
                                                                                                                            { yyextra->das_arrow_depth --; }
    break;

  case 833: /* bitfield_type_declaration: "bitfield" bitfield_basic_type_declaration '<' $@57 bitfield_bits '>' $@58  */
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

  case 836: /* table_type_pair: type_declaration  */
                                      {
        (yyval.aTypePair).firstType = (yyvsp[0].pTypeDecl);
        (yyval.aTypePair).secondType = new TypeDecl(Type::tVoid);
    }
    break;

  case 837: /* table_type_pair: type_declaration c_or_s type_declaration  */
                                                                             {
        (yyval.aTypePair).firstType = (yyvsp[-2].pTypeDecl);
        (yyval.aTypePair).secondType = (yyvsp[0].pTypeDecl);
    }
    break;

  case 838: /* dim_list: '[' expr ']'  */
                             {
        (yyval.pTypeDecl) = appendDimExpr(nullptr, (yyvsp[-1].pExpression), tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 839: /* dim_list: '[' ']'  */
                {
        (yyval.pTypeDecl) = appendDimExpr(nullptr, nullptr, tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 840: /* dim_list: dim_list '[' expr ']'  */
                                            {
        (yyval.pTypeDecl) = appendDimExpr((yyvsp[-3].pTypeDecl), (yyvsp[-1].pExpression), tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 841: /* dim_list: dim_list '[' ']'  */
                              {
        (yyval.pTypeDecl) = appendDimExpr((yyvsp[-2].pTypeDecl), nullptr, tokAt(scanner,(yylsp[-1])));
    }
    break;

  case 842: /* type_declaration_no_options: type_declaration_no_options_no_dim  */
                                                     {
        (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl);
    }
    break;

  case 843: /* type_declaration_no_options: type_declaration_no_options_no_dim dim_list  */
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

  case 844: /* optional_expr_list_in_braces: %empty  */
            { (yyval.pExpression) = nullptr; }
    break;

  case 845: /* optional_expr_list_in_braces: '(' expr_list optional_comma ')'  */
                                                { (yyval.pExpression) = (yyvsp[-2].pExpression); }
    break;

  case 846: /* type_declaration_no_options_no_dim: basic_type_declaration  */
                                                            { (yyval.pTypeDecl) = new TypeDecl((yyvsp[0].type)); (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0])); }
    break;

  case 847: /* type_declaration_no_options_no_dim: auto_type_declaration  */
                                                            { (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl); }
    break;

  case 848: /* type_declaration_no_options_no_dim: bitfield_type_declaration  */
                                                            { (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl); }
    break;

  case 849: /* type_declaration_no_options_no_dim: structure_type_declaration  */
                                                            { (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl); }
    break;

  case 850: /* $@59: %empty  */
                     { yyextra->das_arrow_depth ++; }
    break;

  case 851: /* $@60: %empty  */
                                                                                     { yyextra->das_arrow_depth --; }
    break;

  case 852: /* type_declaration_no_options_no_dim: "type" '<' $@59 type_declaration '>' $@60  */
                                                                                                                      {
        (yyvsp[-2].pTypeDecl)->autoToAlias = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 853: /* type_declaration_no_options_no_dim: "typedecl" '(' expr ')'  */
                                               {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeDecl);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-3]),(yylsp[-1]));
        (yyval.pTypeDecl)->typeMacroExpr.push_back((yyvsp[-1].pExpression));
    }
    break;

  case 854: /* type_declaration_no_options_no_dim: name_in_namespace '(' optional_expr_list ')'  */
                                                                      {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeMacro);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-3]), (yylsp[-1]));
        (yyval.pTypeDecl)->typeMacroExpr = sequenceToList((yyvsp[-1].pExpression));
        (yyval.pTypeDecl)->typeMacroExpr.insert((yyval.pTypeDecl)->typeMacroExpr.begin(), new ExprConstString(tokAt(scanner,(yylsp[-3])), *(yyvsp[-3].s)));
        delete (yyvsp[-3].s);
    }
    break;

  case 855: /* type_declaration_no_options_no_dim: '$' name_in_namespace optional_expr_list_in_braces  */
                                                                            {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeMacro);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-1]), (yylsp[0]));
        (yyval.pTypeDecl)->typeMacroExpr = sequenceToList((yyvsp[0].pExpression));
        (yyval.pTypeDecl)->typeMacroExpr.insert((yyval.pTypeDecl)->typeMacroExpr.begin(), new ExprConstString(tokAt(scanner,(yylsp[-1])), *(yyvsp[-1].s)));
        delete (yyvsp[-1].s);
    }
    break;

  case 856: /* $@61: %empty  */
                                    { yyextra->das_arrow_depth ++; }
    break;

  case 857: /* type_declaration_no_options_no_dim: name_in_namespace '<' $@61 type_declaration_no_options_list '>' optional_expr_list_in_braces  */
                                                                                                                                                         {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeMacro);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-5]), (yylsp[0]));
        (yyval.pTypeDecl)->typeMacroExpr = typesAndSequenceToList((yyvsp[-2].pTypeDeclList),(yyvsp[0].pExpression));
        (yyval.pTypeDecl)->typeMacroExpr.insert((yyval.pTypeDecl)->typeMacroExpr.begin(), new ExprConstString(tokAt(scanner,(yylsp[-5])), *(yyvsp[-5].s)));
        delete (yyvsp[-5].s);
    }
    break;

  case 858: /* $@62: %empty  */
                                        { yyextra->das_arrow_depth ++; }
    break;

  case 859: /* type_declaration_no_options_no_dim: '$' name_in_namespace '<' $@62 type_declaration_no_options_list '>' optional_expr_list_in_braces  */
                                                                                                                                                             {
        (yyval.pTypeDecl) = new TypeDecl(Type::typeMacro);
        (yyval.pTypeDecl)->at = tokRangeAt(scanner,(yylsp[-5]), (yylsp[0]));
        (yyval.pTypeDecl)->typeMacroExpr = typesAndSequenceToList((yyvsp[-2].pTypeDeclList),(yyvsp[0].pExpression));
        (yyval.pTypeDecl)->typeMacroExpr.insert((yyval.pTypeDecl)->typeMacroExpr.begin(), new ExprConstString(tokAt(scanner,(yylsp[-5])), *(yyvsp[-5].s)));
        delete (yyvsp[-5].s);
    }
    break;

  case 860: /* type_declaration_no_options_no_dim: type_declaration_no_options '-' '[' ']'  */
                                                          {
        (yyvsp[-3].pTypeDecl)->removeDim = true;
        (yyval.pTypeDecl) = (yyvsp[-3].pTypeDecl);
    }
    break;

  case 861: /* type_declaration_no_options_no_dim: type_declaration_no_options "explicit"  */
                                                           {
        (yyvsp[-1].pTypeDecl)->isExplicit = true;
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 862: /* type_declaration_no_options_no_dim: type_declaration_no_options "const"  */
                                                        {
        (yyvsp[-1].pTypeDecl)->constant = true;
        (yyvsp[-1].pTypeDecl)->removeConstant = false;
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 863: /* type_declaration_no_options_no_dim: type_declaration_no_options '-' "const"  */
                                                            {
        (yyvsp[-2].pTypeDecl)->constant = false;
        (yyvsp[-2].pTypeDecl)->removeConstant = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 864: /* type_declaration_no_options_no_dim: type_declaration_no_options '&'  */
                                                  {
        (yyvsp[-1].pTypeDecl)->ref = true;
        (yyvsp[-1].pTypeDecl)->removeRef = false;
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 865: /* type_declaration_no_options_no_dim: type_declaration_no_options '-' '&'  */
                                                      {
        (yyvsp[-2].pTypeDecl)->ref = false;
        (yyvsp[-2].pTypeDecl)->removeRef = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 866: /* type_declaration_no_options_no_dim: type_declaration_no_options '#'  */
                                                  {
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
        (yyval.pTypeDecl)->temporary = true;
    }
    break;

  case 867: /* type_declaration_no_options_no_dim: type_declaration_no_options "implicit"  */
                                                           {
        (yyval.pTypeDecl) = (yyvsp[-1].pTypeDecl);
        (yyval.pTypeDecl)->implicit = true;
    }
    break;

  case 868: /* type_declaration_no_options_no_dim: type_declaration_no_options '-' '#'  */
                                                      {
        (yyvsp[-2].pTypeDecl)->temporary = false;
        (yyvsp[-2].pTypeDecl)->removeTemporary = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 869: /* type_declaration_no_options_no_dim: type_declaration_no_options "==" "const"  */
                                                               {
        (yyvsp[-2].pTypeDecl)->explicitConst = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 870: /* type_declaration_no_options_no_dim: type_declaration_no_options "==" '&'  */
                                                         {
        (yyvsp[-2].pTypeDecl)->explicitRef = true;
        (yyval.pTypeDecl) = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 871: /* type_declaration_no_options_no_dim: type_declaration_no_options '?'  */
                                                  {
        (yyval.pTypeDecl) = new TypeDecl(Type::tPointer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-1]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 872: /* $@63: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 873: /* $@64: %empty  */
                                                                                               { yyextra->das_arrow_depth --; }
    break;

  case 874: /* type_declaration_no_options_no_dim: "smart_ptr" '<' $@63 type_declaration '>' $@64  */
                                                                                                                                {
        (yyval.pTypeDecl) = new TypeDecl(Type::tPointer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->smartPtr = true;
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 875: /* type_declaration_no_options_no_dim: type_declaration_no_options "??"  */
                                                 {
        (yyval.pTypeDecl) = new TypeDecl(Type::tPointer);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-1]));
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::tPointer);
        (yyval.pTypeDecl)->firstType->at = tokAt(scanner,(yylsp[-1]));
        (yyval.pTypeDecl)->firstType->firstType = (yyvsp[-1].pTypeDecl);
    }
    break;

  case 876: /* $@65: %empty  */
                           { yyextra->das_arrow_depth ++; }
    break;

  case 877: /* $@66: %empty  */
                                                                                           { yyextra->das_arrow_depth --; }
    break;

  case 878: /* type_declaration_no_options_no_dim: "array" '<' $@65 type_declaration '>' $@66  */
                                                                                                                            {
        (yyval.pTypeDecl) = new TypeDecl(Type::tArray);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 879: /* $@67: %empty  */
                           { yyextra->das_arrow_depth ++; }
    break;

  case 880: /* $@68: %empty  */
                                                                                     { yyextra->das_arrow_depth --; }
    break;

  case 881: /* type_declaration_no_options_no_dim: "table" '<' $@67 table_type_pair '>' $@68  */
                                                                                                                      {
        (yyval.pTypeDecl) = new TypeDecl(Type::tTable);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].aTypePair).firstType;
        (yyval.pTypeDecl)->secondType = (yyvsp[-2].aTypePair).secondType;
    }
    break;

  case 882: /* $@69: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 883: /* $@70: %empty  */
                                                                                                 { yyextra->das_arrow_depth --; }
    break;

  case 884: /* type_declaration_no_options_no_dim: "iterator" '<' $@69 type_declaration '>' $@70  */
                                                                                                                                  {
        (yyval.pTypeDecl) = new TypeDecl(Type::tIterator);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 885: /* type_declaration_no_options_no_dim: "block"  */
                        {
        (yyval.pTypeDecl) = new TypeDecl(Type::tBlock);
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::tVoid);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 886: /* $@71: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 887: /* $@72: %empty  */
                                                                                              { yyextra->das_arrow_depth --; }
    break;

  case 888: /* type_declaration_no_options_no_dim: "block" '<' $@71 type_declaration '>' $@72  */
                                                                                                                               {
        (yyval.pTypeDecl) = new TypeDecl(Type::tBlock);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 889: /* $@73: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 890: /* $@74: %empty  */
                                                                                                                                       { yyextra->das_arrow_depth --; }
    break;

  case 891: /* type_declaration_no_options_no_dim: "block" '<' $@73 optional_function_argument_list optional_function_type '>' $@74  */
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

  case 892: /* type_declaration_no_options_no_dim: "function"  */
                           {
        (yyval.pTypeDecl) = new TypeDecl(Type::tFunction);
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::tVoid);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 893: /* $@75: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 894: /* $@76: %empty  */
                                                                                                { yyextra->das_arrow_depth --; }
    break;

  case 895: /* type_declaration_no_options_no_dim: "function" '<' $@75 type_declaration '>' $@76  */
                                                                                                                                 {
        (yyval.pTypeDecl) = new TypeDecl(Type::tFunction);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 896: /* $@77: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 897: /* $@78: %empty  */
                                                                                                                                         { yyextra->das_arrow_depth --; }
    break;

  case 898: /* type_declaration_no_options_no_dim: "function" '<' $@77 optional_function_argument_list optional_function_type '>' $@78  */
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

  case 899: /* type_declaration_no_options_no_dim: "lambda"  */
                         {
        (yyval.pTypeDecl) = new TypeDecl(Type::tLambda);
        (yyval.pTypeDecl)->firstType = new TypeDecl(Type::tVoid);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[0]));
    }
    break;

  case 900: /* $@79: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 901: /* $@80: %empty  */
                                                                                              { yyextra->das_arrow_depth --; }
    break;

  case 902: /* type_declaration_no_options_no_dim: "lambda" '<' $@79 type_declaration '>' $@80  */
                                                                                                                               {
        (yyval.pTypeDecl) = new TypeDecl(Type::tLambda);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        (yyval.pTypeDecl)->firstType = (yyvsp[-2].pTypeDecl);
    }
    break;

  case 903: /* $@81: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 904: /* $@82: %empty  */
                                                                                                                                       { yyextra->das_arrow_depth --; }
    break;

  case 905: /* type_declaration_no_options_no_dim: "lambda" '<' $@81 optional_function_argument_list optional_function_type '>' $@82  */
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

  case 906: /* $@83: %empty  */
                            { yyextra->das_arrow_depth ++; }
    break;

  case 907: /* $@84: %empty  */
                                                                                       { yyextra->das_arrow_depth --; }
    break;

  case 908: /* type_declaration_no_options_no_dim: "tuple" '<' $@83 tuple_type_list '>' $@84  */
                                                                                                                        {
        (yyval.pTypeDecl) = new TypeDecl(Type::tTuple);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        varDeclToTypeDecl(scanner, (yyval.pTypeDecl), (yyvsp[-2].pVarDeclList), true);
        deleteVariableDeclarationList((yyvsp[-2].pVarDeclList));
    }
    break;

  case 909: /* $@85: %empty  */
                              { yyextra->das_arrow_depth ++; }
    break;

  case 910: /* $@86: %empty  */
                                                                                           { yyextra->das_arrow_depth --; }
    break;

  case 911: /* type_declaration_no_options_no_dim: "variant" '<' $@85 variant_type_list '>' $@86  */
                                                                                                                            {
        (yyval.pTypeDecl) = new TypeDecl(Type::tVariant);
        (yyval.pTypeDecl)->at = tokAt(scanner,(yylsp[-5]));
        varDeclToTypeDecl(scanner, (yyval.pTypeDecl), (yyvsp[-2].pVarDeclList), true);
        deleteVariableDeclarationList((yyvsp[-2].pVarDeclList));
    }
    break;

  case 912: /* type_declaration: type_declaration_no_options  */
                                        {
        (yyval.pTypeDecl) = (yyvsp[0].pTypeDecl);
    }
    break;

  case 913: /* type_declaration: type_declaration '|' type_declaration_no_options  */
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

  case 914: /* type_declaration: type_declaration '|' '#'  */
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

  case 915: /* $@87: %empty  */
                   {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 916: /* $@88: %empty  */
                                                                             {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeTuple(atvname);
        }
    }
    break;

  case 917: /* $@89: %empty  */
          {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeTupleEntries(atvname);
        }
    }
    break;

  case 918: /* $@90: %empty  */
                                                 {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-6]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterTupleEntries(atvname);
        }
        yyextra->pop_nesteds();
    }
    break;

  case 919: /* tuple_alias_declaration: "tuple" $@87 optional_public_or_private_alias "name" optional_emit_semis $@88 '{' $@89 tuple_alias_type_list optional_semis $@90 '}'  */
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

  case 920: /* $@91: %empty  */
                     {
        yyextra->push_nesteds(DAS_EMIT_SEMICOLON);
    }
    break;

  case 921: /* $@92: %empty  */
                                                                             {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-1]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeVariant(atvname);
        }
    }
    break;

  case 922: /* $@93: %empty  */
          {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-3]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeVariantEntries(atvname);
        }

    }
    break;

  case 923: /* $@94: %empty  */
                                                   {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-6]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterVariantEntries(atvname);
        }
        yyextra->pop_nesteds();
    }
    break;

  case 924: /* variant_alias_declaration: "variant" $@91 optional_public_or_private_alias "name" optional_emit_semis $@92 '{' $@93 variant_alias_type_list optional_semis $@94 '}'  */
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

  case 925: /* $@95: %empty  */
                      {
        yyextra->push_nesteds(DAS_EMIT_COMMA);
    }
    break;

  case 926: /* $@96: %empty  */
                                                                                                                         {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-2]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeBitfield(atvname);
        }
    }
    break;

  case 927: /* $@97: %empty  */
          {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-4]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->beforeBitfieldEntries(atvname);
        }
    }
    break;

  case 928: /* $@98: %empty  */
                                                {
        if ( !yyextra->g_CommentReaders.empty() ) {
            auto atvname = tokAt(scanner,(yylsp[-7]));
            for ( auto & crd : yyextra->g_CommentReaders ) crd->afterBitfieldEntries(atvname);
        }
        yyextra->pop_nesteds();
    }
    break;

  case 929: /* bitfield_alias_declaration: "bitfield" $@95 optional_public_or_private_alias "name" bitfield_basic_type_declaration optional_emit_commas $@96 '{' $@97 bitfield_alias_bits optional_commas $@98 '}'  */
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

  case 930: /* make_decl: make_struct_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 931: /* make_decl: make_dim_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 932: /* make_decl: make_table_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 933: /* make_decl: make_table_call  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 934: /* make_decl: array_comprehension  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 935: /* make_decl: table_comprehension  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 936: /* make_decl: make_tuple_call  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 937: /* make_decl_no_bracket: make_struct_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 938: /* make_decl_no_bracket: make_dim_decl  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 939: /* make_decl_no_bracket: make_tuple_call  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 940: /* make_decl_no_bracket: table_comprehension  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 941: /* make_decl_no_bracket: make_table_call  */
                                 { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 942: /* make_struct_fields: "name" copy_or_move expr  */
                                               {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-2])),*(yyvsp[-2].s),(yyvsp[0].pExpression),(yyvsp[-1].b),false);
        delete (yyvsp[-2].s);
        auto msd = new MakeStruct();
        msd->push_back(mfd);
        (yyval.pMakeStruct) = msd;
    }
    break;

  case 943: /* make_struct_fields: "name" ":=" expr  */
                                      {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-2])),*(yyvsp[-2].s),(yyvsp[0].pExpression),false,true);
        delete (yyvsp[-2].s);
        auto msd = new MakeStruct();
        msd->push_back(mfd);
        (yyval.pMakeStruct) = msd;
    }
    break;

  case 944: /* make_struct_fields: make_struct_fields ',' "name" copy_or_move expr  */
                                                                           {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-2])),*(yyvsp[-2].s),(yyvsp[0].pExpression),(yyvsp[-1].b),false);
        delete (yyvsp[-2].s);
        ((MakeStruct *)(yyvsp[-4].pMakeStruct))->push_back(mfd);
        (yyval.pMakeStruct) = (yyvsp[-4].pMakeStruct);
    }
    break;

  case 945: /* make_struct_fields: make_struct_fields ',' "name" ":=" expr  */
                                                                  {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-2])),*(yyvsp[-2].s),(yyvsp[0].pExpression),false,true);
        delete (yyvsp[-2].s);
        ((MakeStruct *)(yyvsp[-4].pMakeStruct))->push_back(mfd);
        (yyval.pMakeStruct) = (yyvsp[-4].pMakeStruct);
    }
    break;

  case 946: /* make_struct_fields: "$f" '(' expr ')' copy_or_move expr  */
                                                                   {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-3])),"``MACRO``TAG``FIELD``",(yyvsp[0].pExpression),(yyvsp[-1].b),false);
        mfd->tag = (yyvsp[-3].pExpression);
        auto msd = new MakeStruct();
        msd->push_back(mfd);
        (yyval.pMakeStruct) = msd;
    }
    break;

  case 947: /* make_struct_fields: "$f" '(' expr ')' ":=" expr  */
                                                          {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-3])),"``MACRO``TAG``FIELD``",(yyvsp[0].pExpression),false,true);
        mfd->tag = (yyvsp[-3].pExpression);
        auto msd = new MakeStruct();
        msd->push_back(mfd);
        (yyval.pMakeStruct) = msd;
    }
    break;

  case 948: /* make_struct_fields: make_struct_fields ',' "$f" '(' expr ')' copy_or_move expr  */
                                                                                               {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-3])),"``MACRO``TAG``FIELD``",(yyvsp[0].pExpression),(yyvsp[-1].b),false);
        mfd->tag = (yyvsp[-3].pExpression);
        ((MakeStruct *)(yyvsp[-7].pMakeStruct))->push_back(mfd);
        (yyval.pMakeStruct) = (yyvsp[-7].pMakeStruct);
    }
    break;

  case 949: /* make_struct_fields: make_struct_fields ',' "$f" '(' expr ')' ":=" expr  */
                                                                                      {
        auto mfd = new MakeFieldDecl(tokAt(scanner,(yylsp[-3])),"``MACRO``TAG``FIELD``",(yyvsp[0].pExpression),false,true);
        mfd->tag = (yyvsp[-3].pExpression);
        ((MakeStruct *)(yyvsp[-7].pMakeStruct))->push_back(mfd);
        (yyval.pMakeStruct) = (yyvsp[-7].pMakeStruct);
    }
    break;

  case 950: /* make_variant_dim: %empty  */
       {
        (yyval.pExpression) = ast_makeStructToMakeVariant(nullptr, LineInfo());
    }
    break;

  case 951: /* make_variant_dim: make_struct_fields  */
                              {
        (yyval.pExpression) = ast_makeStructToMakeVariant((yyvsp[0].pMakeStruct), tokAt(scanner,(yylsp[0])));
    }
    break;

  case 952: /* make_struct_single: make_struct_fields optional_comma  */
                                               {
        auto msd = new ExprMakeStruct();
        msd->structs.push_back(MakeStructPtr((yyvsp[-1].pMakeStruct)));
        (yyval.pExpression) = msd;
    }
    break;

  case 953: /* make_struct_dim_list: '(' make_struct_fields ')'  */
                                        {
        auto msd = new ExprMakeStruct();
        msd->structs.push_back(MakeStructPtr((yyvsp[-1].pMakeStruct)));
        (yyval.pExpression) = msd;
    }
    break;

  case 954: /* make_struct_dim_list: make_struct_dim_list ',' '(' make_struct_fields ')'  */
                                                                     {
        ((ExprMakeStruct *) (yyvsp[-4].pExpression))->structs.push_back(MakeStructPtr((yyvsp[-1].pMakeStruct)));
        (yyval.pExpression) = (yyvsp[-4].pExpression);
    }
    break;

  case 955: /* make_struct_dim_decl: make_struct_fields  */
                                {
        auto msd = new ExprMakeStruct();
        msd->structs.push_back(MakeStructPtr((yyvsp[0].pMakeStruct)));
        (yyval.pExpression) = msd;
    }
    break;

  case 956: /* make_struct_dim_decl: make_struct_dim_list optional_comma  */
                                                 {
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 957: /* optional_make_struct_dim_decl: make_struct_dim_decl  */
                                  { (yyval.pExpression) = (yyvsp[0].pExpression);  }
    break;

  case 958: /* optional_make_struct_dim_decl: %empty  */
        {   (yyval.pExpression) = new ExprMakeStruct(); }
    break;

  case 959: /* use_initializer: %empty  */
                            { (yyval.b) = true; }
    break;

  case 960: /* use_initializer: "uninitialized"  */
                            { (yyval.b) = false; }
    break;

  case 961: /* $@99: %empty  */
                             { yyextra->das_arrow_depth ++; }
    break;

  case 962: /* $@100: %empty  */
                                                                                                   { yyextra->das_arrow_depth --; }
    break;

  case 963: /* make_struct_decl: "struct" '<' $@99 type_declaration_no_options '>' $@100 '(' use_initializer optional_make_struct_dim_decl ')'  */
                                                                                                                                                                                                      {
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-9]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-6].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = (yyvsp[-2].b);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->forceStruct = true;
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->alwaysUseInitializer = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 964: /* $@101: %empty  */
                            { yyextra->das_arrow_depth ++; }
    break;

  case 965: /* $@102: %empty  */
                                                                                                  { yyextra->das_arrow_depth --; }
    break;

  case 966: /* make_struct_decl: "class" '<' $@101 type_declaration_no_options '>' $@102 '(' use_initializer optional_make_struct_dim_decl ')'  */
                                                                                                                                                                                                     {
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-9]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-6].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = (yyvsp[-2].b);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->forceClass = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 967: /* $@103: %empty  */
                               { yyextra->das_arrow_depth ++; }
    break;

  case 968: /* $@104: %empty  */
                                                                                            { yyextra->das_arrow_depth --; }
    break;

  case 969: /* make_struct_decl: "variant" '<' $@103 variant_type_list '>' $@104 '(' use_initializer make_variant_dim ')'  */
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

  case 970: /* $@105: %empty  */
                                        { yyextra->das_arrow_depth ++; }
    break;

  case 971: /* $@106: %empty  */
                                                                                                              { yyextra->das_arrow_depth --; }
    break;

  case 972: /* make_struct_decl: "variant" "type" '<' $@105 type_declaration_no_options '>' $@106 '(' use_initializer make_variant_dim ')'  */
                                                                                                                                                                                                    {
        (yyvsp[-1].pExpression)->at = tokAt(scanner,(yylsp[-10]));
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->makeType = (yyvsp[-6].pTypeDecl);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->useInitializer = (yyvsp[-2].b);
        ((ExprMakeStruct *)(yyvsp[-1].pExpression))->forceVariant = true;
        (yyval.pExpression) = (yyvsp[-1].pExpression);
    }
    break;

  case 973: /* $@107: %empty  */
                              { yyextra->das_arrow_depth ++; }
    break;

  case 974: /* $@108: %empty  */
                                                                                                    { yyextra->das_arrow_depth --; }
    break;

  case 975: /* make_struct_decl: "default" '<' $@107 type_declaration_no_options '>' $@108 use_initializer  */
                                                                                                                                                           {
        auto msd = new ExprMakeStruct();
        msd->at = tokAt(scanner,(yylsp[-6]));
        msd->makeType = (yyvsp[-3].pTypeDecl);
        msd->useInitializer = (yyvsp[0].b);
        msd->alwaysUseInitializer = true;
        (yyval.pExpression) = msd;
    }
    break;

  case 976: /* make_tuple_call: "tuple" '(' expr_list optional_comma ')'  */
                                                                    {
        auto mkt = new ExprMakeTuple(tokAt(scanner,(yylsp[-4])));
        mkt->values = sequenceToList((yyvsp[-2].pExpression));
        mkt->makeType = new TypeDecl(Type::autoinfer);
        (yyval.pExpression) = mkt;
    }
    break;

  case 977: /* $@109: %empty  */
                             { yyextra->das_force_oxford_comma=true; yyextra->das_arrow_depth ++; }
    break;

  case 978: /* $@110: %empty  */
                                                                                                                              { yyextra->das_arrow_depth --; }
    break;

  case 979: /* make_tuple_call: "tuple" '<' $@109 tuple_type_list '>' $@110 '(' use_initializer optional_make_struct_dim_decl ')'  */
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

  case 980: /* make_dim_decl: '[' optional_expr_list ']'  */
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

  case 981: /* $@111: %empty  */
                                       { yyextra->das_arrow_depth ++; }
    break;

  case 982: /* $@112: %empty  */
                                                                                                             { yyextra->das_arrow_depth --; }
    break;

  case 983: /* make_dim_decl: "array" "struct" '<' $@111 type_declaration_no_options '>' $@112 '(' use_initializer optional_make_struct_dim_decl ')'  */
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

  case 984: /* $@113: %empty  */
                                       { yyextra->das_arrow_depth ++; }
    break;

  case 985: /* $@114: %empty  */
                                                                                                  { yyextra->das_arrow_depth --; }
    break;

  case 986: /* make_dim_decl: "array" "tuple" '<' $@113 tuple_type_list '>' $@114 '(' use_initializer optional_make_struct_dim_decl ')'  */
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

  case 987: /* $@115: %empty  */
                                         { yyextra->das_arrow_depth ++; }
    break;

  case 988: /* $@116: %empty  */
                                                                                                      { yyextra->das_arrow_depth --; }
    break;

  case 989: /* make_dim_decl: "array" "variant" '<' $@115 variant_type_list '>' $@116 '(' make_variant_dim ')'  */
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

  case 990: /* make_dim_decl: "array" '(' expr_list optional_comma ')'  */
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

  case 991: /* $@117: %empty  */
                           { yyextra->das_arrow_depth ++; }
    break;

  case 992: /* $@118: %empty  */
                                                                                                 { yyextra->das_arrow_depth --; }
    break;

  case 993: /* make_dim_decl: "array" '<' $@117 type_declaration_no_options '>' $@118 '(' optional_expr_list ')'  */
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

  case 994: /* make_dim_decl: "fixed_array" '(' expr_list optional_comma ')'  */
                                                                         {
        auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-4])));
        mka->values = sequenceToList((yyvsp[-2].pExpression));
        mka->makeType = new TypeDecl(Type::autoinfer);
        mka->gen2 = true;
        (yyval.pExpression) = mka;
    }
    break;

  case 995: /* $@119: %empty  */
                                 { yyextra->das_arrow_depth ++; }
    break;

  case 996: /* $@120: %empty  */
                                                                                                       { yyextra->das_arrow_depth --; }
    break;

  case 997: /* make_dim_decl: "fixed_array" '<' $@119 type_declaration_no_options '>' $@120 '(' expr_list optional_comma ')'  */
                                                                                                                                                                                    {
        auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-9])));
        mka->values = sequenceToList((yyvsp[-2].pExpression));
        mka->makeType = (yyvsp[-6].pTypeDecl);
        mka->gen2 = true;
        (yyval.pExpression) = mka;
    }
    break;

  case 998: /* expr_map_tuple_list: expr  */
                      {
        (yyval.pExpression) = (yyvsp[0].pExpression);
    }
    break;

  case 999: /* expr_map_tuple_list: expr_map_tuple_list ',' expr  */
                                                      {
            (yyval.pExpression) = new ExprSequence(tokAt(scanner,(yylsp[-2])),(yyvsp[-2].pExpression),(yyvsp[0].pExpression));
    }
    break;

  case 1000: /* push_table_nesting: %empty  */
                    {
        yyextra->das_nested_parentheses ++;
    }
    break;

  case 1001: /* make_table_decl: '{' push_table_nesting optional_emit_semis optional_expr_map_tuple_list '}'  */
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

  case 1002: /* make_table_call: "table" '(' expr_map_tuple_list optional_comma ')'  */
                                                                             {
        auto mka = new ExprMakeArray(tokAt(scanner,(yylsp[-4])));
        mka->values = sequenceToList((yyvsp[-2].pExpression));
        mka->makeType = new TypeDecl(Type::autoinfer);
        auto ttm = yyextra->g_Program->makeCall(tokAt(scanner,(yylsp[-4])),"to_table_move");
        ttm->arguments.push_back(mka);
        (yyval.pExpression) = ttm;
    }
    break;

  case 1003: /* make_table_call: "table" '<' type_declaration_no_options '>' '(' optional_expr_map_tuple_list ')'  */
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

  case 1004: /* make_table_call: "table" '<' type_declaration_no_options c_or_s type_declaration_no_options '>' '(' optional_expr_map_tuple_list ')'  */
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

  case 1005: /* array_comprehension_where: %empty  */
                                    { (yyval.pExpression) = nullptr; }
    break;

  case 1006: /* array_comprehension_where: ';' "where" expr  */
                                    { (yyval.pExpression) = (yyvsp[0].pExpression); }
    break;

  case 1007: /* optional_comma: %empty  */
                { (yyval.b) = false; }
    break;

  case 1008: /* optional_comma: ','  */
                { (yyval.b) = true; }
    break;

  case 1009: /* table_comprehension: '[' "for" '(' for_variable_name_with_pos_list "in" expr_list ')' ';' expr array_comprehension_where ']'  */
                                                                                                                                                               {
        (yyval.pExpression) = ast_arrayComprehension(scanner,tokAt(scanner,(yylsp[-9])),(yyvsp[-7].pNameWithPosList),(yyvsp[-5].pExpression),(yyvsp[-2].pExpression),(yyvsp[-1].pExpression),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),false,false);
    }
    break;

  case 1010: /* table_comprehension: '[' "iterator" "for" '(' for_variable_name_with_pos_list "in" expr_list ')' ';' expr array_comprehension_where ']'  */
                                                                                                                                                                            {
        (yyval.pExpression) = ast_arrayComprehension(scanner,tokAt(scanner,(yylsp[-9])),(yyvsp[-7].pNameWithPosList),(yyvsp[-5].pExpression),(yyvsp[-2].pExpression),(yyvsp[-1].pExpression),tokRangeAt(scanner,(yylsp[-2]),(yylsp[0])),true,false);
    }
    break;

  case 1011: /* array_comprehension: '{' push_table_nesting optional_emit_semis "for" '(' for_variable_name_with_pos_list "in" expr_list ')' ';' expr array_comprehension_where '}'  */
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


