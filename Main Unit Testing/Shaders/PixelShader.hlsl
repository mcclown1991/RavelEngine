cbuffer alpha : register (cb0)
{
	float alpha;
	int pad;
	int pad2;
	int pad3;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

float4 main(PixelInputType input) : SV_TARGET
{
	float4 textureColor;

	textureColor = ObjTexture.Sample(ObjSamplerState, input.tex);

	/*textureColor[0] = input.tex[0];
	textureColor[1] = input.tex[1];
	textureColor[2] = 0;
	textureColor[3] = 1;
	*/
	return textureColor;
}