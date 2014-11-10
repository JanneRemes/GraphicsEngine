
#include <Engine/Engine.h>

int main()
{
	Window wnd({ 800, 600 });
	Context ctx(wnd.getHandle());
	Event e;

	Shader shader;
	shader.fromSource(Shader::DefaultVertex, Shader::DefaultFragment);
	
	while (wnd.isOpen())
	{
		while (wnd.pollEvent(e))
		{
			if (e.type == Event::Closed)
				wnd.close();
		}

		ctx.clear({0.1f, 0.3f, 0.4f, 1.0f});

		ctx.swap();
	}
}
