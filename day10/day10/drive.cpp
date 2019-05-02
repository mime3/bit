#include "drive.h"

car::car()
{
	sedan = new engine;
	sports = new engine;
}

car::~car()
{
	delete sedan;
	delete sports;
}

void car::autoStop()
{
	sedan->stop_engine();
	sports->stop_engine();
}

void car::make_bbox()
{
	if (eye != nullptr)
		return;

	eye = new black_box;
	eye->make_history_size();

}

void black_box::make_history_size()
{
	history = new engine[HISTORY_SIZE];

}

void black_box::update_history(int rkm, const char * rmode)
{
	for (int i = 0; i < HISTORY_SIZE; i++)
	{
		engine * enginePointer = history + i;
		if (enginePointer->get_mode() == 0 &&
			enginePointer->get_km() == 0)
		{
			enginePointer->set_mode(*rmode);
			enginePointer->set_km(rkm);
			break;
		}
	}
}

void black_box::display_history()
{
	for (int i = 0; i < HISTORY_SIZE; i++)
	{
		engine * enginePointer = history + i;
		if (enginePointer->get_mode() == 0 &&
			enginePointer->get_km() == 0)
			break;
		enginePointer->speed_engine();
	}
}

void engine::speed_engine()
{
	cout << km << ' ' << mode << endl;
}

void engine::stop_engine()
{
	printf("%s 엔진정지\n", mode == 'e' ? "세단" : "스포츠");
	//cout << "엔진 정지" << endl;
}
