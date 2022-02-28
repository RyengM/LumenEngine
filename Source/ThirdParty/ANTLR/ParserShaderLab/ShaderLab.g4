// Created by demonhub
grammar ShaderLab;

// Paser rules
shader              : 'Shader' shader_name '{' properties? category '}';
properties          : 'Properties' '{' property+ '}';

property            : property_int
                    | property_float
                    | property_range
                    | property_color
                    | property_vector
                    | property_2d
                    | property_cube
                    | property_3d
                    ;

property_int        : meta* property_identifier '(' display_name ',' 'Int' ')' '=' val_int;
property_float      : meta* property_identifier '(' display_name ',' 'Float' ')' '=' val_float;
property_range      : meta* property_identifier '(' display_name ',' 'Range' range ')' '=' val_float;
property_color      : meta* property_identifier '(' display_name ',' 'Color' ')' '=' val_vec4;
property_vector     : meta* property_identifier '(' display_name ',' 'Vector' ')' '=' val_vec4;
property_2d         : meta* property_identifier '(' display_name ',' '2D' ')' '=' texture_name '{}';
property_cube       : meta* property_identifier '(' display_name ',' 'Cube' ')' '=' texture_name '{}';
property_3d         : meta* property_identifier '(' display_name ',' '3D' ')' '=' texture_name '{}';

category            : 'Category' '{' tags? kernel+ '}';

kernel              : 'Kernel' '{' tags common_state* hlsl_block '}';

hlsl_block          : HLSL;

tags                : 'Tags' '{' tag+ '}';
tag                 : tag_key '=' tag_val (',')?;

common_state        : cull
                    | ztest
                    | zwrite
                    | color_mask
                    ;

cull                : 'Cull' CullMode;
ztest               : 'ZTest' Comparator;
zwrite              : 'ZWrite' ZWriteMode;
color_mask          : 'ColorMask' channel;

meta                : MetaInfo;
range               : '(' val_min ',' val_max ')';
tag_key             : String;
tag_val             : String;
shader_name         : String;
display_name        : String;
texture_name        : String;
property_identifier : Identifier;
val_int             : Sign? IntegerLiteral;
val_float           : Sign? FloatingLiteral;
val_min             : Sign? FloatingLiteral;
val_max             : Sign? FloatingLiteral;
val_vec4            : '(' val_float ',' val_float ',' val_float ',' val_float ')';
channel             : Channel
                    | IntegerLiteral
                    ;

// Lexer rules
String              : '"' .*? '"';
MetaInfo            : '[' .*? ']';
HLSL                : 'HLSLPROGRAM' .*? 'ENDHLSL';

Identifier          : [_][0-9a-zA-Z]*;
Sign                : [+-];
IntegerLiteral      : '0' | [1-9][0-9]*;

FloatingLiteral     : [0-9]+ '.' [0-9]+ ExponentPart?
                    | [0-9]+ ExponentPart?
                    ;

ExponentPart        : [eE] Sign? [0-9]+;

CullMode            : 'Front'
                    | 'Back'
                    | 'None'
                    ;

Comparator          : 'Less'
                    | 'Greater'
                    | 'LEqual'
                    | 'GEqual'
                    | 'Equal'
                    | 'NotEqual'
                    | 'Always'
                    | 'Never'
                    ;

ZWriteMode          : 'On'
                    | 'Off'
                    ;

Channel             : 'R'
                    | 'G'
                    | 'B'
                    | 'A'
                    | 'RG'
                    | 'RB'
                    | 'RA'
                    | 'GB'
                    | 'GA'
                    | 'BA'
                    | 'RGB'
                    | 'RGA'
                    | 'RBA'
                    | 'GBA'
                    | 'RGBA'
                    ;

Whitespace          : [ \t]+ -> skip;

Newline             : ('\r' '\n'? | '\n') -> skip;

BlockComment        : '/*' .*? '*/' -> skip;

LineComment         : '//' ~ [\r\n]* -> skip ;