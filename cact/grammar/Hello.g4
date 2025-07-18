grammar Hello;

@header {
    #include <vector>
}

/****** parser ******/

/*** 声明和定义 ***/
//所有{}换成()*,因为g4不支持，任意次（可能0次，也可能多次）
//所有[]换成()?，因为g4不支持，整个括号内容是可选的（0次或1次）

compUnit : ( decl | funcDef )+ EOF ;

decl : constdecl | vardecl ;

constdecl : CONST_KW bType constDef ( Comma constDef )* Semi ;

bType : INT_KW | FLOAT_KW | CHAR_KW;

constDef : Ident ( LeftBracket IntConst RightBracket )* Assign constInitVal ;

constInitVal : constExp | LeftBrace ( constInitVal ( Comma constInitVal )* )? RightBrace ;



//尝试解决数组初始化问题
//解决int a[4] = 4;非法
vardecl : bType (varDef | varDefArray) ( Comma (varDef | varDefArray) )* Semi ;
varDefArray : Ident LeftBracket IntConst RightBracket ( LeftBracket IntConst RightBracket )* ( Assign constInitValArray )?;
constInitValArray : LeftBrace ( constInitVal ( Comma constInitVal )* )? RightBrace ;
varDef : Ident ( Assign constInitVal )?;


funcDef : funcType Ident LeftParen (funcFParams)? RightParen block ;

funcType : VOID_KW | INT_KW | FLOAT_KW | CHAR_KW ;

//funcFParams : funcFParam ( Comma funcFParam )* ;
funcFParams : funcFParam? ( Comma funcFParam )* ;

funcFParam : bType Ident ( LeftBracket (IntConst)? RightBracket ( LeftBracket IntConst RightBracket )* )? ;



/*** 语句和表达式 ***/
block : LeftBrace (blockItem)* RightBrace ;

blockItem : decl | stmt ;

stmt :  exp (Assign exp)? Semi 
        | Semi 
        | block 
        | RETURN_KW exp? Semi
        | IF_KW LeftParen cond RightParen stmt ( ELSE_KW stmt )?
        | WHILE_KW LeftParen cond RightParen stmt
        | BREAK_KW Semi 
        | CONTINUE_KW Semi ;

exp : addExp ;

constExp : addExp ;
// 使用的Ident必须是常量
//显式初始化：CACT限制初值表达式必须是常数
//constExp : number ;

cond : lOrExp ;

lVal : Ident (LeftBracket exp RightBracket)* ;

number : IntConst | FloatConst | CharConst ;

funcRParams : exp (Comma exp)* ;

primaryExp : LeftParen exp RightParen | lVal | number ;

unaryExp : primaryExp | (Plus | Minus | Not) unaryExp
           | Ident LeftParen ( funcRParams )? RightParen ; //'!'仅出现在条件表达式中
/*
mulExp : unaryExp | mulExp (Star | Div | Mod) unaryExp ;

addExp : mulExp | addExp (Plus|Minus) mulExp ;

relExp : addExp | relExp (Less | Greater | LessEqual | GreaterEqual) addExp ;

eqExp : relExp | eqExp (Equal | NotEqual) relExp ;

lAndExp : eqExp | lAndExp AndAnd eqExp ;

lOrExp : lAndExp | lOrExp OrOr lAndExp ;
*/

mulExp   : unaryExp ( (Star | Div | Mod) unaryExp )* ;

addExp   : mulExp ( (Plus | Minus) mulExp )* ;

relExp   : addExp ( (Less | Greater | LessEqual | GreaterEqual) addExp )* ;

eqExp    : relExp ( (Equal | NotEqual) relExp )* ;

lAndExp  : eqExp ( AndAnd eqExp )* ;

lOrExp   : lAndExp ( OrOr lAndExp )* ;


/*
1. 常量表达式不在语句块中出现。
2. 条件表达式只在If和While的条件语句中出现，不出现在赋值语句中。
3. 连加（a+b+c）会出现，但诸如连等(a=b=c)、连续比较(a==b==c，a < b < c)则不会出现，不必考
虑。
*/



/****** lexer  ******/
/*Key Word*/

CONST_KW : 'const' ;

INT_KW : 'int' ;

DOUBLE_KW : 'double' ;

CHAR_KW : 'char' ;

FLOAT_KW : 'float' ;

VOID_KW : 'void' ;

IF_KW : 'if' ;

ELSE_KW : 'else' ;

WHILE_KW : 'while' ;

BREAK_KW : 'break' ;

CONTINUE_KW : 'continue' ;

RETURN_KW : 'return' ;


/*operator*/

LeftBracket : '[' ;

RightBracket : ']' ;

LeftParen : '(' ;

RightParen : ')' ;

Plus : '+' ;

Minus : '-' ;
    
Not : '!' ;

Star : '*' ;

Div : '/' ;

Mod : '%';

LessEqual : '<=' ;

Less : '<' ;

GreaterEqual : '>=' ;

Greater : '>' ;

Equal : '==' ;

NotEqual : '!=' ;

AndAnd : '&&' ;

OrOr : '||' ;


Semi : ';' ;

Comma : ',' ;

Assign : '=' ;

Dot : '.' ;

LeftBrace : '{' ;

RightBrace : '}' ;


/*** 终结符 ***/

Ident: [a-zA-Z_] [a-zA-Z_0-9]*;

IntConst : DecimalConst | OctalConst | HexadecConst ;

HexadecConst : ('0x'|'0X') [0-9a-fA-F]+ ;

OctalConst : '0' [0-7]+ ;

DecimalConst : '0' | [1-9] [0-9]*;



//这段直接来自ISO文件，但是不符合cact中的要求
//float e = 1.5; 非法
//非法原因是1.5是double，不是float
//询问助教之后发现没有问题

FloatConst
    :   DecimalFloatConst
    |   HexadecimalFloatConst
    ;

DecimalFloatConst
    :   FractionalConst ExponentPart? FloatSuffix?
    |   DigitSequence ExponentPart FloatSuffix?
    ;

HexadecimalFloatConst
    :   HexPrefix HexFractionalConst BinaryExponentPart FloatSuffix?
    |   HexPrefix HexDigitSequence BinaryExponentPart FloatSuffix?
    ;

FractionalConst
    :   DigitSequence? '.' DigitSequence
    |   DigitSequence '.'
    ;

ExponentPart
    :   [eE] Sign? DigitSequence
    ;

BinaryExponentPart
    :   [pP] Sign? DigitSequence
    ;

Sign
    :   [+-]
    ;

DigitSequence
    :   Digit+
    ;

Digit
    :   [0-9]
    ;

HexPrefix
    :   '0x' | '0X'
    ;

HexFractionalConst
    :   HexDigitSequence? '.' HexDigitSequence
    |   HexDigitSequence '.'
    |   '.' HexDigitSequence
    ;

HexDigitSequence
    :   HexDigit+
    ;

HexDigit
    :   [0-9a-fA-F]
    ;

FloatSuffix
    :   [fFlL]
    ;


CharConst: '\'' ( ~['\\\r\n] | EscapeSequence ) '\'';

EscapeSequence
    : '\\' [btnr'\\]
    ;


/****** skips  ******/
NewLine :( '\r' '\n'?| '\n' ) -> skip ;

WhiteSpace : [ \t\r\n]+ -> skip;

LineComment : ('//' ~[\r\n]* ) -> skip;

BlockComment :('/*' .*? '*/') -> skip;