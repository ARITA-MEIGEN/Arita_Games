xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 251;
 0.00000;24.99326;-6.70403;,
 2.80296;26.30682;-5.82759;,
 3.27936;23.90630;-6.56423;,
 0.00000;22.92602;-7.72805;,
 5.53196;26.07484;-4.81165;,
 6.32886;23.78910;-5.08137;,
 3.29772;19.11320;-7.57523;,
 0.00000;18.03236;-8.11867;,
 8.75550;19.14726;-4.81029;,
 7.71930;26.42196;-3.00079;,
 8.75954;22.72936;-3.76023;,
 9.58162;26.07484;-1.75699;,
 10.75922;22.52714;-2.12087;,
 10.74628;17.97116;-3.34481;,
 8.75550;19.14726;-4.81029;,
 9.95626;24.08402;0.01719;,
 11.65360;21.37538;-0.15017;,
 10.79140;22.74254;1.77429;,
 12.09980;20.06044;3.66749;,
 11.91058;17.97040;-2.04385;,
 12.40872;17.97116;3.35577;,
 10.10940;22.82158;4.76509;,
 11.50836;20.12540;5.10377;,
 9.34564;25.25222;6.55753;,
 10.49578;20.10588;6.37857;,
 12.88672;15.38066;6.35997;,
 11.58108;15.37520;6.59077;,
 7.44622;25.43946;7.32545;,
 8.43756;20.19852;7.28391;,
 5.39570;25.25222;8.02153;,
 6.04508;20.09814;8.03025;,
 9.41250;15.38098;7.55553;,
 6.68634;15.37520;8.27417;,
 2.72382;25.43254;8.33567;,
 3.07868;20.18832;8.43073;,
 0.00000;25.25222;8.55739;,
 0.00000;20.09462;8.63131;,
 3.43618;15.37878;8.73593;,
 0.00000;15.37520;8.89035;,
 -2.72382;25.43254;8.33569;,
 -3.07868;20.18832;8.43073;,
 -5.39570;25.25222;8.02153;,
 -6.04508;20.09814;8.03025;,
 -3.43618;15.37878;8.73593;,
 -6.68634;15.37520;8.27417;,
 -7.44620;25.43946;7.32545;,
 -8.43756;20.19852;7.28391;,
 -9.34562;25.25222;7.33933;,
 -10.49578;20.10588;7.02331;,
 -9.41250;15.38098;7.55555;,
 -11.58108;15.37520;7.39801;,
 -10.10940;25.33124;5.58923;,
 -11.50836;20.12540;5.10377;,
 -10.79140;22.74254;1.77429;,
 -12.09980;20.06044;3.66749;,
 -12.88672;15.38066;6.35997;,
 -12.40872;17.97116;1.56063;,
 -9.95626;25.06140;0.01719;,
 -11.65360;21.37538;-0.15017;,
 -9.58162;26.07484;-1.75699;,
 -10.75922;22.52714;-2.12087;,
 -11.91058;17.97040;-2.04383;,
 -10.74628;17.97116;-3.34479;,
 -7.71930;26.42196;-3.00079;,
 -8.75956;22.72936;-3.76023;,
 -5.53196;26.07484;-4.81165;,
 -6.32888;23.78910;-5.08137;,
 -8.75550;19.14726;-4.81029;,
 -2.80296;26.30682;-5.82759;,
 -3.27936;23.90630;-6.56423;,
 0.00000;24.99326;-6.70403;,
 0.00000;22.92602;-7.72805;,
 -3.29772;19.11320;-7.57523;,
 -8.75550;19.14726;-4.81029;,
 0.00000;18.03236;-8.11867;,
 2.78514;12.28494;-6.30059;,
 0.00000;12.39548;-7.17947;,
 5.35858;12.46774;-4.89045;,
 1.95698;0.20664;-4.68395;,
 0.00000;0.18716;-5.36005;,
 3.84374;0.45170;-3.80567;,
 7.42724;11.19354;-3.73129;,
 5.31156;0.28366;-2.08727;,
 10.08676;11.20620;-0.25319;,
 7.42724;11.19354;-3.73129;,
 10.62012;11.27706;1.82117;,
 7.24310;0.29584;0.72897;,
 6.65756;0.45170;-0.93217;,
 7.68748;0.45170;2.42729;,
 10.11346;11.18976;5.18769;,
 9.18126;11.27940;6.47509;,
 7.25270;0.26928;5.37817;,
 6.65756;0.45170;7.03313;,
 7.37354;11.19652;7.40035;,
 5.27606;11.28456;8.16293;,
 5.30542;0.27502;7.11641;,
 3.84374;0.45170;7.77691;,
 2.68656;11.20248;8.57031;,
 0.00000;11.28666;8.77367;,
 1.94050;0.28184;8.07745;,
 0.00000;0.45170;8.28671;,
 -2.68654;11.20248;8.57031;,
 -5.27606;11.28456;8.16293;,
 -1.94050;0.28184;8.07745;,
 -3.84374;0.45170;7.77691;,
 -7.37354;11.19652;7.40035;,
 -9.18126;11.27940;7.19377;,
 -5.30542;0.27502;7.11641;,
 -6.65756;0.45170;7.03313;,
 -10.11346;11.18976;5.18771;,
 -10.62012;11.27706;1.82117;,
 -7.25270;0.26928;5.37817;,
 -7.68748;0.45170;2.42731;,
 -10.08676;11.20620;-0.25319;,
 -7.42724;11.19354;-3.73129;,
 -7.24310;0.29584;0.72897;,
 -6.65756;0.45170;-0.93217;,
 -7.42724;11.19354;-3.73129;,
 -5.35860;12.46774;-4.89045;,
 -3.84376;0.45170;-3.80567;,
 -5.31156;0.28366;-2.08727;,
 -2.78514;12.28494;-6.30059;,
 0.00000;12.39548;-7.17947;,
 -1.95698;0.20664;-4.68393;,
 0.00000;0.18716;-5.36005;,
 0.00000;22.74254;1.77429;,
 2.96926;24.99416;-1.91085;,
 0.00000;25.11474;-2.23887;,
 0.00000;22.74254;1.77429;,
 4.75180;24.73034;0.15777;,
 2.96926;24.99416;-1.91085;,
 0.00000;22.74254;1.77429;,
 5.67350;23.65462;1.94153;,
 4.75180;24.73034;0.15777;,
 0.00000;22.74254;1.77429;,
 4.86552;23.48362;4.85639;,
 5.67350;23.65462;1.94153;,
 0.00000;22.74254;1.77429;,
 2.78566;25.84852;7.01713;,
 4.86552;23.48362;4.85639;,
 0.00000;22.74254;1.77429;,
 0.00000;25.79346;6.64575;,
 2.78566;25.84852;7.01713;,
 0.00000;22.74254;1.77429;,
 -2.78566;25.84852;7.01713;,
 0.00000;25.79346;6.64575;,
 0.00000;22.74254;1.77429;,
 -4.86552;25.99326;5.68053;,
 -2.78566;25.84852;7.01713;,
 0.00000;22.74254;1.77429;,
 -5.67350;23.65462;1.94153;,
 -4.86552;25.99326;5.68053;,
 0.00000;22.74254;1.77429;,
 -4.75180;24.73034;0.15779;,
 -5.67350;23.65462;1.94153;,
 0.00000;22.74254;1.77429;,
 -2.96926;24.99416;-1.91085;,
 -4.75180;24.73034;0.15779;,
 0.00000;22.74254;1.77429;,
 0.00000;25.11474;-2.23887;,
 -2.96926;24.99416;-1.91085;,
 0.00000;0.45170;2.42729;,
 0.00000;-0.41492;-1.30623;,
 2.06304;-0.41028;-1.15655;,
 0.00000;0.45170;2.42729;,
 2.06304;-0.41028;-1.15655;,
 3.48948;-0.40580;0.64673;,
 0.00000;0.45170;2.42729;,
 3.48948;-0.40580;0.64673;,
 4.03000;-0.42138;2.42723;,
 0.00000;0.45170;2.42729;,
 4.03000;-0.42138;2.42723;,
 3.46620;-0.38268;5.48073;,
 0.00000;0.45170;2.42729;,
 3.46620;-0.38268;5.48073;,
 1.97524;-0.32214;6.75287;,
 0.00000;0.45170;2.42729;,
 1.97524;-0.32214;6.75287;,
 0.00000;-0.29878;7.20085;,
 0.00000;0.45170;2.42729;,
 0.00000;-0.29878;7.20085;,
 -1.97524;-0.32214;6.75287;,
 0.00000;0.45170;2.42729;,
 -1.97524;-0.32214;6.75287;,
 -3.46620;-0.38268;5.48073;,
 0.00000;0.45170;2.42729;,
 -3.46620;-0.38268;5.48073;,
 -4.03000;-0.42138;2.42723;,
 0.00000;0.45170;2.42729;,
 -4.03000;-0.42138;2.42723;,
 -3.48948;-0.40580;0.64673;,
 0.00000;0.45170;2.42729;,
 -3.48948;-0.40580;0.64673;,
 -2.06304;-0.41028;-1.15655;,
 0.00000;0.45170;2.42729;,
 -2.06304;-0.41028;-1.15655;,
 0.00000;-0.41492;-1.30623;,
 0.00000;29.55788;-1.99507;,
 1.16840;29.55788;-1.58319;,
 4.33228;17.49604;-6.04055;,
 0.00000;17.49604;-7.11235;,
 2.02374;29.55788;-0.45787;,
 7.50372;17.49604;-3.95787;,
 2.33682;29.55788;1.07931;,
 8.66456;17.49604;0.04213;,
 2.02374;29.55788;2.61649;,
 7.50372;14.90008;6.75809;,
 1.16840;29.55788;3.74181;,
 4.33228;14.90008;7.69655;,
 0.00000;29.55788;4.15369;,
 0.00000;14.90008;8.30353;,
 -1.16840;29.55788;3.74181;,
 -4.33228;14.90008;7.69655;,
 -2.02374;29.55788;2.61649;,
 -7.50372;14.90008;6.75809;,
 -2.33682;29.55788;1.07931;,
 -8.66456;17.49604;0.04213;,
 -2.02374;29.55788;-0.45787;,
 -7.50372;17.49604;-3.95787;,
 -1.16840;29.55788;-1.58319;,
 -4.33228;17.49604;-6.88607;,
 0.00000;29.55788;-1.99507;,
 0.00000;17.49604;-7.11235;,
 0.00000;29.55788;1.07931;,
 0.00000;29.55788;1.07931;,
 0.00000;29.55788;1.07931;,
 0.00000;29.55788;1.07931;,
 0.00000;29.55788;1.07931;,
 0.00000;29.55788;1.07931;,
 0.00000;29.55788;1.07931;,
 0.00000;29.55788;1.07931;,
 0.00000;29.55788;1.07931;,
 0.00000;29.55788;1.07931;,
 0.00000;29.55788;1.07931;,
 0.00000;29.55788;1.07931;,
 0.00000;17.49604;0.04213;,
 0.00000;17.49604;0.04213;,
 0.00000;17.49604;0.04213;,
 0.00000;17.49604;0.04213;,
 0.00000;17.49604;0.04213;,
 0.00000;17.49604;0.04213;,
 0.00000;17.49604;0.04213;,
 0.00000;17.49604;0.04213;,
 0.00000;17.49604;0.04213;,
 0.00000;17.49604;0.04213;,
 0.00000;17.49604;0.04213;,
 0.00000;17.49604;0.04213;,
 -8.75550;19.14726;-4.81029;,
 8.75550;19.14726;-4.81029;,
 -7.42724;11.19354;-3.73129;,
 7.42724;11.19354;-3.73129;;
 
 228;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;3,2,6,7;,
 4;2,5,8,6;,
 4;4,9,10,5;,
 4;9,11,12,10;,
 4;10,12,13,14;,
 4;11,15,16,12;,
 4;15,17,18,16;,
 4;12,16,19,13;,
 4;16,18,20,19;,
 4;17,21,22,18;,
 4;21,23,24,22;,
 4;18,22,25,20;,
 4;22,24,26,25;,
 4;23,27,28,24;,
 4;27,29,30,28;,
 4;24,28,31,26;,
 4;28,30,32,31;,
 4;29,33,34,30;,
 4;33,35,36,34;,
 4;30,34,37,32;,
 4;34,36,38,37;,
 4;35,39,40,36;,
 4;39,41,42,40;,
 4;36,40,43,38;,
 4;40,42,44,43;,
 4;41,45,46,42;,
 4;45,47,48,46;,
 4;42,46,49,44;,
 4;46,48,50,49;,
 4;47,51,52,48;,
 4;51,53,54,52;,
 4;48,52,55,50;,
 4;52,54,56,55;,
 4;53,57,58,54;,
 4;57,59,60,58;,
 4;54,58,61,56;,
 4;58,60,62,61;,
 4;59,63,64,60;,
 4;63,65,66,64;,
 4;60,64,67,62;,
 4;65,68,69,66;,
 4;68,70,71,69;,
 4;66,69,72,73;,
 4;69,71,74,72;,
 4;7,6,75,76;,
 4;6,8,77,75;,
 4;76,75,78,79;,
 4;75,77,80,78;,
 4;77,81,82,80;,
 4;13,19,83,84;,
 4;19,20,85,83;,
 4;84,83,86,87;,
 4;83,85,88,86;,
 4;20,25,89,85;,
 4;25,26,90,89;,
 4;85,89,91,88;,
 4;89,90,92,91;,
 4;26,31,93,90;,
 4;31,32,94,93;,
 4;90,93,95,92;,
 4;93,94,96,95;,
 4;32,37,97,94;,
 4;37,38,98,97;,
 4;94,97,99,96;,
 4;97,98,100,99;,
 4;38,43,101,98;,
 4;43,44,102,101;,
 4;98,101,103,100;,
 4;101,102,104,103;,
 4;44,49,105,102;,
 4;49,50,106,105;,
 4;102,105,107,104;,
 4;105,106,108,107;,
 4;50,55,109,106;,
 4;55,56,110,109;,
 4;106,109,111,108;,
 4;109,110,112,111;,
 4;56,61,113,110;,
 4;61,62,114,113;,
 4;110,113,115,112;,
 4;113,114,116,115;,
 4;117,118,119,120;,
 4;73,72,121,118;,
 4;72,74,122,121;,
 4;118,121,123,119;,
 4;121,122,124,123;,
 3;125,126,127;,
 3;126,1,127;,
 3;127,1,0;,
 3;126,4,1;,
 3;128,129,130;,
 3;129,9,130;,
 3;130,9,4;,
 3;129,11,9;,
 3;131,132,133;,
 3;132,15,133;,
 3;133,15,11;,
 3;132,17,15;,
 3;134,135,136;,
 3;135,21,136;,
 3;136,21,17;,
 3;135,23,21;,
 3;137,138,139;,
 3;138,27,139;,
 3;139,27,23;,
 3;138,29,27;,
 3;140,141,142;,
 3;141,33,142;,
 3;142,33,29;,
 3;141,35,33;,
 3;143,144,145;,
 3;144,39,145;,
 3;145,39,35;,
 3;144,41,39;,
 3;146,147,148;,
 3;147,45,148;,
 3;148,45,41;,
 3;147,47,45;,
 3;149,150,151;,
 3;150,51,151;,
 3;151,51,47;,
 3;150,53,51;,
 3;152,153,154;,
 3;153,57,154;,
 3;154,57,53;,
 3;153,59,57;,
 3;155,156,157;,
 3;156,63,157;,
 3;157,63,59;,
 3;156,65,63;,
 3;158,159,160;,
 3;159,68,160;,
 3;160,68,65;,
 3;159,70,68;,
 3;161,162,163;,
 3;162,78,163;,
 3;163,78,80;,
 3;162,79,78;,
 3;164,165,166;,
 3;165,82,166;,
 3;166,82,87;,
 3;165,80,82;,
 3;167,168,169;,
 3;168,86,169;,
 3;169,86,88;,
 3;168,87,86;,
 3;170,171,172;,
 3;171,91,172;,
 3;172,91,92;,
 3;171,88,91;,
 3;173,174,175;,
 3;174,95,175;,
 3;175,95,96;,
 3;174,92,95;,
 3;176,177,178;,
 3;177,99,178;,
 3;178,99,100;,
 3;177,96,99;,
 3;179,180,181;,
 3;180,103,181;,
 3;181,103,104;,
 3;180,100,103;,
 3;182,183,184;,
 3;183,107,184;,
 3;184,107,108;,
 3;183,104,107;,
 3;185,186,187;,
 3;186,111,187;,
 3;187,111,112;,
 3;186,108,111;,
 3;188,189,190;,
 3;189,115,190;,
 3;190,115,116;,
 3;189,112,115;,
 3;191,192,193;,
 3;192,120,193;,
 3;193,120,119;,
 3;192,116,120;,
 3;194,195,196;,
 3;195,123,196;,
 3;196,123,124;,
 3;195,119,123;,
 4;197,198,199,200;,
 4;198,201,202,199;,
 4;201,203,204,202;,
 4;203,205,206,204;,
 4;205,207,208,206;,
 4;207,209,210,208;,
 4;209,211,212,210;,
 4;211,213,214,212;,
 4;213,215,216,214;,
 4;215,217,218,216;,
 4;217,219,220,218;,
 4;219,221,222,220;,
 3;223,198,197;,
 3;224,201,198;,
 3;225,203,201;,
 3;226,205,203;,
 3;227,207,205;,
 3;228,209,207;,
 3;229,211,209;,
 3;230,213,211;,
 3;231,215,213;,
 3;232,217,215;,
 3;233,219,217;,
 3;234,221,219;,
 3;235,200,199;,
 3;236,199,202;,
 3;237,202,204;,
 3;238,204,206;,
 3;239,206,208;,
 3;240,208,210;,
 3;241,210,212;,
 3;242,212,214;,
 3;243,214,216;,
 3;244,216,218;,
 3;245,218,220;,
 3;246,220,222;,
 3;247,64,66;,
 3;247,118,117;,
 3;248,5,10;,
 3;248,81,77;,
 3;249,62,67;,
 3;249,120,116;,
 3;250,14,13;,
 3;250,87,82;;
 
 MeshMaterialList {
  22;
  228;
  11,
  11,
  11,
  11,
  0,
  9,
  9,
  0,
  0,
  0,
  0,
  9,
  2,
  2,
  9,
  2,
  2,
  9,
  9,
  9,
  2,
  9,
  9,
  2,
  9,
  9,
  9,
  2,
  2,
  9,
  9,
  2,
  9,
  9,
  2,
  0,
  0,
  0,
  0,
  9,
  0,
  9,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  9,
  0,
  0,
  0,
  0,
  2,
  11,
  2,
  11,
  11,
  9,
  11,
  9,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  9,
  11,
  9,
  11,
  11,
  2,
  11,
  2,
  0,
  0,
  0,
  0,
  9,
  11,
  11,
  11,
  11,
  11,
  0,
  0,
  0,
  11,
  2,
  2,
  2,
  11,
  2,
  2,
  2,
  11,
  11,
  2,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  2,
  11,
  2,
  2,
  2,
  11,
  2,
  2,
  2,
  11,
  0,
  0,
  0,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  0,
  11,
  11,
  9,
  9,
  11,
  11,
  9,
  9,
  11,
  11,
  0,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  9,
  0,
  9,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.078400;0.429600;0.800000;1.000000;;
   12.000000;
   0.120000;0.120000;0.120000;;
   0.011760;0.064440;0.120000;;
  }
  Material {
   0.357600;0.357600;0.357600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.511200;0.511200;0.511200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.166400;0.166400;0.166400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.580000;0.527200;0.392000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.511200;0.464000;0.344800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.455200;0.455200;0.455200;1.000000;;
   25.000000;
   0.220000;0.220000;0.220000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.006400;0.034400;0.062400;1.000000;;
   12.000000;
   0.120000;0.120000;0.120000;;
   0.000960;0.005160;0.009360;;
  }
  Material {
   0.024800;0.125600;0.235200;1.000000;;
   12.000000;
   0.120000;0.120000;0.120000;;
   0.003720;0.018840;0.035280;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.545600;0.128800;0.930000;;
   15.000000;
   0.020000;0.020000;0.020000;;
   0.240000;0.163680;0.038640;;
  }
  Material {
   0.718400;0.021600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.599760;0.487200;0.000000;1.000000;;
   20.000000;
   0.400000;0.400000;0.400000;;
   0.042840;0.034800;0.000000;;
  }
  Material {
   0.000000;0.360800;0.800000;0.800000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.417600;0.731200;0.718400;0.800000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.180000;0.180000;0.180000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.892800;0.747900;0.229500;1.000000;;
   8.000000;
   0.250000;0.250000;0.250000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.056800;0.460800;0.800000;1.000000;;
   11.000000;
   0.330000;0.330000;0.330000;;
   0.024850;0.201600;0.350000;;
  }
  Material {
   0.800000;0.800000;0.800000;0.550000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.213600;0.448800;1.000000;;
   5.000000;
   0.250000;0.250000;0.250000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  213;
  0.000000;0.382511;-0.923951;,
  0.280535;0.339077;-0.897957;,
  0.483398;0.301246;-0.821935;,
  0.000000;0.265226;-0.964186;,
  0.304366;0.252240;-0.918551;,
  0.488045;0.256067;-0.834411;,
  0.000000;-0.019002;-0.999819;,
  0.349338;-0.014741;-0.936881;,
  0.509497;0.006048;-0.860451;,
  0.582717;0.301549;-0.754658;,
  0.829109;0.397970;-0.392680;,
  0.588511;0.261753;-0.764944;,
  0.800842;0.303126;-0.516494;,
  0.714434;-0.033934;-0.698880;,
  0.498255;0.759702;0.417845;,
  0.570460;0.786753;0.235784;,
  0.935449;0.329318;-0.128393;,
  0.932110;0.343244;0.115564;,
  0.933887;-0.072206;-0.350201;,
  0.995961;-0.086655;-0.023506;,
  0.568453;0.797382;0.202592;,
  0.686267;0.216751;0.694303;,
  0.828641;0.342197;0.443008;,
  0.570351;0.210562;0.793954;,
  0.845470;-0.105852;0.523428;,
  0.466170;-0.072426;0.881726;,
  0.349657;0.053321;0.935359;,
  0.217495;0.033799;0.975476;,
  0.344678;0.084379;0.934921;,
  0.211898;0.059216;0.975496;,
  0.353510;-0.043776;0.934406;,
  0.214885;-0.013076;0.976552;,
  0.099272;0.020598;0.994847;,
  0.000002;0.018923;0.999821;,
  0.097704;0.043350;0.994271;,
  0.000001;0.039847;0.999206;,
  0.100386;0.005714;0.994932;,
  -0.000000;0.011330;0.999936;,
  -0.099272;0.020596;0.994847;,
  -0.217498;0.033798;0.975476;,
  -0.097704;0.043349;0.994271;,
  -0.211899;0.059216;0.975496;,
  -0.100386;0.005714;0.994932;,
  -0.214883;-0.013076;0.976552;,
  -0.183957;0.011914;0.982862;,
  -0.058047;-0.021375;0.998085;,
  -0.185989;0.052730;0.981136;,
  -0.322673;0.134007;0.936976;,
  -0.192371;-0.014224;0.981219;,
  -0.455173;-0.061697;0.888263;,
  -0.903341;0.312590;0.293707;,
  -0.892198;0.436346;0.116553;,
  -0.888027;0.301618;0.347037;,
  -0.940882;0.329477;0.078659;,
  -0.928599;-0.108869;0.354756;,
  -0.996409;-0.072031;-0.044512;,
  -0.913233;0.407432;-0.002080;,
  -0.817981;0.359543;-0.449039;,
  -0.940161;0.306370;-0.149110;,
  -0.792141;0.284165;-0.540150;,
  -0.930636;-0.064080;-0.360292;,
  -0.714436;-0.033935;-0.698878;,
  -0.582718;0.301552;-0.754656;,
  -0.483397;0.301249;-0.821934;,
  -0.588512;0.261753;-0.764944;,
  -0.488044;0.256068;-0.834411;,
  -0.509499;0.006047;-0.860450;,
  -0.280534;0.339078;-0.897957;,
  -0.304366;0.252240;-0.918551;,
  -0.349337;-0.014741;-0.936881;,
  -0.000001;-0.167088;-0.985942;,
  0.373449;-0.168227;-0.912269;,
  0.475925;-0.182300;-0.860385;,
  -0.000002;-0.151541;-0.988451;,
  0.384818;-0.144494;-0.911612;,
  0.524033;-0.167536;-0.835058;,
  0.631346;-0.238055;-0.738060;,
  0.618722;-0.212781;-0.756245;,
  0.758446;-0.240783;-0.605626;,
  0.882786;-0.287118;-0.371823;,
  0.950081;-0.298772;-0.089896;,
  0.900276;-0.255202;-0.352669;,
  0.963788;-0.262304;-0.048056;,
  0.871857;-0.344372;0.348243;,
  0.530619;-0.243726;0.811813;,
  0.924163;-0.227726;0.306699;,
  0.612185;-0.134871;0.779128;,
  0.339650;-0.135769;0.930701;,
  0.243750;-0.091280;0.965533;,
  0.261729;-0.586221;0.766709;,
  0.224272;-0.551610;0.803386;,
  0.113966;-0.053363;0.992050;,
  -0.000000;-0.043303;0.999062;,
  0.109078;-0.521392;0.846317;,
  -0.000000;-0.486635;0.873605;,
  -0.113966;-0.053363;0.992050;,
  -0.243749;-0.091281;0.965533;,
  -0.086805;-0.340319;0.936295;,
  -0.237964;-0.382405;0.892827;,
  -0.213852;-0.093090;0.972421;,
  -0.499999;-0.248412;0.829634;,
  -0.213556;-0.378386;0.900677;,
  -0.090908;-0.040065;0.995053;,
  -0.893262;-0.368728;0.257143;,
  -0.947345;-0.308360;-0.086317;,
  -0.935661;-0.237605;0.260925;,
  -0.963788;-0.262304;-0.048055;,
  -0.880520;-0.286965;-0.377273;,
  -0.631348;-0.238055;-0.738058;,
  -0.900276;-0.255202;-0.352668;,
  -0.758446;-0.240783;-0.605626;,
  -0.475925;-0.182301;-0.860385;,
  -0.618724;-0.212781;-0.756244;,
  -0.524031;-0.167537;-0.835058;,
  -0.373448;-0.168227;-0.912270;,
  -0.384817;-0.144495;-0.911613;,
  0.026554;0.995485;0.091127;,
  0.000000;0.959122;0.282992;,
  -0.132925;0.936867;0.323438;,
  -0.083986;0.873472;0.479577;,
  0.049097;0.953737;0.296606;,
  0.048077;0.890688;-0.452066;,
  0.104145;0.956670;-0.271911;,
  0.000000;0.999895;0.014499;,
  0.013847;0.998167;0.058908;,
  0.003973;0.986134;-0.165902;,
  -0.037501;0.843455;-0.535889;,
  0.134003;0.886078;0.443744;,
  0.132925;0.936867;0.323437;,
  -0.000000;-0.999780;0.020972;,
  0.059978;-0.996569;-0.057038;,
  -0.000000;-0.999500;-0.031634;,
  0.063002;-0.996989;-0.045210;,
  0.067487;-0.997718;0.001848;,
  0.048130;-0.994870;0.088978;,
  0.052090;-0.974805;0.216890;,
  0.000000;-0.956452;0.291889;,
  -0.052090;-0.974805;0.216890;,
  -0.048130;-0.994870;0.088978;,
  -0.067487;-0.997718;0.001848;,
  -0.063002;-0.996989;-0.045210;,
  -0.059977;-0.996569;-0.057038;,
  0.000000;1.000000;0.000000;,
  0.043074;0.403060;-0.914160;,
  0.445633;0.428841;-0.785816;,
  0.758989;0.472062;-0.448435;,
  0.888735;0.458144;0.015951;,
  0.739858;0.409972;0.533417;,
  0.387148;0.316776;0.865892;,
  0.000000;0.280077;0.959978;,
  -0.387148;0.316776;0.865892;,
  -0.739858;0.409972;0.533417;,
  -0.888735;0.458144;0.015951;,
  -0.776498;0.474694;-0.414387;,
  -0.435833;0.447236;-0.781044;,
  0.000000;-0.987356;-0.158517;,
  -0.883884;0.183433;0.430233;,
  -0.895987;-0.220508;0.385465;,
  -0.155846;0.965057;0.210656;,
  0.000000;0.999630;-0.027196;,
  -0.149886;0.962491;0.226155;,
  -0.190022;0.941562;0.278123;,
  0.003749;0.813917;0.580969;,
  -0.034813;0.737213;-0.674763;,
  0.062562;0.605005;-0.793760;,
  0.257202;0.765307;-0.590044;,
  -0.011236;0.789499;-0.613649;,
  0.053497;0.913496;0.403315;,
  0.076699;0.932075;0.354052;,
  -0.000128;0.956423;0.291985;,
  0.000001;0.962178;0.272421;,
  0.000127;0.956424;0.291983;,
  -0.076700;0.932076;0.354050;,
  -0.073681;0.960589;0.268030;,
  -0.110868;0.983909;0.140112;,
  -0.124395;0.934516;-0.333475;,
  -0.130445;0.831086;-0.540630;,
  0.016789;0.775486;0.631141;,
  -0.019056;0.792709;0.609303;,
  -0.137123;0.629137;0.765104;,
  0.068836;0.889789;0.451151;,
  0.190021;0.941563;0.278122;,
  0.149886;0.962491;0.226155;,
  0.155846;0.965057;0.210656;,
  0.094180;-0.981750;-0.165216;,
  0.175262;-0.964791;-0.196118;,
  -0.000001;-0.989150;-0.146910;,
  0.175453;-0.972731;-0.151690;,
  0.197975;-0.971497;-0.130381;,
  0.201161;-0.977445;-0.064312;,
  0.232187;-0.972670;0.001295;,
  0.192198;-0.979364;0.062498;,
  0.155938;-0.967431;0.199401;,
  0.148817;-0.964015;0.220291;,
  0.083464;-0.905872;0.415247;,
  -0.114551;-0.902748;0.414638;,
  -0.145526;-0.898742;0.413624;,
  -0.144413;-0.963581;0.225069;,
  -0.155938;-0.967431;0.199401;,
  -0.192198;-0.979364;0.062498;,
  -0.232187;-0.972670;0.001295;,
  -0.201161;-0.977445;-0.064312;,
  -0.197975;-0.971497;-0.130381;,
  -0.175453;-0.972731;-0.151690;,
  -0.175260;-0.964791;-0.196118;,
  -0.094179;-0.981750;-0.165216;,
  0.000000;-1.000000;0.000000;,
  0.000000;-0.983042;-0.183379;,
  -0.041207;-0.946573;-0.319844;,
  -0.062132;-0.955359;-0.288840;,
  0.000000;-0.954010;-0.299776;,
  0.062132;-0.955359;-0.288840;,
  0.041207;-0.946573;-0.319844;;
  228;
  4;0,1,4,3;,
  4;1,2,5,4;,
  4;3,4,7,6;,
  4;4,5,8,7;,
  4;2,9,11,5;,
  4;9,10,12,11;,
  4;11,12,13,8;,
  4;10,14,16,12;,
  4;14,15,17,16;,
  4;12,16,18,13;,
  4;16,17,19,18;,
  4;15,20,22,17;,
  4;20,21,23,22;,
  4;17,22,24,19;,
  4;22,23,25,24;,
  4;21,26,28,23;,
  4;26,27,29,28;,
  4;23,28,30,25;,
  4;28,29,31,30;,
  4;27,32,34,29;,
  4;32,33,35,34;,
  4;29,34,36,31;,
  4;34,35,37,36;,
  4;33,38,40,35;,
  4;38,39,41,40;,
  4;35,40,42,37;,
  4;40,41,43,42;,
  4;39,44,46,41;,
  4;44,45,47,46;,
  4;41,46,48,43;,
  4;46,47,49,48;,
  4;156,50,52,156;,
  4;50,51,53,52;,
  4;47,52,54,49;,
  4;52,53,55,54;,
  4;51,56,58,53;,
  4;56,57,59,58;,
  4;53,58,60,55;,
  4;58,59,61,60;,
  4;57,62,64,59;,
  4;62,63,65,64;,
  4;59,64,66,61;,
  4;63,67,68,65;,
  4;67,0,3,68;,
  4;65,68,69,66;,
  4;68,3,6,69;,
  4;6,7,71,70;,
  4;7,8,72,71;,
  4;70,71,74,73;,
  4;71,72,75,74;,
  4;72,76,77,75;,
  4;13,18,79,76;,
  4;18,19,80,79;,
  4;76,79,81,78;,
  4;79,80,82,81;,
  4;19,24,83,80;,
  4;24,25,84,83;,
  4;80,83,85,82;,
  4;83,84,86,85;,
  4;25,30,87,84;,
  4;30,31,88,87;,
  4;84,87,89,86;,
  4;87,88,90,89;,
  4;31,36,91,88;,
  4;36,37,92,91;,
  4;88,91,93,90;,
  4;91,92,94,93;,
  4;37,42,95,92;,
  4;42,43,96,95;,
  4;92,95,97,94;,
  4;95,96,98,97;,
  4;43,48,99,96;,
  4;48,49,100,99;,
  4;96,99,101,98;,
  4;99,100,102,101;,
  4;49,54,103,100;,
  4;54,55,104,103;,
  4;100,103,105,157;,
  4;103,104,106,105;,
  4;55,60,107,104;,
  4;60,61,108,107;,
  4;104,107,109,106;,
  4;107,108,110,109;,
  4;108,111,113,112;,
  4;66,69,114,111;,
  4;69,6,70,114;,
  4;111,114,115,113;,
  4;114,70,73,115;,
  3;116,118,117;,
  3;118,158,117;,
  3;117,158,159;,
  3;118,160,158;,
  3;116,119,118;,
  3;119,161,118;,
  3;118,161,160;,
  3;119,162,161;,
  3;116,120,119;,
  3;120,14,119;,
  3;119,14,162;,
  3;120,15,14;,
  3;116,121,120;,
  3;121,20,120;,
  3;120,20,15;,
  3;121,163,164;,
  3;165,122,121;,
  3;122,166,121;,
  3;121,166,163;,
  3;167,168,167;,
  3;116,123,122;,
  3;123,169,122;,
  3;122,169,168;,
  3;123,170,169;,
  3;116,124,123;,
  3;124,171,123;,
  3;123,171,170;,
  3;124,172,171;,
  3;116,125,124;,
  3;125,173,124;,
  3;124,173,172;,
  3;125,174,173;,
  3;116,126,125;,
  3;126,175,125;,
  3;125,175,174;,
  3;126,176,175;,
  3;116,127,177;,
  3;127,178,177;,
  3;177,178,179;,
  3;127,180,178;,
  3;116,128,127;,
  3;128,181,127;,
  3;127,181,180;,
  3;128,182,181;,
  3;116,117,128;,
  3;117,183,128;,
  3;128,183,182;,
  3;117,159,183;,
  3;129,131,130;,
  3;131,184,130;,
  3;130,184,185;,
  3;131,186,184;,
  3;129,130,132;,
  3;130,187,132;,
  3;132,187,188;,
  3;130,185,187;,
  3;129,132,133;,
  3;132,189,133;,
  3;133,189,190;,
  3;132,188,189;,
  3;129,133,134;,
  3;133,191,134;,
  3;134,191,192;,
  3;133,190,191;,
  3;129,134,135;,
  3;134,193,135;,
  3;135,89,90;,
  3;134,192,89;,
  3;129,135,136;,
  3;135,194,136;,
  3;136,93,94;,
  3;135,90,93;,
  3;129,136,137;,
  3;136,195,137;,
  3;137,195,196;,
  3;136,94,97;,
  3;129,137,138;,
  3;137,197,138;,
  3;138,197,198;,
  3;137,98,101;,
  3;129,138,139;,
  3;138,199,139;,
  3;139,199,200;,
  3;138,198,199;,
  3;129,139,140;,
  3;139,201,140;,
  3;140,201,202;,
  3;139,200,201;,
  3;129,140,141;,
  3;140,203,141;,
  3;141,203,204;,
  3;140,202,203;,
  3;129,141,131;,
  3;141,205,131;,
  3;131,205,186;,
  3;141,204,205;,
  4;143,144,144,143;,
  4;144,145,145,144;,
  4;145,146,146,145;,
  4;146,147,147,146;,
  4;147,148,148,147;,
  4;148,149,149,148;,
  4;149,150,150,149;,
  4;150,151,151,150;,
  4;151,152,152,151;,
  4;152,153,153,152;,
  4;153,154,154,153;,
  4;154,143,143,154;,
  3;142,142,142;,
  3;142,142,142;,
  3;142,142,142;,
  3;142,142,142;,
  3;142,142,142;,
  3;142,142,142;,
  3;142,142,142;,
  3;142,142,142;,
  3;142,142,142;,
  3;142,142,142;,
  3;142,142,142;,
  3;142,142,142;,
  3;155,206,206;,
  3;155,206,206;,
  3;155,206,207;,
  3;155,207,208;,
  3;155,208,209;,
  3;155,209,210;,
  3;155,210,211;,
  3;155,211,212;,
  3;155,212,207;,
  3;155,207,206;,
  3;155,206,206;,
  3;155,206,206;,
  3;66,64,65;,
  3;66,111,108;,
  3;8,5,11;,
  3;8,76,72;,
  3;108,61,66;,
  3;108,112,110;,
  3;76,8,13;,
  3;76,78,77;;
 }
 MeshTextureCoords {
  251;
  0.000000;0.000000;,
  0.041670;0.000000;,
  0.041670;0.250000;,
  0.000000;0.250000;,
  0.083330;0.000000;,
  0.083330;0.250000;,
  0.041670;0.500000;,
  0.000000;0.500000;,
  0.083330;0.500000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.166670;0.000000;,
  0.166670;0.250000;,
  0.166670;0.500000;,
  0.125000;0.500000;,
  0.208330;0.000000;,
  0.208330;0.250000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.208330;0.500000;,
  0.250000;0.500000;,
  0.291670;0.000000;,
  0.291670;0.250000;,
  0.333330;0.000000;,
  0.333330;0.250000;,
  0.291670;0.500000;,
  0.333330;0.500000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.416670;0.000000;,
  0.416670;0.250000;,
  0.375000;0.500000;,
  0.416670;0.500000;,
  0.458330;0.000000;,
  0.458330;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.458330;0.500000;,
  0.500000;0.500000;,
  0.541670;0.000000;,
  0.541670;0.250000;,
  0.583330;0.000000;,
  0.583330;0.250000;,
  0.541670;0.500000;,
  0.583330;0.500000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.666670;0.000000;,
  0.666670;0.250000;,
  0.625000;0.500000;,
  0.666670;0.500000;,
  0.708330;0.000000;,
  0.708330;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.708330;0.500000;,
  0.750000;0.500000;,
  0.791670;0.000000;,
  0.791670;0.250000;,
  0.833330;0.000000;,
  0.833330;0.250000;,
  0.791670;0.500000;,
  0.833330;0.500000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.916670;0.000000;,
  0.916670;0.250000;,
  0.875000;0.500000;,
  0.958330;0.000000;,
  0.958330;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.958330;0.500000;,
  0.916670;0.500000;,
  1.000000;0.500000;,
  0.041670;0.750000;,
  0.000000;0.750000;,
  0.083330;0.750000;,
  0.041670;1.000000;,
  0.000000;1.000000;,
  0.083330;1.000000;,
  0.125000;0.750000;,
  0.125000;1.000000;,
  0.208330;0.750000;,
  0.166670;0.750000;,
  0.250000;0.750000;,
  0.208330;1.000000;,
  0.166670;1.000000;,
  0.250000;1.000000;,
  0.291670;0.750000;,
  0.333330;0.750000;,
  0.291670;1.000000;,
  0.333330;1.000000;,
  0.375000;0.750000;,
  0.416670;0.750000;,
  0.375000;1.000000;,
  0.416670;1.000000;,
  0.458330;0.750000;,
  0.500000;0.750000;,
  0.458330;1.000000;,
  0.500000;1.000000;,
  0.541670;0.750000;,
  0.583330;0.750000;,
  0.541670;1.000000;,
  0.583330;1.000000;,
  0.625000;0.750000;,
  0.666670;0.750000;,
  0.625000;1.000000;,
  0.666670;1.000000;,
  0.708330;0.750000;,
  0.750000;0.750000;,
  0.708330;1.000000;,
  0.750000;1.000000;,
  0.791670;0.750000;,
  0.833330;0.750000;,
  0.791670;1.000000;,
  0.833330;1.000000;,
  0.875000;0.750000;,
  0.916670;0.750000;,
  0.916670;1.000000;,
  0.875000;1.000000;,
  0.958330;0.750000;,
  1.000000;0.750000;,
  0.958330;1.000000;,
  1.000000;1.000000;,
  0.041670;0.000000;,
  0.062500;0.000000;,
  0.020830;0.000000;,
  0.125000;0.000000;,
  0.145830;0.000000;,
  0.104170;0.000000;,
  0.208330;0.000000;,
  0.229170;0.000000;,
  0.187500;0.000000;,
  0.291670;0.000000;,
  0.312500;0.000000;,
  0.270830;0.000000;,
  0.375000;0.000000;,
  0.395830;0.000000;,
  0.354170;0.000000;,
  0.458330;0.000000;,
  0.479170;0.000000;,
  0.437500;0.000000;,
  0.541670;0.000000;,
  0.562500;0.000000;,
  0.520830;0.000000;,
  0.625000;0.000000;,
  0.645830;0.000000;,
  0.604170;0.000000;,
  0.708330;0.000000;,
  0.729170;0.000000;,
  0.687500;0.000000;,
  0.791670;0.000000;,
  0.812500;0.000000;,
  0.770830;0.000000;,
  0.875000;0.000000;,
  0.895830;0.000000;,
  0.854170;0.000000;,
  0.958330;0.000000;,
  0.979170;0.000000;,
  0.937500;0.000000;,
  0.041670;1.000000;,
  0.020830;1.000000;,
  0.062500;1.000000;,
  0.125000;1.000000;,
  0.104170;1.000000;,
  0.145830;1.000000;,
  0.208330;1.000000;,
  0.187500;1.000000;,
  0.229170;1.000000;,
  0.291670;1.000000;,
  0.270830;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.354170;1.000000;,
  0.395830;1.000000;,
  0.458330;1.000000;,
  0.437500;1.000000;,
  0.479170;1.000000;,
  0.541670;1.000000;,
  0.520830;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.604170;1.000000;,
  0.645830;1.000000;,
  0.708330;1.000000;,
  0.687500;1.000000;,
  0.729170;1.000000;,
  0.791670;1.000000;,
  0.770830;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.854170;1.000000;,
  0.895830;1.000000;,
  0.958330;1.000000;,
  0.937500;1.000000;,
  0.979170;1.000000;,
  0.000000;0.000000;,
  0.083330;0.000000;,
  0.083330;1.000000;,
  0.000000;1.000000;,
  0.166670;0.000000;,
  0.166670;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.416670;0.000000;,
  0.416670;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.583330;0.000000;,
  0.583330;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.833330;0.000000;,
  0.833330;1.000000;,
  0.916670;0.000000;,
  0.916670;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.041670;0.000000;,
  0.125000;0.000000;,
  0.208330;0.000000;,
  0.291670;0.000000;,
  0.375000;0.000000;,
  0.458330;0.000000;,
  0.541670;0.000000;,
  0.625000;0.000000;,
  0.708330;0.000000;,
  0.791670;0.000000;,
  0.875000;0.000000;,
  0.958330;0.000000;,
  0.041670;1.000000;,
  0.125000;1.000000;,
  0.208330;1.000000;,
  0.291670;1.000000;,
  0.375000;1.000000;,
  0.458330;1.000000;,
  0.541670;1.000000;,
  0.625000;1.000000;,
  0.708330;1.000000;,
  0.791670;1.000000;,
  0.875000;1.000000;,
  0.958330;1.000000;,
  0.895840;0.500000;,
  0.104170;0.500000;,
  0.854160;0.750000;,
  0.145830;0.750000;;
 }
}
