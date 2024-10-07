#include "RandomClan.h"
#include "../Define/Definition.h"
std::wstring RandomWstring(unsigned int Seed, DWORD dwStyle, size_t min_length, size_t max_length) {
    switch (Seed)
    {
    case 0: {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        break;
    }
    default: {
        std::srand(Seed);
        break;
    }
    };
    std::wstring characters;
        
    switch (dwStyle)
    {
    case RSS_DEFAULT: {
        characters =
            L"0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        break;
    }
    case RSS_MIXSYNBOLS: {
        characters =
            L"0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "~!@#$%^&*()_+=-<>?,./{}[];':\"";
        break;
    }
    case RSS_CHINESE: {
        characters =
            L"0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "Ñ¨±ÆÆ‹ŒÂ";
        break;
    }
    default: {
        characters =
            L"0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        break;
    }
    };


    const size_t length = min_length + std::rand() % (max_length - min_length + 1);

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::wstring random_string;
    for (size_t i = 0; i < length; ++i) {
        random_string += characters[distribution(generator)];
    }

    return random_string;
}

