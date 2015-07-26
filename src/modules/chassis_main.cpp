/*
 * chassis_module.cpp
 *
 * Created: 22.07.2015 21:40:36
 *  Author: ultrablox
 */ 

#include "led_driver.h"
#include "brain_module.h"
#include <avr/io.h>
#include "chassis.pb.h"

class chassis_module : public brain_module
{
	enum class mode_t {normal, direct, combined, invalid};
public:
	chassis_module()
		:m_ledMode(2, 8)
	{
		register_led(m_ledMode);
		
		//Initialize PWM driver
		
		//Initialize ADC
		
		set_mode(mode_t::direct);
	}
	
	void set_mode(mode_t new_mode)
	{
		m_mode = new_mode;
		
		switch(m_mode)
		{
			case mode_t::normal:
				m_ledMode.set_mode(led_driver::mode_t::flash);
				break;
			case mode_t::direct:
				m_ledMode.set_mode(led_driver::mode_t::blink);
				break;
			case mode_t::combined:
				m_ledMode.set_mode(led_driver::mode_t::slow_blink);
				break;
			default:
				break;
		}
	}
	
	/*
	0 - OK
	1 - unknown command
	2+ - command specific
	*/
	response_m process_message(const request_m & msg)
	{
		response_m res;
		
		switch(msg.cmd_id)
		{
			case command_id_SET_SINGLE_OUTPUT:
				res.error_code = 1;
				break;
			case command_id_SET_ALL_OUTPUTS:
				res.error_code = 1;
				break;
			case command_id_GET_SINGLE_INPUT:
				res.error_code = 1;
				break;
			case command_id_GET_ALL_INPUTS:
				res.error_code = 1;
				break;
			default:
				res.error_code = 1;
				break;
		}
		
		return res;
	}
	
private:
	led_driver m_ledMode;
	mode_t m_mode;
};
	
int main(void)
{
	sei();
	
	chassis_module chs;
	chs.set_status(brain_module::status_t::error);
	
	
	
	chs.run();
}
