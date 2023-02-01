#ifndef OPENGL_H
#define OPENGL_H

#include <Windows.h>
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "GraphicsAPI.h"

class OpenGL : public Graphics {
public:
	OpenGL();
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
	virtual void SetBackgroundColor(Color const& color) {};
	virtual void SetMainCamera(Camera* camera) {};
	virtual bool CheckCondition() { return true; };

private:
	HDC hDC;
	HGLRC hRC;
	int m_PixelFormat;

	unsigned m_VertexID, m_FragmentID;

	GLuint m_ProgramID;

	glm::mat4 m_Projection;
};

#endif
