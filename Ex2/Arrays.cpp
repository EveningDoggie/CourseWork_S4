#include "Arrays.h"
#include <iostream>
using namespace std;

size_t Arrays::GetSize(int* A)
{
	return  _msize(A) / sizeof(int);
}

void Arrays::Load(int **A, std::string path)
{
	if (A==nullptr || *A==nullptr)
	{
		throw logic_error("Null ptr exception");
	}

	size_t size = 0;
	string line;
	ifstream fin(path);
	if (!fin.is_open()) throw logic_error("File is not open");
	
	while (getline(fin, line))
	{
		++size;
	}
	fin.close();

	
	try
	{
		delete* A;
		*A = new int[size];
	}
	catch (exception e)
	{
		throw e;
	}

	fin.open(path);
	if (!fin.is_open()) throw logic_error("File is not open");
	int count = 0;
	for (int i = 0; i < size; ++i)
	{
		try
		{
			getline(fin, line);
			(*A)[i] = stoi(line);
		}
		catch (exception e)
		{
			throw e;
		}
	}
	fin.close();
}

void Arrays::Save(int* A, std::string path)
{
	if (A == nullptr)
	{
		throw logic_error("Null ptr exception");
	}

	std::ofstream out;
	out.open(path);
	if (!out.is_open())
	{
		throw logic_error("Can't open file");
	}

	for (int i = 0; i < GetSize(A); i++)
	{
		out << A[i] << std::endl;
	}

	out.close();
}

 //3) Rand A, count, lb, rb; -заполнить массив A случайными элементами из отрезка  [𝑙𝑏; 𝑙𝑟] в количестве count штук.
 void Arrays::Rand(int **A, size_t count, size_t firstvalue, size_t endvalue)
 {
	 if (A == nullptr || *A == nullptr)
	 {
		 throw logic_error("Null ptr exception");
	 }

	 try
	 {
		 delete* A;
		 *A = new int[count];
	 }
	 catch (exception e)
	 {
		 throw e;
	 }

	 for (int i = 0; i < count; i++)
	 {
		 (*A)[i] = rand() % (endvalue - firstvalue + 1) + firstvalue;
	 }
 }

 //4) Concat A, b; -объединить два массива A и B, с результат сохранить в массив A.
 void Arrays::Concat(int **A, int *B)
 {
	 if (A == nullptr || *A == nullptr || B == nullptr)
	 {
		 throw logic_error("Null ptr exception");
	 }
	 

	 size_t size_a = GetSize(*A);
	 size_t size_b = GetSize(B);
	 int* arr;
	 try
	 {
		 arr = new int[size_a+size_b];
	 }
	 catch (exception e)
	 {
		 throw e;
	 }

	 for (int i = 0; i < size_a; i++)
	 {
		 arr[i] = (*A)[i];
	 }

	 for (int j = 0; j < size_b; j++)
	 {
		 arr[size_a+j] = B[j];
	 }

	 delete *A;
	 *A = arr;
 
 }

 //5) Free(a); -очистить массив А.
 void Arrays::Free(int **A)
 {
	 if (A == nullptr || *A == nullptr)
	 {
		 throw logic_error("Null ptr exception");
	 }

	 try
	 {
		 delete* A;
		 *A = new int[0];
	 }
	 catch (exception e)
	 {
		 throw e;
	 }
 
 }

 //Remove a, 2, 7; -удалить из массива a 7 элементов, начиная с элемента с индексом2;
 void Arrays::Remove(int **A, size_t start, size_t count)
 {
	 if (A == nullptr || *A == nullptr)
	 {
		 throw logic_error("Null ptr exception");
	 }

	 int* arr;
	 try
	 {
		 arr = new int[GetSize(*A) - count];
	 }
	 catch (exception e)
	 {
		 throw e;
	 }

	 for (int j = 0; j < start; j++)
	 {
		 arr[j] = (*A)[j];
	 }


	 for (int i = start+count; i < GetSize(*A); i++)
	 {
		 arr[i-count] = (*A)[i];
	 }

	 delete* A;
	 *A = arr;
 }

 //Copy A, 4, 10, b; -скопировать из массива b элементы с 4 по 10 и сохранить их в a;
 void Arrays::Copy(int **A, int *B, size_t start, size_t end)
 {
	 if (A == nullptr || *A == nullptr || B==nullptr)
	 {
		 throw logic_error("Null ptr exception");
	 }

	 int* arr;
	 try
	 {
		 arr = new int[end-start+1];
	 }
	 catch (exception e)
	 {
		 throw e;
	 }

	 int j = -1;
	 for (int i = start; i <= end; ++i)
	 {
		 arr[++j] = B[i];
	 }

	 delete* A;
	 *A = arr;
 }

 //Sort A + (-); -сортировать элементы массива A по возрастанию(убыванию);
 void Arrays::Sort(int **A, bool type)
 {
	 if (A == nullptr || *A == nullptr)
	 {
		 throw logic_error("Null ptr exception");
	 }

	 int i, j, index, n = GetSize(*A);

	 // Проходим по всем элементам массива
	 for (i = 0; i < n - 1; i++) {
		 // Находим индекс минимального элемента в оставшейся части массива
		 index = i;
		 for (j = i + 1; j < n; j++) {
			 if (
				 (type && (*A)[j] < (*A)[index]) ||
				 (!type && (*A)[j] > (*A)[index])
				 ) {
				 index = j;
			 }
		 }

		 // Обмениваем минимальный элемент с текущим элементом
		 int temp = (*A)[i];
		 (*A)[i] = (*A)[index];
		 (*A)[index] = temp;
	 }
 }


 //Permute A; -переставить элементы массива в случайном порядке.
 void Arrays::Permute(int **A)
 {
	 if (A == nullptr || *A == nullptr)
	 {
		 throw logic_error("Null ptr exception");
	 }

	 int* arr;
	 try
	 {
		 arr = new int[GetSize(*A)];
	 }
	 catch (exception e)
	 {
		 throw e;
	 }

	 int k = -1;
	 while (GetSize(*A)!=0)
	 {
		 int index = rand() % GetSize(*A);
		 arr[++k] = (*A)[index];
		 Remove(A, index, 1);
	 }
	 
	 delete *A;
	 *A = arr;
 }

 //Intersect A, B; -найти пересечение массивов A и B, результат сохранить в массив A;
 void Arrays::Intersect(int **A, int *B)
 {
	 if (A == nullptr || *A == nullptr || B==nullptr)
	 {
		 throw logic_error("Null ptr exception");
	 }

	 int* arr;
	 int sizea = GetSize(*A);
	 int sizeb = GetSize(B);

	 map <int, size_t> values;
	 for (int j = 0; j < sizea; ++j)
	 {
		values[(*A)[j]] = 1;
	 }


	 int count = 0;
	 for (int j = 0; j < sizeb; ++j)
	 {
		 if (values.count(B[j]) != 0)
		 {
			 values[B[j]] += 1;
			 if (values[B[j]] == 2) ++count;
		 }
	 }

	 try
	 {
		 arr = new int[count];
	 }
	 catch (exception e)
	 {
		 throw e;
	 }

	 count = -1;
	 for (auto v : values)
	 {
		 if (v.second>=2)
		 {
			 arr[++count] = v.first;
		 }
	 }

	 delete* A;
	 *A = arr;


 }

 //Xor A, B; найти симметрическую разность массивов A и B, результат сохранить в массив A;
 void Arrays::Xor(int **A, int *B)
 {
	 if (A == nullptr || *A == nullptr || B==nullptr)
	 {
		 throw logic_error("Null ptr exception");
	 }

	 int* arr;
	 int sizea = GetSize(*A);
	 int sizeb = GetSize(B);

	 int count = 0;
	 map <int, size_t> values;
	 for (int j = 0; j < sizea; ++j)
	 {
		 values[(*A)[j]] = 1;
	 }

	 for (int j = 0; j < sizeb; ++j)
	 {
		 if (values.count(B[j]) != 0)
		 {
			 if (values[B[j]] != 0)
			 {
				 values[B[j]] = 2;
				 --count;
			 }
		 }
		 else
		 {
			 values[B[j]] = 0;
		 }
	 }

	 count += values.size();
	 try
	 {
		 arr = new int[count];
	 }
	 catch (exception e)
	 {
		 throw e;
	 }

	 count = -1;
	 for (auto v : values)
	 {
		 if (v.second<2)
		 {
			 arr[++count] = v.first;
		 }
	 }

	 delete* A;
	 *A = arr;


 }

//Stat a; -вывести статистическую информацию о массиве а : размер массива,
//максимальный и минимальный элемент(и их индексы), наиболее часто
//встречающийся элемент, среднее значение элементов, максимальное отклонение
//элементов от среднего значения.
 void Arrays::Stat(int *A)
 {
	 if (A == nullptr)
	 {
		 throw logic_error("Null ptr exception");
	 }
	 size_t size = GetSize(A);
	 if (size == 0)
	 {
		 cout << "Size: 0\n";
		 return;
	 }

	 size_t min_id=0, max_id=0;
	 double average=0;
	 std::map<int, size_t> values;
	 for (int i = 0; i < size; ++i)
	 {
		 if (A[i] > A[max_id])
			 max_id = i;
		 if (A[i] < A[min_id])
			 min_id = i;

		 average += A[i];
		 
		 if (values.count(A[i]) == 0)
			 values[A[i]] = 1;
		 else
			 values[A[i]] += 1;
	 }

	 size_t often_count = 0;
	 size_t often = 0;
	 for (auto v : values)
	 {
		 if (v.second > often_count)
		 {
			 often_count = v.second;
			 often = v.first;
		 }
	 }

	 average /= size;
	 double deviation = std::abs(A[max_id] - average);
	 double dev1 = std::abs(A[min_id] - average);
	 if (dev1 > deviation) deviation = dev1;

	 cout
		 << "Size: " << size
		 << "\nMax: " << A[max_id] << " (id " << max_id << ")"
		 << "\nMin: " << A[min_id] << " (id " << min_id << ")"
		 << "\nOften: " << often
		 << "\nAverage: " << average
		 << "\nMax deviation: " << deviation
		 << "\n";
 }

 void Arrays::Print(int *A)
 {
	 if (A == nullptr)
	 {
		 throw logic_error("Null ptr exception");
	 }


	 for (int i = 0; i < GetSize(A); ++i)
	 {
		 cout << A[i] << " ";
	 }

	 cout << "\n";

 }

 void Arrays::Print(int *A, size_t start, size_t end)
 {
	 if (A == nullptr)
	 {
		 throw logic_error("Null ptr exception");
	 }

	 for (int i = start; i < end && i<GetSize(A); ++i)
	 {
		 cout << A[i] << " ";
	 }

	 cout << "\n";
 }