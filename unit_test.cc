
#ifdef TMAIN_KAUTIL_HASH_RHASH_STATIC

#include "./rhash.h"
#include <stdint.h>
#include <vector>
#include <iostream>
#include <string>

int main(){

    auto src= std::string_view{"aaa"};
    auto src2= std::string_view{"abc"};
    auto digest = std::vector<uint8_t>{};
    auto o =[](auto digest,auto src){
        auto dst = std::string{};
        dst.resize(digest.size()*2);
    };

    
//    while(true)
//    for(auto i = 0; i < 10000 ; ++ i)
    {
        auto hash = kautil::hash::Rhash_Sha3_256{};
        // at once
        digest.resize(hash.digest_size());
        hash.generate(digest.data(),src.data(),src.size());
        hash.reset();
        o(digest,src);
        

        // update,same result with fst
        digest.resize(hash.digest_size());
        for(auto c : src) hash.buffer_update(&c,sizeof(c));
        hash.buffer_generate(digest.data());
        hash.reset();
        o(digest,src);
        
        // update,different result from fst
        digest.resize(hash.digest_size());
        for(auto c : src2) hash.buffer_update(&c,sizeof(c));
        hash.buffer_generate(digest.data());
        hash.reset();
        o(digest,src2);


        {
            auto digest_str= std::string(hash.digest_size()*2,'\0');
            hash.buffer_update(src.data(),src.size());
            hash.buffer_generate_string(digest_str.data());
            std::cout << digest_str << std::endl;
        }

    }


    return 0;
}


#endif