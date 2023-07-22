#include "CStack.h"
#include "Factory.h"

#include <chrono>
#include <omp.h>


int fillInputFile(int); // filling input file

int fillInputFile(int numberOfLines) {

    ofstream File("input.txt");

    for (int i = 0; i < numberOfLines; ++++i) {
        File << "0 file" << i << " 0" << endl;
        File << "1 file" << i + 1 << " 1" << endl;
    }

    File.close();

    return 0;
}


int main() {

    CData0 a(7);

    fillInputFile(10);

    vector <Factory*> f = {new FactoryCData0, new FactoryCData1};
    vector <CStack*> arr;
    size_t n = 0, e = 0;
    ifstream in("input.txt");
    string str;

    try {
        while (getline(in,str)) {
            if (str.size() == 0) {
                ++e;
                continue;
            }
            CStack* tmp = CStack::create_by_Factory(str, f);
            arr.push_back(tmp);
            ++e;
            ++n;
        }
        cout << "--------------------" << endl;
        for (size_t i = 0; i < n; ++i)
            arr[i]->output();

        cout << "The output to output-files was made" << endl;
        cout << "--------------------" << endl;

        // cyclic shift testing

        cout << "Cyclic shift testing" << endl;
//        cout << "Before cyclic shift:" << endl;

//        for (size_t i = 0; i < n; ++i)
//            cout << *arr[i] << endl;

        // cyclic shift without omp
        CData0 tmpObj1(*arr[0]);

        auto start = chrono::system_clock::now();

        for (size_t i = 0; i < n - 1; ++i)
            *arr[i] = *arr[i + 1];
        *arr[n - 1] = tmpObj1;

        auto end = chrono::system_clock::now();
        int elapsed_ms = static_cast<int>
        (chrono::duration_cast<chrono::milliseconds>(end - start).count() );
        cout << "\nTime for cyclic shift without omp constructions = " << elapsed_ms <<" ms\n";

        // cyclic shift WITH omp
        CData0 tmpObj11(*arr[0]), tmpObj2(*arr[n / 4]), tmpObj3(*arr[n / 2]), tmpObj4(*arr[(3 * n) / 4]); // last elements of subArrays

        start = chrono::system_clock::now();

#pragma omp parallel sections
        {
#pragma omp section
            {
                for (size_t i = 0; i < n / 4 - 1; ++i)
                    *arr[i] = *arr[i + 1];
                *arr[n / 4 - 1] = tmpObj2;
            }
#pragma omp section
            {
                for (size_t i = n / 4; i < n / 2 - 1; ++i)
                    *arr[i] = *arr[i + 1];
                *arr[n / 2 - 1] = tmpObj3;
            }
#pragma omp section
            {
                for (size_t i = n / 2; i < (3 * n) / 4 - 1; ++i)
                    *arr[i] = *arr[i + 1];
                *arr[(3 * n) / 4 - 1] = tmpObj4;
            }
#pragma omp section
            {
                for (size_t i = (3 * n) / 4; i < n - 1; ++i)
                    *arr[i] = *arr[i + 1];
                *arr[n - 1] = tmpObj11;
            }
        }
        end = chrono::system_clock::now();
        elapsed_ms = static_cast<int>
        (chrono::duration_cast<chrono::milliseconds>(end - start).count() );
        cout << "Time for cyclic shift WITH omp constructions = " << elapsed_ms <<" ms\n";
        
        cout << "--------------------" << endl;
//        cout << "After:" << endl;
//        for (size_t i = 0; i < n; ++i)
//            cout << *arr[i] << endl;
//        cout << "--------------------" << endl;

//        for (size_t i = 0; i < n; ++i)
//            arr[i]->output();
//        cout << "The output to output-files was made" << endl;
//        cout << "--------------------" << endl;
        // incrementing and decrementing testing
//        cout << "---------------------" << endl;
//        cout << "Incrementing testing:" << endl;
//        cout << "Object at the beginning: " << st1 << endl;
//        cout << "Return prefix value: " << --st1 << endl;
//        cout << "Return postfix value: " << st1-- << endl;
//        cout << "After postfix:" << st1 << endl;
//        cout << "Return prefix value: " << --st1 << endl;
//        cout << "Return prefix value: " << --st1 << endl;
//        cout << "---------------------" << endl;
        // operator + testing
//        cout << "--------------------" << endl;
//        cout << "Operator + testing" << endl;
//        cout << (*arr[4]) << " + " <<  (*arr[1]) << " = ";
//        cout << (*arr[4]) + (*arr[1]) << endl;
//        cout << (*arr[0]) << " + " <<  (*arr[2]) << " = ";
//        cout << (*arr[0]) + (*arr[2]) << endl;
//        cout << (*arr[3]) << " + " <<  (*arr[4]) << " = ";
//        cout << (*arr[3]) + (*arr[4]) << endl;
//        cout << "--------------------" << endl;

        cout << "Sum searching testing\n\n";
        // sum searching without omp construction
        CData0 result_sum_wo_omp(0);

        start = chrono::system_clock::now();

        for (size_t i = 0; i < n; ++i) {
            result_sum_wo_omp = result_sum_wo_omp + *arr[i];
            cout << result_sum_wo_omp << endl;
        }

//        cout << "Sum without omp constructions = " << result_sum_wo_omp << endl;
        end = chrono::system_clock::now();
        elapsed_ms = static_cast<int>
        (chrono::duration_cast<chrono::milliseconds>(end - start).count() );
        cout << "Time for searching the sum without omp constructions = " << elapsed_ms <<" ms\n";
        cout << "sum afer adding WO omp = " << result_sum_wo_omp << endl;
//        cout << "--------------------" << endl;

        // sum searching WITH omp construction
        CData0 result_sum_W_omp(0);

        CData0 sum1(0);
        CData0 sum2(0);
        CData0 sum3(0);
        CData0 sum4(0);

        start = chrono::system_clock::now();

#pragma omp parallel sections
        {
#pragma omp section
            {
                for (size_t i = 0; i < n / 4; ++i)
                    sum1 = sum1 + *arr[i];
            }
#pragma omp section
            {
                for (size_t i = n / 4; i < n / 2 ; ++i)
                    sum2 = sum2 + *arr[i];
            }
#pragma omp section
            {
                for (size_t i = n/2; i < (3 * n) / 4; ++i)
                    sum3 = sum3 + *arr[i];
            }
#pragma omp section
            {
                for (size_t i = (3 * n) / 4; i < n; ++i)
                    sum4 = sum4 + *arr[i];
            }
        }
        result_sum_W_omp = sum1 + sum2 + sum3 + sum4;

        end = chrono::system_clock::now();
        elapsed_ms = static_cast<int>
        (chrono::duration_cast<chrono::milliseconds>(end - start).count() );
        cout << "Time for searching the sum WITH omp constructions = " << elapsed_ms <<" ms\n";
        cout << "sum afer adding WITH omp = " << result_sum_W_omp << endl;
        cout << "--------------------" << endl;

//        cout << "Sum WITH omp constructions = " << result_sum_wo_omp << endl;

    }
    catch (int i) {
        if (i == -1) {
            cout << "Incorrect type(string " << e + 1 << ")\n";
        }
        if (i == -2) {
            cout << "Incorrect data(string " << e + 1 << ")\n";
        }
    }

    for (size_t i = 0; i < n; ++i)
        delete arr[i];
    for (size_t i = 0; i < 2; ++i)
        delete f[i];

    in.close();

    return 0;
}
