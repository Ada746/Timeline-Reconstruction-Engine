#include <iostream>
#include "TimelineManager.h"

using namespace std;

int main()
{
	TimelineManager tm;

	//initial events
	Event e1;
	e1.id = 1;
	e1.description = "Quantum energy";
	e1.year = 2300;
	e1.impact = 90;
	tm.recordRecentEvent(e1);

	Event e2;
	e2.id = 2;
	e2.description = "Mars colonization";
	e2.year = 2350;
	e2.impact = 70;
	tm.recordRecentEvent(e2);

	Event e0;
	e0.id = 0;
	e0.description = "First contact";
	e0.year = 2200;
	e0.impact = 100;
	tm.recordAncientEvent(e0);

	//display initial state
	cout << "Initial timeline:" << endl;
	tm.displayChronology();
	cout << endl;

	//insert between events 1 and 2
	Event e3;
	e3.id = 3;
	e3.description = "Temporal crisis";
	e3.year = 2400;
	e3.impact = 95;
	tm.insertEventBetween(1, 2, e3);

	cout << "After insert : " << endl;
	tm.displayChronology();
	cout << endl;

	tm.relocateEvent(3, 0, false);

	cout << "After relocation:" << endl;
	tm.displayChronology();
	cout << endl;

	tm.eraseCorruptedEvent(1);

	cout << "After removal:" << endl;
	tm.displayChronology();
	cout << endl;

	cout << "Total impact: " << tm.computeTotalImpact() << endl;
	cout << endl;

	tm.stabilizeTimeline(80);

	cout << "After stabilization:" << endl;
	tm.displayChronology();

	return 0;
}