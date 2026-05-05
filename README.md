# Timeline-Reconstruction-Engine

A timeline reconstruction system implemented in C++, based on a generic doubly linked list. The project simulates a timeline correction engine in which events can be added, inserted, moved, deleted, and reorganized according to their importance.

Project Structure

liste1.h = generic doubly linked list, LinkedList<T> and Node<T>
TimelineManager.h = Event structure and TimelineManager class
ex2.cpp = main program that demonstrates the features

Files
liste1.h

Contains the implementation of the generic doubly linked list.

Defines the node structure Node<T> with the fields info, next, and prev, as well as the class LinkedList<T> with the methods addFirst, addLast, removeFirst, removeLast, findFirstOccurrence, findLastOccurrence, removeFirstOccurrence, removeLastOccurrence, and isEmpty.

TimelineManager.h

Contains the Event structure and the TimelineManager class.

Internally, it uses a LinkedList<Event>, the doubly linked list defined in liste1.h, specialized for the Event type.

ex2.cpp

Main program.

Creates a TimelineManager object, adds events, demonstrates all available operations, and displays the state of the timeline after each operation.

Event Structure

Each timeline event has 4 fields:

id (int) = positive unique identifier
description (string) = short description of the event
year (int) = year in which the event takes place
impact (int) = importance of the event, integer value

Features
recordAncientEvent(Event e)

Adds an event to the beginning of the timeline.

Uses addFirst from liste1.h.

recordRecentEvent(Event e)

Adds an event to the end of the timeline.

Uses addLast from liste1.h.

insertEventBetween(int leftId, int rightId, Event e)

Inserts a new event between two existing events.

Checks that both identifiers exist in the timeline and that they are consecutive, meaning that no other event is located between them. If the checks fail, it displays an error message and does not modify the list.

eraseCorruptedEvent(int id)

Deletes the event with the given identifier. If the identifier does not exist, it displays an error.

Internally uses the private function erase(), which reconnects the node’s neighbors before deletion.

relocateEvent(int idToMove, int newNeighborId, bool before)

Moves an event to a new position.

The before parameter controls the direction:

true = the event is placed before the specified neighbor
false = the event is placed after it

The node is first detached from its current position, then reinserted at the new position.

displayChronology()

Traverses the list from pfirst to plast and displays all events in the following format:

[id | description | year | impact]

computeTotalImpact()

Traverses the entire list and returns the sum of the impact values of all events.

stabilizeTimeline(int threshold)

Reorganizes the timeline so that all events with an impact greater than or equal to threshold appear first, while preserving the relative order of each group.

Internally, it builds two temporary sublists, highList and lowList, fills them by traversing the list only once, then concatenates them.

Private Functions
findById(int id)

Traverses the list from pfirst and returns a pointer to the node with the searched identifier, or nullptr if it does not exist.

Used internally by most public methods.

erase(Node<Event>* n)

Detaches a node from the list without deleting it from memory, by reconnecting its neighbors.

Updates pfirst or plast if the node was the first or the last.

Used in eraseCorruptedEvent and relocateEvent.
