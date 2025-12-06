/*
 * config.cpp
 * Definitions related to configuration (kept minimal).
 */

#include "config.h"
#include "api.h"

// TODO: Update ports after wiring

const pros::controller_digital_e_t INTAKE_BUTTON = pros::E_CONTROLLER_DIGITAL_L1;
const pros::controller_digital_e_t SCORE_HIGH_BUTTON = pros::E_CONTROLLER_DIGITAL_L2;
const pros::controller_digital_e_t SCORE_MID_BUTTON = pros::E_CONTROLLER_DIGITAL_R1;
const pros::controller_digital_e_t SCORE_LOW_BUTTON = pros::E_CONTROLLER_DIGITAL_R2;
const pros::controller_digital_e_t MATCHLOAD_BUTTON = pros::E_CONTROLLER_DIGITAL_DOWN;
const pros::controller_digital_e_t SCORE_7_LOW_BUTTON = pros::E_CONTROLLER_DIGITAL_A;
const pros::controller_digital_e_t SCORE_7_MID_BUTTON = pros::E_CONTROLLER_DIGITAL_Y;

pros::Motor left_front_motor(1);
pros::Motor left_mid_motor(2);
pros::Motor left_rear_motor(3);
pros::Motor right_front_motor(4);
pros::Motor right_mid_motor(5);
pros::Motor right_rear_motor(6);

pros::MotorGroup left_motor_group({1, 2, 3});
pros::MotorGroup right_motor_group({4, 5, 6});

lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              10, // 10 inch track width
                              lemlib::Omniwheel::NEW_4, // using new 4" omnis
                              343, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

pros::Motor intake(7);

pros::Imu imu(8);

lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

pros::adi::DigitalOut score_long_piston('A');
pros::adi::DigitalOut score_mid_piston('B');
pros::adi::DigitalOut park_piston('C');

lemlib::ExpoDriveCurve throttle_curve(
    5,
    10,
    1
);

lemlib::ExpoDriveCurve steer_curve(
    5,
    10,
    1.3
);

// create the chassis
lemlib::Chassis chassis(
    drivetrain,
    lateral_controller,
    angular_controller,
    sensors,
    &throttle_curve,
    &steer_curve
);