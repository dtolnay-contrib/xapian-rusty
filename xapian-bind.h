#pragma once
#include "rust/cxx.h"
#include <memory>
#include <xapian.h>
#include <string>
#include <string.h>


namespace org {
namespace example {

class ThingC {
public:
  ThingC(std::string appname);
  ~ThingC();

  std::string appname;
};

struct SharedThing;

std::unique_ptr<ThingC> make_demo(rust::Str appname);
const std::string &get_name(const ThingC &thing);
void do_thing(SharedThing state);

char get_err_code (const char* type);

using namespace std;


} // namespace example
} // namespace org

using namespace Xapian;

std::unique_ptr<Database> new_database(int8_t &err);

//
std::unique_ptr<Database> new_database_with_path(rust::Str path, int8_t db_type, int8_t &err);
void database_reopen (Database &db, int8_t &err);

//
std::unique_ptr<Stem> new_stem(rust::Str lang, int8_t &err);

//
std::unique_ptr<WritableDatabase> new_writable_database_with_path(rust::Str path, int8_t action, int8_t db_type, int8_t &err);
void commit (WritableDatabase &db, int8_t &err);
docid replace_document(WritableDatabase &db, rust::Str unique_term, Document &doc,  int8_t &err);
void delete_document(WritableDatabase &db, rust::Str unique_term, Document &doc,  int8_t &err);

//
std::unique_ptr<TermGenerator> new_termgenerator(int8_t &err);
void set_stemmer (TermGenerator &tg, Stem &stem, int8_t &err);
void set_document (TermGenerator &tg, Document &doc, int8_t &err);
void index_text (TermGenerator &tg, rust::Str data, int8_t &err);
void index_int (TermGenerator &tg, int32_t data, int8_t &err);
void index_long (TermGenerator &tg, int64_t data, int8_t &err);
void index_float (TermGenerator &tg, float data, int8_t &err);
void index_double (TermGenerator &tg, double data, int8_t &err);

//
std::unique_ptr<Document> new_document (int8_t &err);
void add_string (Document &doc, valueno slot, rust::Str data, int8_t &err);
void add_int (Document &doc, valueno slot, int data, int8_t &err);
void set_data (Document &doc, rust::Str data, int8_t &err);
