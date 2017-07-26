cbuffer Transform : register (cb0) {
	matrix world;
	matrix projection;
	matrix camera;
};

cbuffer UV : register (cb1) {
	float2 uv;
	float2 scale;
};

struct VertexInputType {
	float4 position : POSITION;
	float2 tex : TEXCOORD0;
};

struct PixelInputType {
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
};


PixelInputType main(VertexInputType input )
{
	PixelInputType output;

	//temp for calc
	float4 temp = mul(input.position, world);
	temp = mul(temp, camera);
	output.position = mul(temp, projection);

	//input.tex.x += uv.x;
	//input.tex.y += uv.y;

	//input.tex.x *= scale.x;
	//input.tex.y *= scale.y;

	output.tex = input.tex;

	return output;
}