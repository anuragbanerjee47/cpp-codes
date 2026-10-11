#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
using namespace std;

class Advisory
{
public:
    virtual void giveAdvice() = 0;
    virtual ~Advisory() {}
};

class Crop : public Advisory
{
protected:
    string name;
    double area;
    string season;
    double yieldPerAcre;

public:
    static int count;

    Crop()
    {
        name = "Unknown";
        area = 1;
        season = "Unknown";
        yieldPerAcre = 1;
        count++;
    }

    Crop(string n, double a, string s, double y)
    {
        if (a <= 0)
            throw invalid_argument("Area must be greater than 0");
        if (y <= 0)
            throw invalid_argument("Yield must be greater than 0");
        name = n;
        area = a;
        season = s;
        yieldPerAcre = y;
        count++;
    }

    virtual ~Crop() { count--; }

    virtual double totalYield() { return area * yieldPerAcre; }
    virtual void display() = 0;
    virtual void save(ofstream &file) = 0;

    bool operator>(Crop &other)
    {
        return totalYield() > other.totalYield();
    }

    string getName() { return name; }
};

int Crop::count = 0;

class CerealCrop : public Crop
{
    string fertilizer;

public:
    CerealCrop(string n, double a, string s, double y, string f)
        : Crop(n, a, s, y)
    {
        fertilizer = f;
    }

    void display()
    {
        cout << name << " | Cereal | " << area << " acres | " << season
             << " | Fertilizer: " << fertilizer
             << " | Total yield: " << totalYield() << endl;
    }

    void giveAdvice()
    {
        cout << name << ": Use " << fertilizer << " and harvest when grains turn golden.\n";
    }

    void save(ofstream &file)
    {
        file << "Cereal " << name << " " << area << " " << season << " "
             << yieldPerAcre << " " << fertilizer << endl;
    }
};

class VegetableCrop : public Crop
{
    int irrigation; // times per week

public:
    VegetableCrop(string n, double a, string s, double y, int i)
        : Crop(n, a, s, y)
    {
        if (i <= 0)
            throw invalid_argument("Irrigation must be greater than 0");
        irrigation = i;
    }

    double totalYield() { return area * yieldPerAcre * 0.9; }

    void display()
    {
        cout << name << " | Vegetable | " << area << " acres | " << season
             << " | Irrigation/week: " << irrigation
             << " | Total yield: " << totalYield() << endl;
    }

    void giveAdvice()
    {
        cout << name << ": Water " << irrigation << " times a week and check for pests.\n";
    }

    void save(ofstream &file)
    {
        file << "Vegetable " << name << " " << area << " " << season << " "
             << yieldPerAcre << " " << irrigation << endl;
    }
};

Crop *crops[10];
int total = 0;

void addCrop(bool isCereal)
{
    if (total == 10)
        throw runtime_error("Farm is full");

    string name, season;
    double area, y;
    cout << "Name (one word): ";
    cin >> name;
    cout << "Area (acres): ";
    cin >> area;
    cout << "Season: ";
    cin >> season;
    cout << "Yield per acre: ";
    cin >> y;

    if (isCereal)
    {
        string fert;
        cout << "Fertilizer type: ";
        cin >> fert;
        crops[total] = new CerealCrop(name, area, season, y, fert);
    }
    else
    {
        int irr;
        cout << "Irrigation times per week: ";
        cin >> irr;
        crops[total] = new VegetableCrop(name, area, season, y, irr);
    }
    total++;
    cout << "Crop added!\n";
}

void showCrops()
{
    for (int i = 0; i < total; i++)
    {
        cout << i + 1 << ". ";
        crops[i]->display();
    }
    cout << "Total crops: " << Crop::count << endl;

    cout << "\nAdvice:\n";
    for (int i = 0; i < total; i++)
    {
        crops[i]->giveAdvice();
    }
}

void compareCrops()
{
    int a, b;
    cout << "First crop number: ";
    cin >> a;
    cout << "Second crop number: ";
    cin >> b;
    if (a < 1 || b < 1 || a > total || b > total)
        throw out_of_range("Crop number does not exist");

    if (*crops[a - 1] > *crops[b - 1])
        cout << crops[a - 1]->getName() << " has the higher yield.\n";
    else
        cout << crops[b - 1]->getName() << " has the higher (or equal) yield.\n";
}

void saveCrops()
{
    ofstream file("crops.txt");
    for (int i = 0; i < total; i++)
    {
        crops[i]->save(file);
    }
    cout << "Saved!\n";
}

void loadCrops()
{
    ifstream file("crops.txt");
    if (!file)
        throw runtime_error("No saved file found");

    for (int i = 0; i < total; i++)
        delete crops[i];
    total = 0;

    string type, name, season, extra;
    double area, y;
    while (total < 10 && file >> type >> name >> area >> season >> y >> extra)
    {
        if (type == "Cereal")
            crops[total] = new CerealCrop(name, area, season, y, extra);
        else
            crops[total] = new VegetableCrop(name, area, season, y, atoi(extra.c_str()));
        total++;
    }
    cout << "Loaded " << total << " crops.\n";
}

int main()
{
    int choice = 0;

    while (choice != 7)
    {
        cout << "\n--- Smart Farm Menu ---\n";
        cout << "1. Add cereal crop\n";
        cout << "2. Add vegetable crop\n";
        cout << "3. Show all crops\n";
        cout << "4. Compare two crops\n";
        cout << "5. Save to file\n";
        cout << "6. Load from file\n";
        cout << "7. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        try
        {
            if (!cin)
            {
                cin.clear();
                cin.ignore(1000, '\n');
                choice = 0;
                throw invalid_argument("Please enter a number");
            }

            if (choice == 1)
                addCrop(true);
            else if (choice == 2)
                addCrop(false);
            else if (choice == 3)
                showCrops();
            else if (choice == 4)
                compareCrops();
            else if (choice == 5)
                saveCrops();
            else if (choice == 6)
                loadCrops();
        }
        catch (exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }

    for (int i = 0; i < total; i++)
        delete crops[i];
    return 0;
}