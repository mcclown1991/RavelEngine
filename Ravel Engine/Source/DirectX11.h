#ifndef DIRECTX11_H
#define DIRECTX11_H

/////////////
// LINKING //
/////////////
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <dxgi.h>
#include <D3Dcompiler.h>
#include <directxmath.h>
#include <WICTextureLoader.h>
#include <ScreenGrab.h>
#include <atlbase.h>		//CComPtr
#include <string>
#include <iostream>
#include <wincodec.h>

#include "GraphicsAPI.h"
#include "RavelMath.h"
#include <vector>
#include <array>


class DirectX11 : public Graphics {
public:
	DirectX11();
	virtual void Initialise(HWND hWnd, unsigned Width, unsigned Height, bool IsWindowed = false);
	virtual void UnInitialise();

	virtual unsigned LoadVertexShader(std::string filename, std::string entry, std::string shaderModel);
	virtual unsigned LoadFragmentShader(std::string filename, std::string entry, std::string shaderModel);

	virtual void SetVertexShader(unsigned vertexID);
	virtual void SetFragmentShader(unsigned fragmentID);

	virtual void LinkProgram();

	virtual void StartFrame();
	virtual void EndFrame();

	virtual void OrthoProjectionMatrix(float ScreenW, float ScreenH);


	virtual HRESULT CreateMesh();
	virtual HRESULT CreateTexture(std::string const& filename, unsigned& sampleID);

	virtual HRESULT Render(unsigned sampleID, Matrix4x4 transform, Vector2 uv, Vector2 UVscale, bool blend, float alpha);

private:

	struct TransformObjectBuffer {
		DirectX::XMMATRIX world;
		DirectX::XMMATRIX projection;
		DirectX::XMMATRIX camera;
	}TransformBuffer;

	struct UVObjectBuffer {
		DirectX::XMFLOAT2 textureUV;
		DirectX::XMFLOAT2 scale;
	}UVBuffer;

	struct AlphaObjectBuffer {
		float alpha;
		int pad;
		int pad2;
		int pad3;		
	};

	CComPtr<IDXGISwapChain> m_SwapChain;
	CComPtr<ID3D11Device> m_Device;
	CComPtr<ID3D11DeviceContext> m_DeviceContext;
	ID3D11RenderTargetView* m_BackBuffer;

	ID3D11Buffer* pVertex;						//the pointer to the vertec buffer
	ID3D11Buffer* pIndex;						//the pointer to the indices
	ID3D11Buffer* pTransform;					// the pointer to the transform buffer
	ID3D11Buffer* pUV;							// the pointer to the UV buffer
	ID3D11Buffer* pAlpha;

	CComPtr<ID3D11InputLayout> pLayTex;

	CComPtr<ID3D11BlendState> Transparency;		// blend state
	CComPtr<ID3D11RasterizerState> CullMode;	// rasterizer

	CComPtr<ID3D11DepthStencilView> depthStencilView;	//depthstencil
	CComPtr<ID3D11Texture2D> depthStencilBuffer;		//depthstencil

	CComPtr<ID3D11Debug> pDebug;

	std::vector<ID3D11VertexShader*> pVertexShader;
	std::vector<ID3D11PixelShader*> pFragmentShader;

	std::array<ID3D11ShaderResourceView*, 1024> m_SampleList;
	std::array<ID3D11SamplerState*, 1024> m_SampleState;

	unsigned m_SampleIDinUsed;

};

#endif