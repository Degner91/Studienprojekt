/*
 * VCOM.h
 *
 *  Created on: 05.02.2019
 *      Author: degne
 */

#ifndef BSP_VCOM_VCOM_H_
#define BSP_VCOM_VCOM_H_

class VCOM
{
public:
	static VCOM& GetInstance()
	{
		static VCOM instance;
		return instance;
	}
	~VCOM() {}

	void Initialize();
	void Print(char const * const str);
	void Println(char const * const str);

private:
	// prevent more than one instances
	VCOM() {}
	VCOM(VCOM const &);
	VCOM& operator =(VCOM const &);
};

#endif /* BSP_VCOM_VCOM_H_ */
