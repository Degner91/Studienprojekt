/*
 * LED.h
 *
 *  Created on: 05.02.2019
 *      Author: degne
 */

#ifndef _LED_H_
#define _LED_H_

class LED
{
public:
	static LED& GetInstance()
	{
		static LED instance;
		return instance;
	}
	~LED() {}

	enum LED_Color
	{
		RED, YELLOW, GREEN, ALL
	};

	void Initialize();
	void On(LED_Color const color);
	void Off(LED_Color const color);
	void Toggle(LED_Color const color);
	bool GetState(LED_Color const color);

private:
	// prevent more than one instances
	LED() { isInitialized = false; redState = false; yellowState = false; greenState = false; }
	LED(LED const &);
	LED& operator = (LED const &);

	bool isInitialized;

	// LED states
	bool redState;
	bool yellowState;
	bool greenState;
};

#endif
