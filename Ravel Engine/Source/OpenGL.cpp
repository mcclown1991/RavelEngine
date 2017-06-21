#include "OpenGL.h"

namespace GraphicsAPI {
	namespace OpenGL {
		Graphics::Graphics() {

		}

		void Graphics::Initialise(HWND hWnd, unsigned Width, unsigned Height, bool IsWindowed) {
			PIXELFORMATDESCRIPTOR pfd;
			memset(&pfd, 0, sizeof(pfd));
			pfd.nSize = sizeof(pfd);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.cColorBits = 24;
			pfd.cDepthBits = 24;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.iLayerType = PFD_MAIN_PLANE;

			hDC = GetDC(hWnd);
			if (!hDC) {
				// Failed to get device context
			}

			if (!(m_PixelFormat = ChoosePixelFormat(hDC, &pfd))) {

			}

			if (!SetPixelFormat(hDC, m_PixelFormat, &pfd)) {

			}

			if (!(hRC = wglCreateContext(hDC))) {

			}

			if (!wglMakeCurrent(hDC, hRC)) {

			}

			// Dark blue background
			glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

			// Enable depth test
			glEnable(GL_DEPTH_TEST);
			// Accept fragment if it closer to the camera than the former one
			glDepthFunc(GL_LESS);
		}
	}
}