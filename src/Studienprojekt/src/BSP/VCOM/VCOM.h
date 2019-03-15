/**
 ******************************************************************************
 * \file    VCOM.h
 * \author  Lucas Degner
 * \version V1.0.0
 * \date    05.02.2019
 * \brief   Definition of USART interface class and functions
 ******************************************************************************
 */

#ifndef BSP_VCOM_VCOM_H_
#define BSP_VCOM_VCOM_H_

/**
 * \brief Class to control the USART interface
 * \note Singleton pattern
 */
class VCOM
{
public:
	/**
	 * \brief Get static instance of VCOM class
	 * \param None
	 * \return Instance of VCOM
	 */
	static VCOM& GetInstance()
	{
		static VCOM instance;
		return instance;
	}
	~VCOM()
	{
	}

	/**
	 * \brief Initialize USART hardware
	 * \param None
	 * \return None
	 */
	void Initialize();

	/**
	 * \brief Print string without line break (\r\n)
	 * \param str To be sent string
	 * \return None
	 */
	void Print(char const * const str);

	/**
	 * \brief Print string with line break (\r\n)
	 * \param str To be sent string
	 * \return None
	 */
	void Println(char const * const str);

private:
	// prevent more than one instances
	VCOM()
	{
		isInitialized = false;
	}
	VCOM(VCOM const &);
	VCOM& operator =(VCOM const &);

	bool isInitialized; /**< Member to store, if hardware is initialized or not */
};

#endif /* BSP_VCOM_VCOM_H_ */
