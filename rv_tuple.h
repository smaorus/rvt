#ifndef RV_TUPLE_H
#define RV_TUPLE_H

template <typename T1, typename T2> struct Tuple {
	T1 item1;
	T2 item2;

	Tuple(const T1& i1, const T2& i2) : item1(i1), item2(i2) {}
};


typedef Tuple<int, int> Edge;
typedef Tuple<int, int> Match;


#endif
