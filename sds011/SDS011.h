#ifndef __SDS011_H__
#define __SDS011_H__

#include "driver.h"
#include "device.h"
#include "driver/gpio.h"
#include "driver/uart.h"

class SDS011 : public Device {
	private:
		uint8_t rx_pin;
		
		uint16_t PM25 = 0;
		uint16_t PM10 = 0;


	public:
		TickType_t tickcnt;
		// constructor
		SDS011(uint8_t pin);

		// override
		void init(void);
		void process(Driver *drv);
		int prop_count(void);
		bool prop_name(int index, char *name);
		bool prop_unit(int index, char *unit);
		bool prop_attr(int index, char *attr);
		bool prop_read(int index, char *value);
		bool prop_write(int index, char *value);

		// method
		double get(int type) ;
		
};

#endif
