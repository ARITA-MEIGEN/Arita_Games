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
 266;
 0.00458;14.66320;7.88695;,
 1.39785;10.34645;-0.62522;,
 0.04761;11.28772;-0.52835;,
 0.00458;14.66320;7.88695;,
 2.43909;10.62396;1.03601;,
 0.00458;14.66320;7.88695;,
 2.17475;10.19009;3.15838;,
 0.00458;14.66320;7.88695;,
 0.00478;11.68081;4.24036;,
 3.09903;8.32227;-2.71060;,
 0.05618;10.23212;-2.59985;,
 5.03733;8.63972;0.78355;,
 3.31898;9.59748;4.95175;,
 -0.02112;10.62836;6.56608;,
 3.54217;7.14885;-2.19909;,
 0.09173;8.02602;-6.49742;,
 7.30158;9.05522;3.10534;,
 4.69581;8.49794;5.22780;,
 -0.06297;6.60551;6.97996;,
 5.96734;7.19418;0.85595;,
 0.01794;6.63051;-8.07868;,
 4.11307;6.56113;5.28221;,
 -0.06602;5.19352;7.97893;,
 -0.01857;7.06661;0.92979;,
 -0.01857;7.06661;0.92979;,
 -0.01857;7.06661;0.92979;,
 0.01136;10.54364;1.40149;,
 1.35368;9.80576;2.38844;,
 0.00817;10.14976;-0.77528;,
 0.01136;10.54364;1.40149;,
 1.48131;10.14976;1.40149;,
 0.01136;10.54364;1.40149;,
 1.35368;10.14976;2.94070;,
 0.01136;10.54364;1.40149;,
 0.00817;10.14976;3.57823;,
 2.46051;9.02828;-1.44259;,
 0.01594;8.49554;-2.62064;,
 3.45981;9.02828;1.40149;,
 2.46051;9.02828;4.24555;,
 0.00817;9.02826;5.42362;,
 3.20009;7.34970;-2.31446;,
 0.00817;7.34970;-3.85369;,
 4.50570;7.34970;1.40149;,
 3.20009;7.34970;5.11744;,
 0.00817;7.34970;6.65665;,
 3.45981;6.34601;-2.62064;,
 0.00817;6.88767;-4.72590;,
 4.60170;6.90542;1.40149;,
 3.25929;5.36979;5.42362;,
 0.00817;5.36978;7.08963;,
 3.17448;2.70516;-1.78298;,
 0.05949;0.12176;-3.87722;,
 4.21774;3.38984;1.40149;,
 3.19956;2.91612;5.11798;,
 0.00817;3.38984;6.65665;,
 1.82626;1.71131;-1.44259;,
 0.00817;2.11133;-1.97009;,
 2.99497;1.71131;1.40149;,
 2.46051;1.71131;4.24555;,
 0.00817;1.71128;5.42362;,
 1.03089;0.58977;-0.13772;,
 0.00817;0.58973;-0.77528;,
 1.89447;0.58977;1.40149;,
 1.35368;0.58977;2.94070;,
 0.00817;0.58973;3.57823;,
 0.00817;0.19592;1.40149;,
 0.00817;0.19592;1.40149;,
 0.00817;0.19592;1.40149;,
 0.00817;0.19592;1.40149;,
 0.00817;-1.10178;3.02314;,
 1.60638;0.48519;4.62680;,
 0.00817;0.15192;5.32431;,
 0.00817;-1.10178;3.02314;,
 2.28441;-0.07641;2.93230;,
 0.00817;-1.10178;3.02314;,
 1.57290;-0.58687;1.23344;,
 0.00817;-1.10178;3.02314;,
 0.00817;-1.24188;1.45645;,
 1.85118;1.71671;6.46319;,
 0.00817;3.22748;8.32651;,
 3.52552;0.67895;3.33217;,
 3.02691;-0.03738;-0.48034;,
 0.00817;-1.07236;-0.69794;,
 2.97459;4.78754;7.00842;,
 0.00817;7.11703;8.46465;,
 4.07865;2.21033;3.42811;,
 3.07023;0.97797;-1.18388;,
 0.00817;-0.02061;-2.34797;,
 3.66708;8.28030;5.82471;,
 0.00817;9.89652;7.53683;,
 4.54467;4.27394;0.66635;,
 3.17448;2.70516;-1.78298;,
 0.05949;0.12176;-3.87722;,
 0.00817;4.32110;0.58838;,
 0.00817;4.32110;0.58838;,
 0.00817;4.32110;0.58838;,
 0.00817;4.32110;0.58838;,
 0.00458;14.66320;7.88695;,
 0.04761;11.28772;-0.52835;,
 -1.31432;10.37889;-0.66008;,
 0.00458;14.66320;7.88695;,
 -2.39397;10.66922;0.98738;,
 0.00458;14.66320;7.88695;,
 -2.16945;10.22176;3.12431;,
 0.00458;14.66320;7.88695;,
 0.00478;11.68081;4.24036;,
 0.05618;10.23212;-2.59985;,
 -3.02073;8.38188;-2.77469;,
 -5.01674;8.71308;0.70469;,
 -3.35017;9.64604;4.89945;,
 -0.02112;10.62836;6.56608;,
 0.09173;8.02602;-6.49742;,
 -3.48687;7.22564;-2.28166;,
 -7.30158;9.16725;2.98496;,
 -4.77128;8.56694;5.15355;,
 -0.06297;6.60551;6.97996;,
 0.01794;6.63051;-7.65359;,
 -5.99289;7.28680;0.75638;,
 -4.21750;6.63798;5.19964;,
 -0.06602;5.19352;7.91509;,
 -0.01857;7.06661;0.92979;,
 -0.01857;7.06661;0.92979;,
 -0.01857;7.06661;0.92979;,
 0.01136;10.54364;1.40149;,
 0.00817;10.14976;-0.77528;,
 -1.33734;9.80576;2.38844;,
 0.01136;10.54364;1.40149;,
 -1.45863;10.14976;1.40149;,
 0.01136;10.54364;1.40149;,
 -1.33734;10.14976;2.94070;,
 0.01136;10.54364;1.40149;,
 0.00817;10.14976;3.57823;,
 0.01594;8.49554;-2.62064;,
 -2.44419;9.02828;-1.44259;,
 -3.44346;9.02828;1.40149;,
 -2.44419;9.02828;4.24555;,
 0.00817;9.02826;5.42362;,
 0.00817;7.34970;-3.85369;,
 -3.18375;7.34970;-2.31446;,
 -4.48937;7.34970;1.40149;,
 -2.50419;7.34970;5.11744;,
 0.00817;7.34970;6.65665;,
 0.00817;6.88767;-4.72590;,
 -3.44346;6.34601;-2.62064;,
 -4.58538;6.90542;1.40149;,
 -3.24294;5.36979;5.42362;,
 0.00817;5.36978;7.08963;,
 -3.16152;2.91612;-1.78298;,
 -4.20141;3.38984;1.40149;,
 -3.18375;3.38984;5.11744;,
 0.00817;3.38984;6.65665;,
 0.00817;2.11133;-1.97009;,
 -2.10339;1.71131;-1.44259;,
 -2.97864;1.71131;1.40149;,
 -2.44419;1.71131;4.24555;,
 0.00817;1.71128;5.42362;,
 0.00817;0.58973;-0.77528;,
 -1.15035;0.58977;-0.13772;,
 -1.87815;0.58977;1.40149;,
 -1.33734;0.58977;2.94070;,
 0.00817;0.58973;3.57823;,
 0.00817;0.19592;1.40149;,
 0.00817;0.19592;1.40149;,
 0.00817;0.19592;1.40149;,
 0.00817;0.19592;1.40149;,
 0.00817;-1.10178;3.02314;,
 0.00817;0.15192;5.32431;,
 -1.59003;0.48519;4.62680;,
 0.00817;-1.10178;3.02314;,
 -2.26809;-0.07641;2.93230;,
 0.00817;-1.10178;3.02314;,
 -1.55657;-0.58687;1.23344;,
 0.00817;-1.10178;3.02314;,
 0.00817;-1.24188;1.45645;,
 0.00817;3.22748;8.32651;,
 -1.83483;1.71671;6.46319;,
 -3.50919;0.67895;3.33217;,
 -3.01057;-0.03738;-0.48034;,
 0.00817;-1.07236;-0.69794;,
 0.00817;7.11703;8.46465;,
 -2.95827;4.78754;7.00842;,
 -4.06230;2.21033;2.26894;,
 -3.05391;0.97797;-1.18388;,
 0.00817;-0.02061;-2.34797;,
 0.00817;9.89652;7.53683;,
 -3.65075;8.28030;5.82471;,
 -4.52835;4.27394;0.66635;,
 -3.16152;2.91612;-1.78298;,
 0.00817;4.32110;0.58838;,
 0.00817;4.32110;0.58838;,
 0.00817;4.32110;0.58838;,
 0.00817;4.32110;0.58838;,
 -5.54481;5.19992;1.65146;,
 -5.07255;3.97958;-0.69416;,
 -5.03038;2.27154;0.48247;,
 -5.50265;3.49193;2.82808;,
 -4.57011;3.95372;-0.94397;,
 -4.52795;2.24570;0.23266;,
 -4.06767;3.92789;-1.19377;,
 -4.02551;2.21984;-0.01714;,
 -4.06767;3.92789;-1.19377;,
 -3.71445;6.69308;3.23975;,
 -3.30648;4.52709;4.77696;,
 -4.02551;2.21984;-0.01714;,
 -3.71445;6.69308;3.23975;,
 -4.32783;6.72462;3.54472;,
 -3.85887;4.55867;5.08191;,
 -3.30648;4.52709;4.77696;,
 -4.94121;6.75619;3.84968;,
 -4.41125;4.59029;5.38686;,
 -5.55459;6.78775;4.15462;,
 -4.96364;4.62183;5.69180;,
 -5.55459;6.78775;4.15462;,
 -5.54481;5.19992;1.65146;,
 -5.50265;3.49193;2.82808;,
 -4.96364;4.62183;5.69180;,
 -4.94121;6.75619;3.84968;,
 -5.07255;3.97958;-0.69416;,
 -5.54481;5.19992;1.65146;,
 -4.32783;6.72462;3.54472;,
 -4.57011;3.95372;-0.94397;,
 -4.06767;3.92789;-1.19377;,
 -5.50265;3.49193;2.82808;,
 -5.03038;2.27154;0.48247;,
 -4.41125;4.59029;5.38686;,
 -4.52795;2.24570;0.23266;,
 -3.85887;4.55867;5.08191;,
 -4.02551;2.21984;-0.01714;,
 5.55777;5.19992;1.65146;,
 5.51562;3.49193;2.82808;,
 5.04334;2.27154;0.48247;,
 5.08551;3.97958;-0.69416;,
 4.54091;2.24570;0.23266;,
 4.58307;3.95372;-0.94397;,
 4.03847;2.21984;-0.01714;,
 4.08063;3.92789;-1.19377;,
 4.08063;3.92789;-1.19377;,
 4.03847;2.21984;-0.01714;,
 3.31944;4.52709;4.77696;,
 3.72743;6.69308;3.23975;,
 3.72743;6.69308;3.23975;,
 3.31944;4.52709;4.77696;,
 3.87183;4.55867;5.08191;,
 4.34079;6.72462;3.54472;,
 4.42421;4.59029;5.38686;,
 4.95417;6.75619;3.84968;,
 4.97659;4.62183;5.69180;,
 5.56755;6.78775;4.15462;,
 5.56755;6.78775;4.15462;,
 4.97659;4.62183;5.69180;,
 5.51562;3.49193;2.82808;,
 5.55777;5.19992;1.65146;,
 5.55777;5.19992;1.65146;,
 5.08551;3.97958;-0.69416;,
 4.95417;6.75619;3.84968;,
 4.58307;3.95372;-0.94397;,
 4.34079;6.72462;3.54472;,
 4.08063;3.92789;-1.19377;,
 5.51562;3.49193;2.82808;,
 4.42421;4.59029;5.38686;,
 5.04334;2.27154;0.48247;,
 3.87183;4.55867;5.08191;,
 4.54091;2.24570;0.23266;,
 4.03847;2.21984;-0.01714;,
 0.01794;6.63051;-7.65359;,
 0.01794;6.63051;-8.07868;;
 
 170;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 4;2,1,9,10;,
 4;1,4,11,9;,
 4;4,6,12,11;,
 4;6,8,13,12;,
 4;10,9,14,15;,
 4;9,11,16,14;,
 4;11,12,17,16;,
 4;12,13,18,17;,
 4;14,16,19,20;,
 4;16,17,21,19;,
 4;17,18,22,21;,
 3;23,20,19;,
 3;24,19,21;,
 3;25,21,22;,
 3;26,27,28;,
 3;29,30,27;,
 3;31,32,30;,
 3;33,34,32;,
 4;28,27,35,36;,
 4;27,30,37,35;,
 4;30,32,38,37;,
 4;32,34,39,38;,
 4;36,35,40,41;,
 4;35,37,42,40;,
 4;37,38,43,42;,
 4;38,39,44,43;,
 4;41,40,45,46;,
 4;40,42,47,45;,
 4;42,43,48,47;,
 4;43,44,49,48;,
 4;46,45,50,51;,
 4;45,47,52,50;,
 4;47,48,53,52;,
 4;48,49,54,53;,
 4;51,50,55,56;,
 4;50,52,57,55;,
 4;52,53,58,57;,
 4;53,54,59,58;,
 4;56,55,60,61;,
 4;55,57,62,60;,
 4;57,58,63,62;,
 4;58,59,64,63;,
 3;61,60,65;,
 3;60,62,66;,
 3;62,63,67;,
 3;63,64,68;,
 3;69,70,71;,
 3;72,73,70;,
 3;74,75,73;,
 3;76,77,75;,
 4;71,70,78,79;,
 4;70,73,80,78;,
 4;73,75,81,80;,
 4;75,77,82,81;,
 4;79,78,83,84;,
 4;78,80,85,83;,
 4;80,81,86,85;,
 4;81,82,87,86;,
 4;84,83,88,89;,
 4;83,85,90,88;,
 4;85,86,91,90;,
 4;86,87,92,91;,
 3;93,89,88;,
 3;94,88,90;,
 3;95,90,91;,
 3;96,91,92;,
 3;97,98,99;,
 3;100,99,101;,
 3;102,101,103;,
 3;104,103,105;,
 4;98,106,107,99;,
 4;99,107,108,101;,
 4;101,108,109,103;,
 4;103,109,110,105;,
 4;106,111,112,107;,
 4;107,112,113,108;,
 4;108,113,114,109;,
 4;109,114,115,110;,
 4;112,116,117,113;,
 4;113,117,118,114;,
 4;114,118,119,115;,
 3;120,117,116;,
 3;121,118,117;,
 3;122,119,118;,
 3;123,124,125;,
 3;126,125,127;,
 3;128,127,129;,
 3;130,129,131;,
 4;124,132,133,125;,
 4;125,133,134,127;,
 4;127,134,135,129;,
 4;129,135,136,131;,
 4;132,137,138,133;,
 4;133,138,139,134;,
 4;134,139,140,135;,
 4;135,140,141,136;,
 4;137,142,143,138;,
 4;138,143,144,139;,
 4;139,144,145,140;,
 4;140,145,146,141;,
 4;142,51,147,143;,
 4;143,147,148,144;,
 4;144,148,149,145;,
 4;145,149,150,146;,
 4;51,151,152,147;,
 4;147,152,153,148;,
 4;148,153,154,149;,
 4;149,154,155,150;,
 4;151,156,157,152;,
 4;152,157,158,153;,
 4;153,158,159,154;,
 4;154,159,160,155;,
 3;156,161,157;,
 3;157,162,158;,
 3;158,163,159;,
 3;159,164,160;,
 3;165,166,167;,
 3;168,167,169;,
 3;170,169,171;,
 3;172,171,173;,
 4;166,174,175,167;,
 4;167,175,176,169;,
 4;169,176,177,171;,
 4;171,177,178,173;,
 4;174,179,180,175;,
 4;175,180,181,176;,
 4;176,181,182,177;,
 4;177,182,183,178;,
 4;179,184,185,180;,
 4;180,185,186,181;,
 4;181,186,187,182;,
 4;182,187,92,183;,
 3;188,185,184;,
 3;189,186,185;,
 3;190,187,186;,
 3;191,92,187;,
 4;192,193,194,195;,
 4;193,196,197,194;,
 4;196,198,199,197;,
 4;200,201,202,203;,
 4;204,205,206,207;,
 4;205,208,209,206;,
 4;208,210,211,209;,
 4;212,213,214,215;,
 4;212,216,217,218;,
 4;216,219,220,217;,
 4;219,201,221,220;,
 4;222,223,224,215;,
 4;223,225,226,224;,
 4;225,227,202,226;,
 4;228,229,230,231;,
 4;231,230,232,233;,
 4;233,232,234,235;,
 4;236,237,238,239;,
 4;240,241,242,243;,
 4;243,242,244,245;,
 4;245,244,246,247;,
 4;248,249,250,251;,
 4;248,252,253,254;,
 4;254,253,255,256;,
 4;256,255,257,239;,
 4;258,249,259,260;,
 4;260,259,261,262;,
 4;262,261,238,263;,
 3;264,112,111;,
 3;265,15,14;;
 
 MeshMaterialList {
  22;
  170;
  0,
  11,
  0,
  4,
  9,
  11,
  11,
  0,
  11,
  9,
  11,
  4,
  0,
  4,
  0,
  3,
  3,
  11,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  4,
  4,
  0,
  0,
  0,
  0,
  0,
  0,
  11,
  11,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  10,
  10,
  11,
  11,
  0,
  10,
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
  0,
  11,
  0,
  4,
  9,
  11,
  11,
  0,
  11,
  9,
  11,
  4,
  0,
  4,
  0,
  3,
  3,
  11,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  4,
  4,
  0,
  0,
  0,
  0,
  0,
  0,
  11,
  11,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  10,
  10,
  11,
  11,
  0,
  10,
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
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  9,
  11,
  11;;
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
  218;
  0.680020;0.708334;-0.189303;,
  0.511998;0.785276;-0.348137;,
  0.476861;0.798227;-0.368017;,
  0.650682;0.747548;-0.133356;,
  0.703760;0.687977;0.177225;,
  -0.211239;-0.756619;0.618794;,
  0.606359;0.623858;-0.493082;,
  0.615014;0.614926;-0.493583;,
  0.541270;0.811942;-0.218579;,
  0.430687;0.893512;0.127063;,
  0.459975;0.620410;0.635228;,
  0.705900;0.470471;-0.529492;,
  0.686542;0.494584;-0.532960;,
  0.569111;0.733149;-0.372297;,
  0.229458;0.972102;0.048645;,
  0.341597;0.252661;0.905248;,
  0.671576;0.556229;-0.489485;,
  0.617848;0.607281;-0.499473;,
  0.338505;-0.940962;-0.002022;,
  0.367511;0.243313;0.897627;,
  0.064261;-0.991422;-0.113812;,
  0.309988;0.950582;0.017362;,
  0.433375;0.859243;-0.271823;,
  -0.242732;-0.905863;-0.347122;,
  0.288981;0.933242;0.213423;,
  0.165932;0.922534;0.348421;,
  0.300638;0.764072;-0.570799;,
  0.253263;0.796215;-0.549454;,
  -0.541487;0.701657;-0.463108;,
  0.521512;0.727988;0.445039;,
  0.307468;0.703192;0.641081;,
  0.356095;0.619229;-0.699823;,
  0.652733;0.536969;-0.534419;,
  0.925867;0.377807;0.005784;,
  0.694422;0.373528;0.615024;,
  0.408927;0.368734;0.834754;,
  0.526809;0.247285;-0.813217;,
  0.795924;0.166604;-0.582021;,
  0.998560;0.053376;0.005345;,
  0.758429;0.020521;0.651432;,
  0.441440;0.007103;0.897263;,
  0.914952;-0.403433;-0.010213;,
  0.708092;-0.410801;0.574324;,
  0.381048;-0.403670;0.831777;,
  0.159917;-0.875668;0.455666;,
  0.480973;-0.854023;-0.198266;,
  0.715751;-0.697002;-0.043452;,
  0.535140;-0.736282;0.414143;,
  0.276006;-0.734445;0.620010;,
  0.164926;-0.886020;-0.433322;,
  0.307724;-0.891154;-0.333392;,
  0.453449;-0.890079;-0.046292;,
  0.312403;-0.917836;0.244912;,
  0.165929;-0.922560;0.348355;,
  0.152101;-0.988308;-0.010583;,
  0.395767;-0.878536;0.267475;,
  0.373952;-0.927307;0.016149;,
  0.316978;-0.788698;0.526765;,
  0.351540;-0.802250;0.482509;,
  0.418777;-0.866850;0.270549;,
  0.407363;-0.911548;0.055987;,
  0.388920;-0.848679;-0.358448;,
  0.394122;-0.495746;0.773889;,
  0.512241;-0.560327;0.650879;,
  0.724409;-0.637242;0.262973;,
  0.608169;-0.768816;-0.197618;,
  0.503853;-0.646157;-0.573248;,
  0.511469;0.019930;0.859071;,
  0.742896;-0.092420;0.662996;,
  0.964764;-0.239961;0.107933;,
  0.776011;-0.484813;-0.403439;,
  0.522699;0.223169;0.822789;,
  0.805930;0.101814;0.583190;,
  0.986871;-0.161489;0.002496;,
  0.803045;-0.404494;-0.437611;,
  -0.013186;0.785735;-0.618423;,
  -0.662732;0.721572;-0.200299;,
  -0.487331;0.796282;-0.358392;,
  -0.454995;0.806988;-0.376496;,
  -0.637061;0.757452;-0.142899;,
  -0.696086;0.698296;0.166873;,
  0.190906;-0.759838;0.621450;,
  -0.582262;0.634644;-0.508131;,
  -0.593225;0.627122;-0.504779;,
  -0.522913;0.821894;-0.225948;,
  -0.418080;0.900401;0.120363;,
  -0.460353;0.627993;0.627455;,
  -0.691004;0.457967;-0.559268;,
  -0.676951;0.480389;-0.557641;,
  -0.563259;0.727620;-0.391546;,
  -0.210335;0.976653;0.043688;,
  -0.354006;0.247745;0.901833;,
  -0.676594;0.513412;-0.527853;,
  -0.634977;0.557298;-0.534998;,
  -0.354449;-0.935046;-0.007403;,
  -0.382137;0.226627;0.895886;,
  -0.078986;-0.990373;-0.113676;,
  -0.308969;0.950914;0.017346;,
  -0.431961;0.860087;-0.271402;,
  0.242859;-0.906354;-0.345748;,
  -0.288831;0.933425;0.212823;,
  -0.165877;0.922586;0.348310;,
  -0.299929;0.764424;-0.570700;,
  -0.251873;0.796069;-0.550304;,
  0.545740;0.697626;-0.464204;,
  -0.548944;0.685982;0.477586;,
  -0.338649;0.675052;0.655455;,
  -0.355563;0.619791;-0.699596;,
  -0.652509;0.537318;-0.534342;,
  -0.919814;0.387931;0.058757;,
  -0.677759;0.366044;0.637695;,
  -0.450485;0.364993;0.814766;,
  -0.526096;0.241703;-0.815354;,
  -0.795563;0.162401;-0.583700;,
  -0.995375;0.089534;0.034812;,
  -0.742582;0.071778;0.665898;,
  -0.467323;0.034985;0.883394;,
  -0.929662;-0.368410;-0.001674;,
  -0.719516;-0.375255;0.584363;,
  -0.408928;-0.368734;0.834753;,
  -0.278266;-0.898528;0.339434;,
  -0.518855;-0.827602;-0.214160;,
  -0.742904;-0.669082;-0.020581;,
  -0.558628;-0.705797;0.435644;,
  -0.307479;-0.703185;0.641083;,
  -0.145025;-0.889541;-0.433225;,
  -0.300917;-0.900317;-0.314448;,
  -0.453853;-0.890690;-0.026256;,
  -0.312402;-0.917836;0.244913;,
  -0.165927;-0.922560;0.348355;,
  -0.148916;-0.988831;-0.006156;,
  -0.395764;-0.878537;0.267476;,
  -0.373949;-0.927308;0.016149;,
  -0.316978;-0.788698;0.526764;,
  -0.351538;-0.802249;0.482511;,
  -0.418775;-0.866850;0.270550;,
  -0.407361;-0.911550;0.055986;,
  -0.388917;-0.848681;-0.358448;,
  -0.394120;-0.495747;0.773889;,
  -0.545023;-0.546605;0.635746;,
  -0.746925;-0.623394;0.231263;,
  -0.601277;-0.773262;-0.201326;,
  -0.509592;-0.627966;-0.588195;,
  -0.511466;0.019930;0.859072;,
  -0.768224;-0.078387;0.635364;,
  -0.970614;-0.229353;0.072837;,
  -0.772950;-0.479820;-0.415115;,
  0.602637;-0.400727;-0.690106;,
  -0.522697;0.223171;0.822790;,
  -0.809924;0.083835;0.580513;,
  -0.984581;-0.174878;-0.004316;,
  -0.812217;-0.378303;-0.444061;,
  0.024493;0.795798;-0.605067;,
  -0.995779;-0.091251;-0.009887;,
  -0.783776;-0.365325;-0.502228;,
  -0.400029;-0.526609;-0.750106;,
  -0.400017;-0.526611;-0.750112;,
  0.992391;0.019506;-0.121570;,
  0.400823;0.586496;0.703821;,
  0.398638;0.593784;0.698934;,
  0.397519;0.597392;0.696492;,
  0.995779;-0.091248;-0.009889;,
  0.783776;-0.365324;-0.502230;,
  0.400029;-0.526609;-0.750106;,
  0.400017;-0.526611;-0.750112;,
  -0.992391;0.019509;-0.121570;,
  -0.400825;0.586496;0.703820;,
  -0.398638;0.593784;0.698934;,
  -0.397519;0.597392;0.696492;,
  0.500510;0.838697;0.214654;,
  0.315405;0.261802;0.912129;,
  0.733660;-0.562556;0.381146;,
  0.288811;-0.951010;0.110312;,
  0.021880;-0.998587;0.048430;,
  0.149556;-0.955842;-0.252979;,
  0.099092;0.987030;-0.126303;,
  0.758890;0.649825;0.042577;,
  -0.060760;-0.910867;0.408202;,
  0.206777;-0.725644;-0.656265;,
  0.051605;0.778916;-0.625001;,
  0.035174;0.785186;-0.618261;,
  0.018428;0.814893;-0.579318;,
  -0.061851;0.784430;-0.617125;,
  -0.540310;-0.010306;-0.841403;,
  -0.491544;0.845922;0.206883;,
  -0.325423;0.268548;0.906632;,
  -0.749059;-0.550625;0.368406;,
  -0.305524;-0.946146;0.107060;,
  -0.038248;-0.997989;0.050542;,
  -0.163638;-0.952580;-0.256544;,
  -0.097350;0.987017;-0.127749;,
  -0.781407;0.619563;0.074465;,
  -0.181505;-0.732252;-0.656401;,
  -0.035174;0.785186;-0.618261;,
  -0.051605;0.778916;-0.625001;,
  -0.018166;0.832865;-0.553178;,
  0.084790;0.803422;-0.589342;,
  0.185021;0.716974;-0.672098;,
  0.401889;0.582816;0.706266;,
  -0.991168;-0.062661;0.116871;,
  -0.269518;0.819317;-0.506043;,
  -0.239027;0.828705;-0.506078;,
  -0.208306;0.837247;-0.505595;,
  -0.208320;0.837244;-0.505593;,
  0.003209;-0.919409;0.393290;,
  0.083780;-0.912370;0.400703;,
  0.164189;-0.898927;0.406168;,
  0.164580;-0.898542;0.406862;,
  -0.401893;0.582816;0.706263;,
  0.991169;-0.062657;0.116871;,
  0.269518;0.819317;-0.506043;,
  0.239027;0.828705;-0.506078;,
  0.208307;0.837246;-0.505595;,
  0.208322;0.837244;-0.505593;,
  -0.003211;-0.919409;0.393289;,
  -0.083781;-0.912370;0.400703;,
  -0.164189;-0.898927;0.406168;,
  -0.164580;-0.898542;0.406862;;
  170;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;5,5,5;,
  4;1,2,7,6;,
  4;2,3,8,7;,
  4;3,4,9,8;,
  4;4,169,10,9;,
  4;6,7,12,11;,
  4;7,8,13,12;,
  4;8,9,14,13;,
  4;170,10,15,15;,
  4;12,13,17,16;,
  4;171,171,18,172;,
  4;15,15,19,19;,
  3;20,173,172;,
  3;20,172,18;,
  3;20,18,174;,
  3;21,22,22;,
  3;23,23,23;,
  3;21,24,175;,
  3;21,25,24;,
  4;22,22,27,26;,
  4;28,175,28,27;,
  4;175,24,29,176;,
  4;24,25,30,29;,
  4;26,27,32,31;,
  4;27,176,33,32;,
  4;176,29,34,33;,
  4;29,30,35,34;,
  4;31,32,37,36;,
  4;32,33,38,37;,
  4;33,34,39,38;,
  4;34,35,40,39;,
  4;36,37,74,147;,
  4;37,38,41,74;,
  4;38,39,42,41;,
  4;39,40,43,42;,
  4;177,44,45,44;,
  4;74,41,46,45;,
  4;41,42,47,46;,
  4;42,43,48,47;,
  4;178,45,50,49;,
  4;45,46,51,50;,
  4;46,47,52,51;,
  4;47,48,53,52;,
  3;49,50,54;,
  3;50,51,54;,
  3;51,52,54;,
  3;52,53,54;,
  3;55,58,57;,
  3;55,59,58;,
  3;55,60,59;,
  3;55,56,60;,
  4;57,58,63,62;,
  4;58,59,64,63;,
  4;59,60,65,64;,
  4;60,56,61,65;,
  4;62,63,68,67;,
  4;63,64,69,68;,
  4;64,65,70,69;,
  4;65,61,66,70;,
  4;67,68,72,71;,
  4;68,69,73,72;,
  4;69,70,74,73;,
  4;70,66,147,74;,
  3;75,179,180;,
  3;75,180,181;,
  3;75,181,182;,
  3;75,182,183;,
  3;76,77,78;,
  3;76,78,79;,
  3;76,79,80;,
  3;81,81,81;,
  4;77,82,83,78;,
  4;78,83,84,79;,
  4;79,84,85,80;,
  4;80,85,86,184;,
  4;82,87,88,83;,
  4;83,88,89,84;,
  4;84,89,90,85;,
  4;185,91,91,86;,
  4;88,92,93,89;,
  4;186,187,94,186;,
  4;91,95,95,91;,
  3;96,187,188;,
  3;96,94,187;,
  3;96,189,94;,
  3;97,98,98;,
  3;99,99,99;,
  3;97,190,100;,
  3;97,100,101;,
  4;98,102,103,98;,
  4;104,103,104,190;,
  4;190,191,105,100;,
  4;100,105,106,101;,
  4;102,107,108,103;,
  4;103,108,109,191;,
  4;191,109,110,105;,
  4;105,110,111,106;,
  4;107,112,113,108;,
  4;108,113,114,109;,
  4;109,114,115,110;,
  4;110,115,116,111;,
  4;112,183,151,113;,
  4;113,151,117,114;,
  4;114,117,118,115;,
  4;115,118,119,116;,
  4;177,120,121,120;,
  4;151,121,122,117;,
  4;117,122,123,118;,
  4;118,123,124,119;,
  4;192,125,126,121;,
  4;121,126,127,122;,
  4;122,127,128,123;,
  4;123,128,129,124;,
  3;125,130,126;,
  3;126,130,127;,
  3;127,130,128;,
  3;128,130,129;,
  3;131,133,134;,
  3;131,134,135;,
  3;131,135,136;,
  3;131,136,132;,
  4;133,138,139,134;,
  4;134,139,140,135;,
  4;135,140,141,136;,
  4;136,141,137,132;,
  4;138,143,144,139;,
  4;139,144,145,140;,
  4;140,145,146,141;,
  4;141,146,142,137;,
  4;143,148,149,144;,
  4;144,149,150,145;,
  4;145,150,151,146;,
  4;146,151,183,142;,
  3;152,193,194;,
  3;152,195,193;,
  3;152,196,195;,
  3;152,197,196;,
  4;153,154,154,153;,
  4;154,155,155,154;,
  4;155,156,156,155;,
  4;157,157,157,157;,
  4;198,158,158,198;,
  4;158,159,159,158;,
  4;159,160,160,159;,
  4;199,153,153,199;,
  4;200,201,201,200;,
  4;201,202,202,201;,
  4;202,203,203,202;,
  4;204,205,205,204;,
  4;205,206,206,205;,
  4;206,207,207,206;,
  4;161,161,162,162;,
  4;162,162,163,163;,
  4;163,163,164,164;,
  4;165,165,165,165;,
  4;208,208,166,166;,
  4;166,166,167,167;,
  4;167,167,168,168;,
  4;209,209,161,161;,
  4;210,210,211,211;,
  4;211,211,212,212;,
  4;212,212,213,213;,
  4;214,214,215,215;,
  4;215,215,216,216;,
  4;216,216,217,217;,
  3;92,88,87;,
  3;16,11,12;;
 }
 MeshTextureCoords {
  266;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.250000;0.500000;,
  0.125000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.187500;0.625000;,
  0.312500;0.625000;,
  0.437500;0.625000;,
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.500000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.625000;0.250000;,
  0.500000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.625000;0.375000;,
  0.500000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.625000;0.500000;,
  0.500000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.562500;0.625000;,
  0.687500;0.625000;,
  0.812500;0.625000;,
  0.937500;0.625000;,
  0.062500;0.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.187500;0.625000;,
  0.312500;0.625000;,
  0.437500;0.625000;,
  0.062500;0.000000;,
  0.000000;0.125000;,
  0.125000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.000000;0.375000;,
  0.125000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.125000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.000000;0.875000;,
  0.125000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;0.000000;,
  0.500000;0.125000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  0.562500;0.625000;,
  0.687500;0.625000;,
  0.812500;0.625000;,
  0.937500;0.625000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.000000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;,
  0.062500;0.500000;,
  0.062500;0.500000;;
 }
}
