#pragma once

#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <simpleble/Exceptions.h>
#include <simpleble/Types.h>

namespace SimpleBLE {

class PeripheralBase;

class Peripheral {
  public:
    Peripheral() = default;
    virtual ~Peripheral() = default;

    bool initialized() const;

    std::string identifier();
    BluetoothAddress address();
    int16_t rssi();

    void connect();
    void disconnect();
    bool is_connected();
    bool is_connectable();
    bool is_paired();
    void unpair();

    std::vector<BluetoothService> services();
    std::map<uint16_t, ByteStrArray> manufacturer_data();

    ByteStrArray read(BluetoothUUID const& service, BluetoothUUID const& characteristic);
    ByteArray readBytes(BluetoothUUID const& service, BluetoothUUID const& characteristic);
    void write_request(BluetoothUUID const& service, BluetoothUUID const& characteristic, ByteStrArray const& data);
    void write_request(BluetoothUUID const& service, BluetoothUUID const& characteristic, ByteArray const& data);
    void write_command(BluetoothUUID const& service, BluetoothUUID const& characteristic, ByteStrArray const& data);
    void write_command(BluetoothUUID const& service, BluetoothUUID const& characteristic, ByteArray const& data);
    void notify(BluetoothUUID const& service, BluetoothUUID const& characteristic,
                std::function<void(ByteStrArray payload)> callback);
    void notify(BluetoothUUID const& service, BluetoothUUID const& characteristic,
                std::function<void(ByteArray payload)> callback);
    void indicate(BluetoothUUID const& service, BluetoothUUID const& characteristic,
                  std::function<void(ByteStrArray payload)> callback);
    void indicate(BluetoothUUID const& service, BluetoothUUID const& characteristic,
                  std::function<void(ByteArray payload)> callback);
    void unsubscribe(BluetoothUUID const& service, BluetoothUUID const& characteristic);

    void set_callback_on_connected(std::function<void()> on_connected);
    void set_callback_on_disconnected(std::function<void()> on_disconnected);

  protected:
    std::shared_ptr<PeripheralBase> internal_;
};

}  // namespace SimpleBLE
