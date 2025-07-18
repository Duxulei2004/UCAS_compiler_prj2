
    #include <vector>


// Generated from ./Hello.g4 by ANTLR 4.13.1


#include "HelloVisitor.h"

#include "HelloParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct HelloParserStaticData final {
  HelloParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  HelloParserStaticData(const HelloParserStaticData&) = delete;
  HelloParserStaticData(HelloParserStaticData&&) = delete;
  HelloParserStaticData& operator=(const HelloParserStaticData&) = delete;
  HelloParserStaticData& operator=(HelloParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag helloParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
HelloParserStaticData *helloParserStaticData = nullptr;

void helloParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (helloParserStaticData != nullptr) {
    return;
  }
#else
  assert(helloParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<HelloParserStaticData>(
    std::vector<std::string>{
      "compUnit", "decl", "constdecl", "bType", "constDef", "constInitVal", 
      "vardecl", "varDefArray", "constInitValArray", "varDef", "funcDef", 
      "funcType", "funcFParams", "funcFParam", "block", "blockItem", "stmt", 
      "exp", "constExp", "cond", "lVal", "number", "funcRParams", "primaryExp", 
      "unaryExp", "mulExp", "addExp", "relExp", "eqExp", "lAndExp", "lOrExp"
    },
    std::vector<std::string>{
      "", "'const'", "'int'", "'double'", "'char'", "'float'", "'void'", 
      "'if'", "'else'", "'while'", "'break'", "'continue'", "'return'", 
      "'['", "']'", "'('", "')'", "'+'", "'-'", "'!'", "'*'", "'/'", "'%'", 
      "'<='", "'<'", "'>='", "'>'", "'=='", "'!='", "'&&'", "'||'", "';'", 
      "','", "'='", "'.'", "'{'", "'}'"
    },
    std::vector<std::string>{
      "", "CONST_KW", "INT_KW", "DOUBLE_KW", "CHAR_KW", "FLOAT_KW", "VOID_KW", 
      "IF_KW", "ELSE_KW", "WHILE_KW", "BREAK_KW", "CONTINUE_KW", "RETURN_KW", 
      "LeftBracket", "RightBracket", "LeftParen", "RightParen", "Plus", 
      "Minus", "Not", "Star", "Div", "Mod", "LessEqual", "Less", "GreaterEqual", 
      "Greater", "Equal", "NotEqual", "AndAnd", "OrOr", "Semi", "Comma", 
      "Assign", "Dot", "LeftBrace", "RightBrace", "Ident", "IntConst", "HexadecConst", 
      "OctalConst", "DecimalConst", "FloatConst", "DecimalFloatConst", "HexadecimalFloatConst", 
      "FractionalConst", "ExponentPart", "BinaryExponentPart", "Sign", "DigitSequence", 
      "Digit", "HexPrefix", "HexFractionalConst", "HexDigitSequence", "HexDigit", 
      "FloatSuffix", "CharConst", "EscapeSequence", "NewLine", "WhiteSpace", 
      "LineComment", "BlockComment"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,61,346,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,1,0,1,0,4,0,65,8,0,11,0,12,0,66,1,0,1,0,1,1,1,
  	1,3,1,73,8,1,1,2,1,2,1,2,1,2,1,2,5,2,80,8,2,10,2,12,2,83,9,2,1,2,1,2,
  	1,3,1,3,1,4,1,4,1,4,1,4,5,4,93,8,4,10,4,12,4,96,9,4,1,4,1,4,1,4,1,5,1,
  	5,1,5,1,5,1,5,5,5,106,8,5,10,5,12,5,109,9,5,3,5,111,8,5,1,5,3,5,114,8,
  	5,1,6,1,6,1,6,3,6,119,8,6,1,6,1,6,1,6,3,6,124,8,6,5,6,126,8,6,10,6,12,
  	6,129,9,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,5,7,140,8,7,10,7,12,7,143,
  	9,7,1,7,1,7,3,7,147,8,7,1,8,1,8,1,8,1,8,5,8,153,8,8,10,8,12,8,156,9,8,
  	3,8,158,8,8,1,8,1,8,1,9,1,9,1,9,3,9,165,8,9,1,10,1,10,1,10,1,10,3,10,
  	171,8,10,1,10,1,10,1,10,1,11,1,11,1,12,3,12,179,8,12,1,12,1,12,5,12,183,
  	8,12,10,12,12,12,186,9,12,1,13,1,13,1,13,1,13,3,13,192,8,13,1,13,1,13,
  	1,13,1,13,5,13,198,8,13,10,13,12,13,201,9,13,3,13,203,8,13,1,14,1,14,
  	5,14,207,8,14,10,14,12,14,210,9,14,1,14,1,14,1,15,1,15,3,15,216,8,15,
  	1,16,1,16,1,16,3,16,221,8,16,1,16,1,16,1,16,1,16,1,16,1,16,3,16,229,8,
  	16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,3,16,239,8,16,1,16,1,16,1,
  	16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,3,16,251,8,16,1,17,1,17,1,18,1,
  	18,1,19,1,19,1,20,1,20,1,20,1,20,1,20,5,20,264,8,20,10,20,12,20,267,9,
  	20,1,21,1,21,1,22,1,22,1,22,5,22,274,8,22,10,22,12,22,277,9,22,1,23,1,
  	23,1,23,1,23,1,23,1,23,3,23,285,8,23,1,24,1,24,1,24,1,24,1,24,1,24,3,
  	24,293,8,24,1,24,3,24,296,8,24,1,25,1,25,1,25,5,25,301,8,25,10,25,12,
  	25,304,9,25,1,26,1,26,1,26,5,26,309,8,26,10,26,12,26,312,9,26,1,27,1,
  	27,1,27,5,27,317,8,27,10,27,12,27,320,9,27,1,28,1,28,1,28,5,28,325,8,
  	28,10,28,12,28,328,9,28,1,29,1,29,1,29,5,29,333,8,29,10,29,12,29,336,
  	9,29,1,30,1,30,1,30,5,30,341,8,30,10,30,12,30,344,9,30,1,30,0,0,31,0,
  	2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,
  	52,54,56,58,60,0,8,2,0,2,2,4,5,2,0,2,2,4,6,3,0,38,38,42,42,56,56,1,0,
  	17,19,1,0,20,22,1,0,17,18,1,0,23,26,1,0,27,28,361,0,64,1,0,0,0,2,72,1,
  	0,0,0,4,74,1,0,0,0,6,86,1,0,0,0,8,88,1,0,0,0,10,113,1,0,0,0,12,115,1,
  	0,0,0,14,132,1,0,0,0,16,148,1,0,0,0,18,161,1,0,0,0,20,166,1,0,0,0,22,
  	175,1,0,0,0,24,178,1,0,0,0,26,187,1,0,0,0,28,204,1,0,0,0,30,215,1,0,0,
  	0,32,250,1,0,0,0,34,252,1,0,0,0,36,254,1,0,0,0,38,256,1,0,0,0,40,258,
  	1,0,0,0,42,268,1,0,0,0,44,270,1,0,0,0,46,284,1,0,0,0,48,295,1,0,0,0,50,
  	297,1,0,0,0,52,305,1,0,0,0,54,313,1,0,0,0,56,321,1,0,0,0,58,329,1,0,0,
  	0,60,337,1,0,0,0,62,65,3,2,1,0,63,65,3,20,10,0,64,62,1,0,0,0,64,63,1,
  	0,0,0,65,66,1,0,0,0,66,64,1,0,0,0,66,67,1,0,0,0,67,68,1,0,0,0,68,69,5,
  	0,0,1,69,1,1,0,0,0,70,73,3,4,2,0,71,73,3,12,6,0,72,70,1,0,0,0,72,71,1,
  	0,0,0,73,3,1,0,0,0,74,75,5,1,0,0,75,76,3,6,3,0,76,81,3,8,4,0,77,78,5,
  	32,0,0,78,80,3,8,4,0,79,77,1,0,0,0,80,83,1,0,0,0,81,79,1,0,0,0,81,82,
  	1,0,0,0,82,84,1,0,0,0,83,81,1,0,0,0,84,85,5,31,0,0,85,5,1,0,0,0,86,87,
  	7,0,0,0,87,7,1,0,0,0,88,94,5,37,0,0,89,90,5,13,0,0,90,91,5,38,0,0,91,
  	93,5,14,0,0,92,89,1,0,0,0,93,96,1,0,0,0,94,92,1,0,0,0,94,95,1,0,0,0,95,
  	97,1,0,0,0,96,94,1,0,0,0,97,98,5,33,0,0,98,99,3,10,5,0,99,9,1,0,0,0,100,
  	114,3,36,18,0,101,110,5,35,0,0,102,107,3,10,5,0,103,104,5,32,0,0,104,
  	106,3,10,5,0,105,103,1,0,0,0,106,109,1,0,0,0,107,105,1,0,0,0,107,108,
  	1,0,0,0,108,111,1,0,0,0,109,107,1,0,0,0,110,102,1,0,0,0,110,111,1,0,0,
  	0,111,112,1,0,0,0,112,114,5,36,0,0,113,100,1,0,0,0,113,101,1,0,0,0,114,
  	11,1,0,0,0,115,118,3,6,3,0,116,119,3,18,9,0,117,119,3,14,7,0,118,116,
  	1,0,0,0,118,117,1,0,0,0,119,127,1,0,0,0,120,123,5,32,0,0,121,124,3,18,
  	9,0,122,124,3,14,7,0,123,121,1,0,0,0,123,122,1,0,0,0,124,126,1,0,0,0,
  	125,120,1,0,0,0,126,129,1,0,0,0,127,125,1,0,0,0,127,128,1,0,0,0,128,130,
  	1,0,0,0,129,127,1,0,0,0,130,131,5,31,0,0,131,13,1,0,0,0,132,133,5,37,
  	0,0,133,134,5,13,0,0,134,135,5,38,0,0,135,141,5,14,0,0,136,137,5,13,0,
  	0,137,138,5,38,0,0,138,140,5,14,0,0,139,136,1,0,0,0,140,143,1,0,0,0,141,
  	139,1,0,0,0,141,142,1,0,0,0,142,146,1,0,0,0,143,141,1,0,0,0,144,145,5,
  	33,0,0,145,147,3,16,8,0,146,144,1,0,0,0,146,147,1,0,0,0,147,15,1,0,0,
  	0,148,157,5,35,0,0,149,154,3,10,5,0,150,151,5,32,0,0,151,153,3,10,5,0,
  	152,150,1,0,0,0,153,156,1,0,0,0,154,152,1,0,0,0,154,155,1,0,0,0,155,158,
  	1,0,0,0,156,154,1,0,0,0,157,149,1,0,0,0,157,158,1,0,0,0,158,159,1,0,0,
  	0,159,160,5,36,0,0,160,17,1,0,0,0,161,164,5,37,0,0,162,163,5,33,0,0,163,
  	165,3,10,5,0,164,162,1,0,0,0,164,165,1,0,0,0,165,19,1,0,0,0,166,167,3,
  	22,11,0,167,168,5,37,0,0,168,170,5,15,0,0,169,171,3,24,12,0,170,169,1,
  	0,0,0,170,171,1,0,0,0,171,172,1,0,0,0,172,173,5,16,0,0,173,174,3,28,14,
  	0,174,21,1,0,0,0,175,176,7,1,0,0,176,23,1,0,0,0,177,179,3,26,13,0,178,
  	177,1,0,0,0,178,179,1,0,0,0,179,184,1,0,0,0,180,181,5,32,0,0,181,183,
  	3,26,13,0,182,180,1,0,0,0,183,186,1,0,0,0,184,182,1,0,0,0,184,185,1,0,
  	0,0,185,25,1,0,0,0,186,184,1,0,0,0,187,188,3,6,3,0,188,202,5,37,0,0,189,
  	191,5,13,0,0,190,192,5,38,0,0,191,190,1,0,0,0,191,192,1,0,0,0,192,193,
  	1,0,0,0,193,199,5,14,0,0,194,195,5,13,0,0,195,196,5,38,0,0,196,198,5,
  	14,0,0,197,194,1,0,0,0,198,201,1,0,0,0,199,197,1,0,0,0,199,200,1,0,0,
  	0,200,203,1,0,0,0,201,199,1,0,0,0,202,189,1,0,0,0,202,203,1,0,0,0,203,
  	27,1,0,0,0,204,208,5,35,0,0,205,207,3,30,15,0,206,205,1,0,0,0,207,210,
  	1,0,0,0,208,206,1,0,0,0,208,209,1,0,0,0,209,211,1,0,0,0,210,208,1,0,0,
  	0,211,212,5,36,0,0,212,29,1,0,0,0,213,216,3,2,1,0,214,216,3,32,16,0,215,
  	213,1,0,0,0,215,214,1,0,0,0,216,31,1,0,0,0,217,220,3,34,17,0,218,219,
  	5,33,0,0,219,221,3,34,17,0,220,218,1,0,0,0,220,221,1,0,0,0,221,222,1,
  	0,0,0,222,223,5,31,0,0,223,251,1,0,0,0,224,251,5,31,0,0,225,251,3,28,
  	14,0,226,228,5,12,0,0,227,229,3,34,17,0,228,227,1,0,0,0,228,229,1,0,0,
  	0,229,230,1,0,0,0,230,251,5,31,0,0,231,232,5,7,0,0,232,233,5,15,0,0,233,
  	234,3,38,19,0,234,235,5,16,0,0,235,238,3,32,16,0,236,237,5,8,0,0,237,
  	239,3,32,16,0,238,236,1,0,0,0,238,239,1,0,0,0,239,251,1,0,0,0,240,241,
  	5,9,0,0,241,242,5,15,0,0,242,243,3,38,19,0,243,244,5,16,0,0,244,245,3,
  	32,16,0,245,251,1,0,0,0,246,247,5,10,0,0,247,251,5,31,0,0,248,249,5,11,
  	0,0,249,251,5,31,0,0,250,217,1,0,0,0,250,224,1,0,0,0,250,225,1,0,0,0,
  	250,226,1,0,0,0,250,231,1,0,0,0,250,240,1,0,0,0,250,246,1,0,0,0,250,248,
  	1,0,0,0,251,33,1,0,0,0,252,253,3,52,26,0,253,35,1,0,0,0,254,255,3,52,
  	26,0,255,37,1,0,0,0,256,257,3,60,30,0,257,39,1,0,0,0,258,265,5,37,0,0,
  	259,260,5,13,0,0,260,261,3,34,17,0,261,262,5,14,0,0,262,264,1,0,0,0,263,
  	259,1,0,0,0,264,267,1,0,0,0,265,263,1,0,0,0,265,266,1,0,0,0,266,41,1,
  	0,0,0,267,265,1,0,0,0,268,269,7,2,0,0,269,43,1,0,0,0,270,275,3,34,17,
  	0,271,272,5,32,0,0,272,274,3,34,17,0,273,271,1,0,0,0,274,277,1,0,0,0,
  	275,273,1,0,0,0,275,276,1,0,0,0,276,45,1,0,0,0,277,275,1,0,0,0,278,279,
  	5,15,0,0,279,280,3,34,17,0,280,281,5,16,0,0,281,285,1,0,0,0,282,285,3,
  	40,20,0,283,285,3,42,21,0,284,278,1,0,0,0,284,282,1,0,0,0,284,283,1,0,
  	0,0,285,47,1,0,0,0,286,296,3,46,23,0,287,288,7,3,0,0,288,296,3,48,24,
  	0,289,290,5,37,0,0,290,292,5,15,0,0,291,293,3,44,22,0,292,291,1,0,0,0,
  	292,293,1,0,0,0,293,294,1,0,0,0,294,296,5,16,0,0,295,286,1,0,0,0,295,
  	287,1,0,0,0,295,289,1,0,0,0,296,49,1,0,0,0,297,302,3,48,24,0,298,299,
  	7,4,0,0,299,301,3,48,24,0,300,298,1,0,0,0,301,304,1,0,0,0,302,300,1,0,
  	0,0,302,303,1,0,0,0,303,51,1,0,0,0,304,302,1,0,0,0,305,310,3,50,25,0,
  	306,307,7,5,0,0,307,309,3,50,25,0,308,306,1,0,0,0,309,312,1,0,0,0,310,
  	308,1,0,0,0,310,311,1,0,0,0,311,53,1,0,0,0,312,310,1,0,0,0,313,318,3,
  	52,26,0,314,315,7,6,0,0,315,317,3,52,26,0,316,314,1,0,0,0,317,320,1,0,
  	0,0,318,316,1,0,0,0,318,319,1,0,0,0,319,55,1,0,0,0,320,318,1,0,0,0,321,
  	326,3,54,27,0,322,323,7,7,0,0,323,325,3,54,27,0,324,322,1,0,0,0,325,328,
  	1,0,0,0,326,324,1,0,0,0,326,327,1,0,0,0,327,57,1,0,0,0,328,326,1,0,0,
  	0,329,334,3,56,28,0,330,331,5,29,0,0,331,333,3,56,28,0,332,330,1,0,0,
  	0,333,336,1,0,0,0,334,332,1,0,0,0,334,335,1,0,0,0,335,59,1,0,0,0,336,
  	334,1,0,0,0,337,342,3,58,29,0,338,339,5,30,0,0,339,341,3,58,29,0,340,
  	338,1,0,0,0,341,344,1,0,0,0,342,340,1,0,0,0,342,343,1,0,0,0,343,61,1,
  	0,0,0,344,342,1,0,0,0,39,64,66,72,81,94,107,110,113,118,123,127,141,146,
  	154,157,164,170,178,184,191,199,202,208,215,220,228,238,250,265,275,284,
  	292,295,302,310,318,326,334,342
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  helloParserStaticData = staticData.release();
}

}

HelloParser::HelloParser(TokenStream *input) : HelloParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

HelloParser::HelloParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  HelloParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *helloParserStaticData->atn, helloParserStaticData->decisionToDFA, helloParserStaticData->sharedContextCache, options);
}

HelloParser::~HelloParser() {
  delete _interpreter;
}

const atn::ATN& HelloParser::getATN() const {
  return *helloParserStaticData->atn;
}

std::string HelloParser::getGrammarFileName() const {
  return "Hello.g4";
}

const std::vector<std::string>& HelloParser::getRuleNames() const {
  return helloParserStaticData->ruleNames;
}

const dfa::Vocabulary& HelloParser::getVocabulary() const {
  return helloParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView HelloParser::getSerializedATN() const {
  return helloParserStaticData->serializedATN;
}


//----------------- CompUnitContext ------------------------------------------------------------------

HelloParser::CompUnitContext::CompUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::CompUnitContext::EOF() {
  return getToken(HelloParser::EOF, 0);
}

std::vector<HelloParser::DeclContext *> HelloParser::CompUnitContext::decl() {
  return getRuleContexts<HelloParser::DeclContext>();
}

HelloParser::DeclContext* HelloParser::CompUnitContext::decl(size_t i) {
  return getRuleContext<HelloParser::DeclContext>(i);
}

std::vector<HelloParser::FuncDefContext *> HelloParser::CompUnitContext::funcDef() {
  return getRuleContexts<HelloParser::FuncDefContext>();
}

HelloParser::FuncDefContext* HelloParser::CompUnitContext::funcDef(size_t i) {
  return getRuleContext<HelloParser::FuncDefContext>(i);
}


size_t HelloParser::CompUnitContext::getRuleIndex() const {
  return HelloParser::RuleCompUnit;
}


std::any HelloParser::CompUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitCompUnit(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::CompUnitContext* HelloParser::compUnit() {
  CompUnitContext *_localctx = _tracker.createInstance<CompUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, HelloParser::RuleCompUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(64); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(64);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(62);
        decl();
        break;
      }

      case 2: {
        setState(63);
        funcDef();
        break;
      }

      default:
        break;
      }
      setState(66); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 118) != 0));
    setState(68);
    match(HelloParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclContext ------------------------------------------------------------------

HelloParser::DeclContext::DeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::ConstdeclContext* HelloParser::DeclContext::constdecl() {
  return getRuleContext<HelloParser::ConstdeclContext>(0);
}

HelloParser::VardeclContext* HelloParser::DeclContext::vardecl() {
  return getRuleContext<HelloParser::VardeclContext>(0);
}


size_t HelloParser::DeclContext::getRuleIndex() const {
  return HelloParser::RuleDecl;
}


std::any HelloParser::DeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitDecl(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::DeclContext* HelloParser::decl() {
  DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
  enterRule(_localctx, 2, HelloParser::RuleDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(72);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HelloParser::CONST_KW: {
        enterOuterAlt(_localctx, 1);
        setState(70);
        constdecl();
        break;
      }

      case HelloParser::INT_KW:
      case HelloParser::CHAR_KW:
      case HelloParser::FLOAT_KW: {
        enterOuterAlt(_localctx, 2);
        setState(71);
        vardecl();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstdeclContext ------------------------------------------------------------------

HelloParser::ConstdeclContext::ConstdeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::ConstdeclContext::CONST_KW() {
  return getToken(HelloParser::CONST_KW, 0);
}

HelloParser::BTypeContext* HelloParser::ConstdeclContext::bType() {
  return getRuleContext<HelloParser::BTypeContext>(0);
}

std::vector<HelloParser::ConstDefContext *> HelloParser::ConstdeclContext::constDef() {
  return getRuleContexts<HelloParser::ConstDefContext>();
}

HelloParser::ConstDefContext* HelloParser::ConstdeclContext::constDef(size_t i) {
  return getRuleContext<HelloParser::ConstDefContext>(i);
}

tree::TerminalNode* HelloParser::ConstdeclContext::Semi() {
  return getToken(HelloParser::Semi, 0);
}

std::vector<tree::TerminalNode *> HelloParser::ConstdeclContext::Comma() {
  return getTokens(HelloParser::Comma);
}

tree::TerminalNode* HelloParser::ConstdeclContext::Comma(size_t i) {
  return getToken(HelloParser::Comma, i);
}


size_t HelloParser::ConstdeclContext::getRuleIndex() const {
  return HelloParser::RuleConstdecl;
}


std::any HelloParser::ConstdeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitConstdecl(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::ConstdeclContext* HelloParser::constdecl() {
  ConstdeclContext *_localctx = _tracker.createInstance<ConstdeclContext>(_ctx, getState());
  enterRule(_localctx, 4, HelloParser::RuleConstdecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(74);
    match(HelloParser::CONST_KW);
    setState(75);
    bType();
    setState(76);
    constDef();
    setState(81);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::Comma) {
      setState(77);
      match(HelloParser::Comma);
      setState(78);
      constDef();
      setState(83);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(84);
    match(HelloParser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BTypeContext ------------------------------------------------------------------

HelloParser::BTypeContext::BTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::BTypeContext::INT_KW() {
  return getToken(HelloParser::INT_KW, 0);
}

tree::TerminalNode* HelloParser::BTypeContext::FLOAT_KW() {
  return getToken(HelloParser::FLOAT_KW, 0);
}

tree::TerminalNode* HelloParser::BTypeContext::CHAR_KW() {
  return getToken(HelloParser::CHAR_KW, 0);
}


size_t HelloParser::BTypeContext::getRuleIndex() const {
  return HelloParser::RuleBType;
}


std::any HelloParser::BTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitBType(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::BTypeContext* HelloParser::bType() {
  BTypeContext *_localctx = _tracker.createInstance<BTypeContext>(_ctx, getState());
  enterRule(_localctx, 6, HelloParser::RuleBType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 52) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDefContext ------------------------------------------------------------------

HelloParser::ConstDefContext::ConstDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::ConstDefContext::Ident() {
  return getToken(HelloParser::Ident, 0);
}

tree::TerminalNode* HelloParser::ConstDefContext::Assign() {
  return getToken(HelloParser::Assign, 0);
}

HelloParser::ConstInitValContext* HelloParser::ConstDefContext::constInitVal() {
  return getRuleContext<HelloParser::ConstInitValContext>(0);
}

std::vector<tree::TerminalNode *> HelloParser::ConstDefContext::LeftBracket() {
  return getTokens(HelloParser::LeftBracket);
}

tree::TerminalNode* HelloParser::ConstDefContext::LeftBracket(size_t i) {
  return getToken(HelloParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> HelloParser::ConstDefContext::IntConst() {
  return getTokens(HelloParser::IntConst);
}

tree::TerminalNode* HelloParser::ConstDefContext::IntConst(size_t i) {
  return getToken(HelloParser::IntConst, i);
}

std::vector<tree::TerminalNode *> HelloParser::ConstDefContext::RightBracket() {
  return getTokens(HelloParser::RightBracket);
}

tree::TerminalNode* HelloParser::ConstDefContext::RightBracket(size_t i) {
  return getToken(HelloParser::RightBracket, i);
}


size_t HelloParser::ConstDefContext::getRuleIndex() const {
  return HelloParser::RuleConstDef;
}


std::any HelloParser::ConstDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitConstDef(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::ConstDefContext* HelloParser::constDef() {
  ConstDefContext *_localctx = _tracker.createInstance<ConstDefContext>(_ctx, getState());
  enterRule(_localctx, 8, HelloParser::RuleConstDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    match(HelloParser::Ident);
    setState(94);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::LeftBracket) {
      setState(89);
      match(HelloParser::LeftBracket);
      setState(90);
      match(HelloParser::IntConst);
      setState(91);
      match(HelloParser::RightBracket);
      setState(96);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(97);
    match(HelloParser::Assign);
    setState(98);
    constInitVal();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstInitValContext ------------------------------------------------------------------

HelloParser::ConstInitValContext::ConstInitValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::ConstExpContext* HelloParser::ConstInitValContext::constExp() {
  return getRuleContext<HelloParser::ConstExpContext>(0);
}

tree::TerminalNode* HelloParser::ConstInitValContext::LeftBrace() {
  return getToken(HelloParser::LeftBrace, 0);
}

tree::TerminalNode* HelloParser::ConstInitValContext::RightBrace() {
  return getToken(HelloParser::RightBrace, 0);
}

std::vector<HelloParser::ConstInitValContext *> HelloParser::ConstInitValContext::constInitVal() {
  return getRuleContexts<HelloParser::ConstInitValContext>();
}

HelloParser::ConstInitValContext* HelloParser::ConstInitValContext::constInitVal(size_t i) {
  return getRuleContext<HelloParser::ConstInitValContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::ConstInitValContext::Comma() {
  return getTokens(HelloParser::Comma);
}

tree::TerminalNode* HelloParser::ConstInitValContext::Comma(size_t i) {
  return getToken(HelloParser::Comma, i);
}


size_t HelloParser::ConstInitValContext::getRuleIndex() const {
  return HelloParser::RuleConstInitVal;
}


std::any HelloParser::ConstInitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitConstInitVal(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::ConstInitValContext* HelloParser::constInitVal() {
  ConstInitValContext *_localctx = _tracker.createInstance<ConstInitValContext>(_ctx, getState());
  enterRule(_localctx, 10, HelloParser::RuleConstInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(113);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HelloParser::LeftParen:
      case HelloParser::Plus:
      case HelloParser::Minus:
      case HelloParser::Not:
      case HelloParser::Ident:
      case HelloParser::IntConst:
      case HelloParser::FloatConst:
      case HelloParser::CharConst: {
        enterOuterAlt(_localctx, 1);
        setState(100);
        constExp();
        break;
      }

      case HelloParser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(101);
        match(HelloParser::LeftBrace);
        setState(110);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 72062438761988096) != 0)) {
          setState(102);
          constInitVal();
          setState(107);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == HelloParser::Comma) {
            setState(103);
            match(HelloParser::Comma);
            setState(104);
            constInitVal();
            setState(109);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(112);
        match(HelloParser::RightBrace);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VardeclContext ------------------------------------------------------------------

HelloParser::VardeclContext::VardeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::BTypeContext* HelloParser::VardeclContext::bType() {
  return getRuleContext<HelloParser::BTypeContext>(0);
}

tree::TerminalNode* HelloParser::VardeclContext::Semi() {
  return getToken(HelloParser::Semi, 0);
}

std::vector<HelloParser::VarDefContext *> HelloParser::VardeclContext::varDef() {
  return getRuleContexts<HelloParser::VarDefContext>();
}

HelloParser::VarDefContext* HelloParser::VardeclContext::varDef(size_t i) {
  return getRuleContext<HelloParser::VarDefContext>(i);
}

std::vector<HelloParser::VarDefArrayContext *> HelloParser::VardeclContext::varDefArray() {
  return getRuleContexts<HelloParser::VarDefArrayContext>();
}

HelloParser::VarDefArrayContext* HelloParser::VardeclContext::varDefArray(size_t i) {
  return getRuleContext<HelloParser::VarDefArrayContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::VardeclContext::Comma() {
  return getTokens(HelloParser::Comma);
}

tree::TerminalNode* HelloParser::VardeclContext::Comma(size_t i) {
  return getToken(HelloParser::Comma, i);
}


size_t HelloParser::VardeclContext::getRuleIndex() const {
  return HelloParser::RuleVardecl;
}


std::any HelloParser::VardeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitVardecl(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::VardeclContext* HelloParser::vardecl() {
  VardeclContext *_localctx = _tracker.createInstance<VardeclContext>(_ctx, getState());
  enterRule(_localctx, 12, HelloParser::RuleVardecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(115);
    bType();
    setState(118);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      setState(116);
      varDef();
      break;
    }

    case 2: {
      setState(117);
      varDefArray();
      break;
    }

    default:
      break;
    }
    setState(127);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::Comma) {
      setState(120);
      match(HelloParser::Comma);
      setState(123);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
      case 1: {
        setState(121);
        varDef();
        break;
      }

      case 2: {
        setState(122);
        varDefArray();
        break;
      }

      default:
        break;
      }
      setState(129);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(130);
    match(HelloParser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDefArrayContext ------------------------------------------------------------------

HelloParser::VarDefArrayContext::VarDefArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::VarDefArrayContext::Ident() {
  return getToken(HelloParser::Ident, 0);
}

std::vector<tree::TerminalNode *> HelloParser::VarDefArrayContext::LeftBracket() {
  return getTokens(HelloParser::LeftBracket);
}

tree::TerminalNode* HelloParser::VarDefArrayContext::LeftBracket(size_t i) {
  return getToken(HelloParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> HelloParser::VarDefArrayContext::IntConst() {
  return getTokens(HelloParser::IntConst);
}

tree::TerminalNode* HelloParser::VarDefArrayContext::IntConst(size_t i) {
  return getToken(HelloParser::IntConst, i);
}

std::vector<tree::TerminalNode *> HelloParser::VarDefArrayContext::RightBracket() {
  return getTokens(HelloParser::RightBracket);
}

tree::TerminalNode* HelloParser::VarDefArrayContext::RightBracket(size_t i) {
  return getToken(HelloParser::RightBracket, i);
}

tree::TerminalNode* HelloParser::VarDefArrayContext::Assign() {
  return getToken(HelloParser::Assign, 0);
}

HelloParser::ConstInitValArrayContext* HelloParser::VarDefArrayContext::constInitValArray() {
  return getRuleContext<HelloParser::ConstInitValArrayContext>(0);
}


size_t HelloParser::VarDefArrayContext::getRuleIndex() const {
  return HelloParser::RuleVarDefArray;
}


std::any HelloParser::VarDefArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitVarDefArray(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::VarDefArrayContext* HelloParser::varDefArray() {
  VarDefArrayContext *_localctx = _tracker.createInstance<VarDefArrayContext>(_ctx, getState());
  enterRule(_localctx, 14, HelloParser::RuleVarDefArray);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(132);
    match(HelloParser::Ident);
    setState(133);
    match(HelloParser::LeftBracket);
    setState(134);
    match(HelloParser::IntConst);
    setState(135);
    match(HelloParser::RightBracket);
    setState(141);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::LeftBracket) {
      setState(136);
      match(HelloParser::LeftBracket);
      setState(137);
      match(HelloParser::IntConst);
      setState(138);
      match(HelloParser::RightBracket);
      setState(143);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(146);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HelloParser::Assign) {
      setState(144);
      match(HelloParser::Assign);
      setState(145);
      constInitValArray();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstInitValArrayContext ------------------------------------------------------------------

HelloParser::ConstInitValArrayContext::ConstInitValArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::ConstInitValArrayContext::LeftBrace() {
  return getToken(HelloParser::LeftBrace, 0);
}

tree::TerminalNode* HelloParser::ConstInitValArrayContext::RightBrace() {
  return getToken(HelloParser::RightBrace, 0);
}

std::vector<HelloParser::ConstInitValContext *> HelloParser::ConstInitValArrayContext::constInitVal() {
  return getRuleContexts<HelloParser::ConstInitValContext>();
}

HelloParser::ConstInitValContext* HelloParser::ConstInitValArrayContext::constInitVal(size_t i) {
  return getRuleContext<HelloParser::ConstInitValContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::ConstInitValArrayContext::Comma() {
  return getTokens(HelloParser::Comma);
}

tree::TerminalNode* HelloParser::ConstInitValArrayContext::Comma(size_t i) {
  return getToken(HelloParser::Comma, i);
}


size_t HelloParser::ConstInitValArrayContext::getRuleIndex() const {
  return HelloParser::RuleConstInitValArray;
}


std::any HelloParser::ConstInitValArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitConstInitValArray(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::ConstInitValArrayContext* HelloParser::constInitValArray() {
  ConstInitValArrayContext *_localctx = _tracker.createInstance<ConstInitValArrayContext>(_ctx, getState());
  enterRule(_localctx, 16, HelloParser::RuleConstInitValArray);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(148);
    match(HelloParser::LeftBrace);
    setState(157);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72062438761988096) != 0)) {
      setState(149);
      constInitVal();
      setState(154);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == HelloParser::Comma) {
        setState(150);
        match(HelloParser::Comma);
        setState(151);
        constInitVal();
        setState(156);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(159);
    match(HelloParser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDefContext ------------------------------------------------------------------

HelloParser::VarDefContext::VarDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::VarDefContext::Ident() {
  return getToken(HelloParser::Ident, 0);
}

tree::TerminalNode* HelloParser::VarDefContext::Assign() {
  return getToken(HelloParser::Assign, 0);
}

HelloParser::ConstInitValContext* HelloParser::VarDefContext::constInitVal() {
  return getRuleContext<HelloParser::ConstInitValContext>(0);
}


size_t HelloParser::VarDefContext::getRuleIndex() const {
  return HelloParser::RuleVarDef;
}


std::any HelloParser::VarDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitVarDef(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::VarDefContext* HelloParser::varDef() {
  VarDefContext *_localctx = _tracker.createInstance<VarDefContext>(_ctx, getState());
  enterRule(_localctx, 18, HelloParser::RuleVarDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(161);
    match(HelloParser::Ident);
    setState(164);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HelloParser::Assign) {
      setState(162);
      match(HelloParser::Assign);
      setState(163);
      constInitVal();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

HelloParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::FuncTypeContext* HelloParser::FuncDefContext::funcType() {
  return getRuleContext<HelloParser::FuncTypeContext>(0);
}

tree::TerminalNode* HelloParser::FuncDefContext::Ident() {
  return getToken(HelloParser::Ident, 0);
}

tree::TerminalNode* HelloParser::FuncDefContext::LeftParen() {
  return getToken(HelloParser::LeftParen, 0);
}

tree::TerminalNode* HelloParser::FuncDefContext::RightParen() {
  return getToken(HelloParser::RightParen, 0);
}

HelloParser::BlockContext* HelloParser::FuncDefContext::block() {
  return getRuleContext<HelloParser::BlockContext>(0);
}

HelloParser::FuncFParamsContext* HelloParser::FuncDefContext::funcFParams() {
  return getRuleContext<HelloParser::FuncFParamsContext>(0);
}


size_t HelloParser::FuncDefContext::getRuleIndex() const {
  return HelloParser::RuleFuncDef;
}


std::any HelloParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::FuncDefContext* HelloParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 20, HelloParser::RuleFuncDef);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(166);
    funcType();
    setState(167);
    match(HelloParser::Ident);
    setState(168);
    match(HelloParser::LeftParen);
    setState(170);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
    case 1: {
      setState(169);
      funcFParams();
      break;
    }

    default:
      break;
    }
    setState(172);
    match(HelloParser::RightParen);
    setState(173);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncTypeContext ------------------------------------------------------------------

HelloParser::FuncTypeContext::FuncTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::FuncTypeContext::VOID_KW() {
  return getToken(HelloParser::VOID_KW, 0);
}

tree::TerminalNode* HelloParser::FuncTypeContext::INT_KW() {
  return getToken(HelloParser::INT_KW, 0);
}

tree::TerminalNode* HelloParser::FuncTypeContext::FLOAT_KW() {
  return getToken(HelloParser::FLOAT_KW, 0);
}

tree::TerminalNode* HelloParser::FuncTypeContext::CHAR_KW() {
  return getToken(HelloParser::CHAR_KW, 0);
}


size_t HelloParser::FuncTypeContext::getRuleIndex() const {
  return HelloParser::RuleFuncType;
}


std::any HelloParser::FuncTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitFuncType(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::FuncTypeContext* HelloParser::funcType() {
  FuncTypeContext *_localctx = _tracker.createInstance<FuncTypeContext>(_ctx, getState());
  enterRule(_localctx, 22, HelloParser::RuleFuncType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(175);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 116) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamsContext ------------------------------------------------------------------

HelloParser::FuncFParamsContext::FuncFParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::FuncFParamContext *> HelloParser::FuncFParamsContext::funcFParam() {
  return getRuleContexts<HelloParser::FuncFParamContext>();
}

HelloParser::FuncFParamContext* HelloParser::FuncFParamsContext::funcFParam(size_t i) {
  return getRuleContext<HelloParser::FuncFParamContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::FuncFParamsContext::Comma() {
  return getTokens(HelloParser::Comma);
}

tree::TerminalNode* HelloParser::FuncFParamsContext::Comma(size_t i) {
  return getToken(HelloParser::Comma, i);
}


size_t HelloParser::FuncFParamsContext::getRuleIndex() const {
  return HelloParser::RuleFuncFParams;
}


std::any HelloParser::FuncFParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitFuncFParams(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::FuncFParamsContext* HelloParser::funcFParams() {
  FuncFParamsContext *_localctx = _tracker.createInstance<FuncFParamsContext>(_ctx, getState());
  enterRule(_localctx, 24, HelloParser::RuleFuncFParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(178);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 52) != 0)) {
      setState(177);
      funcFParam();
    }
    setState(184);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::Comma) {
      setState(180);
      match(HelloParser::Comma);
      setState(181);
      funcFParam();
      setState(186);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamContext ------------------------------------------------------------------

HelloParser::FuncFParamContext::FuncFParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::BTypeContext* HelloParser::FuncFParamContext::bType() {
  return getRuleContext<HelloParser::BTypeContext>(0);
}

tree::TerminalNode* HelloParser::FuncFParamContext::Ident() {
  return getToken(HelloParser::Ident, 0);
}

std::vector<tree::TerminalNode *> HelloParser::FuncFParamContext::LeftBracket() {
  return getTokens(HelloParser::LeftBracket);
}

tree::TerminalNode* HelloParser::FuncFParamContext::LeftBracket(size_t i) {
  return getToken(HelloParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> HelloParser::FuncFParamContext::RightBracket() {
  return getTokens(HelloParser::RightBracket);
}

tree::TerminalNode* HelloParser::FuncFParamContext::RightBracket(size_t i) {
  return getToken(HelloParser::RightBracket, i);
}

std::vector<tree::TerminalNode *> HelloParser::FuncFParamContext::IntConst() {
  return getTokens(HelloParser::IntConst);
}

tree::TerminalNode* HelloParser::FuncFParamContext::IntConst(size_t i) {
  return getToken(HelloParser::IntConst, i);
}


size_t HelloParser::FuncFParamContext::getRuleIndex() const {
  return HelloParser::RuleFuncFParam;
}


std::any HelloParser::FuncFParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitFuncFParam(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::FuncFParamContext* HelloParser::funcFParam() {
  FuncFParamContext *_localctx = _tracker.createInstance<FuncFParamContext>(_ctx, getState());
  enterRule(_localctx, 26, HelloParser::RuleFuncFParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(187);
    bType();
    setState(188);
    match(HelloParser::Ident);
    setState(202);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HelloParser::LeftBracket) {
      setState(189);
      match(HelloParser::LeftBracket);
      setState(191);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == HelloParser::IntConst) {
        setState(190);
        match(HelloParser::IntConst);
      }
      setState(193);
      match(HelloParser::RightBracket);
      setState(199);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == HelloParser::LeftBracket) {
        setState(194);
        match(HelloParser::LeftBracket);
        setState(195);
        match(HelloParser::IntConst);
        setState(196);
        match(HelloParser::RightBracket);
        setState(201);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

HelloParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::BlockContext::LeftBrace() {
  return getToken(HelloParser::LeftBrace, 0);
}

tree::TerminalNode* HelloParser::BlockContext::RightBrace() {
  return getToken(HelloParser::RightBrace, 0);
}

std::vector<HelloParser::BlockItemContext *> HelloParser::BlockContext::blockItem() {
  return getRuleContexts<HelloParser::BlockItemContext>();
}

HelloParser::BlockItemContext* HelloParser::BlockContext::blockItem(size_t i) {
  return getRuleContext<HelloParser::BlockItemContext>(i);
}


size_t HelloParser::BlockContext::getRuleIndex() const {
  return HelloParser::RuleBlock;
}


std::any HelloParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::BlockContext* HelloParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 28, HelloParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(204);
    match(HelloParser::LeftBrace);
    setState(208);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72062440909479606) != 0)) {
      setState(205);
      blockItem();
      setState(210);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(211);
    match(HelloParser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

HelloParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::DeclContext* HelloParser::BlockItemContext::decl() {
  return getRuleContext<HelloParser::DeclContext>(0);
}

HelloParser::StmtContext* HelloParser::BlockItemContext::stmt() {
  return getRuleContext<HelloParser::StmtContext>(0);
}


size_t HelloParser::BlockItemContext::getRuleIndex() const {
  return HelloParser::RuleBlockItem;
}


std::any HelloParser::BlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitBlockItem(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::BlockItemContext* HelloParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 30, HelloParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(215);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HelloParser::CONST_KW:
      case HelloParser::INT_KW:
      case HelloParser::CHAR_KW:
      case HelloParser::FLOAT_KW: {
        enterOuterAlt(_localctx, 1);
        setState(213);
        decl();
        break;
      }

      case HelloParser::IF_KW:
      case HelloParser::WHILE_KW:
      case HelloParser::BREAK_KW:
      case HelloParser::CONTINUE_KW:
      case HelloParser::RETURN_KW:
      case HelloParser::LeftParen:
      case HelloParser::Plus:
      case HelloParser::Minus:
      case HelloParser::Not:
      case HelloParser::Semi:
      case HelloParser::LeftBrace:
      case HelloParser::Ident:
      case HelloParser::IntConst:
      case HelloParser::FloatConst:
      case HelloParser::CharConst: {
        enterOuterAlt(_localctx, 2);
        setState(214);
        stmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

HelloParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::ExpContext *> HelloParser::StmtContext::exp() {
  return getRuleContexts<HelloParser::ExpContext>();
}

HelloParser::ExpContext* HelloParser::StmtContext::exp(size_t i) {
  return getRuleContext<HelloParser::ExpContext>(i);
}

tree::TerminalNode* HelloParser::StmtContext::Semi() {
  return getToken(HelloParser::Semi, 0);
}

tree::TerminalNode* HelloParser::StmtContext::Assign() {
  return getToken(HelloParser::Assign, 0);
}

HelloParser::BlockContext* HelloParser::StmtContext::block() {
  return getRuleContext<HelloParser::BlockContext>(0);
}

tree::TerminalNode* HelloParser::StmtContext::RETURN_KW() {
  return getToken(HelloParser::RETURN_KW, 0);
}

tree::TerminalNode* HelloParser::StmtContext::IF_KW() {
  return getToken(HelloParser::IF_KW, 0);
}

tree::TerminalNode* HelloParser::StmtContext::LeftParen() {
  return getToken(HelloParser::LeftParen, 0);
}

HelloParser::CondContext* HelloParser::StmtContext::cond() {
  return getRuleContext<HelloParser::CondContext>(0);
}

tree::TerminalNode* HelloParser::StmtContext::RightParen() {
  return getToken(HelloParser::RightParen, 0);
}

std::vector<HelloParser::StmtContext *> HelloParser::StmtContext::stmt() {
  return getRuleContexts<HelloParser::StmtContext>();
}

HelloParser::StmtContext* HelloParser::StmtContext::stmt(size_t i) {
  return getRuleContext<HelloParser::StmtContext>(i);
}

tree::TerminalNode* HelloParser::StmtContext::ELSE_KW() {
  return getToken(HelloParser::ELSE_KW, 0);
}

tree::TerminalNode* HelloParser::StmtContext::WHILE_KW() {
  return getToken(HelloParser::WHILE_KW, 0);
}

tree::TerminalNode* HelloParser::StmtContext::BREAK_KW() {
  return getToken(HelloParser::BREAK_KW, 0);
}

tree::TerminalNode* HelloParser::StmtContext::CONTINUE_KW() {
  return getToken(HelloParser::CONTINUE_KW, 0);
}


size_t HelloParser::StmtContext::getRuleIndex() const {
  return HelloParser::RuleStmt;
}


std::any HelloParser::StmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitStmt(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::StmtContext* HelloParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 32, HelloParser::RuleStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(250);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HelloParser::LeftParen:
      case HelloParser::Plus:
      case HelloParser::Minus:
      case HelloParser::Not:
      case HelloParser::Ident:
      case HelloParser::IntConst:
      case HelloParser::FloatConst:
      case HelloParser::CharConst: {
        enterOuterAlt(_localctx, 1);
        setState(217);
        exp();
        setState(220);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == HelloParser::Assign) {
          setState(218);
          match(HelloParser::Assign);
          setState(219);
          exp();
        }
        setState(222);
        match(HelloParser::Semi);
        break;
      }

      case HelloParser::Semi: {
        enterOuterAlt(_localctx, 2);
        setState(224);
        match(HelloParser::Semi);
        break;
      }

      case HelloParser::LeftBrace: {
        enterOuterAlt(_localctx, 3);
        setState(225);
        block();
        break;
      }

      case HelloParser::RETURN_KW: {
        enterOuterAlt(_localctx, 4);
        setState(226);
        match(HelloParser::RETURN_KW);
        setState(228);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 72062404402249728) != 0)) {
          setState(227);
          exp();
        }
        setState(230);
        match(HelloParser::Semi);
        break;
      }

      case HelloParser::IF_KW: {
        enterOuterAlt(_localctx, 5);
        setState(231);
        match(HelloParser::IF_KW);
        setState(232);
        match(HelloParser::LeftParen);
        setState(233);
        cond();
        setState(234);
        match(HelloParser::RightParen);
        setState(235);
        stmt();
        setState(238);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
        case 1: {
          setState(236);
          match(HelloParser::ELSE_KW);
          setState(237);
          stmt();
          break;
        }

        default:
          break;
        }
        break;
      }

      case HelloParser::WHILE_KW: {
        enterOuterAlt(_localctx, 6);
        setState(240);
        match(HelloParser::WHILE_KW);
        setState(241);
        match(HelloParser::LeftParen);
        setState(242);
        cond();
        setState(243);
        match(HelloParser::RightParen);
        setState(244);
        stmt();
        break;
      }

      case HelloParser::BREAK_KW: {
        enterOuterAlt(_localctx, 7);
        setState(246);
        match(HelloParser::BREAK_KW);
        setState(247);
        match(HelloParser::Semi);
        break;
      }

      case HelloParser::CONTINUE_KW: {
        enterOuterAlt(_localctx, 8);
        setState(248);
        match(HelloParser::CONTINUE_KW);
        setState(249);
        match(HelloParser::Semi);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpContext ------------------------------------------------------------------

HelloParser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::AddExpContext* HelloParser::ExpContext::addExp() {
  return getRuleContext<HelloParser::AddExpContext>(0);
}


size_t HelloParser::ExpContext::getRuleIndex() const {
  return HelloParser::RuleExp;
}


std::any HelloParser::ExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::ExpContext* HelloParser::exp() {
  ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, getState());
  enterRule(_localctx, 34, HelloParser::RuleExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(252);
    addExp();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstExpContext ------------------------------------------------------------------

HelloParser::ConstExpContext::ConstExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::AddExpContext* HelloParser::ConstExpContext::addExp() {
  return getRuleContext<HelloParser::AddExpContext>(0);
}


size_t HelloParser::ConstExpContext::getRuleIndex() const {
  return HelloParser::RuleConstExp;
}


std::any HelloParser::ConstExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitConstExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::ConstExpContext* HelloParser::constExp() {
  ConstExpContext *_localctx = _tracker.createInstance<ConstExpContext>(_ctx, getState());
  enterRule(_localctx, 36, HelloParser::RuleConstExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(254);
    addExp();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CondContext ------------------------------------------------------------------

HelloParser::CondContext::CondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::LOrExpContext* HelloParser::CondContext::lOrExp() {
  return getRuleContext<HelloParser::LOrExpContext>(0);
}


size_t HelloParser::CondContext::getRuleIndex() const {
  return HelloParser::RuleCond;
}


std::any HelloParser::CondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitCond(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::CondContext* HelloParser::cond() {
  CondContext *_localctx = _tracker.createInstance<CondContext>(_ctx, getState());
  enterRule(_localctx, 38, HelloParser::RuleCond);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(256);
    lOrExp();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LValContext ------------------------------------------------------------------

HelloParser::LValContext::LValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::LValContext::Ident() {
  return getToken(HelloParser::Ident, 0);
}

std::vector<tree::TerminalNode *> HelloParser::LValContext::LeftBracket() {
  return getTokens(HelloParser::LeftBracket);
}

tree::TerminalNode* HelloParser::LValContext::LeftBracket(size_t i) {
  return getToken(HelloParser::LeftBracket, i);
}

std::vector<HelloParser::ExpContext *> HelloParser::LValContext::exp() {
  return getRuleContexts<HelloParser::ExpContext>();
}

HelloParser::ExpContext* HelloParser::LValContext::exp(size_t i) {
  return getRuleContext<HelloParser::ExpContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::LValContext::RightBracket() {
  return getTokens(HelloParser::RightBracket);
}

tree::TerminalNode* HelloParser::LValContext::RightBracket(size_t i) {
  return getToken(HelloParser::RightBracket, i);
}


size_t HelloParser::LValContext::getRuleIndex() const {
  return HelloParser::RuleLVal;
}


std::any HelloParser::LValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitLVal(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::LValContext* HelloParser::lVal() {
  LValContext *_localctx = _tracker.createInstance<LValContext>(_ctx, getState());
  enterRule(_localctx, 40, HelloParser::RuleLVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(258);
    match(HelloParser::Ident);
    setState(265);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::LeftBracket) {
      setState(259);
      match(HelloParser::LeftBracket);
      setState(260);
      exp();
      setState(261);
      match(HelloParser::RightBracket);
      setState(267);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

HelloParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::NumberContext::IntConst() {
  return getToken(HelloParser::IntConst, 0);
}

tree::TerminalNode* HelloParser::NumberContext::FloatConst() {
  return getToken(HelloParser::FloatConst, 0);
}

tree::TerminalNode* HelloParser::NumberContext::CharConst() {
  return getToken(HelloParser::CharConst, 0);
}


size_t HelloParser::NumberContext::getRuleIndex() const {
  return HelloParser::RuleNumber;
}


std::any HelloParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::NumberContext* HelloParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 42, HelloParser::RuleNumber);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(268);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 72062266962345984) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncRParamsContext ------------------------------------------------------------------

HelloParser::FuncRParamsContext::FuncRParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::ExpContext *> HelloParser::FuncRParamsContext::exp() {
  return getRuleContexts<HelloParser::ExpContext>();
}

HelloParser::ExpContext* HelloParser::FuncRParamsContext::exp(size_t i) {
  return getRuleContext<HelloParser::ExpContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::FuncRParamsContext::Comma() {
  return getTokens(HelloParser::Comma);
}

tree::TerminalNode* HelloParser::FuncRParamsContext::Comma(size_t i) {
  return getToken(HelloParser::Comma, i);
}


size_t HelloParser::FuncRParamsContext::getRuleIndex() const {
  return HelloParser::RuleFuncRParams;
}


std::any HelloParser::FuncRParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitFuncRParams(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::FuncRParamsContext* HelloParser::funcRParams() {
  FuncRParamsContext *_localctx = _tracker.createInstance<FuncRParamsContext>(_ctx, getState());
  enterRule(_localctx, 44, HelloParser::RuleFuncRParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(270);
    exp();
    setState(275);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::Comma) {
      setState(271);
      match(HelloParser::Comma);
      setState(272);
      exp();
      setState(277);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpContext ------------------------------------------------------------------

HelloParser::PrimaryExpContext::PrimaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::PrimaryExpContext::LeftParen() {
  return getToken(HelloParser::LeftParen, 0);
}

HelloParser::ExpContext* HelloParser::PrimaryExpContext::exp() {
  return getRuleContext<HelloParser::ExpContext>(0);
}

tree::TerminalNode* HelloParser::PrimaryExpContext::RightParen() {
  return getToken(HelloParser::RightParen, 0);
}

HelloParser::LValContext* HelloParser::PrimaryExpContext::lVal() {
  return getRuleContext<HelloParser::LValContext>(0);
}

HelloParser::NumberContext* HelloParser::PrimaryExpContext::number() {
  return getRuleContext<HelloParser::NumberContext>(0);
}


size_t HelloParser::PrimaryExpContext::getRuleIndex() const {
  return HelloParser::RulePrimaryExp;
}


std::any HelloParser::PrimaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitPrimaryExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::PrimaryExpContext* HelloParser::primaryExp() {
  PrimaryExpContext *_localctx = _tracker.createInstance<PrimaryExpContext>(_ctx, getState());
  enterRule(_localctx, 46, HelloParser::RulePrimaryExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(284);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HelloParser::LeftParen: {
        enterOuterAlt(_localctx, 1);
        setState(278);
        match(HelloParser::LeftParen);
        setState(279);
        exp();
        setState(280);
        match(HelloParser::RightParen);
        break;
      }

      case HelloParser::Ident: {
        enterOuterAlt(_localctx, 2);
        setState(282);
        lVal();
        break;
      }

      case HelloParser::IntConst:
      case HelloParser::FloatConst:
      case HelloParser::CharConst: {
        enterOuterAlt(_localctx, 3);
        setState(283);
        number();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpContext ------------------------------------------------------------------

HelloParser::UnaryExpContext::UnaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::PrimaryExpContext* HelloParser::UnaryExpContext::primaryExp() {
  return getRuleContext<HelloParser::PrimaryExpContext>(0);
}

HelloParser::UnaryExpContext* HelloParser::UnaryExpContext::unaryExp() {
  return getRuleContext<HelloParser::UnaryExpContext>(0);
}

tree::TerminalNode* HelloParser::UnaryExpContext::Plus() {
  return getToken(HelloParser::Plus, 0);
}

tree::TerminalNode* HelloParser::UnaryExpContext::Minus() {
  return getToken(HelloParser::Minus, 0);
}

tree::TerminalNode* HelloParser::UnaryExpContext::Not() {
  return getToken(HelloParser::Not, 0);
}

tree::TerminalNode* HelloParser::UnaryExpContext::Ident() {
  return getToken(HelloParser::Ident, 0);
}

tree::TerminalNode* HelloParser::UnaryExpContext::LeftParen() {
  return getToken(HelloParser::LeftParen, 0);
}

tree::TerminalNode* HelloParser::UnaryExpContext::RightParen() {
  return getToken(HelloParser::RightParen, 0);
}

HelloParser::FuncRParamsContext* HelloParser::UnaryExpContext::funcRParams() {
  return getRuleContext<HelloParser::FuncRParamsContext>(0);
}


size_t HelloParser::UnaryExpContext::getRuleIndex() const {
  return HelloParser::RuleUnaryExp;
}


std::any HelloParser::UnaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitUnaryExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::UnaryExpContext* HelloParser::unaryExp() {
  UnaryExpContext *_localctx = _tracker.createInstance<UnaryExpContext>(_ctx, getState());
  enterRule(_localctx, 48, HelloParser::RuleUnaryExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(295);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(286);
      primaryExp();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(287);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 917504) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(288);
      unaryExp();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(289);
      match(HelloParser::Ident);
      setState(290);
      match(HelloParser::LeftParen);
      setState(292);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 72062404402249728) != 0)) {
        setState(291);
        funcRParams();
      }
      setState(294);
      match(HelloParser::RightParen);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulExpContext ------------------------------------------------------------------

HelloParser::MulExpContext::MulExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::UnaryExpContext *> HelloParser::MulExpContext::unaryExp() {
  return getRuleContexts<HelloParser::UnaryExpContext>();
}

HelloParser::UnaryExpContext* HelloParser::MulExpContext::unaryExp(size_t i) {
  return getRuleContext<HelloParser::UnaryExpContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::MulExpContext::Star() {
  return getTokens(HelloParser::Star);
}

tree::TerminalNode* HelloParser::MulExpContext::Star(size_t i) {
  return getToken(HelloParser::Star, i);
}

std::vector<tree::TerminalNode *> HelloParser::MulExpContext::Div() {
  return getTokens(HelloParser::Div);
}

tree::TerminalNode* HelloParser::MulExpContext::Div(size_t i) {
  return getToken(HelloParser::Div, i);
}

std::vector<tree::TerminalNode *> HelloParser::MulExpContext::Mod() {
  return getTokens(HelloParser::Mod);
}

tree::TerminalNode* HelloParser::MulExpContext::Mod(size_t i) {
  return getToken(HelloParser::Mod, i);
}


size_t HelloParser::MulExpContext::getRuleIndex() const {
  return HelloParser::RuleMulExp;
}


std::any HelloParser::MulExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitMulExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::MulExpContext* HelloParser::mulExp() {
  MulExpContext *_localctx = _tracker.createInstance<MulExpContext>(_ctx, getState());
  enterRule(_localctx, 50, HelloParser::RuleMulExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(297);
    unaryExp();
    setState(302);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 7340032) != 0)) {
      setState(298);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 7340032) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(299);
      unaryExp();
      setState(304);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddExpContext ------------------------------------------------------------------

HelloParser::AddExpContext::AddExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::MulExpContext *> HelloParser::AddExpContext::mulExp() {
  return getRuleContexts<HelloParser::MulExpContext>();
}

HelloParser::MulExpContext* HelloParser::AddExpContext::mulExp(size_t i) {
  return getRuleContext<HelloParser::MulExpContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::AddExpContext::Plus() {
  return getTokens(HelloParser::Plus);
}

tree::TerminalNode* HelloParser::AddExpContext::Plus(size_t i) {
  return getToken(HelloParser::Plus, i);
}

std::vector<tree::TerminalNode *> HelloParser::AddExpContext::Minus() {
  return getTokens(HelloParser::Minus);
}

tree::TerminalNode* HelloParser::AddExpContext::Minus(size_t i) {
  return getToken(HelloParser::Minus, i);
}


size_t HelloParser::AddExpContext::getRuleIndex() const {
  return HelloParser::RuleAddExp;
}


std::any HelloParser::AddExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitAddExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::AddExpContext* HelloParser::addExp() {
  AddExpContext *_localctx = _tracker.createInstance<AddExpContext>(_ctx, getState());
  enterRule(_localctx, 52, HelloParser::RuleAddExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(305);
    mulExp();
    setState(310);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::Plus

    || _la == HelloParser::Minus) {
      setState(306);
      _la = _input->LA(1);
      if (!(_la == HelloParser::Plus

      || _la == HelloParser::Minus)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(307);
      mulExp();
      setState(312);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelExpContext ------------------------------------------------------------------

HelloParser::RelExpContext::RelExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::AddExpContext *> HelloParser::RelExpContext::addExp() {
  return getRuleContexts<HelloParser::AddExpContext>();
}

HelloParser::AddExpContext* HelloParser::RelExpContext::addExp(size_t i) {
  return getRuleContext<HelloParser::AddExpContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::RelExpContext::Less() {
  return getTokens(HelloParser::Less);
}

tree::TerminalNode* HelloParser::RelExpContext::Less(size_t i) {
  return getToken(HelloParser::Less, i);
}

std::vector<tree::TerminalNode *> HelloParser::RelExpContext::Greater() {
  return getTokens(HelloParser::Greater);
}

tree::TerminalNode* HelloParser::RelExpContext::Greater(size_t i) {
  return getToken(HelloParser::Greater, i);
}

std::vector<tree::TerminalNode *> HelloParser::RelExpContext::LessEqual() {
  return getTokens(HelloParser::LessEqual);
}

tree::TerminalNode* HelloParser::RelExpContext::LessEqual(size_t i) {
  return getToken(HelloParser::LessEqual, i);
}

std::vector<tree::TerminalNode *> HelloParser::RelExpContext::GreaterEqual() {
  return getTokens(HelloParser::GreaterEqual);
}

tree::TerminalNode* HelloParser::RelExpContext::GreaterEqual(size_t i) {
  return getToken(HelloParser::GreaterEqual, i);
}


size_t HelloParser::RelExpContext::getRuleIndex() const {
  return HelloParser::RuleRelExp;
}


std::any HelloParser::RelExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitRelExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::RelExpContext* HelloParser::relExp() {
  RelExpContext *_localctx = _tracker.createInstance<RelExpContext>(_ctx, getState());
  enterRule(_localctx, 54, HelloParser::RuleRelExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(313);
    addExp();
    setState(318);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 125829120) != 0)) {
      setState(314);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 125829120) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(315);
      addExp();
      setState(320);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqExpContext ------------------------------------------------------------------

HelloParser::EqExpContext::EqExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::RelExpContext *> HelloParser::EqExpContext::relExp() {
  return getRuleContexts<HelloParser::RelExpContext>();
}

HelloParser::RelExpContext* HelloParser::EqExpContext::relExp(size_t i) {
  return getRuleContext<HelloParser::RelExpContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::EqExpContext::Equal() {
  return getTokens(HelloParser::Equal);
}

tree::TerminalNode* HelloParser::EqExpContext::Equal(size_t i) {
  return getToken(HelloParser::Equal, i);
}

std::vector<tree::TerminalNode *> HelloParser::EqExpContext::NotEqual() {
  return getTokens(HelloParser::NotEqual);
}

tree::TerminalNode* HelloParser::EqExpContext::NotEqual(size_t i) {
  return getToken(HelloParser::NotEqual, i);
}


size_t HelloParser::EqExpContext::getRuleIndex() const {
  return HelloParser::RuleEqExp;
}


std::any HelloParser::EqExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitEqExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::EqExpContext* HelloParser::eqExp() {
  EqExpContext *_localctx = _tracker.createInstance<EqExpContext>(_ctx, getState());
  enterRule(_localctx, 56, HelloParser::RuleEqExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(321);
    relExp();
    setState(326);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::Equal

    || _la == HelloParser::NotEqual) {
      setState(322);
      _la = _input->LA(1);
      if (!(_la == HelloParser::Equal

      || _la == HelloParser::NotEqual)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(323);
      relExp();
      setState(328);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LAndExpContext ------------------------------------------------------------------

HelloParser::LAndExpContext::LAndExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::EqExpContext *> HelloParser::LAndExpContext::eqExp() {
  return getRuleContexts<HelloParser::EqExpContext>();
}

HelloParser::EqExpContext* HelloParser::LAndExpContext::eqExp(size_t i) {
  return getRuleContext<HelloParser::EqExpContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::LAndExpContext::AndAnd() {
  return getTokens(HelloParser::AndAnd);
}

tree::TerminalNode* HelloParser::LAndExpContext::AndAnd(size_t i) {
  return getToken(HelloParser::AndAnd, i);
}


size_t HelloParser::LAndExpContext::getRuleIndex() const {
  return HelloParser::RuleLAndExp;
}


std::any HelloParser::LAndExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitLAndExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::LAndExpContext* HelloParser::lAndExp() {
  LAndExpContext *_localctx = _tracker.createInstance<LAndExpContext>(_ctx, getState());
  enterRule(_localctx, 58, HelloParser::RuleLAndExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(329);
    eqExp();
    setState(334);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::AndAnd) {
      setState(330);
      match(HelloParser::AndAnd);
      setState(331);
      eqExp();
      setState(336);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LOrExpContext ------------------------------------------------------------------

HelloParser::LOrExpContext::LOrExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::LAndExpContext *> HelloParser::LOrExpContext::lAndExp() {
  return getRuleContexts<HelloParser::LAndExpContext>();
}

HelloParser::LAndExpContext* HelloParser::LOrExpContext::lAndExp(size_t i) {
  return getRuleContext<HelloParser::LAndExpContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::LOrExpContext::OrOr() {
  return getTokens(HelloParser::OrOr);
}

tree::TerminalNode* HelloParser::LOrExpContext::OrOr(size_t i) {
  return getToken(HelloParser::OrOr, i);
}


size_t HelloParser::LOrExpContext::getRuleIndex() const {
  return HelloParser::RuleLOrExp;
}


std::any HelloParser::LOrExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitLOrExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::LOrExpContext* HelloParser::lOrExp() {
  LOrExpContext *_localctx = _tracker.createInstance<LOrExpContext>(_ctx, getState());
  enterRule(_localctx, 60, HelloParser::RuleLOrExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(337);
    lAndExp();
    setState(342);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::OrOr) {
      setState(338);
      match(HelloParser::OrOr);
      setState(339);
      lAndExp();
      setState(344);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void HelloParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  helloParserInitialize();
#else
  ::antlr4::internal::call_once(helloParserOnceFlag, helloParserInitialize);
#endif
}
