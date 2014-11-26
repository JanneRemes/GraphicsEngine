
#include <Engine/Window.h>
#include <Engine/Context.h>
#include <Engine/SpriteBatch.h>
#include <glm/glm.hpp>

int main()
{
	Window wnd({ 800, 600 }, "Title");
	Context::Init(wnd);

	SpriteBatch batch;

	while (wnd.isOpen())
	{
		wnd.update();

		Context::Clear({ 0.0f, 0.0f, 0.0f, 1.0f });

		batch.Start();
		batch.Draw(
		{
			0.0f, 0.0f, 0.0f, /**/ 1.0f, 0.0f, 0.0f, 1.0f, /**/ 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, /**/ 0.0f, 1.0f, 0.0f, 1.0f, /**/ 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f, /**/ 0.0f, 0.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f,
			1.0f, 0.0f, 0.0f, /**/ 1.0f, 1.0f, 0.0f, 1.0f, /**/ 1.0f, 0.0f,
		});
		batch.End();
		
		Context::Swap();
	}
}
