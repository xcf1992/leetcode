/*
https://www.hack2hire.com/companies/reddit/coding-questions/6945c23f2c048134ada834f1/practice?questionId=6945c50a2c048134ada834f9
Chat Message Range Merge
A chat application maintains a history of messages, where each message is identified by a unique, strictly increasing
integer id and contains a string content. The messages are stored in ascending order by id.

Each message is represented by a provided data model. You may assume the following structure for a message, and you
should treat it as read-only in this problem.

class Message {
    int id;
    String content;
}
You are given access to a chat system that allows querying messages around a specific message ID. Given the
getChatMessages API:

This is a provided API class.
class Chat {
    **
     * Returns a list of messages centered at the given message ID.
     *
     * @param id The target message ID.
     * @param windowSize The number of messages to include before and after the target ID.
     * @return A list containing the message with the given ID and up to windowSize messages
     *         before and after it. The returned list is sorted by message id in ascending order.
     *         If the given id does not exist, an empty list is returned.
     *
    public List<Message> getChatMessages(int id, int windowSize);
}
Implement the ChatMessageMerger class:

ChatMessageMerger(Chat chat, int windowSize) Initializes the merger with a provided chat object and a windowSize. All
queries will use this windowSize to determine how many messages before and after each ID are included.

List<Message> mergeMessages(List<Integer> ids) Retrieves and merges all non-duplicate context messages for the given
list of message IDs.

For each message ID, its context window includes the message itself and up to windowSize messages before and after it.
The returned list contains unique messages only and must be sorted by message id in ascending order.
Note: Your solution must run in time complexity better than O(M∗logM), where
M is the total context message of the input ID list.

Constraints:

ids may contain up to k elements ( 1 <= k <= 10^6)
Each call to getChatMessages returns at most 2 × windowSize + 1 messages.
Example

Input:
["ChatMessageMerger", "mergeMessages"]
["Chat([[1, "Hello"], [2, "World"], [3, "How"], [4, "Are"], [5, "You"], [6, "Today"], [7, "Friend"], [8, "Nice"], [9,
"Weather"], [10, "Right"]])", 1], [[3, 7]]]

Output:
[null, [[2, "World"], [3, "How"], [4, "Are"], [6, "Today"], [7, "Friend"], [8, "Nice"]]]

Explanation:

Chat chat = new Chat([[1, "Hello"], [2, "World"], [3, "How"], [4, "Are"], [5, "You"], [6, "Today"], [7, "Friend"], [8,
"Nice"], [9, "Weather"], [10, "Right"]]); // Initializes the chat history with messages sorted by id. ChatMessageMerger
merger = new ChatMessageMerger(chat, 1); // Creates a merger with windowSize = 1. merger.mergeMessages([3, 7]); //
Returns [[2, "World"], [3, "How"], [4, "Are"], [6, "Today"], [7, "Friend"], [8, "Nice"]].

*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <climits>
#include <map>
using namespace std;

class Message {
public:
    int id;
    string content;

    Message(int id, string content) : id(id), content(content) {
    }

    string toString() const {
        return "[" + to_string(id) + ": " + content + "]";
    }
};

/**
 * External API that checks if a version supports a specific feature. You should
 * NOT directly access the `messages`.
 */
class Chat {
private:
    vector<Message> messages;

    int findIndex(int id) {
        for (int i = 0; i < messages.size(); i++) {
            if (messages[i].id == id) {
                return i;
            }
        }
        return -1;
    }

public:
    Chat(vector<Message> messages) : messages(messages) {
    }

    vector<Message> getChatMessages(int id, int windowSize) {
        vector<Message> result;
        int idx = findIndex(id);
        if (idx == -1) {
            return result;
        }

        int start = max(0, idx - windowSize);
        int end = min((int)messages.size() - 1, idx + windowSize);

        for (int i = start; i <= end; i++) {
            result.push_back(messages[i]);
        }

        return result;
    }
};

struct myComp {
    bool operator()(pair<Message, pair<int, int>>& a, pair<Message, pair<int, int>>& b) {
        return a.first.id > b.first.id;
    }
};

class ChatMessageMerger {
private:
    Chat chat;
    int windowSize;

public:
    ChatMessageMerger(Chat chat, int windowSize) : chat(chat), windowSize(windowSize) {
    }

    vector<Message> mergeMessages(vector<int> ids) {
        if (ids.empty()) {
            return {};
        }

        vector<vector<Message>> msg_list;
        for (int id : ids) {
            vector<Message> messages = chat.getChatMessages(id, windowSize);
            if (!messages.empty()) {
                msg_list.push_back(messages);
            }
        }

        if (msg_list.empty()) {
            return {};
        }

        priority_queue<pair<Message, pair<int, int>>, vector<pair<Message, pair<int, int>>>, myComp> pq;
        for (int i = 0; i < msg_list.size(); i++) {
            Message& msg = msg_list[i][0];
            pq.push({msg, {i, 0}});
        }

        vector<Message> rst;
        while (!pq.empty()) {
            Message msg = pq.top().first;
            int list_idx = pq.top().second.first;
            int msg_idx = pq.top().second.second;
            pq.pop();

            rst.push_back(msg);
            msg_idx += 1;
            if (msg_idx < msg_list[list_idx].size()) {
                pq.push({msg_list[list_idx][msg_idx], {list_idx, msg_idx}});
            }
        }
        return rst;
    }

    static void test1() {
        cout << "===== Test 1 =====" << endl;
        vector<Message> messages = {Message(1, "Hello"),  Message(2, "World"), Message(3, "How"),
                                    Message(4, "Are"),    Message(5, "You"),   Message(6, "Today"),
                                    Message(7, "Friend"), Message(8, "Nice"),  Message(9, "Weather"),
                                    Message(10, "Right")};

        Chat chat(messages);
        ChatMessageMerger merger(chat, 1);
        vector<Message> result = merger.mergeMessages({3, 7});
        cout << "[";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i].toString();
            if (i < result.size() - 1)
                cout << ", ";
        }
        cout << "]" << endl;
        // Expected: [[2: "World"], [3: "How"], [4: "Are"], [6: "Today"], [7: "Friend"],
        // [8: "Nice"]]
    }

    static void test2() {
        cout << "\n===== Test 2 =====" << endl;
        vector<Message> messages;
        for (int i = 1; i <= 20; i++) {
            messages.push_back(Message(i, "Msg" + to_string(i)));
        }

        Chat chat(messages);
        ChatMessageMerger merger(chat, 2);
        vector<Message> result = merger.mergeMessages({5, 15});
        cout << "[";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i].toString();
            if (i < result.size() - 1)
                cout << ", ";
        }
        cout << "]" << endl;
        // Expected: [[3: "Msg3"], [4: "Msg4"], [5: "Msg5"], [6: "Msg6"], [7: "Msg7"],
        // [13: "Msg13"], [14: "Msg14"], [15: "Msg15"], [16: "Msg16"], [17: "Msg17"]]
    }

    static void test3() {
        cout << "\n===== Test 3 =====" << endl;
        vector<Message> messages;
        for (int i = 1; i <= 30; i++) {
            messages.push_back(Message(i, "Message" + to_string(i)));
        }

        Chat chat(messages);
        ChatMessageMerger merger(chat, 2);
        vector<Message> result = merger.mergeMessages({10, 15, 20});
        cout << "[";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i].toString();
            if (i < result.size() - 1)
                cout << ", ";
        }
        cout << "]" << endl;
        // Expected: [[8: "Message8"], [9: "Message9"], [10: "Message10"], [11:
        // "Message11"], [12: "Message12"], [13: "Message13"], [14: "Message14"], [15:
        // "Message15"], [16: "Message16"], [17: "Message17"], [18: "Message18"], [19:
        // "Message19"], [20: "Message20"], [21: "Message21"], [22: "Message22"]]
    }

    static void test4() {
        cout << "\n===== Test 4 =====" << endl;
        vector<Message> messages;
        for (int i = 1; i <= 15; i++) {
            messages.push_back(Message(i, "Item" + to_string(i)));
        }

        Chat chat(messages);
        ChatMessageMerger merger(chat, 2);
        vector<Message> result = merger.mergeMessages({2, 13});
        cout << "[";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i].toString();
            if (i < result.size() - 1)
                cout << ", ";
        }
        cout << "]" << endl;
        // Expected: [[1: "Item1"], [2: "Item2"], [3: "Item3"], [4: "Item4"], [11:
        // "Item11"], [12: "Item12"], [13: "Item13"], [14: "Item14"], [15: "Item15"]]
    }

    static void test5() {
        cout << "\n===== Test 5 =====" << endl;
        vector<Message> messages = {Message(1, "First"), Message(2, "Second"), Message(3, "Third"),
                                    Message(4, "Fourth"), Message(5, "Fifth")};

        Chat chat(messages);
        ChatMessageMerger merger(chat, 1);
        vector<Message> result = merger.mergeMessages({1});
        cout << "[";
        for (int i = 0; i < result.size(); i++) {
            cout << result[i].toString();
            if (i < result.size() - 1)
                cout << ", ";
        }
        cout << "]" << endl;
        // Expected: [[1: "First"], [2: "Second"]]
    }

    static void main() {
        test1();
        test2();
        test3();
        test4();
        test5();
    }
};

int main() {
    ChatMessageMerger::main();
    return 0;
}

/*
Follow-up:
Extend the chat system to support editing of each message with a full version history. Every message is uniquely
identified by id and can be updated multiple times. Each update creates a new version, but earlier versions must remain
accessible.

Extend the Message class and support the following:

Message(int id, String content) Creates a message with a unique id and initial content. The initial version number is 1.

void updateContent(String newContent) Updates the message with newContent, creating a new version. Each call to this
method increments the version number by 1, assigns the new content to that version, and preserves all previous versions
so they remain accessible.

String getLatestContent() Returns the content of the latest version of the message.

String getContent(int version) Returns the content of the given version. If that version does not exist, return "".

Besides, mergeMessages function continues to sort, deduplicate, and merge messages using only id, and always displays
the latest version content. Older versions are not shown unless directly requested via getContent(version) function.

Constraints:

There are up to n messages in the chat, 1<= n <= 10^6
Each message may have up to m versions, 1 <= m <= 10^6
Example

Input:
["Message", "getLatestContent", "updateContent", "getLatestContent", "updateContent", "getLatestContent", "getContent",
"getContent", "getContent", "Chat", "ChatMessageMerger", "mergeMessages"]
[[1, "Draft"], [], ["Draft v2"], [], ["Final"], [], [1], [2], [3], [[Message(1), Message(2), Message(3)]], [chat, 1],
[[2]]]

Output:
[null, "Draft", null, "Draft v2", null, "Final", "Draft", "Draft v2", "Final", null, null, [[1, "Final"], [2, "Hello"],
[3, "World"]]]

Explanation:

Message msg = new Message(1, "Draft");
msg.getLatestContent(); // Returns "Draft".
msg.updateContent("Draft v2");
msg.getLatestContent(); // Returns "Draft v2".
msg.updateContent("Final");
msg.getLatestContent(); // Returns "Final".
msg.getContent(1); // Returns "Draft".
msg.getContent(2); // Returns "Draft v2".
msg.getContent(3); // Returns "Final".
Chat chat = new Chat([msg, Message(2, "Hello"), Message(3, "World")]);
ChatMessageMerger merger = new ChatMessageMerger(chat, 1);
merger.mergeMessages([2]); // Returns [[1, "Final"], [2, "Hello"], [3, "World"]], using the latest version of each
message.
*/
class Message {
public:
    int id;

private:
    int latestVersion;
    std::unordered_map<int, std::string> versionHistory;

public:
    Message(int id, const std::string& content) {
        this->id = id;
        this->latestVersion = 1;
        this->versionHistory[latestVersion] = content;
    }

    void updateContent(const std::string& newContent) {
        latestVersion += 1;
        versionHistory[latestVersion] = newContent;
    }

    std::string getLatestContent() {
        return versionHistory[latestVersion];
    }

    std::string getContent(int version) {
        if (versionHistory.find(version) == versionHistory.end()) {
            return "";
        }
        return versionHistory[version];
    }

    std::string toString() {
        return "[" + std::to_string(id) + ": \"" + getLatestContent() + "\"]";
    }
};

/**
* External API that checks if a version supports a specific feature. You should
* NOT directly access the `messages`.
*/
class Chat {
private:
    std::vector<Message> messages;

public:
    Chat(const std::vector<Message>& messages) {
        this->messages = messages;
    }

    std::vector<Message> getChatMessages(int id, int windowSize) {
        std::vector<Message> result;
        int idx = -1;
        for (int i = 0; i < messages.size(); i++) {
            if (messages[i].id == id) {
                idx = i;
                break;
            }
        }

        if (idx == -1) {
            return result;
        }

        int start = std::max(0, idx - windowSize);
        int end = std::min((int)messages.size() - 1, idx + windowSize);

        for (int i = start; i <= end; i++) {
            result.push_back(messages[i]);
        }

        return result;
    }
};

struct myComp {
    bool operator()(pair<Message, pair<int, int>>& a, pair<Message, pair<int, int>>& b) {
        return a.first.id > b.first.id;
    }
};

class ChatMessageMerger {
private:
    Chat chat;
    int windowSize;

public:
    ChatMessageMerger(const Chat& chat, int windowSize)
        : chat(chat), windowSize(windowSize) {
    }

    vector<Message> mergeMessages(vector<int> ids) {
        if (ids.empty()) {
            return {};
        }

        vector<vector<Message>> msg_list;
        for (int id : ids) {
            vector<Message> messages = chat.getChatMessages(id, windowSize);
            if (!messages.empty()) {
                msg_list.push_back(messages);
            }
        }

        if (msg_list.empty()) {
            return {};
        }

        priority_queue<pair<Message, pair<int, int>>, vector<pair<Message, pair<int, int>>>, myComp> pq;
        for (int i = 0; i < msg_list.size(); i++) {
            Message& msg = msg_list[i][0];
            pq.push({msg, {i, 0}});
        }

        vector<Message> rst;
        while (!pq.empty()) {
            Message msg = pq.top().first;
            int list_idx = pq.top().second.first;
            int msg_idx = pq.top().second.second;
            pq.pop();

            rst.push_back(msg);
            msg_idx += 1;
            if (msg_idx < msg_list[list_idx].size()) {
                pq.push({msg_list[list_idx][msg_idx], {list_idx, msg_idx}});
            }
        }
        return rst;
    }

    static void test1() {
        std::cout << "===== Test 1 =====" << std::endl;
        Message msg1(1, "Draft");
        Message msg2(2, "Hello");
        Message msg3(3, "World");

        std::cout << msg1.getLatestContent() << std::endl; // Expected: "Draft"

        msg1.updateContent("Draft v2");
        std::cout << msg1.getLatestContent() << std::endl; // Expected: "Draft v2"

        msg1.updateContent("Final");
        std::cout << msg1.getLatestContent() << std::endl; // Expected: "Final"

        std::cout << msg1.getContent(1) << std::endl; // Expected: "Draft"
        std::cout << msg1.getContent(2) << std::endl; // Expected: "Draft v2"
        std::cout << msg1.getContent(3) << std::endl; // Expected: "Final"

        std::vector<Message> messages = {msg1, msg2, msg3};
        Chat chat(messages);
        ChatMessageMerger merger(chat, 1);

        std::vector<int> ids = {2};
        std::vector<Message> result = merger.mergeMessages(ids);
        std::cout << "[";
        for (int i = 0; i < result.size(); i++) {
            if (i > 0) std::cout << ", ";
            std::cout << result[i].toString();
        }
        std::cout << "]" << std::endl;
        // Expected: [[1: "Final"], [2: "Hello"], [3: "World"]]
    }

    static void test2() {
        std::cout << "\n===== Test 2 =====" << std::endl;
        std::vector<Message> messages = {Message(1, "Hello"), Message(2, "World"),
                Message(3, "How"), Message(4, "Are"), Message(5, "You")};
        messages[1].updateContent("World Updated");
        messages[3].updateContent("Are Updated");

        Chat chat(messages);
        ChatMessageMerger merger(chat, 1);
        std::vector<Message> result = merger.mergeMessages({2, 4});
        std::cout << "[";
        for (int i = 0; i < result.size(); i++) {
            if (i > 0) std::cout << ", ";
            std::cout << result[i].toString();
        }
        std::cout << "]" << std::endl;
        // Expected: [[1: "Hello"], [2: "World Updated"], [3: "How"], [4: "Are
        // Updated"], [5: "You"]]
    }

    static void test3() {
        std::cout << "\n===== Test 3 =====" << std::endl;
        Message msg1(10, "Version 1");
        msg1.updateContent("Version 2");
        msg1.updateContent("Version 3");
        msg1.updateContent("Version 4");

        Message msg2(20, "Original");

        Message msg3(30, "First");
        msg3.updateContent("Second");

        std::vector<Message> messages = {msg1, msg2, msg3};

        Chat chat(messages);
        ChatMessageMerger merger(chat, 1);

        std::vector<Message> result = merger.mergeMessages({20});
        std::cout << "[";
        for (int i = 0; i < result.size(); i++) {
            if (i > 0) std::cout << ", ";
            std::cout << result[i].toString();
        }
        std::cout << "]" << std::endl;
        // Expected: [[10: "Version 4"], [20: "Original"], [30: "Second"]]

        std::cout << msg1.getContent(1) << std::endl; // Expected: "Version 1"
        std::cout << msg1.getContent(2) << std::endl; // Expected: "Version 2"
        std::cout << msg1.getContent(3) << std::endl; // Expected: "Version 3"
        std::cout << msg1.getContent(4) << std::endl; // Expected: "Version 4"
    }

    static void test4() {
        std::cout << "\n===== Test 4 =====" << std::endl;
        std::vector<Message> messages;
        for (int i = 1; i <= 20; i++) {
            messages.push_back(Message(i, "Msg" + std::to_string(i)));
        }
        messages[4].updateContent("Msg5 Updated");
        messages[4].updateContent("Msg5 Final");
        messages[14].updateContent("Msg15 Updated");

        Chat chat(messages);
        ChatMessageMerger merger(chat, 2);
        std::vector<Message> result = merger.mergeMessages({5, 15});
        std::cout << "[";
        for (int i = 0; i < result.size(); i++) {
            if (i > 0) std::cout << ", ";
            std::cout << result[i].toString();
        }
        std::cout << "]" << std::endl;
        // Expected: [[3: "Msg3"], [4: "Msg4"], [5: "Msg5 Final"], [6: "Msg6"], [7:
        // "Msg7"], [13: "Msg13"], [14: "Msg14"], [15: "Msg15 Updated"], [16: "Msg16"],
        // [17: "Msg17"]]
    }

    static void test5() {
        std::cout << "\n===== Test 5 =====" << std::endl;
        std::vector<Message> messages = {Message(1, "First"), Message(2, "Second"), Message(3, "Third")};

        Chat chat(messages);
        ChatMessageMerger merger(chat, 1);

        std::vector<Message> result = merger.mergeMessages({2});
        std::cout << "[";
        for (int i = 0; i < result.size(); i++) {
            if (i > 0) std::cout << ", ";
            std::cout << result[i].toString();
        }
        std::cout << "]" << std::endl;
        // Expected: [[1: "First"], [2: "Second"], [3: "Third"]]
    }

    static void main() {
        test1();
        test2();
        test3();
        test4();
        test5();
    }
};

int main() {
    ChatMessageMerger::main();
    return 0;
}