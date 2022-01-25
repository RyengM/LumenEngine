
// Generated from ShaderLab.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  ShaderLabParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, T__21 = 22, T__22 = 23, T__23 = 24, String = 25, MetaInfo = 26, 
    HLSL = 27, Identifier = 28, Sign = 29, IntegerLiteral = 30, FloatingLiteral = 31, 
    ExponentPart = 32, CullMode = 33, Comparator = 34, ZWriteMode = 35, 
    Channel = 36, Whitespace = 37, Newline = 38, BlockComment = 39, LineComment = 40
  };

  enum {
    RuleShader = 0, RuleProperties = 1, RuleProperty = 2, RuleProperty_int = 3, 
    RuleProperty_float = 4, RuleProperty_range = 5, RuleProperty_color = 6, 
    RuleProperty_vector = 7, RuleProperty_2d = 8, RuleProperty_cube = 9, 
    RuleProperty_3d = 10, RuleCategory = 11, RuleKernel = 12, RuleHlsl_block = 13, 
    RuleTags = 14, RuleTag = 15, RuleCommon_state = 16, RuleCull = 17, RuleZtest = 18, 
    RuleZwrite = 19, RuleColor_mask = 20, RuleMeta = 21, RuleRange = 22, 
    RuleTag_key = 23, RuleTag_val = 24, RuleShader_name = 25, RuleDisplay_name = 26, 
    RuleTexture_name = 27, RuleProperty_identifier = 28, RuleVal_int = 29, 
    RuleVal_float = 30, RuleVal_min = 31, RuleVal_max = 32, RuleVal_vec4 = 33, 
    RuleChannel = 34
  };

  ShaderLabParser(antlr4::TokenStream *input);
  ~ShaderLabParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class ShaderContext;
  class PropertiesContext;
  class PropertyContext;
  class Property_intContext;
  class Property_floatContext;
  class Property_rangeContext;
  class Property_colorContext;
  class Property_vectorContext;
  class Property_2dContext;
  class Property_cubeContext;
  class Property_3dContext;
  class CategoryContext;
  class KernelContext;
  class Hlsl_blockContext;
  class TagsContext;
  class TagContext;
  class Common_stateContext;
  class CullContext;
  class ZtestContext;
  class ZwriteContext;
  class Color_maskContext;
  class MetaContext;
  class RangeContext;
  class Tag_keyContext;
  class Tag_valContext;
  class Shader_nameContext;
  class Display_nameContext;
  class Texture_nameContext;
  class Property_identifierContext;
  class Val_intContext;
  class Val_floatContext;
  class Val_minContext;
  class Val_maxContext;
  class Val_vec4Context;
  class ChannelContext; 

  class  ShaderContext : public antlr4::ParserRuleContext {
  public:
    ShaderContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Shader_nameContext *shader_name();
    CategoryContext *category();
    PropertiesContext *properties();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ShaderContext* shader();

  class  PropertiesContext : public antlr4::ParserRuleContext {
  public:
    PropertiesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PropertyContext *> property();
    PropertyContext* property(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PropertiesContext* properties();

  class  PropertyContext : public antlr4::ParserRuleContext {
  public:
    PropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Property_intContext *property_int();
    Property_floatContext *property_float();
    Property_rangeContext *property_range();
    Property_colorContext *property_color();
    Property_vectorContext *property_vector();
    Property_2dContext *property_2d();
    Property_cubeContext *property_cube();
    Property_3dContext *property_3d();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PropertyContext* property();

  class  Property_intContext : public antlr4::ParserRuleContext {
  public:
    Property_intContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Property_identifierContext *property_identifier();
    Display_nameContext *display_name();
    Val_intContext *val_int();
    std::vector<MetaContext *> meta();
    MetaContext* meta(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_intContext* property_int();

  class  Property_floatContext : public antlr4::ParserRuleContext {
  public:
    Property_floatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Property_identifierContext *property_identifier();
    Display_nameContext *display_name();
    Val_floatContext *val_float();
    std::vector<MetaContext *> meta();
    MetaContext* meta(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_floatContext* property_float();

  class  Property_rangeContext : public antlr4::ParserRuleContext {
  public:
    Property_rangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Property_identifierContext *property_identifier();
    Display_nameContext *display_name();
    RangeContext *range();
    Val_floatContext *val_float();
    std::vector<MetaContext *> meta();
    MetaContext* meta(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_rangeContext* property_range();

  class  Property_colorContext : public antlr4::ParserRuleContext {
  public:
    Property_colorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Property_identifierContext *property_identifier();
    Display_nameContext *display_name();
    Val_vec4Context *val_vec4();
    std::vector<MetaContext *> meta();
    MetaContext* meta(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_colorContext* property_color();

  class  Property_vectorContext : public antlr4::ParserRuleContext {
  public:
    Property_vectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Property_identifierContext *property_identifier();
    Display_nameContext *display_name();
    Val_vec4Context *val_vec4();
    std::vector<MetaContext *> meta();
    MetaContext* meta(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_vectorContext* property_vector();

  class  Property_2dContext : public antlr4::ParserRuleContext {
  public:
    Property_2dContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Property_identifierContext *property_identifier();
    Display_nameContext *display_name();
    Texture_nameContext *texture_name();
    std::vector<MetaContext *> meta();
    MetaContext* meta(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_2dContext* property_2d();

  class  Property_cubeContext : public antlr4::ParserRuleContext {
  public:
    Property_cubeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Property_identifierContext *property_identifier();
    Display_nameContext *display_name();
    Texture_nameContext *texture_name();
    std::vector<MetaContext *> meta();
    MetaContext* meta(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_cubeContext* property_cube();

  class  Property_3dContext : public antlr4::ParserRuleContext {
  public:
    Property_3dContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Property_identifierContext *property_identifier();
    Display_nameContext *display_name();
    Texture_nameContext *texture_name();
    std::vector<MetaContext *> meta();
    MetaContext* meta(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_3dContext* property_3d();

  class  CategoryContext : public antlr4::ParserRuleContext {
  public:
    CategoryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TagsContext *tags();
    std::vector<KernelContext *> kernel();
    KernelContext* kernel(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CategoryContext* category();

  class  KernelContext : public antlr4::ParserRuleContext {
  public:
    KernelContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TagsContext *tags();
    Hlsl_blockContext *hlsl_block();
    std::vector<Common_stateContext *> common_state();
    Common_stateContext* common_state(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  KernelContext* kernel();

  class  Hlsl_blockContext : public antlr4::ParserRuleContext {
  public:
    Hlsl_blockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HLSL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Hlsl_blockContext* hlsl_block();

  class  TagsContext : public antlr4::ParserRuleContext {
  public:
    TagsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TagContext *> tag();
    TagContext* tag(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TagsContext* tags();

  class  TagContext : public antlr4::ParserRuleContext {
  public:
    TagContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Tag_keyContext *tag_key();
    Tag_valContext *tag_val();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TagContext* tag();

  class  Common_stateContext : public antlr4::ParserRuleContext {
  public:
    Common_stateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CullContext *cull();
    ZtestContext *ztest();
    ZwriteContext *zwrite();
    Color_maskContext *color_mask();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Common_stateContext* common_state();

  class  CullContext : public antlr4::ParserRuleContext {
  public:
    CullContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CullMode();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CullContext* cull();

  class  ZtestContext : public antlr4::ParserRuleContext {
  public:
    ZtestContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Comparator();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ZtestContext* ztest();

  class  ZwriteContext : public antlr4::ParserRuleContext {
  public:
    ZwriteContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ZWriteMode();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ZwriteContext* zwrite();

  class  Color_maskContext : public antlr4::ParserRuleContext {
  public:
    Color_maskContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ChannelContext *channel();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Color_maskContext* color_mask();

  class  MetaContext : public antlr4::ParserRuleContext {
  public:
    MetaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MetaInfo();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MetaContext* meta();

  class  RangeContext : public antlr4::ParserRuleContext {
  public:
    RangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Val_minContext *val_min();
    Val_maxContext *val_max();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RangeContext* range();

  class  Tag_keyContext : public antlr4::ParserRuleContext {
  public:
    Tag_keyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *String();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Tag_keyContext* tag_key();

  class  Tag_valContext : public antlr4::ParserRuleContext {
  public:
    Tag_valContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *String();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Tag_valContext* tag_val();

  class  Shader_nameContext : public antlr4::ParserRuleContext {
  public:
    Shader_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *String();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Shader_nameContext* shader_name();

  class  Display_nameContext : public antlr4::ParserRuleContext {
  public:
    Display_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *String();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Display_nameContext* display_name();

  class  Texture_nameContext : public antlr4::ParserRuleContext {
  public:
    Texture_nameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *String();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Texture_nameContext* texture_name();

  class  Property_identifierContext : public antlr4::ParserRuleContext {
  public:
    Property_identifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Property_identifierContext* property_identifier();

  class  Val_intContext : public antlr4::ParserRuleContext {
  public:
    Val_intContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IntegerLiteral();
    antlr4::tree::TerminalNode *Sign();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Val_intContext* val_int();

  class  Val_floatContext : public antlr4::ParserRuleContext {
  public:
    Val_floatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FloatingLiteral();
    antlr4::tree::TerminalNode *Sign();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Val_floatContext* val_float();

  class  Val_minContext : public antlr4::ParserRuleContext {
  public:
    Val_minContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FloatingLiteral();
    antlr4::tree::TerminalNode *Sign();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Val_minContext* val_min();

  class  Val_maxContext : public antlr4::ParserRuleContext {
  public:
    Val_maxContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FloatingLiteral();
    antlr4::tree::TerminalNode *Sign();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Val_maxContext* val_max();

  class  Val_vec4Context : public antlr4::ParserRuleContext {
  public:
    Val_vec4Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Val_floatContext *> val_float();
    Val_floatContext* val_float(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  Val_vec4Context* val_vec4();

  class  ChannelContext : public antlr4::ParserRuleContext {
  public:
    ChannelContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *Channel();
    antlr4::tree::TerminalNode *IntegerLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChannelContext* channel();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

