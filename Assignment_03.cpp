#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// ---------- generate test cases ----------

vector<int> gen_random_ints(int n, int minv, int maxv) {
    static random_device rd;
    static mt19937 mt(rd());
    uniform_int_distribution<int> dist(minv, maxv);
    vector<int> a(n);
    for (int i=0;i<n;++i) a[i] = dist(mt);
    return a;
}
vector<int> gen_sorted_ints(int n, int minv, int maxv) {
    vector<int> a = gen_random_ints(n, minv, maxv);
    sort(a.begin(), a.end());
    return a;
}
vector<int> gen_reverse_ints(int n, int minv, int maxv) {
    vector<int> a = gen_sorted_ints(n, minv, maxv);
    reverse(a.begin(), a.end());
    return a;
}
vector<int> gen_few_unique(int n, int minv, int maxv) {
    static random_device rd; static mt19937 mt(rd());
    vector<int> choices;
    int k = max(2, (maxv-minv+1) / 10);
    for (int i=0;i<k;i++) choices.push_back(minv + (i*(maxv-minv))/max(1,k-1));
    vector<int> a(n);
    uniform_int_distribution<int> pick(0, (int)choices.size()-1);
    for (int i=0;i<n;i++) a[i] = choices[pick(mt)];
    return a;
}

// ---------- Counting Sort (non-stable) ----------
void counting_sort_nonstable(vector<int> &a) {
    int minv = *min_element(a.begin(), a.end());
    int maxv = *max_element(a.begin(), a.end());

    int k = maxv - minv + 1;

    vector<int> counts(k, 0);
    for (int x : a) counts[x - minv]++;
    int idx = 0;
    for (int v = 0; v < k; ++v) {
        while (counts[v]--) {
            a[idx++] = v + minv;
        }
    }
}

// ---------- Counting Sort (stable) ----------
vector<int> counting_sort_stable(const vector<int> &a) {
    int minv = *min_element(a.begin(), a.end());
    int maxv = *max_element(a.begin(), a.end());

    int k = maxv - minv + 1;
    vector<int> counts(k, 0);
    for (int x : a) counts[x - minv]++;
    // prefix sums
    for (int i=1;i<k;i++) counts[i] += counts[i-1];
    vector<int> out(a.size());
    // iterate right to left to preserve stability
    for (int i = (int)a.size()-1; i>=0; --i) {
        int v = a[i] - minv;
        counts[v]--;
        out[counts[v]] = a[i];
    }
    return out;
}

// ---------- LSD Radix Sort (base 10, nonnegative integers) ----------
void lsd_radix_sort(vector<int> &a) {
    if (a.empty()) return;
    int maxv = *max_element(a.begin(), a.end());
    int exp = 1;
    vector<int> output(a.size());
    while (maxv / exp > 0) {
        vector<int> count(10, 0);
        for (int v : a) {
            int d = (v / exp) % 10;
            count[d]++;
        }
        for (int i=1;i<10;i++) count[i] += count[i-1];
        for (int i = (int)a.size()-1; i>=0; --i) {
            int d = (a[i] / exp) % 10;
            count[d]--;
            output[count[d]] = a[i];
        }
        a = output;
        exp *= 10;
    }
}

// ---------- Bucket Sort  ----------
void bucket_sort(vector<int> &a,  int num_buckets = 16) {
    int minv = *min_element(a.begin(), a.end());
    int maxv = *max_element(a.begin(), a.end());
    
    if (a.empty()) return;
    double range = double(maxv - minv + 1);
    int m = max(1, num_buckets);
    vector<vector<int>> buckets(m);
    for (int v : a) {
        int idx = int((double)(v - minv) / range * m);
        if (idx == m) idx = m-1;
        buckets[idx].push_back(v);
    }
    // sort each bucket using stable sort 
    int pos = 0;
    for (auto &b : buckets) {
        sort(b.begin(), b.end()); // stable sort 
        for (int v : b) a[pos++] = v;
    }
}

// ---------- Pigeonhole Sort (stable using vectors) ----------
void pigeonhole_sort(vector<int> &a) {
    int minv = *min_element(a.begin(), a.end());
    int maxv = *max_element(a.begin(), a.end());

    int range = maxv - minv + 1;
    vector<vector<int>> holes(range);
    for (int v : a) holes[v - minv].push_back(v);
    int idx = 0;
    for (int i=0;i<range;i++) {
        for (int val : holes[i]) a[idx++] = val;
    }
}

// ---------- check sorted ----------
bool is_sorted_asc(const vector<int> &a) {
    for (int i=1;i<(int)a.size();++i) if (a[i-1] > a[i]) return false;
    return true;
}

// ---------- timing  ----------
template<typename F, typename... Args>
double time_ms(F func, Args&&... args) {
    auto t1 = high_resolution_clock::now();
    func(forward<Args>(args)...);
    auto t2 = high_resolution_clock::now();
    return duration<double, milli>(t2 - t1).count();
}
// ---------- print Array ----------
void printArr(const vector<int>& arr){
    if (arr.size()>20){
        cout<<endl;
        return;
    }
    cout<<"[ ";
    for(int i=0;i<arr.size();i++){
        cout<<arr[i]<<" ";
    };
    cout<<"]"<<endl;

}

// ---------- Test cases ----------
void run_one_case(const vector<int>& case_data, int minv, int maxv) {
    cout << "n=" << case_data.size() << " range=[" << minv << "," << maxv << "]\n";
    printArr(case_data);
 
    vector<int> a;

// Counting (non-stable)
a = case_data;
double t1 = time_ms([&](vector<int>& v){ counting_sort_nonstable(v); }, a);
cout << left << setw(20) << "Counting (non-stable)" 
     << ": " << setw(8) << t1 << "ms"
     << " sorted=" << setw(2) << is_sorted_asc(a) ;
    printArr(a);


// Counting (stable)
a = case_data;
double t2 = time_ms([&](vector<int>& v){ v = counting_sort_stable(v); }, a);
cout << left << setw(20) << "Counting (stable)" 
     << ": " << setw(8) << t2 << "ms"
     << " sorted=" << setw(2) << is_sorted_asc(a) ;
    printArr(a) ;

// LSD Radix (base10)
if (minv >= 0) {
    a = case_data;
    double t3 = time_ms(lsd_radix_sort, a);
    cout << left << setw(20) << "LSD Radix (base10)" 
         << ": " << setw(8) << t3 << "ms"
         << " sorted=" << setw(2) << is_sorted_asc(a) ;
         printArr(a) ;

} else {
    cout << left << setw(20) << "LSD Radix (base10)" 
         << ": not run (requires non-negative keys)\n";
}

// Bucket Sort
a = case_data;
double t4 = time_ms([&](vector<int>& v){ bucket_sort(v,32); }, a);
cout << left << setw(20) << "Bucket Sort" 
     << ": " << setw(8) << t4 << "ms"
     << " sorted=" << setw(2) << is_sorted_asc(a) ;
    printArr(a) ;


// Pigeonhole Sort
if ((maxv - minv) <= 2000000) { // avoid too big
    a = case_data;
    double t5 = time_ms(pigeonhole_sort, a);
    cout << left << setw(20) << "Pigeonhole Sort" 
         << ": " << setw(8) << t5 << "ms"
         << " sorted=" << setw(2) << is_sorted_asc(a) ;
         printArr(a); 
} else {
    cout << left << setw(20) << "Pigeonhole Sort" 
         << ": skipped (range too large)\n";
}

cout << "--------------------------------------\n";

}

int main() {

    int n = 1000; // adjust value for machine  if too slow
    int minv = 0, maxv = 1500; // keep reasonable range for counting/pigeonhole 
    cout << "=== Non-comparison sorting experiments ===\n";

    // 1) Random uniform
    auto a1 = gen_random_ints(n, minv, maxv);
    cout << "Case: Random Uniform\n";
    run_one_case(a1, minv, maxv);

    // 2) Few unique
    auto a2 = gen_few_unique(n, minv, maxv);
    cout << "Case: Few Unique Values\n";
    run_one_case(a2, minv, maxv);

    // 3) Already sorted
    auto a3 = gen_sorted_ints(n, minv, maxv);
    cout << "Case: Already Sorted\n";
    run_one_case(a3, minv, maxv);

    // 4) Reverse sorted
    auto a4 = gen_reverse_ints(n, minv, maxv);
    cout << "Case: Reverse Sorted\n";
    run_one_case(a4, minv, maxv);

    return 0;
}


