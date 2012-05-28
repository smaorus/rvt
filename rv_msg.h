/*
 * rv_msg.h
 *
 *  Created on: Jul 05, 2011
 *      Author: edima
 */

#ifndef RV_MSG_H_
#define RV_MSG_H_

#include <string>
#include <vector>

struct RvMsgArg {
	static const RvMsgArg RvMsgVoidArg;

	RvMsgArg(const std::string&);
	RvMsgArg(const char *);
	RvMsgArg(long);
	RvMsgArg(double);
	RvMsgArg(char);
	RvMsgArg(const void *);

	~RvMsgArg();

	long toLong(void) const;
	char toChar(void) const;
	double toDouble(void) const;
	const std::string& toString(void) const;
	const void *toPtr(void) const;

	bool isVoid(void) const;

	RvMsgArg* clone(void) const;

private:
	RvMsgArg(void);
	RvMsgArg(const RvMsgArg&);
	void assertValueType(unsigned expected) const;

	unsigned    m_type;
	void *m_pVal;
};


struct RVIdMsgPair {
	unsigned       m_id;
	const char*    m_msg;
};



class RVMsgBase {
public:
	void args(const RvMsgArg& a1,
			  const RvMsgArg& a2 = RvMsgArg::RvMsgVoidArg,
			  const RvMsgArg& a3 = RvMsgArg::RvMsgVoidArg,
			  const RvMsgArg& a4 = RvMsgArg::RvMsgVoidArg,
			  const RvMsgArg& a5 = RvMsgArg::RvMsgVoidArg);

	~RVMsgBase();

protected:
	RVMsgBase(unsigned id,
			  const RVIdMsgPair* locMsgsEng = NULL,
			  unsigned n_locMsgs = 0,
			  const char *whereDefined = NULL);

	std::string    		   m_out;
private:
	std::string retrieveMessageBase(bool rec);

	unsigned               m_id;
	unsigned               m_nLocMsgs;
	const RVIdMsgPair     *m_locMsgsEng;
	const char            *m_whereDefined;
	std::vector<RvMsgArg*> m_argv;
};


template<unsigned ID> struct RVMsg : public RVMsgBase {
	RVMsg(const RvMsgArg& a1,
		  const RvMsgArg& a2 = RvMsgArg::RvMsgVoidArg,
		  const RvMsgArg& a3 = RvMsgArg::RvMsgVoidArg,
		  const RvMsgArg& a4 = RvMsgArg::RvMsgVoidArg,
		  const RvMsgArg& a5 = RvMsgArg::RvMsgVoidArg)
	  : RVMsgBase(ID)
	{
		args(a1, a2, a3, a4, a5);
	}

	RVMsg(void) : RVMsgBase(ID) {}

	operator const char* (void) const { return m_out.data(); }
};

#define RV_LOC_MSGS_ENG_BEGIN \
	static RVIdMsgPair _RV_Local_Messages_Eng_[] = {

#define RV_LOC_MSGS_ENG_END(filename) \
	};\
	template <unsigned ID> struct RVLocMsg : public RVMsgBase {\
		RVLocMsg(const RvMsgArg& a1,\
			     const RvMsgArg& a2 = RvMsgArg::RvMsgVoidArg,\
			     const RvMsgArg& a3 = RvMsgArg::RvMsgVoidArg,\
			     const RvMsgArg& a4 = RvMsgArg::RvMsgVoidArg,\
			     const RvMsgArg& a5 = RvMsgArg::RvMsgVoidArg)\
		  : RVMsgBase(ID,\
					  _RV_Local_Messages_Eng_,\
					  sizeof(_RV_Local_Messages_Eng_)/sizeof(RVIdMsgPair),\
					  filename)\
		{\
			args(a1, a2, a3, a4, a5);\
		}\
\
		RVLocMsg(void) : RVMsgBase(ID) {}\
\
		operator const char* (void) const { return m_out.data(); }\
	}


#endif /* RV_MSG_H_ */
