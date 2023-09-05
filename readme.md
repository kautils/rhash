### kautil_hash_rhash
* wrapper of rhash
* possible to extern via dlopen / Loadlibrary

### note 
* this is written with mingw
* it requires some more dependency if build with mingw 
* dlls on this [page(MSYS2 Packages)](https://packages.msys2.org/package/mingw-w64-x86_64-rhash?repo=mingw64) should be prenty to run this module.  

### example

````c++

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


````
