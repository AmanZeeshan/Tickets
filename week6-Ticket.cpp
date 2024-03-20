#include <iostream>
#include <vector>
#include <string>
#include <map>

struct Attraction {
    std::string name;
    double cost;
};

struct Ticket {
    std::string type;
    double costOneDay;
    double costTwoDays;
    bool appliesForExtra; // Indicates if the ticket can have extra attractions
};

// Global variables for attractions and tickets
std::vector<Attraction> attractions = {
    {"Lion feeding", 2.50},
    {"Penguin feeding", 2.00},
    {"Evening barbecue", 5.00} // Two-day tickets only
};

std::vector<Ticket> tickets = {
    {"One adult", 20.00, 30.00, true},
    {"One child", 12.00, 18.00, true},
    {"One senior", 16.00, 24.00, true},
    {"Family ticket", 60.00, 90.00, true},
    {"Group of six or more", 15.00, 22.50, true}
};

// Function prototypes
void displayOptions();
void processBooking();
double calculateCost(int ticketIndex, int days, int quantity, const std::vector<int>& attractionsSelected);
void suggestBetterValue(double& totalCost, int& ticketIndex, int quantity);

int main() {
    displayOptions();
    processBooking();
    return 0;
}

void displayOptions() {
    std::cout << "Ticket Options:\n";
    for (int i = 0; i < tickets.size(); ++i) {
        std::cout << i + 1 << ". " << tickets[i].type 
                  << ": $" << tickets[i].costOneDay << " for one day, $" 
                  << tickets[i].costTwoDays << " for two days\n";
    }

    std::cout << "\nExtra Attractions:\n";
    for (int i = 0; i < attractions.size(); ++i) {
        std::cout << i + 1 << ". " << attractions[i].name 
                  << ": $" << attractions[i].cost << "\n";
    }
}

void processBooking() {
    int ticketIndex, days, quantity, attractionChoice, numAttractions;
    double totalCost;
    std::vector<int> attractionsSelected;

    std::cout << "\nEnter ticket option (1-" << tickets.size() << "): ";
    std::cin >> ticketIndex;
    ticketIndex--; // Adjust for zero-based index

    std::cout << "Enter number of days (1 or 2): ";
    std::cin >> days;

    std::cout << "Enter quantity: ";
    std::cin >> quantity;

    if (tickets[ticketIndex].appliesForExtra) {
        std::cout << "Enter number of extra attractions (0-" << attractions.size() << "): ";
        std::cin >> numAttractions;

        for (int i = 0; i < numAttractions; ++i) {
            std::cout << "Select attraction " << i + 1 << ": ";
            std::cin >> attractionChoice;
            attractionsSelected.push_back(attractionChoice - 1); // Adjust for zero-based index
        }
    }

    totalCost = calculateCost(ticketIndex, days, quantity, attractionsSelected);

    // Suggest better value if applicable
    suggestBetterValue(totalCost, ticketIndex, quantity);

    std::cout << "\nTotal cost for booking: $" << totalCost << "\n";
}

double calculateCost(int ticketIndex, int days, int quantity, const std::vector<int>& attractionsSelected) {
    double cost = 0.0;

    // Calculate ticket cost
    if (days == 1) {
        cost += tickets[ticketIndex].costOneDay * quantity;
    } else {
        cost += tickets[ticketIndex].costTwoDays * quantity;
    }

    // Add extra attractions cost
    for (int index : attractionsSelected) {
        cost += attractions[index].cost * quantity;
    }

    return cost;
}

void suggestBetterValue(double& totalCost, int& ticketIndex, int quantity) {
    // Example suggestion mechanism for groups larger than six
    if (quantity >= 6) {
        double groupCost = tickets[4].costOneDay * quantity; // Group price for one day
        if (totalCost > groupCost) {
            std::cout << "Suggestion: A group booking would be cheaper at $" << groupCost << "\n";
            totalCost = groupCost; // Update total cost to reflect suggested option
        }
    }

    // Example suggestion for family tickets
    // Note: This is a simplified suggestion mechanism. You might want to add more sophisticated logic.
    if (quantity == 2) { // Assuming 2 adults could opt for a family ticket instead
        double familyCost = tickets[3].costOneDay; // Family ticket price for one day
        if (totalCost > familyCost) {
            std::cout << "Suggestion: A family ticket would be cheaper at $" << familyCost << "\n";
            totalCost = familyCost; // Update total cost to reflect suggested option
        }
    }
}

