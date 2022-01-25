// Generated from e:\Workplace\LumenEngine\Source\ThirdParty\ANTLR\ParserShaderLab\ShaderLab.g4 by ANTLR 4.8
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ShaderLabLexer extends Lexer {
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
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
			"T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "T__16", 
			"T__17", "T__18", "T__19", "T__20", "T__21", "T__22", "T__23", "String", 
			"MetaInfo", "HLSL", "Identifier", "Sign", "IntegerLiteral", "FloatingLiteral", 
			"ExponentPart", "CullMode", "Comparator", "ZWriteMode", "Channel", "Whitespace", 
			"Newline", "BlockComment", "LineComment"
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


	public ShaderLabLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "ShaderLab.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\3\u608b\ua72a\u8133\ub9ed\u417c\u3be7\u7786\u5964\2*\u01bc\b\1\4\2\t"+
		"\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\3\2\3\2\3\2\3"+
		"\2\3\2\3\2\3\2\3\3\3\3\3\4\3\4\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5"+
		"\3\5\3\6\3\6\3\7\3\7\3\b\3\b\3\b\3\b\3\t\3\t\3\n\3\n\3\13\3\13\3\13\3"+
		"\13\3\13\3\13\3\f\3\f\3\f\3\f\3\f\3\f\3\r\3\r\3\r\3\r\3\r\3\r\3\16\3\16"+
		"\3\16\3\16\3\16\3\16\3\16\3\17\3\17\3\17\3\20\3\20\3\20\3\21\3\21\3\21"+
		"\3\21\3\21\3\22\3\22\3\22\3\23\3\23\3\23\3\23\3\23\3\23\3\23\3\23\3\23"+
		"\3\24\3\24\3\24\3\24\3\24\3\24\3\24\3\25\3\25\3\25\3\25\3\25\3\26\3\26"+
		"\3\26\3\26\3\26\3\27\3\27\3\27\3\27\3\27\3\27\3\30\3\30\3\30\3\30\3\30"+
		"\3\30\3\30\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\32\3\32"+
		"\7\32\u00d0\n\32\f\32\16\32\u00d3\13\32\3\32\3\32\3\33\3\33\7\33\u00d9"+
		"\n\33\f\33\16\33\u00dc\13\33\3\33\3\33\3\34\3\34\3\34\3\34\3\34\3\34\3"+
		"\34\3\34\3\34\3\34\3\34\3\34\3\34\7\34\u00ed\n\34\f\34\16\34\u00f0\13"+
		"\34\3\34\3\34\3\34\3\34\3\34\3\34\3\34\3\34\3\35\3\35\7\35\u00fc\n\35"+
		"\f\35\16\35\u00ff\13\35\3\36\3\36\3\37\3\37\3\37\7\37\u0106\n\37\f\37"+
		"\16\37\u0109\13\37\5\37\u010b\n\37\3 \6 \u010e\n \r \16 \u010f\3 \3 \6"+
		" \u0114\n \r \16 \u0115\3 \5 \u0119\n \3 \6 \u011c\n \r \16 \u011d\3 "+
		"\5 \u0121\n \5 \u0123\n \3!\3!\5!\u0127\n!\3!\6!\u012a\n!\r!\16!\u012b"+
		"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\3\"\5\"\u013b\n\"\3#"+
		"\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#"+
		"\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#\3#"+
		"\5#\u016c\n#\3$\3$\3$\3$\3$\5$\u0173\n$\3%\3%\3%\3%\3%\3%\3%\3%\3%\3%"+
		"\3%\3%\3%\3%\3%\3%\3%\3%\3%\3%\3%\3%\3%\3%\3%\3%\3%\3%\3%\5%\u0192\n%"+
		"\3&\6&\u0195\n&\r&\16&\u0196\3&\3&\3\'\3\'\5\'\u019d\n\'\3\'\5\'\u01a0"+
		"\n\'\3\'\3\'\3(\3(\3(\3(\7(\u01a8\n(\f(\16(\u01ab\13(\3(\3(\3(\3(\3(\3"+
		")\3)\3)\3)\7)\u01b6\n)\f)\16)\u01b9\13)\3)\3)\6\u00d1\u00da\u00ee\u01a9"+
		"\2*\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\16\33\17\35"+
		"\20\37\21!\22#\23%\24\'\25)\26+\27-\30/\31\61\32\63\33\65\34\67\359\36"+
		";\37= ?!A\"C#E$G%I&K\'M(O)Q*\3\2\13\3\2aa\5\2\62;C\\c|\4\2--//\3\2\63"+
		";\3\2\62;\4\2GGgg\5\2CDIITT\4\2\13\13\"\"\4\2\f\f\17\17\2\u01e3\2\3\3"+
		"\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2"+
		"\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3"+
		"\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2"+
		"%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2\2\61"+
		"\3\2\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67\3\2\2\2\29\3\2\2\2\2;\3\2\2\2"+
		"\2=\3\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2C\3\2\2\2\2E\3\2\2\2\2G\3\2\2\2\2I"+
		"\3\2\2\2\2K\3\2\2\2\2M\3\2\2\2\2O\3\2\2\2\2Q\3\2\2\2\3S\3\2\2\2\5Z\3\2"+
		"\2\2\7\\\3\2\2\2\t^\3\2\2\2\13i\3\2\2\2\rk\3\2\2\2\17m\3\2\2\2\21q\3\2"+
		"\2\2\23s\3\2\2\2\25u\3\2\2\2\27{\3\2\2\2\31\u0081\3\2\2\2\33\u0087\3\2"+
		"\2\2\35\u008e\3\2\2\2\37\u0091\3\2\2\2!\u0094\3\2\2\2#\u0099\3\2\2\2%"+
		"\u009c\3\2\2\2\'\u00a5\3\2\2\2)\u00ac\3\2\2\2+\u00b1\3\2\2\2-\u00b6\3"+
		"\2\2\2/\u00bc\3\2\2\2\61\u00c3\3\2\2\2\63\u00cd\3\2\2\2\65\u00d6\3\2\2"+
		"\2\67\u00df\3\2\2\29\u00f9\3\2\2\2;\u0100\3\2\2\2=\u010a\3\2\2\2?\u0122"+
		"\3\2\2\2A\u0124\3\2\2\2C\u013a\3\2\2\2E\u016b\3\2\2\2G\u0172\3\2\2\2I"+
		"\u0191\3\2\2\2K\u0194\3\2\2\2M\u019f\3\2\2\2O\u01a3\3\2\2\2Q\u01b1\3\2"+
		"\2\2ST\7U\2\2TU\7j\2\2UV\7c\2\2VW\7f\2\2WX\7g\2\2XY\7t\2\2Y\4\3\2\2\2"+
		"Z[\7}\2\2[\6\3\2\2\2\\]\7\177\2\2]\b\3\2\2\2^_\7R\2\2_`\7t\2\2`a\7q\2"+
		"\2ab\7r\2\2bc\7g\2\2cd\7t\2\2de\7v\2\2ef\7k\2\2fg\7g\2\2gh\7u\2\2h\n\3"+
		"\2\2\2ij\7*\2\2j\f\3\2\2\2kl\7.\2\2l\16\3\2\2\2mn\7K\2\2no\7p\2\2op\7"+
		"v\2\2p\20\3\2\2\2qr\7+\2\2r\22\3\2\2\2st\7?\2\2t\24\3\2\2\2uv\7H\2\2v"+
		"w\7n\2\2wx\7q\2\2xy\7c\2\2yz\7v\2\2z\26\3\2\2\2{|\7T\2\2|}\7c\2\2}~\7"+
		"p\2\2~\177\7i\2\2\177\u0080\7g\2\2\u0080\30\3\2\2\2\u0081\u0082\7E\2\2"+
		"\u0082\u0083\7q\2\2\u0083\u0084\7n\2\2\u0084\u0085\7q\2\2\u0085\u0086"+
		"\7t\2\2\u0086\32\3\2\2\2\u0087\u0088\7X\2\2\u0088\u0089\7g\2\2\u0089\u008a"+
		"\7e\2\2\u008a\u008b\7v\2\2\u008b\u008c\7q\2\2\u008c\u008d\7t\2\2\u008d"+
		"\34\3\2\2\2\u008e\u008f\7\64\2\2\u008f\u0090\7F\2\2\u0090\36\3\2\2\2\u0091"+
		"\u0092\7}\2\2\u0092\u0093\7\177\2\2\u0093 \3\2\2\2\u0094\u0095\7E\2\2"+
		"\u0095\u0096\7w\2\2\u0096\u0097\7d\2\2\u0097\u0098\7g\2\2\u0098\"\3\2"+
		"\2\2\u0099\u009a\7\65\2\2\u009a\u009b\7F\2\2\u009b$\3\2\2\2\u009c\u009d"+
		"\7E\2\2\u009d\u009e\7c\2\2\u009e\u009f\7v\2\2\u009f\u00a0\7g\2\2\u00a0"+
		"\u00a1\7i\2\2\u00a1\u00a2\7q\2\2\u00a2\u00a3\7t\2\2\u00a3\u00a4\7{\2\2"+
		"\u00a4&\3\2\2\2\u00a5\u00a6\7M\2\2\u00a6\u00a7\7g\2\2\u00a7\u00a8\7t\2"+
		"\2\u00a8\u00a9\7p\2\2\u00a9\u00aa\7g\2\2\u00aa\u00ab\7n\2\2\u00ab(\3\2"+
		"\2\2\u00ac\u00ad\7V\2\2\u00ad\u00ae\7c\2\2\u00ae\u00af\7i\2\2\u00af\u00b0"+
		"\7u\2\2\u00b0*\3\2\2\2\u00b1\u00b2\7E\2\2\u00b2\u00b3\7w\2\2\u00b3\u00b4"+
		"\7n\2\2\u00b4\u00b5\7n\2\2\u00b5,\3\2\2\2\u00b6\u00b7\7\\\2\2\u00b7\u00b8"+
		"\7V\2\2\u00b8\u00b9\7g\2\2\u00b9\u00ba\7u\2\2\u00ba\u00bb\7v\2\2\u00bb"+
		".\3\2\2\2\u00bc\u00bd\7\\\2\2\u00bd\u00be\7Y\2\2\u00be\u00bf\7t\2\2\u00bf"+
		"\u00c0\7k\2\2\u00c0\u00c1\7v\2\2\u00c1\u00c2\7g\2\2\u00c2\60\3\2\2\2\u00c3"+
		"\u00c4\7E\2\2\u00c4\u00c5\7q\2\2\u00c5\u00c6\7n\2\2\u00c6\u00c7\7q\2\2"+
		"\u00c7\u00c8\7t\2\2\u00c8\u00c9\7O\2\2\u00c9\u00ca\7c\2\2\u00ca\u00cb"+
		"\7u\2\2\u00cb\u00cc\7m\2\2\u00cc\62\3\2\2\2\u00cd\u00d1\7$\2\2\u00ce\u00d0"+
		"\13\2\2\2\u00cf\u00ce\3\2\2\2\u00d0\u00d3\3\2\2\2\u00d1\u00d2\3\2\2\2"+
		"\u00d1\u00cf\3\2\2\2\u00d2\u00d4\3\2\2\2\u00d3\u00d1\3\2\2\2\u00d4\u00d5"+
		"\7$\2\2\u00d5\64\3\2\2\2\u00d6\u00da\7]\2\2\u00d7\u00d9\13\2\2\2\u00d8"+
		"\u00d7\3\2\2\2\u00d9\u00dc\3\2\2\2\u00da\u00db\3\2\2\2\u00da\u00d8\3\2"+
		"\2\2\u00db\u00dd\3\2\2\2\u00dc\u00da\3\2\2\2\u00dd\u00de\7_\2\2\u00de"+
		"\66\3\2\2\2\u00df\u00e0\7J\2\2\u00e0\u00e1\7N\2\2\u00e1\u00e2\7U\2\2\u00e2"+
		"\u00e3\7N\2\2\u00e3\u00e4\7R\2\2\u00e4\u00e5\7T\2\2\u00e5\u00e6\7Q\2\2"+
		"\u00e6\u00e7\7I\2\2\u00e7\u00e8\7T\2\2\u00e8\u00e9\7C\2\2\u00e9\u00ea"+
		"\7O\2\2\u00ea\u00ee\3\2\2\2\u00eb\u00ed\13\2\2\2\u00ec\u00eb\3\2\2\2\u00ed"+
		"\u00f0\3\2\2\2\u00ee\u00ef\3\2\2\2\u00ee\u00ec\3\2\2\2\u00ef\u00f1\3\2"+
		"\2\2\u00f0\u00ee\3\2\2\2\u00f1\u00f2\7G\2\2\u00f2\u00f3\7P\2\2\u00f3\u00f4"+
		"\7F\2\2\u00f4\u00f5\7J\2\2\u00f5\u00f6\7N\2\2\u00f6\u00f7\7U\2\2\u00f7"+
		"\u00f8\7N\2\2\u00f88\3\2\2\2\u00f9\u00fd\t\2\2\2\u00fa\u00fc\t\3\2\2\u00fb"+
		"\u00fa\3\2\2\2\u00fc\u00ff\3\2\2\2\u00fd\u00fb\3\2\2\2\u00fd\u00fe\3\2"+
		"\2\2\u00fe:\3\2\2\2\u00ff\u00fd\3\2\2\2\u0100\u0101\t\4\2\2\u0101<\3\2"+
		"\2\2\u0102\u010b\7\62\2\2\u0103\u0107\t\5\2\2\u0104\u0106\t\6\2\2\u0105"+
		"\u0104\3\2\2\2\u0106\u0109\3\2\2\2\u0107\u0105\3\2\2\2\u0107\u0108\3\2"+
		"\2\2\u0108\u010b\3\2\2\2\u0109\u0107\3\2\2\2\u010a\u0102\3\2\2\2\u010a"+
		"\u0103\3\2\2\2\u010b>\3\2\2\2\u010c\u010e\t\6\2\2\u010d\u010c\3\2\2\2"+
		"\u010e\u010f\3\2\2\2\u010f\u010d\3\2\2\2\u010f\u0110\3\2\2\2\u0110\u0111"+
		"\3\2\2\2\u0111\u0113\7\60\2\2\u0112\u0114\t\6\2\2\u0113\u0112\3\2\2\2"+
		"\u0114\u0115\3\2\2\2\u0115\u0113\3\2\2\2\u0115\u0116\3\2\2\2\u0116\u0118"+
		"\3\2\2\2\u0117\u0119\5A!\2\u0118\u0117\3\2\2\2\u0118\u0119\3\2\2\2\u0119"+
		"\u0123\3\2\2\2\u011a\u011c\t\6\2\2\u011b\u011a\3\2\2\2\u011c\u011d\3\2"+
		"\2\2\u011d\u011b\3\2\2\2\u011d\u011e\3\2\2\2\u011e\u0120\3\2\2\2\u011f"+
		"\u0121\5A!\2\u0120\u011f\3\2\2\2\u0120\u0121\3\2\2\2\u0121\u0123\3\2\2"+
		"\2\u0122\u010d\3\2\2\2\u0122\u011b\3\2\2\2\u0123@\3\2\2\2\u0124\u0126"+
		"\t\7\2\2\u0125\u0127\5;\36\2\u0126\u0125\3\2\2\2\u0126\u0127\3\2\2\2\u0127"+
		"\u0129\3\2\2\2\u0128\u012a\t\6\2\2\u0129\u0128\3\2\2\2\u012a\u012b\3\2"+
		"\2\2\u012b\u0129\3\2\2\2\u012b\u012c\3\2\2\2\u012cB\3\2\2\2\u012d\u012e"+
		"\7H\2\2\u012e\u012f\7t\2\2\u012f\u0130\7q\2\2\u0130\u0131\7p\2\2\u0131"+
		"\u013b\7v\2\2\u0132\u0133\7D\2\2\u0133\u0134\7c\2\2\u0134\u0135\7e\2\2"+
		"\u0135\u013b\7m\2\2\u0136\u0137\7P\2\2\u0137\u0138\7q\2\2\u0138\u0139"+
		"\7p\2\2\u0139\u013b\7g\2\2\u013a\u012d\3\2\2\2\u013a\u0132\3\2\2\2\u013a"+
		"\u0136\3\2\2\2\u013bD\3\2\2\2\u013c\u013d\7N\2\2\u013d\u013e\7g\2\2\u013e"+
		"\u013f\7u\2\2\u013f\u016c\7u\2\2\u0140\u0141\7I\2\2\u0141\u0142\7t\2\2"+
		"\u0142\u0143\7g\2\2\u0143\u0144\7c\2\2\u0144\u0145\7v\2\2\u0145\u0146"+
		"\7g\2\2\u0146\u016c\7t\2\2\u0147\u0148\7N\2\2\u0148\u0149\7G\2\2\u0149"+
		"\u014a\7s\2\2\u014a\u014b\7w\2\2\u014b\u014c\7c\2\2\u014c\u016c\7n\2\2"+
		"\u014d\u014e\7I\2\2\u014e\u014f\7G\2\2\u014f\u0150\7s\2\2\u0150\u0151"+
		"\7w\2\2\u0151\u0152\7c\2\2\u0152\u016c\7n\2\2\u0153\u0154\7G\2\2\u0154"+
		"\u0155\7s\2\2\u0155\u0156\7w\2\2\u0156\u0157\7c\2\2\u0157\u016c\7n\2\2"+
		"\u0158\u0159\7P\2\2\u0159\u015a\7q\2\2\u015a\u015b\7v\2\2\u015b\u015c"+
		"\7G\2\2\u015c\u015d\7s\2\2\u015d\u015e\7w\2\2\u015e\u015f\7c\2\2\u015f"+
		"\u016c\7n\2\2\u0160\u0161\7C\2\2\u0161\u0162\7n\2\2\u0162\u0163\7y\2\2"+
		"\u0163\u0164\7c\2\2\u0164\u0165\7{\2\2\u0165\u016c\7u\2\2\u0166\u0167"+
		"\7P\2\2\u0167\u0168\7g\2\2\u0168\u0169\7x\2\2\u0169\u016a\7g\2\2\u016a"+
		"\u016c\7t\2\2\u016b\u013c\3\2\2\2\u016b\u0140\3\2\2\2\u016b\u0147\3\2"+
		"\2\2\u016b\u014d\3\2\2\2\u016b\u0153\3\2\2\2\u016b\u0158\3\2\2\2\u016b"+
		"\u0160\3\2\2\2\u016b\u0166\3\2\2\2\u016cF\3\2\2\2\u016d\u016e\7Q\2\2\u016e"+
		"\u0173\7p\2\2\u016f\u0170\7Q\2\2\u0170\u0171\7h\2\2\u0171\u0173\7h\2\2"+
		"\u0172\u016d\3\2\2\2\u0172\u016f\3\2\2\2\u0173H\3\2\2\2\u0174\u0192\t"+
		"\b\2\2\u0175\u0176\7T\2\2\u0176\u0192\7I\2\2\u0177\u0178\7T\2\2\u0178"+
		"\u0192\7D\2\2\u0179\u017a\7T\2\2\u017a\u0192\7C\2\2\u017b\u017c\7I\2\2"+
		"\u017c\u0192\7D\2\2\u017d\u017e\7I\2\2\u017e\u0192\7C\2\2\u017f\u0180"+
		"\7D\2\2\u0180\u0192\7C\2\2\u0181\u0182\7T\2\2\u0182\u0183\7I\2\2\u0183"+
		"\u0192\7D\2\2\u0184\u0185\7T\2\2\u0185\u0186\7I\2\2\u0186\u0192\7C\2\2"+
		"\u0187\u0188\7T\2\2\u0188\u0189\7D\2\2\u0189\u0192\7C\2\2\u018a\u018b"+
		"\7I\2\2\u018b\u018c\7D\2\2\u018c\u0192\7C\2\2\u018d\u018e\7T\2\2\u018e"+
		"\u018f\7I\2\2\u018f\u0190\7D\2\2\u0190\u0192\7C\2\2\u0191\u0174\3\2\2"+
		"\2\u0191\u0175\3\2\2\2\u0191\u0177\3\2\2\2\u0191\u0179\3\2\2\2\u0191\u017b"+
		"\3\2\2\2\u0191\u017d\3\2\2\2\u0191\u017f\3\2\2\2\u0191\u0181\3\2\2\2\u0191"+
		"\u0184\3\2\2\2\u0191\u0187\3\2\2\2\u0191\u018a\3\2\2\2\u0191\u018d\3\2"+
		"\2\2\u0192J\3\2\2\2\u0193\u0195\t\t\2\2\u0194\u0193\3\2\2\2\u0195\u0196"+
		"\3\2\2\2\u0196\u0194\3\2\2\2\u0196\u0197\3\2\2\2\u0197\u0198\3\2\2\2\u0198"+
		"\u0199\b&\2\2\u0199L\3\2\2\2\u019a\u019c\7\17\2\2\u019b\u019d\7\f\2\2"+
		"\u019c\u019b\3\2\2\2\u019c\u019d\3\2\2\2\u019d\u01a0\3\2\2\2\u019e\u01a0"+
		"\7\f\2\2\u019f\u019a\3\2\2\2\u019f\u019e\3\2\2\2\u01a0\u01a1\3\2\2\2\u01a1"+
		"\u01a2\b\'\2\2\u01a2N\3\2\2\2\u01a3\u01a4\7\61\2\2\u01a4\u01a5\7,\2\2"+
		"\u01a5\u01a9\3\2\2\2\u01a6\u01a8\13\2\2\2\u01a7\u01a6\3\2\2\2\u01a8\u01ab"+
		"\3\2\2\2\u01a9\u01aa\3\2\2\2\u01a9\u01a7\3\2\2\2\u01aa\u01ac\3\2\2\2\u01ab"+
		"\u01a9\3\2\2\2\u01ac\u01ad\7,\2\2\u01ad\u01ae\7\61\2\2\u01ae\u01af\3\2"+
		"\2\2\u01af\u01b0\b(\2\2\u01b0P\3\2\2\2\u01b1\u01b2\7\61\2\2\u01b2\u01b3"+
		"\7\61\2\2\u01b3\u01b7\3\2\2\2\u01b4\u01b6\n\n\2\2\u01b5\u01b4\3\2\2\2"+
		"\u01b6\u01b9\3\2\2\2\u01b7\u01b5\3\2\2\2\u01b7\u01b8\3\2\2\2\u01b8\u01ba"+
		"\3\2\2\2\u01b9\u01b7\3\2\2\2\u01ba\u01bb\b)\2\2\u01bbR\3\2\2\2\32\2\u00d1"+
		"\u00da\u00ee\u00fd\u0107\u010a\u010f\u0115\u0118\u011d\u0120\u0122\u0126"+
		"\u012b\u013a\u016b\u0172\u0191\u0196\u019c\u019f\u01a9\u01b7\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}