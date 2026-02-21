/*
https://www.hack2hire.com/companies/openai/coding-questions/691523c93f8671d8f7a56570/practice?questionId=691523d03f8671d8f7a56571
Design Persistent Key-Value Store

You are designing a persistent key-value store that supports saving and restoring its data using a binary middleware
medium. The system should store only string keys and string values and be able to serialize its entire state to a binary
blob for durability across restarts.

A storage interface called Medium is provided, allowing you to save and retrieve a single binary blob. The
implementation is in InMemoryMedium.

// This is a provided API interface.
interface Medium {

     * Saves a byte array to the storage medium (e.g., file, in-memory).
     * @param data The byte array to persist.

    void saveBlob(byte[] data);


     * Retrieves the most recently saved byte array from the storage medium.
     * @return The stored byte array, or null if nothing is saved.

    byte[] getBlob();
}
You need to implement the KVStore class, ensuring that the binary serialization format can exactly recover all string
keys and values, including those with Unicode characters or empty strings. Native object serialization (such as direct
use of language-specific serialization, or JSON) is not allowed. You must construct your own serialization format.

Implement the KVStore class:

KVStore(Medium medium) Initializes a new, empty key-value store using the provided storage medium. The store only
interacts with data via this medium.

void put(String key, String value) Stores the specified value associated with the given key. If the key already exists,
its value is updated.

String get(String key) Returns the value associated with key. If the key is not present, it returns the empty string "".

void shutdown() Serializes the current store into a custom binary format and writes it to the associated medium. After
shutdown, the instance becomes closed, any subsequent get or put must fail and throw an error.

void restore() Loads the key-value data from the binary blob saved in the medium, completely replacing the in-memory
store. If the blob is missing or empty, the store should become empty.

Constraints:

Keys and values are arbitrary strings (may include Unicode and empty strings).
After calling shutdown, the instance is permanently closed; further calls to get or put must fail.
The restore method always replaces the in-memory state, discarding any unsaved changes.
1 ≤ number of keys ≤ 10⁴.
Total size of all keys and values together ≤ 10⁶ characters.
Each key and value is a string of length ≤ 10⁴.
All methods are called in a valid order (e.g., shutdown is not called twice in a row).
Example:

Input:
["InMemoryMedium", "KVStore", "put", "put", "put", "get", "get", "shutdown", "KVStore", "get", "put", "restore", "get",
"get", "get", "get"]
[[], [], ["key1", "value1"], ["key2", "value2_is_longer"], ["key3", "value3"], ["key1"], ["key4"], [], [medium],
["key1"], ["key4", "value4"], [], ["key1"], ["key2"], ["key3"], ["key4"]]

Output:
[null, null, null, null, null, "value1", "", null, null, "", null, null, "value1", "value2_is_longer", "value3", ""]

Explanation:

Medium medium = new InMemoryMedium();
KVStore store1 = new KVStore(medium); // Initializes a new store backed by medium.
store1.put("key1", "value1"); // Stores "key1" -> "value1".
store1.put("key2", "value2_is_longer"); // Stores "key2" -> "value2_is_longer".
store1.put("key3", "value3"); // Stores "key3" -> "value3".
store1.get("key1"); // Returns "value1".
store1.get("key4"); // Returns "".
store1.shutdown(); // Persists the current store and closes this instance.
KVStore store2 = new KVStore(medium); // Creates a new store with same medium.
store2.get("key1"); // Returns "", since nothing has been restored yet.
store2.put("key4", "value4"); // Adds "key4" -> "value4" to store2's in-memory map.
store2.restore(); // Loads the blob, replacing all in-memory data with what was persisted by store1.
store2.get("key1"); // Returns "value1", loaded from persisted state.
store2.get("key2"); // Returns "value2_is_longer".
store2.get("key3"); // Returns "value3".
store2.get("key4"); // Returns "", since "key4" was never persisted and was overwritten by restore.
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

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>
#include <sstream>
using namespace std;

/**
 * The Medium interface allows persisting and retrieving raw binary data.
 */
class Medium {
public:
    virtual void saveBlob(const std::vector<unsigned char>& data) = 0;
    virtual std::vector<unsigned char> getBlob() = 0;
};

/**
 * An in-memory implementation of the Medium interface for testing purposes.
 */
class InMemoryMedium : public Medium {
private:
    std::vector<unsigned char> storage;
    bool hasData = false;

public:
    void saveBlob(const std::vector<unsigned char>& data) override {
        this->storage = data;
        this->hasData = true;
    }

    std::vector<unsigned char> getBlob() override {
        if (!hasData) {
            return std::vector<unsigned char>();
        }
        return this->storage;
    }
};

class KVStore {
private:
    void writeInt(std::vector<unsigned char>& buffer, int value) {
        buffer.push_back((value >> 24) & 0xFF);
        buffer.push_back((value >> 16) & 0xFF);
        buffer.push_back((value >> 8) & 0xFF);
        buffer.push_back(value & 0xFF);
    }

    int readInt(const std::vector<unsigned char>& data, size_t& pos) {
        if (pos + 4 > data.size()) {
            throw std::runtime_error("readInt: data too short");
        }

        int value = (data[pos] << 24) | (data[pos + 1] << 16) | (data[pos + 2] << 8) | data[pos + 3];
        pos += 4;
        return value;
    }

    void writeBytes(std::vector<unsigned char>& buffer, const std::vector<unsigned char>& bytes) {
        buffer.insert(buffer.end(), bytes.begin(), bytes.end());
    }

    std::vector<unsigned char> readBytes(const std::vector<unsigned char>& data, size_t& pos, int length) {
        if (pos + length > data.size()) {
            throw std::runtime_error("Not enough data to read bytes");
        }

        vector<unsigned char> result(data.begin() + pos, data.begin() + pos + length);
        pos += length;
        return result;
    }

    std::vector<unsigned char> stringToBytes(const std::string& str) {
        return vector<unsigned char>(str.begin(), str.end());
    }

    std::string bytesToString(const std::vector<unsigned char>& bytes) {
        return std::string(bytes.begin(), bytes.end());
    }

private:
    std::unordered_map<std::string, std::string> key_to_val_;
    Medium* medium_;
    bool closed_;

public:
    KVStore(Medium* medium) {
        medium_ = medium;
        closed_ = false;
    }

    void put(const std::string& key, const std::string& value) {
        if (closed_) {
            return;
        }

        key_to_val_[key] = value;
    }

    std::string get(const std::string& key) {
        if (closed_) {
            return "";
        }

        if (key_to_val_.find(key) == key_to_val_.end()) {
            return "";
        }

        return key_to_val_[key];
    }

    void shutdown() {
        try {
            vector<unsigned char> buffer;
            writeInt(buffer, key_to_val_.size());

            for (auto& [key, val] : key_to_val_) {
                vector<unsigned char> key_bytes = stringToBytes(key);
                writeInt(buffer, key_bytes.size());
                writeBytes(buffer, key_bytes);

                vector<unsigned char> val_bytes = stringToBytes(val);
                writeInt(buffer, val_bytes.size());
                writeBytes(buffer, val_bytes);
            }

            medium_->saveBlob(buffer);
            closed_ = true;
        } catch (std::exception& e) {
            throw std::runtime_error("Exception thrown: " + std::string(e.what()));
        }
    }

    void restore() {
        vector<unsigned char> data = medium_->getBlob();
        if (data.empty()) {
            return;
        }

        try {
            key_to_val_.clear();
            size_t pos = 0;
            int total_cnt = readInt(data, pos);

            for (int i = 0; i < total_cnt; i++) {
                int key_len = readInt(data, pos);
                vector<unsigned char> key_bytes = readBytes(data, pos, key_len);
                string key = bytesToString(key_bytes);

                int val_len = readInt(data, pos);
                vector<unsigned char> val_bytes = readBytes(data, pos, val_len);
                string val = bytesToString(val_bytes);
                key_to_val_[key] = val;
            }
            closed_ = false;
        } catch (std::exception& e) {
            throw std::runtime_error("Exception thrown: " + std::string(e.what()));
        }
    }

    static void test1() {
        std::cout << "===== Test 1 =====" << std::endl;

        InMemoryMedium medium;
        KVStore store1(&medium);
        store1.put("key1", "value1");
        store1.put("key2", "value2_is_longer");
        store1.put("key3", "value3");
        std::cout << store1.get("key1") << std::endl;  // Expected: "value1"
        std::cout << store1.get("key4") << std::endl;  // Expected: ""
        store1.shutdown();

        KVStore store2(&medium);
        std::cout << store2.get("key1") << std::endl;  // Expected: ""
        store2.put("key4", "value4");

        store2.restore();
        std::cout << store2.get("key1") << std::endl;  // Expected: "value1"
        std::cout << store2.get("key2") << std::endl;  // Expected: "value2_is_longer"
        std::cout << store2.get("key3") << std::endl;  // Expected: "value3"
        std::cout << store2.get("key4") << std::endl;  // Expected: ""
    }

    static void test2() {
        std::cout << "\n===== Test 2 =====" << std::endl;

        InMemoryMedium medium;
        KVStore store1(&medium);
        store1.put("counter", "1");
        store1.put("status", "active");
        std::cout << store1.get("counter") << std::endl;  // Expected: "1"
        std::cout << store1.get("status") << std::endl;   // Expected: "active"
        store1.shutdown();

        KVStore store2(&medium);
        store2.restore();
        store2.put("counter", "2");
        store2.put("status", "inactive");
        store2.put("new_field", "added");
        std::cout << store2.get("counter") << std::endl;    // Expected: "2"
        std::cout << store2.get("status") << std::endl;     // Expected: "inactive"
        std::cout << store2.get("new_field") << std::endl;  // Expected: "added"
        store2.shutdown();

        KVStore store3(&medium);
        store3.restore();
        std::cout << store3.get("counter") << std::endl;    // Expected: "2"
        std::cout << store3.get("status") << std::endl;     // Expected: "inactive"
        std::cout << store3.get("new_field") << std::endl;  // Expected: "added"
    }

    static void test3() {
        std::cout << "\n===== Test 3 =====" << std::endl;

        InMemoryMedium medium;
        KVStore store1(&medium);
        store1.put("emoji_key_😊", "emoji_value_🎉");
        store1.put("unicode_key_中文", "unicode_value_日本語");
        store1.put("empty_value", "");
        std::cout << store1.get("emoji_key_😊") << std::endl;  // Expected: "emoji_value_🎉"
        std::cout << store1.get("empty_value") << std::endl;   // Expected: ""
        store1.shutdown();

        KVStore store2(&medium);
        store2.restore();
        std::cout << store2.get("emoji_key_😊") << std::endl;      // Expected: "emoji_value_🎉"
        std::cout << store2.get("unicode_key_中文") << std::endl;  // Expected: "unicode_value_日本語"
        std::cout << store2.get("empty_value") << std::endl;       // Expected: ""
        std::cout << store2.get("nonexistent_key") << std::endl;   // Expected: ""
    }

    static void main() {
        test1();
        test2();
        test3();
    }
};

int main() {
    KVStore::main();
    return 0;
}

/*
Follow-up:
You are required to implement a persistent key-value store for string keys and values, with the added constraint that
all stored data can be split and saved across multiple files, with each file being no larger than sizeLimit bytes.

When serializing the key-value store, if the binary data exceeds this size limit, it should be divided into multiple
files or segments. During deserialization, the store must be able to correctly reconstruct its state by reading from all
saved parts, ensuring that all key-value pairs are restored exactly as before.

You may modify the provided implementations of the saveBlob() and getBlob() methods in the InMemoryMedium class to
support reading from and writing to multiple files as necessary.


 * An in-memory implementation of the Medium interface.
 * Supports splitting data into multiple parts based on a size limit.

class InMemoryMedium implements Medium {

    public InMemoryMedium(int sizeLimit){...}

    public void saveBlob(byte[] data) {...}

    public byte[] getBlob(){...}
}

Implement the KVStore class:

KVStore(Medium medium) Initializes a new, empty key-value store using the provided storage medium. The store only
interacts with data via this medium.

void put(String key, String value) Stores the specified value associated with the given key. If the key already exists,
its value is updated.

String get(String key) Returns the value associated with key. If the key is not present, it returns the empty string "".

void shutdown() Serializes the current store into a custom binary format and writes it to the associated medium,
splitting the data into multiple parts of at most sizeLimit bytes each as needed. After shutdown, the instance becomes
closed, any subsequent get or put must fail and throw an error.

void restore() Requests the complete logical byte stream from the medium by concatenating all saved parts in the correct
order. And restores the in-memory store from this data, fully overwriting its contents.

Constraints:

All keys and values are ASCII strings.
Each file or persisted part must have size ≤ sizeLimit bytes.
1 ≤ number of keys ≤ 10⁴.
Total size of all persisted keys, values, and headers ≤ 10⁶ bytes.
Methods are called in a valid order.
Example:

Input:
["InMemoryMedium", "KVStore", "put", "put", "put", "put", "put", "get", "get", "get", "shutdown", "KVStore", "get",
"put", "restore", "get", "get", "get", "get"]

[[64], [], ["user1", "Alice_Johnson_from_New_York"], ["user2", "Bob_Smith_from_Los_Angeles"], ["user3",
"Charlie_Brown_from_Chicago"], ["user4", "Diana_Prince_from_San_Francisco"], ["user5", "Eve_Williams_from_Seattle"],
["user1"], ["user3"], ["user_nonexistent"], [], [], ["user1"], ["temp_key", "temp_value"], [], ["user1"], ["user2"],
["user5"], ["temp_key"]]

Output:
[null, null, null, null, null, null, "Alice_Johnson_from_New_York", "Charlie_Brown_from_Chicago", "", null, null, "",
null, null, "Alice_Johnson_from_New_York", "Bob_Smith_from_Los_Angeles", "Eve_Williams_from_Seattle", ""]

Explanation:

Medium medium = new InMemoryMedium(64); Initialize medium with 64 bytes file size limit.
KVStore store1 = new KVStore(medium);
store1.put("user1", "Alice_Johnson_from_New_York"); // This entry is around 40 btyes after serizilation.
store1.put("user2", "Bob_Smith_from_Los_Angeles"); // Around 39 btyes.
store1.put("user3", "Charlie_Brown_from_Chicago"); // Around 38 btyes.
store1.put("user4", "Diana_Prince_from_San_Francisco"); // Around 42 bytes.
store1.put("user5", "Eve_Williams_from_Seattle"); // Around 38 btyes.
store1.get("user1"); // Returns "Alice_Johnson_from_New_York".
store1.get("user3"); // Returns "Charlie_Brown_from_Chicago".
store1.get("user_nonexistent"); // Returns "".
store1.shutdown(); // Serializes the data and distributes it across multiple files (approximately 197 bytes in total),
requiring 3 or 4 files for storage. KVStore store2 = new KVStore(medium); // New store using same medium.
store2.get("user1"); // Returns "" (not restored yet).
store2.put("temp_key", "temp_value"); // Adds "temp_key" temporarily.
store2.restore(); // Loads and restores all entries from all persisted parts.
store2.get("user1"); // Returns "Alice_Johnson_from_New_York".
store2.get("user2"); // Returns "Bob_Smith_from_Los_Angeles".
store2.get("user5"); // Returns "Eve_Williams_from_Seattle".
store2.get("temp_key"); // Returns "".
 */

/**
 * The Medium interface allows persisting and retrieving raw binary data.
 */
class Medium {
public:
    virtual void saveBlob(const std::vector<unsigned char>& data) = 0;
    virtual std::vector<unsigned char> getBlob() = 0;
};

/**
 * An in-memory implementation of the Medium interface for testing purposes.
 * Supports splitting data into multiple parts based on a size limit.
 */
class InMemoryMedium : public Medium {
private:
    int sizeLimit;
    std::vector<std::vector<unsigned char>> parts;

public:
    InMemoryMedium(int sizeLimit) : sizeLimit(sizeLimit) {}

    void saveBlob(const std::vector<unsigned char>& data) override {
        parts.clear();

        if (data.empty()) {
            return;
        }

        // Split data into chunks of at most sizeLimit bytes
        int offset = 0;
        while (offset < data.size()) {
            int chunkSize = std::min(sizeLimit, (int)(data.size() - offset));
            std::vector<unsigned char> chunk(chunkSize);
            std::copy(data.begin() + offset, data.begin() + offset + chunkSize, chunk.begin());
            parts.push_back(chunk);
            offset = offset + chunkSize;
        }
    }

    std::vector<unsigned char> getBlob() override {
        if (parts.empty()) {
            return std::vector<unsigned char>();
        }

        // Calculate total size
        int totalSize = 0;
        for (const auto& part : parts) {
            totalSize = totalSize + part.size();
        }

        // Concatenate all parts
        std::vector<unsigned char> result(totalSize);
        int offset = 0;
        for (const auto& part : parts) {
            std::copy(part.begin(), part.end(), result.begin() + offset);
            offset = offset + part.size();
        }
        return result;
    }
};

class KVStore {
private:
    std::unordered_map<std::string, std::string> map;
    Medium* medium;
    bool isClosed;

    void writeInt(std::vector<unsigned char>& buffer, int value) {
        buffer.push_back((value >> 24) & 0xFF);
        buffer.push_back((value >> 16) & 0xFF);
        buffer.push_back((value >> 8) & 0xFF);
        buffer.push_back(value & 0xFF);
    }

    int readInt(const std::vector<unsigned char>& data, int& offset) {
        int value = (data[offset] << 24) | (data[offset + 1] << 16) | (data[offset + 2] << 8) | data[offset + 3];
        offset += 4;
        return value;
    }

public:
    KVStore(Medium* medium) : medium(medium), isClosed(false) {}

    void put(const std::string& key, const std::string& value) {
        if (isClosed) {
            throw std::runtime_error("Store is closed after shutdown");
        }
        map[key] = value;
    }

    std::string get(const std::string& key) {
        if (isClosed) {
            throw std::runtime_error("Store is closed after shutdown");
        }
        auto it = map.find(key);
        return it != map.end() ? it->second : "";
    }

    void shutdown() {
        std::vector<unsigned char> buffer;

        // Serialization Format:[num_entries: int] -> [key1_len: int][key1: byte[]][val1_len: int][val1: byte[]]
        writeInt(buffer, map.size());

        for (const auto& entry : map) {
            std::vector<unsigned char> keyBytes(entry.first.begin(), entry.first.end());
            std::vector<unsigned char> valueBytes(entry.second.begin(), entry.second.end());

            writeInt(buffer, keyBytes.size());
            buffer.insert(buffer.end(), keyBytes.begin(), keyBytes.end());
            writeInt(buffer, valueBytes.size());
            buffer.insert(buffer.end(), valueBytes.begin(), valueBytes.end());
        }

        medium->saveBlob(buffer);
        isClosed = true;
    }

    void restore() {
        std::vector<unsigned char> data = medium->getBlob();
        if (data.empty()) {
            return;
        }

        map.clear();
        int offset = 0;
        int entryCount = readInt(data, offset);

        for (int i = 0; i < entryCount; i = i + 1) {
            int keyLength = readInt(data, offset);
            std::string key(data.begin() + offset, data.begin() + offset + keyLength);
            offset += keyLength;

            int valueLength = readInt(data, offset);
            std::string value(data.begin() + offset, data.begin() + offset + valueLength);
            offset += valueLength;

            map[key] = value;
        }
    }

    static void main() {
        test1();
        test2();
    }

private:
    static void test1() {
        std::cout << "===== Test 1 =====" << std::endl;

        InMemoryMedium medium(64);
        KVStore store1(&medium);
        store1.put("user1", "Alice_Johnson_from_New_York");
        store1.put("user2", "Bob_Smith_from_Los_Angeles");
        store1.put("user3", "Charlie_Brown_from_Chicago");
        store1.put("user4", "Diana_Prince_from_San_Francisco");
        store1.put("user5", "Eve_Williams_from_Seattle");
        std::cout << store1.get("user1") << std::endl; // Expected: "Alice_Johnson_from_New_York"
        std::cout << store1.get("user3") << std::endl; // Expected: "Charlie_Brown_from_Chicago"
        std::cout << store1.get("user_nonexistent") << std::endl; // Expected: ""
        store1.shutdown();

        KVStore store2(&medium);
        std::cout << store2.get("user1") << std::endl; // Expected: ""
        store2.put("temp_key", "temp_value");
        store2.restore();
        std::cout << store2.get("user1") << std::endl; // Expected: "Alice_Johnson_from_New_York"
        std::cout << store2.get("user2") << std::endl; // Expected: "Bob_Smith_from_Los_Angeles"
        std::cout << store2.get("user5") << std::endl; // Expected: "Eve_Williams_from_Seattle"
        std::cout << store2.get("temp_key") << std::endl; // Expected: ""
    }

    static void test2() {
        std::cout << "\n===== Test 2 (Large Value) =====" << std::endl;

        InMemoryMedium medium(32);
        KVStore store1(&medium);

        // Create a large value that exceeds the size limit (500 characters)
        std::string largeData;
        for (int i = 0; i < 50; i++) {
            largeData += "ABCDEFGHIJ";
        }

        store1.put("large_key", largeData);
        store1.put("small_key", "small_value");
        std::cout << "Length: " << store1.get("large_key").length() << std::endl; // Expected: 500
        std::cout << store1.get("small_key") << std::endl; // Expected: "small_value"
        store1.shutdown();

        KVStore store2(&medium);
        store2.restore();
        std::cout << "Length: " << store2.get("large_key").length() << std::endl; // Expected: 500
        std::cout << store2.get("small_key") << std::endl; // Expected: "small_value"
        store2.put("large_key", "updated_value");
        store2.put("new_key", "new_data");
        store2.shutdown();

        KVStore store3(&medium);
        store3.restore();
        std::cout << store3.get("large_key") << std::endl; // Expected: "updated_value"
        std::cout << store3.get("new_key") << std::endl; // Expected: "new_data"
    }
};

int main() {
    KVStore::main();
    return 0;
}