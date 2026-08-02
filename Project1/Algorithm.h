#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <vector>
//In here I used Function overloading.
//Function Overloading provides you to create more than one function
//Our compiler knows that which function is used and approved by the function.
namespace Algorithm {
	///////////////////////////////////////////////
	///////////////////////////////////////////////
	
	template <typename T>
	bool IsSorted(T Array[], size_t Size) {
		if (Size <= 1)return true;
		for (size_t i = 0; Size > i; i++) {
			if (Array[i] > Array[i + 1]) return false;
		}
		return true;
	}

	template <typename T>
	bool IsSorted(const std::vector<T>& vec, size_t Size) {
		if (Size <= 1)return true;
		for (size_t i = 0; Size > i; i++) {
			if (vec[i] > vec[i + 1]) { return false; }
		}
		return true;
	}


	///////////////////////////////////////////////
	///////////////////////////////////////////////





	///////////////////////////////////////////////
	// Search Algorithms for arrays
	///////////////////////////////////////////////

	template <typename T>
	int LinearSearch(T Array[], int Size, T Target) {
		for (int i = 0; i < Size; i++) {
			if (Array[i] == Target) {
				return i; // Bulursa indeksini dön
			}
		}
		return -1; // Bulamazsa -1 dön
	}

	template <typename T>
	int LinearSearch(const std::vector<T>& vec, T Target) {
		for (size_t i = 0; vec.size() > i; i++) {
			if (vec[i] == Target) { return i; }
		}
		return -1;
		//in this function I want to give you a hint:
		//First of all I used Size_t in this function cuz I dont know how many Vectors are there
		//So I initialised it by using the largest data type So What's the problem?
		//The probem is returns function even I create the largest data type I return just int?
		//So Why did u use that?
		//the main goal of using int data returned type is '-1' case. if the target one wasnt in the vector
		//it needs to return -1, but the size_t cannot return under the zero.
		//To sum up,I used int data type to get the index value for in case of not being the vector,
		//if you wanna get much more than int data type , you can manually change  the data type.
	}

	template <typename T>
	int BinarySearch(T Array[], int Size, T Target) {
		int Max = Size - 1;
		int Min = 0;

		while (Min <= Max) {
			int Mid = Min + (Max - Min) / 2;

			if (Array[Mid] == Target) {
				return Mid; // Bulursa indeksini dön
			}
			else if (Array[Mid] < Target) {
				Min = Mid + 1;
			}
			else {
				Max = Mid - 1;
			}
		}
		return -1; // Bulamazsa -1 dön
	}

	template <typename T>
	int BinarySearch(const std::vector<T>& vec, T Target) {
		int Max = static_cast<int>(vec.size()) - 1;
		int Min = 0;

		while (Min <= Max) {
			int Mid = Min + (Max - Min) / 2;
			if (vec[Mid] == Target) { return Mid; }
			else if (vec[Mid] < Target) { Min = Mid + 1; }
			else { Max = Mid - 1; }
		}
		return -1;
	}
	///////////////////////////////////////////////
	// Sorting Algorithms for arrays
	///////////////////////////////////////////////

	template <typename T>
	void BubbleSort(T Array[], int Size) {
		for (int i = 0; i < Size - 1; i++) {
			for (int j = 0; j < Size - 1 - i; j++) {
				if (Array[j] > Array[j + 1]) {
					T Temp = Array[j];
					Array[j] = Array[j + 1];
					Array[j + 1] = Temp;
				}
			}
		}
	}
	template <typename T>
	void BubbleSort(std::vector<T>& vec) {
		size_t Size = vec.size();
		if (Size == 0) return;

		for (size_t i = 0; i < Size - 1; i++) {
			for (size_t j = 0; j < Size - 1 - i; j++) {
				if (vec[j] > vec[j + 1]) {
					T Temp = vec[j];
					vec[j] = vec[j + 1];
					vec[j + 1] = Temp;
				}
			}
		}
	}
	template <typename T>
	void SelectionSort(T Array[], int Size) {
		for (int i = 0; i < Size - 1; i++) {
			int MinIndex = i;
			for (int j = i + 1; j < Size; j++) {
				if (Array[j] < Array[MinIndex]) {
					MinIndex = j;
				}
			}
			if (MinIndex != i) {
				T temp = Array[MinIndex];
				Array[MinIndex] = Array[i];
				Array[i] = temp;
			}
		}
	}
	template <typename T>
	void SelectionSort(std::vector<T>& vec) {
		size_t Size = vec.size();
		if (Size == 0) return;

		for (size_t i = 0; i < Size - 1; i++) {
			size_t MinIndex = i;
			for (size_t j = i + 1; j < Size; j++) {
				if (vec[j] < vec[MinIndex]) { MinIndex = j; }
			}
			if (MinIndex != i) {
				T temp = vec[MinIndex];
				vec[MinIndex] = vec[i];
				vec[i] = temp;
			}
		}
	}
	template <typename T>
	void InsertionSort(T Array[], int Size) {
		for (int i = 1; i < Size; i++) {
			T key = Array[i];
			int j = i - 1;

			while (j >= 0 && Array[j] > key) {
				Array[j + 1] = Array[j];
				j--;
			}
			Array[j + 1] = key;
		}
	}
	template <typename T>
	void InsertionSort(std::vector<T>& vec) {
		size_t Size = vec.size();
		for (size_t i = 1; i < Size; i++) {
			T key = vec[i];
			int j = static_cast<int>(i) - 1;

			while (j >= 0 && vec[j] > key) {
				vec[j + 1] = vec[j];
				j--;
			}
			vec[j + 1] = key;
		}
	}
}

#endif