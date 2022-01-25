
// Generated from ShaderLab.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "ShaderLabParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by ShaderLabParser.
 */
class  ShaderLabVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ShaderLabParser.
   */
    virtual antlrcpp::Any visitShader(ShaderLabParser::ShaderContext *context) = 0;

    virtual antlrcpp::Any visitProperties(ShaderLabParser::PropertiesContext *context) = 0;

    virtual antlrcpp::Any visitProperty(ShaderLabParser::PropertyContext *context) = 0;

    virtual antlrcpp::Any visitProperty_int(ShaderLabParser::Property_intContext *context) = 0;

    virtual antlrcpp::Any visitProperty_float(ShaderLabParser::Property_floatContext *context) = 0;

    virtual antlrcpp::Any visitProperty_range(ShaderLabParser::Property_rangeContext *context) = 0;

    virtual antlrcpp::Any visitProperty_color(ShaderLabParser::Property_colorContext *context) = 0;

    virtual antlrcpp::Any visitProperty_vector(ShaderLabParser::Property_vectorContext *context) = 0;

    virtual antlrcpp::Any visitProperty_2d(ShaderLabParser::Property_2dContext *context) = 0;

    virtual antlrcpp::Any visitProperty_cube(ShaderLabParser::Property_cubeContext *context) = 0;

    virtual antlrcpp::Any visitProperty_3d(ShaderLabParser::Property_3dContext *context) = 0;

    virtual antlrcpp::Any visitCategory(ShaderLabParser::CategoryContext *context) = 0;

    virtual antlrcpp::Any visitKernel(ShaderLabParser::KernelContext *context) = 0;

    virtual antlrcpp::Any visitHlsl_block(ShaderLabParser::Hlsl_blockContext *context) = 0;

    virtual antlrcpp::Any visitTags(ShaderLabParser::TagsContext *context) = 0;

    virtual antlrcpp::Any visitTag(ShaderLabParser::TagContext *context) = 0;

    virtual antlrcpp::Any visitCommon_state(ShaderLabParser::Common_stateContext *context) = 0;

    virtual antlrcpp::Any visitCull(ShaderLabParser::CullContext *context) = 0;

    virtual antlrcpp::Any visitZtest(ShaderLabParser::ZtestContext *context) = 0;

    virtual antlrcpp::Any visitZwrite(ShaderLabParser::ZwriteContext *context) = 0;

    virtual antlrcpp::Any visitColor_mask(ShaderLabParser::Color_maskContext *context) = 0;

    virtual antlrcpp::Any visitMeta(ShaderLabParser::MetaContext *context) = 0;

    virtual antlrcpp::Any visitRange(ShaderLabParser::RangeContext *context) = 0;

    virtual antlrcpp::Any visitTag_key(ShaderLabParser::Tag_keyContext *context) = 0;

    virtual antlrcpp::Any visitTag_val(ShaderLabParser::Tag_valContext *context) = 0;

    virtual antlrcpp::Any visitShader_name(ShaderLabParser::Shader_nameContext *context) = 0;

    virtual antlrcpp::Any visitDisplay_name(ShaderLabParser::Display_nameContext *context) = 0;

    virtual antlrcpp::Any visitTexture_name(ShaderLabParser::Texture_nameContext *context) = 0;

    virtual antlrcpp::Any visitProperty_identifier(ShaderLabParser::Property_identifierContext *context) = 0;

    virtual antlrcpp::Any visitVal_int(ShaderLabParser::Val_intContext *context) = 0;

    virtual antlrcpp::Any visitVal_float(ShaderLabParser::Val_floatContext *context) = 0;

    virtual antlrcpp::Any visitVal_min(ShaderLabParser::Val_minContext *context) = 0;

    virtual antlrcpp::Any visitVal_max(ShaderLabParser::Val_maxContext *context) = 0;

    virtual antlrcpp::Any visitVal_vec4(ShaderLabParser::Val_vec4Context *context) = 0;

    virtual antlrcpp::Any visitChannel(ShaderLabParser::ChannelContext *context) = 0;


};

