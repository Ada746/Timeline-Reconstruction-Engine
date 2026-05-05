#ifndef TIMELINEMANAGER_H
#define TIMELINEMANAGER_H

#include <iostream>
#include "liste1.h"
#include <string>

using namespace std;

struct Event {
	int id;
	string description;
	int year;
	int impact;
};

class TimelineManager {

private:
	LinkedList<Event> timeline;

	Node<Event>* findById(int id) {
		Node<Event>* p = timeline.pfirst;
		while (p != nullptr) {
			if (p->info.id == id) {
				return p;
			}
			p = p->next;
		}
		return nullptr;
	}

	void erase(Node<Event>* n) {
		if (n->prev != nullptr) {
			n->prev->next = n->next;
		}
		else {
			timeline.pfirst = n->next;
		}
		if (n->next != nullptr) {
			n->next->prev = n->prev;
		}
		else {
			timeline.plast = n->prev;
		}
		n->prev = nullptr;
		n->next = nullptr;
	}

public:
	//adds an event at the beginning
	void recordAncientEvent(Event e) {
		timeline.addFirst(e);
	}

	//adds an event at the end
	void recordRecentEvent(Event e) {
		timeline.addLast(e);
	}

	void insertEventBetween(int leftId, int rightId, Event e) {
		Node<Event>* left = findById(leftId);
		Node<Event>* right = findById(rightId);

		//checks if the IDs exist
		if (left == nullptr || right == nullptr) {
			cout << "ERROR. An ID does not exist in the timeline." << endl;
			return;
		}

		//checks if the IDs are consecutive
		if (left->next != right) {
			cout << "ERROR. " << leftId << " and " << rightId << "are not consecutiv" << endl;
			return;
		}

		Node <Event>* n = new Node<Event>;
		n->info = e;
		n->prev = left;
		n->next = right;
		left->next = n;
		right->prev = n;
	}

	//deletes the event with the given ID
	void eraseCorruptedEvent(int id) {
		Node<Event>* p = findById(id);

		if (p == nullptr) {
			cout << "ERROR. The event with the following id: " << id << " does not exist in this timeline." << endl;
			return;
		}

		erase(p);
		delete p;
	}

	//moves an event before or after another event
	void relocateEvent(int idToMove, int newNeighborId, bool before) {
		Node<Event>* toMove = findById(idToMove);
		Node<Event>* neighbor = findById(newNeighborId);

		if (toMove == nullptr) {
			cout << "ERROR. The following id: " << idToMove << "does not exist" << endl;
			return;
		}

		if (neighbor == nullptr) {
			cout << "ERROR. You can't move an event next to itself" << endl;
			return;
		}

		erase(toMove);

		if (before) {
			//places it before the neighbor
			toMove->next = neighbor;
			toMove->prev = neighbor->prev;

			if (neighbor->prev != nullptr) {
				neighbor->prev->next = toMove;
			}
			else {
				timeline.pfirst = toMove;
			}
			neighbor->prev = toMove;
		}
		else {
			//places it after the neighbor
			toMove->prev = neighbor;
			toMove->next = neighbor->next;

			if (neighbor->next != nullptr) {
				neighbor->next->prev = toMove;
			}
			else {
				timeline.plast = toMove;
			}
			neighbor->next = toMove;
		}
	}

	//displays the entire chronology
	void displayChronology() {
		Node<Event>* p = timeline.pfirst;
		while (p != nullptr) {
			cout << "[" << p->info.id << " | " << p->info.description << " | " << p->info.year << " | " << p->info.impact << "]" << endl;
			p = p->next;
		}
	}

	//impact - all events
	int computeTotalImpact() {
		int total = 0;
		Node<Event>* p = timeline.pfirst;
		while (p != nullptr) {
			total += p->info.impact;
			p = p->next;
		}
		return total;
	}

	//events with higher impact at the beginning
	void stabilizeTimeline(int threshold) {
		Node<Event>* highHead = nullptr;
		Node<Event>* highTail = nullptr;
		Node<Event>* lowHead = nullptr;
		Node<Event>* lowTail = nullptr;

		Node<Event>* p = timeline.pfirst;
		while (p != nullptr) {
			Node<Event>* next = p->next;

			p->prev = nullptr;
			p->next = nullptr;

			if (p->info.impact >= threshold) {
				if (highTail == nullptr) {
					highHead = p;
					highTail = p;
				}
				else {
					highTail->next = p;
					p->prev = highTail;
					highTail = p;
				}
			}
			else {
				if (lowTail == nullptr) {
					lowHead = p;
					lowTail = p;
				}
				else {
					lowTail->next = p;
					p->prev = lowTail;
					lowTail = p;
				}
			}
			p = next;
		}
		
		if (highHead == nullptr) {
			timeline.pfirst = lowHead;
			timeline.plast = lowTail;
		}
		else if (lowHead == nullptr) {
			timeline.pfirst = highHead;
			timeline.plast = highHead;
		}
		else {
			highTail->next = lowHead;
			lowHead->prev = highTail;
			timeline.pfirst = highHead;
			timeline.plast = lowTail;
		}
	}
};

#endif