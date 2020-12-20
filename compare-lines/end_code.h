/*

    end_code.h: header untuk mengakhiri suatu bagian dari source code

*/

#ifdef _BEGIN_CODE_H
#undef _BEGIN_CODE_H

#undef MAX
#undef MIN
#undef TRACE
#undef DUMP
#undef ERROR
#undef STRINGIZE

/*
    jika macro yang asli diganti oleh macro yang baru, maka kembalikan definisi macro aslinya
    menggunakan #pragma pop_macro("NAMA MACRO")
*/

#ifdef _UNDEFINED_MAX
#undef _UNDEFINED_MAX
#pragma pop_macro("MAX")
#endif

#ifdef _UNDEFINED_MAX
#undef _UNDEFINED_MIN
#pragma pop_macro("MIN")
#endif

#ifdef _UNDEFINED_TRACE
#undef _UNDEFINED_TRACE
#pragma pop_macro("TRACE")
#endif

#ifdef _UNDEFINED_DUMP
#undef _UNDEFINED_DUMP
#pragma pop_macro("DUMP")
#endif

#ifdef _UNDEFINED_ERROR
#undef _UNDEFINED_ERROR
#pragma pop_macro("ERROR")
#endif

#ifdef _UNDEFINED_STRINGIZE
#undef _UNDEFINED_STRINGIZE
#pragma pop_macro("STRINGIZE")
#endif

#endif

