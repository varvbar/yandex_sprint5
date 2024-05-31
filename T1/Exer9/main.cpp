#include "log_duration.h"
#include "testiks.h"

#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>
#include <assert.h>

using namespace std;

vector<float> ComputeAvgTemp(const vector<vector<float>>& measures) {
    // место для вашего решения
    if(measures.empty()){
        return {};
    }
    
    const size_t days_size = measures.size();
    const size_t day_size = measures[0].size();
    
    vector<float> sum_meas(day_size);
    vector<int> positive_meas(day_size);

    for(size_t j = 0; j < days_size; ++j){
        for(size_t i = 0; i < day_size; ++i){
            sum_meas[i] += (measures[j][i] > 0 ? measures[j][i] : 0);
            positive_meas[i] += (measures[j][i] > 0 ? 1 : 0);
        }
    }

    vector<float> result(day_size);
    
    for(size_t i = 0; i < day_size; ++i){
        result[i] = (positive_meas[i] != 0 ? sum_meas[i]/positive_meas[i] : 0);
    }

    return result;
}

vector<float> GetRandomVector(int size) {
    static mt19937 engine;
    uniform_real_distribution<float> d(-100, 100);

    vector<float> res(size);
    for (int i = 0; i < size; ++i) {
        res[i] = d(engine);
    }

    return res;
}

void Test() {
    // 4 дня по 3 измерения
    vector<vector<float>> v = {
        {0, -1, -1},
        {1, -2, -2},
        {2, 3, -3},
        {3, 4, -4}
    };

    // среднее для 0-го измерения (1+2+3) / 3 = 2 (не учитывам 0)
    // среднее для 1-го измерения (3+4) / 2 = 3.5 (не учитывам -1, -2)
    // среднее для 2-го не определено (все температуры отрицательны), поэтому должен быть 0

    assert(ComputeAvgTemp(v) == vector<float>({2, 3.5f, 0}));
}
void MyTest(){
    vector<vector<float>> v = {
        {0, -1, -1},
        {1, -2, -2},
        {2, 3, -3},
        {3, 4, -4}
    };
    vector<float> results = ComputeAvgTemp(v);
    ASSERT_HINT(results[0] = 2, "Wrong calc"s);
    ASSERT_HINT(results[1] = 3.5f, "Wrong calc"s);
    ASSERT_HINT(results[2] = 0.f, "Wrong calc"s);
}

void TestProg(){
    RUN_TEST(MyTest);
}

int main() {
    TestProg();
    /* vector<vector<float>> data;
    data.reserve(5000);

    for (int i = 0; i < 5000; ++i) {
        data.push_back(GetRandomVector(5000));
    }

    vector<float> avg;
    {
        LOG_DURATION("ComputeAvgTemp"s);
        avg = ComputeAvgTemp(data);
    }

    cout << "Total mean: "s << accumulate(avg.begin(), avg.end(), 0.f) / avg.size() << endl; */
}