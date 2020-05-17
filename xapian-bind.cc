#include "xapian-bind.h"
#include "lib.rs.h"
#include <iostream>

#include <xapian.h>
#include <string>
#include <string.h>

namespace org {
namespace example {

ThingC::ThingC(std::string appname) : appname(std::move(appname)) {}

ThingC::~ThingC() { std::cout << "done with ThingC" << std::endl; }

std::unique_ptr<ThingC> make_demo(rust::Str appname) {
  return std::make_unique<ThingC>(std::string(appname));
}

const std::string &get_name(const ThingC &thing) { return thing.appname; }

void do_thing(SharedThing state) { print_r(*state.y); }

using namespace std;

char get_err_code (const char* type)
{
    signed char err = 0;
//    cout << "XAPIAN_D:" << type;
if (strcmp (type, (char*)"DatabaseModifiedError") == 0)
    err = -1;
else if (strcmp (type, (char*)"DatabaseLockError") == 0)
    err = -2;
else if (strcmp (type, (char*)"LogicError") == 0)
    err = -3;
else if (strcmp (type, (char*)"AssertionError") == 0)
    err = -4;
else if (strcmp (type, (char*)"InvalidArgumentError") == 0)
    err = -5;
else if (strcmp (type, (char*)"InvalidOperationError") == 0)
    err = -6;
else if (strcmp (type, (char*)"UnimplementedError") == 0) 
    err = -7;
else if (strcmp (type, (char*)"RuntimeError") == 0)
    err = -8;
else if (strcmp (type, (char*)"DatabaseError") == 0)
    err = -9;
else if (strcmp (type, (char*)"DatabaseCorruptError") == 0)
    err = -10;
else if (strcmp (type, (char*)"DatabaseCreateError") == 0)
    err = -11;
else if (strcmp (type, (char*)"DatabaseOpeningError") == 0)
    err = -12;
else if (strcmp (type, (char*)"DatabaseVersionError") == 0) 
    err = -13;
else if (strcmp (type, (char*)"DocNotFoundError") == 0)
    err = -14;
else if (strcmp (type, (char*)"FeatureUnavailableError") == 0)
    err = -15;
else if (strcmp (type, (char*)"InternalError") == 0)
    err = -16;
else if (strcmp (type, (char*)"NetworkError") == 0)
    err = -17;
else if (strcmp (type, (char*)"NetworkTimeoutError") == 0) 
    err = -18;
else if (strcmp (type, (char*)"QueryParserError") == 0)
    err = -19;
else if (strcmp (type, (char*)"RangeError") == 0)
    err = -20;
else if (strcmp (type, (char*)"SerialisationError") == 0) 
    err = -21;

   return err; 
}


///////////////////////////////////////////////////////////////////////////////////////
const int BRASS = 1;
const int CHERT = 2;
const int IN_MEMORY = 3;
/*
XapianDatabase* new_Database1(const char* _path, unsigned int _path_len, int db_type, signed char *err)
{
    try
    {
	    std::string path (_path, (unsigned long)_path_len);

	    Xapian::Database* db;
	     db = new Xapian::Database(path);
//	    if (db_type == BRASS)
//    	     db = new Xapian::Database(Xapian::Brass::open(path));
//	    else if (db_type == CHERT)
//    	     db = new Xapian::Database(Xapian::Chert::open(path));
//	    else if (db_type == IN_MEMORY)
//    	     db = new Xapian::Database(Xapian::InMemory::open());


	    XapianDatabase* _new = new XapianDatabase ();
	    _new->db = db;
        *err = 0;
        return _new;
    }
    catch (Xapian::Error ex)
    {	    
        *err = get_err_code (ex.get_type ());
        return NULL;
    }
}
*/


} // namespace example
} // namespace org

using namespace Xapian;

const int BRASS = 1;
const int CHERT = 2;
const int IN_MEMORY = 3;

/** Open for read/write; create if no db exists. */
const int DB_CREATE_OR_OPEN      = 1;
/** Create a new database; fail if db exists. */
const int DB_CREATE              = 2;
/** Overwrite existing db; create if none exists. */
const int DB_CREATE_OR_OVERWRITE = 3;

std::unique_ptr<Database> new_database(int8_t &err) {
    try
    {
        err = 0;
        return std::make_unique<Xapian::Database>();
        
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
        return NULL;
    }
}

std::unique_ptr<Database> new_database_with_path(rust::Str path, int8_t db_type, int8_t &err) {
    try
    {
        err = 0;

	    if (db_type == BRASS)
    	     return std::make_unique<Database>(Brass::open(std::string(path)));
	    else if (db_type == CHERT)
    	     return std::make_unique<Database>(Chert::open(std::string(path)));
	    else if (db_type == IN_MEMORY)
    	     return std::make_unique<Database>(InMemory::open());
    	else      
			return std::make_unique<Database>(std::string(path));

    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
        return NULL;
    }
}

void database_reopen (Database &db, int8_t &err) {
    try
    {
		db.reopen ();
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
    }
}

std::unique_ptr<Stem> new_stem(rust::Str lang, int8_t &err) {
    try
    {
        err = 0;
        return std::make_unique<Stem>(std::string(lang));
        
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
        return NULL;
    }	
}

///////////////////////////////////////////////////////////////
std::unique_ptr<WritableDatabase> new_writable_database_with_path(rust::Str path, int8_t action, int8_t db_type, int8_t &err) {
    try
    {
        err = 0;

		return std::make_unique<WritableDatabase>(std::string(path), action);

    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
        return NULL;
    }

}

void commit (WritableDatabase &db, int8_t &err) {
    try
    {
		db.commit ();
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
    }
}


docid replace_document(WritableDatabase &db, rust::Str unique_term, Document &doc,  int8_t &err) {
    try
    {		
		return db.replace_document (std::string(unique_term), doc);
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
        return -1;
    }
}

void delete_document(WritableDatabase &db, rust::Str unique_term, Document &doc,  int8_t &err) {
    try
    {		
		db.replace_document (std::string(unique_term), doc);
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
    }
}


////////////////////////////////////////////////////////////////

std::unique_ptr<TermGenerator> new_termgenerator(int8_t &err) {
    try
    {
        err = 0;
        return std::make_unique<TermGenerator>();
        
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
        return NULL;
    }
}

void set_stemmer (TermGenerator &tg, Stem &stem, int8_t &err) {
    try
    {
		tg.set_stemmer (stem);
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
    }
}

void set_document (TermGenerator &tg, Document &doc, int8_t &err) {
    try
    {
        err = 0;
        tg.set_document(doc);
        
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
    }
}

void index_text (TermGenerator &tg, rust::Str data, int8_t &err) {
    try
    {
        err = 0;
        tg.index_text(std::string(data));
        
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
    }
}

void index_int (TermGenerator &tg, int32_t in_data, int8_t &err) {
    try
    {
        err = 0;
        std::string data = sortable_serialise(in_data);
        tg.index_text(data);
        
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
    }
}

void index_long (TermGenerator &tg, int64_t in_data, int8_t &err) {
    try
    {
        err = 0;
        std::string data = sortable_serialise(in_data);
        tg.index_text(data);
        
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
    }
}

void index_float (TermGenerator &tg, float in_data, int8_t &err) {
    try
    {
        err = 0;
        std::string data = sortable_serialise(in_data);
        tg.index_text(data);
        
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
    }
}

void index_double (TermGenerator &tg, double in_data, int8_t &err) {
    try
    {
        err = 0;
        std::string data = sortable_serialise(in_data);
        tg.index_text(data);
        
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
    }
}

////////////////////////////////////////////////////////////////

std::unique_ptr<Document> new_document (int8_t &err) {
    try
    {
        err = 0;
        return std::make_unique<Document>();
        
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
        return NULL;
    }
}

void add_string (Document &doc, valueno slot, rust::Str data, int8_t &err) {
    try
    {
        err = 0;
        doc.add_value(slot, std::string(data));        
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
    }
}

void add_int (Document &doc, valueno slot, int in_data, int8_t &err) {
    try
    {
        err = 0;
        std::string data = sortable_serialise(in_data);
        doc.add_value(slot, data);        
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
    }
}

void set_data (Document &doc, rust::Str data, int8_t &err) {
    try
    {
        err = 0;
        doc.set_data(std::string(data));        
    }
    catch (Xapian::Error ex)
    {	    
        err = org::example::get_err_code (ex.get_type ());
    }
}