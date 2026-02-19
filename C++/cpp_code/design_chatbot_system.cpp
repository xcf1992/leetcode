/*
https://www.hack2hire.com/companies/openai/coding-questions/69190ae16723130c5456345b/practice?questionId=69190b156723130c5456345c
Design ChatBot System

You are building a chat system that supports human users and automated bots. Users can send messages to a shared
channel, which may contain multiple users and multiple bots. Bots can respond to specific commands.

The system must be extensible so new bot types can be added without modifying existing logic. For simplicity, you can
assume there's only one shared channel in the system.

You need to implement the ChatApp class, which is responsible for managing channels and processing messages. When a user
sends a message, the message should first be added to the channel's message log. After that, each bot may react to the
message and add its own output to the same log.

The system must support the following three bot types:

AwayBot: Records that a user is away in that specific channel

Triggered when a message starts with "/away ".
Adds the message: "AwayBot: <user> is away: <reason>".
TacoBot: Gives tacos from one user to another

Triggered with the command: "/givetaco @<recipient> <count>".

If <count> is not provided, it defaults to 1.

Tracks taco totals per user, per channel.

Adds a message reflecting the updated count, using the correct singular or plural form, such as:

"TacoBot: @<giver> gave @<recipient> 1 taco. @<recipient> now has 1 taco."
"TacoBot: @<giver> gave @<recipient> 2 tacos. @<recipient> now has 3 tacos."
MeetBot: Sets up a one-on-one meeting and marks the involved users as away

Triggered by: "/meet <targetUser>".

This bot works together with AwayBot in the following way:

If <targetUser> is currently away, AwayBot must output its away message first, for example: "AwayBot: <targetUser> is
away: <reason>". After the optional AwayBot output, MeetBot adds its own message: "MeetBot: Google Meet with @<sender>,
and <targetUser> starting at /abc-def-123". Finally, it marks both the <sender> and <targetUser> as away in that
channel, using the reason "@<user> may be in a meeting right now". Implement the ChatApp class:

ChatApp() Initializes the chat system.
void sendMessage(String name, String text) A user specified by name sends a message with text content to the channel.
This action may trigger responses from one or more bots. List<String> getMessages() Returns a list of all messages from
the channel, in the exact order they were processed. This includes both user-sent messages and bot-generated responses.
Constraints:

Bot command messages (e.g., "/away", "/meet", "/givetaco") are guaranteed to be in a valid format if they match the
command prefix. The total number of calls to sendMessage will be between 0 and 1000. Example:

Input:
["ChatApp", "sendMessage", "sendMessage", "sendMessage", "sendMessage", "sendMessage", "sendMessage", "sendMessage",
"sendMessage", "sendMessage", "sendMessage", "getMessages"]

[[], ["general", "Alice", "Hello"], ["general", "Bob", "Hi"], ["general", "Alice", "Nice job on your presentations"],
["general", "Cindy", "/givetaco @justin"], ["general", "Bob", "/givetaco @justin 2"], ["general", "Alice", "Bob let's
meet"], ["general", "Bob", "/meet Alice"], ["general", "David", "/away out for lunch"], ["general", "Emily", "Anyone
around?"], ["general", "Frank", "/meet David"], []]

Output:
[null, null, null, null, null, null, null, null, null, null, null,
  ["Alice: Hello",
   "Bob: Hi",
   "Alice: Nice job on your presentations",
   "Cindy: /givetaco @justin",
   "TacoBot: @Cindy gave @justin 1 taco. @justin now has 1 taco.",
   "Bob: /givetaco @justin 2",
   "TacoBot: @Bob gave @justin 2 tacos. @justin now has 3 tacos.",
   "Alice: Bob let's meet",
   "Bob: /meet Alice",
   "MeetBot: Google Meet with @Bob, and Alice starting at /abc-def-123",
   "David: /away out for lunch",
   "AwayBot: David is away: out for lunch",
   "Emily: Anyone around?",
   "Frank: /meet David",
   "AwayBot: David is away: out for lunch",
   "MeetBot: Google Meet with @Frank, and David starting at /abc-def-123"]]

Explanation:

ChatApp chatApp = new ChatApp();
chatApp.sendMessage("Alice", "Hello"); // Message added.
chatApp.sendMessage("Bob", "Hi");
chatApp.sendMessage("Alice", "Nice job on your presentations");
chatApp.sendMessage("Cindy", "/givetaco @justin"); // Triggers TacoBot. @justin's "general" count is 1.
chatApp.sendMessage("Bob", "/givetaco @justin 2"); // Triggers TacoBot. @justin's "general" count is 3.
chatApp.sendMessage("Alice", "Bob let's meet");
chatApp.sendMessage("Bob", "/meet Alice"); // Triggers MeetBot. Alice is not away.
chatApp.sendMessage("David", "/away out for lunch"); // Triggers AwayBot. David is now away.
chatApp.sendMessage("Emily", "Anyone around?");
chatApp.sendMessage("Frank", "/meet David"); Triggers MeetBot. David is away, so AwayBot responds first, then MeetBot.
chatApp.getMessages(); // Returns the 16 messages from the "general" channel as shown above.

*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <map>
#include <functional>
#include <typeindex>
#include <memory>
#include <sstream>
#include <any>
using namespace std;

class Channel;
class EventBus;

// ==================== Event ====================
class EventBus {
public:
    std::map<std::type_index, std::vector<std::function<void(std::any)>>> handlers;

    template <typename E>
    void subscribe(std::function<void(E)> handler) {
        std::type_index eventType = std::type_index(typeid(E));
        if (handlers.find(eventType) == handlers.end()) {
            handlers[eventType] = std::vector<std::function<void(std::any)>>();
        }
        handlers[eventType].push_back([handler](std::any event) { handler(std::any_cast<E>(event)); });
    }

    template <typename E>
    void publish(E event) {
        std::type_index eventType = std::type_index(typeid(E));
        if (handlers.find(eventType) != handlers.end()) {
            std::vector<std::function<void(std::any)>>& eventHandlers = handlers[eventType];
            for (auto& handler : eventHandlers) {
                handler(std::any(event));
            }
        }
    }
};

class UserMessageEvent {
public:
    std::string name;
    std::string text;

    UserMessageEvent(std::string name, std::string text) : name(name), text(text) {
    }
};

class AwaySetEvent {
public:
    std::string name;
    std::string reason;

    AwaySetEvent(std::string name, std::string reason) : name(name), reason(reason) {
    }
};

class AwayNotifyEvent {
public:
    std::string name;
    std::string reason;

    AwayNotifyEvent(std::string name, std::string reason) : name(name), reason(reason) {
    }
};

class Channel {
public:
    std::vector<std::string>& messages;
    std::map<std::string, std::string> awayMap;
    std::map<std::string, int> tacoMap;

    Channel(std::vector<std::string>& messages) : messages(messages) {
    }

    void push(std::string line) {
        messages.push_back(line);
    }
};

// ==================== Bot ====================
class Bot {
public:
    virtual void init(Channel* context, EventBus* eventBus) = 0;
};

class AwayBot : public Bot {
private:
    Channel* context;
    EventBus* eventBus;

public:
    void init(Channel* context, EventBus* eventBus) override {
        this->context = context;
        this->eventBus = eventBus;

        eventBus->subscribe<UserMessageEvent>([this](UserMessageEvent event) { this->handleUserMessage(event); });
        eventBus->subscribe<AwayNotifyEvent>([this](AwayNotifyEvent event) { this->handleAwayNotify(event); });
        eventBus->subscribe<AwaySetEvent>([this](AwaySetEvent event) { this->handleAwaySet(event); });
    }

private:
    void handleUserMessage(UserMessageEvent event) {
        std::string text = event.text;
        if (text.substr(0, 6) == "/away ") {
            std::string reason = text.substr(6);
            std::string name = event.name;

            context->push("AwayBot: " + name + " is away: " + reason);
            eventBus->publish(AwaySetEvent(name, reason));
        }
    }

    void handleAwayNotify(AwayNotifyEvent event) {
        context->push("AwayBot: " + event.name + " is away: " + event.reason);
    }

    void handleAwaySet(AwaySetEvent event) {
        context->awayMap[event.name] = event.reason;
    }
};

class MeetBot : public Bot {
private:
    Channel* context;
    EventBus* eventBus;

public:
    void init(Channel* context, EventBus* eventBus) override {
        this->context = context;
        this->eventBus = eventBus;

        eventBus->subscribe<UserMessageEvent>([this](UserMessageEvent event) { this->handleUserMessage(event); });
    }

private:
    void handleUserMessage(UserMessageEvent event) {
        std::string text = event.text;
        if (text.substr(0, 6) == "/meet ") {
            std::string target = text.substr(6);
            std::string sender = event.name;

            std::map<std::string, std::string>& awayMap = context->awayMap;

            // Check if either participant is away and notify
            if (awayMap.find(target) != awayMap.end()) {
                eventBus->publish(AwayNotifyEvent(target, awayMap[target]));
            }

            // Announce the meeting
            context->push("MeetBot: Google Meet with @" + sender + ", and " + target + " starting at /abc-def-123");

            // Mark both as away
            eventBus->publish(AwaySetEvent(sender, "@" + sender + " may be in a meeting right now"));
            eventBus->publish(AwaySetEvent(target, "@" + target + " may be in a meeting right now"));
        }
    }
};

class TacoBot : public Bot {
private:
    Channel* context;

public:
    void init(Channel* context, EventBus* eventBus) override {
        this->context = context;

        eventBus->subscribe<UserMessageEvent>([this](UserMessageEvent event) { this->handleUserMessage(event); });
    }

private:
    void handleUserMessage(UserMessageEvent event) {
        std::string text = event.text;
        if (text.substr(0, 10) == "/givetaco ") {
            std::istringstream iss(text);
            std::vector<std::string> parts;
            std::string part;
            while (iss >> part) {
                parts.push_back(part);
            }

            if (parts.size() >= 2) {
                std::string recipient = parts[1];
                std::string giver = event.name;

                int tacoCount = 1;
                if (parts.size() >= 3) {
                    tacoCount = std::stoi(parts[2]);
                }

                std::map<std::string, int>& tacoMap = context->tacoMap;
                int currentTacos = 0;
                if (tacoMap.find(recipient) != tacoMap.end()) {
                    currentTacos = tacoMap[recipient];
                }

                int newTacos = currentTacos + tacoCount;
                tacoMap[recipient] = newTacos;

                std::string tacoWord = tacoCount == 1 ? "taco" : "tacos";
                std::string totalTacoWord = newTacos == 1 ? "taco" : "tacos";
                context->push("TacoBot: @" + giver + " gave " + recipient + " " + std::to_string(tacoCount) + " " +
                              tacoWord + ". " + recipient + " now has " + std::to_string(newTacos) + " " +
                              totalTacoWord + ".");
            }
        }
    }
};

class ChatApp {
public:
    std::vector<std::string> messages;
    EventBus eventBus;
    Channel* channel;

    ChatApp() {
        this->channel = new Channel(messages);
        registerAllBots(channel, &eventBus);
    }

    void sendMessage(std::string name, std::string text) {
        messages.push_back(name + ": " + text);
        eventBus.publish(UserMessageEvent(name, text));
    }

    std::vector<std::string> getMessages() {
        return std::vector<std::string>(messages);
    }

private:
    void registerAllBots(Channel* ctx, EventBus* bus) {
        (new AwayBot())->init(ctx, bus);
        (new MeetBot())->init(ctx, bus);
        (new TacoBot())->init(ctx, bus);
    }
};

class Solution {
public:
    static void main() {
        test1();
        test2();
    }

private:
    static void test1() {
        std::cout << "===== Test 1 =====" << std::endl;
        ChatApp app;

        app.sendMessage("Alice", "Hello");
        app.sendMessage("Bob", "Hi");
        app.sendMessage("Alice", "Nice job on your presentations");
        app.sendMessage("Cindy", "/givetaco @justin");
        app.sendMessage("Bob", "/givetaco @justin 2");
        app.sendMessage("Alice", "Bob let's meet");
        app.sendMessage("Bob", "/meet Alice");
        app.sendMessage("David", "/away out for lunch");
        app.sendMessage("Emily", "Anyone around?");
        app.sendMessage("Frank", "/meet David");

        std::vector<std::string> messages = app.getMessages();
        std::cout << "[";
        for (size_t i = 0; i < messages.size(); ++i) {
            std::cout << "\"" << messages[i] << "\"";
            if (i < messages.size() - 1)
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;
        // Expected: ["Alice: Hello",
        // "Bob: Hi",
        // "Alice: Nice job on your presentations",
        // "Cindy: /givetaco @justin",
        // "TacoBot: @Cindy gave @justin 1 taco. @justin now has 1 taco.",
        // "Bob: /givetaco @justin 2",
        // "TacoBot: @Bob gave @justin 2 tacos. @justin now has 3 tacos.",
        // "Alice: Bob let's meet",
        // "Bob: /meet Alice",
        // "MeetBot: Google Meet with @Bob, and Alice starting at /abc-def-123",
        // "David: /away out for lunch",
        // "AwayBot: David is away: out for lunch",
        // "Emily: Anyone around?",
        // "Frank: /meet David",
        // "AwayBot: David is away: out for lunch",
        // "MeetBot: Google Meet with @Frank, and David starting at /abc-def-123"]
    }

    static void test2() {
        std::cout << std::endl << "===== Test 2 =====" << std::endl;
        ChatApp app;

        app.sendMessage("Alice", "/away on vacation");
        app.sendMessage("Bob", "/away sick today");
        app.sendMessage("Charlie", "/meet Alice");
        app.sendMessage("David", "Hello everyone");
        app.sendMessage("Eve", "/meet Bob");

        std::vector<std::string> messages = app.getMessages();
        std::cout << "[";
        for (size_t i = 0; i < messages.size(); ++i) {
            std::cout << "\"" << messages[i] << "\"";
            if (i < messages.size() - 1)
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;
        // Expected: ["Alice: /away on vacation",
        // "AwayBot: Alice is away: on vacation",
        // "Bob: /away sick today",
        // "AwayBot: Bob is away: sick today",
        // "Charlie: /meet Alice",
        // "AwayBot: Alice is away: on vacation",
        // "MeetBot: Google Meet with @Charlie, and Alice starting at /abc-def-123",
        // "David: Hello everyone",
        // "Eve: /meet Bob",
        // "AwayBot: Bob is away: sick today",
        // "MeetBot: Google Meet with @Eve, and Bob starting at /abc-def-123"]
    }
};

int main() {
    Solution::main();
    return 0;
}