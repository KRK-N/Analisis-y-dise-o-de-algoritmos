#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <cmath>

using namespace std;
using namespace std::chrono;

// ==========================================
// 1. BUBBLE SORT
// ==========================================
void bubbleSort(vector<double>& arr) {
    size_t n = arr.size();
    for (size_t i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// ==========================================
// 2. MERGE SORT
// ==========================================
void merge(vector<double>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<double> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<double>& arr, int l, int r) {
    if (l >= r) return;
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
}

// ==========================================
// 3. TREE SORT
// ==========================================
struct Node {
    double key;
    Node *left, *right;
    Node(double item) : key(item), left(nullptr), right(nullptr) {}
};

Node* insertNode(Node* node, double key) {
    if (node == nullptr) return new Node(key);
    if (key < node->key) node->left = insertNode(node->left, key);
    else node->right = insertNode(node->right, key);
    return node;
}

void storeInorder(Node* root, vector<double>& arr, int& index) {
    if (root != nullptr) {
        storeInorder(root->left, arr, index);
        arr[index++] = root->key;
        storeInorder(root->right, arr, index);
    }
}

void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

void treeSort(vector<double>& arr) {
    if (arr.empty()) return;
    Node* root = nullptr;
    root = insertNode(root, arr[0]);
    for (size_t i = 1; i < arr.size(); i++) {
        insertNode(root, arr[i]);
    }
    int index = 0;
    storeInorder(root, arr, index);
    freeTree(root);
}

// ==========================================
// 4. HEAP SORT
// ==========================================
void heapify(vector<double>& arr, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest]) largest = l;
    if (r < n && arr[r] > arr[largest]) largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<double>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ==========================================
// 5. COUNTING SORT (Adaptado para doubles por escalamiento)
// ==========================================
void countingSortReal(vector<double>& arr, double scale = 100.0) {
    if (arr.empty()) return;
    double minVal = *min_element(arr.begin(), arr.end());
    double maxVal = *max_element(arr.begin(), arr.end());

    long long minInt = static_cast<long long>(floor(minVal * scale));
    long long maxInt = static_cast<long long>(ceil(maxVal * scale));
    long long range = maxInt - minInt + 1;

    vector<int> count(range, 0);
    for (double val : arr) {
        long long scaled = static_cast<long long>(round(val * scale));
        count[scaled - minInt]++;
    }

    int idx = 0;
    for (long long i = 0; i < range; ++i) {
        while (count[i] > 0) {
            arr[idx++] = static_cast<double>(i + minInt) / scale;
            count[i]--;
        }
    }
}

// ==========================================
// MAIN & BENCHMARK
// ==========================================
vector<double> generateRandomArray(size_t size) {
    vector<double> arr(size);
    mt19937_64 rng(42); // Semilla fija para reproducibilidad
    uniform_real_distribution<double> dist(0.0, 1000.0);
    for (size_t i = 0; i < size; ++i) {
        arr[i] = dist(rng);
    }
    return arr;
}

int main() {
    vector<size_t> sizes = {100000, 1000000, 10000000}; // Ajustar según capacidad de hardware
    cout << "Pruebas c++" << endl;

    for (size_t N : sizes) {
        cout << "\n=== PRUEBAS CON N = " << N << " ===" << endl;
        
        vector<double> data = generateRandomArray(N);
        
        // Ejemplo de ejecución para Heap Sort
        vector<double> testHeap = data;
        auto start = high_resolution_clock::now();
        heapSort(testHeap);
        auto stop = high_resolution_clock::now();
        duration<double> duration = stop - start;
        cout << "Heap Sort: " << duration.count() << " s" << endl;

        // Ejemplo de ejecución para Merge Sort
        vector<double> testMerge = data;
        start = high_resolution_clock::now();
        mergeSort(testMerge, 0, N - 1);
        stop = high_resolution_clock::now();
        duration = stop - start;
        cout << "Merge Sort: " << duration.count() << " s" << endl;
    }

    return 0;
}