#pragma once

/**
 * @file config.h
 * @brief Robot hardware configuration for VEX V5
 * 
 * Defines all motor ports, sensor ports, and pneumatic actuator ports
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "api.h"
#include "lib/data/data.h"

constexpr uint32_t PROCESS_DELAY = 10;

// ============================================================================
// DRIVETRAIN CONFIGURATION
// ============================================================================

// One 5.5W motor per side (geared for speed)
#define LEFT_FRONT_5_5W_PORT (-15)

// Left side drivetrain motors (11W - higher torque)
#define LEFT_BACK_11W_PORT (-13)
#define LEFT_MID_11W_PORT (14)
#define LEFT_FRONT_11W_PORT (-12)

#define RIGHT_FRONT_5_5W_PORT (17)
// Right side drivetrain motors (11W - higher torque)
#define RIGHT_BACK_11W_PORT (18)
#define RIGHT_MID_11W_PORT (-19)
#define RIGHT_FRONT_11W_PORT (20)

// ============================================================================
// INTAKE SYSTEM
// ============================================================================

// Intake motor (11W)
#define INTAKE_MOTOR_PORT (-2)

// ============================================================================
// SENSOR CONFIGURATION
// ============================================================================

// IMU sensor (for gyro heading)
#define IMU_PORT 16

// ============================================================================
// PNEUMATIC ACTUATORS (ADI Ports)
// ============================================================================

// Pneumatics for goal mechanisms
#define MATCHLOADER_SOLENOID_PORT 'B'    // Matchloader piston
#define WING_SOLENOID_PORT 'A'
#define PTO_SOLENOID_PORT 'C'          // PTO piston A
#define PARK_SOLENOID_PORT 'D'         // Park piston A
#define CLAMP_SOLENOID_PORT 'E'        // Descore piston
#define INDEXER_SOLENOID_PORT 'G'   // Middle goal piston
#define DESCORE_SOLENOID_PORT 'F'        // Descore piston

// ============================================================================
// MOTOR CONFIGURATION CONSTANTS
// ============================================================================

// Motor gearing ratios
#define MOTOR_SPEED_GEAR_RATIO 3.6   // 5.5W motors (36:100)
#define MOTOR_TORQUE_GEAR_RATIO 2.0  // 11W motors (20:100)

// Wheel diameter (in inches)
#define DRIVETRAIN_WHEEL_DIAMETER 4.0

// Track width (distance between left and right wheels in inches)
#define DRIVETRAIN_TRACK_WIDTH 9.8

// 0.5714


// ============================================================================
// SENSOR CALIBRATION
// ============================================================================

// Distance sensor calibration (raw values)
#define FRONT_DIST_PORT 1
#define LEFT_DIST_PORT 3
#define RIGHT_DIST_PORT 10

// Maximum distance sensor readings (in mm)
#define MAX_DISTANCE_READING 2000

// ============================================================================
// CONTROLS
// ============================================================================

inline constexpr pros::controller_digital_e_t INTAKE_BUTTON = pros::E_CONTROLLER_DIGITAL_L1;
inline constexpr pros::controller_digital_e_t SCORE_HIGH_BUTTON = pros::E_CONTROLLER_DIGITAL_R1;
inline constexpr pros::controller_digital_e_t SCORE_MID_BUTTON = pros::E_CONTROLLER_DIGITAL_L2;
inline constexpr pros::controller_digital_e_t SCORE_LOW_BUTTON = pros::E_CONTROLLER_DIGITAL_R2;

inline constexpr pros::controller_digital_e_t PARK_BUTTON = pros::E_CONTROLLER_DIGITAL_A;
inline constexpr pros::controller_digital_e_t CLAMP_BUTTON = pros::E_CONTROLLER_DIGITAL_B;

inline constexpr pros::controller_digital_e_t DESCORE_BUTTON = pros::E_CONTROLLER_DIGITAL_Y;
inline constexpr pros::controller_digital_e_t MATCHLOAD_BUTTON = pros::E_CONTROLLER_DIGITAL_DOWN;
inline constexpr pros::controller_digital_e_t WING_BUTTONS[] = {
    pros::E_CONTROLLER_DIGITAL_LEFT,
    pros::E_CONTROLLER_DIGITAL_UP,
    pros::E_CONTROLLER_DIGITAL_RIGHT,
};

inline constexpr pros::controller_digital_e_t WING_ON_BUTTON_COMBINATION[] = {
    pros::E_CONTROLLER_DIGITAL_L1,
    pros::E_CONTROLLER_DIGITAL_R1,
};

inline constexpr pros::controller_digital_e_t WING_OFF_BUTTON_COMBINATION[] = {
    pros::E_CONTROLLER_DIGITAL_L2,
    pros::E_CONTROLLER_DIGITAL_R2,
};


// ============================================================================
// DEVICES
// ============================================================================

inline pros::Controller master = pros::Controller(pros::E_CONTROLLER_MASTER);

extern pros::adi::DigitalOut matchloader_piston;
extern pros::adi::DigitalOut pto_piston;
extern pros::adi::DigitalOut score_mid_piston;
extern pros::adi::DigitalOut park_piston;
extern pros::adi::DigitalOut wing_piston;
extern pros::adi::DigitalOut descore_piston;
extern pros::adi::DigitalOut clamp_piston;

extern pros::Distance front_dist;
extern pros::Distance left_dist;
extern pros::Distance right_dist;

extern Point front_dist_offset;
extern Point left_dist_offset;
extern Point right_dist_offset;

extern lemlib::Drivetrain drivetrain;
extern pros::IMU imu;
extern lemlib::OdomSensors sensors;
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::ExpoDriveCurve throttle_curve;
extern lemlib::ExpoDriveCurve steer_curve;
extern lemlib::Chassis chassis;


#endif // CONFIG_H
