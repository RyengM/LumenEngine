
// Generated from ShaderLab.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "ShaderLabParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by ShaderLabParser.
 */
class  ShaderLabListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterShader(ShaderLabParser::ShaderContext *ctx) = 0;
  virtual void exitShader(ShaderLabParser::ShaderContext *ctx) = 0;

  virtual void enterProperties(ShaderLabParser::PropertiesContext *ctx) = 0;
  virtual void exitProperties(ShaderLabParser::PropertiesContext *ctx) = 0;

  virtual void enterProperty(ShaderLabParser::PropertyContext *ctx) = 0;
  virtual void exitProperty(ShaderLabParser::PropertyContext *ctx) = 0;

  virtual void enterProperty_int(ShaderLabParser::Property_intContext *ctx) = 0;
  virtual void exitProperty_int(ShaderLabParser::Property_intContext *ctx) = 0;

  virtual void enterProperty_float(ShaderLabParser::Property_floatContext *ctx) = 0;
  virtual void exitProperty_float(ShaderLabParser::Property_floatContext *ctx) = 0;

  virtual void enterProperty_range(ShaderLabParser::Property_rangeContext *ctx) = 0;
  virtual void exitProperty_range(ShaderLabParser::Property_rangeContext *ctx) = 0;

  virtual void enterProperty_color(ShaderLabParser::Property_colorContext *ctx) = 0;
  virtual void exitProperty_color(ShaderLabParser::Property_colorContext *ctx) = 0;

  virtual void enterProperty_vector(ShaderLabParser::Property_vectorContext *ctx) = 0;
  virtual void exitProperty_vector(ShaderLabParser::Property_vectorContext *ctx) = 0;

  virtual void enterProperty_2d(ShaderLabParser::Property_2dContext *ctx) = 0;
  virtual void exitProperty_2d(ShaderLabParser::Property_2dContext *ctx) = 0;

  virtual void enterProperty_cube(ShaderLabParser::Property_cubeContext *ctx) = 0;
  virtual void exitProperty_cube(ShaderLabParser::Property_cubeContext *ctx) = 0;

  virtual void enterProperty_3d(ShaderLabParser::Property_3dContext *ctx) = 0;
  virtual void exitProperty_3d(ShaderLabParser::Property_3dContext *ctx) = 0;

  virtual void enterCategory(ShaderLabParser::CategoryContext *ctx) = 0;
  virtual void exitCategory(ShaderLabParser::CategoryContext *ctx) = 0;

  virtual void enterKernel(ShaderLabParser::KernelContext *ctx) = 0;
  virtual void exitKernel(ShaderLabParser::KernelContext *ctx) = 0;

  virtual void enterHlsl_block(ShaderLabParser::Hlsl_blockContext *ctx) = 0;
  virtual void exitHlsl_block(ShaderLabParser::Hlsl_blockContext *ctx) = 0;

  virtual void enterTags(ShaderLabParser::TagsContext *ctx) = 0;
  virtual void exitTags(ShaderLabParser::TagsContext *ctx) = 0;

  virtual void enterTag(ShaderLabParser::TagContext *ctx) = 0;
  virtual void exitTag(ShaderLabParser::TagContext *ctx) = 0;

  virtual void enterCommon_state(ShaderLabParser::Common_stateContext *ctx) = 0;
  virtual void exitCommon_state(ShaderLabParser::Common_stateContext *ctx) = 0;

  virtual void enterCull(ShaderLabParser::CullContext *ctx) = 0;
  virtual void exitCull(ShaderLabParser::CullContext *ctx) = 0;

  virtual void enterZtest(ShaderLabParser::ZtestContext *ctx) = 0;
  virtual void exitZtest(ShaderLabParser::ZtestContext *ctx) = 0;

  virtual void enterZwrite(ShaderLabParser::ZwriteContext *ctx) = 0;
  virtual void exitZwrite(ShaderLabParser::ZwriteContext *ctx) = 0;

  virtual void enterColor_mask(ShaderLabParser::Color_maskContext *ctx) = 0;
  virtual void exitColor_mask(ShaderLabParser::Color_maskContext *ctx) = 0;

  virtual void enterMeta(ShaderLabParser::MetaContext *ctx) = 0;
  virtual void exitMeta(ShaderLabParser::MetaContext *ctx) = 0;

  virtual void enterRange(ShaderLabParser::RangeContext *ctx) = 0;
  virtual void exitRange(ShaderLabParser::RangeContext *ctx) = 0;

  virtual void enterTag_key(ShaderLabParser::Tag_keyContext *ctx) = 0;
  virtual void exitTag_key(ShaderLabParser::Tag_keyContext *ctx) = 0;

  virtual void enterTag_val(ShaderLabParser::Tag_valContext *ctx) = 0;
  virtual void exitTag_val(ShaderLabParser::Tag_valContext *ctx) = 0;

  virtual void enterShader_name(ShaderLabParser::Shader_nameContext *ctx) = 0;
  virtual void exitShader_name(ShaderLabParser::Shader_nameContext *ctx) = 0;

  virtual void enterDisplay_name(ShaderLabParser::Display_nameContext *ctx) = 0;
  virtual void exitDisplay_name(ShaderLabParser::Display_nameContext *ctx) = 0;

  virtual void enterTexture_name(ShaderLabParser::Texture_nameContext *ctx) = 0;
  virtual void exitTexture_name(ShaderLabParser::Texture_nameContext *ctx) = 0;

  virtual void enterProperty_identifier(ShaderLabParser::Property_identifierContext *ctx) = 0;
  virtual void exitProperty_identifier(ShaderLabParser::Property_identifierContext *ctx) = 0;

  virtual void enterVal_int(ShaderLabParser::Val_intContext *ctx) = 0;
  virtual void exitVal_int(ShaderLabParser::Val_intContext *ctx) = 0;

  virtual void enterVal_float(ShaderLabParser::Val_floatContext *ctx) = 0;
  virtual void exitVal_float(ShaderLabParser::Val_floatContext *ctx) = 0;

  virtual void enterVal_min(ShaderLabParser::Val_minContext *ctx) = 0;
  virtual void exitVal_min(ShaderLabParser::Val_minContext *ctx) = 0;

  virtual void enterVal_max(ShaderLabParser::Val_maxContext *ctx) = 0;
  virtual void exitVal_max(ShaderLabParser::Val_maxContext *ctx) = 0;

  virtual void enterVal_vec4(ShaderLabParser::Val_vec4Context *ctx) = 0;
  virtual void exitVal_vec4(ShaderLabParser::Val_vec4Context *ctx) = 0;

  virtual void enterChannel(ShaderLabParser::ChannelContext *ctx) = 0;
  virtual void exitChannel(ShaderLabParser::ChannelContext *ctx) = 0;


};

