// Generated from e:\Workplace\LumenEngine\Source\ThirdParty\ANTLR\ParserShaderLab\ShaderLab.g4 by ANTLR 4.8
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ShaderLabParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.8", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, T__20=21, T__21=22, T__22=23, T__23=24, 
		String=25, MetaInfo=26, HLSL=27, Identifier=28, Sign=29, IntegerLiteral=30, 
		FloatingLiteral=31, ExponentPart=32, CullMode=33, Comparator=34, ZWriteMode=35, 
		Channel=36, Whitespace=37, Newline=38, BlockComment=39, LineComment=40;
	public static final int
		RULE_shader = 0, RULE_properties = 1, RULE_property = 2, RULE_property_int = 3, 
		RULE_property_float = 4, RULE_property_range = 5, RULE_property_color = 6, 
		RULE_property_vector = 7, RULE_property_2d = 8, RULE_property_cube = 9, 
		RULE_property_3d = 10, RULE_category = 11, RULE_kernel = 12, RULE_hlsl_block = 13, 
		RULE_tags = 14, RULE_tag = 15, RULE_common_state = 16, RULE_cull = 17, 
		RULE_ztest = 18, RULE_zwrite = 19, RULE_color_mask = 20, RULE_meta = 21, 
		RULE_range = 22, RULE_tag_key = 23, RULE_tag_val = 24, RULE_shader_name = 25, 
		RULE_display_name = 26, RULE_texture_name = 27, RULE_property_identifier = 28, 
		RULE_val_int = 29, RULE_val_float = 30, RULE_val_min = 31, RULE_val_max = 32, 
		RULE_val_vec4 = 33, RULE_channel = 34;
	private static String[] makeRuleNames() {
		return new String[] {
			"shader", "properties", "property", "property_int", "property_float", 
			"property_range", "property_color", "property_vector", "property_2d", 
			"property_cube", "property_3d", "category", "kernel", "hlsl_block", "tags", 
			"tag", "common_state", "cull", "ztest", "zwrite", "color_mask", "meta", 
			"range", "tag_key", "tag_val", "shader_name", "display_name", "texture_name", 
			"property_identifier", "val_int", "val_float", "val_min", "val_max", 
			"val_vec4", "channel"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'Shader'", "'{'", "'}'", "'Properties'", "'('", "','", "'Int'", 
			"')'", "'='", "'Float'", "'Range'", "'Color'", "'Vector'", "'2D'", "'{}'", 
			"'Cube'", "'3D'", "'Category'", "'Kernel'", "'Tags'", "'Cull'", "'ZTest'", 
			"'ZWrite'", "'ColorMask'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, "String", "MetaInfo", "HLSL", "Identifier", "Sign", "IntegerLiteral", 
			"FloatingLiteral", "ExponentPart", "CullMode", "Comparator", "ZWriteMode", 
			"Channel", "Whitespace", "Newline", "BlockComment", "LineComment"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "ShaderLab.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public ShaderLabParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	public static class ShaderContext extends ParserRuleContext {
		public Shader_nameContext shader_name() {
			return getRuleContext(Shader_nameContext.class,0);
		}
		public CategoryContext category() {
			return getRuleContext(CategoryContext.class,0);
		}
		public PropertiesContext properties() {
			return getRuleContext(PropertiesContext.class,0);
		}
		public ShaderContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_shader; }
	}

	public final ShaderContext shader() throws RecognitionException {
		ShaderContext _localctx = new ShaderContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_shader);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(70);
			match(T__0);
			setState(71);
			shader_name();
			setState(72);
			match(T__1);
			setState(74);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__3) {
				{
				setState(73);
				properties();
				}
			}

			setState(76);
			category();
			setState(77);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PropertiesContext extends ParserRuleContext {
		public List<PropertyContext> property() {
			return getRuleContexts(PropertyContext.class);
		}
		public PropertyContext property(int i) {
			return getRuleContext(PropertyContext.class,i);
		}
		public PropertiesContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_properties; }
	}

	public final PropertiesContext properties() throws RecognitionException {
		PropertiesContext _localctx = new PropertiesContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_properties);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(79);
			match(T__3);
			setState(80);
			match(T__1);
			setState(82); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(81);
				property();
				}
				}
				setState(84); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==MetaInfo || _la==Identifier );
			setState(86);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PropertyContext extends ParserRuleContext {
		public Property_intContext property_int() {
			return getRuleContext(Property_intContext.class,0);
		}
		public Property_floatContext property_float() {
			return getRuleContext(Property_floatContext.class,0);
		}
		public Property_rangeContext property_range() {
			return getRuleContext(Property_rangeContext.class,0);
		}
		public Property_colorContext property_color() {
			return getRuleContext(Property_colorContext.class,0);
		}
		public Property_vectorContext property_vector() {
			return getRuleContext(Property_vectorContext.class,0);
		}
		public Property_2dContext property_2d() {
			return getRuleContext(Property_2dContext.class,0);
		}
		public Property_cubeContext property_cube() {
			return getRuleContext(Property_cubeContext.class,0);
		}
		public Property_3dContext property_3d() {
			return getRuleContext(Property_3dContext.class,0);
		}
		public PropertyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property; }
	}

	public final PropertyContext property() throws RecognitionException {
		PropertyContext _localctx = new PropertyContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_property);
		try {
			setState(96);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,2,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(88);
				property_int();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(89);
				property_float();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(90);
				property_range();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(91);
				property_color();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(92);
				property_vector();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(93);
				property_2d();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(94);
				property_cube();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(95);
				property_3d();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_intContext extends ParserRuleContext {
		public Property_identifierContext property_identifier() {
			return getRuleContext(Property_identifierContext.class,0);
		}
		public Display_nameContext display_name() {
			return getRuleContext(Display_nameContext.class,0);
		}
		public Val_intContext val_int() {
			return getRuleContext(Val_intContext.class,0);
		}
		public List<MetaContext> meta() {
			return getRuleContexts(MetaContext.class);
		}
		public MetaContext meta(int i) {
			return getRuleContext(MetaContext.class,i);
		}
		public Property_intContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_int; }
	}

	public final Property_intContext property_int() throws RecognitionException {
		Property_intContext _localctx = new Property_intContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_property_int);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(101);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==MetaInfo) {
				{
				{
				setState(98);
				meta();
				}
				}
				setState(103);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(104);
			property_identifier();
			setState(105);
			match(T__4);
			setState(106);
			display_name();
			setState(107);
			match(T__5);
			setState(108);
			match(T__6);
			setState(109);
			match(T__7);
			setState(110);
			match(T__8);
			setState(111);
			val_int();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_floatContext extends ParserRuleContext {
		public Property_identifierContext property_identifier() {
			return getRuleContext(Property_identifierContext.class,0);
		}
		public Display_nameContext display_name() {
			return getRuleContext(Display_nameContext.class,0);
		}
		public Val_floatContext val_float() {
			return getRuleContext(Val_floatContext.class,0);
		}
		public List<MetaContext> meta() {
			return getRuleContexts(MetaContext.class);
		}
		public MetaContext meta(int i) {
			return getRuleContext(MetaContext.class,i);
		}
		public Property_floatContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_float; }
	}

	public final Property_floatContext property_float() throws RecognitionException {
		Property_floatContext _localctx = new Property_floatContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_property_float);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(116);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==MetaInfo) {
				{
				{
				setState(113);
				meta();
				}
				}
				setState(118);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(119);
			property_identifier();
			setState(120);
			match(T__4);
			setState(121);
			display_name();
			setState(122);
			match(T__5);
			setState(123);
			match(T__9);
			setState(124);
			match(T__7);
			setState(125);
			match(T__8);
			setState(126);
			val_float();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_rangeContext extends ParserRuleContext {
		public Property_identifierContext property_identifier() {
			return getRuleContext(Property_identifierContext.class,0);
		}
		public Display_nameContext display_name() {
			return getRuleContext(Display_nameContext.class,0);
		}
		public RangeContext range() {
			return getRuleContext(RangeContext.class,0);
		}
		public Val_floatContext val_float() {
			return getRuleContext(Val_floatContext.class,0);
		}
		public List<MetaContext> meta() {
			return getRuleContexts(MetaContext.class);
		}
		public MetaContext meta(int i) {
			return getRuleContext(MetaContext.class,i);
		}
		public Property_rangeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_range; }
	}

	public final Property_rangeContext property_range() throws RecognitionException {
		Property_rangeContext _localctx = new Property_rangeContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_property_range);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(131);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==MetaInfo) {
				{
				{
				setState(128);
				meta();
				}
				}
				setState(133);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(134);
			property_identifier();
			setState(135);
			match(T__4);
			setState(136);
			display_name();
			setState(137);
			match(T__5);
			setState(138);
			match(T__10);
			setState(139);
			range();
			setState(140);
			match(T__7);
			setState(141);
			match(T__8);
			setState(142);
			val_float();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_colorContext extends ParserRuleContext {
		public Property_identifierContext property_identifier() {
			return getRuleContext(Property_identifierContext.class,0);
		}
		public Display_nameContext display_name() {
			return getRuleContext(Display_nameContext.class,0);
		}
		public Val_vec4Context val_vec4() {
			return getRuleContext(Val_vec4Context.class,0);
		}
		public List<MetaContext> meta() {
			return getRuleContexts(MetaContext.class);
		}
		public MetaContext meta(int i) {
			return getRuleContext(MetaContext.class,i);
		}
		public Property_colorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_color; }
	}

	public final Property_colorContext property_color() throws RecognitionException {
		Property_colorContext _localctx = new Property_colorContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_property_color);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(147);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==MetaInfo) {
				{
				{
				setState(144);
				meta();
				}
				}
				setState(149);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(150);
			property_identifier();
			setState(151);
			match(T__4);
			setState(152);
			display_name();
			setState(153);
			match(T__5);
			setState(154);
			match(T__11);
			setState(155);
			match(T__7);
			setState(156);
			match(T__8);
			setState(157);
			val_vec4();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_vectorContext extends ParserRuleContext {
		public Property_identifierContext property_identifier() {
			return getRuleContext(Property_identifierContext.class,0);
		}
		public Display_nameContext display_name() {
			return getRuleContext(Display_nameContext.class,0);
		}
		public Val_vec4Context val_vec4() {
			return getRuleContext(Val_vec4Context.class,0);
		}
		public List<MetaContext> meta() {
			return getRuleContexts(MetaContext.class);
		}
		public MetaContext meta(int i) {
			return getRuleContext(MetaContext.class,i);
		}
		public Property_vectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_vector; }
	}

	public final Property_vectorContext property_vector() throws RecognitionException {
		Property_vectorContext _localctx = new Property_vectorContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_property_vector);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(162);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==MetaInfo) {
				{
				{
				setState(159);
				meta();
				}
				}
				setState(164);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(165);
			property_identifier();
			setState(166);
			match(T__4);
			setState(167);
			display_name();
			setState(168);
			match(T__5);
			setState(169);
			match(T__12);
			setState(170);
			match(T__7);
			setState(171);
			match(T__8);
			setState(172);
			val_vec4();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_2dContext extends ParserRuleContext {
		public Property_identifierContext property_identifier() {
			return getRuleContext(Property_identifierContext.class,0);
		}
		public Display_nameContext display_name() {
			return getRuleContext(Display_nameContext.class,0);
		}
		public Texture_nameContext texture_name() {
			return getRuleContext(Texture_nameContext.class,0);
		}
		public List<MetaContext> meta() {
			return getRuleContexts(MetaContext.class);
		}
		public MetaContext meta(int i) {
			return getRuleContext(MetaContext.class,i);
		}
		public Property_2dContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_2d; }
	}

	public final Property_2dContext property_2d() throws RecognitionException {
		Property_2dContext _localctx = new Property_2dContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_property_2d);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(177);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==MetaInfo) {
				{
				{
				setState(174);
				meta();
				}
				}
				setState(179);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(180);
			property_identifier();
			setState(181);
			match(T__4);
			setState(182);
			display_name();
			setState(183);
			match(T__5);
			setState(184);
			match(T__13);
			setState(185);
			match(T__7);
			setState(186);
			match(T__8);
			setState(187);
			texture_name();
			setState(188);
			match(T__14);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_cubeContext extends ParserRuleContext {
		public Property_identifierContext property_identifier() {
			return getRuleContext(Property_identifierContext.class,0);
		}
		public Display_nameContext display_name() {
			return getRuleContext(Display_nameContext.class,0);
		}
		public Texture_nameContext texture_name() {
			return getRuleContext(Texture_nameContext.class,0);
		}
		public List<MetaContext> meta() {
			return getRuleContexts(MetaContext.class);
		}
		public MetaContext meta(int i) {
			return getRuleContext(MetaContext.class,i);
		}
		public Property_cubeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_cube; }
	}

	public final Property_cubeContext property_cube() throws RecognitionException {
		Property_cubeContext _localctx = new Property_cubeContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_property_cube);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(193);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==MetaInfo) {
				{
				{
				setState(190);
				meta();
				}
				}
				setState(195);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(196);
			property_identifier();
			setState(197);
			match(T__4);
			setState(198);
			display_name();
			setState(199);
			match(T__5);
			setState(200);
			match(T__15);
			setState(201);
			match(T__7);
			setState(202);
			match(T__8);
			setState(203);
			texture_name();
			setState(204);
			match(T__14);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_3dContext extends ParserRuleContext {
		public Property_identifierContext property_identifier() {
			return getRuleContext(Property_identifierContext.class,0);
		}
		public Display_nameContext display_name() {
			return getRuleContext(Display_nameContext.class,0);
		}
		public Texture_nameContext texture_name() {
			return getRuleContext(Texture_nameContext.class,0);
		}
		public List<MetaContext> meta() {
			return getRuleContexts(MetaContext.class);
		}
		public MetaContext meta(int i) {
			return getRuleContext(MetaContext.class,i);
		}
		public Property_3dContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_3d; }
	}

	public final Property_3dContext property_3d() throws RecognitionException {
		Property_3dContext _localctx = new Property_3dContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_property_3d);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(209);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==MetaInfo) {
				{
				{
				setState(206);
				meta();
				}
				}
				setState(211);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(212);
			property_identifier();
			setState(213);
			match(T__4);
			setState(214);
			display_name();
			setState(215);
			match(T__5);
			setState(216);
			match(T__16);
			setState(217);
			match(T__7);
			setState(218);
			match(T__8);
			setState(219);
			texture_name();
			setState(220);
			match(T__14);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CategoryContext extends ParserRuleContext {
		public TagsContext tags() {
			return getRuleContext(TagsContext.class,0);
		}
		public List<KernelContext> kernel() {
			return getRuleContexts(KernelContext.class);
		}
		public KernelContext kernel(int i) {
			return getRuleContext(KernelContext.class,i);
		}
		public CategoryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_category; }
	}

	public final CategoryContext category() throws RecognitionException {
		CategoryContext _localctx = new CategoryContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_category);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(222);
			match(T__17);
			setState(223);
			match(T__1);
			setState(225);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__19) {
				{
				setState(224);
				tags();
				}
			}

			setState(228); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(227);
				kernel();
				}
				}
				setState(230); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==T__18 );
			setState(232);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class KernelContext extends ParserRuleContext {
		public TagsContext tags() {
			return getRuleContext(TagsContext.class,0);
		}
		public Hlsl_blockContext hlsl_block() {
			return getRuleContext(Hlsl_blockContext.class,0);
		}
		public List<Common_stateContext> common_state() {
			return getRuleContexts(Common_stateContext.class);
		}
		public Common_stateContext common_state(int i) {
			return getRuleContext(Common_stateContext.class,i);
		}
		public KernelContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_kernel; }
	}

	public final KernelContext kernel() throws RecognitionException {
		KernelContext _localctx = new KernelContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_kernel);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(234);
			match(T__18);
			setState(235);
			match(T__1);
			setState(236);
			tags();
			setState(240);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__20) | (1L << T__21) | (1L << T__22) | (1L << T__23))) != 0)) {
				{
				{
				setState(237);
				common_state();
				}
				}
				setState(242);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(243);
			hlsl_block();
			setState(244);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Hlsl_blockContext extends ParserRuleContext {
		public TerminalNode HLSL() { return getToken(ShaderLabParser.HLSL, 0); }
		public Hlsl_blockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_hlsl_block; }
	}

	public final Hlsl_blockContext hlsl_block() throws RecognitionException {
		Hlsl_blockContext _localctx = new Hlsl_blockContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_hlsl_block);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(246);
			match(HLSL);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TagsContext extends ParserRuleContext {
		public List<TagContext> tag() {
			return getRuleContexts(TagContext.class);
		}
		public TagContext tag(int i) {
			return getRuleContext(TagContext.class,i);
		}
		public TagsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tags; }
	}

	public final TagsContext tags() throws RecognitionException {
		TagsContext _localctx = new TagsContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_tags);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(248);
			match(T__19);
			setState(249);
			match(T__1);
			setState(251); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(250);
				tag();
				}
				}
				setState(253); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==String );
			setState(255);
			match(T__2);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TagContext extends ParserRuleContext {
		public Tag_keyContext tag_key() {
			return getRuleContext(Tag_keyContext.class,0);
		}
		public Tag_valContext tag_val() {
			return getRuleContext(Tag_valContext.class,0);
		}
		public TagContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tag; }
	}

	public final TagContext tag() throws RecognitionException {
		TagContext _localctx = new TagContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_tag);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(257);
			tag_key();
			setState(258);
			match(T__8);
			setState(259);
			tag_val();
			setState(261);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==T__5) {
				{
				setState(260);
				match(T__5);
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Common_stateContext extends ParserRuleContext {
		public CullContext cull() {
			return getRuleContext(CullContext.class,0);
		}
		public ZtestContext ztest() {
			return getRuleContext(ZtestContext.class,0);
		}
		public ZwriteContext zwrite() {
			return getRuleContext(ZwriteContext.class,0);
		}
		public Color_maskContext color_mask() {
			return getRuleContext(Color_maskContext.class,0);
		}
		public Common_stateContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_common_state; }
	}

	public final Common_stateContext common_state() throws RecognitionException {
		Common_stateContext _localctx = new Common_stateContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_common_state);
		try {
			setState(267);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case T__20:
				enterOuterAlt(_localctx, 1);
				{
				setState(263);
				cull();
				}
				break;
			case T__21:
				enterOuterAlt(_localctx, 2);
				{
				setState(264);
				ztest();
				}
				break;
			case T__22:
				enterOuterAlt(_localctx, 3);
				{
				setState(265);
				zwrite();
				}
				break;
			case T__23:
				enterOuterAlt(_localctx, 4);
				{
				setState(266);
				color_mask();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CullContext extends ParserRuleContext {
		public TerminalNode CullMode() { return getToken(ShaderLabParser.CullMode, 0); }
		public CullContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_cull; }
	}

	public final CullContext cull() throws RecognitionException {
		CullContext _localctx = new CullContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_cull);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(269);
			match(T__20);
			setState(270);
			match(CullMode);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ZtestContext extends ParserRuleContext {
		public TerminalNode Comparator() { return getToken(ShaderLabParser.Comparator, 0); }
		public ZtestContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ztest; }
	}

	public final ZtestContext ztest() throws RecognitionException {
		ZtestContext _localctx = new ZtestContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_ztest);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(272);
			match(T__21);
			setState(273);
			match(Comparator);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ZwriteContext extends ParserRuleContext {
		public TerminalNode ZWriteMode() { return getToken(ShaderLabParser.ZWriteMode, 0); }
		public ZwriteContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_zwrite; }
	}

	public final ZwriteContext zwrite() throws RecognitionException {
		ZwriteContext _localctx = new ZwriteContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_zwrite);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(275);
			match(T__22);
			setState(276);
			match(ZWriteMode);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Color_maskContext extends ParserRuleContext {
		public ChannelContext channel() {
			return getRuleContext(ChannelContext.class,0);
		}
		public Color_maskContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_color_mask; }
	}

	public final Color_maskContext color_mask() throws RecognitionException {
		Color_maskContext _localctx = new Color_maskContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_color_mask);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(278);
			match(T__23);
			setState(279);
			channel();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class MetaContext extends ParserRuleContext {
		public TerminalNode MetaInfo() { return getToken(ShaderLabParser.MetaInfo, 0); }
		public MetaContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_meta; }
	}

	public final MetaContext meta() throws RecognitionException {
		MetaContext _localctx = new MetaContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_meta);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(281);
			match(MetaInfo);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class RangeContext extends ParserRuleContext {
		public Val_minContext val_min() {
			return getRuleContext(Val_minContext.class,0);
		}
		public Val_maxContext val_max() {
			return getRuleContext(Val_maxContext.class,0);
		}
		public RangeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_range; }
	}

	public final RangeContext range() throws RecognitionException {
		RangeContext _localctx = new RangeContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_range);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(283);
			match(T__4);
			setState(284);
			val_min();
			setState(285);
			match(T__5);
			setState(286);
			val_max();
			setState(287);
			match(T__7);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tag_keyContext extends ParserRuleContext {
		public TerminalNode String() { return getToken(ShaderLabParser.String, 0); }
		public Tag_keyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tag_key; }
	}

	public final Tag_keyContext tag_key() throws RecognitionException {
		Tag_keyContext _localctx = new Tag_keyContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_tag_key);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(289);
			match(String);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Tag_valContext extends ParserRuleContext {
		public TerminalNode String() { return getToken(ShaderLabParser.String, 0); }
		public Tag_valContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tag_val; }
	}

	public final Tag_valContext tag_val() throws RecognitionException {
		Tag_valContext _localctx = new Tag_valContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_tag_val);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(291);
			match(String);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Shader_nameContext extends ParserRuleContext {
		public TerminalNode String() { return getToken(ShaderLabParser.String, 0); }
		public Shader_nameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_shader_name; }
	}

	public final Shader_nameContext shader_name() throws RecognitionException {
		Shader_nameContext _localctx = new Shader_nameContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_shader_name);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(293);
			match(String);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Display_nameContext extends ParserRuleContext {
		public TerminalNode String() { return getToken(ShaderLabParser.String, 0); }
		public Display_nameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_display_name; }
	}

	public final Display_nameContext display_name() throws RecognitionException {
		Display_nameContext _localctx = new Display_nameContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_display_name);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(295);
			match(String);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Texture_nameContext extends ParserRuleContext {
		public TerminalNode String() { return getToken(ShaderLabParser.String, 0); }
		public Texture_nameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_texture_name; }
	}

	public final Texture_nameContext texture_name() throws RecognitionException {
		Texture_nameContext _localctx = new Texture_nameContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_texture_name);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(297);
			match(String);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Property_identifierContext extends ParserRuleContext {
		public TerminalNode Identifier() { return getToken(ShaderLabParser.Identifier, 0); }
		public Property_identifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_property_identifier; }
	}

	public final Property_identifierContext property_identifier() throws RecognitionException {
		Property_identifierContext _localctx = new Property_identifierContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_property_identifier);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(299);
			match(Identifier);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Val_intContext extends ParserRuleContext {
		public TerminalNode IntegerLiteral() { return getToken(ShaderLabParser.IntegerLiteral, 0); }
		public TerminalNode Sign() { return getToken(ShaderLabParser.Sign, 0); }
		public Val_intContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_val_int; }
	}

	public final Val_intContext val_int() throws RecognitionException {
		Val_intContext _localctx = new Val_intContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_val_int);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(302);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Sign) {
				{
				setState(301);
				match(Sign);
				}
			}

			setState(304);
			match(IntegerLiteral);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Val_floatContext extends ParserRuleContext {
		public TerminalNode FloatingLiteral() { return getToken(ShaderLabParser.FloatingLiteral, 0); }
		public TerminalNode Sign() { return getToken(ShaderLabParser.Sign, 0); }
		public Val_floatContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_val_float; }
	}

	public final Val_floatContext val_float() throws RecognitionException {
		Val_floatContext _localctx = new Val_floatContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_val_float);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(307);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Sign) {
				{
				setState(306);
				match(Sign);
				}
			}

			setState(309);
			match(FloatingLiteral);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Val_minContext extends ParserRuleContext {
		public TerminalNode FloatingLiteral() { return getToken(ShaderLabParser.FloatingLiteral, 0); }
		public TerminalNode Sign() { return getToken(ShaderLabParser.Sign, 0); }
		public Val_minContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_val_min; }
	}

	public final Val_minContext val_min() throws RecognitionException {
		Val_minContext _localctx = new Val_minContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_val_min);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(312);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Sign) {
				{
				setState(311);
				match(Sign);
				}
			}

			setState(314);
			match(FloatingLiteral);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Val_maxContext extends ParserRuleContext {
		public TerminalNode FloatingLiteral() { return getToken(ShaderLabParser.FloatingLiteral, 0); }
		public TerminalNode Sign() { return getToken(ShaderLabParser.Sign, 0); }
		public Val_maxContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_val_max; }
	}

	public final Val_maxContext val_max() throws RecognitionException {
		Val_maxContext _localctx = new Val_maxContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_val_max);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(317);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==Sign) {
				{
				setState(316);
				match(Sign);
				}
			}

			setState(319);
			match(FloatingLiteral);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class Val_vec4Context extends ParserRuleContext {
		public List<Val_floatContext> val_float() {
			return getRuleContexts(Val_floatContext.class);
		}
		public Val_floatContext val_float(int i) {
			return getRuleContext(Val_floatContext.class,i);
		}
		public Val_vec4Context(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_val_vec4; }
	}

	public final Val_vec4Context val_vec4() throws RecognitionException {
		Val_vec4Context _localctx = new Val_vec4Context(_ctx, getState());
		enterRule(_localctx, 66, RULE_val_vec4);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(321);
			match(T__4);
			setState(322);
			val_float();
			setState(323);
			match(T__5);
			setState(324);
			val_float();
			setState(325);
			match(T__5);
			setState(326);
			val_float();
			setState(327);
			match(T__5);
			setState(328);
			val_float();
			setState(329);
			match(T__7);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ChannelContext extends ParserRuleContext {
		public TerminalNode Channel() { return getToken(ShaderLabParser.Channel, 0); }
		public TerminalNode IntegerLiteral() { return getToken(ShaderLabParser.IntegerLiteral, 0); }
		public ChannelContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_channel; }
	}

	public final ChannelContext channel() throws RecognitionException {
		ChannelContext _localctx = new ChannelContext(_ctx, getState());
		enterRule(_localctx, 68, RULE_channel);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(331);
			_la = _input.LA(1);
			if ( !(_la==IntegerLiteral || _la==Channel) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\3*\u0150\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\3\2\3\2\3\2\3\2\5\2M\n\2\3\2\3\2\3\2\3\3\3\3\3"+
		"\3\6\3U\n\3\r\3\16\3V\3\3\3\3\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\5\4c\n\4"+
		"\3\5\7\5f\n\5\f\5\16\5i\13\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\6\7"+
		"\6u\n\6\f\6\16\6x\13\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\7\7\7\u0084"+
		"\n\7\f\7\16\7\u0087\13\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\b\7"+
		"\b\u0094\n\b\f\b\16\b\u0097\13\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3\b\3"+
		"\t\7\t\u00a3\n\t\f\t\16\t\u00a6\13\t\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3"+
		"\t\3\n\7\n\u00b2\n\n\f\n\16\n\u00b5\13\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3"+
		"\n\3\n\3\n\3\13\7\13\u00c2\n\13\f\13\16\13\u00c5\13\13\3\13\3\13\3\13"+
		"\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\f\7\f\u00d2\n\f\f\f\16\f\u00d5\13"+
		"\f\3\f\3\f\3\f\3\f\3\f\3\f\3\f\3\f\3\f\3\f\3\r\3\r\3\r\5\r\u00e4\n\r\3"+
		"\r\6\r\u00e7\n\r\r\r\16\r\u00e8\3\r\3\r\3\16\3\16\3\16\3\16\7\16\u00f1"+
		"\n\16\f\16\16\16\u00f4\13\16\3\16\3\16\3\16\3\17\3\17\3\20\3\20\3\20\6"+
		"\20\u00fe\n\20\r\20\16\20\u00ff\3\20\3\20\3\21\3\21\3\21\3\21\5\21\u0108"+
		"\n\21\3\22\3\22\3\22\3\22\5\22\u010e\n\22\3\23\3\23\3\23\3\24\3\24\3\24"+
		"\3\25\3\25\3\25\3\26\3\26\3\26\3\27\3\27\3\30\3\30\3\30\3\30\3\30\3\30"+
		"\3\31\3\31\3\32\3\32\3\33\3\33\3\34\3\34\3\35\3\35\3\36\3\36\3\37\5\37"+
		"\u0131\n\37\3\37\3\37\3 \5 \u0136\n \3 \3 \3!\5!\u013b\n!\3!\3!\3\"\5"+
		"\"\u0140\n\"\3\"\3\"\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3$\3$\3$\2\2%\2\4\6"+
		"\b\n\f\16\20\22\24\26\30\32\34\36 \"$&(*,.\60\62\64\668:<>@BDF\2\3\4\2"+
		"  &&\2\u0149\2H\3\2\2\2\4Q\3\2\2\2\6b\3\2\2\2\bg\3\2\2\2\nv\3\2\2\2\f"+
		"\u0085\3\2\2\2\16\u0095\3\2\2\2\20\u00a4\3\2\2\2\22\u00b3\3\2\2\2\24\u00c3"+
		"\3\2\2\2\26\u00d3\3\2\2\2\30\u00e0\3\2\2\2\32\u00ec\3\2\2\2\34\u00f8\3"+
		"\2\2\2\36\u00fa\3\2\2\2 \u0103\3\2\2\2\"\u010d\3\2\2\2$\u010f\3\2\2\2"+
		"&\u0112\3\2\2\2(\u0115\3\2\2\2*\u0118\3\2\2\2,\u011b\3\2\2\2.\u011d\3"+
		"\2\2\2\60\u0123\3\2\2\2\62\u0125\3\2\2\2\64\u0127\3\2\2\2\66\u0129\3\2"+
		"\2\28\u012b\3\2\2\2:\u012d\3\2\2\2<\u0130\3\2\2\2>\u0135\3\2\2\2@\u013a"+
		"\3\2\2\2B\u013f\3\2\2\2D\u0143\3\2\2\2F\u014d\3\2\2\2HI\7\3\2\2IJ\5\64"+
		"\33\2JL\7\4\2\2KM\5\4\3\2LK\3\2\2\2LM\3\2\2\2MN\3\2\2\2NO\5\30\r\2OP\7"+
		"\5\2\2P\3\3\2\2\2QR\7\6\2\2RT\7\4\2\2SU\5\6\4\2TS\3\2\2\2UV\3\2\2\2VT"+
		"\3\2\2\2VW\3\2\2\2WX\3\2\2\2XY\7\5\2\2Y\5\3\2\2\2Zc\5\b\5\2[c\5\n\6\2"+
		"\\c\5\f\7\2]c\5\16\b\2^c\5\20\t\2_c\5\22\n\2`c\5\24\13\2ac\5\26\f\2bZ"+
		"\3\2\2\2b[\3\2\2\2b\\\3\2\2\2b]\3\2\2\2b^\3\2\2\2b_\3\2\2\2b`\3\2\2\2"+
		"ba\3\2\2\2c\7\3\2\2\2df\5,\27\2ed\3\2\2\2fi\3\2\2\2ge\3\2\2\2gh\3\2\2"+
		"\2hj\3\2\2\2ig\3\2\2\2jk\5:\36\2kl\7\7\2\2lm\5\66\34\2mn\7\b\2\2no\7\t"+
		"\2\2op\7\n\2\2pq\7\13\2\2qr\5<\37\2r\t\3\2\2\2su\5,\27\2ts\3\2\2\2ux\3"+
		"\2\2\2vt\3\2\2\2vw\3\2\2\2wy\3\2\2\2xv\3\2\2\2yz\5:\36\2z{\7\7\2\2{|\5"+
		"\66\34\2|}\7\b\2\2}~\7\f\2\2~\177\7\n\2\2\177\u0080\7\13\2\2\u0080\u0081"+
		"\5> \2\u0081\13\3\2\2\2\u0082\u0084\5,\27\2\u0083\u0082\3\2\2\2\u0084"+
		"\u0087\3\2\2\2\u0085\u0083\3\2\2\2\u0085\u0086\3\2\2\2\u0086\u0088\3\2"+
		"\2\2\u0087\u0085\3\2\2\2\u0088\u0089\5:\36\2\u0089\u008a\7\7\2\2\u008a"+
		"\u008b\5\66\34\2\u008b\u008c\7\b\2\2\u008c\u008d\7\r\2\2\u008d\u008e\5"+
		".\30\2\u008e\u008f\7\n\2\2\u008f\u0090\7\13\2\2\u0090\u0091\5> \2\u0091"+
		"\r\3\2\2\2\u0092\u0094\5,\27\2\u0093\u0092\3\2\2\2\u0094\u0097\3\2\2\2"+
		"\u0095\u0093\3\2\2\2\u0095\u0096\3\2\2\2\u0096\u0098\3\2\2\2\u0097\u0095"+
		"\3\2\2\2\u0098\u0099\5:\36\2\u0099\u009a\7\7\2\2\u009a\u009b\5\66\34\2"+
		"\u009b\u009c\7\b\2\2\u009c\u009d\7\16\2\2\u009d\u009e\7\n\2\2\u009e\u009f"+
		"\7\13\2\2\u009f\u00a0\5D#\2\u00a0\17\3\2\2\2\u00a1\u00a3\5,\27\2\u00a2"+
		"\u00a1\3\2\2\2\u00a3\u00a6\3\2\2\2\u00a4\u00a2\3\2\2\2\u00a4\u00a5\3\2"+
		"\2\2\u00a5\u00a7\3\2\2\2\u00a6\u00a4\3\2\2\2\u00a7\u00a8\5:\36\2\u00a8"+
		"\u00a9\7\7\2\2\u00a9\u00aa\5\66\34\2\u00aa\u00ab\7\b\2\2\u00ab\u00ac\7"+
		"\17\2\2\u00ac\u00ad\7\n\2\2\u00ad\u00ae\7\13\2\2\u00ae\u00af\5D#\2\u00af"+
		"\21\3\2\2\2\u00b0\u00b2\5,\27\2\u00b1\u00b0\3\2\2\2\u00b2\u00b5\3\2\2"+
		"\2\u00b3\u00b1\3\2\2\2\u00b3\u00b4\3\2\2\2\u00b4\u00b6\3\2\2\2\u00b5\u00b3"+
		"\3\2\2\2\u00b6\u00b7\5:\36\2\u00b7\u00b8\7\7\2\2\u00b8\u00b9\5\66\34\2"+
		"\u00b9\u00ba\7\b\2\2\u00ba\u00bb\7\20\2\2\u00bb\u00bc\7\n\2\2\u00bc\u00bd"+
		"\7\13\2\2\u00bd\u00be\58\35\2\u00be\u00bf\7\21\2\2\u00bf\23\3\2\2\2\u00c0"+
		"\u00c2\5,\27\2\u00c1\u00c0\3\2\2\2\u00c2\u00c5\3\2\2\2\u00c3\u00c1\3\2"+
		"\2\2\u00c3\u00c4\3\2\2\2\u00c4\u00c6\3\2\2\2\u00c5\u00c3\3\2\2\2\u00c6"+
		"\u00c7\5:\36\2\u00c7\u00c8\7\7\2\2\u00c8\u00c9\5\66\34\2\u00c9\u00ca\7"+
		"\b\2\2\u00ca\u00cb\7\22\2\2\u00cb\u00cc\7\n\2\2\u00cc\u00cd\7\13\2\2\u00cd"+
		"\u00ce\58\35\2\u00ce\u00cf\7\21\2\2\u00cf\25\3\2\2\2\u00d0\u00d2\5,\27"+
		"\2\u00d1\u00d0\3\2\2\2\u00d2\u00d5\3\2\2\2\u00d3\u00d1\3\2\2\2\u00d3\u00d4"+
		"\3\2\2\2\u00d4\u00d6\3\2\2\2\u00d5\u00d3\3\2\2\2\u00d6\u00d7\5:\36\2\u00d7"+
		"\u00d8\7\7\2\2\u00d8\u00d9\5\66\34\2\u00d9\u00da\7\b\2\2\u00da\u00db\7"+
		"\23\2\2\u00db\u00dc\7\n\2\2\u00dc\u00dd\7\13\2\2\u00dd\u00de\58\35\2\u00de"+
		"\u00df\7\21\2\2\u00df\27\3\2\2\2\u00e0\u00e1\7\24\2\2\u00e1\u00e3\7\4"+
		"\2\2\u00e2\u00e4\5\36\20\2\u00e3\u00e2\3\2\2\2\u00e3\u00e4\3\2\2\2\u00e4"+
		"\u00e6\3\2\2\2\u00e5\u00e7\5\32\16\2\u00e6\u00e5\3\2\2\2\u00e7\u00e8\3"+
		"\2\2\2\u00e8\u00e6\3\2\2\2\u00e8\u00e9\3\2\2\2\u00e9\u00ea\3\2\2\2\u00ea"+
		"\u00eb\7\5\2\2\u00eb\31\3\2\2\2\u00ec\u00ed\7\25\2\2\u00ed\u00ee\7\4\2"+
		"\2\u00ee\u00f2\5\36\20\2\u00ef\u00f1\5\"\22\2\u00f0\u00ef\3\2\2\2\u00f1"+
		"\u00f4\3\2\2\2\u00f2\u00f0\3\2\2\2\u00f2\u00f3\3\2\2\2\u00f3\u00f5\3\2"+
		"\2\2\u00f4\u00f2\3\2\2\2\u00f5\u00f6\5\34\17\2\u00f6\u00f7\7\5\2\2\u00f7"+
		"\33\3\2\2\2\u00f8\u00f9\7\35\2\2\u00f9\35\3\2\2\2\u00fa\u00fb\7\26\2\2"+
		"\u00fb\u00fd\7\4\2\2\u00fc\u00fe\5 \21\2\u00fd\u00fc\3\2\2\2\u00fe\u00ff"+
		"\3\2\2\2\u00ff\u00fd\3\2\2\2\u00ff\u0100\3\2\2\2\u0100\u0101\3\2\2\2\u0101"+
		"\u0102\7\5\2\2\u0102\37\3\2\2\2\u0103\u0104\5\60\31\2\u0104\u0105\7\13"+
		"\2\2\u0105\u0107\5\62\32\2\u0106\u0108\7\b\2\2\u0107\u0106\3\2\2\2\u0107"+
		"\u0108\3\2\2\2\u0108!\3\2\2\2\u0109\u010e\5$\23\2\u010a\u010e\5&\24\2"+
		"\u010b\u010e\5(\25\2\u010c\u010e\5*\26\2\u010d\u0109\3\2\2\2\u010d\u010a"+
		"\3\2\2\2\u010d\u010b\3\2\2\2\u010d\u010c\3\2\2\2\u010e#\3\2\2\2\u010f"+
		"\u0110\7\27\2\2\u0110\u0111\7#\2\2\u0111%\3\2\2\2\u0112\u0113\7\30\2\2"+
		"\u0113\u0114\7$\2\2\u0114\'\3\2\2\2\u0115\u0116\7\31\2\2\u0116\u0117\7"+
		"%\2\2\u0117)\3\2\2\2\u0118\u0119\7\32\2\2\u0119\u011a\5F$\2\u011a+\3\2"+
		"\2\2\u011b\u011c\7\34\2\2\u011c-\3\2\2\2\u011d\u011e\7\7\2\2\u011e\u011f"+
		"\5@!\2\u011f\u0120\7\b\2\2\u0120\u0121\5B\"\2\u0121\u0122\7\n\2\2\u0122"+
		"/\3\2\2\2\u0123\u0124\7\33\2\2\u0124\61\3\2\2\2\u0125\u0126\7\33\2\2\u0126"+
		"\63\3\2\2\2\u0127\u0128\7\33\2\2\u0128\65\3\2\2\2\u0129\u012a\7\33\2\2"+
		"\u012a\67\3\2\2\2\u012b\u012c\7\33\2\2\u012c9\3\2\2\2\u012d\u012e\7\36"+
		"\2\2\u012e;\3\2\2\2\u012f\u0131\7\37\2\2\u0130\u012f\3\2\2\2\u0130\u0131"+
		"\3\2\2\2\u0131\u0132\3\2\2\2\u0132\u0133\7 \2\2\u0133=\3\2\2\2\u0134\u0136"+
		"\7\37\2\2\u0135\u0134\3\2\2\2\u0135\u0136\3\2\2\2\u0136\u0137\3\2\2\2"+
		"\u0137\u0138\7!\2\2\u0138?\3\2\2\2\u0139\u013b\7\37\2\2\u013a\u0139\3"+
		"\2\2\2\u013a\u013b\3\2\2\2\u013b\u013c\3\2\2\2\u013c\u013d\7!\2\2\u013d"+
		"A\3\2\2\2\u013e\u0140\7\37\2\2\u013f\u013e\3\2\2\2\u013f\u0140\3\2\2\2"+
		"\u0140\u0141\3\2\2\2\u0141\u0142\7!\2\2\u0142C\3\2\2\2\u0143\u0144\7\7"+
		"\2\2\u0144\u0145\5> \2\u0145\u0146\7\b\2\2\u0146\u0147\5> \2\u0147\u0148"+
		"\7\b\2\2\u0148\u0149\5> \2\u0149\u014a\7\b\2\2\u014a\u014b\5> \2\u014b"+
		"\u014c\7\n\2\2\u014cE\3\2\2\2\u014d\u014e\t\2\2\2\u014eG\3\2\2\2\27LV"+
		"bgv\u0085\u0095\u00a4\u00b3\u00c3\u00d3\u00e3\u00e8\u00f2\u00ff\u0107"+
		"\u010d\u0130\u0135\u013a\u013f";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}