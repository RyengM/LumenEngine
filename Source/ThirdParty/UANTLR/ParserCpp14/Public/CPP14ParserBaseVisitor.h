
// Generated from CPP14Parser.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"
#include "CPP14ParserVisitor.h"


namespace Ubpa {

/**
 * This class provides an empty implementation of CPP14ParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CPP14ParserBaseVisitor : public CPP14ParserVisitor {
public:

  virtual antlrcpp::Any visitTranslationUnit(CPP14Parser::TranslationUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrimaryExpression(CPP14Parser::PrimaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIdExpression(CPP14Parser::IdExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnqualifiedId(CPP14Parser::UnqualifiedIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQualifiedId(CPP14Parser::QualifiedIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNestedNameSpecifier(CPP14Parser::NestedNameSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLambdaExpression(CPP14Parser::LambdaExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLambdaIntroducer(CPP14Parser::LambdaIntroducerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLambdaCapture(CPP14Parser::LambdaCaptureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCaptureDefault(CPP14Parser::CaptureDefaultContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCaptureList(CPP14Parser::CaptureListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCapture(CPP14Parser::CaptureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSimpleCapture(CPP14Parser::SimpleCaptureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInitcapture(CPP14Parser::InitcaptureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLambdaDeclarator(CPP14Parser::LambdaDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPostfixExpression(CPP14Parser::PostfixExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeIdOfTheTypeId(CPP14Parser::TypeIdOfTheTypeIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpressionList(CPP14Parser::ExpressionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPseudoDestructorName(CPP14Parser::PseudoDestructorNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExpression(CPP14Parser::UnaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryOperator(CPP14Parser::UnaryOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNewExpression(CPP14Parser::NewExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNewPlacement(CPP14Parser::NewPlacementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNewTypeId(CPP14Parser::NewTypeIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNewDeclarator(CPP14Parser::NewDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNoPointerNewDeclarator(CPP14Parser::NoPointerNewDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNewInitializer(CPP14Parser::NewInitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeleteExpression(CPP14Parser::DeleteExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNoExceptExpression(CPP14Parser::NoExceptExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCastExpression(CPP14Parser::CastExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPointerMemberExpression(CPP14Parser::PointerMemberExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMultiplicativeExpression(CPP14Parser::MultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAdditiveExpression(CPP14Parser::AdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitShiftExpression(CPP14Parser::ShiftExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitShiftOperator(CPP14Parser::ShiftOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRelationalExpression(CPP14Parser::RelationalExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEqualityExpression(CPP14Parser::EqualityExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAndExpression(CPP14Parser::AndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExclusiveOrExpression(CPP14Parser::ExclusiveOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInclusiveOrExpression(CPP14Parser::InclusiveOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLogicalAndExpression(CPP14Parser::LogicalAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLogicalOrExpression(CPP14Parser::LogicalOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConditionalExpression(CPP14Parser::ConditionalExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignmentExpression(CPP14Parser::AssignmentExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignmentOperator(CPP14Parser::AssignmentOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpression(CPP14Parser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstantExpression(CPP14Parser::ConstantExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement(CPP14Parser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLabeledStatement(CPP14Parser::LabeledStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpressionStatement(CPP14Parser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCompoundStatement(CPP14Parser::CompoundStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatementSeq(CPP14Parser::StatementSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSelectionStatement(CPP14Parser::SelectionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCondition(CPP14Parser::ConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIterationStatement(CPP14Parser::IterationStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitForInitStatement(CPP14Parser::ForInitStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitForRangeDeclaration(CPP14Parser::ForRangeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitForRangeInitializer(CPP14Parser::ForRangeInitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitJumpStatement(CPP14Parser::JumpStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclarationStatement(CPP14Parser::DeclarationStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclarationseq(CPP14Parser::DeclarationseqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclaration(CPP14Parser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlockDeclaration(CPP14Parser::BlockDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAliasDeclaration(CPP14Parser::AliasDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSimpleDeclaration(CPP14Parser::SimpleDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStaticAssertDeclaration(CPP14Parser::StaticAssertDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEmptyDeclaration(CPP14Parser::EmptyDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttributeDeclaration(CPP14Parser::AttributeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclSpecifier(CPP14Parser::DeclSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclSpecifierSeq(CPP14Parser::DeclSpecifierSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStorageClassSpecifier(CPP14Parser::StorageClassSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionSpecifier(CPP14Parser::FunctionSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypedefName(CPP14Parser::TypedefNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeSpecifier(CPP14Parser::TypeSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTrailingTypeSpecifier(CPP14Parser::TrailingTypeSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeSpecifierSeq(CPP14Parser::TypeSpecifierSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTrailingTypeSpecifierSeq(CPP14Parser::TrailingTypeSpecifierSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSimpleTypeSpecifier(CPP14Parser::SimpleTypeSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTheTypeName(CPP14Parser::TheTypeNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDecltypeSpecifier(CPP14Parser::DecltypeSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitElaboratedTypeSpecifier(CPP14Parser::ElaboratedTypeSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEnumName(CPP14Parser::EnumNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEnumSpecifier(CPP14Parser::EnumSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEnumHead(CPP14Parser::EnumHeadContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOpaqueEnumDeclaration(CPP14Parser::OpaqueEnumDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEnumkey(CPP14Parser::EnumkeyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEnumbase(CPP14Parser::EnumbaseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEnumeratorList(CPP14Parser::EnumeratorListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEnumeratorDefinition(CPP14Parser::EnumeratorDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEnumerator(CPP14Parser::EnumeratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNamespaceName(CPP14Parser::NamespaceNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOriginalNamespaceName(CPP14Parser::OriginalNamespaceNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNamespaceDefinition(CPP14Parser::NamespaceDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNamespaceAlias(CPP14Parser::NamespaceAliasContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNamespaceAliasDefinition(CPP14Parser::NamespaceAliasDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQualifiedNamespaceSpecifier(CPP14Parser::QualifiedNamespaceSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUsingDeclaration(CPP14Parser::UsingDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUsingDirective(CPP14Parser::UsingDirectiveContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAsmDefinition(CPP14Parser::AsmDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLinkageSpecification(CPP14Parser::LinkageSpecificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttributeSpecifierSeq(CPP14Parser::AttributeSpecifierSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttributeSpecifier(CPP14Parser::AttributeSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAlignmentspecifier(CPP14Parser::AlignmentspecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttributeList(CPP14Parser::AttributeListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttribute(CPP14Parser::AttributeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttributeNamespace(CPP14Parser::AttributeNamespaceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAttributeArgumentClause(CPP14Parser::AttributeArgumentClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBalancedTokenSeq(CPP14Parser::BalancedTokenSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBalancedtoken(CPP14Parser::BalancedtokenContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInitDeclaratorList(CPP14Parser::InitDeclaratorListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInitDeclarator(CPP14Parser::InitDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclarator(CPP14Parser::DeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPointerDeclarator(CPP14Parser::PointerDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNoPointerDeclarator(CPP14Parser::NoPointerDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParametersAndQualifiers(CPP14Parser::ParametersAndQualifiersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTrailingReturnType(CPP14Parser::TrailingReturnTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPointerOperator(CPP14Parser::PointerOperatorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCvqualifierseq(CPP14Parser::CvqualifierseqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCvQualifier(CPP14Parser::CvQualifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRefqualifier(CPP14Parser::RefqualifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeclaratorid(CPP14Parser::DeclaratoridContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTheTypeId(CPP14Parser::TheTypeIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAbstractDeclarator(CPP14Parser::AbstractDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPointerAbstractDeclarator(CPP14Parser::PointerAbstractDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNoPointerAbstractDeclarator(CPP14Parser::NoPointerAbstractDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAbstractPackDeclarator(CPP14Parser::AbstractPackDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNoPointerAbstractPackDeclarator(CPP14Parser::NoPointerAbstractPackDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameterDeclarationClause(CPP14Parser::ParameterDeclarationClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameterDeclarationList(CPP14Parser::ParameterDeclarationListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProSimpleTypeSpecifier(CPP14Parser::ProSimpleTypeSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNonSimpleTypeDeclSpecifier(CPP14Parser::NonSimpleTypeDeclSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPreDeclSpecifierSeq(CPP14Parser::PreDeclSpecifierSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPostDeclSpecifierSeq(CPP14Parser::PostDeclSpecifierSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitProDeclSpecifierSeq(CPP14Parser::ProDeclSpecifierSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParameterDeclaration(CPP14Parser::ParameterDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionDefinition(CPP14Parser::FunctionDefinitionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionBody(CPP14Parser::FunctionBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInitializer(CPP14Parser::InitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBraceOrEqualInitializer(CPP14Parser::BraceOrEqualInitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInitializerClause(CPP14Parser::InitializerClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInitializerList(CPP14Parser::InitializerListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBracedInitList(CPP14Parser::BracedInitListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassName(CPP14Parser::ClassNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassSpecifier(CPP14Parser::ClassSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassHead(CPP14Parser::ClassHeadContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassHeadName(CPP14Parser::ClassHeadNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassVirtSpecifier(CPP14Parser::ClassVirtSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassKey(CPP14Parser::ClassKeyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMemberSpecification(CPP14Parser::MemberSpecificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMemberDeclaration(CPP14Parser::MemberDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMemberDeclaratorList(CPP14Parser::MemberDeclaratorListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMemberDeclarator(CPP14Parser::MemberDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVirtualSpecifierSeq(CPP14Parser::VirtualSpecifierSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVirtualSpecifier(CPP14Parser::VirtualSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPureSpecifier(CPP14Parser::PureSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBaseClause(CPP14Parser::BaseClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBaseSpecifierList(CPP14Parser::BaseSpecifierListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBaseSpecifierX(CPP14Parser::BaseSpecifierXContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBaseSpecifier(CPP14Parser::BaseSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClassOrDeclType(CPP14Parser::ClassOrDeclTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBaseTypeSpecifier(CPP14Parser::BaseTypeSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAccessSpecifier(CPP14Parser::AccessSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConversionFunctionId(CPP14Parser::ConversionFunctionIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConversionTypeId(CPP14Parser::ConversionTypeIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConversionDeclarator(CPP14Parser::ConversionDeclaratorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstructorInitializer(CPP14Parser::ConstructorInitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMemInitializerList(CPP14Parser::MemInitializerListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMemInitializer(CPP14Parser::MemInitializerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMeminitializerid(CPP14Parser::MeminitializeridContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOperatorFunctionId(CPP14Parser::OperatorFunctionIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLiteralOperatorId(CPP14Parser::LiteralOperatorIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTemplateDeclaration(CPP14Parser::TemplateDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTemplateparameterList(CPP14Parser::TemplateparameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTemplateParameter(CPP14Parser::TemplateParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeParameter(CPP14Parser::TypeParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSimpleTemplateId(CPP14Parser::SimpleTemplateIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTemplateId(CPP14Parser::TemplateIdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTemplateName(CPP14Parser::TemplateNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTemplateArgumentList(CPP14Parser::TemplateArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTemplateArgument(CPP14Parser::TemplateArgumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeNameSpecifier(CPP14Parser::TypeNameSpecifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExplicitInstantiation(CPP14Parser::ExplicitInstantiationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExplicitSpecialization(CPP14Parser::ExplicitSpecializationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTryBlock(CPP14Parser::TryBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionTryBlock(CPP14Parser::FunctionTryBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitHandlerSeq(CPP14Parser::HandlerSeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitHandler(CPP14Parser::HandlerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExceptionDeclaration(CPP14Parser::ExceptionDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitThrowExpression(CPP14Parser::ThrowExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExceptionSpecification(CPP14Parser::ExceptionSpecificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDynamicExceptionSpecification(CPP14Parser::DynamicExceptionSpecificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTypeIdList(CPP14Parser::TypeIdListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNoeExceptSpecification(CPP14Parser::NoeExceptSpecificationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTheOperator(CPP14Parser::TheOperatorContext *ctx) override {
    return visitChildren(ctx);
  }


};

}  // namespace Ubpa
