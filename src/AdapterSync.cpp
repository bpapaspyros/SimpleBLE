#include <simpleble/AdapterSync.h>

#include "AdapterBase.h"
#include "AdapterBuilder.h"

using namespace SimpleBLE;

std::vector<AdapterSync> AdapterSync::get_adapters() {
    std::vector<AdapterSync> available_adapters;
    // auto internal_adapters = AdapterBase::get_adapters();

    // for (auto& internal_adapter : internal_adapters) {
    //     AdapterBuilder adapter(internal_adapter);
    //     available_adapters.push_back(adapter);
    // }

    // return available_adapters;
}

bool AdapterSync::initialized() const { return internal_ != nullptr; }

std::string AdapterSync::identifier() {
    if (!initialized()) throw Exception::NotInitialized();

    return internal_->identifier();
}

BluetoothAddress AdapterSync::address() {
    if (!initialized()) throw Exception::NotInitialized();

    return internal_->address();
}

void AdapterSync::scan_start() {
    if (!initialized()) throw Exception::NotInitialized();

    internal_->scan_start();
}

void AdapterSync::scan_stop() {
    if (!initialized()) throw Exception::NotInitialized();

    internal_->scan_stop();
}

void AdapterSync::scan_for(int timeout_ms) {
    if (!initialized()) throw Exception::NotInitialized();

    internal_->scan_for(timeout_ms);
}

bool AdapterSync::scan_is_active() {
    if (!initialized()) throw Exception::NotInitialized();

    return internal_->scan_is_active();
}

std::vector<Peripheral> AdapterSync::scan_get_results() {
    if (!initialized()) throw Exception::NotInitialized();

    return internal_->scan_get_results();
}

std::vector<Peripheral> AdapterSync::get_paired_peripherals() {
    if (!initialized()) throw Exception::NotInitialized();

    return internal_->get_paired_peripherals();
}

void AdapterSync::set_callback_on_scan_start(std::function<void()> on_scan_start) {
    if (!initialized()) throw Exception::NotInitialized();

    internal_->set_callback_on_scan_start(std::move(on_scan_start));
}

void AdapterSync::set_callback_on_scan_stop(std::function<void()> on_scan_stop) {
    if (!initialized()) throw Exception::NotInitialized();

    internal_->set_callback_on_scan_stop(std::move(on_scan_stop));
}

void AdapterSync::set_callback_on_scan_updated(std::function<void(Peripheral)> on_scan_updated) {
    if (!initialized()) throw Exception::NotInitialized();

    internal_->set_callback_on_scan_updated(std::move(on_scan_updated));
}

void AdapterSync::set_callback_on_scan_found(std::function<void(Peripheral)> on_scan_found) {
    if (!initialized()) throw Exception::NotInitialized();

    internal_->set_callback_on_scan_found(std::move(on_scan_found));
}
