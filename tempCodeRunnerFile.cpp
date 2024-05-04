<< "List of highest spending users in descending order:" << endl;
                auto compare = [](const Account* a1, const Account* a2) { // Using pointers
                    return a1->expenditure < a2->expenditure;
                };
                priority_queue<Account*, vector<Account*>, decltype(compare)> pq(compare);
                break;
            }