//
//  CarHardware.h
//  dachuang_car_xcode
//
//  Created by 黄正跃 on 5/12/16.
//  Copyright © 2016 黄正跃. All rights reserved.
//

#ifndef CarHardware_h
#define CarHardware_h
#include <stdexcept>
#include <exception>
#include <iostream>
#include <wiringPi.h>

/*
 树莓派2引脚定义如下
 
 +-----+-----+---------+------+---+---Pi 2---+---+------+---------+-----+-----+
 | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
 +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
 |     |     |    3.3v |      |   |  1 || 2  |   |      | 5v      |     |     |
 |   2 |   8 |   SDA.1 |   IN | 1 |  3 || 4  |   |      | 5V      |     |     |
 |   3 |   9 |   SCL.1 |   IN | 1 |  5 || 6  |   |      | 0v      |     |     |
 |   4 |   7 | GPIO. 7 |   IN | 1 |  7 || 8  | 1 | ALT0 | TxD     | 15  | 14  |
 |     |     |      0v |      |   |  9 || 10 | 1 | ALT0 | RxD     | 16  | 15  |
 |  17 |   0 | GPIO. 0 |   IN | 1 | 11 || 12 | 0 | IN   | GPIO. 1 | 1   | 18  |
 |  27 |   2 | GPIO. 2 |   IN | 0 | 13 || 14 |   |      | 0v      |     |     |
 |  22 |   3 | GPIO. 3 |   IN | 0 | 15 || 16 | 0 | IN   | GPIO. 4 | 4   | 23  |
 |     |     |    3.3v |      |   | 17 || 18 | 0 | IN   | GPIO. 5 | 5   | 24  |
 |  10 |  12 |    MOSI |   IN | 0 | 19 || 20 |   |      | 0v      |     |     |
 |   9 |  13 |    MISO |   IN | 0 | 21 || 22 | 0 | IN   | GPIO. 6 | 6   | 25  |
 |  11 |  14 |    SCLK |   IN | 0 | 23 || 24 | 1 | IN   | CE0     | 10  | 8   |
 |     |     |      0v |      |   | 25 || 26 | 1 | IN   | CE1     | 11  | 7   |
 |   0 |  30 |   SDA.0 |   IN | 1 | 27 || 28 | 1 | IN   | SCL.0   | 31  | 1   |
 |   5 |  21 | GPIO.21 |   IN | 1 | 29 || 30 |   |      | 0v      |     |     |
 |   6 |  22 | GPIO.22 |   IN | 1 | 31 || 32 | 0 | IN   | GPIO.26 | 26  | 12  |
 |  13 |  23 | GPIO.23 |   IN | 0 | 33 || 34 |   |      | 0v      |     |     |
 |  19 |  24 | GPIO.24 |   IN | 0 | 35 || 36 | 0 | IN   | GPIO.27 | 27  | 16  |
 |  26 |  25 | GPIO.25 |   IN | 0 | 37 || 38 | 0 | IN   | GPIO.28 | 28  | 20  |
 |     |     |      0v |      |   | 39 || 40 | 0 | IN   | GPIO.29 | 29  | 21  |
 +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
 | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
 +-----+-----+---------+------+---+---Pi 2---+---+------+---------+-----+-----+
 
 */

class CarHardware{
private:
    //motor pins (connect to L298N)
    int MOTOR_LEFT_1;
    int MOTOR_LEFT_2;
    int MOTOR_RIGHT_1;
    int MOTOR_RIGHT_2;
    int MOTOR_PWM_1;
    int MOTOR_PWM_2;
    
    //single instance
    static CarHardware* car;
    //private constructor
    CarHardware(int motor_left_1,int motor_left_2,int motor_right_1,int motor_right_2)
    :MOTOR_LEFT_1(motor_left_1),
    MOTOR_LEFT_2(motor_left_2),
    MOTOR_RIGHT_1(motor_right_1),
    MOTOR_RIGHT_2(motor_right_2){
        wiringPiSetup();//initial all
        pinMode(MOTOR_LEFT_1, OUTPUT);
        pinMode(MOTOR_LEFT_2, OUTPUT);
        pinMode(MOTOR_RIGHT_1, OUTPUT);
        pinMode(MOTOR_RIGHT_2, OUTPUT);
        
    }
public:
    static CarHardware* create(int motor_left_1,int motor_left_2,int motor_right_1,int motor_right_2){
        if(nullptr==car){
            car=new CarHardware(motor_left_1,motor_left_2,motor_right_1,motor_right_2);
        }
        return car;
    }
    static CarHardware* getInstance(){
        //instance must be created before getInstance()
        if(nullptr==car){
            throw std::runtime_error("CarHardware not created!");
        }
        return car;
    }
    
    void goForward(double speed);
    void goBackward(double speed);
    void turnLeft(double speed);
    void turnRight(double speed);
    void stop();
    
};

#endif /* CarHardware_h */
