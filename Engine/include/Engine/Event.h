
#ifndef EVENT_H
#define EVENT_H

class Event
{
public:
	enum Type
	{
		Closed // Window receives the WM_CLOSE message
	};

	Type type;

	// TEMP - Placeholder data
	UINT msg;
	WPARAM wp;
	LPARAM lp;
};

#endif // Include guard
