//
// Created by Hanyu Zhang on 12/9/25.
//

#include "config.h"
#include "autons.h"
#include "lib/data/data.h"

pros::Motor left_front_5_5w(LEFT_FRONT_5_5W_PORT, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor left_mid_11w(LEFT_MID_11W_PORT, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor left_back_11w(LEFT_BACK_11W_PORT, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor left_front_11w(LEFT_FRONT_11W_PORT, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::Motor right_front_5_5w(RIGHT_FRONT_5_5W_PORT, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor right_mid_11w(RIGHT_MID_11W_PORT, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor right_back_11w(RIGHT_BACK_11W_PORT, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor right_front_11w(RIGHT_FRONT_11W_PORT, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::MotorGroup left_drive({LEFT_FRONT_5_5W_PORT, LEFT_MID_11W_PORT, LEFT_BACK_11W_PORT, LEFT_FRONT_11W_PORT});
pros::MotorGroup right_drive({RIGHT_FRONT_5_5W_PORT, RIGHT_MID_11W_PORT, RIGHT_BACK_11W_PORT, RIGHT_FRONT_11W_PORT});

bool matchload_val = false;
bool wing_val = false;
bool park_val = false;

pros::adi::DigitalOut matchloader_piston(MATCHLOADER_SOLENOID_PORT);
pros::adi::DigitalOut pto_piston(PTO_SOLENOID_PORT);
pros::adi::DigitalOut score_mid_piston(INDEXER_SOLENOID_PORT);
pros::adi::DigitalOut park_piston(PARK_SOLENOID_PORT);
pros::adi::DigitalOut wing_piston(WING_SOLENOID_PORT);
pros::adi::DigitalOut descore_piston(DESCORE_SOLENOID_PORT);

pros::Distance front_dist(FRONT_DIST_PORT);
pros::Distance left_dist(LEFT_DIST_PORT);
pros::Distance right_dist(RIGHT_DIST_PORT);

Point front_dist_offset(-5, 6.5);
Point left_dist_offset(-5, -0.25);
Point right_dist_offset(6.5, 4);

// drivetrain settings
lemlib::Drivetrain drivetrain(&left_drive, //
                              &right_drive, //
                              10, // 
                              lemlib::Omniwheel::NEW_4, // 
                              343, // 
                              2 // 
);

pros::Imu imu(IMU_PORT);

// odometry settings
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

lemlib::ControllerSettings lateral_controller(10,
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
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

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain,
                        lateral_controller,
                        angular_controller,
                        sensors,
                        &throttle_curve,
                        &steer_curve
);