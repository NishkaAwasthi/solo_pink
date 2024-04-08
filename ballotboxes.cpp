#include <iostream>
#include <queue>
#include <tuple>
#include <cmath>
using namespace std;


// Define a custom comparison function to compare tuples based on the first integer
auto compare = [](const tuple<double, double, double>& lhs, const tuple<double, double, double>& rhs) {
    // Compare based on the first element of the tuple
    return get<0>(lhs) < get<0>(rhs);
};

int main() {
    int cities;
    int ballots;
    cin >> cities >> ballots;

    while (cities != -1) {
        // collect populations
        priority_queue<tuple<double, double, double>, vector<tuple<double, double, double>>, decltype(compare)> heap(compare);

        for (int i = 0; i < cities; i++) {
            int temp;
            cin >> temp;
            heap.push(make_tuple(temp, 1, temp));
            ballots--;
        }
        
        while (ballots > 0) {
            auto top_tuple = heap.top();
            double pop_by_ballot = get<0>(top_tuple);
            double num_ballots = get<1>(top_tuple);
            double tot_pop = get<2>(top_tuple);

            
            // Modify values
            num_ballots++;
            pop_by_ballot = ceil(tot_pop/num_ballots);
            ballots--;
            
            // Pop the top tuple
            heap.pop();
            
            // Push the modified tuple back into the heap
            heap.push(make_tuple(pop_by_ballot, num_ballots, tot_pop));
        }
            
        cout << get<0>(heap.top()) << "\n";
        
        // get new cities and ballots
        cin >> cities >> ballots;
    }
}
