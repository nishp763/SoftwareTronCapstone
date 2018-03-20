#include "Arduino.h"
#include "Pitch.h"
#include "Servo.h"

#define MaxPitchLimit 135
#define MinPitchLimit 45
#define HomeLocation 90.0

Servo myservo; // create servo object to control a servo

Pitch::Pitch() // Constructor
{
	current_location = 0.0;
	target_location = 90.0; // Go home position by default

	myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

bool Pitch::move_to_location(double desired_location)
{
	if (MinPitchLimit <= desired_location && desired_location <= MaxPitchLimit)
	{
		myservo.write(desired_location); // move the servo to the desired location
		set_current_location(desired_location);
		return true;
	}	
	else
	{
		Serial.println("Target Location Out of Reach");
    	return false;
	}
}

bool Pitch::home_assembly()
{
	if(get_current_location() != HomeLocation)
	{
		myservo.write(HomeLocation);
		set_current_location(HomeLocation);
		return true;
	}
	else
	{
		Serial.println("Unable to Home the Servo Motor");
		return false;
	}	
}

double Pitch::get_current_location()
{
	return current_location;
}

void Pitch::set_current_location(double location)
{
	current_location = location;
}