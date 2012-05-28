using namespace std;

#include <ctool/decl.h>
#include <ctool/stemnt.h>
#include <ctool/project.h>
#include <ctool/express.h>
#include <ctool/symbol.h>
#include <rv_typeeqmac.h>
#include <algorithm>
#include <vector>
#include <map>

RvTypeEqMac::RvTypeEqMac(std::ostream &os)
   : out(os)
{

}

string RvTypeEqMac::type_2_name(Type *t ) 
{
    string ret;
    BaseType *b = (BaseType *) t;
    BaseTypeSpec typemask = b->typemask;

    ret = "common";

    if (t->isPointer()) {
        PtrType *pt = (PtrType *) t;
        ret = type_2_name(pt->subType);
    } else if (t->isArray()) {
        ArrayType *arr = (ArrayType *) t;
        ret = type_2_name(arr->subType);
    } else if (!t->isFunction()) {
        if ((typemask & BT_Struct) || (typemask & BT_Union ) ||
            (typemask & BT_Enum  ) || (typemask & BT_UserType)) {
           if (b->typeName) ret = b->typeName->name;
           else {
               if (b->tag)  {
                   ret = b->tag->name;
               }
               else {
                   ret = "ERR_HHH";
                   t->printType( out, NULL, true, 0);;
               }
           }
        }
    }
    return ret;
}

int RvTypeEqMac::get_array_size(Expression *exp )
{
    int ret = -1;

    if (exp->etype != ET_Constant) {
    } else {
        Constant *tcon = (Constant *) exp;
        switch  (tcon->ctype)  {
            case CT_Int  : ret = static_cast<IntConstant *>(tcon)->lng  ;break;
            case CT_UInt : ret = static_cast<UIntConstant *>(tcon)->ulng;break;
            default : break;
        }
    }
    return ret;
}

void RvTypeEqMac::insert(string name, Type *t)
{
     static bool common_in = false;
     
     //out << "Inserting " << name << "\n";

     if (name == "common") {
         if (!common_in) {
             common_in = true;
             by_name.insert( pair<string, Type*>(name, t) );
         }
         return;
     }

     by_name.insert( pair<string, Type*>(name, t) );
}


Type* RvTypeEqMac::get_by_name(string name)
{
    std::map<std::string, Type*>::iterator i;

    /*
    for (i = by_name.begin(); i != by_name.end(); i++) {
        cout << "second : " << (*i).first << "\n";
    }
    */

    i = by_name.find(name);
    if( i == by_name.end() ) { 
        return NULL; 
    }
    return (*i).second;
}


void RvTypeEqMac::gen_chk_code(Type *t, int array_size, bool is_top )
{
    static bool generated_common = false;
    string t_2_name = type_2_name(t);


    if (t_2_name == "common") {
        if (!generated_common) {
            insert(t_2_name , t);
            generated_common = true;

            out << "\n#define chk_one_common(a,b,eq) { eq = (eq && (a==b)); }\n";
            out << "\n#define cp_one_common(a,b) { a=b; }\n";
            out << "\n#define nondet_one_common(a) { a= nondet_int(); }\n";
        }
    }
    
    // YL-open I do not cover the case of the "next" pointer 
    //
    if (t->isPointer()) {
        PtrType *pt = (PtrType *) t;
        string sz      = convertInt(array_size);
        if (get_by_name("ptr_" + sz + "_" + t_2_name) != NULL) return;

        out << "\n#define chk_ptr_"  << sz << "_" << t_2_name << "(a,b)";
        out << "{int i; int eq = 1; for (i=0;i<" << sz << ";i++)  chk_one_"<< type_2_name(pt->subType) <<"(*(a+i),*(b+i),eq);}\n\n";

        out << "\n#define cp_ptr_"  << sz << "_" << t_2_name << "(a,b)";
        out << "{int i; for (i=0;i<" << sz << ";i++)  cp_one_"<< type_2_name(pt->subType) <<"(*(a+i),*(b+i));}\n\n";

        out << "\n#define nondet_ptr_"  << sz << "_" << t_2_name << "(a)";
        out << "{int i; for (i=0;i<" << sz << ";i++)  nondet_one_"<< type_2_name(pt->subType) <<"(*(a+i));}\n\n";

        gen_chk_code(pt->subType,array_size,false);
        insert("ptr_" + sz + "_" + t_2_name , t);
    } else if (t->isArray()) {
        ArrayType *arr = (ArrayType *) t;
        string sz       = convertInt(array_size);
        if (!is_top) sz = convertInt(get_array_size(arr->size));

        if (get_by_name("arr_" + sz + "_" + t_2_name) != NULL) return;

        out << "\n#define chk_arr_" << sz << "_" << t_2_name << "(a,b)\\\n";
        out << "{int i; int eq = 1; for (i=0;i<" << sz << ";i++) chk_one_" 
            << type_2_name(arr->subType) << "(a[i],b[i],eq);}\n\n";

        out << "\n#define cp_arr_" << sz << "_" << t_2_name << "(a,b)\\\n";
        out << "{int i; for (i=0;i<" << sz << ";i++) cp_one_" 
            << type_2_name(arr->subType) << "(a[i],b[i]);}\n\n";

        out << "\n#define nondet_arr_" << sz << "_" << t_2_name << "(a)\\\n";
        out << "{int i; for (i=0;i<" << sz << ";i++) nondet_one_" 
            << type_2_name(arr->subType) << "(a);}\n\n";

        gen_chk_code(arr->subType,array_size,false);
        insert("arr_" + sz + "_" + t_2_name , t);
    } else if (!t->isFunction()) {
        BaseType *b = (BaseType *) t;
        BaseTypeSpec typemask = b->typemask;

        if (get_by_name(t_2_name) != NULL) return;

        // YL-open, I am not allowing typedef inside typedef
        if (typemask & BT_UserType) {
            BaseType *tmp_base; 

            if (!b->typeName) 
                out << "type :" << b->tag->entry->type << "\n";

            tmp_base = (b->typeName != NULL) ?
                       (BaseType *) b->typeName->entry->uVarDecl->form:
                       (BaseType *) b->tag->entry->uStructDef ;

            typemask = tmp_base->typemask;
            b        = tmp_base;

        }

        if (typemask & BT_Struct) {
            StructDef *stdefn = b->stDefn;
            int j, n;
            stringstream cp_ss;    
            stringstream nondet_ss;

            n = stdefn->nComponents ;

            // YL-open array under struct
            //         multidimensional array

            out   << "\n#define chk_one_" << t_2_name << "(a,b,eq) { \\\n" ;
            cp_ss << "\n#define cp_one_" << t_2_name << "(a,b) { \\\n" ;
            nondet_ss << "\n#define nondet_one_" << t_2_name << "(a) { \\\n" ;

            for (j=0;j<n;j++) {
                string fld_name = stdefn->components[j]->name->name;

                out << " chk_one_" << type_2_name(stdefn->components[j]->form) 
                    <<"(a." << fld_name << ",b." << fld_name << ",eq); \\\n";
                cp_ss << " cp_one_" << type_2_name(stdefn->components[j]->form) 
                    <<"(a." << fld_name << ",b." << fld_name << "); \\\n";
                nondet_ss << " nondet_one_" << type_2_name(stdefn->components[j]->form) 
                    <<"(a." << fld_name << "); \\\n";

                Decl *decl = stdefn->components[j]->next;
                while (decl != NULL) {
                   fld_name = decl->name->name;
                   out << " chk_one_" << type_2_name(decl->form) 
                       <<"(a." << fld_name << ",b." << fld_name << ",eq); \\\n";
                    cp_ss << " cp_one_" << type_2_name(stdefn->components[j]->form) 
                        <<"(a." << fld_name << ",b." << fld_name << "); \\\n";
                    nondet_ss << " nondet_one_" << type_2_name(stdefn->components[j]->form) 
                        <<"(a." << fld_name << "); \\\n";
                   decl = decl->next;
                }
            }
            out <<  "} \n";
            cp_ss <<  "} \n";
            nondet_ss <<  "} \n";
            
            // Create the macros, for the various fields, if thet are
            // needed
            for (j=0;j<n;j++) {
                gen_chk_code(stdefn->components[j]->form,array_size,false);
                Decl *decl = stdefn->components[j]->next;
                while (decl != NULL) {
                   decl = decl->next;
                   gen_chk_code(decl->form,array_size,false);
                }
            }

            out << cp_ss.str();
            out << nondet_ss.str();
        } else if (typemask & BT_Union ) {
            StructDef *stdefn = b->stDefn;
            stringstream cp_ss;    
            stringstream nondet_ss;
            int j, n;

            n = stdefn->nComponents ;

            out << "\n#define chk_one_" << t_2_name << "(a,b,eq) { \\\n" ;
            cp_ss << "\n#define cp_one_" << t_2_name << "(a,b) { \\\n" ;
            nondet_ss << "\n#define nondet_one_" << t_2_name << "(a) { \\\n" ;

            for (j=0;j<1;j++) {
                string fld_name = stdefn->components[j]->name->name;
                out << " chk_one_" << type_2_name(stdefn->components[j]->form) 
                    <<"(a." << fld_name << ",b." << fld_name << ",eq); \\\n";
                cp_ss << " cp_one_" << type_2_name(stdefn->components[j]->form) 
                    <<"(a." << fld_name << ",b." << fld_name << "); \\\n";
                nondet_ss << " chk_one_" << type_2_name(stdefn->components[j]->form) 
                    <<"(a." << fld_name << "); \\\n";
            }
            out <<  "}\n";
            cp_ss <<  "}\n";
            nondet_ss <<  "}\n";

            gen_chk_code(stdefn->components[0]->form,array_size,false);

            out << cp_ss.str();
            out << nondet_ss.str();
        } else if (typemask & BT_UserType) {
            out << "USER TYPE\n";
            BaseType *tmp_base = (BaseType *) b->typeName->entry->uVarDecl->form;
            BaseTypeSpec tmp_mask = tmp_base->typemask;
            b->typeName->entry->uVarDecl->form->printType( out, NULL, true, 0);
            out << b->typeName->entry->uVarDecl->form->type << "\n";

            out << "STRUCT " << (tmp_mask & BT_Struct) << "\n";
            out << "USER   " << (tmp_mask & BT_UserType) << "\n";
            out << "UNION  " << (tmp_mask & BT_Union) << "\n";

            tmp_base->printType(out,NULL,true,0);
        }
        // YL-open Enum + type need to think what to do
        insert(t_2_name , t);
    } else {
    }
}



void RvTypeEqMac::create_enum()
{
}


