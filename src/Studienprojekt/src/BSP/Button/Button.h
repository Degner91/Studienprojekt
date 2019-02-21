/*
 * Button.h
 *
 *  Created on: 15.02.2019
 *      Author: degne
 */

#ifndef _BUTTON_H_
#define _BUTTON_H_

class Button
{
public:
	static Button& GetInstance()
	{
		static Button instance;
		return instance;
	}
	~Button() {}

	enum Button_Name
	{
		NOBTN, WAKEUP, USER0, USER1
	};

	void Initialize();
	Button_Name GetState();
	void SetState(Button_Name const name); // only for EXTI IRQs

private:
	// prevent more than one instances
	Button() { isInitialized = false; lastButton = NOBTN; }
	Button(Button const &);
	Button& operator = (Button const &);

	bool isInitialized;
	Button_Name lastButton;
};


#endif /* BSP_BUTTON_BUTTON_H_ */
