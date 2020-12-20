/*

    begin_code.h: header untuk mengawali suatu bagian dari source code

*/
#ifndef _BEGIN_CODE_H
#define _BEGIN_CODE_H

/*
    cek apakah macro sebelumnya telah terdefinisi
    jika sudah terdefinisi, simpan definisi macro yang asli kemudian ganti sementara dengan definisi macro yang baru
    penyimpanan menggunakan #pragma push_macro("NAMA MACRO")
*/

#ifdef MAX
#pragma push_macro("MAX")
#undef MAX
#define _UNDEFINED_MAX
#endif
#define MAX(_A, _B) (((_A) > (_B)) ? (_A) : (_B))

#ifdef MIN
#pragma push_macro("MIN")
#undef MIN
#define _UNDEFINED_MIN
#endif
#define MIN(_A, _B) (((_A) < (_B)) ? (_A) : (_B))

#ifdef TRACE
#pragma push_macro("TRACE")
#undef TRACE
#define _UNDEFINED_TRACE
#endif
#ifndef NDEBUG
#define TRACE(_X) printf("[%s] %s\n", __FUNCTION__, (_X))
#else
#define TRACE(_X)
#endif

#ifdef DUMP
#pragma push_macro("DUMP")
#undef DUMP
#define _UNDEFINED_DUMP
#endif
#ifndef NDEBUG
#define DUMP(_Format, _X) printf("[%s] dump `" #_X "`: %" #_Format "\n", __FUNCTION__, (_X))
#else
#define DUMP(_Format, _X)
#endif

#ifdef ERROR
#pragma push_macro("ERROR")
#undef ERROR
#define _UNDEFINED_ERROR
#endif
#define ERROR(_Str) printf("[%s] E: %s\n", __FUNCTION__, (_Str))

#undef __STRINGIZE
#define __STRINGIZE(_X) #_X /* implementasi internal, jika _X adalah suatu macro, maka yang dihasilkan adalah nama macro tsb (bukan isi dari macro tsb) */

#ifdef STRINGIZE
#pragma push_macro("STRINGIZE")
#undef STRINGIZE
#define _UNDEFINED_STRINGIZE
#endif
#define STRINGIZE(_X) __STRINGIZE(_X) /* supaya dapat mensubstitusi nama macro dengan isi macro nya sehingga nama macro dievaluasi di sini terlebih dahulu sehingga mendapatkan nilai dari macro tsb kemudian nilai tsb diubah dalam bentuk string oleh fungsi __STRINGIZE */

#endif

