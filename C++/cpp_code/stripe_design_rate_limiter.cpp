/*
https://www.hack2hire.com/companies/stripe/coding-questions/67ce44ae8f73eb6319edd1ed/practice?questionId=67ce4e968f73eb6319edd1f0
Design Rate Limiter

Design a rate limiter system that begins with a specified capacity (limit) indicating the maximum number of requests
allowed within a certain time interval (ttl, unit: Millisecond). When a new request arrives, return true if it is
accepted under the current limit. Otherwise, return false.

Implement the RateLimiter class:

RateLimiter(int ttl, int limit) Initializes the rate limiter with a time-to-live window ttl in milliseconds and a
maximum limit for the number of requests allowed in that time frame.

boolean allowRequest() Checks if a new request can be served based on recent requests within the ttl window.

Example 1:

Input:
(Assuming the interval for each request is 100ms)

["RateLimiter","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest"]

[[1000,5],[],[],[],[],[],[],[],[],[],[],[]]

Output:
[null, true, true, true, true, true, false, false, false, false, false, true]

Explanation:

RateLimiter rateLimiter = new RateLimiter(1000, 5); // Initialize with ttl = 1000 ms and limit = 5.
rateLimiter.allowRequest(); // Returns true. (t = 0ms)
rateLimiter.allowRequest(); // Returns true. (t = 100ms)
rateLimiter.allowRequest(); // Returns true. (t = 200ms)
rateLimiter.allowRequest(); // Returns true. (t = 300ms)
rateLimiter.allowRequest(); // Returns true. (t = 400ms)
rateLimiter.allowRequest(); // Returns false, as the limit of 5 is hit within the last 1000 ms. (t = 500ms)
rateLimiter.allowRequest(); // Returns false. (t = 600ms)
rateLimiter.allowRequest(); // Returns false. (t = 700ms)
rateLimiter.allowRequest(); // Returns false. (t = 800ms)
rateLimiter.allowRequest(); // Returns false. (t = 900ms)
rateLimiter.allowRequest(); // Returns true, as the oldest request (t = 0ms) has expired. (t = 1000ms)
Example 2:

Input:
(Assuming the interval for each request is 300ms)

["RateLimiter","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest"]

[[1000,5],[],[],[],[],[],[],[],[],[],[],[]]

Output:
[null, true, true, true, true, true, true, true, true, true, true]

Explanation:
Since all 10 requests were sent at a rate slower than the rate limiter, they should all be allowed.
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
#include <chrono>
#include <iostream>
#include <thread>
using namespace std;

class RateLimiter {
private:
    queue<long> req_ts_;
    long ttl_;
    long limit_;
    mutex mtx_;

public:
    RateLimiter(long ttl, long limit) {
        ttl_ = ttl;
        limit_ = limit;
    }

    bool allowRequest() {
        lock_guard<mutex> lock(mtx_);

        long curr_ts = std::chrono::duration_cast<std::chrono::milliseconds>(
                               std::chrono::system_clock::now().time_since_epoch())
                               .count();
        while (!req_ts_.empty() && curr_ts - req_ts_.front() >= ttl_) {
            req_ts_.pop();
        }

        if (req_ts_.size() >= limit_) {
            return false;
        }

        req_ts_.push(curr_ts);
        return true;
    }

    static void test1() {
        std::cout << "========= Test 1 =========" << std::endl;
        RateLimiter rateLimiter(1000, 5);

        // Make 11 requests at a rate faster than the rate limiter allows
        for (int i = 0; i < 11; i++) {
            std::cout << "Request " << (i + 1) << " accepted (t=" << (i * 100)
                      << "ms)? : " << (rateLimiter.allowRequest() ? "true" : "false") << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Sleep for 100 milliseconds between requests
        }
    }

    static void test2() {
        std::cout << "\n========= Test 2 =========" << std::endl;
        RateLimiter rateLimiter(1000, 5);

        // Make 10 requests at a rate slower than the rate limiter allows
        for (int i = 0; i < 10; i++) {
            std::cout << "Request " << (i + 1) << " accepted (t=" << (i * 300)
                      << "ms)? : " << (rateLimiter.allowRequest() ? "true" : "false") << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(300));  // Sleep for 300 milliseconds between requests
        }
    }
};

int main() {
    RateLimiter::test1();
    RateLimiter::test2();
    return 0;
}

/*
Follow-up:
Design a per-customer rate limiter system that begins with a specified capacity (limit) indicating the maximum number of
requests allowed for a single customer within a certain time interval (ttl, unit: Millisecond).

Each customer is limited independently. When a new request arrives for a given customerId, return true if it is accepted
under the current limit for that customer. Otherwise, return false.

Implement the RateLimiter class:

RateLimiter(int ttl, int limit) Initializes the rate limiter with a time-to-live window ttl in milliseconds and a
maximum limit for the number of requests allowed per customer in that time frame.

boolean allowRequest(int customerId) Checks if a new request for the given customerId can be served based on recent
requests for the same customer within the ttl window.

Constraints:

All allowRequest calls occur with real-time spacing (in milliseconds).
Example

Input:
(For each customer, assume that the interval between consecutive requests is 100ms)

["RateLimiter","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest","allowRequest"]

[[1000,3],[123],[456],[123],[456],[123],[456],[123],[456],[123],[456],[123],[456],[123],[456],[123],[456]]

Output:
[null, true, true, true, true, true, true, false, false, false, false, false, false, false, false, false, false]

Explanation:

RateLimiter rateLimiter = new RateLimiter(1000, 3); // Initialize with ttl = 1000 ms and limit = 3.
rateLimiter.allowRequest(123); // Returns true. (t = 0ms)
rateLimiter.allowRequest(456); // Returns true. (t = 0ms)
rateLimiter.allowRequest(123); // Returns true. (t = 100ms)
rateLimiter.allowRequest(456); // Returns true. (t = 100ms)
rateLimiter.allowRequest(123); // Returns true. (t = 200ms)
rateLimiter.allowRequest(456); // Returns true. (t = 200ms)
rateLimiter.allowRequest(123); // Returns false, as customer 123 reached the limit of 3 within 1000 ms. (t = 300ms)
rateLimiter.allowRequest(456); // Returns false, as customer 456 reached the limit of 3 within 1000 ms. (t = 300ms)
rateLimiter.allowRequest(123); // Returns false. (t = 400ms)
rateLimiter.allowRequest(456); // Returns false. (t = 400ms)
rateLimiter.allowRequest(123); // Returns false. (t = 500ms)
rateLimiter.allowRequest(456); // Returns false. (t = 500ms)
rateLimiter.allowRequest(123); // Returns false. (t = 600ms)
rateLimiter.allowRequest(456); // Returns false. (t = 600ms)
rateLimiter.allowRequest(123); // Returns false. (t = 700ms)
rateLimiter.allowRequest(456); // Returns false. (t = 700ms)
 */
class RateLimiter {
private:
    std::unordered_map<int, std::queue<long long>> customer_to_ts_; // Map to store timestamps per customer
    int ttl_; // Time window in milliseconds
    int limit_; // Maximum requests allowed in the window
    std::mutex mtx_; // Mutex for synchronization

    long long get_current_time_millis() {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    }

public:
    RateLimiter(int ttl, int limit) : ttl_(ttl), limit_(limit) {}

    bool allowRequest(int customerId) {
        std::lock_guard<std::mutex> lock(mtx_);

        long long curr_ts = get_current_time_millis();

        // Get or create queue for this customer
        if (customer_to_ts_.find(customerId) == customer_to_ts_.end()) {
            customer_to_ts_[customerId] = std::queue<long long>();
        }
        std::queue<long long>& req_ts = customer_to_ts_[customerId];

        // Remove timestamps that are outside the sliding window
        while (!req_ts.empty() && req_ts.front() <= curr_ts - ttl_) {
            req_ts.pop();
        }

        // Check if we can allow a new request for this customer
        if (req_ts.size() < limit_) {
            req_ts.push(curr_ts); // Add current timestamp to the queue
            return true;
        }

        return false;
    }

    static void test1() {
        std::cout << "========= Test 1 =========" << std::endl;
        RateLimiter rateLimiter(1000, 3);
        int customer1 = 123;
        int customer2 = 456;

        // Make 8 requests alternating between two customers at a rate faster than the rate limiter allows
        for (int i = 0; i < 8; i++) {
            std::cout << "Customer " << customer1 << " Request " << (i + 1) << " accepted (t=" << (i * 100) << "ms)? : "
                      << (rateLimiter.allowRequest(customer1) ? "true" : "false") << std::endl;
            std::cout << "Customer " << customer2 << " Request " << (i + 1) << " accepted (t=" << (i * 100) << "ms)? : "
                      << (rateLimiter.allowRequest(customer2) ? "true" : "false") << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Sleep for 100 milliseconds between requests
        }
    }

    static void test2() {
        std::cout << "\n========= Test 2 =========" << std::endl;
        RateLimiter rateLimiter(1000, 2);

        // Test that different customers have independent limits
        for (int i = 0; i < 4; i++) {
            std::cout << "Customer 100 Request " << (i + 1) << " accepted (t=" << (i * 200) << "ms)? : "
                      << (rateLimiter.allowRequest(100) ? "true" : "false") << std::endl;
            std::cout << "Customer 200 Request " << (i + 1) << " accepted (t=" << (i * 200) << "ms)? : "
                      << (rateLimiter.allowRequest(200) ? "true" : "false") << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }

    static void test3() {
        std::cout << "\n========= Test 3 =========" << std::endl;
        RateLimiter rateLimiter(1000, 2);
        int customerId = 456;

        // Fill up the rate limit
        std::cout << "Filling up rate limit:" << std::endl;
        for (int i = 0; i < 4; i++) {
            std::cout << "Customer " << customerId << " Request " << (i + 1) << " accepted (t=0ms)? : "
                      << (rateLimiter.allowRequest(customerId) ? "true" : "false") << std::endl;
        }

        // Wait for time window to expire
        std::cout << "\nWaiting for time window to expire (1.1 seconds)..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1100));

        // Try requests again - should be allowed after window expiration
        std::cout << "After time window expiration:" << std::endl;
        for (int i = 0; i < 3; i++) {
            std::cout << "Customer " << customerId << " Request " << (i + 5) << " accepted (t=1100ms)? : "
                      << (rateLimiter.allowRequest(customerId) ? "true" : "false") << std::endl;
        }
    }

    static void test4() {
        std::cout << "\n========= Test 4 =========" << std::endl;
        RateLimiter rateLimiter(1000, 2); // 2 requests per 1000ms window

        int customer1 = 101;
        int customer2 = 202;
        int customer3 = 303;

        // Initial simultaneous requests
        std::cout << "Customer " << customer1 << " Request 1 accepted (t=0ms)? : " << (rateLimiter.allowRequest(customer1) ? "true" : "false") << std::endl;
        std::cout << "Customer " << customer2 << " Request 1 accepted (t=0ms)? : " << (rateLimiter.allowRequest(customer2) ? "true" : "false") << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait 100ms

        // Customer2 makes consecutive requests, Customer1 also tries
        std::cout << "Customer " << customer2 << " Request 2 accepted (t=100ms)? : " << (rateLimiter.allowRequest(customer2) ? "true" : "false") << std::endl;
        std::cout << "Customer " << customer1 << " Request 2 accepted (t=100ms)? : " << (rateLimiter.allowRequest(customer1) ? "true" : "false") << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait 100ms

        // Customer2 continues consecutive requests, Customer3 joins
        std::cout << "Customer " << customer2 << " Request 3 accepted (t=200ms)? : " << (rateLimiter.allowRequest(customer2) ? "true" : "false") << std::endl;
        std::cout << "Customer " << customer3 << " Request 1 accepted (t=200ms)? : " << (rateLimiter.allowRequest(customer3) ? "true" : "false") << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait 100ms

        // All customers try to make requests - some should fail due to rate limiting
        std::cout << "Customer " << customer2 << " Request 4 accepted (t=300ms)? : " << (rateLimiter.allowRequest(customer2) ? "true" : "false") << std::endl;
        std::cout << "Customer " << customer1 << " Request 3 accepted (t=300ms)? : " << (rateLimiter.allowRequest(customer1) ? "true" : "false") << std::endl;
        std::cout << "Customer " << customer3 << " Request 2 accepted (t=300ms)? : " << (rateLimiter.allowRequest(customer3) ? "true" : "false") << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Wait 200ms

        // Customer3 tries multiple consecutive requests
        std::cout << "Customer " << customer3 << " Request 3 accepted (t=500ms)? : " << (rateLimiter.allowRequest(customer3) ? "true" : "false") << std::endl;
        std::cout << "Customer " << customer3 << " Request 4 accepted (t=500ms)? : " << (rateLimiter.allowRequest(customer3) ? "true" : "false") << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(600)); // Wait 600ms - total elapsed = 1100ms

        // Window should have reset for all customers
        std::cout << "Customer " << customer1 << " Request 4 accepted (t=1100ms)? : " << (rateLimiter.allowRequest(customer1) ? "true" : "false") << std::endl;
        std::cout << "Customer " << customer2 << " Request 5 accepted (t=1100ms)? : " << (rateLimiter.allowRequest(customer2) ? "true" : "false") << std::endl;
        std::cout << "Customer " << customer3 << " Request 5 accepted (t=1100ms)? : " << (rateLimiter.allowRequest(customer3) ? "true" : "false") << std::endl;
        std::cout << "Customer " << customer1 << " Request 5 accepted (t=1100ms)? : " << (rateLimiter.allowRequest(customer1) ? "true" : "false") << std::endl;
        std::cout << "Customer " << customer1 << " Request 6 accepted (t=1100ms)? : " << (rateLimiter.allowRequest(customer1) ? "true" : "false") << std::endl;
    }
};

int main() {
    RateLimiter::test1();
    RateLimiter::test2();
    RateLimiter::test3();
    RateLimiter::test4();
    return 0;
}