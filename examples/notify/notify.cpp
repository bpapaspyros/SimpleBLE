#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>
#include <vector>

#include "simpleble/SimpleBLE.h"

std::vector<SimpleBLE::Peripheral> peripherals;

void print_byte_array(SimpleBLE::ByteStrArray& bytes) {
    for (auto byte : bytes) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (uint32_t)((uint8_t)byte) << " ";
    }
    std::cout << std::endl;
}

int main() {
    auto adapter_list = SimpleBLE::Adapter::get_adapters();

    if (adapter_list.size() == 0) {
        std::cout << "No adapter was found." << std::endl;
        return 1;
    }

    std::cout << "Available adapters: \n";
    int i = 0;
    for (auto& adapter : adapter_list) {
        std::cout << "[" << i++ << "] " << adapter.identifier() << " [" << adapter.address() << "]" << std::endl;
    }

    int adapter_selection = -1;
    while (adapter_selection < 0 || adapter_selection > adapter_list.size() - 1) {
        std::cout << "Please select an adapter: ";
        std::cin >> adapter_selection;
    }

    SimpleBLE::Adapter& adapter = adapter_list[adapter_selection];

    adapter.set_callback_on_scan_start([]() { std::cout << "Scan started." << std::endl; });

    adapter.set_callback_on_scan_stop([]() { std::cout << "Scan stopped." << std::endl; });

    adapter.set_callback_on_scan_found([&](SimpleBLE::Peripheral peripheral) {
        std::cout << "Found device: " << peripheral.identifier() << " [" << peripheral.address() << "]" << std::endl;
        peripherals.push_back(peripheral);
    });

    // Scan for 5 seconds and return.
    adapter.scan_for(5000);

    std::cout << "The following devices were found:" << std::endl;
    for (size_t i = 0; i < peripherals.size(); i++) {
        std::cout << "[" << i << "] " << peripherals[i].identifier() << " [" << peripherals[i].address() << "]"
                  << std::endl;
    }

    int selection = -1;
    std::cout << "Please select a device to connect to: ";
    std::cin >> selection;

    if (selection >= 0 && selection < peripherals.size()) {
        auto peripheral = peripherals[selection];
        std::cout << "Connecting to " << peripheral.identifier() << " [" << peripheral.address() << "]" << std::endl;
        peripheral.connect();

        std::cout << "Successfully connected, printing services and characteristics.." << std::endl;

        // Store all service and characteristic uuids in a vector.
        std::vector<std::pair<SimpleBLE::BluetoothUUID, SimpleBLE::BluetoothUUID>> uuids;
        for (auto service : peripheral.services()) {
            for (auto characteristic : service.characteristics) {
                uuids.push_back(std::make_pair(service.uuid, characteristic));
            }
        }

        std::cout << "The following services and characteristics were found:" << std::endl;
        for (size_t i = 0; i < uuids.size(); i++) {
            std::cout << "[" << i << "] " << uuids[i].first << " " << uuids[i].second << std::endl;
        }

        std::cout << "Please select a characteristic to read: ";
        std::cin >> selection;

        if (selection >= 0 && selection < uuids.size()) {
            // Subscribe to the characteristic.
            peripheral.notify(uuids[selection].first, uuids[selection].second, [&](SimpleBLE::ByteStrArray bytes) {
                std::cout << "Received: ";
                print_byte_array(bytes);
            });

            std::this_thread::sleep_for(std::chrono::seconds(5));

            peripheral.unsubscribe(uuids[selection].first, uuids[selection].second);
        }
        peripheral.disconnect();
    }

    return 0;
}
