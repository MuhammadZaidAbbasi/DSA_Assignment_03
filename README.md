
# Non-Comparison Sorting Algorithms

This project implements and evaluates several non-comparison-based sorting algorithms:

- Counting Sort (Non-Stable & Stable)
- LSD Radix Sort (Base 10)
- Bucket Sort
- Pigeonhole Sort

---

## 1. Counting Sort (Non-Stable)

**Idea:** Count occurrences of each key and overwrite array in sorted order.  
**Data Structure:** `counts[]`  
**Stability:** ❌ Non-stable  
**Complexity:**  
- `O(n + k)` time  , `O(k)` space    
  - **n:** number of elements to sort  
  - **k:** range of key values (`max - min + 1`)     

**Assumption:** Keys small or map-able to small non-negative integers.

---

## 2. Counting Sort (Stable)

**Idea:** Count → prefix sums → place elements right-to-left into output array.  
**Data Structures:** `counts[]`, `output[]`  
**Stability:** ✅ Stable  
**Complexity:** 
- `O(n + k)` time, `O(k)` space      
  - **n:** input size  
  - **k:** key range   

**Assumption:** Small integer key range.

---

## 3. LSD Radix Sort (Base-10 Integers)

**Idea:** Sort digits from least → most significant using stable counting sort.    
**Stability:** ✅ Stable  
**Complexity:**  
- `O(d × (n + b))`  
  - **d:** number of digits (e.g., 3 digits → 0–999)  
  - **n:** input size  
  - **b:** base of numbering system (e.g., 10 for decimal)
 
**Assumption:** Fixed digit length or known upper bound.

---

## 4. Bucket Sort

**Idea:** Distribute values into buckets, sort each bucket individually, then merge.  
**Data Structures:** `vector<vector<int>>` (buckets)         
**Best Case:** Uniformly distributed values  
**Complexity:**  
- **Average:** `O(n)`  
  - **n:** number of values; distribution assumed uniform  
- **Worst:** `O(n²)`  
  - happens when all values fall into one bucket
   
**Assumption:** Values lie in a known range (typically `[0,1)`).

---

## 5. Pigeonhole Sort

**Idea:** Place elements directly into “holes” indexed by key.  
**Data Structures:**  ` Array of vectors ` ("holes")      
**Stability:** ✅ Stable (when using vectors/lists per hole)  
**Complexity:**  
- `O(n + R)`  
  - **n:** number of elements  
  - **R:** total key range (`max - min + 1`)

**Assumption:**  Small integer range `e.g. R<200000`.

---


## 6. Experimental Setup

### Test Cases
- Uniform random values  
- Few unique values  
- Already sorted  
- Reverse sorted  
 
### Measurements
- Wall-clock time (ms)  
- Correctness via `is_sorted`  
- Stability checks using `(value, originalIndex)`  
- Memory observations (counting/pigeonhole need `O(k)`)

---

## 7. Summary  

- **Counting Sorts & Pigeonhole:** fastest when key range is small  
- **Stable vs Non-Stable Counting:** similar speed; stable uses extra array  
- **LSD Radix:** excellent for fixed-digit integers  
- **Bucket Sort:** strong on uniform data, worst-case slows heavily  
- **Pigeonhole:** impractical for large key ranges due to memory cost


