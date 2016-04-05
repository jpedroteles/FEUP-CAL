/*
 * UtilFunctions.cpp
 */

#include "Ponto.h"
#include "Util.h"
#include <time.h>
#include <sys/timeb.h>

double nearestPoints_BF(vector<Ponto> &vp, vector<Ponto> &vMP) {
	Ponto p1, p2;
	double dMin = DMAXIMUM, dist;
	for (unsigned i = 0; i < vp.size(); i++) {
		for (unsigned j = i + 1; j < vp.size(); j++) {
			dist = vp[i].distancia(vp[j]);
			if (dist < dMin) {
				p1 = vp[i];
				p2 = vp[j];
				dMin = dist;
			}
		}
	}
	vMP.push_back(p1);
	vMP.push_back(p2);
	return dMin;
}

// divide and conquer approach
double np_DC(vector<Ponto> &vp, int left, int right, Ponto &pLeft, Ponto &pRight) {

	if ((right - left) == 1) {
		pLeft = vp[left];
		pRight = vp[right];
		return vp[left].distancia(vp[right]);
	}
	if (right==left) {
		pLeft=vp[left];
		pRight=vp[right];
		return DMAXIMUM;
	}

	Ponto p1L, p2L, p1R, p2R;
	int middle=(right + left)/2;
	double dminL = np_DC(vp, left, middle, p1L, p2L);
	double dminR = np_DC(vp, middle + 1, right, p1R, p2R);
	double dminAux;
	if (dminR < dminL) {
		pLeft = p1R;
		pRight = p2R;
		dminAux = dminR;
	}
	else {
		pLeft = p1L;
		pRight = p2L;
		dminAux = dminL;
	}

	int indLeft = middle-1;
	int indRight = middle+1;
	while ((indLeft > left) && (vp[middle].x - vp[indLeft].x < dminAux))
		indLeft--;
	while ((indRight < right) && (vp[indRight].x - vp[middle].x < dminAux))
		indRight++;

	quickSort(vp, indLeft, indRight, Y);

	for (int i = indLeft; i < indRight; i++) {
		for (int j = i + 1; j <= indRight; j++) {
			if (vp[j].y - vp[i].y > dminAux)
				break;
			else {
				double d = vp[i].distancia(vp[j]);
				if (d < dminAux) {
					pLeft = vp[i];
					pRight = vp[j];
					dminAux = d;
				}
			}
		}
	}
	quickSort(vp, indLeft, indRight, X);
	return dminAux;
}

double nearestPoints_DC(vector<Ponto> &vp, vector<Ponto> &vMP) {
	quickSort(vp, 0, vp.size() -1, X);
	Ponto p1, p2;
	double dist = np_DC(vp, 0, vp.size() - 1, p1, p2);

	vMP.push_back(p1);
	vMP.push_back(p2);
	return dist;
}

/**
 * function to fill list 'lp' with 'Ponto' objects read from 'is'
 */
void lerPontos(istream &is, vector<Ponto> &vp){
	double x, y;
	if (!is)
		return;
	while (!is.eof()) {
		is >> x >> y;
		Ponto p(x,y);
		vp.push_back(p);
	}
}
//---------------------------------------------------------------------------

/**
 * function to compare 'Ponto' based on 'X' or 'Y'
 */
double comparaPontos(Ponto p1, Ponto p2, int type) {
	if (type == X)
		return p1.x - p2.x;
	return p1.y - p2.y;
}
//---------------------------------------------------------------------------
/**
 * quickSort algorithm for 'std::vector<bestHistory>' by ascending X coordinate
 */
void quickSortX(vector<Ponto> &vp)
{
	quickSort(vp, 0, vp.size()-1, X);
}
//---------------------------------------------------------------------------

/**
 * quickSort algorithm for 'std::vector<bestHistory>' by ascending Y coordinate
 */
void quickSortY(vector<Ponto> &vp)
{
	quickSort(vp, 0, vp.size()-1, Y);
}
//---------------------------------------------------------------------------

void quickSort(vector<Ponto> &v, int left, int right, int type)
{
	if (right - left <= 50)    // if small vector
		insertionSort(v, left, right, type);
	else {
		Ponto p = median3(v, left, right, type);  // x is pivot
		int i = left; int j = right-1;            // partition step
		double comp;
		for(; ; ) {

			comp = -1;
			while (comp < 0) {
				comp = comparaPontos(v[++i], p, type);
			}

			comp = -1;
			while (comp < 0) {
				comp = comparaPontos(p, v[--j], type);
			}
			if (i < j)
				swap(v[i], v[j]);
			else break;
		}
		swap(v[i], v[right-1]);  // reset pivot
		quickSort(v, left, i-1, type);
		quickSort(v, i+1, right, type);
	}
}
//---------------------------------------------------------------------------

/**
 * choose pivot as the median of three values:
 * extremes and central value of vector
 */
Ponto & median3(vector<Ponto> &v, int left, int right, int type)
{
	int center = (left+right) /2;
	if (comparaPontos(v[center], v[left], type) < 0)
		swap(v[left], v[center]);

	if (comparaPontos(v[right], v[left], type) < 0)
		swap(v[left], v[right]);

	if (comparaPontos(v[right], v[center], type) < 0)
		swap(v[center], v[right]);

	swap(v[center], v[right-1]);     // put pivot in position 'right-1'
	return v[right-1];
}
//---------------------------------------------------------------------------

/**
 * for small vectors use a simple method - insertion sort
 */
void insertionSort(vector<Ponto> &v, int left, int right, int type)
{
	for (int i = left+1; i < right+1; i++)
	{
		Ponto tmp = v[i];
		int j;
		for (j = i; j > left && comparaPontos(tmp, v[j-1], type) < 0; j--)
			v[j] = v[j-1];
		v[j] = tmp;
	}
}
//---------------------------------------------------------------------------

/*
 * Print time
 */
// Something like GetTickCount but portable
// It rolls over every ~ 12.1 days (0x100000/24/60/60)
// Use GetMilliSpan to correct for rollover

int GetMilliCount()
{
	timeb tb;
	ftime( &tb );
	int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
	return nCount;
}
//---------------------------------------------------------------------------

int GetMilliSpan(int nTimeStart)
{
	int nSpan = GetMilliCount() - nTimeStart;
	if (nSpan < 0)
		nSpan += 0x100000 * 1000;
	return nSpan;
}
//---------------------------------------------------------------------------

