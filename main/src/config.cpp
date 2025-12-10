//
// Created by Hanyu Zhang on 12/9/25.
//

#include "config.h"

pros::Motor left_front_5_5w(LEFT_FRONT_5_5W_PORT, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor left_mid_11w(LEFT_MID_11W_PORT, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor left_back_11w(LEFT_BACK_11W_PORT, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor left_front_11w(LEFT_FRONT_11W_PORT, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::Motor right_front_5_5w(LEFT_FRONT_5_5W_PORT, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
pros::Motor right_mid_11w(LEFT_MID_11W_PORT, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor right_back_11w(LEFT_BACK_11W_PORT, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::Motor right_front_11w(LEFT_FRONT_11W_PORT, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

pros::MotorGroup left_drive({left_front_5_5w, left_mid_11w, left_back_11w, left_front_11w});
pros::MotorGroup right_drive({right_front_5_5w, right_mid_11w, right_back_11w, right_front_11w});

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

// create the chassis
lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);