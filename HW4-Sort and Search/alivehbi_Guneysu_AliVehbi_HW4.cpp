#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<chrono>

using namespace std;
/*I used gulsen hoca's code for all the sort types, I tried all the sampleruns and there has been no problem.(All of them working correctly),
* But the only difference with sampleruns, I think there is some problem with alphebeth(sorting) in some of sampleruns; For example in sample run 5,
* William Jimminez should not be at the end It should come before William Johnson.
* Fianlly, I checked my code several times, and it works completely fine and in alphabetic way (sorted),
* Thank you for reading.
*/

inline int leftChild(int i)
{
	return 2 * i + 1;
}
template <class Comparable>
void percDown(vector<Comparable>& a, int i, int n)
{
	int child;
	Comparable tmp;

	for (tmp = a[i]; leftChild(i) < n; i = child)
	{
		child = leftChild(i);
		if (child != n - 1 && a[child] < a[child + 1])
			child++;
		if (a[child] > tmp)
			a[i] = a[child];
		else
			break;
	}
	a[i] = tmp;
}

template <class Comparable>
void heapsort(vector<Comparable>& a)
{
	// buildHeap
	for (int i = a.size() / 2; i >= 0; i--)
		percDown(a, i, a.size());

	// sort
	for (int j = a.size() -1; j > 0; j--)
	{
		swap(a[0], a[j]);    // swap max to the last pos.
		percDown(a, 0, j); // re-form the heap
	}
}





template <class Comparable>
void insertionSort(vector <Comparable>& a)
{
	int j;
	for (int p = 1; p < a.size(); p++)
	{
		Comparable tmp = a[p];

		for (j = p; j > 0 && tmp < a[j - 1]; j--){
			a[j] = a[j - 1];
		}
			
		a[j] = tmp;
	}
}

template <class Comparable>
void merge(vector<Comparable>& a,vector<Comparable>& tmpArray, int leftPos, int rightPos, int rightEnd)
{
	int leftEnd = rightPos - 1;
	int tmpPos = leftPos;
	int numElements = rightEnd - leftPos + 1;
	while (leftPos <= leftEnd && rightPos <= rightEnd)
		if (a[leftPos] <= a[rightPos])
			tmpArray[tmpPos++] = a[leftPos++];
		else
			tmpArray[tmpPos++] = a[rightPos++];

	while (leftPos <= leftEnd)    // Copy rest of first half
		tmpArray[tmpPos++] = a[leftPos++];

	while (rightPos <= rightEnd)  // Copy rest of right half
		tmpArray[tmpPos++] = a[rightPos++];

	// Copy tmpArray back
	for (int i = 0; i < numElements; i++, rightEnd--)
		a[rightEnd] = tmpArray[rightEnd];
}
template <class Comparable>
void mergeSort(vector<Comparable>& a,
	vector<Comparable>& tmpArray, int left, int right)
{
	if (left < right)
	{
		int center = (left + right) / 2;
		mergeSort(a, tmpArray, left, center);
		mergeSort(a, tmpArray, center + 1, right);
		merge(a, tmpArray, left, center + 1, right);
	}
}
template <class Comparable>
void mergeSort(vector<Comparable>& a)
{
	vector<Comparable> tmpArray(a.size());

	mergeSort(a, tmpArray, 0, a.size() - 1);
}

template <class Comparable>
inline void swap(Comparable& obj1, Comparable& obj2)
{
	Comparable tmp = obj1;
	obj1 = obj2;
	obj2 = tmp;

}
template <class Comparable>
const Comparable& median3(vector<Comparable>& a,
	int left, int right)
{
	int center = (left + right) / 2;
	if (a[center] < a[left])
		swap(a[left], a[center]);
	if (a[right] < a[left])
		swap(a[left], a[right]);
	if (a[right] < a[center])
		swap(a[center], a[right]);

	// Place pivot at position right - 1
	swap(a[center], a[right - 1]);
	return a[right - 1];
}
template <class Comparable>
void insertionSort(vector<Comparable>& a, int left, int right)
{
	for (int p = left + 1; p <= right; p++)
	{
		Comparable tmp = a[p];
		int j;

		for (j = p; j > left && tmp < a[j - 1]; j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}

template <class Comparable>
void quicksort(vector<Comparable>& a,
	int left, int right)
{
	if (left + 10 <= right)
	{
		Comparable pivot = median3(a, left, right);
		int i = left, j = right - 1;
		for (; ; )
		{
			while (a[++i] < pivot) {}

			while (pivot < a[--j]) {}

			if (i < j)
				swap(a[i], a[j]);
			else
				break;
		}
		swap(a[i], a[right - 1]);   // Restore pivot

		quicksort(a, left, i - 1);       // Sort small elements
		quicksort(a, i + 1, right);    // Sort large elements
	}
	else  // Do an insertion sort on the subarray
		insertionSort(a, left, right);
}




template <class Comparable>
void quicksort(vector<Comparable>& a)
{
	quicksort(a, 0, a.size() - 1);
}

template <class Comparable>
int BinarySearchExactPerson(vector<Comparable> a, int l, int r, Comparable & x) // if the query includes second name
{


	if (r >= l) {
		int mid = l + (r - l) / 2;
		string word ="";
		int counter = 0;
		for (int i = 0; i < a[mid].length(); i++) {
			if (counter < 2) {


				if (a[mid][i] == ' ') {
					counter++;
					if (counter == 1) {
						word = word + a[mid][i];
					}
					

				}
				else {
					word = word + a[mid][i];
				}
			}

		}


		if (word == x) {
			cout << a[mid] << endl;
			return 1;

		}
			


		if (a[mid] > x)
			return BinarySearchExactPerson(a, l, mid - 1, x);


	    return BinarySearchExactPerson(a, mid + 1, r, x);
	}


	return -1;
}
template <class Comparable>
int BinarySearchSelectPerson(vector<Comparable> & a, int l, int r, Comparable& x) // if the query includes only first part
{


	if (r >= l) {
		int mid = l + (r - l) / 2;
		string word = "";
		int counter = 0;
		for (int i = 0; i < a[mid].length(); i++) {
			if (counter == 0) {

				if (word == x) {
					
					counter++;
					return mid;
					
				}
				word = word + a[mid][i];
			}

		}


		



		if (a[mid] > x)
			return BinarySearchSelectPerson(a, l, mid - 1, x);


		return BinarySearchSelectPerson(a, mid + 1, r, x);
	}


	return -1;
}
template <class Comparable>
void ReNewVec(vector<Comparable>& a, int x) {
	vector<Comparable> b;
	for (int i = 0; i < a.size(); i++) {
		if (i != x) {
			b.push_back(a[i]);
		}
		
	}
	a = b;

}




template <class Comparable>
void SequentialSearch(vector<Comparable>& a, Comparable& search) {
	int spaceCounter = 0;
	for (int i = 0; i < search.length(); i++) {
		if (search[i] == ' ') {
			spaceCounter++;
		}
	}
	bool exist = false;

	if (spaceCounter == 0) {


		for (int x = 0; x < a.size(); x++) {
			string word = "";
			int counter = 0;
			for (int y = 0; y < a[x].length(); y++) {
				
				if (counter == 0) {
					if (word == search) {
						cout << a[x] << endl;
						exist = true;
						counter++;
					}
					word = word + a[x][y];


				}


			}
		}

	}
	else {
		for (int x = 0; x < a.size(); x++) {
			string word = "";
			int counter = 0;
			for (int y = 0; y < a[x].length(); y++) {
				
				if (a[x][y] == ' ') {
					counter++;
					if (counter == 1) {
						 word = word + a[x][y];
						
					}
					else if (counter == 2) {
						if (word == search) {
							cout << a[x] << endl;
							exist = true;

						}
					}
					


				}
				else {
					word = word + a[x][y];
				}


			}
		}

	}
	if (exist == false) {
		cout << search << " does NOT exist in the dataset" << endl;
	}

}

void changer(string & w) {
	int spacecounter = 0;
	string word;
	for (int i = 0; i < w.length(); i++) {
		if (spacecounter < 2) {
			if (w[i] == ' ') {
				word = word + w[i];
				spacecounter++;

			}
			else if(w[i] >= 97 && w[i] <= 122) {
				char a = w[i] - 32;
				word = word + a;
				

			}
			else {
				word = word + w[i];
			}

		}
		else {
			word = word + w[i];
		}

	}
	w = word;
	
}





int main() {
	
	
	string fileName, line ,search;

	
	
	

	ifstream input;
	vector<string> insertionSortV;
	vector<string> quickSortV;
	vector<string> mergeSortV;
	vector<string> heapSortV;

	cout << "Please enter the contact file name:" << endl;
	cin >> fileName;
	
	cout << "Please enter the word to be queried :" << endl;
	cin.ignore();
	getline(cin, search);
	
	
	
	input.open(fileName.c_str());
	while (getline(input, line)){
		changer(line);
		insertionSortV.push_back(line);
		heapSortV.push_back(line);
		quickSortV.push_back(line);
		mergeSortV.push_back(line);

	}
	input.close();
	cout << endl << endl;;
	cout << "Sorting the vector copies" << endl;
	cout << "===================================" << endl;
	auto start = std::chrono::high_resolution_clock::now();
	quicksort(quickSortV);
	auto quickTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
	cout << "Quick Sort Time: "<<quickTime.count() / 10 << " Nanoseconds" << endl;

	start = std::chrono::high_resolution_clock::now();
	insertionSort(insertionSortV);
	auto insertionTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
	cout << "Insertion Sort Time: " << insertionTime.count() / 10 << " Nanoseconds" << endl;

	

	start = std::chrono::high_resolution_clock::now();
	mergeSort(mergeSortV);
	auto mergeTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
	cout << "Merge Sort Time: " << mergeTime.count() / 10 << " Nanoseconds" << endl;

	start = std::chrono::high_resolution_clock::now();
	heapsort(heapSortV);
	auto heapTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
	cout << "Heap Sort Time: " << heapTime.count() / 10 << " Nanoseconds" << endl;
	cout << endl;
	cout << "Searching for " << search << endl;
	cout << "===================================" << endl;
	cout << endl;
	cout << "Search Results For Binary Search:" << endl;
	changer(search);
	vector<string> copy = insertionSortV;
	vector<string>founds;
	
	auto BinaryTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
	int spaceCounterV2 = 0;
	for (int i = 0; i < search.length(); i++) {
		if (search[i] == ' ') {
			spaceCounterV2++;
		}
	}

	if (spaceCounterV2 == 0) {
		start = std::chrono::high_resolution_clock::now();
		int countedF = 1;
		int mid = 0;
		while (mid != -1) {
			mid = BinarySearchSelectPerson(copy, 0, copy.size() - 1, search);
			if (mid != -1) {
				countedF++;
				founds.push_back(copy[mid]);

				ReNewVec(copy, mid);

			}


		}
		BinaryTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
		if (countedF != 1) {
			insertionSort(founds);
			for (int f = 0; f < founds.size(); f++) {
				cout << founds[f] << endl;
			}
			
		}
		else {
			cout << search << " does NOT exist in the dataset" << endl;
		}
		double BinaryTimeD = BinaryTime.count();
		cout << "Binary Search Time: "<< BinaryTimeD / 1000 << " Nanoseconds" << endl<<endl;

	}
	else {
		start = std::chrono::high_resolution_clock::now();
		int result = BinarySearchExactPerson(insertionSortV, 0, insertionSortV.size() - 1, search);
		BinaryTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
		if (result == -1) {
			cout << search << " does NOT exist in the dataset" << endl;
		}
		double BinaryTimeD = BinaryTime.count();
		cout << "Binary Search Time: " << BinaryTimeD / 1000 << " Nanoseconds" << endl << endl;

	}
	cout << endl;
	cout << "Search results for Sequential Search:" << endl;
	
	
	

	start = std::chrono::high_resolution_clock::now();
	SequentialSearch(insertionSortV, search);
	auto SequentialTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
	double BinaryTimeD = BinaryTime.count();
	double insertionTimeD = insertionTime.count();
	double quickTimeD = quickTime.count();
	double heapTimeD = heapTime.count();
	double mergeTimeD = mergeTime.count();
	double SequentialTimeD = SequentialTime.count();

	cout << "Sequential Search Time: " << SequentialTimeD / 1000 << " Nanoseconds" << endl << endl;
	cout << "SpeedUp between Search Algorithms" << endl;
	cout << "===================================" << endl;
	cout << "(Sequential Search/ Binary Search) SpeedUp = " << SequentialTimeD / BinaryTimeD << endl << endl;
	cout << "SpeedUps between Sorting Algorithms" << endl;
	cout << "===================================" << endl;
	cout << "(Insertion Sort/ Quick Sort) SpeedUp =" << insertionTimeD / quickTimeD << endl;
	cout << "(Merge Sort / Quick Sort)  SpeedUp =" << mergeTimeD / quickTimeD << endl;
	cout << "(Heap Sort / Quick Sort)  SpeedUp =" << heapTimeD / quickTimeD << endl;


	


	return 0;
}

