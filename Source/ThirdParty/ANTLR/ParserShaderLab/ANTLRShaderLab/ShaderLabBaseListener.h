
// Generated from ShaderLab.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "ShaderLabListener.h"


/**
 * This class provides an empty implementation of ShaderLabListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  ShaderLabBaseListener : public ShaderLabListener {
public:

  virtual void enterShader(ShaderLabParser::ShaderContext * /*ctx*/) override { }
  virtual void exitShader(ShaderLabParser::ShaderContext * /*ctx*/) override { }

  virtual void enterProperties(ShaderLabParser::PropertiesContext * /*ctx*/) override { }
  virtual void exitProperties(ShaderLabParser::PropertiesContext * /*ctx*/) override { }

  virtual void enterProperty(ShaderLabParser::PropertyContext * /*ctx*/) override { }
  virtual void exitProperty(ShaderLabParser::PropertyContext * /*ctx*/) override { }

  virtual void enterProperty_int(ShaderLabParser::Property_intContext * /*ctx*/) override { }
  virtual void exitProperty_int(ShaderLabParser::Property_intContext * /*ctx*/) override { }

  virtual void enterProperty_float(ShaderLabParser::Property_floatContext * /*ctx*/) override { }
  virtual void exitProperty_float(ShaderLabParser::Property_floatContext * /*ctx*/) override { }

  virtual void enterProperty_range(ShaderLabParser::Property_rangeContext * /*ctx*/) override { }
  virtual void exitProperty_range(ShaderLabParser::Property_rangeContext * /*ctx*/) override { }

  virtual void enterProperty_color(ShaderLabParser::Property_colorContext * /*ctx*/) override { }
  virtual void exitProperty_color(ShaderLabParser::Property_colorContext * /*ctx*/) override { }

  virtual void enterProperty_vector(ShaderLabParser::Property_vectorContext * /*ctx*/) override { }
  virtual void exitProperty_vector(ShaderLabParser::Property_vectorContext * /*ctx*/) override { }

  virtual void enterProperty_2d(ShaderLabParser::Property_2dContext * /*ctx*/) override { }
  virtual void exitProperty_2d(ShaderLabParser::Property_2dContext * /*ctx*/) override { }

  virtual void enterProperty_cube(ShaderLabParser::Property_cubeContext * /*ctx*/) override { }
  virtual void exitProperty_cube(ShaderLabParser::Property_cubeContext * /*ctx*/) override { }

  virtual void enterProperty_3d(ShaderLabParser::Property_3dContext * /*ctx*/) override { }
  virtual void exitProperty_3d(ShaderLabParser::Property_3dContext * /*ctx*/) override { }

  virtual void enterCategory(ShaderLabParser::CategoryContext * /*ctx*/) override { }
  virtual void exitCategory(ShaderLabParser::CategoryContext * /*ctx*/) override { }

  virtual void enterKernel(ShaderLabParser::KernelContext * /*ctx*/) override { }
  virtual void exitKernel(ShaderLabParser::KernelContext * /*ctx*/) override { }

  virtual void enterHlsl_block(ShaderLabParser::Hlsl_blockContext * /*ctx*/) override { }
  virtual void exitHlsl_block(ShaderLabParser::Hlsl_blockContext * /*ctx*/) override { }

  virtual void enterTags(ShaderLabParser::TagsContext * /*ctx*/) override { }
  virtual void exitTags(ShaderLabParser::TagsContext * /*ctx*/) override { }

  virtual void enterTag(ShaderLabParser::TagContext * /*ctx*/) override { }
  virtual void exitTag(ShaderLabParser::TagContext * /*ctx*/) override { }

  virtual void enterCommon_state(ShaderLabParser::Common_stateContext * /*ctx*/) override { }
  virtual void exitCommon_state(ShaderLabParser::Common_stateContext * /*ctx*/) override { }

  virtual void enterCull(ShaderLabParser::CullContext * /*ctx*/) override { }
  virtual void exitCull(ShaderLabParser::CullContext * /*ctx*/) override { }

  virtual void enterZtest(ShaderLabParser::ZtestContext * /*ctx*/) override { }
  virtual void exitZtest(ShaderLabParser::ZtestContext * /*ctx*/) override { }

  virtual void enterZwrite(ShaderLabParser::ZwriteContext * /*ctx*/) override { }
  virtual void exitZwrite(ShaderLabParser::ZwriteContext * /*ctx*/) override { }

  virtual void enterColor_mask(ShaderLabParser::Color_maskContext * /*ctx*/) override { }
  virtual void exitColor_mask(ShaderLabParser::Color_maskContext * /*ctx*/) override { }

  virtual void enterMeta(ShaderLabParser::MetaContext * /*ctx*/) override { }
  virtual void exitMeta(ShaderLabParser::MetaContext * /*ctx*/) override { }

  virtual void enterRange(ShaderLabParser::RangeContext * /*ctx*/) override { }
  virtual void exitRange(ShaderLabParser::RangeContext * /*ctx*/) override { }

  virtual void enterTag_key(ShaderLabParser::Tag_keyContext * /*ctx*/) override { }
  virtual void exitTag_key(ShaderLabParser::Tag_keyContext * /*ctx*/) override { }

  virtual void enterTag_val(ShaderLabParser::Tag_valContext * /*ctx*/) override { }
  virtual void exitTag_val(ShaderLabParser::Tag_valContext * /*ctx*/) override { }

  virtual void enterShader_name(ShaderLabParser::Shader_nameContext * /*ctx*/) override { }
  virtual void exitShader_name(ShaderLabParser::Shader_nameContext * /*ctx*/) override { }

  virtual void enterDisplay_name(ShaderLabParser::Display_nameContext * /*ctx*/) override { }
  virtual void exitDisplay_name(ShaderLabParser::Display_nameContext * /*ctx*/) override { }

  virtual void enterTexture_name(ShaderLabParser::Texture_nameContext * /*ctx*/) override { }
  virtual void exitTexture_name(ShaderLabParser::Texture_nameContext * /*ctx*/) override { }

  virtual void enterProperty_identifier(ShaderLabParser::Property_identifierContext * /*ctx*/) override { }
  virtual void exitProperty_identifier(ShaderLabParser::Property_identifierContext * /*ctx*/) override { }

  virtual void enterVal_int(ShaderLabParser::Val_intContext * /*ctx*/) override { }
  virtual void exitVal_int(ShaderLabParser::Val_intContext * /*ctx*/) override { }

  virtual void enterVal_float(ShaderLabParser::Val_floatContext * /*ctx*/) override { }
  virtual void exitVal_float(ShaderLabParser::Val_floatContext * /*ctx*/) override { }

  virtual void enterVal_min(ShaderLabParser::Val_minContext * /*ctx*/) override { }
  virtual void exitVal_min(ShaderLabParser::Val_minContext * /*ctx*/) override { }

  virtual void enterVal_max(ShaderLabParser::Val_maxContext * /*ctx*/) override { }
  virtual void exitVal_max(ShaderLabParser::Val_maxContext * /*ctx*/) override { }

  virtual void enterVal_vec4(ShaderLabParser::Val_vec4Context * /*ctx*/) override { }
  virtual void exitVal_vec4(ShaderLabParser::Val_vec4Context * /*ctx*/) override { }

  virtual void enterChannel(ShaderLabParser::ChannelContext * /*ctx*/) override { }
  virtual void exitChannel(ShaderLabParser::ChannelContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

