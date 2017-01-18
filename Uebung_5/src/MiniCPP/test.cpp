void Sieve(int n); // declaration

void main() {
	int n;
	int x = 0;
	cout << "n > ";
	cin >> n;
	if (n > 2)
		Sieve(n);
	
	if(n > 2) {
		x++;
	}
	else {
		x--;
	}	
} // main

void Sieve(int n) { // definition
	int col, i, j;
	bool *sieve = 0;

	sieve = new bool[n + 1];
	i = 2;

	while (i <= n) {
		sieve[i] = true;
		i++;
	} // while

	cout << 2 << " ";
	col = 1;
	i = 3;

	while (i <= n) {
		if (sieve[i]) {
			if (col == 10) {
				cout << endl;
				col = 0;
			} // if
			
			col++;
			cout << i << " ";
			j = i * i;
			
			while (j <= n) {
				sieve[j] = false;
				j = j + 2 * i;
			} // while
		} // if

		i = i + 2;
	} // while
	delete[] sieve;
} // Sieve