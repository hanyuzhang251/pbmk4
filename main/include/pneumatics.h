#ifndef PNEUMATICS_H
#define PNEUMATICS_H

/**
 * \file pneumatics.h
 *
 * Pneumatics subsystem declarations
 */

// Pneumatics actuator states
struct PneumaticsState {
	bool matchloader;
	bool pto;
	bool park;
	bool score_mid;
	bool score_high;
};

/**
 * @brief Pneumatic actuator wrapper class for convenient boolean assignment
 * 
 * Allows syntax like: score_mid_piston = true;
 * Instead of: pneumatics_set_score_mid(true);
 */
class PneumaticActuator {
private:
	void (*setter_func)(bool);
	bool state;
	
public:
	/**
	 * @brief Constructor
	 * @param setter Function pointer to the pneumatics setter function
	 */
	explicit PneumaticActuator(void (*setter)(bool)) : setter_func(setter), state(false) {}
	
	/**
	 * @brief Assignment operator to set actuator state
	 * @param value true to extend, false to retract
	 */
	PneumaticActuator& operator=(bool value) {
		state = value;
		setter_func(value);
		return *this;
	}
	
	/**
	 * @brief Implicit conversion to bool to read current state
	 */
	operator bool() const {
		return state;
	}
};

void pneumatics_init();
void pneumatics_set_state(const PneumaticsState& state);
PneumaticsState pneumatics_get_state();

// Convenience functions for individual actuators
void pneumatics_set_matchloader(bool enable);
void pneumatics_set_pto(bool enable);
void pneumatics_set_park(bool enable);
void pneumatics_set_score_mid(bool enable);
void pneumatics_set_score_high(bool enable);

// Global actuator instances for convenient access
extern PneumaticActuator matchloader_piston;
extern PneumaticActuator pto_piston;
extern PneumaticActuator park_piston;
extern PneumaticActuator score_mid_piston;
extern PneumaticActuator score_high_piston;

#endif // PNEUMATICS_H