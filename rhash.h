#ifndef KAUTIL_HASH_RHASH_RHASH_H
#define KAUTIL_HASH_RHASH_RHASH_H

#include <stdint.h>

struct st_kautil_rhash;

namespace kautil{
namespace hash{

    struct Rhash{
        
        Rhash();
        virtual ~Rhash();

        virtual int configure_sha3_256();
        virtual uint64_t digest_size();
        virtual uint64_t digest_string_size();
        virtual int buffer_update(const void * src,uint64_t const& src_len);
        virtual int buffer_generate(const void * digest);
        virtual int generate(const void * digest,const void * src,uint64_t const& src_len);
        virtual void reset();
        
        virtual int buffer_generate_string(const void * digest);
        virtual int generate_string(const void * digest,const void * src,uint64_t const& src_len);
        
    private:
        st_kautil_rhash * m = 0;
    }; // Rhash

    
    /** @note  sha3-256 struct Rhash needs to run configure_sha3_256 to specify context.
     *  Rhash_Sha3_256 omit this configuration process.  
     * **/
    struct Rhash_Sha3_256 : public Rhash{ 
        Rhash_Sha3_256();
        virtual ~Rhash_Sha3_256();
    private:
        using Rhash::configure_sha3_256;
    }; // Rhash
    
}// namespace hash{
} //namespace kautil{

extern "C" kautil::hash::Rhash * kautil_rhash_initialize();
extern "C" void kautil_rhash_release(kautil::hash::Rhash * );
extern "C" kautil::hash::Rhash_Sha3_256 * kautil_rhash_sha3_256_initialize();
extern "C" void kautil_rhash_sha3_256_release(kautil::hash::Rhash_Sha3_256 * obj);


#endif