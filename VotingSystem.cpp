#include <bits/stdc++.h>
using namespace std;

// ----------- ENTITIES -----------
class Candidate {
    int id;
    string name;
    int votes;

public:
    Candidate(int id, string name) : id(id), name(name), votes(0) {}
    int getId() const { return id; }
    string getName() const { return name; }
    int getVotes() const { return votes; }
    void addVote() { votes++; }
};


class Voter {
    int id;
    string name;
    bool hasVoted;

public:
    Voter(int id, string name) : id(id), name(name), hasVoted(false) {}
    int getId() const { return id; }
    string getName() const { return name; }
    bool alreadyVoted() const { return hasVoted; }
    void markVoted() { hasVoted = true; }
};

// ----------- VOTING SYSTEM -----------
class VotingSystem {
    unordered_map<int, Candidate*> candidates;
    unordered_map<int, Voter*> voters;

public:
    ~VotingSystem() {
        for (auto &c : candidates) delete c.second;
        for (auto &v : voters) delete v.second;
    }

    void addCandidate(int id, string name) {
        if (candidates.count(id)) {
            cout << "[Error] Candidate with this ID already exists!\n";
            return;
        }
        candidates[id] = new Candidate(id, name);
    }

    void addVoter(int id, string name) {
        if (voters.count(id)) {
            cout << "[Error] Voter with this ID already exists!\n";
            return;
        }
        voters[id] = new Voter(id, name);
    }

    void vote(int voterId, int candidateId) {
        if (!voters.count(voterId)) {
            cout << "[Error] Invalid voter!\n";
            return;
        }
        if (!candidates.count(candidateId)) {
            cout << "[Error] Invalid candidate!\n";
            return;
        }
        if (voters[voterId]->alreadyVoted()) {
            cout << "[Error] Voter has already voted!\n";
            return;
        }

        candidates[candidateId]->addVote();
        voters[voterId]->markVoted();
        cout << voters[voterId]->getName() << " successfully voted for "
             << candidates[candidateId]->getName() << "\n";
    }

    void displayResults() {
        cout << "\n------ ELECTION RESULTS ------\n";
        int maxVotes = -1;
        string winner = "No votes cast";

        for (auto &entry : candidates) {
            Candidate* c = entry.second;
            cout << c->getName() << " : " << c->getVotes() << " votes\n";
            if (c->getVotes() > maxVotes) {
                maxVotes = c->getVotes();
                winner = c->getName();
            }
        }
        cout << "Winner: " << winner << "\n";
        cout << "--------------------------------\n";
    }
};

// ----------- MAIN DEMO -----------
int main() {
    VotingSystem voting;

    // Add Candidates
    voting.addCandidate(1, "Alice");
    voting.addCandidate(2, "Bob");
    voting.addCandidate(3, "Charlie");

    // Add Voters
    voting.addVoter(101, "John");
    voting.addVoter(102, "Emma");
    voting.addVoter(103, "Noah");

    // Voting
    voting.vote(101, 1);
    voting.vote(102, 1);
    voting.vote(103, 2);
    voting.vote(103, 2); // duplicate vote test

    // Results
    voting.displayResults();

    return 0;
}
