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
 112;
 0.00000;28.54479;-2.40916;,
 1.41606;28.54479;-1.94904;,
 1.41606;12.72020;-1.94904;,
 0.00000;12.72020;-2.40916;,
 2.29125;28.54479;-0.74448;,
 2.29125;12.72020;-0.74448;,
 2.29125;28.54479;0.74449;,
 2.29125;12.72020;0.74449;,
 1.41606;28.54479;1.94904;,
 1.41606;12.72020;1.94904;,
 0.00000;28.54479;2.40918;,
 0.00000;12.72020;2.40917;,
 -1.41607;28.54479;1.94904;,
 -1.41607;12.72020;1.94904;,
 -2.29126;28.54479;0.74449;,
 -2.29126;12.72020;0.74449;,
 -2.29126;28.54479;-0.74448;,
 -2.29126;12.72020;-0.74448;,
 -1.41607;28.54479;-1.94904;,
 -1.41607;12.72020;-1.94904;,
 0.00000;28.54479;-2.40916;,
 0.00000;12.72020;-2.40916;,
 1.55766;-27.84512;-2.14396;,
 0.00000;-27.84512;-2.65008;,
 2.52038;-27.84512;-0.81894;,
 2.52038;-27.84512;0.81894;,
 1.55766;-27.84512;2.14397;,
 0.00000;-27.84512;2.65008;,
 -1.55768;-27.84512;2.14397;,
 -2.52039;-27.84512;0.81894;,
 -2.52039;-27.84512;-0.81894;,
 -1.55768;-27.84512;-2.14396;,
 0.00000;-27.84512;-2.65008;,
 1.69927;-37.39574;-2.33888;,
 0.00000;-37.39574;-2.89101;,
 2.74950;-37.39574;-0.89338;,
 2.74950;-37.39574;0.89337;,
 1.69927;-37.39574;2.33886;,
 0.00000;-37.39574;2.89099;,
 -1.69929;-37.39574;2.33886;,
 -2.74952;-37.39574;0.89337;,
 -2.74952;-37.39574;-0.89338;,
 -1.69929;-37.39574;-2.33888;,
 0.00000;-37.39574;-2.89101;,
 0.00000;28.54479;0.00000;,
 0.00000;28.54479;0.00000;,
 0.00000;28.54479;0.00000;,
 0.00000;28.54479;0.00000;,
 0.00000;28.54479;0.00000;,
 0.00000;28.54479;0.00000;,
 0.00000;28.54479;0.00000;,
 0.00000;28.54479;0.00000;,
 0.00000;28.54479;0.00000;,
 0.00000;28.54479;0.00000;,
 0.00000;-37.39574;-0.00000;,
 0.00000;-37.39574;-0.00000;,
 0.00000;-37.39574;-0.00000;,
 0.00000;-37.39574;-0.00000;,
 0.00000;-37.39574;-0.00000;,
 0.00000;-37.39574;-0.00000;,
 0.00000;-37.39574;-0.00000;,
 0.00000;-37.39574;-0.00000;,
 0.00000;-37.39574;-0.00000;,
 0.00000;-37.39574;-0.00000;,
 -5.96410;-35.38269;-7.40617;,
 8.31571;-35.38269;-7.40617;,
 8.31571;-49.66256;-7.40617;,
 -5.96410;-49.66256;-7.40617;,
 8.31571;-35.38269;-7.40617;,
 8.31571;-35.38269;6.87363;,
 8.31571;-49.66256;6.87363;,
 8.31571;-49.66256;-7.40617;,
 8.31571;-35.38269;6.87363;,
 -5.96410;-35.38269;6.87363;,
 -5.96410;-49.66256;6.87363;,
 8.31571;-49.66256;6.87363;,
 -5.96410;-35.38269;6.87363;,
 -5.96410;-35.38269;-7.40617;,
 -5.96410;-49.66256;-7.40617;,
 -5.96410;-49.66256;6.87363;,
 8.31571;-35.38269;-7.40617;,
 -5.96410;-35.38269;-7.40617;,
 -5.96410;-49.66256;-7.40617;,
 8.31571;-49.66256;-7.40617;,
 -10.72405;-49.41663;-12.16614;,
 13.07567;-49.41663;-12.16614;,
 17.04228;-54.81173;-16.13277;,
 -14.69067;-54.81173;-16.13277;,
 17.04228;-63.69640;-16.13277;,
 -14.69067;-63.69640;-16.13277;,
 13.07567;-49.41663;-12.16614;,
 13.07567;-49.41663;11.63360;,
 17.04228;-54.81173;15.60021;,
 17.04228;-54.81173;-16.13277;,
 17.04228;-63.69640;15.60021;,
 17.04228;-63.69640;-16.13277;,
 13.07567;-49.41663;11.63360;,
 -10.72405;-49.41663;11.63360;,
 -14.69067;-54.81173;15.60021;,
 17.04228;-54.81173;15.60021;,
 -14.69067;-63.69640;15.60021;,
 17.04228;-63.69640;15.60021;,
 -10.72405;-49.41663;11.63360;,
 -10.72405;-49.41663;-12.16614;,
 -14.69067;-54.81173;-16.13277;,
 -14.69067;-54.81173;15.60021;,
 -14.69067;-63.69640;-16.13277;,
 -14.69067;-63.69640;15.60021;,
 13.07567;-49.41663;-12.16614;,
 -10.72405;-49.41663;-12.16614;,
 -14.69067;-63.69640;-16.13277;,
 17.04228;-63.69640;-16.13277;;
 
 66;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 4;3,2,22,23;,
 4;2,5,24,22;,
 4;5,7,25,24;,
 4;7,9,26,25;,
 4;9,11,27,26;,
 4;11,13,28,27;,
 4;13,15,29,28;,
 4;15,17,30,29;,
 4;17,19,31,30;,
 4;19,21,32,31;,
 4;23,22,33,34;,
 4;22,24,35,33;,
 4;24,25,36,35;,
 4;25,26,37,36;,
 4;26,27,38,37;,
 4;27,28,39,38;,
 4;28,29,40,39;,
 4;29,30,41,40;,
 4;30,31,42,41;,
 4;31,32,43,42;,
 3;44,1,0;,
 3;45,4,1;,
 3;46,6,4;,
 3;47,8,6;,
 3;48,10,8;,
 3;49,12,10;,
 3;50,14,12;,
 3;51,16,14;,
 3;52,18,16;,
 3;53,20,18;,
 3;54,34,33;,
 3;55,33,35;,
 3;56,35,36;,
 3;57,36,37;,
 3;58,37,38;,
 3;59,38,39;,
 3;60,39,40;,
 3;61,40,41;,
 3;62,41,42;,
 3;63,42,43;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;76,69,80,81;,
 4;82,83,70,79;,
 4;84,85,86,87;,
 4;87,86,88,89;,
 4;90,91,92,93;,
 4;93,92,94,95;,
 4;96,97,98,99;,
 4;99,98,100,101;,
 4;102,103,104,105;,
 4;105,104,106,107;,
 4;102,91,108,109;,
 4;110,111,94,107;;
 
 MeshMaterialList {
  22;
  66;
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  8,
  8,
  8,
  8,
  8,
  8,
  3,
  0,
  3,
  0,
  3,
  0,
  3,
  0,
  3,
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
  56;
  0.000000;1.000000;0.000000;,
  0.000001;0.000000;-1.000000;,
  0.587785;0.000000;-0.809017;,
  0.951054;0.000000;-0.309024;,
  0.951054;0.000000;0.309026;,
  0.587784;-0.000000;0.809018;,
  0.000001;-0.000000;1.000000;,
  -0.587783;-0.000000;0.809018;,
  -0.951054;0.000000;0.309026;,
  -0.951054;0.000000;-0.309024;,
  -0.587784;0.000000;-0.809018;,
  0.000001;0.002970;-0.999996;,
  0.587781;0.002970;-0.809015;,
  0.951050;0.002970;-0.309022;,
  0.951049;0.002969;0.309024;,
  0.587780;0.002969;0.809015;,
  0.000001;0.002969;0.999996;,
  -0.587779;0.002969;0.809016;,
  -0.951050;0.002969;0.309024;,
  -0.951050;0.002970;-0.309022;,
  -0.587780;0.002970;-0.809016;,
  0.000001;0.015580;-0.999879;,
  0.587711;0.015579;-0.808921;,
  0.950939;0.015579;-0.308985;,
  0.950939;0.015579;0.308986;,
  0.587710;0.015579;0.808922;,
  0.000001;0.015579;0.999879;,
  -0.587709;0.015579;0.808922;,
  -0.950939;0.015579;0.308986;,
  -0.950939;0.015579;-0.308985;,
  -0.587710;0.015579;-0.808922;,
  0.000001;0.025218;-0.999682;,
  0.587595;0.025218;-0.808762;,
  0.950752;0.025217;-0.308924;,
  0.950752;0.025217;0.308924;,
  0.587594;0.025217;0.808763;,
  0.000001;0.025217;0.999682;,
  -0.587593;0.025217;0.808763;,
  -0.950752;0.025217;0.308924;,
  -0.950752;0.025218;-0.308924;,
  -0.587594;0.025218;-0.808763;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.892288;-0.451466;,
  0.000000;0.311708;-0.950178;,
  0.451467;0.892288;0.000000;,
  0.950178;0.311707;0.000000;,
  0.000000;0.892288;0.451467;,
  0.000000;0.311707;0.950178;,
  -1.000000;0.000000;0.000000;,
  0.805677;0.592355;0.000000;,
  0.000000;0.592355;0.805677;,
  -0.805677;0.592355;0.000000;,
  -0.950178;0.311707;0.000000;;
  66;
  4;1,2,12,11;,
  4;2,3,13,12;,
  4;3,4,14,13;,
  4;4,5,15,14;,
  4;5,6,16,15;,
  4;6,7,17,16;,
  4;7,8,18,17;,
  4;8,9,19,18;,
  4;9,10,20,19;,
  4;10,1,11,20;,
  4;11,12,22,21;,
  4;12,13,23,22;,
  4;13,14,24,23;,
  4;14,15,25,24;,
  4;15,16,26,25;,
  4;16,17,27,26;,
  4;17,18,28,27;,
  4;18,19,29,28;,
  4;19,20,30,29;,
  4;20,11,21,30;,
  4;21,22,32,31;,
  4;22,23,33,32;,
  4;23,24,34,33;,
  4;24,25,35,34;,
  4;25,26,36,35;,
  4;26,27,37,36;,
  4;27,28,38,37;,
  4;28,29,39,38;,
  4;29,30,40,39;,
  4;30,21,31,40;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  3;41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;51,51,51,51;,
  4;0,0,0,0;,
  4;41,41,41,41;,
  4;45,45,46,46;,
  4;46,46,42,42;,
  4;52,47,48,48;,
  4;48,48,43,43;,
  4;53,49,50,50;,
  4;50,50,44,44;,
  4;54,54,55,55;,
  4;55,55,51,51;,
  4;49,47,45,45;,
  4;41,41,41,41;;
 }
 MeshTextureCoords {
  112;
  0.000000;0.000000;,
  0.100000;0.000000;,
  0.100000;0.333330;,
  0.000000;0.333330;,
  0.200000;0.000000;,
  0.200000;0.333330;,
  0.300000;0.000000;,
  0.300000;0.333330;,
  0.400000;0.000000;,
  0.400000;0.333330;,
  0.500000;0.000000;,
  0.500000;0.333330;,
  0.600000;0.000000;,
  0.600000;0.333330;,
  0.700000;0.000000;,
  0.700000;0.333330;,
  0.800000;0.000000;,
  0.800000;0.333330;,
  0.900000;0.000000;,
  0.900000;0.333330;,
  1.000000;0.000000;,
  1.000000;0.333330;,
  0.100000;0.666670;,
  0.000000;0.666670;,
  0.200000;0.666670;,
  0.300000;0.666670;,
  0.400000;0.666670;,
  0.500000;0.666670;,
  0.600000;0.666670;,
  0.700000;0.666670;,
  0.800000;0.666670;,
  0.900000;0.666670;,
  1.000000;0.666670;,
  0.100000;1.000000;,
  0.000000;1.000000;,
  0.200000;1.000000;,
  0.300000;1.000000;,
  0.400000;1.000000;,
  0.500000;1.000000;,
  0.600000;1.000000;,
  0.700000;1.000000;,
  0.800000;1.000000;,
  0.900000;1.000000;,
  1.000000;1.000000;,
  0.050000;0.000000;,
  0.150000;0.000000;,
  0.250000;0.000000;,
  0.350000;0.000000;,
  0.450000;0.000000;,
  0.550000;0.000000;,
  0.650000;0.000000;,
  0.750000;0.000000;,
  0.850000;0.000000;,
  0.950000;0.000000;,
  0.050000;1.000000;,
  0.150000;1.000000;,
  0.250000;1.000000;,
  0.350000;1.000000;,
  0.450000;1.000000;,
  0.550000;1.000000;,
  0.650000;1.000000;,
  0.750000;1.000000;,
  0.850000;1.000000;,
  0.950000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
