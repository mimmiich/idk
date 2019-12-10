#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
const int N = 30;
const char Filename[] = "Spisyk.dat";
struct uchastnici {
	int num, pointsA, pointsB, pointsAB = 0;
	char ime[30], uchz[30];
};
fstream fp;

int menu() {
	int ch;
	cout << "\n Menu" << endl;
	cout << "1. Wywejdane na uchastnik" << endl;
	cout << "2. Spisyk s uchastnici" << endl;
	cout << "3. Max tochki" << endl;
	cout << "4. Tyrsene na uchastnik po ime" << endl;
	cout << "5. Zapazi spisyk" << endl;
	cout << "6. Izhod" << endl;
	do {
		cout << "Twoqt izbor e: ";
		cin >> ch;
	} while (ch < 1 || ch>5);
	return(ch);
}


uchastnici input() {
	uchastnici a = { 0 };
	cout << "\n Nomer na uchastnika: ";
	cin >> a.num; cin.ignore();
	cout << "Ime: ";
	cin.getline(a.ime, 30);
	cout << "Uchebno zawedenie: ";
	cin.getline(a.uchz, 50);
	cout << "Tochki Modul A: ";
	cin >> a.pointsA;
	cout << "Tochki Modul B: ";
	cin >> a.pointsB;
	a.pointsAB = a.pointsA + a.pointsB;
	cout << "Obsht broi tochki = " << a.pointsAB << endl;
	return(a);
}



int enter(uchastnici Spisyk[], int n) {
	int i, m;
	do {
		cout << "\n Kolko uchastnika iskate da wywedete?(max 5): ";
		cin >> m;
	} while (m < 0 || m>5);
	if (m + n < 30)
		for (i = n; i < n + m; i++) {
			cout << "\n uchastnik " << i + 1 << endl;
			Spisyk[i] = input();
		}
	else
		cout << "\n Nqma swobodni mesta w spisyka" << endl;
	return(n + m);
}

void saveinfile(uchastnici Spisyk[], int n) {
	fp.open(Filename, ios::binary | ios::out);
	if (!fp) {
		cout << "\n Error in file" << endl;
		exit(1);
	}
	fp.write((char*)Spisyk, n * sizeof(uchastnici));
	fp.close();
}


void output(uchastnici Spisyk[], int n) {
	int i, k = 0;
	cout << "Spisyk na uchasntici" << endl;
	for (i = 0; i < n; i++) {
		cout << "\n" << i + 1 << "\t" << Spisyk[i].num << " " << Spisyk[i].ime;
		cout << " " << Spisyk[i].uchz << " " << Spisyk[i].pointsA;
		cout << " " << Spisyk[i].pointsB << " " << Spisyk[i].pointsAB;
		k++;
		if (k % 5 == 0) cout << "\v";
	}
}


void max(uchastnici Spisyk[], int n) {
	int max, i;
	max = Spisyk[0].pointsAB;
	for (i = 0; i < n; i++) {
		if (max < Spisyk[i].pointsAB)
			max = Spisyk[i].pointsAB;
		cout << "Max tochki = " << max << " na uchenik: " << Spisyk[i].ime << endl;
	}

}


void uchpoime(uchastnici Spisyk[], int n) {
	char im[30];
	int flag = 0;
	cout << "Ime na uchastnika: ";
	cin >> im;
	for (int i = 0; i < n; i++)
		if (!strcmp(im, Spisyk[i].ime)) {
			cout << "Nameren" << endl;;
			flag = 1;
			cout << "Nomer: " << Spisyk[i].num << " ," << "Ime: " << Spisyk[i].ime << " ," << "Uchebno zawedenie: " << Spisyk[i].uchz << " ,";
			cout << "Tochki Modul A: " << Spisyk[i].pointsA << " ," << "Tochki Modul B: " << Spisyk[i].pointsB << " ,";
			cout << "Obsht broi tochki: " << Spisyk[i].pointsAB << endl;
		}
	if (!flag)
		cout << "\n Nqma uchastnik s takowa ime." << endl;
}


int loadfile(uchastnici Spisyk[]) {
	long pos;
	int n = 0, i;
	uchastnici b;
	fp.open(Filename, ios::binary | ios::in);
	if (!fp) {
		cout << "\n File doesnt exist" << endl;
		return n;
	}
	fp.seekg(0l, ios::end);
	pos = fp.tellg();
	fp.close();
	n = pos / (sizeof(uchastnici));
	fp.open(Filename, ios::binary | ios::in);
	if (!fp) {
		cout << "Error in file" << endl;
		exit(1);
	}
	for (i = 0; i < n; i++) {
		fp.read((char*)&b, sizeof(uchastnici));
		Spisyk[i] = b;
	}
	fp.close();
	return n;
}



int main() {
	int choice, n = 0;
	uchastnici Spisyk[N];
	n = loadfile(Spisyk);
	choice = menu();
	do {
		switch (choice) {
		case 1: n = enter(Spisyk, n); saveinfile(Spisyk, n); break;
		case 2: n = loadfile(Spisyk); output(Spisyk, n); break;
		case 3: n = loadfile(Spisyk); max(Spisyk, n); break;
		case 4: n = loadfile(Spisyk); uchpoime(Spisyk, n); break;
		case 5: saveinfile(Spisyk, n); break;
		}
	} while (choice != 6);
}