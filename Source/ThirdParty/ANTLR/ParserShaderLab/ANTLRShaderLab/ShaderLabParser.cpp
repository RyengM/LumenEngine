
// Generated from ShaderLab.g4 by ANTLR 4.7


#include "ShaderLabListener.h"
#include "ShaderLabVisitor.h"

#include "ShaderLabParser.h"


using namespace antlrcpp;
using namespace antlr4;

ShaderLabParser::ShaderLabParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

ShaderLabParser::~ShaderLabParser() {
  delete _interpreter;
}

std::string ShaderLabParser::getGrammarFileName() const {
  return "ShaderLab.g4";
}

const std::vector<std::string>& ShaderLabParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& ShaderLabParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ShaderContext ------------------------------------------------------------------

ShaderLabParser::ShaderContext::ShaderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ShaderLabParser::Shader_nameContext* ShaderLabParser::ShaderContext::shader_name() {
  return getRuleContext<ShaderLabParser::Shader_nameContext>(0);
}

ShaderLabParser::CategoryContext* ShaderLabParser::ShaderContext::category() {
  return getRuleContext<ShaderLabParser::CategoryContext>(0);
}

ShaderLabParser::PropertiesContext* ShaderLabParser::ShaderContext::properties() {
  return getRuleContext<ShaderLabParser::PropertiesContext>(0);
}


size_t ShaderLabParser::ShaderContext::getRuleIndex() const {
  return ShaderLabParser::RuleShader;
}

void ShaderLabParser::ShaderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShader(this);
}

void ShaderLabParser::ShaderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShader(this);
}


antlrcpp::Any ShaderLabParser::ShaderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitShader(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::ShaderContext* ShaderLabParser::shader() {
  ShaderContext *_localctx = _tracker.createInstance<ShaderContext>(_ctx, getState());
  enterRule(_localctx, 0, ShaderLabParser::RuleShader);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(70);
    match(ShaderLabParser::T__0);
    setState(71);
    shader_name();
    setState(72);
    match(ShaderLabParser::T__1);
    setState(74);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ShaderLabParser::T__3) {
      setState(73);
      properties();
    }
    setState(76);
    category();
    setState(77);
    match(ShaderLabParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertiesContext ------------------------------------------------------------------

ShaderLabParser::PropertiesContext::PropertiesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ShaderLabParser::PropertyContext *> ShaderLabParser::PropertiesContext::property() {
  return getRuleContexts<ShaderLabParser::PropertyContext>();
}

ShaderLabParser::PropertyContext* ShaderLabParser::PropertiesContext::property(size_t i) {
  return getRuleContext<ShaderLabParser::PropertyContext>(i);
}


size_t ShaderLabParser::PropertiesContext::getRuleIndex() const {
  return ShaderLabParser::RuleProperties;
}

void ShaderLabParser::PropertiesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperties(this);
}

void ShaderLabParser::PropertiesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperties(this);
}


antlrcpp::Any ShaderLabParser::PropertiesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitProperties(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::PropertiesContext* ShaderLabParser::properties() {
  PropertiesContext *_localctx = _tracker.createInstance<PropertiesContext>(_ctx, getState());
  enterRule(_localctx, 2, ShaderLabParser::RuleProperties);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(79);
    match(ShaderLabParser::T__3);
    setState(80);
    match(ShaderLabParser::T__1);
    setState(82); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(81);
      property();
      setState(84); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ShaderLabParser::MetaInfo

    || _la == ShaderLabParser::Identifier);
    setState(86);
    match(ShaderLabParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyContext ------------------------------------------------------------------

ShaderLabParser::PropertyContext::PropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ShaderLabParser::Property_intContext* ShaderLabParser::PropertyContext::property_int() {
  return getRuleContext<ShaderLabParser::Property_intContext>(0);
}

ShaderLabParser::Property_floatContext* ShaderLabParser::PropertyContext::property_float() {
  return getRuleContext<ShaderLabParser::Property_floatContext>(0);
}

ShaderLabParser::Property_rangeContext* ShaderLabParser::PropertyContext::property_range() {
  return getRuleContext<ShaderLabParser::Property_rangeContext>(0);
}

ShaderLabParser::Property_colorContext* ShaderLabParser::PropertyContext::property_color() {
  return getRuleContext<ShaderLabParser::Property_colorContext>(0);
}

ShaderLabParser::Property_vectorContext* ShaderLabParser::PropertyContext::property_vector() {
  return getRuleContext<ShaderLabParser::Property_vectorContext>(0);
}

ShaderLabParser::Property_2dContext* ShaderLabParser::PropertyContext::property_2d() {
  return getRuleContext<ShaderLabParser::Property_2dContext>(0);
}

ShaderLabParser::Property_cubeContext* ShaderLabParser::PropertyContext::property_cube() {
  return getRuleContext<ShaderLabParser::Property_cubeContext>(0);
}

ShaderLabParser::Property_3dContext* ShaderLabParser::PropertyContext::property_3d() {
  return getRuleContext<ShaderLabParser::Property_3dContext>(0);
}


size_t ShaderLabParser::PropertyContext::getRuleIndex() const {
  return ShaderLabParser::RuleProperty;
}

void ShaderLabParser::PropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty(this);
}

void ShaderLabParser::PropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty(this);
}


antlrcpp::Any ShaderLabParser::PropertyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitProperty(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::PropertyContext* ShaderLabParser::property() {
  PropertyContext *_localctx = _tracker.createInstance<PropertyContext>(_ctx, getState());
  enterRule(_localctx, 4, ShaderLabParser::RuleProperty);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(96);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(88);
      property_int();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(89);
      property_float();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(90);
      property_range();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(91);
      property_color();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(92);
      property_vector();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(93);
      property_2d();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(94);
      property_cube();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(95);
      property_3d();
      break;
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

//----------------- Property_intContext ------------------------------------------------------------------

ShaderLabParser::Property_intContext::Property_intContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ShaderLabParser::Property_identifierContext* ShaderLabParser::Property_intContext::property_identifier() {
  return getRuleContext<ShaderLabParser::Property_identifierContext>(0);
}

ShaderLabParser::Display_nameContext* ShaderLabParser::Property_intContext::display_name() {
  return getRuleContext<ShaderLabParser::Display_nameContext>(0);
}

ShaderLabParser::Val_intContext* ShaderLabParser::Property_intContext::val_int() {
  return getRuleContext<ShaderLabParser::Val_intContext>(0);
}

std::vector<ShaderLabParser::MetaContext *> ShaderLabParser::Property_intContext::meta() {
  return getRuleContexts<ShaderLabParser::MetaContext>();
}

ShaderLabParser::MetaContext* ShaderLabParser::Property_intContext::meta(size_t i) {
  return getRuleContext<ShaderLabParser::MetaContext>(i);
}


size_t ShaderLabParser::Property_intContext::getRuleIndex() const {
  return ShaderLabParser::RuleProperty_int;
}

void ShaderLabParser::Property_intContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_int(this);
}

void ShaderLabParser::Property_intContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_int(this);
}


antlrcpp::Any ShaderLabParser::Property_intContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitProperty_int(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Property_intContext* ShaderLabParser::property_int() {
  Property_intContext *_localctx = _tracker.createInstance<Property_intContext>(_ctx, getState());
  enterRule(_localctx, 6, ShaderLabParser::RuleProperty_int);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(101);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ShaderLabParser::MetaInfo) {
      setState(98);
      meta();
      setState(103);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(104);
    property_identifier();
    setState(105);
    match(ShaderLabParser::T__4);
    setState(106);
    display_name();
    setState(107);
    match(ShaderLabParser::T__5);
    setState(108);
    match(ShaderLabParser::T__6);
    setState(109);
    match(ShaderLabParser::T__7);
    setState(110);
    match(ShaderLabParser::T__8);
    setState(111);
    val_int();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_floatContext ------------------------------------------------------------------

ShaderLabParser::Property_floatContext::Property_floatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ShaderLabParser::Property_identifierContext* ShaderLabParser::Property_floatContext::property_identifier() {
  return getRuleContext<ShaderLabParser::Property_identifierContext>(0);
}

ShaderLabParser::Display_nameContext* ShaderLabParser::Property_floatContext::display_name() {
  return getRuleContext<ShaderLabParser::Display_nameContext>(0);
}

ShaderLabParser::Val_floatContext* ShaderLabParser::Property_floatContext::val_float() {
  return getRuleContext<ShaderLabParser::Val_floatContext>(0);
}

std::vector<ShaderLabParser::MetaContext *> ShaderLabParser::Property_floatContext::meta() {
  return getRuleContexts<ShaderLabParser::MetaContext>();
}

ShaderLabParser::MetaContext* ShaderLabParser::Property_floatContext::meta(size_t i) {
  return getRuleContext<ShaderLabParser::MetaContext>(i);
}


size_t ShaderLabParser::Property_floatContext::getRuleIndex() const {
  return ShaderLabParser::RuleProperty_float;
}

void ShaderLabParser::Property_floatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_float(this);
}

void ShaderLabParser::Property_floatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_float(this);
}


antlrcpp::Any ShaderLabParser::Property_floatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitProperty_float(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Property_floatContext* ShaderLabParser::property_float() {
  Property_floatContext *_localctx = _tracker.createInstance<Property_floatContext>(_ctx, getState());
  enterRule(_localctx, 8, ShaderLabParser::RuleProperty_float);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(116);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ShaderLabParser::MetaInfo) {
      setState(113);
      meta();
      setState(118);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(119);
    property_identifier();
    setState(120);
    match(ShaderLabParser::T__4);
    setState(121);
    display_name();
    setState(122);
    match(ShaderLabParser::T__5);
    setState(123);
    match(ShaderLabParser::T__9);
    setState(124);
    match(ShaderLabParser::T__7);
    setState(125);
    match(ShaderLabParser::T__8);
    setState(126);
    val_float();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_rangeContext ------------------------------------------------------------------

ShaderLabParser::Property_rangeContext::Property_rangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ShaderLabParser::Property_identifierContext* ShaderLabParser::Property_rangeContext::property_identifier() {
  return getRuleContext<ShaderLabParser::Property_identifierContext>(0);
}

ShaderLabParser::Display_nameContext* ShaderLabParser::Property_rangeContext::display_name() {
  return getRuleContext<ShaderLabParser::Display_nameContext>(0);
}

ShaderLabParser::RangeContext* ShaderLabParser::Property_rangeContext::range() {
  return getRuleContext<ShaderLabParser::RangeContext>(0);
}

ShaderLabParser::Val_floatContext* ShaderLabParser::Property_rangeContext::val_float() {
  return getRuleContext<ShaderLabParser::Val_floatContext>(0);
}

std::vector<ShaderLabParser::MetaContext *> ShaderLabParser::Property_rangeContext::meta() {
  return getRuleContexts<ShaderLabParser::MetaContext>();
}

ShaderLabParser::MetaContext* ShaderLabParser::Property_rangeContext::meta(size_t i) {
  return getRuleContext<ShaderLabParser::MetaContext>(i);
}


size_t ShaderLabParser::Property_rangeContext::getRuleIndex() const {
  return ShaderLabParser::RuleProperty_range;
}

void ShaderLabParser::Property_rangeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_range(this);
}

void ShaderLabParser::Property_rangeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_range(this);
}


antlrcpp::Any ShaderLabParser::Property_rangeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitProperty_range(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Property_rangeContext* ShaderLabParser::property_range() {
  Property_rangeContext *_localctx = _tracker.createInstance<Property_rangeContext>(_ctx, getState());
  enterRule(_localctx, 10, ShaderLabParser::RuleProperty_range);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(131);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ShaderLabParser::MetaInfo) {
      setState(128);
      meta();
      setState(133);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(134);
    property_identifier();
    setState(135);
    match(ShaderLabParser::T__4);
    setState(136);
    display_name();
    setState(137);
    match(ShaderLabParser::T__5);
    setState(138);
    match(ShaderLabParser::T__10);
    setState(139);
    range();
    setState(140);
    match(ShaderLabParser::T__7);
    setState(141);
    match(ShaderLabParser::T__8);
    setState(142);
    val_float();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_colorContext ------------------------------------------------------------------

ShaderLabParser::Property_colorContext::Property_colorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ShaderLabParser::Property_identifierContext* ShaderLabParser::Property_colorContext::property_identifier() {
  return getRuleContext<ShaderLabParser::Property_identifierContext>(0);
}

ShaderLabParser::Display_nameContext* ShaderLabParser::Property_colorContext::display_name() {
  return getRuleContext<ShaderLabParser::Display_nameContext>(0);
}

ShaderLabParser::Val_vec4Context* ShaderLabParser::Property_colorContext::val_vec4() {
  return getRuleContext<ShaderLabParser::Val_vec4Context>(0);
}

std::vector<ShaderLabParser::MetaContext *> ShaderLabParser::Property_colorContext::meta() {
  return getRuleContexts<ShaderLabParser::MetaContext>();
}

ShaderLabParser::MetaContext* ShaderLabParser::Property_colorContext::meta(size_t i) {
  return getRuleContext<ShaderLabParser::MetaContext>(i);
}


size_t ShaderLabParser::Property_colorContext::getRuleIndex() const {
  return ShaderLabParser::RuleProperty_color;
}

void ShaderLabParser::Property_colorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_color(this);
}

void ShaderLabParser::Property_colorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_color(this);
}


antlrcpp::Any ShaderLabParser::Property_colorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitProperty_color(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Property_colorContext* ShaderLabParser::property_color() {
  Property_colorContext *_localctx = _tracker.createInstance<Property_colorContext>(_ctx, getState());
  enterRule(_localctx, 12, ShaderLabParser::RuleProperty_color);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(147);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ShaderLabParser::MetaInfo) {
      setState(144);
      meta();
      setState(149);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(150);
    property_identifier();
    setState(151);
    match(ShaderLabParser::T__4);
    setState(152);
    display_name();
    setState(153);
    match(ShaderLabParser::T__5);
    setState(154);
    match(ShaderLabParser::T__11);
    setState(155);
    match(ShaderLabParser::T__7);
    setState(156);
    match(ShaderLabParser::T__8);
    setState(157);
    val_vec4();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_vectorContext ------------------------------------------------------------------

ShaderLabParser::Property_vectorContext::Property_vectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ShaderLabParser::Property_identifierContext* ShaderLabParser::Property_vectorContext::property_identifier() {
  return getRuleContext<ShaderLabParser::Property_identifierContext>(0);
}

ShaderLabParser::Display_nameContext* ShaderLabParser::Property_vectorContext::display_name() {
  return getRuleContext<ShaderLabParser::Display_nameContext>(0);
}

ShaderLabParser::Val_vec4Context* ShaderLabParser::Property_vectorContext::val_vec4() {
  return getRuleContext<ShaderLabParser::Val_vec4Context>(0);
}

std::vector<ShaderLabParser::MetaContext *> ShaderLabParser::Property_vectorContext::meta() {
  return getRuleContexts<ShaderLabParser::MetaContext>();
}

ShaderLabParser::MetaContext* ShaderLabParser::Property_vectorContext::meta(size_t i) {
  return getRuleContext<ShaderLabParser::MetaContext>(i);
}


size_t ShaderLabParser::Property_vectorContext::getRuleIndex() const {
  return ShaderLabParser::RuleProperty_vector;
}

void ShaderLabParser::Property_vectorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_vector(this);
}

void ShaderLabParser::Property_vectorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_vector(this);
}


antlrcpp::Any ShaderLabParser::Property_vectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitProperty_vector(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Property_vectorContext* ShaderLabParser::property_vector() {
  Property_vectorContext *_localctx = _tracker.createInstance<Property_vectorContext>(_ctx, getState());
  enterRule(_localctx, 14, ShaderLabParser::RuleProperty_vector);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(162);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ShaderLabParser::MetaInfo) {
      setState(159);
      meta();
      setState(164);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(165);
    property_identifier();
    setState(166);
    match(ShaderLabParser::T__4);
    setState(167);
    display_name();
    setState(168);
    match(ShaderLabParser::T__5);
    setState(169);
    match(ShaderLabParser::T__12);
    setState(170);
    match(ShaderLabParser::T__7);
    setState(171);
    match(ShaderLabParser::T__8);
    setState(172);
    val_vec4();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_2dContext ------------------------------------------------------------------

ShaderLabParser::Property_2dContext::Property_2dContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ShaderLabParser::Property_identifierContext* ShaderLabParser::Property_2dContext::property_identifier() {
  return getRuleContext<ShaderLabParser::Property_identifierContext>(0);
}

ShaderLabParser::Display_nameContext* ShaderLabParser::Property_2dContext::display_name() {
  return getRuleContext<ShaderLabParser::Display_nameContext>(0);
}

ShaderLabParser::Texture_nameContext* ShaderLabParser::Property_2dContext::texture_name() {
  return getRuleContext<ShaderLabParser::Texture_nameContext>(0);
}

std::vector<ShaderLabParser::MetaContext *> ShaderLabParser::Property_2dContext::meta() {
  return getRuleContexts<ShaderLabParser::MetaContext>();
}

ShaderLabParser::MetaContext* ShaderLabParser::Property_2dContext::meta(size_t i) {
  return getRuleContext<ShaderLabParser::MetaContext>(i);
}


size_t ShaderLabParser::Property_2dContext::getRuleIndex() const {
  return ShaderLabParser::RuleProperty_2d;
}

void ShaderLabParser::Property_2dContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_2d(this);
}

void ShaderLabParser::Property_2dContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_2d(this);
}


antlrcpp::Any ShaderLabParser::Property_2dContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitProperty_2d(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Property_2dContext* ShaderLabParser::property_2d() {
  Property_2dContext *_localctx = _tracker.createInstance<Property_2dContext>(_ctx, getState());
  enterRule(_localctx, 16, ShaderLabParser::RuleProperty_2d);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(177);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ShaderLabParser::MetaInfo) {
      setState(174);
      meta();
      setState(179);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(180);
    property_identifier();
    setState(181);
    match(ShaderLabParser::T__4);
    setState(182);
    display_name();
    setState(183);
    match(ShaderLabParser::T__5);
    setState(184);
    match(ShaderLabParser::T__13);
    setState(185);
    match(ShaderLabParser::T__7);
    setState(186);
    match(ShaderLabParser::T__8);
    setState(187);
    texture_name();
    setState(188);
    match(ShaderLabParser::T__14);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_cubeContext ------------------------------------------------------------------

ShaderLabParser::Property_cubeContext::Property_cubeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ShaderLabParser::Property_identifierContext* ShaderLabParser::Property_cubeContext::property_identifier() {
  return getRuleContext<ShaderLabParser::Property_identifierContext>(0);
}

ShaderLabParser::Display_nameContext* ShaderLabParser::Property_cubeContext::display_name() {
  return getRuleContext<ShaderLabParser::Display_nameContext>(0);
}

ShaderLabParser::Texture_nameContext* ShaderLabParser::Property_cubeContext::texture_name() {
  return getRuleContext<ShaderLabParser::Texture_nameContext>(0);
}

std::vector<ShaderLabParser::MetaContext *> ShaderLabParser::Property_cubeContext::meta() {
  return getRuleContexts<ShaderLabParser::MetaContext>();
}

ShaderLabParser::MetaContext* ShaderLabParser::Property_cubeContext::meta(size_t i) {
  return getRuleContext<ShaderLabParser::MetaContext>(i);
}


size_t ShaderLabParser::Property_cubeContext::getRuleIndex() const {
  return ShaderLabParser::RuleProperty_cube;
}

void ShaderLabParser::Property_cubeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_cube(this);
}

void ShaderLabParser::Property_cubeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_cube(this);
}


antlrcpp::Any ShaderLabParser::Property_cubeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitProperty_cube(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Property_cubeContext* ShaderLabParser::property_cube() {
  Property_cubeContext *_localctx = _tracker.createInstance<Property_cubeContext>(_ctx, getState());
  enterRule(_localctx, 18, ShaderLabParser::RuleProperty_cube);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(193);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ShaderLabParser::MetaInfo) {
      setState(190);
      meta();
      setState(195);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(196);
    property_identifier();
    setState(197);
    match(ShaderLabParser::T__4);
    setState(198);
    display_name();
    setState(199);
    match(ShaderLabParser::T__5);
    setState(200);
    match(ShaderLabParser::T__15);
    setState(201);
    match(ShaderLabParser::T__7);
    setState(202);
    match(ShaderLabParser::T__8);
    setState(203);
    texture_name();
    setState(204);
    match(ShaderLabParser::T__14);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_3dContext ------------------------------------------------------------------

ShaderLabParser::Property_3dContext::Property_3dContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ShaderLabParser::Property_identifierContext* ShaderLabParser::Property_3dContext::property_identifier() {
  return getRuleContext<ShaderLabParser::Property_identifierContext>(0);
}

ShaderLabParser::Display_nameContext* ShaderLabParser::Property_3dContext::display_name() {
  return getRuleContext<ShaderLabParser::Display_nameContext>(0);
}

ShaderLabParser::Texture_nameContext* ShaderLabParser::Property_3dContext::texture_name() {
  return getRuleContext<ShaderLabParser::Texture_nameContext>(0);
}

std::vector<ShaderLabParser::MetaContext *> ShaderLabParser::Property_3dContext::meta() {
  return getRuleContexts<ShaderLabParser::MetaContext>();
}

ShaderLabParser::MetaContext* ShaderLabParser::Property_3dContext::meta(size_t i) {
  return getRuleContext<ShaderLabParser::MetaContext>(i);
}


size_t ShaderLabParser::Property_3dContext::getRuleIndex() const {
  return ShaderLabParser::RuleProperty_3d;
}

void ShaderLabParser::Property_3dContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_3d(this);
}

void ShaderLabParser::Property_3dContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_3d(this);
}


antlrcpp::Any ShaderLabParser::Property_3dContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitProperty_3d(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Property_3dContext* ShaderLabParser::property_3d() {
  Property_3dContext *_localctx = _tracker.createInstance<Property_3dContext>(_ctx, getState());
  enterRule(_localctx, 20, ShaderLabParser::RuleProperty_3d);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(209);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ShaderLabParser::MetaInfo) {
      setState(206);
      meta();
      setState(211);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(212);
    property_identifier();
    setState(213);
    match(ShaderLabParser::T__4);
    setState(214);
    display_name();
    setState(215);
    match(ShaderLabParser::T__5);
    setState(216);
    match(ShaderLabParser::T__16);
    setState(217);
    match(ShaderLabParser::T__7);
    setState(218);
    match(ShaderLabParser::T__8);
    setState(219);
    texture_name();
    setState(220);
    match(ShaderLabParser::T__14);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CategoryContext ------------------------------------------------------------------

ShaderLabParser::CategoryContext::CategoryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ShaderLabParser::TagsContext* ShaderLabParser::CategoryContext::tags() {
  return getRuleContext<ShaderLabParser::TagsContext>(0);
}

std::vector<ShaderLabParser::KernelContext *> ShaderLabParser::CategoryContext::kernel() {
  return getRuleContexts<ShaderLabParser::KernelContext>();
}

ShaderLabParser::KernelContext* ShaderLabParser::CategoryContext::kernel(size_t i) {
  return getRuleContext<ShaderLabParser::KernelContext>(i);
}


size_t ShaderLabParser::CategoryContext::getRuleIndex() const {
  return ShaderLabParser::RuleCategory;
}

void ShaderLabParser::CategoryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCategory(this);
}

void ShaderLabParser::CategoryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCategory(this);
}


antlrcpp::Any ShaderLabParser::CategoryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitCategory(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::CategoryContext* ShaderLabParser::category() {
  CategoryContext *_localctx = _tracker.createInstance<CategoryContext>(_ctx, getState());
  enterRule(_localctx, 22, ShaderLabParser::RuleCategory);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(222);
    match(ShaderLabParser::T__17);
    setState(223);
    match(ShaderLabParser::T__1);
    setState(225);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ShaderLabParser::T__19) {
      setState(224);
      tags();
    }
    setState(228); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(227);
      kernel();
      setState(230); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ShaderLabParser::T__18);
    setState(232);
    match(ShaderLabParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- KernelContext ------------------------------------------------------------------

ShaderLabParser::KernelContext::KernelContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ShaderLabParser::TagsContext* ShaderLabParser::KernelContext::tags() {
  return getRuleContext<ShaderLabParser::TagsContext>(0);
}

ShaderLabParser::Hlsl_blockContext* ShaderLabParser::KernelContext::hlsl_block() {
  return getRuleContext<ShaderLabParser::Hlsl_blockContext>(0);
}

std::vector<ShaderLabParser::Common_stateContext *> ShaderLabParser::KernelContext::common_state() {
  return getRuleContexts<ShaderLabParser::Common_stateContext>();
}

ShaderLabParser::Common_stateContext* ShaderLabParser::KernelContext::common_state(size_t i) {
  return getRuleContext<ShaderLabParser::Common_stateContext>(i);
}


size_t ShaderLabParser::KernelContext::getRuleIndex() const {
  return ShaderLabParser::RuleKernel;
}

void ShaderLabParser::KernelContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterKernel(this);
}

void ShaderLabParser::KernelContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitKernel(this);
}


antlrcpp::Any ShaderLabParser::KernelContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitKernel(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::KernelContext* ShaderLabParser::kernel() {
  KernelContext *_localctx = _tracker.createInstance<KernelContext>(_ctx, getState());
  enterRule(_localctx, 24, ShaderLabParser::RuleKernel);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(234);
    match(ShaderLabParser::T__18);
    setState(235);
    match(ShaderLabParser::T__1);
    setState(236);
    tags();
    setState(240);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ShaderLabParser::T__20)
      | (1ULL << ShaderLabParser::T__21)
      | (1ULL << ShaderLabParser::T__22)
      | (1ULL << ShaderLabParser::T__23))) != 0)) {
      setState(237);
      common_state();
      setState(242);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(243);
    hlsl_block();
    setState(244);
    match(ShaderLabParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Hlsl_blockContext ------------------------------------------------------------------

ShaderLabParser::Hlsl_blockContext::Hlsl_blockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ShaderLabParser::Hlsl_blockContext::HLSL() {
  return getToken(ShaderLabParser::HLSL, 0);
}


size_t ShaderLabParser::Hlsl_blockContext::getRuleIndex() const {
  return ShaderLabParser::RuleHlsl_block;
}

void ShaderLabParser::Hlsl_blockContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHlsl_block(this);
}

void ShaderLabParser::Hlsl_blockContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHlsl_block(this);
}


antlrcpp::Any ShaderLabParser::Hlsl_blockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitHlsl_block(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Hlsl_blockContext* ShaderLabParser::hlsl_block() {
  Hlsl_blockContext *_localctx = _tracker.createInstance<Hlsl_blockContext>(_ctx, getState());
  enterRule(_localctx, 26, ShaderLabParser::RuleHlsl_block);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(246);
    match(ShaderLabParser::HLSL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TagsContext ------------------------------------------------------------------

ShaderLabParser::TagsContext::TagsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ShaderLabParser::TagContext *> ShaderLabParser::TagsContext::tag() {
  return getRuleContexts<ShaderLabParser::TagContext>();
}

ShaderLabParser::TagContext* ShaderLabParser::TagsContext::tag(size_t i) {
  return getRuleContext<ShaderLabParser::TagContext>(i);
}


size_t ShaderLabParser::TagsContext::getRuleIndex() const {
  return ShaderLabParser::RuleTags;
}

void ShaderLabParser::TagsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTags(this);
}

void ShaderLabParser::TagsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTags(this);
}


antlrcpp::Any ShaderLabParser::TagsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitTags(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::TagsContext* ShaderLabParser::tags() {
  TagsContext *_localctx = _tracker.createInstance<TagsContext>(_ctx, getState());
  enterRule(_localctx, 28, ShaderLabParser::RuleTags);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(248);
    match(ShaderLabParser::T__19);
    setState(249);
    match(ShaderLabParser::T__1);
    setState(251); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(250);
      tag();
      setState(253); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ShaderLabParser::String);
    setState(255);
    match(ShaderLabParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TagContext ------------------------------------------------------------------

ShaderLabParser::TagContext::TagContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ShaderLabParser::Tag_keyContext* ShaderLabParser::TagContext::tag_key() {
  return getRuleContext<ShaderLabParser::Tag_keyContext>(0);
}

ShaderLabParser::Tag_valContext* ShaderLabParser::TagContext::tag_val() {
  return getRuleContext<ShaderLabParser::Tag_valContext>(0);
}


size_t ShaderLabParser::TagContext::getRuleIndex() const {
  return ShaderLabParser::RuleTag;
}

void ShaderLabParser::TagContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTag(this);
}

void ShaderLabParser::TagContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTag(this);
}


antlrcpp::Any ShaderLabParser::TagContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitTag(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::TagContext* ShaderLabParser::tag() {
  TagContext *_localctx = _tracker.createInstance<TagContext>(_ctx, getState());
  enterRule(_localctx, 30, ShaderLabParser::RuleTag);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(257);
    tag_key();
    setState(258);
    match(ShaderLabParser::T__8);
    setState(259);
    tag_val();
    setState(261);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ShaderLabParser::T__5) {
      setState(260);
      match(ShaderLabParser::T__5);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Common_stateContext ------------------------------------------------------------------

ShaderLabParser::Common_stateContext::Common_stateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ShaderLabParser::CullContext* ShaderLabParser::Common_stateContext::cull() {
  return getRuleContext<ShaderLabParser::CullContext>(0);
}

ShaderLabParser::ZtestContext* ShaderLabParser::Common_stateContext::ztest() {
  return getRuleContext<ShaderLabParser::ZtestContext>(0);
}

ShaderLabParser::ZwriteContext* ShaderLabParser::Common_stateContext::zwrite() {
  return getRuleContext<ShaderLabParser::ZwriteContext>(0);
}

ShaderLabParser::Color_maskContext* ShaderLabParser::Common_stateContext::color_mask() {
  return getRuleContext<ShaderLabParser::Color_maskContext>(0);
}


size_t ShaderLabParser::Common_stateContext::getRuleIndex() const {
  return ShaderLabParser::RuleCommon_state;
}

void ShaderLabParser::Common_stateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCommon_state(this);
}

void ShaderLabParser::Common_stateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCommon_state(this);
}


antlrcpp::Any ShaderLabParser::Common_stateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitCommon_state(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Common_stateContext* ShaderLabParser::common_state() {
  Common_stateContext *_localctx = _tracker.createInstance<Common_stateContext>(_ctx, getState());
  enterRule(_localctx, 32, ShaderLabParser::RuleCommon_state);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(267);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ShaderLabParser::T__20: {
        enterOuterAlt(_localctx, 1);
        setState(263);
        cull();
        break;
      }

      case ShaderLabParser::T__21: {
        enterOuterAlt(_localctx, 2);
        setState(264);
        ztest();
        break;
      }

      case ShaderLabParser::T__22: {
        enterOuterAlt(_localctx, 3);
        setState(265);
        zwrite();
        break;
      }

      case ShaderLabParser::T__23: {
        enterOuterAlt(_localctx, 4);
        setState(266);
        color_mask();
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

//----------------- CullContext ------------------------------------------------------------------

ShaderLabParser::CullContext::CullContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ShaderLabParser::CullContext::CullMode() {
  return getToken(ShaderLabParser::CullMode, 0);
}


size_t ShaderLabParser::CullContext::getRuleIndex() const {
  return ShaderLabParser::RuleCull;
}

void ShaderLabParser::CullContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCull(this);
}

void ShaderLabParser::CullContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCull(this);
}


antlrcpp::Any ShaderLabParser::CullContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitCull(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::CullContext* ShaderLabParser::cull() {
  CullContext *_localctx = _tracker.createInstance<CullContext>(_ctx, getState());
  enterRule(_localctx, 34, ShaderLabParser::RuleCull);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(269);
    match(ShaderLabParser::T__20);
    setState(270);
    match(ShaderLabParser::CullMode);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ZtestContext ------------------------------------------------------------------

ShaderLabParser::ZtestContext::ZtestContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ShaderLabParser::ZtestContext::Comparator() {
  return getToken(ShaderLabParser::Comparator, 0);
}


size_t ShaderLabParser::ZtestContext::getRuleIndex() const {
  return ShaderLabParser::RuleZtest;
}

void ShaderLabParser::ZtestContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterZtest(this);
}

void ShaderLabParser::ZtestContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitZtest(this);
}


antlrcpp::Any ShaderLabParser::ZtestContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitZtest(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::ZtestContext* ShaderLabParser::ztest() {
  ZtestContext *_localctx = _tracker.createInstance<ZtestContext>(_ctx, getState());
  enterRule(_localctx, 36, ShaderLabParser::RuleZtest);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(272);
    match(ShaderLabParser::T__21);
    setState(273);
    match(ShaderLabParser::Comparator);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ZwriteContext ------------------------------------------------------------------

ShaderLabParser::ZwriteContext::ZwriteContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ShaderLabParser::ZwriteContext::ZWriteMode() {
  return getToken(ShaderLabParser::ZWriteMode, 0);
}


size_t ShaderLabParser::ZwriteContext::getRuleIndex() const {
  return ShaderLabParser::RuleZwrite;
}

void ShaderLabParser::ZwriteContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterZwrite(this);
}

void ShaderLabParser::ZwriteContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitZwrite(this);
}


antlrcpp::Any ShaderLabParser::ZwriteContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitZwrite(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::ZwriteContext* ShaderLabParser::zwrite() {
  ZwriteContext *_localctx = _tracker.createInstance<ZwriteContext>(_ctx, getState());
  enterRule(_localctx, 38, ShaderLabParser::RuleZwrite);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(275);
    match(ShaderLabParser::T__22);
    setState(276);
    match(ShaderLabParser::ZWriteMode);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Color_maskContext ------------------------------------------------------------------

ShaderLabParser::Color_maskContext::Color_maskContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ShaderLabParser::ChannelContext* ShaderLabParser::Color_maskContext::channel() {
  return getRuleContext<ShaderLabParser::ChannelContext>(0);
}


size_t ShaderLabParser::Color_maskContext::getRuleIndex() const {
  return ShaderLabParser::RuleColor_mask;
}

void ShaderLabParser::Color_maskContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterColor_mask(this);
}

void ShaderLabParser::Color_maskContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitColor_mask(this);
}


antlrcpp::Any ShaderLabParser::Color_maskContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitColor_mask(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Color_maskContext* ShaderLabParser::color_mask() {
  Color_maskContext *_localctx = _tracker.createInstance<Color_maskContext>(_ctx, getState());
  enterRule(_localctx, 40, ShaderLabParser::RuleColor_mask);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(278);
    match(ShaderLabParser::T__23);
    setState(279);
    channel();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MetaContext ------------------------------------------------------------------

ShaderLabParser::MetaContext::MetaContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ShaderLabParser::MetaContext::MetaInfo() {
  return getToken(ShaderLabParser::MetaInfo, 0);
}


size_t ShaderLabParser::MetaContext::getRuleIndex() const {
  return ShaderLabParser::RuleMeta;
}

void ShaderLabParser::MetaContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMeta(this);
}

void ShaderLabParser::MetaContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMeta(this);
}


antlrcpp::Any ShaderLabParser::MetaContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitMeta(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::MetaContext* ShaderLabParser::meta() {
  MetaContext *_localctx = _tracker.createInstance<MetaContext>(_ctx, getState());
  enterRule(_localctx, 42, ShaderLabParser::RuleMeta);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(281);
    match(ShaderLabParser::MetaInfo);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RangeContext ------------------------------------------------------------------

ShaderLabParser::RangeContext::RangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ShaderLabParser::Val_minContext* ShaderLabParser::RangeContext::val_min() {
  return getRuleContext<ShaderLabParser::Val_minContext>(0);
}

ShaderLabParser::Val_maxContext* ShaderLabParser::RangeContext::val_max() {
  return getRuleContext<ShaderLabParser::Val_maxContext>(0);
}


size_t ShaderLabParser::RangeContext::getRuleIndex() const {
  return ShaderLabParser::RuleRange;
}

void ShaderLabParser::RangeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRange(this);
}

void ShaderLabParser::RangeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRange(this);
}


antlrcpp::Any ShaderLabParser::RangeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitRange(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::RangeContext* ShaderLabParser::range() {
  RangeContext *_localctx = _tracker.createInstance<RangeContext>(_ctx, getState());
  enterRule(_localctx, 44, ShaderLabParser::RuleRange);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(283);
    match(ShaderLabParser::T__4);
    setState(284);
    val_min();
    setState(285);
    match(ShaderLabParser::T__5);
    setState(286);
    val_max();
    setState(287);
    match(ShaderLabParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Tag_keyContext ------------------------------------------------------------------

ShaderLabParser::Tag_keyContext::Tag_keyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ShaderLabParser::Tag_keyContext::String() {
  return getToken(ShaderLabParser::String, 0);
}


size_t ShaderLabParser::Tag_keyContext::getRuleIndex() const {
  return ShaderLabParser::RuleTag_key;
}

void ShaderLabParser::Tag_keyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTag_key(this);
}

void ShaderLabParser::Tag_keyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTag_key(this);
}


antlrcpp::Any ShaderLabParser::Tag_keyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitTag_key(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Tag_keyContext* ShaderLabParser::tag_key() {
  Tag_keyContext *_localctx = _tracker.createInstance<Tag_keyContext>(_ctx, getState());
  enterRule(_localctx, 46, ShaderLabParser::RuleTag_key);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(289);
    match(ShaderLabParser::String);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Tag_valContext ------------------------------------------------------------------

ShaderLabParser::Tag_valContext::Tag_valContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ShaderLabParser::Tag_valContext::String() {
  return getToken(ShaderLabParser::String, 0);
}


size_t ShaderLabParser::Tag_valContext::getRuleIndex() const {
  return ShaderLabParser::RuleTag_val;
}

void ShaderLabParser::Tag_valContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTag_val(this);
}

void ShaderLabParser::Tag_valContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTag_val(this);
}


antlrcpp::Any ShaderLabParser::Tag_valContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitTag_val(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Tag_valContext* ShaderLabParser::tag_val() {
  Tag_valContext *_localctx = _tracker.createInstance<Tag_valContext>(_ctx, getState());
  enterRule(_localctx, 48, ShaderLabParser::RuleTag_val);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(291);
    match(ShaderLabParser::String);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Shader_nameContext ------------------------------------------------------------------

ShaderLabParser::Shader_nameContext::Shader_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ShaderLabParser::Shader_nameContext::String() {
  return getToken(ShaderLabParser::String, 0);
}


size_t ShaderLabParser::Shader_nameContext::getRuleIndex() const {
  return ShaderLabParser::RuleShader_name;
}

void ShaderLabParser::Shader_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterShader_name(this);
}

void ShaderLabParser::Shader_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitShader_name(this);
}


antlrcpp::Any ShaderLabParser::Shader_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitShader_name(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Shader_nameContext* ShaderLabParser::shader_name() {
  Shader_nameContext *_localctx = _tracker.createInstance<Shader_nameContext>(_ctx, getState());
  enterRule(_localctx, 50, ShaderLabParser::RuleShader_name);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(293);
    match(ShaderLabParser::String);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Display_nameContext ------------------------------------------------------------------

ShaderLabParser::Display_nameContext::Display_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ShaderLabParser::Display_nameContext::String() {
  return getToken(ShaderLabParser::String, 0);
}


size_t ShaderLabParser::Display_nameContext::getRuleIndex() const {
  return ShaderLabParser::RuleDisplay_name;
}

void ShaderLabParser::Display_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDisplay_name(this);
}

void ShaderLabParser::Display_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDisplay_name(this);
}


antlrcpp::Any ShaderLabParser::Display_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitDisplay_name(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Display_nameContext* ShaderLabParser::display_name() {
  Display_nameContext *_localctx = _tracker.createInstance<Display_nameContext>(_ctx, getState());
  enterRule(_localctx, 52, ShaderLabParser::RuleDisplay_name);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(295);
    match(ShaderLabParser::String);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Texture_nameContext ------------------------------------------------------------------

ShaderLabParser::Texture_nameContext::Texture_nameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ShaderLabParser::Texture_nameContext::String() {
  return getToken(ShaderLabParser::String, 0);
}


size_t ShaderLabParser::Texture_nameContext::getRuleIndex() const {
  return ShaderLabParser::RuleTexture_name;
}

void ShaderLabParser::Texture_nameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTexture_name(this);
}

void ShaderLabParser::Texture_nameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTexture_name(this);
}


antlrcpp::Any ShaderLabParser::Texture_nameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitTexture_name(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Texture_nameContext* ShaderLabParser::texture_name() {
  Texture_nameContext *_localctx = _tracker.createInstance<Texture_nameContext>(_ctx, getState());
  enterRule(_localctx, 54, ShaderLabParser::RuleTexture_name);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(297);
    match(ShaderLabParser::String);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Property_identifierContext ------------------------------------------------------------------

ShaderLabParser::Property_identifierContext::Property_identifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ShaderLabParser::Property_identifierContext::Identifier() {
  return getToken(ShaderLabParser::Identifier, 0);
}


size_t ShaderLabParser::Property_identifierContext::getRuleIndex() const {
  return ShaderLabParser::RuleProperty_identifier;
}

void ShaderLabParser::Property_identifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty_identifier(this);
}

void ShaderLabParser::Property_identifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty_identifier(this);
}


antlrcpp::Any ShaderLabParser::Property_identifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitProperty_identifier(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Property_identifierContext* ShaderLabParser::property_identifier() {
  Property_identifierContext *_localctx = _tracker.createInstance<Property_identifierContext>(_ctx, getState());
  enterRule(_localctx, 56, ShaderLabParser::RuleProperty_identifier);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(299);
    match(ShaderLabParser::Identifier);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Val_intContext ------------------------------------------------------------------

ShaderLabParser::Val_intContext::Val_intContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ShaderLabParser::Val_intContext::IntegerLiteral() {
  return getToken(ShaderLabParser::IntegerLiteral, 0);
}

tree::TerminalNode* ShaderLabParser::Val_intContext::Sign() {
  return getToken(ShaderLabParser::Sign, 0);
}


size_t ShaderLabParser::Val_intContext::getRuleIndex() const {
  return ShaderLabParser::RuleVal_int;
}

void ShaderLabParser::Val_intContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVal_int(this);
}

void ShaderLabParser::Val_intContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVal_int(this);
}


antlrcpp::Any ShaderLabParser::Val_intContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitVal_int(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Val_intContext* ShaderLabParser::val_int() {
  Val_intContext *_localctx = _tracker.createInstance<Val_intContext>(_ctx, getState());
  enterRule(_localctx, 58, ShaderLabParser::RuleVal_int);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(302);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ShaderLabParser::Sign) {
      setState(301);
      match(ShaderLabParser::Sign);
    }
    setState(304);
    match(ShaderLabParser::IntegerLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Val_floatContext ------------------------------------------------------------------

ShaderLabParser::Val_floatContext::Val_floatContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ShaderLabParser::Val_floatContext::FloatingLiteral() {
  return getToken(ShaderLabParser::FloatingLiteral, 0);
}

tree::TerminalNode* ShaderLabParser::Val_floatContext::Sign() {
  return getToken(ShaderLabParser::Sign, 0);
}


size_t ShaderLabParser::Val_floatContext::getRuleIndex() const {
  return ShaderLabParser::RuleVal_float;
}

void ShaderLabParser::Val_floatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVal_float(this);
}

void ShaderLabParser::Val_floatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVal_float(this);
}


antlrcpp::Any ShaderLabParser::Val_floatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitVal_float(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Val_floatContext* ShaderLabParser::val_float() {
  Val_floatContext *_localctx = _tracker.createInstance<Val_floatContext>(_ctx, getState());
  enterRule(_localctx, 60, ShaderLabParser::RuleVal_float);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(307);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ShaderLabParser::Sign) {
      setState(306);
      match(ShaderLabParser::Sign);
    }
    setState(309);
    match(ShaderLabParser::FloatingLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Val_minContext ------------------------------------------------------------------

ShaderLabParser::Val_minContext::Val_minContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ShaderLabParser::Val_minContext::FloatingLiteral() {
  return getToken(ShaderLabParser::FloatingLiteral, 0);
}

tree::TerminalNode* ShaderLabParser::Val_minContext::Sign() {
  return getToken(ShaderLabParser::Sign, 0);
}


size_t ShaderLabParser::Val_minContext::getRuleIndex() const {
  return ShaderLabParser::RuleVal_min;
}

void ShaderLabParser::Val_minContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVal_min(this);
}

void ShaderLabParser::Val_minContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVal_min(this);
}


antlrcpp::Any ShaderLabParser::Val_minContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitVal_min(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Val_minContext* ShaderLabParser::val_min() {
  Val_minContext *_localctx = _tracker.createInstance<Val_minContext>(_ctx, getState());
  enterRule(_localctx, 62, ShaderLabParser::RuleVal_min);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(312);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ShaderLabParser::Sign) {
      setState(311);
      match(ShaderLabParser::Sign);
    }
    setState(314);
    match(ShaderLabParser::FloatingLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Val_maxContext ------------------------------------------------------------------

ShaderLabParser::Val_maxContext::Val_maxContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ShaderLabParser::Val_maxContext::FloatingLiteral() {
  return getToken(ShaderLabParser::FloatingLiteral, 0);
}

tree::TerminalNode* ShaderLabParser::Val_maxContext::Sign() {
  return getToken(ShaderLabParser::Sign, 0);
}


size_t ShaderLabParser::Val_maxContext::getRuleIndex() const {
  return ShaderLabParser::RuleVal_max;
}

void ShaderLabParser::Val_maxContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVal_max(this);
}

void ShaderLabParser::Val_maxContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVal_max(this);
}


antlrcpp::Any ShaderLabParser::Val_maxContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitVal_max(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Val_maxContext* ShaderLabParser::val_max() {
  Val_maxContext *_localctx = _tracker.createInstance<Val_maxContext>(_ctx, getState());
  enterRule(_localctx, 64, ShaderLabParser::RuleVal_max);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(317);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ShaderLabParser::Sign) {
      setState(316);
      match(ShaderLabParser::Sign);
    }
    setState(319);
    match(ShaderLabParser::FloatingLiteral);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Val_vec4Context ------------------------------------------------------------------

ShaderLabParser::Val_vec4Context::Val_vec4Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ShaderLabParser::Val_floatContext *> ShaderLabParser::Val_vec4Context::val_float() {
  return getRuleContexts<ShaderLabParser::Val_floatContext>();
}

ShaderLabParser::Val_floatContext* ShaderLabParser::Val_vec4Context::val_float(size_t i) {
  return getRuleContext<ShaderLabParser::Val_floatContext>(i);
}


size_t ShaderLabParser::Val_vec4Context::getRuleIndex() const {
  return ShaderLabParser::RuleVal_vec4;
}

void ShaderLabParser::Val_vec4Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVal_vec4(this);
}

void ShaderLabParser::Val_vec4Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVal_vec4(this);
}


antlrcpp::Any ShaderLabParser::Val_vec4Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitVal_vec4(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::Val_vec4Context* ShaderLabParser::val_vec4() {
  Val_vec4Context *_localctx = _tracker.createInstance<Val_vec4Context>(_ctx, getState());
  enterRule(_localctx, 66, ShaderLabParser::RuleVal_vec4);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(321);
    match(ShaderLabParser::T__4);
    setState(322);
    val_float();
    setState(323);
    match(ShaderLabParser::T__5);
    setState(324);
    val_float();
    setState(325);
    match(ShaderLabParser::T__5);
    setState(326);
    val_float();
    setState(327);
    match(ShaderLabParser::T__5);
    setState(328);
    val_float();
    setState(329);
    match(ShaderLabParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ChannelContext ------------------------------------------------------------------

ShaderLabParser::ChannelContext::ChannelContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ShaderLabParser::ChannelContext::Channel() {
  return getToken(ShaderLabParser::Channel, 0);
}

tree::TerminalNode* ShaderLabParser::ChannelContext::IntegerLiteral() {
  return getToken(ShaderLabParser::IntegerLiteral, 0);
}


size_t ShaderLabParser::ChannelContext::getRuleIndex() const {
  return ShaderLabParser::RuleChannel;
}

void ShaderLabParser::ChannelContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChannel(this);
}

void ShaderLabParser::ChannelContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<ShaderLabListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChannel(this);
}


antlrcpp::Any ShaderLabParser::ChannelContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ShaderLabVisitor*>(visitor))
    return parserVisitor->visitChannel(this);
  else
    return visitor->visitChildren(this);
}

ShaderLabParser::ChannelContext* ShaderLabParser::channel() {
  ChannelContext *_localctx = _tracker.createInstance<ChannelContext>(_ctx, getState());
  enterRule(_localctx, 68, ShaderLabParser::RuleChannel);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(331);
    _la = _input->LA(1);
    if (!(_la == ShaderLabParser::IntegerLiteral

    || _la == ShaderLabParser::Channel)) {
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

// Static vars and initialization.
std::vector<dfa::DFA> ShaderLabParser::_decisionToDFA;
atn::PredictionContextCache ShaderLabParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN ShaderLabParser::_atn;
std::vector<uint16_t> ShaderLabParser::_serializedATN;

std::vector<std::string> ShaderLabParser::_ruleNames = {
  "shader", "properties", "property", "property_int", "property_float", 
  "property_range", "property_color", "property_vector", "property_2d", 
  "property_cube", "property_3d", "category", "kernel", "hlsl_block", "tags", 
  "tag", "common_state", "cull", "ztest", "zwrite", "color_mask", "meta", 
  "range", "tag_key", "tag_val", "shader_name", "display_name", "texture_name", 
  "property_identifier", "val_int", "val_float", "val_min", "val_max", "val_vec4", 
  "channel"
};

std::vector<std::string> ShaderLabParser::_literalNames = {
  "", "'Shader'", "'{'", "'}'", "'Properties'", "'('", "','", "'Int'", "')'", 
  "'='", "'Float'", "'Range'", "'Color'", "'Vector'", "'2D'", "'{}'", "'Cube'", 
  "'3D'", "'Category'", "'Kernel'", "'Tags'", "'Cull'", "'ZTest'", "'ZWrite'", 
  "'ColorMask'"
};

std::vector<std::string> ShaderLabParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "String", "MetaInfo", "HLSL", "Identifier", 
  "Sign", "IntegerLiteral", "FloatingLiteral", "ExponentPart", "CullMode", 
  "Comparator", "ZWriteMode", "Channel", "Whitespace", "Newline", "BlockComment", 
  "LineComment"
};

dfa::Vocabulary ShaderLabParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> ShaderLabParser::_tokenNames;

ShaderLabParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x2a, 0x150, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0x4d, 0xa, 0x2, 0x3, 0x2, 0x3, 0x2, 
    0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x6, 0x3, 0x55, 0xa, 0x3, 0xd, 
    0x3, 0xe, 0x3, 0x56, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x63, 0xa, 
    0x4, 0x3, 0x5, 0x7, 0x5, 0x66, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0x69, 0xb, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x7, 0x6, 0x75, 0xa, 0x6, 0xc, 0x6, 
    0xe, 0x6, 0x78, 0xb, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x7, 0x7, 0x84, 
    0xa, 0x7, 0xc, 0x7, 0xe, 0x7, 0x87, 0xb, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x8, 0x7, 0x8, 0x94, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x97, 0xb, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x7, 0x9, 0xa3, 0xa, 0x9, 0xc, 0x9, 
    0xe, 0x9, 0xa6, 0xb, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x7, 0xa, 0xb2, 
    0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0xb5, 0xb, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xb, 0x7, 0xb, 0xc2, 0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0xc5, 0xb, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x7, 0xc, 0xd2, 0xa, 0xc, 
    0xc, 0xc, 0xe, 0xc, 0xd5, 0xb, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0xe4, 0xa, 0xd, 0x3, 0xd, 0x6, 0xd, 
    0xe7, 0xa, 0xd, 0xd, 0xd, 0xe, 0xd, 0xe8, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 
    0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0xf1, 0xa, 0xe, 0xc, 0xe, 0xe, 
    0xe, 0xf4, 0xb, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x6, 0x10, 0xfe, 0xa, 0x10, 0xd, 0x10, 
    0xe, 0x10, 0xff, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 
    0x3, 0x11, 0x5, 0x11, 0x108, 0xa, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x3, 0x12, 0x5, 0x12, 0x10e, 0xa, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 
    0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1d, 
    0x3, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x5, 0x1f, 0x131, 0xa, 0x1f, 
    0x3, 0x1f, 0x3, 0x1f, 0x3, 0x20, 0x5, 0x20, 0x136, 0xa, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x21, 0x5, 0x21, 0x13b, 0xa, 0x21, 0x3, 0x21, 0x3, 0x21, 
    0x3, 0x22, 0x5, 0x22, 0x140, 0xa, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 
    0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x2, 0x2, 
    0x25, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 
    0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 
    0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x2, 
    0x3, 0x4, 0x2, 0x20, 0x20, 0x26, 0x26, 0x2, 0x149, 0x2, 0x48, 0x3, 0x2, 
    0x2, 0x2, 0x4, 0x51, 0x3, 0x2, 0x2, 0x2, 0x6, 0x62, 0x3, 0x2, 0x2, 0x2, 
    0x8, 0x67, 0x3, 0x2, 0x2, 0x2, 0xa, 0x76, 0x3, 0x2, 0x2, 0x2, 0xc, 0x85, 
    0x3, 0x2, 0x2, 0x2, 0xe, 0x95, 0x3, 0x2, 0x2, 0x2, 0x10, 0xa4, 0x3, 
    0x2, 0x2, 0x2, 0x12, 0xb3, 0x3, 0x2, 0x2, 0x2, 0x14, 0xc3, 0x3, 0x2, 
    0x2, 0x2, 0x16, 0xd3, 0x3, 0x2, 0x2, 0x2, 0x18, 0xe0, 0x3, 0x2, 0x2, 
    0x2, 0x1a, 0xec, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xf8, 0x3, 0x2, 0x2, 0x2, 
    0x1e, 0xfa, 0x3, 0x2, 0x2, 0x2, 0x20, 0x103, 0x3, 0x2, 0x2, 0x2, 0x22, 
    0x10d, 0x3, 0x2, 0x2, 0x2, 0x24, 0x10f, 0x3, 0x2, 0x2, 0x2, 0x26, 0x112, 
    0x3, 0x2, 0x2, 0x2, 0x28, 0x115, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x118, 0x3, 
    0x2, 0x2, 0x2, 0x2c, 0x11b, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x11d, 0x3, 0x2, 
    0x2, 0x2, 0x30, 0x123, 0x3, 0x2, 0x2, 0x2, 0x32, 0x125, 0x3, 0x2, 0x2, 
    0x2, 0x34, 0x127, 0x3, 0x2, 0x2, 0x2, 0x36, 0x129, 0x3, 0x2, 0x2, 0x2, 
    0x38, 0x12b, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x12d, 0x3, 0x2, 0x2, 0x2, 0x3c, 
    0x130, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x135, 0x3, 0x2, 0x2, 0x2, 0x40, 0x13a, 
    0x3, 0x2, 0x2, 0x2, 0x42, 0x13f, 0x3, 0x2, 0x2, 0x2, 0x44, 0x143, 0x3, 
    0x2, 0x2, 0x2, 0x46, 0x14d, 0x3, 0x2, 0x2, 0x2, 0x48, 0x49, 0x7, 0x3, 
    0x2, 0x2, 0x49, 0x4a, 0x5, 0x34, 0x1b, 0x2, 0x4a, 0x4c, 0x7, 0x4, 0x2, 
    0x2, 0x4b, 0x4d, 0x5, 0x4, 0x3, 0x2, 0x4c, 0x4b, 0x3, 0x2, 0x2, 0x2, 
    0x4c, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x4e, 
    0x4f, 0x5, 0x18, 0xd, 0x2, 0x4f, 0x50, 0x7, 0x5, 0x2, 0x2, 0x50, 0x3, 
    0x3, 0x2, 0x2, 0x2, 0x51, 0x52, 0x7, 0x6, 0x2, 0x2, 0x52, 0x54, 0x7, 
    0x4, 0x2, 0x2, 0x53, 0x55, 0x5, 0x6, 0x4, 0x2, 0x54, 0x53, 0x3, 0x2, 
    0x2, 0x2, 0x55, 0x56, 0x3, 0x2, 0x2, 0x2, 0x56, 0x54, 0x3, 0x2, 0x2, 
    0x2, 0x56, 0x57, 0x3, 0x2, 0x2, 0x2, 0x57, 0x58, 0x3, 0x2, 0x2, 0x2, 
    0x58, 0x59, 0x7, 0x5, 0x2, 0x2, 0x59, 0x5, 0x3, 0x2, 0x2, 0x2, 0x5a, 
    0x63, 0x5, 0x8, 0x5, 0x2, 0x5b, 0x63, 0x5, 0xa, 0x6, 0x2, 0x5c, 0x63, 
    0x5, 0xc, 0x7, 0x2, 0x5d, 0x63, 0x5, 0xe, 0x8, 0x2, 0x5e, 0x63, 0x5, 
    0x10, 0x9, 0x2, 0x5f, 0x63, 0x5, 0x12, 0xa, 0x2, 0x60, 0x63, 0x5, 0x14, 
    0xb, 0x2, 0x61, 0x63, 0x5, 0x16, 0xc, 0x2, 0x62, 0x5a, 0x3, 0x2, 0x2, 
    0x2, 0x62, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x62, 0x5c, 0x3, 0x2, 0x2, 0x2, 
    0x62, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x62, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x62, 
    0x5f, 0x3, 0x2, 0x2, 0x2, 0x62, 0x60, 0x3, 0x2, 0x2, 0x2, 0x62, 0x61, 
    0x3, 0x2, 0x2, 0x2, 0x63, 0x7, 0x3, 0x2, 0x2, 0x2, 0x64, 0x66, 0x5, 
    0x2c, 0x17, 0x2, 0x65, 0x64, 0x3, 0x2, 0x2, 0x2, 0x66, 0x69, 0x3, 0x2, 
    0x2, 0x2, 0x67, 0x65, 0x3, 0x2, 0x2, 0x2, 0x67, 0x68, 0x3, 0x2, 0x2, 
    0x2, 0x68, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x69, 0x67, 0x3, 0x2, 0x2, 0x2, 
    0x6a, 0x6b, 0x5, 0x3a, 0x1e, 0x2, 0x6b, 0x6c, 0x7, 0x7, 0x2, 0x2, 0x6c, 
    0x6d, 0x5, 0x36, 0x1c, 0x2, 0x6d, 0x6e, 0x7, 0x8, 0x2, 0x2, 0x6e, 0x6f, 
    0x7, 0x9, 0x2, 0x2, 0x6f, 0x70, 0x7, 0xa, 0x2, 0x2, 0x70, 0x71, 0x7, 
    0xb, 0x2, 0x2, 0x71, 0x72, 0x5, 0x3c, 0x1f, 0x2, 0x72, 0x9, 0x3, 0x2, 
    0x2, 0x2, 0x73, 0x75, 0x5, 0x2c, 0x17, 0x2, 0x74, 0x73, 0x3, 0x2, 0x2, 
    0x2, 0x75, 0x78, 0x3, 0x2, 0x2, 0x2, 0x76, 0x74, 0x3, 0x2, 0x2, 0x2, 
    0x76, 0x77, 0x3, 0x2, 0x2, 0x2, 0x77, 0x79, 0x3, 0x2, 0x2, 0x2, 0x78, 
    0x76, 0x3, 0x2, 0x2, 0x2, 0x79, 0x7a, 0x5, 0x3a, 0x1e, 0x2, 0x7a, 0x7b, 
    0x7, 0x7, 0x2, 0x2, 0x7b, 0x7c, 0x5, 0x36, 0x1c, 0x2, 0x7c, 0x7d, 0x7, 
    0x8, 0x2, 0x2, 0x7d, 0x7e, 0x7, 0xc, 0x2, 0x2, 0x7e, 0x7f, 0x7, 0xa, 
    0x2, 0x2, 0x7f, 0x80, 0x7, 0xb, 0x2, 0x2, 0x80, 0x81, 0x5, 0x3e, 0x20, 
    0x2, 0x81, 0xb, 0x3, 0x2, 0x2, 0x2, 0x82, 0x84, 0x5, 0x2c, 0x17, 0x2, 
    0x83, 0x82, 0x3, 0x2, 0x2, 0x2, 0x84, 0x87, 0x3, 0x2, 0x2, 0x2, 0x85, 
    0x83, 0x3, 0x2, 0x2, 0x2, 0x85, 0x86, 0x3, 0x2, 0x2, 0x2, 0x86, 0x88, 
    0x3, 0x2, 0x2, 0x2, 0x87, 0x85, 0x3, 0x2, 0x2, 0x2, 0x88, 0x89, 0x5, 
    0x3a, 0x1e, 0x2, 0x89, 0x8a, 0x7, 0x7, 0x2, 0x2, 0x8a, 0x8b, 0x5, 0x36, 
    0x1c, 0x2, 0x8b, 0x8c, 0x7, 0x8, 0x2, 0x2, 0x8c, 0x8d, 0x7, 0xd, 0x2, 
    0x2, 0x8d, 0x8e, 0x5, 0x2e, 0x18, 0x2, 0x8e, 0x8f, 0x7, 0xa, 0x2, 0x2, 
    0x8f, 0x90, 0x7, 0xb, 0x2, 0x2, 0x90, 0x91, 0x5, 0x3e, 0x20, 0x2, 0x91, 
    0xd, 0x3, 0x2, 0x2, 0x2, 0x92, 0x94, 0x5, 0x2c, 0x17, 0x2, 0x93, 0x92, 
    0x3, 0x2, 0x2, 0x2, 0x94, 0x97, 0x3, 0x2, 0x2, 0x2, 0x95, 0x93, 0x3, 
    0x2, 0x2, 0x2, 0x95, 0x96, 0x3, 0x2, 0x2, 0x2, 0x96, 0x98, 0x3, 0x2, 
    0x2, 0x2, 0x97, 0x95, 0x3, 0x2, 0x2, 0x2, 0x98, 0x99, 0x5, 0x3a, 0x1e, 
    0x2, 0x99, 0x9a, 0x7, 0x7, 0x2, 0x2, 0x9a, 0x9b, 0x5, 0x36, 0x1c, 0x2, 
    0x9b, 0x9c, 0x7, 0x8, 0x2, 0x2, 0x9c, 0x9d, 0x7, 0xe, 0x2, 0x2, 0x9d, 
    0x9e, 0x7, 0xa, 0x2, 0x2, 0x9e, 0x9f, 0x7, 0xb, 0x2, 0x2, 0x9f, 0xa0, 
    0x5, 0x44, 0x23, 0x2, 0xa0, 0xf, 0x3, 0x2, 0x2, 0x2, 0xa1, 0xa3, 0x5, 
    0x2c, 0x17, 0x2, 0xa2, 0xa1, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa6, 0x3, 0x2, 
    0x2, 0x2, 0xa4, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa5, 0x3, 0x2, 0x2, 
    0x2, 0xa5, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa4, 0x3, 0x2, 0x2, 0x2, 
    0xa7, 0xa8, 0x5, 0x3a, 0x1e, 0x2, 0xa8, 0xa9, 0x7, 0x7, 0x2, 0x2, 0xa9, 
    0xaa, 0x5, 0x36, 0x1c, 0x2, 0xaa, 0xab, 0x7, 0x8, 0x2, 0x2, 0xab, 0xac, 
    0x7, 0xf, 0x2, 0x2, 0xac, 0xad, 0x7, 0xa, 0x2, 0x2, 0xad, 0xae, 0x7, 
    0xb, 0x2, 0x2, 0xae, 0xaf, 0x5, 0x44, 0x23, 0x2, 0xaf, 0x11, 0x3, 0x2, 
    0x2, 0x2, 0xb0, 0xb2, 0x5, 0x2c, 0x17, 0x2, 0xb1, 0xb0, 0x3, 0x2, 0x2, 
    0x2, 0xb2, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb1, 0x3, 0x2, 0x2, 0x2, 
    0xb3, 0xb4, 0x3, 0x2, 0x2, 0x2, 0xb4, 0xb6, 0x3, 0x2, 0x2, 0x2, 0xb5, 
    0xb3, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb7, 0x5, 0x3a, 0x1e, 0x2, 0xb7, 0xb8, 
    0x7, 0x7, 0x2, 0x2, 0xb8, 0xb9, 0x5, 0x36, 0x1c, 0x2, 0xb9, 0xba, 0x7, 
    0x8, 0x2, 0x2, 0xba, 0xbb, 0x7, 0x10, 0x2, 0x2, 0xbb, 0xbc, 0x7, 0xa, 
    0x2, 0x2, 0xbc, 0xbd, 0x7, 0xb, 0x2, 0x2, 0xbd, 0xbe, 0x5, 0x38, 0x1d, 
    0x2, 0xbe, 0xbf, 0x7, 0x11, 0x2, 0x2, 0xbf, 0x13, 0x3, 0x2, 0x2, 0x2, 
    0xc0, 0xc2, 0x5, 0x2c, 0x17, 0x2, 0xc1, 0xc0, 0x3, 0x2, 0x2, 0x2, 0xc2, 
    0xc5, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xc1, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xc4, 
    0x3, 0x2, 0x2, 0x2, 0xc4, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc3, 0x3, 
    0x2, 0x2, 0x2, 0xc6, 0xc7, 0x5, 0x3a, 0x1e, 0x2, 0xc7, 0xc8, 0x7, 0x7, 
    0x2, 0x2, 0xc8, 0xc9, 0x5, 0x36, 0x1c, 0x2, 0xc9, 0xca, 0x7, 0x8, 0x2, 
    0x2, 0xca, 0xcb, 0x7, 0x12, 0x2, 0x2, 0xcb, 0xcc, 0x7, 0xa, 0x2, 0x2, 
    0xcc, 0xcd, 0x7, 0xb, 0x2, 0x2, 0xcd, 0xce, 0x5, 0x38, 0x1d, 0x2, 0xce, 
    0xcf, 0x7, 0x11, 0x2, 0x2, 0xcf, 0x15, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xd2, 
    0x5, 0x2c, 0x17, 0x2, 0xd1, 0xd0, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd5, 0x3, 
    0x2, 0x2, 0x2, 0xd3, 0xd1, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd4, 0x3, 0x2, 
    0x2, 0x2, 0xd4, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xd5, 0xd3, 0x3, 0x2, 0x2, 
    0x2, 0xd6, 0xd7, 0x5, 0x3a, 0x1e, 0x2, 0xd7, 0xd8, 0x7, 0x7, 0x2, 0x2, 
    0xd8, 0xd9, 0x5, 0x36, 0x1c, 0x2, 0xd9, 0xda, 0x7, 0x8, 0x2, 0x2, 0xda, 
    0xdb, 0x7, 0x13, 0x2, 0x2, 0xdb, 0xdc, 0x7, 0xa, 0x2, 0x2, 0xdc, 0xdd, 
    0x7, 0xb, 0x2, 0x2, 0xdd, 0xde, 0x5, 0x38, 0x1d, 0x2, 0xde, 0xdf, 0x7, 
    0x11, 0x2, 0x2, 0xdf, 0x17, 0x3, 0x2, 0x2, 0x2, 0xe0, 0xe1, 0x7, 0x14, 
    0x2, 0x2, 0xe1, 0xe3, 0x7, 0x4, 0x2, 0x2, 0xe2, 0xe4, 0x5, 0x1e, 0x10, 
    0x2, 0xe3, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xe4, 0x3, 0x2, 0x2, 0x2, 
    0xe4, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xe5, 0xe7, 0x5, 0x1a, 0xe, 0x2, 0xe6, 
    0xe5, 0x3, 0x2, 0x2, 0x2, 0xe7, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xe8, 0xe6, 
    0x3, 0x2, 0x2, 0x2, 0xe8, 0xe9, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xea, 0x3, 
    0x2, 0x2, 0x2, 0xea, 0xeb, 0x7, 0x5, 0x2, 0x2, 0xeb, 0x19, 0x3, 0x2, 
    0x2, 0x2, 0xec, 0xed, 0x7, 0x15, 0x2, 0x2, 0xed, 0xee, 0x7, 0x4, 0x2, 
    0x2, 0xee, 0xf2, 0x5, 0x1e, 0x10, 0x2, 0xef, 0xf1, 0x5, 0x22, 0x12, 
    0x2, 0xf0, 0xef, 0x3, 0x2, 0x2, 0x2, 0xf1, 0xf4, 0x3, 0x2, 0x2, 0x2, 
    0xf2, 0xf0, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xf3, 
    0xf5, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xf2, 0x3, 0x2, 0x2, 0x2, 0xf5, 0xf6, 
    0x5, 0x1c, 0xf, 0x2, 0xf6, 0xf7, 0x7, 0x5, 0x2, 0x2, 0xf7, 0x1b, 0x3, 
    0x2, 0x2, 0x2, 0xf8, 0xf9, 0x7, 0x1d, 0x2, 0x2, 0xf9, 0x1d, 0x3, 0x2, 
    0x2, 0x2, 0xfa, 0xfb, 0x7, 0x16, 0x2, 0x2, 0xfb, 0xfd, 0x7, 0x4, 0x2, 
    0x2, 0xfc, 0xfe, 0x5, 0x20, 0x11, 0x2, 0xfd, 0xfc, 0x3, 0x2, 0x2, 0x2, 
    0xfe, 0xff, 0x3, 0x2, 0x2, 0x2, 0xff, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xff, 
    0x100, 0x3, 0x2, 0x2, 0x2, 0x100, 0x101, 0x3, 0x2, 0x2, 0x2, 0x101, 
    0x102, 0x7, 0x5, 0x2, 0x2, 0x102, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x103, 0x104, 
    0x5, 0x30, 0x19, 0x2, 0x104, 0x105, 0x7, 0xb, 0x2, 0x2, 0x105, 0x107, 
    0x5, 0x32, 0x1a, 0x2, 0x106, 0x108, 0x7, 0x8, 0x2, 0x2, 0x107, 0x106, 
    0x3, 0x2, 0x2, 0x2, 0x107, 0x108, 0x3, 0x2, 0x2, 0x2, 0x108, 0x21, 0x3, 
    0x2, 0x2, 0x2, 0x109, 0x10e, 0x5, 0x24, 0x13, 0x2, 0x10a, 0x10e, 0x5, 
    0x26, 0x14, 0x2, 0x10b, 0x10e, 0x5, 0x28, 0x15, 0x2, 0x10c, 0x10e, 0x5, 
    0x2a, 0x16, 0x2, 0x10d, 0x109, 0x3, 0x2, 0x2, 0x2, 0x10d, 0x10a, 0x3, 
    0x2, 0x2, 0x2, 0x10d, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x10d, 0x10c, 0x3, 
    0x2, 0x2, 0x2, 0x10e, 0x23, 0x3, 0x2, 0x2, 0x2, 0x10f, 0x110, 0x7, 0x17, 
    0x2, 0x2, 0x110, 0x111, 0x7, 0x23, 0x2, 0x2, 0x111, 0x25, 0x3, 0x2, 
    0x2, 0x2, 0x112, 0x113, 0x7, 0x18, 0x2, 0x2, 0x113, 0x114, 0x7, 0x24, 
    0x2, 0x2, 0x114, 0x27, 0x3, 0x2, 0x2, 0x2, 0x115, 0x116, 0x7, 0x19, 
    0x2, 0x2, 0x116, 0x117, 0x7, 0x25, 0x2, 0x2, 0x117, 0x29, 0x3, 0x2, 
    0x2, 0x2, 0x118, 0x119, 0x7, 0x1a, 0x2, 0x2, 0x119, 0x11a, 0x5, 0x46, 
    0x24, 0x2, 0x11a, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x11b, 0x11c, 0x7, 0x1c, 
    0x2, 0x2, 0x11c, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x11e, 0x7, 0x7, 0x2, 
    0x2, 0x11e, 0x11f, 0x5, 0x40, 0x21, 0x2, 0x11f, 0x120, 0x7, 0x8, 0x2, 
    0x2, 0x120, 0x121, 0x5, 0x42, 0x22, 0x2, 0x121, 0x122, 0x7, 0xa, 0x2, 
    0x2, 0x122, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x123, 0x124, 0x7, 0x1b, 0x2, 
    0x2, 0x124, 0x31, 0x3, 0x2, 0x2, 0x2, 0x125, 0x126, 0x7, 0x1b, 0x2, 
    0x2, 0x126, 0x33, 0x3, 0x2, 0x2, 0x2, 0x127, 0x128, 0x7, 0x1b, 0x2, 
    0x2, 0x128, 0x35, 0x3, 0x2, 0x2, 0x2, 0x129, 0x12a, 0x7, 0x1b, 0x2, 
    0x2, 0x12a, 0x37, 0x3, 0x2, 0x2, 0x2, 0x12b, 0x12c, 0x7, 0x1b, 0x2, 
    0x2, 0x12c, 0x39, 0x3, 0x2, 0x2, 0x2, 0x12d, 0x12e, 0x7, 0x1e, 0x2, 
    0x2, 0x12e, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x131, 0x7, 0x1f, 0x2, 
    0x2, 0x130, 0x12f, 0x3, 0x2, 0x2, 0x2, 0x130, 0x131, 0x3, 0x2, 0x2, 
    0x2, 0x131, 0x132, 0x3, 0x2, 0x2, 0x2, 0x132, 0x133, 0x7, 0x20, 0x2, 
    0x2, 0x133, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x134, 0x136, 0x7, 0x1f, 0x2, 
    0x2, 0x135, 0x134, 0x3, 0x2, 0x2, 0x2, 0x135, 0x136, 0x3, 0x2, 0x2, 
    0x2, 0x136, 0x137, 0x3, 0x2, 0x2, 0x2, 0x137, 0x138, 0x7, 0x21, 0x2, 
    0x2, 0x138, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x139, 0x13b, 0x7, 0x1f, 0x2, 
    0x2, 0x13a, 0x139, 0x3, 0x2, 0x2, 0x2, 0x13a, 0x13b, 0x3, 0x2, 0x2, 
    0x2, 0x13b, 0x13c, 0x3, 0x2, 0x2, 0x2, 0x13c, 0x13d, 0x7, 0x21, 0x2, 
    0x2, 0x13d, 0x41, 0x3, 0x2, 0x2, 0x2, 0x13e, 0x140, 0x7, 0x1f, 0x2, 
    0x2, 0x13f, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x140, 0x3, 0x2, 0x2, 
    0x2, 0x140, 0x141, 0x3, 0x2, 0x2, 0x2, 0x141, 0x142, 0x7, 0x21, 0x2, 
    0x2, 0x142, 0x43, 0x3, 0x2, 0x2, 0x2, 0x143, 0x144, 0x7, 0x7, 0x2, 0x2, 
    0x144, 0x145, 0x5, 0x3e, 0x20, 0x2, 0x145, 0x146, 0x7, 0x8, 0x2, 0x2, 
    0x146, 0x147, 0x5, 0x3e, 0x20, 0x2, 0x147, 0x148, 0x7, 0x8, 0x2, 0x2, 
    0x148, 0x149, 0x5, 0x3e, 0x20, 0x2, 0x149, 0x14a, 0x7, 0x8, 0x2, 0x2, 
    0x14a, 0x14b, 0x5, 0x3e, 0x20, 0x2, 0x14b, 0x14c, 0x7, 0xa, 0x2, 0x2, 
    0x14c, 0x45, 0x3, 0x2, 0x2, 0x2, 0x14d, 0x14e, 0x9, 0x2, 0x2, 0x2, 0x14e, 
    0x47, 0x3, 0x2, 0x2, 0x2, 0x17, 0x4c, 0x56, 0x62, 0x67, 0x76, 0x85, 
    0x95, 0xa4, 0xb3, 0xc3, 0xd3, 0xe3, 0xe8, 0xf2, 0xff, 0x107, 0x10d, 
    0x130, 0x135, 0x13a, 0x13f, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

ShaderLabParser::Initializer ShaderLabParser::_init;
