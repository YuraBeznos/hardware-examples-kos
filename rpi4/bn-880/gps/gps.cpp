#include <nmea/sentence.hpp>
#include <nmea/message/gga.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <climits>
#include <regex>

#include <coresrv/syscalls.h>
#include <rtl/countof.h>
#include <bsp/bsp.h>
#include <uart/uart.h>

#define HW_MODULE_CFG   "rpi4_bcm2711.default"

int main() {

    Retcode rc;
    UartHandle uartH = KDF_INVALID_HANDLE;
    UartConfig uartPortConfig;

    rc = BspInit(RTL_NULL);
    if (rc != BSP_EOK) {
        std::cerr << "Failed to initialize BSP, error code: " << RC_GET_CODE(rc)
            << std::endl;
        return false;
    }
    std::cerr << "BspInit: OK" << std::endl;

    rc = BspEnableModule(PORT_NAME);
    if (rc != BSP_EOK) {
        std::cerr << "Failed to initialize BspEnableModule(PORT_NAME), error code: " << RC_GET_CODE(rc)
            << std::endl;
        return false;
    }
    std::cerr << "BspEnableModule: OK" << std::endl;


    if (rcOk == rc) {
        rc = BspSetConfig(PORT_NAME, HW_MODULE_CFG);
        if (rcOk != rc) {
            std::cerr << "Failed to set mux configuration for " << PORT_NAME
                      << " module, error code: " << RC_GET_CODE(rc) << std::endl;
        return false;
        }
    }
    std::cerr << "BspSetConfig: OK" << std::endl;


    // Initialize the UART driver.
    rc = UartInit();

    if (rc != UART_OK) {
        std::cerr <<  "UartInit() failed" << std::endl;
        return EXIT_FAILURE;
    }
    std::cerr << "UartInit(): OK" << std::endl;
    // Open port.
    rc = UartOpenPort(PORT_NAME, &uartH);

    if (rc != UART_OK) {
        std::cerr <<  "UartOpenPort() failed: " << PORT_NAME << std::endl;
        return EXIT_FAILURE;
    }
    std::cerr << "UartOpenPort(): OK" << std::endl;

    // uart handler
    rc = UartGetConfig(uartH, &uartPortConfig);
    if (rc != UART_OK) {
        std::cerr <<  "UartGetConfig() failed." << std::endl;
        return EXIT_FAILURE;
    }
    std::cerr << "UartGetConfig(): OK" << std::endl;

    uartPortConfig.baudrate = UartBaudRate::UART_BR_9600;
    rc = UartSetConfig(uartH, &uartPortConfig);
    if (rc != UART_OK) {
        std::cerr <<  "UartSetConfig() failed." << std::endl;
        return EXIT_FAILURE;
    }
    std::cerr << "UartSetConfig(): OK" << std::endl;

    // Read an NMEA string from your serial port
    std::string nmea_string;

    
    rtl_uint8_t * uartBuffer = new rtl_uint8_t [512];
    UartTimeouts uartTimeout;
    uartTimeout.overall = 4000;
    uartTimeout.interval = 2000;
    rtl_size_t uartBufferSize = 512;
    rtl_size_t uartBytesRead;
    
    std::stringstream oss;
    std::regex gga_regex("\\$\\w\\wGGA(,.*){14}\\*(\\w\\w)", 
            std::regex_constants::ECMAScript );

    while(true) {
        rc = UartRead(uartH, uartBuffer, uartBufferSize, &uartTimeout, &uartBytesRead);
        if (rc != UART_OK) {
            std::cerr << "UartRead() failed" << std::endl;
            continue;
        }

        if (uartBytesRead == 0) {
            continue;
        }
        oss << uartBuffer;

        while (std::getline(oss, nmea_string)) 
        {

            if (!std::regex_search(nmea_string, gga_regex)) {
                continue;
            }
            std::cerr << nmea_string << std::endl;
            // Parse the NMEA string into an NMEA sentence.
            nmea::sentence nmea_sentence(nmea_string);

            // Check if the NMEA message type is GGA.
            if(nmea_sentence.type() == "GGA")
            {
                // Parse GGA message from NMEA sentence.
                nmea::gga gga(nmea_sentence);

                // Print UTC time of day (seconds since 12:00AM UTC).
                std::cerr << "UTC: " << std::fixed << std::setprecision(2) << gga.utc.get() << std::endl;

                // Check if latitude is provided in the message.
                if(gga.latitude.exists())
                {
                    // Print latitude.
                    std::cerr << "Latitude: " << std::fixed << std::setprecision(6) << gga.latitude.get() << std::endl;
                }
                // Check if longitude is provided in the message.
                if(gga.longitude.exists())
                {
                    // Print longitude.
                    std::cerr << "Longitude: " << std::fixed << std::setprecision(6) << gga.longitude.get() << std::endl;
                }
            }
        }        
        oss.clear();
    }
    UartClosePort(uartH);
    UartFini();
    return 0;
}
