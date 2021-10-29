
// Generated from CPP14Lexer.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"


namespace Ubpa {


class  CPP14Lexer : public antlr4::Lexer {
public:
  enum {
    Literal = 1, MultiLineMacro = 2, Directive = 3, Alignas = 4, Alignof = 5, 
    Asm = 6, Auto = 7, Bool = 8, Break = 9, Case = 10, Catch = 11, Char = 12, 
    Char16 = 13, Char32 = 14, Class = 15, Const = 16, Constexpr = 17, Const_cast = 18, 
    Continue = 19, Decltype = 20, Default = 21, Delete = 22, Do = 23, Double = 24, 
    Dynamic_cast = 25, Else = 26, Enum = 27, Explicit = 28, Export = 29, 
    Extern = 30, False_ = 31, Final = 32, Float = 33, For = 34, Friend = 35, 
    Goto = 36, If = 37, Inline = 38, Int = 39, Long = 40, Mutable = 41, 
    Namespace = 42, New = 43, Noexcept = 44, Nullptr = 45, Operator = 46, 
    Override = 47, Private = 48, Protected = 49, Public = 50, Register = 51, 
    Reinterpret_cast = 52, Return = 53, Short = 54, Signed = 55, Sizeof = 56, 
    Static = 57, Static_assert = 58, Static_cast = 59, Struct = 60, Switch = 61, 
    Template = 62, This = 63, Thread_local = 64, Throw = 65, True_ = 66, 
    Try = 67, Typedef = 68, Typeid_ = 69, Typename_ = 70, Union = 71, Unsigned = 72, 
    Using = 73, Virtual = 74, Void = 75, Volatile = 76, Wchar = 77, While = 78, 
    LeftParen = 79, RightParen = 80, LeftBracket = 81, RightBracket = 82, 
    LeftBrace = 83, RightBrace = 84, Plus = 85, Minus = 86, Star = 87, Div = 88, 
    Mod = 89, Caret = 90, And = 91, Or = 92, Tilde = 93, Not = 94, Assign = 95, 
    Less = 96, Greater = 97, PlusAssign = 98, MinusAssign = 99, StarAssign = 100, 
    DivAssign = 101, ModAssign = 102, XorAssign = 103, AndAssign = 104, 
    OrAssign = 105, LeftShift = 106, RightShift = 107, LeftShiftAssign = 108, 
    RightShiftAssign = 109, Equal = 110, NotEqual = 111, LessEqual = 112, 
    GreaterEqual = 113, AndAnd = 114, OrOr = 115, PlusPlus = 116, MinusMinus = 117, 
    Comma = 118, ArrowStar = 119, Arrow = 120, Question = 121, Colon = 122, 
    Doublecolon = 123, Semi = 124, Dot = 125, DotStar = 126, Ellipsis = 127, 
    Identifier = 128, IntegerLiteral = 129, DecimalLiteral = 130, OctalLiteral = 131, 
    HexadecimalLiteral = 132, BinaryLiteral = 133, Integersuffix = 134, 
    CharacterLiteral = 135, FloatingLiteral = 136, StringLiteral = 137, 
    BooleanLiteral = 138, PointerLiteral = 139, UserDefinedLiteral = 140, 
    UserDefinedIntegerLiteral = 141, UserDefinedFloatingLiteral = 142, UserDefinedStringLiteral = 143, 
    UserDefinedCharacterLiteral = 144, Whitespace = 145, Newline = 146, 
    BlockComment = 147, LineComment = 148
  };

  CPP14Lexer(antlr4::CharStream *input);
  ~CPP14Lexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace Ubpa
