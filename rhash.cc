#include "./rhash.h"
#include <rhash.h>

struct st_kautil_rhash{
    st_kautil_rhash(){
        static auto kInitOnce =[]()->bool{ 
            rhash_library_init();return true;
        }.operator()();
    }
    rhash ctx = nullptr;
    unsigned current = RHASH_SHA3_256; // ? may cause confusion
    
};


kautil::hash::Rhash::Rhash() : m(new st_kautil_rhash){}
kautil::hash::Rhash::~Rhash() {
    if(m){
        rhash_free(m->ctx);
        m->ctx=0;
        delete m; 
    }
}
int kautil::hash::Rhash::configure_sha3_256() {
    if(m->ctx) rhash_free(m->ctx);
    m->ctx = rhash_init((m->current= RHASH_SHA3_256) );
    return 0;
}
uint64_t kautil::hash::Rhash::digest_size() { return rhash_get_digest_size(m->current); }
uint64_t kautil::hash::Rhash::digest_string_size() { return rhash_get_digest_size(m->current)*2; }


int kautil::hash::Rhash::buffer_update(const void *src, const uint64_t &src_len) { return rhash_update(m->ctx,src,src_len); }
int kautil::hash::Rhash::buffer_generate(const void *digest) { return rhash_print((char*)digest,m->ctx, m->current, RHPR_RAW) ? 0 : 1; }
int kautil::hash::Rhash::generate(const void *digest, const void *src, const uint64_t &src_len) { return !rhash_update(m->ctx,src,src_len) && rhash_print((char*)digest,m->ctx, m->current, RHPR_RAW) ? 0 : 1; }
void kautil::hash::Rhash::reset() { rhash_reset(m->ctx); }
int kautil::hash::Rhash::generate_string(const void *digest, const void *src, const uint64_t &src_len) { return !rhash_update(m->ctx,src,src_len) && rhash_print((char*)digest,m->ctx, m->current, RHPR_HEX) ? 0 : 1; }
int kautil::hash::Rhash::buffer_generate_string(const void *digest) { 
    return rhash_print((char*)digest,m->ctx, m->current, RHPR_HEX) ? 0 : 1;
}

kautil::hash::Rhash_Sha3_256::Rhash_Sha3_256() : Rhash() { Rhash::configure_sha3_256(); }
kautil::hash::Rhash_Sha3_256::~Rhash_Sha3_256() {}



extern "C" kautil::hash::Rhash * kautil_rhash_initialize(){ return new kautil::hash::Rhash; }
extern "C" void kautil_rhash_release(kautil::hash::Rhash * obj){ delete obj; }
extern "C" kautil::hash::Rhash_Sha3_256 * kautil_rhash_sha3_256_initialize(){ return new kautil::hash::Rhash_Sha3_256; }
extern "C" void kautil_rhash_sha3_256_release(kautil::hash::Rhash_Sha3_256 * obj){ delete obj; }

