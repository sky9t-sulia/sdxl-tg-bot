#ifndef REQUESTSENDER_H
#define REQUESTSENDER_H

#include <ArduinoJson.h>
#include <HTTPClient.h>

/**
 * Class to send HTTP requests.
 */
class RequestSender
{
public:
    /**
     * Constructor for the RequestSender class.
     *
     * @param token The token to use for authentication.
     */
    RequestSender(const String &token);

    /**
     * Send a GET request to the specified endpoint.
     *
     * @param endpoint The endpoint to send the request to.
     * @param response The JsonDocument to store the response in.
     * @return true if the request was successful, false otherwise.
     */
    bool getRequest(const String &endpoint, JsonDocument &response);

    /**
     * Send a POST request to the specified endpoint.
     *
     * @param endpoint The endpoint to send the request to.
     * @param response The JsonDocument to store the response in.
     * @param data The data to send in the request body.
     * @return true if the request was successful, false otherwise.
     */
    bool postRequest(const String &endpoint, JsonDocument &response, const String &data);

private:
    String monsterapiToken; ///< The token to use for authentication.

    /**
     * Send a request to the specified endpoint.
     *
     * @param endpoint The endpoint to send the request to.
     * @param response The JsonDocument to store the response in.
     * @param type The type of the request (e.g., "GET", "POST").
     * @param data The data to send in the request body (optional).
     * @return true if the request was successful, false otherwise.
     */
    bool sendRequest(const String &endpoint, JsonDocument &response, const String &type, const String &data = "");

    /**
     * Handle the response from the server.
     *
     * @param http The HTTPClient instance.
     * @param response The JsonDocument to store the response in.
     * @return true if the response was handled successfully, false otherwise.
     */
    bool handleResponse(HTTPClient &http, JsonDocument &response);

    /**
     * Close the connection.
     *
     * @param http The HTTPClient instance.
     */
    void closeConnection(HTTPClient &http);
};

#endif // REQUESTSENDER_H