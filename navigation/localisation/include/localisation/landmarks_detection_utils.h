#include "laserScan.h"
#include "Point.h"
#include "Droite.h"
#include "Modele.h"
#include "Segment.h"
#include "Machine.h"

double dist(Point a, Droite d);

double dist(Point a, Segment s);

Point ortho(Point a, Droite d);

Point ortho(Point a, Segment s);

Modele ransac(std::list<Point> &listOfPoints, int n, int NbPtPertinent, double proba, double seuil, int NbPts);

void maj(std::list<Point> &list, Modele m);

std::list<Modele> findLines(const std::list<Point> &listOfPoints);

Segment build(const std::list<Point> &points);

std::list<Segment> buildSegment(Modele m, double seuil);

std::list<Segment> buildSegments(std::list<Modele> &listOfModeles);

std::list<Machine> recognizeMachinesFrom(std::list<Segment> listOfSegments);