
#ifndef EVENT_H
#define EVENT_H

class Event
{
public:
	enum Type
	{
		Closed
	};

	Type type;

	// TEMP - Place holder members
	UINT msg;
	WPARAM wp;
	LPARAM lp;
};

#endif // Include guard
