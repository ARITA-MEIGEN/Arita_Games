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
 200;
 1.72600;-0.00674;-1.41203;,
 2.10502;-1.43850;-1.97647;,
 0.65810;-1.43850;-2.26363;,
 0.67870;-0.00674;-1.63057;,
 -0.78884;-1.43850;-2.26363;,
 -1.01234;-0.00674;-1.63057;,
 -2.23576;-1.43850;-1.97647;,
 -2.46266;-0.00674;-1.41203;,
 2.72148;-3.40720;-2.56709;,
 0.91282;-3.40720;-2.92603;,
 -0.89582;-3.40720;-2.92603;,
 -2.70450;-3.40720;-2.56709;,
 2.72148;-5.19692;-2.56709;,
 0.91282;-5.19692;-2.92603;,
 -0.89582;-5.19692;-2.92603;,
 -2.34984;-4.80758;-2.56709;,
 -2.46266;-0.00674;-1.41203;,
 -2.23576;-1.43850;-1.97647;,
 -2.57584;-1.43850;-0.40151;,
 -2.83068;-0.00674;-0.21337;,
 -2.57584;-1.43850;1.17345;,
 -2.83068;-0.00674;0.98531;,
 -2.23576;-1.43850;2.74841;,
 -2.46266;-0.00674;2.18397;,
 -2.70450;-3.40720;-2.56709;,
 -3.12024;-3.40720;-0.59837;,
 -3.12024;-3.40720;1.37031;,
 -2.70450;-3.40720;3.33903;,
 -2.34984;-4.80758;-2.56709;,
 -2.70830;-4.80758;-0.59837;,
 -2.70830;-4.80758;1.37031;,
 -2.34984;-4.80758;3.03701;,
 -2.46266;-0.00674;2.18397;,
 -2.23576;-1.43850;2.74841;,
 -0.78884;-1.43850;3.03557;,
 -1.01234;-0.00674;2.40253;,
 0.65810;-1.43850;3.03557;,
 0.67870;-0.00674;2.40253;,
 2.10502;-1.43850;2.74841;,
 1.72600;-0.00674;2.18397;,
 -2.70450;-3.40720;3.33903;,
 -0.89582;-3.40720;3.69797;,
 0.91282;-3.40720;3.69797;,
 2.72148;-3.40720;3.33903;,
 -2.34984;-4.80758;3.03701;,
 -0.54116;-4.80758;3.35923;,
 0.91282;-5.19692;3.35923;,
 2.72148;-5.19692;3.03701;,
 1.72600;-0.00674;2.18397;,
 2.10502;-1.43850;2.74841;,
 2.46552;-1.43850;1.17345;,
 2.03406;-0.00674;0.98531;,
 2.46552;-1.43850;-0.40151;,
 2.03406;-0.00674;-0.21337;,
 2.10502;-1.43850;-1.97647;,
 1.72600;-0.00674;-1.41203;,
 2.72148;-3.40720;3.33903;,
 3.18148;-3.40720;1.37031;,
 3.18148;-3.40720;-0.59837;,
 2.72148;-3.40720;-2.56709;,
 2.72148;-5.19692;3.03701;,
 3.18148;-5.19692;1.37031;,
 3.18148;-5.19692;-0.59837;,
 2.72148;-5.19692;-2.56709;,
 2.03406;-0.00674;0.98531;,
 0.81770;-0.00674;1.05817;,
 0.67870;-0.00674;2.40253;,
 -1.14628;-0.00674;1.05817;,
 -1.01234;-0.00674;2.40253;,
 -2.83068;-0.00674;0.98531;,
 2.03406;-0.00674;-0.21337;,
 0.81770;-0.00674;-0.28623;,
 -1.14628;-0.00674;-0.28623;,
 -2.83068;-0.00674;-0.21337;,
 1.72600;-0.00674;-1.41203;,
 0.67870;-0.00674;-1.63057;,
 -1.01234;-0.00674;-1.63057;,
 -2.46266;-0.00674;-1.41203;,
 3.18148;-5.19692;1.37031;,
 0.91282;-5.19692;3.35923;,
 1.08090;-5.19692;1.48997;,
 -0.54116;-4.80758;3.35923;,
 -0.60772;-4.80758;1.48997;,
 -2.70830;-4.80758;1.37031;,
 3.18148;-5.19692;-0.59837;,
 1.08090;-5.19692;-0.71803;,
 -0.60772;-4.80758;-0.71803;,
 -2.70830;-4.80758;-0.59837;,
 2.72148;-5.19692;-2.56709;,
 0.91282;-5.19692;-2.92603;,
 -0.89582;-5.19692;-2.92603;,
 -2.34984;-4.80758;-2.56709;,
 2.83434;-2.49710;-2.34141;,
 3.24470;-5.21996;-2.34141;,
 1.00600;-5.62122;-2.34141;,
 1.00600;-2.49710;-2.34141;,
 2.59878;-8.05822;-2.34141;,
 0.96838;-6.27590;-2.34141;,
 0.53608;-9.74706;-2.34141;,
 -0.19854;-8.83508;-2.34141;,
 1.00600;-2.49710;-2.34141;,
 1.00600;-5.62122;-2.34141;,
 1.00600;-5.62122;-0.18637;,
 1.00600;-2.49710;-0.18637;,
 0.96838;-6.27590;-2.34141;,
 0.96838;-6.27590;-0.18637;,
 -0.19854;-8.83508;-2.34141;,
 -0.19854;-8.83508;-0.18637;,
 1.00600;-2.49710;-0.18637;,
 1.00600;-5.62122;-0.18637;,
 3.24470;-5.21996;-0.18637;,
 2.83434;-2.49710;-0.18637;,
 0.96838;-6.27590;-0.18637;,
 2.59878;-8.05822;-0.18637;,
 -0.19854;-8.83508;-0.18637;,
 0.53608;-9.74706;-0.18637;,
 2.83434;-2.49710;-0.18637;,
 3.24470;-5.21996;-0.18637;,
 3.24470;-5.21996;-2.34141;,
 2.83434;-2.49710;-2.34141;,
 2.59878;-8.05822;-0.18637;,
 2.59878;-8.05822;-2.34141;,
 0.53608;-9.74706;-0.18637;,
 0.53608;-9.74706;-2.34141;,
 2.83434;-2.49710;-2.34141;,
 1.00600;-2.49710;-2.34141;,
 0.53608;-9.74706;-2.34141;,
 -0.19854;-8.83508;-2.34141;,
 2.59768;-2.04666;0.48075;,
 3.00800;-4.76956;0.48075;,
 0.76936;-5.17074;0.48075;,
 0.76936;-2.04666;0.48075;,
 2.36210;-7.60780;0.48075;,
 0.73174;-5.82552;0.48075;,
 0.29942;-9.29658;0.48075;,
 -0.43518;-8.38462;0.48075;,
 0.76936;-2.04666;0.48075;,
 0.76936;-5.17074;0.48075;,
 0.76936;-5.17074;2.63583;,
 0.76936;-2.04666;2.63583;,
 0.73174;-5.82552;0.48075;,
 0.73174;-5.82552;2.63583;,
 -0.43518;-8.38462;0.48075;,
 -0.43518;-8.38462;2.63583;,
 0.76936;-2.04666;2.63583;,
 0.76936;-5.17074;2.63583;,
 3.00800;-4.76956;2.63583;,
 2.59768;-2.04666;2.63583;,
 0.73174;-5.82552;2.63583;,
 2.36210;-7.60780;2.63583;,
 -0.43518;-8.38462;2.63583;,
 0.29942;-9.29658;2.63583;,
 2.59768;-2.04666;2.63583;,
 3.00800;-4.76956;2.63583;,
 3.00800;-4.76956;0.48075;,
 2.59768;-2.04666;0.48075;,
 2.36210;-7.60780;2.63583;,
 2.36210;-7.60780;0.48075;,
 0.29942;-9.29658;2.63583;,
 0.29942;-9.29658;0.48075;,
 2.59768;-2.04666;0.48075;,
 0.76936;-2.04666;0.48075;,
 0.29942;-9.29658;0.48075;,
 -0.43518;-8.38462;0.48075;,
 -2.25802;-3.13516;-1.48989;,
 -0.83472;-3.73352;-1.48989;,
 -1.49132;-5.81710;-1.48989;,
 -3.14972;-4.81690;-1.48989;,
 -1.59968;-6.26612;-1.48989;,
 -3.24344;-6.92124;-1.48989;,
 -1.22908;-8.35476;-1.48989;,
 -1.99264;-8.72260;-1.48989;,
 -0.83472;-3.73352;-1.48989;,
 -0.83472;-3.73352;0.23417;,
 -1.49132;-5.81710;0.23417;,
 -1.49132;-5.81710;-1.48989;,
 -1.59968;-6.26612;0.23417;,
 -1.59968;-6.26612;-1.48989;,
 -1.22908;-8.35476;0.23417;,
 -1.22908;-8.35476;-1.48989;,
 -0.83472;-3.73352;0.23417;,
 -2.25802;-3.13516;0.23417;,
 -3.14972;-4.81690;0.23417;,
 -1.49132;-5.81710;0.23417;,
 -3.24344;-6.92124;0.23417;,
 -1.59968;-6.26612;0.23417;,
 -1.99264;-8.72260;0.23417;,
 -1.22908;-8.35476;0.23417;,
 -2.25802;-3.13516;0.23417;,
 -2.25802;-3.13516;-1.48989;,
 -3.14972;-4.81690;-1.48989;,
 -3.14972;-4.81690;0.23417;,
 -3.24344;-6.92124;-1.48989;,
 -3.24344;-6.92124;0.23417;,
 -1.99264;-8.72260;-1.48989;,
 -1.99264;-8.72260;0.23417;,
 -0.83472;-3.73352;-1.48989;,
 -2.25802;-3.13516;-1.48989;,
 -1.99264;-8.72260;-1.48989;,
 -1.22908;-8.35476;-1.48989;;
 
 96;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;1,8,9,2;,
 4;2,9,10,4;,
 4;4,10,11,6;,
 4;8,12,13,9;,
 4;9,13,14,10;,
 4;10,14,15,11;,
 4;16,17,18,19;,
 4;19,18,20,21;,
 4;21,20,22,23;,
 4;17,24,25,18;,
 4;18,25,26,20;,
 4;20,26,27,22;,
 4;24,28,29,25;,
 4;25,29,30,26;,
 4;26,30,31,27;,
 4;32,33,34,35;,
 4;35,34,36,37;,
 4;37,36,38,39;,
 4;33,40,41,34;,
 4;34,41,42,36;,
 4;36,42,43,38;,
 4;40,44,45,41;,
 4;41,45,46,42;,
 4;42,46,47,43;,
 4;48,49,50,51;,
 4;51,50,52,53;,
 4;53,52,54,55;,
 4;49,56,57,50;,
 4;50,57,58,52;,
 4;52,58,59,54;,
 4;56,60,61,57;,
 4;57,61,62,58;,
 4;58,62,63,59;,
 4;48,64,65,66;,
 4;66,65,67,68;,
 4;68,67,69,23;,
 4;64,70,71,65;,
 4;65,71,72,67;,
 4;67,72,73,69;,
 4;70,74,75,71;,
 4;71,75,76,72;,
 4;72,76,77,73;,
 4;78,60,79,80;,
 4;80,79,81,82;,
 4;82,81,31,83;,
 4;84,78,80,85;,
 4;85,80,82,86;,
 4;86,82,83,87;,
 4;88,84,85,89;,
 4;89,85,86,90;,
 4;90,86,87,91;,
 4;92,93,94,95;,
 4;93,96,97,94;,
 4;96,98,99,97;,
 4;100,101,102,103;,
 4;101,104,105,102;,
 4;104,106,107,105;,
 4;108,109,110,111;,
 4;109,112,113,110;,
 4;112,114,115,113;,
 4;116,117,118,119;,
 4;117,120,121,118;,
 4;120,122,123,121;,
 4;116,124,125,103;,
 4;126,122,107,127;,
 4;128,129,130,131;,
 4;129,132,133,130;,
 4;132,134,135,133;,
 4;136,137,138,139;,
 4;137,140,141,138;,
 4;140,142,143,141;,
 4;144,145,146,147;,
 4;145,148,149,146;,
 4;148,150,151,149;,
 4;152,153,154,155;,
 4;153,156,157,154;,
 4;156,158,159,157;,
 4;152,160,161,139;,
 4;162,158,143,163;,
 4;164,165,166,167;,
 4;167,166,168,169;,
 4;169,168,170,171;,
 4;172,173,174,175;,
 4;175,174,176,177;,
 4;177,176,178,179;,
 4;180,181,182,183;,
 4;183,182,184,185;,
 4;185,184,186,187;,
 4;188,189,190,191;,
 4;191,190,192,193;,
 4;193,192,194,195;,
 4;188,173,196,197;,
 4;198,199,178,195;;
 
 MeshMaterialList {
  22;
  96;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
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
  103;
  0.182984;0.398165;-0.898878;,
  0.091881;0.402982;-0.910584;,
  -0.080422;0.383071;-0.920211;,
  0.183316;0.366660;-0.912116;,
  0.092072;0.365903;-0.926087;,
  -0.086521;0.352763;-0.931704;,
  0.191834;0.169831;-0.966622;,
  0.096299;0.166476;-0.981332;,
  -0.102361;0.157248;-0.982240;,
  0.194660;0.000000;-0.980871;,
  0.097799;0.000000;-0.995206;,
  -0.109246;-0.012392;-0.993938;,
  -0.160284;0.359088;-0.919437;,
  -0.982106;-0.139387;-0.126645;,
  -0.982106;-0.139387;0.126645;,
  -0.172318;0.340840;-0.924194;,
  -0.990764;0.069877;-0.116206;,
  -0.990764;0.069877;0.116206;,
  -0.203896;0.151252;-0.967238;,
  -0.994887;0.001673;-0.100980;,
  -0.994486;-0.003361;0.104813;,
  -0.217167;-0.024634;-0.975824;,
  -0.957761;-0.271930;-0.093531;,
  -0.954189;-0.281782;0.100608;,
  -0.962666;-0.101122;0.251096;,
  -0.080425;0.383062;0.920215;,
  0.091885;0.402973;0.910587;,
  -0.968826;0.091837;0.230090;,
  -0.086523;0.352758;0.931706;,
  0.092074;0.365899;0.926089;,
  -0.977991;0.001476;0.208641;,
  -0.101360;0.044070;0.993873;,
  0.088699;0.070237;0.993579;,
  -0.939341;-0.278498;0.200195;,
  -0.102081;-0.237175;0.966089;,
  0.079109;-0.192965;0.978011;,
  0.182993;0.398159;0.898879;,
  0.945596;0.305214;0.112656;,
  0.945596;0.305214;-0.112656;,
  0.183320;0.366657;0.912116;,
  0.938699;0.326917;0.109402;,
  0.938699;0.326917;-0.109402;,
  0.189074;0.083509;0.978405;,
  0.978025;0.172445;0.117176;,
  0.977793;0.177088;-0.112073;,
  0.182222;-0.173226;0.967878;,
  0.992189;-0.009671;0.124370;,
  0.993421;0.000000;-0.114516;,
  0.000000;1.000000;0.000000;,
  -0.117408;-0.993083;-0.001383;,
  -0.084964;-0.996090;0.024199;,
  -0.111302;-0.992575;0.049063;,
  0.000000;0.000000;-1.000000;,
  -1.000000;0.000000;0.000000;,
  -0.999588;0.028696;0.000000;,
  -0.970715;0.240233;0.000000;,
  -0.909876;0.414880;0.000000;,
  0.000000;-0.000000;1.000000;,
  -0.999588;0.028692;0.000000;,
  -0.970715;0.240234;0.000000;,
  -0.909871;0.414891;0.000000;,
  0.953763;-0.300560;-0.000000;,
  0.963493;-0.267733;-0.000000;,
  0.999532;-0.030590;-0.000000;,
  0.984620;0.174707;0.000000;,
  -0.962666;-0.101122;-0.251096;,
  -0.968826;0.091837;-0.230090;,
  -0.979565;0.011471;-0.200802;,
  -0.947686;-0.259245;-0.186234;,
  -0.160291;0.359081;0.919439;,
  -0.172322;0.340836;0.924195;,
  -0.189723;0.031497;0.981332;,
  -0.178586;-0.262182;0.948350;,
  0.921326;0.317894;0.223835;,
  0.916943;0.334564;0.217445;,
  0.916943;0.334564;-0.217445;,
  0.921326;0.317894;-0.223835;,
  0.957670;0.168983;0.233052;,
  0.958391;0.178423;-0.222829;,
  0.968877;-0.019191;0.246797;,
  0.973772;0.000000;-0.227526;,
  0.000000;-1.000000;-0.000000;,
  -0.121757;-0.992556;-0.002768;,
  -0.052732;-0.997372;0.049683;,
  -0.056853;-0.997215;0.048277;,
  -0.109289;-0.989197;0.097695;,
  -0.105188;-0.989502;0.099104;,
  0.988833;0.149026;0.000000;,
  0.999312;-0.037082;-0.000000;,
  0.850298;-0.526302;-0.000000;,
  0.633502;-0.773741;-0.000000;,
  -0.778767;-0.627314;0.000000;,
  0.988836;0.149010;0.000000;,
  0.999312;-0.037088;-0.000000;,
  0.850296;-0.526305;-0.000000;,
  0.633492;-0.773749;-0.000000;,
  -0.778768;-0.627312;0.000000;,
  -0.883491;0.468449;0.000000;,
  -0.964825;0.262894;0.000000;,
  -0.960719;-0.277521;0.000000;,
  -0.821401;-0.570351;0.000000;,
  0.387548;0.921849;0.000000;,
  0.434007;-0.900909;-0.000000;;
  96;
  4;0,3,4,1;,
  4;1,4,5,2;,
  4;2,5,15,12;,
  4;3,6,7,4;,
  4;4,7,8,5;,
  4;5,8,18,15;,
  4;6,9,10,7;,
  4;7,10,11,8;,
  4;8,11,21,18;,
  4;65,66,16,13;,
  4;13,16,17,14;,
  4;14,17,27,24;,
  4;66,67,19,16;,
  4;16,19,20,17;,
  4;17,20,30,27;,
  4;67,68,22,19;,
  4;19,22,23,20;,
  4;20,23,33,30;,
  4;69,70,28,25;,
  4;25,28,29,26;,
  4;26,29,39,36;,
  4;70,71,31,28;,
  4;28,31,32,29;,
  4;29,32,42,39;,
  4;71,72,34,31;,
  4;31,34,35,32;,
  4;32,35,45,42;,
  4;73,74,40,37;,
  4;37,40,41,38;,
  4;38,41,75,76;,
  4;74,77,43,40;,
  4;40,43,44,41;,
  4;41,44,78,75;,
  4;77,79,46,43;,
  4;43,46,47,44;,
  4;44,47,80,78;,
  4;48,48,48,48;,
  4;48,48,48,48;,
  4;48,48,48,48;,
  4;48,48,48,48;,
  4;48,48,48,48;,
  4;48,48,48,48;,
  4;48,48,48,48;,
  4;48,48,48,48;,
  4;48,48,48,48;,
  4;81,81,82,49;,
  4;49,82,82,49;,
  4;49,82,81,81;,
  4;81,81,49,50;,
  4;50,49,49,51;,
  4;51,49,81,83;,
  4;81,81,50,84;,
  4;84,50,51,85;,
  4;85,51,83,86;,
  4;52,52,52,52;,
  4;52,52,52,52;,
  4;52,52,52,52;,
  4;53,54,54,53;,
  4;54,55,55,54;,
  4;55,56,56,55;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;87,88,88,87;,
  4;88,89,89,88;,
  4;89,90,90,89;,
  4;48,48,48,48;,
  4;91,91,91,91;,
  4;52,52,52,52;,
  4;52,52,52,52;,
  4;52,52,52,52;,
  4;53,58,58,53;,
  4;58,59,59,58;,
  4;59,60,60,59;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;92,93,93,92;,
  4;93,94,94,93;,
  4;94,95,95,94;,
  4;48,48,48,48;,
  4;96,96,96,96;,
  4;52,52,52,52;,
  4;52,52,52,52;,
  4;52,52,52,52;,
  4;61,61,62,62;,
  4;62,62,63,63;,
  4;63,63,64,64;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;57,57,57,57;,
  4;97,97,98,98;,
  4;98,98,99,99;,
  4;99,99,100,100;,
  4;101,101,101,101;,
  4;102,102,102,102;;
 }
 MeshTextureCoords {
  200;
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.333330;0.000000;,
  0.666670;0.333330;,
  0.666670;0.000000;,
  1.000000;0.333330;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  0.333330;1.000000;,
  0.666670;1.000000;,
  1.000000;1.000000;,
  0.000000;0.666670;,
  0.333330;1.000000;,
  0.333330;0.666670;,
  0.666670;1.000000;,
  0.666670;0.666670;,
  1.000000;0.666670;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.666670;0.333330;,
  1.000000;0.333330;,
  0.000000;0.000000;,
  0.333330;0.000000;,
  0.666670;0.000000;,
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
  0.000000;0.333330;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
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
  0.000000;0.333330;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.333330;,
  1.000000;0.333330;,
  1.000000;0.000000;,
  0.000000;0.666670;,
  1.000000;0.666670;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.666670;,
  0.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.666670;,
  0.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.666670;,
  0.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.000000;0.333330;,
  1.000000;0.666670;,
  0.000000;0.666670;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
