#include "main.h"
#include "pneumatics.h"
#include "config.h"

/**
 * \file pneumatics.cpp
 *
 * Pneumatics subsystem implementation
 * 
 * Uses ADI (Analog-Digital Input) ports for solenoid control via the
 * pneumatics module connected to the V5 brain.
 */

// Define pneumatic solenoids using PROS 4 ADI API
// Each solenoid is controlled via a digital output on an ADI port
static pros::adi::DigitalOut matchloader_solenoid(MATCHLOADER_SOLENOID_PORT);
static pros::adi::DigitalOut pto_solenoid(PTO_SOLENOID_PORT);
static pros::adi::DigitalOut score_middle_solenoid(SCORE_MIDDLE_SOLENOID_PORT);
static pros::adi::DigitalOut score_high_solenoid(SCORE_HIGH_SOLENOID_PORT);
static pros::adi::DigitalOut park_solenoid(PARK_SOLENOID_PORT);

// Global pneumatic actuator instances for convenient assignment syntax
// These allow syntax like: score_high_piston = true;
PneumaticActuator matchloader_piston(pneumatics_set_matchloader);
PneumaticActuator pto_piston(pneumatics_set_pto);
PneumaticActuator park_piston(pneumatics_set_park);
PneumaticActuator score_mid_piston(pneumatics_set_score_mid);
PneumaticActuator score_high_piston(pneumatics_set_score_high);

// Current pneumatics state
static PneumaticsState current_state = {
	.matchloader = false,
	.pto = false,
	.park = false,
	.score_mid = false,
	.score_high = false
};

void pneumatics_init() {
	current_state = {
		.matchloader = false,
		.pto = false,
		.park = false,
		.score_mid = false,
		.score_high = false
	};
}

void pneumatics_set_state(const PneumaticsState& state) {
	current_state = state;
	
	// Matchloader solenoid control
	if (current_state.matchloader) {
		matchloader_solenoid.set_value(true);
	} else {
		matchloader_solenoid.set_value(false);
	}
	
	// PTO solenoids control (dual solenoid)
	if (current_state.pto) {
		pto_solenoid.set_value(true);
	} else {
		pto_solenoid.set_value(false);
	}
	
	// Park solenoids control (dual solenoid)
	if (current_state.park) {
		park_solenoid.set_value(true);
	} else {
		park_solenoid.set_value(false);
	}
	
	// Score middle goal solenoid
	if (current_state.score_mid) {
		score_middle_solenoid.set_value(true);
	} else {
		score_middle_solenoid.set_value(false);
	}
	
	// Score high/long goal solenoid
	if (current_state.score_high) {
		score_high_solenoid.set_value(true);
	} else {
		score_high_solenoid.set_value(false);
	}
}

PneumaticsState pneumatics_get_state() {
	return current_state;
}

void pneumatics_set_matchloader(bool enable) {
	current_state.matchloader = enable;
	if (enable) {
		matchloader_solenoid.set_value(true);
	} else {
		matchloader_solenoid.set_value(false);
	}
}

void pneumatics_set_pto(bool enable) {
	current_state.pto = enable;
	if (enable) {
		pto_solenoid.set_value(true);
	} else {
		pto_solenoid.set_value(false);
	}
}

void pneumatics_set_park(bool enable) {
	current_state.park = enable;
	if (enable) {
		park_solenoid.set_value(true);;
	} else {
		park_solenoid.set_value(false);;
	}
}

void pneumatics_set_score_mid(bool enable) {
	current_state.score_mid = enable;
	if (enable) {
		score_middle_solenoid.set_value(true);;
	} else {
		score_middle_solenoid.set_value(false);;
	}
}

void pneumatics_set_score_high(bool enable) {
	current_state.score_high = enable;
	if (enable) {
		score_high_solenoid.set_value(true);;
	} else {
		score_high_solenoid.set_value(false);;
	}
}
