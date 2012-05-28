#ifndef RV_PROPAGATE_H
#define RV_PROPAGATE_H

#include <string>
#include <map>
#include <rv_walk.h>

class RVSide;


class RVTypeProp : public RVWalk
{
	typedef std::map<std::string, BaseType*> RVFuncPtrSubstitutionMap;
	bool m_inTypedef;
	Project *m_project;
	RVFuncPtrSubstitutionMap m_newFuncPtrSubstitutions;

  protected:
    virtual bool process_const(Constant* it);
    virtual bool process_binary(BinaryExpr* it);
    virtual bool process_unary(UnaryExpr* it);

    bool CheckIntTypes(BinaryExpr* s0p, const char* op_name);

    bool ArithOpTypeConv(Expression* s0p, Type* ltp, Type* rtp);

    virtual bool process_member_op(BinaryExpr* it);
    virtual bool processStatement(Statement*, const RVSide&);

  public:
    static const BaseTypeSpec ArithMask;
    static const BaseTypeSpec IntMask;

    static bool isPointerToFunctionSubstitutingType(Type *);

    RVTypeProp(const char *_where = "UNKNOWN");
    virtual ~RVTypeProp() {}

    RVBoolStatus process_all(Project* pt, const RVSide& side);

    virtual bool process(Statement* it);

    virtual bool process(Expression* it);

    virtual bool process(ExprVector& it);

    virtual bool process(Decl* it);

    virtual bool try_replace(Type**);

    Type* enum_type(SymEntry* se, Location& location);

    BaseTypeSpec ArithOpTypeConvMask(BaseTypeSpec ltm, BaseTypeSpec rtm, Location& l);

    /* ignore parts: */
    virtual bool process(Symbol* it)     { return true; }
    virtual bool process(Label* it)      { return true; }    
};


class RVTypePropIgnoreNondet : public RVTypeProp {
public:
	virtual bool process(Expression* it);

	static bool ignored(const Variable*);
};


class RVDequalifier : public RVWalk {
public:
	void dequalify(Project *pt, const RVSide&);
	virtual bool process(Symbol* s0p);
    virtual bool try_replace(Type** s0p);
};

#endif /* RV_PROPAGATE_H */
