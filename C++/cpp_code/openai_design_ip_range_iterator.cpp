/*
https://www.hack2hire.com/companies/openai/coding-questions/69a5f7bb3d95612a1782be6a/practice?questionId=69a5fdb73d95612a1782be7b
Design IP Range Iterator

Every device on the public Internet is identified by an IPv4 address, written in dotted-decimal notation as "A.B.C.D",
where A, B, C, and D are integers from 0 to 255. Conceptually, the four octets form a single 32-bit unsigned value.

You are asked to implement a simple, forward-only iterator that produces every address from a given starting point up to
the absolute upper limit (255.255.255.255).

Implement the IPv4Iterator class:

IPv4Iterator(String startIp) Initializes the iterator with the startIp. The first address yielded by the iterator must
be exactly startIp.

boolean hasNext() Returns true if there is at least one address left to be produced. Otherwise, returns false.

String next() Returns the current address as a string in dotted-decimal form, then advances the internal cursor to the
next sequential address.

It is guaranteed that next() is called only when hasNext() returns true.
The iterator visits addresses in strict ascending order (e.g., after "x.y.z.255" comes "x.y.(z+1).0").
Constraints:

startIp is a valid IPv4 address string.
0 ≤ startIp ≤ 255.255.255.255.
The number of next() calls will not exceed the remaining addresses in the range.
Example

Input:
["IPv4Iterator", "next", "next", "next", "hasNext"]
[["255.255.255.253"], [], [], [], []]

Output:
[null, "255.255.255.253", "255.255.255.254", "255.255.255.255", false]

Explanation:

IPv4Iterator iterator = new IPv4Iterator("255.255.255.253");
iterator.next(); // Returns "255.255.255.253".
iterator.next(); // Returns "255.255.255.254".
iterator.next(); // Returns "255.255.255.255".
iterator.hasNext(); // Returns false.
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
#include <sstream>
#include <sstream>
using namespace std;

class IPv4Iterator {
private:
    static string int_to_string(uint32_t val) {
        stringstream ss;
        ss << to_string((val >> 24) & 0xFF) << "." << to_string((val >> 16) & 0xFF) << "."
           << to_string((val >> 8) & 0xFF) << "." << to_string(val & 0xFF);
        return ss.str();
    }

    static uint32_t string_to_int(string ip) {
        uint32_t rst = 0;
        size_t pos = ip.find('.');
        while (pos != string::npos) {
            int val = stoi(ip.substr(0, pos));
            rst = (rst << 8) | (0xFF & val);
            ip = ip.substr(pos + 1);
            pos = ip.find('.');
        }

        int val = stoi(ip);
        return (rst << 8) | (0xFF & val);
    }

    uint32_t cur_ip_val_;
    uint32_t max_ip_val_;
    bool has_next_;

public:
    IPv4Iterator(string startIp) {
        cur_ip_val_ = string_to_int(startIp);
        max_ip_val_ = string_to_int("255.255.255.255");
        has_next_ = true;
    }

    bool hasNext() {
        return has_next_;
    }

    string next() {
        string rst = int_to_string(cur_ip_val_);
        if (cur_ip_val_ == max_ip_val_) {
            has_next_ = false;
        } else {
            cur_ip_val_ += 1;
        }
        return rst;
    }
};

/*
Follow-up 1:
Networking tasks sometimes need to enumerate IPv4 addresses in reverse order, such as when reclaiming unused space or
performing backward scans. In this follow-up question, you need to implement a backward-only iterator that starts at a
given address and walks toward the absolute minimum (0.0.0.0).

Implement the ReverseIPv4Iterator class:

ReverseIPv4Iterator(String endIp) Initializes the iterator with the endIp. The first address yielded by the iterator
must be exactly endIp.

boolean hasNext() Returns true if there is at least one address left to be produced. Otherwise, returns false.

String next() Returns the current address in dotted-decimal form, then moves the internal cursor to the preceding
address.

It is guaranteed that next() is called only when hasNext() returns true.
The iterator visits addresses in strict descending order (e.g., after "x.y.z.0" comes "x.y.(z-1).255").
Constraints:

startIp is a valid IPv4 address string.
0 ≤ startIp ≤ 255.255.255.255.
The number of next() calls will not exceed the remaining addresses in the range.
Example

Input:
["ReverseIPv4Iterator", "next", "next", "next", "hasNext"]
[["0.0.0.2"], [], [], [], []]

Output:
[null, "0.0.0.2", "0.0.0.1", "0.0.0.0", false]

Explanation:

ReverseIPv4Iterator iterator = new ReverseIPv4Iterator("0.0.0.2");
iterator.next(); // Returns "0.0.0.2".
iterator.next(); // Returns "0.0.0.1".
iterator.next(); // Returns "0.0.0.0".
iterator.hasNext(); // Returns false.
 */

class ReverseIPv4Iterator {
private:
    static string int_to_string(uint32_t val) {
        stringstream ss;
        ss << to_string((val >> 24) & 0xFF) << "." << to_string((val >> 16) & 0xFF) << "."
           << to_string((val >> 8) & 0xFF) << "." << to_string(val & 0xFF);
        return ss.str();
    }

    static uint32_t string_to_int(string ip) {
        uint32_t rst = 0;
        size_t pos = ip.find('.');
        while (pos != string::npos) {
            int val = stoi(ip.substr(0, pos));
            rst = (rst << 8) | (0xFF & val);
            ip = ip.substr(pos + 1);
            pos = ip.find('.');
        }

        int val = stoi(ip);
        return (rst << 8) | (0xFF & val);
    }

    uint32_t cur_ip_val_;
    uint32_t end_ip_val_;
    bool has_next_;

public:
    ReverseIPv4Iterator(string endIp) {
        cur_ip_val_ = string_to_int(endIp);
        end_ip_val_ = 0;
        has_next_ = true;
    }

    bool hasNext() {
        return has_next_;
    }

    string next() {
        string rst = int_to_string(cur_ip_val_);
        if (cur_ip_val_ == end_ip_val_) {
            has_next_ = false;
        } else {
            cur_ip_val_ -= 1;
        }
        return rst;
    }
};

/*
Follow-up 2:
CIDR (Classless Inter-Domain Routing) notation compresses a consecutive block of IPv4 addresses into one string in the
format "<IP>/<prefix>" (e.g., "192.168.1.0/30"). The prefix is an integer n (0 - 32) where the left-most n bits are
fixed, and the remaining 32 - n bits vary to form 2^(32 - n) addresses.

This problem asks you to build an iterator that lists every address in a given CIDR block, starting from the network
address and moving upward.

Implement the CIDRIterator class:

CIDRIterator(String cidr) Initializes the iterator with the CIDR string. It derives the first and last addresses and
positions at the network address (all host bits zero).

boolean hasNext() Returns true if there is at least one address left to be produced. Otherwise, returns false.

String next() Returns the current address in dotted-decimal form, then advances the cursor to the next sequential
address.

It is guaranteed that next() is called only when hasNext() returns true.
The iterator must always begin at the network address.
Constraints:

0 ≤ prefix ≤ 32
Example

Input:
["CIDRIterator", "next", "next", "next", "next", "hasNext"]
[["192.168.1.0/30"], [], [], [], [], []]
Output:
[null, "192.168.1.0", "192.168.1.1", "192.168.1.2", "192.168.1.3", false]
Explanation:

CIDRIterator iterator = new CIDRIterator("192.168.1.0/30"); // Initialize with CIDR "192.168.1.0/30" (4 addresses).
iterator.next(); // Returns "192.168.1.0".
iterator.next(); // Returns "192.168.1.1".
iterator.next(); // Returns "192.168.1.2".
iterator.next(); // Returns "192.168.1.3".
iterator.hasNext(); // Returns false. All addresses in the block have been produced.
*/
class CIDRIterator {
private:
    static string int_to_string(uint32_t val) {
        stringstream ss;
        ss << to_string((val >> 24) & 0xFF) << "." << to_string((val >> 16) & 0xFF) << "."
           << to_string((val >> 8) & 0xFF) << "." << to_string(val & 0xFF);
        return ss.str();
    }

    static uint32_t string_to_int(string ip) {
        uint32_t rst = 0;
        size_t pos = ip.find('.');
        while (pos != string::npos) {
            int val = stoi(ip.substr(0, pos));
            rst = (rst << 8) | (0xFF & val);
            ip = ip.substr(pos + 1);
            pos = ip.find('.');
        }

        int val = stoi(ip);
        return (rst << 8) | (0xFF & val);
    }

    uint32_t cur_ip_val_;
    uint32_t end_ip_val_;
    bool has_next_;

public:
    CIDRIterator(string cidr) {
        size_t pos = cidr.find('/');
        string base_ip = cidr.substr(0, pos);
        int mask_len = string_to_int(cidr.substr(pos + 1));

        uint32_t base_ip_val = string_to_int(base_ip);
        int mask = 0;
        if (mask_len != 0) {
            mask = 0xFFFFFFFF << (32 - mask_len);
        }
        cur_ip_val_ = base_ip_val & mask;
        end_ip_val_ = base_ip_val | ~mask;

        has_next_ = true;
    }

    bool hasNext() {
        return has_next_;
    }

    string next() {
        string rst = int_to_string(cur_ip_val_);
        if (cur_ip_val_ == end_ip_val_) {
            has_next_ = false;
        } else {
            cur_ip_val_ += 1;
        }
        return rst;
    }
};