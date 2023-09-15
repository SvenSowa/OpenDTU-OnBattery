// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Copyright (C) 2022 Thomas Basler and others
 */
#include "MqttHandleVedirectHass.h"
#include "Configuration.h"
#include "MqttSettings.h"
#include "NetworkSettings.h"
#include "MessageOutput.h"

MqttHandleVedirectHassClass MqttHandleVedirectHass;

void MqttHandleVedirectHassClass::init()
{
}

void MqttHandleVedirectHassClass::loop()
{
    if (!Configuration.get().Vedirect_Enabled) {
        return;
    }
    if (_updateForced) {
        publishConfig();
        _updateForced = false;
    }

    if (MqttSettings.getConnected() && !_wasConnected) {
        // Connection established
        _wasConnected = true;
        publishConfig();
    } else if (!MqttSettings.getConnected() && _wasConnected) {
        // Connection lost
        _wasConnected = false;
    }
}

void MqttHandleVedirectHassClass::forceUpdate()
{
    _updateForced = true;
}

void MqttHandleVedirectHassClass::publishConfig()
{
    if ((!Configuration.get().Mqtt_Hass_Enabled) ||
       (!Configuration.get().Vedirect_Enabled)) {
        return;
    }

    if (!MqttSettings.getConnected()) {
        return;
    }
    // ensure data is revieved from victron
    if (!VeDirect.isDataValid()) { 
        return;
    }

    MessageOutput.printf("[MqttHandleVedirectHassClass::publishConfig] free heap=%d \r\n", ESP.getFreeHeap());
  

    // device info
    publishBinarySensor("MPPT load output state", "mdi:export", "LOAD", "ON", "OFF");
    publishSensor("MPPT serial number", "mdi:counter", "SER");
    publishSensor("MPPT firmware number", "mdi:counter", "FW");
    publishSensor("MPPT state of operation", "mdi:wrench", "CS");
    publishSensor("MPPT error code", "mdi:bell", "ERR");
    publishSensor("MPPT off reason", "mdi:wrench", "OR");
    publishSensor("MPPT tracker operation mode", "mdi:wrench", "MPPT");
    publishSensor("MPPT Day sequence number (0...364)", "mdi:calendar-month-outline", "HSDS", NULL, "total", "d");

    // battery info
    publishSensor("Battery voltage", NULL, "V", "voltage", "measurement", "V");
    publishSensor("Battery current", NULL, "I", "current", "measurement", "A");

    // panel info
    publishSensor("Panel voltage", NULL, "VPV", "voltage", "measurement", "V");
    publishSensor("Panel power", NULL, "PPV", "power", "measurement", "W");
    publishSensor("Panel yield total", NULL, "H19", "energy", "total_increasing", "kWh");
    publishSensor("Panel yield today", NULL, "H20", "energy", "total", "kWh");
    publishSensor("Panel maximum power today", NULL, "H21", "power", "measurement", "W");
    publishSensor("Panel yield yesterday", NULL, "H22", "energy", "total", "kWh");
    publishSensor("Panel maximum power yesterday", NULL, "H23", "power", "measurement", "W");

    yield();
}

void MqttHandleVedirectHassClass::publishSensor(const char* caption, const char* icon, const char* subTopic, const char* deviceClass, const char* stateClass, const char* unitOfMeasurement )
{
    MessageOutput.printf("[MqttHandleVedirectHassClass::publishSensor] free heap=%d caption=\"%s\", icon=\"%s\", subTopic=\"%s\", deviceClass=\"%s\", stateClass=\"%s\", unitOfMeasurement=\"%s\",\r\n", ESP.getFreeHeap(), caption, icon != NULL ? icon : "", subTopic, deviceClass != NULL ? deviceClass : "", stateClass != NULL ? stateClass : "", unitOfMeasurement != NULL ? unitOfMeasurement : "");
    String serial = VeDirect.veFrame.SER;

    String sensorId = caption;
    sensorId.replace(" ", "_");
    sensorId.replace(".", "");
    sensorId.replace("(", "");
    sensorId.replace(")", "");
    sensorId.toLowerCase();

    String configTopic = "sensor/dtu_victron_" + serial
        + "/" + sensorId
        + "/config";
    
    String statTopic = MqttSettings.getPrefix() + "victron/";
    statTopic.concat(VeDirect.veFrame.SER);
    statTopic.concat("/");
    statTopic.concat(subTopic);

    DynamicJsonDocument root(1024);
    root[F("name")] = caption;
    root[F("stat_t")] = statTopic;
    root[F("uniq_id")] = serial + "_" + sensorId;

    if (icon != NULL) {
        root[F("icon")] = icon;
    }

    if (unitOfMeasurement != NULL) {
        root[F("unit_of_meas")] = unitOfMeasurement;
    }

    JsonObject deviceObj = root.createNestedObject("dev");
    createDeviceInfo(deviceObj);

    if (Configuration.get().Mqtt_Hass_Expire) {
        root[F("exp_aft")] = Configuration.get().Mqtt_PublishInterval * 3;
    }
    if (deviceClass != NULL) {
        root[F("dev_cla")] = deviceClass;
    }
    if (stateClass != NULL) {
        root[F("stat_cla")] = stateClass;
    }

    char buffer[1024];
    int byte = serializeJson(root, buffer);
    MessageOutput.printf("[MqttHandleVedirectHassClass::publishSensor] size of buffer: %d\r\n", byte);
    publish(configTopic, buffer);

}
void MqttHandleVedirectHassClass::publishBinarySensor(const char* caption, const char* icon, const char* subTopic, const char* payload_on, const char* payload_off)
{
    String serial = VeDirect.veFrame.SER;

    String sensorId = caption;
    sensorId.replace(" ", "_");
    sensorId.replace(".", "");
    sensorId.replace("(", "");
    sensorId.replace(")", "");
    sensorId.toLowerCase();

    String configTopic = "binary_sensor/dtu_victron_" + serial
        + "/" + sensorId
        + "/config";

    String statTopic = MqttSettings.getPrefix() + "victron/";
    statTopic.concat(VeDirect.veFrame.SER);
    statTopic.concat("/");
    statTopic.concat(subTopic);

    DynamicJsonDocument root(1024);
    root[F("name")] = caption;
    root[F("uniq_id")] = serial + "_" + sensorId;
    root[F("stat_t")] = statTopic;
    root[F("pl_on")] = payload_on;
    root[F("pl_off")] = payload_off;

    if (icon != NULL) {
        root[F("icon")] = icon;
    }

    JsonObject deviceObj = root.createNestedObject("dev");
    createDeviceInfo(deviceObj);

    char buffer[1024];;
    
    int byte = serializeJson(root, buffer);
    MessageOutput.printf("[MqttHandleVedirectHassClass::publishBinarySensor] size of buffer: %d\r\n", byte);
    publish(configTopic, buffer);
}

void MqttHandleVedirectHassClass::createDeviceInfo(JsonObject& object)
{
    String serial = VeDirect.veFrame.SER;
    object[F("name")] = "Victron(" + serial + ")";
    object[F("ids")] = serial;
    object[F("cu")] = String(F("http://")) + NetworkSettings.localIP().toString();
    object[F("mf")] = F("OpenDTU");
    object[F("mdl")] = VeDirect.getPidAsString(VeDirect.veFrame.PID);
    object[F("sw")] = AUTO_GIT_HASH;
}

void MqttHandleVedirectHassClass::publish(const String& subtopic, const String& payload)
{
    String topic = Configuration.get().Mqtt_Hass_Topic;
    topic += subtopic;
    MqttSettings.publishGeneric(topic.c_str(), payload.c_str(), Configuration.get().Mqtt_Hass_Retain);
}