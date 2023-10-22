// 定数レジスタは最大で、頂点シェーダーは256、ピクセルシェーダーは32個まで宣言できる
// 2_0なら16個までの可能性があります
float4x4 worldViewProjectionMatrix : register(c0);

float4x4 g_cameraView;
float4x4 g_cameraProjection;
float4x4 g_mtxWorld;

// オブジェクトのテクスチャ、pDevice->SetTexture()で設定されたやつ
sampler textureSampler : register(s0);

// inputはよくても、outputじゃダメなセマンティクスがある
struct VS_INPUT
{	// 頂点シェーダー入力用
	float4 pos : POSITION;
	float3 nor : NORMAL;
	float4 col : COLOR0;
	float2 texCoord : TEXCOORD0;
};
struct VS_OUTPUT
{	// 頂点シェーダー出力用
	float4 pos : SV_POSITION;
	float4 col : COLOR0;
	float2 texCoord : TEXCOORD0;
};

// 一時レジスタの最大数を超えるとコンパイルエラーが出るらしい
// （上のg_...の変数を一つの関数に使えるのは最大３つまで）
// 頂点を射影空間へ移動
float4 TransVertex(float4 vtx)
{
	vtx = mul(vtx, g_mtxWorld);
	vtx = mul(vtx, g_cameraView);
	vtx = mul(vtx, g_cameraProjection);
	return vtx;
}

// テクスチャ座標正規化
float2 NormalizeTexCoord(float2 texCoord)
{
	float2 normalizedTexCoord;
	normalizedTexCoord.x = texCoord.x - floor(texCoord.x);
	normalizedTexCoord.y = texCoord.y - floor(texCoord.y);
	return normalizedTexCoord;
}

// ただの掛け算( A * B )は単純な乗算で、mulは行列の乗算になる
// エントリポイントの関数を用意しないとコンパイルエラー
VS_OUTPUT test(VS_INPUT inVS)
{
	VS_OUTPUT outVS;
	outVS.pos = TransVertex(inVS.pos);
	outVS.col = inVS.col;
	outVS.texCoord = inVS.texCoord;
	return outVS;
}

struct PS_OUTPUT
{	// ピクセルシェーダー出力用
	float4 col : SV_Target;
};

// memo0: vertexShaderの返り値をちゃんとしないと、画面全体がtex2D(textureSampler, inPS.texCoord)の返り値の色に塗りつぶされたりする
PS_OUTPUT PS_Main(VS_OUTPUT inVS)
{
	PS_OUTPUT outPS;
	float2 normalizedTexCoord = NormalizeTexCoord(inVS.texCoord);

	// テクスチャサンプリング
	outPS.col = tex2D(textureSampler, normalizedTexCoord) * inVS.col;
	return outPS;
}

technique TechShader
{
	pass P0
	{
		VertexShader = compile vs_2_0 test();
		PixelShader = compile ps_2_0 PS_Main();
	}
}