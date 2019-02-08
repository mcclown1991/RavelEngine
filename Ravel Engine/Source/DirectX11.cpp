#include"DirectX11.h"

DirectX11::DirectX11() : Graphics(){}

void DirectX11::Initialise(HWND hWnd, unsigned Width, unsigned Height, bool IsWindowed) {

	CoInitialize(NULL);


		// create a struct to hold information about the swap chain
		DXGI_SWAP_CHAIN_DESC scd;

		// clear out the struct for use
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

		// fill the swap chain description struct
		scd.BufferCount = 1;                                   // one back buffer
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;    // use 32-bit color
		scd.BufferDesc.Width = Width;			               // set the back buffer width
		scd.BufferDesc.Height = Height;				           // set the back buffer height
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;     // how swap chain is to be used
		scd.OutputWindow = hWnd;                               // the window to be used
		scd.SampleDesc.Count = 4;                              // how many multisamples
		scd.Windowed = IsWindowed;                               // windowed/full-screen mode
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;    // allow full-screen switching

		//_width = Width;
		//_height = Height;

		//isFullScreen = !Windowed;

		// create a device, device context and swap chain using the information in the scd struct
		HRESULT r = D3D11CreateDeviceAndSwapChain(NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			D3D11_CREATE_DEVICE_DEBUG,
			NULL,
			NULL,
			D3D11_SDK_VERSION,
			&scd,
			&m_SwapChain,
			&m_Device,
			NULL,
			&m_DeviceContext);

		// get the address of the back buffer
		ID3D11Texture2D *pBackBuffer;
		m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

		// use the back buffer address to create the render target
		m_Device->CreateRenderTargetView(pBackBuffer, NULL, &m_BackBuffer);
		pBackBuffer->Release();

		// set the render target as the back buffer
		m_DeviceContext->OMSetRenderTargets(1, &m_BackBuffer, NULL);

		m_Device->QueryInterface(IID_PPV_ARGS(&pDebug));

		// Set the viewport
		D3D11_VIEWPORT viewport;
		ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = (float)Width;
		viewport.Height = (float)Height;

		m_DeviceContext->RSSetViewports(1, &viewport);

		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(blendDesc));

		D3D11_RENDER_TARGET_BLEND_DESC rtbd;
		ZeroMemory(&rtbd, sizeof(rtbd));

		rtbd.BlendEnable = true;
		rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
		rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		rtbd.BlendOp = D3D11_BLEND_OP_ADD;
		rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
		rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
		rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.RenderTarget[0] = rtbd;

		m_Device->CreateBlendState(&blendDesc, &Transparency);

		// select which primtive type we are using
		//m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//Describe our Depth/Stencil Buffer
		D3D11_TEXTURE2D_DESC depthStencilDesc;

		depthStencilDesc.Width = Width;
		depthStencilDesc.Height = Height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		//Create the Depth/Stencil View
		m_Device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
		m_Device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

		D3D11_RASTERIZER_DESC wfdesc;
		ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
		wfdesc.FillMode = D3D11_FILL_SOLID;
		wfdesc.CullMode = D3D11_CULL_FRONT;
		wfdesc.MultisampleEnable = true;
		wfdesc.AntialiasedLineEnable = true;
		m_Device->CreateRasterizerState(&wfdesc, &CullMode);

		m_DeviceContext->RSSetState(CullMode);

		D3D11_BUFFER_DESC cbbd;
		ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

		cbbd.Usage = D3D11_USAGE_DYNAMIC;
		cbbd.ByteWidth = sizeof(TransformObjectBuffer);
		cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbbd.MiscFlags = 0;
		cbbd.StructureByteStride = 0;

		m_Device->CreateBuffer(&cbbd, NULL, &pTransform);

		D3D11_BUFFER_DESC cbbduv;
		ZeroMemory(&cbbduv, sizeof(D3D11_BUFFER_DESC));

		cbbduv.Usage = D3D11_USAGE_DYNAMIC;
		cbbduv.ByteWidth = sizeof(UVObjectBuffer);
		cbbduv.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbbduv.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbbduv.MiscFlags = 0;
		cbbduv.StructureByteStride = 4;

		m_Device->CreateBuffer(&cbbduv, NULL, &pUV);

		D3D11_BUFFER_DESC cbbda;
		ZeroMemory(&cbbda, sizeof(D3D11_BUFFER_DESC));

		cbbda.Usage = D3D11_USAGE_DYNAMIC;
		cbbda.ByteWidth = sizeof(AlphaObjectBuffer);
		cbbda.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbbda.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbbda.MiscFlags = 0;
		cbbda.StructureByteStride = 4;

		m_Device->CreateBuffer(&cbbda, NULL, &pAlpha);

		CreateMesh();

		m_SampleIDinUsed = -1;
	}

void DirectX11::UnInitialise() {
	//release all pointers
	//release buffers
	pVertex->Release();
	pIndex->Release();
	pTransform->Release();
	pUV->Release();
	pAlpha->Release();

	pVertex = nullptr;
	pIndex = nullptr;
	pTransform = nullptr;
	pUV = nullptr;
	pAlpha = nullptr;

	//release com objects
	pLayTex = nullptr;
	Transparency = nullptr;
	CullMode = nullptr;
	depthStencilView = nullptr;
	depthStencilBuffer = nullptr;

	//release shaders
	for (auto elem : pVertexShader) {
		if(elem)
			elem->Release();
	}

	for (auto elem : pFragmentShader) {
		if (elem)
			elem->Release();
	}

	for (auto elem : m_SampleList) {
		if(elem)
			elem->Release();
	}

	for (auto elem : m_SampleState) {
		if (elem)
			elem->Release();
	}

	for (auto elem : m_Resource) {
		if (elem)
			elem->Release();
	}

	m_SwapChain.Release();
	m_BackBuffer->Release();
	m_DeviceContext.Release();
	m_Device.Release();

	if (pDebug != nullptr)
	{
		pDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
		pDebug = nullptr;
	}
}

unsigned DirectX11::LoadVertexShader(std::string filename, std::string entry, std::string shaderModel)
{
	wchar_t* wString = new wchar_t[4096];

	filename += "_dx.vs";

	MultiByteToWideChar(CP_ACP, 0, filename.c_str(), -1, wString, 4096);

	ID3D10Blob* blob; ID3D10Blob* err;
	HRESULT hr;
	hr = D3DCompileFromFile(wString, 0, 0, entry.c_str(), shaderModel.c_str(), 0, 0, &blob, &err);

	if (FAILED(hr))
	{
		std::cout << "Failed to compile shader!" << std::endl;
		std::cout << "Failed to compile shader!\nError: " << (char*)err->GetBufferPointer() << std::endl;
		err->Release();
	}

	ID3D11VertexShader* pV{ 0 };
	hr = m_Device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &pV);

	if (FAILED(hr))
	{
		std::cout << "Failed to create shader!" << std::endl;
	}

	pVertexShader.push_back(std::move(pV));

	delete[] wString;

	D3D11_INPUT_ELEMENT_DESC tex[2];
	tex[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 };
	tex[1] = { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 };

	m_Device->CreateInputLayout(tex, 2, blob->GetBufferPointer(), blob->GetBufferSize(), &pLayTex);

	return pVertexShader.size() - 1;
}

unsigned DirectX11::LoadFragmentShader(std::string filename, std::string entry, std::string shaderModel) {
	wchar_t* wString = new wchar_t[4096];

	filename += "_dx.frag";

	MultiByteToWideChar(CP_ACP, 0, filename.c_str(), -1, wString, 4096);

	ID3D10Blob* blob; ID3D10Blob* err;
	HRESULT hr;
	hr = D3DCompileFromFile(wString, 0, 0, entry.c_str(), shaderModel.c_str(), 0, 0, &blob, &err);

	if (FAILED(hr))
	{
		std::cout << "Failed to compile shader!" << std::endl;
		std::cout << "Failed to compile shader!\nError: " << (char*)err->GetBufferPointer() << std::endl;
		err->Release();
	}

	ID3D11PixelShader* pS{ 0 };
	hr = m_Device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &pS);

	if (FAILED(hr))
	{
		std::cout << "Failed to create shader!" << std::endl;
	}

	pFragmentShader.push_back(std::move(pS));

	delete[] wString;

	return pFragmentShader.size() - 1;
}

void DirectX11::SetVertexShader(unsigned vertexID) {
	m_DeviceContext->VSSetShader(pVertexShader[vertexID], 0, 0);
}

void DirectX11::SetFragmentShader(unsigned fragmentID) {
	m_DeviceContext->PSSetShader(pFragmentShader[fragmentID], 0, 0);
}

void DirectX11::LinkProgram() {

}

void DirectX11::StartFrame() {
	float color[4] = { 0.f, 0.f, 0.f, 1.f };
	m_DeviceContext->ClearRenderTargetView(m_BackBuffer, color);

	m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_DeviceContext->IASetInputLayout(pLayTex);

	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	m_DeviceContext->IASetVertexBuffers(0, 1, &pVertex, &stride, &offset);
	m_DeviceContext->IASetIndexBuffer(pIndex, DXGI_FORMAT_R32_UINT, 0);

	//test code only
	TransformBuffer.camera = Matrix4x4::Mtx44Identity().ToXMMatrix();
}

void DirectX11::EndFrame() {
	m_SwapChain->Present(1, 0);

	//debugging used
	m_DrawCount = 0;
}

void DirectX11::OrthoProjectionMatrix(float ScreenW, float ScreenH) {
	TransformBuffer.projection = DirectX::XMMatrixOrthographicLH(ScreenW, ScreenH, 1.f, 10.0f);
}

HRESULT DirectX11::CreateMesh() {
	// create 2 triangle using the VERTEX struct
	VERTEX vertices[] =
	{
		VERTEX(-0.5f, -0.5f, 0.5f, 0.0f, 1.0f),
		VERTEX(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f),
		VERTEX(0.5f, 0.5f, 0.5f, 1.0f, 0.0f),
		VERTEX(0.5f, -0.5f, 0.5f, 1.0f, 1.0f)
	};

	DWORD indices[] = {
		0, 1, 2,
		0, 3, 2,
	};

	HRESULT hr;

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * 2 * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;

	iinitData.pSysMem = indices;
	hr = m_Device->CreateBuffer(&indexBufferDesc, &iinitData, &pIndex);
	if (FAILED(hr))
	{
		std::cout << "Failed to create index buffer!" << std::endl;
		return hr;
	}

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));

	vertexDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.ByteWidth = sizeof(VERTEX) * 4;

	D3D11_SUBRESOURCE_DATA resourceData;
	ZeroMemory(&resourceData, sizeof(resourceData));
	resourceData.pSysMem = vertices;

	hr = m_Device->CreateBuffer(&vertexDesc, &resourceData, &pVertex);
	if (FAILED(hr))
	{
		std::cout << "Failed to create Mesh vertex buffer!" << std::endl;
		return hr;
	}

	return S_OK;
}

HRESULT DirectX11::CreateTexture(std::string const& filename, unsigned& sampleID) {
	if (m_SampleID != 0)
	{
		auto iter = std::find(m_SampleFiles.begin(), m_SampleFiles.end(), filename);

		if (iter != m_SampleFiles.end())
		{
			sampleID = iter - m_SampleFiles.begin();
			return true;
		}

		sampleID = m_SampleID;
	}
	else
		sampleID = 0;

	std::wstring stemp = std::wstring(filename.begin(), filename.end());
	LPCWSTR sw = stemp.c_str();

	std::cout << "SampleID: " << sampleID << " ";
	std::wcout << stemp << std::endl;
	ID3D11ShaderResourceView* elem;

	HRESULT hr;
	ID3D11Resource* Res;

	hr = DirectX::CreateWICTextureFromFile(m_Device, sw, &Res, &elem);
	
	m_SampleList[m_SampleID] = std::move(elem);
	m_SampleFiles[m_SampleID] = filename;
	m_Resource[m_SampleID] = std::move(Res);

	if (FAILED(hr))
	{
		std::cout << "Failed to load the texture image!" << std::endl;
		return hr;
	}

	//DirectX::SaveWICTextureToFile(m_DeviceContext, Res, GUID_ContainerFormatBmp, L"SCREENSHOT.BMP");

	D3D11_SAMPLER_DESC colorMapDesc;
	ZeroMemory(&colorMapDesc, sizeof(colorMapDesc));

	colorMapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	
	colorMapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	colorMapDesc.MaxLOD = D3D11_FLOAT32_MAX;
	colorMapDesc.MipLODBias = 0.0f;
	colorMapDesc.MaxAnisotropy = 1;
	colorMapDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	colorMapDesc.BorderColor[0] = 0;
	colorMapDesc.BorderColor[1] = 0;
	colorMapDesc.BorderColor[2] = 0;
	colorMapDesc.BorderColor[3] = 0;
	colorMapDesc.MinLOD = 0;

	ID3D11SamplerState* elem2;

	hr = m_Device->CreateSamplerState(&colorMapDesc, &elem2);
	m_SampleState[m_SampleID] = std::move(elem2);
	if (FAILED(hr))
	{
		std::cout << "Failed to create color map sampler state" << std::endl;
		return hr;
	}

	m_SampleID++;

	return S_OK;
}

HRESULT DirectX11::Render(unsigned sampleID, Matrix4x4 transform, Vector2 uv, Vector2 UVscale, bool blend, float alpha) {
	D3D11_MAPPED_SUBRESOURCE mappedResource;

	TransformObjectBuffer* transformConstBuffer;
	// int bufferNumber;

	HRESULT hr;

	hr = m_DeviceContext->Map(pTransform, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(hr))
		return hr;

	transformConstBuffer = (TransformObjectBuffer*)mappedResource.pData;

	TransformBuffer.world = transform.ToXMMatrix();
	transformConstBuffer->world = TransformBuffer.world;
	transformConstBuffer->projection = TransformBuffer.projection;
	transformConstBuffer->camera = TransformBuffer.camera;

	m_DeviceContext->Unmap(pTransform, 0);

	m_DeviceContext->VSSetConstantBuffers(0, 1, &pTransform);

	if (sampleID != m_SampleIDinUsed) {
		m_DeviceContext->PSSetShaderResources(0, 1, &m_SampleList[sampleID]);
		m_SampleIDinUsed = sampleID;
		m_DeviceContext->PSSetSamplers(0, 1, &m_SampleState[sampleID]);
	}

	UVObjectBuffer* uvConstBuffer;

	hr = m_DeviceContext->Map(pUV, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(hr))
		return hr;

	uvConstBuffer = (UVObjectBuffer*)mappedResource.pData;

	uvConstBuffer->textureUV = uv.ToXMFloat();
	uvConstBuffer->scale = UVscale.ToXMFloat();

	m_DeviceContext->Unmap(pUV, 0);

	m_DeviceContext->VSSetConstantBuffers(1, 1, &pUV);

	if (blend) {
		float blendFactor[] = { 0.75f, 0.75f, 0.75f, 1.0f };
		m_DeviceContext->OMSetBlendState(0, 0, 0xffffffff);
		m_DeviceContext->OMSetBlendState(Transparency, blendFactor, 0xffffffff);
	}

	AlphaObjectBuffer* alphaConstBuffer;

	hr = m_DeviceContext->Map(pAlpha, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(hr))
		return hr;

	alphaConstBuffer = (AlphaObjectBuffer*)mappedResource.pData;

	alphaConstBuffer->alpha = alpha;

	m_DeviceContext->Unmap(pAlpha, 0);

	m_DeviceContext->PSSetConstantBuffers(0, 1, &pAlpha);

	m_DeviceContext->DrawIndexedInstanced(6, 1, 0, 0, 0);

	++m_DrawCount;

	return S_OK;
}