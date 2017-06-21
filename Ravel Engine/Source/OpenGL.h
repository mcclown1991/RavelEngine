#ifndef OPENGL_H
#define OPENGL_H

#include <Windows.h>
#include <GL/glew.h>
#include <glm.hpp>

namespace GraphicsAPI {
	namespace OpenGL {
		class Graphics {
		public:
			Graphics();
			void Initialise(HWND hWnd, unsigned Width, unsigned Height, bool IsWindowed = false);

		private:
			HDC hDC;
			HGLRC hRC;
			int m_PixelFormat;
		};
	}
}

#endif
