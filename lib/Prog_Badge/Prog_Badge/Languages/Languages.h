#pragma once

#ifndef TR_LANGUAGE
#error No language defined!
#endif

#define LANG_STRINGIFY(x) #x
#define LANG_HEADER(lang) LANG_STRINGIFY(lang.h)
#include LANG_HEADER(TR_LANGUAGE)
#undef LANG_STRINGIFY
#undef LANG_HEADER
