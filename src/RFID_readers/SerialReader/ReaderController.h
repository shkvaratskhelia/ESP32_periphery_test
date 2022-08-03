#ifndef _READER_CONTROLLER_H_
#define _READER_CONTROLLER_H_

#include <HardwareSerial.h>
#include <../config/sdkconfig.h>
#include <stdio.h>

#define MAX_SERIAL_BUFFER_SIZE          256

class EMReaderController {

        HardwareSerial reader_1 = HardwareSerial(1);
        HardwareSerial reader_2 = HardwareSerial(2);

        uint8_t _serial_buffer[MAX_SERIAL_BUFFER_SIZE] = {0};
        uint16_t _payload_size = 0;

        bool Read_Serial (HardwareSerial reader)
        {
            uint16_t payload_size = _payload_size = reader.available();
            if (payload_size)
            {
                uint16_t counter = 0;
                while (payload_size-- && counter < MAX_SERIAL_BUFFER_SIZE)
                {
                    _serial_buffer[counter] = reader.read();
                    counter++;
                }
                return true;
            }
            return false;
        }

        void Clear_Buffer ()
        {
            for (uint16_t i = 0; i < _payload_size; i++)
                _serial_buffer[i] = 0;
        }

        void Dump_Serial_Buffer (char * text)
        {
            Serial.print("Reading ");
            Serial.print(text);
            for (uint16_t i = 0; i < _payload_size; i++)
                Serial.print(_serial_buffer[i]);
            Serial.println("");
        }

    public :

        EMReaderController () {
            reader_1.begin(RDM_BAUDRATE, SERIAL_8N1, RDM_RX_PIN_1, RDM_TX_PIN_1);
            reader_2.begin(RDM_BAUDRATE, SERIAL_8N1, RDM_RX_PIN_2, RDM_TX_PIN_2);
        }

        void Main_Thread ()
        {
            if (Read_Serial(reader_1))
            {
                char buffer[64];
                sprintf(buffer, "Data From Reader 1; Total : %d Bytes; Payload: ", int(_payload_size));
                Dump_Serial_Buffer(buffer);
                Clear_Buffer();
            }
            if (Read_Serial(reader_2))
            {
                char buffer[64];
                sprintf(buffer, "Data From Reader 2; Total : %d Bytes; Payload: ", int(_payload_size));
                Dump_Serial_Buffer(buffer);
                Clear_Buffer();
            }
        }
};

#endif