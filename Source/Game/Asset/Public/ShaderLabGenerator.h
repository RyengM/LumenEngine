#pragma once

#include "ThirdParty/ANTLR/Runtime/Public/antlr4-runtime.h"
#include "ThirdParty/ANTLR/ParserShaderLab/ANTLRShaderLab/ShaderLabLexer.h"
#include "ThirdParty/ANTLR/ParserShaderLab/ANTLRShaderLab/ShaderLabBaseVisitor.h"

#include "ShaderLab.h"

namespace Lumen::Game
{
    class ShaderLabGenerator : public ShaderLabBaseVisitor
    {
    public:
        ShaderLab Compile(std::string_view source);

    private:
        virtual antlrcpp::Any visitChildren(antlr4::tree::ParseTree* node) override;

        virtual antlrcpp::Any visitShader(ShaderLabParser::ShaderContext* ctx) override;

        virtual antlrcpp::Any visitProperties(ShaderLabParser::PropertiesContext* ctx) override;

        virtual antlrcpp::Any visitProperty_int(ShaderLabParser::Property_intContext* ctx) override;

        virtual antlrcpp::Any visitProperty_float(ShaderLabParser::Property_floatContext* ctx) override;

        virtual antlrcpp::Any visitProperty_range(ShaderLabParser::Property_rangeContext* ctx) override;

        virtual antlrcpp::Any visitProperty_color(ShaderLabParser::Property_colorContext* ctx) override;

        virtual antlrcpp::Any visitProperty_vector(ShaderLabParser::Property_vectorContext* ctx) override;

        virtual antlrcpp::Any visitProperty_2d(ShaderLabParser::Property_2dContext* ctx) override;

        virtual antlrcpp::Any visitProperty_cube(ShaderLabParser::Property_cubeContext* ctx) override;

        virtual antlrcpp::Any visitProperty_3d(ShaderLabParser::Property_3dContext* ctx) override;

        virtual antlrcpp::Any visitCategory(ShaderLabParser::CategoryContext* ctx) override;

        virtual antlrcpp::Any visitKernel(ShaderLabParser::KernelContext * ctx) override;

        virtual antlrcpp::Any visitHlsl_block(ShaderLabParser::Hlsl_blockContext* ctx) override;

        virtual antlrcpp::Any visitTags(ShaderLabParser::TagsContext* context) override;

        virtual antlrcpp::Any visitCull(ShaderLabParser::CullContext* ctx) override;

        virtual antlrcpp::Any visitZtest(ShaderLabParser::ZtestContext* ctx) override;

        virtual antlrcpp::Any visitZwrite(ShaderLabParser::ZwriteContext* ctx) override;

        virtual antlrcpp::Any visitColor_mask(ShaderLabParser::Color_maskContext* ctx) override;

        virtual antlrcpp::Any visitMeta(ShaderLabParser::MetaContext* ctx) override;

        virtual antlrcpp::Any visitRange(ShaderLabParser::RangeContext* ctx) override;

        virtual antlrcpp::Any visitTag_key(ShaderLabParser::Tag_keyContext* ctx) override;

        virtual antlrcpp::Any visitTag_val(ShaderLabParser::Tag_valContext* ctx) override;

        virtual antlrcpp::Any visitShader_name(ShaderLabParser::Shader_nameContext* ctx) override;

        virtual antlrcpp::Any visitDisplay_name(ShaderLabParser::Display_nameContext* ctx) override;

        virtual antlrcpp::Any visitTexture_name(ShaderLabParser::Texture_nameContext* ctx) override;

        virtual antlrcpp::Any visitProperty_identifier(ShaderLabParser::Property_identifierContext* ctx) override;

        virtual antlrcpp::Any visitVal_int(ShaderLabParser::Val_intContext* ctx) override;

        virtual antlrcpp::Any visitVal_float(ShaderLabParser::Val_floatContext* ctx) override;

        virtual antlrcpp::Any visitVal_min(ShaderLabParser::Val_minContext* ctx) override;

        virtual antlrcpp::Any visitVal_max(ShaderLabParser::Val_maxContext* ctx) override;

        virtual antlrcpp::Any visitVal_vec4(ShaderLabParser::Val_vec4Context* ctx) override;

        virtual antlrcpp::Any visitChannel(ShaderLabParser::ChannelContext* ctx) override;
    };
}