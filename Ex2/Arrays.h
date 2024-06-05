#pragma once
#include <string>
#include <fstream>
#include <map>
#include <iostream>

class Arrays
{

public:
	static void Load(int **A, std::string path);
	static void Save(int* A, std::string path);
	static void Rand(int **A, size_t count, size_t firstvalue, size_t endvalue);
	static void Concat(int** A, int* B);
	static void Free(int** A);
	static void Remove(int** A, size_t start, size_t count);
	static void Copy(int **A, int *B, size_t start, size_t end);
	static void Sort(int **A, bool type);
	static void Permute(int **A);
	static void Intersect(int **A, int *B);
	static void Xor(int **A, int *B);
	static void Stat(int *A);
	static void Print(int* A);
	static void Print(int *A, size_t start, size_t end);
	static size_t GetSize(int* A);
};

