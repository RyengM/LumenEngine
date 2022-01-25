
// Generated from CPP14Parser.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "CPP14Parser.h"


namespace Ubpa {

/**
 * This class defines an abstract visitor for a parse tree
 * produced by CPP14Parser.
 */
class  CPP14ParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CPP14Parser.
   */
    virtual antlrcpp::Any visitTranslationUnit(CPP14Parser::TranslationUnitContext *context) = 0;

    virtual antlrcpp::Any visitPrimaryExpression(CPP14Parser::PrimaryExpressionContext *context) = 0;

    virtual antlrcpp::Any visitIdExpression(CPP14Parser::IdExpressionContext *context) = 0;

    virtual antlrcpp::Any visitUnqualifiedId(CPP14Parser::UnqualifiedIdContext *context) = 0;

    virtual antlrcpp::Any visitQualifiedId(CPP14Parser::QualifiedIdContext *context) = 0;

    virtual antlrcpp::Any visitNestedNameSpecifier(CPP14Parser::NestedNameSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitLambdaExpression(CPP14Parser::LambdaExpressionContext *context) = 0;

    virtual antlrcpp::Any visitLambdaIntroducer(CPP14Parser::LambdaIntroducerContext *context) = 0;

    virtual antlrcpp::Any visitLambdaCapture(CPP14Parser::LambdaCaptureContext *context) = 0;

    virtual antlrcpp::Any visitCaptureDefault(CPP14Parser::CaptureDefaultContext *context) = 0;

    virtual antlrcpp::Any visitCaptureList(CPP14Parser::CaptureListContext *context) = 0;

    virtual antlrcpp::Any visitCapture(CPP14Parser::CaptureContext *context) = 0;

    virtual antlrcpp::Any visitSimpleCapture(CPP14Parser::SimpleCaptureContext *context) = 0;

    virtual antlrcpp::Any visitInitcapture(CPP14Parser::InitcaptureContext *context) = 0;

    virtual antlrcpp::Any visitLambdaDeclarator(CPP14Parser::LambdaDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitPostfixExpression(CPP14Parser::PostfixExpressionContext *context) = 0;

    virtual antlrcpp::Any visitTypeIdOfTheTypeId(CPP14Parser::TypeIdOfTheTypeIdContext *context) = 0;

    virtual antlrcpp::Any visitExpressionList(CPP14Parser::ExpressionListContext *context) = 0;

    virtual antlrcpp::Any visitPseudoDestructorName(CPP14Parser::PseudoDestructorNameContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExpression(CPP14Parser::UnaryExpressionContext *context) = 0;

    virtual antlrcpp::Any visitUnaryOperator(CPP14Parser::UnaryOperatorContext *context) = 0;

    virtual antlrcpp::Any visitNewExpression(CPP14Parser::NewExpressionContext *context) = 0;

    virtual antlrcpp::Any visitNewPlacement(CPP14Parser::NewPlacementContext *context) = 0;

    virtual antlrcpp::Any visitNewTypeId(CPP14Parser::NewTypeIdContext *context) = 0;

    virtual antlrcpp::Any visitNewDeclarator(CPP14Parser::NewDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitNoPointerNewDeclarator(CPP14Parser::NoPointerNewDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitNewInitializer(CPP14Parser::NewInitializerContext *context) = 0;

    virtual antlrcpp::Any visitDeleteExpression(CPP14Parser::DeleteExpressionContext *context) = 0;

    virtual antlrcpp::Any visitNoExceptExpression(CPP14Parser::NoExceptExpressionContext *context) = 0;

    virtual antlrcpp::Any visitCastExpression(CPP14Parser::CastExpressionContext *context) = 0;

    virtual antlrcpp::Any visitPointerMemberExpression(CPP14Parser::PointerMemberExpressionContext *context) = 0;

    virtual antlrcpp::Any visitMultiplicativeExpression(CPP14Parser::MultiplicativeExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAdditiveExpression(CPP14Parser::AdditiveExpressionContext *context) = 0;

    virtual antlrcpp::Any visitShiftExpression(CPP14Parser::ShiftExpressionContext *context) = 0;

    virtual antlrcpp::Any visitShiftOperator(CPP14Parser::ShiftOperatorContext *context) = 0;

    virtual antlrcpp::Any visitRelationalExpression(CPP14Parser::RelationalExpressionContext *context) = 0;

    virtual antlrcpp::Any visitEqualityExpression(CPP14Parser::EqualityExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAndExpression(CPP14Parser::AndExpressionContext *context) = 0;

    virtual antlrcpp::Any visitExclusiveOrExpression(CPP14Parser::ExclusiveOrExpressionContext *context) = 0;

    virtual antlrcpp::Any visitInclusiveOrExpression(CPP14Parser::InclusiveOrExpressionContext *context) = 0;

    virtual antlrcpp::Any visitLogicalAndExpression(CPP14Parser::LogicalAndExpressionContext *context) = 0;

    virtual antlrcpp::Any visitLogicalOrExpression(CPP14Parser::LogicalOrExpressionContext *context) = 0;

    virtual antlrcpp::Any visitConditionalExpression(CPP14Parser::ConditionalExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAssignmentExpression(CPP14Parser::AssignmentExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAssignmentOperator(CPP14Parser::AssignmentOperatorContext *context) = 0;

    virtual antlrcpp::Any visitExpression(CPP14Parser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitConstantExpression(CPP14Parser::ConstantExpressionContext *context) = 0;

    virtual antlrcpp::Any visitStatement(CPP14Parser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitLabeledStatement(CPP14Parser::LabeledStatementContext *context) = 0;

    virtual antlrcpp::Any visitExpressionStatement(CPP14Parser::ExpressionStatementContext *context) = 0;

    virtual antlrcpp::Any visitCompoundStatement(CPP14Parser::CompoundStatementContext *context) = 0;

    virtual antlrcpp::Any visitStatementSeq(CPP14Parser::StatementSeqContext *context) = 0;

    virtual antlrcpp::Any visitSelectionStatement(CPP14Parser::SelectionStatementContext *context) = 0;

    virtual antlrcpp::Any visitCondition(CPP14Parser::ConditionContext *context) = 0;

    virtual antlrcpp::Any visitIterationStatement(CPP14Parser::IterationStatementContext *context) = 0;

    virtual antlrcpp::Any visitForInitStatement(CPP14Parser::ForInitStatementContext *context) = 0;

    virtual antlrcpp::Any visitForRangeDeclaration(CPP14Parser::ForRangeDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitForRangeInitializer(CPP14Parser::ForRangeInitializerContext *context) = 0;

    virtual antlrcpp::Any visitJumpStatement(CPP14Parser::JumpStatementContext *context) = 0;

    virtual antlrcpp::Any visitDeclarationStatement(CPP14Parser::DeclarationStatementContext *context) = 0;

    virtual antlrcpp::Any visitDeclarationseq(CPP14Parser::DeclarationseqContext *context) = 0;

    virtual antlrcpp::Any visitDeclaration(CPP14Parser::DeclarationContext *context) = 0;

    virtual antlrcpp::Any visitBlockDeclaration(CPP14Parser::BlockDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitAliasDeclaration(CPP14Parser::AliasDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitSimpleDeclaration(CPP14Parser::SimpleDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitStaticAssertDeclaration(CPP14Parser::StaticAssertDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitEmptyDeclaration(CPP14Parser::EmptyDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitAttributeDeclaration(CPP14Parser::AttributeDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitDeclSpecifier(CPP14Parser::DeclSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitDeclSpecifierSeq(CPP14Parser::DeclSpecifierSeqContext *context) = 0;

    virtual antlrcpp::Any visitStorageClassSpecifier(CPP14Parser::StorageClassSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitFunctionSpecifier(CPP14Parser::FunctionSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitTypedefName(CPP14Parser::TypedefNameContext *context) = 0;

    virtual antlrcpp::Any visitTypeSpecifier(CPP14Parser::TypeSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitTrailingTypeSpecifier(CPP14Parser::TrailingTypeSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitTypeSpecifierSeq(CPP14Parser::TypeSpecifierSeqContext *context) = 0;

    virtual antlrcpp::Any visitTrailingTypeSpecifierSeq(CPP14Parser::TrailingTypeSpecifierSeqContext *context) = 0;

    virtual antlrcpp::Any visitSimpleTypeSpecifier(CPP14Parser::SimpleTypeSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitTheTypeName(CPP14Parser::TheTypeNameContext *context) = 0;

    virtual antlrcpp::Any visitDecltypeSpecifier(CPP14Parser::DecltypeSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitElaboratedTypeSpecifier(CPP14Parser::ElaboratedTypeSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitEnumName(CPP14Parser::EnumNameContext *context) = 0;

    virtual antlrcpp::Any visitEnumSpecifier(CPP14Parser::EnumSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitEnumHead(CPP14Parser::EnumHeadContext *context) = 0;

    virtual antlrcpp::Any visitOpaqueEnumDeclaration(CPP14Parser::OpaqueEnumDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitEnumkey(CPP14Parser::EnumkeyContext *context) = 0;

    virtual antlrcpp::Any visitEnumbase(CPP14Parser::EnumbaseContext *context) = 0;

    virtual antlrcpp::Any visitEnumeratorList(CPP14Parser::EnumeratorListContext *context) = 0;

    virtual antlrcpp::Any visitEnumeratorDefinition(CPP14Parser::EnumeratorDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitEnumerator(CPP14Parser::EnumeratorContext *context) = 0;

    virtual antlrcpp::Any visitNamespaceName(CPP14Parser::NamespaceNameContext *context) = 0;

    virtual antlrcpp::Any visitOriginalNamespaceName(CPP14Parser::OriginalNamespaceNameContext *context) = 0;

    virtual antlrcpp::Any visitNamespaceDefinition(CPP14Parser::NamespaceDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitNamespaceAlias(CPP14Parser::NamespaceAliasContext *context) = 0;

    virtual antlrcpp::Any visitNamespaceAliasDefinition(CPP14Parser::NamespaceAliasDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitQualifiedNamespaceSpecifier(CPP14Parser::QualifiedNamespaceSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitUsingDeclaration(CPP14Parser::UsingDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitUsingDirective(CPP14Parser::UsingDirectiveContext *context) = 0;

    virtual antlrcpp::Any visitAsmDefinition(CPP14Parser::AsmDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitLinkageSpecification(CPP14Parser::LinkageSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitAttributeSpecifierSeq(CPP14Parser::AttributeSpecifierSeqContext *context) = 0;

    virtual antlrcpp::Any visitAttributeSpecifier(CPP14Parser::AttributeSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitAlignmentspecifier(CPP14Parser::AlignmentspecifierContext *context) = 0;

    virtual antlrcpp::Any visitAttributeList(CPP14Parser::AttributeListContext *context) = 0;

    virtual antlrcpp::Any visitAttribute(CPP14Parser::AttributeContext *context) = 0;

    virtual antlrcpp::Any visitAttributeNamespace(CPP14Parser::AttributeNamespaceContext *context) = 0;

    virtual antlrcpp::Any visitAttributeArgumentClause(CPP14Parser::AttributeArgumentClauseContext *context) = 0;

    virtual antlrcpp::Any visitBalancedTokenSeq(CPP14Parser::BalancedTokenSeqContext *context) = 0;

    virtual antlrcpp::Any visitBalancedtoken(CPP14Parser::BalancedtokenContext *context) = 0;

    virtual antlrcpp::Any visitInitDeclaratorList(CPP14Parser::InitDeclaratorListContext *context) = 0;

    virtual antlrcpp::Any visitInitDeclarator(CPP14Parser::InitDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitDeclarator(CPP14Parser::DeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitPointerDeclarator(CPP14Parser::PointerDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitNoPointerDeclarator(CPP14Parser::NoPointerDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitParametersAndQualifiers(CPP14Parser::ParametersAndQualifiersContext *context) = 0;

    virtual antlrcpp::Any visitTrailingReturnType(CPP14Parser::TrailingReturnTypeContext *context) = 0;

    virtual antlrcpp::Any visitPointerOperator(CPP14Parser::PointerOperatorContext *context) = 0;

    virtual antlrcpp::Any visitCvqualifierseq(CPP14Parser::CvqualifierseqContext *context) = 0;

    virtual antlrcpp::Any visitCvQualifier(CPP14Parser::CvQualifierContext *context) = 0;

    virtual antlrcpp::Any visitRefqualifier(CPP14Parser::RefqualifierContext *context) = 0;

    virtual antlrcpp::Any visitDeclaratorid(CPP14Parser::DeclaratoridContext *context) = 0;

    virtual antlrcpp::Any visitTheTypeId(CPP14Parser::TheTypeIdContext *context) = 0;

    virtual antlrcpp::Any visitAbstractDeclarator(CPP14Parser::AbstractDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitPointerAbstractDeclarator(CPP14Parser::PointerAbstractDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitNoPointerAbstractDeclarator(CPP14Parser::NoPointerAbstractDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitAbstractPackDeclarator(CPP14Parser::AbstractPackDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitNoPointerAbstractPackDeclarator(CPP14Parser::NoPointerAbstractPackDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitParameterDeclarationClause(CPP14Parser::ParameterDeclarationClauseContext *context) = 0;

    virtual antlrcpp::Any visitParameterDeclarationList(CPP14Parser::ParameterDeclarationListContext *context) = 0;

    virtual antlrcpp::Any visitProSimpleTypeSpecifier(CPP14Parser::ProSimpleTypeSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitNonSimpleTypeDeclSpecifier(CPP14Parser::NonSimpleTypeDeclSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitPreDeclSpecifierSeq(CPP14Parser::PreDeclSpecifierSeqContext *context) = 0;

    virtual antlrcpp::Any visitPostDeclSpecifierSeq(CPP14Parser::PostDeclSpecifierSeqContext *context) = 0;

    virtual antlrcpp::Any visitProDeclSpecifierSeq(CPP14Parser::ProDeclSpecifierSeqContext *context) = 0;

    virtual antlrcpp::Any visitParameterDeclaration(CPP14Parser::ParameterDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitFunctionDefinition(CPP14Parser::FunctionDefinitionContext *context) = 0;

    virtual antlrcpp::Any visitFunctionBody(CPP14Parser::FunctionBodyContext *context) = 0;

    virtual antlrcpp::Any visitInitializer(CPP14Parser::InitializerContext *context) = 0;

    virtual antlrcpp::Any visitBraceOrEqualInitializer(CPP14Parser::BraceOrEqualInitializerContext *context) = 0;

    virtual antlrcpp::Any visitInitializerClause(CPP14Parser::InitializerClauseContext *context) = 0;

    virtual antlrcpp::Any visitInitializerList(CPP14Parser::InitializerListContext *context) = 0;

    virtual antlrcpp::Any visitBracedInitList(CPP14Parser::BracedInitListContext *context) = 0;

    virtual antlrcpp::Any visitClassName(CPP14Parser::ClassNameContext *context) = 0;

    virtual antlrcpp::Any visitClassSpecifier(CPP14Parser::ClassSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitClassHead(CPP14Parser::ClassHeadContext *context) = 0;

    virtual antlrcpp::Any visitClassHeadName(CPP14Parser::ClassHeadNameContext *context) = 0;

    virtual antlrcpp::Any visitClassVirtSpecifier(CPP14Parser::ClassVirtSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitClassKey(CPP14Parser::ClassKeyContext *context) = 0;

    virtual antlrcpp::Any visitMemberSpecification(CPP14Parser::MemberSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitMemberDeclaration(CPP14Parser::MemberDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitMemberDeclaratorList(CPP14Parser::MemberDeclaratorListContext *context) = 0;

    virtual antlrcpp::Any visitMemberDeclarator(CPP14Parser::MemberDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitVirtualSpecifierSeq(CPP14Parser::VirtualSpecifierSeqContext *context) = 0;

    virtual antlrcpp::Any visitVirtualSpecifier(CPP14Parser::VirtualSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitPureSpecifier(CPP14Parser::PureSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitBaseClause(CPP14Parser::BaseClauseContext *context) = 0;

    virtual antlrcpp::Any visitBaseSpecifierList(CPP14Parser::BaseSpecifierListContext *context) = 0;

    virtual antlrcpp::Any visitBaseSpecifierX(CPP14Parser::BaseSpecifierXContext *context) = 0;

    virtual antlrcpp::Any visitBaseSpecifier(CPP14Parser::BaseSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitClassOrDeclType(CPP14Parser::ClassOrDeclTypeContext *context) = 0;

    virtual antlrcpp::Any visitBaseTypeSpecifier(CPP14Parser::BaseTypeSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitAccessSpecifier(CPP14Parser::AccessSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitConversionFunctionId(CPP14Parser::ConversionFunctionIdContext *context) = 0;

    virtual antlrcpp::Any visitConversionTypeId(CPP14Parser::ConversionTypeIdContext *context) = 0;

    virtual antlrcpp::Any visitConversionDeclarator(CPP14Parser::ConversionDeclaratorContext *context) = 0;

    virtual antlrcpp::Any visitConstructorInitializer(CPP14Parser::ConstructorInitializerContext *context) = 0;

    virtual antlrcpp::Any visitMemInitializerList(CPP14Parser::MemInitializerListContext *context) = 0;

    virtual antlrcpp::Any visitMemInitializer(CPP14Parser::MemInitializerContext *context) = 0;

    virtual antlrcpp::Any visitMeminitializerid(CPP14Parser::MeminitializeridContext *context) = 0;

    virtual antlrcpp::Any visitOperatorFunctionId(CPP14Parser::OperatorFunctionIdContext *context) = 0;

    virtual antlrcpp::Any visitLiteralOperatorId(CPP14Parser::LiteralOperatorIdContext *context) = 0;

    virtual antlrcpp::Any visitTemplateDeclaration(CPP14Parser::TemplateDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitTemplateparameterList(CPP14Parser::TemplateparameterListContext *context) = 0;

    virtual antlrcpp::Any visitTemplateParameter(CPP14Parser::TemplateParameterContext *context) = 0;

    virtual antlrcpp::Any visitTypeParameter(CPP14Parser::TypeParameterContext *context) = 0;

    virtual antlrcpp::Any visitSimpleTemplateId(CPP14Parser::SimpleTemplateIdContext *context) = 0;

    virtual antlrcpp::Any visitTemplateId(CPP14Parser::TemplateIdContext *context) = 0;

    virtual antlrcpp::Any visitTemplateName(CPP14Parser::TemplateNameContext *context) = 0;

    virtual antlrcpp::Any visitTemplateArgumentList(CPP14Parser::TemplateArgumentListContext *context) = 0;

    virtual antlrcpp::Any visitTemplateArgument(CPP14Parser::TemplateArgumentContext *context) = 0;

    virtual antlrcpp::Any visitTypeNameSpecifier(CPP14Parser::TypeNameSpecifierContext *context) = 0;

    virtual antlrcpp::Any visitExplicitInstantiation(CPP14Parser::ExplicitInstantiationContext *context) = 0;

    virtual antlrcpp::Any visitExplicitSpecialization(CPP14Parser::ExplicitSpecializationContext *context) = 0;

    virtual antlrcpp::Any visitTryBlock(CPP14Parser::TryBlockContext *context) = 0;

    virtual antlrcpp::Any visitFunctionTryBlock(CPP14Parser::FunctionTryBlockContext *context) = 0;

    virtual antlrcpp::Any visitHandlerSeq(CPP14Parser::HandlerSeqContext *context) = 0;

    virtual antlrcpp::Any visitHandler(CPP14Parser::HandlerContext *context) = 0;

    virtual antlrcpp::Any visitExceptionDeclaration(CPP14Parser::ExceptionDeclarationContext *context) = 0;

    virtual antlrcpp::Any visitThrowExpression(CPP14Parser::ThrowExpressionContext *context) = 0;

    virtual antlrcpp::Any visitExceptionSpecification(CPP14Parser::ExceptionSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitDynamicExceptionSpecification(CPP14Parser::DynamicExceptionSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitTypeIdList(CPP14Parser::TypeIdListContext *context) = 0;

    virtual antlrcpp::Any visitNoeExceptSpecification(CPP14Parser::NoeExceptSpecificationContext *context) = 0;

    virtual antlrcpp::Any visitTheOperator(CPP14Parser::TheOperatorContext *context) = 0;


};

}  // namespace Ubpa
