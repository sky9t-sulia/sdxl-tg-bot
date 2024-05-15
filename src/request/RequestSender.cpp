#include "request/RequestSender.h"

RequestSender::RequestSender(const String &token) : monsterapiToken(token) {}

bool RequestSender::getRequest(const String &endpoint, JsonDocument &response)
{
    return sendRequest(endpoint, response, "GET");
}

bool RequestSender::postRequest(const String &endpoint, JsonDocument &response, const String &data)
{
    return sendRequest(endpoint, response, "POST", data);
}

bool RequestSender::sendRequest(const String &endpoint, JsonDocument &response, const String &type, const String &data)
{
    HTTPClient http;
    WiFiClientSecure client;

    client.setInsecure();

    if (!http.begin(client, endpoint))
    {
        Serial.println(String("ERROR: Failed to establish connection to " + endpoint));
        return false;
    }

    http.addHeader("Accept", "application/json");
    http.addHeader("Authorization", "Bearer " + monsterapiToken);

    int code = 0;

    if (type == "POST")
    {
        http.addHeader("Content-Type", "application/json");
        code = http.POST(data);

        if (code == HTTP_CODE_OK)
        {
            return handleResponse(http, response);
        }
    }

    if (type == "GET")
    {
        code = http.GET();

        if (code == HTTP_CODE_OK)
        {
            return handleResponse(http, response);
        }
    }

    Serial.println(String("ERROR: Failed to send request. Error code: " + String(code)));
    return false;
}

bool RequestSender::handleResponse(HTTPClient &http, JsonDocument &response)
{
    // Get response
    String responseStr = http.getString();
    DeserializationError jsonError = deserializeJson(response, responseStr);
    if (jsonError)
    {
        Serial.println(String("ERROR: Failed to parse JSON. Error message: " + String(jsonError.c_str())));
        closeConnection(http);
        return false;
    }

    closeConnection(http);
    return true;
}

void RequestSender::closeConnection(HTTPClient &http)
{
    http.end();
}