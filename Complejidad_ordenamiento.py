import sys
import time
import random
import math

# Aumentar límite de recursión para algoritmos recursivos
sys.setrecursionlimit(2000000)

# ==========================================
# 1. BUBBLE SORT
# ==========================================
def bubble_sort(arr):
    n = len(arr)
    for i in range(n - 1):
        swapped = False
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                swapped = True
        if not swapped:
            break

# ==========================================
# 2. MERGE SORT
# ==========================================
def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        L = arr[:mid]
        R = arr[mid:]

        merge_sort(L)
        merge_sort(R)

        i = j = k = 0
        while i < len(L) and j < len(R):
            if L[i] <= R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1

        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1

        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1

# ==========================================
# 3. TREE SORT
# ==========================================
class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None

def insert_node(root, key):
    if root is None:
        return Node(key)
    if key < root.key:
        root.left = insert_node(root.left, key)
    else:
        root.right = insert_node(root.right, key)
    return root

def store_inorder(root, res):
    if root:
        store_inorder(root.left, res)
        res.append(root.key)
        store_inorder(root.right, res)

def tree_sort(arr):
    if not arr:
        return
    root = Node(arr[0])
    for val in arr[1:]:
        insert_node(root, val)
    res = []
    store_inorder(root, res)
    for i in range(len(arr)):
        arr[i] = res[i]

# ==========================================
# 4. HEAP SORT
# ==========================================
def heapify(arr, n, i):
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2

    if l < n and arr[l] > arr[largest]:
        largest = l
    if r < n and arr[r] > arr[largest]:
        largest = r

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)

def heap_sort(arr):
    n = len(arr)
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]
        heapify(arr, i, 0)

# ==========================================
# 5. COUNTING SORT (Adaptado para flotantes)
# ==========================================
def counting_sort_real(arr, scale=100.0):
    if not arr:
        return
    min_val = min(arr)
    max_val = max(arr)

    min_int = math.floor(min_val * scale)
    max_int = math.ceil(max_val * scale)
    range_val = max_int - min_int + 1

    count = [0] * range_val
    for val in arr:
        scaled = round(val * scale)
        count[scaled - min_int] += 1

    idx = 0
    for i in range(range_val):
        while count[i] > 0:
            arr[idx] = (i + min_int) / scale
            idx += 1
            count[i] -= 1

# ==========================================
# PRUEBAS DE DESEMPEÑO
# ==========================================
if __name__ == "__main__":
    sizes = [100000, 1000000, 10000000] # N mayores ajustables según memoria RAM disponible

    print("Pruebas en Python")
    
    for N in sizes:
        print(f"\n--- Probando con N = {N} ---")
        data = [random.uniform(0.0, 1000.0) for _ in range(N)]

        # Prueba Heap Sort
        arr_heap = list(data)
        t_start = time.time()
        heap_sort(arr_heap)
        t_end = time.time()
        print(f"Heap Sort: {t_end - t_start:.4f} segundos")

        # Prueba Counting Sort
        arr_counting = list(data)
        t_start = time.time()
        counting_sort_real(arr_counting)
        t_end = time.time()
        print(f"Counting Sort: {t_end - t_start:.4f} segundos")