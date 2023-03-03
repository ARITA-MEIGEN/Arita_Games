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
 28;
 -89.31026;353.66600;-13.89824;,
 89.31026;353.66600;-13.89824;,
 63.62221;175.04549;-13.89824;,
 -63.62221;175.04549;-13.89824;,
 89.31026;353.66600;-13.89824;,
 89.31026;353.66600;13.89824;,
 63.62221;175.04549;13.89824;,
 63.62221;175.04549;-13.89824;,
 89.31026;353.66600;13.89824;,
 -89.31026;353.66600;13.89824;,
 -63.62221;175.04549;13.89824;,
 63.62221;175.04549;13.89824;,
 -89.31026;353.66600;13.89824;,
 -89.31026;353.66600;-13.89824;,
 -63.62221;175.04549;-13.89824;,
 -63.62221;175.04549;13.89824;,
 89.31026;353.66600;-13.89824;,
 -89.31026;353.66600;-13.89824;,
 32.44820;144.36214;-13.89824;,
 -32.44820;144.36214;-13.89824;,
 -63.62221;175.04549;-13.89824;,
 63.62221;175.04549;-13.89824;,
 32.44820;144.36214;13.89824;,
 -32.44820;144.36214;13.89824;,
 32.44820;0.19285;-13.89824;,
 -32.44820;0.19285;-13.89824;,
 32.44820;0.19285;13.89824;,
 -32.44820;0.19285;13.89824;;
 
 14;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,20,21;,
 4;22,18,21,6;,
 4;23,22,6,15;,
 4;19,23,15,20;,
 4;24,25,19,18;,
 4;26,24,18,22;,
 4;27,26,22,23;,
 4;25,27,23,19;,
 4;25,24,26,27;;
 
 MeshMaterialList {
  3;
  14;
  1,
  2,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.473600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Flower.jpg";
   }
  }
  Material {
   0.800000;0.772000;0.467200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  12;
  0.000000;0.000000;-1.000000;,
  0.989816;-0.142349;-0.000000;,
  0.892435;-0.451176;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.922355;-0.386344;-0.000000;,
  1.000000;0.000000;0.000000;,
  -0.989816;-0.142349;0.000000;,
  -0.892435;-0.451176;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.922355;-0.386344;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  14;
  4;0,0,0,0;,
  4;1,1,2,2;,
  4;3,3,3,3;,
  4;6,6,7,7;,
  4;8,8,8,8;,
  4;0,0,0,0;,
  4;4,4,2,2;,
  4;3,3,3,3;,
  4;9,9,7,7;,
  4;0,0,0,0;,
  4;5,5,4,4;,
  4;3,3,3,3;,
  4;10,10,9,9;,
  4;11,11,11,11;;
 }
 MeshTextureCoords {
  28;
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
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}
