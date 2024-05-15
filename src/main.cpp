#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <FastBot2.h>
#include "request/RequestQueue.h"
#include "request/RequestSender.h"
#include "promptExtractor.h"
#include "TimedAction.h"
#include "staticText.h"

#include "env.h"

FastBot2 bot;
RequestQueue queue(10);
RequestSender sender(monsterapiToken);
TimedAction checkQueueAction(5000);

/**
 * Checks the request queue and processes each item.
 * If the request status is "COMPLETED", the item is removed from the queue and the file is sent.
 * If the request status is "FAILED", the item is removed from the queue and an error message is sent.
 */
void checkQueue()
{
    if (queue.isEmpty())
    {
        Serial.println("Nothing in queue...");
    }

    for (int i = 0; i < queue.size(); i++)
    {
        JsonDocument response;
        RequestQueueItem item = queue.getItem(i);

        if (!item.statusUrl.isEmpty())
        {
            if (sender.getRequest(item.statusUrl, response))
            {
                if (response["status"] == "COMPLETED")
                {
                    queue.remove(i);
                    String imageUrl = response["result"]["image_url"][0];
                    fb::File file("sdxl.jpg", fb::File::Type::photo, imageUrl);
                    file.chatID = item.chatId;
                    bot.sendFile(file);
                }

                if (response["status"] == "FAILED")
                {
                    queue.remove(i);
                    bot.sendMessage(fb::Message(response["result"]["errorMessage"], item.chatId));
                }
            }
        }
        response.clear();
    }
}

/**
 * Generates an image based on the provided text and sends it to the specified chat ID.
 *
 * @param text The text to generate the image from.
 * @param chatId The ID of the chat to send the image to.
 */
void generateImage(String text, String chatId)
{
    Prompts prompts;
    extractPrompts(text, prompts);

    if (prompts.prompt.isEmpty())
    {
        Serial.println("ERR: Prompt is empty");
        return;
    }

    JsonDocument data;
    JsonDocument response;
    data["steps"] = 30;
    data["style"] = prompts.style;
    data["prompt"] = prompts.prompt + ", 8k, UHD, highly detailed";
    data["enhance"] = false;
    data["samples"] = 1;
    data["optimize"] = false;
    data["negprompt"] = prompts.negativePrompt + ", deformed, bad anatomy, disfigured, poorly drawn face";
    data["safe_filter"] = false;
    data["aspect_ratio"] = prompts.orientation;
    data["guidance_scale"] = 7;

    String dataStr;
    serializeJson(data, dataStr);
    if (sender.postRequest(txt2imgEndpoint, response, dataStr))
    {
        // add to queue
        if (queue.add(response["status_url"], chatId))
        {
            bot.sendMessage(fb::Message(response["message"], chatId));
        }
        else
        {
            bot.sendMessage(fb::Message("Queue is full. Try again later.", chatId));
        }
    }
    else
    {
        bot.sendMessage(fb::Message("Unable to send request :(", chatId));
    }

    data.clear();
    response.clear();
}

/**
 * Validates the chat ID against a list of allowed chats.
 *
 * @param chatId The ID of the chat to validate.
 * @return true if the chat ID is in the list of allowed chats, false otherwise.
 */
bool validateChat(const String &chatId)
{
    for (int i = 0; i < allowedChatsLen; i++)
    {
        if (chatId == allowedChats[i])
        {
            return true;
        }
    }

    return false;
}

/**
 * Handles updates from the bot.
 *
 * @param u The update from the bot.
 */
void botUpdate(fb::Update &u)
{
    const String message = u.message().text().toString();
    const String chatId = u.message().chat().id();

    Serial.println(message);

    if (!validateChat(chatId))
    {
        bot.sendMessage(fb::Message("This chat can not be used for this bot.", chatId));
        return;
    }

    if (message.startsWith("/help"))
    {
        bot.sendMessage(fb::Message(helpMessage, chatId));
    }

    if (message.startsWith("/sdxl"))
    {
        generateImage(message, chatId);
    }
}

/*
 * Setup function
 */
void setup()
{
    Serial.begin(115200);
    WiFi.begin(SSID, PASS);

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }

    Serial.println("Connected to: " + String(SSID));

    bot.setToken(botToken);
    bot.attachUpdate(botUpdate);
    bot.skipUpdates();
}

/*
 * Main loop
 */
void loop()
{
    bot.tick();

    if (checkQueueAction.isTime())
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            checkQueue();
        }
    }
}
