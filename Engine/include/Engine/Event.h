
#ifndef EVENT_H
#define EVENT_H

class Event
{
public:
	enum Type
	{
		Closed,
		Resized
	};

	Type type;

	// TEMP - Place holder members
	UINT msg;
	WPARAM wp;
	LPARAM lp;
};

#endif // Include guard
