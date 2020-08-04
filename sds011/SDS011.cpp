#include "esp_system.h"
#include "kidbright32.h"
#include "esp_log.h"
#include "SDS011.h"

SDS011::SDS011(uint8_t pin) {
	this->rx_pin = pin;
}

void SDS011::init(void) {
	// Debug
	esp_log_level_set("*", ESP_LOG_INFO);
	
	uart_config_t uart_config = {
		.baud_rate = 9600,
		.data_bits = UART_DATA_8_BITS,
		.parity    = UART_PARITY_DISABLE,
		.stop_bits = UART_STOP_BITS_1,
		.flow_ctrl = UART_HW_FLOWCTRL_DISABLE
	};
	ESP_ERROR_CHECK(uart_param_config(UART_NUM_2, &uart_config));
	ESP_ERROR_CHECK(uart_set_pin(UART_NUM_2, UART_PIN_NO_CHANGE, this->rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
	ESP_ERROR_CHECK(uart_driver_install(UART_NUM_2, 256, 0, 0, NULL, 0));

	// clear error flag
	error = false;
	// set initialized flag
	initialized = true;
}

int SDS011::prop_count(void) {
	// not supported
	return 0;
}

bool SDS011::prop_name(int index, char *name) {
	// not supported
	return false;
}

bool SDS011::prop_unit(int index, char *unit) {
	// not supported
	return false;
}

bool SDS011::prop_attr(int index, char *attr) {
	// not supported
	return false;
}

bool SDS011::prop_read(int index, char *value) {
	// not supported
	return false;
}

bool SDS011::prop_write(int index, char *value) {
	// not supported
	return false;
}

void SDS011::process(Driver *drv) {
	if (!is_tickcnt_elapsed(tickcnt, 100)) {
		return;
	}

	size_t length = 0;
	ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_2, &length));
	if (length > 0) {
		uint8_t *data = (uint8_t*)malloc(length);
		int len = uart_read_bytes(UART_NUM_2, data, length, 100 / portTICK_RATE_MS);
		for (int i = 0; i < len; i++) {
			static int state = 0;
			static int data_len = 0;
			static uint8_t pm_data[6];
			static uint8_t sum;
			uint8_t c = data[i];
			if (state == 0) { // Chack Message header
				if (c == 0xAA) {
					state = 1;
				} else {
					state = 0;
				}
			} else if (state == 1) { // Check Commander No. 
				if (c == 0xC0) {
					data_len = 0;
					sum = 0;
					state = 2;
				} else {
					state = 0;
				}
			} else if (state == 2) { // DATA 1 - 6
				pm_data[data_len++] = c;
				sum += c;
				if (data_len == 6) {
					state = 3;
				}
			} else if (state == 3) { // Check-sum
				if (c == sum) {
					this->PM25 = ((uint16_t)(pm_data[1]) << 16) | pm_data[0];
					this->PM10 = ((uint16_t)(pm_data[3]) << 16) | pm_data[2];
					ESP_LOGI("SDS011", "PM2.5: %d\tPM10: %d\n", this->PM25, this->PM10);
				} else {
					ESP_LOGI("SDS011", "SUM error");
				}
				state = 0;
			}
		}
		free(data);
	}

	// get current tickcnt
	tickcnt = get_tickcnt();
}

double SDS011::get(int type) {
	return type == 1 ? this->PM25 : this->PM10;
}