/*
 * rv_side.h
 *
 *  Created on: Jul 3, 2011
 *      Author: edima
 */

#ifndef RV_SIDE_H_
#define RV_SIDE_H_

#include <string>

#define RV_NSIDES (2U)


class RVSide {
public:
    RVSide(int num);
	RVSide(const char *name) : m_name(name), m_index(-1) {}
	RVSide(const std::string& name) : m_name(name), m_index(-1) {}
	RVSide(const RVSide& o) : m_name(o.m_name), m_index(o.m_index) {}

	RVSide& operator= (const RVSide& o);
	bool operator== (const RVSide& o) const { return m_index == o.m_index; }

	const char* get_rvact_name(void) const;
	const char* get_side_prefix(void) const;
    const char* get_side_ufprefix(void) const;
	std::string insert_side_ufprefix(const std::string& id) const;
    const char* get_semchk_prefix(void) const;
    const char* get_main_prefix(bool semchk) const;

	const std::string& toString(void) const { return m_name; }
	std::string toString(const char *prefix) const;
	int index(void) const;
	bool isSide0(void) const { return index() == 0; }
	bool isIllegalIndex(void) const { return m_index != 0 && m_index != 1; }

	template <typename T> T& select(T& v0, T& v1) const {
		switch(m_index) {
		case 0: return v0;
		case 1: return v1;
		}

		badIndexError("select()");
		return v0;
	}

	template <typename T> static void initArray(T* arr, const T& val = 0) {
		for (unsigned i = 0; i < RV_NSIDES; ++i)
			arr[i] = val;
	}

private:
	operator bool (void) const {return false;} //Casting into bool is forbidden
	operator int (void) const {return m_index;} //Casting into int is forbidden

	void badIndexError(const char *where) const;

	std::string m_name;
	int         m_index;
};


#endif /* RV_SIDE_H_ */
