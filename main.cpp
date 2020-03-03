#include <bits/stdc++.h>

using namespace std;

// change to 0.5 to get a slightly better score on task F
#define PROCESS_EXPONENT 1

int B, L, D;

vector<int> bookScores;
unordered_set<int> remainingBooks;
vector<int> scannedLibs;
unordered_set<int> remainingLibs;
class Lib;
vector<Lib> libs;

class Lib
{
public:
    int id;
    int bookCount, process, perday;
    int val;
    vector<int> books;
    vector<int> booksToScan;
    vector<int> scannedBooks;

    // also reads input
    Lib(int id) : id(id)
    {
        cin >> bookCount >> process >> perday;

        books.reserve(bookCount);
        booksToScan.reserve(bookCount);
        scannedBooks.reserve(bookCount);

        int bid;
        for (int i = 0; i < bookCount; i++)
        {
            cin >> bid;
            books.push_back(bid);
        }

        // Sort the books in descending score order
        sort(books.begin(), books.end(),
             [](int bid1, int bid2)
             {
                return bookScores[bid1] > bookScores[bid2];
             }
        );

        // Calculate this library's value
        update();

        // register this library as not-yet-scanned
        remainingLibs.insert(id);
    }

    // update which books would be scanned and how many points they would score
    // if this library started scanning today
    void update()
    {
//cerr << "Updating the library " << id << "\n";

        // reset values
        booksToScan.clear();
        val = 0;

        // how many books it can scan max starting from today
        // may be negative, but no need to rectify
        int toScanMax = (D - process) * perday;
//cerr << "toScanMax = " << toScanMax << "\n";
        // determine how many books can be scanned from now on
        int toScanCount = 0;
        for (int i = 0; i < books.size() && toScanCount < toScanMax; i++)
        {
            int bid = books[i];
//cerr << "Book " << bid << " with " << bookScores[bid] << " points ";
            auto f = remainingBooks.find(bid);
            if (f != remainingBooks.end())
            {
                val += bookScores[bid];
                booksToScan.push_back(bid);
                toScanCount++;
//cerr << "registered to be scanned.\t";
            }
            else
            {
//cerr << "already scanned before.\t";
                ;
            }
//cerr << "toScanCount = " << toScanCount << "\n";
        }
    }

    void scan()
    {
//cerr << "Scanning the library " << id << "\n";
        
        remainingLibs.erase(id);
        scannedLibs.push_back(id);

        // scan books
        for (int i = 0; i < booksToScan.size(); i++)
        {
            int bid = booksToScan[i];
            scannedBooks.push_back(bid);
            remainingBooks.erase(bid);
//cerr << "Book " << bid << " scanned.\n";
        }

        // update available days remaining
        D -= process;
//cerr << "Remaining days D = " << D << "\n";

        // trigger updating the value of each remaining library
        for (int lid : remainingLibs)
        {
            libs[lid].update();
        }
    }

    void output()
    {
        // If did not scan any book, skip
        if (scannedBooks.size() == 0) return;

        cout << id << " " << scannedBooks.size() << "\n";
        for (int bid : scannedBooks)
        {
            cout << bid << " ";
        }
        cout << "\n";
    }
};


// The function to evaluate the remaining libraries
// Returns the id of the best library to scan now
int findBestLib()
{
    int maxPriority = INT_MIN; // the higher the better
    int bestLid = -1;     // the id/index of the library with the highest priority
    
    int priority;
    for (int lid : remainingLibs)
    {
        auto & lib = libs[lid];
        priority = lib.val / pow(lib.process, PROCESS_EXPONENT);

        if (priority > maxPriority)
        {
            bestLid = lid;
            maxPriority = priority;
        }
    }

    return bestLid;
}


int main()
{

    // TAKE INPUT
    cin >> B >> L >> D;

    bookScores.reserve(B);
    scannedLibs.reserve(L);
    libs.reserve(L);

    // Register books and scores
    int s;
    for (int i = 0; i < B; i++)
    {
        cin >> s;
        bookScores.push_back(s);
        remainingBooks.insert(i);
    }

    // Register libraries
    for (int i = 0; i < L; i++)
    {
        libs.emplace_back(Lib(i));
    }

    // PROCESS
    // Scan the best library
    // (highest value; prefer lower process for tiebreak)
    // At the end of scan(), the days D and other libraries' values are updated
    while (D >= 0 && remainingLibs.size() > 0)
    {
        int bestLid = findBestLib();
        libs[bestLid].scan();
    }

    // OUTPUT
    // Ignore the libraries that could not scan any books
    int scannedLibCount = 0;
    for (int i = 0; i < scannedLibs.size(); i++)
    {
        if (libs[scannedLibs[i]].scannedBooks.size() > 0)
        {
            scannedLibCount++;
        }
    }
    cout << scannedLibCount << "\n";
    for (int i = 0; i < scannedLibs.size(); i++)
    {
        // libraries that could not scan any book won't output 
        libs[scannedLibs[i]].output();
    }

    return 0;
}