#include <string>
#include <cmath>
using namespace std;

template<typename F, typename G>
auto compose(F f, G g){
    return [f, g](auto x){
        return f(g(x));
    };
};

auto baseSalaryForPosition = [](const string& position){
    int baseSalary;
    if(position == "Tester") baseSalary = 1500;
    if(position == "Analyst") baseSalary = 1600;
    if(position == "Developer") baseSalary = 2000;
    if(position == "Team Leader") baseSalary = 3000;
    if(position == "Manager") baseSalary = 4000;
    return baseSalary;
};

class BaseSalaryForPosition{
    private:
        const string& position;

    public:
        BaseSalaryForPosition(const string& position) : position(position){};

        int baseSalaryForPosition() const{
            int baseSalary;
            if(position == "Tester") baseSalary = 1500;
            if(position == "Analyst") baseSalary = 1600;
            if(position == "Developer") baseSalary = 2000;
            if(position == "Team Leader") baseSalary = 3000;
            if(position == "Manager") baseSalary = 4000;
            return baseSalary;
        }
};

auto factorForSeniority = [](const string& seniority_level){
    double factor;
    if(seniority_level == "Entry") factor = 1;
    if(seniority_level == "Junior") factor = 1.2;
    if(seniority_level == "Senior") factor = 1.5;
    return factor;
};

auto factorForContinuity = [](const string& years_worked_continuously){
    double continuityFactor;
    int continuity = stoi(years_worked_continuously);
    if(continuity < 3) continuityFactor = 1;
    if(continuity >= 3 && continuity < 5) continuityFactor = 1.2;
    if(continuity >= 5 && continuity < 10) continuityFactor = 1.5;
    if(continuity >=10 && continuity <= 20) continuityFactor = 1.7;
    if(continuity > 20) continuityFactor = 2;
    return continuityFactor;
};

auto bonusLevel = [](const string& special_bonus_level){
    return stoi(special_bonus_level);
};

auto specialBonusFactor = [] (auto bonusLevel) {
    return bonusLevel() * 0.03;
};

auto computeSalary = [](const BaseSalaryForPosition& baseSalaryForPosition, auto factorForSeniority, auto factorForContinuity, auto bonusFactor){
    return ceil (
            (1 + bonusFactor()) * baseSalaryForPosition.baseSalaryForPosition() * factorForSeniority() * factorForContinuity()
            );
};
