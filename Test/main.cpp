
#include <iostream>
#include <string>

#include <Engine\Engine.h>

int main()
{
	Window wnd({ 800, 600 });
	Context ctx(wnd.getHandle());
	Event e;

	while (wnd.isOpen())
	{
		while (wnd.pollEvent(e))
		{
			if (e.type == Event::Closed)
				wnd.close();
		}

		ctx.clear();

		ctx.display();
	}
}

