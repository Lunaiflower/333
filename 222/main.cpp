#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <algorithm>
#include <tuple>

using namespace std;

struct Transition {
    string startState;
    char symbol;
    string endState;
    bool operator<(const Transition& other) const {
        return tie(startState, symbol, endState) < tie(other.startState, other.symbol, other.endState);
    }
};

void minimizeDFA(const vector<string>& initialStates, const vector<string>& finalStates, const vector<Transition>& transitions) {
    set<string> states;
    map<string, map<char, string>> transitionTable;

    // Populate states and transition table
    for (const auto& t : transitions) {
        states.insert(t.startState);
        states.insert(t.endState);
        transitionTable[t.startState][t.symbol] = t.endState;
    }

    // Separate states into final and non-final groups
    set<string> finalStateSet(finalStates.begin(), finalStates.end());
    set<string> nonFinalStates;
    for (const auto& state : states) {
        if (finalStateSet.find(state) == finalStateSet.end()) {
            nonFinalStates.insert(state);
        }
    }

    // Initial partition
    vector<set<string>> partitions = { finalStateSet, nonFinalStates };

    // Refine partitions until they stabilize
    bool changed;
    do {
        changed = false;
        vector<set<string>> newPartitions;

        for (const auto& group : partitions) {
            map<map<char, int>, set<string>> splitGroups;
            for (const auto& state : group) {
                map<char, int> transitionGroups;
                for (const auto& entry : transitionTable[state]) {
                    char symbol = entry.first;
                    string target = entry.second;
                    for (int i = 0; i < partitions.size(); ++i) {
                        if (partitions[i].find(target) != partitions[i].end()) {
                            transitionGroups[symbol] = i;
                            break;
                        }
                    }
                }
                splitGroups[transitionGroups].insert(state);
            }
            for (const auto& splitEntry : splitGroups) {
                const auto& splitGroup = splitEntry.second;
                newPartitions.push_back(splitGroup);
                if (splitGroup.size() < group.size()) {
                    changed = true;
                }
            }
        }

        partitions = newPartitions;
    } while (changed);

    // Create a mapping from old states to new states
    map<string, string> stateMapping;
    for (const auto& group : partitions) {
        string representative = *group.begin();
        for (const auto& state : group) {
            stateMapping[state] = representative;
        }
    }

    // Generate minimized DFA transitions
    set<Transition> minimizedTransitions;
    for (const auto& t : transitions) {
        string newStart = stateMapping[t.startState];
        string newEnd = stateMapping[t.endState];
        minimizedTransitions.insert({ newStart, t.symbol, newEnd });
    }

    // Output minimized DFA
    cout << "Êä³ö£º" << endl;
    set<string> processedStates;
    for (const auto& t : minimizedTransitions) {
        if (processedStates.find(t.startState) == processedStates.end()) {
            cout << t.startState << " ";
            for (const auto& symbol : { 'a', 'b' }) {
                if (transitionTable[t.startState].count(symbol)) {
                    cout << t.startState << "-" << symbol << "->" << stateMapping[transitionTable[t.startState][symbol]] << " ";
                }
            }
            cout << endl;
            processedStates.insert(t.startState);
        }
    }
}

int main() {
    vector<string> initialStates;
    vector<string> finalStates;
    vector<Transition> transitions;

    string line;

    // Read initial states (first line)
    getline(cin, line);
    stringstream ss(line);
    string state;
    while (ss >> state) {
        initialStates.push_back(state);
    }

    // Read final states (second line)
    getline(cin, line);
    ss.clear();
    ss.str(line);
    while (ss >> state) {
        finalStates.push_back(state);
    }

    // Read transitions (remaining lines)
    while (getline(cin, line) && !line.empty()) {
        ss.clear();
        ss.str(line);
        string startState, endState;
        char symbol;
        ss >> startState >> startState >> symbol >> endState;
        transitions.push_back({ startState, symbol, endState });
    }

    minimizeDFA(initialStates, finalStates, transitions);

    return 0;
}
