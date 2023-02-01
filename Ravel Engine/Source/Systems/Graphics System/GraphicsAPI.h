#pragma once
#include <Windows.h>
#include <array>

#include "Camera.h"
#include "RavelMath.h"

class Graphics {
public:

	struct VERTEX {
		VERTEX() {}
		VERTEX(float x, float y, float z,
			float u, float v)
			: pos(x, y, z), texCoord(u, v) {}

		Vector3 pos;
		Vector2 texCoord;
	};

	Graphics() {};
	virtual ~Graphics() {};
	virtual void Initialise(HWND hWnd, unsigned Width, unsigned Height, bool IsWindowed = false) = 0;
	virtual void UnInitialise() = 0;

	virtual unsigned LoadVertexShader(std::string filename, std::string entry, std::string shaderModel) = 0;
	virtual unsigned LoadFragmentShader(std::string filename, std::string entry, std::string shaderModel) = 0;

	virtual void SetVertexShader(unsigned vertexID) = 0;
	virtual void SetFragmentShader(unsigned fragmentID) = 0;

	virtual void LinkProgram() = 0;

	virtual void StartFrame() = 0;
	virtual void EndFrame() = 0;

	virtual void OrthoProjectionMatrix(float ScreenW, float ScreenH) = 0;


	///Primitive Creation Functions
	virtual HRESULT CreateMesh() = 0;
	virtual HRESULT CreateTexture(std::string const& filename, unsigned& sampleID) = 0;

	virtual HRESULT Render(unsigned sampleID, Matrix4x4 transform, Vector2 uv, Vector2 UVscale, bool blend, float alpha) = 0;
	virtual void SetBackgroundColor(Color const& color) = 0;
	virtual void SetMainCamera(Camera* camera) = 0;
	virtual bool CheckCondition() = 0;

protected:
	//common structures
	unsigned m_SampleID;
	std::array<std::string, 1024> m_SampleFiles;

	Camera* render_camera;

	//debugging used
	unsigned m_DrawCount;
};