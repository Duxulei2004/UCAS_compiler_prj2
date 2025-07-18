
    #include <vector>


// Generated from ./Hello.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  HelloLexer : public antlr4::Lexer {
public:
  enum {
    CONST_KW = 1, INT_KW = 2, DOUBLE_KW = 3, CHAR_KW = 4, FLOAT_KW = 5, 
    VOID_KW = 6, IF_KW = 7, ELSE_KW = 8, WHILE_KW = 9, BREAK_KW = 10, CONTINUE_KW = 11, 
    RETURN_KW = 12, LeftBracket = 13, RightBracket = 14, LeftParen = 15, 
    RightParen = 16, Plus = 17, Minus = 18, Not = 19, Star = 20, Div = 21, 
    Mod = 22, LessEqual = 23, Less = 24, GreaterEqual = 25, Greater = 26, 
    Equal = 27, NotEqual = 28, AndAnd = 29, OrOr = 30, Semi = 31, Comma = 32, 
    Assign = 33, Dot = 34, LeftBrace = 35, RightBrace = 36, Ident = 37, 
    IntConst = 38, HexadecConst = 39, OctalConst = 40, DecimalConst = 41, 
    FloatConst = 42, DecimalFloatConst = 43, HexadecimalFloatConst = 44, 
    FractionalConst = 45, ExponentPart = 46, BinaryExponentPart = 47, Sign = 48, 
    DigitSequence = 49, Digit = 50, HexPrefix = 51, HexFractionalConst = 52, 
    HexDigitSequence = 53, HexDigit = 54, FloatSuffix = 55, CharConst = 56, 
    EscapeSequence = 57, NewLine = 58, WhiteSpace = 59, LineComment = 60, 
    BlockComment = 61
  };

  explicit HelloLexer(antlr4::CharStream *input);

  ~HelloLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

