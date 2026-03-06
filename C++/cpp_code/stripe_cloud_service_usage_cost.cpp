/*
https://www.hack2hire.com/companies/stripe/coding-questions/6973cad1a0697bac5fdca793/practice?questionId=6973d4f9a0697bac5fdca7ad
Cloud Service Usage Cost

You are developing a billing module for a cloud computing platform. Given a JSON usage_report specifying the target
region and a JSON object pricing_table containing hourly rates for services in each region, determine the total cost for
the usage.

Example data:

// Usage Report
{
    "region": "us-east-1",
    "services": [
        {"service": "db.t3.micro", "hours": 20},
          ...
    ]
    ...
}
// Pricing Table
{
    "us-east-1": [
        {"service": "db.t3.micro", "rate": 550},
          ...
    ],
    ...
}
The total cost for a single service is determined by multiplying its usage hours by the hourly rate for that service in
the given region. If the report's region does not exist in the pricing_table, or if any service in the report is missing
for that region, return -1.

Constraints:

0 ≤ services.length ≤ 1000
0 ≤ hours ≤ 1000
All rates are non-negative integers
Service names and region codes are case-sensitive
Example:

Input:
usage_report = {
  "region": "us-east-1",
  "services": [
    {"service": "db.t3.micro", "hours": 20},
    {"service": "ec2.m5.large", "hours": 5}
  ]
}
pricing_table = {
  "us-east-1": [
    {"service": "db.t3.micro", "rate": 550},
    {"service": "ec2.m5.large", "rate": 1000}
  ],
  "ca-central-1": [
    {"service": "db.t3.micro", "rate": 750},
    {"service": "ec2.m5.large", "rate": 1100}
  ]
}
Output: 16000
Explanation: The usage is in us-east-1:

"db.t3.micro" cost: 20 x 550 = 11000
"ec2.m5.large" cost: 5 x 1000 = 5000
Total = 11000 + 5000 = 16000.
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
#include <any>

using namespace std;

class Solution {
public:
    int calculateUsageCost(unordered_map<string, any> usageReport, unordered_map<string, any> pricingTable) {
        string usage_region = any_cast<string>(usageReport["region"]);
        if (pricingTable.find(usage_region) == pricingTable.end()) {
            return -1;
        }

        vector<unordered_map<string, any>> region_rates =
                any_cast<vector<unordered_map<string, any>>>(pricingTable[usage_region]);
        unordered_map<string, int> svc_rates;
        for (const auto& entry : region_rates) {
            svc_rates[any_cast<string>(entry.at("service"))] = any_cast<int>(entry.at("rate"));
        }

        vector<unordered_map<string, any>> usage_svc =
                any_cast<vector<unordered_map<string, any>>>(usageReport["services"]);
        int rst = 0;
        for (const auto& item : usage_svc) {
            string svc_name = any_cast<string>(item.at("service"));
            int hours = any_cast<int>(item.at("hours"));
            if (svc_rates.find(svc_name) == svc_rates.end()) {
                return -1;
            }

            rst += hours * svc_rates[svc_name];
        }
        return rst;
    }

    static void test1() {
        Solution solution;
        unordered_map<string, any> usage1 = {
                {"region", string("us-east-1")},
                {"services", vector<unordered_map<string, any>>{{{"service", string("db.t3.micro")}, {"hours", 20}},
                                                                {{"service", string("ec2.m5.large")}, {"hours", 5}}}}};

        unordered_map<string, any> pricing1 = {
                {"us-east-1",
                 vector<unordered_map<string, any>>{{{"service", string("db.t3.micro")}, {"rate", 550}},
                                                    {{"service", string("ec2.m5.large")}, {"rate", 1000}}}},
                {"ca-central-1",
                 vector<unordered_map<string, any>>{{{"service", string("db.t3.micro")}, {"rate", 750}},
                                                    {{"service", string("ec2.m5.large")}, {"rate", 1100}}}}};

        int res1 = solution.calculateUsageCost(usage1, pricing1);
        cout << res1 << endl;  // Expected: 16000
    }

    static void test2() {
        Solution solution;
        unordered_map<string, any> usage2 = {
                {"region", string("ca-central-1")},
                {"services", vector<unordered_map<string, any>>{{{"service", string("ec2.m5.large")}, {"hours", 3}}}}};

        unordered_map<string, any> pricing2 = {
                {"ca-central-1",
                 vector<unordered_map<string, any>>{{{"service", string("ec2.m5.large")}, {"rate", 1100}}}}};

        int res2 = solution.calculateUsageCost(usage2, pricing2);
        cout << res2 << endl;  // Expected: 3300
    }

    static void test3() {
        Solution solution;
        unordered_map<string, any> usage3 = {
                {"region", string("us-east-1")},
                {"services",
                 vector<unordered_map<string, any>>{{{"service", string("s3.standard")}, {"hours", 10}},
                                                    {{"service", string("rds.gp2")}, {"hours", 8}},
                                                    {{"service", string("lambda.invocations")}, {"hours", 50}}}}};

        unordered_map<string, any> pricing3 = {
                {"us-east-1",
                 vector<unordered_map<string, any>>{{{"service", string("s3.standard")}, {"rate", 800}},
                                                    {{"service", string("rds.gp2")}, {"rate", 2000}},
                                                    {{"service", string("lambda.invocations")}, {"rate", 100}}}}};

        int res3 = solution.calculateUsageCost(usage3, pricing3);
        cout << res3 << endl;  // Expected: 29000
    }

    static void test4() {
        Solution solution;
        unordered_map<string, any> usage4 = {
                {"region", string("us-east-1")},
                {"services", vector<unordered_map<string, any>>{{{"service", string("db.t3.micro")}, {"hours", 0}},
                                                                {{"service", string("ec2.m5.large")}, {"hours", 5}}}}};

        unordered_map<string, any> pricing4 = {
                {"us-east-1",
                 vector<unordered_map<string, any>>{{{"service", string("db.t3.micro")}, {"rate", 550}},
                                                    {{"service", string("ec2.m5.large")}, {"rate", 1000}}}}};

        int res4 = solution.calculateUsageCost(usage4, pricing4);
        cout << res4 << endl;  // Expected: 5000
    }

    static void test5() {
        Solution solution;
        unordered_map<string, any> usage5 = {
                {"region", string("eu-central-1")},
                {"services", vector<unordered_map<string, any>>{{{"service", string("ec2.m5.large")}, {"hours", 2}}}}};

        unordered_map<string, any> pricing5 = {
                {"us-east-1",
                 vector<unordered_map<string, any>>{{{"service", string("ec2.m5.large")}, {"rate", 1000}}}}};

        int res5 = solution.calculateUsageCost(usage5, pricing5);
        cout << res5 << endl;  // Expected: -1
    }
};

int main() {
    Solution::test1();
    Solution::test2();
    Solution::test3();
    Solution::test4();
    Solution::test5();
    return 0;
}

/*
Follow-up 1:
Building on the previous part, pricing is now determined by usage tiers with incremental strategy. The rate per unit
changes depending on how much usage has already been processed in previous tiers.

The pricing_table data is updated such that each service contains an array of tiers objects. Each tier object contains
minHours, maxHours, and rate. Pricing follows a progressive calculation:

Usage is assigned to tiers in the order they are provided.
A maxHours of null indicates the range extends to infinity.
For example:

If a tier is defined as {"min": 0, "max": 2, "rate": 1000}, the first 2 hours cost 1000 each.
If the next tier is {"min": 0, "max": null, "rate": 900}, the 3rd hour and all subsequent hours cost 900 each.
Return -1 if the report's region does not exist in pricing_table, or if any service is missing a pricing rule.

Example:

Input:
usage_report = {
  "region": "us-east-1",
  "services": [
    {
      "service": "ec2.m5.large",
      "hours": 5
    }
  ]
},
pricing_table = {
  "us-east-1": [
    {
      "service": "ec2.m5.large",
      "tiers": [
        {
          "minHours": 0,
          "maxHours": 2,
          "rate": 1000
        },
        {
          "minHours": 3,
          "maxHours": null,
          "rate": 900
        }
      ]
    }
  ]
}
Output: 4700
Explanation: The report contains 5 hours of "ec2.m5.large":

Tier 1: The first 2 hours cost 1000 each. Subtotal: 2 x 1000 = 2000.
Tier 2: The remaining 3 hours cost 900 each. Subtotal: 3 x 900 = 2700.
Total: 2000 + 2700 = 4700.
 */

class Solution {
private:
    int calculateTieredCost(int hours, vector<unordered_map<string, any>> tiers) {
        int rst = 0;
        int remaining = hours;
        for (auto& tier : tiers) {
            int minHrs = any_cast<int>(tier["minHours"]);
            int* maxHrsPtr = nullptr;
            int maxHrs = 0;
            try {
                maxHrs = any_cast<int>(tier["maxHours"]);
                maxHrsPtr = &maxHrs;
            } catch (const bad_any_cast&) {
                // maxHours is null
            }
            int rate = any_cast<int>(tier["rate"]);

            int tier_size;
            if (maxHrsPtr == nullptr) {
                tier_size = remaining;
            } else {
                tier_size = *maxHrsPtr - minHrs;
            }

            int hours_in_cur_tier = min(remaining, tier_size);
            rst += hours_in_cur_tier * rate;
            remaining -= hours_in_cur_tier;

            if (remaining == 0) {
                break;
            }
        }
        return rst;
    }

public:
    int calculateUsageCost(unordered_map<string, any> usageReport, unordered_map<string, any> pricingTable) {
        string usage_region = any_cast<string>(usageReport["region"]);
        if (pricingTable.find(usage_region) == pricingTable.end()) {
            return -1;
        }

        vector<unordered_map<string, any>> region_rates =
                any_cast<vector<unordered_map<string, any>>>(pricingTable[usage_region]);
        unordered_map<string, vector<unordered_map<string, any>>> svc_rates_tier;
        for (auto& entry : region_rates) {
            svc_rates_tier[any_cast<string>(entry["service"])] =
                    any_cast<vector<unordered_map<string, any>>>(entry["tiers"]);
        }

        vector<unordered_map<string, any>> usage_svc =
                any_cast<vector<unordered_map<string, any>>>(usageReport["services"]);
        int rst = 0;
        for (auto& item : usage_svc) {
            string svc_name = any_cast<string>(item["service"]);
            int hours = any_cast<int>(item["hours"]);
            if (svc_rates_tier.find(svc_name) == svc_rates_tier.end()) {
                return -1;
            }

            vector<unordered_map<string, any>> tiers = svc_rates_tier[svc_name];
            rst += calculateTieredCost(hours, tiers);
        }
        return rst;
    }

    static void test1() {
        Solution solution;

        unordered_map<string, any> usage1;
        usage1["region"] = string("us-east-1");
        vector<unordered_map<string, any>> services1;
        unordered_map<string, any> service1_item;
        service1_item["service"] = string("ec2.m5.large");
        service1_item["hours"] = 5;
        services1.push_back(service1_item);
        usage1["services"] = services1;

        unordered_map<string, any> pricing1;
        vector<unordered_map<string, any>> tiersList1;
        unordered_map<string, any> service1;
        service1["service"] = string("ec2.m5.large");
        vector<unordered_map<string, any>> tiers1;

        unordered_map<string, any> tier1;
        tier1["minHours"] = 0;
        tier1["maxHours"] = 2;
        tier1["rate"] = 1000;
        tiers1.push_back(tier1);

        unordered_map<string, any> tierWithNull;
        tierWithNull["minHours"] = 3;
        tierWithNull["rate"] = 900;
        tiers1.push_back(tierWithNull);

        service1["tiers"] = tiers1;
        tiersList1.push_back(service1);
        pricing1["us-east-1"] = tiersList1;

        int res1 = solution.calculateUsageCost(usage1, pricing1);
        cout << res1 << endl;  // Expected: 4700
    }

    static void test2() {
        Solution solution;

        unordered_map<string, any> usage2;
        usage2["region"] = string("ca-central-1");
        vector<unordered_map<string, any>> services2;
        unordered_map<string, any> service2_item;
        service2_item["service"] = string("db.t3.micro");
        service2_item["hours"] = 10;
        services2.push_back(service2_item);
        usage2["services"] = services2;

        unordered_map<string, any> pricing2;
        vector<unordered_map<string, any>> tiersList2;
        unordered_map<string, any> service2;
        service2["service"] = string("db.t3.micro");
        vector<unordered_map<string, any>> tiers2;
        unordered_map<string, any> tierWithNull;
        tierWithNull["minHours"] = 0;
        tierWithNull["rate"] = 500;
        tiers2.push_back(tierWithNull);
        service2["tiers"] = tiers2;
        tiersList2.push_back(service2);
        pricing2["ca-central-1"] = tiersList2;

        int res2 = solution.calculateUsageCost(usage2, pricing2);
        cout << res2 << endl;  // Expected: 5000
    }

    static void test3() {
        Solution solution;

        unordered_map<string, any> usage3;
        usage3["region"] = string("us-east-1");
        vector<unordered_map<string, any>> services3;

        unordered_map<string, any> service3_item1;
        service3_item1["service"] = string("db.t3.micro");
        service3_item1["hours"] = 25;
        services3.push_back(service3_item1);

        unordered_map<string, any> service3_item2;
        service3_item2["service"] = string("s3.standard");
        service3_item2["hours"] = 8;
        services3.push_back(service3_item2);

        usage3["services"] = services3;

        unordered_map<string, any> pricing3;
        vector<unordered_map<string, any>> ratesList3;

        unordered_map<string, any> dbService;
        dbService["service"] = string("db.t3.micro");
        vector<unordered_map<string, any>> dbTiers;

        unordered_map<string, any> dbTier1;
        dbTier1["minHours"] = 0;
        dbTier1["maxHours"] = 9;
        dbTier1["rate"] = 600;
        dbTiers.push_back(dbTier1);

        unordered_map<string, any> dbTier2;
        dbTier2["minHours"] = 10;
        dbTier2["maxHours"] = 19;
        dbTier2["rate"] = 550;
        dbTiers.push_back(dbTier2);

        unordered_map<string, any> dbTierWithNull;
        dbTierWithNull["minHours"] = 20;
        dbTierWithNull["rate"] = 500;
        dbTiers.push_back(dbTierWithNull);

        dbService["tiers"] = dbTiers;
        ratesList3.push_back(dbService);

        unordered_map<string, any> s3Service;
        s3Service["service"] = string("s3.standard");
        vector<unordered_map<string, any>> s3Tiers;

        unordered_map<string, any> s3Tier1;
        s3Tier1["minHours"] = 0;
        s3Tier1["maxHours"] = 4;
        s3Tier1["rate"] = 800;
        s3Tiers.push_back(s3Tier1);

        unordered_map<string, any> s3TierWithNull;
        s3TierWithNull["minHours"] = 5;
        s3TierWithNull["rate"] = 750;
        s3Tiers.push_back(s3TierWithNull);

        s3Service["tiers"] = s3Tiers;
        ratesList3.push_back(s3Service);

        pricing3["us-east-1"] = ratesList3;

        int res3 = solution.calculateUsageCost(usage3, pricing3);
        cout << res3 << endl;  // Expected: 20050
    }

    static void test4() {
        Solution solution;

        unordered_map<string, any> usage4;
        usage4["region"] = string("us-east-1");
        vector<unordered_map<string, any>> services4;
        unordered_map<string, any> service4_item;
        service4_item["service"] = string("ec2.m5.large");
        service4_item["hours"] = 0;
        services4.push_back(service4_item);
        usage4["services"] = services4;

        unordered_map<string, any> pricing4;
        vector<unordered_map<string, any>> tiersList4;
        unordered_map<string, any> service4;
        service4["service"] = string("ec2.m5.large");
        vector<unordered_map<string, any>> tiers4;

        unordered_map<string, any> tier4;
        tier4["minHours"] = 0;
        tier4["maxHours"] = 2;
        tier4["rate"] = 1000;
        tiers4.push_back(tier4);

        service4["tiers"] = tiers4;
        tiersList4.push_back(service4);
        pricing4["us-east-1"] = tiersList4;

        int res4 = solution.calculateUsageCost(usage4, pricing4);
        cout << res4 << endl;  // Expected: 0
    }

    static void test5() {
        Solution solution;

        unordered_map<string, any> usage5;
        usage5["region"] = string("eu-central-1");
        vector<unordered_map<string, any>> services5;
        unordered_map<string, any> service5_item;
        service5_item["service"] = string("ec2.m5.large");
        service5_item["hours"] = 5;
        services5.push_back(service5_item);
        usage5["services"] = services5;

        unordered_map<string, any> pricing5;
        vector<unordered_map<string, any>> tiersList5;
        unordered_map<string, any> service5;
        service5["service"] = string("ec2.m5.large");
        vector<unordered_map<string, any>> tiers5;
        unordered_map<string, any> tierWithNull;
        tierWithNull["minHours"] = 0;
        tierWithNull["rate"] = 1000;
        tiers5.push_back(tierWithNull);
        service5["tiers"] = tiers5;
        tiersList5.push_back(service5);
        pricing5["us-east-1"] = tiersList5;

        int res5 = solution.calculateUsageCost(usage5, pricing5);
        cout << res5 << endl;  // Expected: -1
    }
};

int main() {
    Solution::test1();
    Solution::test2();
    Solution::test3();
    Solution::test4();
    Solution::test5();
    return 0;
}
/*
Follow-up 2:
Some pricing tiers are now fixed rather than incremental. Each cost tier now includes a type field that determines how
the cost is applied:

"incremental": The cost is calculated by multiplying the tier's rate by the number of hours that fall within that tier's
range, which is the same as the previous question. "fixed": A flat fee is charged once if at least one hour (or part of
it) is assigned to the tier, regardless of how many hours fill it. For example, if a tier is defined as {"min": 0,
"max": 2, "type": "fixed", "rate": 1000}, it means:

A usage of 1 hour costs 1000.
A usage of 2 hours costs 1000.
The total usage cost is the sum of the costs calculated for every tier that the total hours touch. Return -1 if the
destination region is not found or if a service is missing a pricing rule.

Example:

Input:
usage_report = {
  "region": "us-east-1",
  "services": [
    {
      "service": "ec2.m5.large",
      "hours": 5
    }
  ]
},
pricing_table = {
  "us-east-1": [
    {
      "service": "ec2.m5.large",
      "tiers": [
        {
          "type": "fixed",
          "minHours": 0,
          "maxHours": 2,
          "rate": 1000
        },
        {
          "type": "incremental",
          "minHours": 3,
          "maxHours": null,
          "rate": 900
        }
      ]
    }
  ]
}
Output: 3700
Explanation: The report contains 5 hours of ec2.m5.large：

Tier 1 (Fixed): The first 2 hours are allocated to this tier. Since it is fixed, the cost of 1000 is charged once.
Tier 2 (Incremental): The remaining 3 hours fall into this tier and are charged at 900 per hour. Subtotal: 3 × 900 =
2700. Total: 1000 + 2700 = 3700.
 */

class Solution {
public:
    int calculateUsageCost(unordered_map<string, any> usageReport, unordered_map<string, any> pricingTable) {
        string usage_region = any_cast<string>(usageReport["region"]);
        if (pricingTable.find(usage_region) == pricingTable.end()) {
            return -1;
        }

        vector<unordered_map<string, any>> region_rates =
                any_cast<vector<unordered_map<string, any>>>(pricingTable[usage_region]);
        unordered_map<string, vector<unordered_map<string, any>>> svc_tiers;
        for (auto& entry : region_rates) {
            svc_tiers[any_cast<string>(entry["service"])] =
                    any_cast<vector<unordered_map<string, any>>>(entry["tiers"]);
        }

        vector<unordered_map<string, any>> usage_svc =
                any_cast<vector<unordered_map<string, any>>>(usageReport["services"]);
        int totalCost = 0;
        for (auto& item : usage_svc) {
            string svc_name = any_cast<string>(item["service"]);
            int hours = any_cast<int>(item["hours"]);

            if (svc_tiers.find(svc_name) == svc_tiers.end()) {
                return -1;
            }

            vector<unordered_map<string, any>> tiers = svc_tiers[svc_name];
            int itemCost = calc_tiered_cost(hours, tiers);
            totalCost += itemCost;
        }

        return totalCost;
    }

    int calc_tiered_cost(int hours, const vector<unordered_map<string, any>>& tiers) {
        int total = 0;
        int remaining = hours;

        for (const auto& tier : tiers) {
            string type = any_cast<string>(tier.at("type"));
            int minHrs = any_cast<int>(tier.at("minHours"));
            int tier_cap = 0;
            int rate = any_cast<int>(tier.at("rate"));
            if (tier.count("maxHours") && tier.at("maxHours").has_value() &&
                tier.at("maxHours").type() == typeid(int)) {
                int maxHrs = any_cast<int>(tier.at("maxHours"));
                tier_cap = maxHrs - minHrs;
            } else {
                tier_cap = remaining;
            }

            int hours_in_tier = min(remaining, tier_cap);
            if (hours_in_tier > 0) {
                if (type == "fixed") {
                    total += rate;
                } else {
                    total += hours_in_tier * rate;
                }
            }

            remaining -= hours_in_tier;
            if (remaining <= 0)
                break;
        }
        return total;
    }

    static void test1() {
        Solution solution;

        unordered_map<string, any> usage1;
        usage1["region"] = string("us-east-1");
        vector<unordered_map<string, any>> services1;
        unordered_map<string, any> service1;
        service1["service"] = string("ec2.m5.large");
        service1["hours"] = 5;
        services1.push_back(service1);
        usage1["services"] = services1;

        unordered_map<string, any> pricing1;
        vector<unordered_map<string, any>> regionPricing1;
        unordered_map<string, any> tieredService;
        tieredService["service"] = string("ec2.m5.large");
        vector<unordered_map<string, any>> tiers;
        unordered_map<string, any> tier1;
        tier1["type"] = string("fixed");
        tier1["minHours"] = 0;
        tier1["maxHours"] = 2;
        tier1["rate"] = 1000;
        tiers.push_back(tier1);
        unordered_map<string, any> incTier;
        incTier["type"] = string("incremental");
        incTier["minHours"] = 3;
        incTier["maxHours"] = any{};  // null equivalent
        incTier["rate"] = 900;
        tiers.push_back(incTier);
        tieredService["tiers"] = tiers;
        regionPricing1.push_back(tieredService);
        pricing1["us-east-1"] = regionPricing1;

        int res1 = solution.calculateUsageCost(usage1, pricing1);
        cout << res1 << endl;  // Expected: 3700
    }

    static void test2() {
        Solution solution;

        unordered_map<string, any> usage2;
        usage2["region"] = string("ca-central-1");
        vector<unordered_map<string, any>> services2;
        unordered_map<string, any> service1;
        service1["service"] = string("db.t3.micro");
        service1["hours"] = 10;
        services2.push_back(service1);
        usage2["services"] = services2;

        unordered_map<string, any> pricing2;
        vector<unordered_map<string, any>> regionPricing2;
        unordered_map<string, any> tieredService;
        tieredService["service"] = string("db.t3.micro");
        vector<unordered_map<string, any>> tiers;
        unordered_map<string, any> incTier;
        incTier["type"] = string("incremental");
        incTier["minHours"] = 0;
        incTier["maxHours"] = any{};  // null equivalent
        incTier["rate"] = 500;
        tiers.push_back(incTier);
        tieredService["tiers"] = tiers;
        regionPricing2.push_back(tieredService);
        pricing2["ca-central-1"] = regionPricing2;

        int res2 = solution.calculateUsageCost(usage2, pricing2);
        cout << res2 << endl;  // Expected: 5000
    }

    static void test3() {
        Solution solution;

        unordered_map<string, any> usage3;
        usage3["region"] = string("us-east-1");
        vector<unordered_map<string, any>> services3;
        unordered_map<string, any> service1;
        service1["service"] = string("s3.standard");
        service1["hours"] = 15;
        services3.push_back(service1);
        usage3["services"] = services3;

        unordered_map<string, any> pricing3;
        vector<unordered_map<string, any>> regionPricing3;
        unordered_map<string, any> tieredService;
        tieredService["service"] = string("s3.standard");
        vector<unordered_map<string, any>> tiers;
        unordered_map<string, any> tier1;
        tier1["type"] = string("fixed");
        tier1["minHours"] = 0;
        tier1["maxHours"] = 4;
        tier1["rate"] = 2000;
        tiers.push_back(tier1);
        unordered_map<string, any> tier2;
        tier2["type"] = string("fixed");
        tier2["minHours"] = 5;
        tier2["maxHours"] = 9;
        tier2["rate"] = 1500;
        tiers.push_back(tier2);
        unordered_map<string, any> incTier;
        incTier["type"] = string("incremental");
        incTier["minHours"] = 10;
        incTier["maxHours"] = any{};  // null equivalent
        incTier["rate"] = 800;
        tiers.push_back(incTier);
        tieredService["tiers"] = tiers;
        regionPricing3.push_back(tieredService);
        pricing3["us-east-1"] = regionPricing3;

        int res3 = solution.calculateUsageCost(usage3, pricing3);
        cout << res3 << endl;  // Expected: 9100
    }

    static void test4() {
        Solution solution;

        unordered_map<string, any> usage4;
        usage4["region"] = string("us-east-1");
        vector<unordered_map<string, any>> services4;
        unordered_map<string, any> service1;
        service1["service"] = string("ec2.m5.large");
        service1["hours"] = 0;
        services4.push_back(service1);
        usage4["services"] = services4;

        unordered_map<string, any> pricing4;
        vector<unordered_map<string, any>> regionPricing4;
        unordered_map<string, any> tieredService;
        tieredService["service"] = string("ec2.m5.large");
        vector<unordered_map<string, any>> tiers;
        unordered_map<string, any> tier1;
        tier1["type"] = string("fixed");
        tier1["minHours"] = 0;
        tier1["maxHours"] = 2;
        tier1["rate"] = 1000;
        tiers.push_back(tier1);
        tieredService["tiers"] = tiers;
        regionPricing4.push_back(tieredService);
        pricing4["us-east-1"] = regionPricing4;

        int res4 = solution.calculateUsageCost(usage4, pricing4);
        cout << res4 << endl;  // Expected: 0
    }

    static void test5() {
        Solution solution;

        unordered_map<string, any> usage5;
        usage5["region"] = string("eu-central-1");
        vector<unordered_map<string, any>> services5;
        unordered_map<string, any> service1;
        service1["service"] = string("ec2.m5.large");
        service1["hours"] = 5;
        services5.push_back(service1);
        usage5["services"] = services5;

        unordered_map<string, any> pricing5;
        vector<unordered_map<string, any>> regionPricing5;
        unordered_map<string, any> tieredService;
        tieredService["service"] = string("ec2.m5.large");
        vector<unordered_map<string, any>> tiers;
        unordered_map<string, any> incTier;
        incTier["type"] = string("incremental");
        incTier["minHours"] = 0;
        incTier["maxHours"] = any{};  // null equivalent
        incTier["rate"] = 1000;
        tiers.push_back(incTier);
        tieredService["tiers"] = tiers;
        regionPricing5.push_back(tieredService);
        pricing5["us-east-1"] = regionPricing5;

        int res5 = solution.calculateUsageCost(usage5, pricing5);
        cout << res5 << endl;  // Expected: -1
    }
};

int main() {
    Solution::test1();
    Solution::test2();
    Solution::test3();
    Solution::test4();
    Solution::test5();
    return 0;
}
