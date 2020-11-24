#ifndef GRAPHBASICS_EDGE_HPP
#define GRAPHBASICS_EDGE_HPP

#include <iostream>
#include <cassert>

using std::cout;
using std::endl;
using std::ostream;


class Edge {
private:
    // two endpoints
    int Start, End;
    // weight of the edge
    double Weight;
public:
    Edge() {}

    Edge(int Start, int End, double Weight) : Start(Start), End(End), Weight(Weight) {}

    virtual ~Edge() {}

    int startPoint() const {
        return this->Start;
    }

    int endPoint() const {
        return this->End;
    }

    double weight() const {
        return this->Weight;
    }

    void setWeight(double Weight) {
        this->Weight = Weight;
    }

    // return the other endpoint
    int theOtherEndPoint(int oneEndPoint) const {
        return oneEndPoint == Start ? End : Start;
    }

    friend ostream& operator<<(ostream &out, const Edge &e) {
        out << e.Start << "->" << e.End << ": " << e.Weight << endl;
        return out;
    }

    bool operator<(Edge& e) const {
        return Weight < e.Weight;
    }

    bool operator<(const Edge& e) const {
        return Weight < e.Weight;
    }

    bool operator<=(Edge& e) const {
        return Weight <= e.Weight;
    }

    bool operator>(Edge& e) const {
        return Weight > e.Weight;
    }

    bool operator>(const Edge& e) const {
        return Weight > e.Weight;
    }

    bool operator>=(Edge& e) const {
        return Weight >= e.Weight;
    }

    bool operator==(Edge& e) const {
        return Weight == e.Weight;
    }

    bool operator!=(Edge& e) const {
        return Weight != e.Weight;
    }
};

#endif // GRAPHBASICS_EDGE_HPP
