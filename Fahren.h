

#ifndef FAHREN_H_
#define FAHREN_H_

#include "Verhalten.h"

class Fahren: public Verhalten {
public:

	Fahren(Weg& w1);
	virtual ~Fahren();
};

#endif /* FAHREN_H_ */
