#include "Game/Asset/Public/ShaderLabGenerator.h"

using namespace Lumen::Game;

std::string_view ExtractString(std::string_view sourceStr)
{
    sourceStr.remove_prefix(1);
    sourceStr.remove_suffix(1);
    return sourceStr;
}

std::string_view ExtractHLSL(std::string_view sourceStr)
{
    sourceStr.remove_prefix(11);
    sourceStr.remove_suffix(7);
    return sourceStr;
}

ShaderLab ShaderLabGenerator::Compile(std::string_view source)
{
    antlr4::ANTLRInputStream input(source.data());
    ShaderLabLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    ShaderLabParser parser(&tokens);

    ShaderLab shaderLab = std::move(visitShader(parser.shader()));

    return shaderLab;
}

antlrcpp::Any ShaderLabGenerator::visitChildren(antlr4::tree::ParseTree* node)
{
    antlrcpp::Any result = defaultResult();
    std::size_t n = node->children.size();
    for (std::size_t i = 0; i < n; i++)
    {
        if (!shouldVisitNextChild(node, result))
            break;
        antlrcpp::Any childResult = node->children[i]->accept(this);
        result = std::move(childResult);
    }
    return result;
}

antlrcpp::Any ShaderLabGenerator::visitShader(ShaderLabParser::ShaderContext* ctx)
{
    ShaderLab shaderLab;

    std::string shaderName = visitShader_name(ctx->shader_name());
    shaderLab.name = std::move(shaderName);
    if (ctx->properties())
    {
        std::unordered_map<std::string, Property> properties = visitProperties(ctx->properties());
        shaderLab.properties = std::move(properties);
    }
    if (ctx->category())
    {
        Category category = visitCategory(ctx->category());
        shaderLab.categories = std::move(category);
    }

    return shaderLab;
}

antlrcpp::Any ShaderLabGenerator::visitProperties(ShaderLabParser::PropertiesContext* ctx)
{
    std::unordered_map<std::string, Property> properties;

    for (auto propertyContext : ctx->property())
    {
        Property property = std::move(visitProperty(propertyContext));
        properties.insert({ property.name, property });
    }
    
    return properties;
}

antlrcpp::Any ShaderLabGenerator::visitProperty_int(ShaderLabParser::Property_intContext* ctx)
{
    Property property;
    std::string name = visitProperty_identifier(ctx->property_identifier());
    property.name = std::move(name);
    std::string displayName = visitDisplay_name(ctx->display_name());
    property.displayName = std::move(displayName);
    for (auto metaContext : ctx->meta())
    {
        std::string meta = visitMeta(metaContext);
        property.metas.emplace_back(std::move(meta));
    }
    int value = visitVal_int(ctx->val_int());
    property.value = value;

    return property;
}

antlrcpp::Any ShaderLabGenerator::visitProperty_float(ShaderLabParser::Property_floatContext* ctx)
{
    Property property;
    std::string name = visitProperty_identifier(ctx->property_identifier());
    property.name = std::move(name);
    std::string displayName = visitDisplay_name(ctx->display_name());
    property.displayName = std::move(displayName);
    for (auto metaContext : ctx->meta())
    {
        std::string meta = visitMeta(metaContext);
        property.metas.emplace_back(std::move(meta));
    }
    float value = visitVal_float(ctx->val_float());
    property.value = value;

    return property;
}

antlrcpp::Any ShaderLabGenerator::visitProperty_range(ShaderLabParser::Property_rangeContext* ctx)
{
    Property property;
    std::string name = visitProperty_identifier(ctx->property_identifier());
    property.name = std::move(name);
    std::string displayName = visitDisplay_name(ctx->display_name());
    property.displayName = std::move(displayName);
    for (auto metaContext : ctx->meta())
    {
        std::string meta = visitMeta(metaContext);
        property.metas.emplace_back(std::move(meta));
    }
    std::pair<float, float> range = visitRange(ctx->range());
    property.range = range;
    float value = visitVal_float(ctx->val_float());
    property.value = value;

    return property;
}

antlrcpp::Any ShaderLabGenerator::visitProperty_color(ShaderLabParser::Property_colorContext* ctx)
{
    Property property;
    std::string name = visitProperty_identifier(ctx->property_identifier());
    property.name = std::move(name);
    std::string displayName = visitDisplay_name(ctx->display_name());
    property.displayName = std::move(displayName);
    for (auto metaContext : ctx->meta())
    {
        std::string meta = visitMeta(metaContext);
        property.metas.emplace_back(std::move(meta));
    }
    Vec4 color = visitVal_vec4(ctx->val_vec4());
    property.value = color;

    return property;
}

antlrcpp::Any ShaderLabGenerator::visitProperty_vector(ShaderLabParser::Property_vectorContext* ctx)
{
    Property property;
    std::string name = visitProperty_identifier(ctx->property_identifier());
    property.name = std::move(name);
    std::string displayName = visitDisplay_name(ctx->display_name());
    property.displayName = std::move(displayName);
    for (auto metaContext : ctx->meta())
    {
        std::string meta = visitMeta(metaContext);
        property.metas.emplace_back(std::move(meta));
    }
    Vec4 vector = visitVal_vec4(ctx->val_vec4());
    property.value = vector;

    return property;
}

antlrcpp::Any ShaderLabGenerator::visitProperty_2d(ShaderLabParser::Property_2dContext* ctx)
{
    Property property;
    std::string name = visitProperty_identifier(ctx->property_identifier());
    property.name = std::move(name);
    std::string displayName = visitDisplay_name(ctx->display_name());
    property.displayName = std::move(displayName);
    for (auto metaContext : ctx->meta())
    {
        std::string meta = visitMeta(metaContext);
        property.metas.emplace_back(std::move(meta));
    }
    std::string val = visitTexture_name(ctx->texture_name());
    property.value = std::move(val);

    return property;
}

antlrcpp::Any ShaderLabGenerator::visitProperty_cube(ShaderLabParser::Property_cubeContext* ctx)
{
    Property property;
    std::string name = visitProperty_identifier(ctx->property_identifier());
    property.name = std::move(name);
    std::string displayName = visitDisplay_name(ctx->display_name());
    property.displayName = std::move(displayName);
    for (auto metaContext : ctx->meta())
    {
        std::string meta = visitMeta(metaContext);
        property.metas.emplace_back(std::move(meta));
    }
    std::string val = visitTexture_name(ctx->texture_name());
    property.value = std::move(val);

    return property;
}

antlrcpp::Any ShaderLabGenerator::visitProperty_3d(ShaderLabParser::Property_3dContext* ctx)
{
    Property property;
    std::string name = visitProperty_identifier(ctx->property_identifier());
    property.name = std::move(name);
    std::string displayName = visitDisplay_name(ctx->display_name());
    property.displayName = std::move(displayName);
    for (auto metaContext : ctx->meta())
    {
        std::string meta = visitMeta(metaContext);
        property.metas.emplace_back(std::move(meta));
    }
    std::string val = visitTexture_name(ctx->texture_name());
    property.value = std::move(val);

    return property;
}

antlrcpp::Any ShaderLabGenerator::visitCategory(ShaderLabParser::CategoryContext* ctx)
{
    Category category;
    if (ctx->tags())
    {
        std::unordered_map<std::string, std::string> tags = std::move(visitTags(ctx->tags()));
        category.tags = std::move(tags);
    }
    for (auto kernelContext : ctx->kernel())
        category.kernels.emplace_back(std::move(visitKernel(kernelContext)));

    return category;
}

antlrcpp::Any ShaderLabGenerator::visitKernel(ShaderLabParser::KernelContext* ctx)
{
    Kernel kernel;
    if (ctx->tags())
    {
        std::unordered_map<std::string, std::string> tags = std::move(visitTags(ctx->tags()));
        kernel.tags = std::move(tags);
    }
    for (auto stateContext : ctx->common_state())
    {
        std::pair<EStateType, std::uint8_t> state = visitCommon_state(stateContext);
        switch (state.first)
        {
        case EStateType::CullMode:
            kernel.commonState.cullMode = ECullMode(state.second);
            break;
        case EStateType::ZTest:
            kernel.commonState.zTestMode = EComparator(state.second);
            break;
        case EStateType::ZWriteMode:
            kernel.commonState.zWriteMode = EZWriteMode(state.second);
            break;
        case EStateType::ColorMask:
            kernel.commonState.colorMaskChannel = EChannel(state.second);
        default:
            break;
        }
    }
    std::string hlsl = visitHlsl_block(ctx->hlsl_block());
    kernel.hlsl = std::move(hlsl);

    return kernel;
}

antlrcpp::Any ShaderLabGenerator::visitHlsl_block(ShaderLabParser::Hlsl_blockContext* ctx)
{
    std::string hlsl;
    hlsl = ExtractHLSL(ctx->HLSL()->getText());

    return hlsl;
}

antlrcpp::Any ShaderLabGenerator::visitTags(ShaderLabParser::TagsContext* ctx)
{
    std::unordered_map<std::string, std::string> tags;
    for (auto tagContext : ctx->tag())
    {
        std::string key = visitTag_key(tagContext->tag_key());
        std::string val = visitTag_val(tagContext->tag_val());
        tags.insert({ key, val });
    }

    return tags;
}

antlrcpp::Any Lumen::Game::ShaderLabGenerator::visitCull(ShaderLabParser::CullContext* ctx)
{
    std::pair<EStateType, std::uint8_t> state;
    state.first = EStateType::CullMode;
    std::string content = ctx->CullMode()->getText();
    if (content == "Front")            state.second = 0;
    else if (content == "Back")        state.second = 1;
    else if (content == "None")        state.second = 2;

    return state;
}

antlrcpp::Any Lumen::Game::ShaderLabGenerator::visitZtest(ShaderLabParser::ZtestContext* ctx)
{
    std::pair<EStateType, std::uint8_t> state;
    state.first = EStateType::ZTest;
    std::string content = ctx->Comparator()->getText();
    if (content == "Less")             state.second = 0;
    else if (content == "Greater")     state.second = 1;
    else if (content == "LEqual")      state.second = 2;
    else if (content == "GEqual")      state.second = 3;
    else if (content == "NotEqual")    state.second = 4;
    else if (content == "Always")      state.second = 5;
    else if (content == "Never")       state.second = 6;

    return state;
}

antlrcpp::Any Lumen::Game::ShaderLabGenerator::visitZwrite(ShaderLabParser::ZwriteContext* ctx)
{
    std::pair<EStateType, std::uint8_t> state;
    state.first = EStateType::ZWriteMode;
    std::string content;
    content = ExtractString(ctx->ZWriteMode()->getText());
    if (content == "On")               state.second = 0;
    else if (content == "Off")         state.second = 1;
    

    return state;
}

antlrcpp::Any Lumen::Game::ShaderLabGenerator::visitColor_mask(ShaderLabParser::Color_maskContext* ctx)
{
    std::pair<EStateType, std::uint8_t> state;
    state.first = EStateType::ColorMask;
    std::string content = visitChannel(ctx->channel());
    if (content.find('R') != std::string::npos)
        state.second |= 1;
    if (content.find('G') != std::string::npos)
        state.second |= 2;
    if (content.find('B') != std::string::npos)
        state.second |= 4;
    if (content.find('A') != std::string::npos)
        state.second |= 8;

    return state;
}

antlrcpp::Any Lumen::Game::ShaderLabGenerator::visitMeta(ShaderLabParser::MetaContext* ctx)
{
    std::string meta;
    meta = ExtractString(ctx->MetaInfo()->getText());

    return meta;
}

antlrcpp::Any ShaderLabGenerator::visitRange(ShaderLabParser::RangeContext* ctx)
{
    float min = visitVal_min(ctx->val_min()), max = visitVal_max(ctx->val_max());
    std::pair<float, float> range = std::make_pair(min, max);

    return range;
}

antlrcpp::Any Lumen::Game::ShaderLabGenerator::visitTag_key(ShaderLabParser::Tag_keyContext* ctx)
{
    std::string key;
    key = ExtractString(ctx->String()->getText());

    return key;
}

antlrcpp::Any Lumen::Game::ShaderLabGenerator::visitTag_val(ShaderLabParser::Tag_valContext* ctx)
{
    std::string val;
    val = ExtractString(ctx->String()->getText());

    return val;
}

antlrcpp::Any ShaderLabGenerator::visitShader_name(ShaderLabParser::Shader_nameContext* ctx)
{
    std::string name;
    name = ExtractString(ctx->String()->getText());

    return name;
}

antlrcpp::Any Lumen::Game::ShaderLabGenerator::visitDisplay_name(ShaderLabParser::Display_nameContext* ctx)
{
    std::string name;
    name = ExtractString(ctx->String()->getText());

    return name;
}

antlrcpp::Any Lumen::Game::ShaderLabGenerator::visitTexture_name(ShaderLabParser::Texture_nameContext* ctx)
{
    std::string name;
    name = ExtractString(ctx->String()->getText());

    return name;
}

antlrcpp::Any Lumen::Game::ShaderLabGenerator::visitProperty_identifier(ShaderLabParser::Property_identifierContext* ctx)
{
    std::string identifier = ctx->Identifier()->getText();

    return identifier;
}

antlrcpp::Any Lumen::Game::ShaderLabGenerator::visitVal_int(ShaderLabParser::Val_intContext* ctx)
{
    int val = std::stoi(ctx->IntegerLiteral()->getText());
    if (ctx->Sign() && ctx->Sign()->getText() == "-")
        val = -val;

    return val;
}

antlrcpp::Any Lumen::Game::ShaderLabGenerator::visitVal_float(ShaderLabParser::Val_floatContext* ctx)
{
    float val = std::stof(ctx->FloatingLiteral()->getText());
    if (ctx->Sign() && ctx->Sign()->getText() == "-")
        val = -val;

    return val;
}

antlrcpp::Any Lumen::Game::ShaderLabGenerator::visitVal_min(ShaderLabParser::Val_minContext* ctx)
{
    float val = std::stof(ctx->FloatingLiteral()->getText());
    if (ctx->Sign() && ctx->Sign()->getText() == "-")
        val = -val;

    return val;
}

antlrcpp::Any Lumen::Game::ShaderLabGenerator::visitVal_max(ShaderLabParser::Val_maxContext* ctx)
{
    float val = std::stof(ctx->FloatingLiteral()->getText());
    if (ctx->Sign() && ctx->Sign()->getText() == "-")
        val = -val;

    return val;
}

antlrcpp::Any Lumen::Game::ShaderLabGenerator::visitVal_vec4(ShaderLabParser::Val_vec4Context* ctx)
{
    Vec4 vec4;
    vec4.x = visitVal_float(ctx->val_float(0));
    vec4.y = visitVal_float(ctx->val_float(1));
    vec4.z = visitVal_float(ctx->val_float(2));
    vec4.w = visitVal_float(ctx->val_float(3));

    return vec4;
}

antlrcpp::Any Lumen::Game::ShaderLabGenerator::visitChannel(ShaderLabParser::ChannelContext* ctx)
{
    std::string channel;
    if (ctx->Channel())
        channel = ctx->Channel()->getText();
    else if (ctx->IntegerLiteral())
        channel = ctx->IntegerLiteral()->getText();

    return channel;
}
