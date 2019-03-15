/**
 ******************************************************************************
 * \file    Button.h
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    15.02.2019
 * \brief   Definition of button class and functions
 ******************************************************************************
 */

#ifndef BSP_BUTTON_BUTTON_H_
#define BSP_BUTTON_BUTTON_H_

/**
 * \brief Class to control the buttons
 * \note Singleton pattern
 */
class Button
{
public:
	/**
	 * \brief Get static instance of Button class
	 * \param None
	 * \return Instance of Button
	 */
	static Button& GetInstance()
	{
		static Button instance;
		return instance;
	}
	~Button()
	{
	}

	/**
	 * \brief Button names
	 */
	enum Button_Name
	{
		NOBTN, /**< No button */
		WAKEUP, /**< WAKEUP button */
		USER0, /**< USER0 button */
		USER1 /**< USER1 button */
	};

	/**
	 * \brief Initialize button hardware
	 * \param None
	 * \return None
	 */
	void Initialize();

	/**
	 * \brief Get last pressed button
	 * \param None
	 * \return Last pressed button
	 */
	Button_Name GetState();

	/**
	 * \brief Set last pressed button
	 * \param Last pressed button read from EXTI
	 * \return None
	 * \note Only use in interrupt handler interrupt handler
	 */
	void SetState(Button_Name const name); // only for EXTI IRQs

private:
	// prevent more than one instances
	Button()
	{
		isInitialized = false;
		lastButton = NOBTN;
	}
	Button(Button const &);
	Button& operator =(Button const &);

	bool isInitialized; /**< Member to store, if hardware is initialized or not */
	Button_Name lastButton; /**< State of last button pressed */
};

#endif
