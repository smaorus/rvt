
/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

    CTool Library
    Copyright (C) 1998-2001	Shaun Flisakowski

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 1, or (at your option)
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
    o+
    o+     File:         decl.h
    o+
    o+     Programmer:   Shaun Flisakowski
    o+     Date:         Aug 9, 1998
    o+
    o+     A high-level view of types / declarations.
    o+
    o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

#ifndef    DECL_H
#define    DECL_H

#include <iostream>
#include <vector>
#include <cassert>

#include <ctool/symbol.h>
#include <ctool/callback.h>
#include <ctool/location.h>

#include <ctool/dup.h>

#include <ctool/Traversal.h>

#include "rv_glob.h"

class Constant;
class Expression;
class EnumConstant;

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

typedef unsigned long BaseTypeSpec;

const BaseTypeSpec BT_NoType       = 0x00000000;  // no type provided
const BaseTypeSpec BT_Void         = 0x00000001;  // explicitly no type
const BaseTypeSpec BT_Bool         = 0x00000002;
const BaseTypeSpec BT_Char         = 0x00000004;
const BaseTypeSpec BT_Short        = 0x00000008;
const BaseTypeSpec BT_Int          = 0x00000010;
const BaseTypeSpec BT_Int64        = 0x00000020;
const BaseTypeSpec BT_Int32        = 0x00000040;
const BaseTypeSpec BT_Int16        = 0x00000080;
const BaseTypeSpec BT_Int8         = 0x00000100;
const BaseTypeSpec BT_Long         = 0x00000200;
const BaseTypeSpec BT_LongLong     = 0x00000400;  // a likely C9X addition
const BaseTypeSpec BT_Float        = 0x00000800;
const BaseTypeSpec BT_Double       = 0x00001000;
const BaseTypeSpec BT_Ellipsis     = 0x00002000;

const BaseTypeSpec BT_Struct       = 0x00008000;
const BaseTypeSpec BT_Union        = 0x00010000;
const BaseTypeSpec BT_Enum         = 0x00020000;
const BaseTypeSpec BT_UserType     = 0x00040000;
const BaseTypeSpec BT_BaseMask     = 0x0004FFFF;

// Sign indicator
const BaseTypeSpec BT_Signed       = 0x00100000;
const BaseTypeSpec BT_UnSigned     = 0x00200000;
const BaseTypeSpec BT_SignMask     = 0x00300000;

const BaseTypeSpec BT_TypeError    = 0x10000000;

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
typedef unsigned short TypeQual;

const TypeQual TQ_None         = 0x0000;
const TypeQual TQ_Const        = 0x0001;
const TypeQual TQ_Volatile     = 0x0002;

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
enum StorageType
{
    ST_None  = 0,
    ST_Auto,
    ST_Extern,
    ST_Register,
    ST_Static,
    ST_Typedef
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
enum TypeKind
{
    TK_Base = 0,
    TK_TypeDef,
    TK_UserType
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
enum TypeType
{
    TT_Base,        // a simple base type, T
    TT_Pointer,     // pointer to T
    TT_Array,       // an array of T
    TT_BitField,    // a bitfield
    TT_Function     // <args> -> <result>

    /*    These are now considered TT_Base
    TT_Struct,     
    TT_Union,
    TT_Enum
    */
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
// For gcc extension __attribute__
enum GccAttribType
{
    GCC_Unsupported = 0,    // Not supported by cTool

    GCC_Aligned,
    GCC_Packed,
    GCC_CDecl,
    GCC_Mode,
    GCC_Format,
   
    GCC_Const,
    GCC_NoReturn,
    GCC_Malloc
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

class Decl;

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class StructDef
{
  public:
    StructDef( bool _is_union = false );
    ~StructDef();

    bool    isUnion() const { return _isUnion; }

    StructDef*   dup0() const;
    StructDef*   dup() const;    // deep-copy

    void    print(std::ostream& out, Symbol *name, int level) const;

    void    findExpr( fnExprCallback cb );

    void    addComponent(Decl *comp);

    void    registerComponents();

    // Lookup this symbol in this struct/union and set its entry
    // if its a component of it.
    bool    lookup( Symbol* sym ) const;

    bool            _isUnion;
    Symbol         *tag;

    int             size;          // size of the array.
    int             nComponents;
    Decl          **components;

// benny added:
    const StructDef*      assumeEq;   // to compare recursive struct/union

  private:
    Decl   *lastDecl();
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class EnumDef
{
  public:
    EnumDef();
    ~EnumDef();

    EnumDef*   dup0() const;
    EnumDef*   dup() const;    // deep-copy

    void print(std::ostream& out, Symbol *name, int level) const;
    void findExpr( fnExprCallback cb );

    void addElement( Symbol *nme, Expression *val = NULL );

    void addElement( EnumConstant* ec );

    Symbol         *tag;

    int             size;       // size of the arrays.
    int             nElements;
    Symbol        **names;
    Expression    **values;
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

class Type;
typedef Dup<Type> DupableType;

class Type : public DupableType
{
  public:
    Type(TypeType _type=TT_Base);
    virtual ~Type();

    virtual void accept(Traversal *) = 0;

    virtual int     precedence() const { return 16; }
    virtual Type*   dup0() const =0;    // deep-copy
	
    virtual Type*   extend(Type *extension)=0;

    // This function handles the complexity of printing a type.
    void    printType( std::ostream& out, Symbol *name,
                       bool showBase, int level) const;

	void    myprintType( std::ostream& out, Symbol *name) const; // ofer: change tag NO_ALLOCATION_IN_MAIN
    virtual void printBase( std::ostream& out, int level ) const {}	
	virtual void printBefore( std::ostream& out, Symbol *name, int level) const {}    	
	virtual void printBefore( std::ostream& out, Symbol *name, int level, bool remove_pointer) const {}    	
    virtual void printAfter( std::ostream& out ) const {}

    virtual void printForm(std::ostream& out) const { out << "-[ABT]"; }

    virtual void registerComponents() {}

    virtual void findExpr( fnExprCallback cb ) {}

    virtual bool lookup( Symbol* sym ) const { return false; }

    bool    isBaseType() const { return (type == TT_Base); }
    bool    isPointer() const { return (type == TT_Pointer); }
    bool    isFunction() const { return (type == TT_Function); }
    bool    isArray() const { return (type == TT_Array); }

    // Delete all types stored in this list.
    static void    DeleteTypeList(Type* typelist);
	bool isVoid();


    TypeType        type;

    // Temporary - is moved into the declaration (Decl).
    StorageType     storage;

// benny added:
    const Type*           equalTo;

  private:
    Type*           link;    // For linking all type classes together.
    GLOB_UNIQ_ID;   //m_uniq_id
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class BaseType : public Type
{
  public:
    BaseType( BaseTypeSpec = BT_NoType );
    BaseType( StructDef *sd );
    BaseType( EnumDef *ed );
    ~BaseType();

    virtual void accept(Traversal *t) { t->traverse_base(this);}

    Type* dup0() const;    // deep-copy

    Type* extend(Type *extension) { assert(0); return NULL; }

    void printBase( std::ostream& out, int level ) const;
    void printBefore( std::ostream& out, Symbol *name, int level) const;
    void printAfter( std::ostream& out ) const;

    void printForm(std::ostream& out) const;

    void registerComponents();

    bool lookup( Symbol* sym ) const;

    BaseTypeSpec    typemask;

    TypeQual        qualifier;

    Symbol          *tag;        // tag for struct/union/enum
    Symbol          *typeName;   // typedef name for a UserType

    StructDef       *stDefn;     // optional definition of struct/union
    EnumDef         *enDefn;     // optional definition of enum 
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class PtrType : public Type
{
  public:
    PtrType(TypeQual qual = TQ_None)
        : Type(TT_Pointer), qualifier(qual), subType(NULL){};
    ~PtrType(){};

    virtual void accept(Traversal *t) { t->traverse_ptr(this);}

    int    precedence() const { return 15; }

    Type* dup0() const;    // deep-copy

    Type* extend(Type *extension);

    void printBase( std::ostream& out, int level ) const;
    void printBefore( std::ostream& out, Symbol *name, int level) const;
	void printBefore( std::ostream& out, Symbol *name, int level, bool print_pointer) const; // ofer: change tag NO_ALLOCATION_IN_MAIN
	void myprintBefore( std::ostream& out) const;
    void printAfter( std::ostream& out ) const;

    void printForm(std::ostream& out) const;

    void registerComponents() { if (subType) subType->registerComponents(); }

    void findExpr( fnExprCallback cb );

    bool lookup( Symbol* sym ) const;

    TypeQual        qualifier;
    Type           *subType;
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class ArrayType : public Type
{
  public:
    ArrayType(Expression *s)
          : Type(TT_Array), subType(NULL), size(s) {};

    ~ArrayType();

    virtual void accept(Traversal *t) { t->traverse_array(this);}

    Type* dup0() const;    // deep-copy

    Type* extend(Type *extension);

    void printBase( std::ostream& out, int level ) const;
    void printBefore( std::ostream& out, Symbol *name, int level) const;
    void printAfter( std::ostream& out ) const;

    void printForm(std::ostream& out) const;

    void registerComponents() { if (subType) subType->registerComponents(); }

    void findExpr( fnExprCallback cb );

    bool lookup( Symbol* sym ) const;

    Type           *subType;

    Expression     *size;
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class BitFieldType : public Type
{
  public:
    BitFieldType(Expression * s = NULL)
          : Type(TT_BitField),size(s),subType(NULL) {};
    ~BitFieldType();

    virtual void accept(Traversal *t) { t->traverse_bit_field(this);}

    Type* dup0() const;    // deep-copy

    Type* extend(Type *extension);

    void printBase( std::ostream& out, int level ) const;
    void printBefore( std::ostream& out, Symbol *name, int level) const;
    void printAfter( std::ostream& out ) const;

    void printForm(std::ostream& out) const;

    void registerComponents() { if (subType) subType->registerComponents(); }

    void findExpr( fnExprCallback cb );

    bool lookup( Symbol* sym ) const;

    Expression     *size;

    Type           *subType;
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class FunctionType : public Type
{
  public:
    FunctionType(Decl *args_list = NULL);
    ~FunctionType();

    virtual void accept(Traversal *t) { t->traverse_function(this);}

    Type* dup0() const;    // deep-copy

    Type* extend(Type *extension);

    void printBase( std::ostream& out, int level ) const;
    void printBefore( std::ostream& out, Symbol *name, int level) const;
    void printAfter( std::ostream& out ) const;

    void printForm(std::ostream& out) const;

    void registerComponents() { if (subType) subType->registerComponents(); }

    void addArg(Decl *arg);
    void addArgs(Decl *args);

    void findExpr( fnExprCallback cb );

    bool lookup( Symbol* sym ) const;

    bool            KnR_decl;    // old-style function declaration?
    int             nArgs;
    int             size;
    Decl          **args;

    Type           *subType;    // The return type
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class GccAttrib
{
  public:
    GccAttrib( GccAttribType gccType );
    ~GccAttrib();

    GccAttrib* dup0() const;
    GccAttrib* dup() const;

    void    print( std::ostream& out ) const;

    GccAttribType    type;

    uint             value;    // For use with GCC_Aligned
    Symbol          *mode;     // For use with GCC_Mode, GCC_Format

    uint             strIdx;   // For use with GCC_Format
    uint             first;    // For use with GCC_Format
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
class Decl
{
  public:
    Decl( Symbol* sym = (Symbol*) NULL );
    Decl( Type* type );
    ~Decl();

    Type*   extend( Type* type );

    bool    isTypedef() const { return (storage == ST_Typedef); }
    bool    isStatic() const { return (storage == ST_Static); }

    void    clear();

    Decl*   dup0() const;
    Decl*   dup() const;        // deep-copy

    void    copy(const Decl& decl);    // shallow copy

    void    print(std::ostream& out, bool showBase, int level=0) const;
    void    printBase(std::ostream& out, Symbol *name,
                       bool showBase, int level) const;

    void    findExpr( fnExprCallback cb );

    bool lookup( Symbol* sym ) const;

    StorageType     storage;

    Type            *form;    // i.e., int *x[5] 

    Symbol          *name;    // The symbol being declared.

    GccAttrib       *attrib;  // optional gcc attribute

    Expression      *initializer;

    Decl            *next;    // For linking into lists
};

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

typedef    std::vector<Decl*>    DeclVector;

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

Decl*	ReverseList( Decl* dList );

// o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o

#endif  /* DECL_H */

