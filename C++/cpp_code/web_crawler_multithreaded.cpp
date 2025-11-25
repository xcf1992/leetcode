/*
https://leetcode.com/problems/web-crawler-multithreaded/description/
1242. Web Crawler Multithreaded

Given a URL startUrl and an interface HtmlParser, implement a Multi-threaded web crawler to crawl all links that are
under the same hostname as startUrl.

Return all URLs obtained by your web crawler in any order.

Your crawler should:

Start from the page: startUrl
Call HtmlParser.getUrls(url) to get all URLs from a webpage of a given URL.
Do not crawl the same link twice.
Explore only the links that are under the same hostname as startUrl.

As shown in the example URL above, the hostname is example.org. For simplicity's sake, you may assume all URLs use HTTP
protocol without any port specified. For example, the URLs http://leetcode.com/problems and http://leetcode.com/contest
are under the same hostname, while URLs http://example.org/test and http://example.com/abc are not under the same
hostname.

The HtmlParser interface is defined as such:

interface HtmlParser {
  // Return a list of all urls from a webpage of given url.
  // This is a blocking call, that means it will do HTTP request and return when this request is finished.
  public List<String> getUrls(String url);
}
Note that getUrls(String url) simulates performing an HTTP request. You can treat it as a blocking function call that
waits for an HTTP request to finish. It is guaranteed that getUrls(String url) will return the URLs within 15ms.
Single-threaded solutions will exceed the time limit so, can your multi-threaded web crawler do better?

Below are two examples explaining the functionality of the problem. For custom testing purposes, you'll have three
variables urls, edges and startUrl. Notice that you will only have access to startUrl in your code, while urls and edges
are not directly accessible to you in code.



Example 1:



Input:
urls = [
  "http://news.yahoo.com",
  "http://news.yahoo.com/news",
  "http://news.yahoo.com/news/topics/",
  "http://news.google.com",
  "http://news.yahoo.com/us"
]
edges = [[2,0],[2,1],[3,2],[3,1],[0,4]]
startUrl = "http://news.yahoo.com/news/topics/"
Output: [
  "http://news.yahoo.com",
  "http://news.yahoo.com/news",
  "http://news.yahoo.com/news/topics/",
  "http://news.yahoo.com/us"
]
Example 2:



Input:
urls = [
  "http://news.yahoo.com",
  "http://news.yahoo.com/news",
  "http://news.yahoo.com/news/topics/",
  "http://news.google.com"
]
edges = [[0,2],[2,1],[3,2],[3,1],[3,0]]
startUrl = "http://news.google.com"
Output: ["http://news.google.com"]
Explanation: The startUrl links to all other pages that do not share the same hostname.


Constraints:

1 <= urls.length <= 1000
1 <= urls[i].length <= 300
startUrl is one of the urls.
Hostname label must be from 1 to 63 characters long, including the dots, may contain only the ASCII letters from 'a' to
'z', digits from '0' to '9' and the hyphen-minus character ('-'). The hostname may not start or end with the
hyphen-minus character ('-'). See:  https://en.wikipedia.org/wiki/Hostname#Restrictions_on_valid_hostnames You may
assume there're no duplicates in the URL library.


Follow up:

Assume we have 10,000 nodes and 1 billion URLs to crawl. We will deploy the same software onto each node. The software
can know about all the nodes. We have to minimize communication between machines and make sure each node does equal
amount of work. How would your web crawler design change? What if one node fails or does not work? How do you know when
the crawler is done?
*/
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <thread>
using namespace std;

/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 */
class HtmlParser {
public:
    vector<string> getUrls(string url);
};

class Solution {
private:
    int worker_cnt_;
    string hostname;
    queue<string> work_queue_;
    vector<thread> workers_;
    unordered_set<string> visited_urls_;
    int working_cnt_ = 0;
    bool all_done_ = false;
    mutex mtx_;
    condition_variable cv_;

    string extract_host_name(string& url) {
        int start = url.find('/') + 2;
        int end = url.find('/', start);
        if (end == string::npos) {
            return url.substr(start);
        }
        return url.substr(start, end - start);
    }

    // this a worker thread that will be doing tasks.
    void start_worker(HtmlParser* parser) {
        while (true) {
            unique_lock<mutex> lk(mtx_);
            // wait until there are some tasks OR
            // we are done executing
            cv_.wait(lk, [&]() { return work_queue_.size() > 0 || all_done_; });

            // if done, return.
            if (all_done_) {
                return;
            }

            // indicate that this thread is in progress
            working_cnt_ += 1;
            string item = work_queue_.front();
            work_queue_.pop();

            lk.unlock();
            // since getUrls can take a lot of time, release the lock.
            vector<string> accessible = parser->getUrls(item);

            // acquire the lock and add tasks.
            lk.lock();

            for (string& url : accessible) {
                // if it has been seen already or the host name doesn't match, ignore it.
                if (visited_urls_.count(url) || extract_host_name(url) != hostname) {
                    continue;
                }

                visited_urls_.insert(url);
                work_queue_.push(url);
            }
            working_cnt_ -= 1;

            // IF
            //   1) no thread is processing
            //   2) no tasks are available even after executing this task
            // THEN we are done.
            if (working_cnt_ == 0 && work_queue_.empty()) {
                all_done_ = true;
            }

            // notify all the threads either about finishing or about availability of tasks.
            lk.unlock();
            cv_.notify_all();
        }
    }

public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        all_done_ = false;
        hostname = extract_host_name(startUrl);
        visited_urls_.insert(startUrl);
        work_queue_.push(startUrl);

        // start a bunch of worker threads.
        // get number of supported threads
        worker_cnt_ = thread::hardware_concurrency();
        for (int i = 0; i < worker_cnt_; i++) {
            workers_.emplace_back(&Solution::start_worker, this, &htmlParser);
        }

        // join those threads so that crawl is a blocking call
        for (auto& t : workers_) {
            t.join();
        }

        // return every unique processed string
        return vector<string>(visited_urls_.begin(), visited_urls_.end());
    }
};
