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
 212;
 3.85800;-25.00674;-11.21403;,
 4.26430;-26.09624;-11.71671;,
 1.41114;-26.09624;-11.71671;,
 1.27570;-25.00674;-11.21403;,
 -1.44206;-26.09624;-11.71671;,
 -1.30662;-25.00674;-11.21403;,
 -4.29524;-26.09624;-11.71671;,
 -3.88892;-25.00674;-11.21403;,
 4.26430;-29.54440;-12.18679;,
 1.41114;-29.54440;-12.18679;,
 -1.44206;-29.54440;-12.18679;,
 -4.29524;-29.54440;-12.18679;,
 -3.88892;-25.00674;-11.21403;,
 -4.29524;-26.09624;-11.71671;,
 -4.29524;-26.09624;-6.62561;,
 -2.80248;-23.82740;-6.59513;,
 -4.29524;-26.09624;-2.45791;,
 -2.17654;-22.64806;-4.11657;,
 -4.29524;-26.09624;1.70979;,
 -2.17654;-21.46872;1.13975;,
 -4.29524;-26.09624;5.87753;,
 -3.88892;-24.37310;5.37483;,
 -4.29524;-29.54440;-12.18679;,
 -4.29524;-29.54440;-6.86065;,
 -4.29524;-29.54440;-2.45791;,
 -4.29524;-29.54440;1.94485;,
 -4.29524;-29.54440;6.34761;,
 -3.88892;-24.37310;5.37483;,
 -4.29524;-26.09624;5.87753;,
 -1.44206;-26.09624;5.87753;,
 -1.30662;-24.37310;5.37483;,
 1.41114;-26.09624;5.87753;,
 1.27570;-24.37310;5.37483;,
 4.26430;-26.09624;5.87753;,
 3.85800;-24.37310;5.37483;,
 -4.29524;-29.54440;6.34761;,
 -1.44206;-29.54440;6.34761;,
 1.41114;-29.54440;6.34761;,
 4.26430;-29.54440;6.34761;,
 3.85800;-24.37310;5.37483;,
 4.26430;-26.09624;5.87753;,
 4.26430;-26.09624;1.70979;,
 2.14562;-21.46872;1.13975;,
 4.26430;-26.09624;-2.45791;,
 2.14562;-22.64806;-4.11657;,
 4.26430;-26.09624;-6.62561;,
 2.77156;-23.82740;-6.59513;,
 4.26430;-26.09624;-11.71671;,
 3.85800;-25.00674;-11.21403;,
 4.26430;-29.54440;6.34761;,
 4.26430;-29.54440;1.94485;,
 4.26430;-29.54440;-2.45791;,
 4.26430;-29.54440;-6.86065;,
 4.26430;-29.54440;-12.18679;,
 2.14562;-21.46872;1.13975;,
 0.70492;-21.46872;1.13975;,
 1.27570;-24.37310;5.37483;,
 -0.73584;-21.46872;1.13975;,
 -1.30662;-24.37310;5.37483;,
 -2.17654;-21.46872;1.13975;,
 2.14562;-22.64806;-4.11657;,
 0.70492;-22.64806;-4.11657;,
 -0.73584;-22.64806;-4.11657;,
 -2.17654;-22.64806;-4.11657;,
 2.77156;-23.82740;-6.59513;,
 0.91354;-23.82740;-6.59513;,
 -0.94446;-23.82740;-6.59513;,
 -2.80248;-23.82740;-6.59513;,
 3.85800;-25.00674;-11.21403;,
 1.27570;-25.00674;-11.21403;,
 -1.30662;-25.00674;-11.21403;,
 -3.88892;-25.00674;-11.21403;,
 4.26430;-29.54440;1.94485;,
 1.41114;-29.54440;6.34761;,
 1.41114;-29.54440;1.94485;,
 -1.44206;-29.54440;6.34761;,
 -1.44206;-29.54440;1.94485;,
 -4.29524;-29.54440;1.94485;,
 4.26430;-29.54440;-2.45791;,
 1.41114;-29.54440;-2.45791;,
 -1.44206;-29.54440;-2.45791;,
 -4.29524;-29.54440;-2.45791;,
 4.26430;-29.54440;-6.86065;,
 1.41114;-29.54440;-6.86065;,
 -1.44206;-29.54440;-6.86065;,
 -4.29524;-29.54440;-6.86065;,
 4.26430;-29.54440;-12.18679;,
 1.41114;-29.54440;-12.18679;,
 -1.44206;-29.54440;-12.18679;,
 -4.29524;-29.54440;-12.18679;,
 2.27378;-2.95468;-0.54025;,
 2.27378;-2.95468;-2.05461;,
 -2.27510;-2.95468;-2.05461;,
 -2.27510;-2.95468;-0.54025;,
 1.88108;-5.18168;-4.08321;,
 1.96748;-8.31486;-5.33641;,
 -1.96884;-8.31486;-5.33641;,
 -1.88244;-5.18168;-4.08321;,
 1.57180;-11.44898;-3.78479;,
 -1.57316;-11.44898;-3.78479;,
 2.14444;-22.16454;-5.74705;,
 -2.14576;-22.16454;-5.74705;,
 2.68068;-23.69876;-2.05461;,
 2.68068;-23.69876;2.73773;,
 -2.68204;-23.69876;2.73773;,
 -2.68204;-23.69876;-2.05461;,
 2.14444;-22.16454;6.43017;,
 1.57180;-10.05296;5.06921;,
 -1.57316;-10.05296;5.06921;,
 -2.14576;-22.16454;6.43017;,
 1.96748;-6.91884;3.34285;,
 -1.96884;-6.91884;3.34285;,
 1.88108;-5.18168;1.48835;,
 -1.88244;-5.18168;1.48835;,
 -4.03302;-5.18168;-0.72405;,
 -4.03302;-5.18168;-1.87083;,
 -4.21816;-8.31486;-2.49743;,
 -4.21816;-6.91884;0.50385;,
 -3.37028;-11.44898;-1.72161;,
 -3.37028;-10.05296;3.00603;,
 -4.59728;-22.16454;-2.70275;,
 -4.59728;-22.16454;3.38587;,
 4.59596;-22.16454;3.38587;,
 4.59596;-22.16454;-2.70275;,
 3.36894;-11.44898;-1.72161;,
 3.36894;-10.05296;3.00603;,
 4.21682;-8.31486;-2.49743;,
 4.21682;-6.91884;0.50385;,
 4.03168;-5.18168;-1.87083;,
 4.03168;-5.18168;-0.72405;,
 2.27378;-2.95468;-2.05461;,
 -1.88244;-5.18168;-4.08321;,
 -2.27510;-2.95468;-2.05461;,
 2.14444;-22.16454;-5.74705;,
 -2.68204;-23.69876;-2.05461;,
 -2.14576;-22.16454;-5.74705;,
 1.88108;-5.18168;1.48835;,
 -2.27510;-2.95468;-0.54025;,
 -1.88244;-5.18168;1.48835;,
 2.68068;-23.69876;2.73773;,
 -2.14576;-22.16454;6.43017;,
 -2.68204;-23.69876;2.73773;,
 -4.03302;-5.18168;-1.87083;,
 -4.59728;-22.16454;3.38587;,
 -4.59728;-22.16454;-2.70275;,
 4.03168;-5.18168;-0.72405;,
 4.03168;-5.18168;-1.87083;,
 4.59596;-22.16454;-2.70275;,
 -3.37028;-11.44898;-1.72161;,
 -1.57316;-11.44898;-3.78479;,
 -4.21816;-8.31486;-2.49743;,
 -1.96884;-8.31486;-5.33641;,
 -1.57316;-10.05296;5.06921;,
 -3.37028;-10.05296;3.00603;,
 -1.96884;-6.91884;3.34285;,
 -4.21816;-6.91884;0.50385;,
 1.57180;-11.44898;-3.78479;,
 3.36894;-11.44898;-1.72161;,
 1.96748;-8.31486;-5.33641;,
 4.21682;-8.31486;-2.49743;,
 3.36894;-10.05296;3.00603;,
 1.57180;-10.05296;5.06921;,
 4.21682;-6.91884;0.50385;,
 1.96748;-6.91884;3.34285;,
 2.59868;0.21904;-2.05461;,
 2.59868;-4.23498;-2.05461;,
 -0.00068;-4.23498;-2.05461;,
 -0.00068;0.21904;-2.05461;,
 -2.60004;-4.23498;-2.05461;,
 -2.60004;0.21904;-2.05461;,
 2.59868;-8.68898;-2.05461;,
 -0.00068;-8.68898;-2.05461;,
 -2.60004;-8.68898;-2.05461;,
 -2.60004;0.21904;-2.05461;,
 -2.60004;-4.23498;-2.05461;,
 -2.60004;-4.23498;0.34157;,
 -2.60004;0.21904;0.34157;,
 -2.60004;-4.23498;2.73773;,
 -2.60004;0.21904;2.73773;,
 -2.60004;-8.68898;-2.05461;,
 -2.60004;-8.68898;0.34157;,
 -2.60004;-8.68898;2.73773;,
 -2.60004;0.21904;2.73773;,
 -2.60004;-4.23498;2.73773;,
 -0.00068;-4.23498;2.73773;,
 -0.00068;0.21904;2.73773;,
 2.59868;-4.23498;2.73773;,
 2.59868;0.21904;2.73773;,
 -2.60004;-8.68898;2.73773;,
 -0.00068;-8.68898;2.73773;,
 2.59868;-8.68898;2.73773;,
 2.59868;0.21904;2.73773;,
 2.59868;-4.23498;2.73773;,
 2.59868;-4.23498;0.34157;,
 2.59868;0.21904;0.34157;,
 2.59868;-4.23498;-2.05461;,
 2.59868;0.21904;-2.05461;,
 2.59868;-8.68898;2.73773;,
 2.59868;-8.68898;0.34157;,
 2.59868;-8.68898;-2.05461;,
 2.59868;0.21904;0.34157;,
 -0.00068;0.21904;0.34157;,
 -2.60004;0.21904;0.34157;,
 2.59868;0.21904;-2.05461;,
 -0.00068;0.21904;-2.05461;,
 -2.60004;0.21904;-2.05461;,
 2.59868;-8.68898;0.34157;,
 -0.00068;-8.68898;0.34157;,
 -2.60004;-8.68898;0.34157;,
 2.59868;-8.68898;-2.05461;,
 -0.00068;-8.68898;-2.05461;,
 -2.60004;-8.68898;-2.05461;;
 
 118;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;1,8,9,2;,
 4;2,9,10,4;,
 4;4,10,11,6;,
 4;12,13,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 4;13,22,23,14;,
 4;14,23,24,16;,
 4;16,24,25,18;,
 4;18,25,26,20;,
 4;27,28,29,30;,
 4;30,29,31,32;,
 4;32,31,33,34;,
 4;28,35,36,29;,
 4;29,36,37,31;,
 4;31,37,38,33;,
 4;39,40,41,42;,
 4;42,41,43,44;,
 4;44,43,45,46;,
 4;46,45,47,48;,
 4;40,49,50,41;,
 4;41,50,51,43;,
 4;43,51,52,45;,
 4;45,52,53,47;,
 4;39,54,55,56;,
 4;56,55,57,58;,
 4;58,57,59,21;,
 4;54,60,61,55;,
 4;55,61,62,57;,
 4;57,62,63,59;,
 4;60,64,65,61;,
 4;61,65,66,62;,
 4;62,66,67,63;,
 4;64,68,69,65;,
 4;65,69,70,66;,
 4;66,70,71,67;,
 4;72,49,73,74;,
 4;74,73,75,76;,
 4;76,75,26,77;,
 4;78,72,74,79;,
 4;79,74,76,80;,
 4;80,76,77,81;,
 4;82,78,79,83;,
 4;83,79,80,84;,
 4;84,80,81,85;,
 4;86,82,83,87;,
 4;87,83,84,88;,
 4;88,84,85,89;,
 4;90,91,92,93;,
 4;94,95,96,97;,
 4;95,98,99,96;,
 4;98,100,101,99;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;107,110,111,108;,
 4;110,112,113,111;,
 4;114,115,116,117;,
 4;117,116,118,119;,
 4;119,118,120,121;,
 4;122,123,124,125;,
 4;125,124,126,127;,
 4;127,126,128,129;,
 4;130,94,131,132;,
 4;133,102,134,135;,
 4;136,90,137,138;,
 4;139,106,140,141;,
 4;132,142,114,137;,
 4;141,143,144,134;,
 4;90,145,146,130;,
 4;102,147,122,139;,
 4;135,144,148,149;,
 4;149,148,150,151;,
 4;151,150,142,131;,
 4;152,153,143,140;,
 4;154,155,153,152;,
 4;138,114,155,154;,
 4;156,157,147,133;,
 4;158,159,157,156;,
 4;94,146,159,158;,
 4;106,122,160,161;,
 4;161,160,162,163;,
 4;163,162,145,136;,
 3;132,131,142;,
 3;94,130,146;,
 3;135,134,144;,
 3;138,137,114;,
 3;102,133,147;,
 3;141,140,143;,
 3;90,136,145;,
 3;106,139,122;,
 4;164,165,166,167;,
 4;167,166,168,169;,
 4;165,170,171,166;,
 4;166,171,172,168;,
 4;173,174,175,176;,
 4;176,175,177,178;,
 4;174,179,180,175;,
 4;175,180,181,177;,
 4;182,183,184,185;,
 4;185,184,186,187;,
 4;183,188,189,184;,
 4;184,189,190,186;,
 4;191,192,193,194;,
 4;194,193,195,196;,
 4;192,197,198,193;,
 4;193,198,199,195;,
 4;191,200,201,185;,
 4;185,201,202,178;,
 4;200,203,204,201;,
 4;201,204,205,202;,
 4;206,197,189,207;,
 4;207,189,181,208;,
 4;209,206,207,210;,
 4;210,207,208,211;;
 
 MeshMaterialList {
  22;
  118;
  11,
  0,
  11,
  9,
  0,
  9,
  11,
  11,
  11,
  11,
  9,
  9,
  9,
  9,
  11,
  0,
  11,
  9,
  9,
  9,
  11,
  11,
  11,
  11,
  9,
  9,
  9,
  9,
  11,
  0,
  11,
  11,
  11,
  11,
  11,
  0,
  11,
  11,
  0,
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
  11,
  0,
  0,
  0,
  4,
  11,
  10,
  0,
  11,
  11,
  11,
  11,
  11,
  11,
  0,
  4,
  11,
  4,
  11,
  4,
  11,
  4,
  11,
  11,
  11,
  11,
  10,
  10,
  11,
  11,
  11,
  11,
  10,
  10,
  11,
  11,
  4,
  10,
  4,
  4,
  10,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
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
  87;
  0.000000;0.768533;-0.639810;,
  0.000000;0.768533;-0.639810;,
  0.000000;0.280090;-0.959974;,
  0.000000;0.280090;-0.959974;,
  0.000000;0.135078;-0.990835;,
  0.000000;0.135078;-0.990835;,
  -0.870314;0.492444;0.007226;,
  -0.870138;0.491627;-0.034097;,
  -0.921285;0.385687;-0.049795;,
  -0.967078;0.254453;0.003734;,
  -0.967033;0.254042;-0.017619;,
  -0.980175;0.196504;-0.025370;,
  -1.000000;0.000000;0.000000;,
  -0.946612;0.319200;-0.045128;,
  0.000000;0.586527;0.809930;,
  -0.986563;0.161774;-0.022872;,
  0.000000;0.208142;0.978099;,
  0.000000;0.208142;0.978099;,
  0.000000;0.135078;0.990835;,
  0.921287;0.385681;-0.049796;,
  0.870140;0.491623;-0.034097;,
  0.870318;0.492437;0.007227;,
  0.000000;0.208142;0.978099;,
  0.980175;0.196501;-0.025370;,
  0.967033;0.254040;-0.017619;,
  0.967079;0.254449;0.003734;,
  1.000000;0.000000;0.000000;,
  0.000000;0.981965;0.189063;,
  0.000000;0.945258;-0.326325;,
  0.000000;0.945258;-0.326325;,
  0.000000;0.940380;-0.340127;,
  0.000000;-1.000000;-0.000000;,
  0.421390;0.812617;0.402597;,
  -0.421388;0.812619;0.402595;,
  0.421389;0.812617;-0.402597;,
  -0.421387;0.812619;-0.402595;,
  0.374227;0.468741;-0.800148;,
  -0.374228;0.468743;-0.800146;,
  0.426805;-0.062572;-0.902176;,
  -0.426807;-0.062572;-0.902175;,
  0.424472;-0.136450;-0.895101;,
  -0.424474;-0.136450;-0.895100;,
  0.417043;0.181535;-0.890573;,
  -0.417044;0.181534;-0.890573;,
  0.298256;-0.931515;-0.208140;,
  -0.298260;-0.931514;-0.208141;,
  0.298256;-0.931515;0.208140;,
  -0.298260;-0.931514;0.208141;,
  0.420298;0.117554;0.899739;,
  -0.420299;0.117553;0.899739;,
  0.417983;0.267087;0.868306;,
  -0.417985;0.267086;0.868305;,
  0.375406;0.549607;0.746326;,
  -0.375408;0.549606;0.746326;,
  0.338788;0.636720;0.692684;,
  -0.338789;0.636721;0.692682;,
  -0.831594;0.456731;0.315987;,
  -0.922393;0.178361;0.342605;,
  -0.931955;0.067117;0.356307;,
  -0.861719;-0.405041;0.305584;,
  -0.859930;0.371473;-0.350039;,
  -0.942744;-0.081300;-0.323457;,
  -0.943757;-0.089936;-0.318172;,
  -0.864286;-0.392392;-0.314703;,
  0.861717;-0.405045;0.305584;,
  0.931954;0.067118;0.356309;,
  0.922392;0.178363;0.342607;,
  0.831595;0.456729;0.315989;,
  0.864284;-0.392396;-0.314703;,
  0.943757;-0.089936;-0.318174;,
  0.942743;-0.081300;-0.323459;,
  0.859931;0.371471;-0.350041;,
  0.000000;0.000000;-1.000000;,
  0.000000;-0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  -0.891642;0.451854;0.028332;,
  -0.972533;0.232308;0.014566;,
  0.946615;0.319193;-0.045130;,
  0.986563;0.161770;-0.022872;,
  0.972535;0.232302;0.014567;,
  0.891647;0.451844;0.028334;,
  0.000000;0.981965;0.189063;,
  0.000000;0.940380;-0.340127;,
  0.253192;-0.879789;-0.402325;,
  -0.253195;-0.879787;-0.402327;,
  0.253192;-0.879789;0.402325;,
  -0.253195;-0.879787;0.402327;;
  118;
  4;0,2,3,1;,
  4;1,3,3,1;,
  4;1,3,2,0;,
  4;2,4,5,3;,
  4;3,5,5,3;,
  4;3,5,4,2;,
  4;75,76,9,6;,
  4;6,9,10,7;,
  4;7,10,11,8;,
  4;8,11,15,13;,
  4;76,12,12,9;,
  4;9,12,12,10;,
  4;10,12,12,11;,
  4;11,12,12,15;,
  4;14,22,16,14;,
  4;14,16,17,14;,
  4;14,17,22,14;,
  4;22,18,18,16;,
  4;16,18,18,17;,
  4;17,18,18,22;,
  4;77,78,23,19;,
  4;19,23,24,20;,
  4;20,24,25,21;,
  4;21,25,79,80;,
  4;78,26,26,23;,
  4;23,26,26,24;,
  4;24,26,26,25;,
  4;25,26,26,79;,
  4;14,27,27,14;,
  4;14,27,27,14;,
  4;14,27,81,14;,
  4;27,28,28,27;,
  4;27,28,29,27;,
  4;27,29,28,81;,
  4;28,82,30,28;,
  4;28,30,30,29;,
  4;29,30,82,28;,
  4;82,0,1,30;,
  4;30,1,1,30;,
  4;30,1,0,82;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;32,34,35,33;,
  4;36,38,39,37;,
  4;38,40,41,39;,
  4;40,42,43,41;,
  4;44,46,47,45;,
  4;48,50,51,49;,
  4;50,52,53,51;,
  4;52,54,55,53;,
  4;56,60,61,57;,
  4;57,61,62,58;,
  4;58,62,63,59;,
  4;64,68,69,65;,
  4;65,69,70,66;,
  4;66,70,71,67;,
  4;34,36,37,35;,
  4;83,44,45,84;,
  4;54,32,33,55;,
  4;46,85,86,47;,
  4;35,60,56,33;,
  4;47,59,63,45;,
  4;32,67,71,34;,
  4;44,68,64,46;,
  4;43,63,62,41;,
  4;41,62,61,39;,
  4;39,61,60,37;,
  4;51,58,59,49;,
  4;53,57,58,51;,
  4;55,56,57,53;,
  4;40,69,68,42;,
  4;38,70,69,40;,
  4;36,71,70,38;,
  4;48,64,65,50;,
  4;50,65,66,52;,
  4;52,66,67,54;,
  3;35,37,60;,
  3;36,34,71;,
  3;84,45,63;,
  3;55,33,56;,
  3;44,83,68;,
  3;47,86,59;,
  3;32,54,67;,
  3;85,46,64;,
  4;72,72,72,72;,
  4;72,72,72,72;,
  4;72,72,72,72;,
  4;72,72,72,72;,
  4;12,12,12,12;,
  4;12,12,12,12;,
  4;12,12,12,12;,
  4;12,12,12,12;,
  4;73,73,73,73;,
  4;73,73,73,73;,
  4;73,73,73,73;,
  4;73,73,73,73;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;26,26,26,26;,
  4;74,74,74,74;,
  4;74,74,74,74;,
  4;74,74,74,74;,
  4;74,74,74,74;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;,
  4;31,31,31,31;;
 }
 MeshTextureCoords {
  212;
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.333330;0.000000;,
  0.666670;0.500000;,
  0.666670;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.250000;0.000000;,
  0.500000;0.500000;,
  0.500000;0.000000;,
  0.750000;0.500000;,
  0.750000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.333330;0.000000;,
  0.666670;0.500000;,
  0.666670;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.250000;0.000000;,
  0.500000;0.500000;,
  0.500000;0.000000;,
  0.750000;0.500000;,
  0.750000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.500000;1.000000;,
  0.750000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.250000;,
  0.333330;0.250000;,
  0.333330;0.000000;,
  0.666670;0.250000;,
  0.666670;0.000000;,
  1.000000;0.250000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.666670;0.500000;,
  1.000000;0.500000;,
  0.000000;0.750000;,
  0.333330;0.750000;,
  0.666670;0.750000;,
  1.000000;0.750000;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.750000;,
  0.333330;1.000000;,
  0.333330;0.750000;,
  0.666670;1.000000;,
  0.666670;0.750000;,
  1.000000;0.750000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.666670;0.500000;,
  1.000000;0.500000;,
  0.000000;0.250000;,
  0.333330;0.250000;,
  0.666670;0.250000;,
  1.000000;0.250000;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.666670;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  1.000000;1.000000;,
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
  0.333330;1.000000;,
  0.333330;0.000000;,
  0.666670;1.000000;,
  0.666670;0.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;;
 }
}
