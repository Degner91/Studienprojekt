/**
 ******************************************************************************
 * \file    LED.h
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    05.02.2019
 * \brief   Definition of string converter functions
 ******************************************************************************
 */

#ifndef BSP_LED_LED_H_
#define BSP_LED_LED_H_

/**
 * \brief Class to control the LEDs
 * \note Singleton pattern
 */
class LED
{
public:
	/**
	 * \brief Get static instance of LED class
	 * \param None
	 * \return Instance of LED
	 */
	static LED& GetInstance()
	{
		static LED instance;
		return instance;
	}
	~LED()
	{
	}

	/**
	 * \brief LED colors
	 */
	enum LED_Color
	{
		RED, /**< Red LED */
		YELLOW, /**< Yellow LED */
		GREEN, /**< Green LED */
		ALL /**< All LEDs */
	};

	/**
	 * \brief Initialize LED hardware
	 * \param None
	 * \return None
	 */
	void Initialize();

	/**
	 * \brief Set LED on
	 * \param color To be set LED
	 * \return None
	 */
	void On(LED_Color const color);

	/**
	 * \brief Set LED off
	 * \param color To be reset LED
	 * \return None
	 */
	void Off(LED_Color const color);

	/**
	 * \brief Toggle LED
	 * \param color To be toggled LED
	 * \return None
	 */
	void Toggle(LED_Color const color);

	/**
	 * \brief Get LED state
	 * \param color To be queried LED
	 * \return State of quiered LED (true = on, false = off)
	 */
	bool GetState(LED_Color const color);

private:
	// prevent more than one instances
	LED()
	{
		isInitialized = false;
		redState = false;
		yellowState = false;
		greenState = false;
	}
	LED(LED const &);
	LED& operator =(LED const &);

	bool isInitialized; /**< Member to store, if hardware is initialized or not */

	// LED states
	bool redState; /**< State of red LED */
	bool yellowState; /**< State of yellow LED */
	bool greenState; /**< State of green LED */
};

#endif
