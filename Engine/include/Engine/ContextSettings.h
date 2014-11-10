
#ifndef CONTEXTSETTINGS_H
#define CONTEXTSETTINGS_H

struct ContextSettings
{
	GLubyte ColorBits = 32;
	GLubyte DepthBits = 24;
	GLubyte StencilBits = 8;
	GLubyte AntialiasLevel = 8;

	ContextSettings() = default;

	ContextSettings(GLubyte colorBits, GLubyte depthBits, GLubyte stencilBits, GLubyte antialiasLevel)
		: ColorBits(colorBits)
		, DepthBits(depthBits)
		, StencilBits(stencilBits)
		, AntialiasLevel(antialiasLevel)
	{
	}
};

#endif // Include guard

