#include "OpenGL.h"

OpenGL::OpenGL() : Graphics(){

}

void OpenGL::Initialise(HWND hWnd, unsigned Width, unsigned Height, bool IsWindowed) {
	PIXELFORMATDESCRIPTOR pfd = { 0 };
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 32;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.iLayerType = PFD_MAIN_PLANE;

	hDC = GetDC(hWnd);
	if (!hDC) {
		// Failed to get device context
		std::cout << "Failed to get context" << std::endl;
	}

	if (!(m_PixelFormat = ChoosePixelFormat(hDC, &pfd))) {
		std::cout << "Failed to get Pixel Format" << std::endl;
	}

	if (!SetPixelFormat(hDC, m_PixelFormat, &pfd)) {
		std::cout << "Failed to set Pixel Format" << std::endl;
	}

	if (!(hRC = wglCreateContext(hDC))) {
		std::cout << "Failed to create context" << std::endl;
	}

	if (!wglMakeCurrent(hDC, hRC)) {
		std::cout << "Failed to make context" << std::endl;
	}

	GLenum err = glewInit();



	glViewport(0, 0, Width, Height);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
}

void OpenGL::UnInitialise() {

}

unsigned OpenGL::LoadVertexShader(std::string filename, std::string entry, std::string shaderModel) {
	UNREFERENCED_PARAMETER(entry);
	UNREFERENCED_PARAMETER(shaderModel);

	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	filename += "_gl.vs";
	std::ifstream VertexShaderStream(filename, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (std::getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		std::cout << "Impossible to open " << filename << ". Are you in the right directory ? Don't forget to read the FAQ !" << std::endl;
		//printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", filename);
		getchar();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	std::cout << "Compiling shader : " << filename << std::endl;
	//printf("Compiling shader : %s\n", filename);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	return VertexShaderID;
}

unsigned OpenGL::LoadFragmentShader(std::string filename, std::string entry, std::string shaderModel) {
	UNREFERENCED_PARAMETER(entry);
	UNREFERENCED_PARAMETER(shaderModel);

	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	filename += "_gl.frag";
	std::ifstream FragmentShaderStream(filename, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	
	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Fragment Shader
	std::cout << "Compiling shader : " << filename << std::endl;
	//printf("Compiling shader : %s\n", filename);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}
	
	return FragmentShaderID;
}

void OpenGL::SetVertexShader(unsigned vertexID) {
	m_VertexID = vertexID;
}

void OpenGL::SetFragmentShader(unsigned fragmentID) {
	m_FragmentID = fragmentID;
}

void OpenGL::LinkProgram() {
	// Link the program
	printf("Linking program\n");
	m_ProgramID = glCreateProgram();
	glAttachShader(m_ProgramID, m_VertexID);
	glAttachShader(m_ProgramID, m_FragmentID);
	glLinkProgram(m_ProgramID);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Check the program
	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(m_ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(m_ProgramID, m_VertexID);
	glDetachShader(m_ProgramID, m_FragmentID);

	glDeleteShader(m_VertexID);
	glDeleteShader(m_FragmentID);

}

void OpenGL::StartFrame() {
	glUseProgram(m_ProgramID);

}

void OpenGL::EndFrame() {

}

void OpenGL::OrthoProjectionMatrix(float ScreenW, float ScreenH) {
	m_Projection = glm::ortho(0.f, ScreenW, ScreenH, 0.f, -5.f, 5.f);
}

HRESULT OpenGL::CreateMesh() {
	VERTEX vertices[] =
	{
		VERTEX(-1.0f, -1.0f, 1.0f, 0.0f, 1.0f),
		VERTEX(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f),
		VERTEX(1.0f, 1.0f, 1.0f, 1.0f, 0.0f),
		VERTEX(1.0f, -1.0f, 1.0f, 1.0f, 1.0f)
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTEX) * 4, vertices, GL_STATIC_DRAW);
	return S_OK;
}

HRESULT OpenGL::CreateTexture(std::string const& filename, unsigned& sampleID) {
	//GLuint texture = Load
	return S_OK;
}

HRESULT OpenGL::Render(unsigned sampleID, Matrix4x4 transform, Vector2 uv, Vector2 UVscale, bool blend, float alpha) {
	
	return S_OK;
}