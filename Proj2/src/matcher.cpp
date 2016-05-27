/*
 * matcher.cpp
 */

#include "matcher.h"

int kmp(string text, string pattern){
	int num=0;
	int m=pattern.length();
	vector<int> prefix(m);
	prefix[0]=-1;
	int k=-1;
	for (int q=1; q<m; q++) {
		while (k>-1 && pattern[k+1]!=pattern[q])
			k = prefix[k];
		if (pattern[k+1]==pattern[q]) k=k+1;
		prefix[q]=k;
	}
	int n=text.length();
	int q=-1;
	for (int i=0; i<n; i++) {
		while (q>-1 && pattern[q+1]!=text[i])
			q=prefix[q];
		if (pattern[q+1]==text[i])
			q++;
		if (q==m-1) {
			cout <<"pattern occurs with shift" << i-m+1 << endl;
			num++;
			q=prefix[q];
		}
	}
	return num;
}

int numStringMatching(string filename, string toSearch){
	ifstream file(filename.c_str());
	if (!file){
		cout << "Erro a abrir ficheiro de leitura\n";
		return 0;
	}
	string line1;
	int num=0;
	while (!file.eof()) {
		getline(file,line1);
		num+=kmp(line1,toSearch);
	}
	file.close();
	return num;
}

int editDistance(string pattern, string text){
	int n=text.length();
	vector<int> d(n+1);
	int old,newOne;
	for (int j=0; j<=n; j++)
		d[j]=j;
	int m=pattern.length();
	for (int i=1; i<=m; i++) {
		old = d[0];
		d[0]=i;
		for (int j=1; j<=n; j++) {
			if (pattern[i-1]==text[j-1]) newOne = old;
			else {
				newOne = min(old,d[j]);
				newOne = min(newOne,d[j-1]);
				newOne = newOne +1;
			}
			old = d[j];
			d[j] = newOne;
		}
	}
	return d[n];
}

float numApproximateStringMatching(string filename, string toSearch){
	ifstream file(filename.c_str());
	if (!file){
		cout << "Erro a abrir ficheiro de leitura\n";
		return 0;
	}
	string line1,word;
	int num=0,nwords=0;
	while (!file.eof()) {
		getline(file,line1);
		stringstream s1(line1);
		while (!s1.eof()) {
			s1 >> word;
			num += editDistance(toSearch,word);
			nwords++;
		}
	}
	file.close();
	float res=(float)num/nwords;
	return res;
}



