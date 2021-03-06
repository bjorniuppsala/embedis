/*  Embedis - Embedded Dictionary Server
    Copyright (C) 2015 PatternAgents, LLC

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*
   ====================================================================================== 

    Embedis_I2C_EEPROM : Embedis example with Internal EEPROM and External I2C EEPROM Keystores
    -------------------------------------------------------------------------------------------
    This example Arduino IDE sketch works on a number of platforms including AVR & ESP8266
    and provides an Embedis server that store permenant (persistant) data in
    either the internal EEPROM of the processor or an external I2C EEPROM,
    such as the 24AA256 or 24LC256 type parts.

    The Embedis server can be used to get/set keys in the EEPROM or I2C_EEPROM databases,
    and can be used to store project and configuration settings. 
    You no longer need to embed  that "data" into your "program"! 
    The EEPROM & I2C_EEPROM are persistant memory structures, and can be
    used across multiple projects to configure your program setting for
    the specific hardware and network configuration you are using. 
    
    Now, you don't need to recompile your program and reflash your device
    in order to change the device settings anymore.

    We think that this is a much better mechanism for storing settings between projects.
    Once you start using Embedis for your projects, you'll see how quick and easy
    it is to move and reconfigure your devices without needing to recompile 
    and reflash your device firmware just to change a configuration setting.
    Now settings can be changed "on-the-fly" with just an Embedis Server.
    (some settings changes however, will require a restart/reboot to take effect.)

   ======================================================================================
*/

#include <Embedis.h>

// Embedis will run on the Serial port. Use the Arduino
// serial monitor and send "COMMANDS" to get started.
// Make sure "No line ending" is -not- selected. All others work.
//
Embedis embedis(Serial);

void setup() 
{
    Serial.begin(115200);
    delay(50);

    LOG( String() + F(" ") );
    LOG( String() + F("[ Embedis I2C_EEPROM Sketch ]") );
    
    setup_EEPROM();
    setup_I2C_EEPROM();
    setup_commands();

    LOG( String() + F("[ type 'commands' to get a list... ]") );    
}

void loop() 
{
    /* Always call the process method fro the main loop to run the Embedis system */
    embedis.process();

    /* Give the internal RTOS time to task switch in ESP8266, Edison, Currie, etc.   */
    /* not really necessary on AVR or Cortex platforms, but hey - it doesn't hurt... */
    delay(20); 
}

// This will log to an embedis channel called "log".
// Use SUBSCRIBE LOG to get these messages.
// Logs are also printed to Serial until an empty message is received.
void LOG(const String& message) {
    static bool inSetup = true;
    if (inSetup) {
        if (!message.length()) {
            inSetup = false;
            return;
        }
        SERIAL_PORT_MONITOR.println(message);
    }
    Embedis::publish("log", message);
}
