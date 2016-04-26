/*
 * POI.h
 */

#ifndef POI_H_
#define POI_H_

#include "street.h"

class POI{
private:
	string name;
	Street* street;
public:
	POI(string name, Street * street);
	string getName() const;
	void setName(string name);
	Street * getStreet() const;
	void setStreet(Street* street);
	bool operator==(const POI &b);
};

void loadPOIs(string filename, list<POI*> &vecPOI, list<Street*> &streets);

#endif /* POI_H_ */
