
// Generated from ShaderLab.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "ShaderLabVisitor.h"


/**
 * This class provides an empty implementation of ShaderLabVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ShaderLabBaseVisitor : public ShaderLabVisitor {
public:

  virtual antlrcpp::Any visitShader(ShaderLabParser::ShaderContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProperties(ShaderLabParser::PropertiesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProperty(ShaderLabParser::PropertyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProperty_int(ShaderLabParser::Property_intContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProperty_float(ShaderLabParser::Property_floatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProperty_range(ShaderLabParser::Property_rangeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProperty_color(ShaderLabParser::Property_colorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProperty_vector(ShaderLabParser::Property_vectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProperty_2d(ShaderLabParser::Property_2dContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProperty_cube(ShaderLabParser::Property_cubeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProperty_3d(ShaderLabParser::Property_3dContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCategory(ShaderLabParser::CategoryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitKernel(ShaderLabParser::KernelContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitHlsl_block(ShaderLabParser::Hlsl_blockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTags(ShaderLabParser::TagsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTag(ShaderLabParser::TagContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCommon_state(ShaderLabParser::Common_stateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCull(ShaderLabParser::CullContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitZtest(ShaderLabParser::ZtestContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitZwrite(ShaderLabParser::ZwriteContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitColor_mask(ShaderLabParser::Color_maskContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMeta(ShaderLabParser::MetaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRange(ShaderLabParser::RangeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTag_key(ShaderLabParser::Tag_keyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTag_val(ShaderLabParser::Tag_valContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitShader_name(ShaderLabParser::Shader_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDisplay_name(ShaderLabParser::Display_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTexture_name(ShaderLabParser::Texture_nameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProperty_identifier(ShaderLabParser::Property_identifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVal_int(ShaderLabParser::Val_intContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVal_float(ShaderLabParser::Val_floatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVal_min(ShaderLabParser::Val_minContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVal_max(ShaderLabParser::Val_maxContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVal_vec4(ShaderLabParser::Val_vec4Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitChannel(ShaderLabParser::ChannelContext *ctx) override {
    return visitChildren(ctx);
  }


};

