#include "main.h"
#include "config.h"
#include "distance-reset.h"

int quadrant = 1;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    pros::lcd::initialize(); // initialize brain screen


    chassis.calibrate(); // calibrate sensors

    // Initialize subsystems
    intake_init();

    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(50);
        }
    });
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    while (true) {
        if (master.get_digital(INTAKE_BUTTON)) intake_set_state(INTAKE);
        else if (master.get_digital(SCORE_HIGH_BUTTON)) intake_set_state(SCORE_HIGH);
        else if (master.get_digital(SCORE_MID_BUTTON)) intake_set_state(SCORE_MID);
        else if (master.get_digital(SCORE_LOW_BUTTON)) intake_set_state(SCORE_LOW);
        else intake_set_state(IDLE);

        if (master.get_digital_new_press(MATCHLOAD_BUTTON)) set_matchloader(!matchloader_value);
        if (master.get_digital_new_press(DESCORE_BUTTON)) set_descore(!descore_value);

        for (const pros::controller_digital_e_t button : WING_BUTTONS) {
            if (master.get_digital_new_press(button)) {
                set_wing(!wing_value);
                break;
            }
        }

        if (master.get_digital_new_press(DIGITAL_B)) {
            quadrant++;
            if (quadrant == 5) quadrant = 1;
            pros::lcd::print(4, "QUAD: %d   ", quadrant); // x

        }
        if (master.get_digital_new_press(DIGITAL_A)) {
            match_load_reset(300, 0, quadrant);
        }

        const int drive = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        const int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        chassis.arcade(drive, turn);

        pros::delay(PROCESS_DELAY);
    }
}
